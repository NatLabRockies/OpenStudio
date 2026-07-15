/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/HVACComponent.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../PlanarSurface/Surface.hpp"
#include "../PlanarSurfaceGroup/Space.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/CoilCoolingWaterPanelRadiant.hpp"
#include "../StraightComponent/CoilCoolingWaterPanelRadiant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"

#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);

  EXPECT_EQ(ZoneHVACCoolingPanelRadiantConvectiveWater::iddObjectType(), panel.iddObject().type());
  EXPECT_FALSE(panel.nameString().empty());
  EXPECT_EQ(0u, panel.inletPort());
  EXPECT_EQ(0u, panel.outletPort());
  EXPECT_DOUBLE_EQ(0.65, panel.fractionRadiant());
  EXPECT_DOUBLE_EQ(0.2, panel.fractionofRadiantEnergyIncidentonPeople());
  ASSERT_EQ(1u, panel.children().size());

  auto coil = panel.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
  EXPECT_DOUBLE_EQ(5.0, coil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(24.0, coil.ratedInletSpaceTemperature());
  EXPECT_DOUBLE_EQ(0.063, coil.ratedWaterMassFlowRate());
  EXPECT_EQ("CoolingDesignCapacity", coil.coolingDesignCapacityMethod());
  EXPECT_TRUE(coil.isCoolingDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.0, coil.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(1.0, coil.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_TRUE(coil.isMaximumChilledWaterFlowRateAutosized());
  EXPECT_EQ("MeanAirTemperature", coil.controlType());
  EXPECT_DOUBLE_EQ(0.5, coil.coolingControlThrottlingRange());
  EXPECT_EQ("SimpleOff", coil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.0, coil.condensationControlDewpointOffset());
}

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_ParentCoolingCoilSetterCopiesCanonicalChildState) {
  Model model;

  ZoneHVACCoolingPanelRadiantConvectiveWater source(model);
  auto sourceCoil = source.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();

  ScheduleConstant controlSchedule(model);
  ASSERT_TRUE(controlSchedule.setValue(18.0));

  Node inlet = model.getOrCreateTransientByName<Node>("Cooling Panel Inlet");
  Node outlet = model.getOrCreateTransientByName<Node>("Cooling Panel Outlet");
  ASSERT_TRUE(source.setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName, inlet.handle()));
  ASSERT_TRUE(source.setPointer(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName, outlet.handle()));

  ASSERT_TRUE(sourceCoil.setRatedInletWaterTemperature(7.5));
  ASSERT_TRUE(sourceCoil.setRatedInletSpaceTemperature(22.5));
  ASSERT_TRUE(sourceCoil.setRatedWaterMassFlowRate(0.075));
  ASSERT_TRUE(sourceCoil.setCoolingDesignCapacityMethod("CapacityPerFloorArea"));
  ASSERT_TRUE(sourceCoil.setCoolingDesignCapacityPerFloorArea(12.0));
  ASSERT_TRUE(sourceCoil.setFractionofAutosizedCoolingDesignCapacity(0.8));
  ASSERT_TRUE(sourceCoil.setMaximumChilledWaterFlowRate(0.08));
  ASSERT_TRUE(sourceCoil.setControlType("OutdoorDryBulbTemperature"));
  ASSERT_TRUE(sourceCoil.setCoolingControlThrottlingRange(0.75));
  ASSERT_TRUE(sourceCoil.setCoolingControlTemperatureSchedule(controlSchedule));
  ASSERT_TRUE(sourceCoil.setCondensationControlType("VariableOff"));
  ASSERT_TRUE(sourceCoil.setCondensationControlDewpointOffset(1.5));

  ZoneHVACCoolingPanelRadiantConvectiveWater target(model);
  HVACComponent sourceCoilComponent = sourceCoil;
  EXPECT_TRUE(target.setCoolingCoil(sourceCoilComponent));

  auto targetCoil = target.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();
  EXPECT_DOUBLE_EQ(7.5, targetCoil.ratedInletWaterTemperature());
  EXPECT_DOUBLE_EQ(22.5, targetCoil.ratedInletSpaceTemperature());
  EXPECT_DOUBLE_EQ(0.075, targetCoil.ratedWaterMassFlowRate());
  EXPECT_EQ("CapacityPerFloorArea", targetCoil.coolingDesignCapacityMethod());
  EXPECT_DOUBLE_EQ(12.0, targetCoil.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(0.8, targetCoil.fractionofAutosizedCoolingDesignCapacity());
  ASSERT_TRUE(targetCoil.maximumChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.08, *targetCoil.maximumChilledWaterFlowRate());
  EXPECT_EQ("OutdoorDryBulbTemperature", targetCoil.controlType());
  EXPECT_DOUBLE_EQ(0.75, targetCoil.coolingControlThrottlingRange());
  ASSERT_TRUE(targetCoil.coolingControlTemperatureSchedule());
  EXPECT_EQ(controlSchedule.handle(), targetCoil.coolingControlTemperatureSchedule()->handle());
  EXPECT_EQ("VariableOff", targetCoil.condensationControlType());
  EXPECT_DOUBLE_EQ(1.5, targetCoil.condensationControlDewpointOffset());
  ASSERT_TRUE(targetCoil.inletModelObject());
  EXPECT_EQ(inlet.handle(), targetCoil.inletModelObject()->handle());
  ASSERT_TRUE(targetCoil.outletModelObject());
  EXPECT_EQ(outlet.handle(), targetCoil.outletModelObject()->handle());
}

TEST_F(EPModelFixture, ZoneHVACCoolingPanelRadiantConvectiveWater_ZoneAttachmentRewritesPersistedSurfaceFractions) {
  Model model;
  ThermalZone zone(model);
  Space space(model);
  ASSERT_TRUE(space.setThermalZone(zone));

  // The envelope side of epmodel is still fairly thin, so this test sets up
  // the parent/space/surface relationships directly at the field level for
  // now. Once richer surface wrappers mature, this should move up to those
  // higher-level APIs.
  Surface floor(model);
  floor.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle());
  floor.setString(openstudio::BuildingSurface_DetailedFields::SurfaceType, "Floor");
  floor.setName("Cooling Panel Floor");
  floor.clearExtensibleGroups();
  {
    auto g = floor.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }
  {
    auto g = floor.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }
  {
    auto g = floor.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }
  {
    auto g = floor.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }

  Surface wall(model);
  wall.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle());
  wall.setString(openstudio::BuildingSurface_DetailedFields::SurfaceType, "Wall");
  wall.setName("Cooling Panel Wall");
  wall.clearExtensibleGroups();
  {
    auto g = wall.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }
  {
    auto g = wall.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 0.0);
  }
  {
    auto g = wall.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }
  {
    auto g = wall.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }

  Surface ceiling(model);
  ceiling.setPointer(openstudio::BuildingSurface_DetailedFields::SpaceName, space.handle());
  ceiling.setString(openstudio::BuildingSurface_DetailedFields::SurfaceType, "Ceiling");
  ceiling.setName("Cooling Panel Ceiling");
  ceiling.clearExtensibleGroups();
  {
    auto g = ceiling.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }
  {
    auto g = ceiling.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }
  {
    auto g = ceiling.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }
  {
    auto g = ceiling.pushExtensibleGroup();
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexXcoordinate, 0.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexYcoordinate, 2.0);
    g.setDouble(openstudio::BuildingSurface_DetailedExtensibleFields::VertexZcoordinate, 2.0);
  }

  ZoneHVACCoolingPanelRadiantConvectiveWater panel(model);
  ASSERT_TRUE(panel.setFractionofRadiantEnergyIncidentonPeople(0.25));
  ASSERT_TRUE(panel.addToThermalZone(zone));

  const auto groups = panel.extensibleGroups();
  ASSERT_EQ(3u, groups.size());

  double totalFraction = 0.0;
  for (const auto& group : groups) {
    auto workspaceGroup = group.cast<openstudio::WorkspaceExtensibleGroup>();
    auto target = workspaceGroup.getTarget(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::SurfaceName);
    ASSERT_TRUE(target);
    auto fraction =
      group.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::FractionofRadiantEnergytoSurface, true);
    ASSERT_TRUE(fraction);
    totalFraction += *fraction;
  }
  EXPECT_NEAR(0.75, totalFraction, 1e-9);

  ASSERT_TRUE(panel.setFractionofRadiantEnergyIncidentonPeople(0.1));
  double updatedTotalFraction = 0.0;
  for (const auto& group : panel.extensibleGroups()) {
    auto fraction =
      group.getDouble(openstudio::ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::FractionofRadiantEnergytoSurface, true);
    ASSERT_TRUE(fraction);
    updatedTotalFraction += *fraction;
  }
  EXPECT_NEAR(0.9, updatedTotalFraction, 1e-9);

  panel.removeFromThermalZone();
  EXPECT_FALSE(panel.thermalZone());
  EXPECT_TRUE(panel.extensibleGroups().empty());
}
