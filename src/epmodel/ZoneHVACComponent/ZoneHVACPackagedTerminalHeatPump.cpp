/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalHeatPump_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_ZoneHVAC_PackagedTerminalHeatPump_FieldEnums.hxx>

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  ZoneHVACPackagedTerminalHeatPump::ZoneHVACPackagedTerminalHeatPump(const Model& model)
    : ModelObject(ZoneHVACPackagedTerminalHeatPump::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>());
  }

  ZoneHVACPackagedTerminalHeatPump::ZoneHVACPackagedTerminalHeatPump(std::shared_ptr<detail::ZoneHVACPackagedTerminalHeatPump_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACPackagedTerminalHeatPump::iddObjectType() {
    return IddObjectType::OS_ZoneHVAC_PackagedTerminalHeatPump;
  }

  std::vector<std::string> ZoneHVACPackagedTerminalHeatPump::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACPackagedTerminalHeatPump::validFanPlacementValues() {
    return fanPlacementValues();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
      supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(
      supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool
    ZoneHVACPackagedTerminalHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  double ZoneHVACPackagedTerminalHeatPump::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetHeatingConvergenceTolerance() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetHeatingConvergenceTolerance();
  }

  double ZoneHVACPackagedTerminalHeatPump::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  double ZoneHVACPackagedTerminalHeatPump::coolingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->coolingConvergenceTolerance();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isCoolingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isCoolingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setCoolingConvergenceTolerance(coolingConvergenceTolerance);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetCoolingConvergenceTolerance() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetCoolingConvergenceTolerance();
  }

  boost::optional<double> ZoneHVACPackagedTerminalHeatPump::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool
    ZoneHVACPackagedTerminalHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(
      maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void ZoneHVACPackagedTerminalHeatPump::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACPackagedTerminalHeatPump::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACPackagedTerminalHeatPump::fanPlacement() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->fanPlacement();
  }

  bool ZoneHVACPackagedTerminalHeatPump::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACPackagedTerminalHeatPump::resetFanPlacement() {
    getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->resetFanPlacement();
  }

  double ZoneHVACPackagedTerminalHeatPump::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool ZoneHVACPackagedTerminalHeatPump::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
    return getImpl<detail::ZoneHVACPackagedTerminalHeatPump_Impl>()->setDXHeatingCoilSizingRatio(dXHeatingCoilSizingRatio);
  }

  namespace detail {

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result = supplyAirFlowRateDuringCoolingOperation
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation,
                                        supplyAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result = supplyAirFlowRateDuringHeatingOperation
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation,
                                        supplyAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded,
                                        supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "Autosize", false);
      OS_ASSERT(result);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      auto value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
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

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No", false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = outdoorAirFlowRateDuringCoolingOperation
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation,
                                        outdoorAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = outdoorAirFlowRateDuringHeatingOperation
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation,
                                        outdoorAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::heatingConvergenceTolerance() const {
      boost::optional<double> value = getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      bool result = setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, heatingConvergenceTolerance, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetHeatingConvergenceTolerance() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      boost::optional<double> value =
        getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted() const {
      return isEmpty(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      bool result = setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                              minimumOutdoorDryBulbTemperatureforCompressorOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetMinimumOutdoorDryBulbTemperatureforCompressorOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::coolingConvergenceTolerance() const {
      boost::optional<double> value = getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isCoolingConvergenceToleranceDefaulted() const {
      return isEmpty(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setCoolingConvergenceTolerance(double coolingConvergenceTolerance) {
      bool result = setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, coolingConvergenceTolerance, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetCoolingConvergenceTolerance() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, "", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater) {
      const bool result = maximumSupplyAirTemperaturefromSupplementalHeater
                            ? setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                        maximumSupplyAirTemperaturefromSupplementalHeater.get(), false)
                            : setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                              maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACPackagedTerminalHeatPump_Impl::fanPlacement() const {
      auto value = getString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
      if (!value) {
        return std::string();
      }
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::isFanPlacementDefaulted() const {
      return isEmpty(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement);
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setFanPlacement(const std::string& fanPlacement) {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, fanPlacement, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalHeatPump_Impl::resetFanPlacement() {
      bool result = setString(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACPackagedTerminalHeatPump_Impl::dXHeatingCoilSizingRatio() const {
      boost::optional<double> value = getDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACPackagedTerminalHeatPump_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      bool result = setDouble(OS_ZoneHVAC_PackagedTerminalHeatPumpFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio, false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACPackagedTerminalHeatPump_Impl::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
      return {};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
