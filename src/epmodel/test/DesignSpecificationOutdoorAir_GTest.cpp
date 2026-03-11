/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../DesignSpecificationOutdoorAir.hpp"
#include "../DesignSpecificationOutdoorAir_Impl.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../Space.hpp"
#include "../HVACComponent/ThermalZone.hpp"

#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idd/DesignSpecification_OutdoorAir_SpaceList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAir_DefaultConstructor) {
  Model model;
  DesignSpecificationOutdoorAir dsoa(model);
  EXPECT_EQ(DesignSpecificationOutdoorAir::iddObjectType(), dsoa.iddObject().type());
  EXPECT_FALSE(dsoa.outdoorAirMethod().empty());
  EXPECT_DOUBLE_EQ(0.0, dsoa.outdoorAirFlowRate());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_DefaultConstructor) {
  Model model;
  DesignSpecificationOutdoorAirSpaceList list(model);
  EXPECT_EQ(DesignSpecificationOutdoorAirSpaceList::iddObjectType(), list.iddObject().type());
  EXPECT_TRUE(list.spaces().empty());
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_NameScalarAccessor_RoundTrip) {
  Model model;
  DesignSpecificationOutdoorAirSpaceList list(model);
  ASSERT_TRUE(list.setName("DSOA Space List A"));
  EXPECT_EQ("DSOA Space List A", list.nameString());
}

TEST_F(EPModelFixture, API_Space_SetDesignSpecificationOutdoorAir_CreatesZoneSpaceListEntry) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);

  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject =
    sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(dsoaSpaceList);
  auto mapped = dsoaSpaceList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(mapped);
  EXPECT_EQ(dsoa, *mapped);
}

TEST_F(EPModelFixture, API_Space_DesignSpecificationOutdoorAir_FromSpaceSetter) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  auto spaceDSOA = space.designSpecificationOutdoorAir();
  ASSERT_TRUE(spaceDSOA);
  EXPECT_EQ(dsoa, *spaceDSOA);
}

TEST_F(EPModelFixture, API_SizingZone_Canonicalize_NormalizesDirectToSpaceList_SingleSpace) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject =
    sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto spaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(spaceList);
  const auto spaces = spaceList->spaces();
  ASSERT_EQ(1u, spaces.size());
  EXPECT_EQ(space, spaces.front());
  auto listedDSOA = spaceList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(listedDSOA);
  EXPECT_EQ(dsoa, *listedDSOA);
}

TEST_F(EPModelFixture, API_SizingZone_Canonicalize_NormalizesDirectToSpaceList_MultiSpace) {
  Model model;
  ThermalZone zone(model);
  Space space1(model);
  Space space2(model);
  ASSERT_TRUE(space1.setThermalZone(zone));
  ASSERT_TRUE(space2.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa(model);
  ASSERT_TRUE(space1.setDesignSpecificationOutdoorAir(dsoa));
  ASSERT_TRUE(space2.setDesignSpecificationOutdoorAir(dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto sizingZone = zone.sizingZone();
  auto sizingZoneImpl = sizingZone.getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  auto dsoaObject =
    sizingZone.getModelObjectTarget<ModelObject>(openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  auto directDSOA = dsoaObject ? dsoaObject->optionalCast<DesignSpecificationOutdoorAir>() : boost::none;
  EXPECT_FALSE(directDSOA);
  auto spaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
  ASSERT_TRUE(spaceList);
  EXPECT_EQ(2u, spaceList->spaces().size());
  auto listed1 = spaceList->designSpecificationOutdoorAir(space1);
  auto listed2 = spaceList->designSpecificationOutdoorAir(space2);
  ASSERT_TRUE(listed1);
  ASSERT_TRUE(listed2);
  EXPECT_EQ(dsoa, *listed1);
  EXPECT_EQ(dsoa, *listed2);
}

TEST_F(EPModelFixture, API_Space_DesignSpecificationOutdoorAir_FromSpaceList) {
  Model model;
  ThermalZone zone(model);
  Space space1(model);
  Space space2(model);
  ASSERT_TRUE(space1.setThermalZone(zone));
  ASSERT_TRUE(space2.setThermalZone(zone));

  DesignSpecificationOutdoorAir dsoa1(model);
  DesignSpecificationOutdoorAir dsoa2(model);
  dsoa1.setOutdoorAirFlowRate(0.1);
  dsoa2.setOutdoorAirFlowRate(0.2);

  ASSERT_TRUE(space1.setDesignSpecificationOutdoorAir(dsoa1));
  ASSERT_TRUE(space2.setDesignSpecificationOutdoorAir(dsoa2));

  auto space1DSOA = space1.designSpecificationOutdoorAir();
  auto space2DSOA = space2.designSpecificationOutdoorAir();
  ASSERT_TRUE(space1DSOA);
  ASSERT_TRUE(space2DSOA);
  EXPECT_EQ(dsoa1, *space1DSOA);
  EXPECT_EQ(dsoa2, *space2DSOA);
}

TEST_F(EPModelFixture, API_DesignSpecificationOutdoorAirSpaceList_Canonicalize_DeduplicatesConflictingSpaceRows) {
  Model model;
  Space space(model);
  DesignSpecificationOutdoorAir dsoa1(model);
  DesignSpecificationOutdoorAir dsoa2(model);
  dsoa1.setName("DSOA 1");
  dsoa2.setName("DSOA 2");

  DesignSpecificationOutdoorAirSpaceList list(model);
  list.setName("Orphan Spaces DSOA Space List");

  auto group1 = list.pushExtensibleGroup();
  auto workspaceGroup1 = group1.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup1);
  ASSERT_TRUE(
    workspaceGroup1->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle()));
  ASSERT_TRUE(workspaceGroup1->setPointer(
    openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, dsoa1.handle()));

  auto group2 = list.pushExtensibleGroup();
  auto workspaceGroup2 = group2.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup2);
  ASSERT_TRUE(
    workspaceGroup2->setPointer(openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceName, space.handle()));
  ASSERT_TRUE(workspaceGroup2->setPointer(
    openstudio::DesignSpecification_OutdoorAir_SpaceListExtensibleFields::SpaceDesignSpecificationOutdoorAirObjectName, dsoa2.handle()));

  EXPECT_EQ(2u, list.numExtensibleGroups());
  model.canonicalize(SanitizationPolicy::Repair);

  EXPECT_EQ(1u, list.numExtensibleGroups());
  auto assigned = list.designSpecificationOutdoorAir(space);
  ASSERT_TRUE(assigned);
  EXPECT_EQ(dsoa1, *assigned);
}
