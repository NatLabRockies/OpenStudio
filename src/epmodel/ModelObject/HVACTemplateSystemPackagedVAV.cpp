/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemPackagedVAV.hpp"
#include "HVACTemplateSystemPackagedVAV_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_PackagedVAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateSystemPackagedVAV::HVACTemplateSystemPackagedVAV(const Model& model)
  : ModelObject(HVACTemplateSystemPackagedVAV::iddObjectType(), model) {}

HVACTemplateSystemPackagedVAV::HVACTemplateSystemPackagedVAV(std::shared_ptr<detail::HVACTemplateSystemPackagedVAV_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateSystemPackagedVAV::iddObjectType() {
  return IddObjectType::HVACTemplate_System_PackagedVAV;
}

#define OS_PACKAGEDVAV_VALUES_MAP(X)                                                                                                         \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                                                                            \
  X(coolingCoilTypeValues, CoolingCoilType)                                                                                                  \
  X(heatingCoilTypeValues, HeatingCoilType)                                                                                                  \
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
  std::vector<std::string> HVACTemplateSystemPackagedVAV::method() {                                                                        \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_PackagedVAVFields::field); \
  }

OS_PACKAGEDVAV_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_PACKAGEDVAV_REQUIRED_STRING_GETTERS(X)                                                                                            \
  X(supplyFanPlacement)                                                                                                                      \
  X(coolingCoilType)                                                                                                                         \
  X(heatingCoilType)                                                                                                                         \
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

#define OS_PACKAGEDVAV_REQUIRED_DOUBLE_GETTERS(X)                                                                                            \
  X(supplyFanTotalEfficiency)                                                                                                                \
  X(supplyFanDeltaPressure)                                                                                                                  \
  X(supplyFanMotorEfficiency)                                                                                                                \
  X(supplyFanMotorinAirStreamFraction)                                                                                                       \
  X(coolingCoilDesignSetpoint)                                                                                                               \
  X(coolingCoilGrossRatedCOP)                                                                                                                \
  X(heatingCoilDesignSetpoint)                                                                                                               \
  X(gasHeatingCoilEfficiency)                                                                                                                \
  X(gasHeatingCoilParasiticElectricLoad)                                                                                                     \
  X(sensibleHeatRecoveryEffectiveness)                                                                                                       \
  X(latentHeatRecoveryEffectiveness)                                                                                                         \
  X(dehumidificationSetpoint)                                                                                                                \
  X(humidifierRatedCapacity)                                                                                                                 \
  X(humidifierSetpoint)                                                                                                                      \
  X(returnFanTotalEfficiency)                                                                                                                \
  X(returnFanDeltaPressure)                                                                                                                  \
  X(returnFanMotorEfficiency)                                                                                                                \
  X(returnFanMotorinAirStreamFraction)

#define OS_PACKAGEDVAV_OPTIONAL_DOUBLE_GETTERS(X)                                                                                            \
  X(supplyFanMaximumFlowRate)                                                                                                                \
  X(supplyFanMinimumFlowRate)                                                                                                                \
  X(coolingCoilGrossRatedTotalCapacity)                                                                                                      \
  X(coolingCoilGrossRatedSensibleHeatRatio)                                                                                                  \
  X(heatingCoilCapacity)                                                                                                                     \
  X(maximumOutdoorAirFlowRate)                                                                                                               \
  X(minimumOutdoorAirFlowRate)                                                                                                               \
  X(economizerMaximumLimitDryBulbTemperature)                                                                                                \
  X(economizerMaximumLimitEnthalpy)                                                                                                          \
  X(economizerMaximumLimitDewpointTemperature)                                                                                               \
  X(economizerMinimumLimitDryBulbTemperature)                                                                                                \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                                                                                            \
  std::string HVACTemplateSystemPackagedVAV::method() const {                                                                               \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method();                                                                 \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                                                                                            \
  double HVACTemplateSystemPackagedVAV::method() const {                                                                                    \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method();                                                                 \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                                                                            \
  boost::optional<double> HVACTemplateSystemPackagedVAV::method() const {                                                                   \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method();                                                                 \
  }

OS_PACKAGEDVAV_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
OS_PACKAGEDVAV_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
OS_PACKAGEDVAV_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

bool HVACTemplateSystemPackagedVAV::returnFan() const {
  return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->returnFan();
}

#define OS_PACKAGEDVAV_DEFAULTED_METHODS_MAP(X)                                                                                             \
  X(isSupplyFanMaximumFlowRateDefaulted)                                                                                                    \
  X(isSupplyFanMinimumFlowRateDefaulted)                                                                                                    \
  X(isSupplyFanPlacementDefaulted)                                                                                                          \
  X(isSupplyFanTotalEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanDeltaPressureDefaulted)                                                                                                      \
  X(isSupplyFanMotorEfficiencyDefaulted)                                                                                                    \
  X(isSupplyFanMotorinAirStreamFractionDefaulted)                                                                                           \
  X(isCoolingCoilTypeDefaulted)                                                                                                             \
  X(isCoolingCoilDesignSetpointDefaulted)                                                                                                   \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted)                                                                                          \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)                                                                                      \
  X(isCoolingCoilGrossRatedCOPDefaulted)                                                                                                    \
  X(isHeatingCoilTypeDefaulted)                                                                                                             \
  X(isHeatingCoilDesignSetpointDefaulted)                                                                                                   \
  X(isHeatingCoilCapacityDefaulted)                                                                                                         \
  X(isGasHeatingCoilEfficiencyDefaulted)                                                                                                    \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted)                                                                                         \
  X(isMaximumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateDefaulted)                                                                                                   \
  X(isMinimumOutdoorAirControlTypeDefaulted)                                                                                                \
  X(isEconomizerTypeDefaulted)                                                                                                              \
  X(isEconomizerLockoutDefaulted)                                                                                                           \
  X(isEconomizerMaximumLimitDryBulbTemperatureDefaulted)                                                                                    \
  X(isEconomizerMaximumLimitEnthalpyDefaulted)                                                                                              \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted)                                                                                   \
  X(isEconomizerMinimumLimitDryBulbTemperatureDefaulted)                                                                                    \
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

#define OS_PACKAGEDVAV_AUTOSIZED_METHODS_MAP(X)                                                                                             \
  X(isSupplyFanMaximumFlowRateAutosized)                                                                                                    \
  X(isSupplyFanMinimumFlowRateAutosized)                                                                                                    \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized)                                                                                          \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized)                                                                                      \
  X(isHeatingCoilCapacityAutosized)                                                                                                         \
  X(isMaximumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isMinimumOutdoorAirFlowRateAutosized)                                                                                                   \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                                                                                              \
  bool HVACTemplateSystemPackagedVAV::method() const {                                                                                      \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method();                                                                 \
  }

OS_PACKAGEDVAV_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
OS_PACKAGEDVAV_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_PACKAGEDVAV_STRING_SETTERS(X)                                                                                                     \
  X(setSupplyFanPlacement)                                                                                                                  \
  X(setCoolingCoilType)                                                                                                                     \
  X(setHeatingCoilType)                                                                                                                     \
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

#define OS_PACKAGEDVAV_DOUBLE_SETTERS(X)                                                                                                     \
  X(setSupplyFanMaximumFlowRate)                                                                                                            \
  X(setSupplyFanMinimumFlowRate)                                                                                                            \
  X(setSupplyFanTotalEfficiency)                                                                                                            \
  X(setSupplyFanDeltaPressure)                                                                                                              \
  X(setSupplyFanMotorEfficiency)                                                                                                            \
  X(setSupplyFanMotorinAirStreamFraction)                                                                                                   \
  X(setCoolingCoilDesignSetpoint)                                                                                                           \
  X(setCoolingCoilGrossRatedTotalCapacity)                                                                                                  \
  X(setCoolingCoilGrossRatedSensibleHeatRatio)                                                                                              \
  X(setCoolingCoilGrossRatedCOP)                                                                                                            \
  X(setHeatingCoilDesignSetpoint)                                                                                                           \
  X(setHeatingCoilCapacity)                                                                                                                 \
  X(setGasHeatingCoilEfficiency)                                                                                                            \
  X(setGasHeatingCoilParasiticElectricLoad)                                                                                                 \
  X(setMaximumOutdoorAirFlowRate)                                                                                                           \
  X(setMinimumOutdoorAirFlowRate)                                                                                                           \
  X(setEconomizerMaximumLimitDryBulbTemperature)                                                                                            \
  X(setEconomizerMaximumLimitEnthalpy)                                                                                                      \
  X(setEconomizerMaximumLimitDewpointTemperature)                                                                                           \
  X(setEconomizerMinimumLimitDryBulbTemperature)                                                                                            \
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

#define OS_FORWARD_STRING_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemPackagedVAV::method(const std::string& value) {                                                                   \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(value);                                                           \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                                                                                     \
  bool HVACTemplateSystemPackagedVAV::method(double value) {                                                                                \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(value);                                                           \
  }

OS_PACKAGEDVAV_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
OS_PACKAGEDVAV_DOUBLE_SETTERS(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER

bool HVACTemplateSystemPackagedVAV::setReturnFan(bool returnFan) {
  return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->setReturnFan(returnFan);
}

#define OS_PACKAGEDVAV_RESETS(X)                                                                                                             \
  X(resetSupplyFanMaximumFlowRate)                                                                                                          \
  X(resetSupplyFanMinimumFlowRate)                                                                                                          \
  X(resetSupplyFanPlacement)                                                                                                                \
  X(resetSupplyFanTotalEfficiency)                                                                                                          \
  X(resetSupplyFanDeltaPressure)                                                                                                            \
  X(resetSupplyFanMotorEfficiency)                                                                                                          \
  X(resetSupplyFanMotorinAirStreamFraction)                                                                                                 \
  X(resetCoolingCoilType)                                                                                                                   \
  X(resetCoolingCoilDesignSetpoint)                                                                                                         \
  X(resetCoolingCoilGrossRatedTotalCapacity)                                                                                                \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio)                                                                                            \
  X(resetCoolingCoilGrossRatedCOP)                                                                                                          \
  X(resetHeatingCoilType)                                                                                                                   \
  X(resetHeatingCoilDesignSetpoint)                                                                                                         \
  X(resetHeatingCoilCapacity)                                                                                                               \
  X(resetGasHeatingCoilEfficiency)                                                                                                          \
  X(resetGasHeatingCoilParasiticElectricLoad)                                                                                               \
  X(resetMaximumOutdoorAirFlowRate)                                                                                                         \
  X(resetMinimumOutdoorAirFlowRate)                                                                                                         \
  X(resetMinimumOutdoorAirControlType)                                                                                                      \
  X(resetEconomizerType)                                                                                                                    \
  X(resetEconomizerLockout)                                                                                                                 \
  X(resetEconomizerMaximumLimitDryBulbTemperature)                                                                                          \
  X(resetEconomizerMaximumLimitEnthalpy)                                                                                                    \
  X(resetEconomizerMaximumLimitDewpointTemperature)                                                                                         \
  X(resetEconomizerMinimumLimitDryBulbTemperature)                                                                                          \
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

#define OS_PACKAGEDVAV_AUTOSIZES(X)                                                                                                          \
  X(autosizeSupplyFanMaximumFlowRate)                                                                                                       \
  X(autosizeSupplyFanMinimumFlowRate)                                                                                                       \
  X(autosizeCoolingCoilGrossRatedTotalCapacity)                                                                                             \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio)                                                                                         \
  X(autosizeHeatingCoilCapacity)                                                                                                            \
  X(autosizeMaximumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeMinimumOutdoorAirFlowRate)                                                                                                      \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                                                                                              \
  void HVACTemplateSystemPackagedVAV::method() {                                                                                            \
    getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method();                                                                        \
  }

OS_PACKAGEDVAV_RESETS(OS_FORWARD_VOID)
OS_PACKAGEDVAV_AUTOSIZES(OS_FORWARD_VOID)

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

#define OS_PACKAGEDVAV_REQUIRED_STRING_MAP(X)                                                                                               \
  X(supplyFanPlacement, SupplyFanPlacement)                                                                                                 \
  X(coolingCoilType, CoolingCoilType)                                                                                                       \
  X(heatingCoilType, HeatingCoilType)                                                                                                       \
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

#define OS_PACKAGEDVAV_REQUIRED_DOUBLE_MAP(X)                                                                                               \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                     \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                         \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                     \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                                   \
  X(coolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                                   \
  X(coolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                     \
  X(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                   \
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

#define OS_PACKAGEDVAV_OPTIONAL_DOUBLE_MAP(X)                                                                                               \
  X(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                     \
  X(supplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                     \
  X(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                                 \
  X(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                         \
  X(heatingCoilCapacity, HeatingCoilCapacity)                                                                                                \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                   \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                   \
  X(economizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)                                                     \
  X(economizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                                                                         \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                   \
  X(economizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)                                                     \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                                                              \
  std::string HVACTemplateSystemPackagedVAV_Impl::method() const {                                                                          \
    const auto value = getString(openstudio::HVACTemplate_System_PackagedVAVFields::field, true);                                          \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                                                              \
  double HVACTemplateSystemPackagedVAV_Impl::method() const {                                                                               \
    const auto value = getDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, true);                                          \
    OS_ASSERT(value);                                                                                                                        \
    return *value;                                                                                                                           \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                                                                              \
  boost::optional<double> HVACTemplateSystemPackagedVAV_Impl::method() const {                                                              \
    return getDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, true);                                                      \
  }

OS_PACKAGEDVAV_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING)
OS_PACKAGEDVAV_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE)
OS_PACKAGEDVAV_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE)

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_STRING

bool HVACTemplateSystemPackagedVAV_Impl::returnFan() const {
  return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_PackagedVAVFields::ReturnFan);
}

#define OS_PACKAGEDVAV_DEFAULTED_MAP(X)                                                                                                     \
  X(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)                                                                          \
  X(isSupplyFanMinimumFlowRateDefaulted, SupplyFanMinimumFlowRate)                                                                          \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                                                                      \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                                                          \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                                                              \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                                                          \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                                                       \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                            \
  X(isCoolingCoilDesignSetpointDefaulted, CoolingCoilDesignSetpoint)                                                                        \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)                                                     \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)                                             \
  X(isCoolingCoilGrossRatedCOPDefaulted, CoolingCoilGrossRatedCOP)                                                                          \
  X(isHeatingCoilTypeDefaulted, HeatingCoilType)                                                                                            \
  X(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)                                                                        \
  X(isHeatingCoilCapacityDefaulted, HeatingCoilCapacity)                                                                                    \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                                                          \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)                                                   \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirControlTypeDefaulted, MinimumOutdoorAirControlType)                                                                  \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                              \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                                        \
  X(isEconomizerMaximumLimitDryBulbTemperatureDefaulted, EconomizerMaximumLimitDryBulbTemperature)                                         \
  X(isEconomizerMaximumLimitEnthalpyDefaulted, EconomizerMaximumLimitEnthalpy)                                                             \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)                                       \
  X(isEconomizerMinimumLimitDryBulbTemperatureDefaulted, EconomizerMinimumLimitDryBulbTemperature)                                         \
  X(isSupplyFanPartLoadPowerCoefficientsDefaulted, SupplyFanPartLoadPowerCoefficients)                                                     \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                                                        \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                                          \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                                        \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                            \
  X(isCoolingCoilSetpointResetTypeDefaulted, CoolingCoilSetpointResetType)                                                                  \
  X(isHeatingCoilSetpointResetTypeDefaulted, HeatingCoilSetpointResetType)                                                                  \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                                                                    \
  X(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)                                                                          \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                              \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                            \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                                  \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                                                                      \
  X(isSizingOptionDefaulted, SizingOption)                                                                                                  \
  X(isReturnFanDefaulted, ReturnFan)                                                                                                        \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                                          \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                              \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                                          \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)                                                       \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_DEFAULTED(method, field)                                                                                                    \
  bool HVACTemplateSystemPackagedVAV_Impl::method() const {                                                                                 \
    return isEmpty(openstudio::HVACTemplate_System_PackagedVAVFields::field);                                                              \
  }

OS_PACKAGEDVAV_DEFAULTED_MAP(OS_IMPL_DEFAULTED)

#undef OS_IMPL_DEFAULTED

#define OS_PACKAGEDVAV_AUTOSIZED_MAP(X)                                                                                                     \
  X(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)                                                                          \
  X(isSupplyFanMinimumFlowRateAutosized, SupplyFanMinimumFlowRate)                                                                          \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)                                                     \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio)                                             \
  X(isHeatingCoilCapacityAutosized, HeatingCoilCapacity)                                                                                    \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                                                                        \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                                                                        \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZED(method, field)                                                                                                    \
  bool HVACTemplateSystemPackagedVAV_Impl::method() const {                                                                                 \
    if (auto value = getString(openstudio::HVACTemplate_System_PackagedVAVFields::field, true)) {                                         \
      return openstudio::istringEqual(*value, "autosize");                                                                                \
    }                                                                                                                                        \
    return false;                                                                                                                            \
  }

OS_PACKAGEDVAV_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_AUTOSIZED

#define OS_PACKAGEDVAV_STRING_SETTER_MAP(X)                                                                                                 \
  X(setSupplyFanPlacement, SupplyFanPlacement)                                                                                              \
  X(setCoolingCoilType, CoolingCoilType)                                                                                                    \
  X(setHeatingCoilType, HeatingCoilType)                                                                                                    \
  X(setMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                          \
  X(setEconomizerType, EconomizerType)                                                                                                      \
  X(setEconomizerLockout, EconomizerLockout)                                                                                                \
  X(setSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)                                                             \
  X(setNightCycleControl, NightCycleControl)                                                                                                \
  X(setHeatRecoveryType, HeatRecoveryType)                                                                                                  \
  X(setCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)                                                                          \
  X(setHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)                                                                          \
  X(setDehumidificationControlType, DehumidificationControlType)                                                                            \
  X(setHumidifierType, HumidifierType)                                                                                                      \
  X(setSizingOption, SizingOption)                                                                                                          \
  X(setReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_PACKAGEDVAV_DOUBLE_SETTER_MAP(X)                                                                                                 \
  X(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                  \
  X(setSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                  \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                  \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                      \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                  \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                               \
  X(setCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                                \
  X(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                              \
  X(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                      \
  X(setCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                  \
  X(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                                \
  X(setHeatingCoilCapacity, HeatingCoilCapacity)                                                                                            \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                  \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                            \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                                \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                                \
  X(setEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)                                                 \
  X(setEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                                                                      \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                                \
  X(setEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)                                                  \
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
  bool HVACTemplateSystemPackagedVAV_Impl::method(const std::string& value) {                                                              \
    return setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, value);                                                     \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                                                                                   \
  bool HVACTemplateSystemPackagedVAV_Impl::method(double value) {                                                                           \
    return setDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, value);                                                     \
  }

OS_PACKAGEDVAV_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
OS_PACKAGEDVAV_DOUBLE_SETTER_MAP(OS_IMPL_SET_DOUBLE)

#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

bool HVACTemplateSystemPackagedVAV_Impl::setReturnFan(bool returnFan) {
  const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_PackagedVAVFields::ReturnFan, returnFan);
  OS_ASSERT(result);
  return result;
}

#define OS_PACKAGEDVAV_RESET_MAP(X)                                                                                                         \
  X(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                                \
  X(resetSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                                \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                                                                            \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                                \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                    \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                                \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                                  \
  X(resetCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                                                              \
  X(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                            \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                    \
  X(resetCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                                                                \
  X(resetHeatingCoilType, HeatingCoilType)                                                                                                  \
  X(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                                                              \
  X(resetHeatingCoilCapacity, HeatingCoilCapacity)                                                                                          \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                                \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                              \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                              \
  X(resetMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                                                                        \
  X(resetEconomizerType, EconomizerType)                                                                                                    \
  X(resetEconomizerLockout, EconomizerLockout)                                                                                              \
  X(resetEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)                                               \
  X(resetEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                                                                   \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                             \
  X(resetEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)                                               \
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
  void HVACTemplateSystemPackagedVAV_Impl::method() {                                                                                       \
    const bool result = setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, "");                                        \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_PACKAGEDVAV_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_PACKAGEDVAV_AUTOSIZE_MAP(X)                                                                                                      \
  X(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                                                             \
  X(autosizeSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                                                             \
  X(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)                                                         \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)                                                 \
  X(autosizeHeatingCoilCapacity, HeatingCoilCapacity)                                                                                       \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                                                     \
  void HVACTemplateSystemPackagedVAV_Impl::method() {                                                                                       \
    const bool result = setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, "Autosize");                                \
    OS_ASSERT(result);                                                                                                                       \
  }

OS_PACKAGEDVAV_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                                       \
  std::vector<std::string> HVACTemplateSystemPackagedVAV_Impl::method() const {                                                            \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_PackagedVAV).get(),                          \
                          openstudio::HVACTemplate_System_PackagedVAVFields::field);                                                       \
  }

OS_PACKAGEDVAV_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_PACKAGEDVAV_VALUES_MAP

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
