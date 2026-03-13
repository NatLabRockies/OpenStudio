/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner.hpp"
#include "ZoneHVACComponent/ZoneHVACPackagedTerminalAirConditioner_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_PackagedTerminalAirConditioner_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(const Model& model)
    : ModelObject(ZoneHVACPackagedTerminalAirConditioner::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>());
  }

  ZoneHVACPackagedTerminalAirConditioner::ZoneHVACPackagedTerminalAirConditioner(
    std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACPackagedTerminalAirConditioner::iddObjectType() {
    return IddObjectType::ZoneHVAC_PackagedTerminalAirConditioner;
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::fanPlacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
  }

  std::vector<std::string> ZoneHVACPackagedTerminalAirConditioner::validFanPlacementValues() {
    return fanPlacementValues();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringCoolingOperation(
      supplyAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateDuringHeatingOperation(
      supplyAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->supplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->noLoadSupplyAirFlowRateControlSetToLowSpeed();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setNoLoadSupplyAirFlowRateControlSetToLowSpeed(
      noLoadSupplyAirFlowRateControlSetToLowSpeed);
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringCoolingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringCoolingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringCoolingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringCoolingOperation(
      outdoorAirFlowRateDuringCoolingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringCoolingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateDuringHeatingOperation() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateDuringHeatingOperation();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateDuringHeatingOperationAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateDuringHeatingOperation(
      outdoorAirFlowRateDuringHeatingOperation);
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateDuringHeatingOperation();
  }

  boost::optional<double> ZoneHVACPackagedTerminalAirConditioner::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
    double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  void ZoneHVACPackagedTerminalAirConditioner::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  }

  std::string ZoneHVACPackagedTerminalAirConditioner::fanPlacement() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->fanPlacement();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::isFanPlacementDefaulted() const {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->isFanPlacementDefaulted();
  }

  bool ZoneHVACPackagedTerminalAirConditioner::setFanPlacement(const std::string& fanPlacement) {
    return getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->setFanPlacement(fanPlacement);
  }

  void ZoneHVACPackagedTerminalAirConditioner::resetFanPlacement() {
    getImpl<detail::ZoneHVACPackagedTerminalAirConditioner_Impl>()->resetFanPlacement();
  }

  namespace detail {

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringCoolingOperation(
      boost::optional<double> supplyAirFlowRateDuringCoolingOperation) {
      const bool result =
        supplyAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, supplyAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateDuringHeatingOperation(
      boost::optional<double> supplyAirFlowRateDuringHeatingOperation) {
      const bool result =
        supplyAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, supplyAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = supplyAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate,
                                        supplyAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::noLoadSupplyAirFlowRateControlSetToLowSpeed() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed);
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

    bool
      ZoneHVACPackagedTerminalAirConditioner_Impl::setNoLoadSupplyAirFlowRateControlSetToLowSpeed(bool noLoadSupplyAirFlowRateControlSetToLowSpeed) {
      const bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed,
                                    noLoadSupplyAirFlowRateControlSetToLowSpeed ? "Yes" : "No", false);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringCoolingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringCoolingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringCoolingOperation(
      boost::optional<double> outdoorAirFlowRateDuringCoolingOperation) {
      const bool result =
        outdoorAirFlowRateDuringCoolingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, outdoorAirFlowRateDuringCoolingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringCoolingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringCoolingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateDuringHeatingOperation() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateDuringHeatingOperationAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateDuringHeatingOperation(
      boost::optional<double> outdoorAirFlowRateDuringHeatingOperation) {
      const bool result =
        outdoorAirFlowRateDuringHeatingOperation
          ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, outdoorAirFlowRateDuringHeatingOperation.get(), false)
          : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateDuringHeatingOperation() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateDuringHeatingOperation() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      return getDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const {
      bool result = false;
      boost::optional<std::string> value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, true);
      if (value) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(
      boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded) {
      const bool result = outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
                            ? setDouble(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate,
                                        outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded.get(), false)
                            : setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "", false);
      OS_ASSERT(result);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACPackagedTerminalAirConditioner_Impl::autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    std::string ZoneHVACPackagedTerminalAirConditioner_Impl::fanPlacement() const {
      auto value = getString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
      if (!value) {
        return std::string();
      }
      return value.get();
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::isFanPlacementDefaulted() const {
      return isEmpty(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement);
    }

    bool ZoneHVACPackagedTerminalAirConditioner_Impl::setFanPlacement(const std::string& fanPlacement) {
      return setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, fanPlacement);
    }

    void ZoneHVACPackagedTerminalAirConditioner_Impl::resetFanPlacement() {
      bool result = setString(ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
