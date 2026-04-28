/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXVariableSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_DOUBLE_EQ(0.0, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());
  EXPECT_DOUBLE_EQ(0.0, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());
  EXPECT_DOUBLE_EQ(2.5, coil.maximumCyclingRate());
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(60.0, coil.fanDelayTime());
  EXPECT_EQ("AirCooled", coil.condenserType());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  ASSERT_TRUE(coil.energyPartLoadFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(0.0, coil.evaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_DOUBLE_EQ(0.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_DOUBLE_EQ(10.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(0.0, coil.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, coil.basinHeaterSetpointTemperature());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
  EXPECT_DOUBLE_EQ(-25.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_RelationshipConstructor) {
  Model model;
  CurveQuadratic partLoadFraction(model);

  CoilCoolingDXVariableSpeed coil(model, partLoadFraction);

  EXPECT_EQ(partLoadFraction.handle(), coil.energyPartLoadFractionCurve().handle());
  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(partLoadFraction.handle(), children[0].handle());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXVariableSpeed::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(4200.0));
  ASSERT_TRUE(coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(4200.0, coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(1.4));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(1.4, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setNominalTimeforCondensatetoBeginLeavingtheCoil(50.0));
  EXPECT_DOUBLE_EQ(50.0, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());
  EXPECT_TRUE(coil.setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(0.3));
  EXPECT_DOUBLE_EQ(0.3, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());
  EXPECT_TRUE(coil.setMaximumCyclingRate(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.maximumCyclingRate());
  EXPECT_TRUE(coil.setLatentCapacityTimeConstant(70.0));
  EXPECT_DOUBLE_EQ(70.0, coil.latentCapacityTimeConstant());
  EXPECT_TRUE(coil.setFanDelayTime(45.0));
  EXPECT_DOUBLE_EQ(45.0, coil.fanDelayTime());

  CurveQuadratic plf(model);
  EXPECT_TRUE(coil.setEnergyPartLoadFractionCurve(plf));
  EXPECT_EQ(plf.handle(), coil.energyPartLoadFractionCurve().handle());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setEvaporativeCondenserPumpRatedPowerConsumption(120.0));
  ASSERT_TRUE(coil.evaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(120.0, coil.evaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(80.0));
  EXPECT_DOUBLE_EQ(80.0, coil.crankcaseHeaterCapacity());
  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(8.0));
  EXPECT_DOUBLE_EQ(8.0, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_TRUE(coil.setBasinHeaterCapacity(25.0));
  EXPECT_DOUBLE_EQ(25.0, coil.basinHeaterCapacity());
  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.0));
  EXPECT_DOUBLE_EQ(3.0, coil.basinHeaterSetpointTemperature());
  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXVariableSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.4));
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.8));
  CurveQuadratic partLoadFraction(model);
  CurveCubic crankcaseCurve(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setEnergyPartLoadFractionCurve(partLoadFraction));
  EXPECT_EQ(partLoadFraction.handle(), coil.energyPartLoadFractionCurve().handle());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(partLoadFraction.handle(), children[0].handle());
  EXPECT_EQ(crankcaseCurve.handle(), children[1].handle());

  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  coil.resetBasinHeaterOperatingSchedule();

  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
  ASSERT_EQ(1u, coil.children().size());
  EXPECT_EQ(partLoadFraction.handle(), coil.children()[0].handle());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableSpeed_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingDXVariableSpeed supplyCoil(model);
  CoilCoolingDXVariableSpeed demandCoil(model);
  CoilCoolingDXVariableSpeed oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  auto oaNode = oaSystem.outboardOANode();
  ASSERT_TRUE(oaNode);
  EXPECT_FALSE(oaCoil.addToNode(*oaNode));
  EXPECT_FALSE(oaCoil.inletModelObject());
  EXPECT_FALSE(oaCoil.outletModelObject());
}
