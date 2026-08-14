/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../ModelObject/SizingPlant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

}  // namespace

TEST_F(EPModelFixture, SizingPlant_DefaultConstructor) {
  Model model;
  PlantLoop plantLoop(model);
  const auto sizingPlant = plantLoop.sizingPlant();

  EXPECT_EQ(SizingPlant::iddObjectType(), sizingPlant.iddObject().type());
  EXPECT_EQ(plantLoop, sizingPlant.plantLoop());

  EXPECT_EQ("Heating", sizingPlant.loopType());
  EXPECT_DOUBLE_EQ(82.0, sizingPlant.designLoopExitTemperature());
  EXPECT_DOUBLE_EQ(11.0, sizingPlant.loopDesignTemperatureDifference());
  EXPECT_EQ("NonCoincident", sizingPlant.sizingOption());
  EXPECT_EQ(1, sizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_EQ("None", sizingPlant.coincidentSizingFactorMode());
}

TEST_F(EPModelFixture, SizingPlant_ScalarAccessors_RoundTrip) {
  Model model;
  PlantLoop plantLoop(model);
  auto sizingPlant = plantLoop.sizingPlant();

  EXPECT_EQ(std::vector<std::string>({"Heating", "Cooling", "Condenser", "Steam"}), SizingPlant::loopTypeValues());
  EXPECT_EQ(std::vector<std::string>({"Coincident", "NonCoincident"}), SizingPlant::sizingOptionValues());
  EXPECT_EQ(std::vector<std::string>({"None", "GlobalHeatingSizingFactor", "GlobalCoolingSizingFactor", "LoopComponentSizingFactor"}),
            SizingPlant::coincidentSizingFactorModeValues());

  EXPECT_TRUE(sizingPlant.setLoopType("Cooling"));
  EXPECT_EQ("Cooling", sizingPlant.loopType());
  EXPECT_FALSE(sizingPlant.setLoopType("NotARealLoopType"));

  EXPECT_TRUE(sizingPlant.setDesignLoopExitTemperature(7.22));
  EXPECT_DOUBLE_EQ(7.22, sizingPlant.designLoopExitTemperature());

  EXPECT_TRUE(sizingPlant.setLoopDesignTemperatureDifference(6.67));
  EXPECT_DOUBLE_EQ(6.67, sizingPlant.loopDesignTemperatureDifference());
  EXPECT_FALSE(sizingPlant.setLoopDesignTemperatureDifference(0.0));

  EXPECT_TRUE(sizingPlant.setSizingOption("Coincident"));
  EXPECT_EQ("Coincident", sizingPlant.sizingOption());
  EXPECT_FALSE(sizingPlant.setSizingOption("InvalidSizingOption"));

  EXPECT_TRUE(sizingPlant.setZoneTimestepsinAveragingWindow(6));
  EXPECT_EQ(6, sizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_FALSE(sizingPlant.setZoneTimestepsinAveragingWindow(0));

  EXPECT_TRUE(sizingPlant.setCoincidentSizingFactorMode("GlobalCoolingSizingFactor"));
  EXPECT_EQ("GlobalCoolingSizingFactor", sizingPlant.coincidentSizingFactorMode());
  EXPECT_FALSE(sizingPlant.setCoincidentSizingFactorMode("InvalidCoincidentSizingFactorMode"));
}

TEST_F(EPModelFixture, SizingPlant_PlantLoopBackReferenceSaveLoad) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-sizing-plant-back-reference-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  PlantLoop plantLoop(model);
  ASSERT_TRUE(plantLoop.setName("Sizing Plant Back-Reference Loop"));

  const auto sizingPlant = plantLoop.sizingPlant();
  SizingPlant duplicateSizingPlant(model, plantLoop);
  SizingPlant orphanSizingPlant(model, plantLoop);
  ASSERT_TRUE(orphanSizingPlant.setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));

  EXPECT_EQ(plantLoop, sizingPlant.plantLoop());
  EXPECT_EQ(plantLoop, plantLoop.sizingPlant().plantLoop());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto loadedSizingPlants = loadedModel->getConcreteModelObjects<SizingPlant>();
  ASSERT_EQ(1u, loadedSizingPlants.size());

  const auto& loadedSizingPlant = loadedSizingPlants.front();
  EXPECT_EQ("Sizing Plant Back-Reference Loop", loadedSizingPlant.plantLoop().nameString());
  EXPECT_EQ(loadedSizingPlant, loadedSizingPlant.plantLoop().sizingPlant());
}

TEST_F(EPModelFixture, SizingPlant_CanonicalizeRemovesOrphanAndDuplicateCompanions) {
  Model model;
  PlantLoop plantLoop(model);
  SizingPlant duplicateSizingPlant(model, plantLoop);
  SizingPlant orphanSizingPlant(model, plantLoop);
  const auto duplicateHandle = duplicateSizingPlant.handle();
  const auto orphanHandle = orphanSizingPlant.handle();
  ASSERT_TRUE(orphanSizingPlant.setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));
  const auto retainedSizingPlantHandle = plantLoop.sizingPlant().handle();

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.warningCount, 2u);
  EXPECT_TRUE(model.getObject(retainedSizingPlantHandle));
  if (duplicateHandle != retainedSizingPlantHandle) {
    EXPECT_FALSE(model.getObject(duplicateHandle));
  }
  EXPECT_FALSE(model.getObject(orphanHandle));

  const auto sizingPlants = model.getConcreteModelObjects<SizingPlant>();
  ASSERT_EQ(1u, sizingPlants.size());
  EXPECT_EQ(retainedSizingPlantHandle, sizingPlants.front().handle());
  EXPECT_EQ(plantLoop, sizingPlants.front().plantLoop());
  EXPECT_EQ(sizingPlants.front(), plantLoop.sizingPlant());
}

TEST_F(EPModelFixture, SizingPlant_IsRemovedWithOwningPlantLoop) {
  Model model;
  PlantLoop plantLoop(model);
  const auto plantLoopHandle = plantLoop.handle();
  const auto sizingPlantHandle = plantLoop.sizingPlant().handle();

  EXPECT_FALSE(plantLoop.remove().empty());
  EXPECT_FALSE(model.getObject(plantLoopHandle));
  EXPECT_FALSE(model.getObject(sizingPlantHandle));
}
