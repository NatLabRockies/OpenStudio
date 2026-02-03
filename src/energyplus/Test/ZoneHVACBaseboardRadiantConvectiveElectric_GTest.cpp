/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/ZoneHVACBaseboardRadiantConvectiveElectric.hpp"
#include "../../model/ZoneHVACBaseboardRadiantConvectiveElectric_Impl.hpp"

#include "../../model/Model.hpp"
#include "../../model/HVACComponent.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/Space.hpp"
#include "../../model/Surface.hpp"
#include "../../model/Schedule.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/geometry/Point3d.hpp"

#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ZoneHVACBaseboardRadiantConvectiveElectric) {
  //make the example model
  Model m = model::exampleModel();

  ZoneHVACBaseboardRadiantConvectiveElectric baseboard(m);

  Point3dVector floorPrint{
    {0, 10, 0},
    {10, 10, 0},
    {10, 0, 0},
    {0, 0, 0},
  };
  boost::optional<Space> space1 = Space::fromFloorPrint(floorPrint, 3, m);
  ASSERT_TRUE(space1);
  auto surfs = space1->surfaces();
  EXPECT_EQ(6u, surfs.size());

  // Space needs to be in a ThermalZone or it's not translated
  ThermalZone z(m);
  EXPECT_TRUE(space1->setThermalZone(z));

  EXPECT_TRUE(baseboard.addToThermalZone(z));

  // Some tweaks to disambiguate the ft tests later
  baseboard.setName("My Baseboard");
  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(0));
  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(100.0));
  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0));
  EXPECT_TRUE(baseboard.setEfficiency(0.9));
  EXPECT_TRUE(baseboard.setFractionRadiant(0.4));
  EXPECT_TRUE(baseboard.setFractionofRadiantEnergyIncidentonPeople(0.35));
  EXPECT_TRUE(baseboard.setFractionofRadiantEnergytoFloorSurfaces(0.41));
  EXPECT_TRUE(baseboard.setFractionofRadiantEnergytoWallSurfaces(0.51));
  EXPECT_TRUE(baseboard.setFractionofRadiantEnergytoCeilingSurfaces(0.61));

  // Translate
  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfBaseboards = w.getObjectsByType(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Electric);
  ASSERT_EQ(1u, idfBaseboards.size());
  WorkspaceObject idfBaseboard(idfBaseboards[0]);

  // Name
  EXPECT_EQ(baseboard.nameString(), idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::Name).get());
  // Availability Schedule Name
  EXPECT_EQ(baseboard.availabilitySchedule().nameString(),
            idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::AvailabilityScheduleName).get());
  // Heating Design Capacity Method
  EXPECT_EQ("CapacityPerFloorArea", idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityMethod).get());
  // Heating Design Capacity
  EXPECT_EQ(0.0, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity).get());
  // Heating Design Capacity Per Floor Area
  EXPECT_EQ(100.0, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityPerFloorArea).get());
  // Fraction of Autosized Heating Design Capacity
  EXPECT_EQ(0.0, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofAutosizedHeatingDesignCapacity).get());
  // Efficiency
  EXPECT_EQ(0.9, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::Efficiency).get());
  // Fraction Radiant
  EXPECT_EQ(0.4, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionRadiant).get());
  // Fraction of Radiant Energy Incident on People
  EXPECT_EQ(0.35, idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofRadiantEnergyIncidentonPeople).get());

  auto const& surfaces = baseboard.getImpl<model::detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->surfaces();

  double totalAreaOfWallSurfaces = 0;
  double totalAreaOfCeilingSurfaces = 0;
  double totalAreaOfFloorSurfaces = 0;

  for (auto const& surface : surfaces) {
    if (istringEqual(surface.surfaceType(), "Floor")) {
      totalAreaOfFloorSurfaces += surface.grossArea();
    } else if (istringEqual(surface.surfaceType(), "RoofCeiling")) {
      totalAreaOfCeilingSurfaces += surface.grossArea();
    } else {
      totalAreaOfWallSurfaces += surface.grossArea();
    }
  }

  double fractionOnFloor = (1.0 - 0.35) * 0.41;
  double fractionOnWall = (1.0 - 0.35) * 0.51;
  double fractionOnCeiling = (1.0 - 0.35) * 0.61;

  // Surface 1 Name
  // Fraction of Radiant Energy to Surface 1
  EXPECT_EQ(surfaces.size(), idfBaseboard.numExtensibleGroups());
  for (const auto& idf_eg : idfBaseboard.extensibleGroups()) {
    const auto& surface = surfaces[idf_eg.groupIndex()];

    EXPECT_EQ(surface.nameString(), idf_eg.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricExtensibleFields::SurfaceName).get());
    if (istringEqual(surface.surfaceType(), "Floor")) {
      EXPECT_EQ(surface.grossArea() / totalAreaOfFloorSurfaces * fractionOnFloor,
                idf_eg.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricExtensibleFields::FractionofRadiantEnergytoSurface).get());
    } else if (istringEqual(surface.surfaceType(), "RoofCeiling")) {
      EXPECT_EQ(surface.grossArea() / totalAreaOfCeilingSurfaces * fractionOnCeiling,
                idf_eg.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricExtensibleFields::FractionofRadiantEnergytoSurface).get());
    } else {
      EXPECT_EQ(surface.grossArea() / totalAreaOfWallSurfaces * fractionOnWall,
                idf_eg.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricExtensibleFields::FractionofRadiantEnergytoSurface).get());
    }
  }
}
