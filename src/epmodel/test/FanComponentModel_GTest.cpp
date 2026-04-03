/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveExponentialDecay.hpp"
#include "../Curve/CurveExponentialDecay_Impl.hpp"
#include "../Curve/CurveExponentialSkewNormal.hpp"
#include "../Curve/CurveExponentialSkewNormal_Impl.hpp"
#include "../Curve/CurveFanPressureRise.hpp"
#include "../Curve/CurveFanPressureRise_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/CurveQuartic.hpp"
#include "../Curve/CurveQuartic_Impl.hpp"
#include "../Curve/CurveRectangularHyperbola1.hpp"
#include "../Curve/CurveRectangularHyperbola1_Impl.hpp"
#include "../Curve/CurveRectangularHyperbola2.hpp"
#include "../Curve/CurveRectangularHyperbola2_Impl.hpp"
#include "../Curve/CurveSigmoid.hpp"
#include "../Curve/CurveSigmoid_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FanComponentModel.hpp"
#include "../StraightComponent/Node.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FanComponentModel_DefaultConstructor) {
  Model model;
  FanComponentModel fan(model);
  EXPECT_EQ(FanComponentModel::iddObjectType(), fan.iddObject().type());
  EXPECT_FALSE(fan.nameString().empty());
  auto defaultSchedule = fan.availabilitySchedule();
  auto constantSchedule = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(constantSchedule);
  EXPECT_DOUBLE_EQ(1.0, constantSchedule->value());
  EXPECT_TRUE(fan.fanPressureRiseCurve().optionalCast<CurveFanPressureRise>());
  EXPECT_TRUE(fan.ductStaticPressureResetCurve().optionalCast<CurveLinear>());
  EXPECT_TRUE(fan.normalizedFanStaticEfficiencyCurveNonStallRegion().optionalCast<CurveExponentialSkewNormal>());
  EXPECT_TRUE(fan.normalizedFanStaticEfficiencyCurveStallRegion().optionalCast<CurveExponentialSkewNormal>());
  EXPECT_TRUE(fan.normalizedDimensionlessAirflowCurveNonStallRegion().optionalCast<CurveSigmoid>());
  EXPECT_TRUE(fan.normalizedDimensionlessAirflowCurveStallRegion().optionalCast<CurveSigmoid>());
  EXPECT_FALSE(fan.maximumBeltEfficiencyCurve());
  EXPECT_FALSE(fan.vFDEfficiencyCurve());
}

TEST_F(EPModelFixture, FanComponentModel_AvailabilitySchedule_RoundTripAndValidation) {
  Model model;
  FanComponentModel fan(model);

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.65));
  EXPECT_TRUE(fan.setAvailabilitySchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), fan.availabilitySchedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(19.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(fan.setAvailabilitySchedule(wrongSchedule));
}

TEST_F(EPModelFixture, FanComponentModel_ScalarAccessors_RoundTrip) {
  Model model;
  FanComponentModel fan(model);

  EXPECT_TRUE(fan.setMaximumFlowRate(1.25));
  ASSERT_TRUE(fan.maximumFlowRate());
  EXPECT_DOUBLE_EQ(1.25, fan.maximumFlowRate().get());
  EXPECT_FALSE(fan.isMaximumFlowRateAutosized());
  fan.autosizeMaximumFlowRate();
  EXPECT_TRUE(fan.isMaximumFlowRateAutosized());

  EXPECT_TRUE(fan.setMinimumFlowRate(0.40));
  ASSERT_TRUE(fan.minimumFlowRate());
  EXPECT_DOUBLE_EQ(0.40, fan.minimumFlowRate().get());
  fan.autosizeMinimumFlowRate();
  EXPECT_TRUE(fan.isMinimumFlowRateAutosized());

  EXPECT_TRUE(fan.setFanWheelDiameter(0.5));
  EXPECT_DOUBLE_EQ(0.5, fan.fanWheelDiameter());

  EXPECT_TRUE(fan.setMaximumFanStaticEfficiency(0.72));
  EXPECT_DOUBLE_EQ(0.72, fan.maximumFanStaticEfficiency());

  EXPECT_TRUE(fan.setMaximumMotorOutputPower(1750.0));
  ASSERT_TRUE(fan.maximumMotorOutputPower());
  EXPECT_DOUBLE_EQ(1750.0, fan.maximumMotorOutputPower().get());
  fan.autosizeMaximumMotorOutputPower();
  EXPECT_TRUE(fan.isMaximumMotorOutputPowerAutosized());

  auto vfdTypes = FanComponentModel::vFDEfficiencyTypeValues();
  ASSERT_FALSE(vfdTypes.empty());
  EXPECT_TRUE(fan.setVFDEfficiencyType(vfdTypes.front()));
  EXPECT_EQ(vfdTypes.front(), fan.vFDEfficiencyType());

  EXPECT_TRUE(fan.setEndUseSubcategory("Fans"));
  EXPECT_EQ("Fans", fan.endUseSubcategory());
}

TEST_F(EPModelFixture, FanComponentModel_CurveRelationships_RoundTrip) {
  Model model;
  FanComponentModel fan(model);

  CurveFanPressureRise fanPressureRiseCurve(model);
  CurveLinear ductStaticPressureResetCurve(model);
  CurveExponentialSkewNormal normalEfficiencyCurve(model);
  CurveExponentialSkewNormal stallEfficiencyCurve(model);
  CurveSigmoid normalAirflowCurve(model);
  CurveSigmoid stallAirflowCurve(model);

  EXPECT_TRUE(fan.setFanPressureRiseCurve(fanPressureRiseCurve));
  EXPECT_TRUE(fan.setDuctStaticPressureResetCurve(ductStaticPressureResetCurve));
  EXPECT_TRUE(fan.setNormalizedFanStaticEfficiencyCurveNonStallRegion(normalEfficiencyCurve));
  EXPECT_TRUE(fan.setNormalizedFanStaticEfficiencyCurveStallRegion(stallEfficiencyCurve));
  EXPECT_TRUE(fan.setNormalizedDimensionlessAirflowCurveNonStallRegion(normalAirflowCurve));
  EXPECT_TRUE(fan.setNormalizedDimensionlessAirflowCurveStallRegion(stallAirflowCurve));
  EXPECT_EQ(fanPressureRiseCurve.cast<ModelObject>(), fan.fanPressureRiseCurve().cast<ModelObject>());
  EXPECT_EQ(ductStaticPressureResetCurve.cast<ModelObject>(), fan.ductStaticPressureResetCurve().cast<ModelObject>());

  EXPECT_TRUE(fan.assignDefaultOptionalCurves());
  EXPECT_TRUE(fan.maximumBeltEfficiencyCurve());
  EXPECT_TRUE(fan.normalizedBeltEfficiencyCurveRegion1());
  EXPECT_TRUE(fan.normalizedBeltEfficiencyCurveRegion2());
  EXPECT_TRUE(fan.normalizedBeltEfficiencyCurveRegion3());
  EXPECT_TRUE(fan.maximumMotorEfficiencyCurve());
  EXPECT_TRUE(fan.normalizedMotorEfficiencyCurve());
  EXPECT_TRUE(fan.vFDEfficiencyCurve());

  fan.resetMaximumBeltEfficiencyCurve();
  EXPECT_FALSE(fan.maximumBeltEfficiencyCurve());
  fan.resetVFDEfficiencyCurve();
  EXPECT_FALSE(fan.vFDEfficiencyCurve());
}

TEST_F(EPModelFixture, FanComponentModel_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  FanComponentModel supplyFan(model);
  FanComponentModel demandFan(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyFan.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyFan.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyFan.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyFan.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandFan.addToNode(demandInletNode));
  EXPECT_FALSE(demandFan.airLoopHVAC());
}

TEST_F(EPModelFixture, FanComponentModel_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  FanComponentModel fan(model);
  EXPECT_TRUE(fan.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
