/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/ZoneHVACCoolingPanelRadiantConvectiveWater.hpp"
#include "../../model/ZoneHVACCoolingPanelRadiantConvectiveWater_Impl.hpp"
#include "../../model/CoilCoolingWaterPanelRadiant.hpp"
#include "../../model/CoilCoolingWaterPanelRadiant_Impl.hpp"

#include "../../model/Model.hpp"
#include "../../model/HVACComponent.hpp"
#include "../../model/PlantLoop.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/Space.hpp"
#include "../../model/Surface.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/ScheduleConstant.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/geometry/Point3d.hpp"

#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>
#include <utilities/idd/BuildingSurface_Detailed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ZoneHVACCoolingPanelRadiantConvectiveWater) {
  //make the example model
  Model m = model::exampleModel();

  ZoneHVACCoolingPanelRadiantConvectiveWater panel(m);
  auto coil = panel.coolingCoil().cast<CoilCoolingWaterPanelRadiant>();

  PlantLoop p(m);
  EXPECT_TRUE(p.addDemandBranchForComponent(coil));

  Point3dVector floorPrint{
    {0, 10, 0},
    {10, 10, 0},
    {10, 0, 0},
    {0, 0, 0},
  };
  boost::optional<Space> space1 = Space::fromFloorPrint(floorPrint, 3, m);
  ASSERT_TRUE(space1);
  auto surfaces = space1->surfaces();
  EXPECT_EQ(6u, surfaces.size());

  // Space needs to be in a ThermalZone or it's not translated
  ThermalZone z(m);
  EXPECT_TRUE(space1->setThermalZone(z));

  EXPECT_TRUE(panel.addToThermalZone(z));

  // Some tweaks to disambiguate the ft tests later
  panel.setName("My Panel");
  EXPECT_TRUE(panel.setFractionRadiant(0.4));
  EXPECT_TRUE(panel.setFractionofRadiantEnergyIncidentonPeople(0.3));
  EXPECT_TRUE(panel.setFractionofRadiantEnergytoFloorSurfaces(0.43));
  EXPECT_TRUE(panel.setFractionofRadiantEnergytoWallSurfaces(0.53));
  EXPECT_TRUE(panel.setFractionofRadiantEnergytoCeilingSurfaces(0.63));
  EXPECT_TRUE(coil.setRatedInletWaterTemperature(1.0));
  EXPECT_TRUE(coil.setRatedInletSpaceTemperature(2.0));
  EXPECT_TRUE(coil.setRatedWaterMassFlowRate(3.0));
  EXPECT_TRUE(coil.setCoolingDesignCapacityMethod("FractionOfAutosizedCoolingCapacity"));
  EXPECT_TRUE(coil.setCoolingDesignCapacity(0));
  EXPECT_TRUE(coil.setCoolingDesignCapacityPerFloorArea(0));
  EXPECT_TRUE(coil.setFractionofAutosizedCoolingDesignCapacity(4.0));
  EXPECT_TRUE(coil.setMaximumChilledWaterFlowRate(5.0));
  EXPECT_TRUE(coil.setControlType("OutdoorDryBulbTemperature"));
  EXPECT_TRUE(coil.setCoolingControlThrottlingRange(6.0));
  ScheduleConstant coolingControlTemperatureSchedule(m);
  EXPECT_TRUE(coil.setCoolingControlTemperatureSchedule(coolingControlTemperatureSchedule));
  EXPECT_TRUE(coil.setCondensationControlType("SimpleOff"));
  EXPECT_TRUE(coil.setCondensationControlDewpointOffset(7.0));

  // Translate
  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfPanels = w.getObjectsByType(IddObjectType::ZoneHVAC_CoolingPanel_RadiantConvective_Water);
  ASSERT_EQ(1u, idfPanels.size());
  WorkspaceObject idfPanel(idfPanels[0]);

  // Name
  EXPECT_EQ(panel.nameString(), idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::Name).get());
  // Availability Schedule Name
  EXPECT_EQ(panel.availabilitySchedule().nameString(),
            idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::AvailabilityScheduleName).get());
  // Water Inlet Node Name
  EXPECT_FALSE(idfPanel.isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterInletNodeName));
  // Water Outlet Node Name
  EXPECT_FALSE(idfPanel.isEmpty(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::WaterOutletNodeName));
  // Rated Inlet Water Temperature
  EXPECT_EQ(1.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletWaterTemperature).get());
  // Rated Inlet Space Temperature
  EXPECT_EQ(2.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedInletSpaceTemperature).get());
  // Rated Water Mass Flow Rate
  EXPECT_EQ(3.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate).get());
  // Cooling Design Capacity Method
  EXPECT_EQ("FractionOfAutosizedCoolingCapacity",
            idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityMethod).get());
  // Cooling Design Capacity
  EXPECT_EQ(0.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacity).get());
  // Cooling Design Capacity Per Floor Area
  EXPECT_EQ(0.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingDesignCapacityPerFloorArea).get());
  // Fraction of Autosized Cooling Design Capacity
  EXPECT_EQ(4.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofAutosizedCoolingDesignCapacity).get());
  // Maximum Chilled Water Flow Rate
  EXPECT_EQ(5.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumChilledWaterFlowRate).get());
  // Control Type
  EXPECT_EQ("OutdoorDryBulbTemperature", idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::ControlType).get());
  // Cooling Control Throttling Range
  EXPECT_EQ(6.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlThrottlingRange).get());
  // Cooling Control Temperature Schedule Name
  EXPECT_EQ(coolingControlTemperatureSchedule.nameString(),
            idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CoolingControlTemperatureScheduleName).get());
  // Condensation Control Type
  EXPECT_EQ("SimpleOff", idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlType).get());
  // Condensation Control Dewpoint Offset
  EXPECT_EQ(7.0, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::CondensationControlDewpointOffset).get());
  // Fraction Radiant
  EXPECT_EQ(0.4, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionRadiant).get());
  // Fraction of Radiant Energy Incident on People
  EXPECT_EQ(0.3, idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::FractionofRadiantEnergyIncidentonPeople).get());

  double totalAreaOfWallSurfaces = 4 * 10.0 * 10.0;
  double totalAreaOfCeilingSurfaces = 1 * 10.0 * 10.0;
  double totalAreaOfFloorSurfaces = 1 * 10.0 * 10.0;

  double fractionOnFloor = (1.0 - 0.3) * 0.43;
  double fractionOnWall = (1.0 - 0.3) * 0.53;
  double fractionOnCeiling = (1.0 - 0.3) * 0.63;

  // Surface 1 Name
  // Fraction of Radiant Energy to Surface 1
  EXPECT_EQ(surfaces.size(), idfPanel.numExtensibleGroups());
  for (const auto& idf_eg : idfPanel.extensibleGroups()) {
    auto idfSurf = idf_eg.getTarget(ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::SurfaceName).get();
    std::string surfaceType = idfSurf.getString(BuildingSurface_DetailedFields::SurfaceType).get();
    double fractionofRadiantEnergytoSurface =
      idf_eg.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterExtensibleFields::FractionofRadiantEnergytoSurface).get();
    if (istringEqual(surfaceType, "Floor")) {
      EXPECT_EQ(100.0 / totalAreaOfFloorSurfaces * fractionOnFloor, fractionofRadiantEnergytoSurface);
    } else if (istringEqual(surfaceType, "Roof") || istringEqual(surfaceType, "Ceiling")) {
      EXPECT_EQ(100.0 / totalAreaOfCeilingSurfaces * fractionOnCeiling, fractionofRadiantEnergytoSurface);
    } else {
      EXPECT_EQ(100.0 / totalAreaOfWallSurfaces * fractionOnWall, fractionofRadiantEnergytoSurface);
    }
  }
}
