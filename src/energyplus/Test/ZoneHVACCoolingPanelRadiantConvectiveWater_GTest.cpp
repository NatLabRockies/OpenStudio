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
#include "../../utilities/geometry/Point3d.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/geometry/Point3d.hpp"

#include <utilities/idd/ZoneHVAC_CoolingPanel_RadiantConvective_Water_FieldEnums.hxx>
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
  EXPECT_TRUE(coil.setMaximumChilledWaterFlowRate(1.0));

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
  // Inlet Node Name
  EXPECT_FALSE(idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::InletNodeName).get().empty());
  // Outlet Node Name
  EXPECT_FALSE(idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::OutletNodeName).get().empty());
  // Rated Average Water Temperature
  EXPECT_EQ(coil.ratedAverageWaterTemperature(),
            idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedAverageWaterTemperature).get());
  // Rated Water Mass Flow Rate
  EXPECT_EQ(coil.ratedWaterMassFlowRate(), idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::RatedWaterMassFlowRate).get());
  // Heating Design Capacity
  EXPECT_TRUE(
    openstudio::istringEqual("autosize", idfPanel.getString(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::HeatingDesignCapacity).get()));
  // Maximum Water Flow Rate
  EXPECT_EQ(coil.maximumWaterFlowRate().get(), idfPanel.getDouble(ZoneHVAC_CoolingPanel_RadiantConvective_WaterFields::MaximumWaterFlowRate).get());

  // Surface 1 Name
  // Fraction of Radiant Energy to Surface 1
  EXPECT_EQ(surfaces.size(), idfPanel.numExtensibleGroups());
}
