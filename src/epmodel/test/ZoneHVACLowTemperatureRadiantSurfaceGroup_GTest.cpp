/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup.hpp"

#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_SurfaceGroup_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantSurfaceGroup_DefaultConstructor) {
  Model model;
  ZoneHVACLowTemperatureRadiantSurfaceGroup group(model);

  EXPECT_EQ(ZoneHVACLowTemperatureRadiantSurfaceGroup::iddObjectType(), group.iddObject().type());
  EXPECT_TRUE(group.surfaces().empty());
  EXPECT_TRUE(group.flowFractions().empty());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantSurfaceGroup_SurfaceRows_RoundTrip) {
  Model model;
  ZoneHVACLowTemperatureRadiantSurfaceGroup group(model);
  Surface floor(model);
  Surface ceiling(model);

  ASSERT_TRUE(floor.setName("Radiant Floor"));
  ASSERT_TRUE(ceiling.setName("Radiant Ceiling"));
  ASSERT_TRUE(floor.setSurfaceType("Floor"));
  ASSERT_TRUE(ceiling.setSurfaceType("Roof"));

  // This EnergyPlus-only emitted companion wrapper is intentionally read-
  // oriented in the public API. Populate the persisted extensible rows
  // directly and verify that the typed getters read them back correctly.
  auto floorGroup = group.pushExtensibleGroup();
  EXPECT_TRUE(floorGroup.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::SurfaceName, floor.nameString()));
  EXPECT_TRUE(floorGroup.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::FlowFractionforSurface, 0.4));

  auto ceilingGroup = group.pushExtensibleGroup();
  EXPECT_TRUE(ceilingGroup.setString(openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::SurfaceName, ceiling.nameString()));
  EXPECT_TRUE(ceilingGroup.setDouble(openstudio::ZoneHVAC_LowTemperatureRadiant_SurfaceGroupExtensibleFields::FlowFractionforSurface, 0.6));

  ASSERT_EQ(2u, group.surfaces().size());
  EXPECT_EQ(floor.handle(), group.surfaces()[0].handle());
  EXPECT_EQ(ceiling.handle(), group.surfaces()[1].handle());

  ASSERT_EQ(2u, group.flowFractions().size());
  EXPECT_DOUBLE_EQ(0.4, group.flowFractions()[0]);
  EXPECT_DOUBLE_EQ(0.6, group.flowFractions()[1]);

  group.clearExtensibleGroups();
  EXPECT_TRUE(group.surfaces().empty());
  EXPECT_TRUE(group.flowFractions().empty());
}
