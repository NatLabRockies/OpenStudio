/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Loop/PlantLoop.hpp"
#include "StraightComponent/Node.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/IdfObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <set>

namespace openstudio {
namespace epmodel {

  AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(const Model& model)
    : StraightComponent(AirConditionerVariableRefrigerantFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->ensureTerminalUnitList());
  }

  AirConditionerVariableRefrigerantFlow::AirConditionerVariableRefrigerantFlow(
    std::shared_ptr<detail::AirConditionerVariableRefrigerantFlow_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirConditionerVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::AirConditioner_VariableRefrigerantFlow;
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues() {
    return {"WetBulbTemperature", "DryBulbTemperature"};
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::defrostStrategyValues() {
    return {"ReverseCycle", "Resistive"};
  }

  std::vector<std::string> AirConditionerVariableRefrigerantFlow::condenserTypeValues() {
    return {"AirCooled", "EvaporativelyCooled", "WaterCooled"};
  }

  bool AirConditionerVariableRefrigerantFlow::addToNode(Node& node) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->addToNode(node);
  }

  bool AirConditionerVariableRefrigerantFlow::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->addTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlow::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->removeTerminal(terminal);
  }

  void AirConditionerVariableRefrigerantFlow::removeAllTerminals() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->removeAllTerminals();
  }

  std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlow::terminals() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->terminals();
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedTotalCoolingCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedTotalCoolingCapacity();
  }

  bool AirConditionerVariableRefrigerantFlow::isGrossRatedTotalCoolingCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedTotalCoolingCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedTotalCoolingCapacity(grossRatedTotalCoolingCapacity);
  }

  void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedTotalCoolingCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedTotalCoolingCapacity();
  }

  double AirConditionerVariableRefrigerantFlow::grossRatedCoolingCOP() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedCoolingCOP();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedCoolingCOP(grossRatedCoolingCOP);
  }

  boost::optional<double> AirConditionerVariableRefrigerantFlow::grossRatedHeatingCapacity() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->grossRatedHeatingCapacity();
  }

  bool AirConditionerVariableRefrigerantFlow::isGrossRatedHeatingCapacityAutosized() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isGrossRatedHeatingCapacityAutosized();
  }

  bool AirConditionerVariableRefrigerantFlow::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setGrossRatedHeatingCapacity(grossRatedHeatingCapacity);
  }

  void AirConditionerVariableRefrigerantFlow::autosizeGrossRatedHeatingCapacity() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->autosizeGrossRatedHeatingCapacity();
  }

  double AirConditionerVariableRefrigerantFlow::ratedHeatingCapacitySizingRatio() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->ratedHeatingCapacitySizingRatio();
  }

  bool AirConditionerVariableRefrigerantFlow::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setRatedHeatingCapacitySizingRatio(ratedHeatingCapacitySizingRatio);
  }

  std::string AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatingPerformanceCurveOutdoorTemperatureType();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatingPerformanceCurveOutdoorTemperatureType(
    const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatingPerformanceCurveOutdoorTemperatureType(
      heatingPerformanceCurveOutdoorTemperatureType);
  }

  bool AirConditionerVariableRefrigerantFlow::heatPumpWasteHeatRecovery() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->heatPumpWasteHeatRecovery();
  }

  bool AirConditionerVariableRefrigerantFlow::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setHeatPumpWasteHeatRecovery(heatPumpWasteHeatRecovery);
  }

  int AirConditionerVariableRefrigerantFlow::numberofCompressors() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->numberofCompressors();
  }

  bool AirConditionerVariableRefrigerantFlow::setNumberofCompressors(int numberofCompressors) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setNumberofCompressors(numberofCompressors);
  }

  std::string AirConditionerVariableRefrigerantFlow::defrostStrategy() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->defrostStrategy();
  }

  bool AirConditionerVariableRefrigerantFlow::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  std::string AirConditionerVariableRefrigerantFlow::condenserType() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->condenserType();
  }

  bool AirConditionerVariableRefrigerantFlow::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->setCondenserType(condenserType);
  }

  bool AirConditionerVariableRefrigerantFlow::isCondenserTypeDefaulted() const {
    return getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->isCondenserTypeDefaulted();
  }

  void AirConditionerVariableRefrigerantFlow::resetCondenserType() {
    getImpl<detail::AirConditionerVariableRefrigerantFlow_Impl>()->resetCondenserType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlow_Impl::terminalUnitList() const {
      auto list = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
      if (list && list->iddObject().type() == openstudio::IddObjectType::ZoneTerminalUnitList) {
        return list;
      }
      return boost::none;
    }

    boost::optional<ModelObject> AirConditionerVariableRefrigerantFlow_Impl::ensureTerminalUnitList() {
      if (auto list = terminalUnitList()) {
        return list;
      }

      auto owner = getObject<ModelObject>();
      if (!owner.name()) {
        owner.createName();
      }
      if (!owner.name()) {
        return boost::none;
      }

      IdfObject listIdfObject(openstudio::IddObjectType::ZoneTerminalUnitList);
      if (!listIdfObject.setName(model().nextName(openstudio::IddObjectType::ZoneTerminalUnitList, true))) {
        return boost::none;
      }
      auto addedObject = model().addObject(listIdfObject);
      if (!addedObject) {
        return boost::none;
      }
      auto list = addedObject->optionalCast<ModelObject>();
      if (!list) {
        addedObject->remove();
        return boost::none;
      }
      if (!setPointer(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName, list->handle(), false)) {
        list->remove();
        return boost::none;
      }
      return list;
    }

    std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> AirConditionerVariableRefrigerantFlow_Impl::terminals() const {
      std::vector<ZoneHVACTerminalUnitVariableRefrigerantFlow> result;
      auto list = terminalUnitList();
      if (!list) {
        return result;
      }

      std::set<Handle> seen;
      for (const auto& group : list->extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
        if (!target) {
          continue;
        }
        auto terminal = target->optionalCast<ZoneHVACTerminalUnitVariableRefrigerantFlow>();
        if (terminal && seen.insert(terminal->handle()).second) {
          result.push_back(*terminal);
        }
      }
      return result;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::addTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
      if (terminal.model() != model()) {
        return false;
      }
      auto terminalImpl = terminal.getImpl<ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>();
      OS_ASSERT(terminalImpl);
      if (terminalImpl->isFluidTemperatureControl()) {
        return false;
      }

      if (auto currentSystem = terminal.vrfSystem()) {
        if (currentSystem->handle() != handle()) {
          return false;
        }
        return true;
      }

      auto list = ensureTerminalUnitList();
      if (!list) {
        return false;
      }
      auto group = list->pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!group) {
        return false;
      }
      if (!group->setPointer(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName, terminal.handle())) {
        list->eraseExtensibleGroup(static_cast<unsigned>(list->extensibleGroups().size() - 1u));
        return false;
      }
      return true;
    }

    void AirConditionerVariableRefrigerantFlow_Impl::removeTerminal(ZoneHVACTerminalUnitVariableRefrigerantFlow& terminal) {
      auto list = terminalUnitList();
      if (!list) {
        return;
      }
      auto groups = list->extensibleGroups();
      for (unsigned i = static_cast<unsigned>(groups.size()); i > 0u; --i) {
        const auto index = i - 1u;
        auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
        if (target && target->handle() == terminal.handle()) {
          list->eraseExtensibleGroup(index);
        }
      }
    }

    void AirConditionerVariableRefrigerantFlow_Impl::removeAllTerminals() {
      auto list = terminalUnitList();
      if (!list) {
        return;
      }
      while (!list->extensibleGroups().empty()) {
        list->eraseExtensibleGroup(static_cast<unsigned>(list->extensibleGroups().size() - 1u));
      }
    }

    std::vector<IdfObject> AirConditionerVariableRefrigerantFlow_Impl::remove() {
      auto list = terminalUnitList();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<IdfObject> result;
      if (list) {
        auto removedList = list->remove();
        result.insert(result.end(), removedList.begin(), removedList.end());
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedTotalCoolingCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedTotalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedTotalCoolingCapacity(double grossRatedTotalCoolingCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, grossRatedTotalCoolingCapacity);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedTotalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::grossRatedCoolingCOP() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedCoolingCOP(double grossRatedCoolingCOP) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, grossRatedCoolingCOP);
    }

    boost::optional<double> AirConditionerVariableRefrigerantFlow_Impl::grossRatedHeatingCapacity() const {
      return getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isGrossRatedHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setGrossRatedHeatingCapacity(double grossRatedHeatingCapacity) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, grossRatedHeatingCapacity);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::autosizeGrossRatedHeatingCapacity() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "autosize"));
    }

    double AirConditionerVariableRefrigerantFlow_Impl::ratedHeatingCapacitySizingRatio() const {
      const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setRatedHeatingCapacitySizingRatio(double ratedHeatingCapacitySizingRatio) {
      return setDouble(openstudio::AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, ratedHeatingCapacitySizingRatio);
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureType() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatingPerformanceCurveOutdoorTemperatureType(
      const std::string& heatingPerformanceCurveOutdoorTemperatureType) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType,
                       heatingPerformanceCurveOutdoorTemperatureType);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::heatPumpWasteHeatRecovery() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setHeatPumpWasteHeatRecovery(bool heatPumpWasteHeatRecovery) {
      const bool result =
        setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, heatPumpWasteHeatRecovery ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    int AirConditionerVariableRefrigerantFlow_Impl::numberofCompressors() const {
      const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setNumberofCompressors(int numberofCompressors) {
      return setInt(openstudio::AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, numberofCompressors);
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, defrostStrategy);
    }

    std::string AirConditionerVariableRefrigerantFlow_Impl::condenserType() const {
      if (!isCondenserTypeDefaulted()) {
        if (auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, false)) {
          return *value;
        }
      }
      return plantLoop() ? "WaterCooled" : "AirCooled";
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, condenserType);
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType);
    }

    void AirConditionerVariableRefrigerantFlow_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserType, ""));
    }

    bool AirConditionerVariableRefrigerantFlow_Impl::addToNode(Node& node) {
      auto plantLoop_ = node.plantLoop();
      if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::heatingPerformanceCurveOutdoorTemperatureTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::defrostStrategyValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
    }

    std::vector<std::string> AirConditionerVariableRefrigerantFlow_Impl::condenserTypeValues() const {
      return openstudio::epmodel::AirConditionerVariableRefrigerantFlow::condenserTypeValues();
    }

    unsigned AirConditionerVariableRefrigerantFlow_Impl::inletPort() const {
      return openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserInletNodeName;
    }

    unsigned AirConditionerVariableRefrigerantFlow_Impl::outletPort() const {
      return openstudio::AirConditioner_VariableRefrigerantFlowFields::CondenserOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
