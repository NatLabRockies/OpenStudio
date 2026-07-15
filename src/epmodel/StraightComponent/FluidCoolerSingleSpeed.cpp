/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FluidCoolerSingleSpeed.hpp"
#include "StraightComponent/FluidCoolerSingleSpeed_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/FluidCooler_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  FluidCoolerSingleSpeed::FluidCoolerSingleSpeed(const Model& model) : StraightComponent(FluidCoolerSingleSpeed::iddObjectType(), model) {
    bool ok = true;
    ok = setPerformanceInputMethod("NominalCapacity");
    OS_ASSERT(ok);
    autosizeDesignAirFlowRateUfactorTimesAreaValue();
    ok = setNominalCapacity(58601.0);
    OS_ASSERT(ok);
    ok = setDesignEnteringWaterTemperature(51.67);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirTemperature(35.0);
    OS_ASSERT(ok);
    ok = setDesignEnteringAirWetbulbTemperature(25.6);
    OS_ASSERT(ok);
    ok = setDesignWaterFlowRate(0.001388);
    OS_ASSERT(ok);
    ok = setDesignAirFlowRate(9.911);
    OS_ASSERT(ok);
    autosizeDesignAirFlowRateFanPower();
  }

  FluidCoolerSingleSpeed::FluidCoolerSingleSpeed(std::shared_ptr<detail::FluidCoolerSingleSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FluidCoolerSingleSpeed::iddObjectType() {
    return IddObjectType::FluidCooler_SingleSpeed;
  }

  std::vector<std::string> FluidCoolerSingleSpeed::performanceInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod);
  }

  std::string FluidCoolerSingleSpeed::performanceInputMethod() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->performanceInputMethod();
  }

  bool FluidCoolerSingleSpeed::setPerformanceInputMethod(const std::string& performanceInputMethod) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setPerformanceInputMethod(performanceInputMethod);
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRateUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRateUfactorTimesAreaValue();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateUfactorTimesAreaValueAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateUfactorTimesAreaValueAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRateUfactorTimesAreaValue(double designAirFlowRateUfactorTimesAreaValue) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRateUfactorTimesAreaValue(designAirFlowRateUfactorTimesAreaValue);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRateUfactorTimesAreaValue() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRateUfactorTimesAreaValue();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRateUfactorTimesAreaValue() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRateUfactorTimesAreaValue();
  }

  double FluidCoolerSingleSpeed::nominalCapacity() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->nominalCapacity();
  }

  bool FluidCoolerSingleSpeed::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setNominalCapacity(nominalCapacity);
  }

  double FluidCoolerSingleSpeed::designEnteringWaterTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringWaterTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringWaterTemperature(double designEnteringWaterTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringWaterTemperature(designEnteringWaterTemperature);
  }

  double FluidCoolerSingleSpeed::designEnteringAirTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringAirTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringAirTemperature(double designEnteringAirTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirTemperature(designEnteringAirTemperature);
  }

  double FluidCoolerSingleSpeed::designEnteringAirWetbulbTemperature() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designEnteringAirWetbulbTemperature();
  }

  bool FluidCoolerSingleSpeed::setDesignEnteringAirWetbulbTemperature(double designEnteringAirWetbulbTemperature) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignEnteringAirWetbulbTemperature(designEnteringAirWetbulbTemperature);
  }

  boost::optional<double> FluidCoolerSingleSpeed::designWaterFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designWaterFlowRate();
  }

  bool FluidCoolerSingleSpeed::isDesignWaterFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignWaterFlowRateAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignWaterFlowRate(double designWaterFlowRate) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignWaterFlowRate(designWaterFlowRate);
  }

  void FluidCoolerSingleSpeed::autosizeDesignWaterFlowRate() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignWaterFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignWaterFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRate();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRate(double designAirFlowRate) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRate(designAirFlowRate);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRate() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRate() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRate();
  }

  boost::optional<double> FluidCoolerSingleSpeed::designAirFlowRateFanPower() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->designAirFlowRateFanPower();
  }

  bool FluidCoolerSingleSpeed::isDesignAirFlowRateFanPowerAutosized() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->isDesignAirFlowRateFanPowerAutosized();
  }

  bool FluidCoolerSingleSpeed::setDesignAirFlowRateFanPower(double designAirFlowRateFanPower) {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->setDesignAirFlowRateFanPower(designAirFlowRateFanPower);
  }

  void FluidCoolerSingleSpeed::autosizeDesignAirFlowRateFanPower() {
    getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizeDesignAirFlowRateFanPower();
  }

  boost::optional<double> FluidCoolerSingleSpeed::autosizedDesignAirFlowRateFanPower() const {
    return getImpl<detail::FluidCoolerSingleSpeed_Impl>()->autosizedDesignAirFlowRateFanPower();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FluidCoolerSingleSpeed_Impl::inletPort() const {
      return openstudio::FluidCooler_SingleSpeedFields::WaterInletNodeName;
    }

    unsigned FluidCoolerSingleSpeed_Impl::outletPort() const {
      return openstudio::FluidCooler_SingleSpeedFields::WaterOutletNodeName;
    }

    bool FluidCoolerSingleSpeed_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->supplyComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }

      return false;
    }

    std::vector<std::string> FluidCoolerSingleSpeed_Impl::performanceInputMethodValues() const {
      return FluidCoolerSingleSpeed::performanceInputMethodValues();
    }

    std::string FluidCoolerSingleSpeed_Impl::performanceInputMethod() const {
      const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setPerformanceInputMethod(const std::string& performanceInputMethod) {
      return setString(openstudio::FluidCooler_SingleSpeedFields::PerformanceInputMethod, performanceInputMethod);
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRateUfactorTimesAreaValue() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateUfactorTimesAreaValueAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRateUfactorTimesAreaValue(boost::optional<double> designAirFlowRateUfactorTimesAreaValue) {
      bool result = false;
      if (designAirFlowRateUfactorTimesAreaValue) {
        result =
          setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, *designAirFlowRateUfactorTimesAreaValue);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRateUfactorTimesAreaValue() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateUfactorTimesAreaValue, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRateUfactorTimesAreaValue() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    double FluidCoolerSingleSpeed_Impl::nominalCapacity() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::NominalCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::FluidCooler_SingleSpeedFields::NominalCapacity, nominalCapacity);
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringWaterTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringWaterTemperature(boost::optional<double> designEnteringWaterTemperature) {
      bool result = false;
      if (designEnteringWaterTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringWaterTemperature, *designEnteringWaterTemperature);
      }
      return result;
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringAirTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringAirTemperature(boost::optional<double> designEnteringAirTemperature) {
      bool result = false;
      if (designEnteringAirTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirTemperature, *designEnteringAirTemperature);
      }
      return result;
    }

    double FluidCoolerSingleSpeed_Impl::designEnteringAirWetbulbTemperature() const {
      const auto value = getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignEnteringAirWetbulbTemperature(boost::optional<double> designEnteringAirWetbulbTemperature) {
      bool result = false;
      if (designEnteringAirWetbulbTemperature) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignEnteringAirWetbulbTemperature, *designEnteringAirWetbulbTemperature);
      }
      return result;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designWaterFlowRate() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignWaterFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignWaterFlowRate(boost::optional<double> designWaterFlowRate) {
      bool result = false;
      if (designWaterFlowRate) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, *designWaterFlowRate);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignWaterFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignWaterFlowRate, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignWaterFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRate() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRate(boost::optional<double> designAirFlowRate) {
      bool result = false;
      if (designAirFlowRate) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, *designAirFlowRate);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRate() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRate, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRate() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::designAirFlowRateFanPower() const {
      return getDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true);
    }

    bool FluidCoolerSingleSpeed_Impl::isDesignAirFlowRateFanPowerAutosized() const {
      if (const auto value = getString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FluidCoolerSingleSpeed_Impl::setDesignAirFlowRateFanPower(boost::optional<double> designAirFlowRateFanPower) {
      bool result = false;
      if (designAirFlowRateFanPower) {
        result = setDouble(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, *designAirFlowRateFanPower);
      }
      return result;
    }

    void FluidCoolerSingleSpeed_Impl::autosizeDesignAirFlowRateFanPower() {
      OS_ASSERT(setString(openstudio::FluidCooler_SingleSpeedFields::DesignAirFlowRateFanPower, "Autosize"));
    }

    boost::optional<double> FluidCoolerSingleSpeed_Impl::autosizedDesignAirFlowRateFanPower() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
