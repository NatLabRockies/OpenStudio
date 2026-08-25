/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilSystemCoolingWater.hpp"
#include "StraightComponent/CoilSystemCoolingWater_Impl.hpp"

#include "HVACComponent/HVACComponent.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "WaterToAirComponent/CoilCoolingWater.hpp"
#include "WaterToAirComponent/CoilCoolingWater_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/CoilSystem_Cooling_Water_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  namespace {

    constexpr auto kAvailabilityScheduleField = openstudio::CoilSystem_Cooling_WaterFields::AvailabilityScheduleName;
    constexpr auto kCoolingCoilField = openstudio::CoilSystem_Cooling_WaterFields::CoolingCoilName;
    constexpr auto kCompanionCoilField = openstudio::CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery;

  }  // namespace

  CoilSystemCoolingWater::CoilSystemCoolingWater(const Model& model) : StraightComponent(CoilSystemCoolingWater::iddObjectType(), model) {
    auto alwaysOn = const_cast<Model&>(model).alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));

    CoilCoolingWater coolingCoil(model);
    OS_ASSERT(setCoolingCoil(coolingCoil));

    // Keep strict scalar getters populated for model-parity behavior.
    OS_ASSERT(setDehumidificationControlType("None"));
    OS_ASSERT(setRunonSensibleLoad(true));
    OS_ASSERT(setRunonLatentLoad(false));
    OS_ASSERT(setMinimumAirToWaterTemperatureOffset(0.0));
    OS_ASSERT(setEconomizerLockout(true));
    OS_ASSERT(setMinimumWaterLoopTemperatureForHeatRecovery(0.0));
  }

  CoilSystemCoolingWater::CoilSystemCoolingWater(const Model& model, const HVACComponent& coolingCoil)
    : StraightComponent(CoilSystemCoolingWater::iddObjectType(), model) {
    auto alwaysOn = const_cast<Model&>(model).alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    if (!setCoolingCoil(coolingCoil)) {
      throw std::runtime_error("Unable to set cooling coil for CoilSystemCoolingWater.");
    }

    OS_ASSERT(setDehumidificationControlType("None"));
    OS_ASSERT(setRunonSensibleLoad(true));
    OS_ASSERT(setRunonLatentLoad(false));
    OS_ASSERT(setMinimumAirToWaterTemperatureOffset(0.0));
    OS_ASSERT(setEconomizerLockout(true));
    OS_ASSERT(setMinimumWaterLoopTemperatureForHeatRecovery(0.0));
  }

  CoilSystemCoolingWater::CoilSystemCoolingWater(std::shared_ptr<detail::CoilSystemCoolingWater_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilSystemCoolingWater::iddObjectType() {
    return IddObjectType::CoilSystem_Cooling_Water;
  }

  std::vector<std::string> CoilSystemCoolingWater::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType);
  }

  bool CoilSystemCoolingWater::addToNode(Node& node) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->addToNode(node);
  }

  Schedule CoilSystemCoolingWater::availabilitySchedule() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->availabilitySchedule();
  }

  bool CoilSystemCoolingWater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent CoilSystemCoolingWater::coolingCoil() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->coolingCoil();
  }

  bool CoilSystemCoolingWater::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setCoolingCoil(coolingCoil);
  }

  std::string CoilSystemCoolingWater::dehumidificationControlType() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->dehumidificationControlType();
  }

  bool CoilSystemCoolingWater::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  bool CoilSystemCoolingWater::runonSensibleLoad() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonSensibleLoad();
  }

  bool CoilSystemCoolingWater::setRunonSensibleLoad(bool runonSensibleLoad) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonSensibleLoad(runonSensibleLoad);
  }

  bool CoilSystemCoolingWater::runonLatentLoad() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonLatentLoad();
  }

  bool CoilSystemCoolingWater::setRunonLatentLoad(bool runonLatentLoad) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonLatentLoad(runonLatentLoad);
  }

  double CoilSystemCoolingWater::minimumAirToWaterTemperatureOffset() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumAirToWaterTemperatureOffset();
  }

  bool CoilSystemCoolingWater::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumAirToWaterTemperatureOffset(minimumAirToWaterTemperatureOffset);
  }

  bool CoilSystemCoolingWater::economizerLockout() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->economizerLockout();
  }

  bool CoilSystemCoolingWater::setEconomizerLockout(bool economizerLockout) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setEconomizerLockout(economizerLockout);
  }

  double CoilSystemCoolingWater::minimumWaterLoopTemperatureForHeatRecovery() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumWaterLoopTemperatureForHeatRecovery();
  }

  bool CoilSystemCoolingWater::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumWaterLoopTemperatureForHeatRecovery(minimumWaterLoopTemperatureForHeatRecovery);
  }

  boost::optional<HVACComponent> CoilSystemCoolingWater::companionCoilUsedForHeatRecovery() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->companionCoilUsedForHeatRecovery();
  }

  bool CoilSystemCoolingWater::setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setCompanionCoilUsedForHeatRecovery(companionCoilUsedForHeatRecovery);
  }

  void CoilSystemCoolingWater::resetCompanionCoilUsedForHeatRecovery() {
    getImpl<detail::CoilSystemCoolingWater_Impl>()->resetCompanionCoilUsedForHeatRecovery();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    unsigned CoilSystemCoolingWater_Impl::inletPort() const {
      return openstudio::CoilSystem_Cooling_WaterFields::AirInletNodeName;
    }

    unsigned CoilSystemCoolingWater_Impl::outletPort() const {
      return openstudio::CoilSystem_Cooling_WaterFields::AirOutletNodeName;
    }

    bool CoilSystemCoolingWater_Impl::addToNode(Node& node) {
      for (auto oaSystem : model().getConcreteModelObjects<AirLoopHVACOutdoorAirSystem>()) {
        auto outboardOANode = oaSystem.outboardOANode();
        if (outboardOANode && (*outboardOANode == node)) {
          return StraightComponent_Impl::addToOutdoorAirSystem(oaSystem, node);
        }
      }

      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      const bool ok = StraightComponent_Impl::addToNode(node);
      if (!ok) {
        return false;
      }

      auto inletNode = getObject<ModelObject>().getModelObjectTarget<Node>(inletPort());
      auto outletNode = getObject<ModelObject>().getModelObjectTarget<Node>(outletPort());
      if (inletNode && outletNode) {
        if (auto companionCoil = companionCoilUsedForHeatRecovery()) {
          if (auto coolingWaterCoil = companionCoil->optionalCast<CoilCoolingWater>()) {
            auto coolingWaterCoilImpl = coolingWaterCoil->getImpl<detail::CoilCoolingWater_Impl>();
            OS_ASSERT(coolingWaterCoilImpl->setPointer(coolingWaterCoil->airInletPort(), inletNode->handle(), false));
            OS_ASSERT(coolingWaterCoilImpl->setPointer(coolingWaterCoil->airOutletPort(), outletNode->handle(), false));
          }
        }
      }

      return true;
    }

    std::vector<ModelObject> CoilSystemCoolingWater_Impl::children() const {
      std::vector<ModelObject> result;
      result.push_back(coolingCoil().cast<ModelObject>());
      if (auto companionCoil = companionCoilUsedForHeatRecovery()) {
        result.push_back(companionCoil->cast<ModelObject>());
      }
      return result;
    }

    std::vector<IdfObject> CoilSystemCoolingWater_Impl::remove() {
      const auto ownedChildren = children();
      auto removedParent = StraightComponent_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<IdfObject> result;
      for (const auto& child : ownedChildren) {
        if (auto component = child.optionalCast<HVACComponent>()) {
          auto removed = component->remove();
          result.insert(result.end(), removed.begin(), removed.end());
        }
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    Schedule CoilSystemCoolingWater_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(kAvailabilityScheduleField);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(kAvailabilityScheduleField, schedule.handle());
    }

    HVACComponent CoilSystemCoolingWater_Impl::coolingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(kCoolingCoilField);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWater_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      return setPointer(kCoolingCoilField, coolingCoil.handle());
    }

    std::string CoilSystemCoolingWater_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWater_Impl::runonSensibleLoad() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonSensibleLoad);
    }

    bool CoilSystemCoolingWater_Impl::runonLatentLoad() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonLatentLoad);
    }

    double CoilSystemCoolingWater_Impl::minimumAirToWaterTemperatureOffset() const {
      const auto value = getDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWater_Impl::economizerLockout() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::EconomizerLockout);
    }

    double CoilSystemCoolingWater_Impl::minimumWaterLoopTemperatureForHeatRecovery() const {
      const auto value = getDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingWater_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::CoilSystem_Cooling_WaterFields::DehumidificationControlType, dehumidificationControlType);
    }

    bool CoilSystemCoolingWater_Impl::setRunonSensibleLoad(bool runonSensibleLoad) {
      const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonSensibleLoad, runonSensibleLoad);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setRunonLatentLoad(bool runonLatentLoad) {
      const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::RunonLatentLoad, runonLatentLoad);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
      return setDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, minimumAirToWaterTemperatureOffset);
    }

    bool CoilSystemCoolingWater_Impl::setEconomizerLockout(bool economizerLockout) {
      const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_WaterFields::EconomizerLockout, economizerLockout);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
      const bool result =
        setDouble(openstudio::CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, minimumWaterLoopTemperatureForHeatRecovery);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<HVACComponent> CoilSystemCoolingWater_Impl::companionCoilUsedForHeatRecovery() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(kCompanionCoilField);
    }

    bool CoilSystemCoolingWater_Impl::setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery) {
      if (companionCoilUsedForHeatRecovery.iddObject().name() != "Coil:Cooling:Water") {
        return false;
      }
      return setPointer(kCompanionCoilField, companionCoilUsedForHeatRecovery.handle());
    }

    void CoilSystemCoolingWater_Impl::resetCompanionCoilUsedForHeatRecovery() {
      OS_ASSERT(setString(kCompanionCoilField, ""));
    }

    std::vector<std::string> CoilSystemCoolingWater_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingWater::dehumidificationControlTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
