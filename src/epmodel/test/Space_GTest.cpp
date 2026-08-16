/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "../ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "../ModelObject/SizingZone.hpp"
#include "../ModelObject/SizingZone_Impl.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurface/Surface_Impl.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../PlanarSurfaceGroup/Space_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Thermostat/ThermostatSetpointDualSetpoint.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idd/ZoneControl_Thermostat_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_Space_DefaultConstructor) {
  Model model;
  Space space(model);
  EXPECT_EQ(Space::iddObjectType(), space.iddObject().type());
}

TEST_F(EPModelFixture, API_Space_ScalarAccessors_RoundTrip) {
  Model model;
  Space space(model);

  EXPECT_TRUE(space.isCeilingHeightDefaulted());
  EXPECT_TRUE(space.isVolumeDefaulted());
  EXPECT_TRUE(space.isFloorAreaDefaulted());

  EXPECT_TRUE(space.setCeilingHeight(2.8));
  EXPECT_TRUE(space.setVolume(125.0));
  EXPECT_TRUE(space.setFloorArea(45.0));

  EXPECT_DOUBLE_EQ(2.8, space.ceilingHeight());
  EXPECT_DOUBLE_EQ(125.0, space.volume());
  EXPECT_DOUBLE_EQ(45.0, space.floorArea());

  EXPECT_FALSE(space.isCeilingHeightDefaulted());
  EXPECT_FALSE(space.isVolumeDefaulted());
  EXPECT_FALSE(space.isFloorAreaDefaulted());

  space.autocalculateCeilingHeight();
  space.autocalculateVolume();
  space.autocalculateFloorArea();

  EXPECT_TRUE(space.isCeilingHeightAutocalculated());
  EXPECT_TRUE(space.isVolumeAutocalculated());
  EXPECT_TRUE(space.isFloorAreaAutocalculated());

  space.resetCeilingHeight();
  space.resetVolume();
  space.resetFloorArea();

  EXPECT_TRUE(space.isCeilingHeightDefaulted());
  EXPECT_TRUE(space.isVolumeDefaulted());
  EXPECT_TRUE(space.isFloorAreaDefaulted());
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

TEST_F(EPModelFixture, API_Space_ThermalZoneSynchronizesSurfaceZoneStorage) {
  Model model;
  const std::vector<openstudio::Point3d> floorPrint{{0.0, 0.0, 0.0}, {0.0, 10.0, 0.0}, {10.0, 10.0, 0.0}, {10.0, 0.0, 0.0}};
  auto space = Space::fromFloorPrint(floorPrint, 3.0, model);
  ASSERT_TRUE(space);
  ThermalZone zone(model);

  ASSERT_TRUE(space->setThermalZone(zone));
  ASSERT_EQ(6u, space->surfaces().size());
  for (const auto& surface : space->surfaces()) {
    const auto target = surface.getTarget(openstudio::BuildingSurface_DetailedFields::ZoneName);
    ASSERT_TRUE(target);
    EXPECT_EQ(zone.handle(), target->handle());
  }

  // Assigning an existing Surface to an already-zoned Space synchronizes both
  // redundant EnergyPlus relationship fields in the same public operation.
  Space destination(model);
  ThermalZone destinationZone(model);
  ASSERT_TRUE(destination.setThermalZone(destinationZone));
  auto movedSurface = space->surfaces().back();
  ASSERT_TRUE(movedSurface.setSpace(destination));
  const auto movedZoneTarget = movedSurface.getTarget(openstudio::BuildingSurface_DetailedFields::ZoneName);
  ASSERT_TRUE(movedZoneTarget);
  EXPECT_EQ(destinationZone.handle(), movedZoneTarget->handle());

  // Intentional malformed-import fixture: canonicalization restores the
  // redundant field from the typed Space -> ThermalZone relationship.
  auto surface = space->surfaces().front();
  ASSERT_TRUE(surface.setString(openstudio::BuildingSurface_DetailedFields::ZoneName, ""));
  const auto report = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_GT(report.warningCount, 0u);
  EXPECT_TRUE(surface.getString(openstudio::BuildingSurface_DetailedFields::ZoneName, false, true).value_or("").empty());
  model.canonicalize(SanitizationPolicy::Repair);
  auto repairedTarget = surface.getTarget(openstudio::BuildingSurface_DetailedFields::ZoneName);
  ASSERT_TRUE(repairedTarget);
  EXPECT_EQ(zone.handle(), repairedTarget->handle());

  space->resetThermalZone();
  for (const auto& currentSurface : space->surfaces()) {
    EXPECT_TRUE(currentSurface.getString(openstudio::BuildingSurface_DetailedFields::ZoneName, false, true).value_or("").empty());
  }
}

TEST_F(EPModelFixture, API_Space_ThermalZoneAndThermostatStorage_Reload) {
  Model model;
  const std::vector<openstudio::Point3d> floorPrint{{0.0, 0.0, 0.0}, {0.0, 10.0, 0.0}, {10.0, 10.0, 0.0}, {10.0, 0.0, 0.0}};
  auto space = Space::fromFloorPrint(floorPrint, 3.0, model, "Reload Space");
  ASSERT_TRUE(space);
  ThermalZone zone(model);
  ASSERT_TRUE(zone.setName("Reload Zone"));
  ASSERT_TRUE(space->setThermalZone(zone));
  ThermostatSetpointDualSetpoint thermostat(model);
  ASSERT_TRUE(thermostat.setName("Reload Thermostat"));
  ASSERT_TRUE(zone.setThermostatSetpointDualSetpoint(thermostat));

  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-space-zone-thermostat-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);

  const auto loadedSpaces = loadedModel->getConcreteModelObjects<Space>();
  const auto loadedZones = loadedModel->getConcreteModelObjects<ThermalZone>();
  ASSERT_EQ(1u, loadedSpaces.size());
  ASSERT_EQ(1u, loadedZones.size());
  for (const auto& surface : loadedSpaces.front().surfaces()) {
    const auto loadedSpaceTarget = surface.getTarget(openstudio::BuildingSurface_DetailedFields::SpaceName);
    const auto loadedZoneTarget = surface.getTarget(openstudio::BuildingSurface_DetailedFields::ZoneName);
    ASSERT_TRUE(loadedSpaceTarget);
    ASSERT_TRUE(loadedZoneTarget);
    EXPECT_EQ(loadedSpaces.front().handle(), loadedSpaceTarget->handle());
    EXPECT_EQ(loadedZones.front().handle(), loadedZoneTarget->handle());
  }

  const auto zoneControls = loadedModel->getObjectsByType(openstudio::IddObjectType::ZoneControl_Thermostat);
  ASSERT_EQ(1u, zoneControls.size());
  EXPECT_TRUE(zoneControls.front().getTarget(openstudio::ZoneControl_ThermostatFields::ControlTypeScheduleName));
  EXPECT_TRUE(zoneControls.front().getTarget(openstudio::ZoneControl_ThermostatFields::Control1Name));
  openstudio::filesystem::remove(idfPath);
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

TEST_F(EPModelFixture, API_Space_Canonicalize_MigratesZonedSpaceAssignmentFromOrphanToZoneList) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));
  DesignSpecificationOutdoorAir dsoa(model);

  auto orphanList = model.getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Orphan Spaces DSOA Space List");
  if (!orphanList) {
    orphanList = DesignSpecificationOutdoorAirSpaceList(model);
    orphanList->setName("Orphan Spaces DSOA Space List");
  }
  ASSERT_TRUE(orphanList->getImpl<detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(space, dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto zoneList = zone.sizingZone().getModelObjectTarget<DesignSpecificationOutdoorAirSpaceList>(
    openstudio::Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName);
  ASSERT_TRUE(zoneList);
  auto zoneAssignment = zoneList->designSpecificationOutdoorAir(space);
  ASSERT_TRUE(zoneAssignment);
  EXPECT_EQ(dsoa, *zoneAssignment);

  auto orphanAssignment = orphanList->designSpecificationOutdoorAir(space);
  EXPECT_FALSE(orphanAssignment);
}

TEST_F(EPModelFixture, API_Space_Canonicalize_MigratesUnzonedSpaceAssignmentFromZoneListToOrphan) {
  Model model;
  ThermalZone zone(model);
  Space unzonedSpace(model);
  DesignSpecificationOutdoorAir dsoa(model);

  DesignSpecificationOutdoorAirSpaceList zoneList(model);
  zoneList.setName("Temporary Zone DSOA Space List");
  auto sizingZoneImpl = zone.sizingZone().getImpl<detail::SizingZone_Impl>();
  ASSERT_TRUE(sizingZoneImpl);
  ASSERT_TRUE(sizingZoneImpl->setDesignSpecificationOutdoorAirSpaceList(zoneList));
  ASSERT_TRUE(zoneList.getImpl<detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(unzonedSpace, dsoa));

  model.canonicalize(SanitizationPolicy::Repair);

  auto zoneAssignment = zoneList.designSpecificationOutdoorAir(unzonedSpace);
  EXPECT_FALSE(zoneAssignment);

  auto orphanList = model.getConcreteModelObjectByName<DesignSpecificationOutdoorAirSpaceList>("Orphan Spaces DSOA Space List");
  ASSERT_TRUE(orphanList);
  auto orphanAssignment = orphanList->designSpecificationOutdoorAir(unzonedSpace);
  ASSERT_TRUE(orphanAssignment);
  EXPECT_EQ(dsoa, *orphanAssignment);
}
