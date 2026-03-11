/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemDualDuct.hpp"
#include "HVACTemplateSystemDualDuct_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_DualDuct_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateSystemDualDuct::HVACTemplateSystemDualDuct(const Model& model) : ModelObject(HVACTemplateSystemDualDuct::iddObjectType(), model) {}

HVACTemplateSystemDualDuct::HVACTemplateSystemDualDuct(std::shared_ptr<detail::HVACTemplateSystemDualDuct_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateSystemDualDuct::iddObjectType() {
  return IddObjectType::HVACTemplate_System_DualDuct;
}

#define OS_DUALDUCT_VALUES_MAP(X)                                                                                                          \
  X(systemConfigurationTypeValues, SystemConfigurationType)                                                                                \
  X(mainSupplyFanPartLoadPowerCoefficientsValues, MainSupplyFanPartLoadPowerCoefficients)                                                 \
  X(coldDuctSupplyFanPartLoadPowerCoefficientsValues, ColdDuctSupplyFanPartLoadPowerCoefficients)                                         \
  X(coldDuctSupplyFanPlacementValues, ColdDuctSupplyFanPlacement)                                                                          \
  X(hotDuctSupplyFanPartLoadPowerCoefficientsValues, HotDuctSupplyFanPartLoadPowerCoefficients)                                           \
  X(hotDuctSupplyFanPlacementValues, HotDuctSupplyFanPlacement)                                                                            \
  X(coolingCoilTypeValues, CoolingCoilType)                                                                                                 \
  X(coolingCoilSetpointControlTypeValues, CoolingCoilSetpointControlType)                                                                  \
  X(heatingCoilTypeValues, HeatingCoilType)                                                                                                 \
  X(heatingCoilSetpointControlTypeValues, HeatingCoilSetpointControlType)                                                                  \
  X(preheatCoilTypeValues, PreheatCoilType)                                                                                                 \
  X(minimumOutdoorAirControlTypeValues, MinimumOutdoorAirControlType)                                                                      \
  X(economizerTypeValues, EconomizerType)                                                                                                   \
  X(economizerLockoutValues, EconomizerLockout)                                                                                             \
  X(nightCycleControlValues, NightCycleControl)                                                                                             \
  X(heatRecoveryTypeValues, HeatRecoveryType)                                                                                               \
  X(heatRecoveryHeatExchangerTypeValues, HeatRecoveryHeatExchangerType)                                                                     \
  X(heatRecoveryFrostControlTypeValues, HeatRecoveryFrostControlType)                                                                       \
  X(dehumidificationControlTypeValues, DehumidificationControlType)                                                                         \
  X(humidifierTypeValues, HumidifierType)                                                                                                   \
  X(sizingOptionValues, SizingOption)                                                                                                       \
  X(returnFanPartLoadPowerCoefficientsValues, ReturnFanPartLoadPowerCoefficients)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                              \
  std::vector<std::string> HVACTemplateSystemDualDuct::method() {                                                                          \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_DualDuctFields::field); \
  }

OS_DUALDUCT_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_DUALDUCT_REQUIRED_STRING_GETTERS(X)                                                                                              \
  X(systemConfigurationType)                                                                                                                \
  X(mainSupplyFanPartLoadPowerCoefficients)                                                                                                 \
  X(coldDuctSupplyFanPartLoadPowerCoefficients)                                                                                             \
  X(coldDuctSupplyFanPlacement)                                                                                                              \
  X(hotDuctSupplyFanPartLoadPowerCoefficients)                                                                                              \
  X(hotDuctSupplyFanPlacement)                                                                                                               \
  X(coolingCoilType)                                                                                                                         \
  X(coolingCoilSetpointControlType)                                                                                                          \
  X(heatingCoilType)                                                                                                                         \
  X(heatingCoilSetpointControlType)                                                                                                          \
  X(preheatCoilType)                                                                                                                         \
  X(minimumOutdoorAirControlType)                                                                                                            \
  X(economizerType)                                                                                                                          \
  X(economizerLockout)                                                                                                                       \
  X(nightCycleControl)                                                                                                                       \
  X(heatRecoveryType)                                                                                                                        \
  X(heatRecoveryHeatExchangerType)                                                                                                           \
  X(heatRecoveryFrostControlType)                                                                                                            \
  X(dehumidificationControlType)                                                                                                             \
  X(humidifierType)                                                                                                                          \
  X(sizingOption)                                                                                                                            \
  X(returnFanPartLoadPowerCoefficients)

#define OS_DUALDUCT_REQUIRED_DOUBLE_GETTERS(X)                                                                                              \
  X(mainSupplyFanMinimumFlowFraction)                                                                                                        \
  X(mainSupplyFanTotalEfficiency)                                                                                                            \
  X(mainSupplyFanDeltaPressure)                                                                                                              \
  X(mainSupplyFanMotorEfficiency)                                                                                                            \
  X(mainSupplyFanMotorinAirStreamFraction)                                                                                                   \
  X(coldDuctSupplyFanMinimumFlowFraction)                                                                                                    \
  X(coldDuctSupplyFanTotalEfficiency)                                                                                                        \
  X(coldDuctSupplyFanDeltaPressure)                                                                                                          \
  X(coldDuctSupplyFanMotorEfficiency)                                                                                                        \
  X(coldDuctSupplyFanMotorinAirStreamFraction)                                                                                               \
  X(hotDuctSupplyFanMinimumFlowFraction)                                                                                                     \
  X(hotDuctSupplyFanTotalEfficiency)                                                                                                         \
  X(hotDuctSupplyFanDeltaPressure)                                                                                                           \
  X(hotDuctSupplyFanMotorEfficiency)                                                                                                         \
  X(hotDuctSupplyFanMotorinAirStreamFraction)                                                                                                \
  X(coolingCoilDesignSetpointTemperature)                                                                                                    \
  X(coolingCoilSetpointatOutdoorDryBulbLow)                                                                                                  \
  X(coolingCoilResetOutdoorDryBulbLow)                                                                                                       \
  X(coolingCoilSetpointatOutdoorDryBulbHigh)                                                                                                 \
  X(coolingCoilResetOutdoorDryBulbHigh)                                                                                                      \
  X(heatingCoilDesignSetpoint)                                                                                                               \
  X(heatingCoilSetpointatOutdoorDryBulbLow)                                                                                                  \
  X(heatingCoilResetOutdoorDryBulbLow)                                                                                                       \
  X(heatingCoilSetpointatOutdoorDryBulbHigh)                                                                                                 \
  X(heatingCoilResetOutdoorDryBulbHigh)                                                                                                      \
  X(gasHeatingCoilEfficiency)                                                                                                                \
  X(gasHeatingCoilParasiticElectricLoad)                                                                                                     \
  X(preheatCoilDesignSetpoint)                                                                                                               \
  X(gasPreheatCoilEfficiency)                                                                                                                \
  X(gasPreheatCoilParasiticElectricLoad)                                                                                                     \
  X(sensibleHeatRecoveryEffectiveness)                                                                                                       \
  X(latentHeatRecoveryEffectiveness)                                                                                                         \
  X(dehumidificationRelativeHumiditySetpoint)                                                                                                \
  X(humidifierRatedCapacity)                                                                                                                 \
  X(humidifierRelativeHumiditySetpoint)                                                                                                      \
  X(returnFanTotalEfficiency)                                                                                                                \
  X(returnFanDeltaPressure)                                                                                                                  \
  X(returnFanMotorEfficiency)                                                                                                                \
  X(returnFanMotorinAirStreamFraction)

#define OS_DUALDUCT_OPTIONAL_DOUBLE_GETTERS(X)                                                                                              \
  X(mainSupplyFanMaximumFlowRate)                                                                                                            \
  X(coldDuctSupplyFanMaximumFlowRate)                                                                                                        \
  X(hotDuctSupplyFanMaximumFlowRate)                                                                                                         \
  X(heatingCoilCapacity)                                                                                                                     \
  X(maximumOutdoorAirFlowRate)                                                                                                               \
  X(minimumOutdoorAirFlowRate)                                                                                                               \
  X(economizerUpperTemperatureLimit)                                                                                                         \
  X(economizerLowerTemperatureLimit)                                                                                                         \
  X(economizerUpperEnthalpyLimit)                                                                                                            \
  X(economizerMaximumLimitDewpointTemperature)                                                                                               \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                                                                                           \
  std::string HVACTemplateSystemDualDuct::method() const {                                                                                  \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method();                                                                   \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                                                                                           \
  double HVACTemplateSystemDualDuct::method() const {                                                                                       \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method();                                                                   \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                                                                           \
  boost::optional<double> HVACTemplateSystemDualDuct::method() const {                                                                      \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method();                                                                   \
  }

OS_DUALDUCT_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
OS_DUALDUCT_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
OS_DUALDUCT_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

bool HVACTemplateSystemDualDuct::returnFan() const {
  return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->returnFan();
}

#define OS_DUALDUCT_DEFAULTED_METHODS_MAP(X)                                                                                                \
  X(isSystemConfigurationTypeDefaulted)                                                                                                      \
  X(isMainSupplyFanMaximumFlowRateDefaulted)                                                                                                 \
  X(isMainSupplyFanMinimumFlowFractionDefaulted)                                                                                             \
  X(isMainSupplyFanTotalEfficiencyDefaulted)                                                                                                 \
  X(isMainSupplyFanDeltaPressureDefaulted)                                                                                                   \
  X(isMainSupplyFanMotorEfficiencyDefaulted)                                                                                                 \
  X(isMainSupplyFanMotorinAirStreamFractionDefaulted)                                                                                        \
  X(isMainSupplyFanPartLoadPowerCoefficientsDefaulted)                                                                                       \
  X(isColdDuctSupplyFanMaximumFlowRateDefaulted)                                                                                             \
  X(isColdDuctSupplyFanMinimumFlowFractionDefaulted)                                                                                         \
  X(isColdDuctSupplyFanTotalEfficiencyDefaulted)                                                                                             \
  X(isColdDuctSupplyFanDeltaPressureDefaulted)                                                                                               \
  X(isColdDuctSupplyFanMotorEfficiencyDefaulted)                                                                                             \
  X(isColdDuctSupplyFanMotorinAirStreamFractionDefaulted)                                                                                    \
  X(isColdDuctSupplyFanPartLoadPowerCoefficientsDefaulted)                                                                                   \
  X(isColdDuctSupplyFanPlacementDefaulted)                                                                                                   \
  X(isHotDuctSupplyFanMaximumFlowRateDefaulted)                                                                                              \
  X(isHotDuctSupplyFanMinimumFlowFractionDefaulted)                                                                                          \
  X(isHotDuctSupplyFanTotalEfficiencyDefaulted)                                                                                              \
  X(isHotDuctSupplyFanDeltaPressureDefaulted)                                                                                                \
  X(isHotDuctSupplyFanMotorEfficiencyDefaulted)                                                                                              \
  X(isHotDuctSupplyFanMotorinAirStreamFractionDefaulted)                                                                                     \
  X(isHotDuctSupplyFanPartLoadPowerCoefficientsDefaulted)                                                                                    \
  X(isHotDuctSupplyFanPlacementDefaulted)                                                                                                    \
  X(isCoolingCoilTypeDefaulted)                                                                                                              \
  X(isCoolingCoilSetpointControlTypeDefaulted)                                                                                               \
  X(isCoolingCoilDesignSetpointTemperatureDefaulted)                                                                                         \
  X(isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted)                                                                                       \
  X(isCoolingCoilResetOutdoorDryBulbLowDefaulted)                                                                                            \
  X(isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted)                                                                                      \
  X(isCoolingCoilResetOutdoorDryBulbHighDefaulted)                                                                                           \
  X(isHeatingCoilTypeDefaulted)                                                                                                              \
  X(isHeatingCoilSetpointControlTypeDefaulted)                                                                                               \
  X(isHeatingCoilDesignSetpointDefaulted)                                                                                                    \
  X(isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted)                                                                                       \
  X(isHeatingCoilResetOutdoorDryBulbLowDefaulted)                                                                                            \
  X(isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted)                                                                                      \
  X(isHeatingCoilResetOutdoorDryBulbHighDefaulted)                                                                                           \
  X(isHeatingCoilCapacityDefaulted)                                                                                                          \
  X(isGasHeatingCoilEfficiencyDefaulted)                                                                                                     \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted)                                                                                          \
  X(isPreheatCoilTypeDefaulted)                                                                                                              \
  X(isPreheatCoilDesignSetpointDefaulted)                                                                                                    \
  X(isGasPreheatCoilEfficiencyDefaulted)                                                                                                     \
  X(isGasPreheatCoilParasiticElectricLoadDefaulted)                                                                                          \
  X(isMaximumOutdoorAirFlowRateDefaulted)                                                                                                    \
  X(isMinimumOutdoorAirFlowRateDefaulted)                                                                                                    \
  X(isMinimumOutdoorAirControlTypeDefaulted)                                                                                                 \
  X(isEconomizerTypeDefaulted)                                                                                                               \
  X(isEconomizerLockoutDefaulted)                                                                                                            \
  X(isEconomizerUpperTemperatureLimitDefaulted)                                                                                              \
  X(isEconomizerLowerTemperatureLimitDefaulted)                                                                                              \
  X(isEconomizerUpperEnthalpyLimitDefaulted)                                                                                                 \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted)                                                                                    \
  X(isNightCycleControlDefaulted)                                                                                                            \
  X(isHeatRecoveryTypeDefaulted)                                                                                                             \
  X(isSensibleHeatRecoveryEffectivenessDefaulted)                                                                                            \
  X(isLatentHeatRecoveryEffectivenessDefaulted)                                                                                              \
  X(isHeatRecoveryHeatExchangerTypeDefaulted)                                                                                                \
  X(isHeatRecoveryFrostControlTypeDefaulted)                                                                                                 \
  X(isDehumidificationControlTypeDefaulted)                                                                                                  \
  X(isDehumidificationRelativeHumiditySetpointDefaulted)                                                                                     \
  X(isHumidifierTypeDefaulted)                                                                                                               \
  X(isHumidifierRatedCapacityDefaulted)                                                                                                      \
  X(isHumidifierRatedElectricPowerDefaulted)                                                                                                 \
  X(isHumidifierRelativeHumiditySetpointDefaulted)                                                                                           \
  X(isSizingOptionDefaulted)                                                                                                                 \
  X(isReturnFanDefaulted)                                                                                                                    \
  X(isReturnFanTotalEfficiencyDefaulted)                                                                                                     \
  X(isReturnFanDeltaPressureDefaulted)                                                                                                       \
  X(isReturnFanMotorEfficiencyDefaulted)                                                                                                     \
  X(isReturnFanMotorinAirStreamFractionDefaulted)                                                                                            \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted)

#define OS_DUALDUCT_AUTOSIZED_METHODS_MAP(X)                                                                                                \
  X(isMainSupplyFanMaximumFlowRateAutosized)                                                                                                 \
  X(isColdDuctSupplyFanMaximumFlowRateAutosized)                                                                                             \
  X(isHotDuctSupplyFanMaximumFlowRateAutosized)                                                                                              \
  X(isHeatingCoilCapacityAutosized)                                                                                                          \
  X(isMaximumOutdoorAirFlowRateAutosized)                                                                                                    \
  X(isMinimumOutdoorAirFlowRateAutosized)                                                                                                    \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                                                                                              \
  bool HVACTemplateSystemDualDuct::method() const {                                                                                         \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method();                                                                   \
  }

OS_DUALDUCT_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
OS_DUALDUCT_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_DUALDUCT_STRING_SETTERS(X)                                                                                                        \
  X(setSystemConfigurationType)                                                                                                              \
  X(setMainSupplyFanPartLoadPowerCoefficients)                                                                                              \
  X(setColdDuctSupplyFanPartLoadPowerCoefficients)                                                                                          \
  X(setColdDuctSupplyFanPlacement)                                                                                                           \
  X(setHotDuctSupplyFanPartLoadPowerCoefficients)                                                                                            \
  X(setHotDuctSupplyFanPlacement)                                                                                                            \
  X(setCoolingCoilType)                                                                                                                      \
  X(setCoolingCoilSetpointControlType)                                                                                                       \
  X(setHeatingCoilType)                                                                                                                      \
  X(setHeatingCoilSetpointControlType)                                                                                                       \
  X(setPreheatCoilType)                                                                                                                      \
  X(setMinimumOutdoorAirControlType)                                                                                                         \
  X(setEconomizerType)                                                                                                                       \
  X(setEconomizerLockout)                                                                                                                    \
  X(setNightCycleControl)                                                                                                                    \
  X(setHeatRecoveryType)                                                                                                                     \
  X(setHeatRecoveryHeatExchangerType)                                                                                                        \
  X(setHeatRecoveryFrostControlType)                                                                                                         \
  X(setDehumidificationControlType)                                                                                                          \
  X(setHumidifierType)                                                                                                                       \
  X(setSizingOption)                                                                                                                         \
  X(setReturnFanPartLoadPowerCoefficients)

#define OS_DUALDUCT_DOUBLE_SETTERS(X)                                                                                                        \
  X(setMainSupplyFanMaximumFlowRate)                                                                                                         \
  X(setMainSupplyFanMinimumFlowFraction)                                                                                                     \
  X(setMainSupplyFanTotalEfficiency)                                                                                                         \
  X(setMainSupplyFanDeltaPressure)                                                                                                           \
  X(setMainSupplyFanMotorEfficiency)                                                                                                         \
  X(setMainSupplyFanMotorinAirStreamFraction)                                                                                                \
  X(setColdDuctSupplyFanMaximumFlowRate)                                                                                                     \
  X(setColdDuctSupplyFanMinimumFlowFraction)                                                                                                 \
  X(setColdDuctSupplyFanTotalEfficiency)                                                                                                     \
  X(setColdDuctSupplyFanDeltaPressure)                                                                                                       \
  X(setColdDuctSupplyFanMotorEfficiency)                                                                                                     \
  X(setColdDuctSupplyFanMotorinAirStreamFraction)                                                                                            \
  X(setHotDuctSupplyFanMaximumFlowRate)                                                                                                      \
  X(setHotDuctSupplyFanMinimumFlowFraction)                                                                                                  \
  X(setHotDuctSupplyFanTotalEfficiency)                                                                                                      \
  X(setHotDuctSupplyFanDeltaPressure)                                                                                                        \
  X(setHotDuctSupplyFanMotorEfficiency)                                                                                                      \
  X(setHotDuctSupplyFanMotorinAirStreamFraction)                                                                                             \
  X(setCoolingCoilDesignSetpointTemperature)                                                                                                 \
  X(setCoolingCoilSetpointatOutdoorDryBulbLow)                                                                                               \
  X(setCoolingCoilResetOutdoorDryBulbLow)                                                                                                    \
  X(setCoolingCoilSetpointatOutdoorDryBulbHigh)                                                                                              \
  X(setCoolingCoilResetOutdoorDryBulbHigh)                                                                                                   \
  X(setHeatingCoilDesignSetpoint)                                                                                                            \
  X(setHeatingCoilSetpointatOutdoorDryBulbLow)                                                                                               \
  X(setHeatingCoilResetOutdoorDryBulbLow)                                                                                                    \
  X(setHeatingCoilSetpointatOutdoorDryBulbHigh)                                                                                              \
  X(setHeatingCoilResetOutdoorDryBulbHigh)                                                                                                   \
  X(setHeatingCoilCapacity)                                                                                                                  \
  X(setGasHeatingCoilEfficiency)                                                                                                             \
  X(setGasHeatingCoilParasiticElectricLoad)                                                                                                  \
  X(setPreheatCoilDesignSetpoint)                                                                                                            \
  X(setGasPreheatCoilEfficiency)                                                                                                             \
  X(setGasPreheatCoilParasiticElectricLoad)                                                                                                  \
  X(setMaximumOutdoorAirFlowRate)                                                                                                            \
  X(setMinimumOutdoorAirFlowRate)                                                                                                            \
  X(setEconomizerUpperTemperatureLimit)                                                                                                      \
  X(setEconomizerLowerTemperatureLimit)                                                                                                      \
  X(setEconomizerUpperEnthalpyLimit)                                                                                                         \
  X(setEconomizerMaximumLimitDewpointTemperature)                                                                                            \
  X(setSensibleHeatRecoveryEffectiveness)                                                                                                    \
  X(setLatentHeatRecoveryEffectiveness)                                                                                                      \
  X(setDehumidificationRelativeHumiditySetpoint)                                                                                             \
  X(setHumidifierRatedCapacity)                                                                                                              \
  X(setHumidifierRatedElectricPower)                                                                                                         \
  X(setHumidifierRelativeHumiditySetpoint)                                                                                                   \
  X(setReturnFanTotalEfficiency)                                                                                                             \
  X(setReturnFanDeltaPressure)                                                                                                               \
  X(setReturnFanMotorEfficiency)                                                                                                             \
  X(setReturnFanMotorinAirStreamFraction)

#define OS_DUALDUCT_STRING_SETTER_MAP(X)                                                                                                     \
  X(setSystemConfigurationType, SystemConfigurationType)                                                                                     \
  X(setMainSupplyFanPartLoadPowerCoefficients, MainSupplyFanPartLoadPowerCoefficients)                                                     \
  X(setColdDuctSupplyFanPartLoadPowerCoefficients, ColdDuctSupplyFanPartLoadPowerCoefficients)                                             \
  X(setColdDuctSupplyFanPlacement, ColdDuctSupplyFanPlacement)                                                                              \
  X(setHotDuctSupplyFanPartLoadPowerCoefficients, HotDuctSupplyFanPartLoadPowerCoefficients)                                               \
  X(setHotDuctSupplyFanPlacement, HotDuctSupplyFanPlacement)                                                                                \
  X(setCoolingCoilType, CoolingCoilType)                                                                                                     \
  X(setCoolingCoilSetpointControlType, CoolingCoilSetpointControlType)                                                                      \
  X(setHeatingCoilType, HeatingCoilType)                                                                                                     \
  X(setHeatingCoilSetpointControlType, HeatingCoilSetpointControlType)                                                                      \
  X(setPreheatCoilType, PreheatCoilType)                                                                                                     \
  X(setMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                          \
  X(setEconomizerType, EconomizerType)                                                                                                       \
  X(setEconomizerLockout, EconomizerLockout)                                                                                                 \
  X(setNightCycleControl, NightCycleControl)                                                                                                 \
  X(setHeatRecoveryType, HeatRecoveryType)                                                                                                   \
  X(setHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)                                                                         \
  X(setHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)                                                                           \
  X(setDehumidificationControlType, DehumidificationControlType)                                                                             \
  X(setHumidifierType, HumidifierType)                                                                                                       \
  X(setSizingOption, SizingOption)                                                                                                           \
  X(setReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_DUALDUCT_DOUBLE_SETTER_MAP(X)                                                                                                     \
  X(setMainSupplyFanMaximumFlowRate, MainSupplyFanMaximumFlowRate)                                                                          \
  X(setMainSupplyFanMinimumFlowFraction, MainSupplyFanMinimumFlowFraction)                                                                  \
  X(setMainSupplyFanTotalEfficiency, MainSupplyFanTotalEfficiency)                                                                          \
  X(setMainSupplyFanDeltaPressure, MainSupplyFanDeltaPressure)                                                                              \
  X(setMainSupplyFanMotorEfficiency, MainSupplyFanMotorEfficiency)                                                                          \
  X(setMainSupplyFanMotorinAirStreamFraction, MainSupplyFanMotorinAirStreamFraction)                                                       \
  X(setColdDuctSupplyFanMaximumFlowRate, ColdDuctSupplyFanMaximumFlowRate)                                                                  \
  X(setColdDuctSupplyFanMinimumFlowFraction, ColdDuctSupplyFanMinimumFlowFraction)                                                          \
  X(setColdDuctSupplyFanTotalEfficiency, ColdDuctSupplyFanTotalEfficiency)                                                                  \
  X(setColdDuctSupplyFanDeltaPressure, ColdDuctSupplyFanDeltaPressure)                                                                      \
  X(setColdDuctSupplyFanMotorEfficiency, ColdDuctSupplyFanMotorEfficiency)                                                                  \
  X(setColdDuctSupplyFanMotorinAirStreamFraction, ColdDuctSupplyFanMotorinAirStreamFraction)                                               \
  X(setHotDuctSupplyFanMaximumFlowRate, HotDuctSupplyFanMaximumFlowRate)                                                                    \
  X(setHotDuctSupplyFanMinimumFlowFraction, HotDuctSupplyFanMinimumFlowFraction)                                                            \
  X(setHotDuctSupplyFanTotalEfficiency, HotDuctSupplyFanTotalEfficiency)                                                                    \
  X(setHotDuctSupplyFanDeltaPressure, HotDuctSupplyFanDeltaPressure)                                                                        \
  X(setHotDuctSupplyFanMotorEfficiency, HotDuctSupplyFanMotorEfficiency)                                                                    \
  X(setHotDuctSupplyFanMotorinAirStreamFraction, HotDuctSupplyFanMotorinAirStreamFraction)                                                 \
  X(setCoolingCoilDesignSetpointTemperature, CoolingCoilDesignSetpointTemperature)                                                          \
  X(setCoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)                                                     \
  X(setCoolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)                                                                \
  X(setCoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)                                                   \
  X(setCoolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)                                                              \
  X(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                \
  X(setHeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)                                                     \
  X(setHeatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)                                                                \
  X(setHeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)                                                   \
  X(setHeatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)                                                              \
  X(setHeatingCoilCapacity, HeatingCoilCapacity)                                                                                             \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                   \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                            \
  X(setPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                                \
  X(setGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                  \
  X(setGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                            \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                \
  X(setEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                    \
  X(setEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                    \
  X(setEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                          \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                    \
  X(setDehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                                  \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                    \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                          \
  X(setHumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                              \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                  \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                      \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                  \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_FORWARD_STRING_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemDualDuct::method(const std::string& value) {                                                                      \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method(value);                                                              \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemDualDuct::method(double value) {                                                                                   \
    return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method(value);                                                              \
  }

OS_DUALDUCT_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
OS_DUALDUCT_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER

bool HVACTemplateSystemDualDuct::setReturnFan(bool returnFan) {
  return getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->setReturnFan(returnFan);
}

#define OS_DUALDUCT_RESETS(X)                                                                                                                \
  X(resetSystemConfigurationType)                                                                                                            \
  X(resetMainSupplyFanMaximumFlowRate)                                                                                                       \
  X(resetMainSupplyFanMinimumFlowFraction)                                                                                                   \
  X(resetMainSupplyFanTotalEfficiency)                                                                                                       \
  X(resetMainSupplyFanDeltaPressure)                                                                                                         \
  X(resetMainSupplyFanMotorEfficiency)                                                                                                       \
  X(resetMainSupplyFanMotorinAirStreamFraction)                                                                                              \
  X(resetMainSupplyFanPartLoadPowerCoefficients)                                                                                             \
  X(resetColdDuctSupplyFanMaximumFlowRate)                                                                                                   \
  X(resetColdDuctSupplyFanMinimumFlowFraction)                                                                                               \
  X(resetColdDuctSupplyFanTotalEfficiency)                                                                                                   \
  X(resetColdDuctSupplyFanDeltaPressure)                                                                                                     \
  X(resetColdDuctSupplyFanMotorEfficiency)                                                                                                   \
  X(resetColdDuctSupplyFanMotorinAirStreamFraction)                                                                                          \
  X(resetColdDuctSupplyFanPartLoadPowerCoefficients)                                                                                         \
  X(resetColdDuctSupplyFanPlacement)                                                                                                         \
  X(resetHotDuctSupplyFanMaximumFlowRate)                                                                                                    \
  X(resetHotDuctSupplyFanMinimumFlowFraction)                                                                                                \
  X(resetHotDuctSupplyFanTotalEfficiency)                                                                                                    \
  X(resetHotDuctSupplyFanDeltaPressure)                                                                                                      \
  X(resetHotDuctSupplyFanMotorEfficiency)                                                                                                    \
  X(resetHotDuctSupplyFanMotorinAirStreamFraction)                                                                                           \
  X(resetHotDuctSupplyFanPartLoadPowerCoefficients)                                                                                          \
  X(resetHotDuctSupplyFanPlacement)                                                                                                          \
  X(resetCoolingCoilType)                                                                                                                    \
  X(resetCoolingCoilSetpointControlType)                                                                                                     \
  X(resetCoolingCoilDesignSetpointTemperature)                                                                                               \
  X(resetCoolingCoilSetpointatOutdoorDryBulbLow)                                                                                             \
  X(resetCoolingCoilResetOutdoorDryBulbLow)                                                                                                  \
  X(resetCoolingCoilSetpointatOutdoorDryBulbHigh)                                                                                            \
  X(resetCoolingCoilResetOutdoorDryBulbHigh)                                                                                                 \
  X(resetHeatingCoilType)                                                                                                                    \
  X(resetHeatingCoilSetpointControlType)                                                                                                     \
  X(resetHeatingCoilDesignSetpoint)                                                                                                          \
  X(resetHeatingCoilSetpointatOutdoorDryBulbLow)                                                                                             \
  X(resetHeatingCoilResetOutdoorDryBulbLow)                                                                                                  \
  X(resetHeatingCoilSetpointatOutdoorDryBulbHigh)                                                                                            \
  X(resetHeatingCoilResetOutdoorDryBulbHigh)                                                                                                 \
  X(resetHeatingCoilCapacity)                                                                                                                \
  X(resetGasHeatingCoilEfficiency)                                                                                                           \
  X(resetGasHeatingCoilParasiticElectricLoad)                                                                                                \
  X(resetPreheatCoilType)                                                                                                                    \
  X(resetPreheatCoilDesignSetpoint)                                                                                                          \
  X(resetGasPreheatCoilEfficiency)                                                                                                           \
  X(resetGasPreheatCoilParasiticElectricLoad)                                                                                                \
  X(resetMaximumOutdoorAirFlowRate)                                                                                                          \
  X(resetMinimumOutdoorAirFlowRate)                                                                                                          \
  X(resetMinimumOutdoorAirControlType)                                                                                                       \
  X(resetEconomizerType)                                                                                                                     \
  X(resetEconomizerLockout)                                                                                                                  \
  X(resetEconomizerUpperTemperatureLimit)                                                                                                    \
  X(resetEconomizerLowerTemperatureLimit)                                                                                                    \
  X(resetEconomizerUpperEnthalpyLimit)                                                                                                       \
  X(resetEconomizerMaximumLimitDewpointTemperature)                                                                                          \
  X(resetNightCycleControl)                                                                                                                  \
  X(resetHeatRecoveryType)                                                                                                                   \
  X(resetSensibleHeatRecoveryEffectiveness)                                                                                                  \
  X(resetLatentHeatRecoveryEffectiveness)                                                                                                    \
  X(resetHeatRecoveryHeatExchangerType)                                                                                                      \
  X(resetHeatRecoveryFrostControlType)                                                                                                       \
  X(resetDehumidificationControlType)                                                                                                        \
  X(resetDehumidificationRelativeHumiditySetpoint)                                                                                           \
  X(resetHumidifierType)                                                                                                                     \
  X(resetHumidifierRatedCapacity)                                                                                                            \
  X(resetHumidifierRatedElectricPower)                                                                                                       \
  X(resetHumidifierRelativeHumiditySetpoint)                                                                                                 \
  X(resetSizingOption)                                                                                                                       \
  X(resetReturnFan)                                                                                                                          \
  X(resetReturnFanTotalEfficiency)                                                                                                           \
  X(resetReturnFanDeltaPressure)                                                                                                             \
  X(resetReturnFanMotorEfficiency)                                                                                                           \
  X(resetReturnFanMotorinAirStreamFraction)                                                                                                  \
  X(resetReturnFanPartLoadPowerCoefficients)

#define OS_DUALDUCT_AUTOSIZES(X)                                                                                                             \
  X(autosizeMainSupplyFanMaximumFlowRate)                                                                                                    \
  X(autosizeColdDuctSupplyFanMaximumFlowRate)                                                                                                \
  X(autosizeHotDuctSupplyFanMaximumFlowRate)                                                                                                 \
  X(autosizeHeatingCoilCapacity)                                                                                                             \
  X(autosizeMaximumOutdoorAirFlowRate)                                                                                                       \
  X(autosizeMinimumOutdoorAirFlowRate)                                                                                                       \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                                                                                              \
  void HVACTemplateSystemDualDuct::method() {                                                                                               \
    getImpl<detail::HVACTemplateSystemDualDuct_Impl>()->method();                                                                           \
  }

OS_DUALDUCT_RESETS(OS_FORWARD_VOID)
OS_DUALDUCT_AUTOSIZES(OS_FORWARD_VOID)

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

#define OS_DUALDUCT_REQUIRED_STRING_MAP(X)                                                                                                  \
  X(systemConfigurationType, SystemConfigurationType)                                                                                        \
  X(mainSupplyFanPartLoadPowerCoefficients, MainSupplyFanPartLoadPowerCoefficients)                                                         \
  X(coldDuctSupplyFanPartLoadPowerCoefficients, ColdDuctSupplyFanPartLoadPowerCoefficients)                                                 \
  X(coldDuctSupplyFanPlacement, ColdDuctSupplyFanPlacement)                                                                                  \
  X(hotDuctSupplyFanPartLoadPowerCoefficients, HotDuctSupplyFanPartLoadPowerCoefficients)                                                   \
  X(hotDuctSupplyFanPlacement, HotDuctSupplyFanPlacement)                                                                                    \
  X(coolingCoilType, CoolingCoilType)                                                                                                        \
  X(coolingCoilSetpointControlType, CoolingCoilSetpointControlType)                                                                          \
  X(heatingCoilType, HeatingCoilType)                                                                                                        \
  X(heatingCoilSetpointControlType, HeatingCoilSetpointControlType)                                                                          \
  X(preheatCoilType, PreheatCoilType)                                                                                                        \
  X(minimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                              \
  X(economizerType, EconomizerType)                                                                                                          \
  X(economizerLockout, EconomizerLockout)                                                                                                    \
  X(nightCycleControl, NightCycleControl)                                                                                                    \
  X(heatRecoveryType, HeatRecoveryType)                                                                                                      \
  X(heatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)                                                                            \
  X(heatRecoveryFrostControlType, HeatRecoveryFrostControlType)                                                                              \
  X(dehumidificationControlType, DehumidificationControlType)                                                                                \
  X(humidifierType, HumidifierType)                                                                                                          \
  X(sizingOption, SizingOption)                                                                                                              \
  X(returnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_DUALDUCT_REQUIRED_DOUBLE_MAP(X)                                                                                                   \
  X(mainSupplyFanMinimumFlowFraction, MainSupplyFanMinimumFlowFraction)                                                                      \
  X(mainSupplyFanTotalEfficiency, MainSupplyFanTotalEfficiency)                                                                              \
  X(mainSupplyFanDeltaPressure, MainSupplyFanDeltaPressure)                                                                                  \
  X(mainSupplyFanMotorEfficiency, MainSupplyFanMotorEfficiency)                                                                              \
  X(mainSupplyFanMotorinAirStreamFraction, MainSupplyFanMotorinAirStreamFraction)                                                           \
  X(coldDuctSupplyFanMinimumFlowFraction, ColdDuctSupplyFanMinimumFlowFraction)                                                             \
  X(coldDuctSupplyFanTotalEfficiency, ColdDuctSupplyFanTotalEfficiency)                                                                      \
  X(coldDuctSupplyFanDeltaPressure, ColdDuctSupplyFanDeltaPressure)                                                                          \
  X(coldDuctSupplyFanMotorEfficiency, ColdDuctSupplyFanMotorEfficiency)                                                                      \
  X(coldDuctSupplyFanMotorinAirStreamFraction, ColdDuctSupplyFanMotorinAirStreamFraction)                                                   \
  X(hotDuctSupplyFanMinimumFlowFraction, HotDuctSupplyFanMinimumFlowFraction)                                                               \
  X(hotDuctSupplyFanTotalEfficiency, HotDuctSupplyFanTotalEfficiency)                                                                        \
  X(hotDuctSupplyFanDeltaPressure, HotDuctSupplyFanDeltaPressure)                                                                            \
  X(hotDuctSupplyFanMotorEfficiency, HotDuctSupplyFanMotorEfficiency)                                                                        \
  X(hotDuctSupplyFanMotorinAirStreamFraction, HotDuctSupplyFanMotorinAirStreamFraction)                                                     \
  X(coolingCoilDesignSetpointTemperature, CoolingCoilDesignSetpointTemperature)                                                              \
  X(coolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)                                                         \
  X(coolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)                                                                    \
  X(coolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)                                                       \
  X(coolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)                                                                  \
  X(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                    \
  X(heatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)                                                         \
  X(heatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)                                                                    \
  X(heatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)                                                       \
  X(heatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)                                                                  \
  X(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                      \
  X(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                                \
  X(preheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                                    \
  X(gasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                      \
  X(gasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                                \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                                    \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                        \
  X(dehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                                      \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                                                                                        \
  X(humidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                                  \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                      \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                          \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                      \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_DUALDUCT_OPTIONAL_DOUBLE_MAP(X)                                                                                                   \
  X(mainSupplyFanMaximumFlowRate, MainSupplyFanMaximumFlowRate)                                                                              \
  X(coldDuctSupplyFanMaximumFlowRate, ColdDuctSupplyFanMaximumFlowRate)                                                                      \
  X(hotDuctSupplyFanMaximumFlowRate, HotDuctSupplyFanMaximumFlowRate)                                                                        \
  X(heatingCoilCapacity, HeatingCoilCapacity)                                                                                                \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                    \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                    \
  X(economizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                        \
  X(economizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                        \
  X(economizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                              \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                    \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                                                               \
  std::string HVACTemplateSystemDualDuct_Impl::method() const {                                                                             \
    const auto value = getString(openstudio::HVACTemplate_System_DualDuctFields::field, true);                                             \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                                                               \
  double HVACTemplateSystemDualDuct_Impl::method() const {                                                                                  \
    const auto value = getDouble(openstudio::HVACTemplate_System_DualDuctFields::field, true);                                             \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                                                                               \
  boost::optional<double> HVACTemplateSystemDualDuct_Impl::method() const {                                                                 \
    return getDouble(openstudio::HVACTemplate_System_DualDuctFields::field, true);                                                         \
  }

OS_DUALDUCT_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING)
OS_DUALDUCT_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE)
OS_DUALDUCT_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE)

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_STRING

bool HVACTemplateSystemDualDuct_Impl::returnFan() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_DualDuctFields::ReturnFan);
}

#define OS_DUALDUCT_DEFAULTED_MAP(X)                                                                                                         \
  X(isSystemConfigurationTypeDefaulted, SystemConfigurationType)                                                                             \
  X(isMainSupplyFanMaximumFlowRateDefaulted, MainSupplyFanMaximumFlowRate)                                                                  \
  X(isMainSupplyFanMinimumFlowFractionDefaulted, MainSupplyFanMinimumFlowFraction)                                                          \
  X(isMainSupplyFanTotalEfficiencyDefaulted, MainSupplyFanTotalEfficiency)                                                                  \
  X(isMainSupplyFanDeltaPressureDefaulted, MainSupplyFanDeltaPressure)                                                                      \
  X(isMainSupplyFanMotorEfficiencyDefaulted, MainSupplyFanMotorEfficiency)                                                                  \
  X(isMainSupplyFanMotorinAirStreamFractionDefaulted, MainSupplyFanMotorinAirStreamFraction)                                               \
  X(isMainSupplyFanPartLoadPowerCoefficientsDefaulted, MainSupplyFanPartLoadPowerCoefficients)                                             \
  X(isColdDuctSupplyFanMaximumFlowRateDefaulted, ColdDuctSupplyFanMaximumFlowRate)                                                          \
  X(isColdDuctSupplyFanMinimumFlowFractionDefaulted, ColdDuctSupplyFanMinimumFlowFraction)                                                  \
  X(isColdDuctSupplyFanTotalEfficiencyDefaulted, ColdDuctSupplyFanTotalEfficiency)                                                          \
  X(isColdDuctSupplyFanDeltaPressureDefaulted, ColdDuctSupplyFanDeltaPressure)                                                              \
  X(isColdDuctSupplyFanMotorEfficiencyDefaulted, ColdDuctSupplyFanMotorEfficiency)                                                          \
  X(isColdDuctSupplyFanMotorinAirStreamFractionDefaulted, ColdDuctSupplyFanMotorinAirStreamFraction)                                       \
  X(isColdDuctSupplyFanPartLoadPowerCoefficientsDefaulted, ColdDuctSupplyFanPartLoadPowerCoefficients)                                     \
  X(isColdDuctSupplyFanPlacementDefaulted, ColdDuctSupplyFanPlacement)                                                                       \
  X(isHotDuctSupplyFanMaximumFlowRateDefaulted, HotDuctSupplyFanMaximumFlowRate)                                                            \
  X(isHotDuctSupplyFanMinimumFlowFractionDefaulted, HotDuctSupplyFanMinimumFlowFraction)                                                    \
  X(isHotDuctSupplyFanTotalEfficiencyDefaulted, HotDuctSupplyFanTotalEfficiency)                                                            \
  X(isHotDuctSupplyFanDeltaPressureDefaulted, HotDuctSupplyFanDeltaPressure)                                                                \
  X(isHotDuctSupplyFanMotorEfficiencyDefaulted, HotDuctSupplyFanMotorEfficiency)                                                            \
  X(isHotDuctSupplyFanMotorinAirStreamFractionDefaulted, HotDuctSupplyFanMotorinAirStreamFraction)                                         \
  X(isHotDuctSupplyFanPartLoadPowerCoefficientsDefaulted, HotDuctSupplyFanPartLoadPowerCoefficients)                                       \
  X(isHotDuctSupplyFanPlacementDefaulted, HotDuctSupplyFanPlacement)                                                                         \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                             \
  X(isCoolingCoilSetpointControlTypeDefaulted, CoolingCoilSetpointControlType)                                                              \
  X(isCoolingCoilDesignSetpointTemperatureDefaulted, CoolingCoilDesignSetpointTemperature)                                                  \
  X(isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted, CoolingCoilSetpointatOutdoorDryBulbLow)                                             \
  X(isCoolingCoilResetOutdoorDryBulbLowDefaulted, CoolingCoilResetOutdoorDryBulbLow)                                                        \
  X(isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted, CoolingCoilSetpointatOutdoorDryBulbHigh)                                           \
  X(isCoolingCoilResetOutdoorDryBulbHighDefaulted, CoolingCoilResetOutdoorDryBulbHigh)                                                      \
  X(isHeatingCoilTypeDefaulted, HeatingCoilType)                                                                                             \
  X(isHeatingCoilSetpointControlTypeDefaulted, HeatingCoilSetpointControlType)                                                              \
  X(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)                                                                        \
  X(isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted, HeatingCoilSetpointatOutdoorDryBulbLow)                                             \
  X(isHeatingCoilResetOutdoorDryBulbLowDefaulted, HeatingCoilResetOutdoorDryBulbLow)                                                        \
  X(isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted, HeatingCoilSetpointatOutdoorDryBulbHigh)                                           \
  X(isHeatingCoilResetOutdoorDryBulbHighDefaulted, HeatingCoilResetOutdoorDryBulbHigh)                                                      \
  X(isHeatingCoilCapacityDefaulted, HeatingCoilCapacity)                                                                                     \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                                                           \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)                                                    \
  X(isPreheatCoilTypeDefaulted, PreheatCoilType)                                                                                             \
  X(isPreheatCoilDesignSetpointDefaulted, PreheatCoilDesignSetpoint)                                                                        \
  X(isGasPreheatCoilEfficiencyDefaulted, GasPreheatCoilEfficiency)                                                                           \
  X(isGasPreheatCoilParasiticElectricLoadDefaulted, GasPreheatCoilParasiticElectricLoad)                                                    \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirControlTypeDefaulted, MinimumOutdoorAirControlType)                                                                  \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                               \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                                         \
  X(isEconomizerUpperTemperatureLimitDefaulted, EconomizerUpperTemperatureLimit)                                                            \
  X(isEconomizerLowerTemperatureLimitDefaulted, EconomizerLowerTemperatureLimit)                                                            \
  X(isEconomizerUpperEnthalpyLimitDefaulted, EconomizerUpperEnthalpyLimit)                                                                  \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)                                        \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                                                         \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                                           \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                                        \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                            \
  X(isHeatRecoveryHeatExchangerTypeDefaulted, HeatRecoveryHeatExchangerType)                                                                \
  X(isHeatRecoveryFrostControlTypeDefaulted, HeatRecoveryFrostControlType)                                                                  \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                                                                     \
  X(isDehumidificationRelativeHumiditySetpointDefaulted, DehumidificationRelativeHumiditySetpoint)                                          \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                               \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                             \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                                  \
  X(isHumidifierRelativeHumiditySetpointDefaulted, HumidifierRelativeHumiditySetpoint)                                                      \
  X(isSizingOptionDefaulted, SizingOption)                                                                                                   \
  X(isReturnFanDefaulted, ReturnFan)                                                                                                         \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                                           \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                               \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                                           \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)                                                        \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_DEFAULTED(method, field)                                                                                                     \
  bool HVACTemplateSystemDualDuct_Impl::method() const {                                                                                    \
    return isEmpty(openstudio::HVACTemplate_System_DualDuctFields::field);                                                                  \
  }

OS_DUALDUCT_DEFAULTED_MAP(OS_IMPL_DEFAULTED)

#undef OS_IMPL_DEFAULTED

#define OS_DUALDUCT_AUTOSIZED_MAP(X)                                                                                                         \
  X(isMainSupplyFanMaximumFlowRateAutosized, MainSupplyFanMaximumFlowRate)                                                                  \
  X(isColdDuctSupplyFanMaximumFlowRateAutosized, ColdDuctSupplyFanMaximumFlowRate)                                                          \
  X(isHotDuctSupplyFanMaximumFlowRateAutosized, HotDuctSupplyFanMaximumFlowRate)                                                            \
  X(isHeatingCoilCapacityAutosized, HeatingCoilCapacity)                                                                                     \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                                                                        \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZED(method, field)                                                                                                     \
  bool HVACTemplateSystemDualDuct_Impl::method() const {                                                                                    \
    if (auto value = getString(openstudio::HVACTemplate_System_DualDuctFields::field, true)) {                                             \
      return openstudio::istringEqual(*value, "autosize");                                                                                 \
    }                                                                                                                                         \
    return false;                                                                                                                             \
  }

OS_DUALDUCT_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_AUTOSIZED

#define OS_IMPL_SET_STRING(method, field)                                                                                                    \
  bool HVACTemplateSystemDualDuct_Impl::method(const std::string& value) {                                                                  \
    return setString(openstudio::HVACTemplate_System_DualDuctFields::field, value);                                                        \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                                                                                    \
  bool HVACTemplateSystemDualDuct_Impl::method(double value) {                                                                               \
    return setDouble(openstudio::HVACTemplate_System_DualDuctFields::field, value);                                                        \
  }

OS_DUALDUCT_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
OS_DUALDUCT_DOUBLE_SETTER_MAP(OS_IMPL_SET_DOUBLE)

#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

bool HVACTemplateSystemDualDuct_Impl::setReturnFan(bool returnFan) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_DualDuctFields::ReturnFan, returnFan);
  OS_ASSERT(result);
  return result;
}

#define OS_IMPL_RESET(method, field)                                                                                                         \
  void HVACTemplateSystemDualDuct_Impl::method() {                                                                                           \
    const bool result = setString(openstudio::HVACTemplate_System_DualDuctFields::field, "");                                             \
    OS_ASSERT(result);                                                                                                                        \
  }

#define OS_DUALDUCT_RESET_MAP(X)                                                                                                              \
  X(resetSystemConfigurationType, SystemConfigurationType)                                                                                    \
  X(resetMainSupplyFanMaximumFlowRate, MainSupplyFanMaximumFlowRate)                                                                         \
  X(resetMainSupplyFanMinimumFlowFraction, MainSupplyFanMinimumFlowFraction)                                                                 \
  X(resetMainSupplyFanTotalEfficiency, MainSupplyFanTotalEfficiency)                                                                         \
  X(resetMainSupplyFanDeltaPressure, MainSupplyFanDeltaPressure)                                                                             \
  X(resetMainSupplyFanMotorEfficiency, MainSupplyFanMotorEfficiency)                                                                         \
  X(resetMainSupplyFanMotorinAirStreamFraction, MainSupplyFanMotorinAirStreamFraction)                                                      \
  X(resetMainSupplyFanPartLoadPowerCoefficients, MainSupplyFanPartLoadPowerCoefficients)                                                    \
  X(resetColdDuctSupplyFanMaximumFlowRate, ColdDuctSupplyFanMaximumFlowRate)                                                                 \
  X(resetColdDuctSupplyFanMinimumFlowFraction, ColdDuctSupplyFanMinimumFlowFraction)                                                         \
  X(resetColdDuctSupplyFanTotalEfficiency, ColdDuctSupplyFanTotalEfficiency)                                                                 \
  X(resetColdDuctSupplyFanDeltaPressure, ColdDuctSupplyFanDeltaPressure)                                                                     \
  X(resetColdDuctSupplyFanMotorEfficiency, ColdDuctSupplyFanMotorEfficiency)                                                                 \
  X(resetColdDuctSupplyFanMotorinAirStreamFraction, ColdDuctSupplyFanMotorinAirStreamFraction)                                              \
  X(resetColdDuctSupplyFanPartLoadPowerCoefficients, ColdDuctSupplyFanPartLoadPowerCoefficients)                                            \
  X(resetColdDuctSupplyFanPlacement, ColdDuctSupplyFanPlacement)                                                                             \
  X(resetHotDuctSupplyFanMaximumFlowRate, HotDuctSupplyFanMaximumFlowRate)                                                                   \
  X(resetHotDuctSupplyFanMinimumFlowFraction, HotDuctSupplyFanMinimumFlowFraction)                                                           \
  X(resetHotDuctSupplyFanTotalEfficiency, HotDuctSupplyFanTotalEfficiency)                                                                   \
  X(resetHotDuctSupplyFanDeltaPressure, HotDuctSupplyFanDeltaPressure)                                                                       \
  X(resetHotDuctSupplyFanMotorEfficiency, HotDuctSupplyFanMotorEfficiency)                                                                   \
  X(resetHotDuctSupplyFanMotorinAirStreamFraction, HotDuctSupplyFanMotorinAirStreamFraction)                                                \
  X(resetHotDuctSupplyFanPartLoadPowerCoefficients, HotDuctSupplyFanPartLoadPowerCoefficients)                                              \
  X(resetHotDuctSupplyFanPlacement, HotDuctSupplyFanPlacement)                                                                               \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                                   \
  X(resetCoolingCoilSetpointControlType, CoolingCoilSetpointControlType)                                                                     \
  X(resetCoolingCoilDesignSetpointTemperature, CoolingCoilDesignSetpointTemperature)                                                         \
  X(resetCoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)                                                    \
  X(resetCoolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)                                                               \
  X(resetCoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)                                                  \
  X(resetCoolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)                                                             \
  X(resetHeatingCoilType, HeatingCoilType)                                                                                                   \
  X(resetHeatingCoilSetpointControlType, HeatingCoilSetpointControlType)                                                                     \
  X(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                               \
  X(resetHeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)                                                    \
  X(resetHeatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)                                                               \
  X(resetHeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)                                                  \
  X(resetHeatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)                                                             \
  X(resetHeatingCoilCapacity, HeatingCoilCapacity)                                                                                           \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                 \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                           \
  X(resetPreheatCoilType, PreheatCoilType)                                                                                                   \
  X(resetPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)                                                                               \
  X(resetGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)                                                                                 \
  X(resetGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)                                                           \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                               \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                               \
  X(resetMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                         \
  X(resetEconomizerType, EconomizerType)                                                                                                     \
  X(resetEconomizerLockout, EconomizerLockout)                                                                                               \
  X(resetEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                                                                   \
  X(resetEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                                                                   \
  X(resetEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                                                                         \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                               \
  X(resetNightCycleControl, NightCycleControl)                                                                                               \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                                                                 \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                               \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                   \
  X(resetHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)                                                                       \
  X(resetHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)                                                                         \
  X(resetDehumidificationControlType, DehumidificationControlType)                                                                           \
  X(resetDehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                                 \
  X(resetHumidifierType, HumidifierType)                                                                                                     \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                   \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                         \
  X(resetHumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                             \
  X(resetSizingOption, SizingOption)                                                                                                         \
  X(resetReturnFan, ReturnFan)                                                                                                               \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                                 \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                     \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                                 \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)                                                              \
  X(resetReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

OS_DUALDUCT_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_DUALDUCT_AUTOSIZE_MAP(X)                                                                                                          \
  X(autosizeMainSupplyFanMaximumFlowRate, MainSupplyFanMaximumFlowRate)                                                                     \
  X(autosizeColdDuctSupplyFanMaximumFlowRate, ColdDuctSupplyFanMaximumFlowRate)                                                             \
  X(autosizeHotDuctSupplyFanMaximumFlowRate, HotDuctSupplyFanMaximumFlowRate)                                                               \
  X(autosizeHeatingCoilCapacity, HeatingCoilCapacity)                                                                                        \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                                                      \
  void HVACTemplateSystemDualDuct_Impl::method() {                                                                                           \
    const bool result = setString(openstudio::HVACTemplate_System_DualDuctFields::field, "Autosize");                                    \
    OS_ASSERT(result);                                                                                                                        \
  }

OS_DUALDUCT_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                                        \
  std::vector<std::string> HVACTemplateSystemDualDuct_Impl::method() const {                                                                \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_DualDuct).get(),                             \
                          openstudio::HVACTemplate_System_DualDuctFields::field);                                                           \
  }

OS_DUALDUCT_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_DUALDUCT_VALUES_MAP

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
