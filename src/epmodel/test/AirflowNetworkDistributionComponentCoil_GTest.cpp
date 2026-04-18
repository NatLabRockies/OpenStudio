/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkDistributionComponentCoil.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentCoil_DefaultConstructor) {
  Model model;
  AirflowNetworkDistributionComponentCoil coil(model);
  EXPECT_EQ(AirflowNetworkDistributionComponentCoil::iddObjectType(), coil.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkDistributionComponentCoil_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkDistributionComponentCoil coil(model);

  const auto coilObjectTypes = AirflowNetworkDistributionComponentCoil::coilObjectTypeValues();
  EXPECT_FALSE(coilObjectTypes.empty());
  EXPECT_NE(std::find(coilObjectTypes.begin(), coilObjectTypes.end(), "Coil:Cooling:WaterToAirHeatPump:EquationFit"), coilObjectTypes.end());
  EXPECT_NE(std::find(coilObjectTypes.begin(), coilObjectTypes.end(), "Coil:Heating:WaterToAirHeatPump:EquationFit"), coilObjectTypes.end());
  EXPECT_NE(std::find(coilObjectTypes.begin(), coilObjectTypes.end(), "Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit"),
            coilObjectTypes.end());
  EXPECT_NE(std::find(coilObjectTypes.begin(), coilObjectTypes.end(), "Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit"),
            coilObjectTypes.end());

  EXPECT_TRUE(coil.setCoilObjectType("Coil:Cooling:WaterToAirHeatPump:EquationFit"));
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:EquationFit", coil.coilObjectType());
  EXPECT_TRUE(coil.setCoilObjectType("Coil:Heating:WaterToAirHeatPump:EquationFit"));
  EXPECT_EQ("Coil:Heating:WaterToAirHeatPump:EquationFit", coil.coilObjectType());
  EXPECT_TRUE(coil.setCoilObjectType("Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit"));
  EXPECT_EQ("Coil:Cooling:WaterToAirHeatPump:VariableSpeedEquationFit", coil.coilObjectType());
  EXPECT_TRUE(coil.setCoilObjectType("Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit"));
  EXPECT_EQ("Coil:Heating:WaterToAirHeatPump:VariableSpeedEquationFit", coil.coilObjectType());

  EXPECT_TRUE(coil.setAirPathLength(1.25));
  EXPECT_DOUBLE_EQ(1.25, coil.airPathLength());

  EXPECT_TRUE(coil.setAirPathHydraulicDiameter(0.41));
  EXPECT_DOUBLE_EQ(0.41, coil.airPathHydraulicDiameter());
}
