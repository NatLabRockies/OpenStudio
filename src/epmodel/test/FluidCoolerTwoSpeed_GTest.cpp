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
#include "../StraightComponent/FluidCoolerTwoSpeed.hpp"
#include "../StraightComponent/FluidCoolerTwoSpeed_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/FluidCooler_TwoSpeed_FieldEnums.hxx>
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

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_DefaultConstructor) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  EXPECT_EQ(FluidCoolerTwoSpeed::iddObjectType(), fluidCooler.iddObject().type());
  EXPECT_FALSE(fluidCooler.nameString().empty());
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());

  EXPECT_EQ("NominalCapacity", fluidCooler.performanceInputMethod());

  EXPECT_FALSE(fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_FALSE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(0.6, fluidCooler.lowFanSpeedUFactorTimesAreaSizingFactor());
  EXPECT_DOUBLE_EQ(58601.0, fluidCooler.highSpeedNominalCapacity());

  ASSERT_TRUE(fluidCooler.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(28601.0, *fluidCooler.lowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.isLowSpeedNominalCapacityAutosized());

  EXPECT_DOUBLE_EQ(0.5, fluidCooler.lowSpeedNominalCapacitySizingFactor());
  EXPECT_DOUBLE_EQ(51.67, fluidCooler.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(35.0, fluidCooler.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, fluidCooler.designEnteringAirWetbulbTemperature());

  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.001388, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());

  ASSERT_TRUE(fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(9.911, *fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_FALSE(fluidCooler.highFanSpeedFanPower());
  EXPECT_TRUE(fluidCooler.isHighFanSpeedFanPowerAutosized());

  ASSERT_TRUE(fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.955, *fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.5, fluidCooler.lowFanSpeedAirFlowRateSizingFactor());
  EXPECT_FALSE(fluidCooler.lowFanSpeedFanPower());
  EXPECT_TRUE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  EXPECT_DOUBLE_EQ(0.16, fluidCooler.lowFanSpeedFanPowerSizingFactor());
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  const auto performanceInputMethods = FluidCoolerTwoSpeed::performanceInputMethodValues();
  ASSERT_EQ(2u, performanceInputMethods.size());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", performanceInputMethods[0]);
  EXPECT_EQ("NominalCapacity", performanceInputMethods[1]);

  EXPECT_TRUE(fluidCooler.setPerformanceInputMethod("UFactorTimesAreaAndDesignWaterFlowRate"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", fluidCooler.performanceInputMethod());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedUfactorTimesAreaValue(3100.0));
  ASSERT_TRUE(fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(3100.0, *fluidCooler.highFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeHighFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedUfactorTimesAreaValue(1700.0));
  ASSERT_TRUE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1700.0, *fluidCooler.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());
  fluidCooler.autosizeLowFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedUfactorTimesAreaValueAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedUfactorTimesAreaValue());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedUFactorTimesAreaSizingFactor(0.58));
  EXPECT_DOUBLE_EQ(0.58, fluidCooler.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_TRUE(fluidCooler.setHighSpeedNominalCapacity(64000.0));
  EXPECT_DOUBLE_EQ(64000.0, fluidCooler.highSpeedNominalCapacity());

  EXPECT_TRUE(fluidCooler.setLowSpeedNominalCapacity(30000.0));
  ASSERT_TRUE(fluidCooler.lowSpeedNominalCapacity());
  EXPECT_DOUBLE_EQ(30000.0, *fluidCooler.lowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.isLowSpeedNominalCapacityAutosized());
  fluidCooler.autosizeLowSpeedNominalCapacity();
  EXPECT_TRUE(fluidCooler.isLowSpeedNominalCapacityAutosized());
  EXPECT_FALSE(fluidCooler.lowSpeedNominalCapacity());

  EXPECT_TRUE(fluidCooler.setLowSpeedNominalCapacitySizingFactor(0.45));
  EXPECT_DOUBLE_EQ(0.45, fluidCooler.lowSpeedNominalCapacitySizingFactor());

  EXPECT_TRUE(fluidCooler.setDesignEnteringWaterTemperature(46.0));
  EXPECT_DOUBLE_EQ(46.0, fluidCooler.designEnteringWaterTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirTemperature(31.0));
  EXPECT_DOUBLE_EQ(31.0, fluidCooler.designEnteringAirTemperature());

  EXPECT_TRUE(fluidCooler.setDesignEnteringAirWetbulbTemperature(22.0));
  EXPECT_DOUBLE_EQ(22.0, fluidCooler.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(fluidCooler.setDesignWaterFlowRate(0.0022));
  ASSERT_TRUE(fluidCooler.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0022, *fluidCooler.designWaterFlowRate());
  EXPECT_FALSE(fluidCooler.isDesignWaterFlowRateAutosized());
  fluidCooler.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(fluidCooler.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.designWaterFlowRate());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedAirFlowRate(12.2));
  ASSERT_TRUE(fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(12.2, *fluidCooler.highFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());
  fluidCooler.autosizeHighFanSpeedAirFlowRate();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedAirFlowRate());

  EXPECT_TRUE(fluidCooler.setHighFanSpeedFanPower(1650.0));
  ASSERT_TRUE(fluidCooler.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1650.0, *fluidCooler.highFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.isHighFanSpeedFanPowerAutosized());
  fluidCooler.autosizeHighFanSpeedFanPower();
  EXPECT_TRUE(fluidCooler.isHighFanSpeedFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.highFanSpeedFanPower());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedAirFlowRate(6.2));
  ASSERT_TRUE(fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(6.2, *fluidCooler.lowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());
  fluidCooler.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedAirFlowRateAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedAirFlowRate());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedAirFlowRateSizingFactor(0.47));
  EXPECT_DOUBLE_EQ(0.47, fluidCooler.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedFanPower(720.0));
  ASSERT_TRUE(fluidCooler.lowFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(720.0, *fluidCooler.lowFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  fluidCooler.autosizeLowFanSpeedFanPower();
  EXPECT_TRUE(fluidCooler.isLowFanSpeedFanPowerAutosized());
  EXPECT_FALSE(fluidCooler.lowFanSpeedFanPower());

  EXPECT_TRUE(fluidCooler.setLowFanSpeedFanPowerSizingFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, fluidCooler.lowFanSpeedFanPowerSizingFactor());

  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(fluidCooler.autosizedLowSpeedNominalCapacity());
  EXPECT_FALSE(fluidCooler.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedHighFanSpeedFanPower());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedAirFlowRate());
  EXPECT_FALSE(fluidCooler.autosizedLowFanSpeedFanPower());
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(fluidCooler.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(fluidCooler.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());
  EXPECT_FALSE(fluidCooler.loop());
  EXPECT_FALSE(fluidCooler.inletModelObject());
  EXPECT_FALSE(fluidCooler.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(fluidCooler.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(fluidCooler.loop());
  EXPECT_EQ(plantLoop.handle(), fluidCooler.loop()->handle());
  ASSERT_TRUE(fluidCooler.inletModelObject());
  ASSERT_TRUE(fluidCooler.outletModelObject());

  auto inletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_TwoSpeedFields::WaterInletNodeName);
  auto outletNode = fluidCooler.getModelObjectTarget<Node>(openstudio::FluidCooler_TwoSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(fluidCooler.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(fluidCooler.outletModelObject()->handle(), outletNode->handle());

  FluidCoolerTwoSpeed secondFluidCooler(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondFluidCooler.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondFluidCooler.loop());
  EXPECT_FALSE(secondFluidCooler.inletModelObject());
  EXPECT_FALSE(secondFluidCooler.outletModelObject());
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_OutdoorAirInletSetReplaceResetAndForeignPreservation) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);
  Node firstNode(model);
  Node replacementNode(model);
  ASSERT_TRUE(firstNode.setName("Two Speed Outdoor Air Inlet"));
  ASSERT_TRUE(replacementNode.setName("Two Speed Replacement Outdoor Air Inlet"));
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

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_OutdoorAirDirectDeclarationTakesPrecedence) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Direct Two Speed Outdoor Air Node"));

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

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_OutdoorAirInletCanonicalizationRepairsImportedStorage) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);
  ASSERT_TRUE(fluidCooler.setName("Imported Two Speed Fluid Cooler"));

  constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
  auto workspaceImpl = fluidCooler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  // Deliberately seed unresolved raw NodeType text to represent a malformed imported IDF without using a public relationship setter.
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Imported Two Speed Outdoor Air Node", false));
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ("Imported Two Speed Outdoor Air Node", fluidCooler.outdoorAirInletNode()->nameString());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Two Speed Outdoor Air Node"));

  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(1u, secondReport.infoCount);  // The canonicalizer's summary is the only informational message on the no-op pass.
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Two Speed Outdoor Air Node"));

  const auto importedNodeHandle = fluidCooler.outdoorAirInletNode()->handle();
  fluidCooler.resetOutdoorAirInletNode();
  EXPECT_FALSE(fluidCooler.outdoorAirInletNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Imported Two Speed Outdoor Air Node"));
  EXPECT_TRUE(model.getObject(importedNodeHandle));
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_CanonicalizationRepairsManagedNodeMissingDeclaration) {
  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Managed Two Speed Outdoor Air Node"));
  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(outdoorAirNode));
  ASSERT_TRUE(fluidCooler.outdoorAirInletNode());

  // Deliberately remove the generated EnergyPlus declaration to represent malformed imported storage around an intact managed pointer.
  constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
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

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_OutdoorAirInletTwoStageReloadMutationAndReset) {
  const auto firstPath = uniqueIdfPath("epmodel-fluid-cooler-two-outdoor-air-first");
  const auto secondPath = uniqueIdfPath("epmodel-fluid-cooler-two-outdoor-air-second");
  const ScopedFileRemoval removeFirst(firstPath);
  const ScopedFileRemoval removeSecond(secondPath);

  Model model;
  FluidCoolerTwoSpeed fluidCooler(model);
  ASSERT_TRUE(fluidCooler.setName("Reload Two Speed Fluid Cooler"));
  Node firstNode(model);
  ASSERT_TRUE(firstNode.setName("Reload Two Speed Outdoor Air Node"));
  ASSERT_TRUE(fluidCooler.setOutdoorAirInletNode(firstNode));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFluidCooler = loadedModel->getConcreteModelObjectByName<FluidCoolerTwoSpeed>("Reload Two Speed Fluid Cooler");
  ASSERT_TRUE(loadedFluidCooler);
  ASSERT_TRUE(loadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ("Reload Two Speed Outdoor Air Node", loadedFluidCooler->outdoorAirInletNode()->nameString());
  Node replacementNode(*loadedModel);
  ASSERT_TRUE(replacementNode.setName("Reload Two Speed Replacement Outdoor Air Node"));
  ASSERT_TRUE(loadedFluidCooler->setOutdoorAirInletNode(replacementNode));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*loadedModel, "Reload Two Speed Outdoor Air Node"));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(*loadedModel, replacementNode.nameString()));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFluidCooler = reloadedModel->getConcreteModelObjectByName<FluidCoolerTwoSpeed>("Reload Two Speed Fluid Cooler");
  ASSERT_TRUE(reloadedFluidCooler);
  ASSERT_TRUE(reloadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ("Reload Two Speed Replacement Outdoor Air Node", reloadedFluidCooler->outdoorAirInletNode()->nameString());
  const auto replacementHandle = reloadedFluidCooler->outdoorAirInletNode()->handle();
  reloadedFluidCooler->resetOutdoorAirInletNode();
  EXPECT_FALSE(reloadedFluidCooler->outdoorAirInletNode());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*reloadedModel, "Reload Two Speed Replacement Outdoor Air Node"));
  EXPECT_TRUE(reloadedModel->getObject(replacementHandle));
}

TEST_F(EPModelFixture, FluidCoolerTwoSpeed_RemovalCleansDeclarationAndPreservesNode) {
  Model model;
  PlantLoop plantLoop(model);
  FluidCoolerTwoSpeed fluidCooler(model);
  const auto fluidCoolerHandle = fluidCooler.handle();
  Node outdoorAirNode(model);
  ASSERT_TRUE(outdoorAirNode.setName("Removed Two Speed Outdoor Air Node"));
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

TEST_F(EPModelFixture, FluidCoolers_SharedOutdoorAirDeclarationSurvivesUntilFinalUser) {
  Model model;
  FluidCoolerSingleSpeed singleSpeed(model);
  FluidCoolerTwoSpeed twoSpeed(model);
  Node sharedNode(model);
  ASSERT_TRUE(sharedNode.setName("Shared Fluid Cooler Outdoor Air Node"));
  const auto sharedNodeHandle = sharedNode.handle();

  ASSERT_TRUE(singleSpeed.setOutdoorAirInletNode(sharedNode));
  ASSERT_TRUE(twoSpeed.setOutdoorAirInletNode(sharedNode));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, sharedNode.nameString()));

  singleSpeed.resetOutdoorAirInletNode();
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, sharedNode.nameString()));
  EXPECT_FALSE(twoSpeed.remove().empty());
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, sharedNode.nameString()));
  EXPECT_TRUE(model.getObject(sharedNodeHandle));
}
