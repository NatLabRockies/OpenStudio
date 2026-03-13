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

#define OS_PACKAGEDVAV_VALUES_MAP(X)                                              \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                 \
  X(coolingCoilTypeValues, CoolingCoilType)                                       \
  X(heatingCoilTypeValues, HeatingCoilType)                                       \
  X(minimumOutdoorAirControlTypeValues, MinimumOutdoorAirControlType)             \
  X(economizerTypeValues, EconomizerType)                                         \
  X(economizerLockoutValues, EconomizerLockout)                                   \
  X(supplyFanPartLoadPowerCoefficientsValues, SupplyFanPartLoadPowerCoefficients) \
  X(nightCycleControlValues, NightCycleControl)                                   \
  X(heatRecoveryTypeValues, HeatRecoveryType)                                     \
  X(coolingCoilSetpointResetTypeValues, CoolingCoilSetpointResetType)             \
  X(heatingCoilSetpointResetTypeValues, HeatingCoilSetpointResetType)             \
  X(dehumidificationControlTypeValues, DehumidificationControlType)               \
  X(humidifierTypeValues, HumidifierType)                                         \
  X(sizingOptionValues, SizingOption)                                             \
  X(returnFanPartLoadPowerCoefficientsValues, ReturnFanPartLoadPowerCoefficients)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                                \
  std::vector<std::string> HVACTemplateSystemPackagedVAV::method() {                                                                          \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_PackagedVAVFields::field); \
  }

  OS_PACKAGEDVAV_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_PACKAGEDVAV_REQUIRED_STRING_GETTERS(X) \
  X(supplyFanPlacement)                           \
  X(coolingCoilType)                              \
  X(heatingCoilType)                              \
  X(minimumOutdoorAirControlType)                 \
  X(economizerType)                               \
  X(economizerLockout)                            \
  X(supplyFanPartLoadPowerCoefficients)           \
  X(nightCycleControl)                            \
  X(heatRecoveryType)                             \
  X(coolingCoilSetpointResetType)                 \
  X(heatingCoilSetpointResetType)                 \
  X(dehumidificationControlType)                  \
  X(humidifierType)                               \
  X(sizingOption)                                 \
  X(returnFanPartLoadPowerCoefficients)

#define OS_PACKAGEDVAV_REQUIRED_DOUBLE_GETTERS(X) \
  X(supplyFanTotalEfficiency)                     \
  X(supplyFanDeltaPressure)                       \
  X(supplyFanMotorEfficiency)                     \
  X(supplyFanMotorinAirStreamFraction)            \
  X(coolingCoilDesignSetpoint)                    \
  X(coolingCoilGrossRatedCOP)                     \
  X(heatingCoilDesignSetpoint)                    \
  X(gasHeatingCoilEfficiency)                     \
  X(gasHeatingCoilParasiticElectricLoad)          \
  X(sensibleHeatRecoveryEffectiveness)            \
  X(latentHeatRecoveryEffectiveness)              \
  X(dehumidificationSetpoint)                     \
  X(humidifierRatedCapacity)                      \
  X(humidifierSetpoint)                           \
  X(returnFanTotalEfficiency)                     \
  X(returnFanDeltaPressure)                       \
  X(returnFanMotorEfficiency)                     \
  X(returnFanMotorinAirStreamFraction)

#define OS_PACKAGEDVAV_OPTIONAL_DOUBLE_GETTERS(X) \
  X(supplyFanMaximumFlowRate)                     \
  X(supplyFanMinimumFlowRate)                     \
  X(coolingCoilGrossRatedTotalCapacity)           \
  X(coolingCoilGrossRatedSensibleHeatRatio)       \
  X(heatingCoilCapacity)                          \
  X(maximumOutdoorAirFlowRate)                    \
  X(minimumOutdoorAirFlowRate)                    \
  X(economizerMaximumLimitDryBulbTemperature)     \
  X(economizerMaximumLimitEnthalpy)               \
  X(economizerMaximumLimitDewpointTemperature)    \
  X(economizerMinimumLimitDryBulbTemperature)     \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                           \
  std::string HVACTemplateSystemPackagedVAV::method() const {               \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                           \
  double HVACTemplateSystemPackagedVAV::method() const {                    \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                           \
  boost::optional<double> HVACTemplateSystemPackagedVAV::method() const {   \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(); \
  }

#define OS_FORWARD_BOOL(method)                                             \
  bool HVACTemplateSystemPackagedVAV::method() const {                      \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(); \
  }

#define OS_FORWARD_STRING_SETTER(method)                                         \
  bool HVACTemplateSystemPackagedVAV::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(value); \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                         \
  bool HVACTemplateSystemPackagedVAV::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(value); \
  }

#define OS_FORWARD_VOID(method)                                      \
  void HVACTemplateSystemPackagedVAV::method() {                     \
    getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->method(); \
  }

  bool HVACTemplateSystemPackagedVAV::returnFan() const {
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->returnFan();
  }

  OS_FORWARD_BOOL(isReturnFanDefaulted)

  bool HVACTemplateSystemPackagedVAV::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemPackagedVAV_Impl>()->setReturnFan(returnFan);
  }

  OS_FORWARD_VOID(resetReturnFan)

  OS_FORWARD_REQUIRED_STRING_GETTER(supplyFanPlacement)
  OS_FORWARD_BOOL(isSupplyFanPlacementDefaulted)
  OS_FORWARD_STRING_SETTER(setSupplyFanPlacement)
  OS_FORWARD_VOID(resetSupplyFanPlacement)

  OS_FORWARD_REQUIRED_STRING_GETTER(coolingCoilType)
  OS_FORWARD_BOOL(isCoolingCoilTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setCoolingCoilType)
  OS_FORWARD_VOID(resetCoolingCoilType)

  OS_FORWARD_REQUIRED_STRING_GETTER(heatingCoilType)
  OS_FORWARD_BOOL(isHeatingCoilTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatingCoilType)
  OS_FORWARD_VOID(resetHeatingCoilType)

  OS_FORWARD_REQUIRED_STRING_GETTER(minimumOutdoorAirControlType)
  OS_FORWARD_BOOL(isMinimumOutdoorAirControlTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setMinimumOutdoorAirControlType)
  OS_FORWARD_VOID(resetMinimumOutdoorAirControlType)

  OS_FORWARD_REQUIRED_STRING_GETTER(economizerType)
  OS_FORWARD_BOOL(isEconomizerTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setEconomizerType)
  OS_FORWARD_VOID(resetEconomizerType)

  OS_FORWARD_REQUIRED_STRING_GETTER(economizerLockout)
  OS_FORWARD_BOOL(isEconomizerLockoutDefaulted)
  OS_FORWARD_STRING_SETTER(setEconomizerLockout)
  OS_FORWARD_VOID(resetEconomizerLockout)

  OS_FORWARD_REQUIRED_STRING_GETTER(supplyFanPartLoadPowerCoefficients)
  OS_FORWARD_BOOL(isSupplyFanPartLoadPowerCoefficientsDefaulted)
  OS_FORWARD_STRING_SETTER(setSupplyFanPartLoadPowerCoefficients)
  OS_FORWARD_VOID(resetSupplyFanPartLoadPowerCoefficients)

  OS_FORWARD_REQUIRED_STRING_GETTER(nightCycleControl)
  OS_FORWARD_BOOL(isNightCycleControlDefaulted)
  OS_FORWARD_STRING_SETTER(setNightCycleControl)
  OS_FORWARD_VOID(resetNightCycleControl)

  OS_FORWARD_REQUIRED_STRING_GETTER(heatRecoveryType)
  OS_FORWARD_BOOL(isHeatRecoveryTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatRecoveryType)
  OS_FORWARD_VOID(resetHeatRecoveryType)

  OS_FORWARD_REQUIRED_STRING_GETTER(coolingCoilSetpointResetType)
  OS_FORWARD_BOOL(isCoolingCoilSetpointResetTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setCoolingCoilSetpointResetType)
  OS_FORWARD_VOID(resetCoolingCoilSetpointResetType)

  OS_FORWARD_REQUIRED_STRING_GETTER(heatingCoilSetpointResetType)
  OS_FORWARD_BOOL(isHeatingCoilSetpointResetTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatingCoilSetpointResetType)
  OS_FORWARD_VOID(resetHeatingCoilSetpointResetType)

  OS_FORWARD_REQUIRED_STRING_GETTER(dehumidificationControlType)
  OS_FORWARD_BOOL(isDehumidificationControlTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setDehumidificationControlType)
  OS_FORWARD_VOID(resetDehumidificationControlType)

  OS_FORWARD_REQUIRED_STRING_GETTER(humidifierType)
  OS_FORWARD_BOOL(isHumidifierTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHumidifierType)
  OS_FORWARD_VOID(resetHumidifierType)

  OS_FORWARD_REQUIRED_STRING_GETTER(sizingOption)
  OS_FORWARD_BOOL(isSizingOptionDefaulted)
  OS_FORWARD_STRING_SETTER(setSizingOption)
  OS_FORWARD_VOID(resetSizingOption)

  OS_FORWARD_REQUIRED_STRING_GETTER(returnFanPartLoadPowerCoefficients)
  OS_FORWARD_BOOL(isReturnFanPartLoadPowerCoefficientsDefaulted)
  OS_FORWARD_STRING_SETTER(setReturnFanPartLoadPowerCoefficients)
  OS_FORWARD_VOID(resetReturnFanPartLoadPowerCoefficients)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanTotalEfficiency)
  OS_FORWARD_BOOL(isSupplyFanTotalEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanTotalEfficiency)
  OS_FORWARD_VOID(resetSupplyFanTotalEfficiency)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanDeltaPressure)
  OS_FORWARD_BOOL(isSupplyFanDeltaPressureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanDeltaPressure)
  OS_FORWARD_VOID(resetSupplyFanDeltaPressure)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanMotorEfficiency)
  OS_FORWARD_BOOL(isSupplyFanMotorEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMotorEfficiency)
  OS_FORWARD_VOID(resetSupplyFanMotorEfficiency)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanMotorinAirStreamFraction)
  OS_FORWARD_BOOL(isSupplyFanMotorinAirStreamFractionDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMotorinAirStreamFraction)
  OS_FORWARD_VOID(resetSupplyFanMotorinAirStreamFraction)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(coolingCoilDesignSetpoint)
  OS_FORWARD_BOOL(isCoolingCoilDesignSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilDesignSetpoint)
  OS_FORWARD_VOID(resetCoolingCoilDesignSetpoint)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(coolingCoilGrossRatedCOP)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedCOPDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedCOP)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedCOP)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(heatingCoilDesignSetpoint)
  OS_FORWARD_BOOL(isHeatingCoilDesignSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHeatingCoilDesignSetpoint)
  OS_FORWARD_VOID(resetHeatingCoilDesignSetpoint)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasHeatingCoilEfficiency)
  OS_FORWARD_BOOL(isGasHeatingCoilEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasHeatingCoilEfficiency)
  OS_FORWARD_VOID(resetGasHeatingCoilEfficiency)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasHeatingCoilParasiticElectricLoad)
  OS_FORWARD_BOOL(isGasHeatingCoilParasiticElectricLoadDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasHeatingCoilParasiticElectricLoad)
  OS_FORWARD_VOID(resetGasHeatingCoilParasiticElectricLoad)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(sensibleHeatRecoveryEffectiveness)
  OS_FORWARD_BOOL(isSensibleHeatRecoveryEffectivenessDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSensibleHeatRecoveryEffectiveness)
  OS_FORWARD_VOID(resetSensibleHeatRecoveryEffectiveness)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(latentHeatRecoveryEffectiveness)
  OS_FORWARD_BOOL(isLatentHeatRecoveryEffectivenessDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setLatentHeatRecoveryEffectiveness)
  OS_FORWARD_VOID(resetLatentHeatRecoveryEffectiveness)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(dehumidificationSetpoint)
  OS_FORWARD_BOOL(isDehumidificationSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setDehumidificationSetpoint)
  OS_FORWARD_VOID(resetDehumidificationSetpoint)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(humidifierRatedCapacity)
  OS_FORWARD_BOOL(isHumidifierRatedCapacityDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierRatedCapacity)
  OS_FORWARD_VOID(resetHumidifierRatedCapacity)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(humidifierSetpoint)
  OS_FORWARD_BOOL(isHumidifierSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierSetpoint)
  OS_FORWARD_VOID(resetHumidifierSetpoint)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanTotalEfficiency)
  OS_FORWARD_BOOL(isReturnFanTotalEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanTotalEfficiency)
  OS_FORWARD_VOID(resetReturnFanTotalEfficiency)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanDeltaPressure)
  OS_FORWARD_BOOL(isReturnFanDeltaPressureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanDeltaPressure)
  OS_FORWARD_VOID(resetReturnFanDeltaPressure)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanMotorEfficiency)
  OS_FORWARD_BOOL(isReturnFanMotorEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanMotorEfficiency)
  OS_FORWARD_VOID(resetReturnFanMotorEfficiency)

  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanMotorinAirStreamFraction)
  OS_FORWARD_BOOL(isReturnFanMotorinAirStreamFractionDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanMotorinAirStreamFraction)
  OS_FORWARD_VOID(resetReturnFanMotorinAirStreamFraction)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanMaximumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMaximumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateAutosized)
  OS_FORWARD_VOID(autosizeSupplyFanMaximumFlowRate)
  OS_FORWARD_VOID(resetSupplyFanMaximumFlowRate)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanMinimumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMinimumFlowRateDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMinimumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMinimumFlowRateAutosized)
  OS_FORWARD_VOID(autosizeSupplyFanMinimumFlowRate)
  OS_FORWARD_VOID(resetSupplyFanMinimumFlowRate)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityAutosized)
  OS_FORWARD_VOID(autosizeCoolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedTotalCapacity)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioAutosized)
  OS_FORWARD_VOID(autosizeCoolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedSensibleHeatRatio)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(heatingCoilCapacity)
  OS_FORWARD_BOOL(isHeatingCoilCapacityDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHeatingCoilCapacity)
  OS_FORWARD_BOOL(isHeatingCoilCapacityAutosized)
  OS_FORWARD_VOID(autosizeHeatingCoilCapacity)
  OS_FORWARD_VOID(resetHeatingCoilCapacity)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(maximumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMaximumOutdoorAirFlowRateDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setMaximumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMaximumOutdoorAirFlowRateAutosized)
  OS_FORWARD_VOID(autosizeMaximumOutdoorAirFlowRate)
  OS_FORWARD_VOID(resetMaximumOutdoorAirFlowRate)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(minimumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMinimumOutdoorAirFlowRateDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setMinimumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMinimumOutdoorAirFlowRateAutosized)
  OS_FORWARD_VOID(autosizeMinimumOutdoorAirFlowRate)
  OS_FORWARD_VOID(resetMinimumOutdoorAirFlowRate)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerMaximumLimitDryBulbTemperature)
  OS_FORWARD_BOOL(isEconomizerMaximumLimitDryBulbTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerMaximumLimitDryBulbTemperature)
  OS_FORWARD_VOID(resetEconomizerMaximumLimitDryBulbTemperature)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerMaximumLimitEnthalpy)
  OS_FORWARD_BOOL(isEconomizerMaximumLimitEnthalpyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerMaximumLimitEnthalpy)
  OS_FORWARD_VOID(resetEconomizerMaximumLimitEnthalpy)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerMaximumLimitDewpointTemperature)
  OS_FORWARD_BOOL(isEconomizerMaximumLimitDewpointTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerMaximumLimitDewpointTemperature)
  OS_FORWARD_VOID(resetEconomizerMaximumLimitDewpointTemperature)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerMinimumLimitDryBulbTemperature)
  OS_FORWARD_BOOL(isEconomizerMinimumLimitDryBulbTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerMinimumLimitDryBulbTemperature)
  OS_FORWARD_VOID(resetEconomizerMinimumLimitDryBulbTemperature)

  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(humidifierRatedElectricPower)
  OS_FORWARD_BOOL(isHumidifierRatedElectricPowerDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierRatedElectricPower)
  OS_FORWARD_BOOL(isHumidifierRatedElectricPowerAutosized)
  OS_FORWARD_VOID(autosizeHumidifierRatedElectricPower)
  OS_FORWARD_VOID(resetHumidifierRatedElectricPower)

#undef OS_FORWARD_VOID
#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_STRING_SETTER
#undef OS_FORWARD_BOOL
#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

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

#define OS_PACKAGEDVAV_REQUIRED_STRING_MAP(X)                               \
  X(supplyFanPlacement, SupplyFanPlacement)                                 \
  X(coolingCoilType, CoolingCoilType)                                       \
  X(heatingCoilType, HeatingCoilType)                                       \
  X(minimumOutdoorAirControlType, MinimumOutdoorAirControlType)             \
  X(economizerType, EconomizerType)                                         \
  X(economizerLockout, EconomizerLockout)                                   \
  X(supplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients) \
  X(nightCycleControl, NightCycleControl)                                   \
  X(heatRecoveryType, HeatRecoveryType)                                     \
  X(coolingCoilSetpointResetType, CoolingCoilSetpointResetType)             \
  X(heatingCoilSetpointResetType, HeatingCoilSetpointResetType)             \
  X(dehumidificationControlType, DehumidificationControlType)               \
  X(humidifierType, HumidifierType)                                         \
  X(sizingOption, SizingOption)                                             \
  X(returnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_PACKAGEDVAV_REQUIRED_DOUBLE_MAP(X)                                 \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                       \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                           \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                       \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)     \
  X(coolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                     \
  X(coolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                       \
  X(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                     \
  X(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                       \
  X(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad) \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)     \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)         \
  X(dehumidificationSetpoint, DehumidificationSetpoint)                       \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                         \
  X(humidifierSetpoint, HumidifierSetpoint)                                   \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                       \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                           \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                       \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_PACKAGEDVAV_OPTIONAL_DOUBLE_MAP(X)                                             \
  X(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(supplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                   \
  X(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(heatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(economizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(economizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(economizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)   \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                    \
  std::string HVACTemplateSystemPackagedVAV_Impl::method() const {                                \
    const auto value = getString(openstudio::HVACTemplate_System_PackagedVAVFields::field, true); \
    OS_ASSERT(value);                                                                             \
    return *value;                                                                                \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                    \
  double HVACTemplateSystemPackagedVAV_Impl::method() const {                                     \
    const auto value = getDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, true); \
    OS_ASSERT(value);                                                                             \
    return *value;                                                                                \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                        \
  boost::optional<double> HVACTemplateSystemPackagedVAV_Impl::method() const {        \
    return getDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, true); \
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

#define OS_PACKAGEDVAV_DEFAULTED_MAP(X)                                                              \
  X(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)                                   \
  X(isSupplyFanMinimumFlowRateDefaulted, SupplyFanMinimumFlowRate)                                   \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                               \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                   \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                       \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                   \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                 \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                     \
  X(isCoolingCoilDesignSetpointDefaulted, CoolingCoilDesignSetpoint)                                 \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)               \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(isCoolingCoilGrossRatedCOPDefaulted, CoolingCoilGrossRatedCOP)                                   \
  X(isHeatingCoilTypeDefaulted, HeatingCoilType)                                                     \
  X(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)                                 \
  X(isHeatingCoilCapacityDefaulted, HeatingCoilCapacity)                                             \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                   \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)             \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                 \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                 \
  X(isMinimumOutdoorAirControlTypeDefaulted, MinimumOutdoorAirControlType)                           \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                       \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                 \
  X(isEconomizerMaximumLimitDryBulbTemperatureDefaulted, EconomizerMaximumLimitDryBulbTemperature)   \
  X(isEconomizerMaximumLimitEnthalpyDefaulted, EconomizerMaximumLimitEnthalpy)                       \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature) \
  X(isEconomizerMinimumLimitDryBulbTemperatureDefaulted, EconomizerMinimumLimitDryBulbTemperature)   \
  X(isSupplyFanPartLoadPowerCoefficientsDefaulted, SupplyFanPartLoadPowerCoefficients)               \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                 \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                   \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                 \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                     \
  X(isCoolingCoilSetpointResetTypeDefaulted, CoolingCoilSetpointResetType)                           \
  X(isHeatingCoilSetpointResetTypeDefaulted, HeatingCoilSetpointResetType)                           \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                             \
  X(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)                                   \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                       \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                     \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                           \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                               \
  X(isSizingOptionDefaulted, SizingOption)                                                           \
  X(isReturnFanDefaulted, ReturnFan)                                                                 \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                   \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                       \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                   \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)                 \
  X(isReturnFanPartLoadPowerCoefficientsDefaulted, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_DEFAULTED(method, field)                                      \
  bool HVACTemplateSystemPackagedVAV_Impl::method() const {                   \
    return isEmpty(openstudio::HVACTemplate_System_PackagedVAVFields::field); \
  }

    OS_PACKAGEDVAV_DEFAULTED_MAP(OS_IMPL_DEFAULTED)

#undef OS_IMPL_DEFAULTED

#define OS_PACKAGEDVAV_AUTOSIZED_MAP(X)                                                        \
  X(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)                             \
  X(isSupplyFanMinimumFlowRateAutosized, SupplyFanMinimumFlowRate)                             \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)         \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(isHeatingCoilCapacityAutosized, HeatingCoilCapacity)                                       \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                           \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                           \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZED(method, field)                                                          \
  bool HVACTemplateSystemPackagedVAV_Impl::method() const {                                       \
    if (auto value = getString(openstudio::HVACTemplate_System_PackagedVAVFields::field, true)) { \
      return openstudio::istringEqual(*value, "autosize");                                        \
    }                                                                                             \
    return false;                                                                                 \
  }

    OS_PACKAGEDVAV_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_AUTOSIZED

#define OS_PACKAGEDVAV_STRING_SETTER_MAP(X)                                    \
  X(setSupplyFanPlacement, SupplyFanPlacement)                                 \
  X(setCoolingCoilType, CoolingCoilType)                                       \
  X(setHeatingCoilType, HeatingCoilType)                                       \
  X(setMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)             \
  X(setEconomizerType, EconomizerType)                                         \
  X(setEconomizerLockout, EconomizerLockout)                                   \
  X(setSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients) \
  X(setNightCycleControl, NightCycleControl)                                   \
  X(setHeatRecoveryType, HeatRecoveryType)                                     \
  X(setCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)             \
  X(setHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)             \
  X(setDehumidificationControlType, DehumidificationControlType)               \
  X(setHumidifierType, HumidifierType)                                         \
  X(setSizingOption, SizingOption)                                             \
  X(setReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_PACKAGEDVAV_DOUBLE_SETTER_MAP(X)                                                  \
  X(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(setSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                   \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                   \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                       \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                   \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                 \
  X(setCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                 \
  X(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(setCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                   \
  X(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                 \
  X(setHeatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                   \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)             \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(setEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(setEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(setEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)   \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                 \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                     \
  X(setDehumidificationSetpoint, DehumidificationSetpoint)                                   \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                     \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                           \
  X(setHumidifierSetpoint, HumidifierSetpoint)                                               \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                   \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                       \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                   \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_SET_STRING(method, field)                                              \
  bool HVACTemplateSystemPackagedVAV_Impl::method(const std::string& value) {          \
    return setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                              \
  bool HVACTemplateSystemPackagedVAV_Impl::method(double value) {                      \
    return setDouble(openstudio::HVACTemplate_System_PackagedVAVFields::field, value); \
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

#define OS_PACKAGEDVAV_RESET_MAP(X)                                                            \
  X(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(resetSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                                   \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                               \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                   \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                       \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                   \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                 \
  X(resetCoolingCoilType, CoolingCoilType)                                                     \
  X(resetCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)                                 \
  X(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(resetCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                   \
  X(resetHeatingCoilType, HeatingCoilType)                                                     \
  X(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)                                 \
  X(resetHeatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                   \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)             \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(resetMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)                           \
  X(resetEconomizerType, EconomizerType)                                                       \
  X(resetEconomizerLockout, EconomizerLockout)                                                 \
  X(resetEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(resetEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(resetEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)   \
  X(resetSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)               \
  X(resetNightCycleControl, NightCycleControl)                                                 \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                   \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                 \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                     \
  X(resetCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)                           \
  X(resetHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)                           \
  X(resetDehumidificationControlType, DehumidificationControlType)                             \
  X(resetDehumidificationSetpoint, DehumidificationSetpoint)                                   \
  X(resetHumidifierType, HumidifierType)                                                       \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                     \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                           \
  X(resetHumidifierSetpoint, HumidifierSetpoint)                                               \
  X(resetSizingOption, SizingOption)                                                           \
  X(resetReturnFan, ReturnFan)                                                                 \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                   \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                       \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                   \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)                 \
  X(resetReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#define OS_IMPL_RESET(method, field)                                                             \
  void HVACTemplateSystemPackagedVAV_Impl::method() {                                            \
    const bool result = setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, ""); \
    OS_ASSERT(result);                                                                           \
  }

    OS_PACKAGEDVAV_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_PACKAGEDVAV_AUTOSIZE_MAP(X)                                                      \
  X(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                             \
  X(autosizeSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)                             \
  X(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)         \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatingCoilCapacity, HeatingCoilCapacity)                                       \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                  \
  void HVACTemplateSystemPackagedVAV_Impl::method() {                                                    \
    const bool result = setString(openstudio::HVACTemplate_System_PackagedVAVFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                                   \
  }

    OS_PACKAGEDVAV_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                             \
  std::vector<std::string> HVACTemplateSystemPackagedVAV_Impl::method() const {                                   \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_PackagedVAV).get(), \
                          openstudio::HVACTemplate_System_PackagedVAVFields::field);                              \
  }

    OS_PACKAGEDVAV_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_PACKAGEDVAV_VALUES_MAP

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
