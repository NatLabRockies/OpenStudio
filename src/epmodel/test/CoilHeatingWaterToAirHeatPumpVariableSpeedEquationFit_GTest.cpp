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
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
#include "../ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"

#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idf/Handle.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_DefaultConstructor) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  EXPECT_EQ(CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit::iddObjectType(), coil.iddObject().type());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName, coil.airInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName, coil.airOutletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterInletNodeName,
            coil.waterInletPort());
  EXPECT_EQ(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::WatertoRefrigerantHXWaterOutletNodeName,
            coil.waterOutletPort());
  EXPECT_FALSE(coil.airInletModelObject());
  EXPECT_FALSE(coil.airOutletModelObject());
  EXPECT_FALSE(coil.waterInletModelObject());
  EXPECT_FALSE(coil.waterOutletModelObject());

  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), coil.availabilitySchedule());
  EXPECT_EQ(1, coil.nominalSpeedLevel());
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
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

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_CurveConstructorAndSetterRoundTrip) {
  Model model;
  CurveQuadratic partLoadFraction(model);
  ScheduleConstant availability(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model, partLoadFraction);

  EXPECT_EQ(partLoadFraction, coil.energyPartLoadFractionCurve());
  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, coil.availabilitySchedule());

  CurveQuadratic replacement(model);
  EXPECT_TRUE(coil.setEnergyPartLoadFractionCurve(replacement));
  EXPECT_EQ(replacement, coil.energyPartLoadFractionCurve());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_ScalarAccessors_RoundTripAndAutosizeFlags) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_TRUE(coil.setNominalSpeedLevel(2));
  EXPECT_EQ(2, coil.nominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedHeatingCapacityAtSelectedNominalSpeedLevel(8100.0));
  ASSERT_TRUE(coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(8100.0, coil.ratedHeatingCapacityAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedHeatingCapacityAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedHeatingCapacityAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(0.71));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.71, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());

  EXPECT_TRUE(coil.setRatedWaterFlowRateAtSelectedNominalSpeedLevel(0.0032));
  ASSERT_TRUE(coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.0032, coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_SpeedChildrenRoundTrip) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed2(model);
  ASSERT_TRUE(speed2.setReferenceUnitGrossRatedHeatingCOP(5.2));

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
  EXPECT_TRUE(speed2.setReferenceUnitGrossRatedHeatingCOP(5.6));
  EXPECT_DOUBLE_EQ(5.6, coil.speeds()[1].referenceUnitGrossRatedHeatingCOP());

  auto attachedSpeed = coil.speeds()[0];
  EXPECT_DOUBLE_EQ(1838.7, attachedSpeed.referenceUnitGrossRatedHeatingCapacity());
  EXPECT_TRUE(attachedSpeed.heatingCapacityFunctionofTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_EQ(7u, attachedSpeed.children().size());

  EXPECT_TRUE(attachedSpeed.setReferenceUnitGrossRatedHeatingCOP(4.5));
  EXPECT_DOUBLE_EQ(4.5, coil.speeds().front().referenceUnitGrossRatedHeatingCOP());

  coil.removeSpeed(attachedSpeed);
  ASSERT_EQ(1u, coil.speeds().size());
  EXPECT_EQ(speed2.handle(), coil.speeds().front().handle());
  EXPECT_DOUBLE_EQ(5.6, coil.speeds().front().referenceUnitGrossRatedHeatingCOP());

  coil.removeSpeed(coil.speeds().front());
  EXPECT_TRUE(coil.speeds().empty());
  const auto finalChildren = coil.children();
  ASSERT_EQ(1u, finalChildren.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), finalChildren.front().handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_ChildrenFollowCanonicalOrderingWithSpeedAndAFN) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed(model);

  ASSERT_TRUE(coil.addSpeed(speed));
  auto afnComponent = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);

  const auto children = coil.children();
  ASSERT_EQ(3u, children.size());
  EXPECT_EQ(speed.handle(), children[0].handle());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(afnComponent.handle(), children[2].handle());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_AirflowNetworkEquivalentDuctRoundTrip) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_FALSE(coil.airflowNetworkEquivalentDuct());

  auto afnComponent = coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), afnComponent.iddObject().type());
  EXPECT_EQ("Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit", afnComponent.coilObjectType());
  EXPECT_DOUBLE_EQ(1.25, afnComponent.airPathLength());
  EXPECT_DOUBLE_EQ(0.41, afnComponent.airPathHydraulicDiameter());

  auto attached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(attached);
  EXPECT_EQ(afnComponent.handle(), attached->handle());

  const auto children = coil.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(coil.energyPartLoadFractionCurve().handle(), children[0].handle());
  EXPECT_EQ(afnComponent.handle(), children[1].handle());

  auto updated = coil.getAirflowNetworkEquivalentDuct(2.5, 0.82);
  EXPECT_EQ(afnComponent.handle(), updated.handle());
  EXPECT_EQ("Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit", updated.coilObjectType());
  EXPECT_DOUBLE_EQ(2.5, updated.airPathLength());
  EXPECT_DOUBLE_EQ(0.82, updated.airPathHydraulicDiameter());

  auto reattached = coil.airflowNetworkEquivalentDuct();
  ASSERT_TRUE(reattached);
  EXPECT_EQ(afnComponent.handle(), reattached->handle());
  EXPECT_DOUBLE_EQ(2.5, reattached->airPathLength());
  EXPECT_DOUBLE_EQ(0.82, reattached->airPathHydraulicDiameter());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_RemoveCleansUpAttachedTransientSpeeds) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed1(model);
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData speed2(model);
  coil.getAirflowNetworkEquivalentDuct(1.25, 0.41);

  ASSERT_TRUE(coil.addSpeed(speed1));
  ASSERT_TRUE(coil.addSpeed(speed2));
  ASSERT_EQ(2u, coil.speeds().size());
  EXPECT_EQ(2u, model.getConcreteModelObjects<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>().size());
  EXPECT_EQ(1u, model.getConcreteModelObjects<AirflowNetworkDistributionComponentCoil>().size());

  coil.remove();

  EXPECT_TRUE(model.getConcreteModelObjects<CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData>().empty());
  EXPECT_TRUE(model.getConcreteModelObjects<AirflowNetworkDistributionComponentCoil>().empty());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  ASSERT_TRUE(
    coil.setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName));

  const auto schedule = coil.availabilitySchedule();
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), schedule);
  const auto repairedSchedule =
    coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName);
  ASSERT_TRUE(repairedSchedule);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), *repairedSchedule);
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));

  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  EXPECT_FALSE(coil.addToNode(*outboardOANode));

  const auto oaComponents = oaSystem.oaComponents();
  ASSERT_EQ(1u, oaComponents.size());
}
