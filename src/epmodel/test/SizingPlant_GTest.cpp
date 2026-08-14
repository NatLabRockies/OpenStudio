/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/SizingPlant.hpp"
#include "../ModelObject/SizingPlant_Impl.hpp"
#include "ScopedTestFailure.hpp"
#include "../TestFailurePoint.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Sizing_Plant_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

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

boost::optional<std::string> rawPlantLoopReference(const SizingPlant& sizingPlant) {
  const auto workspaceImpl = sizingPlant.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  if (!workspaceImpl) {
    return boost::none;
  }
  return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, false, true);
}

bool setRawPlantLoopReference(SizingPlant& sizingPlant, const std::string& rawReference) {
  const auto workspaceImpl = sizingPlant.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  return workspaceImpl
         && workspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, rawReference,
                                                                         false);
}

bool setRawPlantLoopName(PlantLoop& plantLoop, const std::string& rawName) {
  const auto workspaceImpl = plantLoop.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  const auto nameField = plantLoop.iddObject().nameFieldIndex();
  return workspaceImpl && nameField && workspaceImpl->openstudio::detail::IdfObject_Impl::setString(*nameField, rawName, false);
}

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

TEST_F(EPModelFixture, SizingPlant_SetPlantLoop_AtomicallySwapsCompanionsAndPreservesFields) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  ASSERT_TRUE(sourceLoop.setName("Sizing Plant Swap Source Loop"));
  ASSERT_TRUE(targetLoop.setName("Sizing Plant Swap Target Loop"));

  auto sourceSizingPlant = sourceLoop.sizingPlant();
  auto targetSizingPlant = targetLoop.sizingPlant();
  const auto sourceSizingPlantHandle = sourceSizingPlant.handle();
  const auto targetSizingPlantHandle = targetSizingPlant.handle();

  ASSERT_TRUE(sourceSizingPlant.setLoopType("Heating"));
  ASSERT_TRUE(sourceSizingPlant.setDesignLoopExitTemperature(74.3));
  ASSERT_TRUE(sourceSizingPlant.setLoopDesignTemperatureDifference(9.1));
  ASSERT_TRUE(sourceSizingPlant.setSizingOption("Coincident"));
  ASSERT_TRUE(sourceSizingPlant.setZoneTimestepsinAveragingWindow(5));
  ASSERT_TRUE(sourceSizingPlant.setCoincidentSizingFactorMode("GlobalHeatingSizingFactor"));

  ASSERT_TRUE(targetSizingPlant.setLoopType("Cooling"));
  ASSERT_TRUE(targetSizingPlant.setDesignLoopExitTemperature(6.8));
  ASSERT_TRUE(targetSizingPlant.setLoopDesignTemperatureDifference(5.4));
  ASSERT_TRUE(targetSizingPlant.setSizingOption("NonCoincident"));
  ASSERT_TRUE(targetSizingPlant.setZoneTimestepsinAveragingWindow(2));
  ASSERT_TRUE(targetSizingPlant.setCoincidentSizingFactorMode("GlobalCoolingSizingFactor"));

  ASSERT_TRUE(sourceSizingPlant.setPlantLoop(targetLoop));

  EXPECT_EQ(targetLoop, sourceSizingPlant.plantLoop());
  EXPECT_EQ(sourceLoop, targetSizingPlant.plantLoop());
  EXPECT_EQ(sourceSizingPlantHandle, targetLoop.sizingPlant().handle());
  EXPECT_EQ(targetSizingPlantHandle, sourceLoop.sizingPlant().handle());

  EXPECT_EQ("Heating", sourceSizingPlant.loopType());
  EXPECT_DOUBLE_EQ(74.3, sourceSizingPlant.designLoopExitTemperature());
  EXPECT_DOUBLE_EQ(9.1, sourceSizingPlant.loopDesignTemperatureDifference());
  EXPECT_EQ("Coincident", sourceSizingPlant.sizingOption());
  EXPECT_EQ(5, sourceSizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_EQ("GlobalHeatingSizingFactor", sourceSizingPlant.coincidentSizingFactorMode());
  EXPECT_EQ("Heating", sourceSizingPlant.getString(openstudio::Sizing_PlantFields::LoopType, true).get());

  EXPECT_EQ("Cooling", targetSizingPlant.loopType());
  EXPECT_DOUBLE_EQ(6.8, targetSizingPlant.designLoopExitTemperature());
  EXPECT_DOUBLE_EQ(5.4, targetSizingPlant.loopDesignTemperatureDifference());
  EXPECT_EQ("NonCoincident", targetSizingPlant.sizingOption());
  EXPECT_EQ(2, targetSizingPlant.zoneTimestepsinAveragingWindow());
  EXPECT_EQ("GlobalCoolingSizingFactor", targetSizingPlant.coincidentSizingFactorMode());
  EXPECT_EQ("Cooling", targetSizingPlant.getString(openstudio::Sizing_PlantFields::LoopType, true).get());
}

TEST_F(EPModelFixture, SizingPlant_SetPlantLoop_RejectsCrossModelAndSameLoopIsValidatedNoOp) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  auto sourceSizingPlant = sourceLoop.sizingPlant();
  const auto sourceSizingPlantHandle = sourceSizingPlant.handle();
  const auto targetSizingPlantHandle = targetLoop.sizingPlant().handle();

  EXPECT_TRUE(sourceSizingPlant.setPlantLoop(sourceLoop));
  EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
  EXPECT_EQ(sourceSizingPlantHandle, sourceLoop.sizingPlant().handle());

  Model otherModel;
  PlantLoop otherLoop(otherModel);
  EXPECT_FALSE(sourceSizingPlant.setPlantLoop(otherLoop));
  EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
  EXPECT_EQ(sourceSizingPlantHandle, sourceLoop.sizingPlant().handle());
  EXPECT_EQ(targetSizingPlantHandle, targetLoop.sizingPlant().handle());
}

TEST_F(EPModelFixture, SizingPlant_SetPlantLoop_RejectsMalformedCompanionStatesWithoutMutation) {
  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    auto targetSizingPlant = targetLoop.sizingPlant();
    SizingPlant duplicateSizingPlant(model, sourceLoop);

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(targetLoop, targetSizingPlant.plantLoop());
    EXPECT_EQ(sourceLoop, duplicateSizingPlant.plantLoop());
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    auto targetSizingPlant = targetLoop.sizingPlant();
    SizingPlant duplicateSizingPlant(model, targetLoop);

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(targetLoop, targetSizingPlant.plantLoop());
    EXPECT_EQ(targetLoop, duplicateSizingPlant.plantLoop());
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    SizingPlant rawNameDuplicate(model, sourceLoop);
    ASSERT_TRUE(rawNameDuplicate.setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));
    ASSERT_TRUE(setRawPlantLoopReference(rawNameDuplicate, sourceLoop.nameString()));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(sourceLoop.nameString(), rawPlantLoopReference(rawNameDuplicate).value_or(""));
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    SizingPlant rawUUIDDuplicate(model, targetLoop);
    ASSERT_TRUE(rawUUIDDuplicate.setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));
    ASSERT_TRUE(setRawPlantLoopReference(rawUUIDDuplicate, openstudio::toString(targetLoop.handle())));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(openstudio::toString(targetLoop.handle()), rawPlantLoopReference(rawUUIDDuplicate).value_or(""));
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    ASSERT_TRUE(setRawPlantLoopReference(sourceSizingPlant, sourceLoop.nameString()));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(sourceLoop.nameString(), rawPlantLoopReference(sourceSizingPlant).value_or(""));
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    auto targetSizingPlant = targetLoop.sizingPlant();
    ASSERT_TRUE(setRawPlantLoopReference(targetSizingPlant, targetLoop.nameString()));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_EQ(targetLoop, targetSizingPlant.plantLoop());
    EXPECT_EQ(targetLoop.nameString(), rawPlantLoopReference(targetSizingPlant).value_or(""));
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    ASSERT_TRUE(sourceLoop.setName("Sizing Plant Case Ambiguity"));
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    ASSERT_TRUE(setRawPlantLoopName(targetLoop, "sizing plant case ambiguity"));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    auto targetSizingPlant = targetLoop.sizingPlant();
    const auto targetSizingPlantHandle = targetSizingPlant.handle();
    targetSizingPlant.remove();

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
    EXPECT_FALSE(model.getObject(targetSizingPlantHandle));
  }

  {
    Model model;
    PlantLoop sourceLoop(model);
    PlantLoop targetLoop(model);
    auto sourceSizingPlant = sourceLoop.sizingPlant();
    const auto targetSizingPlantHandle = targetLoop.sizingPlant().handle();
    ASSERT_TRUE(sourceSizingPlant.setString(openstudio::Sizing_PlantFields::PlantorCondenserLoopName, ""));

    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
    EXPECT_FALSE(sourceSizingPlant.getModelObjectTarget<PlantLoop>(openstudio::Sizing_PlantFields::PlantorCondenserLoopName));
    EXPECT_EQ(targetSizingPlantHandle, targetLoop.sizingPlant().handle());
  }
}

TEST_F(EPModelFixture, SizingPlant_SetPlantLoop_RollsBackAfterFirstCompanionPointerWriteFailure) {
  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  auto sourceSizingPlant = sourceLoop.sizingPlant();
  auto targetSizingPlant = targetLoop.sizingPlant();
  const auto sourceSizingPlantHandle = sourceSizingPlant.handle();
  const auto targetSizingPlantHandle = targetSizingPlant.handle();
  const auto sourceRawReferenceBefore = rawPlantLoopReference(sourceSizingPlant);
  const auto targetRawReferenceBefore = rawPlantLoopReference(targetSizingPlant);

  ASSERT_TRUE(sourceSizingPlant.setLoopType("Heating"));
  ASSERT_TRUE(targetSizingPlant.setLoopType("Cooling"));
  {
    test::ScopedTestFailure failure(model, detail::TestFailurePoint::SizingPlantAfterFirstCompanionPointerWritten);
    EXPECT_FALSE(sourceSizingPlant.setPlantLoop(targetLoop));
  }

  EXPECT_EQ(sourceLoop, sourceSizingPlant.plantLoop());
  EXPECT_EQ(targetLoop, targetSizingPlant.plantLoop());
  EXPECT_EQ(sourceSizingPlantHandle, sourceLoop.sizingPlant().handle());
  EXPECT_EQ(targetSizingPlantHandle, targetLoop.sizingPlant().handle());
  EXPECT_EQ("Heating", sourceSizingPlant.loopType());
  EXPECT_EQ("Cooling", targetSizingPlant.loopType());
  const auto sourceRawReferenceAfter = rawPlantLoopReference(sourceSizingPlant);
  const auto targetRawReferenceAfter = rawPlantLoopReference(targetSizingPlant);
  EXPECT_EQ(sourceRawReferenceBefore.has_value(), sourceRawReferenceAfter.has_value());
  EXPECT_EQ(targetRawReferenceBefore.has_value(), targetRawReferenceAfter.has_value());
  if (sourceRawReferenceBefore && sourceRawReferenceAfter) {
    EXPECT_EQ(*sourceRawReferenceBefore, *sourceRawReferenceAfter);
  }
  if (targetRawReferenceBefore && targetRawReferenceAfter) {
    EXPECT_EQ(*targetRawReferenceBefore, *targetRawReferenceAfter);
  }

  ASSERT_TRUE(sourceSizingPlant.setPlantLoop(targetLoop));
  EXPECT_EQ(targetLoop, sourceSizingPlant.plantLoop());
  EXPECT_EQ(sourceLoop, targetSizingPlant.plantLoop());
  EXPECT_EQ(sourceSizingPlantHandle, targetLoop.sizingPlant().handle());
  EXPECT_EQ(targetSizingPlantHandle, sourceLoop.sizingPlant().handle());
  EXPECT_EQ("Heating", sourceSizingPlant.loopType());
  EXPECT_EQ("Cooling", targetSizingPlant.loopType());
}

TEST_F(EPModelFixture, SizingPlant_SetPlantLoop_SaveLoadAndRemovalRetainSwappedOwnership) {
  const auto idfPath =
    openstudio::tempDir() / openstudio::toPath("epmodel-sizing-plant-companion-swap-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  PlantLoop sourceLoop(model);
  PlantLoop targetLoop(model);
  ASSERT_TRUE(sourceLoop.setName("Sizing Plant Swap Save Source Loop"));
  ASSERT_TRUE(targetLoop.setName("Sizing Plant Swap Save Target Loop"));
  auto sourceSizingPlant = sourceLoop.sizingPlant();
  auto targetSizingPlant = targetLoop.sizingPlant();
  ASSERT_TRUE(sourceSizingPlant.setLoopType("Heating"));
  ASSERT_TRUE(targetSizingPlant.setLoopType("Cooling"));
  ASSERT_TRUE(sourceSizingPlant.setPlantLoop(targetLoop));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  const auto canonicalReport = loadedModel->canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, canonicalReport.errorCount);
  EXPECT_EQ(0u, canonicalReport.warningCount);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sizing Plant Swap Save Source Loop");
  auto loadedTargetLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Sizing Plant Swap Save Target Loop");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedTargetLoop);
  const auto loadedSourceSizingPlant = loadedTargetLoop->sizingPlant();
  const auto loadedTargetSizingPlant = loadedSourceLoop->sizingPlant();

  EXPECT_EQ(*loadedTargetLoop, loadedSourceSizingPlant.plantLoop());
  EXPECT_EQ(*loadedSourceLoop, loadedTargetSizingPlant.plantLoop());
  EXPECT_EQ(loadedSourceSizingPlant.handle(), loadedTargetLoop->sizingPlant().handle());
  EXPECT_EQ(loadedTargetSizingPlant.handle(), loadedSourceLoop->sizingPlant().handle());
  EXPECT_EQ("Heating", loadedSourceSizingPlant.loopType());
  EXPECT_EQ("Cooling", loadedTargetSizingPlant.loopType());

  EXPECT_FALSE(loadedSourceLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedTargetSizingPlant.handle()));
  EXPECT_TRUE(loadedModel->getObject(loadedSourceSizingPlant.handle()));
  EXPECT_FALSE(loadedTargetLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedSourceSizingPlant.handle()));
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
