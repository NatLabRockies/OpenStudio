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
#include "../SetpointManager/SetpointManagerSystemNodeResetTemperature.hpp"
#include "../SetpointManager/SetpointManagerSystemNodeResetTemperature_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/SetpointManager_SystemNodeReset_Temperature_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedSystemNodeResetTemperatureFileRemoval
{
 public:
  explicit ScopedSystemNodeResetTemperatureFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedSystemNodeResetTemperatureFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueSystemNodeResetTemperatureIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_DefaultConstructor) {
  Model model;
  SetpointManagerSystemNodeResetTemperature spm(model);
  EXPECT_EQ(SetpointManagerSystemNodeResetTemperature::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerSystemNodeResetTemperature spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_DOUBLE_EQ(16.7, spm.setpointatLowReferenceTemperature());
  EXPECT_DOUBLE_EQ(12.8, spm.setpointatHighReferenceTemperature());
  EXPECT_DOUBLE_EQ(20.0, spm.lowReferenceTemperature());
  EXPECT_DOUBLE_EQ(23.3, spm.highReferenceTemperature());

  const auto controlVariableValues = SetpointManagerSystemNodeResetTemperature::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  std::string controlVariable = controlVariableValues.front();
  if ((controlVariable == spm.controlVariable()) && (controlVariableValues.size() > 1u)) {
    controlVariable = controlVariableValues.back();
  }
  EXPECT_TRUE(spm.setControlVariable(controlVariable));
  EXPECT_EQ(controlVariable, spm.controlVariable());

  EXPECT_TRUE(spm.setSetpointatLowReferenceTemperature(15.4));
  EXPECT_TRUE(spm.setSetpointatHighReferenceTemperature(11.9));
  EXPECT_TRUE(spm.setLowReferenceTemperature(19.6));
  EXPECT_TRUE(spm.setHighReferenceTemperature(24.2));

  EXPECT_DOUBLE_EQ(15.4, spm.setpointatLowReferenceTemperature());
  EXPECT_DOUBLE_EQ(11.9, spm.setpointatHighReferenceTemperature());
  EXPECT_DOUBLE_EQ(19.6, spm.lowReferenceTemperature());
  EXPECT_DOUBLE_EQ(24.2, spm.highReferenceTemperature());
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_ReferenceNodeValidationAndRawReset) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  SetpointManagerSystemNodeResetTemperature spm(model);
  auto setpointNode = airLoop.supplyOutletNode();
  auto airReferenceNode = airLoop.supplyInletNode();
  auto plantReferenceNode = plantLoop.supplyInletNode();

  EXPECT_FALSE(spm.referenceNode());
  ASSERT_TRUE(spm.addToNode(setpointNode));
  ASSERT_TRUE(spm.setReferenceNode(airReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(airReferenceNode.handle(), spm.referenceNode()->handle());
  ASSERT_TRUE(spm.setpointNode());
  EXPECT_EQ(setpointNode.handle(), spm.setpointNode()->handle());
  EXPECT_NE(spm.referenceNode()->handle(), spm.setpointNode()->handle());

  ASSERT_TRUE(spm.setReferenceNode(plantReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(plantReferenceNode.handle(), spm.referenceNode()->handle());
  EXPECT_EQ(setpointNode.handle(), spm.setpointNode()->handle());

  Model foreignModel;
  AirLoopHVAC foreignAirLoop(foreignModel);
  const auto foreignReferenceNode = foreignAirLoop.supplyInletNode();
  EXPECT_FALSE(spm.setReferenceNode(foreignReferenceNode));
  ASSERT_TRUE(spm.referenceNode());
  EXPECT_EQ(plantReferenceNode.handle(), spm.referenceNode()->handle());

  SetpointManagerSystemNodeResetTemperature malformed(model);
  auto workspaceImpl = malformed.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto referenceField = openstudio::SetpointManager_SystemNodeReset_TemperatureFields::ReferenceNodeName;

  // This unresolved raw field represents imported malformed state that validated public setters cannot create.
  ASSERT_TRUE(workspaceImpl->setPointer(referenceField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(referenceField, "Missing Temperature Reference Node", false));
  EXPECT_FALSE(malformed.referenceNode());
  EXPECT_EQ("Missing Temperature Reference Node",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));
  EXPECT_FALSE(malformed.setReferenceNode(foreignReferenceNode));
  EXPECT_EQ("Missing Temperature Reference Node",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));

  malformed.resetReferenceNode();
  EXPECT_FALSE(malformed.referenceNode());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(referenceField, false, true).value_or(""));
}

TEST_F(EPModelFixture, SetpointManagerSystemNodeResetTemperature_ReferenceNodeReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueSystemNodeResetTemperatureIdfPath("epmodel-system-node-reset-temperature-first");
  const auto secondIdfPath = uniqueSystemNodeResetTemperatureIdfPath("epmodel-system-node-reset-temperature-second");
  const ScopedSystemNodeResetTemperatureFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedSystemNodeResetTemperatureFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  SetpointManagerSystemNodeResetTemperature spm(model);
  ASSERT_TRUE(airLoop.setName("Temperature Reference Air Loop"));
  ASSERT_TRUE(plantLoop.setName("Temperature Reference Plant Loop"));
  ASSERT_TRUE(spm.setName("System Node Reset Temperature Manager"));
  auto setpointNode = airLoop.supplyOutletNode();
  auto initialReferenceNode = plantLoop.supplyInletNode();
  ASSERT_TRUE(spm.addToNode(setpointNode));
  ASSERT_TRUE(spm.setReferenceNode(initialReferenceNode));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedAirLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Temperature Reference Air Loop");
  auto loadedPlantLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Temperature Reference Plant Loop");
  auto loadedManager = loadedModel->getConcreteModelObjectByName<SetpointManagerSystemNodeResetTemperature>("System Node Reset Temperature Manager");
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
  auto reloadedAirLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Temperature Reference Air Loop");
  auto reloadedPlantLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Temperature Reference Plant Loop");
  auto reloadedManager =
    reloadedModel->getConcreteModelObjectByName<SetpointManagerSystemNodeResetTemperature>("System Node Reset Temperature Manager");
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
