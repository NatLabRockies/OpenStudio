/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idf/IdfExtensibleGroup.hpp>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../LayeredConstruction/ConstructionWithInternalSource.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ModelObject/ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTemperatureRadiantElectric.hpp"

#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ConstructionProperty_InternalHeatSource_FieldEnums.hxx>

#include <array>
#include <algorithm>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant heatingSetpoint(model);

  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatingSetpoint.setValue(22.0));

  ZoneHVACLowTemperatureRadiantElectric radiant(model, availability, heatingSetpoint);

  EXPECT_EQ(availability.handle(), radiant.availabilitySchedule().handle());
  EXPECT_EQ(heatingSetpoint.handle(), radiant.heatingSetpointTemperatureSchedule().handle());
  EXPECT_FALSE(radiant.radiantSurfaceType());
  EXPECT_TRUE(radiant.surfaces().empty());
  EXPECT_FALSE(radiant.surfaceGroup());
  EXPECT_FALSE(radiant.maximumElectricalPowertoPanel());
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelAutosized());
  EXPECT_FALSE(radiant.autosizedMaximumElectricalPowertoPanel());
  EXPECT_FALSE(radiant.isTemperatureControlTypeDefaulted());
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());
  EXPECT_FALSE(radiant.isHeatingThrottlingRangeDefaulted());
  EXPECT_EQ(0u, radiant.inletPort());
  EXPECT_EQ(0u, radiant.outletPort());

  ScheduleConstant updatedAvailability(model);
  ScheduleConstant updatedHeatingSetpoint(model);
  ASSERT_TRUE(updatedAvailability.setValue(1.0));
  ASSERT_TRUE(updatedHeatingSetpoint.setValue(23.0));

  EXPECT_TRUE(radiant.setAvailabilitySchedule(updatedAvailability));
  EXPECT_EQ(updatedAvailability.handle(), radiant.availabilitySchedule().handle());
  EXPECT_TRUE(radiant.setHeatingSetpointTemperatureSchedule(updatedHeatingSetpoint));
  EXPECT_EQ(updatedHeatingSetpoint.handle(), radiant.heatingSetpointTemperatureSchedule().handle());

  EXPECT_TRUE(radiant.setMaximumElectricalPowertoPanel(150.0));
  ASSERT_TRUE(radiant.maximumElectricalPowertoPanel());
  EXPECT_DOUBLE_EQ(150.0, radiant.maximumElectricalPowertoPanel().get());
  radiant.autosizeMaximumElectricalPowertoPanel();
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelAutosized());
  radiant.resetMaximumElectricalPowertoPanel();
  EXPECT_TRUE(radiant.isMaximumElectricalPowertoPanelDefaulted());

  auto temperatureControlTypes = ZoneHVACLowTemperatureRadiantElectric::temperatureControlTypeValues();
  ASSERT_FALSE(temperatureControlTypes.empty());
  EXPECT_TRUE(radiant.setTemperatureControlType(temperatureControlTypes.front()));
  EXPECT_EQ(temperatureControlTypes.front(), radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setSetpointControlType("ZeroFlowPower"));
  EXPECT_EQ("ZeroFlowPower", radiant.setpointControlType());
  EXPECT_FALSE(radiant.isSetpointControlTypeDefaulted());
  radiant.resetSetpointControlType();
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());

  EXPECT_TRUE(radiant.setHeatingThrottlingRange(2.5));
  EXPECT_DOUBLE_EQ(2.5, radiant.heatingThrottlingRange());
  radiant.resetHeatingThrottlingRange();
  EXPECT_TRUE(radiant.isHeatingThrottlingRangeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_ConvenienceConstructorAndRadiantSurfaceType) {
  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant heatingSetpoint(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatingSetpoint.setValue(21.0));

  ZoneHVACLowTemperatureRadiantElectric radiant(model, availability, heatingSetpoint);
  EXPECT_EQ(availability.handle(), radiant.availabilitySchedule().handle());
  EXPECT_EQ(heatingSetpoint.handle(), radiant.heatingSetpointTemperatureSchedule().handle());
  EXPECT_EQ(std::vector<std::string>({"Ceilings", "Floors", "CeilingsandFloors", "AllSurfaces"}),
            ZoneHVACLowTemperatureRadiantElectric::radiantSurfaceTypeValues());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_RadiantSurfaceType_RewritesPersistedSurfaceGroup) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  ModelObject construction = ModelObject::create(IddObjectType::Construction, model);
  ConstructionWithInternalSource radiantConstruction(model);
  ASSERT_TRUE(radiantConstruction.setPointer(openstudio::ConstructionProperty_InternalHeatSourceFields::ConstructionName, construction.handle()));

  auto makeSurface = [&](const std::string& name, const std::string& surfaceType, const std::vector<Point3d>& vertices) -> Surface {
    Surface surface(vertices, model);
    EXPECT_TRUE(surface.setName(name));
    EXPECT_TRUE(surface.setSurfaceType(surfaceType));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::ConstructionName, construction.handle()));
    EXPECT_TRUE(surface.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle()));
    return surface;
  };

  auto floor = makeSurface("Electric Radiant Floor", "Floor", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 3.0, 0.0}, {0.0, 3.0, 0.0}});
  auto ceiling = makeSurface("Electric Radiant Ceiling", "Roof", {{0.0, 0.0, 3.0}, {4.0, 0.0, 3.0}, {4.0, 3.0, 3.0}, {0.0, 3.0, 3.0}});
  auto wall = makeSurface("Electric Radiant Wall", "Wall", {{0.0, 0.0, 0.0}, {4.0, 0.0, 0.0}, {4.0, 0.0, 3.0}, {0.0, 0.0, 3.0}});

  auto sortedHandles = [](const std::vector<Surface>& surfaces) {
    std::vector<Handle> result;
    result.reserve(surfaces.size());
    for (const auto& surface : surfaces) {
      result.push_back(surface.handle());
    }
    std::sort(result.begin(), result.end());
    return result;
  };

  auto sortedExpected = [](std::vector<Handle> handles) {
    std::sort(handles.begin(), handles.end());
    return handles;
  };

  ScheduleConstant availability(model);
  ScheduleConstant heatingSetpoint(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatingSetpoint.setValue(21.0));

  ZoneHVACLowTemperatureRadiantElectric radiant(model, availability, heatingSetpoint);
  ASSERT_TRUE(radiant.addToThermalZone(zone));

  EXPECT_TRUE(radiant.setRadiantSurfaceType("Floors"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("Floors", *radiant.radiantSurfaceType());
  ASSERT_TRUE(radiant.surfaceGroup());
  ASSERT_EQ(1u, radiant.surfaces().size());
  EXPECT_EQ(floor.handle(), radiant.surfaces().front().handle());

  EXPECT_TRUE(radiant.setRadiantSurfaceType("CeilingsandFloors"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("CeilingsandFloors", *radiant.radiantSurfaceType());
  ASSERT_EQ(2u, radiant.surfaces().size());
  EXPECT_EQ(sortedExpected({ceiling.handle(), floor.handle()}), sortedHandles(radiant.surfaces()));

  EXPECT_TRUE(radiant.setRadiantSurfaceType("AllSurfaces"));
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("AllSurfaces", *radiant.radiantSurfaceType());
  ASSERT_EQ(3u, radiant.surfaces().size());
  EXPECT_EQ(sortedExpected({ceiling.handle(), floor.handle(), wall.handle()}), sortedHandles(radiant.surfaces()));

  auto surfaceGroupImpl = radiant.surfaceGroup()->getImpl<openstudio::epmodel::detail::ZoneHVACLowTemperatureRadiantSurfaceGroup_Impl>();
  surfaceGroupImpl->clearSurfaces();
  ASSERT_TRUE(surfaceGroupImpl->addSurface(floor, 0.5));
  ASSERT_TRUE(surfaceGroupImpl->addSurface(wall, 0.5));
  EXPECT_FALSE(radiant.radiantSurfaceType());

  radiant.resetRadiantSurfaceType();
  ASSERT_TRUE(radiant.radiantSurfaceType());
  EXPECT_EQ("Ceilings", *radiant.radiantSurfaceType());
  ASSERT_EQ(1u, radiant.surfaces().size());
  EXPECT_EQ(ceiling.handle(), radiant.surfaces().front().handle());
}

TEST_F(EPModelFixture, ZoneHVACLowTemperatureRadiantElectric_ZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ScheduleConstant availability(model);
  ScheduleConstant heatingSetpoint(model);
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(heatingSetpoint.setValue(21.0));

  ZoneHVACLowTemperatureRadiantElectric radiant(model, availability, heatingSetpoint);

  EXPECT_TRUE(radiant.addToThermalZone(zone));
  ASSERT_TRUE(radiant.thermalZone());
  EXPECT_EQ(zone, radiant.thermalZone().get());
  EXPECT_FALSE(radiant.inletNode());
  EXPECT_FALSE(radiant.outletNode());

  radiant.removeFromThermalZone();
  EXPECT_FALSE(radiant.thermalZone());
}
