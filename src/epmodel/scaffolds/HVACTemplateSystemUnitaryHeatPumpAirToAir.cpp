/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemUnitaryHeatPumpAirToAir.hpp"
#include "HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_UnitaryHeatPump_AirToAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateSystemUnitaryHeatPumpAirToAir::HVACTemplateSystemUnitaryHeatPumpAirToAir(const Model& model)
    : ModelObject(HVACTemplateSystemUnitaryHeatPumpAirToAir::iddObjectType(), model) {}

  HVACTemplateSystemUnitaryHeatPumpAirToAir::HVACTemplateSystemUnitaryHeatPumpAirToAir(
    std::shared_ptr<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateSystemUnitaryHeatPumpAirToAir::iddObjectType() {
    return IddObjectType::HVACTemplate_System_UnitaryHeatPump_AirToAir;
  }

#define OS_UHPA_VALUES_MAP(X)                                       \
  X(supplyFanPlacementValues, SupplyFanPlacement)                   \
  X(coolingCoilTypeValues, CoolingCoilType)                         \
  X(heatPumpHeatingCoilTypeValues, HeatPumpHeatingCoilType)         \
  X(heatPumpDefrostStrategyValues, HeatPumpDefrostStrategy)         \
  X(heatPumpDefrostControlValues, HeatPumpDefrostControl)           \
  X(supplementalHeatingCoilTypeValues, SupplementalHeatingCoilType) \
  X(economizerTypeValues, EconomizerType)                           \
  X(economizerLockoutValues, EconomizerLockout)                     \
  X(nightCycleControlValues, NightCycleControl)                     \
  X(heatRecoveryTypeValues, HeatRecoveryType)                       \
  X(humidifierTypeValues, HumidifierType)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                    \
  std::vector<std::string> HVACTemplateSystemUnitaryHeatPumpAirToAir::method() {                  \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),                \
                          openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field); \
  }

  OS_UHPA_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_UHPA_REQUIRED_STRING_GETTERS(X) \
  X(supplyFanPlacement)                    \
  X(coolingCoilType)                       \
  X(heatPumpHeatingCoilType)               \
  X(heatPumpDefrostStrategy)               \
  X(heatPumpDefrostControl)                \
  X(supplementalHeatingCoilType)           \
  X(economizerType)                        \
  X(economizerLockout)                     \
  X(nightCycleControl)                     \
  X(heatRecoveryType)                      \
  X(humidifierType)

#define OS_UHPA_REQUIRED_DOUBLE_GETTERS(X)                   \
  X(supplyFanTotalEfficiency)                                \
  X(supplyFanDeltaPressure)                                  \
  X(supplyFanMotorEfficiency)                                \
  X(supplyFanMotorinAirStreamFraction)                       \
  X(coolingDesignSupplyAirTemperature)                       \
  X(coolingCoilGrossRatedCOP)                                \
  X(heatingDesignSupplyAirTemperature)                       \
  X(heatPumpHeatingCoilRatedCOP)                             \
  X(heatPumpHeatingMinimumOutdoorDryBulbTemperature)         \
  X(heatPumpDefrostMaximumOutdoorDryBulbTemperature)         \
  X(heatPumpDefrostTimePeriodFraction)                       \
  X(supplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(supplementalGasHeatingCoilEfficiency)                    \
  X(supplementalGasHeatingCoilParasiticElectricLoad)         \
  X(sensibleHeatRecoveryEffectiveness)                       \
  X(latentHeatRecoveryEffectiveness)                         \
  X(humidifierRatedCapacity)                                 \
  X(humidifierSetpoint)                                      \
  X(returnFanTotalEfficiency)                                \
  X(returnFanDeltaPressure)                                  \
  X(returnFanMotorEfficiency)                                \
  X(returnFanMotorinAirStreamFraction)

#define OS_UHPA_OPTIONAL_DOUBLE_GETTERS(X)     \
  X(coolingSupplyAirFlowRate)                  \
  X(heatingSupplyAirFlowRate)                  \
  X(noLoadSupplyAirFlowRate)                   \
  X(coolingCoilGrossRatedTotalCapacity)        \
  X(coolingCoilGrossRatedSensibleHeatRatio)    \
  X(heatPumpHeatingCoilGrossRatedCapacity)     \
  X(supplementalHeatingCoilCapacity)           \
  X(maximumOutdoorAirFlowRate)                 \
  X(minimumOutdoorAirFlowRate)                 \
  X(economizerMaximumLimitDryBulbTemperature)  \
  X(economizerMaximumLimitEnthalpy)            \
  X(economizerMaximumLimitDewpointTemperature) \
  X(economizerMinimumLimitDryBulbTemperature)  \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                                       \
  std::string HVACTemplateSystemUnitaryHeatPumpAirToAir::method() const {               \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                                       \
  double HVACTemplateSystemUnitaryHeatPumpAirToAir::method() const {                    \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                       \
  boost::optional<double> HVACTemplateSystemUnitaryHeatPumpAirToAir::method() const {   \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(); \
  }

  OS_UHPA_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
  OS_UHPA_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
  OS_UHPA_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

  bool HVACTemplateSystemUnitaryHeatPumpAirToAir::returnFan() const {
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->returnFan();
  }

#define OS_UHPA_DEFAULTED_METHODS_MAP(X)                                \
  X(isCoolingSupplyAirFlowRateDefaulted)                                \
  X(isHeatingSupplyAirFlowRateDefaulted)                                \
  X(isNoLoadSupplyAirFlowRateDefaulted)                                 \
  X(isSupplyFanPlacementDefaulted)                                      \
  X(isSupplyFanTotalEfficiencyDefaulted)                                \
  X(isSupplyFanDeltaPressureDefaulted)                                  \
  X(isSupplyFanMotorEfficiencyDefaulted)                                \
  X(isSupplyFanMotorinAirStreamFractionDefaulted)                       \
  X(isCoolingCoilTypeDefaulted)                                         \
  X(isCoolingDesignSupplyAirTemperatureDefaulted)                       \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted)                      \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)                  \
  X(isCoolingCoilGrossRatedCOPDefaulted)                                \
  X(isHeatPumpHeatingCoilTypeDefaulted)                                 \
  X(isHeatingDesignSupplyAirTemperatureDefaulted)                       \
  X(isHeatPumpHeatingCoilGrossRatedCapacityDefaulted)                   \
  X(isHeatPumpHeatingCoilRatedCOPDefaulted)                             \
  X(isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted)         \
  X(isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted)         \
  X(isHeatPumpDefrostStrategyDefaulted)                                 \
  X(isHeatPumpDefrostControlDefaulted)                                  \
  X(isHeatPumpDefrostTimePeriodFractionDefaulted)                       \
  X(isSupplementalHeatingCoilTypeDefaulted)                             \
  X(isSupplementalHeatingCoilCapacityDefaulted)                         \
  X(isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted) \
  X(isSupplementalGasHeatingCoilEfficiencyDefaulted)                    \
  X(isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted)         \
  X(isMaximumOutdoorAirFlowRateDefaulted)                               \
  X(isMinimumOutdoorAirFlowRateDefaulted)                               \
  X(isEconomizerTypeDefaulted)                                          \
  X(isEconomizerLockoutDefaulted)                                       \
  X(isNightCycleControlDefaulted)                                       \
  X(isHeatRecoveryTypeDefaulted)                                        \
  X(isSensibleHeatRecoveryEffectivenessDefaulted)                       \
  X(isLatentHeatRecoveryEffectivenessDefaulted)                         \
  X(isHumidifierTypeDefaulted)                                          \
  X(isHumidifierRatedCapacityDefaulted)                                 \
  X(isHumidifierRatedElectricPowerDefaulted)                            \
  X(isHumidifierSetpointDefaulted)                                      \
  X(isReturnFanDefaulted)                                               \
  X(isReturnFanTotalEfficiencyDefaulted)                                \
  X(isReturnFanDeltaPressureDefaulted)                                  \
  X(isReturnFanMotorEfficiencyDefaulted)                                \
  X(isReturnFanMotorinAirStreamFractionDefaulted)

#define OS_UHPA_AUTOSIZED_METHODS_MAP(X)               \
  X(isCoolingSupplyAirFlowRateAutosized)               \
  X(isHeatingSupplyAirFlowRateAutosized)               \
  X(isNoLoadSupplyAirFlowRateAutosized)                \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized)     \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized) \
  X(isHeatPumpHeatingCoilGrossRatedCapacityAutosized)  \
  X(isSupplementalHeatingCoilCapacityAutosized)        \
  X(isMaximumOutdoorAirFlowRateAutosized)              \
  X(isMinimumOutdoorAirFlowRateAutosized)              \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                                         \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir::method() const {                      \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(); \
  }

  OS_UHPA_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
  OS_UHPA_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_UHPA_STRING_SETTERS(X)   \
  X(setSupplyFanPlacement)          \
  X(setCoolingCoilType)             \
  X(setHeatPumpHeatingCoilType)     \
  X(setHeatPumpDefrostStrategy)     \
  X(setHeatPumpDefrostControl)      \
  X(setSupplementalHeatingCoilType) \
  X(setEconomizerType)              \
  X(setEconomizerLockout)           \
  X(setNightCycleControl)           \
  X(setHeatRecoveryType)            \
  X(setHumidifierType)

#define OS_UHPA_DOUBLE_SETTERS(X)                               \
  X(setCoolingSupplyAirFlowRate)                                \
  X(setHeatingSupplyAirFlowRate)                                \
  X(setNoLoadSupplyAirFlowRate)                                 \
  X(setSupplyFanTotalEfficiency)                                \
  X(setSupplyFanDeltaPressure)                                  \
  X(setSupplyFanMotorEfficiency)                                \
  X(setSupplyFanMotorinAirStreamFraction)                       \
  X(setCoolingDesignSupplyAirTemperature)                       \
  X(setCoolingCoilGrossRatedTotalCapacity)                      \
  X(setCoolingCoilGrossRatedSensibleHeatRatio)                  \
  X(setCoolingCoilGrossRatedCOP)                                \
  X(setHeatingDesignSupplyAirTemperature)                       \
  X(setHeatPumpHeatingCoilGrossRatedCapacity)                   \
  X(setHeatPumpHeatingCoilRatedCOP)                             \
  X(setHeatPumpHeatingMinimumOutdoorDryBulbTemperature)         \
  X(setHeatPumpDefrostMaximumOutdoorDryBulbTemperature)         \
  X(setHeatPumpDefrostTimePeriodFraction)                       \
  X(setSupplementalHeatingCoilCapacity)                         \
  X(setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(setSupplementalGasHeatingCoilEfficiency)                    \
  X(setSupplementalGasHeatingCoilParasiticElectricLoad)         \
  X(setMaximumOutdoorAirFlowRate)                               \
  X(setMinimumOutdoorAirFlowRate)                               \
  X(setEconomizerMaximumLimitDryBulbTemperature)                \
  X(setEconomizerMaximumLimitEnthalpy)                          \
  X(setEconomizerMaximumLimitDewpointTemperature)               \
  X(setEconomizerMinimumLimitDryBulbTemperature)                \
  X(setSensibleHeatRecoveryEffectiveness)                       \
  X(setLatentHeatRecoveryEffectiveness)                         \
  X(setHumidifierRatedCapacity)                                 \
  X(setHumidifierRatedElectricPower)                            \
  X(setHumidifierSetpoint)                                      \
  X(setReturnFanTotalEfficiency)                                \
  X(setReturnFanDeltaPressure)                                  \
  X(setReturnFanMotorEfficiency)                                \
  X(setReturnFanMotorinAirStreamFraction)

#define OS_FORWARD_STRING_SETTER(method)                                                     \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(value); \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                                     \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(value); \
  }

  OS_UHPA_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
  OS_UHPA_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER

  bool HVACTemplateSystemUnitaryHeatPumpAirToAir::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->setReturnFan(returnFan);
  }

#define OS_UHPA_RESETS(X)                                         \
  X(resetCoolingSupplyAirFlowRate)                                \
  X(resetHeatingSupplyAirFlowRate)                                \
  X(resetNoLoadSupplyAirFlowRate)                                 \
  X(resetSupplyFanPlacement)                                      \
  X(resetSupplyFanTotalEfficiency)                                \
  X(resetSupplyFanDeltaPressure)                                  \
  X(resetSupplyFanMotorEfficiency)                                \
  X(resetSupplyFanMotorinAirStreamFraction)                       \
  X(resetCoolingCoilType)                                         \
  X(resetCoolingDesignSupplyAirTemperature)                       \
  X(resetCoolingCoilGrossRatedTotalCapacity)                      \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio)                  \
  X(resetCoolingCoilGrossRatedCOP)                                \
  X(resetHeatPumpHeatingCoilType)                                 \
  X(resetHeatingDesignSupplyAirTemperature)                       \
  X(resetHeatPumpHeatingCoilGrossRatedCapacity)                   \
  X(resetHeatPumpHeatingCoilRatedCOP)                             \
  X(resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature)         \
  X(resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature)         \
  X(resetHeatPumpDefrostStrategy)                                 \
  X(resetHeatPumpDefrostControl)                                  \
  X(resetHeatPumpDefrostTimePeriodFraction)                       \
  X(resetSupplementalHeatingCoilType)                             \
  X(resetSupplementalHeatingCoilCapacity)                         \
  X(resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(resetSupplementalGasHeatingCoilEfficiency)                    \
  X(resetSupplementalGasHeatingCoilParasiticElectricLoad)         \
  X(resetMaximumOutdoorAirFlowRate)                               \
  X(resetMinimumOutdoorAirFlowRate)                               \
  X(resetEconomizerType)                                          \
  X(resetEconomizerLockout)                                       \
  X(resetEconomizerMaximumLimitDryBulbTemperature)                \
  X(resetEconomizerMaximumLimitEnthalpy)                          \
  X(resetEconomizerMaximumLimitDewpointTemperature)               \
  X(resetEconomizerMinimumLimitDryBulbTemperature)                \
  X(resetNightCycleControl)                                       \
  X(resetHeatRecoveryType)                                        \
  X(resetSensibleHeatRecoveryEffectiveness)                       \
  X(resetLatentHeatRecoveryEffectiveness)                         \
  X(resetHumidifierType)                                          \
  X(resetHumidifierRatedCapacity)                                 \
  X(resetHumidifierRatedElectricPower)                            \
  X(resetHumidifierSetpoint)                                      \
  X(resetReturnFan)                                               \
  X(resetReturnFanTotalEfficiency)                                \
  X(resetReturnFanDeltaPressure)                                  \
  X(resetReturnFanMotorEfficiency)                                \
  X(resetReturnFanMotorinAirStreamFraction)

#define OS_UHPA_AUTOSIZES(X)                        \
  X(autosizeCoolingSupplyAirFlowRate)               \
  X(autosizeHeatingSupplyAirFlowRate)               \
  X(autosizeNoLoadSupplyAirFlowRate)                \
  X(autosizeCoolingCoilGrossRatedTotalCapacity)     \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatPumpHeatingCoilGrossRatedCapacity)  \
  X(autosizeSupplementalHeatingCoilCapacity)        \
  X(autosizeMaximumOutdoorAirFlowRate)              \
  X(autosizeMinimumOutdoorAirFlowRate)              \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                                  \
  void HVACTemplateSystemUnitaryHeatPumpAirToAir::method() {                     \
    getImpl<detail::HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl>()->method(); \
  }

  OS_UHPA_RESETS(OS_FORWARD_VOID)
  OS_UHPA_AUTOSIZES(OS_FORWARD_VOID)

#undef OS_FORWARD_VOID

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

#define OS_UHPA_REQUIRED_STRING_MAP(X)                        \
  X(supplyFanPlacement, SupplyFanPlacement)                   \
  X(coolingCoilType, CoolingCoilType)                         \
  X(heatPumpHeatingCoilType, HeatPumpHeatingCoilType)         \
  X(heatPumpDefrostStrategy, HeatPumpDefrostStrategy)         \
  X(heatPumpDefrostControl, HeatPumpDefrostControl)           \
  X(supplementalHeatingCoilType, SupplementalHeatingCoilType) \
  X(economizerType, EconomizerType)                           \
  X(economizerLockout, EconomizerLockout)                     \
  X(nightCycleControl, NightCycleControl)                     \
  X(heatRecoveryType, HeatRecoveryType)                       \
  X(humidifierType, HumidifierType)

#define OS_UHPA_REQUIRED_DOUBLE_MAP(X)                                                                                \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                               \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                   \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                               \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                             \
  X(coolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                             \
  X(coolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                               \
  X(heatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                             \
  X(heatPumpHeatingCoilRatedCOP, HeatPumpHeatingCoilRatedCOP)                                                         \
  X(heatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(heatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(heatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                             \
  X(supplementalHeatingCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(supplementalGasHeatingCoilEfficiency, SupplementalGasHeatingCoilEfficiency)                                       \
  X(supplementalGasHeatingCoilParasiticElectricLoad, SupplementalGasHeatingCoilParasiticElectricLoad)                 \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                             \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                 \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                                                                 \
  X(humidifierSetpoint, HumidifierSetpoint)                                                                           \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                               \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                                                                   \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                               \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_UHPA_OPTIONAL_DOUBLE_MAP(X)                                                    \
  X(coolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                   \
  X(heatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                   \
  X(noLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                     \
  X(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(heatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)         \
  X(supplementalHeatingCoilCapacity, SupplementalHeatingCoilCapacity)                     \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(economizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(economizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(economizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)   \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                                 \
  std::string HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {                                 \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, true); \
    OS_ASSERT(value);                                                                                          \
    return *value;                                                                                             \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                                 \
  double HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {                                      \
    const auto value = getDouble(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, true); \
    OS_ASSERT(value);                                                                                          \
    return *value;                                                                                             \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                                     \
  boost::optional<double> HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {         \
    return getDouble(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, true); \
  }

    OS_UHPA_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING)
    OS_UHPA_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE)
    OS_UHPA_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE)

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_STRING

    bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::returnFan() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFan);
    }

#define OS_UHPA_DEFAULTED_MAP(X)                                                                                                 \
  X(isCoolingSupplyAirFlowRateDefaulted, CoolingSupplyAirFlowRate)                                                               \
  X(isHeatingSupplyAirFlowRateDefaulted, HeatingSupplyAirFlowRate)                                                               \
  X(isNoLoadSupplyAirFlowRateDefaulted, NoLoadSupplyAirFlowRate)                                                                 \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                                                           \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                                               \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                                                   \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                                               \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                                             \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                 \
  X(isCoolingDesignSupplyAirTemperatureDefaulted, CoolingDesignSupplyAirTemperature)                                             \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)                                           \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)                                   \
  X(isCoolingCoilGrossRatedCOPDefaulted, CoolingCoilGrossRatedCOP)                                                               \
  X(isHeatPumpHeatingCoilTypeDefaulted, HeatPumpHeatingCoilType)                                                                 \
  X(isHeatingDesignSupplyAirTemperatureDefaulted, HeatingDesignSupplyAirTemperature)                                             \
  X(isHeatPumpHeatingCoilGrossRatedCapacityDefaulted, HeatPumpHeatingCoilGrossRatedCapacity)                                     \
  X(isHeatPumpHeatingCoilRatedCOPDefaulted, HeatPumpHeatingCoilRatedCOP)                                                         \
  X(isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(isHeatPumpDefrostStrategyDefaulted, HeatPumpDefrostStrategy)                                                                 \
  X(isHeatPumpDefrostControlDefaulted, HeatPumpDefrostControl)                                                                   \
  X(isHeatPumpDefrostTimePeriodFractionDefaulted, HeatPumpDefrostTimePeriodFraction)                                             \
  X(isSupplementalHeatingCoilTypeDefaulted, SupplementalHeatingCoilType)                                                         \
  X(isSupplementalHeatingCoilCapacityDefaulted, SupplementalHeatingCoilCapacity)                                                 \
  X(isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(isSupplementalGasHeatingCoilEfficiencyDefaulted, SupplementalGasHeatingCoilEfficiency)                                       \
  X(isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted, SupplementalGasHeatingCoilParasiticElectricLoad)                 \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                             \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                             \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                   \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                             \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                                             \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                               \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                             \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                 \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                   \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                 \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                       \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                                                           \
  X(isReturnFanDefaulted, ReturnFan)                                                                                             \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                               \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                   \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                               \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)

#define OS_UHPA_AUTOSIZED_MAP(X)                                                               \
  X(isCoolingSupplyAirFlowRateAutosized, CoolingSupplyAirFlowRate)                             \
  X(isHeatingSupplyAirFlowRateAutosized, HeatingSupplyAirFlowRate)                             \
  X(isNoLoadSupplyAirFlowRateAutosized, NoLoadSupplyAirFlowRate)                               \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)         \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(isHeatPumpHeatingCoilGrossRatedCapacityAutosized, HeatPumpHeatingCoilGrossRatedCapacity)   \
  X(isSupplementalHeatingCoilCapacityAutosized, SupplementalHeatingCoilCapacity)               \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                           \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                           \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_DEFAULTED(method, field)                                                   \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {                    \
    return isEmpty(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field); \
  }

#define OS_IMPL_AUTOSIZED(method, field)                                                                       \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {                                        \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, true); \
    if (value) {                                                                                               \
      return openstudio::istringEqual(*value, "autosize");                                                     \
    }                                                                                                          \
    return false;                                                                                              \
  }

    OS_UHPA_DEFAULTED_MAP(OS_IMPL_DEFAULTED)
    OS_UHPA_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_DEFAULTED
#undef OS_IMPL_AUTOSIZED

#define OS_UHPA_STRING_SETTER_MAP(X)                             \
  X(setSupplyFanPlacement, SupplyFanPlacement)                   \
  X(setCoolingCoilType, CoolingCoilType)                         \
  X(setHeatPumpHeatingCoilType, HeatPumpHeatingCoilType)         \
  X(setHeatPumpDefrostStrategy, HeatPumpDefrostStrategy)         \
  X(setHeatPumpDefrostControl, HeatPumpDefrostControl)           \
  X(setSupplementalHeatingCoilType, SupplementalHeatingCoilType) \
  X(setEconomizerType, EconomizerType)                           \
  X(setEconomizerLockout, EconomizerLockout)                     \
  X(setNightCycleControl, NightCycleControl)                     \
  X(setHeatRecoveryType, HeatRecoveryType)                       \
  X(setHumidifierType, HumidifierType)

#define OS_UHPA_DOUBLE_SETTER_CAN_FAIL_MAP(X)                                                                            \
  X(setCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                                               \
  X(setHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                                               \
  X(setNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                                                 \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                               \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                   \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                               \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                             \
  X(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                   \
  X(setCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                               \
  X(setHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)                                     \
  X(setHeatPumpHeatingCoilRatedCOP, HeatPumpHeatingCoilRatedCOP)                                                         \
  X(setHeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(setHeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(setHeatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                             \
  X(setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(setSupplementalGasHeatingCoilEfficiency, SupplementalGasHeatingCoilEfficiency)                                       \
  X(setSupplementalGasHeatingCoilParasiticElectricLoad, SupplementalGasHeatingCoilParasiticElectricLoad)                 \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                             \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                             \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                             \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                 \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                 \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                       \
  X(setHumidifierSetpoint, HumidifierSetpoint)                                                                           \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                               \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                   \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                               \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_UHPA_DOUBLE_SETTER_NOFAIL_MAP(X)                                                  \
  X(setCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                 \
  X(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(setHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                 \
  X(setSupplementalHeatingCoilCapacity, SupplementalHeatingCoilCapacity)                     \
  X(setEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(setEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(setEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)

#define OS_IMPL_SET_STRING(method, field)                                                           \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method(const std::string& value) {           \
    return setString(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE_CANFAIL(method, field)                                                   \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method(double value) {                       \
    return setDouble(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE_NOFAIL(method, field)                                                                 \
  bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method(double value) {                                    \
    const bool result = setDouble(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, value); \
    OS_ASSERT(result);                                                                                           \
    return result;                                                                                               \
  }

    OS_UHPA_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
    OS_UHPA_DOUBLE_SETTER_CAN_FAIL_MAP(OS_IMPL_SET_DOUBLE_CANFAIL)
    OS_UHPA_DOUBLE_SETTER_NOFAIL_MAP(OS_IMPL_SET_DOUBLE_NOFAIL)

#undef OS_IMPL_SET_DOUBLE_NOFAIL
#undef OS_IMPL_SET_DOUBLE_CANFAIL
#undef OS_IMPL_SET_STRING

    bool HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::setReturnFan(bool returnFan) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFan, returnFan);
      OS_ASSERT(result);
      return result;
    }

#define OS_UHPA_RESET_MAP(X)                                                                                               \
  X(resetCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                                               \
  X(resetHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                                               \
  X(resetNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                                                 \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                                                           \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                               \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                   \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                               \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                             \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                 \
  X(resetCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                             \
  X(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                           \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                   \
  X(resetCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                               \
  X(resetHeatPumpHeatingCoilType, HeatPumpHeatingCoilType)                                                                 \
  X(resetHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                             \
  X(resetHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)                                     \
  X(resetHeatPumpHeatingCoilRatedCOP, HeatPumpHeatingCoilRatedCOP)                                                         \
  X(resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(resetHeatPumpDefrostStrategy, HeatPumpDefrostStrategy)                                                                 \
  X(resetHeatPumpDefrostControl, HeatPumpDefrostControl)                                                                   \
  X(resetHeatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                             \
  X(resetSupplementalHeatingCoilType, SupplementalHeatingCoilType)                                                         \
  X(resetSupplementalHeatingCoilCapacity, SupplementalHeatingCoilCapacity)                                                 \
  X(resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature) \
  X(resetSupplementalGasHeatingCoilEfficiency, SupplementalGasHeatingCoilEfficiency)                                       \
  X(resetSupplementalGasHeatingCoilParasiticElectricLoad, SupplementalGasHeatingCoilParasiticElectricLoad)                 \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                             \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                             \
  X(resetEconomizerType, EconomizerType)                                                                                   \
  X(resetEconomizerLockout, EconomizerLockout)                                                                             \
  X(resetEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)                               \
  X(resetEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                                                   \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                             \
  X(resetEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)                               \
  X(resetNightCycleControl, NightCycleControl)                                                                             \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                                               \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                             \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                 \
  X(resetHumidifierType, HumidifierType)                                                                                   \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                 \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                       \
  X(resetHumidifierSetpoint, HumidifierSetpoint)                                                                           \
  X(resetReturnFan, ReturnFan)                                                                                             \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                               \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                   \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                               \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_RESET(method, field)                                                                          \
  void HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() {                                             \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, ""); \
    OS_ASSERT(result);                                                                                        \
  }

    OS_UHPA_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_UHPA_AUTOSIZE_MAP(X)                                                             \
  X(autosizeCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                             \
  X(autosizeHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                             \
  X(autosizeNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                               \
  X(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)         \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)   \
  X(autosizeSupplementalHeatingCoilCapacity, SupplementalHeatingCoilCapacity)               \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                               \
  void HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() {                                                     \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                                                \
  }

    OS_UHPA_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                          \
  std::vector<std::string> HVACTemplateSystemUnitaryHeatPumpAirToAir_Impl::method() const {                                    \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_UnitaryHeatPump_AirToAir).get(), \
                          openstudio::HVACTemplate_System_UnitaryHeatPump_AirToAirFields::field);                              \
  }

    OS_UHPA_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_UHPA_VALUES_MAP

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
