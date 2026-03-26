/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/WaterHeaterStratified.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterStratified_DefaultConstructor) {
  Model model;
  WaterHeaterStratified heater(model);
  EXPECT_EQ(WaterHeaterStratified::iddObjectType(), heater.iddObject().type());
  EXPECT_FALSE(heater.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), heater.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), heater.demandInletPort());
}

TEST_F(EPModelFixture, WaterHeaterStratified_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterStratified heater(model);

  EXPECT_TRUE(heater.setTankVolume(0.65));
  ASSERT_TRUE(heater.tankVolume());
  EXPECT_DOUBLE_EQ(0.65, heater.tankVolume().get());
  heater.autosizeTankVolume();
  EXPECT_TRUE(heater.isTankVolumeAutosized());

  EXPECT_TRUE(heater.setTankHeight(1.2));
  ASSERT_TRUE(heater.tankHeight());
  heater.autosizeTankHeight();
  EXPECT_TRUE(heater.isTankHeightAutosized());

  EXPECT_TRUE(heater.setHeaterFuelType("Electricity"));
  EXPECT_EQ("Electricity", heater.heaterFuelType());

  EXPECT_TRUE(heater.setHeaterThermalEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, heater.heaterThermalEfficiency());

  EXPECT_TRUE(heater.setOffCycleParasiticFuelType("Electricity"));
  EXPECT_TRUE(heater.setOnCycleParasiticFuelType("NaturalGas"));

  EXPECT_TRUE(heater.setAmbientTemperatureIndicator("ThermalZone"));
  EXPECT_EQ("ThermalZone", heater.ambientTemperatureIndicator());

  EXPECT_TRUE(heater.setAmbientTemperatureOutdoorAirNodeName("OutdoorNode"));
  ASSERT_TRUE(heater.ambientTemperatureOutdoorAirNodeName());
  heater.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_FALSE(heater.ambientTemperatureOutdoorAirNodeName());

  EXPECT_TRUE(heater.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(2.5));
  heater.resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

  EXPECT_TRUE(heater.setPeakUseFlowRate(0.002));
  heater.resetPeakUseFlowRate();

  EXPECT_TRUE(heater.setUseSideOutletHeight(0.4));
  EXPECT_DOUBLE_EQ(0.4, heater.useSideOutletHeight().get());
  heater.autocalculateUseSideOutletHeight();
  EXPECT_TRUE(heater.isUseSideOutletHeightAutocalculated());

  EXPECT_TRUE(heater.setSourceSideInletHeight(0.25));
  EXPECT_DOUBLE_EQ(0.25, heater.sourceSideInletHeight().get());
  heater.autocalculateSourceSideInletHeight();
  EXPECT_TRUE(heater.isSourceSideInletHeightAutocalculated());

  EXPECT_TRUE(heater.setUseSideDesignFlowRate(0.002));
  heater.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(heater.isUseSideDesignFlowRateAutosized());

  EXPECT_TRUE(heater.setSourceSideDesignFlowRate(0.0015));
  heater.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(heater.isSourceSideDesignFlowRateAutosized());

  EXPECT_TRUE(heater.setNumberofNodes(3));
  EXPECT_TRUE(heater.setNode1AdditionalLossCoefficient(0.1));

  EXPECT_TRUE(heater.setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint"));
  EXPECT_EQ("IndirectHeatPrimarySetpoint", heater.sourceSideFlowControlMode());

  EXPECT_TRUE(heater.setEndUseSubcategory("DomesticHotWater"));
  EXPECT_EQ("DomesticHotWater", heater.endUseSubcategory());
}
