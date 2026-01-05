/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilSystemCoolingWater.hpp"
#include "CoilSystemCoolingWater_Impl.hpp"

#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "HVACComponent.hpp"
#include "HVACComponent_Impl.hpp"
#include "CoilCoolingWater.hpp"
#include "CoilCoolingWater_Impl.hpp"
#include "CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"

#include "AirLoopHVACUnitarySystem.hpp"
#include "AirLoopHVACUnitarySystem_Impl.hpp"
#include "ZoneHVACFourPipeFanCoil.hpp"
#include "ZoneHVACFourPipeFanCoil_Impl.hpp"
#include "ZoneHVACUnitVentilator.hpp"
#include "ZoneHVACUnitVentilator_Impl.hpp"

#include "AirLoopHVACOutdoorAirSystem.hpp"
#include "AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/data/DataEnums.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_CoilSystem_Cooling_Water_FieldEnums.hxx>

namespace openstudio {
namespace model {

  namespace detail {

    CoilSystemCoolingWater_Impl::CoilSystemCoolingWater_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(idfObject, model, keepHandle) {
      OS_ASSERT(idfObject.iddObject().type() == CoilSystemCoolingWater::iddObjectType());
    }

    CoilSystemCoolingWater_Impl::CoilSystemCoolingWater_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model,
                                                             bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {
      OS_ASSERT(other.iddObject().type() == CoilSystemCoolingWater::iddObjectType());
    }

    CoilSystemCoolingWater_Impl::CoilSystemCoolingWater_Impl(const CoilSystemCoolingWater_Impl& other, Model_Impl* model, bool keepHandle)
      : StraightComponent_Impl(other, model, keepHandle) {}

    const std::vector<std::string>& CoilSystemCoolingWater_Impl::outputVariableNames() const {
      static std::vector<std::string> result;
      if (result.empty()) {
      }
      return result;
    }

    IddObjectType CoilSystemCoolingWater_Impl::iddObjectType() const {
      return CoilSystemCoolingWater::iddObjectType();
    }

    std::vector<ScheduleTypeKey> CoilSystemCoolingWater_Impl::getScheduleTypeKeys(const Schedule& schedule) const {
      std::vector<ScheduleTypeKey> result;
      const UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
      if (std::find(fieldIndices.cbegin(), fieldIndices.cend(), OS_CoilSystem_Cooling_WaterFields::AvailabilityScheduleName) != fieldIndices.cend()) {
        result.emplace_back("CoilSystemCoolingWater", "Availability");
      }
      return result;
    }

    unsigned CoilSystemCoolingWater_Impl::inletPort() const {
      return OS_CoilSystem_Cooling_WaterFields::AirInletNodeName;
    }

    unsigned CoilSystemCoolingWater_Impl::outletPort() const {
      return OS_CoilSystem_Cooling_WaterFields::AirOutletNodeName;
    }

    std::vector<ModelObject> CoilSystemCoolingWater_Impl::children() const {
      std::vector<ModelObject> result;
      if (OptionalHVACComponent intermediate = optionalCoolingCoil()) {
        result.push_back(*intermediate);
      }
      if (OptionalHVACComponent intermediate = companionCoilUsedForHeatRecovery()) {
        result.push_back(*intermediate);
      }

      return result;
    }

    std::vector<IdfObject> CoilSystemCoolingWater_Impl::remove() {
      std::vector<IdfObject> result;

      if (auto c_ = optionalCoolingCoil()) {  // This is false when the explicit ctor throws
        if (boost::optional<WaterToAirComponent> cc_ = c_->optionalCast<WaterToAirComponent>()) {
          cc_->removeFromPlantLoop();
        } else if (auto cc_ = c_->optionalCast<CoilSystemCoolingWaterHeatExchangerAssisted>()) {
          cc_->coolingCoil().removeFromPlantLoop();
        } else {
          OS_ASSERT(false);
        }
      }
      if (auto companionCoil_ = companionCoilUsedForHeatRecovery()) {
        if (auto cc_ = companionCoil_->optionalCast<WaterToAirComponent>()) {
          cc_->removeFromPlantLoop();
        } else {
          OS_ASSERT(false);
        }
      }

      return StraightComponent_Impl::remove();
    }

    ModelObject CoilSystemCoolingWater_Impl::clone(Model model) const {
      auto coilSystemClone = StraightComponent_Impl::clone(model).cast<CoilSystemCoolingWater>();

      if (OptionalHVACComponent intermediate = optionalCoolingCoil()) {
        coilSystemClone.setCoolingCoil(intermediate->clone(model).cast<HVACComponent>());
      }
      if (OptionalHVACComponent intermediate = companionCoilUsedForHeatRecovery()) {
        coilSystemClone.setCompanionCoilUsedForHeatRecovery(intermediate->clone(model).cast<HVACComponent>());
      }

      return std::move(coilSystemClone);
    }

    bool CoilSystemCoolingWater_Impl::addToNode(Node& node) {
      bool result = false;

      if (boost::optional<AirLoopHVAC> airLoop = node.airLoopHVAC()) {
        if (!airLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      } else if (boost::optional<AirLoopHVACOutdoorAirSystem> oas = node.airLoopHVACOutdoorAirSystem()) {
        if (oas->airLoopHVACDedicatedOutdoorAirSystem()) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return result;
    }

    boost::optional<HVACComponent> CoilSystemCoolingWater_Impl::containingHVACComponent() const {
      return boost::none;
    }

    boost::optional<ZoneHVACComponent> CoilSystemCoolingWater_Impl::containingZoneHVACComponent() const {
      return boost::none;
    }

    ComponentType CoilSystemCoolingWater_Impl::componentType() const {
      return ComponentType::Cooling;
    }

    std::vector<FuelType> CoilSystemCoolingWater_Impl::coolingFuelTypes() const {
      return coolingCoil().coolingFuelTypes();
    }

    std::vector<FuelType> CoilSystemCoolingWater_Impl::heatingFuelTypes() const {
      return {};
    }

    std::vector<AppGFuelType> CoilSystemCoolingWater_Impl::appGHeatingFuelTypes() const {
      return {};
    }

    Schedule CoilSystemCoolingWater_Impl::availabilitySchedule() const {
      boost::optional<Schedule> value = optionalAvailabilitySchedule();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Availability Schedule attached.");
      }
      return value.get();
    }

    HVACComponent CoilSystemCoolingWater_Impl::coolingCoil() const {
      boost::optional<HVACComponent> value = optionalCoolingCoil();
      if (!value) {
        LOG_AND_THROW(briefDescription() << " does not have an Cooling Coil attached.");
      }
      return value.get();
    }

    std::string CoilSystemCoolingWater_Impl::dehumidificationControlType() const {
      boost::optional<std::string> value = getString(OS_CoilSystem_Cooling_WaterFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool CoilSystemCoolingWater_Impl::runonSensibleLoad() const {
      return getBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::RunonSensibleLoad);
    }

    bool CoilSystemCoolingWater_Impl::runonLatentLoad() const {
      return getBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::RunonLatentLoad);
    }

    double CoilSystemCoolingWater_Impl::minimumAirToWaterTemperatureOffset() const {
      boost::optional<double> value = getDouble(OS_CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool CoilSystemCoolingWater_Impl::economizerLockout() const {
      return getBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::EconomizerLockout);
    }

    double CoilSystemCoolingWater_Impl::minimumWaterLoopTemperatureForHeatRecovery() const {
      boost::optional<double> value = getDouble(OS_CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, true);
      OS_ASSERT(value);
      return value.get();
    }

    boost::optional<HVACComponent> CoilSystemCoolingWater_Impl::companionCoilUsedForHeatRecovery() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(OS_CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery);
    }

    bool CoilSystemCoolingWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      const bool result =
        setSchedule(OS_CoilSystem_Cooling_WaterFields::AvailabilityScheduleName, "CoilSystemCoolingWater", "Availability", schedule);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setCoolingCoil(const HVACComponent& coolingCoil) {
      const bool result = setPointer(OS_CoilSystem_Cooling_WaterFields::CoolingCoil, coolingCoil.handle());
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      const bool result = setString(OS_CoilSystem_Cooling_WaterFields::DehumidificationControlType, dehumidificationControlType);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setRunonSensibleLoad(bool runonSensibleLoad) {
      const bool result = setBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::RunonSensibleLoad, runonSensibleLoad);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setRunonLatentLoad(bool runonLatentLoad) {
      const bool result = setBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::RunonLatentLoad, runonLatentLoad);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
      const bool result = setDouble(OS_CoilSystem_Cooling_WaterFields::MinimumAirToWaterTemperatureOffset, minimumAirToWaterTemperatureOffset);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setEconomizerLockout(bool economizerLockout) {
      const bool result = setBooleanFieldValue(OS_CoilSystem_Cooling_WaterFields::EconomizerLockout, economizerLockout);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
      const bool result =
        setDouble(OS_CoilSystem_Cooling_WaterFields::MinimumWaterLoopTemperatureForHeatRecovery, minimumWaterLoopTemperatureForHeatRecovery);
      OS_ASSERT(result);
      return result;
    }

    bool CoilSystemCoolingWater_Impl::setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery) {
      if (companionCoilUsedForHeatRecovery.iddObjectType() == IddObjectType::OS_Coil_Cooling_Water) {
        const bool result =
          setPointer(OS_CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery, companionCoilUsedForHeatRecovery.handle());
        return result;
      } else {
        LOG(Warn, "Invalid Companion Coil Used For Heat Recovery Type (expected CoilCoolingWater, not '"
                    << companionCoilUsedForHeatRecovery.iddObjectType().valueName() << "') for " << briefDescription());
        return false;
      }
    }

    void CoilSystemCoolingWater_Impl::resetCompanionCoilUsedForHeatRecovery() {
      const bool result = setString(OS_CoilSystem_Cooling_WaterFields::CompanionCoilUsedForHeatRecovery, "");
      OS_ASSERT(result);
    }

    boost::optional<Schedule> CoilSystemCoolingWater_Impl::optionalAvailabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_CoilSystem_Cooling_WaterFields::AvailabilityScheduleName);
    }

    boost::optional<HVACComponent> CoilSystemCoolingWater_Impl::optionalCoolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<HVACComponent>(OS_CoilSystem_Cooling_WaterFields::CoolingCoil);
    }

  }  // namespace detail

  void CoilSystemCoolingWater::assignEnergyPlusIDDDefaults() {
    bool ok = true;
    auto alwaysOn = model().alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(ok);

    ok = setDehumidificationControlType("None");
    OS_ASSERT(ok);
    ok = setRunonSensibleLoad(true);
    OS_ASSERT(ok);
    ok = setRunonLatentLoad(false);
    OS_ASSERT(ok);
    ok = setMinimumAirToWaterTemperatureOffset(0.0);
    OS_ASSERT(ok);
    ok = setEconomizerLockout(true);
    OS_ASSERT(ok);
    ok = setMinimumWaterLoopTemperatureForHeatRecovery(0.0);
    OS_ASSERT(ok);
  }

  CoilSystemCoolingWater::CoilSystemCoolingWater(const Model& model) : StraightComponent(CoilSystemCoolingWater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilSystemCoolingWater_Impl>());

    CoilCoolingWater coolingCoil(model);
    coolingCoil.setName(name().get() + " Cooling Coil");
    bool ok = setCoolingCoil(coolingCoil);
    OS_ASSERT(ok);

    assignEnergyPlusIDDDefaults();
  }

  CoilSystemCoolingWater::CoilSystemCoolingWater(const Model& model, const HVACComponent& coolingCoil)
    : StraightComponent(CoilSystemCoolingWater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilSystemCoolingWater_Impl>());

    bool ok = true;
    ok = setCoolingCoil(coolingCoil);
    if (!ok) {
      remove();
      LOG_AND_THROW("Unable to set " << briefDescription() << "'s Cooling Coil " << coolingCoil.briefDescription() << ".");
    }

    assignEnergyPlusIDDDefaults();
  }

  IddObjectType CoilSystemCoolingWater::iddObjectType() {
    return {IddObjectType::OS_CoilSystem_Cooling_Water};
  }

  std::vector<std::string> CoilSystemCoolingWater::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_CoilSystem_Cooling_WaterFields::DehumidificationControlType);
  }

  Schedule CoilSystemCoolingWater::availabilitySchedule() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->availabilitySchedule();
  }

  HVACComponent CoilSystemCoolingWater::coolingCoil() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->coolingCoil();
  }

  std::string CoilSystemCoolingWater::dehumidificationControlType() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->dehumidificationControlType();
  }

  bool CoilSystemCoolingWater::runonSensibleLoad() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonSensibleLoad();
  }

  bool CoilSystemCoolingWater::runonLatentLoad() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->runonLatentLoad();
  }

  double CoilSystemCoolingWater::minimumAirToWaterTemperatureOffset() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumAirToWaterTemperatureOffset();
  }

  bool CoilSystemCoolingWater::economizerLockout() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->economizerLockout();
  }

  double CoilSystemCoolingWater::minimumWaterLoopTemperatureForHeatRecovery() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->minimumWaterLoopTemperatureForHeatRecovery();
  }

  boost::optional<HVACComponent> CoilSystemCoolingWater::companionCoilUsedForHeatRecovery() const {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->companionCoilUsedForHeatRecovery();
  }

  bool CoilSystemCoolingWater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setAvailabilitySchedule(schedule);
  }

  bool CoilSystemCoolingWater::setCoolingCoil(const HVACComponent& coolingCoil) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setCoolingCoil(coolingCoil);
  }

  bool CoilSystemCoolingWater::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  bool CoilSystemCoolingWater::setRunonSensibleLoad(bool runonSensibleLoad) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonSensibleLoad(runonSensibleLoad);
  }

  bool CoilSystemCoolingWater::setRunonLatentLoad(bool runonLatentLoad) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setRunonLatentLoad(runonLatentLoad);
  }

  bool CoilSystemCoolingWater::setMinimumAirToWaterTemperatureOffset(double minimumAirToWaterTemperatureOffset) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumAirToWaterTemperatureOffset(minimumAirToWaterTemperatureOffset);
  }

  bool CoilSystemCoolingWater::setEconomizerLockout(bool economizerLockout) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setEconomizerLockout(economizerLockout);
  }

  bool CoilSystemCoolingWater::setMinimumWaterLoopTemperatureForHeatRecovery(double minimumWaterLoopTemperatureForHeatRecovery) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setMinimumWaterLoopTemperatureForHeatRecovery(minimumWaterLoopTemperatureForHeatRecovery);
  }

  bool CoilSystemCoolingWater::setCompanionCoilUsedForHeatRecovery(const HVACComponent& companionCoilUsedForHeatRecovery) {
    return getImpl<detail::CoilSystemCoolingWater_Impl>()->setCompanionCoilUsedForHeatRecovery(companionCoilUsedForHeatRecovery);
  }

  void CoilSystemCoolingWater::resetCompanionCoilUsedForHeatRecovery() {
    getImpl<detail::CoilSystemCoolingWater_Impl>()->resetCompanionCoilUsedForHeatRecovery();
  }

  /// @cond
  CoilSystemCoolingWater::CoilSystemCoolingWater(std::shared_ptr<detail::CoilSystemCoolingWater_Impl> impl) : StraightComponent(std::move(impl)) {}
  /// @endcond

}  // namespace model
}  // namespace openstudio
