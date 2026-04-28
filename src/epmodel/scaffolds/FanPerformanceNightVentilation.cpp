/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FanPerformanceNightVentilation.hpp"
#include "FanPerformanceNightVentilation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/FanPerformance_NightVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FanPerformanceNightVentilation::FanPerformanceNightVentilation(const Model& model)
    : ModelObject(FanPerformanceNightVentilation::iddObjectType(), model) {}

  FanPerformanceNightVentilation::FanPerformanceNightVentilation(std::shared_ptr<detail::FanPerformanceNightVentilation_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType FanPerformanceNightVentilation::iddObjectType() {
    return IddObjectType::FanPerformance_NightVentilation;
  }

  double FanPerformanceNightVentilation::fanTotalEfficiency() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->fanTotalEfficiency();
  }

  bool FanPerformanceNightVentilation::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  double FanPerformanceNightVentilation::pressureRise() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->pressureRise();
  }

  bool FanPerformanceNightVentilation::setPressureRise(double pressureRise) {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->setPressureRise(pressureRise);
  }

  boost::optional<double> FanPerformanceNightVentilation::maximumFlowRate() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->maximumFlowRate();
  }

  bool FanPerformanceNightVentilation::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void FanPerformanceNightVentilation::resetMaximumFlowRate() {
    getImpl<detail::FanPerformanceNightVentilation_Impl>()->resetMaximumFlowRate();
  }

  void FanPerformanceNightVentilation::autosizeMaximumFlowRate() {
    getImpl<detail::FanPerformanceNightVentilation_Impl>()->autosizeMaximumFlowRate();
  }

  bool FanPerformanceNightVentilation::isMaximumFlowRateAutosized() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->isMaximumFlowRateAutosized();
  }

  double FanPerformanceNightVentilation::motorEfficiency() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->motorEfficiency();
  }

  bool FanPerformanceNightVentilation::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  double FanPerformanceNightVentilation::motorinAirstreamFraction() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->motorinAirstreamFraction();
  }

  bool FanPerformanceNightVentilation::setMotorinAirstreamFraction(double motorinAirstreamFraction) {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->setMotorinAirstreamFraction(motorinAirstreamFraction);
  }

  void FanPerformanceNightVentilation::resetMotorinAirstreamFraction() {
    getImpl<detail::FanPerformanceNightVentilation_Impl>()->resetMotorinAirstreamFraction();
  }

  bool FanPerformanceNightVentilation::isMotorinAirstreamFractionDefaulted() const {
    return getImpl<detail::FanPerformanceNightVentilation_Impl>()->isMotorinAirstreamFractionDefaulted();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double FanPerformanceNightVentilation_Impl::fanTotalEfficiency() const {
      const auto value = getDouble(openstudio::FanPerformance_NightVentilationFields::FanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanPerformanceNightVentilation_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      return setDouble(openstudio::FanPerformance_NightVentilationFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    double FanPerformanceNightVentilation_Impl::pressureRise() const {
      const auto value = getDouble(openstudio::FanPerformance_NightVentilationFields::PressureRise, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanPerformanceNightVentilation_Impl::setPressureRise(double pressureRise) {
      const bool result = setDouble(openstudio::FanPerformance_NightVentilationFields::PressureRise, pressureRise);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> FanPerformanceNightVentilation_Impl::maximumFlowRate() const {
      return getDouble(openstudio::FanPerformance_NightVentilationFields::MaximumFlowRate, true);
    }

    bool FanPerformanceNightVentilation_Impl::setMaximumFlowRate(double maximumFlowRate) {
      return setDouble(openstudio::FanPerformance_NightVentilationFields::MaximumFlowRate, maximumFlowRate);
    }

    void FanPerformanceNightVentilation_Impl::resetMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::FanPerformance_NightVentilationFields::MaximumFlowRate, ""));
    }

    void FanPerformanceNightVentilation_Impl::autosizeMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::FanPerformance_NightVentilationFields::MaximumFlowRate, "autosize"));
    }

    bool FanPerformanceNightVentilation_Impl::isMaximumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FanPerformance_NightVentilationFields::MaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FanPerformanceNightVentilation_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::FanPerformance_NightVentilationFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanPerformanceNightVentilation_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::FanPerformance_NightVentilationFields::MotorEfficiency, motorEfficiency);
    }

    double FanPerformanceNightVentilation_Impl::motorinAirstreamFraction() const {
      const auto value = getDouble(openstudio::FanPerformance_NightVentilationFields::MotorinAirstreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanPerformanceNightVentilation_Impl::setMotorinAirstreamFraction(double motorinAirstreamFraction) {
      return setDouble(openstudio::FanPerformance_NightVentilationFields::MotorinAirstreamFraction, motorinAirstreamFraction);
    }

    void FanPerformanceNightVentilation_Impl::resetMotorinAirstreamFraction() {
      OS_ASSERT(setString(openstudio::FanPerformance_NightVentilationFields::MotorinAirstreamFraction, ""));
    }

    bool FanPerformanceNightVentilation_Impl::isMotorinAirstreamFractionDefaulted() const {
      return isEmpty(openstudio::FanPerformance_NightVentilationFields::MotorinAirstreamFraction);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
