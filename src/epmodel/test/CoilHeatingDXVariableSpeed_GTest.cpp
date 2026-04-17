/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingDXVariableSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(-5.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  EXPECT_DOUBLE_EQ(5.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_DOUBLE_EQ(200.0, coil.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 0.000001);
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  ASSERT_TRUE(coil.energyPartLoadFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_RelationshipConstructor) {
  Model model;
  CurveQuadratic partLoadFraction(model);

  CoilHeatingDXVariableSpeed coil(model, partLoadFraction);

  EXPECT_EQ(partLoadFraction.handle(), coil.energyPartLoadFractionCurve().handle());
  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_DOUBLE_EQ(-5.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(5.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_DOUBLE_EQ(200.0, coil.crankcaseHeaterCapacity());
  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 0.000001);
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(partLoadFraction.handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXVariableSpeed::defrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXVariableSpeed::defrostControlValues().empty());

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  coil.autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.setRatedHeatingCapacityAtSelectedNominalSpeedLevel(10000.0));
  ASSERT_TRUE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(10000.0, *coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_FALSE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());

  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(1.2));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(1.2, *coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setOutdoorDryBulbTemperaturetoTurnOnCompressor(4.0));
  ASSERT_TRUE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  EXPECT_DOUBLE_EQ(4.0, *coil.outdoorDryBulbTemperaturetoTurnOnCompressor());
  coil.resetOutdoorDryBulbTemperaturetoTurnOnCompressor();
  EXPECT_FALSE(coil.outdoorDryBulbTemperaturetoTurnOnCompressor());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(50.0));
  EXPECT_DOUBLE_EQ(50.0, coil.crankcaseHeaterCapacity());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());

  EXPECT_TRUE(coil.setDefrostControl("Timed"));
  EXPECT_EQ("Timed", coil.defrostControl());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.12));
  EXPECT_DOUBLE_EQ(0.12, coil.defrostTimePeriodFraction());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(500.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(500.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingDXVariableSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.4));
  CurveQuadratic partLoadFraction(model);
  CurveQuadratic defrostCurve(model);
  CurveQuadratic crankcaseCurve(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setEnergyPartLoadFractionCurve(partLoadFraction));
  EXPECT_EQ(partLoadFraction.handle(), coil.energyPartLoadFractionCurve().handle());

  EXPECT_TRUE(coil.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostCurve));
  ASSERT_TRUE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostCurve.handle(), coil.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(partLoadFraction.handle(), children[0].handle());
  EXPECT_EQ(defrostCurve.handle(), children[1].handle());
  EXPECT_EQ(crankcaseCurve.handle(), children[2].handle());

  coil.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  ASSERT_EQ(1u, coil.children().size());
  EXPECT_EQ(partLoadFraction.handle(), coil.children()[0].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilHeatingDXVariableSpeed supplyCoil(model);
  CoilHeatingDXVariableSpeed demandCoil(model);
  CoilHeatingDXVariableSpeed oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), supplyCoil.airLoopHVAC()->handle());
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());
  EXPECT_FALSE(demandCoil.inletModelObject());
  EXPECT_FALSE(demandCoil.outletModelObject());

  auto oaNode = oaSystem.outboardOANode();
  ASSERT_TRUE(oaNode);
  EXPECT_FALSE(oaCoil.addToNode(*oaNode));
  EXPECT_FALSE(oaCoil.inletModelObject());
  EXPECT_FALSE(oaCoil.outletModelObject());
}
