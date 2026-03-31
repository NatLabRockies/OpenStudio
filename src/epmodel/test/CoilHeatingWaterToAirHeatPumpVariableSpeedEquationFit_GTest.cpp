/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpVariableSpeedEquationFit.hpp"

#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>

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
