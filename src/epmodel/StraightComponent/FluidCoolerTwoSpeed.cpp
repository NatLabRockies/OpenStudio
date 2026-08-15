/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FluidCoolerTwoSpeed.hpp"
#include "StraightComponent/FluidCoolerTwoSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/FluidCooler_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  FluidCoolerTwoSpeed::FluidCoolerTwoSpeed(const Model& model) : StraightComponent(FluidCoolerTwoSpeed::iddObjectType(), model) {
    bool ok = true;
    ok = setPerformanceInputMethod("NominalCapacity");
    OS_ASSERT(ok);
    autosizeHighFanSpeedUfactorTimesAreaValue();
    autosizeLowFanSpeedUfactorTimesAreaValue();
    ok = setLowFanSpeedUFactorTimesAreaSizingFactor(0.6);
    OS_ASSERT(ok);
    ok = setHighSpeedNominalCapacity(58601.0);
    OS_ASSERT(ok);
    ok = setLowSpeedNominalCapacity(28601.0);
    OS_ASSERT(ok);
    ok = setLowSpeedNominalCapacitySizingFactor(0.5);
    OS_ASSERT(ok);
    ok = setDesignEnteringWaterTemperature(51.67);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirTemperature(35.0);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirWetbulbTemperature(25.6);
    OS_ASSERT(ok);
    ok = setDesignWaterFlowRate(0.001388);
    OS_ASSERT(ok);
    ok = setHighFanSpeedAirFlowRate(9.911);
    OS_ASSERT(ok);
    autosizeHighFanSpeedFanPower();
    ok = setLowFanSpeedAirFlowRate(4.955);
    OS_ASSERT(ok);
    ok = setLowFanSpeedAirFlowRateSizingFactor(0.5);
    OS_ASSERT(ok);
    autosizeLowFanSpeedFanPower();
    ok = setLowFanSpeedFanPowerSizingFactor(0.16);
    OS_ASSERT(ok);
  }

  FluidCoolerTwoSpeed::FluidCoolerTwoSpeed(std::shared_ptr<detail::FluidCoolerTwoSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FluidCoolerTwoSpeed::iddObjectType() {
    return IddObjectType::FluidCooler_TwoSpeed;
  }

  std::vector<std::string> FluidCoolerTwoSpeed::performanceInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod);
  }

  boost::optional<Node> FluidCoolerTwoSpeed::outdoorAirInletNode() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->outdoorAirInletNode();
  }

  bool FluidCoolerTwoSpeed::setOutdoorAirInletNode(const Node& node) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setOutdoorAirInletNode(node);
  }

  void FluidCoolerTwoSpeed::resetOutdoorAirInletNode() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->resetOutdoorAirInletNode();
  }

  std::string FluidCoolerTwoSpeed::performanceInputMethod() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->performanceInputMethod();
  }

  bool FluidCoolerTwoSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
  }

  boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedUfactorTimesAreaValue();
  }

  bool FluidCoolerTwoSpeed::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedUfactorTimesAreaValueAutosized();
  }

  bool FluidCoolerTwoSpeed::setHighFanSpeedUfactorTimesAreaValue(double highFanSpeedUfactorTimesAreaValue) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedUfactorTimesAreaValue(highFanSpeedUfactorTimesAreaValue);
  }

  void FluidCoolerTwoSpeed::autosizeHighFanSpeedUfactorTimesAreaValue() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedUfactorTimesAreaValue();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedUfactorTimesAreaValue();
  }

  boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedUfactorTimesAreaValue();
  }

  bool FluidCoolerTwoSpeed::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedUfactorTimesAreaValueAutosized();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedUfactorTimesAreaValue(double lowFanSpeedUfactorTimesAreaValue) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUfactorTimesAreaValue(lowFanSpeedUfactorTimesAreaValue);
  }

  void FluidCoolerTwoSpeed::autosizeLowFanSpeedUfactorTimesAreaValue() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedUfactorTimesAreaValue();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedUfactorTimesAreaValue();
  }

  double FluidCoolerTwoSpeed::lowFanSpeedUFactorTimesAreaSizingFactor() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedUFactorTimesAreaSizingFactor();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedUFactorTimesAreaSizingFactor(lowFanSpeedUFactorTimesAreaSizingFactor);
  }

  double FluidCoolerTwoSpeed::highSpeedNominalCapacity() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highSpeedNominalCapacity();
  }

  bool FluidCoolerTwoSpeed::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighSpeedNominalCapacity(highSpeedNominalCapacity);
  }

  boost::optional<double> FluidCoolerTwoSpeed::lowSpeedNominalCapacity() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowSpeedNominalCapacity();
  }

  bool FluidCoolerTwoSpeed::isLowSpeedNominalCapacityAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowSpeedNominalCapacityAutosized();
  }

  bool FluidCoolerTwoSpeed::setLowSpeedNominalCapacity(double lowSpeedNominalCapacity) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowSpeedNominalCapacity(lowSpeedNominalCapacity);
  }

  void FluidCoolerTwoSpeed::autosizeLowSpeedNominalCapacity() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowSpeedNominalCapacity();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedLowSpeedNominalCapacity() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowSpeedNominalCapacity();
  }

  double FluidCoolerTwoSpeed::lowSpeedNominalCapacitySizingFactor() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowSpeedNominalCapacitySizingFactor();
  }

  bool FluidCoolerTwoSpeed::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowSpeedNominalCapacitySizingFactor(lowSpeedNominalCapacitySizingFactor);
  }

  double FluidCoolerTwoSpeed::designEnteringWaterTemperature() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringWaterTemperature();
  }

  bool FluidCoolerTwoSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
  }

  double FluidCoolerTwoSpeed::designEnteringAirTemperature() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringAirTemperature();
  }

  bool FluidCoolerTwoSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
  }

  double FluidCoolerTwoSpeed::designEnteringAirWetbulbTemperature() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designEnteringAirWetbulbTemperature();
  }

  bool FluidCoolerTwoSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
  }

  boost::optional<double> FluidCoolerTwoSpeed::designWaterFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->designWaterFlowRate();
  }

  bool FluidCoolerTwoSpeed::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool FluidCoolerTwoSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void FluidCoolerTwoSpeed::autosizeDesignWaterFlowRate() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedDesignWaterFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedAirFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedAirFlowRate();
  }

  bool FluidCoolerTwoSpeed::isHighFanSpeedAirFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedAirFlowRateAutosized();
  }

  bool FluidCoolerTwoSpeed::setHighFanSpeedAirFlowRate(double highFanSpeedAirFlowRate) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedAirFlowRate(highFanSpeedAirFlowRate);
  }

  void FluidCoolerTwoSpeed::autosizeHighFanSpeedAirFlowRate() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedAirFlowRate();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedAirFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedAirFlowRate();
  }

  boost::optional<double> FluidCoolerTwoSpeed::highFanSpeedFanPower() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->highFanSpeedFanPower();
  }

  bool FluidCoolerTwoSpeed::isHighFanSpeedFanPowerAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isHighFanSpeedFanPowerAutosized();
  }

  bool FluidCoolerTwoSpeed::setHighFanSpeedFanPower(double highFanSpeedFanPower) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setHighFanSpeedFanPower(highFanSpeedFanPower);
  }

  void FluidCoolerTwoSpeed::autosizeHighFanSpeedFanPower() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeHighFanSpeedFanPower();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedHighFanSpeedFanPower() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedHighFanSpeedFanPower();
  }

  boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedAirFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRate();
  }

  bool FluidCoolerTwoSpeed::isLowFanSpeedAirFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedAirFlowRateAutosized();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedAirFlowRate(double lowFanSpeedAirFlowRate) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRate(lowFanSpeedAirFlowRate);
  }

  void FluidCoolerTwoSpeed::autosizeLowFanSpeedAirFlowRate() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedAirFlowRate();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedAirFlowRate() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedAirFlowRate();
  }

  double FluidCoolerTwoSpeed::lowFanSpeedAirFlowRateSizingFactor() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedAirFlowRateSizingFactor();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedAirFlowRateSizingFactor(lowFanSpeedAirFlowRateSizingFactor);
  }

  boost::optional<double> FluidCoolerTwoSpeed::lowFanSpeedFanPower() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPower();
  }

  bool FluidCoolerTwoSpeed::isLowFanSpeedFanPowerAutosized() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->isLowFanSpeedFanPowerAutosized();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedFanPower(double lowFanSpeedFanPower) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPower(lowFanSpeedFanPower);
  }

  void FluidCoolerTwoSpeed::autosizeLowFanSpeedFanPower() {
    getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizeLowFanSpeedFanPower();
  }

  boost::optional<double> FluidCoolerTwoSpeed::autosizedLowFanSpeedFanPower() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->autosizedLowFanSpeedFanPower();
  }

  double FluidCoolerTwoSpeed::lowFanSpeedFanPowerSizingFactor() const {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->lowFanSpeedFanPowerSizingFactor();
  }

  bool FluidCoolerTwoSpeed::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
    return getImpl<detail::FluidCoolerTwoSpeed_Impl>()->setLowFanSpeedFanPowerSizingFactor(lowFanSpeedFanPowerSizingFactor);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FluidCoolerTwoSpeed_Impl::inletPort() const {
      return openstudio::FluidCooler_TwoSpeedFields::WaterInletNodeName;
    }

    unsigned FluidCoolerTwoSpeed_Impl::outletPort() const {
      return openstudio::FluidCooler_TwoSpeedFields::WaterOutletNodeName;
    }

    bool FluidCoolerTwoSpeed_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<Node> FluidCoolerTwoSpeed_Impl::outdoorAirInletNode() const {
      constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      if (!managedValue || managedValue->empty()) {
        return boost::none;
      }
      const auto targetHandle = openstudio::toUUID(*managedValue);
      if (targetHandle.isNull()) {
        return boost::none;
      }
      return model().getModelObject<Node>(targetHandle);
    }

    bool FluidCoolerTwoSpeed_Impl::setOutdoorAirInletNode(const Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.FluidCoolerTwoSpeed",
                 "Cannot set the outdoor air inlet Node because the Node belongs to a different model.");
        return false;
      }

      constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
      const auto previousRaw = openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
      const auto previousNode = outdoorAirInletNode();
      const auto previousName = previousNode ? previousNode->nameString() : previousRaw;
      if (!setPointer(field, node.handle(), false)) {
        return false;
      }
      if (maintainOutdoorAirInletNode(previousName)) {
        return true;
      }

      const bool restored =
        previousNode ? setPointer(field, previousNode->handle(), false)
                     : (setPointer(field, openstudio::Handle(), false) && openstudio::detail::IdfObject_Impl::setString(field, previousRaw, false));
      if (!restored) {
        LOG_FREE(Error, "openstudio.epmodel.FluidCoolerTwoSpeed",
                 "Failed to restore the previous outdoor air inlet Node after declaration maintenance failed.");
      }
      removeUnusedOutdoorAirInletNode(node.nameString());
      return false;
    }

    void FluidCoolerTwoSpeed_Impl::resetOutdoorAirInletNode() {
      constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
      const auto previousRaw = openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
      const auto previousNode = outdoorAirInletNode();
      const auto previousName = previousNode ? previousNode->nameString() : previousRaw;
      if (setPointer(field, openstudio::Handle(), false) && openstudio::detail::IdfObject_Impl::setString(field, "", false)) {
        removeUnusedOutdoorAirInletNode(previousName);
        return;
      }

      const bool restored =
        previousNode ? setPointer(field, previousNode->handle(), false)
                     : (setPointer(field, openstudio::Handle(), false) && openstudio::detail::IdfObject_Impl::setString(field, previousRaw, false));
      if (!restored) {
        LOG_FREE(Error, "openstudio.epmodel.FluidCoolerTwoSpeed", "Failed to restore the outdoor air inlet Node after reset failed.");
      }
    }

    bool FluidCoolerTwoSpeed_Impl::maintainOutdoorAirInletNode(const std::string& previousNodeName) {
      const auto currentNode = outdoorAirInletNode();
      if (!currentNode) {
        return false;
      }
      const auto currentNodeName = currentNode->nameString();

      const auto directDeclarations = model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node);
      const bool declaredByOutdoorAirNode =
        std::ranges::any_of(directDeclarations, [&](const auto& object) { return openstudio::istringEqual(object.nameString(), currentNodeName); });

      bool declaredAsOutdoorAir = declaredByOutdoorAirNode;
      if (declaredByOutdoorAirNode) {
        removeOutdoorAirNodeListEntries(currentNodeName);
      } else {
        for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
          for (const auto& group : object.extensibleGroups()) {
            const auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
            if (!workspaceGroup) {
              continue;
            }
            const auto nodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
            if (nodeName && openstudio::istringEqual(*nodeName, currentNodeName)) {
              declaredAsOutdoorAir = true;
              break;
            }
          }
          if (declaredAsOutdoorAir) {
            break;
          }
        }
      }

      if (!declaredAsOutdoorAir) {
        auto nodeList = ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model());
        auto group = nodeList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!(group && group->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, currentNodeName))) {
          nodeList.remove();
          return false;
        }
      }

      if (!previousNodeName.empty() && !openstudio::istringEqual(previousNodeName, currentNodeName)) {
        removeUnusedOutdoorAirInletNode(previousNodeName);
      }
      return true;
    }

    unsigned FluidCoolerTwoSpeed_Impl::removeOutdoorAirNodeListEntries(const std::string& nodeName) {
      unsigned removedEntries = 0;
      for (auto object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
        const auto groups = object.extensibleGroups();
        std::vector<unsigned> matchingGroups;
        for (const auto& group : groups) {
          const auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          if (!workspaceGroup) {
            continue;
          }
          const auto listedNodeName = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
          if (listedNodeName && openstudio::istringEqual(*listedNodeName, nodeName)) {
            matchingGroups.push_back(workspaceGroup->groupIndex());
          }
        }

        removedEntries += static_cast<unsigned>(matchingGroups.size());
        if (!matchingGroups.empty() && (matchingGroups.size() == groups.size())) {
          object.remove();
          continue;
        }
        for (auto it = matchingGroups.rbegin(); it != matchingGroups.rend(); ++it) {
          object.eraseExtensibleGroup(*it);
        }
      }
      return removedEntries;
    }

    void FluidCoolerTwoSpeed_Impl::removeUnusedOutdoorAirInletNode(const std::string& nodeName) {
      if (nodeName.empty()) {
        return;
      }

      constexpr auto ownerField = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
      for (const auto& object : model().objects()) {
        if (object.iddObject().type() == openstudio::IddObjectType::OutdoorAir_NodeList) {
          continue;
        }
        for (unsigned fieldIndex = 0; fieldIndex < object.numFields(); ++fieldIndex) {
          if ((object.handle() == handle()) && (fieldIndex == ownerField)) {
            continue;
          }
          const auto iddField = object.iddObject().getField(fieldIndex);
          if (!(iddField && (iddField->properties().type == openstudio::IddFieldType::NodeType))) {
            continue;
          }
          const auto fieldValue = object.getString(fieldIndex);
          if (fieldValue && openstudio::istringEqual(*fieldValue, nodeName)) {
            return;
          }
        }
      }

      removeOutdoorAirNodeListEntries(nodeName);
    }

    void FluidCoolerTwoSpeed_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      constexpr auto field = openstudio::FluidCooler_TwoSpeedFields::OutdoorAirInletNodeName;
      const auto rawNodeName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
      auto node = outdoorAirInletNode();
      if (!node && !(rawNodeName && !rawNodeName->empty())) {
        return;
      }

      if (!node) {
        node = resolvedNodeTarget(field);
      }
      if (!node) {
        detail::addLoadWarning(context, "Preserved unresolved outdoor air inlet Node reference '" + rawNodeName.value_or("")
                                          + "' for two-speed fluid cooler '" + getObject<ModelObject>().nameString() + "'.");
        return;
      }
      const auto nodeName = node->nameString();

      bool hasDirectDeclaration = false;
      bool hasNodeListDeclaration = false;
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node)) {
        if (openstudio::istringEqual(object.nameString(), nodeName)) {
          hasDirectDeclaration = true;
          break;
        }
      }
      for (const auto& object : model().getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
        for (const auto& group : object.extensibleGroups()) {
          const auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
          const auto listedNodeName = workspaceGroup ? workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName)
                                                     : boost::optional<std::string>();
          if (listedNodeName && openstudio::istringEqual(*listedNodeName, nodeName)) {
            hasNodeListDeclaration = true;
            break;
          }
        }
        if (hasNodeListDeclaration) {
          break;
        }
      }
      const bool needsRepair = hasDirectDeclaration ? hasNodeListDeclaration : !hasNodeListDeclaration;

      if (!maintainOutdoorAirInletNode()) {
        detail::addLoadError(context, "Failed to maintain the outdoor-air declaration for two-speed fluid cooler '"
                                        + getObject<ModelObject>().nameString() + "'.");
      } else if (needsRepair) {
        detail::addLoadInfo(context,
                            "Repaired the outdoor-air declaration for two-speed fluid cooler '" + getObject<ModelObject>().nameString() + "'.");
      }
    }

    std::vector<IdfObject> FluidCoolerTwoSpeed_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }
      const auto outdoorAirNode = outdoorAirInletNode();
      const auto nodeName = outdoorAirNode ? outdoorAirNode->nameString() : std::string{};
      removeUnusedOutdoorAirInletNode(nodeName);
      return StraightComponent_Impl::remove();
    }

    std::vector<std::string> FluidCoolerTwoSpeed_Impl::performanceInputMethodValues() const {
      return FluidCoolerTwoSpeed::performanceInputMethodValues();
    }

    std::string FluidCoolerTwoSpeed_Impl::performanceInputMethod() const {
      const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedUfactorTimesAreaValue() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedUfactorTimesAreaValueAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedUfactorTimesAreaValue() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedUfactorTimesAreaValueAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FluidCoolerTwoSpeed_Impl::lowFanSpeedUFactorTimesAreaSizingFactor() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    double FluidCoolerTwoSpeed_Impl::highSpeedNominalCapacity() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::HighSpeedNominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::lowSpeedNominalCapacity() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isLowSpeedNominalCapacityAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FluidCoolerTwoSpeed_Impl::lowSpeedNominalCapacitySizingFactor() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    double FluidCoolerTwoSpeed_Impl::designEnteringWaterTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double FluidCoolerTwoSpeed_Impl::designEnteringAirTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    double FluidCoolerTwoSpeed_Impl::designEnteringAirWetbulbTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isDesignWaterFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedAirFlowRate() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::highFanSpeedFanPower() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isHighFanSpeedFanPowerAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRate() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FluidCoolerTwoSpeed_Impl::lowFanSpeedAirFlowRateSizingFactor() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::lowFanSpeedFanPower() const {
      return getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true);
    }

    bool FluidCoolerTwoSpeed_Impl::isLowFanSpeedFanPowerAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FluidCoolerTwoSpeed_Impl::lowFanSpeedFanPowerSizingFactor() const {
      const auto value = getDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerTwoSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
      return setString(openstudio::FluidCooler_TwoSpeedFields::PerformanceInputMethod, performanceInputMethod);
    }

    bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedUfactorTimesAreaValue(boost::optional<double> highFanSpeedUfactorTimesAreaValue) {
      bool result = false;
      if (highFanSpeedUfactorTimesAreaValue) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, *highFanSpeedUfactorTimesAreaValue);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedUfactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedUfactorTimesAreaValue, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedUfactorTimesAreaValue(boost::optional<double> lowFanSpeedUfactorTimesAreaValue) {
      bool result = false;
      if (lowFanSpeedUfactorTimesAreaValue) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, *lowFanSpeedUfactorTimesAreaValue);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedUfactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUfactorTimesAreaValue, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedUFactorTimesAreaSizingFactor(double lowFanSpeedUFactorTimesAreaSizingFactor) {
      const bool result =
        setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedUFactorTimesAreaSizingFactor, lowFanSpeedUFactorTimesAreaSizingFactor);
      OS_ASSERT(result);
      return result;
    }

    bool FluidCoolerTwoSpeed_Impl::setHighSpeedNominalCapacity(double highSpeedNominalCapacity) {
      return setDouble(openstudio::FluidCooler_TwoSpeedFields::HighSpeedNominalCapacity, highSpeedNominalCapacity);
    }

    bool FluidCoolerTwoSpeed_Impl::setLowSpeedNominalCapacity(boost::optional<double> lowSpeedNominalCapacity) {
      bool result = false;
      if (lowSpeedNominalCapacity) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, *lowSpeedNominalCapacity);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeLowSpeedNominalCapacity() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacity, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowSpeedNominalCapacitySizingFactor(double lowSpeedNominalCapacitySizingFactor) {
      const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowSpeedNominalCapacitySizingFactor, lowSpeedNominalCapacitySizingFactor);
      OS_ASSERT(result);
      return result;
    }

    bool FluidCoolerTwoSpeed_Impl::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
      return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringWaterTemperature, designEnteringWaterTemperature);
    }

    bool FluidCoolerTwoSpeed_Impl::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
      return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirTemperature, designEnteringAirTemperature);
    }

    bool FluidCoolerTwoSpeed_Impl::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
      return setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignEnteringAirWetbulbTemperature, designEnteringAirWetbulbTemperature);
    }

    bool FluidCoolerTwoSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
      bool result = false;
      if (designWaterFlowRate) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::DesignWaterFlowRate, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedAirFlowRate(boost::optional<double> highFanSpeedAirFlowRate) {
      bool result = false;
      if (highFanSpeedAirFlowRate) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, *highFanSpeedAirFlowRate);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedAirFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedAirFlowRate, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setHighFanSpeedFanPower(boost::optional<double> highFanSpeedFanPower) {
      bool result = false;
      if (highFanSpeedFanPower) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, *highFanSpeedFanPower);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeHighFanSpeedFanPower() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::HighFanSpeedFanPower, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRate(boost::optional<double> lowFanSpeedAirFlowRate) {
      bool result = false;
      if (lowFanSpeedAirFlowRate) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, *lowFanSpeedAirFlowRate);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedAirFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRate, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedAirFlowRateSizingFactor(double lowFanSpeedAirFlowRateSizingFactor) {
      const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedAirFlowRateSizingFactor, lowFanSpeedAirFlowRateSizingFactor);
      OS_ASSERT(result);
      return result;
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPower(boost::optional<double> lowFanSpeedFanPower) {
      bool result = false;
      if (lowFanSpeedFanPower) {
        result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, *lowFanSpeedFanPower);
      }
      return result;
    }

    void FluidCoolerTwoSpeed_Impl::autosizeLowFanSpeedFanPower() {
      OS_ASSERT(setString(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPower, "Autosize"));
    }

    bool FluidCoolerTwoSpeed_Impl::setLowFanSpeedFanPowerSizingFactor(double lowFanSpeedFanPowerSizingFactor) {
      const bool result = setDouble(openstudio::FluidCooler_TwoSpeedFields::LowFanSpeedFanPowerSizingFactor, lowFanSpeedFanPowerSizingFactor);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedUfactorTimesAreaValue() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedUfactorTimesAreaValue() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowSpeedNominalCapacity() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedDesignWaterFlowRate() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedHighFanSpeedFanPower() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> FluidCoolerTwoSpeed_Impl::autosizedLowFanSpeedFanPower() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
