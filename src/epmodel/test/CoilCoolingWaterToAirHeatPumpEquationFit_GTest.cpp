/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadLinear_Impl.hpp"
#include "../Curve/CurveQuintLinear.hpp"
#include "../Curve/CurveQuintLinear_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"

#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);
  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), coil.availabilitySchedule());
  EXPECT_TRUE(coil.totalCoolingCapacityCurve().optionalCast<CurveQuadLinear>());
  EXPECT_TRUE(coil.sensibleCoolingCapacityCurve().optionalCast<CurveQuintLinear>());
  EXPECT_TRUE(coil.coolingPowerConsumptionCurve().optionalCast<CurveQuadLinear>());
  EXPECT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveLinear>());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_CurveConstructorAndSetters) {
  Model model;
  CurveQuadLinear totalCurve(model);
  CurveQuintLinear sensibleCurve(model);
  CurveQuadLinear powerCurve(model);
  ScheduleConstant availability(model);

  CoilCoolingWaterToAirHeatPumpEquationFit coil(model, totalCurve, sensibleCurve, powerCurve);
  EXPECT_EQ(totalCurve, coil.totalCoolingCapacityCurve());
  EXPECT_EQ(sensibleCurve, coil.sensibleCoolingCapacityCurve());
  EXPECT_EQ(powerCurve, coil.coolingPowerConsumptionCurve());

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, coil.availabilitySchedule());

  CurveQuadLinear replacementTotal(model);
  CurveQuintLinear replacementSensible(model);
  CurveQuadLinear replacementPower(model);
  CurveLinear partLoadCurve(model);

  EXPECT_TRUE(coil.setTotalCoolingCapacityCurve(replacementTotal));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCurve(replacementSensible));
  EXPECT_TRUE(coil.setCoolingPowerConsumptionCurve(replacementPower));
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(partLoadCurve));

  EXPECT_EQ(replacementTotal, coil.totalCoolingCapacityCurve());
  EXPECT_EQ(replacementSensible, coil.sensibleCoolingCapacityCurve());
  EXPECT_EQ(replacementPower, coil.coolingPowerConsumptionCurve());
  EXPECT_EQ(partLoadCurve, coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  ASSERT_TRUE(coil.setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_DeprecatedCoefficientAliasesDelegateThroughStoredCurves) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_TRUE(coil.setTotalCoolingCapacityCoefficient1(1.1));
  EXPECT_TRUE(coil.setTotalCoolingCapacityCoefficient2(1.2));
  EXPECT_TRUE(coil.setTotalCoolingCapacityCoefficient3(1.3));
  EXPECT_TRUE(coil.setTotalCoolingCapacityCoefficient4(1.4));
  EXPECT_TRUE(coil.setTotalCoolingCapacityCoefficient5(1.5));
  EXPECT_DOUBLE_EQ(1.1, coil.totalCoolingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(1.2, coil.totalCoolingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(1.3, coil.totalCoolingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(1.4, coil.totalCoolingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(1.5, coil.totalCoolingCapacityCoefficient5());

  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient1(2.1));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient2(2.2));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient3(2.3));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient4(2.4));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient5(2.5));
  EXPECT_TRUE(coil.setSensibleCoolingCapacityCoefficient6(2.6));
  EXPECT_DOUBLE_EQ(2.1, coil.sensibleCoolingCapacityCoefficient1());
  EXPECT_DOUBLE_EQ(2.2, coil.sensibleCoolingCapacityCoefficient2());
  EXPECT_DOUBLE_EQ(2.3, coil.sensibleCoolingCapacityCoefficient3());
  EXPECT_DOUBLE_EQ(2.4, coil.sensibleCoolingCapacityCoefficient4());
  EXPECT_DOUBLE_EQ(2.5, coil.sensibleCoolingCapacityCoefficient5());
  EXPECT_DOUBLE_EQ(2.6, coil.sensibleCoolingCapacityCoefficient6());

  EXPECT_TRUE(coil.setCoolingPowerConsumptionCoefficient1(3.1));
  EXPECT_TRUE(coil.setCoolingPowerConsumptionCoefficient2(3.2));
  EXPECT_TRUE(coil.setCoolingPowerConsumptionCoefficient3(3.3));
  EXPECT_TRUE(coil.setCoolingPowerConsumptionCoefficient4(3.4));
  EXPECT_TRUE(coil.setCoolingPowerConsumptionCoefficient5(3.5));
  EXPECT_DOUBLE_EQ(3.1, coil.coolingPowerConsumptionCoefficient1());
  EXPECT_DOUBLE_EQ(3.2, coil.coolingPowerConsumptionCoefficient2());
  EXPECT_DOUBLE_EQ(3.3, coil.coolingPowerConsumptionCoefficient3());
  EXPECT_DOUBLE_EQ(3.4, coil.coolingPowerConsumptionCoefficient4());
  EXPECT_DOUBLE_EQ(3.5, coil.coolingPowerConsumptionCoefficient5());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_DOUBLE_EQ(30.0, coil.ratedEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(27.0, coil.ratedEnteringAirDryBulbTemperature());
  EXPECT_DOUBLE_EQ(19.0, coil.ratedEnteringAirWetBulbTemperature());
  EXPECT_DOUBLE_EQ(2.5, coil.maximumCyclingRate());
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(60.0, coil.fanDelayTime());

  EXPECT_TRUE(coil.setRatedAirFlowRate(0.74));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.74, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  coil.resetRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateDefaulted());
  EXPECT_FALSE(coil.autosizedRatedAirFlowRate());

  EXPECT_TRUE(coil.setRatedWaterFlowRate(0.0036));
  ASSERT_TRUE(coil.ratedWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0036, coil.ratedWaterFlowRate().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAutosized());
  coil.autosizeRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAutosized());
  coil.resetRatedWaterFlowRate();
  EXPECT_TRUE(coil.isRatedWaterFlowRateDefaulted());
  EXPECT_FALSE(coil.autosizedRatedWaterFlowRate());

  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(7200.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(7200.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.resetRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityDefaulted());
  EXPECT_FALSE(coil.autosizedRatedTotalCoolingCapacity());

  EXPECT_TRUE(coil.setRatedSensibleCoolingCapacity(6100.0));
  ASSERT_TRUE(coil.ratedSensibleCoolingCapacity());
  EXPECT_DOUBLE_EQ(6100.0, coil.ratedSensibleCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedSensibleCoolingCapacityAutosized());
  coil.autosizeRatedSensibleCoolingCapacity();
  EXPECT_TRUE(coil.isRatedSensibleCoolingCapacityAutosized());
  coil.resetRatedSensibleCoolingCapacity();
  EXPECT_TRUE(coil.isRatedSensibleCoolingCapacityDefaulted());
  EXPECT_FALSE(coil.autosizedRatedSensibleCoolingCapacity());

  EXPECT_TRUE(coil.isRatedCoolingCoefficientofPerformanceDefaulted());
  EXPECT_TRUE(coil.setRatedCoolingCoefficientofPerformance(4.3));
  EXPECT_DOUBLE_EQ(4.3, coil.ratedCoolingCoefficientofPerformance());
  EXPECT_FALSE(coil.isRatedCoolingCoefficientofPerformanceDefaulted());

  EXPECT_TRUE(coil.setRatedEnteringWaterTemperature(29.4));
  EXPECT_DOUBLE_EQ(29.4, coil.ratedEnteringWaterTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirDryBulbTemperature(24.1));
  EXPECT_DOUBLE_EQ(24.1, coil.ratedEnteringAirDryBulbTemperature());

  EXPECT_TRUE(coil.setRatedEnteringAirWetBulbTemperature(16.2));
  EXPECT_DOUBLE_EQ(16.2, coil.ratedEnteringAirWetBulbTemperature());

  EXPECT_TRUE(coil.setNominalTimeforCondensateRemovaltoBegin(0.4));
  EXPECT_DOUBLE_EQ(0.4, coil.nominalTimeforCondensateRemovaltoBegin());
  EXPECT_FALSE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());
  coil.resetNominalTimeforCondensateRemovaltoBegin();
  EXPECT_TRUE(coil.isNominalTimeforCondensateRemovaltoBeginDefaulted());

  EXPECT_TRUE(coil.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(1.8));
  EXPECT_DOUBLE_EQ(1.8, coil.ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity());
  EXPECT_FALSE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());
  coil.resetRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  EXPECT_TRUE(coil.isRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacityDefaulted());

  EXPECT_TRUE(coil.setMaximumCyclingRate(2.7));
  EXPECT_DOUBLE_EQ(2.7, coil.maximumCyclingRate());
  EXPECT_FALSE(coil.setMaximumCyclingRate(-1.0));
  EXPECT_DOUBLE_EQ(2.7, coil.maximumCyclingRate());

  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(60.0));
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());
  EXPECT_FALSE(coil.setLatentCapacityTimeConstant(-1.0));
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());

  EXPECT_TRUE(coil.setFanDelayTime(100.0));
  EXPECT_DOUBLE_EQ(100.0, coil.fanDelayTime());
  EXPECT_FALSE(coil.setFanDelayTime(-1.0));
  EXPECT_DOUBLE_EQ(100.0, coil.fanDelayTime());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_AirflowNetworkEquivalentDuctRoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_FALSE(coil.airflowNetworkEquivalentDuct());

  auto afnComponent = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), afnComponent.iddObject().type());
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:EquationFit", afnComponent.coilObjectType());
  EXPECT_DOUBLE_EQ(1.25, afnComponent.airPathLength());
  EXPECT_DOUBLE_EQ(0.41, afnComponent.airPathHydraulicDiameter());

  auto attached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(attached);
  EXPECT_EQ(afnComponent.handle(), attached->handle());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(afnComponent.handle(), children.front().handle());

  auto updated = coil.getAirflowNetworkEquivalentDuct(2.5, 0.82);
  EXPECT_EQ(afnComponent.handle(), updated.handle());
  EXPECT_DOUBLE_EQ(2.5, updated.airPathLength());
  EXPECT_DOUBLE_EQ(0.82, updated.airPathHydraulicDiameter());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpEquationFit_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWaterToAirHeatPumpEquationFit coil(model);

  EXPECT_FALSE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(1u, oaComponents.size());
}
