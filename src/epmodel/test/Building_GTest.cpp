/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/Building.hpp"
#include "../ParentObject/Building_Impl.hpp"
#include "../scaffolds/GlobalGeometryRules.hpp"
#include "../scaffolds/GlobalGeometryRules_Impl.hpp"

#include <utilities/core/Filesystem.hpp>

#include <set>

using namespace openstudio::epmodel;

namespace {

GlobalGeometryRules makeCompleteGeometryRules(Model& model) {
  GlobalGeometryRules result(model);
  EXPECT_TRUE(result.setStartingVertexPosition("UpperLeftCorner"));
  EXPECT_TRUE(result.setVertexEntryDirection("Counterclockwise"));
  EXPECT_TRUE(result.setCoordinateSystem("Relative"));
  return result;
}

}  // namespace

TEST_F(EPModelFixture, Building_DefaultConstructor) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();
  EXPECT_EQ(Building::iddObjectType(), building.iddObject().type());
}

TEST_F(EPModelFixture, Building_ScalarAccessors_RoundTrip) {
  Model model;
  auto building = model.getUniqueModelObject<Building>();

  EXPECT_TRUE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, building.northAxis());

  EXPECT_TRUE(building.setNorthAxis(45.0));
  EXPECT_FALSE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(45.0, building.northAxis());

  building.resetNorthAxis();
  EXPECT_TRUE(building.isNorthAxisDefaulted());
  EXPECT_DOUBLE_EQ(0.0, building.northAxis());
}

TEST_F(EPModelFixture, Building_CanonicalizeRequiredSingleton) {
  Model model;
  const auto geometryRules = makeCompleteGeometryRules(model);
  EXPECT_TRUE(model.getObjectsByType(Building::iddObjectType()).empty());

  const auto audit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, audit.warningCount);
  EXPECT_TRUE(model.getObjectsByType(Building::iddObjectType()).empty());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, repair.warningCount);
  auto buildings = model.getConcreteModelObjects<Building>();
  ASSERT_EQ(1u, buildings.size());
  const auto buildingHandle = buildings.front().handle();
  EXPECT_DOUBLE_EQ(0.0, buildings.front().northAxis());

  const auto secondRepair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(1u, secondRepair.infoCount);
  buildings = model.getConcreteModelObjects<Building>();
  ASSERT_EQ(1u, buildings.size());
  EXPECT_EQ(buildingHandle, buildings.front().handle());

  ASSERT_FALSE(buildings.front().remove().empty());
  EXPECT_TRUE(model.getObjectsByType(Building::iddObjectType()).empty());

  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-building-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<Building>().size());
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<GlobalGeometryRules>().size());
  openstudio::filesystem::remove(idfPath);

  model.canonicalize(SanitizationPolicy::Repair);
  buildings = model.getConcreteModelObjects<Building>();
  ASSERT_EQ(1u, buildings.size());
}

TEST_F(EPModelFixture, Building_CanonicalizePreservesDuplicates) {
  Model model;
  const auto geometryRules = makeCompleteGeometryRules(model);
  auto first = model.getUniqueModelObject<Building>();
  EXPECT_TRUE(first.setName("First Building"));

  openstudio::IdfObject secondObject(openstudio::IddObjectType::Building);
  ASSERT_TRUE(secondObject.setName("Second Building"));
  auto added = model.addObject(secondObject);
  ASSERT_TRUE(added);
  const std::set<openstudio::Handle> originalHandles{first.handle(), added->handle()};

  const auto audit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, audit.warningCount);
  EXPECT_EQ(2u, model.getObjectsByType(Building::iddObjectType()).size());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(1u, repair.warningCount);
  const auto preserved = model.getConcreteModelObjects<Building>();
  ASSERT_EQ(2u, preserved.size());
  std::set<openstudio::Handle> preservedHandles;
  for (const auto& object : preserved) {
    preservedHandles.insert(object.handle());
  }
  EXPECT_EQ(originalHandles, preservedHandles);
}
