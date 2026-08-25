/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FluidCoolerSingleSpeed.hpp"
#include "StraightComponent/FluidCoolerSingleSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/FluidCooler_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  FluidCoolerSingleSpeed::FluidCoolerSingleSpeed(const Model& model) : StraightComponent(FluidCoolerSingleSpeed::iddObjectType(), model) {
    bool ok = true;
    ok = setPerformanceInputMethod("NominalCapacity");
    OS_ASSERT(ok);
    autosizeDesignAirFlowRateUfactorTimesAreaValue();
    ok = setNominalCapacity(58601.0);
    OS_ASSERT(ok);
    ok = setDesignEnteringWaterTemperature(51.67);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirTemperature(35.0);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirWetbulbTemperature(25.6);
    OS_ASSERT(ok);
    ok = setDesignWaterFlowRate(0.001388);
    OS_ASSERT(ok);
    ok = setDesignAirFlowRate(9.911);
    OS_ASSERT(ok);
    autosizeDesignAirFlowRateFanPower();
  }

  FluidCoolerSingleSpeed::FluidCoolerSingleSpeed(std::shared_ptr<detail::FluidCoolerSingleSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FluidCoolerSingleSpeed::iddObjectType() {
    return IddObjectType::FluidCooler_SingleSpeed;
  }

  std::vector<std::string> FluidCoolerSingleSpeed::performanceInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod);
  }

  boost::optional<Node> FluidCoolerSingleSpeed::outdoorAirInletNode() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->outdoorAirInletNode();
  }

  bool FluidCoolerSingleSpeed::setOutdoorAirInletNode(const Node& node) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setOutdoorAirInletNode(node);
  }

  void FluidCoolerSingleSpeed::resetOutdoorAirInletNode() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->resetOutdoorAirInletNode();
  }

  std::string FluidCoolerSingleSpeed::performanceInputMethod() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->performanceInputMethod();
  }

  bool FluidCoolerSingleSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRateUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRateUfactorTimesAreaValue();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateUfactorTimesAreaValueAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateUfactorTimesAreaValueAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRateUfactorTimesAreaValue(double designAirFlowRateUfactorTimesAreaValue) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRateUfactorTimesAreaValue(designAirFlowRateUfactorTimesAreaValue);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRateUfactorTimesAreaValue() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRateUfactorTimesAreaValue();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRateUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRateUfactorTimesAreaValue();
  }

  double FluidCoolerSingleSpeed::nominalCapacity() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->nominalCapacity();
  }

  bool FluidCoolerSingleSpeed::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setNominalCapacity(nominalCapacity);
  }

  double FluidCoolerSingleSpeed::designEnteringWaterTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringWaterTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
  }

  double FluidCoolerSingleSpeed::designEnteringAirTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringAirTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
  }

  double FluidCoolerSingleSpeed::designEnteringAirWetbulbTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringAirWetbulbTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
  }

  boost::optional<double> FluidCoolerSingleSpeed::designWaterFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designWaterFlowRate();
  }

  bool FluidCoolerSingleSpeed::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void FluidCoolerSingleSpeed::autosizeDesignWaterFlowRate() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignWaterFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRate();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRate(double designAirFlowRate) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRate(designAirFlowRate);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRate() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRateFanPower() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRateFanPower();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateFanPowerAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateFanPowerAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRateFanPower(double designAirFlowRateFanPower) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRateFanPower(designAirFlowRateFanPower);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRateFanPower() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRateFanPower();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRateFanPower() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRateFanPower();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FluidCoolerSingleSpeed_Impl::inletPort() const {
      return openstudio::FluidCooler_SingleSpeedFields::WaterInletNodeName;
    }

    unsigned FluidCoolerSingleSpeed_Impl::outletPort() const {
      return openstudio::FluidCooler_SingleSpeedFields::WaterOutletNodeName;
    }

    bool FluidCoolerSingleSpeed_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    boost::optional<Node> FluidCoolerSingleSpeed_Impl::outdoorAirInletNode() const {
      constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
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

    bool FluidCoolerSingleSpeed_Impl::setOutdoorAirInletNode(const Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.FluidCoolerSingleSpeed",
                 "Cannot set the outdoor air inlet Node because the Node belongs to a different model.");
        return false;
      }

      constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
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
        LOG_FREE(Error, "openstudio.epmodel.FluidCoolerSingleSpeed",
                 "Failed to restore the previous outdoor air inlet Node after declaration maintenance failed.");
      }
      removeUnusedOutdoorAirInletNode(node.nameString());
      return false;
    }

    void FluidCoolerSingleSpeed_Impl::resetOutdoorAirInletNode() {
      constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
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
        LOG_FREE(Error, "openstudio.epmodel.FluidCoolerSingleSpeed", "Failed to restore the outdoor air inlet Node after reset failed.");
      }
    }

    bool FluidCoolerSingleSpeed_Impl::maintainOutdoorAirInletNode(const std::string& previousNodeName) {
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

    unsigned FluidCoolerSingleSpeed_Impl::removeOutdoorAirNodeListEntries(const std::string& nodeName) {
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

    void FluidCoolerSingleSpeed_Impl::removeUnusedOutdoorAirInletNode(const std::string& nodeName) {
      if (nodeName.empty()) {
        return;
      }

      constexpr auto ownerField = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
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

    void FluidCoolerSingleSpeed_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      constexpr auto field = openstudio::FluidCooler_SingleSpeedFields::OutdoorAirInletNodeName;
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
                                          + "' for single-speed fluid cooler '" + getObject<ModelObject>().nameString() + "'.");
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
        detail::addLoadError(context, "Failed to maintain the outdoor-air declaration for single-speed fluid cooler '"
                                        + getObject<ModelObject>().nameString() + "'.");
      } else if (needsRepair) {
        detail::addLoadInfo(context,
                            "Repaired the outdoor-air declaration for single-speed fluid cooler '" + getObject<ModelObject>().nameString() + "'.");
      }
    }

    std::vector<IdfObject> FluidCoolerSingleSpeed_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }
      const auto outdoorAirNode = outdoorAirInletNode();
      const auto nodeName = outdoorAirNode ? outdoorAirNode->nameString() : std::string{};
      removeUnusedOutdoorAirInletNode(nodeName);
      return StraightComponent_Impl::remove();
    }

    std::vector<std::string> FluidCoolerSingleSpeed_Impl::performanceInputMethodValues() const {
      return FluidCoolerSingleSpeed::performanceInputMethodValues();
    }

    std::string FluidCoolerSingleSpeed_Impl::performanceInputMethod() const {
      const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
      return setString(openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod, performanceInputMethod);
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRateUfactorTimesAreaValue() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateUfactorTimesAreaValueAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRateUfactorTimesAreaValue(boost::optional<double> designAirFlowRateUfactorTimesAreaValue) {
      bool result = false;
      if (designAirFlowRateUfactorTimesAreaValue) {
        result =
          setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, *designAirFlowRateUfactorTimesAreaValue);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRateUfactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRateUfactorTimesAreaValue() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    double FluidCoolerSingleSpeed_Impl::nominalCapacity() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::NominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::FluidCooler_SingleSpeedFields::NominalCapacity, nominalCapacity);
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringWaterTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature) {
      bool result = false;
      if (designEnteringWaterTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, *designEnteringWaterTemperature);
      }
      return result;
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringAirTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature) {
      bool result = false;
      if (designEnteringAirTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, *designEnteringAirTemperature);
      }
      return result;
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringAirWetbulbTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature) {
      bool result = false;
      if (designEnteringAirWetbulbTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, *designEnteringAirWetbulbTemperature);
      }
      return result;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignWaterFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
      bool result = false;
      if (designWaterFlowRate) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignWaterFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRate() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRate(boost::optional<double> designAirFlowRate) {
      bool result = false;
      if (designAirFlowRate) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, *designAirFlowRate);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRateFanPower() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateFanPowerAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRateFanPower(boost::optional<double> designAirFlowRateFanPower) {
      bool result = false;
      if (designAirFlowRateFanPower) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, *designAirFlowRateFanPower);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRateFanPower() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRateFanPower() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
