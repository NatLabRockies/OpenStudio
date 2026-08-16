/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GlobalGeometryRules.hpp"
#include "../scaffolds/GlobalGeometryRules_Impl.hpp"
#include "../ParentObject/Building.hpp"
#include "../ParentObject/Building_Impl.hpp"
#include <utilities/core/Filesystem.hpp>

#include <set>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GlobalGeometryRules_DefaultConstructor) {
  Model model;
  GlobalGeometryRules globalGeometryRules(model);
  EXPECT_EQ(GlobalGeometryRules::iddObjectType(), globalGeometryRules.iddObject().type());
}

TEST_F(EPModelFixture, GlobalGeometryRules_ScalarAccessors_RoundTrip) {
  Model model;
  GlobalGeometryRules globalGeometryRules(model);

  EXPECT_TRUE(globalGeometryRules.setStartingVertexPosition("UpperLeftCorner"));
  EXPECT_EQ("UpperLeftCorner", globalGeometryRules.startingVertexPosition());

  EXPECT_TRUE(globalGeometryRules.setVertexEntryDirection("Counterclockwise"));
  EXPECT_EQ("Counterclockwise", globalGeometryRules.vertexEntryDirection());

  EXPECT_TRUE(globalGeometryRules.setCoordinateSystem("Relative"));
  EXPECT_EQ("Relative", globalGeometryRules.coordinateSystem());

  EXPECT_TRUE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.daylightingReferencePointCoordinateSystem());
  EXPECT_TRUE(globalGeometryRules.setDaylightingReferencePointCoordinateSystem("World"));
  EXPECT_EQ("World", globalGeometryRules.daylightingReferencePointCoordinateSystem());
  EXPECT_FALSE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  globalGeometryRules.resetDaylightingReferencePointCoordinateSystem();
  EXPECT_TRUE(globalGeometryRules.isDaylightingReferencePointCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.daylightingReferencePointCoordinateSystem());

  EXPECT_TRUE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.rectangularSurfaceCoordinateSystem());
  EXPECT_TRUE(globalGeometryRules.setRectangularSurfaceCoordinateSystem("World"));
  EXPECT_EQ("World", globalGeometryRules.rectangularSurfaceCoordinateSystem());
  EXPECT_FALSE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  globalGeometryRules.resetRectangularSurfaceCoordinateSystem();
  EXPECT_TRUE(globalGeometryRules.isRectangularSurfaceCoordinateSystemDefaulted());
  EXPECT_EQ("Relative", globalGeometryRules.rectangularSurfaceCoordinateSystem());

  const auto coordinateSystemValues = GlobalGeometryRules::coordinateSystemValues();
  EXPECT_FALSE(coordinateSystemValues.empty());
}

TEST_F(EPModelFixture, GlobalGeometryRules_CanonicalizeRequiredSingleton) {
  Model model;
  model.getUniqueModelObject<Building>();
  EXPECT_TRUE(model.getObjectsByType(GlobalGeometryRules::iddObjectType()).empty());

  const auto audit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, audit.warningCount);
  EXPECT_TRUE(model.getObjectsByType(GlobalGeometryRules::iddObjectType()).empty());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, repair.warningCount);
  EXPECT_EQ(1u, model.getObjectsByType(GlobalGeometryRules::iddObjectType()).size());

  auto geometryRulesObjects = model.getConcreteModelObjects<GlobalGeometryRules>();
  ASSERT_EQ(1u, geometryRulesObjects.size());
  auto geometryRules = geometryRulesObjects.front();
  const auto geometryRulesHandle = geometryRules.handle();
  EXPECT_EQ("UpperLeftCorner", geometryRules.startingVertexPosition());
  EXPECT_EQ("Counterclockwise", geometryRules.vertexEntryDirection());
  EXPECT_EQ("Relative", geometryRules.coordinateSystem());
  EXPECT_EQ("Relative", geometryRules.daylightingReferencePointCoordinateSystem());
  EXPECT_EQ("Relative", geometryRules.rectangularSurfaceCoordinateSystem());

  const auto secondRepair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(1u, model.getObjectsByType(GlobalGeometryRules::iddObjectType()).size());
  EXPECT_EQ(1u, secondRepair.infoCount);
  EXPECT_EQ(geometryRulesHandle, model.getConcreteModelObjects<GlobalGeometryRules>().front().handle());

  EXPECT_TRUE(geometryRules.setStartingVertexPosition("LowerLeftCorner"));
  model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ("LowerLeftCorner", geometryRules.startingVertexPosition());

  EXPECT_TRUE(geometryRules.setStartingVertexPosition(""));
  EXPECT_TRUE(geometryRules.setVertexEntryDirection(""));
  EXPECT_TRUE(geometryRules.setCoordinateSystem(""));
  const auto blankAudit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, blankAudit.warningCount);
  EXPECT_TRUE(geometryRules.startingVertexPosition().empty());
  model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ("UpperLeftCorner", geometryRules.startingVertexPosition());
  EXPECT_EQ("Counterclockwise", geometryRules.vertexEntryDirection());
  EXPECT_EQ("Relative", geometryRules.coordinateSystem());

  ASSERT_FALSE(geometryRules.remove().empty());
  const auto removedAudit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, removedAudit.warningCount);
  EXPECT_TRUE(model.getObjectsByType(GlobalGeometryRules::iddObjectType()).empty());
  model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(1u, model.getObjectsByType(GlobalGeometryRules::iddObjectType()).size());

  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-global-geometry-rules-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto loadedRules = loadedModel->getConcreteModelObjects<GlobalGeometryRules>();
  ASSERT_EQ(1u, loadedRules.size());
  EXPECT_EQ("UpperLeftCorner", loadedRules.front().startingVertexPosition());
  EXPECT_EQ("Counterclockwise", loadedRules.front().vertexEntryDirection());
  EXPECT_EQ("Relative", loadedRules.front().coordinateSystem());
  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, GlobalGeometryRules_CanonicalizePreservesDuplicates) {
  Model model;
  model.getUniqueModelObject<Building>();
  GlobalGeometryRules first(model);
  GlobalGeometryRules second(model);
  ASSERT_TRUE(first.setStartingVertexPosition("UpperLeftCorner"));
  ASSERT_TRUE(second.setStartingVertexPosition("LowerLeftCorner"));
  const std::set<openstudio::Handle> originalHandles{first.handle(), second.handle()};

  const auto audit = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(1u, audit.warningCount);
  EXPECT_EQ(2u, model.getObjectsByType(GlobalGeometryRules::iddObjectType()).size());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(1u, repair.warningCount);
  const auto preserved = model.getConcreteModelObjects<GlobalGeometryRules>();
  ASSERT_EQ(2u, preserved.size());
  std::set<openstudio::Handle> preservedHandles;
  for (const auto& object : preserved) {
    preservedHandles.insert(object.handle());
  }
  EXPECT_EQ(originalHandles, preservedHandles);
}
