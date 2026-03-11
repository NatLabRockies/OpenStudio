/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/MaterialPropertyVariableAbsorptance.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyVariableAbsorptance_DefaultConstructor) {
  Model model;
  MaterialPropertyVariableAbsorptance object(model);
  EXPECT_EQ(MaterialPropertyVariableAbsorptance::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyVariableAbsorptance_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyVariableAbsorptance object(model);

  EXPECT_FALSE(MaterialPropertyVariableAbsorptance::controlSignalValues().empty());
  EXPECT_EQ("SurfaceTemperature", object.controlSignal());
  EXPECT_TRUE(object.isControlSignalDefaulted());

  EXPECT_TRUE(object.setControlSignal("Scheduled"));
  EXPECT_EQ("Scheduled", object.controlSignal());
  EXPECT_FALSE(object.isControlSignalDefaulted());
  object.resetControlSignal();
  EXPECT_TRUE(object.isControlSignalDefaulted());
  EXPECT_EQ("SurfaceTemperature", object.controlSignal());

  EXPECT_FALSE(object.thermalAbsorptanceFunctionName());
  EXPECT_TRUE(object.setThermalAbsorptanceFunctionName("TA Curve"));
  ASSERT_TRUE(object.thermalAbsorptanceFunctionName());
  EXPECT_EQ("TA Curve", object.thermalAbsorptanceFunctionName().get());
  object.resetThermalAbsorptanceFunctionName();
  EXPECT_FALSE(object.thermalAbsorptanceFunctionName());

  EXPECT_FALSE(object.thermalAbsorptanceScheduleName());
  EXPECT_TRUE(object.setThermalAbsorptanceScheduleName("TA Schedule"));
  ASSERT_TRUE(object.thermalAbsorptanceScheduleName());
  EXPECT_EQ("TA Schedule", object.thermalAbsorptanceScheduleName().get());
  object.resetThermalAbsorptanceScheduleName();
  EXPECT_FALSE(object.thermalAbsorptanceScheduleName());

  EXPECT_FALSE(object.solarAbsorptanceFunctionName());
  EXPECT_TRUE(object.setSolarAbsorptanceFunctionName("SA Curve"));
  ASSERT_TRUE(object.solarAbsorptanceFunctionName());
  EXPECT_EQ("SA Curve", object.solarAbsorptanceFunctionName().get());
  object.resetSolarAbsorptanceFunctionName();
  EXPECT_FALSE(object.solarAbsorptanceFunctionName());

  EXPECT_FALSE(object.solarAbsorptanceScheduleName());
  EXPECT_TRUE(object.setSolarAbsorptanceScheduleName("SA Schedule"));
  ASSERT_TRUE(object.solarAbsorptanceScheduleName());
  EXPECT_EQ("SA Schedule", object.solarAbsorptanceScheduleName().get());
  object.resetSolarAbsorptanceScheduleName();
  EXPECT_FALSE(object.solarAbsorptanceScheduleName());
}
