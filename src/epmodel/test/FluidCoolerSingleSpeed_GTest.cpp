/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/FluidCoolerSingleSpeed.hpp"
#include "../StraightComponent/FluidCoolerSingleSpeed_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/FluidCooler_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
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

openstudio::path uniqueIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

unsigned outdoorAirNodeListEntryCount(const Model& model, const std::string& nodeName) {
  unsigned result = 0;
  for (const auto& object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    for (const auto& group : object.extensibleGroups()) {
      const auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        continue;
      }
      const auto value = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
      if (value && openstudio::istringEqual(*value, nodeName)) {
        ++result;
      }
    }
  }
  return result;
}

bool hasOutdoorAirNode(const Model& model, const std::string& nodeName) {
  const auto objects = model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node);
  return std::ranges::any_of(objects, [&](const auto& object) { return openstudio::istringEqual(object.nameString(), nodeName); });
}

}  // namespace

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_DefaultConstructor) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  EXPECT_EQ(FluidCoolerSingleSpeed::iddObjectType(), fluidCooler.iddObject().type());
  EXPECT_FALSE(fluidCooler.nameString().empty());
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());

  EXPECT_EQ("NominalCapacity", fluidCooler.performanceInputMethod());

  EXPECT_FALSE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(58601.0, fluidCooler.nominalCapacity());
  EXPECT_DOUBLE_EQ(51.67, fluidCooler.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, fluidCooler.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, fluidCooler.designEnteringAirWetbulbTemperature());

  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001388, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());

  ASSERT_TRUE(fluidCooler.designAirFlowRate());
  EXPECT_DOUBLE_EQ(9.911, *fluidCooler.designAirFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(fluidCooler.designAirFlowRateFanPower());
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  const auto performanceInputMethods = FluidCoolerSingleSpeed::performanceInputMethodValues();
  ASSERT_EQ(2u, performanceInputMethods.size());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", performanceInputMethods[0]);
  EXPECT_EQ("NominalCapacity", performanceInputMethods[1]);

  EXPECT_TRUE(fluidCooler.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", fluidCooler.performanceInputMethod());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRateUfactorTimesAreaValue(1500.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1500.0, *fluidCooler.designAirFlowRateUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeDesignAirFlowRateUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRateUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setNominalCapacity(64000.0));
  EXPECT_DOUBLE_EQ(64000.0, fluidCooler.nominalCapacity());

  EXPECT_TRUE(fluidCooler.setDesignEnteringWaterTemperature(45.0));
  EXPECT_DOUBLE_EQ(45.0, fluidCooler.designEnteringWaterTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirTemperature(30.0));
  EXPECT_DOUBLE_EQ(30.0, fluidCooler.designEnteringAirTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirWetbulbTemperature(21.5));
  EXPECT_DOUBLE_EQ(21.5, fluidCooler.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(fluidCooler.setDesignWaterFlowRate(0.003));
  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.003, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());
  fluidCooler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designWaterFlowRate());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRate(11.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRate());
  EXPECT_DOUBLE_EQ(11.0, *fluidCooler.designAirFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateAutosized());
  fluidCooler.autosizeDesignAirFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRate());

  EXPECT_TRUE(fluidCooler.setDesignAirFlowRateFanPower(350.0));
  ASSERT_TRUE(fluidCooler.designAirFlowRateFanPower());
  EXPECT_DOUBLE_EQ(350.0, *fluidCooler.designAirFlowRateFanPower());
  EXPECT_FALSE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
  fluidCooler.autosizeDesignAirFlowRateFanPower();
  EXPECT_TRUE(fluidCooler.isDesignAirFlowRateFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.designAirFlowRateFanPower());

  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRateUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedDesignAirFlowRateFanPower());
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(fluidCooler.addToNode(airSupplyOutletNode));
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(fluidCooler.addToNode(*demandBranchNode));
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(fluidCooler.addToNode(plantSupplyOutletNode));
  ASSERT_TRUE(fluidCooler.loop());
  EXPECT_EQ(plantLoop.handle(), fluidCooler.loop()->handle());
  ASSERT_TRUE(fluidCooler.inletModelObject());
  ASSERT_TRUE(fluidCooler.outletModelObject());

  auto inletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_SingleSpeedFields::WaterInletNodeName);
  auto outletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_SingleSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(fluidCooler.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(fluidCooler.outletModelObject()->handle(), outletNode->handle());

  FluidCoolerSingleSpeed secondFluidCooler(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondFluidCooler.addToNode(plantDemandOutletNode));
  EXPECT_FALSE(secondFluidCooler.loop());
  EXPECT_FALSE(secondFluidCooler.inletModelObject());
  EXPECT_FALSE(secondFluidCooler.outletModelObject());
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_OutdoorAirInletSetReplaceResetAndForeignPreservation) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);
  Node firstNode(model);
  Node replacementNode(model);
  ASSERT_TRUE(firstNode.setName("Single Speed Outdoor Air Inlet"));
  ASSERT_TRUE(replacementNode.setName("Single Speed Replacement Outdoor Air Inlet"));
  const auto firstNodeHandle = firstNode.handle();
  const auto replacementNodeHandle = replacementNode.handle();

  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(firstNode));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(firstNodeHandle, fluidCooler.outdoorAirInletNode()->handle());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, firstNode.nameString()));

  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(replacementNode));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(replacementNodeHandle, fluidCooler.outdoorAirInletNode()->handle());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, firstNode.nameString()));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, replacementNode.nameString()));
  EXPECT_TRUE(model.getObject(firstNodeHandle));

  Model foreignModel;
  Node foreignNode(foreignModel);
  EXPECT_FALSE(fluidCooler.setOutdoorAirInletNode(foreignNode));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(replacementNodeHandle, fluidCooler.outdoorAirInletNode()->handle());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, replacementNode.nameString()));

  fluidCooler.resetOutdoorAirInletNode();
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, replacementNode.nameString()));
  EXPECT_TRUE(model.getObject(replacementNodeHandle));
  fluidCooler.resetOutdoorAirInletNode();
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_OutdoorAirDirectDeclarationTakesPrecedence) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Direct Single Speed Outdoor Air Node"));

  // These low-level objects intentionally model imported EnergyPlus outdoor-air declarations; epmodel has no typed declaration wrapper.
  auto directDeclaration = ModelObject::create(openstudio::IddObjectType::OutdoorAir_Node, model);
  ASSERT_TRUE(directDeclaration.setName(outdoorAirNode.nameString()));
  auto conflictingList = ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model);
  auto conflictingGroup = conflictingList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(conflictingGroup);
  ASSERT_TRUE(conflictingGroup->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, outdoorAirNode.nameString()));
  auto retainedGroup = conflictingList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(retainedGroup);
  ASSERT_TRUE(retainedGroup->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, "Unrelated Outdoor Air Node"));

  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(outdoorAirNode));
  EXPECT_TRUE(hasOutdoorAirNode(model, outdoorAirNode.nameString()));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, outdoorAirNode.nameString()));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Unrelated Outdoor Air Node"));

  fluidCooler.resetOutdoorAirInletNode();
  EXPECT_TRUE(hasOutdoorAirNode(model, outdoorAirNode.nameString()));
  EXPECT_TRUE(model.getObject(outdoorAirNode.handle()));
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_OutdoorAirInletCanonicalizationRepairsImportedStorage) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);
  ASSERT_TRUE(fluidCooler.setName("Imported Single Speed Fluid Cooler"));

  constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
  auto workspaceImpl = fluidCooler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  // Deliberately seed unresolved raw NodeType text to represent a malformed imported IDF without using a public relationship setter.
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Imported Single Speed Outdoor Air Node", false));
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ("Imported Single Speed Outdoor Air Node", fluidCooler.outdoorAirInletNode()->nameString());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Single Speed Outdoor Air Node"));

  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(1u, secondReport.infoCount);  // The canonicalizer's summary is the only informational message on the no-op pass.
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Single Speed Outdoor Air Node"));

  const auto importedNodeHandle = fluidCooler.outdoorAirInletNode()->handle();
  fluidCooler.resetOutdoorAirInletNode();
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Imported Single Speed Outdoor Air Node"));
  EXPECT_TRUE(model.getObject(importedNodeHandle));
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_CanonicalizationRepairsManagedNodeMissingDeclaration) {
  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Managed Single Speed Outdoor Air Node"));
  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(outdoorAirNode));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());

  // Deliberately remove the generated EnergyPlus declaration to represent malformed imported storage around an intact managed pointer.
  constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
  auto workspaceImpl = fluidCooler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("").empty());
  for (auto object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    object.remove();
  }
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, outdoorAirNode.nameString()));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(outdoorAirNode.handle(), fluidCooler.outdoorAirInletNode()->handle());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(outdoorAirNode.handle(), fluidCooler.outdoorAirInletNode()->handle());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, outdoorAirNode.nameString()));
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_OutdoorAirInletTwoStageReloadMutationAndReset) {
  const auto firstPath = uniqueIdfPath("epmodel-fluid-cooler-single-outdoor-air-first");
  const auto secondPath = uniqueIdfPath("epmodel-fluid-cooler-single-outdoor-air-second");
  const ScopedFileRemoval removeFirst(firstPath);
  const ScopedFileRemoval removeSecond(secondPath);

  Model model;
  FluidCoolerSingleSpeed fluidCooler(model);
  ASSERT_TRUE(fluidCooler.setName("Reload Single Speed Fluid Cooler"));
  Node firstNode(model);
  ASSERT_TRUE(firstNode.setName("Reload Single Speed Outdoor Air Node"));
  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(firstNode));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFluidCooler = loadedModel->getConcreteModelObjectByName<FluidCoolerSingleSpeed>("Reload Single Speed Fluid Cooler");
  ASSERT_TRUE(loadedFluidCooler);
  ASSERT_TRUE(loadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ("Reload Single Speed Outdoor Air Node", loadedFluidCooler->outdoorAirInletNode()->nameString());
  Node replacementNode(*loadedModel);
  ASSERT_TRUE(replacementNode.setName("Reload Single Speed Replacement Outdoor Air Node"));
  ASSERT_TRUE(loadedFluidCooler->setOutdoorAirInletNode(replacementNode));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*loadedModel, "Reload Single Speed Outdoor Air Node"));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(*loadedModel, replacementNode.nameString()));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFluidCooler = reloadedModel->getConcreteModelObjectByName<FluidCoolerSingleSpeed>("Reload Single Speed Fluid Cooler");
  ASSERT_TRUE(reloadedFluidCooler);
  ASSERT_TRUE(reloadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ("Reload Single Speed Replacement Outdoor Air Node", reloadedFluidCooler->outdoorAirInletNode()->nameString());
  const auto replacementHandle = reloadedFluidCooler->outdoorAirInletNode()->handle();
  reloadedFluidCooler->resetOutdoorAirInletNode();
  EXPECT_FALSE(reloadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*reloadedModel, "Reload Single Speed Replacement Outdoor Air Node"));
  EXPECT_TRUE(reloadedModel->getObject(replacementHandle));
}

TEST_F(EPModelFixture, FluidCoolerSingleSpeed_RemovalCleansDeclarationAndPreservesNode) {
  Model model;
  PlantLoop plantLoop(model);
  FluidCoolerSingleSpeed fluidCooler(model);
  const auto fluidCoolerHandle = fluidCooler.handle();
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Removed Single Speed Outdoor Air Node"));
  const auto outdoorAirNodeHandle = outdoorAirNode.handle();

  auto supplyOutletNode = plantLoop.supplyOutletNode();
  ASSERT_TRUE(fluidCooler.addToNode(supplyOutletNode));
  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(outdoorAirNode));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, outdoorAirNode.nameString()));

  EXPECT_FALSE(fluidCooler.remove().empty());
  EXPECT_FALSE(model.getObject(fluidCoolerHandle));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, outdoorAirNode.nameString()));
  EXPECT_TRUE(model.getObject(outdoorAirNodeHandle));
  EXPECT_TRUE(model.getObject(plantLoop.handle()));
}
