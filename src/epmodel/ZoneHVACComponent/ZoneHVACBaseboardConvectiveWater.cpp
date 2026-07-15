/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboard_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Water_FieldEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  namespace detail {

    // These companion coils are transient views over parent-owned storage, so they
    // still need a stable model-level identity while the parent exists. We key
    // that identity off the parent handle instead of the parent display name so a
    // rename does not orphan the transient child.
    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACBaseboardConvectiveWater& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__heating_water_baseboard";
    }

  }  // namespace detail

  ZoneHVACBaseboardConvectiveWater::ZoneHVACBaseboardConvectiveWater(const Model& model)
    : ZoneHVACComponent(ZoneHVACBaseboardConvectiveWater::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>());

    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
    autosizeHeatingDesignCapacity();
    OS_ASSERT(setHeatingDesignCapacityPerFloorArea(0.0));
    OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(1.0));
  }

  ZoneHVACBaseboardConvectiveWater::ZoneHVACBaseboardConvectiveWater(const Model& model, Schedule& availabilitySchedule,
                                                                     StraightComponent& heatingCoilBaseboard)
    : ZoneHVACBaseboardConvectiveWater(model) {
    if (!setAvailabilitySchedule(availabilitySchedule)) {
      remove();
      throw std::runtime_error("Unable to set baseboard convective water availability schedule.");
    }
    if (!setHeatingCoil(heatingCoilBaseboard)) {
      remove();
      throw std::runtime_error("Unable to set baseboard convective water heating coil.");
    }
  }

  ZoneHVACBaseboardConvectiveWater::ZoneHVACBaseboardConvectiveWater(std::shared_ptr<detail::ZoneHVACBaseboardConvectiveWater_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardConvectiveWater::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_Convective_Water;
  }

  std::vector<std::string> ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod);
  }

  Schedule ZoneHVACBaseboardConvectiveWater::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACBaseboardConvectiveWater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setAvailabilitySchedule(schedule);
  }

  StraightComponent ZoneHVACBaseboardConvectiveWater::heatingCoil() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingCoil();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingCoil(const StraightComponent& heatingCoilBaseboard) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingCoil(heatingCoilBaseboard);
  }

  std::vector<ModelObject> ZoneHVACBaseboardConvectiveWater::children() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->children();
  }

  std::string ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardConvectiveWater::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeHeatingDesignCapacity();
  }

  double ZoneHVACBaseboardConvectiveWater::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACBaseboardConvectiveWater::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setHeatingDesignCapacityPerFloorArea(heatingDesignCapacityPerFloorArea);
  }

  double ZoneHVACBaseboardConvectiveWater::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACBaseboardConvectiveWater::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::uFactorTimesAreaValue() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->uFactorTimesAreaValue();
  }

  bool ZoneHVACBaseboardConvectiveWater::isUFactorTimesAreaValueDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isUFactorTimesAreaValueDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::isUFactorTimesAreaValueAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isUFactorTimesAreaValueAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setUFactorTimesAreaValue(uFactorTimesAreaValue);
  }

  void ZoneHVACBaseboardConvectiveWater::resetUFactorTimesAreaValue() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetUFactorTimesAreaValue();
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeUFactorTimesAreaValue() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeUFactorTimesAreaValue();
  }

  boost::optional<double> ZoneHVACBaseboardConvectiveWater::maximumWaterFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->maximumWaterFlowRate();
  }

  bool ZoneHVACBaseboardConvectiveWater::isMaximumWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isMaximumWaterFlowRateDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::isMaximumWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isMaximumWaterFlowRateAutosized();
  }

  bool ZoneHVACBaseboardConvectiveWater::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  void ZoneHVACBaseboardConvectiveWater::resetMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetMaximumWaterFlowRate();
  }

  void ZoneHVACBaseboardConvectiveWater::autosizeMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->autosizeMaximumWaterFlowRate();
  }

  double ZoneHVACBaseboardConvectiveWater::convergenceTolerance() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->convergenceTolerance();
  }

  bool ZoneHVACBaseboardConvectiveWater::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool ZoneHVACBaseboardConvectiveWater::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void ZoneHVACBaseboardConvectiveWater::resetConvergenceTolerance() {
    getImpl<detail::ZoneHVACBaseboardConvectiveWater_Impl>()->resetConvergenceTolerance();
  }

  namespace detail {

    unsigned ZoneHVACBaseboardConvectiveWater_Impl::inletPort() const {
      return 0u;
    }

    unsigned ZoneHVACBaseboardConvectiveWater_Impl::outletPort() const {
      return 0u;
    }

    Schedule ZoneHVACBaseboardConvectiveWater_Impl::availabilitySchedule() const {
      if (auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(
            openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::AvailabilityScheduleName)) {
        return *target;
      }
      throw std::runtime_error("Baseboard convective water is missing its availability schedule.");
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::AvailabilityScheduleName, "ZoneHVACBaseboardConvectiveWater",
                         "Availability", schedule);
    }

    StraightComponent ZoneHVACBaseboardConvectiveWater_Impl::heatingCoil() const {
      const auto parent = getObject<openstudio::epmodel::ZoneHVACBaseboardConvectiveWater>();
      return model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingWaterBaseboard>(detail::transientHeatingCoilName(parent));
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingCoil(const StraightComponent& heatingCoil) {
      auto source = heatingCoil.optionalCast<CoilHeatingWaterBaseboard>();
      if (!source) {
        return false;
      }

      auto target = this->heatingCoil().cast<CoilHeatingWaterBaseboard>();
      bool result = true;

      result = target.setHeatingDesignCapacityMethod(source->heatingDesignCapacityMethod()) && result;
      if (source->heatingDesignCapacity()) {
        result = target.setHeatingDesignCapacity(*source->heatingDesignCapacity()) && result;
      } else {
        target.autosizeHeatingDesignCapacity();
      }
      result = target.setHeatingDesignCapacityPerFloorArea(source->heatingDesignCapacityPerFloorArea()) && result;
      result = target.setFractionofAutosizedHeatingDesignCapacity(source->fractionofAutosizedHeatingDesignCapacity()) && result;

      if (source->uFactorTimesAreaValue()) {
        result = target.setUFactorTimesAreaValue(*source->uFactorTimesAreaValue()) && result;
      } else if (source->isUFactorTimesAreaValueAutosized()) {
        target.autosizeUFactorTimesAreaValue();
      } else {
        target.resetUFactorTimesAreaValue();
      }

      if (source->maximumWaterFlowRate()) {
        result = target.setMaximumWaterFlowRate(*source->maximumWaterFlowRate()) && result;
      } else if (source->isMaximumWaterFlowRateAutosized()) {
        target.autosizeMaximumWaterFlowRate();
      } else {
        target.resetMaximumWaterFlowRate();
      }

      result = target.setConvergenceTolerance(source->convergenceTolerance()) && result;

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result = setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::InletNodeName, Handle(), false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result = setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_Baseboard_Convective_WaterFields::OutletNodeName, Handle(), false) && result;
      }

      return result;
    }

    std::vector<ModelObject> ZoneHVACBaseboardConvectiveWater_Impl::children() const {
      return {heatingCoil().cast<ModelObject>()};
    }

    std::string ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacityMethod() const {
      auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      const bool result = setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isHeatingDesignCapacityAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacity, "autosize"));
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::heatingDesignCapacityPerFloorArea() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityPerFloorArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::FractionofAutosizedHeatingDesignCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
      const bool result =
        setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::FractionofAutosizedHeatingDesignCapacity, fractionofAutosizedHeatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::uFactorTimesAreaValue() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isUFactorTimesAreaValueDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isUFactorTimesAreaValueAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setUFactorTimesAreaValue(double uFactorTimesAreaValue) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, uFactorTimesAreaValue);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetUFactorTimesAreaValue() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, ""));
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeUFactorTimesAreaValue() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::UFactorTimesAreaValue, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardConvectiveWater_Impl::maximumWaterFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, true);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isMaximumWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isMaximumWaterFlowRateAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, true)) {
        result = openstudio::istringEqual(*value, "autosize");
      }
      return result;
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, maximumWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, ""));
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::autosizeMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::MaximumWaterFlowRate, "autosize"));
    }

    double ZoneHVACBaseboardConvectiveWater_Impl::convergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance);
    }

    bool ZoneHVACBaseboardConvectiveWater_Impl::setConvergenceTolerance(double convergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, convergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardConvectiveWater_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_Convective_WaterFields::ConvergenceTolerance, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
