/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirTemperaturePatternTwoGradient.hpp"
#include "RoomAirTemperaturePatternTwoGradient_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoomAir_TemperaturePattern_TwoGradient_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirTemperaturePatternTwoGradient::RoomAirTemperaturePatternTwoGradient(const Model& model)
    : ModelObject(RoomAirTemperaturePatternTwoGradient::iddObjectType(), model) {}

  RoomAirTemperaturePatternTwoGradient::RoomAirTemperaturePatternTwoGradient(std::shared_ptr<detail::RoomAirTemperaturePatternTwoGradient_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirTemperaturePatternTwoGradient::iddObjectType() {
    return IddObjectType::RoomAir_TemperaturePattern_TwoGradient;
  }

  std::vector<std::string> RoomAirTemperaturePatternTwoGradient::gradientInterpolationModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::RoomAir_TemperaturePattern_TwoGradientFields::GradientInterpolationMode);
  }

  int RoomAirTemperaturePatternTwoGradient::controlIntegerforPatternControlScheduleName() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->controlIntegerforPatternControlScheduleName();
  }

  bool RoomAirTemperaturePatternTwoGradient::setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setControlIntegerforPatternControlScheduleName(
      controlIntegerforPatternControlScheduleName);
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::thermostatHeight() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->thermostatHeight();
  }

  bool RoomAirTemperaturePatternTwoGradient::setThermostatHeight(double thermostatHeight) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setThermostatHeight(thermostatHeight);
  }

  void RoomAirTemperaturePatternTwoGradient::resetThermostatHeight() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetThermostatHeight();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::returnAirHeight() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->returnAirHeight();
  }

  bool RoomAirTemperaturePatternTwoGradient::setReturnAirHeight(double returnAirHeight) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setReturnAirHeight(returnAirHeight);
  }

  void RoomAirTemperaturePatternTwoGradient::resetReturnAirHeight() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetReturnAirHeight();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::exhaustAirHeight() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->exhaustAirHeight();
  }

  bool RoomAirTemperaturePatternTwoGradient::setExhaustAirHeight(double exhaustAirHeight) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setExhaustAirHeight(exhaustAirHeight);
  }

  void RoomAirTemperaturePatternTwoGradient::resetExhaustAirHeight() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetExhaustAirHeight();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::temperatureGradientLowerBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->temperatureGradientLowerBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setTemperatureGradientLowerBound(double temperatureGradientLowerBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setTemperatureGradientLowerBound(temperatureGradientLowerBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetTemperatureGradientLowerBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetTemperatureGradientLowerBound();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::temperatureGradientUpperBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->temperatureGradientUpperBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setTemperatureGradientUpperBound(double temperatureGradientUpperBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setTemperatureGradientUpperBound(temperatureGradientUpperBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetTemperatureGradientUpperBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetTemperatureGradientUpperBound();
  }

  boost::optional<std::string> RoomAirTemperaturePatternTwoGradient::gradientInterpolationMode() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->gradientInterpolationMode();
  }

  bool RoomAirTemperaturePatternTwoGradient::setGradientInterpolationMode(const std::string& gradientInterpolationMode) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setGradientInterpolationMode(gradientInterpolationMode);
  }

  void RoomAirTemperaturePatternTwoGradient::resetGradientInterpolationMode() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetGradientInterpolationMode();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::upperTemperatureBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->upperTemperatureBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setUpperTemperatureBound(double upperTemperatureBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setUpperTemperatureBound(upperTemperatureBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetUpperTemperatureBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetUpperTemperatureBound();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::lowerTemperatureBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->lowerTemperatureBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setLowerTemperatureBound(double lowerTemperatureBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setLowerTemperatureBound(lowerTemperatureBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetLowerTemperatureBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetLowerTemperatureBound();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::upperHeatRateBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->upperHeatRateBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setUpperHeatRateBound(double upperHeatRateBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setUpperHeatRateBound(upperHeatRateBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetUpperHeatRateBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetUpperHeatRateBound();
  }

  boost::optional<double> RoomAirTemperaturePatternTwoGradient::lowerHeatRateBound() const {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->lowerHeatRateBound();
  }

  bool RoomAirTemperaturePatternTwoGradient::setLowerHeatRateBound(double lowerHeatRateBound) {
    return getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->setLowerHeatRateBound(lowerHeatRateBound);
  }

  void RoomAirTemperaturePatternTwoGradient::resetLowerHeatRateBound() {
    getImpl<detail::RoomAirTemperaturePatternTwoGradient_Impl>()->resetLowerHeatRateBound();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int RoomAirTemperaturePatternTwoGradient_Impl::controlIntegerforPatternControlScheduleName() const {
      const auto value = getInt(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ControlIntegerforPatternControlScheduleName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setControlIntegerforPatternControlScheduleName(int controlIntegerforPatternControlScheduleName) {
      const bool result = setInt(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ControlIntegerforPatternControlScheduleName,
                                 controlIntegerforPatternControlScheduleName);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::thermostatHeight() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ThermostatHeight, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setThermostatHeight(double thermostatHeight) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ThermostatHeight, thermostatHeight);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetThermostatHeight() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ThermostatHeight, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::returnAirHeight() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ReturnAirHeight, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setReturnAirHeight(double returnAirHeight) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ReturnAirHeight, returnAirHeight);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetReturnAirHeight() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ReturnAirHeight, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::exhaustAirHeight() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ExhaustAirHeight, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setExhaustAirHeight(double exhaustAirHeight) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ExhaustAirHeight, exhaustAirHeight);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetExhaustAirHeight() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::ExhaustAirHeight, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::temperatureGradientLowerBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientLowerBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setTemperatureGradientLowerBound(double temperatureGradientLowerBound) {
      const bool result =
        setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientLowerBound, temperatureGradientLowerBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetTemperatureGradientLowerBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientLowerBound, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::temperatureGradientUpperBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientUpperBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setTemperatureGradientUpperBound(double temperatureGradientUpperBound) {
      const bool result =
        setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientUpperBound, temperatureGradientUpperBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetTemperatureGradientUpperBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::TemperatureGradientUpperBound, ""));
    }

    boost::optional<std::string> RoomAirTemperaturePatternTwoGradient_Impl::gradientInterpolationMode() const {
      if (auto value = getString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::GradientInterpolationMode, false)) {
        if (!value->empty()) {
          return value;
        }
      }
      return boost::none;
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setGradientInterpolationMode(const std::string& gradientInterpolationMode) {
      return setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::GradientInterpolationMode, gradientInterpolationMode);
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetGradientInterpolationMode() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::GradientInterpolationMode, "", false));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::upperTemperatureBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperTemperatureBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setUpperTemperatureBound(double upperTemperatureBound) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperTemperatureBound, upperTemperatureBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetUpperTemperatureBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperTemperatureBound, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::lowerTemperatureBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerTemperatureBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setLowerTemperatureBound(double lowerTemperatureBound) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerTemperatureBound, lowerTemperatureBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetLowerTemperatureBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerTemperatureBound, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::upperHeatRateBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperHeatRateBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setUpperHeatRateBound(double upperHeatRateBound) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperHeatRateBound, upperHeatRateBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetUpperHeatRateBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::UpperHeatRateBound, ""));
    }

    boost::optional<double> RoomAirTemperaturePatternTwoGradient_Impl::lowerHeatRateBound() const {
      return getDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerHeatRateBound, true);
    }

    bool RoomAirTemperaturePatternTwoGradient_Impl::setLowerHeatRateBound(double lowerHeatRateBound) {
      const bool result = setDouble(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerHeatRateBound, lowerHeatRateBound);
      OS_ASSERT(result);
      return result;
    }

    void RoomAirTemperaturePatternTwoGradient_Impl::resetLowerHeatRateBound() {
      OS_ASSERT(setString(openstudio::RoomAir_TemperaturePattern_TwoGradientFields::LowerHeatRateBound, ""));
    }

    std::vector<std::string> RoomAirTemperaturePatternTwoGradient_Impl::gradientInterpolationModeValues() const {
      return openstudio::epmodel::RoomAirTemperaturePatternTwoGradient::gradientInterpolationModeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
