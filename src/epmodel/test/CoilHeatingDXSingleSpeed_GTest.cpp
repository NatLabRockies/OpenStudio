/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/ScheduleConstant_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXSingleSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());

  EXPECT_DOUBLE_EQ(5.0, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("Timed", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 1e-6);
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  ASSERT_TRUE(coil.totalHeatingCapacityFunctionofTemperatureCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.totalHeatingCapacityFunctionofFlowFractionCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionofTemperatureCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionofFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(2000.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());

  const auto children = coil.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(coil.totalHeatingCapacityFunctionofTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalHeatingCapacityFunctionofFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionofTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionofFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostControlValues().empty());

  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(15000.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, *coil.ratedTotalHeatingCapacity());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedCOP(4.2));
  EXPECT_DOUBLE_EQ(4.2, coil.ratedCOP());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.2));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, *coil.ratedAirFlowRate());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate(800.0));
  EXPECT_DOUBLE_EQ(800.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate2023(950.0));
  EXPECT_DOUBLE_EQ(950.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  coil.resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(120.0));
  EXPECT_DOUBLE_EQ(120.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.isCrankcaseHeaterCapacityDefaulted());
  coil.resetCrankcaseHeaterCapacity();
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());

  CurveBiquadratic defrostCurve(model);
  EXPECT_TRUE(coil.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostCurve));
  ASSERT_TRUE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostCurve.handle(), coil.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  coil.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());

  CurveCubic crankcaseCurve(model);
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());
  EXPECT_FALSE(coil.isDefrostStrategyDefaulted());
  coil.resetDefrostStrategy();
  EXPECT_TRUE(coil.isDefrostStrategyDefaulted());

  EXPECT_TRUE(coil.setDefrostControl("OnDemand"));
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_FALSE(coil.isDefrostControlDefaulted());
  coil.resetDefrostControl();
  EXPECT_TRUE(coil.isDefrostControlDefaulted());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, coil.defrostTimePeriodFraction());
  EXPECT_FALSE(coil.isDefrostTimePeriodFractionDefaulted());
  coil.resetDefrostTimePeriodFraction();
  EXPECT_TRUE(coil.isDefrostTimePeriodFractionDefaulted());

  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(450.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(450.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());

  coil.resetResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(0.0, *coil.resistiveDefrostHeaterCapacity());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.3));
  CurveCubic totalHeatingTemp(model);
  CurveCubic totalHeatingFlow(model);
  CurveCubic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);

  CoilHeatingDXSingleSpeed coil(model, availability, totalHeatingTemp, totalHeatingFlow, eirTemp, eirFlow, plf);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(totalHeatingTemp.handle(), coil.totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(totalHeatingFlow.handle(), coil.totalHeatingCapacityFunctionofFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionofFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingDXSingleSpeed coil(model);

  auto supplyNode = airLoop.supplyInletNode();
  EXPECT_TRUE(coil.addToNode(supplyNode));

  auto supplyComponent = airLoop.supplyComponent(coil.handle());
  ASSERT_TRUE(supplyComponent);
  EXPECT_EQ(coil, *supplyComponent);
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToDemandNodeFails) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingDXSingleSpeed coil(model);

  auto demandNode = airLoop.demandInletNode();
  EXPECT_FALSE(coil.addToNode(demandNode));
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToOutdoorAirNodeFails) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyNode));

  CoilHeatingDXSingleSpeed coil(model);

  auto outdoorAirObject = oaSystem.outdoorAirModelObject();
  ASSERT_TRUE(outdoorAirObject);
  auto outdoorNode = outdoorAirObject->optionalCast<Node>();
  ASSERT_TRUE(outdoorNode);

  EXPECT_FALSE(coil.addToNode(*outdoorNode));
}
