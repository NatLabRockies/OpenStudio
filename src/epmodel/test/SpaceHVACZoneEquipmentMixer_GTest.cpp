/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SpaceHVACZoneEquipmentMixer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SpaceHVACZoneEquipmentMixer_DefaultConstructor) {
  Model model;
  SpaceHVACZoneEquipmentMixer object(model);
  EXPECT_EQ(SpaceHVACZoneEquipmentMixer::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SpaceHVACZoneEquipmentMixer_ScalarAccessors_RoundTrip) {
  Model model;
  SpaceHVACZoneEquipmentMixer object(model);

  // This type has no fixed class-specific simple scalar fields; base Name scalar is roundtrip coverage.
  EXPECT_TRUE(object.setName("EPModel SpaceHVAC Zone Equipment Mixer"));
  EXPECT_EQ("EPModel SpaceHVAC Zone Equipment Mixer", object.nameString());
}
