/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ParentObject/RefrigerationSecondarySystem.hpp"
#include "../ParentObject/RefrigerationSecondarySystem_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Refrigeration_SecondarySystem_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedSecondarySystemFileRemoval
{
 public:
  explicit ScopedSecondarySystemFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedSecondarySystemFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueSecondarySystemPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, RefrigerationSecondarySystem_DefaultConstructor) {
  Model model;
  RefrigerationSecondarySystem secondarySystem(model);
  EXPECT_EQ(RefrigerationSecondarySystem::iddObjectType(), openstudio::IddObjectType::Refrigeration_SecondarySystem);
  EXPECT_FALSE(secondarySystem.distributionPipingZone());
  EXPECT_FALSE(secondarySystem.receiverSeparatorZone());
}

TEST_F(EPModelFixture, RefrigerationSecondarySystem_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationSecondarySystem secondarySystem(model);

  EXPECT_TRUE(secondarySystem.setEvaporatorEvaporatingTemperature(-12.5));
  EXPECT_DOUBLE_EQ(-12.5, secondarySystem.evaporatorEvaporatingTemperature());

  EXPECT_TRUE(secondarySystem.setEvaporatorApproachTemperatureDifference(3.1));
  EXPECT_DOUBLE_EQ(3.1, secondarySystem.evaporatorApproachTemperatureDifference());

  EXPECT_TRUE(secondarySystem.setEvaporatorRangeTemperatureDifference(5.0));
  EXPECT_DOUBLE_EQ(5.0, secondarySystem.evaporatorRangeTemperatureDifference().get());
  secondarySystem.resetEvaporatorRangeTemperatureDifference();
  EXPECT_FALSE(secondarySystem.evaporatorRangeTemperatureDifference());

  EXPECT_TRUE(secondarySystem.setNumberofPumpsinLoop(3));
  EXPECT_EQ(3, secondarySystem.numberofPumpsinLoop());
  secondarySystem.resetNumberofPumpsinLoop();
  EXPECT_TRUE(secondarySystem.isNumberofPumpsinLoopDefaulted());

  EXPECT_TRUE(secondarySystem.setTotalPumpFlowRate(0.003));
  EXPECT_DOUBLE_EQ(0.003, secondarySystem.totalPumpFlowRate().get());
  secondarySystem.resetTotalPumpFlowRate();
  EXPECT_FALSE(secondarySystem.totalPumpFlowRate());

  EXPECT_TRUE(secondarySystem.setTotalPumpPower(450.0));
  EXPECT_DOUBLE_EQ(450.0, secondarySystem.totalPumpPower().get());
  secondarySystem.resetTotalPumpPower();
  EXPECT_FALSE(secondarySystem.totalPumpPower());

  EXPECT_TRUE(secondarySystem.setTotalPumpHead(2.1e5));
  EXPECT_DOUBLE_EQ(2.1e5, secondarySystem.totalPumpHead().get());
  secondarySystem.resetTotalPumpHead();
  EXPECT_FALSE(secondarySystem.totalPumpHead());

  EXPECT_TRUE(secondarySystem.setPhaseChangeCirculatingRate(3.3));
  EXPECT_DOUBLE_EQ(3.3, secondarySystem.phaseChangeCirculatingRate());
  secondarySystem.resetPhaseChangeCirculatingRate();
  EXPECT_TRUE(secondarySystem.isPhaseChangeCirculatingRateDefaulted());

  EXPECT_TRUE(secondarySystem.setPumpMotorHeattoFluid(0.92));
  EXPECT_DOUBLE_EQ(0.92, secondarySystem.pumpMotorHeattoFluid());
  secondarySystem.resetPumpMotorHeattoFluid();
  EXPECT_TRUE(secondarySystem.isPumpMotorHeattoFluidDefaulted());

  EXPECT_TRUE(secondarySystem.setSumUADistributionPiping(1.2));
  EXPECT_DOUBLE_EQ(1.2, secondarySystem.sumUADistributionPiping());
  secondarySystem.resetSumUADistributionPiping();
  EXPECT_TRUE(secondarySystem.isSumUADistributionPipingDefaulted());

  EXPECT_TRUE(secondarySystem.setSumUAReceiverSeparatorShell(2.4));
  EXPECT_DOUBLE_EQ(2.4, secondarySystem.sumUAReceiverSeparatorShell());
  secondarySystem.resetSumUAReceiverSeparatorShell();
  EXPECT_TRUE(secondarySystem.isSumUAReceiverSeparatorShellDefaulted());

  EXPECT_TRUE(secondarySystem.setEvaporatorRefrigerantInventory(15.0));
  EXPECT_DOUBLE_EQ(15.0, secondarySystem.evaporatorRefrigerantInventory());
  secondarySystem.resetEvaporatorRefrigerantInventory();
  EXPECT_TRUE(secondarySystem.isEvaporatorRefrigerantInventoryDefaulted());

  EXPECT_TRUE(secondarySystem.setEndUseSubcategory("Custom"));
  EXPECT_EQ("Custom", secondarySystem.endUseSubcategory());
  secondarySystem.resetEndUseSubcategory();
  EXPECT_TRUE(secondarySystem.isEndUseSubcategoryDefaulted());

  const auto pumpDriveTypes = RefrigerationSecondarySystem::pumpDriveTypeValues();
  ASSERT_FALSE(pumpDriveTypes.empty());
  EXPECT_TRUE(secondarySystem.setPumpDriveType(pumpDriveTypes.back()));
  EXPECT_EQ(pumpDriveTypes.back(), secondarySystem.pumpDriveType());
  secondarySystem.resetPumpDriveType();
  EXPECT_TRUE(secondarySystem.isPumpDriveTypeDefaulted());
}

TEST_F(EPModelFixture, RefrigerationSecondarySystem_HeatGainZonesValidationAndUnresolvedState) {
  Model model;
  RefrigerationSecondarySystem system(model);
  ThermalZone distributionZone(model);
  ThermalZone receiverZone(model);
  constexpr auto distributionField = openstudio::Refrigeration_SecondarySystemFields::DistributionPipingZoneName;
  constexpr auto receiverField = openstudio::Refrigeration_SecondarySystemFields::Receiver_SeparatorZoneName;

  EXPECT_TRUE(model.canBeTarget(distributionZone.handle(), system.iddObject().objectLists(distributionField)));
  EXPECT_TRUE(model.canBeTarget(receiverZone.handle(), system.iddObject().objectLists(receiverField)));
  ASSERT_TRUE(system.setDistributionPipingZone(distributionZone));
  ASSERT_TRUE(system.setReceiverSeparatorZone(receiverZone));
  EXPECT_EQ(distributionZone.handle(), system.distributionPipingZone()->handle());
  EXPECT_EQ(receiverZone.handle(), system.receiverSeparatorZone()->handle());

  Model foreignModel;
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(system.setDistributionPipingZone(foreignZone));
  EXPECT_FALSE(system.setReceiverSeparatorZone(foreignZone));
  EXPECT_EQ(distributionZone.handle(), system.distributionPipingZone()->handle());
  EXPECT_EQ(receiverZone.handle(), system.receiverSeparatorZone()->handle());
  system.resetDistributionPipingZone();
  system.resetReceiverSeparatorZone();
  EXPECT_FALSE(system.distributionPipingZone());
  EXPECT_FALSE(system.receiverSeparatorZone());

  RefrigerationSecondarySystem unresolved(model);
  // Public typed APIs cannot create unresolved object-list references. Seed these imported malformed fields deliberately to
  // prove that canonicalization and failed typed mutation preserve them until explicit resets.
  auto impl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(impl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(impl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(impl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) { return impl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""); };
  setUnresolvedRaw(distributionField, "Missing Distribution Piping Zone");
  setUnresolvedRaw(receiverField, "Missing Receiver Separator Zone");
  EXPECT_FALSE(unresolved.distributionPipingZone());
  EXPECT_FALSE(unresolved.receiverSeparatorZone());
  EXPECT_FALSE(unresolved.setDistributionPipingZone(foreignZone));
  EXPECT_FALSE(unresolved.setReceiverSeparatorZone(foreignZone));
  EXPECT_EQ(0u, model.canonicalize().errorCount);
  EXPECT_EQ("Missing Distribution Piping Zone", rawValue(distributionField));
  EXPECT_EQ("Missing Receiver Separator Zone", rawValue(receiverField));
  unresolved.resetDistributionPipingZone();
  unresolved.resetReceiverSeparatorZone();
  EXPECT_TRUE(rawValue(distributionField).empty());
  EXPECT_TRUE(rawValue(receiverField).empty());
}

TEST_F(EPModelFixture, RefrigerationSecondarySystem_HeatGainZonesSurviveReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueSecondarySystemPath("epmodel-secondary-system-zones-first");
  const auto secondIdfPath = uniqueSecondarySystemPath("epmodel-secondary-system-zones-second");
  const ScopedSecondarySystemFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedSecondarySystemFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  RefrigerationSecondarySystem system(model);
  ThermalZone distributionZone(model);
  ThermalZone receiverZone(model);
  ASSERT_TRUE(system.setName("Reloaded Secondary System"));
  ASSERT_TRUE(distributionZone.setName("Original Distribution Piping Zone"));
  ASSERT_TRUE(receiverZone.setName("Original Receiver Separator Zone"));
  ASSERT_TRUE(system.setDistributionPipingZone(distributionZone));
  ASSERT_TRUE(system.setReceiverSeparatorZone(receiverZone));
  ASSERT_TRUE(system.setSumUADistributionPiping(1.75));
  ASSERT_TRUE(system.setSumUAReceiverSeparatorShell(2.75));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<RefrigerationSecondarySystem>("Reloaded Secondary System");
  auto loadedDistributionZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Original Distribution Piping Zone");
  auto loadedReceiverZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Original Receiver Separator Zone");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedDistributionZone);
  ASSERT_TRUE(loadedReceiverZone);
  ASSERT_TRUE(loadedSystem->distributionPipingZone());
  ASSERT_TRUE(loadedSystem->receiverSeparatorZone());
  EXPECT_EQ(loadedDistributionZone->handle(), loadedSystem->distributionPipingZone()->handle());
  EXPECT_EQ(loadedReceiverZone->handle(), loadedSystem->receiverSeparatorZone()->handle());
  EXPECT_DOUBLE_EQ(1.75, loadedSystem->sumUADistributionPiping());
  EXPECT_DOUBLE_EQ(2.75, loadedSystem->sumUAReceiverSeparatorShell());

  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement Distribution Piping Zone"));
  ASSERT_TRUE(loadedSystem->setDistributionPipingZone(replacementZone));
  loadedSystem->resetReceiverSeparatorZone();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<RefrigerationSecondarySystem>("Reloaded Secondary System");
  auto reloadedDistributionZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Original Distribution Piping Zone");
  auto reloadedReceiverZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Original Receiver Separator Zone");
  auto reloadedReplacementZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement Distribution Piping Zone");
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedDistributionZone);
  ASSERT_TRUE(reloadedReceiverZone);
  ASSERT_TRUE(reloadedReplacementZone);
  ASSERT_TRUE(reloadedSystem->distributionPipingZone());
  EXPECT_EQ(reloadedReplacementZone->handle(), reloadedSystem->distributionPipingZone()->handle());
  EXPECT_FALSE(reloadedSystem->receiverSeparatorZone());

  EXPECT_FALSE(reloadedSystem->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedDistributionZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReceiverZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementZone->handle()));
}
