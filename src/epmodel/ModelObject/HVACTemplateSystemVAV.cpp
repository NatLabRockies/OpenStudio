/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemVAV.hpp"
#include "HVACTemplateSystemVAV_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_VAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateSystemVAV::HVACTemplateSystemVAV(const Model& model) : ModelObject(HVACTemplateSystemVAV::iddObjectType(), model) {}

HVACTemplateSystemVAV::HVACTemplateSystemVAV(std::shared_ptr<detail::HVACTemplateSystemVAV_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateSystemVAV::iddObjectType() {
  return IddObjectType::HVACTemplate_System_VAV;
}

#define OS_VAV_VALUES_MAP(X)                                                                                                                \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                                                                            \
  X(coolingCoilTypeValues, CoolingCoilType)                                                                                                  \
  X(heatingCoilTypeValues, HeatingCoilType)                                                                                                  \
  X(preheatCoilTypeValues, PreheatCoilType)                                                                                                  \
  X(minimumOutdoorAirControlTypeValues, MinimumOutdoorAirControlType)                                                                        \
  X(economizerTypeValues, EconomizerType)                                                                                                    \
  X(economizerLockoutValues, EconomizerLockout)                                                                                              \
  X(supplyFanPartLoadPowerCoefficientsValues, SupplyFanPartLoadPowerCoefficients)                                                           \
  X(nightCycleControlValues, NightCycleControl)                                                                                              \
  X(heatRecoveryTypeValues, HeatRecoveryType)                                                                                                 \
  X(coolingCoilSetpointResetTypeValues, CoolingCoilSetpointResetType)                                                                        \
  X(heatingCoilSetpointResetTypeValues, HeatingCoilSetpointResetType)                                                                        \
  X(dehumidificationControlTypeValues, DehumidificationControlType)                                                                          \
  X(humidifierTypeValues, HumidifierType)                                                                                                    \
  X(sizingOptionValues, SizingOption)                                                                                                        \
  X(returnFanPartLoadPowerCoefficientsValues, ReturnFanPartLoadPowerCoefficients)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                               \
  std::vector<std::string> HVACTemplateSystemVAV::method() {                                                                                \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VAVFields::field);      \
  }

OS_VAV_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_VAV_REQUIRED_STRING_GETTERS(X)                                                                                                    \
  X(supplyFanPlacement)                                                                                                                      \
  X(coolingCoilType)                                                                                                                         \
  X(heatingCoilType)                                                                                                                         \
  X(preheatCoilType)                                                                                                                         \
  X(minimumOutdoorAirControlType)                                                                                                            \
  X(economizerType)                                                                                                                          \
  X(economizerLockout)                                                                                                                       \
  X(supplyFanPartLoadPowerCoefficients)                                                                                                      \
  X(nightCycleControl)                                                                                                                       \
  X(heatRecoveryType)                                                                                                                        \
  X(coolingCoilSetpointResetType)                                                                                                            \
  X(heatingCoilSetpointResetType)                                                                                                            \
  X(dehumidificationControlType)                                                                                                             \
  X(humidifierType)                                                                                                                          \
  X(sizingOption)                                                                                                                            \
  X(returnFanPartLoadPowerCoefficients)

#define OS_VAV_REQUIRED_DOUBLE_GETTERS(X)                                                                                                    \
  X(supplyFanTotalEfficiency)                                                                                                                \
  X(supplyFanDeltaPressure)                                                                                                                  \
  X(supplyFanMotorEfficiency)                                                                                                                \
  X(supplyFanMotorinAirStreamFraction)                                                                                                       \
  X(coolingCoilDesignSetpoint)                                                                                                               \
  X(heatingCoilDesignSetpoint)                                                                                                               \
  X(gasHeatingCoilEfficiency)                                                                                                                \
  X(gasHeatingCoilParasiticElectricLoad)                                                                                                     \
  X(preheatCoilDesignSetpoint)                                                                                                               \
  X(gasPreheatCoilEfficiency)                                                                                                                \
  X(gasPreheatCoilParasiticElectricLoad)                                                                                                     \
  X(sensibleHeatRecoveryEffectiveness)                                                                                                       \
  X(latentHeatRecoveryEffectiveness)                                                                                                         \
  X(dehumidificationSetpoint)                                                                                                                \
  X(humidifierRatedCapacity)                                                                                                                 \
  X(humidifierSetpoint)                                                                                                                      \
  X(returnFanTotalEfficiency)                                                                                                                \
  X(returnFanDeltaPressure)                                                                                                                  \
  X(returnFanMotorEfficiency)                                                                                                                \
  X(returnFanMotorinAirStreamFraction)

#define OS_VAV_OPTIONAL_DOUBLE_GETTERS(X)                                                                                                    \
  X(supplyFanMaximumFlowRate)                                                                                                                \
  X(supplyFanMinimumFlowRate)                                                                                                                \
  X(maximumOutdoorAirFlowRate)                                                                                                               \
  X(minimumOutdoorAirFlowRate)                                                                                                               \
  X(economizerUpperTemperatureLimit)                                                                                                         \
  X(economizerLowerTemperatureLimit)                                                                                                         \
  X(economizerUpperEnthalpyLimit)                                                                                                            \
  X(economizerMaximumLimitDewpointTemperature)                                                                                               \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                                                                                            \
  std::string HVACTemplateSystemVAV::method() const {                                                                                        \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method();                                                                         \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                                                                                            \
  double HVACTemplateSystemVAV::method() const {                                                                                             \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method();                                                                         \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                                                                            \
  boost::optional<double> HVACTemplateSystemVAV::method() const {                                                                           \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method();                                                                         \
  }

OS_VAV_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
OS_VAV_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
OS_VAV_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

bool HVACTemplateSystemVAV::returnFan() const {
  return getImpl<detail::HVACTemplateSystemVAV_Impl>()->returnFan();
}

#define OS_VAV_DEFAULTED_METHODS_MAP(X)                                                                                                      \
  X(isSupplyFanMaximumFlowRateDefaulted)                                                                                                    \
  X(isSupplyFanMinimumFlowRateDefaulted)                                                                                                    \
  X(isSupplyFanPlacementDefaulted)                                                                                                          \
  X(isSupplyFanTotalEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanDeltaPressureDefaulted)                                                                                                      \
  X(isSupplyFanMotorEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanMotorinAirStreamFractionDefaulted)                                                                                           \
  X(isCoolingCoilTypeDefaulted)                                                                                                             \
  X(isCoolingCoilDesignSetpointDefaulted)                                                                                                   \
  X(isHeatingCoilTypeDefaulted)                                                                                                             \
  X(isHeatingCoilDesignSetpointDefaulted)                                                                                                   \
  X(isGasHeatingCoilEfficiencyDefaulted)                                                                                                    \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted)                                                                                         \
  X(isPreheatCoilTypeDefaulted)                                                                                                             \
  X(isPreheatCoilDesignSetpointDefaulted)                                                                                                   \
  X(isGasPreheatCoilEfficiencyDefaulted)                                                                                                    \
  X(isGasPreheatCoilParasiticElectricLoadDefaulted)                                                                                         \
  X(isMaximumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isMinimumOutdoorAirControlTypeDefaulted)                                                                                                \
  X(isEconomizerTypeDefaulted)                                                                                                              \
  X(isEconomizerLockoutDefaulted)                                                                                                           \
  X(isEconomizerUpperTemperatureLimitDefaulted)                                                                                             \
  X(isEconomizerLowerTemperatureLimitDefaulted)                                                                                             \
  X(isEconomizerUpperEnthalpyLimitDefaulted)                                                                                                \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted)                                                                                   \
  X(isSupplyFanPartLoadPowerCoefficientsDefaulted)                                                                                          \
  X(isNightCycleControlDefaulted)                                                                                                           \
  X(isHeatRecoveryTypeDefaulted)                                                                                                            \
  X(isSensibleHeatRecoveryEffectivenessDefaulted)                                                                                           \
  X(isLatentHeatRecoveryEffectivenessDefaulted)                                                                                             \
  X(isCoolingCoilSetpointResetTypeDefaulted)                                                                                                \
  X(isHeatingCoilSetpointResetTypeDefaulted)                                                                                                \
  X(isDehumidificationControlTypeDefaulted)                                                                                                 \
  X(isDehumidificationSetpointDefaulted)                                                                                                    \
  X(isHumidifierTypeDefaulted)                                                                                                              \
  X(isHumidifierRatedCapacityDefaulted)                                                                                                     \
  X(isHumidifierRatedElectricPowerDefaulted)                                                                                                \
  X(isHumidifierSetpointDefaulted)                                                                                                          \
  X(isSizingOptionDefaulted)                                                                                                                \
  X(isReturnFanDefaulted)                                                                                                                   \
  X(isReturnFanTotalEfficiencyDefaulted)                                                                                                    \
  X(isReturnFanDeltaPressureDefaulted)                                                                                                      \
  X(isReturnFanMotorEfficiencyDefaulted)                                                                                                    \
  X(isReturnFanMotorinAirStreamFractionDefaulted)                                                                                           \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted)

#define OS_VAV_AUTOSIZED_METHODS_MAP(X)                                                                                                     \
  X(isSupplyFanMaximumFlowRateAutosized)                                                                                                    \
  X(isSupplyFanMinimumFlowRateAutosized)                                                                                                    \
  X(isMaximumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                                                                                              \
  bool HVACTemplateSystemVAV::method() const {                                                                                              \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method();                                                                         \
  }

OS_VAV_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
OS_VAV_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_VAV_STRING_SETTERS(X)                                                                                                             \
  X(setSupplyFanPlacement)                                                                                                                  \
  X(setCoolingCoilType)                                                                                                                     \
  X(setHeatingCoilType)                                                                                                                     \
  X(setPreheatCoilType)                                                                                                                     \
  X(setMinimumOutdoorAirControlType)                                                                                                        \
  X(setEconomizerType)                                                                                                                      \
  X(setEconomizerLockout)                                                                                                                   \
  X(setSupplyFanPartLoadPowerCoefficients)                                                                                                  \
  X(setNightCycleControl)                                                                                                                   \
  X(setHeatRecoveryType)                                                                                                                    \
  X(setCoolingCoilSetpointResetType)                                                                                                        \
  X(setHeatingCoilSetpointResetType)                                                                                                        \
  X(setDehumidificationControlType)                                                                                                         \
  X(setHumidifierType)                                                                                                                      \
  X(setSizingOption)                                                                                                                        \
  X(setReturnFanPartLoadPowerCoefficients)

#define OS_VAV_DOUBLE_SETTERS(X)                                                                                                             \
  X(setSupplyFanMaximumFlowRate)                                                                                                            \
  X(setSupplyFanMinimumFlowRate)                                                                                                            \
  X(setSupplyFanTotalEfficiency)                                                                                                            \
  X(setSupplyFanDeltaPressure)                                                                                                              \
  X(setSupplyFanMotorEfficiency)                                                                                                            \
  X(setSupplyFanMotorinAirStreamFraction)                                                                                                   \
  X(setGasHeatingCoilEfficiency)                                                                                                            \
  X(setGasHeatingCoilParasiticElectricLoad)                                                                                                 \
  X(setGasPreheatCoilEfficiency)                                                                                                            \
  X(setGasPreheatCoilParasiticElectricLoad)                                                                                                 \
  X(setMaximumOutdoorAirFlowRate)                                                                                                           \
  X(setMinimumOutdoorAirFlowRate)                                                                                                           \
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

#define OS_VAV_ASSERT_DOUBLE_SETTERS(X)                                                                                                      \
  X(setCoolingCoilDesignSetpoint)                                                                                                           \
  X(setHeatingCoilDesignSetpoint)                                                                                                           \
  X(setPreheatCoilDesignSetpoint)                                                                                                           \
  X(setEconomizerUpperTemperatureLimit)                                                                                                     \
  X(setEconomizerLowerTemperatureLimit)                                                                                                     \
  X(setEconomizerUpperEnthalpyLimit)                                                                                                        \
  X(setEconomizerMaximumLimitDewpointTemperature)

#define OS_FORWARD_STRING_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemVAV::method(const std::string& value) {                                                                            \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(value);                                                                   \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemVAV::method(double value) {                                                                                         \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(value);                                                                   \
  }

OS_VAV_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
OS_VAV_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)
OS_VAV_ASSERT_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER

bool HVACTemplateSystemVAV::setReturnFan(bool returnFan) {
  return getImpl<detail::HVACTemplateSystemVAV_Impl>()->setReturnFan(returnFan);
}

#define OS_VAV_RESETS(X)                                                                                                                     \
  X(resetSupplyFanMaximumFlowRate)                                                                                                          \
  X(resetSupplyFanMinimumFlowRate)                                                                                                          \
  X(resetSupplyFanPlacement)                                                                                                                \
  X(resetSupplyFanTotalEfficiency)                                                                                                          \
  X(resetSupplyFanDeltaPressure)                                                                                                            \
  X(resetSupplyFanMotorEfficiency)                                                                                                          \
  X(resetSupplyFanMotorinAirStreamFraction)                                                                                                 \
  X(resetCoolingCoilType)                                                                                                                   \
  X(resetCoolingCoilDesignSetpoint)                                                                                                         \
  X(resetHeatingCoilType)                                                                                                                   \
  X(resetHeatingCoilDesignSetpoint)                                                                                                         \
  X(resetGasHeatingCoilEfficiency)                                                                                                          \
  X(resetGasHeatingCoilParasiticElectricLoad)                                                                                               \
  X(resetPreheatCoilType)                                                                                                                   \
  X(resetPreheatCoilDesignSetpoint)                                                                                                         \
  X(resetGasPreheatCoilEfficiency)                                                                                                          \
  X(resetGasPreheatCoilParasiticElectricLoad)                                                                                               \
  X(resetMaximumOutdoorAirFlowRate)                                                                                                         \
  X(resetMinimumOutdoorAirFlowRate)                                                                                                         \
  X(resetMinimumOutdoorAirControlType)                                                                                                      \
  X(resetEconomizerType)                                                                                                                    \
  X(resetEconomizerLockout)                                                                                                                 \
  X(resetEconomizerUpperTemperatureLimit)                                                                                                   \
  X(resetEconomizerLowerTemperatureLimit)                                                                                                   \
  X(resetEconomizerUpperEnthalpyLimit)                                                                                                      \
  X(resetEconomizerMaximumLimitDewpointTemperature)                                                                                         \
  X(resetSupplyFanPartLoadPowerCoefficients)                                                                                                \
  X(resetNightCycleControl)                                                                                                                 \
  X(resetHeatRecoveryType)                                                                                                                  \
  X(resetSensibleHeatRecoveryEffectiveness)                                                                                                 \
  X(resetLatentHeatRecoveryEffectiveness)                                                                                                   \
  X(resetCoolingCoilSetpointResetType)                                                                                                      \
  X(resetHeatingCoilSetpointResetType)                                                                                                      \
  X(resetDehumidificationControlType)                                                                                                       \
  X(resetDehumidificationSetpoint)                                                                                                          \
  X(resetHumidifierType)                                                                                                                    \
  X(resetHumidifierRatedCapacity)                                                                                                           \
  X(resetHumidifierRatedElectricPower)                                                                                                      \
  X(resetHumidifierSetpoint)                                                                                                                \
  X(resetSizingOption)                                                                                                                      \
  X(resetReturnFan)                                                                                                                         \
  X(resetReturnFanTotalEfficiency)                                                                                                          \
  X(resetReturnFanDeltaPressure)                                                                                                            \
  X(resetReturnFanMotorEfficiency)                                                                                                          \
  X(resetReturnFanMotorinAirStreamFraction)                                                                                                 \
  X(resetReturnFanPartLoadPowerCoefficients)

#define OS_VAV_AUTOSIZES(X)                                                                                                                  \
  X(autosizeSupplyFanMaximumFlowRate)                                                                                                       \
  X(autosizeSupplyFanMinimumFlowRate)                                                                                                       \
  X(autosizeMaximumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeMinimumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                                                                                              \
  void HVACTemplateSystemVAV::method() {                                                                                                    \
    getImpl<detail::HVACTemplateSystemVAV_Impl>()->method();                                                                                \
  }

OS_VAV_RESETS(OS_FORWARD_VOID)
OS_VAV_AUTOSIZES(OS_FORWARD_VOID)

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

#define OS_VAV_REQUIRED_STRING_MAP(X)                                                                                                       \
  X(supplyFanPlacement, SupplyFanPlacement)                                                                                                 \
  X(coolingCoilType, CoolingCoilType)                                                                                                       \
  X(heatingCoilType, HeatingCoilType)                                                                                                       \
  X(preheatCoilType, PreheatCoilType)                                                                                                       \
  X(minimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                             \
  X(economizerType, EconomizerType)                                                                                                         \
  X(economizerLockout, EconomizerLockout)                                                                                                   \
  X(supplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)                                                                \
  X(nightCycleControl, NightCycleControl)                                                                                                   \
  X(heatRecoveryType, HeatRecoveryType)                                                                                                     \
  X(coolingCoilSetpointResetType, CoolingCoilSetpointResetType)                                                                             \
  X(heatingCoilSetpointResetType, HeatingCoilSetpointResetType)                                                                             \
  X(dehumidificationControlType, DehumidificationControlType)                                                                               \
  X(humidifierType, HumidifierType)                                                                                                         \
  X(sizingOption, SizingOption)                                                                                                             \
  X(returnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_VAV_REQUIRED_DOUBLE_MAP(X)                                                                                                       \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                     \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                         \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                     \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                                   \
  X(coolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                                   \
  X(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                   \
  X(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                     \
  X(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                               \
  X(preheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                                   \
  X(gasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                     \
  X(gasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                               \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                   \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                       \
  X(dehumidificationSetpoint, DehumidificationSetpoint)                                                                                     \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                                                                                       \
  X(humidifierSetpoint, HumidifierSetpoint)                                                                                                 \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                     \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                         \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                     \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_VAV_OPTIONAL_DOUBLE_MAP(X)                                                                                                       \
  X(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                     \
  X(supplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                     \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                   \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                   \
  X(economizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                       \
  X(economizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                       \
  X(economizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                             \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                  \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING_GETTER(method, field)                                                                                       \
  std::string HVACTemplateSystemVAV_Impl::method() const {                                                                                  \
    const auto value = getString(openstudio::HVACTemplate_System_VAVFields::field, true);                                                  \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_REQUIRED_DOUBLE_GETTER(method, field)                                                                                       \
  double HVACTemplateSystemVAV_Impl::method() const {                                                                                       \
    const auto value = getDouble(openstudio::HVACTemplate_System_VAVFields::field, true);                                                  \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_OPTIONAL_DOUBLE_GETTER(method, field)                                                                                       \
  boost::optional<double> HVACTemplateSystemVAV_Impl::method() const {                                                                      \
    return getDouble(openstudio::HVACTemplate_System_VAVFields::field, true);                                                               \
  }

OS_VAV_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING_GETTER)
OS_VAV_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE_GETTER)
OS_VAV_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE_GETTER)

#undef OS_IMPL_OPTIONAL_DOUBLE_GETTER
#undef OS_IMPL_REQUIRED_DOUBLE_GETTER
#undef OS_IMPL_REQUIRED_STRING_GETTER

bool HVACTemplateSystemVAV_Impl::returnFan() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_VAVFields::ReturnFan);
}

#define OS_VAV_DEFAULTED_FIELD_MAP(X)                                                                                                       \
  X(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)                                                                         \
  X(isSupplyFanMinimumFlowRateDefaulted, SupplyFanMinimumFlowRate)                                                                         \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                                                                      \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                                                         \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                                                             \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                                                         \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                                                      \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                           \
  X(isCoolingCoilDesignSetpointDefaulted, CoolingCoilDesignSetpoint)                                                                       \
  X(isHeatingCoilTypeDefaulted, HeatingCoilType)                                                                                           \
  X(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)                                                                       \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                                                         \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)                                                  \
  X(isPreheatCoilTypeDefaulted, PreheatCoilType)                                                                                           \
  X(isPreheatCoilDesignSetpointDefaulted, PreheatCoilDesignSetpoint)                                                                       \
  X(isGasPreheatCoilEfficiencyDefaulted, GasPreheatCoilEfficiency)                                                                         \
  X(isGasPreheatCoilParasiticElectricLoadDefaulted, GasPreheatCoilParasiticElectricLoad)                                                  \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                                       \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                                       \
  X(isMinimumOutdoorAirControlTypeDefaulted, MinimumOutdoorAirControlType)                                                                 \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                             \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                                       \
  X(isEconomizerUpperTemperatureLimitDefaulted, EconomizerUpperTemperatureLimit)                                                           \
  X(isEconomizerLowerTemperatureLimitDefaulted, EconomizerLowerTemperatureLimit)                                                           \
  X(isEconomizerUpperEnthalpyLimitDefaulted, EconomizerUpperEnthalpyLimit)                                                                 \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)                                      \
  X(isSupplyFanPartLoadPowerCoefficientsDefaulted, SupplyFanPartLoadPowerCoefficients)                                                    \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                                                        \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                                          \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                                      \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                          \
  X(isCoolingCoilSetpointResetTypeDefaulted, CoolingCoilSetpointResetType)                                                                 \
  X(isHeatingCoilSetpointResetTypeDefaulted, HeatingCoilSetpointResetType)                                                                 \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                                                                   \
  X(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)                                                                         \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                              \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                           \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                                 \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                                                                      \
  X(isSizingOptionDefaulted, SizingOption)                                                                                                  \
  X(isReturnFanDefaulted, ReturnFan)                                                                                                        \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                                         \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                             \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                                         \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)                                                      \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_DEFAULTED(method, field)                                                                                                    \
  bool HVACTemplateSystemVAV_Impl::method() const {                                                                                         \
    return isEmpty(openstudio::HVACTemplate_System_VAVFields::field);                                                                       \
  }

OS_VAV_DEFAULTED_FIELD_MAP(OS_IMPL_DEFAULTED)

#undef OS_IMPL_DEFAULTED
#undef OS_VAV_DEFAULTED_FIELD_MAP

#define OS_VAV_AUTOSIZED_MAP(X)                                                                                                             \
  X(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)                                                                          \
  X(isSupplyFanMinimumFlowRateAutosized, SupplyFanMinimumFlowRate)                                                                          \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                                                                        \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_IS_AUTOSIZED(method, field)                                                                                                 \
  bool HVACTemplateSystemVAV_Impl::method() const {                                                                                         \
    if (auto value = getString(openstudio::HVACTemplate_System_VAVFields::field, true)) {                                                  \
      return openstudio::istringEqual(*value, "autosize");                                                                                \
    }                                                                                                                                         \
    return false;                                                                                                                            \
  }

OS_VAV_AUTOSIZED_MAP(OS_IMPL_IS_AUTOSIZED)

#undef OS_IMPL_IS_AUTOSIZED

#define OS_VAV_STRING_SETTER_MAP(X)                                                                                                         \
  X(setSupplyFanPlacement, SupplyFanPlacement)                                                                                               \
  X(setCoolingCoilType, CoolingCoilType)                                                                                                     \
  X(setHeatingCoilType, HeatingCoilType)                                                                                                     \
  X(setPreheatCoilType, PreheatCoilType)                                                                                                     \
  X(setMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                           \
  X(setEconomizerType, EconomizerType)                                                                                                       \
  X(setEconomizerLockout, EconomizerLockout)                                                                                                 \
  X(setSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)                                                              \
  X(setNightCycleControl, NightCycleControl)                                                                                                 \
  X(setHeatRecoveryType, HeatRecoveryType)                                                                                                   \
  X(setCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)                                                                           \
  X(setHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)                                                                           \
  X(setDehumidificationControlType, DehumidificationControlType)                                                                             \
  X(setHumidifierType, HumidifierType)                                                                                                       \
  X(setSizingOption, SizingOption)                                                                                                           \
  X(setReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_VAV_DOUBLE_SETTER_MAP(X)                                                                                                         \
  X(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                   \
  X(setSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                   \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                   \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                       \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                   \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                                 \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                   \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                             \
  X(setGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                   \
  X(setGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                             \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                 \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                 \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                 \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                     \
  X(setDehumidificationSetpoint, DehumidificationSetpoint)                                                                                   \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                     \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                           \
  X(setHumidifierSetpoint, HumidifierSetpoint)                                                                                               \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                   \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                       \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                   \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_VAV_ASSERT_DOUBLE_SETTER_MAP(X)                                                                                                   \
  X(setCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                                 \
  X(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                 \
  X(setPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                                 \
  X(setEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                     \
  X(setEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                     \
  X(setEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                           \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)

#define OS_IMPL_SET_STRING(method, field)                                                                                                   \
  bool HVACTemplateSystemVAV_Impl::method(const std::string& value) {                                                                       \
    return setString(openstudio::HVACTemplate_System_VAVFields::field, value);                                                              \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                                                                                   \
  bool HVACTemplateSystemVAV_Impl::method(double value) {                                                                                   \
    return setDouble(openstudio::HVACTemplate_System_VAVFields::field, value);                                                              \
  }

#define OS_IMPL_SET_DOUBLE_ASSERT(method, field)                                                                                            \
  bool HVACTemplateSystemVAV_Impl::method(double value) {                                                                                   \
    const bool result = setDouble(openstudio::HVACTemplate_System_VAVFields::field, value);                                                 \
    OS_ASSERT(result);                                                                                                                       \
    return result;                                                                                                                           \
  }

OS_VAV_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
OS_VAV_DOUBLE_SETTER_MAP(OS_IMPL_SET_DOUBLE)
OS_VAV_ASSERT_DOUBLE_SETTER_MAP(OS_IMPL_SET_DOUBLE_ASSERT)

#undef OS_IMPL_SET_DOUBLE_ASSERT
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

bool HVACTemplateSystemVAV_Impl::setReturnFan(bool returnFan) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_VAVFields::ReturnFan, returnFan);
  OS_ASSERT(result);
  return result;
}

#define OS_VAV_RESET_MAP(X)                                                                                                                 \
  X(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                \
  X(resetSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                                                                            \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                    \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                                  \
  X(resetCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                              \
  X(resetHeatingCoilType, HeatingCoilType)                                                                                                  \
  X(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                              \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(resetPreheatCoilType, PreheatCoilType)                                                                                                  \
  X(resetPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                              \
  X(resetGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                \
  X(resetGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                         \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                              \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                              \
  X(resetMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                        \
  X(resetEconomizerType, EconomizerType)                                                                                                    \
  X(resetEconomizerLockout, EconomizerLockout)                                                                                              \
  X(resetEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                  \
  X(resetEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                  \
  X(resetEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                        \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                             \
  X(resetSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)                                                           \
  X(resetNightCycleControl, NightCycleControl)                                                                                              \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                                                                \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                              \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                  \
  X(resetCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)                                                                        \
  X(resetHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)                                                                        \
  X(resetDehumidificationControlType, DehumidificationControlType)                                                                          \
  X(resetDehumidificationSetpoint, DehumidificationSetpoint)                                                                                \
  X(resetHumidifierType, HumidifierType)                                                                                                    \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                  \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                        \
  X(resetHumidifierSetpoint, HumidifierSetpoint)                                                                                            \
  X(resetSizingOption, SizingOption)                                                                                                        \
  X(resetReturnFan, ReturnFan)                                                                                                              \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                    \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)                                                             \
  X(resetReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_RESET(method, field)                                                                                                        \
  void HVACTemplateSystemVAV_Impl::method() {                                                                                               \
    const bool result = setString(openstudio::HVACTemplate_System_VAVFields::field, "");                                                 \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_VAV_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_VAV_AUTOSIZE_MAP(X)                                                                                                              \
  X(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                             \
  X(autosizeSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                             \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                                                     \
  void HVACTemplateSystemVAV_Impl::method() {                                                                                               \
    const bool result = setString(openstudio::HVACTemplate_System_VAVFields::field, "Autosize");                                         \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_VAV_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                                       \
  std::vector<std::string> HVACTemplateSystemVAV_Impl::method() const {                                                                     \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_VAV).get(),                                  \
                          openstudio::HVACTemplate_System_VAVFields::field);                                                               \
  }

OS_VAV_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_VAV_VALUES_MAP

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
