/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/HybridModelZone.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HybridModelZone_DefaultConstructor) {
  Model model;
  HybridModelZone hybridModelZone(model);
  EXPECT_EQ(HybridModelZone::iddObjectType(), hybridModelZone.iddObject().type());
}

TEST_F(EPModelFixture, HybridModelZone_ScalarAccessors_RoundTrip) {
  Model model;
  HybridModelZone hybridModelZone(model);

  EXPECT_TRUE(hybridModelZone.isCalculateZoneInternalThermalMassDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZoneInternalThermalMass());
  EXPECT_TRUE(hybridModelZone.setCalculateZoneInternalThermalMass(true));
  EXPECT_TRUE(hybridModelZone.calculateZoneInternalThermalMass());
  EXPECT_FALSE(hybridModelZone.isCalculateZoneInternalThermalMassDefaulted());
  hybridModelZone.resetCalculateZoneInternalThermalMass();
  EXPECT_TRUE(hybridModelZone.isCalculateZoneInternalThermalMassDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZoneInternalThermalMass());

  EXPECT_TRUE(hybridModelZone.isCalculateZoneAirInfiltrationRateDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZoneAirInfiltrationRate());
  EXPECT_TRUE(hybridModelZone.setCalculateZoneAirInfiltrationRate(true));
  EXPECT_TRUE(hybridModelZone.calculateZoneAirInfiltrationRate());
  EXPECT_FALSE(hybridModelZone.isCalculateZoneAirInfiltrationRateDefaulted());
  hybridModelZone.resetCalculateZoneAirInfiltrationRate();
  EXPECT_TRUE(hybridModelZone.isCalculateZoneAirInfiltrationRateDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZoneAirInfiltrationRate());

  EXPECT_TRUE(hybridModelZone.isCalculateZonePeopleCountDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZonePeopleCount());
  EXPECT_TRUE(hybridModelZone.setCalculateZonePeopleCount(true));
  EXPECT_TRUE(hybridModelZone.calculateZonePeopleCount());
  EXPECT_FALSE(hybridModelZone.isCalculateZonePeopleCountDefaulted());
  hybridModelZone.resetCalculateZonePeopleCount();
  EXPECT_TRUE(hybridModelZone.isCalculateZonePeopleCountDefaulted());
  EXPECT_FALSE(hybridModelZone.calculateZonePeopleCount());

  EXPECT_TRUE(hybridModelZone.setBeginMonth(1));
  EXPECT_EQ(1, hybridModelZone.beginMonth());

  EXPECT_TRUE(hybridModelZone.setBeginDayofMonth(15));
  EXPECT_EQ(15, hybridModelZone.beginDayofMonth());

  EXPECT_TRUE(hybridModelZone.setEndMonth(2));
  EXPECT_EQ(2, hybridModelZone.endMonth());

  EXPECT_TRUE(hybridModelZone.setEndDayofMonth(28));
  EXPECT_EQ(28, hybridModelZone.endDayofMonth());
}
