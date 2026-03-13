/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirTemperaturePatternNondimensionalHeight.hpp"
#include "RoomAirTemperaturePatternNondimensionalHeight_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/RoomAir_TemperaturePattern_NondimensionalHeight_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirTemperaturePatternNondimensionalHeight::RoomAirTemperaturePatternNondimensionalHeight(const Model& model)
    : ModelObject(RoomAirTemperaturePatternNondimensionalHeight::iddObjectType(), model) {}

  RoomAirTemperaturePatternNondimensionalHeight::RoomAirTemperaturePatternNondimensionalHeight(
    std::shared_ptr<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirTemperaturePatternNondimensionalHeight::iddObjectType() {
    return IddObjectType::RoomAir_TemperaturePattern_NondimensionalHeight;
  }

  int RoomAirTemperaturePatternNondimensionalHeight::controlIntegerforPatternControlScheduleName() const {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->controlIntegerforPatternControlScheduleName();
  }

  bool
    RoomAirTemperaturePatternNondimensionalHeight::setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName) {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->setControlIntegerforPatternControlScheduleName(
      controlIntegerforPatternControlScheduleName);
  }

  boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight::thermostatOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->thermostatOffset();
  }

  bool RoomAirTemperaturePatternNondimensionalHeight::setThermostatOffset(double thermostatOffset) {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->setThermostatOffset(thermostatOffset);
  }

  void RoomAirTemperaturePatternNondimensionalHeight::resetThermostatOffset() {
    getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->resetThermostatOffset();
  }

  boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight::returnAirOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->returnAirOffset();
  }

  bool RoomAirTemperaturePatternNondimensionalHeight::setReturnAirOffset(double returnAirOffset) {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->setReturnAirOffset(returnAirOffset);
  }

  void RoomAirTemperaturePatternNondimensionalHeight::resetReturnAirOffset() {
    getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->resetReturnAirOffset();
  }

  boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight::exhaustAirOffset() const {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->exhaustAirOffset();
  }

  bool RoomAirTemperaturePatternNondimensionalHeight::setExhaustAirOffset(double exhaustAirOffset) {
    return getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->setExhaustAirOffset(exhaustAirOffset);
  }

  void RoomAirTemperaturePatternNondimensionalHeight::resetExhaustAirOffset() {
    getImpl<detail::RoomAirTemperaturePatternNondimensionalHeight_Impl>()->resetExhaustAirOffset();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int RoomAirTemperaturePatternNondimensionalHeight_Impl::controlIntegerforPatternControlScheduleName() const {
      const auto value = getInt(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ControlIntegerforPatternControlScheduleName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirTemperaturePatternNondimensionalHeight_Impl::setControlIntegerforPatternControlScheduleName(
      int controlIntegerforPatternControlScheduleName) {
      const bool result = setInt(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ControlIntegerforPatternControlScheduleName,
                                 controlIntegerforPatternControlScheduleName);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight_Impl::thermostatOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ThermostatOffset, true);
    }

    bool RoomAirTemperaturePatternNondimensionalHeight_Impl::setThermostatOffset(double thermostatOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ThermostatOffset, thermostatOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternNondimensionalHeight_Impl::resetThermostatOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ThermostatOffset, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight_Impl::returnAirOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ReturnAirOffset, true);
    }

    bool RoomAirTemperaturePatternNondimensionalHeight_Impl::setReturnAirOffset(double returnAirOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ReturnAirOffset, returnAirOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternNondimensionalHeight_Impl::resetReturnAirOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ReturnAirOffset, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoomAirTemperaturePatternNondimensionalHeight_Impl::exhaustAirOffset() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ExhaustAirOffset, true);
    }

    bool RoomAirTemperaturePatternNondimensionalHeight_Impl::setExhaustAirOffset(double exhaustAirOffset) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ExhaustAirOffset, exhaustAirOffset);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternNondimensionalHeight_Impl::resetExhaustAirOffset() {
      const bool result = setString(openstudio::RoomAir_TemperaturePattern_NondimensionalHeightFields::ExhaustAirOffset, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
