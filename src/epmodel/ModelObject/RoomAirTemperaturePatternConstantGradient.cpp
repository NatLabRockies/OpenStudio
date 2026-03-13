/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirTemperaturePatternConstantGradient.hpp"
#include "RoomAirTemperaturePatternConstantGradient_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAir_TemperaturePattern_ConstantGradient_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirTemperaturePatternConstantGradient::RoomAirTemperaturePatternConstantGradient(const Model& model)
    : ModelObject(RoomAirTemperaturePatternConstantGradient::iddObjectType(), model) {}

  RoomAirTemperaturePatternConstantGradient::RoomAirTemperaturePatternConstantGradient(
    std::shared_ptr<detail::RoomAirTemperaturePatternConstantGradient_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirTemperaturePatternConstantGradient::iddObjectType() {
    return IddObjectType::RoomAir_TemperaturePattern_ConstantGradient;
  }

  int RoomAirTemperaturePatternConstantGradient::controlIntegerforPatternControlScheduleName() const {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->controlIntegerforPatternControlScheduleName();
  }

  bool RoomAirTemperaturePatternConstantGradient::setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName) {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->setControlIntegerforPatternControlScheduleName(
      controlIntegerforPatternControlScheduleName);
  }

  boost::optional<double> RoomAirTemperaturePatternConstantGradient::thermostatOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->thermostatOffset();
  }

  bool RoomAirTemperaturePatternConstantGradient::setThermostatOffset(double thermostatOffset) {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->setThermostatOffset(thermostatOffset);
  }

  void RoomAirTemperaturePatternConstantGradient::resetThermostatOffset() {
    getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->resetThermostatOffset();
  }

  boost::optional<double> RoomAirTemperaturePatternConstantGradient::returnAirOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->returnAirOffset();
  }

  bool RoomAirTemperaturePatternConstantGradient::setReturnAirOffset(double returnAirOffset) {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->setReturnAirOffset(returnAirOffset);
  }

  void RoomAirTemperaturePatternConstantGradient::resetReturnAirOffset() {
    getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->resetReturnAirOffset();
  }

  boost::optional<double> RoomAirTemperaturePatternConstantGradient::exhaustAirOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->exhaustAirOffset();
  }

  bool RoomAirTemperaturePatternConstantGradient::setExhaustAirOffset(double exhaustAirOffset) {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->setExhaustAirOffset(exhaustAirOffset);
  }

  void RoomAirTemperaturePatternConstantGradient::resetExhaustAirOffset() {
    getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->resetExhaustAirOffset();
  }

  boost::optional<double> RoomAirTemperaturePatternConstantGradient::temperatureGradient() const {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->temperatureGradient();
  }

  bool RoomAirTemperaturePatternConstantGradient::setTemperatureGradient(double temperatureGradient) {
    return getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->setTemperatureGradient(temperatureGradient);
  }

  void RoomAirTemperaturePatternConstantGradient::resetTemperatureGradient() {
    getImpl<detail::RoomAirTemperaturePatternConstantGradient_Impl>()->resetTemperatureGradient();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int RoomAirTemperaturePatternConstantGradient_Impl::controlIntegerforPatternControlScheduleName() const {
      const auto value = getInt(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ControlIntegerforPatternControlScheduleName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirTemperaturePatternConstantGradient_Impl::setControlIntegerforPatternControlScheduleName(
      int controlIntegerforPatternControlScheduleName) {
      const bool result = setInt(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ControlIntegerforPatternControlScheduleName,
                                 controlIntegerforPatternControlScheduleName);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RoomAirTemperaturePatternConstantGradient_Impl::thermostatOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ThermostatOffset, true);
    }

    bool RoomAirTemperaturePatternConstantGradient_Impl::setThermostatOffset(double thermostatOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ThermostatOffset, thermostatOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternConstantGradient_Impl::resetThermostatOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ThermostatOffset, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoomAirTemperaturePatternConstantGradient_Impl::returnAirOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ReturnAirOffset, true);
    }

    bool RoomAirTemperaturePatternConstantGradient_Impl::setReturnAirOffset(double returnAirOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ReturnAirOffset, returnAirOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternConstantGradient_Impl::resetReturnAirOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ReturnAirOffset, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoomAirTemperaturePatternConstantGradient_Impl::exhaustAirOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ExhaustAirOffset, true);
    }

    bool RoomAirTemperaturePatternConstantGradient_Impl::setExhaustAirOffset(double exhaustAirOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ExhaustAirOffset, exhaustAirOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternConstantGradient_Impl::resetExhaustAirOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::ExhaustAirOffset, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoomAirTemperaturePatternConstantGradient_Impl::temperatureGradient() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::TemperatureGradient, true);
    }

    bool RoomAirTemperaturePatternConstantGradient_Impl::setTemperatureGradient(double temperatureGradient) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::TemperatureGradient, temperatureGradient);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternConstantGradient_Impl::resetTemperatureGradient() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_ConstantGradientFields::TemperatureGradient, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
