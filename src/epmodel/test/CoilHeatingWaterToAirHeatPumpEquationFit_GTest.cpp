/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/Curve.hpp"
#include "../Curve/Curve_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadLinear_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"

#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_DefaultConstructor) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);
  EXPECT_EQ(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), coil.availabilitySchedule());
  EXPECT_TRUE(coil.heatingCapacityCurve().optionalCast<CurveQuadLinear>());
  EXPECT_TRUE(coil.heatingPowerConsumptionCurve().optionalCast<CurveQuadLinear>());
  EXPECT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveLinear>());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear capacityCurve(model);
  CurveQuadLinear powerCurve(model);
  ScheduleConstant availability(model);

  CoilHeatingWaterToAirHeatPumpEquationFit coil(model, capacityCurve, powerCurve);
  EXPECT_EQ(capacityCurve, coil.heatingCapacityCurve());
  EXPECT_EQ(powerCurve, coil.heatingPowerConsumptionCurve());

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, coil.availabilitySchedule());

  CurveQuadLinear replacementCapacity(model);
  CurveQuadLinear replacementPower(model);
  CurveLinear partLoadCurve(model);

  EXPECT_TRUE(coil.setHeatingCapacityCurve(replacementCapacity));
  EXPECT_TRUE(coil.setHeatingPowerConsumptionCurve(replacementPower));
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(partLoadCurve));

  EXPECT_EQ(replacementCapacity, coil.heatingCapacityCurve());
  EXPECT_EQ(replacementPower, coil.heatingPowerConsumptionCurve());
  EXPECT_EQ(partLoadCurve, coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);

  ASSERT_TRUE(coil.setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_TRUE(coil.setHeatingCapacityCoefficient1(1.1));
  EXPECT_TRUE(coil.setHeatingCapacityCoefficient2(1.2));
  EXPECT_TRUE(coil.setHeatingCapacityCoefficient3(1.3));
  EXPECT_TRUE(coil.setHeatingCapacityCoefficient4(1.4));
  EXPECT_TRUE(coil.setHeatingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, coil.heatingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, coil.heatingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, coil.heatingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, coil.heatingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, coil.heatingCapacityCoefficient5());

  EXPECT_TRUE(coil.setHeatingPowerConsumptionCoefficient1(2.1));
  EXPECT_TRUE(coil.setHeatingPowerConsumptionCoefficient2(2.2));
  EXPECT_TRUE(coil.setHeatingPowerConsumptionCoefficient3(2.3));
  EXPECT_TRUE(coil.setHeatingPowerConsumptionCoefficient4(2.4));
  EXPECT_TRUE(coil.setHeatingPowerConsumptionCoefficient5(2.5));
  EXPECT_DOUBLE_EQ(2.1, coil.heatingPowerConsumptionCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, coil.heatingPowerConsumptionCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, coil.heatingPowerConsumptionCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, coil.heatingPowerConsumptionCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, coil.heatingPowerConsumptionCoefficient5());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_TRUE(coil.setRatedAirFlowRate(0.73));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.73, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  coil.resetRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateDefaulted());
  EXPECT_FALSE(coil.autosizedRatedAirFlowRate());

  EXPECT_TRUE(coil.setRatedWaterFlowRate(0.0033));
  ASSERT_TRUE(coil.ratedWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0033, coil.ratedWaterFlowRate().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAutosized());
  coil.autosizeRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAutosized());
  coil.resetRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateDefaulted());
  EXPECT_FALSE(coil.autosizedRatedWaterFlowRate());

  EXPECT_TRUE(coil.setRatedHeatingCapacity(8300.0));
  ASSERT_TRUE(coil.ratedHeatingCapacity());
  EXPECT_DOUBLE_EQ(8300.0, coil.ratedHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedHeatingCapacityAutosized());
  coil.autosizeRatedHeatingCapacity();
  EXPECT_TRUE(coil.isRatedHeatingCapacityAutosized());
  coil.resetRatedHeatingCapacity();
  EXPECT_TRUE(coil.isRatedHeatingCapacityDefaulted());
  EXPECT_FALSE(coil.autosizedRatedHeatingCapacity());

  EXPECT_TRUE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());
  EXPECT_TRUE(coil.setRatedHeatingCoefficientofPerformance(4.5));
  EXPECT_DOUBLE_EQ(4.5, coil.ratedHeatingCoefficientofPerformance());
  EXPECT_FALSE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());
  coil.resetRatedHeatingCoefficientofPerformance();
  EXPECT_TRUE(coil.isRatedHeatingCoefficientofPerformanceDefaulted());

  EXPECT_TRUE(coil.setRatedEnteringWaterTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, coil.ratedEnteringWaterTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirDryBulbTemperature(20.0));
  EXPECT_DOUBLE_EQ(20.0, coil.ratedEnteringAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatioofRatedHeatingCapacitytoRatedCoolingCapacity(1.25));
  EXPECT_DOUBLE_EQ(1.25, coil.ratioofRatedHeatingCapacitytoRatedCoolingCapacity());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpEquationFit_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_FALSE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(1u, oaComponents.size());
}
