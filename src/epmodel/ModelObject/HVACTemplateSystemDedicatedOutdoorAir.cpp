/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemDedicatedOutdoorAir.hpp"
#include "HVACTemplateSystemDedicatedOutdoorAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_DedicatedOutdoorAir_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

HVACTemplateSystemDedicatedOutdoorAir::HVACTemplateSystemDedicatedOutdoorAir(const Model& model)
  : ModelObject(HVACTemplateSystemDedicatedOutdoorAir::iddObjectType(), model) {}

HVACTemplateSystemDedicatedOutdoorAir::HVACTemplateSystemDedicatedOutdoorAir(
  std::shared_ptr<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType HVACTemplateSystemDedicatedOutdoorAir::iddObjectType() {
  return IddObjectType::HVACTemplate_System_DedicatedOutdoorAir;
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::airOutletTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::AirOutletType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::supplyFanPlacementValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanPlacement);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::coolingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::coolingCoilSetpointControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilSetpointControlType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::heatingCoilTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::heatingCoilSetpointControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilSetpointControlType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::heatRecoveryTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::heatRecoveryHeatExchangerTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryHeatExchangerType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::heatRecoveryFrostControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryFrostControlType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::dehumidificationControlTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::DehumidificationControlType);
}

std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir::humidifierTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierType);
}

#define OS_FORWARD_STRING_GETTER(method)                                                                                                   \
  std::string HVACTemplateSystemDedicatedOutdoorAir::method() const {                                                                      \
    return getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method();                                                       \
  }

#define OS_FORWARD_DOUBLE_GETTER(method)                                                                                                   \
  double HVACTemplateSystemDedicatedOutdoorAir::method() const {                                                                           \
    return getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method();                                                       \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                                                                                          \
  boost::optional<double> HVACTemplateSystemDedicatedOutdoorAir::method() const {                                                          \
    return getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method();                                                       \
  }

OS_FORWARD_STRING_GETTER(airOutletType)
OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanFlowRate)
OS_FORWARD_DOUBLE_GETTER(supplyFanTotalEfficiency)
OS_FORWARD_DOUBLE_GETTER(supplyFanDeltaPressure)
OS_FORWARD_DOUBLE_GETTER(supplyFanMotorEfficiency)
OS_FORWARD_DOUBLE_GETTER(supplyFanMotorinAirStreamFraction)
OS_FORWARD_STRING_GETTER(supplyFanPlacement)
OS_FORWARD_STRING_GETTER(coolingCoilType)
OS_FORWARD_STRING_GETTER(coolingCoilSetpointControlType)
OS_FORWARD_DOUBLE_GETTER(coolingCoilDesignSetpoint)
OS_FORWARD_DOUBLE_GETTER(coolingCoilSetpointatOutdoorDryBulbLow)
OS_FORWARD_DOUBLE_GETTER(coolingCoilResetOutdoorDryBulbLow)
OS_FORWARD_DOUBLE_GETTER(coolingCoilSetpointatOutdoorDryBulbHigh)
OS_FORWARD_DOUBLE_GETTER(coolingCoilResetOutdoorDryBulbHigh)
OS_FORWARD_OPTIONAL_DOUBLE_GETTER(dXCoolingCoilGrossRatedTotalCapacity)
OS_FORWARD_OPTIONAL_DOUBLE_GETTER(dXCoolingCoilGrossRatedSensibleHeatRatio)
OS_FORWARD_DOUBLE_GETTER(dXCoolingCoilGrossRatedCOP)
OS_FORWARD_STRING_GETTER(heatingCoilType)
OS_FORWARD_STRING_GETTER(heatingCoilSetpointControlType)
OS_FORWARD_DOUBLE_GETTER(heatingCoilDesignSetpoint)
OS_FORWARD_DOUBLE_GETTER(heatingCoilSetpointatOutdoorDryBulbLow)
OS_FORWARD_DOUBLE_GETTER(heatingCoilResetOutdoorDryBulbLow)
OS_FORWARD_DOUBLE_GETTER(heatingCoilSetpointatOutdoorDryBulbHigh)
OS_FORWARD_DOUBLE_GETTER(heatingCoilResetOutdoorDryBulbHigh)
OS_FORWARD_DOUBLE_GETTER(gasHeatingCoilEfficiency)
OS_FORWARD_DOUBLE_GETTER(gasHeatingCoilParasiticElectricLoad)
OS_FORWARD_STRING_GETTER(heatRecoveryType)
OS_FORWARD_DOUBLE_GETTER(heatRecoverySensibleEffectiveness)
OS_FORWARD_DOUBLE_GETTER(heatRecoveryLatentEffectiveness)
OS_FORWARD_STRING_GETTER(heatRecoveryHeatExchangerType)
OS_FORWARD_STRING_GETTER(heatRecoveryFrostControlType)
OS_FORWARD_STRING_GETTER(dehumidificationControlType)
OS_FORWARD_DOUBLE_GETTER(dehumidificationSetpoint)
OS_FORWARD_STRING_GETTER(humidifierType)
OS_FORWARD_DOUBLE_GETTER(humidifierRatedCapacity)
OS_FORWARD_OPTIONAL_DOUBLE_GETTER(humidifierRatedElectricPower)
OS_FORWARD_DOUBLE_GETTER(humidifierConstantSetpoint)

#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_DOUBLE_GETTER
#undef OS_FORWARD_STRING_GETTER

#define OS_FORWARD_BOOL(method, field)                                                                                                     \
  bool HVACTemplateSystemDedicatedOutdoorAir::method() const {                                                                            \
    return getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method();                                                       \
  }

OS_FORWARD_BOOL(isAirOutletTypeDefaulted, isAirOutletTypeDefaulted)
OS_FORWARD_BOOL(isSupplyFanFlowRateDefaulted, isSupplyFanFlowRateDefaulted)
OS_FORWARD_BOOL(isSupplyFanTotalEfficiencyDefaulted, isSupplyFanTotalEfficiencyDefaulted)
OS_FORWARD_BOOL(isSupplyFanDeltaPressureDefaulted, isSupplyFanDeltaPressureDefaulted)
OS_FORWARD_BOOL(isSupplyFanMotorEfficiencyDefaulted, isSupplyFanMotorEfficiencyDefaulted)
OS_FORWARD_BOOL(isSupplyFanMotorinAirStreamFractionDefaulted, isSupplyFanMotorinAirStreamFractionDefaulted)
OS_FORWARD_BOOL(isSupplyFanPlacementDefaulted, isSupplyFanPlacementDefaulted)
OS_FORWARD_BOOL(isCoolingCoilTypeDefaulted, isCoolingCoilTypeDefaulted)
OS_FORWARD_BOOL(isCoolingCoilSetpointControlTypeDefaulted, isCoolingCoilSetpointControlTypeDefaulted)
OS_FORWARD_BOOL(isCoolingCoilDesignSetpointDefaulted, isCoolingCoilDesignSetpointDefaulted)
OS_FORWARD_BOOL(isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted, isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted)
OS_FORWARD_BOOL(isCoolingCoilResetOutdoorDryBulbLowDefaulted, isCoolingCoilResetOutdoorDryBulbLowDefaulted)
OS_FORWARD_BOOL(isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted, isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted)
OS_FORWARD_BOOL(isCoolingCoilResetOutdoorDryBulbHighDefaulted, isCoolingCoilResetOutdoorDryBulbHighDefaulted)
OS_FORWARD_BOOL(isDXCoolingCoilGrossRatedTotalCapacityDefaulted, isDXCoolingCoilGrossRatedTotalCapacityDefaulted)
OS_FORWARD_BOOL(isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted, isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted)
OS_FORWARD_BOOL(isDXCoolingCoilGrossRatedCOPDefaulted, isDXCoolingCoilGrossRatedCOPDefaulted)
OS_FORWARD_BOOL(isHeatingCoilTypeDefaulted, isHeatingCoilTypeDefaulted)
OS_FORWARD_BOOL(isHeatingCoilSetpointControlTypeDefaulted, isHeatingCoilSetpointControlTypeDefaulted)
OS_FORWARD_BOOL(isHeatingCoilDesignSetpointDefaulted, isHeatingCoilDesignSetpointDefaulted)
OS_FORWARD_BOOL(isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted, isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted)
OS_FORWARD_BOOL(isHeatingCoilResetOutdoorDryBulbLowDefaulted, isHeatingCoilResetOutdoorDryBulbLowDefaulted)
OS_FORWARD_BOOL(isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted, isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted)
OS_FORWARD_BOOL(isHeatingCoilResetOutdoorDryBulbHighDefaulted, isHeatingCoilResetOutdoorDryBulbHighDefaulted)
OS_FORWARD_BOOL(isGasHeatingCoilEfficiencyDefaulted, isGasHeatingCoilEfficiencyDefaulted)
OS_FORWARD_BOOL(isGasHeatingCoilParasiticElectricLoadDefaulted, isGasHeatingCoilParasiticElectricLoadDefaulted)
OS_FORWARD_BOOL(isHeatRecoveryTypeDefaulted, isHeatRecoveryTypeDefaulted)
OS_FORWARD_BOOL(isHeatRecoverySensibleEffectivenessDefaulted, isHeatRecoverySensibleEffectivenessDefaulted)
OS_FORWARD_BOOL(isHeatRecoveryLatentEffectivenessDefaulted, isHeatRecoveryLatentEffectivenessDefaulted)
OS_FORWARD_BOOL(isHeatRecoveryHeatExchangerTypeDefaulted, isHeatRecoveryHeatExchangerTypeDefaulted)
OS_FORWARD_BOOL(isHeatRecoveryFrostControlTypeDefaulted, isHeatRecoveryFrostControlTypeDefaulted)
OS_FORWARD_BOOL(isDehumidificationControlTypeDefaulted, isDehumidificationControlTypeDefaulted)
OS_FORWARD_BOOL(isDehumidificationSetpointDefaulted, isDehumidificationSetpointDefaulted)
OS_FORWARD_BOOL(isHumidifierTypeDefaulted, isHumidifierTypeDefaulted)
OS_FORWARD_BOOL(isHumidifierRatedCapacityDefaulted, isHumidifierRatedCapacityDefaulted)
OS_FORWARD_BOOL(isHumidifierRatedElectricPowerDefaulted, isHumidifierRatedElectricPowerDefaulted)
OS_FORWARD_BOOL(isHumidifierConstantSetpointDefaulted, isHumidifierConstantSetpointDefaulted)
OS_FORWARD_BOOL(isSupplyFanFlowRateAutosized, isSupplyFanFlowRateAutosized)
OS_FORWARD_BOOL(isDXCoolingCoilGrossRatedTotalCapacityAutosized, isDXCoolingCoilGrossRatedTotalCapacityAutosized)
OS_FORWARD_BOOL(isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized, isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized)
OS_FORWARD_BOOL(isHumidifierRatedElectricPowerAutosized, isHumidifierRatedElectricPowerAutosized)

#undef OS_FORWARD_BOOL

#define OS_FORWARD_SETTER(method, type)                                                                                                    \
  bool HVACTemplateSystemDedicatedOutdoorAir::method(type value) {                                                                         \
    return getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method(value);                                                   \
  }

OS_FORWARD_SETTER(setAirOutletType, const std::string&)
OS_FORWARD_SETTER(setSupplyFanFlowRate, double)
OS_FORWARD_SETTER(setSupplyFanTotalEfficiency, double)
OS_FORWARD_SETTER(setSupplyFanDeltaPressure, double)
OS_FORWARD_SETTER(setSupplyFanMotorEfficiency, double)
OS_FORWARD_SETTER(setSupplyFanMotorinAirStreamFraction, double)
OS_FORWARD_SETTER(setSupplyFanPlacement, const std::string&)
OS_FORWARD_SETTER(setCoolingCoilType, const std::string&)
OS_FORWARD_SETTER(setCoolingCoilSetpointControlType, const std::string&)
OS_FORWARD_SETTER(setCoolingCoilDesignSetpoint, double)
OS_FORWARD_SETTER(setCoolingCoilSetpointatOutdoorDryBulbLow, double)
OS_FORWARD_SETTER(setCoolingCoilResetOutdoorDryBulbLow, double)
OS_FORWARD_SETTER(setCoolingCoilSetpointatOutdoorDryBulbHigh, double)
OS_FORWARD_SETTER(setCoolingCoilResetOutdoorDryBulbHigh, double)
OS_FORWARD_SETTER(setDXCoolingCoilGrossRatedTotalCapacity, double)
OS_FORWARD_SETTER(setDXCoolingCoilGrossRatedSensibleHeatRatio, double)
OS_FORWARD_SETTER(setDXCoolingCoilGrossRatedCOP, double)
OS_FORWARD_SETTER(setHeatingCoilType, const std::string&)
OS_FORWARD_SETTER(setHeatingCoilSetpointControlType, const std::string&)
OS_FORWARD_SETTER(setHeatingCoilDesignSetpoint, double)
OS_FORWARD_SETTER(setHeatingCoilSetpointatOutdoorDryBulbLow, double)
OS_FORWARD_SETTER(setHeatingCoilResetOutdoorDryBulbLow, double)
OS_FORWARD_SETTER(setHeatingCoilSetpointatOutdoorDryBulbHigh, double)
OS_FORWARD_SETTER(setHeatingCoilResetOutdoorDryBulbHigh, double)
OS_FORWARD_SETTER(setGasHeatingCoilEfficiency, double)
OS_FORWARD_SETTER(setGasHeatingCoilParasiticElectricLoad, double)
OS_FORWARD_SETTER(setHeatRecoveryType, const std::string&)
OS_FORWARD_SETTER(setHeatRecoverySensibleEffectiveness, double)
OS_FORWARD_SETTER(setHeatRecoveryLatentEffectiveness, double)
OS_FORWARD_SETTER(setHeatRecoveryHeatExchangerType, const std::string&)
OS_FORWARD_SETTER(setHeatRecoveryFrostControlType, const std::string&)
OS_FORWARD_SETTER(setDehumidificationControlType, const std::string&)
OS_FORWARD_SETTER(setDehumidificationSetpoint, double)
OS_FORWARD_SETTER(setHumidifierType, const std::string&)
OS_FORWARD_SETTER(setHumidifierRatedCapacity, double)
OS_FORWARD_SETTER(setHumidifierRatedElectricPower, double)
OS_FORWARD_SETTER(setHumidifierConstantSetpoint, double)

#undef OS_FORWARD_SETTER

#define OS_FORWARD_VOID(method)                                                                                                             \
  void HVACTemplateSystemDedicatedOutdoorAir::method() {                                                                                   \
    getImpl<detail::HVACTemplateSystemDedicatedOutdoorAir_Impl>()->method();                                                               \
  }

OS_FORWARD_VOID(resetAirOutletType)
OS_FORWARD_VOID(resetSupplyFanFlowRate)
OS_FORWARD_VOID(resetSupplyFanTotalEfficiency)
OS_FORWARD_VOID(resetSupplyFanDeltaPressure)
OS_FORWARD_VOID(resetSupplyFanMotorEfficiency)
OS_FORWARD_VOID(resetSupplyFanMotorinAirStreamFraction)
OS_FORWARD_VOID(resetSupplyFanPlacement)
OS_FORWARD_VOID(resetCoolingCoilType)
OS_FORWARD_VOID(resetCoolingCoilSetpointControlType)
OS_FORWARD_VOID(resetCoolingCoilDesignSetpoint)
OS_FORWARD_VOID(resetCoolingCoilSetpointatOutdoorDryBulbLow)
OS_FORWARD_VOID(resetCoolingCoilResetOutdoorDryBulbLow)
OS_FORWARD_VOID(resetCoolingCoilSetpointatOutdoorDryBulbHigh)
OS_FORWARD_VOID(resetCoolingCoilResetOutdoorDryBulbHigh)
OS_FORWARD_VOID(resetDXCoolingCoilGrossRatedTotalCapacity)
OS_FORWARD_VOID(resetDXCoolingCoilGrossRatedSensibleHeatRatio)
OS_FORWARD_VOID(resetDXCoolingCoilGrossRatedCOP)
OS_FORWARD_VOID(resetHeatingCoilType)
OS_FORWARD_VOID(resetHeatingCoilSetpointControlType)
OS_FORWARD_VOID(resetHeatingCoilDesignSetpoint)
OS_FORWARD_VOID(resetHeatingCoilSetpointatOutdoorDryBulbLow)
OS_FORWARD_VOID(resetHeatingCoilResetOutdoorDryBulbLow)
OS_FORWARD_VOID(resetHeatingCoilSetpointatOutdoorDryBulbHigh)
OS_FORWARD_VOID(resetHeatingCoilResetOutdoorDryBulbHigh)
OS_FORWARD_VOID(resetGasHeatingCoilEfficiency)
OS_FORWARD_VOID(resetGasHeatingCoilParasiticElectricLoad)
OS_FORWARD_VOID(resetHeatRecoveryType)
OS_FORWARD_VOID(resetHeatRecoverySensibleEffectiveness)
OS_FORWARD_VOID(resetHeatRecoveryLatentEffectiveness)
OS_FORWARD_VOID(resetHeatRecoveryHeatExchangerType)
OS_FORWARD_VOID(resetHeatRecoveryFrostControlType)
OS_FORWARD_VOID(resetDehumidificationControlType)
OS_FORWARD_VOID(resetDehumidificationSetpoint)
OS_FORWARD_VOID(resetHumidifierType)
OS_FORWARD_VOID(resetHumidifierRatedCapacity)
OS_FORWARD_VOID(resetHumidifierRatedElectricPower)
OS_FORWARD_VOID(resetHumidifierConstantSetpoint)
OS_FORWARD_VOID(autosizeSupplyFanFlowRate)
OS_FORWARD_VOID(autosizeDXCoolingCoilGrossRatedTotalCapacity)
OS_FORWARD_VOID(autosizeDXCoolingCoilGrossRatedSensibleHeatRatio)
OS_FORWARD_VOID(autosizeHumidifierRatedElectricPower)

#undef OS_FORWARD_VOID

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                                                             \
  double HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                                      \
    const auto value = getDouble(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, true);                                 \
    OS_ASSERT(value);                                                                                                                       \
    return *value;                                                                                                                          \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                                                                             \
  boost::optional<double> HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                     \
    return getDouble(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, true);                                              \
  }

#define OS_IMPL_REQUIRED_STRING(method, field)                                                                                             \
  std::string HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                                 \
    const auto value = getString(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, true);                                 \
    OS_ASSERT(value);                                                                                                                       \
    return *value;                                                                                                                          \
  }

OS_IMPL_REQUIRED_STRING(airOutletType, AirOutletType)
OS_IMPL_OPTIONAL_DOUBLE(supplyFanFlowRate, SupplyFanFlowRate)
OS_IMPL_REQUIRED_DOUBLE(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)
OS_IMPL_REQUIRED_DOUBLE(supplyFanDeltaPressure, SupplyFanDeltaPressure)
OS_IMPL_REQUIRED_DOUBLE(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)
OS_IMPL_REQUIRED_DOUBLE(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)
OS_IMPL_REQUIRED_STRING(supplyFanPlacement, SupplyFanPlacement)
OS_IMPL_REQUIRED_STRING(coolingCoilType, CoolingCoilType)
OS_IMPL_REQUIRED_STRING(coolingCoilSetpointControlType, CoolingCoilSetpointControlType)
OS_IMPL_REQUIRED_DOUBLE(coolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)
OS_IMPL_REQUIRED_DOUBLE(coolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_REQUIRED_DOUBLE(coolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)
OS_IMPL_REQUIRED_DOUBLE(coolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_REQUIRED_DOUBLE(coolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)
OS_IMPL_OPTIONAL_DOUBLE(dXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_OPTIONAL_DOUBLE(dXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_REQUIRED_DOUBLE(dXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)
OS_IMPL_REQUIRED_STRING(heatingCoilType, HeatingCoilType)
OS_IMPL_REQUIRED_STRING(heatingCoilSetpointControlType, HeatingCoilSetpointControlType)
OS_IMPL_REQUIRED_DOUBLE(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)
OS_IMPL_REQUIRED_DOUBLE(heatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_REQUIRED_DOUBLE(heatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)
OS_IMPL_REQUIRED_DOUBLE(heatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_REQUIRED_DOUBLE(heatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)
OS_IMPL_REQUIRED_DOUBLE(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)
OS_IMPL_REQUIRED_DOUBLE(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)
OS_IMPL_REQUIRED_STRING(heatRecoveryType, HeatRecoveryType)
OS_IMPL_REQUIRED_DOUBLE(heatRecoverySensibleEffectiveness, HeatRecoverySensibleEffectiveness)
OS_IMPL_REQUIRED_DOUBLE(heatRecoveryLatentEffectiveness, HeatRecoveryLatentEffectiveness)
OS_IMPL_REQUIRED_STRING(heatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)
OS_IMPL_REQUIRED_STRING(heatRecoveryFrostControlType, HeatRecoveryFrostControlType)
OS_IMPL_REQUIRED_STRING(dehumidificationControlType, DehumidificationControlType)
OS_IMPL_REQUIRED_DOUBLE(dehumidificationSetpoint, DehumidificationSetpoint)
OS_IMPL_REQUIRED_STRING(humidifierType, HumidifierType)
OS_IMPL_REQUIRED_DOUBLE(humidifierRatedCapacity, HumidifierRatedCapacity)
OS_IMPL_OPTIONAL_DOUBLE(humidifierRatedElectricPower, HumidifierRatedElectricPower)
OS_IMPL_REQUIRED_DOUBLE(humidifierConstantSetpoint, HumidifierConstantSetpoint)

#undef OS_IMPL_REQUIRED_STRING
#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE

#define OS_IMPL_DEFAULTED(method, field)                                                                                                   \
  bool HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                                        \
    return isEmpty(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field);                                                      \
  }

OS_IMPL_DEFAULTED(isAirOutletTypeDefaulted, AirOutletType)
OS_IMPL_DEFAULTED(isSupplyFanFlowRateDefaulted, SupplyFanFlowRate)
OS_IMPL_DEFAULTED(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)
OS_IMPL_DEFAULTED(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)
OS_IMPL_DEFAULTED(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)
OS_IMPL_DEFAULTED(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)
OS_IMPL_DEFAULTED(isSupplyFanPlacementDefaulted, SupplyFanPlacement)
OS_IMPL_DEFAULTED(isCoolingCoilTypeDefaulted, CoolingCoilType)
OS_IMPL_DEFAULTED(isCoolingCoilSetpointControlTypeDefaulted, CoolingCoilSetpointControlType)
OS_IMPL_DEFAULTED(isCoolingCoilDesignSetpointDefaulted, CoolingCoilDesignSetpoint)
OS_IMPL_DEFAULTED(isCoolingCoilSetpointatOutdoorDryBulbLowDefaulted, CoolingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_DEFAULTED(isCoolingCoilResetOutdoorDryBulbLowDefaulted, CoolingCoilResetOutdoorDryBulbLow)
OS_IMPL_DEFAULTED(isCoolingCoilSetpointatOutdoorDryBulbHighDefaulted, CoolingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_DEFAULTED(isCoolingCoilResetOutdoorDryBulbHighDefaulted, CoolingCoilResetOutdoorDryBulbHigh)
OS_IMPL_DEFAULTED(isDXCoolingCoilGrossRatedTotalCapacityDefaulted, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_DEFAULTED(isDXCoolingCoilGrossRatedSensibleHeatRatioDefaulted, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_DEFAULTED(isDXCoolingCoilGrossRatedCOPDefaulted, DXCoolingCoilGrossRatedCOP)
OS_IMPL_DEFAULTED(isHeatingCoilTypeDefaulted, HeatingCoilType)
OS_IMPL_DEFAULTED(isHeatingCoilSetpointControlTypeDefaulted, HeatingCoilSetpointControlType)
OS_IMPL_DEFAULTED(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)
OS_IMPL_DEFAULTED(isHeatingCoilSetpointatOutdoorDryBulbLowDefaulted, HeatingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_DEFAULTED(isHeatingCoilResetOutdoorDryBulbLowDefaulted, HeatingCoilResetOutdoorDryBulbLow)
OS_IMPL_DEFAULTED(isHeatingCoilSetpointatOutdoorDryBulbHighDefaulted, HeatingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_DEFAULTED(isHeatingCoilResetOutdoorDryBulbHighDefaulted, HeatingCoilResetOutdoorDryBulbHigh)
OS_IMPL_DEFAULTED(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)
OS_IMPL_DEFAULTED(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)
OS_IMPL_DEFAULTED(isHeatRecoveryTypeDefaulted, HeatRecoveryType)
OS_IMPL_DEFAULTED(isHeatRecoverySensibleEffectivenessDefaulted, HeatRecoverySensibleEffectiveness)
OS_IMPL_DEFAULTED(isHeatRecoveryLatentEffectivenessDefaulted, HeatRecoveryLatentEffectiveness)
OS_IMPL_DEFAULTED(isHeatRecoveryHeatExchangerTypeDefaulted, HeatRecoveryHeatExchangerType)
OS_IMPL_DEFAULTED(isHeatRecoveryFrostControlTypeDefaulted, HeatRecoveryFrostControlType)
OS_IMPL_DEFAULTED(isDehumidificationControlTypeDefaulted, DehumidificationControlType)
OS_IMPL_DEFAULTED(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)
OS_IMPL_DEFAULTED(isHumidifierTypeDefaulted, HumidifierType)
OS_IMPL_DEFAULTED(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)
OS_IMPL_DEFAULTED(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)
OS_IMPL_DEFAULTED(isHumidifierConstantSetpointDefaulted, HumidifierConstantSetpoint)

#undef OS_IMPL_DEFAULTED

#define OS_IMPL_AUTOSIZED(method, field)                                                                                                   \
  bool HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                                        \
    if (auto value = getString(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, true)) {                                \
      return openstudio::istringEqual(*value, "autosize");                                                                                 \
    }                                                                                                                                       \
    return false;                                                                                                                           \
  }

OS_IMPL_AUTOSIZED(isSupplyFanFlowRateAutosized, SupplyFanFlowRate)
OS_IMPL_AUTOSIZED(isDXCoolingCoilGrossRatedTotalCapacityAutosized, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_AUTOSIZED(isDXCoolingCoilGrossRatedSensibleHeatRatioAutosized, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_AUTOSIZED(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#undef OS_IMPL_AUTOSIZED

#define OS_IMPL_SET_STRING(method, field)                                                                                                  \
  bool HVACTemplateSystemDedicatedOutdoorAir_Impl::method(const std::string& value) {                                                      \
    return setString(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, value);                                             \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                                                                                  \
  bool HVACTemplateSystemDedicatedOutdoorAir_Impl::method(double value) {                                                                   \
    return setDouble(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, value);                                             \
  }

OS_IMPL_SET_STRING(setAirOutletType, AirOutletType)
OS_IMPL_SET_DOUBLE(setSupplyFanFlowRate, SupplyFanFlowRate)
OS_IMPL_SET_DOUBLE(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)
OS_IMPL_SET_DOUBLE(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)
OS_IMPL_SET_DOUBLE(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)
OS_IMPL_SET_DOUBLE(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)
OS_IMPL_SET_STRING(setSupplyFanPlacement, SupplyFanPlacement)
OS_IMPL_SET_STRING(setCoolingCoilType, CoolingCoilType)
OS_IMPL_SET_STRING(setCoolingCoilSetpointControlType, CoolingCoilSetpointControlType)
OS_IMPL_SET_DOUBLE(setCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)
OS_IMPL_SET_DOUBLE(setCoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_SET_DOUBLE(setCoolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)
OS_IMPL_SET_DOUBLE(setCoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_SET_DOUBLE(setCoolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)
OS_IMPL_SET_DOUBLE(setDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_SET_DOUBLE(setDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_SET_DOUBLE(setDXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)
OS_IMPL_SET_STRING(setHeatingCoilType, HeatingCoilType)
OS_IMPL_SET_STRING(setHeatingCoilSetpointControlType, HeatingCoilSetpointControlType)
OS_IMPL_SET_DOUBLE(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)
OS_IMPL_SET_DOUBLE(setHeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_SET_DOUBLE(setHeatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)
OS_IMPL_SET_DOUBLE(setHeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_SET_DOUBLE(setHeatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)
OS_IMPL_SET_DOUBLE(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)
OS_IMPL_SET_DOUBLE(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)
OS_IMPL_SET_STRING(setHeatRecoveryType, HeatRecoveryType)
OS_IMPL_SET_DOUBLE(setHeatRecoverySensibleEffectiveness, HeatRecoverySensibleEffectiveness)
OS_IMPL_SET_DOUBLE(setHeatRecoveryLatentEffectiveness, HeatRecoveryLatentEffectiveness)
OS_IMPL_SET_STRING(setHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)
OS_IMPL_SET_STRING(setHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)
OS_IMPL_SET_STRING(setDehumidificationControlType, DehumidificationControlType)
OS_IMPL_SET_DOUBLE(setDehumidificationSetpoint, DehumidificationSetpoint)
OS_IMPL_SET_STRING(setHumidifierType, HumidifierType)
OS_IMPL_SET_DOUBLE(setHumidifierRatedCapacity, HumidifierRatedCapacity)
OS_IMPL_SET_DOUBLE(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)
OS_IMPL_SET_DOUBLE(setHumidifierConstantSetpoint, HumidifierConstantSetpoint)

#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

#define OS_IMPL_RESET(method, field)                                                                                                       \
  void HVACTemplateSystemDedicatedOutdoorAir_Impl::method() {                                                                              \
    bool result = setString(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, "");                                       \
    OS_ASSERT(result);                                                                                                                      \
  }

OS_IMPL_RESET(resetAirOutletType, AirOutletType)
OS_IMPL_RESET(resetSupplyFanFlowRate, SupplyFanFlowRate)
OS_IMPL_RESET(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)
OS_IMPL_RESET(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)
OS_IMPL_RESET(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)
OS_IMPL_RESET(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)
OS_IMPL_RESET(resetSupplyFanPlacement, SupplyFanPlacement)
OS_IMPL_RESET(resetCoolingCoilType, CoolingCoilType)
OS_IMPL_RESET(resetCoolingCoilSetpointControlType, CoolingCoilSetpointControlType)
OS_IMPL_RESET(resetCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)
OS_IMPL_RESET(resetCoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_RESET(resetCoolingCoilResetOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow)
OS_IMPL_RESET(resetCoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_RESET(resetCoolingCoilResetOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh)
OS_IMPL_RESET(resetDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_RESET(resetDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_RESET(resetDXCoolingCoilGrossRatedCOP, DXCoolingCoilGrossRatedCOP)
OS_IMPL_RESET(resetHeatingCoilType, HeatingCoilType)
OS_IMPL_RESET(resetHeatingCoilSetpointControlType, HeatingCoilSetpointControlType)
OS_IMPL_RESET(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)
OS_IMPL_RESET(resetHeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbLow)
OS_IMPL_RESET(resetHeatingCoilResetOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow)
OS_IMPL_RESET(resetHeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilSetpointatOutdoorDryBulbHigh)
OS_IMPL_RESET(resetHeatingCoilResetOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh)
OS_IMPL_RESET(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)
OS_IMPL_RESET(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)
OS_IMPL_RESET(resetHeatRecoveryType, HeatRecoveryType)
OS_IMPL_RESET(resetHeatRecoverySensibleEffectiveness, HeatRecoverySensibleEffectiveness)
OS_IMPL_RESET(resetHeatRecoveryLatentEffectiveness, HeatRecoveryLatentEffectiveness)
OS_IMPL_RESET(resetHeatRecoveryHeatExchangerType, HeatRecoveryHeatExchangerType)
OS_IMPL_RESET(resetHeatRecoveryFrostControlType, HeatRecoveryFrostControlType)
OS_IMPL_RESET(resetDehumidificationControlType, DehumidificationControlType)
OS_IMPL_RESET(resetDehumidificationSetpoint, DehumidificationSetpoint)
OS_IMPL_RESET(resetHumidifierType, HumidifierType)
OS_IMPL_RESET(resetHumidifierRatedCapacity, HumidifierRatedCapacity)
OS_IMPL_RESET(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)
OS_IMPL_RESET(resetHumidifierConstantSetpoint, HumidifierConstantSetpoint)

#undef OS_IMPL_RESET

#define OS_IMPL_AUTOSIZE(method, field)                                                                                                    \
  void HVACTemplateSystemDedicatedOutdoorAir_Impl::method() {                                                                              \
    bool result = setString(openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field, "Autosize");                               \
    OS_ASSERT(result);                                                                                                                      \
  }

OS_IMPL_AUTOSIZE(autosizeSupplyFanFlowRate, SupplyFanFlowRate)
OS_IMPL_AUTOSIZE(autosizeDXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedTotalCapacity)
OS_IMPL_AUTOSIZE(autosizeDXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedSensibleHeatRatio)
OS_IMPL_AUTOSIZE(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                                                      \
  std::vector<std::string> HVACTemplateSystemDedicatedOutdoorAir_Impl::method() const {                                                    \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_DedicatedOutdoorAir).get(),                 \
                          openstudio::HVACTemplate_System_DedicatedOutdoorAirFields::field);                                               \
  }

OS_IMPL_VALUES(airOutletTypeValues, AirOutletType)
OS_IMPL_VALUES(supplyFanPlacementValues, SupplyFanPlacement)
OS_IMPL_VALUES(coolingCoilTypeValues, CoolingCoilType)
OS_IMPL_VALUES(coolingCoilSetpointControlTypeValues, CoolingCoilSetpointControlType)
OS_IMPL_VALUES(heatingCoilTypeValues, HeatingCoilType)
OS_IMPL_VALUES(heatingCoilSetpointControlTypeValues, HeatingCoilSetpointControlType)
OS_IMPL_VALUES(heatRecoveryTypeValues, HeatRecoveryType)
OS_IMPL_VALUES(heatRecoveryHeatExchangerTypeValues, HeatRecoveryHeatExchangerType)
OS_IMPL_VALUES(heatRecoveryFrostControlTypeValues, HeatRecoveryFrostControlType)
OS_IMPL_VALUES(dehumidificationControlTypeValues, DehumidificationControlType)
OS_IMPL_VALUES(humidifierTypeValues, HumidifierType)

#undef OS_IMPL_VALUES

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
