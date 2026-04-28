/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <array>

#include "../scaffolds/SiteGroundReflectanceSnowModifier.hpp"
#include "EPModelFixture.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundReflectanceSnowModifier_DefaultConstructor) {
  Model model;
  SiteGroundReflectanceSnowModifier object(model);

  EXPECT_EQ(SiteGroundReflectanceSnowModifier::iddObjectType(), object.iddObject().type());
  EXPECT_TRUE(object.isGroundReflectedSolarModifierDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.groundReflectedSolarModifier());
}

struct SnowModifierAccessor
{
  const char* name;
  double (SiteGroundReflectanceSnowModifier::*getter)() const;
  bool (SiteGroundReflectanceSnowModifier::*isDefaulted)() const;
  bool (SiteGroundReflectanceSnowModifier::*setter)(double);
  void (SiteGroundReflectanceSnowModifier::*reset)();
};

TEST_F(EPModelFixture, SiteGroundReflectanceSnowModifier_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundReflectanceSnowModifier object(model);

  constexpr double defaultValue = 1.0;
  constexpr double updatedValue = 0.75;

  constexpr std::array<SnowModifierAccessor, 2> modifiers{
    SnowModifierAccessor{.name = "GroundReflectedSolar",
                         .getter = &SiteGroundReflectanceSnowModifier::groundReflectedSolarModifier,
                         .isDefaulted = &SiteGroundReflectanceSnowModifier::isGroundReflectedSolarModifierDefaulted,
                         .setter = &SiteGroundReflectanceSnowModifier::setGroundReflectedSolarModifier,
                         .reset = &SiteGroundReflectanceSnowModifier::resetGroundReflectedSolarModifier},
    SnowModifierAccessor{.name = "DaylightingGroundReflectedSolar",
                         .getter = &SiteGroundReflectanceSnowModifier::daylightingGroundReflectedSolarModifier,
                         .isDefaulted = &SiteGroundReflectanceSnowModifier::isDaylightingGroundReflectedSolarModifierDefaulted,
                         .setter = &SiteGroundReflectanceSnowModifier::setDaylightingGroundReflectedSolarModifier,
                         .reset = &SiteGroundReflectanceSnowModifier::resetDaylightingGroundReflectedSolarModifier},
  };

  for (const auto& modifier : modifiers) {
    SCOPED_TRACE(modifier.name);
    EXPECT_TRUE((object.*modifier.isDefaulted)());
    EXPECT_DOUBLE_EQ(defaultValue, (object.*modifier.getter)());
    EXPECT_TRUE((object.*modifier.setter)(updatedValue));
    EXPECT_FALSE((object.*modifier.isDefaulted)());
    EXPECT_DOUBLE_EQ(updatedValue, (object.*modifier.getter)());
    (object.*modifier.reset)();
    EXPECT_TRUE((object.*modifier.isDefaulted)());
    EXPECT_DOUBLE_EQ(defaultValue, (object.*modifier.getter)());
  }
}
