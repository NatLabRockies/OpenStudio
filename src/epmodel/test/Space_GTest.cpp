/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../DesignSpecificationOutdoorAir.hpp"
#include "../DesignSpecificationOutdoorAirSpaceList.hpp"
#include "../DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "../SizingZone.hpp"
#include "../Space.hpp"
#include "../ThermalZone.hpp"

#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_Space_DefaultConstructor) {
  Model model;
  Space space(model);
  EXPECT_EQ(Space::iddObjectType(), space.iddObject().type());
}

TEST_F(EPModelFixture, API_Space_ThermalZoneSetReset) {
  Model model;
  Space space(model);
  ThermalZone zone(model);

  EXPECT_FALSE(space.thermalZone());
  EXPECT_TRUE(space.setThermalZone(zone));

  auto linkedZone = space.thermalZone();
  ASSERT_TRUE(linkedZone);
  EXPECT_EQ(zone, *linkedZone);

  space.resetThermalZone();
  EXPECT_FALSE(space.thermalZone());
}

TEST_F(EPModelFixture, API_Space_SetDesignSpecificationOutdoorAir_UnzonedSpace_PersistsViaOrphanList) {
  Model model;
  Space space(model);
  DesignSpecificationOutdoorAir dsoa(model);

  EXPECT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));
  auto assigned = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(assigned);
  EXPECT_EQ(dsoa, *assigned);

  const auto lists = model.getConcreteModelObjects<DesignSpecificationOutdoorAirSpaceList>();
  ASSERT_FALSE(lists.empty());
  bool found = false;
  for (const auto& list : lists) {
    if (auto fromList = list.designSpecificationOutdoorAir(space)) {
      EXPECT_EQ(dsoa, *fromList);
      found = true;
    }
  }
  EXPECT_TRUE(found);
}

TEST_F(EPModelFixture, API_Space_SetThermalZone_MigratesUnzonedAssignmentToZoneList) {
  Model model;
  Space space(model);
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  ThermalZone zone(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  auto assigned = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(assigned);
  EXPECT_EQ(dsoa, *assigned);

  auto zoneList = zone.sizingZone().getModelObjectTarget<DesignSpecificationOutdoorAirSpaceList>(
    openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(zoneList);
  auto zoneAssignment = zoneList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(zoneAssignment);
  EXPECT_EQ(dsoa, *zoneAssignment);
}

TEST_F(EPModelFixture, API_Space_ResetThermalZone_MigratesAssignmentToOrphanList) {
  Model model;
  Space space(model);
  ThermalZone zone(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  space.resetThermalZone();
  EXPECT_FALSE(space.thermalZone());

  auto assigned = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(assigned);
  EXPECT_EQ(dsoa, *assigned);
}

TEST_F(EPModelFixture, API_Space_Canonicalize_RemovesEmptyOrphanDSOASpaceList) {
  Model model;
  Space space(model);
  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto orphanList = model.getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Orphan Spaces DSOA Space List");
  ASSERT_TRUE(orphanList);
  ASSERT_GT(orphanList->numExtensibleGroups(), 0u);

  ThermalZone zone(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  orphanList = model.getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Orphan Spaces DSOA Space List");
  ASSERT_TRUE(orphanList);
  EXPECT_EQ(0u, orphanList->numExtensibleGroups());

  model.canonicalize(SanitizationPolicy::Repair);
  orphanList = model.getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Orphan Spaces DSOA Space List");
  EXPECT_FALSE(orphanList);
}
