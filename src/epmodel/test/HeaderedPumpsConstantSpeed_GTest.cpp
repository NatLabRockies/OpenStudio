/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/HeaderedPumpsConstantSpeed.hpp"
#include "../StraightComponent/HeaderedPumpsConstantSpeed_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/HeaderedPumps_ConstantSpeed_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

}  // namespace

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_DefaultConstructor) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);
  EXPECT_EQ(HeaderedPumpsConstantSpeed::iddObjectType(), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());

  EXPECT_TRUE(pump.isTotalRatedFlowRateAutosized());
  EXPECT_FALSE(pump.totalRatedFlowRate());
  EXPECT_EQ(2, pump.numberofPumpsinBank());
  EXPECT_EQ("Sequential", pump.flowSequencingControlScheme());
  EXPECT_DOUBLE_EQ(179352.0, pump.ratedPumpHead());
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_FALSE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(0.9, pump.motorEfficiency());
  EXPECT_DOUBLE_EQ(0.0, pump.fractionofMotorInefficienciestoFluidStream());
  EXPECT_EQ("Continuous", pump.pumpControlType());
  EXPECT_DOUBLE_EQ(0.1, pump.skinLossRadiativeFraction());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_DOUBLE_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_DOUBLE_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);

  ASSERT_FALSE(HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().empty());
  ASSERT_FALSE(HeaderedPumpsConstantSpeed::pumpControlTypeValues().empty());
  ASSERT_FALSE(HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().empty());

  auto flowSequencingControlScheme = HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().front();
  if (flowSequencingControlScheme == pump.flowSequencingControlScheme()
      && HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues().size() > 1) {
    flowSequencingControlScheme = HeaderedPumpsConstantSpeed::flowSequencingControlSchemeValues()[1];
  }

  auto pumpControlType = HeaderedPumpsConstantSpeed::pumpControlTypeValues().front();
  if (pumpControlType == pump.pumpControlType() && HeaderedPumpsConstantSpeed::pumpControlTypeValues().size() > 1) {
    pumpControlType = HeaderedPumpsConstantSpeed::pumpControlTypeValues()[1];
  }

  auto designPowerSizingMethod = HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().front();
  if (designPowerSizingMethod == pump.designPowerSizingMethod() && HeaderedPumpsConstantSpeed::designPowerSizingMethodValues().size() > 1) {
    designPowerSizingMethod = HeaderedPumpsConstantSpeed::designPowerSizingMethodValues()[1];
  }

  EXPECT_TRUE(pump.setTotalRatedFlowRate(0.009));
  ASSERT_TRUE(pump.totalRatedFlowRate());
  EXPECT_DOUBLE_EQ(0.009, pump.totalRatedFlowRate().get());
  EXPECT_FALSE(pump.isTotalRatedFlowRateAutosized());

  pump.autosizeTotalRatedFlowRate();
  EXPECT_TRUE(pump.isTotalRatedFlowRateAutosized());
  EXPECT_FALSE(pump.totalRatedFlowRate());

  EXPECT_TRUE(pump.setNumberofPumpsinBank(3));
  EXPECT_EQ(3, pump.numberofPumpsinBank());

  EXPECT_TRUE(pump.setFlowSequencingControlScheme(flowSequencingControlScheme));
  EXPECT_EQ(flowSequencingControlScheme, pump.flowSequencingControlScheme());

  EXPECT_TRUE(pump.setRatedPumpHead(250000.0));
  EXPECT_DOUBLE_EQ(250000.0, pump.ratedPumpHead());

  EXPECT_TRUE(pump.setRatedPowerConsumption(2000.0));
  ASSERT_TRUE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(2000.0, pump.ratedPowerConsumption().get());
  EXPECT_FALSE(pump.isRatedPowerConsumptionAutosized());

  pump.autosizeRatedPowerConsumption();
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_FALSE(pump.ratedPowerConsumption());

  EXPECT_TRUE(pump.setMotorEfficiency(0.85));
  EXPECT_DOUBLE_EQ(0.85, pump.motorEfficiency());

  EXPECT_TRUE(pump.setFractionofMotorInefficienciestoFluidStream(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.fractionofMotorInefficienciestoFluidStream());

  EXPECT_TRUE(pump.setPumpControlType(pumpControlType));
  EXPECT_EQ(pumpControlType, pump.pumpControlType());

  EXPECT_TRUE(pump.setSkinLossRadiativeFraction(0.2));
  EXPECT_DOUBLE_EQ(0.2, pump.skinLossRadiativeFraction());

  EXPECT_TRUE(pump.setDesignPowerSizingMethod(designPowerSizingMethod));
  EXPECT_EQ(designPowerSizingMethod, pump.designPowerSizingMethod());

  EXPECT_TRUE(pump.setDesignElectricPowerPerUnitFlowRate(400000.0));
  EXPECT_DOUBLE_EQ(400000.0, pump.designElectricPowerPerUnitFlowRate());

  EXPECT_TRUE(pump.setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.5));
  EXPECT_DOUBLE_EQ(1.5, pump.designShaftPowerPerUnitFlowRatePerUnitHead());

  EXPECT_TRUE(pump.setEndUseSubcategory("Pumps"));
  EXPECT_EQ("Pumps", pump.endUseSubcategory());

  EXPECT_FALSE(pump.autosizedTotalRatedFlowRate());
  EXPECT_FALSE(pump.autosizedRatedPowerConsumption());
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_RelationshipAccessors_RoundTripAndReset) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ThermalZone thermalZone(model);

  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.thermalZone());

  EXPECT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  EXPECT_TRUE(pump.setThermalZone(thermalZone));

  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  ASSERT_TRUE(pump.thermalZone());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(thermalZone.handle(), pump.thermalZone()->handle());

  pump.resetPumpFlowRateSchedule();
  pump.resetThermalZone();
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.thermalZone());
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_RelationshipSetters_RejectInvalidTargetsWithoutChangingOldTargetOrRawText) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ThermalZone thermalZone(model);
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setThermalZone(thermalZone));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  ThermalZone foreignThermalZone(foreignModel);
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setThermalZone(foreignThermalZone));
  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  ASSERT_TRUE(pump.thermalZone());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(thermalZone.handle(), pump.thermalZone()->handle());

  ScheduleConstant incompatibleFlowSchedule(model);
  ScheduleTypeLimits incompatibleFlowLimits(model);
  ASSERT_TRUE(incompatibleFlowLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleFlowLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleFlowLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleFlowLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleFlowSchedule.setScheduleTypeLimits(incompatibleFlowLimits));
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());

  constexpr unsigned thermalZoneField = openstudio::HeaderedPumps_ConstantSpeedFields::ZoneName;
  EXPECT_TRUE(model.canBeTarget(thermalZone.handle(), pump.iddObject().objectLists(thermalZoneField)));
  EXPECT_FALSE(model.canBeTarget(flowSchedule.handle(), pump.iddObject().objectLists(thermalZoneField)));

  auto pumpWorkspaceImpl = pump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(pumpWorkspaceImpl);
  constexpr unsigned flowScheduleField = openstudio::HeaderedPumps_ConstantSpeedFields::PumpFlowRateScheduleName;
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(flowScheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(thermalZoneField, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(flowScheduleField, "Unresolved Headered Flow Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(thermalZoneField, "Unresolved Headered Thermal Zone", false));

  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setThermalZone(foreignThermalZone));
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.thermalZone());
  EXPECT_EQ("Unresolved Headered Flow Schedule",
            pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(flowScheduleField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Headered Thermal Zone",
            pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(thermalZoneField, false, true).value_or(""));
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_Relationships_SaveLoadIdentityByName) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-headered-pumps-constant-speed-relationships-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  HeaderedPumpsConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ThermalZone thermalZone(model);
  ASSERT_TRUE(pump.setName("Relationship Headered Pump"));
  ASSERT_TRUE(flowSchedule.setName("Headered Pump Flow Schedule"));
  ASSERT_TRUE(thermalZone.setName("Headered Pump Thermal Zone"));
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setThermalZone(thermalZone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPump = loadedModel->getConcreteModelObjectByName<HeaderedPumpsConstantSpeed>("Relationship Headered Pump");
  auto loadedFlowSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Headered Pump Flow Schedule");
  auto loadedThermalZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Headered Pump Thermal Zone");
  ASSERT_TRUE(loadedPump);
  ASSERT_TRUE(loadedFlowSchedule);
  ASSERT_TRUE(loadedThermalZone);
  ASSERT_TRUE(loadedPump->pumpFlowRateSchedule());
  ASSERT_TRUE(loadedPump->thermalZone());
  EXPECT_EQ(loadedFlowSchedule->handle(), loadedPump->pumpFlowRateSchedule()->handle());
  EXPECT_EQ(loadedThermalZone->handle(), loadedPump->thermalZone()->handle());
}

TEST_F(EPModelFixture, HeaderedPumpsConstantSpeed_AddToNode_PlantOnly) {
  Model model;
  HeaderedPumpsConstantSpeed pump(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pump.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(plantDemandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  HeaderedPumpsConstantSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(plantDemandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}
