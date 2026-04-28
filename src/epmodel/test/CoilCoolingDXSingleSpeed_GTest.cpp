/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXSingleSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_TRUE(coil.totalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(coil.energyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(coil.energyInputRatioFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());

  const auto children = coil.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(1u, oaSystem.oaComponents().size());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsDemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*branchNode));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  EXPECT_TRUE(coil.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", coil.condenserType());

  EXPECT_TRUE(coil.setRatedCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());

  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalCoolingCapacity());
  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12000.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, *coil.ratedTotalCoolingCapacity());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());

  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_FALSE(coil.ratedSensibleHeatRatio());
  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.73));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.73, *coil.ratedSensibleHeatRatio());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, *coil.ratedAirFlowRate());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-20.0));
  EXPECT_DOUBLE_EQ(-20.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  CurveBiquadratic coolingTemp(model);
  CurveQuadratic coolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveQuadratic crankcaseCurve(model);
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.5));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(coolingTemp));
  EXPECT_EQ(coolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(coolingFlow));
  EXPECT_EQ(coolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(eirTemp));
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(eirFlow));
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(6u, children.size());
  EXPECT_EQ(crankcaseCurve.handle(), children.back().handle());

  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  coil.resetBasinHeaterOperatingSchedule();
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.75));
  CurveBiquadratic coolingTemp(model);
  CurveQuadratic coolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);

  CoilCoolingDXSingleSpeed coil(model, availability, coolingTemp, coolingFlow, eirTemp, eirFlow, plf);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(coolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(coolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(3.0, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedEvaporatorFanPowerPerVolumeFlowRate2023());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeSupplyPath) {
  Model model;
  AirLoopHVAC airLoop(model);

  CoilCoolingDXSingleSpeed coil(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(coil.addToNode(supplyInletNode));
  ASSERT_TRUE(coil.inletModelObject());
  EXPECT_EQ(supplyInletNode, coil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(coil.outletModelObject());
}
