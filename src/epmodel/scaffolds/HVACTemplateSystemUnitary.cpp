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

#define OS_UNITARY_VALUES_MAP(X)                                    \
  X(coolingCoilTypeValues, CoolingCoilType)                         \
  X(heatingCoilTypeValues, HeatingCoilType)                         \
  X(economizerTypeValues, EconomizerType)                           \
  X(economizerLockoutValues, EconomizerLockout)                     \
  X(supplyFanPlacementValues, SupplyFanPlacement)                   \
  X(nightCycleControlValues, NightCycleControl)                     \
  X(heatRecoveryTypeValues, HeatRecoveryType)                       \
  X(dehumidificationControlTypeValues, DehumidificationControlType) \
  X(humidifierTypeValues, HumidifierType)

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                            \
  std::vector<std::string> HVACTemplateSystemUnitary::method() {                                                                          \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_UnitaryFields::field); \
  }

  OS_UNITARY_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                       \
  std::string HVACTemplateSystemUnitary::method() const {               \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                       \
  double HVACTemplateSystemUnitary::method() const {                    \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                       \
  boost::optional<double> HVACTemplateSystemUnitary::method() const {   \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(); \
  }

#define OS_FORWARD_BOOL(method)                                         \
  bool HVACTemplateSystemUnitary::method() const {                      \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(); \
  }

#define OS_FORWARD_STRING_SETTER(method)                                     \
  bool HVACTemplateSystemUnitary::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(value); \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                     \
  bool HVACTemplateSystemUnitary::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(value); \
  }

#define OS_FORWARD_VOID(method)                                  \
  void HVACTemplateSystemUnitary::method() {                     \
    getImpl<detail::HVACTemplateSystemUnitary_Impl>()->method(); \
  }

  // supplyFanMaximumFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanMaximumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateDefaulted)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateAutosized)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMaximumFlowRate)
  OS_FORWARD_VOID(resetSupplyFanMaximumFlowRate)
  OS_FORWARD_VOID(autosizeSupplyFanMaximumFlowRate)

  // supplyFanTotalEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanTotalEfficiency)
  OS_FORWARD_BOOL(isSupplyFanTotalEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanTotalEfficiency)
  OS_FORWARD_VOID(resetSupplyFanTotalEfficiency)

  // supplyFanDeltaPressure
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanDeltaPressure)
  OS_FORWARD_BOOL(isSupplyFanDeltaPressureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanDeltaPressure)
  OS_FORWARD_VOID(resetSupplyFanDeltaPressure)

  // supplyFanMotorEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanMotorEfficiency)
  OS_FORWARD_BOOL(isSupplyFanMotorEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMotorEfficiency)
  OS_FORWARD_VOID(resetSupplyFanMotorEfficiency)

  // supplyFanMotorinAirStreamFraction
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(supplyFanMotorinAirStreamFraction)
  OS_FORWARD_BOOL(isSupplyFanMotorinAirStreamFractionDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMotorinAirStreamFraction)
  OS_FORWARD_VOID(resetSupplyFanMotorinAirStreamFraction)

  // coolingCoilType
  OS_FORWARD_REQUIRED_STRING_GETTER(coolingCoilType)
  OS_FORWARD_BOOL(isCoolingCoilTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setCoolingCoilType)
  OS_FORWARD_VOID(resetCoolingCoilType)

  // coolingDesignSupplyAirTemperature
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(coolingDesignSupplyAirTemperature)
  OS_FORWARD_BOOL(isCoolingDesignSupplyAirTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingDesignSupplyAirTemperature)
  OS_FORWARD_VOID(resetCoolingDesignSupplyAirTemperature)

  // coolingCoilGrossRatedTotalCapacity
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityDefaulted)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityAutosized)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedTotalCapacity)
  OS_FORWARD_VOID(autosizeCoolingCoilGrossRatedTotalCapacity)

  // coolingCoilGrossRatedSensibleHeatRatio
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioAutosized)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedSensibleHeatRatio)
  OS_FORWARD_VOID(autosizeCoolingCoilGrossRatedSensibleHeatRatio)

  // coolingCoilGrossRatedCOP
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(coolingCoilGrossRatedCOP)
  OS_FORWARD_BOOL(isCoolingCoilGrossRatedCOPDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilGrossRatedCOP)
  OS_FORWARD_VOID(resetCoolingCoilGrossRatedCOP)

  // heatingCoilType
  OS_FORWARD_REQUIRED_STRING_GETTER(heatingCoilType)
  OS_FORWARD_STRING_SETTER(setHeatingCoilType)

  // heatingDesignSupplyAirTemperature
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(heatingDesignSupplyAirTemperature)
  OS_FORWARD_BOOL(isHeatingDesignSupplyAirTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHeatingDesignSupplyAirTemperature)
  OS_FORWARD_VOID(resetHeatingDesignSupplyAirTemperature)

  // heatingCoilCapacity
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(heatingCoilCapacity)
  OS_FORWARD_BOOL(isHeatingCoilCapacityDefaulted)
  OS_FORWARD_BOOL(isHeatingCoilCapacityAutosized)
  OS_FORWARD_DOUBLE_SETTER(setHeatingCoilCapacity)
  OS_FORWARD_VOID(resetHeatingCoilCapacity)
  OS_FORWARD_VOID(autosizeHeatingCoilCapacity)

  // gasHeatingCoilEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasHeatingCoilEfficiency)
  OS_FORWARD_BOOL(isGasHeatingCoilEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasHeatingCoilEfficiency)
  OS_FORWARD_VOID(resetGasHeatingCoilEfficiency)

  // gasHeatingCoilParasiticElectricLoad
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasHeatingCoilParasiticElectricLoad)
  OS_FORWARD_BOOL(isGasHeatingCoilParasiticElectricLoadDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasHeatingCoilParasiticElectricLoad)
  OS_FORWARD_VOID(resetGasHeatingCoilParasiticElectricLoad)

  // maximumOutdoorAirFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(maximumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMaximumOutdoorAirFlowRateDefaulted)
  OS_FORWARD_BOOL(isMaximumOutdoorAirFlowRateAutosized)
  OS_FORWARD_DOUBLE_SETTER(setMaximumOutdoorAirFlowRate)
  OS_FORWARD_VOID(resetMaximumOutdoorAirFlowRate)
  OS_FORWARD_VOID(autosizeMaximumOutdoorAirFlowRate)

  // minimumOutdoorAirFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(minimumOutdoorAirFlowRate)
  OS_FORWARD_BOOL(isMinimumOutdoorAirFlowRateDefaulted)
  OS_FORWARD_BOOL(isMinimumOutdoorAirFlowRateAutosized)
  OS_FORWARD_DOUBLE_SETTER(setMinimumOutdoorAirFlowRate)
  OS_FORWARD_VOID(resetMinimumOutdoorAirFlowRate)
  OS_FORWARD_VOID(autosizeMinimumOutdoorAirFlowRate)

  // economizerType
  OS_FORWARD_REQUIRED_STRING_GETTER(economizerType)
  OS_FORWARD_BOOL(isEconomizerTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setEconomizerType)
  OS_FORWARD_VOID(resetEconomizerType)

  // economizerLockout
  OS_FORWARD_REQUIRED_STRING_GETTER(economizerLockout)
  OS_FORWARD_BOOL(isEconomizerLockoutDefaulted)
  OS_FORWARD_STRING_SETTER(setEconomizerLockout)
  OS_FORWARD_VOID(resetEconomizerLockout)

  // economizerUpperTemperatureLimit
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerUpperTemperatureLimit)
  OS_FORWARD_BOOL(isEconomizerUpperTemperatureLimitDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerUpperTemperatureLimit)
  OS_FORWARD_VOID(resetEconomizerUpperTemperatureLimit)

  // economizerLowerTemperatureLimit
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerLowerTemperatureLimit)
  OS_FORWARD_BOOL(isEconomizerLowerTemperatureLimitDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerLowerTemperatureLimit)
  OS_FORWARD_VOID(resetEconomizerLowerTemperatureLimit)

  // economizerUpperEnthalpyLimit
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerUpperEnthalpyLimit)
  OS_FORWARD_BOOL(isEconomizerUpperEnthalpyLimitDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerUpperEnthalpyLimit)
  OS_FORWARD_VOID(resetEconomizerUpperEnthalpyLimit)

  // economizerMaximumLimitDewpointTemperature
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(economizerMaximumLimitDewpointTemperature)
  OS_FORWARD_BOOL(isEconomizerMaximumLimitDewpointTemperatureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setEconomizerMaximumLimitDewpointTemperature)
  OS_FORWARD_VOID(resetEconomizerMaximumLimitDewpointTemperature)

  // supplyFanPlacement
  OS_FORWARD_REQUIRED_STRING_GETTER(supplyFanPlacement)
  OS_FORWARD_BOOL(isSupplyFanPlacementDefaulted)
  OS_FORWARD_STRING_SETTER(setSupplyFanPlacement)
  OS_FORWARD_VOID(resetSupplyFanPlacement)

  // nightCycleControl
  OS_FORWARD_REQUIRED_STRING_GETTER(nightCycleControl)
  OS_FORWARD_BOOL(isNightCycleControlDefaulted)
  OS_FORWARD_STRING_SETTER(setNightCycleControl)
  OS_FORWARD_VOID(resetNightCycleControl)

  // heatRecoveryType
  OS_FORWARD_REQUIRED_STRING_GETTER(heatRecoveryType)
  OS_FORWARD_BOOL(isHeatRecoveryTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatRecoveryType)
  OS_FORWARD_VOID(resetHeatRecoveryType)

  // sensibleHeatRecoveryEffectiveness
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(sensibleHeatRecoveryEffectiveness)
  OS_FORWARD_BOOL(isSensibleHeatRecoveryEffectivenessDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setSensibleHeatRecoveryEffectiveness)
  OS_FORWARD_VOID(resetSensibleHeatRecoveryEffectiveness)

  // latentHeatRecoveryEffectiveness
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(latentHeatRecoveryEffectiveness)
  OS_FORWARD_BOOL(isLatentHeatRecoveryEffectivenessDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setLatentHeatRecoveryEffectiveness)
  OS_FORWARD_VOID(resetLatentHeatRecoveryEffectiveness)

  // dehumidificationControlType
  OS_FORWARD_REQUIRED_STRING_GETTER(dehumidificationControlType)
  OS_FORWARD_BOOL(isDehumidificationControlTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setDehumidificationControlType)
  OS_FORWARD_VOID(resetDehumidificationControlType)

  // dehumidificationSetpoint
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(dehumidificationSetpoint)
  OS_FORWARD_BOOL(isDehumidificationSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setDehumidificationSetpoint)
  OS_FORWARD_VOID(resetDehumidificationSetpoint)

  // humidifierType
  OS_FORWARD_REQUIRED_STRING_GETTER(humidifierType)
  OS_FORWARD_BOOL(isHumidifierTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHumidifierType)
  OS_FORWARD_VOID(resetHumidifierType)

  // humidifierRatedCapacity
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(humidifierRatedCapacity)
  OS_FORWARD_BOOL(isHumidifierRatedCapacityDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierRatedCapacity)
  OS_FORWARD_VOID(resetHumidifierRatedCapacity)

  // humidifierRatedElectricPower
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(humidifierRatedElectricPower)
  OS_FORWARD_BOOL(isHumidifierRatedElectricPowerDefaulted)
  OS_FORWARD_BOOL(isHumidifierRatedElectricPowerAutosized)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierRatedElectricPower)
  OS_FORWARD_VOID(resetHumidifierRatedElectricPower)
  OS_FORWARD_VOID(autosizeHumidifierRatedElectricPower)

  // humidifierSetpoint
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(humidifierSetpoint)
  OS_FORWARD_BOOL(isHumidifierSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHumidifierSetpoint)
  OS_FORWARD_VOID(resetHumidifierSetpoint)

  // returnFan accessors
  bool HVACTemplateSystemUnitary::returnFan() const {
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->returnFan();
  }
  OS_FORWARD_BOOL(isReturnFanDefaulted)
  bool HVACTemplateSystemUnitary::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemUnitary_Impl>()->setReturnFan(returnFan);
  }
  OS_FORWARD_VOID(resetReturnFan)

  // returnFanTotalEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanTotalEfficiency)
  OS_FORWARD_BOOL(isReturnFanTotalEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanTotalEfficiency)
  OS_FORWARD_VOID(resetReturnFanTotalEfficiency)

  // returnFanDeltaPressure
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanDeltaPressure)
  OS_FORWARD_BOOL(isReturnFanDeltaPressureDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanDeltaPressure)
  OS_FORWARD_VOID(resetReturnFanDeltaPressure)

  // returnFanMotorEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanMotorEfficiency)
  OS_FORWARD_BOOL(isReturnFanMotorEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanMotorEfficiency)
  OS_FORWARD_VOID(resetReturnFanMotorEfficiency)

  // returnFanMotorinAirStreamFraction
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(returnFanMotorinAirStreamFraction)
  OS_FORWARD_BOOL(isReturnFanMotorinAirStreamFractionDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setReturnFanMotorinAirStreamFraction)
  OS_FORWARD_VOID(resetReturnFanMotorinAirStreamFraction)

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

#define OS_UNITARY_REQUIRED_STRING_MAP(X)                     \
  X(coolingCoilType, CoolingCoilType)                         \
  X(heatingCoilType, HeatingCoilType)                         \
  X(economizerType, EconomizerType)                           \
  X(economizerLockout, EconomizerLockout)                     \
  X(supplyFanPlacement, SupplyFanPlacement)                   \
  X(nightCycleControl, NightCycleControl)                     \
  X(heatRecoveryType, HeatRecoveryType)                       \
  X(dehumidificationControlType, DehumidificationControlType) \
  X(humidifierType, HumidifierType)

#define OS_UNITARY_REQUIRED_DOUBLE_MAP(X)                                     \
  X(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)                       \
  X(supplyFanDeltaPressure, SupplyFanDeltaPressure)                           \
  X(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)                       \
  X(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)     \
  X(coolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)     \
  X(coolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                       \
  X(heatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)     \
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

#define OS_UNITARY_OPTIONAL_DOUBLE_MAP(X)                                                 \
  X(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(heatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(economizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                     \
  X(economizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                     \
  X(economizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                           \
  X(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(humidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_REQUIRED_STRING(method, field)                                                \
  std::string HVACTemplateSystemUnitary_Impl::method() const {                                \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryFields::field, true); \
    OS_ASSERT(value);                                                                         \
    return *value;                                                                            \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                                \
  double HVACTemplateSystemUnitary_Impl::method() const {                                     \
    const auto value = getDouble(openstudio::HVACTemplate_System_UnitaryFields::field, true); \
    OS_ASSERT(value);                                                                         \
    return *value;                                                                            \
  }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                    \
  boost::optional<double> HVACTemplateSystemUnitary_Impl::method() const {        \
    return getDouble(openstudio::HVACTemplate_System_UnitaryFields::field, true); \
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

#define OS_UNITARY_DEFAULTED_MAP(X)                                                                  \
  X(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)                                   \
  X(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)                                   \
  X(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)                                       \
  X(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)                                   \
  X(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)                 \
  X(isCoolingCoilTypeDefaulted, CoolingCoilType)                                                     \
  X(isCoolingDesignSupplyAirTemperatureDefaulted, CoolingDesignSupplyAirTemperature)                 \
  X(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)               \
  X(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(isCoolingCoilGrossRatedCOPDefaulted, CoolingCoilGrossRatedCOP)                                   \
  X(isHeatingDesignSupplyAirTemperatureDefaulted, HeatingDesignSupplyAirTemperature)                 \
  X(isHeatingCoilCapacityDefaulted, HeatingCoilCapacity)                                             \
  X(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)                                   \
  X(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)             \
  X(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)                                 \
  X(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)                                 \
  X(isEconomizerTypeDefaulted, EconomizerType)                                                       \
  X(isEconomizerLockoutDefaulted, EconomizerLockout)                                                 \
  X(isEconomizerUpperTemperatureLimitDefaulted, EconomizerUpperTemperatureLimit)                     \
  X(isEconomizerLowerTemperatureLimitDefaulted, EconomizerLowerTemperatureLimit)                     \
  X(isEconomizerUpperEnthalpyLimitDefaulted, EconomizerUpperEnthalpyLimit)                           \
  X(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature) \
  X(isSupplyFanPlacementDefaulted, SupplyFanPlacement)                                               \
  X(isNightCycleControlDefaulted, NightCycleControl)                                                 \
  X(isHeatRecoveryTypeDefaulted, HeatRecoveryType)                                                   \
  X(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)                 \
  X(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)                     \
  X(isDehumidificationControlTypeDefaulted, DehumidificationControlType)                             \
  X(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)                                   \
  X(isHumidifierTypeDefaulted, HumidifierType)                                                       \
  X(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)                                     \
  X(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)                           \
  X(isHumidifierSetpointDefaulted, HumidifierSetpoint)                                               \
  X(isReturnFanDefaulted, ReturnFan)                                                                 \
  X(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)                                   \
  X(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)                                       \
  X(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)                                   \
  X(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)

#define OS_UNITARY_AUTOSIZED_MAP(X)                                                            \
  X(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)                             \
  X(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)         \
  X(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(isHeatingCoilCapacityAutosized, HeatingCoilCapacity)                                       \
  X(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)                           \
  X(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)                           \
  X(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)

#define OS_IMPL_DEFAULTED(method, field)                                  \
  bool HVACTemplateSystemUnitary_Impl::method() const {                   \
    return isEmpty(openstudio::HVACTemplate_System_UnitaryFields::field); \
  }

#define OS_IMPL_AUTOSIZED(method, field)                                                      \
  bool HVACTemplateSystemUnitary_Impl::method() const {                                       \
    const auto value = getString(openstudio::HVACTemplate_System_UnitaryFields::field, true); \
    if (value) {                                                                              \
      return openstudio::istringEqual(*value, "autosize");                                    \
    }                                                                                         \
    return false;                                                                             \
  }

    OS_UNITARY_DEFAULTED_MAP(OS_IMPL_DEFAULTED)
    OS_UNITARY_AUTOSIZED_MAP(OS_IMPL_AUTOSIZED)

#undef OS_IMPL_DEFAULTED
#undef OS_IMPL_AUTOSIZED

#define OS_UNITARY_STRING_SETTER_MAP(X)                          \
  X(setCoolingCoilType, CoolingCoilType)                         \
  X(setHeatingCoilType, HeatingCoilType)                         \
  X(setEconomizerType, EconomizerType)                           \
  X(setEconomizerLockout, EconomizerLockout)                     \
  X(setSupplyFanPlacement, SupplyFanPlacement)                   \
  X(setNightCycleControl, NightCycleControl)                     \
  X(setHeatRecoveryType, HeatRecoveryType)                       \
  X(setDehumidificationControlType, DehumidificationControlType) \
  X(setHumidifierType, HumidifierType)

#define OS_UNITARY_DOUBLE_SETTER_MAP(X)                                                      \
  X(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                   \
  X(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                       \
  X(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                   \
  X(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                 \
  X(setCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                 \
  X(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(setCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                   \
  X(setHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                 \
  X(setHeatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                   \
  X(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)             \
  X(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(setEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                     \
  X(setEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                     \
  X(setEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                           \
  X(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
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

#define OS_IMPL_SET_STRING(method, field)                                          \
  bool HVACTemplateSystemUnitary_Impl::method(const std::string& value) {          \
    return setString(openstudio::HVACTemplate_System_UnitaryFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                          \
  bool HVACTemplateSystemUnitary_Impl::method(double value) {                      \
    return setDouble(openstudio::HVACTemplate_System_UnitaryFields::field, value); \
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

#define OS_UNITARY_RESET_MAP(X)                                                                \
  X(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                                   \
  X(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)                                   \
  X(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)                                       \
  X(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)                                   \
  X(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)                 \
  X(resetCoolingCoilType, CoolingCoilType)                                                     \
  X(resetCoolingDesignSupplyAirTemperature, CoolingDesignSupplyAirTemperature)                 \
  X(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)               \
  X(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)       \
  X(resetCoolingCoilGrossRatedCOP, CoolingCoilGrossRatedCOP)                                   \
  X(resetHeatingDesignSupplyAirTemperature, HeatingDesignSupplyAirTemperature)                 \
  X(resetHeatingCoilCapacity, HeatingCoilCapacity)                                             \
  X(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)                                   \
  X(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)             \
  X(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                                 \
  X(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                                 \
  X(resetEconomizerType, EconomizerType)                                                       \
  X(resetEconomizerLockout, EconomizerLockout)                                                 \
  X(resetEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)                     \
  X(resetEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)                     \
  X(resetEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)                           \
  X(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature) \
  X(resetSupplyFanPlacement, SupplyFanPlacement)                                               \
  X(resetNightCycleControl, NightCycleControl)                                                 \
  X(resetHeatRecoveryType, HeatRecoveryType)                                                   \
  X(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)                 \
  X(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)                     \
  X(resetDehumidificationControlType, DehumidificationControlType)                             \
  X(resetDehumidificationSetpoint, DehumidificationSetpoint)                                   \
  X(resetHumidifierType, HumidifierType)                                                       \
  X(resetHumidifierRatedCapacity, HumidifierRatedCapacity)                                     \
  X(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)                           \
  X(resetHumidifierSetpoint, HumidifierSetpoint)                                               \
  X(resetReturnFan, ReturnFan)                                                                 \
  X(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)                                   \
  X(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)                                       \
  X(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)                                   \
  X(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

#define OS_IMPL_RESET(method, field)                                                         \
  void HVACTemplateSystemUnitary_Impl::method() {                                            \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryFields::field, ""); \
    OS_ASSERT(result);                                                                       \
  }

    OS_UNITARY_RESET_MAP(OS_IMPL_RESET)

#undef OS_IMPL_RESET

#define OS_UNITARY_AUTOSIZE_MAP(X)                                                          \
  X(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)                             \
  X(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)         \
  X(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio) \
  X(autosizeHeatingCoilCapacity, HeatingCoilCapacity)                                       \
  X(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)                           \
  X(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)                           \
  X(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

#define OS_IMPL_AUTOSIZE(method, field)                                                              \
  void HVACTemplateSystemUnitary_Impl::method() {                                                    \
    const bool result = setString(openstudio::HVACTemplate_System_UnitaryFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                               \
  }

    OS_UNITARY_AUTOSIZE_MAP(OS_IMPL_AUTOSIZE)

#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                         \
  std::vector<std::string> HVACTemplateSystemUnitary_Impl::method() const {                                   \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_Unitary).get(), \
                          openstudio::HVACTemplate_System_UnitaryFields::field);                              \
  }

    OS_UNITARY_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_UNITARY_VALUES_MAP

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
