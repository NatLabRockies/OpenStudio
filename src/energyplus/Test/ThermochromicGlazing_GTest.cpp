/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/ThermochromicGlazing.hpp"
#include "../../model/ThermochromicGlazing_Impl.hpp"

#include "../../model/Model.hpp"
#include "../../model/Construction.hpp"
#include "../../model/Space.hpp"
#include "../../model/StandardGlazing.hpp"
#include "../../model/StandardGlazing_Impl.hpp"
#include "../../model/Surface.hpp"
#include "../../model/SubSurface.hpp"
#include "../../model/ThermalZone.hpp"

#include "../../utilities/geometry/Point3d.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_GlazingGroup_Thermochromic_FieldEnums.hxx>
#include <utilities/idd/WindowMaterial_Glazing_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_WindowMaterialGlazingGroupThermochromic) {

  ForwardTranslator ft;

  Model m;

  ThermalZone tz(m);
  Space space(m);
  EXPECT_TRUE(space.setThermalZone(tz));

  const std::vector<Point3d> sPoints{
    {0, 2, 0},
    {0, 0, 0},
    {2, 0, 0},
    {2, 2, 0},
  };
  Surface surface(sPoints, m);
  surface.setName("Surface");
  surface.setSpace(space);

  const std::vector<Point3d> ssPoints = {
    {0, 1, 0},
    {0, 0, 0},
    {1, 0, 0},
    {1, 1, 0},
  };

  SubSurface subSurface(ssPoints, m);
  subSurface.setName("SubSurface");
  subSurface.setSurface(surface);

  Construction construction(m);
  subSurface.setConstruction(construction);

  ThermochromicGlazing thermochromicGlazing(m);
  thermochromicGlazing.setName("My WindowMaterialGlazingGroupThermochromic");

  // Not assigned to a Construction, not translated
  {
    // Assigned to a Surface
    Workspace w = ft.translateModel(m);

    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::FenestrationSurface_Detailed).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Construction).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::WindowMaterial_Glazing).size());
  }

  construction.insertLayer(0, thermochromicGlazing);

  // Assigned to a Construction, but no extensible groups, not translated
  {
    Workspace w = ft.translateModel(m);

    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::FenestrationSurface_Detailed).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Construction).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::WindowMaterial_Glazing).size());
  }

  // Create 5 groups
  for (int i = 1; i <= 5; ++i) {
    StandardGlazing standardGlazing(m);
    standardGlazing.setName("StandardGlazing" + std::to_string(i));

    double optionalDataTemperature = 10.00 * (i - 1);

    if (i % 2 == 0) {
      EXPECT_TRUE(thermochromicGlazing.addThermochromicGroup(standardGlazing, optionalDataTemperature));
    } else {
      ThermochromicGroup group(standardGlazing, optionalDataTemperature);
      EXPECT_TRUE(thermochromicGlazing.addThermochromicGroup(group));
    }
    EXPECT_EQ(i, thermochromicGlazing.numberofThermochromicGroups());
  }
  EXPECT_EQ(5, thermochromicGlazing.numberofThermochromicGroups());

  std::vector<ThermochromicGroup> groups = thermochromicGlazing.thermochromicGroups();

  {
    Workspace w = ft.translateModel(m);

    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::FenestrationSurface_Detailed).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Construction).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic).size());
    EXPECT_EQ(5, w.getObjectsByType(IddObjectType::WindowMaterial_Glazing).size());

    std::vector<WorkspaceObject> wos = w.getObjectsByType(IddObjectType::WindowMaterial_GlazingGroup_Thermochromic);
    ASSERT_EQ(1, wos.size());
    const auto& wo = wos.front();
    EXPECT_EQ(thermochromicGlazing.nameString(), wo.nameString());

    ASSERT_EQ(5, wo.numExtensibleGroups());
    for (const auto& idf_eg : wo.extensibleGroups()) {
      const auto& group = groups[idf_eg.groupIndex()];

      EXPECT_EQ(group.opticalDataTemperature(),
                idf_eg.getDouble(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::OpticalDataTemperature).get());
      EXPECT_EQ(group.standardGlazing().nameString(),
                idf_eg.getString(WindowMaterial_GlazingGroup_ThermochromicExtensibleFields::WindowMaterialGlazingName).get());
    }
  }
}
