/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner_Impl.hpp"

#include "HVACComponent.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(const Model& model)
    : ZoneHVACComponent(ZoneHVACPackagedTerminalAirConditioner::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setSupplyAirFanOperatingModeSchedule(alwaysOn));
  }

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(
    std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACPackagedTerminalAirConditioner::iddObjectType() {
    return IddObjectType::ZoneHVAC_PackagedTerminalAirConditioner;
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::validFanPlacementValues() {
    return fanPlacementValues();
  }

  Schedule ZoneHVACPackagedTerminalAirConditioner::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
      supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(
      supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  std::string ZoneHVACPackagedTerminalAirConditioner::fanPlacement() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->fanPlacement();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetFanPlacement() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetFanPlacement();
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::supplyAirFan() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFan();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFan(HVACComponent& fan) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFan(fan);
  }

  Schedule ZoneHVACPackagedTerminalAirConditioner::supplyAirFanOperatingModeSchedule() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFanOperatingModeSchedule();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFanOperatingModeSchedule(schedule);
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::heatingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->heatingCoil();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setHeatingCoil(HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setHeatingCoil(heatingCoil);
  }

  HVACComponent ZoneHVACPackagedTerminalAirConditioner::coolingCoil() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->coolingCoil();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setCoolingCoil(HVACComponent& coolingCoil) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setCoolingCoil(coolingCoil);
  }

  std::vector<ModelObject> ZoneHVACPackagedTerminalAirConditioner::children() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->children();
  }

  namespace detail {

    Schedule ZoneHVACPackagedTerminalAirConditioner_Impl::availabilitySchedule() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName,
                                           "ZoneHVACPackagedTerminalAirConditioner", "Availability", schedule);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result =
        supplyAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result =
        supplyAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
      if (!value || value->empty()) {
        return false;
      }
      if (openstudio::istringEqual(value.get(), "Yes")) {
        return true;
      }
      if (openstudio::istringEqual(value.get(), "No")) {
        return false;
      }
      return false;
    }

    bool
      ZoneHVACPackagedTerminalAirConditioner_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No", false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result =
        outdoorAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result =
        outdoorAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    std::string ZoneHVACPackagedTerminalAirConditioner_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
      if (!value) {
        return std::string();
      }
      return value.get();
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setFanPlacement(const std::string& fanPlacement) {
      return setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, fanPlacement);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, "");
      OS_ASSERT(result);
    }

    std::vector<ModelObject> ZoneHVACPackagedTerminalAirConditioner_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto heatingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName)) {
        result.push_back(*heatingCoil);
      }
      if (auto fan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName)) {
        result.push_back(*fan);
      }
      if (auto coolingCoil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
            ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName)) {
        result.push_back(*coolingCoil);
      }
      return result;
    }

    unsigned ZoneHVACPackagedTerminalAirConditioner_Impl::inletPort() const {
      return ZoneHVAC_PackagedTerminalAirConditionerFields::AirInletNodeName;
    }

    unsigned ZoneHVACPackagedTerminalAirConditioner_Impl::outletPort() const {
      return ZoneHVAC_PackagedTerminalAirConditionerFields::AirOutletNodeName;
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFan() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFan(HVACComponent& fan) {
      const auto iddObjectType = fan.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Fan_ConstantVolume) || (iddObjectType == IddObjectType::OS_Fan_OnOff)
          || (iddObjectType == IddObjectType::OS_Fan_SystemModel) || (iddObjectType == IddObjectType::Fan_ConstantVolume)
          || (iddObjectType == IddObjectType::Fan_OnOff) || (iddObjectType == IddObjectType::Fan_SystemModel)) {
        return setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName, fan.handle());
      }
      return false;
    }

    Schedule ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFanOperatingModeSchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFanOperatingModeSchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName,
                                           "ZoneHVACPackagedTerminalAirConditioner", "Supply Air Fan Operating Mode", schedule);
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::heatingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setHeatingCoil(HVACComponent& heatingCoil) {
      const auto iddObjectType = heatingCoil.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Coil_Heating_Gas) || (iddObjectType == IddObjectType::OS_Coil_Heating_Electric)
          || (iddObjectType == IddObjectType::OS_Coil_Heating_Water) || (iddObjectType == IddObjectType::Coil_Heating_Fuel)
          || (iddObjectType == IddObjectType::Coil_Heating_Electric) || (iddObjectType == IddObjectType::Coil_Heating_Water)) {
        return setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName, heatingCoil.handle());
      }
      return false;
    }

    HVACComponent ZoneHVACPackagedTerminalAirConditioner_Impl::coolingCoil() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setCoolingCoil(HVACComponent& coolingCoil) {
      const auto iddObjectType = coolingCoil.iddObject().type();
      if ((iddObjectType == IddObjectType::OS_Coil_Cooling_DX_SingleSpeed) || (iddObjectType == IddObjectType::OS_Coil_Cooling_DX_VariableSpeed)
          || (iddObjectType == IddObjectType::OS_CoilSystem_Cooling_DX_HeatExchangerAssisted)
          || (iddObjectType == IddObjectType::OS_Coil_Cooling_DX) || (iddObjectType == IddObjectType::Coil_Cooling_DX_SingleSpeed)
          || (iddObjectType == IddObjectType::Coil_Cooling_DX_VariableSpeed)
          || (iddObjectType == IddObjectType::CoilSystem_Cooling_DX_HeatExchangerAssisted)
          || (iddObjectType == IddObjectType::Coil_Cooling_DX)) {
        return setPointer(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName, coolingCoil.handle());
      }
      return false;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
