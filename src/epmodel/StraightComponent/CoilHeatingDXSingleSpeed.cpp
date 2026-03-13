/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingDXSingleSpeed::CoilHeatingDXSingleSpeed(const Model& model) : StraightComponent(CoilHeatingDXSingleSpeed::iddObjectType(), model) {
    bool ok = true;

    autosizeRatedTotalHeatingCapacity();
    autosizeRatedAirFlowRate();

    ok = setRatedSupplyFanPowerPerVolumeFlowRate2017(773.3);
    OS_ASSERT(ok);
    ok = setRatedSupplyFanPowerPerVolumeFlowRate2023(934.4);
    OS_ASSERT(ok);
    ok = setRatedCOP(5.0);
    OS_ASSERT(ok);

    ok = setDefrostStrategy("Resistive");
    OS_ASSERT(ok);
    ok = setDefrostControl("Timed");
    OS_ASSERT(ok);
    ok = setDefrostTimePeriodFraction(0.166667);
    OS_ASSERT(ok);
    ok = setResistiveDefrostHeaterCapacity(2000.0);
    OS_ASSERT(ok);
  }

  CoilHeatingDXSingleSpeed::CoilHeatingDXSingleSpeed(std::shared_ptr<detail::CoilHeatingDXSingleSpeed_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDXSingleSpeed::iddObjectType() {
    return IddObjectType::Coil_Heating_DX_SingleSpeed;
  }

  std::vector<std::string> CoilHeatingDXSingleSpeed::validDefrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy);
  }

  std::vector<std::string> CoilHeatingDXSingleSpeed::validDefrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl);
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::ratedTotalHeatingCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedTotalHeatingCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isRatedTotalHeatingCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isRatedTotalHeatingCapacityAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedTotalHeatingCapacity(ratedTotalHeatingCapacity);
  }

  void CoilHeatingDXSingleSpeed::autosizeRatedTotalHeatingCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeRatedTotalHeatingCapacity();
  }

  double CoilHeatingDXSingleSpeed::ratedCOP() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedCOP();
  }

  bool CoilHeatingDXSingleSpeed::setRatedCOP(double ratedCOP) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedCOP(ratedCOP);
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::ratedAirFlowRate() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedAirFlowRate();
  }

  bool CoilHeatingDXSingleSpeed::isRatedAirFlowRateAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isRatedAirFlowRateAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setRatedAirFlowRate(double ratedAirFlowRate) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
  }

  void CoilHeatingDXSingleSpeed::autosizeRatedAirFlowRate() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeRatedAirFlowRate();
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2017();
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate2017() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2017();
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate(double ratedSupplyFanPowerPerVolumeFlowRate) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2017(ratedSupplyFanPowerPerVolumeFlowRate);
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2017(ratedSupplyFanPowerPerVolumeFlowRate2017);
  }

  double CoilHeatingDXSingleSpeed::ratedSupplyFanPowerPerVolumeFlowRate2023() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->ratedSupplyFanPowerPerVolumeFlowRate2023();
  }

  bool CoilHeatingDXSingleSpeed::setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setRatedSupplyFanPowerPerVolumeFlowRate2023(ratedSupplyFanPowerPerVolumeFlowRate2023);
  }

  double CoilHeatingDXSingleSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  double CoilHeatingDXSingleSpeed::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforDefrostOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      maximumOutdoorDryBulbTemperatureforDefrostOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMaximumOutdoorDryBulbTemperatureforDefrostOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();
  }

  double CoilHeatingDXSingleSpeed::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isCrankcaseHeaterCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isCrankcaseHeaterCapacityDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  void CoilHeatingDXSingleSpeed::resetCrankcaseHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetCrankcaseHeaterCapacity();
  }

  double CoilHeatingDXSingleSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilHeatingDXSingleSpeed::isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  }

  void CoilHeatingDXSingleSpeed::resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  std::string CoilHeatingDXSingleSpeed::defrostStrategy() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostStrategy();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostStrategyDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostStrategyDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostStrategy() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostStrategy();
  }

  std::string CoilHeatingDXSingleSpeed::defrostControl() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostControl();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostControlDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostControlDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostControl(const std::string& defrostControl) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostControl(defrostControl);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostControl() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostControl();
  }

  double CoilHeatingDXSingleSpeed::defrostTimePeriodFraction() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->defrostTimePeriodFraction();
  }

  bool CoilHeatingDXSingleSpeed::isDefrostTimePeriodFractionDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isDefrostTimePeriodFractionDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setDefrostTimePeriodFraction(defrostTimePeriodFraction);
  }

  void CoilHeatingDXSingleSpeed::resetDefrostTimePeriodFraction() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetDefrostTimePeriodFraction();
  }

  boost::optional<double> CoilHeatingDXSingleSpeed::resistiveDefrostHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resistiveDefrostHeaterCapacity();
  }

  bool CoilHeatingDXSingleSpeed::isResistiveDefrostHeaterCapacityDefaulted() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isResistiveDefrostHeaterCapacityDefaulted();
  }

  bool CoilHeatingDXSingleSpeed::isResistiveDefrostHeaterCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
  }

  bool CoilHeatingDXSingleSpeed::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
  }

  void CoilHeatingDXSingleSpeed::resetResistiveDefrostHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->resetResistiveDefrostHeaterCapacity();
  }

  void CoilHeatingDXSingleSpeed::autosizeResistiveDefrostHeaterCapacity() {
    getImpl<detail::CoilHeatingDXSingleSpeed_Impl>()->autosizeResistiveDefrostHeaterCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool isAutosized(const ModelObject_Impl& impl, int fieldIndex) {
        if (const auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

    }  // namespace

    unsigned CoilHeatingDXSingleSpeed_Impl::inletPort() const {
      return openstudio::Coil_Heating_DX_SingleSpeedFields::AirInletNodeName;
    }

    unsigned CoilHeatingDXSingleSpeed_Impl::outletPort() const {
      return openstudio::Coil_Heating_DX_SingleSpeedFields::AirOutletNodeName;
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::ratedTotalHeatingCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isRatedTotalHeatingCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity);
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedCOP() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::ratedAirFlowRate() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isRatedAirFlowRateAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate);
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedSupplyFanPowerPerVolumeFlowRate2017() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2017, true);
      OS_ASSERT(value);
      return *value;
    }

    double CoilHeatingDXSingleSpeed_Impl::ratedSupplyFanPowerPerVolumeFlowRate2023() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2023, true);
      OS_ASSERT(value);
      return *value;
    }

    double CoilHeatingDXSingleSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    double CoilHeatingDXSingleSpeed_Impl::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation);
    }

    double CoilHeatingDXSingleSpeed_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isCrankcaseHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity);
    }

    double CoilHeatingDXSingleSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    std::vector<std::string> CoilHeatingDXSingleSpeed_Impl::validDefrostStrategyValues() const {
      return CoilHeatingDXSingleSpeed::validDefrostStrategyValues();
    }

    std::string CoilHeatingDXSingleSpeed_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostStrategyDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy);
    }

    std::vector<std::string> CoilHeatingDXSingleSpeed_Impl::validDefrostControlValues() const {
      return CoilHeatingDXSingleSpeed::validDefrostControlValues();
    }

    std::string CoilHeatingDXSingleSpeed_Impl::defrostControl() const {
      const auto value = getString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostControlDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl);
    }

    double CoilHeatingDXSingleSpeed_Impl::defrostTimePeriodFraction() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXSingleSpeed_Impl::isDefrostTimePeriodFractionDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction);
    }

    boost::optional<double> CoilHeatingDXSingleSpeed_Impl::resistiveDefrostHeaterCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, true);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isResistiveDefrostHeaterCapacityDefaulted() const {
      return isEmpty(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity);
    }

    bool CoilHeatingDXSingleSpeed_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
      return isAutosized(*this, openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedTotalHeatingCapacity(double ratedTotalHeatingCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, ratedTotalHeatingCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeRatedTotalHeatingCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCapacity, "autosize");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedCOP(double ratedCOP) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::GrossRatedHeatingCOP, ratedCOP);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedAirFlowRate(double ratedAirFlowRate) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, ratedAirFlowRate);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeRatedAirFlowRate() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedAirFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedSupplyFanPowerPerVolumeFlowRate2017(double ratedSupplyFanPowerPerVolumeFlowRate2017) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2017,
                       ratedSupplyFanPowerPerVolumeFlowRate2017);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setRatedSupplyFanPowerPerVolumeFlowRate2023(double ratedSupplyFanPowerPerVolumeFlowRate2023) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::RatedSupplyFanPowerPerVolumeFlowRate2023,
                       ratedSupplyFanPowerPerVolumeFlowRate2023);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                       minimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation,
                       maximumOutdoorDryBulbTemperatureforDefrostOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMaximumOutdoorDryBulbTemperatureforDefrostOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetCrankcaseHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacity, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, defrostStrategy);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostStrategy() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostStrategy, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostControl(const std::string& defrostControl) {
      return setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, defrostControl);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostControl() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostControl, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, defrostTimePeriodFraction);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetDefrostTimePeriodFraction() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostTimePeriodFraction, "");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXSingleSpeed_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
    }

    void CoilHeatingDXSingleSpeed_Impl::resetResistiveDefrostHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingDXSingleSpeed_Impl::autosizeResistiveDefrostHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_SingleSpeedFields::ResistiveDefrostHeaterCapacity, "autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
