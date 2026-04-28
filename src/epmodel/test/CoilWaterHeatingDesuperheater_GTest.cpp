/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ParentObject/RefrigerationCondenserAirCooled.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/CoilWaterHeatingDesuperheater.hpp"

#include <utilities/idd/Coil_WaterHeating_Desuperheater_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_DefaultConstructor) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);
  EXPECT_EQ(CoilWaterHeatingDesuperheater::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), coil.availabilitySchedule().handle());

  EXPECT_DOUBLE_EQ(5.0, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());
  EXPECT_FALSE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.heatingSource());

  EXPECT_DOUBLE_EQ(50.0, coil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, coil.ratedOutdoorAirTemperature());
  EXPECT_DOUBLE_EQ(60.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_DOUBLE_EQ(0.0001, coil.waterFlowRate());

  EXPECT_DOUBLE_EQ(100.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  EXPECT_DOUBLE_EQ(0.2, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_DOUBLE_EQ(0.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  EXPECT_DOUBLE_EQ(0.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);

  ASSERT_TRUE(coil.setPointer(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName));

  const auto repairedAvailability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(repairedAvailability);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), repairedAvailability->handle());
  EXPECT_DOUBLE_EQ(1.0, repairedAvailability->value());
  ASSERT_TRUE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName));
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(),
            coil.getModelObjectTarget<Schedule>(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName)->handle());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_ScalarAccessors_RoundTrip) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.5));
  CurveBiquadratic curve(model);
  ASSERT_TRUE(curve.setCoefficient1Constant(0.8));
  ASSERT_TRUE(curve.setCoefficient2x(0.1));
  ASSERT_TRUE(curve.setCoefficient3xPOW2(0.0));
  ASSERT_TRUE(curve.setCoefficient4y(0.1));
  ASSERT_TRUE(curve.setCoefficient5yPOW2(0.0));
  ASSERT_TRUE(curve.setCoefficient6xTIMESY(0.0));
  RefrigerationCondenserAirCooled condenser(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.getTarget(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName));
  EXPECT_EQ(availability.handle(), coil.getTarget(openstudio::Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName)->handle());

  EXPECT_TRUE(coil.setHeatReclaimEfficiencyFunctionofTemperatureCurve(curve));
  ASSERT_TRUE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_EQ(curve.handle(), coil.heatReclaimEfficiencyFunctionofTemperatureCurve()->handle());

  EXPECT_TRUE(coil.setHeatingSource(condenser));
  ASSERT_TRUE(coil.heatingSource());
  EXPECT_EQ(condenser.handle(), coil.heatingSource()->handle());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(curve.handle(), children[0].handle());

  EXPECT_TRUE(coil.setDeadBandTemperatureDifference(3.3));
  EXPECT_DOUBLE_EQ(3.3, coil.deadBandTemperatureDifference());
  EXPECT_FALSE(coil.isDeadBandTemperatureDifferenceDefaulted());
  coil.resetDeadBandTemperatureDifference();
  EXPECT_TRUE(coil.isDeadBandTemperatureDifferenceDefaulted());

  EXPECT_TRUE(coil.setRatedHeatReclaimRecoveryEfficiency(0.27));
  ASSERT_TRUE(coil.ratedHeatReclaimRecoveryEfficiency());
  EXPECT_DOUBLE_EQ(0.27, *coil.ratedHeatReclaimRecoveryEfficiency());
  coil.resetRatedHeatReclaimRecoveryEfficiency();
  EXPECT_FALSE(coil.ratedHeatReclaimRecoveryEfficiency());

  EXPECT_TRUE(coil.setRatedInletWaterTemperature(48.0));
  EXPECT_DOUBLE_EQ(48.0, coil.ratedInletWaterTemperature());
  EXPECT_TRUE(coil.setRatedOutdoorAirTemperature(30.0));
  EXPECT_DOUBLE_EQ(30.0, coil.ratedOutdoorAirTemperature());
  EXPECT_TRUE(coil.setMaximumInletWaterTemperatureforHeatReclaim(58.0));
  EXPECT_DOUBLE_EQ(58.0, coil.maximumInletWaterTemperatureforHeatReclaim());
  EXPECT_TRUE(coil.setWaterFlowRate(0.00023));
  EXPECT_DOUBLE_EQ(0.00023, coil.waterFlowRate());

  EXPECT_TRUE(coil.setWaterPumpPower(333.0));
  EXPECT_DOUBLE_EQ(333.0, coil.waterPumpPower());
  EXPECT_FALSE(coil.isWaterPumpPowerDefaulted());
  coil.resetWaterPumpPower();
  EXPECT_TRUE(coil.isWaterPumpPowerDefaulted());

  EXPECT_TRUE(coil.setFractionofPumpHeattoWater(0.61));
  EXPECT_DOUBLE_EQ(0.61, coil.fractionofPumpHeattoWater());
  EXPECT_FALSE(coil.isFractionofPumpHeattoWaterDefaulted());
  coil.resetFractionofPumpHeattoWater();
  EXPECT_TRUE(coil.isFractionofPumpHeattoWaterDefaulted());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(125.0));
  EXPECT_DOUBLE_EQ(125.0, coil.onCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOnCycleParasiticElectricLoadDefaulted());
  coil.resetOnCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOnCycleParasiticElectricLoadDefaulted());

  EXPECT_TRUE(coil.setOffCycleParasiticElectricLoad(44.0));
  EXPECT_DOUBLE_EQ(44.0, coil.offCycleParasiticElectricLoad());
  EXPECT_FALSE(coil.isOffCycleParasiticElectricLoadDefaulted());
  coil.resetOffCycleParasiticElectricLoad();
  EXPECT_TRUE(coil.isOffCycleParasiticElectricLoadDefaulted());

  coil.resetHeatReclaimEfficiencyFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.heatReclaimEfficiencyFunctionofTemperatureCurve());
  EXPECT_TRUE(coil.children().empty());

  coil.resetHeatingSource();
  EXPECT_FALSE(coil.heatingSource());
}

TEST_F(EPModelFixture, CoilWaterHeatingDesuperheater_AddToNode_RejectedAcrossLoopTypes) {
  Model model;
  CoilWaterHeatingDesuperheater coil(model);

  AirLoopHVAC airLoop(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(coil.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto splitterBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(splitterBranchNode);
  EXPECT_FALSE(coil.addToNode(*splitterBranchNode));
  EXPECT_EQ((unsigned)5, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto plantSupplyNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(coil.addToNode(plantSupplyNode));
  EXPECT_EQ((unsigned)5, plantLoop.supplyComponents().size());

  auto plantDemandNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(coil.addToNode(plantDemandNode));
  EXPECT_EQ((unsigned)5, plantLoop.demandComponents().size());
}
