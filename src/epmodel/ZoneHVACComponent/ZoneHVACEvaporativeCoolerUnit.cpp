/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit.hpp"
#include "ZoneHVACComponent/ZoneHVACEvaporativeCoolerUnit_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "ModelObject/ModelObject_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/EvaporativeCoolerDirectResearchSpecial.hpp"
#include "StraightComponent/EvaporativeCoolerIndirectResearchSpecial.hpp"
#include "StraightComponent/FanComponentModel.hpp"
#include "StraightComponent/FanConstantVolume.hpp"
#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/FanSystemModel.hpp"
#include "StraightComponent/FanVariableVolume.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EvaporativeCoolerUnit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACEvaporativeCoolerUnit::ZoneHVACEvaporativeCoolerUnit(const Model& model)
    : ZoneHVACComponent(ZoneHVACEvaporativeCoolerUnit::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));

    FanSystemModel supplyAirFan(model);
    OS_ASSERT(setSupplyAirFan(supplyAirFan));

    autosizeDesignSupplyAirFlowRate();
    OS_ASSERT(setFanPlacement("BlowThrough"));
    OS_ASSERT(setCoolerUnitControlMethod("ZoneTemperatureDeadbandOnOffCycling"));
    OS_ASSERT(setThrottlingRangeTemperatureDifference(1.0));
    OS_ASSERT(setCoolingLoadControlThresholdHeatTransferRate(100.0));

    EvaporativeCoolerDirectResearchSpecial firstEvaporativeCooler(model);
    OS_ASSERT(setFirstEvaporativeCooler(firstEvaporativeCooler));

    OS_ASSERT(setShutOffRelativeHumidity(100.0));
  }

  ZoneHVACEvaporativeCoolerUnit::ZoneHVACEvaporativeCoolerUnit(std::shared_ptr<detail::ZoneHVACEvaporativeCoolerUnit_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACEvaporativeCoolerUnit::iddObjectType() {
    return IddObjectType::ZoneHVAC_EvaporativeCoolerUnit;
  }

  std::vector<std::string> ZoneHVACEvaporativeCoolerUnit::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACEvaporativeCoolerUnit::coolerUnitControlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod);
  }

  unsigned ZoneHVACEvaporativeCoolerUnit::inletPort() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->inletPort();
  }

  unsigned ZoneHVACEvaporativeCoolerUnit::outletPort() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->outletPort();
  }

  Schedule ZoneHVACEvaporativeCoolerUnit::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent ZoneHVACEvaporativeCoolerUnit::supplyAirFan() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->supplyAirFan();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setSupplyAirFan(const HVACComponent& hvacComponent) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setSupplyAirFan(hvacComponent);
  }

  boost::optional<double> ZoneHVACEvaporativeCoolerUnit::designSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->designSupplyAirFlowRate();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setDesignSupplyAirFlowRate(designSupplyAirFlowRate);
  }

  bool ZoneHVACEvaporativeCoolerUnit::isDesignSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->isDesignSupplyAirFlowRateAutosized();
  }

  void ZoneHVACEvaporativeCoolerUnit::autosizeDesignSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->autosizeDesignSupplyAirFlowRate();
  }

  std::string ZoneHVACEvaporativeCoolerUnit::fanPlacement() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->fanPlacement();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setFanPlacement(fanPlacement);
  }

  std::string ZoneHVACEvaporativeCoolerUnit::coolerUnitControlMethod() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->coolerUnitControlMethod();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setCoolerUnitControlMethod(coolerUnitControlMethod);
  }

  double ZoneHVACEvaporativeCoolerUnit::throttlingRangeTemperatureDifference() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->throttlingRangeTemperatureDifference();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setThrottlingRangeTemperatureDifference(throttlingRangeTemperatureDifference);
  }

  double ZoneHVACEvaporativeCoolerUnit::coolingLoadControlThresholdHeatTransferRate() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->coolingLoadControlThresholdHeatTransferRate();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setCoolingLoadControlThresholdHeatTransferRate(
      coolingLoadControlThresholdHeatTransferRate);
  }

  HVACComponent ZoneHVACEvaporativeCoolerUnit::firstEvaporativeCooler() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->firstEvaporativeCooler();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setFirstEvaporativeCooler(const HVACComponent& hvacComponent) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setFirstEvaporativeCooler(hvacComponent);
  }

  boost::optional<HVACComponent> ZoneHVACEvaporativeCoolerUnit::secondEvaporativeCooler() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->secondEvaporativeCooler();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setSecondEvaporativeCooler(const HVACComponent& hvacComponent) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setSecondEvaporativeCooler(hvacComponent);
  }

  void ZoneHVACEvaporativeCoolerUnit::resetSecondEvaporativeCooler() {
    getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->resetSecondEvaporativeCooler();
  }

  double ZoneHVACEvaporativeCoolerUnit::shutOffRelativeHumidity() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->shutOffRelativeHumidity();
  }

  bool ZoneHVACEvaporativeCoolerUnit::setShutOffRelativeHumidity(double shutOffRelativeHumidity) {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->setShutOffRelativeHumidity(shutOffRelativeHumidity);
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit::outdoorAirNode() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->outdoorAirNode();
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit::fanOutletNode() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->fanOutletNode();
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit::firstEvaporativeCoolerOutletNode() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->firstEvaporativeCoolerOutletNode();
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit::secondEvaporativeCoolerOutletNode() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->secondEvaporativeCoolerOutletNode();
  }

  std::vector<ModelObject> ZoneHVACEvaporativeCoolerUnit::children() const {
    return getImpl<detail::ZoneHVACEvaporativeCoolerUnit_Impl>()->children();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

  namespace {

    // This family only owns a simple outdoor-air stream made of one supported fan
    // plus one or two supported research-special evaporative coolers.
    bool isEvaporativeCoolerUnitFan(const HVACComponent& component) {
      const auto type = component.iddObject().type().value();
      return (type == IddObjectType::Fan_ConstantVolume) || (type == IddObjectType::Fan_VariableVolume)
             || (type == IddObjectType::Fan_OnOff) || (type == IddObjectType::Fan_SystemModel)
             || (type == IddObjectType::Fan_ComponentModel);
    }

    bool isEvaporativeCoolerUnitCooler(const HVACComponent& component) {
      const auto type = component.iddObject().type().value();
      return (type == IddObjectType::EvaporativeCooler_Direct_ResearchSpecial)
             || (type == IddObjectType::EvaporativeCooler_Indirect_ResearchSpecial);
    }

    boost::optional<Node> connectedNode(const boost::optional<ModelObject>& object) {
      return object ? object->optionalCast<Node>() : boost::none;
    }

    Node keepOrCreateNode(const boost::optional<Node>& currentNode, Model model, const std::string& suggestedName) {
      return currentNode ? *currentNode : model.getOrCreateTransientByName<Node>(suggestedName);
    }

  }  // namespace

  std::vector<ModelObject> ZoneHVACEvaporativeCoolerUnit_Impl::children() const {
    std::vector<ModelObject> result;
    if (auto supplyAirFan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName)) {
      result.push_back(*supplyAirFan);
    }
    if (auto firstEvaporativeCooler =
          getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName)) {
      result.push_back(*firstEvaporativeCooler);
    }
    if (auto secondEvaporativeCooler =
          getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName)) {
      result.push_back(*secondEvaporativeCooler);
    }
    return result;
  }

  unsigned ZoneHVACEvaporativeCoolerUnit_Impl::inletPort() const {
    return ZoneHVAC_EvaporativeCoolerUnitFields::ZoneReliefAirNodeName;
  }

  unsigned ZoneHVACEvaporativeCoolerUnit_Impl::outletPort() const {
    return ZoneHVAC_EvaporativeCoolerUnitFields::CoolerOutletNodeName;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::addToThermalZone(ThermalZone& thermalZone) {
    if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
      return false;
    }
    maintainContainedAirPath();
    return true;
  }

  void ZoneHVACEvaporativeCoolerUnit_Impl::removeFromThermalZone() {
    ZoneHVACComponent_Impl::removeFromThermalZone();
    maintainContainedAirPath();
  }

  void ZoneHVACEvaporativeCoolerUnit_Impl::doCanonicalize(LoadContext& context) {
    ZoneHVACComponent_Impl::doCanonicalize(context);
    repairContainedAirPath(context);
  }

  Schedule ZoneHVACEvaporativeCoolerUnit_Impl::availabilitySchedule() const {
    auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityScheduleName);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setAvailabilitySchedule(Schedule& schedule) {
    if (schedule.model() != model()) {
      return false;
    }
    return setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::AvailabilityScheduleName, schedule.handle(), false);
  }

  HVACComponent ZoneHVACEvaporativeCoolerUnit_Impl::supplyAirFan() const {
    auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setSupplyAirFan(const HVACComponent& supplyAirFan) {
    if ((supplyAirFan.model() != model()) || !supplyAirFan.optionalCast<StraightComponent>() || !isEvaporativeCoolerUnitFan(supplyAirFan)) {
      return false;
    }

    const bool result = setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName, supplyAirFan.handle(), false);
    if (result) {
      maintainContainedAirPath();
    }
    return result;
  }

  boost::optional<double> ZoneHVACEvaporativeCoolerUnit_Impl::designSupplyAirFlowRate() const {
    return getDouble(ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, true);
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setDesignSupplyAirFlowRate(double designSupplyAirFlowRate) {
    const bool result = setDouble(ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, designSupplyAirFlowRate);
    OS_ASSERT(result);
    return result;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::isDesignSupplyAirFlowRateAutosized() const {
    if (auto value = getString(ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, true)) {
      return openstudio::istringEqual(*value, "autosize");
    }
    return false;
  }

  void ZoneHVACEvaporativeCoolerUnit_Impl::autosizeDesignSupplyAirFlowRate() {
    OS_ASSERT(setString(ZoneHVAC_EvaporativeCoolerUnitFields::DesignSupplyAirFlowRate, "autosize"));
  }

  std::string ZoneHVACEvaporativeCoolerUnit_Impl::fanPlacement() const {
    const auto value = getString(ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setFanPlacement(const std::string& fanPlacement) {
    const bool result = setString(ZoneHVAC_EvaporativeCoolerUnitFields::FanPlacement, fanPlacement);
    if (result) {
      maintainContainedAirPath();
    }
    return result;
  }

  std::string ZoneHVACEvaporativeCoolerUnit_Impl::coolerUnitControlMethod() const {
    const auto value = getString(ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setCoolerUnitControlMethod(const std::string& coolerUnitControlMethod) {
    const bool result = setString(ZoneHVAC_EvaporativeCoolerUnitFields::CoolerUnitControlMethod, coolerUnitControlMethod);
    OS_ASSERT(result);
    return result;
  }

  double ZoneHVACEvaporativeCoolerUnit_Impl::throttlingRangeTemperatureDifference() const {
    const auto value = getDouble(ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setThrottlingRangeTemperatureDifference(double throttlingRangeTemperatureDifference) {
    const bool result = setDouble(ZoneHVAC_EvaporativeCoolerUnitFields::ThrottlingRangeTemperatureDifference, throttlingRangeTemperatureDifference);
    OS_ASSERT(result);
    return result;
  }

  double ZoneHVACEvaporativeCoolerUnit_Impl::coolingLoadControlThresholdHeatTransferRate() const {
    const auto value = getDouble(ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setCoolingLoadControlThresholdHeatTransferRate(double coolingLoadControlThresholdHeatTransferRate) {
    const bool result =
      setDouble(ZoneHVAC_EvaporativeCoolerUnitFields::CoolingLoadControlThresholdHeatTransferRate, coolingLoadControlThresholdHeatTransferRate);
    OS_ASSERT(result);
    return result;
  }

  HVACComponent ZoneHVACEvaporativeCoolerUnit_Impl::firstEvaporativeCooler() const {
    auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setFirstEvaporativeCooler(const HVACComponent& firstEvaporativeCooler) {
    if ((firstEvaporativeCooler.model() != model()) || !firstEvaporativeCooler.optionalCast<StraightComponent>()
        || !isEvaporativeCoolerUnitCooler(firstEvaporativeCooler)) {
      return false;
    }

    const bool result = setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName, firstEvaporativeCooler.handle(), false);
    if (result) {
      const std::string expectedType = firstEvaporativeCooler.iddObject().name();
      if (!openstudio::istringEqual(getString(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectType, true).value_or(""),
                                    expectedType)) {
        OS_ASSERT(setString(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectType, expectedType));
      }
      maintainContainedAirPath();
    }
    return result;
  }

  boost::optional<HVACComponent> ZoneHVACEvaporativeCoolerUnit_Impl::secondEvaporativeCooler() const {
    return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName);
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setSecondEvaporativeCooler(const HVACComponent& secondEvaporativeCooler) {
    if ((secondEvaporativeCooler.model() != model()) || !secondEvaporativeCooler.optionalCast<StraightComponent>()
        || !isEvaporativeCoolerUnitCooler(secondEvaporativeCooler)) {
      return false;
    }

    const bool result = setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName, secondEvaporativeCooler.handle(), false);
    if (result) {
      const std::string expectedType = secondEvaporativeCooler.iddObject().name();
      if (!openstudio::istringEqual(getString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, true).value_or(""),
                                    expectedType)) {
        OS_ASSERT(setString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, expectedType));
      }
      maintainContainedAirPath();
    }
    return result;
  }

  void ZoneHVACEvaporativeCoolerUnit_Impl::resetSecondEvaporativeCooler() {
    OS_ASSERT(setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName, Handle(), false));
    OS_ASSERT(setString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, ""));
    maintainContainedAirPath();
  }

  double ZoneHVACEvaporativeCoolerUnit_Impl::shutOffRelativeHumidity() const {
    const auto value = getDouble(ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, true);
    OS_ASSERT(value);
    return *value;
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::setShutOffRelativeHumidity(double shutOffRelativeHumidity) {
    const auto shutOffIndex = static_cast<unsigned>(ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity);
    while (numFields() <= shutOffIndex) {
      OS_ASSERT(pushString("", false));
    }
    const bool result = setDouble(ZoneHVAC_EvaporativeCoolerUnitFields::ShutOffRelativeHumidity, shutOffRelativeHumidity, false);
    OS_ASSERT(result);
    return result;
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit_Impl::outdoorAirNode() const {
    return resolvedNodeTarget(ZoneHVAC_EvaporativeCoolerUnitFields::OutdoorAirInletNodeName);
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit_Impl::fanOutletNode() const {
    auto fan = supplyAirFan().optionalCast<StraightComponent>();
    if (!fan) {
      return boost::none;
    }
    return connectedNode(fan->outletModelObject());
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit_Impl::firstEvaporativeCoolerOutletNode() const {
    auto cooler = firstEvaporativeCooler().optionalCast<StraightComponent>();
    if (!cooler) {
      return boost::none;
    }
    return connectedNode(cooler->outletModelObject());
  }

  boost::optional<Node> ZoneHVACEvaporativeCoolerUnit_Impl::secondEvaporativeCoolerOutletNode() const {
    auto coolerObject = secondEvaporativeCooler();
    auto cooler = coolerObject ? coolerObject->optionalCast<StraightComponent>() : boost::none;
    if (!cooler) {
      return boost::none;
    }
    return connectedNode(cooler->outletModelObject());
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::maintainContainedAirPath() {
    return reconcileContainedAirPath(false, nullptr);
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::repairContainedAirPath(LoadContext& context) {
    return reconcileContainedAirPath(true, &context);
  }

  bool ZoneHVACEvaporativeCoolerUnit_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
    (void)allowChildNodeRecovery;

    auto thisObject = getObject<ModelObject>();
    if (!thisObject.name()) {
      thisObject.createName();
    }

    auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanName);
    auto firstCoolerObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectName);
    auto secondCoolerObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerName);

    auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
    auto firstCooler = firstCoolerObject ? firstCoolerObject->optionalCast<StraightComponent>() : boost::none;
    auto secondCooler = secondCoolerObject ? secondCoolerObject->optionalCast<StraightComponent>() : boost::none;

    if (!fan || !isEvaporativeCoolerUnitFan(*fanObject) || !firstCooler || !isEvaporativeCoolerUnitCooler(*firstCoolerObject)
        || (secondCoolerObject && (!secondCooler || !isEvaporativeCoolerUnitCooler(*secondCoolerObject)))) {
      if (context) {
        addLoadWarning(*context, "ZoneHVAC:EvaporativeCoolerUnit '" + thisObject.nameString()
                                   + "' could not repair its contained air path because a required child is missing or unsupported.");
      }
      return false;
    }

    const std::string baseName = thisObject.nameString();
    bool changed = false;
    bool nodeWiringChanged = false;
    auto trackNodeChange = [&](bool localChanged) {
      changed = localChanged || changed;
      nodeWiringChanged = localChanged || nodeWiringChanged;
    };

    auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
    auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");
    auto outdoorAirNodeValue = resolvedOrCreatedNodeTarget(ZoneHVAC_EvaporativeCoolerUnitFields::OutdoorAirInletNodeName, baseName + " Outdoor Air Node");

    const bool blowThroughFan = openstudio::istringEqual(fanPlacement(), "BlowThrough");

    boost::optional<Node> fanOutlet;
    if (blowThroughFan) {
      fanOutlet = keepOrCreateNode(fanOutletNode(), model(), baseName + " Fan Outlet Node");
    }

    boost::optional<Node> firstCoolerOutlet = keepOrCreateNode(firstEvaporativeCoolerOutletNode(), model(),
                                                               secondCooler ? baseName + " First Evaporative Cooler Outlet Node"
                                                                            : baseName + " Air Outlet Node");
    if (!secondCooler) {
      firstCoolerOutlet = blowThroughFan ? outletNode : firstCoolerOutlet;
      if (!blowThroughFan) {
        firstCoolerOutlet = keepOrCreateNode(firstEvaporativeCoolerOutletNode(), model(), baseName + " First Evaporative Cooler Outlet Node");
      }
    }

    boost::optional<Node> secondCoolerOutlet;
    if (secondCooler) {
      secondCoolerOutlet = blowThroughFan ? outletNode
                                          : keepOrCreateNode(secondEvaporativeCoolerOutletNode(), model(),
                                                             baseName + " Second Evaporative Cooler Outlet Node");
    }

    trackNodeChange(setPointer(inletPort(), inletNode.handle(), false));
    trackNodeChange(setPointer(outletPort(), outletNode.handle(), false));
    trackNodeChange(setPointer(ZoneHVAC_EvaporativeCoolerUnitFields::OutdoorAirInletNodeName, outdoorAirNodeValue.handle(), false));

    if (blowThroughFan) {
      trackNodeChange(fan->getImpl<ModelObject_Impl>()->setPointer(fan->inletPort(), outdoorAirNodeValue.handle(), false));
      trackNodeChange(fan->getImpl<ModelObject_Impl>()->setPointer(fan->outletPort(), fanOutlet->handle(), false));

      trackNodeChange(firstCooler->getImpl<ModelObject_Impl>()->setPointer(firstCooler->inletPort(), fanOutlet->handle(), false));
      trackNodeChange(firstCooler->getImpl<ModelObject_Impl>()->setPointer(firstCooler->outletPort(),
                                                                           (secondCooler ? *firstCoolerOutlet : outletNode).handle(), false));

      if (secondCooler) {
        trackNodeChange(secondCooler->getImpl<ModelObject_Impl>()->setPointer(secondCooler->inletPort(), firstCoolerOutlet->handle(), false));
        trackNodeChange(secondCooler->getImpl<ModelObject_Impl>()->setPointer(secondCooler->outletPort(), secondCoolerOutlet->handle(), false));
      }
    } else {
      trackNodeChange(firstCooler->getImpl<ModelObject_Impl>()->setPointer(firstCooler->inletPort(), outdoorAirNodeValue.handle(), false));
      trackNodeChange(firstCooler->getImpl<ModelObject_Impl>()->setPointer(firstCooler->outletPort(),
                                                                           (secondCooler ? *firstCoolerOutlet : *firstCoolerOutlet).handle(), false));

      if (secondCooler) {
        trackNodeChange(secondCooler->getImpl<ModelObject_Impl>()->setPointer(secondCooler->inletPort(), firstCoolerOutlet->handle(), false));
        trackNodeChange(secondCooler->getImpl<ModelObject_Impl>()->setPointer(secondCooler->outletPort(), secondCoolerOutlet->handle(), false));
        trackNodeChange(fan->getImpl<ModelObject_Impl>()->setPointer(fan->inletPort(), secondCoolerOutlet->handle(), false));
      } else {
        trackNodeChange(fan->getImpl<ModelObject_Impl>()->setPointer(fan->inletPort(), firstCoolerOutlet->handle(), false));
      }

      trackNodeChange(fan->getImpl<ModelObject_Impl>()->setPointer(fan->outletPort(), outletNode.handle(), false));
    }

    if (secondCooler) {
      const std::string expectedType = secondCoolerObject->iddObject().name();
      if (!openstudio::istringEqual(getString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, true).value_or(""),
                                    expectedType)) {
        changed = setString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, expectedType) || changed;
      }
    } else if (getString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, true)) {
      changed = setString(ZoneHVAC_EvaporativeCoolerUnitFields::SecondEvaporativeCoolerObjectType, "") || changed;
    }

    const std::string expectedFirstType = firstCoolerObject->iddObject().name();
    if (!openstudio::istringEqual(getString(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectType, true).value_or(""),
                                  expectedFirstType)) {
      changed = setString(ZoneHVAC_EvaporativeCoolerUnitFields::FirstEvaporativeCoolerObjectType, expectedFirstType) || changed;
    }

    const std::string expectedFanType = fanObject->iddObject().name();
    if (!openstudio::istringEqual(getString(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanObjectType, true).value_or(""), expectedFanType)) {
      changed = setString(ZoneHVAC_EvaporativeCoolerUnitFields::SupplyAirFanObjectType, expectedFanType) || changed;
    }

    if (nodeWiringChanged && context) {
      addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:EvaporativeCoolerUnit '" + baseName + "'.");
    }

    return changed;
  }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
