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
#include "../../utilities/geometry/Point3d.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
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
  auto surfaces = space1->surfaces();
  EXPECT_EQ(6u, surfaces.size());

  // Space needs to be in a ThermalZone or it's not translated
  ThermalZone z(m);
  EXPECT_TRUE(space1->setThermalZone(z));

  EXPECT_TRUE(baseboard.addToThermalZone(z));

  // Some tweaks to disambiguate the ft tests later
  baseboard.setName("My Baseboard");
  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(0.0));
  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(100.0));
  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0.0));
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
  // Inlet Node Name
  EXPECT_FALSE(idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::InletNodeName).get().empty());
  // Outlet Node Name
  EXPECT_FALSE(idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::OutletNodeName).get().empty());
  // Rated Average Water Temperature
  EXPECT_EQ(coil.ratedAverageWaterTemperature(),
            idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::RatedAverageWaterTemperature).get());
  // Rated Water Mass Flow Rate
  EXPECT_EQ(coil.ratedWaterMassFlowRate(), idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::RatedWaterMassFlowRate).get());
  // Heating Design Capacity
  EXPECT_TRUE(
    openstudio::istringEqual("autosize", idfBaseboard.getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity).get()));
  // Maximum Water Flow Rate
  EXPECT_EQ(coil.maximumWaterFlowRate().get(),
            idfBaseboard.getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::MaximumWaterFlowRate).get());

  // Surface 1 Name
  // Fraction of Radiant Energy to Surface 1
  EXPECT_EQ(surfaces.size(), idfBaseboard.numExtensibleGroups());
}
