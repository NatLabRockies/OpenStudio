/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(const Model& model)
    : ModelObject(ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>());
  }

  ZoneHVACTerminalUnitVariableRefrigerantFlow::ZoneHVACTerminalUnitVariableRefrigerantFlow(
    std::shared_ptr<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACTerminalUnitVariableRefrigerantFlow::iddObjectType() {
    return IddObjectType::OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlow;
  }

  std::vector<std::string> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
  }

  namespace {

    const detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(const ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

    detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl* impl(ZoneHVACTerminalUnitVariableRefrigerantFlow* object) {
      return object->getImpl<detail::ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl>().get();
    }

  }  // namespace

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringCoolingOperation() const {
    return impl(this)->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringCoolingOperation(supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoCoolingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoCoolingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoCoolingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoCoolingisNeeded(double supplyAirFlowRateWhenNoCoolingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoCoolingisNeeded(supplyAirFlowRateWhenNoCoolingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoCoolingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateDuringHeatingOperation() const {
    return impl(this)->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return impl(this)->setSupplyAirFlowRateDuringHeatingOperation(supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFlowRateWhenNoHeatingisNeeded() const {
    return impl(this)->supplyAirFlowRateWhenNoHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
    return impl(this)->isSupplyAirFlowRateWhenNoHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFlowRateWhenNoHeatingisNeeded(double supplyAirFlowRateWhenNoHeatingisNeeded) {
    return impl(this)->setSupplyAirFlowRateWhenNoHeatingisNeeded(supplyAirFlowRateWhenNoHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->resetSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
    impl(this)->autosizeSupplyAirFlowRateWhenNoHeatingisNeeded();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringCoolingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringCoolingOperation(outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateDuringHeatingOperation() const {
    return impl(this)->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return impl(this)->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return impl(this)->setOutdoorAirFlowRateDuringHeatingOperation(outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    impl(this)->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return impl(this)->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return impl(this)->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return impl(this)->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    impl(this)->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOnParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOnParasiticElectricEnergyUse(
    double zoneTerminalUnitOnParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOnParasiticElectricEnergyUse(zoneTerminalUnitOnParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
    return impl(this)->zoneTerminalUnitOffParasiticElectricEnergyUse();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setZoneTerminalUnitOffParasiticElectricEnergyUse(
    double zoneTerminalUnitOffParasiticElectricEnergyUse) {
    return impl(this)->setZoneTerminalUnitOffParasiticElectricEnergyUse(zoneTerminalUnitOffParasiticElectricEnergyUse);
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::ratedTotalHeatingCapacitySizingRatio() const {
    return impl(this)->ratedTotalHeatingCapacitySizingRatio();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
    return impl(this)->setRatedTotalHeatingCapacitySizingRatio(ratedTotalHeatingCapacitySizingRatio);
  }

  boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumSupplyAirTemperaturefromSupplementalHeater() const {
    return impl(this)->maximumSupplyAirTemperaturefromSupplementalHeater();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
    return impl(this)->isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumSupplyAirTemperaturefromSupplementalHeater(
    double maximumSupplyAirTemperaturefromSupplementalHeater) {
    return impl(this)->setMaximumSupplyAirTemperaturefromSupplementalHeater(maximumSupplyAirTemperaturefromSupplementalHeater);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
    impl(this)->autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  }

  double ZoneHVACTerminalUnitVariableRefrigerantFlow::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
    return impl(this)->maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
    return impl(this)->isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
    return impl(this)->setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
    impl(this)->resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  }

  std::string ZoneHVACTerminalUnitVariableRefrigerantFlow::supplyAirFanPlacement() const {
    return impl(this)->supplyAirFanPlacement();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::isSupplyAirFanPlacementDefaulted() const {
    return impl(this)->isSupplyAirFanPlacementDefaulted();
  }

  bool ZoneHVACTerminalUnitVariableRefrigerantFlow::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
    return impl(this)->setSupplyAirFanPlacement(supplyAirFanPlacement);
  }

  void ZoneHVACTerminalUnitVariableRefrigerantFlow::resetSupplyAirFanPlacement() {
    impl(this)->resetSupplyAirFanPlacement();
  }

  namespace detail {

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result = supplyAirFlowRateDuringCoolingOperation
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation,
                                        supplyAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoCoolingisNeeded() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoCoolingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoCoolingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingisNeeded
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded,
                                        supplyAirFlowRateWhenNoCoolingisNeeded.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoCoolingisNeeded() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result = supplyAirFlowRateDuringHeatingOperation
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation,
                                        supplyAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFlowRateWhenNoHeatingisNeeded() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFlowRateWhenNoHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFlowRateWhenNoHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoHeatingisNeeded
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded,
                                        supplyAirFlowRateWhenNoHeatingisNeeded.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeSupplyAirFlowRateWhenNoHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result = outdoorAirFlowRateDuringCoolingOperation
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation,
                                        outdoorAirFlowRateDuringCoolingOperation.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result = outdoorAirFlowRateDuringHeatingOperation
                            ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation,
                                        outdoorAirFlowRateDuringHeatingOperation.get(), false)
                            : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result =
        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
          ? setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded,
                      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
          : setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result =
        setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOnParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOnParasiticElectricEnergyUse(
      double zoneTerminalUnitOnParasiticElectricEnergyUse) {
      bool result = setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse,
                              zoneTerminalUnitOnParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::zoneTerminalUnitOffParasiticElectricEnergyUse() const {
      boost::optional<double> value =
        getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setZoneTerminalUnitOffParasiticElectricEnergyUse(
      double zoneTerminalUnitOffParasiticElectricEnergyUse) {
      bool result = setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse,
                              zoneTerminalUnitOffParasiticElectricEnergyUse, false);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::ratedTotalHeatingCapacitySizingRatio() const {
      boost::optional<double> value = getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedTotalHeatingCapacitySizingRatio, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio) {
      bool result = setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedTotalHeatingCapacitySizingRatio,
                              ratedTotalHeatingCapacitySizingRatio, false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumSupplyAirTemperaturefromSupplementalHeater() const {
      return getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, false);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() const {
      bool result = false;
      boost::optional<std::string> value =
        getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumSupplyAirTemperaturefromSupplementalHeater(
      double maximumSupplyAirTemperaturefromSupplementalHeater) {
      bool result = setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater,
                              maximumSupplyAirTemperaturefromSupplementalHeater, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizeMaximumSupplyAirTemperaturefromSupplementalHeater() {
      bool result =
        setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() const {
      boost::optional<double> value =
        getDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted() const {
      return isEmpty(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation) {
      bool result = setDouble(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,
                              maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation() {
      bool result =
        setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::supplyAirFanPlacement() const {
      auto value = getString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
      if (!value) {
        return {};
      }
      return value.get();
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::isSupplyAirFanPlacementDefaulted() const {
      return isEmpty(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement);
    }

    bool ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::setSupplyAirFanPlacement(const std::string& supplyAirFanPlacement) {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, supplyAirFanPlacement, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::resetSupplyAirFanPlacement() {
      bool result = setString(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, "", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoCoolingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedSupplyAirFlowRateWhenNoHeatingisNeeded() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
