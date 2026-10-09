/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/Building.hpp"
#include "../../model/Building_Impl.hpp"
#include "../../model/DefaultConstructionSet.hpp"
#include "../../model/DefaultConstructionSet_Impl.hpp"
#include "../../model/DefaultSurfaceConstructions.hpp"
#include "../../model/DefaultSubSurfaceConstructions.hpp"
#include "../../model/Construction.hpp"
#include "../../model/Space.hpp"
#include "../../model/Space_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/StandardOpaqueMaterial.hpp"
#include "../../model/StandardOpaqueMaterial_Impl.hpp"

#include "../../utilities/geometry/Point3d.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ConstructionAssignmentSet_FieldEnums.hxx>
#include <utilities/idd/Building_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_DefaultConstructionSet_Building) {

  ForwardTranslator ft;

  Model m;

  DefaultConstructionSet defaultConstructionSet(m);

  defaultConstructionSet.setName("Building Default Construction Set");
  Building building = m.getUniqueModelObject<Building>();
  EXPECT_TRUE(building.setDefaultConstructionSet(defaultConstructionSet));

  DefaultSurfaceConstructions exteriorSurfaceConstructionAssignments(m);
  exteriorSurfaceConstructionAssignments.setName("Exterior Surface Constructions");
  EXPECT_TRUE(defaultConstructionSet.setDefaultExteriorSurfaceConstructions(exteriorSurfaceConstructionAssignments));

  DefaultSurfaceConstructions interiorSurfaceConstructionAssignments(m);
  interiorSurfaceConstructionAssignments.setName("Interior Surface Constructions");
  EXPECT_TRUE(defaultConstructionSet.setDefaultInteriorSurfaceConstructions(interiorSurfaceConstructionAssignments));

  DefaultSurfaceConstructions groundContactSurfaceConstructionAssignments(m);
  groundContactSurfaceConstructionAssignments.setName("Ground Contact Surface Constructions");
  EXPECT_TRUE(defaultConstructionSet.setDefaultGroundContactSurfaceConstructions(groundContactSurfaceConstructionAssignments));

  DefaultSubSurfaceConstructions exteriorSubSurfaceConstructionAssignments(m);
  exteriorSubSurfaceConstructionAssignments.setName("Exterior SubSurface Constructions");
  EXPECT_TRUE(defaultConstructionSet.setDefaultExteriorSubSurfaceConstructions(exteriorSubSurfaceConstructionAssignments));

  DefaultSubSurfaceConstructions interiorSubSurfaceConstructionAssignments(m);
  interiorSubSurfaceConstructionAssignments.setName("Interior SubSurface Constructions");
  EXPECT_TRUE(defaultConstructionSet.setDefaultInteriorSubSurfaceConstructions(interiorSubSurfaceConstructionAssignments));

  Construction interiorPartitionConstruction(m);
  interiorPartitionConstruction.setName("Interior Partition Construction");
  EXPECT_TRUE(defaultConstructionSet.setInteriorPartitionConstruction(interiorPartitionConstruction));

  Construction adiabaticSurfaceConstruction(m);
  adiabaticSurfaceConstruction.setName("Adiabatic Surface Construction");
  EXPECT_TRUE(defaultConstructionSet.setAdiabaticSurfaceConstruction(adiabaticSurfaceConstruction));

  const Workspace w = ft.translateModel(m);

  const auto buildingObjs = w.getObjectsByType(IddObjectType::Building);
  ASSERT_EQ(1, buildingObjs.size());
  EXPECT_EQ(1, w.getObjectsByType(IddObjectType::ConstructionAssignmentSet).size());

  const auto& buildingObj = buildingObjs.front();
  ASSERT_TRUE(buildingObj.getTarget(BuildingFields::ConstructionAssignmentSetName));
  WorkspaceObject idfObject = buildingObj.getTarget(BuildingFields::ConstructionAssignmentSetName).get();

  EXPECT_EQ(defaultConstructionSet.nameString(), idfObject.nameString());
  EXPECT_EQ(exteriorSurfaceConstructionAssignments.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::ExteriorSurfaceConstructionAssignmentsName).get());
  EXPECT_EQ(interiorSurfaceConstructionAssignments.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::InteriorSurfaceConstructionAssignmentsName).get());
  EXPECT_EQ(groundContactSurfaceConstructionAssignments.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::GroundContactSurfaceConstructionAssignmentsName).get());
  EXPECT_EQ(exteriorSubSurfaceConstructionAssignments.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::ExteriorSubSurfaceConstructionAssignmentsName).get());
  EXPECT_EQ(interiorSubSurfaceConstructionAssignments.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::InteriorSubSurfaceConstructionAssignmentsName).get());
  EXPECT_EQ(interiorPartitionConstruction.nameString(),
            idfObject.getString(ConstructionAssignmentSetFields::InteriorPartitionConstructionName).get());
  EXPECT_EQ(adiabaticSurfaceConstruction.nameString(), idfObject.getString(ConstructionAssignmentSetFields::AdiabaticSurfaceConstructionName).get());
}
