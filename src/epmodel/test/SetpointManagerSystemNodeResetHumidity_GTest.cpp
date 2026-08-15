/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../SetpointManager/SetpointManagerSystemNodeResetHumidity.hpp"
#include "../SetpointManager/SetpointManagerSystemNodeResetHumidity_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/SetpointManager_SystemNodeReset_Humidity_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedSystemNodeResetHumidityFileRemoval
{
 public:
  explicit ScopedSystemNodeResetHumidityFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedSystemNodeResetHumidityFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueSystemNodeResetHumidityIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_DefaultConstructor) {
  Model model;
  SetpointManagerSystemNodeResetHumidity spm(model);
  EXPECT_EQ(SetpointManagerSystemNodeResetHumidity::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSystemNodeResetHumidity spm(model);

  EXPECT_EQ("MaximumHumidityRatio", spm.controlVariable());
  EXPECT_DOUBLE_EQ(0.00924, spm.setpointatLowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.00600, spm.setpointatHighReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.00850, spm.lowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.01000, spm.highReferenceHumidityRatio());

  const auto controlVariableValues = SetpointManagerSystemNodeResetHumidity::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_TRUE(spm.setControlVariable("MinimumHumidityRatio"));
  EXPECT_EQ("MinimumHumidityRatio", spm.controlVariable());

  EXPECT_TRUE(spm.setSetpointatLowReferenceHumidityRatio(0.002));
  EXPECT_TRUE(spm.setSetpointatHighReferenceHumidityRatio(0.001));
  EXPECT_TRUE(spm.setLowReferenceHumidityRatio(0.004));
  EXPECT_TRUE(spm.setHighReferenceHumidityRatio(0.003));

  EXPECT_DOUBLE_EQ(0.002, spm.setpointatLowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.001, spm.setpointatHighReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.004, spm.lowReferenceHumidityRatio());
  EXPECT_DOUBLE_EQ(0.003, spm.highReferenceHumidityRatio());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_ReferenceNodeValidationAndRawReset) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  SetpointManagerSystemNodeResetHumidity spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  auto airReferenceNode = airLoop.supplyInletNode();
  auto plantReferenceNode = plantLoop.supplyInletNode();

  EXPECT_FALSE(spm.referenceNode());
  ASSERT_TRUE(spm.addToNode(setpointNode));
  ASSERT_TRUE(spm.setReferenceNode(plantReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(plantReferenceNode.handle(), spm.referenceNode()->handle());
  ASSERT_TRUE(spm.setpointNode());
  EXPECT_EQ(setpointNode.handle(), spm.setpointNode()->handle());
  EXPECT_NE(spm.referenceNode()->handle(), spm.setpointNode()->handle());

  ASSERT_TRUE(spm.setReferenceNode(airReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(airReferenceNode.handle(), spm.referenceNode()->handle());
  EXPECT_EQ(setpointNode.handle(), spm.setpointNode()->handle());

  Model foreignModel;
  PlantLoop foreignPlantLoop(foreignModel);
  const auto foreignReferenceNode = foreignPlantLoop.supplyInletNode();
  EXPECT_FALSE(spm.setReferenceNode(foreignReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(airReferenceNode.handle(), spm.referenceNode()->handle());

  SetpointManagerSystemNodeResetHumidity malformed(model);
  auto workspaceImpl = malformed.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto referenceField = openstudio::SetpointManager_SystemNodeReset_HumidityFields::ReferenceNodeName;

  // This unresolved raw field represents imported malformed state that validated public setters cannot create.
  ASSERT_TRUE(workspaceImpl->setPointer(referenceField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(referenceField, "Missing Humidity Reference Node", false));
  EXPECT_FALSE(malformed.referenceNode());
  EXPECT_EQ("Missing Humidity Reference Node",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));
  EXPECT_FALSE(malformed.setReferenceNode(foreignReferenceNode));
  EXPECT_EQ("Missing Humidity Reference Node",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));

  malformed.resetReferenceNode();
  EXPECT_FALSE(malformed.referenceNode());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetHumidity_ReferenceNodeReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueSystemNodeResetHumidityIdfPath("epmodel-system-node-reset-humidity-first");
  const auto secondIdfPath = uniqueSystemNodeResetHumidityIdfPath("epmodel-system-node-reset-humidity-second");
  const ScopedSystemNodeResetHumidityFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedSystemNodeResetHumidityFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  SetpointManagerSystemNodeResetHumidity spm(model);
  ASSERT_TRUE(airLoop.setName("Humidity Reference Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Humidity Reference Plant Loop"));
  ASSERT_TRUE(spm.setName("System Node Reset Humidity Manager"));
  auto setpointNode = airLoop.supplyOutletNode();
  auto initialReferenceNode = plantLoop.supplyInletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));
  ASSERT_TRUE(spm.setReferenceNode(initialReferenceNode));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Humidity Reference Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Humidity Reference Plant Loop");
  auto loadedManager = loadedModel->getConcreteModelObjectByName<SetpointManagerSystemNodeResetHumidity>("System Node Reset Humidity Manager");
  ASSERT_TRUE(loadedAirLoop);
  ASSERT_TRUE(loadedPlantLoop);
  ASSERT_TRUE(loadedManager);
  const auto loadedSetpointNode = loadedAirLoop->supplyOutletNode();
  const auto loadedInitialReferenceNode = loadedPlantLoop->supplyInletNode();
  ASSERT_TRUE(loadedManager->setpointNode());
  ASSERT_TRUE(loadedManager->referenceNode());
  EXPECT_EQ(loadedSetpointNode.handle(), loadedManager->setpointNode()->handle());
  EXPECT_EQ(loadedInitialReferenceNode.handle(), loadedManager->referenceNode()->handle());

  loadedManager->resetReferenceNode();
  EXPECT_FALSE(loadedManager->referenceNode());
  ASSERT_TRUE(loadedManager->setpointNode());
  EXPECT_EQ(loadedSetpointNode.handle(), loadedManager->setpointNode()->handle());
  const auto replacementReferenceNode = loadedAirLoop->demandOutletNode();
  ASSERT_TRUE(loadedManager->setReferenceNode(replacementReferenceNode));
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Humidity Reference Air Loop");
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Humidity Reference Plant Loop");
  auto reloadedManager = reloadedModel->getConcreteModelObjectByName<SetpointManagerSystemNodeResetHumidity>("System Node Reset Humidity Manager");
  ASSERT_TRUE(reloadedAirLoop);
  ASSERT_TRUE(reloadedPlantLoop);
  ASSERT_TRUE(reloadedManager);
  const auto reloadedSetpointNode = reloadedAirLoop->supplyOutletNode();
  const auto reloadedReferenceNode = reloadedAirLoop->demandOutletNode();
  const auto retainedPlantNode = reloadedPlantLoop->supplyInletNode();
  ASSERT_TRUE(reloadedManager->referenceNode());
  ASSERT_TRUE(reloadedManager->setpointNode());
  EXPECT_EQ(reloadedReferenceNode.handle(), reloadedManager->referenceNode()->handle());
  EXPECT_EQ(reloadedSetpointNode.handle(), reloadedManager->setpointNode()->handle());

  EXPECT_FALSE(reloadedManager->remove().empty());
  EXPECT_TRUE(reloadedSetpointNode.setpointManagers().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedAirLoop->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedPlantLoop->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedSetpointNode.handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReferenceNode.handle()));
  EXPECT_TRUE(reloadedModel->getObject(retainedPlantNode.handle()));
}
