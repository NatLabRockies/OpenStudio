/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ParentObject/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFitSpeedData.hpp"
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
  EXPECT_TRUE(coil.energyPartLoadFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(coil.children().size() == 1u);
  EXPECT_TRUE(coil.speeds().empty());
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

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_ScalarAccessors_RoundTrip) {
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
  EXPECT_FALSE(coil.autosizedRatedHeatingCapacityAtSelectedNominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedAirFlowRateAtSelectedNominalSpeedLevel(0.71));
  ASSERT_TRUE(coil.ratedAirFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.71, coil.ratedAirFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedAirFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.autosizedRatedAirFlowRateAtSelectedNominalSpeedLevel());

  EXPECT_TRUE(coil.setRatedWaterFlowRateAtSelectedNominalSpeedLevel(0.0032));
  ASSERT_TRUE(coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel());
  EXPECT_DOUBLE_EQ(0.0032, coil.ratedWaterFlowRateAtSelectedNominalSpeedLevel().get());
  EXPECT_FALSE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  coil.autosizeRatedWaterFlowRateAtSelectedNominalSpeedLevel();
  EXPECT_TRUE(coil.isRatedWaterFlowRateAtSelectedNominalSpeedLevelAutosized());
  EXPECT_FALSE(coil.autosizedRatedWaterFlowRateAtSelectedNominalSpeedLevel());
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
  EXPECT_EQ(3u, coil.children().size());
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
  EXPECT_EQ(1u, coil.children().size());
}

TEST_F(EPModelFixture, CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit_AvailabilityScheduleGetterRepairsMissingRequiredReference) {
  Model model;
  CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit coil(model);

  ASSERT_TRUE(
    coil.setPointer(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName, openstudio::Handle()));
  EXPECT_FALSE(coil.getModelObjectTarget<Schedule>(openstudio::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::AvailabilityScheduleName));

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
