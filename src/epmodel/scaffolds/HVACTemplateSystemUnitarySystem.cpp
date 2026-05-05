/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemUnitarySystem.hpp"
#include "HVACTemplateSystemUnitarySystem_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_UnitarySystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateSystemUnitarySystem::HVACTemplateSystemUnitarySystem(const Model& model)
    : ModelObject(HVACTemplateSystemUnitarySystem::iddObjectType(), model) {}

  HVACTemplateSystemUnitarySystem::HVACTemplateSystemUnitarySystem(std::shared_ptr<detail::HVACTemplateSystemUnitarySystem_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateSystemUnitarySystem::iddObjectType() {
    return IddObjectType::HVACTemplate_System_UnitarySystem;
  }

#define OS_HVSYS_VALUES_MAP(X)                                                      \
  X(controlTypeValues, ControlType)                                                 \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                   \
  X(coolingCoilTypeValues, CoolingCoilType)                                         \
  X(heatingCoilTypeValues, HeatingCoilType)                                         \
  X(heatPumpDefrostStrategyValues, HeatPumpDefrostStrategy)                         \
  X(heatPumpDefrostControlValues, HeatPumpDefrostControl)                           \
  X(supplementalHeatingorReheatCoilTypeValues, SupplementalHeatingorReheatCoilType) \
  X(economizerTypeValues, EconomizerType)                                           \
  X(economizerLockoutValues, EconomizerLockout)                                     \
  X(heatRecoveryTypeValues, HeatRecoveryType)                                       \
  X(heatRecoveryHeatExchangerTypeValues, HeatRecoveryHeatExchangerType)             \
  X(heatRecoveryFrostControlTypeValues, HeatRecoveryFrostControlType)               \
  X(dehumidificationControlTypeValues, DehumidificationControlType)                 \
  X(humidifierTypeValues, HumidifierType)                                           \
  X(sizingOptionValues, SizingOption)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                                  \
  std::vector<std::string> HVACTemplateSystemUnitarySystem::method() {                                                                          \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_UnitarySystemFields::field); \
  }

  OS_HVSYS_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_HVSYS_REQUIRED_STRING_GETTERS(X) \
  X(controlType)                            \
  X(supplyFanPlacement)                     \
  X(coolingCoilType)                        \
  X(heatingCoilType)                        \
  X(heatPumpDefrostStrategy)                \
  X(heatPumpDefrostControl)                 \
  X(supplementalHeatingorReheatCoilType)    \
  X(economizerType)                         \
  X(economizerLockout)                      \
  X(heatRecoveryType)                       \
  X(heatRecoveryHeatExchangerType)          \
  X(heatRecoveryFrostControlType)           \
  X(dehumidificationControlType)            \
  X(humidifierType)                         \
  X(sizingOption)

#define OS_HVSYS_REQUIRED_INT_GETTERS(X) \
  X(numberofSpeedsforCooling)            \
  X(numberofSpeedsorStagesforHeating)

#define OS_HVSYS_REQUIRED_DOUBLE_GETTERS(X)                          \
  X(supplyFanTotalEfficiency)                                        \
  X(supplyFanDeltaPressure)                                          \
  X(supplyFanMotorEfficiency)                                        \
  X(supplyFanMotorinAirStreamFraction)                               \
  X(coolingDesignSupplyAirTemperature)                               \
  X(dXCoolingCoilGrossRatedCOP)                                      \
  X(heatingDesignSupplyAirTemperature)                               \
  X(gasHeatingCoilEfficiency)                                        \
  X(gasHeatingCoilParasiticElectricLoad)                             \
  X(heatPumpHeatingCoilGrossRatedCOP)                                \
  X(heatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(heatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(heatPumpDefrostTimePeriodFraction)                               \
  X(supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(supplementalGasHeatingorReheatCoilEfficiency)                    \
  X(supplementalGasHeatingorReheatCoilParasiticElectricLoad)         \
  X(sensibleHeatRecoveryEffectiveness)                               \
  X(latentHeatRecoveryEffectiveness)                                 \
  X(dehumidificationRelativeHumiditySetpoint)                        \
  X(humidifierRatedCapacity)                                         \
  X(humidifierRelativeHumiditySetpoint)                              \
  X(returnFanTotalEfficiency)                                        \
  X(returnFanDeltaPressure)                                          \
  X(returnFanMotorEfficiency)                                        \
  X(returnFanMotorinAirStreamFraction)

#define OS_HVSYS_OPTIONAL_DOUBLE_GETTERS(X)    \
  X(coolingSupplyAirFlowRate)                  \
  X(heatingSupplyAirFlowRate)                  \
  X(noLoadSupplyAirFlowRate)                   \
  X(dXCoolingCoilGrossRatedTotalCapacity)      \
  X(dXCoolingCoilGrossRatedSensibleHeatRatio)  \
  X(heatingCoilGrossRatedCapacity)             \
  X(supplementalHeatingorReheatCoilCapacity)   \
  X(maximumOutdoorAirFlowRate)                 \
  X(minimumOutdoorAirFlowRate)                 \
  X(economizerMaximumLimitDryBulbTemperature)  \
  X(economizerMaximumLimitEnthalpy)            \
  X(economizerMaximumLimitDewpointTemperature) \
  X(economizerMinimumLimitDryBulbTemperature)  \
  X(humidifierRatedElectricPower)

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                             \
  std::string HVACTemplateSystemUnitarySystem::method() const {               \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_INT_GETTER(method)                                \
  int HVACTemplateSystemUnitarySystem::method() const {                       \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                             \
  double HVACTemplateSystemUnitarySystem::method() const {                    \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                             \
  boost::optional<double> HVACTemplateSystemUnitarySystem::method() const {   \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

  OS_HVSYS_REQUIRED_STRING_GETTERS(OS_FORWARD_REQUIRED_STRING_GETTER)
  OS_HVSYS_REQUIRED_INT_GETTERS(OS_FORWARD_REQUIRED_INT_GETTER)
  OS_HVSYS_REQUIRED_DOUBLE_GETTERS(OS_FORWARD_REQUIRED_DOUBLE_GETTER)
  OS_HVSYS_OPTIONAL_DOUBLE_GETTERS(OS_FORWARD_OPTIONAL_DOUBLE_GETTER)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_REQUIRED_INT_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER

  bool HVACTemplateSystemUnitarySystem::returnFan() const {
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->returnFan();
  }

#define OS_HVSYS_DEFAULTED_METHODS_MAP(X)                                       \
  X(isControlTypeDefaulted)                                                     \
  X(isCoolingSupplyAirFlowRateDefaulted)                                        \
  X(isHeatingSupplyAirFlowRateDefaulted)                                        \
  X(isNoLoadSupplyAirFlowRateDefaulted)                                         \
  X(isSupplyFanPlacementDefaulted)                                              \
  X(isSupplyFanTotalEfficiencyDefaulted)                                        \
  X(isSupplyFanDeltaPressureDefaulted)                                          \
  X(isSupplyFanMotorEfficiencyDefaulted)                                        \
  X(isSupplyFanMotorinAirStreamFractionDefaulted)                               \
  X(isCoolingCoilTypeDefaulted)                                                 \
  X(isNumberofSpeedsforCoolingDefaulted)                                        \
  X(isCoolingDesignSupplyAirTemperatureDefaulted)                               \
  X(isDXCoolingCoilGrossRatedTotalCapacityDefaulted)                            \
  X(isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted)                        \
  X(isDXCoolingCoilGrossRatedCOPDefaulted)                                      \
  X(isHeatingCoilTypeDefaulted)                                                 \
  X(isNumberofSpeedsorStagesforHeatingDefaulted)                                \
  X(isHeatingDesignSupplyAirTemperatureDefaulted)                               \
  X(isHeatingCoilGrossRatedCapacityDefaulted)                                   \
  X(isGasHeatingCoilEfficiencyDefaulted)                                        \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted)                             \
  X(isHeatPumpHeatingCoilGrossRatedCOPDefaulted)                                \
  X(isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted)                 \
  X(isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted)                 \
  X(isHeatPumpDefrostStrategyDefaulted)                                         \
  X(isHeatPumpDefrostControlDefaulted)                                          \
  X(isHeatPumpDefrostTimePeriodFractionDefaulted)                               \
  X(isSupplementalHeatingorReheatCoilTypeDefaulted)                             \
  X(isSupplementalHeatingorReheatCoilCapacityDefaulted)                         \
  X(isSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperatureDefaulted) \
  X(isSupplementalGasHeatingorReheatCoilEfficiencyDefaulted)                    \
  X(isSupplementalGasHeatingorReheatCoilParasiticElectricLoadDefaulted)         \
  X(isMaximumOutdoorAirFlowRateDefaulted)                                       \
  X(isMinimumOutdoorAirFlowRateDefaulted)                                       \
  X(isEconomizerTypeDefaulted)                                                  \
  X(isEconomizerLockoutDefaulted)                                               \
  X(isEconomizerMaximumLimitDryBulbTemperatureDefaulted)                        \
  X(isEconomizerMaximumLimitEnthalpyDefaulted)                                  \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted)                       \
  X(isEconomizerMinimumLimitDryBulbTemperatureDefaulted)                        \
  X(isHeatRecoveryTypeDefaulted)                                                \
  X(isSensibleHeatRecoveryEffectivenessDefaulted)                               \
  X(isLatentHeatRecoveryEffectivenessDefaulted)                                 \
  X(isHeatRecoveryHeatExchangerTypeDefaulted)                                   \
  X(isHeatRecoveryFrostControlTypeDefaulted)                                    \
  X(isDehumidificationControlTypeDefaulted)                                     \
  X(isDehumidificationRelativeHumiditySetpointDefaulted)                        \
  X(isHumidifierTypeDefaulted)                                                  \
  X(isHumidifierRatedCapacityDefaulted)                                         \
  X(isHumidifierRatedElectricPowerDefaulted)                                    \
  X(isHumidifierRelativeHumiditySetpointDefaulted)                              \
  X(isSizingOptionDefaulted)                                                    \
  X(isReturnFanDefaulted)                                                       \
  X(isReturnFanTotalEfficiencyDefaulted)                                        \
  X(isReturnFanDeltaPressureDefaulted)                                          \
  X(isReturnFanMotorEfficiencyDefaulted)                                        \
  X(isReturnFanMotorinAirStreamFractionDefaulted)

#define OS_HVSYS_AUTOSIZED_METHODS_MAP(X)                \
  X(isCoolingSupplyAirFlowRateAutosized)                 \
  X(isHeatingSupplyAirFlowRateAutosized)                 \
  X(isNoLoadSupplyAirFlowRateAutosized)                  \
  X(isDXCoolingCoilGrossRatedTotalCapacityAutosized)     \
  X(isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized) \
  X(isHeatingCoilGrossRatedCapacityAutosized)            \
  X(isSupplementalHeatingorReheatCoilCapacityAutosized)  \
  X(isMaximumOutdoorAirFlowRateAutosized)                \
  X(isMinimumOutdoorAirFlowRateAutosized)                \
  X(isHumidifierRatedElectricPowerAutosized)

#define OS_FORWARD_BOOL(method)                                               \
  bool HVACTemplateSystemUnitarySystem::method() const {                      \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

  OS_HVSYS_DEFAULTED_METHODS_MAP(OS_FORWARD_BOOL)
  OS_HVSYS_AUTOSIZED_METHODS_MAP(OS_FORWARD_BOOL)

#undef OS_FORWARD_BOOL

#define OS_HVSYS_STRING_SETTERS(X)          \
  X(setControlType)                         \
  X(setSupplyFanPlacement)                  \
  X(setCoolingCoilType)                     \
  X(setHeatingCoilType)                     \
  X(setHeatPumpDefrostStrategy)             \
  X(setHeatPumpDefrostControl)              \
  X(setSupplementalHeatingorReheatCoilType) \
  X(setEconomizerType)                      \
  X(setEconomizerLockout)                   \
  X(setHeatRecoveryType)                    \
  X(setHeatRecoveryHeatExchangerType)       \
  X(setHeatRecoveryFrostControlType)        \
  X(setDehumidificationControlType)         \
  X(setHumidifierType)                      \
  X(setSizingOption)

#define OS_HVSYS_INT_SETTERS(X)  \
  X(setNumberofSpeedsforCooling) \
  X(setNumberofSpeedsorStagesforHeating)

#define OS_HVSYS_DOUBLE_SETTERS_CAN_FAIL(X)                             \
  X(setCoolingSupplyAirFlowRate)                                        \
  X(setHeatingSupplyAirFlowRate)                                        \
  X(setNoLoadSupplyAirFlowRate)                                         \
  X(setSupplyFanTotalEfficiency)                                        \
  X(setSupplyFanDeltaPressure)                                          \
  X(setSupplyFanMotorEfficiency)                                        \
  X(setSupplyFanMotorinAirStreamFraction)                               \
  X(setDXCoolingCoilGrossRatedSensibleHeatRatio)                        \
  X(setDXCoolingCoilGrossRatedCOP)                                      \
  X(setHeatingCoilGrossRatedCapacity)                                   \
  X(setGasHeatingCoilEfficiency)                                        \
  X(setGasHeatingCoilParasiticElectricLoad)                             \
  X(setHeatPumpHeatingCoilGrossRatedCOP)                                \
  X(setHeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(setHeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(setHeatPumpDefrostTimePeriodFraction)                               \
  X(setSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(setSupplementalGasHeatingorReheatCoilEfficiency)                    \
  X(setSupplementalGasHeatingorReheatCoilParasiticElectricLoad)         \
  X(setMaximumOutdoorAirFlowRate)                                       \
  X(setMinimumOutdoorAirFlowRate)                                       \
  X(setSensibleHeatRecoveryEffectiveness)                               \
  X(setLatentHeatRecoveryEffectiveness)                                 \
  X(setDehumidificationRelativeHumiditySetpoint)                        \
  X(setHumidifierRatedCapacity)                                         \
  X(setHumidifierRatedElectricPower)                                    \
  X(setHumidifierRelativeHumiditySetpoint)                              \
  X(setReturnFanTotalEfficiency)                                        \
  X(setReturnFanDeltaPressure)                                          \
  X(setReturnFanMotorEfficiency)                                        \
  X(setReturnFanMotorinAirStreamFraction)

#define OS_HVSYS_DOUBLE_SETTERS_NO_FAIL(X)        \
  X(setCoolingDesignSupplyAirTemperature)         \
  X(setDXCoolingCoilGrossRatedTotalCapacity)      \
  X(setHeatingDesignSupplyAirTemperature)         \
  X(setSupplementalHeatingorReheatCoilCapacity)   \
  X(setEconomizerMaximumLimitDryBulbTemperature)  \
  X(setEconomizerMaximumLimitEnthalpy)            \
  X(setEconomizerMaximumLimitDewpointTemperature) \
  X(setEconomizerMinimumLimitDryBulbTemperature)

#define OS_FORWARD_STRING_SETTER(method)                                           \
  bool HVACTemplateSystemUnitarySystem::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(value); \
  }

#define OS_FORWARD_INT_SETTER(method)                                              \
  bool HVACTemplateSystemUnitarySystem::method(int value) {                        \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(value); \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                           \
  bool HVACTemplateSystemUnitarySystem::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(value); \
  }

  OS_HVSYS_STRING_SETTERS(OS_FORWARD_STRING_SETTER)
  OS_HVSYS_INT_SETTERS(OS_FORWARD_INT_SETTER)
  OS_HVSYS_DOUBLE_SETTERS_CAN_FAIL(OS_FORWARD_DOUBLE_SETTER)
  OS_HVSYS_DOUBLE_SETTERS_NO_FAIL(OS_FORWARD_DOUBLE_SETTER)

#undef OS_FORWARD_DOUBLE_SETTER
#undef OS_FORWARD_INT_SETTER
#undef OS_FORWARD_STRING_SETTER

  bool HVACTemplateSystemUnitarySystem::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->setReturnFan(returnFan);
  }

#define OS_HVSYS_RESETS(X)                                                \
  X(resetControlType)                                                     \
  X(resetCoolingSupplyAirFlowRate)                                        \
  X(resetHeatingSupplyAirFlowRate)                                        \
  X(resetNoLoadSupplyAirFlowRate)                                         \
  X(resetSupplyFanPlacement)                                              \
  X(resetSupplyFanTotalEfficiency)                                        \
  X(resetSupplyFanDeltaPressure)                                          \
  X(resetSupplyFanMotorEfficiency)                                        \
  X(resetSupplyFanMotorinAirStreamFraction)                               \
  X(resetCoolingCoilType)                                                 \
  X(resetNumberofSpeedsforCooling)                                        \
  X(resetCoolingDesignSupplyAirTemperature)                               \
  X(resetDXCoolingCoilGrossRatedTotalCapacity)                            \
  X(resetDXCoolingCoilGrossRatedSensibleHeatRatio)                        \
  X(resetDXCoolingCoilGrossRatedCOP)                                      \
  X(resetHeatingCoilType)                                                 \
  X(resetNumberofSpeedsorStagesforHeating)                                \
  X(resetHeatingDesignSupplyAirTemperature)                               \
  X(resetHeatingCoilGrossRatedCapacity)                                   \
  X(resetGasHeatingCoilEfficiency)                                        \
  X(resetGasHeatingCoilParasiticElectricLoad)                             \
  X(resetHeatPumpHeatingCoilGrossRatedCOP)                                \
  X(resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature)                 \
  X(resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature)                 \
  X(resetHeatPumpDefrostStrategy)                                         \
  X(resetHeatPumpDefrostControl)                                          \
  X(resetHeatPumpDefrostTimePeriodFraction)                               \
  X(resetSupplementalHeatingorReheatCoilType)                             \
  X(resetSupplementalHeatingorReheatCoilCapacity)                         \
  X(resetSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(resetSupplementalGasHeatingorReheatCoilEfficiency)                    \
  X(resetSupplementalGasHeatingorReheatCoilParasiticElectricLoad)         \
  X(resetMaximumOutdoorAirFlowRate)                                       \
  X(resetMinimumOutdoorAirFlowRate)                                       \
  X(resetEconomizerType)                                                  \
  X(resetEconomizerLockout)                                               \
  X(resetEconomizerMaximumLimitDryBulbTemperature)                        \
  X(resetEconomizerMaximumLimitEnthalpy)                                  \
  X(resetEconomizerMaximumLimitDewpointTemperature)                       \
  X(resetEconomizerMinimumLimitDryBulbTemperature)                        \
  X(resetHeatRecoveryType)                                                \
  X(resetSensibleHeatRecoveryEffectiveness)                               \
  X(resetLatentHeatRecoveryEffectiveness)                                 \
  X(resetHeatRecoveryHeatExchangerType)                                   \
  X(resetHeatRecoveryFrostControlType)                                    \
  X(resetDehumidificationControlType)                                     \
  X(resetDehumidificationRelativeHumiditySetpoint)                        \
  X(resetHumidifierType)                                                  \
  X(resetHumidifierRatedCapacity)                                         \
  X(resetHumidifierRatedElectricPower)                                    \
  X(resetHumidifierRelativeHumiditySetpoint)                              \
  X(resetSizingOption)                                                    \
  X(resetReturnFan)                                                       \
  X(resetReturnFanTotalEfficiency)                                        \
  X(resetReturnFanDeltaPressure)                                          \
  X(resetReturnFanMotorEfficiency)                                        \
  X(resetReturnFanMotorinAirStreamFraction)

#define OS_HVSYS_AUTOSIZES(X)                         \
  X(autosizeCoolingSupplyAirFlowRate)                 \
  X(autosizeHeatingSupplyAirFlowRate)                 \
  X(autosizeNoLoadSupplyAirFlowRate)                  \
  X(autosizeDXCoolingCoilGrossRatedTotalCapacity)     \
  X(autosizeDXCoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatingCoilGrossRatedCapacity)            \
  X(autosizeSupplementalHeatingorReheatCoilCapacity)  \
  X(autosizeMaximumOutdoorAirFlowRate)                \
  X(autosizeMinimumOutdoorAirFlowRate)                \
  X(autosizeHumidifierRatedElectricPower)

#define OS_FORWARD_VOID(method)                                        \
  void HVACTemplateSystemUnitarySystem::method() {                     \
    getImpl<detail::HVACTemplateSystemUnitarySystem_Impl>()->method(); \
  }

  OS_HVSYS_RESETS(OS_FORWARD_VOID)
  OS_HVSYS_AUTOSIZES(OS_FORWARD_VOID)

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

#define OS_HVSYS_REQUIRED_STRING_MAP(X)                                       \
  X(controlType, ControlType)                                                 \
  X(supplyFanPlacement, SupplyFanPlacement)                                   \
  X(coolingCoilType, CoolingCoilType)                                         \
  X(heatingCoilType, HeatingCoilType)                                         \
  X(heatPumpDefrostStrategy, HeatPumpDefrostStrategy)                         \
  X(heatPumpDefrostControl, HeatPumpDefrostControl)                           \
  X(supplementalHeatingorReheatCoilType, SupplementalHeatingorReheatCoilType) \
  X(economizerType, EconomizerType)                                           \
  X(economizerLockout, EconomizerLockout)                                     \
  X(heatRecoveryType, HeatRecoveryType)                                       \
  X(heatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)             \
  X(heatRecoveryFrostControlType, HeatRecoveryFrostControlType)               \
  X(dehumidificationControlType, DehumidificationControlType)                 \
  X(humidifierType, HumidifierType)                                           \
  X(sizingOption, SizingOption)

#define OS_HVSYS_REQUIRED_INT_MAP(X)                    \
  X(numberofSpeedsforCooling, NumberofSpeedsforCooling) \
  X(numberofSpeedsorStagesforHeating, NumberofSpeedsorStagesforHeating)

#define OS_HVSYS_REQUIRED_DOUBLE_MAP(X)                                                                                               \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                               \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                   \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                               \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(coolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                                             \
  X(dXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)                                                                           \
  X(heatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                                             \
  X(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                               \
  X(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(heatPumpHeatingCoilGrossRatedCOP, HeatPumpHeatingCoilGrossRatedCOP)                                                               \
  X(heatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                                 \
  X(heatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                                 \
  X(heatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                                             \
  X(supplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(supplementalGasHeatingorReheatCoilEfficiency, SupplementalGasHeatingorReheatCoilEfficiency)                                       \
  X(supplementalGasHeatingorReheatCoilParasiticElectricLoad, SupplementalGasHeatingorReheatCoilParasiticElectricLoad)                 \
  X(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                             \
  X(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                 \
  X(dehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                               \
  X(humidifierRatedCapacity, HumidifierRatedCapacity)                                                                                 \
  X(humidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                           \
  X(returnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                               \
  X(returnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                   \
  X(returnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                               \
  X(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_HVSYS_OPTIONAL_DOUBLE_MAP(X)                                                   \
  X(coolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                   \
  X(heatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                   \
  X(noLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                     \
  X(dXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)           \
  X(dXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)   \
  X(heatingCoilGrossRatedCapacity, HeatingCoilGrossRatedCapacity)                         \
  X(supplementalHeatingorReheatCoilCapacity, SupplementalHeatingorReheatCoilCapacity)     \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(economizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(economizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(economizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)   \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                      \
  std::string HVACTemplateSystemUnitarySystem_Impl::method() const {                                \
    const auto value = getString(openstudio::HVACTemplate_System_UnitarySystemFields::field, true); \
    OS_ASSERT(value);                                                                               \
    return *value;                                                                                  \
  }

#define OS_IMPL_REQUIRED_INT(method, field)                                                      \
  int HVACTemplateSystemUnitarySystem_Impl::method() const {                                     \
    const auto value = getInt(openstudio::HVACTemplate_System_UnitarySystemFields::field, true); \
    OS_ASSERT(value);                                                                            \
    return *value;                                                                               \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                      \
  double HVACTemplateSystemUnitarySystem_Impl::method() const {                                     \
    const auto value = getDouble(openstudio::HVACTemplate_System_UnitarySystemFields::field, true); \
    OS_ASSERT(value);                                                                               \
    return *value;                                                                                  \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                          \
  boost::optional<double> HVACTemplateSystemUnitarySystem_Impl::method() const {        \
    return getDouble(openstudio::HVACTemplate_System_UnitarySystemFields::field, true); \
  }

    OS_HVSYS_REQUIRED_STRING_MAP(OS_IMPL_REQUIRED_STRING)
    OS_HVSYS_REQUIRED_INT_MAP(OS_IMPL_REQUIRED_INT)
    OS_HVSYS_REQUIRED_DOUBLE_MAP(OS_IMPL_REQUIRED_DOUBLE)
    OS_HVSYS_OPTIONAL_DOUBLE_MAP(OS_IMPL_OPTIONAL_DOUBLE)

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_INT
#undef OS_IMPL_REQUIRED_STRING

    bool HVACTemplateSystemUnitarySystem_Impl::returnFan() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitarySystemFields::ReturnFan);
    }

#define OS_HVSYS_DEFAULTED_MAP(X)                                                                                                                \
  X(isControlTypeDefaulted, ControlType)                                                                                                         \
  X(isCoolingSupplyAirFlowRateDefaulted, CoolingSupplyAirFlowRate)                                                                               \
  X(isHeatingSupplyAirFlowRateDefaulted, HeatingSupplyAirFlowRate)                                                                               \
  X(isNoLoadSupplyAirFlowRateDefaulted, NoLoadSupplyAirFlowRate)                                                                                 \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                                                                           \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                                                               \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                                                                   \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                                                               \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                                                             \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                                                                 \
  X(isNumberofSpeedsforCoolingDefaulted, NumberofSpeedsforCooling)                                                                               \
  X(isCoolingDesignSupplyAirTemperatureDefaulted, CoolingDesignSupplyAirTemperature)                                                             \
  X(isDXCoolingCoilGrossRatedTotalCapacityDefaulted, DXCoolingCoilGrossRatedTotalCapacity)                                                       \
  X(isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted, DXCoolingCoilGrossRatedSensibleHeatRatio)                                               \
  X(isDXCoolingCoilGrossRatedCOPDefaulted, DXCoolingCoilGrossRatedCOP)                                                                           \
  X(isHeatingCoilTypeDefaulted, HeatingCoilType)                                                                                                 \
  X(isNumberofSpeedsorStagesforHeatingDefaulted, NumberofSpeedsorStagesforHeating)                                                               \
  X(isHeatingDesignSupplyAirTemperatureDefaulted, HeatingDesignSupplyAirTemperature)                                                             \
  X(isHeatingCoilGrossRatedCapacityDefaulted, HeatingCoilGrossRatedCapacity)                                                                     \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                                                               \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(isHeatPumpHeatingCoilGrossRatedCOPDefaulted, HeatPumpHeatingCoilGrossRatedCOP)                                                               \
  X(isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                                 \
  X(isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                                 \
  X(isHeatPumpDefrostStrategyDefaulted, HeatPumpDefrostStrategy)                                                                                 \
  X(isHeatPumpDefrostControlDefaulted, HeatPumpDefrostControl)                                                                                   \
  X(isHeatPumpDefrostTimePeriodFractionDefaulted, HeatPumpDefrostTimePeriodFraction)                                                             \
  X(isSupplementalHeatingorReheatCoilTypeDefaulted, SupplementalHeatingorReheatCoilType)                                                         \
  X(isSupplementalHeatingorReheatCoilCapacityDefaulted, SupplementalHeatingorReheatCoilCapacity)                                                 \
  X(isSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperatureDefaulted, SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(isSupplementalGasHeatingorReheatCoilEfficiencyDefaulted, SupplementalGasHeatingorReheatCoilEfficiency)                                       \
  X(isSupplementalGasHeatingorReheatCoilParasiticElectricLoadDefaulted, SupplementalGasHeatingorReheatCoilParasiticElectricLoad)                 \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                                                             \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                                                             \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                                                                   \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                                                             \
  X(isEconomizerMaximumLimitDryBulbTemperatureDefaulted, EconomizerMaximumLimitDryBulbTemperature)                                               \
  X(isEconomizerMaximumLimitEnthalpyDefaulted, EconomizerMaximumLimitEnthalpy)                                                                   \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)                                             \
  X(isEconomizerMinimumLimitDryBulbTemperatureDefaulted, EconomizerMinimumLimitDryBulbTemperature)                                               \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                                                               \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                                                             \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                                                                 \
  X(isHeatRecoveryHeatExchangerTypeDefaulted, HeatRecoveryHeatExchangerType)                                                                     \
  X(isHeatRecoveryFrostControlTypeDefaulted, HeatRecoveryFrostControlType)                                                                       \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                                                                         \
  X(isDehumidificationRelativeHumiditySetpointDefaulted, DehumidificationRelativeHumiditySetpoint)                                               \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                                                                   \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                                                                 \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                                                                       \
  X(isHumidifierRelativeHumiditySetpointDefaulted, HumidifierRelativeHumiditySetpoint)                                                           \
  X(isSizingOptionDefaulted, SizingOption)                                                                                                       \
  X(isReturnFanDefaulted, ReturnFan)                                                                                                             \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                                                               \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                                                                   \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                                                               \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)

#define OS_HVSYS_AUTOSIZED_MAP(X)                                                                  \
  X(isCoolingSupplyAirFlowRateAutosized, CoolingSupplyAirFlowRate)                                 \
  X(isHeatingSupplyAirFlowRateAutosized, HeatingSupplyAirFlowRate)                                 \
  X(isNoLoadSupplyAirFlowRateAutosized, NoLoadSupplyAirFlowRate)                                   \
  X(isDXCoolingCoilGrossRatedTotalCapacityAutosized, DXCoolingCoilGrossRatedTotalCapacity)         \
  X(isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized, DXCoolingCoilGrossRatedSensibleHeatRatio) \
  X(isHeatingCoilGrossRatedCapacityAutosized, HeatingCoilGrossRatedCapacity)                       \
  X(isSupplementalHeatingorReheatCoilCapacityAutosized, SupplementalHeatingorReheatCoilCapacity)   \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                               \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                               \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_DEFAULTED(method, field)                                        \
  bool HVACTemplateSystemUnitarySystem_Impl::method() const {                   \
    return isEmpty(openstudio::HVACTemplate_System_UnitarySystemFields::field); \
  }

#define OS_IMPL_AUTOSIZED(method, field)                                                            \
  bool HVACTemplateSystemUnitarySystem_Impl::method() const {                                       \
    const auto value = getString(openstudio::HVACTemplate_System_UnitarySystemFields::field, true); \
    if (value) {                                                                                    \
      return openstudio::istringEqual(*value, "autosize");                                          \
    }                                                                                               \
    return false;                                                                                   \
  }

    OS_HVSYS_DEFAULTED_MAP(OS_IMPL_DEFAULTED)
    OS_HVSYS_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_AUTOSIZED
#undef OS_IMPL_DEFAULTED

#define OS_HVSYS_STRING_SETTER_MAP(X)                                            \
  X(setControlType, ControlType)                                                 \
  X(setSupplyFanPlacement, SupplyFanPlacement)                                   \
  X(setCoolingCoilType, CoolingCoilType)                                         \
  X(setHeatingCoilType, HeatingCoilType)                                         \
  X(setHeatPumpDefrostStrategy, HeatPumpDefrostStrategy)                         \
  X(setHeatPumpDefrostControl, HeatPumpDefrostControl)                           \
  X(setSupplementalHeatingorReheatCoilType, SupplementalHeatingorReheatCoilType) \
  X(setEconomizerType, EconomizerType)                                           \
  X(setEconomizerLockout, EconomizerLockout)                                     \
  X(setHeatRecoveryType, HeatRecoveryType)                                       \
  X(setHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)             \
  X(setHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)               \
  X(setDehumidificationControlType, DehumidificationControlType)                 \
  X(setHumidifierType, HumidifierType)                                           \
  X(setSizingOption, SizingOption)

#define OS_HVSYS_INT_SETTER_MAP(X)                         \
  X(setNumberofSpeedsforCooling, NumberofSpeedsforCooling) \
  X(setNumberofSpeedsorStagesforHeating, NumberofSpeedsorStagesforHeating)

#define OS_HVSYS_DOUBLE_SETTER_CAN_FAIL_MAP(X)                                                                                           \
  X(setCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                                                               \
  X(setHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                                                               \
  X(setNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                                                                 \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                               \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                   \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                               \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(setDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)                                               \
  X(setDXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)                                                                           \
  X(setHeatingCoilGrossRatedCapacity, HeatingCoilGrossRatedCapacity)                                                                     \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                               \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(setHeatPumpHeatingCoilGrossRatedCOP, HeatPumpHeatingCoilGrossRatedCOP)                                                               \
  X(setHeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                                 \
  X(setHeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                                 \
  X(setHeatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                                             \
  X(setSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(setSupplementalGasHeatingorReheatCoilEfficiency, SupplementalGasHeatingorReheatCoilEfficiency)                                       \
  X(setSupplementalGasHeatingorReheatCoilParasiticElectricLoad, SupplementalGasHeatingorReheatCoilParasiticElectricLoad)                 \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                             \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                             \
  X(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                             \
  X(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                 \
  X(setDehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                               \
  X(setHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                 \
  X(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                       \
  X(setHumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                           \
  X(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                               \
  X(setReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                   \
  X(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                               \
  X(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_HVSYS_DOUBLE_SETTER_NO_FAIL_MAP(X)                                                \
  X(setCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                 \
  X(setDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)           \
  X(setHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                 \
  X(setSupplementalHeatingorReheatCoilCapacity, SupplementalHeatingorReheatCoilCapacity)     \
  X(setEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)   \
  X(setEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                       \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(setEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)

#define OS_IMPL_SET_STRING(method, field)                                                \
  bool HVACTemplateSystemUnitarySystem_Impl::method(const std::string& value) {          \
    return setString(openstudio::HVACTemplate_System_UnitarySystemFields::field, value); \
  }

#define OS_IMPL_SET_INT(method, field)                                                \
  bool HVACTemplateSystemUnitarySystem_Impl::method(int value) {                      \
    return setInt(openstudio::HVACTemplate_System_UnitarySystemFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE_CANFAIL(method, field)                                        \
  bool HVACTemplateSystemUnitarySystem_Impl::method(double value) {                      \
    return setDouble(openstudio::HVACTemplate_System_UnitarySystemFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE_NOFAIL(method, field)                                                      \
  bool HVACTemplateSystemUnitarySystem_Impl::method(double value) {                                   \
    const bool result = setDouble(openstudio::HVACTemplate_System_UnitarySystemFields::field, value); \
    OS_ASSERT(result);                                                                                \
    return result;                                                                                    \
  }

    OS_HVSYS_STRING_SETTER_MAP(OS_IMPL_SET_STRING)
    OS_HVSYS_INT_SETTER_MAP(OS_IMPL_SET_INT)
    OS_HVSYS_DOUBLE_SETTER_CAN_FAIL_MAP(OS_IMPL_SET_DOUBLE_CANFAIL)
    OS_HVSYS_DOUBLE_SETTER_NO_FAIL_MAP(OS_IMPL_SET_DOUBLE_NOFAIL)

#undef OS_IMPL_SET_DOUBLE_NOFAIL
#undef OS_IMPL_SET_DOUBLE_CANFAIL
#undef OS_IMPL_SET_INT
#undef OS_IMPL_SET_STRING

    bool HVACTemplateSystemUnitarySystem_Impl::setReturnFan(bool returnFan) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_UnitarySystemFields::ReturnFan, returnFan);
      OS_ASSERT(result);
      return result;
    }

#define OS_HVSYS_RESET_MAP(X)                                                                                                              \
  X(resetControlType, ControlType)                                                                                                         \
  X(resetCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                                                               \
  X(resetHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                                                               \
  X(resetNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                                                                 \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                                                                           \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                                                               \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                                                                   \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                                                               \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                                                             \
  X(resetCoolingCoilType, CoolingCoilType)                                                                                                 \
  X(resetNumberofSpeedsforCooling, NumberofSpeedsforCooling)                                                                               \
  X(resetCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                                                             \
  X(resetDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)                                                       \
  X(resetDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)                                               \
  X(resetDXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)                                                                           \
  X(resetHeatingCoilType, HeatingCoilType)                                                                                                 \
  X(resetNumberofSpeedsorStagesforHeating, NumberofSpeedsorStagesforHeating)                                                               \
  X(resetHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                                                             \
  X(resetHeatingCoilGrossRatedCapacity, HeatingCoilGrossRatedCapacity)                                                                     \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                                                               \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)                                                         \
  X(resetHeatPumpHeatingCoilGrossRatedCOP, HeatPumpHeatingCoilGrossRatedCOP)                                                               \
  X(resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpHeatingMinimumOutdoorDryBulbTemperature)                                 \
  X(resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature)                                 \
  X(resetHeatPumpDefrostStrategy, HeatPumpDefrostStrategy)                                                                                 \
  X(resetHeatPumpDefrostControl, HeatPumpDefrostControl)                                                                                   \
  X(resetHeatPumpDefrostTimePeriodFraction, HeatPumpDefrostTimePeriodFraction)                                                             \
  X(resetSupplementalHeatingorReheatCoilType, SupplementalHeatingorReheatCoilType)                                                         \
  X(resetSupplementalHeatingorReheatCoilCapacity, SupplementalHeatingorReheatCoilCapacity)                                                 \
  X(resetSupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature, SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature) \
  X(resetSupplementalGasHeatingorReheatCoilEfficiency, SupplementalGasHeatingorReheatCoilEfficiency)                                       \
  X(resetSupplementalGasHeatingorReheatCoilParasiticElectricLoad, SupplementalGasHeatingorReheatCoilParasiticElectricLoad)                 \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                                                             \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                                                             \
  X(resetEconomizerType, EconomizerType)                                                                                                   \
  X(resetEconomizerLockout, EconomizerLockout)                                                                                             \
  X(resetEconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitDryBulbTemperature)                                               \
  X(resetEconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitEnthalpy)                                                                   \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)                                             \
  X(resetEconomizerMinimumLimitDryBulbTemperature, EconomizerMinimumLimitDryBulbTemperature)                                               \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                                                               \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                                                             \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                                                                 \
  X(resetHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)                                                                     \
  X(resetHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)                                                                       \
  X(resetDehumidificationControlType, DehumidificationControlType)                                                                         \
  X(resetDehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpoint)                                               \
  X(resetHumidifierType, HumidifierType)                                                                                                   \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                                                                 \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                                                                       \
  X(resetHumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpoint)                                                           \
  X(resetSizingOption, SizingOption)                                                                                                       \
  X(resetReturnFan, ReturnFan)                                                                                                             \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                                                               \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                                                                   \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                                                               \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_RESET(method, field)                                                               \
  void HVACTemplateSystemUnitarySystem_Impl::method() {                                            \
    const bool result = setString(openstudio::HVACTemplate_System_UnitarySystemFields::field, ""); \
    OS_ASSERT(result);                                                                             \
  }

    OS_HVSYS_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_HVSYS_AUTOSIZE_MAP(X)                                                                \
  X(autosizeCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)                                 \
  X(autosizeHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)                                 \
  X(autosizeNoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRate)                                   \
  X(autosizeDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)         \
  X(autosizeDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatingCoilGrossRatedCapacity, HeatingCoilGrossRatedCapacity)                       \
  X(autosizeSupplementalHeatingorReheatCoilCapacity, SupplementalHeatingorReheatCoilCapacity)   \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                               \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                               \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                                    \
  void HVACTemplateSystemUnitarySystem_Impl::method() {                                                    \
    const bool result = setString(openstudio::HVACTemplate_System_UnitarySystemFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                                     \
  }

    OS_HVSYS_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                               \
  std::vector<std::string> HVACTemplateSystemUnitarySystem_Impl::method() const {                                   \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_UnitarySystem).get(), \
                          openstudio::HVACTemplate_System_UnitarySystemFields::field);                              \
  }

    OS_HVSYS_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_HVSYS_VALUES_MAP

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
