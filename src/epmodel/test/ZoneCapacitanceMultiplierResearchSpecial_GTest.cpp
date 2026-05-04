/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneCapacitanceMultiplierResearchSpecial.hpp"
#include "../ModelObject/ZoneCapacitanceMultiplierResearchSpecial_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneCapacitanceMultiplierResearchSpecial_DefaultConstructor) {
  Model model;
  auto zoneCapacitanceMultiplierResearchSpecial = model.getUniqueModelObject<ZoneCapacitanceMultiplierResearchSpecial>();
  EXPECT_EQ(ZoneCapacitanceMultiplierResearchSpecial::iddObjectType(), zoneCapacitanceMultiplierResearchSpecial.iddObject().type());

  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isTemperatureCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.temperatureCapacityMultiplier());
  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isHumidityCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.humidityCapacityMultiplier());
  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isCarbonDioxideCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.carbonDioxideCapacityMultiplier());
}

TEST_F(EPModelFixture, ZoneCapacitanceMultiplierResearchSpecial_ScalarAccessors_RoundTrip) {
  Model model;
  auto zoneCapacitanceMultiplierResearchSpecial = model.getUniqueModelObject<ZoneCapacitanceMultiplierResearchSpecial>();

  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.setTemperatureCapacityMultiplier(2.0));
  EXPECT_FALSE(zoneCapacitanceMultiplierResearchSpecial.isTemperatureCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(2.0, zoneCapacitanceMultiplierResearchSpecial.temperatureCapacityMultiplier());
  zoneCapacitanceMultiplierResearchSpecial.resetTemperatureCapacityMultiplier();
  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isTemperatureCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.temperatureCapacityMultiplier());

  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.setHumidityCapacityMultiplier(3.0));
  EXPECT_FALSE(zoneCapacitanceMultiplierResearchSpecial.isHumidityCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(3.0, zoneCapacitanceMultiplierResearchSpecial.humidityCapacityMultiplier());
  zoneCapacitanceMultiplierResearchSpecial.resetHumidityCapacityMultiplier();
  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isHumidityCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.humidityCapacityMultiplier());

  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.setCarbonDioxideCapacityMultiplier(4.0));
  EXPECT_FALSE(zoneCapacitanceMultiplierResearchSpecial.isCarbonDioxideCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(4.0, zoneCapacitanceMultiplierResearchSpecial.carbonDioxideCapacityMultiplier());
  zoneCapacitanceMultiplierResearchSpecial.resetCarbonDioxideCapacityMultiplier();
  EXPECT_TRUE(zoneCapacitanceMultiplierResearchSpecial.isCarbonDioxideCapacityMultiplierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, zoneCapacitanceMultiplierResearchSpecial.carbonDioxideCapacityMultiplier());
}
