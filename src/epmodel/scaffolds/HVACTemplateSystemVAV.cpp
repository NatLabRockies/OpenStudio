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

#define OS_VAV_VALUES_MAP(X)                                                      \
  X(supplyFanPlacementValues, SupplyFanPlacement)                                 \
  X(coolingCoilTypeValues, CoolingCoilType)                                       \
  X(heatingCoilTypeValues, HeatingCoilType)                                       \
  X(preheatCoilTypeValues, PreheatCoilType)                                       \
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

#define OS_DEFINE_PUBLIC_VALUES(method, field)                                                                                        \
  std::vector<std::string> HVACTemplateSystemVAV::method() {                                                                          \
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VAVFields::field); \
  }

  OS_VAV_VALUES_MAP(OS_DEFINE_PUBLIC_VALUES)

#undef OS_DEFINE_PUBLIC_VALUES

#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                   \
  std::string HVACTemplateSystemVAV::method() const {               \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(); \
  }

#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                   \
  double HVACTemplateSystemVAV::method() const {                    \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                   \
  boost::optional<double> HVACTemplateSystemVAV::method() const {   \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(); \
  }

#define OS_FORWARD_BOOL(method)                                     \
  bool HVACTemplateSystemVAV::method() const {                      \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(); \
  }

#define OS_FORWARD_STRING_SETTER(method)                                 \
  bool HVACTemplateSystemVAV::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(value); \
  }

#define OS_FORWARD_DOUBLE_SETTER(method)                                 \
  bool HVACTemplateSystemVAV::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(value); \
  }

#define OS_FORWARD_VOID(method)                              \
  void HVACTemplateSystemVAV::method() {                     \
    getImpl<detail::HVACTemplateSystemVAV_Impl>()->method(); \
  }

  // supplyFanMaximumFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanMaximumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateDefaulted)
  OS_FORWARD_BOOL(isSupplyFanMaximumFlowRateAutosized)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMaximumFlowRate)
  OS_FORWARD_VOID(resetSupplyFanMaximumFlowRate)
  OS_FORWARD_VOID(autosizeSupplyFanMaximumFlowRate)

  // supplyFanMinimumFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(supplyFanMinimumFlowRate)
  OS_FORWARD_BOOL(isSupplyFanMinimumFlowRateDefaulted)
  OS_FORWARD_BOOL(isSupplyFanMinimumFlowRateAutosized)
  OS_FORWARD_DOUBLE_SETTER(setSupplyFanMinimumFlowRate)
  OS_FORWARD_VOID(resetSupplyFanMinimumFlowRate)
  OS_FORWARD_VOID(autosizeSupplyFanMinimumFlowRate)

  // supplyFanPlacement
  OS_FORWARD_REQUIRED_STRING_GETTER(supplyFanPlacement)
  OS_FORWARD_BOOL(isSupplyFanPlacementDefaulted)
  OS_FORWARD_STRING_SETTER(setSupplyFanPlacement)
  OS_FORWARD_VOID(resetSupplyFanPlacement)

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

  // coolingCoilDesignSetpoint
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(coolingCoilDesignSetpoint)
  OS_FORWARD_BOOL(isCoolingCoilDesignSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setCoolingCoilDesignSetpoint)
  OS_FORWARD_VOID(resetCoolingCoilDesignSetpoint)

  // heatingCoilType
  OS_FORWARD_REQUIRED_STRING_GETTER(heatingCoilType)
  OS_FORWARD_BOOL(isHeatingCoilTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatingCoilType)
  OS_FORWARD_VOID(resetHeatingCoilType)

  // heatingCoilDesignSetpoint
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(heatingCoilDesignSetpoint)
  OS_FORWARD_BOOL(isHeatingCoilDesignSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setHeatingCoilDesignSetpoint)
  OS_FORWARD_VOID(resetHeatingCoilDesignSetpoint)

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

  // preheatCoilType
  OS_FORWARD_REQUIRED_STRING_GETTER(preheatCoilType)
  OS_FORWARD_BOOL(isPreheatCoilTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setPreheatCoilType)
  OS_FORWARD_VOID(resetPreheatCoilType)

  // preheatCoilDesignSetpoint
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(preheatCoilDesignSetpoint)
  OS_FORWARD_BOOL(isPreheatCoilDesignSetpointDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setPreheatCoilDesignSetpoint)
  OS_FORWARD_VOID(resetPreheatCoilDesignSetpoint)

  // gasPreheatCoilEfficiency
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasPreheatCoilEfficiency)
  OS_FORWARD_BOOL(isGasPreheatCoilEfficiencyDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasPreheatCoilEfficiency)
  OS_FORWARD_VOID(resetGasPreheatCoilEfficiency)

  // gasPreheatCoilParasiticElectricLoad
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(gasPreheatCoilParasiticElectricLoad)
  OS_FORWARD_BOOL(isGasPreheatCoilParasiticElectricLoadDefaulted)
  OS_FORWARD_DOUBLE_SETTER(setGasPreheatCoilParasiticElectricLoad)
  OS_FORWARD_VOID(resetGasPreheatCoilParasiticElectricLoad)

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

  // minimumOutdoorAirControlType
  OS_FORWARD_REQUIRED_STRING_GETTER(minimumOutdoorAirControlType)
  OS_FORWARD_BOOL(isMinimumOutdoorAirControlTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setMinimumOutdoorAirControlType)
  OS_FORWARD_VOID(resetMinimumOutdoorAirControlType)

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

  // supplyFanPartLoadPowerCoefficients
  OS_FORWARD_REQUIRED_STRING_GETTER(supplyFanPartLoadPowerCoefficients)
  OS_FORWARD_BOOL(isSupplyFanPartLoadPowerCoefficientsDefaulted)
  OS_FORWARD_STRING_SETTER(setSupplyFanPartLoadPowerCoefficients)
  OS_FORWARD_VOID(resetSupplyFanPartLoadPowerCoefficients)

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

  // coolingCoilSetpointResetType
  OS_FORWARD_REQUIRED_STRING_GETTER(coolingCoilSetpointResetType)
  OS_FORWARD_BOOL(isCoolingCoilSetpointResetTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setCoolingCoilSetpointResetType)
  OS_FORWARD_VOID(resetCoolingCoilSetpointResetType)

  // heatingCoilSetpointResetType
  OS_FORWARD_REQUIRED_STRING_GETTER(heatingCoilSetpointResetType)
  OS_FORWARD_BOOL(isHeatingCoilSetpointResetTypeDefaulted)
  OS_FORWARD_STRING_SETTER(setHeatingCoilSetpointResetType)
  OS_FORWARD_VOID(resetHeatingCoilSetpointResetType)

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

  // sizingOption
  OS_FORWARD_REQUIRED_STRING_GETTER(sizingOption)
  OS_FORWARD_BOOL(isSizingOptionDefaulted)
  OS_FORWARD_STRING_SETTER(setSizingOption)
  OS_FORWARD_VOID(resetSizingOption)

  // returnFan
  bool HVACTemplateSystemVAV::returnFan() const {
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->returnFan();
  }
  OS_FORWARD_BOOL(isReturnFanDefaulted)
  bool HVACTemplateSystemVAV::setReturnFan(bool returnFan) {
    return getImpl<detail::HVACTemplateSystemVAV_Impl>()->setReturnFan(returnFan);
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

  // returnFanPartLoadPowerCoefficients
  OS_FORWARD_REQUIRED_STRING_GETTER(returnFanPartLoadPowerCoefficients)
  OS_FORWARD_BOOL(isReturnFanPartLoadPowerCoefficientsDefaulted)
  OS_FORWARD_STRING_SETTER(setReturnFanPartLoadPowerCoefficients)
  OS_FORWARD_VOID(resetReturnFanPartLoadPowerCoefficients)

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

#define OS_IMPL_REQUIRED_STRING_GETTER(method, field)                                     \
  std::string HVACTemplateSystemVAV_Impl::method() const {                                \
    const auto value = getString(openstudio::HVACTemplate_System_VAVFields::field, true); \
    OS_ASSERT(value);                                                                     \
    return *value;                                                                        \
  }

#define OS_IMPL_REQUIRED_DOUBLE_GETTER(method, field)                                     \
  double HVACTemplateSystemVAV_Impl::method() const {                                     \
    const auto value = getDouble(openstudio::HVACTemplate_System_VAVFields::field, true); \
    OS_ASSERT(value);                                                                     \
    return *value;                                                                        \
  }

#define OS_IMPL_OPTIONAL_DOUBLE_GETTER(method, field)                         \
  boost::optional<double> HVACTemplateSystemVAV_Impl::method() const {        \
    return getDouble(openstudio::HVACTemplate_System_VAVFields::field, true); \
  }

#define OS_IMPL_DEFAULTED(method, field)                              \
  bool HVACTemplateSystemVAV_Impl::method() const {                   \
    return isEmpty(openstudio::HVACTemplate_System_VAVFields::field); \
  }

#define OS_IMPL_IS_AUTOSIZED(method, field)                                               \
  bool HVACTemplateSystemVAV_Impl::method() const {                                       \
    if (auto value = getString(openstudio::HVACTemplate_System_VAVFields::field, true)) { \
      return openstudio::istringEqual(*value, "autosize");                                \
    }                                                                                     \
    return false;                                                                         \
  }

#define OS_IMPL_SET_STRING(method, field)                                      \
  bool HVACTemplateSystemVAV_Impl::method(const std::string& value) {          \
    return setString(openstudio::HVACTemplate_System_VAVFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                      \
  bool HVACTemplateSystemVAV_Impl::method(double value) {                      \
    return setDouble(openstudio::HVACTemplate_System_VAVFields::field, value); \
  }

#define OS_IMPL_SET_DOUBLE_ASSERT(method, field)                                            \
  bool HVACTemplateSystemVAV_Impl::method(double value) {                                   \
    const bool result = setDouble(openstudio::HVACTemplate_System_VAVFields::field, value); \
    OS_ASSERT(result);                                                                      \
    return result;                                                                          \
  }

#define OS_IMPL_RESET(method, field)                                                     \
  void HVACTemplateSystemVAV_Impl::method() {                                            \
    const bool result = setString(openstudio::HVACTemplate_System_VAVFields::field, ""); \
    OS_ASSERT(result);                                                                   \
  }

#define OS_IMPL_AUTOSIZE(method, field)                                                          \
  void HVACTemplateSystemVAV_Impl::method() {                                                    \
    const bool result = setString(openstudio::HVACTemplate_System_VAVFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                           \
  }

    bool HVACTemplateSystemVAV_Impl::returnFan() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_VAVFields::ReturnFan);
    }

    bool HVACTemplateSystemVAV_Impl::setReturnFan(bool returnFan) {
      const bool result = setBooleanFieldValue(*this, openstudio::HVACTemplate_System_VAVFields::ReturnFan, returnFan);
      OS_ASSERT(result);
      return result;
    }

    // supplyFanMaximumFlowRate
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(supplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)
    OS_IMPL_DEFAULTED(isSupplyFanMaximumFlowRateDefaulted, SupplyFanMaximumFlowRate)
    OS_IMPL_IS_AUTOSIZED(isSupplyFanMaximumFlowRateAutosized, SupplyFanMaximumFlowRate)
    OS_IMPL_SET_DOUBLE(setSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)
    OS_IMPL_RESET(resetSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)
    OS_IMPL_AUTOSIZE(autosizeSupplyFanMaximumFlowRate, SupplyFanMaximumFlowRate)

    // supplyFanMinimumFlowRate
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(supplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)
    OS_IMPL_DEFAULTED(isSupplyFanMinimumFlowRateDefaulted, SupplyFanMinimumFlowRate)
    OS_IMPL_IS_AUTOSIZED(isSupplyFanMinimumFlowRateAutosized, SupplyFanMinimumFlowRate)
    OS_IMPL_SET_DOUBLE(setSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)
    OS_IMPL_RESET(resetSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)
    OS_IMPL_AUTOSIZE(autosizeSupplyFanMinimumFlowRate, SupplyFanMinimumFlowRate)

    // supplyFanPlacement
    OS_IMPL_REQUIRED_STRING_GETTER(supplyFanPlacement, SupplyFanPlacement)
    OS_IMPL_DEFAULTED(isSupplyFanPlacementDefaulted, SupplyFanPlacement)
    OS_IMPL_SET_STRING(setSupplyFanPlacement, SupplyFanPlacement)
    OS_IMPL_RESET(resetSupplyFanPlacement, SupplyFanPlacement)

    // supplyFanTotalEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)
    OS_IMPL_DEFAULTED(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)
    OS_IMPL_SET_DOUBLE(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)
    OS_IMPL_RESET(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)

    // supplyFanDeltaPressure
    OS_IMPL_REQUIRED_DOUBLE_GETTER(supplyFanDeltaPressure, SupplyFanDeltaPressure)
    OS_IMPL_DEFAULTED(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)
    OS_IMPL_SET_DOUBLE(setSupplyFanDeltaPressure, SupplyFanDeltaPressure)
    OS_IMPL_RESET(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)

    // supplyFanMotorEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)
    OS_IMPL_DEFAULTED(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)
    OS_IMPL_SET_DOUBLE(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)
    OS_IMPL_RESET(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)

    // supplyFanMotorinAirStreamFraction
    OS_IMPL_REQUIRED_DOUBLE_GETTER(supplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)
    OS_IMPL_DEFAULTED(isSupplyFanMotorinAirStreamFractionDefaulted, SupplyFanMotorinAirStreamFraction)
    OS_IMPL_SET_DOUBLE(setSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)
    OS_IMPL_RESET(resetSupplyFanMotorinAirStreamFraction, SupplyFanMotorinAirStreamFraction)

    // coolingCoilType
    OS_IMPL_REQUIRED_STRING_GETTER(coolingCoilType, CoolingCoilType)
    OS_IMPL_DEFAULTED(isCoolingCoilTypeDefaulted, CoolingCoilType)
    OS_IMPL_SET_STRING(setCoolingCoilType, CoolingCoilType)
    OS_IMPL_RESET(resetCoolingCoilType, CoolingCoilType)

    // coolingCoilDesignSetpoint
    OS_IMPL_REQUIRED_DOUBLE_GETTER(coolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)
    OS_IMPL_DEFAULTED(isCoolingCoilDesignSetpointDefaulted, CoolingCoilDesignSetpoint)
    OS_IMPL_SET_DOUBLE_ASSERT(setCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)
    OS_IMPL_RESET(resetCoolingCoilDesignSetpoint, CoolingCoilDesignSetpoint)

    // heatingCoilType
    OS_IMPL_REQUIRED_STRING_GETTER(heatingCoilType, HeatingCoilType)
    OS_IMPL_DEFAULTED(isHeatingCoilTypeDefaulted, HeatingCoilType)
    OS_IMPL_SET_STRING(setHeatingCoilType, HeatingCoilType)
    OS_IMPL_RESET(resetHeatingCoilType, HeatingCoilType)

    // heatingCoilDesignSetpoint
    OS_IMPL_REQUIRED_DOUBLE_GETTER(heatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)
    OS_IMPL_DEFAULTED(isHeatingCoilDesignSetpointDefaulted, HeatingCoilDesignSetpoint)
    OS_IMPL_SET_DOUBLE_ASSERT(setHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)
    OS_IMPL_RESET(resetHeatingCoilDesignSetpoint, HeatingCoilDesignSetpoint)

    // gasHeatingCoilEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(gasHeatingCoilEfficiency, GasHeatingCoilEfficiency)
    OS_IMPL_DEFAULTED(isGasHeatingCoilEfficiencyDefaulted, GasHeatingCoilEfficiency)
    OS_IMPL_SET_DOUBLE(setGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)
    OS_IMPL_RESET(resetGasHeatingCoilEfficiency, GasHeatingCoilEfficiency)

    // gasHeatingCoilParasiticElectricLoad
    OS_IMPL_REQUIRED_DOUBLE_GETTER(gasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)
    OS_IMPL_DEFAULTED(isGasHeatingCoilParasiticElectricLoadDefaulted, GasHeatingCoilParasiticElectricLoad)
    OS_IMPL_SET_DOUBLE(setGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)
    OS_IMPL_RESET(resetGasHeatingCoilParasiticElectricLoad, GasHeatingCoilParasiticElectricLoad)

    // preheatCoilType
    OS_IMPL_REQUIRED_STRING_GETTER(preheatCoilType, PreheatCoilType)
    OS_IMPL_DEFAULTED(isPreheatCoilTypeDefaulted, PreheatCoilType)
    OS_IMPL_SET_STRING(setPreheatCoilType, PreheatCoilType)
    OS_IMPL_RESET(resetPreheatCoilType, PreheatCoilType)

    // preheatCoilDesignSetpoint
    OS_IMPL_REQUIRED_DOUBLE_GETTER(preheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)
    OS_IMPL_DEFAULTED(isPreheatCoilDesignSetpointDefaulted, PreheatCoilDesignSetpoint)
    OS_IMPL_SET_DOUBLE_ASSERT(setPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)
    OS_IMPL_RESET(resetPreheatCoilDesignSetpoint, PreheatCoilDesignSetpoint)

    // gasPreheatCoilEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(gasPreheatCoilEfficiency, GasPreheatCoilEfficiency)
    OS_IMPL_DEFAULTED(isGasPreheatCoilEfficiencyDefaulted, GasPreheatCoilEfficiency)
    OS_IMPL_SET_DOUBLE(setGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)
    OS_IMPL_RESET(resetGasPreheatCoilEfficiency, GasPreheatCoilEfficiency)

    // gasPreheatCoilParasiticElectricLoad
    OS_IMPL_REQUIRED_DOUBLE_GETTER(gasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)
    OS_IMPL_DEFAULTED(isGasPreheatCoilParasiticElectricLoadDefaulted, GasPreheatCoilParasiticElectricLoad)
    OS_IMPL_SET_DOUBLE(setGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)
    OS_IMPL_RESET(resetGasPreheatCoilParasiticElectricLoad, GasPreheatCoilParasiticElectricLoad)

    // maximumOutdoorAirFlowRate
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(maximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)
    OS_IMPL_DEFAULTED(isMaximumOutdoorAirFlowRateDefaulted, MaximumOutdoorAirFlowRate)
    OS_IMPL_IS_AUTOSIZED(isMaximumOutdoorAirFlowRateAutosized, MaximumOutdoorAirFlowRate)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)
    OS_IMPL_RESET(resetMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)
    OS_IMPL_AUTOSIZE(autosizeMaximumOutdoorAirFlowRate, MaximumOutdoorAirFlowRate)

    // minimumOutdoorAirFlowRate
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(minimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)
    OS_IMPL_DEFAULTED(isMinimumOutdoorAirFlowRateDefaulted, MinimumOutdoorAirFlowRate)
    OS_IMPL_IS_AUTOSIZED(isMinimumOutdoorAirFlowRateAutosized, MinimumOutdoorAirFlowRate)
    OS_IMPL_SET_DOUBLE(setMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)
    OS_IMPL_RESET(resetMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)
    OS_IMPL_AUTOSIZE(autosizeMinimumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate)

    // minimumOutdoorAirControlType
    OS_IMPL_REQUIRED_STRING_GETTER(minimumOutdoorAirControlType, MinimumOutdoorAirControlType)
    OS_IMPL_DEFAULTED(isMinimumOutdoorAirControlTypeDefaulted, MinimumOutdoorAirControlType)
    OS_IMPL_SET_STRING(setMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)
    OS_IMPL_RESET(resetMinimumOutdoorAirControlType, MinimumOutdoorAirControlType)

    // economizerType
    OS_IMPL_REQUIRED_STRING_GETTER(economizerType, EconomizerType)
    OS_IMPL_DEFAULTED(isEconomizerTypeDefaulted, EconomizerType)
    OS_IMPL_SET_STRING(setEconomizerType, EconomizerType)
    OS_IMPL_RESET(resetEconomizerType, EconomizerType)

    // economizerLockout
    OS_IMPL_REQUIRED_STRING_GETTER(economizerLockout, EconomizerLockout)
    OS_IMPL_DEFAULTED(isEconomizerLockoutDefaulted, EconomizerLockout)
    OS_IMPL_SET_STRING(setEconomizerLockout, EconomizerLockout)
    OS_IMPL_RESET(resetEconomizerLockout, EconomizerLockout)

    // economizerUpperTemperatureLimit
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(economizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)
    OS_IMPL_DEFAULTED(isEconomizerUpperTemperatureLimitDefaulted, EconomizerUpperTemperatureLimit)
    OS_IMPL_SET_DOUBLE_ASSERT(setEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)
    OS_IMPL_RESET(resetEconomizerUpperTemperatureLimit, EconomizerUpperTemperatureLimit)

    // economizerLowerTemperatureLimit
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(economizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)
    OS_IMPL_DEFAULTED(isEconomizerLowerTemperatureLimitDefaulted, EconomizerLowerTemperatureLimit)
    OS_IMPL_SET_DOUBLE_ASSERT(setEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)
    OS_IMPL_RESET(resetEconomizerLowerTemperatureLimit, EconomizerLowerTemperatureLimit)

    // economizerUpperEnthalpyLimit
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(economizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)
    OS_IMPL_DEFAULTED(isEconomizerUpperEnthalpyLimitDefaulted, EconomizerUpperEnthalpyLimit)
    OS_IMPL_SET_DOUBLE_ASSERT(setEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)
    OS_IMPL_RESET(resetEconomizerUpperEnthalpyLimit, EconomizerUpperEnthalpyLimit)

    // economizerMaximumLimitDewpointTemperature
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(economizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)
    OS_IMPL_DEFAULTED(isEconomizerMaximumLimitDewpointTemperatureDefaulted, EconomizerMaximumLimitDewpointTemperature)
    OS_IMPL_SET_DOUBLE_ASSERT(setEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)
    OS_IMPL_RESET(resetEconomizerMaximumLimitDewpointTemperature, EconomizerMaximumLimitDewpointTemperature)

    // supplyFanPartLoadPowerCoefficients
    OS_IMPL_REQUIRED_STRING_GETTER(supplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)
    OS_IMPL_DEFAULTED(isSupplyFanPartLoadPowerCoefficientsDefaulted, SupplyFanPartLoadPowerCoefficients)
    OS_IMPL_SET_STRING(setSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)
    OS_IMPL_RESET(resetSupplyFanPartLoadPowerCoefficients, SupplyFanPartLoadPowerCoefficients)

    // nightCycleControl
    OS_IMPL_REQUIRED_STRING_GETTER(nightCycleControl, NightCycleControl)
    OS_IMPL_DEFAULTED(isNightCycleControlDefaulted, NightCycleControl)
    OS_IMPL_SET_STRING(setNightCycleControl, NightCycleControl)
    OS_IMPL_RESET(resetNightCycleControl, NightCycleControl)

    // heatRecoveryType
    OS_IMPL_REQUIRED_STRING_GETTER(heatRecoveryType, HeatRecoveryType)
    OS_IMPL_DEFAULTED(isHeatRecoveryTypeDefaulted, HeatRecoveryType)
    OS_IMPL_SET_STRING(setHeatRecoveryType, HeatRecoveryType)
    OS_IMPL_RESET(resetHeatRecoveryType, HeatRecoveryType)

    // sensibleHeatRecoveryEffectiveness
    OS_IMPL_REQUIRED_DOUBLE_GETTER(sensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)
    OS_IMPL_DEFAULTED(isSensibleHeatRecoveryEffectivenessDefaulted, SensibleHeatRecoveryEffectiveness)
    OS_IMPL_SET_DOUBLE(setSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)
    OS_IMPL_RESET(resetSensibleHeatRecoveryEffectiveness, SensibleHeatRecoveryEffectiveness)

    // latentHeatRecoveryEffectiveness
    OS_IMPL_REQUIRED_DOUBLE_GETTER(latentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)
    OS_IMPL_DEFAULTED(isLatentHeatRecoveryEffectivenessDefaulted, LatentHeatRecoveryEffectiveness)
    OS_IMPL_SET_DOUBLE(setLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)
    OS_IMPL_RESET(resetLatentHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness)

    // coolingCoilSetpointResetType
    OS_IMPL_REQUIRED_STRING_GETTER(coolingCoilSetpointResetType, CoolingCoilSetpointResetType)
    OS_IMPL_DEFAULTED(isCoolingCoilSetpointResetTypeDefaulted, CoolingCoilSetpointResetType)
    OS_IMPL_SET_STRING(setCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)
    OS_IMPL_RESET(resetCoolingCoilSetpointResetType, CoolingCoilSetpointResetType)

    // heatingCoilSetpointResetType
    OS_IMPL_REQUIRED_STRING_GETTER(heatingCoilSetpointResetType, HeatingCoilSetpointResetType)
    OS_IMPL_DEFAULTED(isHeatingCoilSetpointResetTypeDefaulted, HeatingCoilSetpointResetType)
    OS_IMPL_SET_STRING(setHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)
    OS_IMPL_RESET(resetHeatingCoilSetpointResetType, HeatingCoilSetpointResetType)

    // dehumidificationControlType
    OS_IMPL_REQUIRED_STRING_GETTER(dehumidificationControlType, DehumidificationControlType)
    OS_IMPL_DEFAULTED(isDehumidificationControlTypeDefaulted, DehumidificationControlType)
    OS_IMPL_SET_STRING(setDehumidificationControlType, DehumidificationControlType)
    OS_IMPL_RESET(resetDehumidificationControlType, DehumidificationControlType)

    // dehumidificationSetpoint
    OS_IMPL_REQUIRED_DOUBLE_GETTER(dehumidificationSetpoint, DehumidificationSetpoint)
    OS_IMPL_DEFAULTED(isDehumidificationSetpointDefaulted, DehumidificationSetpoint)
    OS_IMPL_SET_DOUBLE(setDehumidificationSetpoint, DehumidificationSetpoint)
    OS_IMPL_RESET(resetDehumidificationSetpoint, DehumidificationSetpoint)

    // humidifierType
    OS_IMPL_REQUIRED_STRING_GETTER(humidifierType, HumidifierType)
    OS_IMPL_DEFAULTED(isHumidifierTypeDefaulted, HumidifierType)
    OS_IMPL_SET_STRING(setHumidifierType, HumidifierType)
    OS_IMPL_RESET(resetHumidifierType, HumidifierType)

    // humidifierRatedCapacity
    OS_IMPL_REQUIRED_DOUBLE_GETTER(humidifierRatedCapacity, HumidifierRatedCapacity)
    OS_IMPL_DEFAULTED(isHumidifierRatedCapacityDefaulted, HumidifierRatedCapacity)
    OS_IMPL_SET_DOUBLE(setHumidifierRatedCapacity, HumidifierRatedCapacity)
    OS_IMPL_RESET(resetHumidifierRatedCapacity, HumidifierRatedCapacity)

    // humidifierRatedElectricPower
    OS_IMPL_OPTIONAL_DOUBLE_GETTER(humidifierRatedElectricPower, HumidifierRatedElectricPower)
    OS_IMPL_DEFAULTED(isHumidifierRatedElectricPowerDefaulted, HumidifierRatedElectricPower)
    OS_IMPL_IS_AUTOSIZED(isHumidifierRatedElectricPowerAutosized, HumidifierRatedElectricPower)
    OS_IMPL_SET_DOUBLE(setHumidifierRatedElectricPower, HumidifierRatedElectricPower)
    OS_IMPL_RESET(resetHumidifierRatedElectricPower, HumidifierRatedElectricPower)
    OS_IMPL_AUTOSIZE(autosizeHumidifierRatedElectricPower, HumidifierRatedElectricPower)

    // humidifierSetpoint
    OS_IMPL_REQUIRED_DOUBLE_GETTER(humidifierSetpoint, HumidifierSetpoint)
    OS_IMPL_DEFAULTED(isHumidifierSetpointDefaulted, HumidifierSetpoint)
    OS_IMPL_SET_DOUBLE(setHumidifierSetpoint, HumidifierSetpoint)
    OS_IMPL_RESET(resetHumidifierSetpoint, HumidifierSetpoint)

    // sizingOption
    OS_IMPL_REQUIRED_STRING_GETTER(sizingOption, SizingOption)
    OS_IMPL_DEFAULTED(isSizingOptionDefaulted, SizingOption)
    OS_IMPL_SET_STRING(setSizingOption, SizingOption)
    OS_IMPL_RESET(resetSizingOption, SizingOption)

    // returnFan
    OS_IMPL_DEFAULTED(isReturnFanDefaulted, ReturnFan)
    OS_IMPL_RESET(resetReturnFan, ReturnFan)

    // returnFanTotalEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(returnFanTotalEfficiency, ReturnFanTotalEfficiency)
    OS_IMPL_DEFAULTED(isReturnFanTotalEfficiencyDefaulted, ReturnFanTotalEfficiency)
    OS_IMPL_SET_DOUBLE(setReturnFanTotalEfficiency, ReturnFanTotalEfficiency)
    OS_IMPL_RESET(resetReturnFanTotalEfficiency, ReturnFanTotalEfficiency)

    // returnFanDeltaPressure
    OS_IMPL_REQUIRED_DOUBLE_GETTER(returnFanDeltaPressure, ReturnFanDeltaPressure)
    OS_IMPL_DEFAULTED(isReturnFanDeltaPressureDefaulted, ReturnFanDeltaPressure)
    OS_IMPL_SET_DOUBLE(setReturnFanDeltaPressure, ReturnFanDeltaPressure)
    OS_IMPL_RESET(resetReturnFanDeltaPressure, ReturnFanDeltaPressure)

    // returnFanMotorEfficiency
    OS_IMPL_REQUIRED_DOUBLE_GETTER(returnFanMotorEfficiency, ReturnFanMotorEfficiency)
    OS_IMPL_DEFAULTED(isReturnFanMotorEfficiencyDefaulted, ReturnFanMotorEfficiency)
    OS_IMPL_SET_DOUBLE(setReturnFanMotorEfficiency, ReturnFanMotorEfficiency)
    OS_IMPL_RESET(resetReturnFanMotorEfficiency, ReturnFanMotorEfficiency)

    // returnFanMotorinAirStreamFraction
    OS_IMPL_REQUIRED_DOUBLE_GETTER(returnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)
    OS_IMPL_DEFAULTED(isReturnFanMotorinAirStreamFractionDefaulted, ReturnFanMotorinAirStreamFraction)
    OS_IMPL_SET_DOUBLE(setReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)
    OS_IMPL_RESET(resetReturnFanMotorinAirStreamFraction, ReturnFanMotorinAirStreamFraction)

    // returnFanPartLoadPowerCoefficients
    OS_IMPL_REQUIRED_STRING_GETTER(returnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)
    OS_IMPL_DEFAULTED(isReturnFanPartLoadPowerCoefficientsDefaulted, ReturnFanPartLoadPowerCoefficients)
    OS_IMPL_SET_STRING(setReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)
    OS_IMPL_RESET(resetReturnFanPartLoadPowerCoefficients, ReturnFanPartLoadPowerCoefficients)

#undef OS_IMPL_AUTOSIZE
#undef OS_IMPL_RESET
#undef OS_IMPL_SET_DOUBLE_ASSERT
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING
#undef OS_IMPL_IS_AUTOSIZED
#undef OS_IMPL_DEFAULTED
#undef OS_IMPL_OPTIONAL_DOUBLE_GETTER
#undef OS_IMPL_REQUIRED_DOUBLE_GETTER
#undef OS_IMPL_REQUIRED_STRING_GETTER

#define OS_IMPL_VALUES(method, field)                                                                     \
  std::vector<std::string> HVACTemplateSystemVAV_Impl::method() const {                                   \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_VAV).get(), \
                          openstudio::HVACTemplate_System_VAVFields::field);                              \
  }

    OS_VAV_VALUES_MAP(OS_IMPL_VALUES)

#undef OS_IMPL_VALUES
#undef OS_VAV_VALUES_MAP

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
