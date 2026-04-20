/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/WindowThermalModelParams.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowThermalModelParams_DefaultConstructor) {
  Model model;
  WindowThermalModelParams params(model);
  EXPECT_EQ(WindowThermalModelParams::iddObjectType(), params.iddObject().type());
  EXPECT_EQ("ISO15099", params.standard());
  EXPECT_EQ("ISO15099", params.thermalModel());
  EXPECT_DOUBLE_EQ(1.0, params.sdScalar());
  EXPECT_EQ("NoDeflection", params.deflectionModel());
  EXPECT_DOUBLE_EQ(13.238, params.vacuumPressureLimit());
  EXPECT_DOUBLE_EQ(25.0, params.initialTemperature());
  EXPECT_DOUBLE_EQ(101325.0, params.initialPressure());
}

TEST_F(EPModelFixture, WindowThermalModelParams_ScalarAccessors_RoundTrip) {
  Model model;
  WindowThermalModelParams params(model);

  EXPECT_TRUE(params.setStandard("EN673Design"));
  EXPECT_EQ("EN673Design", params.standard());
  EXPECT_FALSE(params.isStandardDefaulted());
  params.resetStandard();
  EXPECT_TRUE(params.isStandardDefaulted());
  EXPECT_TRUE(params.setStandard("EN673Declared"));
  EXPECT_EQ("EN673Declared", params.standard());

  EXPECT_TRUE(params.setThermalModel("ScaledCavityWidth"));
  EXPECT_EQ("ScaledCavityWidth", params.thermalModel());
  EXPECT_FALSE(params.isThermalModelDefaulted());
  params.resetThermalModel();
  EXPECT_TRUE(params.isThermalModelDefaulted());
  EXPECT_TRUE(params.setThermalModel("ConvectiveScalarModel_withSDThickness"));
  EXPECT_EQ("ConvectiveScalarModel_withSDThickness", params.thermalModel());

  EXPECT_TRUE(params.setSdScalar(0.6));
  EXPECT_DOUBLE_EQ(0.6, params.sdScalar());
  EXPECT_FALSE(params.isSdScalarDefaulted());
  params.resetSdScalar();
  EXPECT_TRUE(params.isSdScalarDefaulted());
  EXPECT_TRUE(params.setSdScalar(0.85));
  EXPECT_DOUBLE_EQ(0.85, params.sdScalar());

  EXPECT_TRUE(params.setDeflectionModel("MeasuredDeflection"));
  EXPECT_EQ("MeasuredDeflection", params.deflectionModel());
  EXPECT_FALSE(params.isDeflectionModelDefaulted());
  params.resetDeflectionModel();
  EXPECT_TRUE(params.isDeflectionModelDefaulted());
  EXPECT_TRUE(params.setDeflectionModel("TemperatureAndPressureInput"));
  EXPECT_EQ("TemperatureAndPressureInput", params.deflectionModel());

  EXPECT_TRUE(params.setVacuumPressureLimit(42.25));
  EXPECT_DOUBLE_EQ(42.25, params.vacuumPressureLimit());
  EXPECT_FALSE(params.isVacuumPressureLimitDefaulted());
  params.resetVacuumPressureLimit();
  EXPECT_TRUE(params.isVacuumPressureLimitDefaulted());
  EXPECT_TRUE(params.setVacuumPressureLimit(50.7));
  EXPECT_DOUBLE_EQ(50.7, params.vacuumPressureLimit());

  EXPECT_TRUE(params.setInitialTemperature(40.0));
  EXPECT_DOUBLE_EQ(40.0, params.initialTemperature());
  EXPECT_FALSE(params.isInitialTemperatureDefaulted());
  params.resetInitialTemperature();
  EXPECT_TRUE(params.isInitialTemperatureDefaulted());
  EXPECT_TRUE(params.setInitialTemperature(60.0));
  EXPECT_DOUBLE_EQ(60.0, params.initialTemperature());

  EXPECT_TRUE(params.setInitialPressure(150000.0));
  EXPECT_DOUBLE_EQ(150000.0, params.initialPressure());
  EXPECT_FALSE(params.isInitialPressureDefaulted());
  params.resetInitialPressure();
  EXPECT_TRUE(params.isInitialPressureDefaulted());
  EXPECT_TRUE(params.setInitialPressure(110000.0));
  EXPECT_DOUBLE_EQ(110000.0, params.initialPressure());
}
