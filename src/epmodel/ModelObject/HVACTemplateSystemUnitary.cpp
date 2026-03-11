/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemUnitary.hpp"
#include "HVACTemplateSystemUnitary_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_Unitary_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateSystemUnitary::HVACTemplateSystemUnitary(const Model& model) : ModelObject(HVACTemplateSystemUnitary::iddObjectType(), model) {}

HVACTemplateSystemUnitary::HVACTemplateSystemUnitary(std::shared_ptr<detail::HVACTemplateSystemUnitary_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateSystemUnitary::iddObjectType() {
  return IddObjectType::HVACTemplate_System_Unitary;
}

#define OS_UNITARY_VALUES_MAP(X)                                                                                                            \
  X(coolingCoilTypeValues, CoolingCoilType)                                                                                                 \
  X(heatingCoilTypeValues, HeatingCoilType)                                                                                                 \
  X(economizerTypeValues, EconomizerType)                                                                                                   \
  X(economizerLockoutValues, EconomizerLockout)                                                                                             \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                                                                           \
  X(nightCycleControlValues, NightCycleControl)                                                                                             \
  X(heatRecoveryTypeValues, HeatRecoveryType)                                                                                                \
  X(dehumidificationControlTypeValues, DehumidificationControlType)                                                                         \
  X(humidifierTypeValues, HumidifierType)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                              \
  std::vector<std::string> HVACTemplateSystemUnitary::method() {                                                                           \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_UnitaryFields::field); \
  }

OS_UNITARY_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_UNITARY_REQUIRED_STRING_GETTERS(X)                                                                                               \
  X(coolingCoilType)                                                                                                                        \
  X(heatingCoilType)                                                                                                                        \
  X(economizerType)                                                                                                                         \
  X(economizerLockout)                                                                                                                      \
  X(supplyFanPlacement)                                                                                                                     \
  X(nightCycleControl)                                                                                                                      \
  X(heatRecoveryType)                                                                                                                       \
  X(dehumidificationControlType)                                                                                                            \
  X(humidifierType)

#define OS_UNITARY_REQUIRED_DOUBLE_GETTERS(X)                                                                                               \
  X(supplyFanTotalEfficiency)                                                                                                               \
  X(supplyFanDeltaPressure)                                                                                                                 \
  X(supplyFanMotorEfficiency)                                                                                                               \
  X(supplyFanMotorinAirStreamFraction)                                                                                                      \
  X(coolingDesignSupplyAirTemperature)                                                                                                      \
  X(coolingCoilGrossRatedCOP)                                                                                                               \
  X(heatingDesignSupplyAirTemperature)                                                                                                      \
  X(gasHeatingCoilEfficiency)                                                                                                               \
  X(gasHeatingCoilParasiticElectricLoad)                                                                                                    \
  X(sensibleHeatRecoveryEffectiveness)                                                                                                      \
  X(latentHeatRecoveryEffectiveness)                                                                                                        \
  X(dehumidificationSetpoint)                                                                                                               \
  X(humidifierRatedCapacity)                                                                                                                \
  X(humidifierSetpoint)                                                                                                                     \
  X(returnFanTotalEfficiency)                                                                                                               \
  X(returnFanDeltaPressure)                                                                                                                 \
  X(returnFanMotorEfficiency)                                                                                                               \
  X(returnFanMotorinAirStreamFraction)

#define OS_UNITARY_OPTIONAL_DOUBLE_GETTERS(X)                                                                                               \
  X(supplyFanMaximumFlowRate)                                                                                                               \
  X(coolingCoilGrossRatedTotalCapacity)                                                                                                     \
  X(coolingCoilGrossRatedSensibleHeatRatio)                                                                                                 \
  X(heatingCoilCapacity)                                                                                                                    \
  X(maximumOutdoorAirFlowRate)                                                                                                              \
  X(minimumOutdoorAirFlowRate)                                                                                                              \
  X(economizerUpperTemperatureLimit)                                                                                                        \
  X(economizerLowerTemperatureLimit)                                                                                                        \
  X(economizerUpperEnthalpyLimit)                                                                                                           \
  X(economizerMaximumLimitDewpointTemperature)                                                                                              \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                                                                                           \
  std::string HVACTemplateSystemUnitary::method() const {                                                                                  \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method();                                                                    \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                                                                                           \
  double HVACTemplateSystemUnitary::method() const {                                                                                       \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method();                                                                    \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                                                                           \
  boost::optional<double> HVACTemplateSystemUnitary::method() const {                                                                      \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method();                                                                    \
  }

OS_UNITARY_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
OS_UNITARY_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
OS_UNITARY_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

bool HVACTemplateSystemUnitary::returnFan() const {
  return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->returnFan();
}

#define OS_UNITARY_DEFAULTED_METHODS_MAP(X)                                                                                                 \
  X(isSupplyFanMaximumFlowRateDefaulted)                                                                                                    \
  X(isSupplyFanTotalEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanDeltaPressureDefaulted)                                                                                                      \
  X(isSupplyFanMotorEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanMotorinAirStreamFractionDefaulted)                                                                                           \
  X(isCoolingCoilTypeDefaulted)                                                                                                             \
  X(isCoolingDesignSupplyAirTemperatureDefaulted)                                                                                           \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted)                                                                                          \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)                                                                                      \
  X(isCoolingCoilGrossRatedCOPDefaulted)                                                                                                    \
  X(isHeatingDesignSupplyAirTemperatureDefaulted)                                                                                           \
  X(isHeatingCoilCapacityDefaulted)                                                                                                         \
  X(isGasHeatingCoilEfficiencyDefaulted)                                                                                                    \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted)                                                                                         \
  X(isMaximumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isEconomizerTypeDefaulted)                                                                                                              \
  X(isEconomizerLockoutDefaulted)                                                                                                           \
  X(isEconomizerUpperTemperatureLimitDefaulted)                                                                                             \
  X(isEconomizerLowerTemperatureLimitDefaulted)                                                                                             \
  X(isEconomizerUpperEnthalpyLimitDefaulted)                                                                                                \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted)                                                                                   \
  X(isSupplyFanPlacementDefaulted)                                                                                                          \
  X(isNightCycleControlDefaulted)                                                                                                           \
  X(isHeatRecoveryTypeDefaulted)                                                                                                            \
  X(isSensibleHeatRecoveryEffectivenessDefaulted)                                                                                           \
  X(isLatentHeatRecoveryEffectivenessDefaulted)                                                                                             \
  X(isDehumidificationControlTypeDefaulted)                                                                                                 \
  X(isDehumidificationSetpointDefaulted)                                                                                                    \
  X(isHumidifierTypeDefaulted)                                                                                                              \
  X(isHumidifierRatedCapacityDefaulted)                                                                                                     \
  X(isHumidifierRatedElectricPowerDefaulted)                                                                                                \
  X(isHumidifierSetpointDefaulted)                                                                                                          \
  X(isReturnFanDefaulted)                                                                                                                   \
  X(isReturnFanTotalEfficiencyDefaulted)                                                                                                    \
  X(isReturnFanDeltaPressureDefaulted)                                                                                                      \
  X(isReturnFanMotorEfficiencyDefaulted)                                                                                                    \
  X(isReturnFanMotorinAirStreamFractionDefaulted)

#define OS_UNITARY_AUTOSIZED_METHODS_MAP(X)                                                                                                 \
  X(isSupplyFanMaximumFlowRateAutosized)                                                                                                    \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized)                                                                                          \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized)                                                                                      \
  X(isHeatingCoilCapacityAutosized)                                                                                                         \
  X(isMaximumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                                                                                              \
  bool HVACTemplateSystemUnitary::method() const {                                                                                          \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method();                                                                    \
  }

OS_UNITARY_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
OS_UNITARY_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_UNITARY_STRING_SETTERS(X)                                                                                                        \
  X(setCoolingCoilType)                                                                                                                     \
  X(setHeatingCoilType)                                                                                                                     \
  X(setEconomizerType)                                                                                                                      \
  X(setEconomizerLockout)                                                                                                                   \
  X(setSupplyFanPlacement)                                                                                                                  \
  X(setNightCycleControl)                                                                                                                   \
  X(setHeatRecoveryType)                                                                                                                    \
  X(setDehumidificationControlType)                                                                                                         \
  X(setHumidifierType)

#define OS_UNITARY_DOUBLE_SETTERS(X)                                                                                                        \
  X(setSupplyFanMaximumFlowRate)                                                                                                            \
  X(setSupplyFanTotalEfficiency)                                                                                                            \
  X(setSupplyFanDeltaPressure)                                                                                                              \
  X(setSupplyFanMotorEfficiency)                                                                                                            \
  X(setSupplyFanMotorinAirStreamFraction)                                                                                                   \
  X(setCoolingDesignSupplyAirTemperature)                                                                                                   \
  X(setCoolingCoilGrossRatedTotalCapacity)                                                                                                  \
  X(setCoolingCoilGrossRatedSensibleHeatRatio)                                                                                              \
  X(setCoolingCoilGrossRatedCOP)                                                                                                            \
  X(setHeatingDesignSupplyAirTemperature)                                                                                                   \
  X(setHeatingCoilCapacity)                                                                                                                 \
  X(setGasHeatingCoilEfficiency)                                                                                                            \
  X(setGasHeatingCoilParasiticElectricLoad)                                                                                                 \
  X(setMaximumOutdoorAirFlowRate)                                                                                                           \
  X(setMinimumOutdoorAirFlowRate)                                                                                                           \
  X(setEconomizerUpperTemperatureLimit)                                                                                                     \
  X(setEconomizerLowerTemperatureLimit)                                                                                                     \
  X(setEconomizerUpperEnthalpyLimit)                                                                                                        \
  X(setEconomizerMaximumLimitDewpointTemperature)                                                                                           \
  X(setSensibleHeatRecoveryEffectiveness)                                                                                                   \
  X(setLatentHeatRecoveryEffectiveness)                                                                                                     \
  X(setDehumidificationSetpoint)                                                                                                            \
  X(setHumidifierRatedCapacity)                                                                                                             \
  X(setHumidifierRatedElectricPower)                                                                                                        \
  X(setHumidifierSetpoint)                                                                                                                  \
  X(setReturnFanTotalEfficiency)                                                                                                            \
  X(setReturnFanDeltaPressure)                                                                                                              \
  X(setReturnFanMotorEfficiency)                                                                                                            \
  X(setReturnFanMotorinAirStreamFraction)

#define OS_FORWARD_STRING_SETTER(method)                                                                                                    \
  bool HVACTemplateSystemUnitary::method(const std::string& value) {                                                                       \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(value);                                                               \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                                                                                    \
  bool HVACTemplateSystemUnitary::method(double value) {                                                                                   \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(value);                                                               \
  }

OS_UNITARY_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
OS_UNITARY_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER

bool HVACTemplateSystemUnitary::setReturnFan(bool returnFan) {
  return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->setReturnFan(returnFan);
}

#define OS_UNITARY_RESETS(X)                                                                                                                \
  X(resetSupplyFanMaximumFlowRate)                                                                                                          \
  X(resetSupplyFanTotalEfficiency)                                                                                                          \
  X(resetSupplyFanDeltaPressure)                                                                                                            \
  X(resetSupplyFanMotorEfficiency)                                                                                                          \
  X(resetSupplyFanMotorinAirStreamFraction)                                                                                                 \
  X(resetCoolingCoilType)                                                                                                                   \
  X(resetCoolingDesignSupplyAirTemperature)                                                                                                 \
  X(resetCoolingCoilGrossRatedTotalCapacity)                                                                                                \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio)                                                                                            \
  X(resetCoolingCoilGrossRatedCOP)                                                                                                          \
  X(resetHeatingDesignSupplyAirTemperature)                                                                                                 \
  X(resetHeatingCoilCapacity)                                                                                                               \
  X(resetGasHeatingCoilEfficiency)                                                                                                          \
  X(resetGasHeatingCoilParasiticElectricLoad)                                                                                               \
  X(resetMaximumOutdoorAirFlowRate)                                                                                                         \
  X(resetMinimumOutdoorAirFlowRate)                                                                                                         \
  X(resetEconomizerType)                                                                                                                    \
  X(resetEconomizerLockout)                                                                                                                 \
  X(resetEconomizerUpperTemperatureLimit)                                                                                                   \
  X(resetEconomizerLowerTemperatureLimit)                                                                                                   \
  X(resetEconomizerUpperEnthalpyLimit)                                                                                                      \
  X(resetEconomizerMaximumLimitDewpointTemperature)                                                                                         \
  X(resetSupplyFanPlacement)                                                                                                                \
  X(resetNightCycleControl)                                                                                                                 \
  X(resetHeatRecoveryType)                                                                                                                  \
  X(resetSensibleHeatRecoveryEffectiveness)                                                                                                 \
  X(resetLatentHeatRecoveryEffectiveness)                                                                                                   \
  X(resetDehumidificationControlType)                                                                                                       \
  X(resetDehumidificationSetpoint)                                                                                                          \
  X(resetHumidifierType)                                                                                                                    \
  X(resetHumidifierRatedCapacity)                                                                                                           \
  X(resetHumidifierRatedElectricPower)                                                                                                      \
  X(resetHumidifierSetpoint)                                                                                                                \
  X(resetReturnFan)                                                                                                                         \
  X(resetReturnFanTotalEfficiency)                                                                                                          \
  X(resetReturnFanDeltaPressure)                                                                                                            \
  X(resetReturnFanMotorEfficiency)                                                                                                          \
  X(resetReturnFanMotorinAirStreamFraction)

#define OS_UNITARY_AUTOSIZES(X)                                                                                                             \
  X(autosizeSupplyFanMaximumFlowRate)                                                                                                       \
  X(autosizeCoolingCoilGrossRatedTotalCapacity)                                                                                             \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio)                                                                                         \
  X(autosizeHeatingCoilCapacity)                                                                                                            \
  X(autosizeMaximumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeMinimumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                                                                                              \
  void HVACTemplateSystemUnitary::method() {                                                                                                \
    getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method();                                                                           \
  }

OS_UNITARY_RESETS(OS_FORWARD_VOID)
OS_UNITARY_AUTOSIZES(OS_FORWARD_VOID)

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

#define OS_UNITARY_REQUIRED_STRING_MAP(X)                                                                                                   \
  X(coolingCoilType, CoolingCoilType)                                                                                                       \
  X(heatingCoilType, HeatingCoilType)                                                                                                       \
  X(economizerType, EconomizerType)                                                                                                         \
  X(economizerLockout, EconomizerLockout)                                                                                                   \
  X(supplyFanPlacement, SupplyFanPlacement)                                                                                                 \
  X(nightCycleControl, NightCycleControl)                                                                                                   \
  X(heatRecoveryType, HeatRecoveryType)                                                                                                     \
  X(dehumidificationControlType, DehumidificationControlType)                                                                               \
  X(humidifierType, HumidifierType)

#define OS_UNITARY_REQUIRED_DOUBLE_MAP(X)                                                                                                   \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                     \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                         \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                     \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                                   \
  X(coolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                                                   \
  X(coolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                     \
  X(heatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                                                   \
  X(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                     \
  X(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                               \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                   \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                       \
  X(dehumidificationSetpoint, DehumidificationSetpoint)                                                                                     \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                                                                                       \
  X(humidifierSetpoint, HumidifierSetpoint)                                                                                                 \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                     \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                         \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                     \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_UNITARY_OPTIONAL_DOUBLE_MAP(X)                                                                                                   \
  X(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                     \
  X(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                                 \
  X(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                         \
  X(heatingCoilCapacity, HeatingCoilCapacity)                                                                                                \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                   \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                   \
  X(economizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                       \
  X(economizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                       \
  X(economizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                             \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                   \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                                                              \
  std::string HVACTemplateSystemUnitary_Impl::method() const {                                                                              \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryFields::field, true);                                              \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                                                              \
  double HVACTemplateSystemUnitary_Impl::method() const {                                                                                   \
    const auto value = getDouble(openstudio::HVACTemplate_System_UnitaryFields::field, true);                                              \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                                                                              \
  boost::optional<double> HVACTemplateSystemUnitary_Impl::method() const {                                                                  \
    return getDouble(openstudio::HVACTemplate_System_UnitaryFields::field, true);                                                           \
  }

OS_UNITARY_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING)
OS_UNITARY_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE)
OS_UNITARY_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE)

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_STRING

bool HVACTemplateSystemUnitary_Impl::returnFan() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitaryFields::ReturnFan);
}

#define OS_UNITARY_DEFAULTED_MAP(X)                                                                                                         \
  X(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)                                                                          \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                                                          \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                                                              \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                                                          \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                                                        \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                            \
  X(isCoolingDesignSupplyAirTemperatureDefaulted, CoolingDesignSupplyAirTemperature)                                                        \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)                                                      \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)                                              \
  X(isCoolingCoilGrossRatedCOPDefaulted, CoolingCoilGrossRatedCOP)                                                                          \
  X(isHeatingDesignSupplyAirTemperatureDefaulted, HeatingDesignSupplyAirTemperature)                                                        \
  X(isHeatingCoilCapacityDefaulted, HeatingCoilCapacity)                                                                                    \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                                                          \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)                                                    \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                                        \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                              \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                                        \
  X(isEconomizerUpperTemperatureLimitDefaulted, EconomizerUpperTemperatureLimit)                                                            \
  X(isEconomizerLowerTemperatureLimitDefaulted, EconomizerLowerTemperatureLimit)                                                            \
  X(isEconomizerUpperEnthalpyLimitDefaulted, EconomizerUpperEnthalpyLimit)                                                                  \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)                                        \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                                                                      \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                                                        \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                                          \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                                        \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                            \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                                                                    \
  X(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)                                                                          \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                              \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                            \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                                  \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                                                                      \
  X(isReturnFanDefaulted, ReturnFan)                                                                                                        \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                                          \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                              \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                                          \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)

#define OS_UNITARY_AUTOSIZED_MAP(X)                                                                                                         \
  X(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)                                                                          \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)                                                      \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio)                                              \
  X(isHeatingCoilCapacityAutosized, HeatingCoilCapacity)                                                                                    \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                                                                        \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_DEFAULTED(method, field)                                                                                                    \
  bool HVACTemplateSystemUnitary_Impl::method() const {                                                                                     \
    return isEmpty(openstudio::HVACTemplate_System_UnitaryFields::field);                                                            \
  }

#define OS_IMPL_AUTOSIZED(method, field)                                                                                                    \
  bool HVACTemplateSystemUnitary_Impl::method() const {                                                                                     \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryFields::field, true);                                              \
    if (value) {                                                                                                                             \
      return openstudio::istringEqual(*value, "autosize");                                                                                \
    }                                                                                                                                        \
    return false;                                                                                                                            \
  }

OS_UNITARY_DEFAULTED_MAP(OS_IMPL_DEFAULTED)
OS_UNITARY_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_DEFAULTED
#undef OS_IMPL_AUTOSIZED

#define OS_UNITARY_STRING_SETTER_MAP(X)                                                                                                     \
  X(setCoolingCoilType, CoolingCoilType)                                                                                                    \
  X(setHeatingCoilType, HeatingCoilType)                                                                                                    \
  X(setEconomizerType, EconomizerType)                                                                                                      \
  X(setEconomizerLockout, EconomizerLockout)                                                                                                \
  X(setSupplyFanPlacement, SupplyFanPlacement)                                                                                              \
  X(setNightCycleControl, NightCycleControl)                                                                                                \
  X(setHeatRecoveryType, HeatRecoveryType)                                                                                                  \
  X(setDehumidificationControlType, DehumidificationControlType)                                                                            \
  X(setHumidifierType, HumidifierType)

#define OS_UNITARY_DOUBLE_SETTER_MAP(X)                                                                                                     \
  X(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                  \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                  \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                      \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                  \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                               \
  X(setCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                                                \
  X(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                              \
  X(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                      \
  X(setCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                  \
  X(setHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                                                \
  X(setHeatingCoilCapacity, HeatingCoilCapacity)                                                                                            \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                  \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                            \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                \
  X(setEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                    \
  X(setEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                    \
  X(setEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                          \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                    \
  X(setDehumidificationSetpoint, DehumidificationSetpoint)                                                                                  \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                    \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                          \
  X(setHumidifierSetpoint, HumidifierSetpoint)                                                                                              \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                  \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                      \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                  \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_SET_STRING(method, field)                                                                                                   \
  bool HVACTemplateSystemUnitary_Impl::method(const std::string& value) {                                                                  \
    return setString(openstudio::HVACTemplate_System_UnitaryFields::field, value);                                                         \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                                                                                   \
  bool HVACTemplateSystemUnitary_Impl::method(double value) {                                                                               \
    return setDouble(openstudio::HVACTemplate_System_UnitaryFields::field, value);                                                         \
  }

OS_UNITARY_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
OS_UNITARY_DOUBLE_SETTER_MAP(OS_IMPL_SET_DOUBLE)

#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

bool HVACTemplateSystemUnitary_Impl::setReturnFan(bool returnFan) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitaryFields::ReturnFan, returnFan);
  OS_ASSERT(result);
  return result;
}

#define OS_UNITARY_RESET_MAP(X)                                                                                                             \
  X(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                    \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                                  \
  X(resetCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                                              \
  X(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                            \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                    \
  X(resetCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                \
  X(resetHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                                              \
  X(resetHeatingCoilCapacity, HeatingCoilCapacity)                                                                                          \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                              \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                              \
  X(resetEconomizerType, EconomizerType)                                                                                                    \
  X(resetEconomizerLockout, EconomizerLockout)                                                                                              \
  X(resetEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                  \
  X(resetEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                  \
  X(resetEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                        \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                             \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                                                                            \
  X(resetNightCycleControl, NightCycleControl)                                                                                              \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                                                                \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                              \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                  \
  X(resetDehumidificationControlType, DehumidificationControlType)                                                                          \
  X(resetDehumidificationSetpoint, DehumidificationSetpoint)                                                                                \
  X(resetHumidifierType, HumidifierType)                                                                                                    \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                  \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                        \
  X(resetHumidifierSetpoint, HumidifierSetpoint)                                                                                            \
  X(resetReturnFan, ReturnFan)                                                                                                              \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                    \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_RESET(method, field)                                                                                                        \
  void HVACTemplateSystemUnitary_Impl::method() {                                                                                           \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryFields::field, "");                                             \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_UNITARY_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_UNITARY_AUTOSIZE_MAP(X)                                                                                                          \
  X(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                             \
  X(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                         \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                 \
  X(autosizeHeatingCoilCapacity, HeatingCoilCapacity)                                                                                       \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                                                     \
  void HVACTemplateSystemUnitary_Impl::method() {                                                                                           \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryFields::field, "Autosize");                                     \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_UNITARY_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                                       \
  std::vector<std::string> HVACTemplateSystemUnitary_Impl::method() const {                                                                \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_Unitary).get(),                             \
                          openstudio::HVACTemplate_System_UnitaryFields::field);                                                           \
  }

OS_UNITARY_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_UNITARY_VALUES_MAP

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
