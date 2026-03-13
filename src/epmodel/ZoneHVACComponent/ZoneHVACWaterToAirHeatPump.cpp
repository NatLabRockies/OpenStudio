/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp"
#include "ZoneHVACComponent/ZoneHVACWaterToAirHeatPump_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/StringHelpers.hpp"

#include <boost/optional.hpp>

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_WaterToAirHeatPump_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    bool getBooleanFieldValue(const detail::ModelObject_Impl& impl, int fieldIndex) {
      const auto value = impl.getString(fieldIndex, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool setBooleanFieldValue(detail::ModelObject_Impl& impl, int fieldIndex, bool value) {
      return impl.setString(fieldIndex, value ? "Yes" : "No");
    }

  }  // namespace

  ZoneHVACWaterToAirHeatPump::ZoneHVACWaterToAirHeatPump(const Model& model) : ModelObject(ZoneHVACWaterToAirHeatPump::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>());
  }

  ZoneHVACWaterToAirHeatPump::ZoneHVACWaterToAirHeatPump(std::shared_ptr<detail::ZoneHVACWaterToAirHeatPump_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACWaterToAirHeatPump::iddObjectType() {
    return IddObjectType::ZoneHVAC_WaterToAirHeatPump;
  }

  std::vector<std::string> ZoneHVACWaterToAirHeatPump::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACWaterToAirHeatPump::heatPumpCoilWaterFlowModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringCoolingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateDuringCoolingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateDuringHeatingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateDuringHeatingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACWaterToAirHeatPump::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(value);
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringCoolingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateDuringCoolingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateDuringHeatingOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateDuringHeatingOperation();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACWaterToAirHeatPump::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACWaterToAirHeatPump::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumSupplyAirTemperaturefromSupplementalHeater(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumSupplyAirTemperaturefromSupplementalHeater(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  void ZoneHVACWaterToAirHeatPump::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  boost::optional<double> ZoneHVACWaterToAirHeatPump::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->autosizedMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACWaterToAirHeatPump::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACWaterToAirHeatPump::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(boost::optional<double> value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(value);
  }

  bool ZoneHVACWaterToAirHeatPump::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(value);
  }

  void ZoneHVACWaterToAirHeatPump::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACWaterToAirHeatPump::fanPlacement() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->fanPlacement();
  }

  bool ZoneHVACWaterToAirHeatPump::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACWaterToAirHeatPump::resetFanPlacement() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetFanPlacement();
  }

  std::string ZoneHVACWaterToAirHeatPump::heatPumpCoilWaterFlowMode() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->heatPumpCoilWaterFlowMode();
  }

  bool ZoneHVACWaterToAirHeatPump::isHeatPumpCoilWaterFlowModeDefaulted() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->isHeatPumpCoilWaterFlowModeDefaulted();
  }

  bool ZoneHVACWaterToAirHeatPump::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setHeatPumpCoilWaterFlowMode(heatPumpCoilWaterFlowMode);
  }

  void ZoneHVACWaterToAirHeatPump::resetHeatPumpCoilWaterFlowMode() {
    getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->resetHeatPumpCoilWaterFlowMode();
  }

  double ZoneHVACWaterToAirHeatPump::dXHeatingCoilSizingRatio() const {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->dXHeatingCoilSizingRatio();
  }

  bool ZoneHVACWaterToAirHeatPump::setDXHeatingCoilSizingRatio(double value) {
    return getImpl<detail::ZoneHVACWaterToAirHeatPump_Impl>()->setDXHeatingCoilSizingRatio(value);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      bool result = false;
      if (supplyAirFlowRateDuringCoolingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateDuringCoolingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      bool result(false);
      if (supplyAirFlowRateDuringHeatingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateDuringHeatingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      bool result(false);
      if (supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get());
        OS_ASSERT(result);
      } else {
        resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      return getBooleanFieldValue(*this, ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setBooleanFieldValue(*this, ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                               noLoadSupplyAirFlowRateControlSetToLowSpeed);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      bool result(false);
      if (outdoorAirFlowRateDuringCoolingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateDuringCoolingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      bool result(false);
      if (outdoorAirFlowRateDuringHeatingOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateDuringHeatingOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      bool result(false);
      if (outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get());
        OS_ASSERT(result);
      } else {
        resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
        result = true;
      }
      return result;
    }

    bool
      ZoneHVACWaterToAirHeatPump_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, "Autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      boost::optional<double> maximumSupplyAirTemperaturefromSupplementalHeater) {
      bool result = false;
      if (maximumSupplyAirTemperaturefromSupplementalHeater) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                           maximumSupplyAirTemperaturefromSupplementalHeater.get());
        OS_ASSERT(result);
      } else {
        resetMaximumSupplyAirTemperaturefromSupplementalHeater();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                                    maximumSupplyAirTemperaturefromSupplementalHeater);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "");
      OS_ASSERT(result);
    }

    void ZoneHVACWaterToAirHeatPump_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize");
      OS_ASSERT(result);
    }

    double ZoneHVACWaterToAirHeatPump_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      boost::optional<double> maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = false;
      if (maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
        result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                           maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation.get());
        OS_ASSERT(result);
      } else {
        resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
        result = true;
      }
      return result;
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                                    maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "");
      OS_ASSERT(result);
    }

    std::string ZoneHVACWaterToAirHeatPump_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setFanPlacement(const std::string& fanPlacement) {
      const bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, fanPlacement);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, "");
      OS_ASSERT(result);
    }

    std::string ZoneHVACWaterToAirHeatPump_Impl::heatPumpCoilWaterFlowMode() const {
      auto value = getString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::isHeatPumpCoilWaterFlowModeDefaulted() const {
      return isEmpty(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode);
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setHeatPumpCoilWaterFlowMode(const std::string& heatPumpCoilWaterFlowMode) {
      const bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, heatPumpCoilWaterFlowMode);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACWaterToAirHeatPump_Impl::resetHeatPumpCoilWaterFlowMode() {
      bool result = setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, "");
      OS_ASSERT(result);
    }

    double ZoneHVACWaterToAirHeatPump_Impl::dXHeatingCoilSizingRatio() const {
      auto value = getDouble(ZoneHVAC_WaterToAirHeatPumpFields::DXHeatingCoilSizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACWaterToAirHeatPump_Impl::setDXHeatingCoilSizingRatio(double dXHeatingCoilSizingRatio) {
      const bool result = setDouble(ZoneHVAC_WaterToAirHeatPumpFields::DXHeatingCoilSizingRatio, dXHeatingCoilSizingRatio);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return {};
    }

    boost::optional<double> ZoneHVACWaterToAirHeatPump_Impl::autosizedMaximumSupplyAirTemperaturefromSupplementalHeater() const {
      return {};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
