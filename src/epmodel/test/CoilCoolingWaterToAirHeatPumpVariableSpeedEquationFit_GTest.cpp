/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil_Impl.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "../ParentObject/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"

#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_DefaultConstructor) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  EXPECT_EQ(CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterInletNodeName, coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterOutletNodeName, coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), coil.availabilitySchedule());
  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_DOUBLE_EQ(0.0, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());
  EXPECT_DOUBLE_EQ(0.0, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());
  EXPECT_DOUBLE_EQ(2.5, coil.maximumCyclingRate());
  EXPECT_DOUBLE_EQ(60.0, coil.latentCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(60.0, coil.fanDelayTime());
  EXPECT_FALSE(coil.useHotGasReheat());
  auto partLoadFractionCurve = coil.energyPartLoadFractionCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(0.85, partLoadFractionCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.15, partLoadFractionCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.0, partLoadFractionCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, partLoadFractionCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(1.0, partLoadFractionCurve.maximumValueofx());
  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children.front().handle());
  EXPECT_TRUE(coil.speeds().empty());
  EXPECT_FALSE(coil.airflowNetworkEquivalentDuct());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_CurveConstructorAndSetterRoundTrip) {
  Model model;
  CurveLinear partLoadFraction(model);
  ScheduleConstant availability(model);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model, partLoadFraction);

  EXPECT_EQ(partLoadFraction, coil.energyPartLoadFractionCurve());
  EXPECT_EQ(1u, model.getModelObjects<CurveLinear>().size());
  EXPECT_TRUE(model.getModelObjects<CurveQuadratic>().empty());
  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, coil.availabilitySchedule());

  CurveLinear replacement(model);
  EXPECT_TRUE(coil.setEnergyPartLoadFractionCurve(replacement));
  EXPECT_EQ(replacement, coil.energyPartLoadFractionCurve());
  EXPECT_EQ(2u, model.getModelObjects<CurveLinear>().size());
  EXPECT_TRUE(model.getModelObjects<CurveQuadratic>().empty());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel(7200.0));
  ASSERT_TRUE(coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(7200.0, coil.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.autosizedGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(0.74));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.74, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedWaterFlowRateAtSelectedNominalSpeedLevel(0.0036));
  ASSERT_TRUE(coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.0036, coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel());

  EXPECT_TRUE(coil.setNominalTimeforCondensatetoBeginLeavingtheCoil(0.4));
  EXPECT_DOUBLE_EQ(0.4, coil.nominalTimeforCondensatetoBeginLeavingtheCoil());

  EXPECT_TRUE(coil.setInitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity(1.8));
  EXPECT_DOUBLE_EQ(1.8, coil.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity());

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

  EXPECT_TRUE(coil.setUseHotGasReheat(true));
  EXPECT_TRUE(coil.useHotGasReheat());
  EXPECT_TRUE(coil.setUseHotGasReheat(false));
  EXPECT_FALSE(coil.useHotGasReheat());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_SpeedChildrenRoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed2(model);
  ASSERT_TRUE(speed2.setReferenceUnitGrossRatedCoolingCOP(5.2));

  EXPECT_TRUE(coil.addSpeed(speed));
  EXPECT_TRUE(coil.addSpeed(speed2));
  ASSERT_EQ(2u, coil.speeds().size());
  EXPECT_EQ(speed.handle(), coil.speeds()[0].handle());
  EXPECT_EQ(speed2.handle(), coil.speeds()[1].handle());
  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(speed.handle(), children[0].handle());
  EXPECT_EQ(speed2.handle(), children[1].handle());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[2].handle());
  EXPECT_TRUE(speed2.setReferenceUnitGrossRatedCoolingCOP(5.6));
  EXPECT_DOUBLE_EQ(5.6, coil.speeds()[1].referenceUnitGrossRatedCoolingCOP());

  auto attachedSpeed = coil.speeds()[0];
  EXPECT_DOUBLE_EQ(1524.1, attachedSpeed.referenceUnitGrossRatedTotalCoolingCapacity());
  EXPECT_TRUE(attachedSpeed.totalCoolingCapacityFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_EQ(7u, attachedSpeed.children().size());

  EXPECT_TRUE(attachedSpeed.setReferenceUnitGrossRatedCoolingCOP(4.5));
  EXPECT_DOUBLE_EQ(4.5, coil.speeds().front().referenceUnitGrossRatedCoolingCOP());

  coil.removeSpeed(attachedSpeed);
  ASSERT_EQ(1u, coil.speeds().size());
  EXPECT_EQ(speed2.handle(), coil.speeds().front().handle());
  EXPECT_DOUBLE_EQ(5.6, coil.speeds().front().referenceUnitGrossRatedCoolingCOP());

  coil.removeSpeed(coil.speeds().front());
  EXPECT_TRUE(coil.speeds().empty());
  const auto finalChildren = coil.children();
  ASSERT_EQ(1u, finalChildren.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), finalChildren.front().handle());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_AirflowNetworkEquivalentDuctRoundTrip) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_FALSE(coil.airflowNetworkEquivalentDuct());

  auto afnComponent = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), afnComponent.iddObject().type());
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit", afnComponent.coilObjectType());
  EXPECT_DOUBLE_EQ(1.25, afnComponent.airPathLength());
  EXPECT_DOUBLE_EQ(0.41, afnComponent.airPathHydraulicDiameter());

  auto attached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(attached);
  EXPECT_EQ(afnComponent.handle(), attached->handle());

  EXPECT_TRUE(afnComponent.setCoilObjectType("Coil:Heating:WaterToAirHeatPump:EquationFit"));

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[0].handle());
  EXPECT_EQ(afnComponent.handle(), children[1].handle());

  auto updated = coil.getAirflowNetworkEquivalentDuct(2.5, 0.82);
  EXPECT_EQ(afnComponent.handle(), updated.handle());
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit", updated.coilObjectType());
  EXPECT_DOUBLE_EQ(2.5, updated.airPathLength());
  EXPECT_DOUBLE_EQ(0.82, updated.airPathHydraulicDiameter());

  auto reattached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(reattached);
  EXPECT_EQ(afnComponent.handle(), reattached->handle());
  EXPECT_DOUBLE_EQ(2.5, reattached->airPathLength());
  EXPECT_DOUBLE_EQ(0.82, reattached->airPathHydraulicDiameter());
}


TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_RemoveCleansUpAttachedTransientSpeeds) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed1(model);
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed2(model);
  coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);

  ASSERT_TRUE(coil.addSpeed(speed1));
  ASSERT_TRUE(coil.addSpeed(speed2));
  ASSERT_EQ(2u, coil.speeds().size());
  EXPECT_EQ(2u, model.getModelObjects<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(false, true).size());
  EXPECT_EQ(1u, model.getModelObjects<AirflowNetworkDistributionComponentCoil>().size());

  coil.remove();

  EXPECT_TRUE(model.getModelObjects<CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>(false, true).empty());
  EXPECT_TRUE(model.getModelObjects<AirflowNetworkDistributionComponentCoil>().empty());
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  ASSERT_TRUE(
    coil.setPointer(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_FALSE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(1u, oaComponents.size());
}
