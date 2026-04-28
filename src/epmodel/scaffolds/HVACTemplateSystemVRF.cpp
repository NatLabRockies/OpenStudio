/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateSystemVRF.hpp"
#include "HVACTemplateSystemVRF_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_System_VRF_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateSystemVRF::HVACTemplateSystemVRF(const Model& model) : ModelObject(HVACTemplateSystemVRF::iddObjectType(), model) {}

  HVACTemplateSystemVRF::HVACTemplateSystemVRF(std::shared_ptr<detail::HVACTemplateSystemVRF_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateSystemVRF::iddObjectType() {
    return IddObjectType::HVACTemplate_System_VRF;
  }

  std::vector<std::string> HVACTemplateSystemVRF::masterThermostatPriorityControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_System_VRFFields::MasterThermostatPriorityControlType);
  }

  std::vector<std::string> HVACTemplateSystemVRF::defrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VRFFields::DefrostStrategy);
  }

  std::vector<std::string> HVACTemplateSystemVRF::defrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VRFFields::DefrostControl);
  }

  std::vector<std::string> HVACTemplateSystemVRF::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VRFFields::CondenserType);
  }

  std::vector<std::string> HVACTemplateSystemVRF::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_System_VRFFields::FuelType);
  }

#define OS_FORWARD_BOOL(method)                                     \
  bool HVACTemplateSystemVRF::method() const {                      \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }

#define OS_FORWARD_OPTIONAL_DOUBLE_GETTER(method)                   \
  boost::optional<double> HVACTemplateSystemVRF::method() const {   \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }
#define OS_FORWARD_REQUIRED_DOUBLE_GETTER(method)                   \
  double HVACTemplateSystemVRF::method() const {                    \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }
#define OS_FORWARD_REQUIRED_STRING_GETTER(method)                   \
  std::string HVACTemplateSystemVRF::method() const {               \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }
#define OS_FORWARD_REQUIRED_INT_GETTER(method)                      \
  int HVACTemplateSystemVRF::method() const {                       \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }
#define OS_FORWARD_SET_STRING(method)                                    \
  bool HVACTemplateSystemVRF::method(const std::string& value) {         \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(value); \
  }
#define OS_FORWARD_SET_DOUBLE(method)                                    \
  bool HVACTemplateSystemVRF::method(double value) {                     \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(value); \
  }
#define OS_FORWARD_SET_INT(method)                                       \
  bool HVACTemplateSystemVRF::method(int value) {                        \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(value); \
  }
#define OS_FORWARD_SET_BOOL(method)                                      \
  bool HVACTemplateSystemVRF::method(bool value) {                       \
    return getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(value); \
  }
#define OS_FORWARD_VOID(method)                              \
  void HVACTemplateSystemVRF::method() {                     \
    getImpl<detail::HVACTemplateSystemVRF_Impl>()->method(); \
  }

  // grossRatedTotalCoolingCapacity
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(grossRatedTotalCoolingCapacity)
  OS_FORWARD_BOOL(isGrossRatedTotalCoolingCapacityDefaulted)
  OS_FORWARD_BOOL(isGrossRatedTotalCoolingCapacityAutosized)
  OS_FORWARD_SET_DOUBLE(setGrossRatedTotalCoolingCapacity)
  OS_FORWARD_VOID(resetGrossRatedTotalCoolingCapacity)
  OS_FORWARD_VOID(autosizeGrossRatedTotalCoolingCapacity)

  // grossRatedCoolingCOP
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(grossRatedCoolingCOP)
  OS_FORWARD_BOOL(isGrossRatedCoolingCOPDefaulted)
  OS_FORWARD_SET_DOUBLE(setGrossRatedCoolingCOP)
  OS_FORWARD_VOID(resetGrossRatedCoolingCOP)

  // minimumOutdoorTemperatureinCoolingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(minimumOutdoorTemperatureinCoolingMode)
  OS_FORWARD_BOOL(isMinimumOutdoorTemperatureinCoolingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMinimumOutdoorTemperatureinCoolingMode)
  OS_FORWARD_VOID(resetMinimumOutdoorTemperatureinCoolingMode)

  // maximumOutdoorTemperatureinCoolingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(maximumOutdoorTemperatureinCoolingMode)
  OS_FORWARD_BOOL(isMaximumOutdoorTemperatureinCoolingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMaximumOutdoorTemperatureinCoolingMode)
  OS_FORWARD_VOID(resetMaximumOutdoorTemperatureinCoolingMode)

  // grossRatedHeatingCapacity
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(grossRatedHeatingCapacity)
  OS_FORWARD_BOOL(isGrossRatedHeatingCapacityDefaulted)
  OS_FORWARD_BOOL(isGrossRatedHeatingCapacityAutosized)
  OS_FORWARD_SET_DOUBLE(setGrossRatedHeatingCapacity)
  OS_FORWARD_VOID(resetGrossRatedHeatingCapacity)
  OS_FORWARD_VOID(autosizeGrossRatedHeatingCapacity)

  // ratedHeatingCapacitySizingRatio
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(ratedHeatingCapacitySizingRatio)
  OS_FORWARD_BOOL(isRatedHeatingCapacitySizingRatioDefaulted)
  OS_FORWARD_SET_DOUBLE(setRatedHeatingCapacitySizingRatio)
  OS_FORWARD_VOID(resetRatedHeatingCapacitySizingRatio)

  // grossRatedHeatingCOP
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(grossRatedHeatingCOP)
  OS_FORWARD_BOOL(isGrossRatedHeatingCOPDefaulted)
  OS_FORWARD_SET_DOUBLE(setGrossRatedHeatingCOP)
  OS_FORWARD_VOID(resetGrossRatedHeatingCOP)

  // minimumOutdoorTemperatureinHeatingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(minimumOutdoorTemperatureinHeatingMode)
  OS_FORWARD_BOOL(isMinimumOutdoorTemperatureinHeatingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMinimumOutdoorTemperatureinHeatingMode)
  OS_FORWARD_VOID(resetMinimumOutdoorTemperatureinHeatingMode)

  // maximumOutdoorTemperatureinHeatingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(maximumOutdoorTemperatureinHeatingMode)
  OS_FORWARD_BOOL(isMaximumOutdoorTemperatureinHeatingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMaximumOutdoorTemperatureinHeatingMode)
  OS_FORWARD_VOID(resetMaximumOutdoorTemperatureinHeatingMode)

  // minimumHeatPumpPartLoadRatio
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(minimumHeatPumpPartLoadRatio)
  OS_FORWARD_BOOL(isMinimumHeatPumpPartLoadRatioDefaulted)
  OS_FORWARD_SET_DOUBLE(setMinimumHeatPumpPartLoadRatio)
  OS_FORWARD_VOID(resetMinimumHeatPumpPartLoadRatio)

  // masterThermostatPriorityControlType
  OS_FORWARD_REQUIRED_STRING_GETTER(masterThermostatPriorityControlType)
  OS_FORWARD_BOOL(isMasterThermostatPriorityControlTypeDefaulted)
  OS_FORWARD_SET_STRING(setMasterThermostatPriorityControlType)
  OS_FORWARD_VOID(resetMasterThermostatPriorityControlType)

  // heatPumpWasteHeatRecovery
  OS_FORWARD_BOOL(heatPumpWasteHeatRecovery)
  OS_FORWARD_BOOL(isHeatPumpWasteHeatRecoveryDefaulted)
  OS_FORWARD_SET_BOOL(setHeatPumpWasteHeatRecovery)
  OS_FORWARD_VOID(resetHeatPumpWasteHeatRecovery)

  // equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
  OS_FORWARD_BOOL(isEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
  OS_FORWARD_VOID(resetEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)

  // verticalHeightusedforPipingCorrectionFactor
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(verticalHeightusedforPipingCorrectionFactor)
  OS_FORWARD_BOOL(isVerticalHeightusedforPipingCorrectionFactorDefaulted)
  OS_FORWARD_SET_DOUBLE(setVerticalHeightusedforPipingCorrectionFactor)
  OS_FORWARD_VOID(resetVerticalHeightusedforPipingCorrectionFactor)

  // equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
  OS_FORWARD_BOOL(isEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
  OS_FORWARD_VOID(resetEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)

  // crankcaseHeaterPowerperCompressor
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(crankcaseHeaterPowerperCompressor)
  OS_FORWARD_BOOL(isCrankcaseHeaterPowerperCompressorDefaulted)
  OS_FORWARD_SET_DOUBLE(setCrankcaseHeaterPowerperCompressor)
  OS_FORWARD_VOID(resetCrankcaseHeaterPowerperCompressor)

  // numberofCompressors
  OS_FORWARD_REQUIRED_INT_GETTER(numberofCompressors)
  OS_FORWARD_BOOL(isNumberofCompressorsDefaulted)
  OS_FORWARD_SET_INT(setNumberofCompressors)
  OS_FORWARD_VOID(resetNumberofCompressors)

  // ratioofCompressorSizetoTotalCompressorCapacity
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(ratioofCompressorSizetoTotalCompressorCapacity)
  OS_FORWARD_BOOL(isRatioofCompressorSizetoTotalCompressorCapacityDefaulted)
  OS_FORWARD_SET_DOUBLE(setRatioofCompressorSizetoTotalCompressorCapacity)
  OS_FORWARD_VOID(resetRatioofCompressorSizetoTotalCompressorCapacity)

  // maximumOutdoorDrybulbTemperatureforCrankcaseHeater
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(maximumOutdoorDrybulbTemperatureforCrankcaseHeater)
  OS_FORWARD_BOOL(isMaximumOutdoorDrybulbTemperatureforCrankcaseHeaterDefaulted)
  OS_FORWARD_SET_DOUBLE(setMaximumOutdoorDrybulbTemperatureforCrankcaseHeater)
  OS_FORWARD_VOID(resetMaximumOutdoorDrybulbTemperatureforCrankcaseHeater)

  // defrostStrategy
  OS_FORWARD_REQUIRED_STRING_GETTER(defrostStrategy)
  OS_FORWARD_BOOL(isDefrostStrategyDefaulted)
  OS_FORWARD_SET_STRING(setDefrostStrategy)
  OS_FORWARD_VOID(resetDefrostStrategy)

  // defrostControl
  OS_FORWARD_REQUIRED_STRING_GETTER(defrostControl)
  OS_FORWARD_BOOL(isDefrostControlDefaulted)
  OS_FORWARD_SET_STRING(setDefrostControl)
  OS_FORWARD_VOID(resetDefrostControl)

  // defrostTimePeriodFraction
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(defrostTimePeriodFraction)
  OS_FORWARD_BOOL(isDefrostTimePeriodFractionDefaulted)
  OS_FORWARD_SET_DOUBLE(setDefrostTimePeriodFraction)
  OS_FORWARD_VOID(resetDefrostTimePeriodFraction)

  // resistiveDefrostHeaterCapacity
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(resistiveDefrostHeaterCapacity)
  OS_FORWARD_BOOL(isResistiveDefrostHeaterCapacityDefaulted)
  OS_FORWARD_BOOL(isResistiveDefrostHeaterCapacityAutosized)
  OS_FORWARD_SET_DOUBLE(setResistiveDefrostHeaterCapacity)
  OS_FORWARD_VOID(resetResistiveDefrostHeaterCapacity)
  OS_FORWARD_VOID(autosizeResistiveDefrostHeaterCapacity)

  // maximumOutdoorDrybulbTemperatureforDefrostOperation
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(maximumOutdoorDrybulbTemperatureforDefrostOperation)
  OS_FORWARD_BOOL(isMaximumOutdoorDrybulbTemperatureforDefrostOperationDefaulted)
  OS_FORWARD_SET_DOUBLE(setMaximumOutdoorDrybulbTemperatureforDefrostOperation)
  OS_FORWARD_VOID(resetMaximumOutdoorDrybulbTemperatureforDefrostOperation)

  // condenserType
  OS_FORWARD_REQUIRED_STRING_GETTER(condenserType)
  OS_FORWARD_BOOL(isCondenserTypeDefaulted)
  OS_FORWARD_SET_STRING(setCondenserType)
  OS_FORWARD_VOID(resetCondenserType)

  // waterCondenserVolumeFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(waterCondenserVolumeFlowRate)
  OS_FORWARD_BOOL(isWaterCondenserVolumeFlowRateDefaulted)
  OS_FORWARD_BOOL(isWaterCondenserVolumeFlowRateAutosized)
  OS_FORWARD_SET_DOUBLE(setWaterCondenserVolumeFlowRate)
  OS_FORWARD_VOID(resetWaterCondenserVolumeFlowRate)
  OS_FORWARD_VOID(autosizeWaterCondenserVolumeFlowRate)

  // evaporativeCondenserEffectiveness
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(evaporativeCondenserEffectiveness)
  OS_FORWARD_BOOL(isEvaporativeCondenserEffectivenessDefaulted)
  OS_FORWARD_SET_DOUBLE(setEvaporativeCondenserEffectiveness)
  OS_FORWARD_VOID(resetEvaporativeCondenserEffectiveness)

  // evaporativeCondenserAirFlowRate
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(evaporativeCondenserAirFlowRate)
  OS_FORWARD_BOOL(isEvaporativeCondenserAirFlowRateDefaulted)
  OS_FORWARD_BOOL(isEvaporativeCondenserAirFlowRateAutosized)
  OS_FORWARD_SET_DOUBLE(setEvaporativeCondenserAirFlowRate)
  OS_FORWARD_VOID(resetEvaporativeCondenserAirFlowRate)
  OS_FORWARD_VOID(autosizeEvaporativeCondenserAirFlowRate)

  // evaporativeCondenserPumpRatedPowerConsumption
  OS_FORWARD_OPTIONAL_DOUBLE_GETTER(evaporativeCondenserPumpRatedPowerConsumption)
  OS_FORWARD_BOOL(isEvaporativeCondenserPumpRatedPowerConsumptionDefaulted)
  OS_FORWARD_BOOL(isEvaporativeCondenserPumpRatedPowerConsumptionAutosized)
  OS_FORWARD_SET_DOUBLE(setEvaporativeCondenserPumpRatedPowerConsumption)
  OS_FORWARD_VOID(resetEvaporativeCondenserPumpRatedPowerConsumption)
  OS_FORWARD_VOID(autosizeEvaporativeCondenserPumpRatedPowerConsumption)

  // basinHeaterCapacity
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(basinHeaterCapacity)
  OS_FORWARD_BOOL(isBasinHeaterCapacityDefaulted)
  OS_FORWARD_SET_DOUBLE(setBasinHeaterCapacity)
  OS_FORWARD_VOID(resetBasinHeaterCapacity)

  // basinHeaterSetpointTemperature
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(basinHeaterSetpointTemperature)
  OS_FORWARD_BOOL(isBasinHeaterSetpointTemperatureDefaulted)
  OS_FORWARD_SET_DOUBLE(setBasinHeaterSetpointTemperature)
  OS_FORWARD_VOID(resetBasinHeaterSetpointTemperature)

  // fuelType
  OS_FORWARD_REQUIRED_STRING_GETTER(fuelType)
  OS_FORWARD_BOOL(isFuelTypeDefaulted)
  OS_FORWARD_SET_STRING(setFuelType)
  OS_FORWARD_VOID(resetFuelType)

  // minimumOutdoorTemperatureinHeatRecoveryMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(minimumOutdoorTemperatureinHeatRecoveryMode)
  OS_FORWARD_BOOL(isMinimumOutdoorTemperatureinHeatRecoveryModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMinimumOutdoorTemperatureinHeatRecoveryMode)
  OS_FORWARD_VOID(resetMinimumOutdoorTemperatureinHeatRecoveryMode)

  // maximumOutdoorTemperatureinHeatRecoveryMode
  OS_FORWARD_REQUIRED_DOUBLE_GETTER(maximumOutdoorTemperatureinHeatRecoveryMode)
  OS_FORWARD_BOOL(isMaximumOutdoorTemperatureinHeatRecoveryModeDefaulted)
  OS_FORWARD_SET_DOUBLE(setMaximumOutdoorTemperatureinHeatRecoveryMode)
  OS_FORWARD_VOID(resetMaximumOutdoorTemperatureinHeatRecoveryMode)

#undef OS_FORWARD_VOID
#undef OS_FORWARD_SET_BOOL
#undef OS_FORWARD_SET_INT
#undef OS_FORWARD_SET_DOUBLE
#undef OS_FORWARD_SET_STRING
#undef OS_FORWARD_REQUIRED_INT_GETTER
#undef OS_FORWARD_REQUIRED_STRING_GETTER
#undef OS_FORWARD_REQUIRED_DOUBLE_GETTER
#undef OS_FORWARD_OPTIONAL_DOUBLE_GETTER
#undef OS_FORWARD_BOOL

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

#define OS_IMPL_REQUIRED_STRING(method, field)                                            \
  std::string HVACTemplateSystemVRF_Impl::method() const {                                \
    const auto value = getString(openstudio::HVACTemplate_System_VRFFields::field, true); \
    OS_ASSERT(value);                                                                     \
    return *value;                                                                        \
  }
#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                            \
  double HVACTemplateSystemVRF_Impl::method() const {                                     \
    const auto value = getDouble(openstudio::HVACTemplate_System_VRFFields::field, true); \
    OS_ASSERT(value);                                                                     \
    return *value;                                                                        \
  }
#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                                \
  boost::optional<double> HVACTemplateSystemVRF_Impl::method() const {        \
    return getDouble(openstudio::HVACTemplate_System_VRFFields::field, true); \
  }
#define OS_IMPL_REQUIRED_INT(method, field)                                            \
  int HVACTemplateSystemVRF_Impl::method() const {                                     \
    const auto value = getInt(openstudio::HVACTemplate_System_VRFFields::field, true); \
    OS_ASSERT(value);                                                                  \
    return *value;                                                                     \
  }
    OS_IMPL_OPTIONAL_DOUBLE(grossRatedTotalCoolingCapacity, GrossRatedTotalCoolingCapacity)
    OS_IMPL_REQUIRED_DOUBLE(grossRatedCoolingCOP, GrossRatedCoolingCOP)
    OS_IMPL_REQUIRED_DOUBLE(minimumOutdoorTemperatureinCoolingMode, MinimumOutdoorTemperatureinCoolingMode)
    OS_IMPL_REQUIRED_DOUBLE(maximumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode)
    OS_IMPL_OPTIONAL_DOUBLE(grossRatedHeatingCapacity, GrossRatedHeatingCapacity)
    OS_IMPL_REQUIRED_DOUBLE(ratedHeatingCapacitySizingRatio, RatedHeatingCapacitySizingRatio)
    OS_IMPL_REQUIRED_DOUBLE(grossRatedHeatingCOP, GrossRatedHeatingCOP)
    OS_IMPL_REQUIRED_DOUBLE(minimumOutdoorTemperatureinHeatingMode, MinimumOutdoorTemperatureinHeatingMode)
    OS_IMPL_REQUIRED_DOUBLE(maximumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode)
    OS_IMPL_REQUIRED_DOUBLE(minimumHeatPumpPartLoadRatio, MinimumHeatPumpPartLoadRatio)
    OS_IMPL_REQUIRED_STRING(masterThermostatPriorityControlType, MasterThermostatPriorityControlType)
    bool HVACTemplateSystemVRF_Impl::heatPumpWasteHeatRecovery() const {
      return getBooleanFieldValue(*this, openstudio::HVACTemplate_System_VRFFields::HeatPumpWasteHeatRecovery);
    }
    OS_IMPL_REQUIRED_DOUBLE(equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode,
                            EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
    OS_IMPL_REQUIRED_DOUBLE(verticalHeightusedforPipingCorrectionFactor, VerticalHeightusedforPipingCorrectionFactor)
    OS_IMPL_REQUIRED_DOUBLE(equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode,
                            EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
    OS_IMPL_REQUIRED_DOUBLE(crankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
    OS_IMPL_REQUIRED_INT(numberofCompressors, NumberofCompressors)
    OS_IMPL_REQUIRED_DOUBLE(ratioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
    OS_IMPL_REQUIRED_DOUBLE(maximumOutdoorDrybulbTemperatureforCrankcaseHeater, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater)
    OS_IMPL_REQUIRED_STRING(defrostStrategy, DefrostStrategy)
    OS_IMPL_REQUIRED_STRING(defrostControl, DefrostControl)
    OS_IMPL_REQUIRED_DOUBLE(defrostTimePeriodFraction, DefrostTimePeriodFraction)
    OS_IMPL_OPTIONAL_DOUBLE(resistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    OS_IMPL_REQUIRED_DOUBLE(maximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    OS_IMPL_REQUIRED_STRING(condenserType, CondenserType)
    OS_IMPL_OPTIONAL_DOUBLE(waterCondenserVolumeFlowRate, WaterCondenserVolumeFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(evaporativeCondenserEffectiveness, EvaporativeCondenserEffectiveness)
    OS_IMPL_OPTIONAL_DOUBLE(evaporativeCondenserAirFlowRate, EvaporativeCondenserAirFlowRate)
    OS_IMPL_OPTIONAL_DOUBLE(evaporativeCondenserPumpRatedPowerConsumption, EvaporativeCondenserPumpRatedPowerConsumption)
    OS_IMPL_REQUIRED_DOUBLE(basinHeaterCapacity, BasinHeaterCapacity)
    OS_IMPL_REQUIRED_DOUBLE(basinHeaterSetpointTemperature, BasinHeaterSetpointTemperature)
    OS_IMPL_REQUIRED_STRING(fuelType, FuelType)
    OS_IMPL_REQUIRED_DOUBLE(minimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
    OS_IMPL_REQUIRED_DOUBLE(maximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)

#undef OS_IMPL_REQUIRED_INT
#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_REQUIRED_STRING

#define OS_IMPL_DEFAULTED(method, field)                              \
  bool HVACTemplateSystemVRF_Impl::method() const {                   \
    return isEmpty(openstudio::HVACTemplate_System_VRFFields::field); \
  }
    OS_IMPL_DEFAULTED(isGrossRatedTotalCoolingCapacityDefaulted, GrossRatedTotalCoolingCapacity)
    OS_IMPL_DEFAULTED(isGrossRatedCoolingCOPDefaulted, GrossRatedCoolingCOP)
    OS_IMPL_DEFAULTED(isMinimumOutdoorTemperatureinCoolingModeDefaulted, MinimumOutdoorTemperatureinCoolingMode)
    OS_IMPL_DEFAULTED(isMaximumOutdoorTemperatureinCoolingModeDefaulted, MaximumOutdoorTemperatureinCoolingMode)
    OS_IMPL_DEFAULTED(isGrossRatedHeatingCapacityDefaulted, GrossRatedHeatingCapacity)
    OS_IMPL_DEFAULTED(isRatedHeatingCapacitySizingRatioDefaulted, RatedHeatingCapacitySizingRatio)
    OS_IMPL_DEFAULTED(isGrossRatedHeatingCOPDefaulted, GrossRatedHeatingCOP)
    OS_IMPL_DEFAULTED(isMinimumOutdoorTemperatureinHeatingModeDefaulted, MinimumOutdoorTemperatureinHeatingMode)
    OS_IMPL_DEFAULTED(isMaximumOutdoorTemperatureinHeatingModeDefaulted, MaximumOutdoorTemperatureinHeatingMode)
    OS_IMPL_DEFAULTED(isMinimumHeatPumpPartLoadRatioDefaulted, MinimumHeatPumpPartLoadRatio)
    OS_IMPL_DEFAULTED(isMasterThermostatPriorityControlTypeDefaulted, MasterThermostatPriorityControlType)
    OS_IMPL_DEFAULTED(isHeatPumpWasteHeatRecoveryDefaulted, HeatPumpWasteHeatRecovery)
    OS_IMPL_DEFAULTED(isEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingModeDefaulted,
                      EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
    OS_IMPL_DEFAULTED(isVerticalHeightusedforPipingCorrectionFactorDefaulted, VerticalHeightusedforPipingCorrectionFactor)
    OS_IMPL_DEFAULTED(isEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingModeDefaulted,
                      EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
    OS_IMPL_DEFAULTED(isCrankcaseHeaterPowerperCompressorDefaulted, CrankcaseHeaterPowerperCompressor)
    OS_IMPL_DEFAULTED(isNumberofCompressorsDefaulted, NumberofCompressors)
    OS_IMPL_DEFAULTED(isRatioofCompressorSizetoTotalCompressorCapacityDefaulted, RatioofCompressorSizetoTotalCompressorCapacity)
    OS_IMPL_DEFAULTED(isMaximumOutdoorDrybulbTemperatureforCrankcaseHeaterDefaulted, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater)
    OS_IMPL_DEFAULTED(isDefrostStrategyDefaulted, DefrostStrategy)
    OS_IMPL_DEFAULTED(isDefrostControlDefaulted, DefrostControl)
    OS_IMPL_DEFAULTED(isDefrostTimePeriodFractionDefaulted, DefrostTimePeriodFraction)
    OS_IMPL_DEFAULTED(isResistiveDefrostHeaterCapacityDefaulted, ResistiveDefrostHeaterCapacity)
    OS_IMPL_DEFAULTED(isMaximumOutdoorDrybulbTemperatureforDefrostOperationDefaulted, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    OS_IMPL_DEFAULTED(isCondenserTypeDefaulted, CondenserType)
    OS_IMPL_DEFAULTED(isWaterCondenserVolumeFlowRateDefaulted, WaterCondenserVolumeFlowRate)
    OS_IMPL_DEFAULTED(isEvaporativeCondenserEffectivenessDefaulted, EvaporativeCondenserEffectiveness)
    OS_IMPL_DEFAULTED(isEvaporativeCondenserAirFlowRateDefaulted, EvaporativeCondenserAirFlowRate)
    OS_IMPL_DEFAULTED(isEvaporativeCondenserPumpRatedPowerConsumptionDefaulted, EvaporativeCondenserPumpRatedPowerConsumption)
    OS_IMPL_DEFAULTED(isBasinHeaterCapacityDefaulted, BasinHeaterCapacity)
    OS_IMPL_DEFAULTED(isBasinHeaterSetpointTemperatureDefaulted, BasinHeaterSetpointTemperature)
    OS_IMPL_DEFAULTED(isFuelTypeDefaulted, FuelType)
    OS_IMPL_DEFAULTED(isMinimumOutdoorTemperatureinHeatRecoveryModeDefaulted, MinimumOutdoorTemperatureinHeatRecoveryMode)
    OS_IMPL_DEFAULTED(isMaximumOutdoorTemperatureinHeatRecoveryModeDefaulted, MaximumOutdoorTemperatureinHeatRecoveryMode)
#undef OS_IMPL_DEFAULTED

#define OS_IMPL_AUTOSIZED(method, field)                                                  \
  bool HVACTemplateSystemVRF_Impl::method() const {                                       \
    if (auto value = getString(openstudio::HVACTemplate_System_VRFFields::field, true)) { \
      return openstudio::istringEqual(*value, "autosize");                                \
    }                                                                                     \
    return false;                                                                         \
  }
    OS_IMPL_AUTOSIZED(isGrossRatedTotalCoolingCapacityAutosized, GrossRatedTotalCoolingCapacity)
    OS_IMPL_AUTOSIZED(isGrossRatedHeatingCapacityAutosized, GrossRatedHeatingCapacity)
    OS_IMPL_AUTOSIZED(isResistiveDefrostHeaterCapacityAutosized, ResistiveDefrostHeaterCapacity)
    OS_IMPL_AUTOSIZED(isWaterCondenserVolumeFlowRateAutosized, WaterCondenserVolumeFlowRate)
    OS_IMPL_AUTOSIZED(isEvaporativeCondenserAirFlowRateAutosized, EvaporativeCondenserAirFlowRate)
    OS_IMPL_AUTOSIZED(isEvaporativeCondenserPumpRatedPowerConsumptionAutosized, EvaporativeCondenserPumpRatedPowerConsumption)
#undef OS_IMPL_AUTOSIZED

#define OS_IMPL_SET_STRING(method, field)                                      \
  bool HVACTemplateSystemVRF_Impl::method(const std::string& value) {          \
    return setString(openstudio::HVACTemplate_System_VRFFields::field, value); \
  }
#define OS_IMPL_SET_DOUBLE(method, field)                                      \
  bool HVACTemplateSystemVRF_Impl::method(double value) {                      \
    return setDouble(openstudio::HVACTemplate_System_VRFFields::field, value); \
  }
#define OS_IMPL_SET_INT(method, field)                                      \
  bool HVACTemplateSystemVRF_Impl::method(int value) {                      \
    return setInt(openstudio::HVACTemplate_System_VRFFields::field, value); \
  }
    OS_IMPL_SET_DOUBLE(setGrossRatedTotalCoolingCapacity, GrossRatedTotalCoolingCapacity)
    OS_IMPL_SET_DOUBLE(setGrossRatedCoolingCOP, GrossRatedCoolingCOP)
    OS_IMPL_SET_DOUBLE(setMinimumOutdoorTemperatureinCoolingMode, MinimumOutdoorTemperatureinCoolingMode)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode)
    OS_IMPL_SET_DOUBLE(setGrossRatedHeatingCapacity, GrossRatedHeatingCapacity)
    OS_IMPL_SET_DOUBLE(setRatedHeatingCapacitySizingRatio, RatedHeatingCapacitySizingRatio)
    OS_IMPL_SET_DOUBLE(setGrossRatedHeatingCOP, GrossRatedHeatingCOP)
    OS_IMPL_SET_DOUBLE(setMinimumOutdoorTemperatureinHeatingMode, MinimumOutdoorTemperatureinHeatingMode)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode)
    OS_IMPL_SET_DOUBLE(setMinimumHeatPumpPartLoadRatio, MinimumHeatPumpPartLoadRatio)
    OS_IMPL_SET_STRING(setMasterThermostatPriorityControlType, MasterThermostatPriorityControlType)
    bool HVACTemplateSystemVRF_Impl::setHeatPumpWasteHeatRecovery(bool value) {
      return setBooleanFieldValue(*this, openstudio::HVACTemplate_System_VRFFields::HeatPumpWasteHeatRecovery, value);
    }
    OS_IMPL_SET_DOUBLE(setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode,
                       EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
    OS_IMPL_SET_DOUBLE(setVerticalHeightusedforPipingCorrectionFactor, VerticalHeightusedforPipingCorrectionFactor)
    OS_IMPL_SET_DOUBLE(setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode,
                       EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
    OS_IMPL_SET_DOUBLE(setCrankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
    OS_IMPL_SET_INT(setNumberofCompressors, NumberofCompressors)
    OS_IMPL_SET_DOUBLE(setRatioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorDrybulbTemperatureforCrankcaseHeater, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater)
    OS_IMPL_SET_STRING(setDefrostStrategy, DefrostStrategy)
    OS_IMPL_SET_STRING(setDefrostControl, DefrostControl)
    OS_IMPL_SET_DOUBLE(setDefrostTimePeriodFraction, DefrostTimePeriodFraction)
    OS_IMPL_SET_DOUBLE(setResistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    OS_IMPL_SET_STRING(setCondenserType, CondenserType)
    OS_IMPL_SET_DOUBLE(setWaterCondenserVolumeFlowRate, WaterCondenserVolumeFlowRate)
    OS_IMPL_SET_DOUBLE(setEvaporativeCondenserEffectiveness, EvaporativeCondenserEffectiveness)
    OS_IMPL_SET_DOUBLE(setEvaporativeCondenserAirFlowRate, EvaporativeCondenserAirFlowRate)
    OS_IMPL_SET_DOUBLE(setEvaporativeCondenserPumpRatedPowerConsumption, EvaporativeCondenserPumpRatedPowerConsumption)
    OS_IMPL_SET_DOUBLE(setBasinHeaterCapacity, BasinHeaterCapacity)
    OS_IMPL_SET_DOUBLE(setBasinHeaterSetpointTemperature, BasinHeaterSetpointTemperature)
    OS_IMPL_SET_STRING(setFuelType, FuelType)
    OS_IMPL_SET_DOUBLE(setMinimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
    OS_IMPL_SET_DOUBLE(setMaximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)

#undef OS_IMPL_SET_INT
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING

#define OS_IMPL_RESET(method, field)                                                     \
  void HVACTemplateSystemVRF_Impl::method() {                                            \
    const bool result = setString(openstudio::HVACTemplate_System_VRFFields::field, ""); \
    OS_ASSERT(result);                                                                   \
  }
    OS_IMPL_RESET(resetGrossRatedTotalCoolingCapacity, GrossRatedTotalCoolingCapacity)
    OS_IMPL_RESET(resetGrossRatedCoolingCOP, GrossRatedCoolingCOP)
    OS_IMPL_RESET(resetMinimumOutdoorTemperatureinCoolingMode, MinimumOutdoorTemperatureinCoolingMode)
    OS_IMPL_RESET(resetMaximumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode)
    OS_IMPL_RESET(resetGrossRatedHeatingCapacity, GrossRatedHeatingCapacity)
    OS_IMPL_RESET(resetRatedHeatingCapacitySizingRatio, RatedHeatingCapacitySizingRatio)
    OS_IMPL_RESET(resetGrossRatedHeatingCOP, GrossRatedHeatingCOP)
    OS_IMPL_RESET(resetMinimumOutdoorTemperatureinHeatingMode, MinimumOutdoorTemperatureinHeatingMode)
    OS_IMPL_RESET(resetMaximumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode)
    OS_IMPL_RESET(resetMinimumHeatPumpPartLoadRatio, MinimumHeatPumpPartLoadRatio)
    OS_IMPL_RESET(resetMasterThermostatPriorityControlType, MasterThermostatPriorityControlType)
    OS_IMPL_RESET(resetHeatPumpWasteHeatRecovery, HeatPumpWasteHeatRecovery)
    OS_IMPL_RESET(resetEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode,
                  EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode)
    OS_IMPL_RESET(resetVerticalHeightusedforPipingCorrectionFactor, VerticalHeightusedforPipingCorrectionFactor)
    OS_IMPL_RESET(resetEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode,
                  EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode)
    OS_IMPL_RESET(resetCrankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
    OS_IMPL_RESET(resetNumberofCompressors, NumberofCompressors)
    OS_IMPL_RESET(resetRatioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
    OS_IMPL_RESET(resetMaximumOutdoorDrybulbTemperatureforCrankcaseHeater, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater)
    OS_IMPL_RESET(resetDefrostStrategy, DefrostStrategy)
    OS_IMPL_RESET(resetDefrostControl, DefrostControl)
    OS_IMPL_RESET(resetDefrostTimePeriodFraction, DefrostTimePeriodFraction)
    OS_IMPL_RESET(resetResistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    OS_IMPL_RESET(resetMaximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
    OS_IMPL_RESET(resetCondenserType, CondenserType)
    OS_IMPL_RESET(resetWaterCondenserVolumeFlowRate, WaterCondenserVolumeFlowRate)
    OS_IMPL_RESET(resetEvaporativeCondenserEffectiveness, EvaporativeCondenserEffectiveness)
    OS_IMPL_RESET(resetEvaporativeCondenserAirFlowRate, EvaporativeCondenserAirFlowRate)
    OS_IMPL_RESET(resetEvaporativeCondenserPumpRatedPowerConsumption, EvaporativeCondenserPumpRatedPowerConsumption)
    OS_IMPL_RESET(resetBasinHeaterCapacity, BasinHeaterCapacity)
    OS_IMPL_RESET(resetBasinHeaterSetpointTemperature, BasinHeaterSetpointTemperature)
    OS_IMPL_RESET(resetFuelType, FuelType)
    OS_IMPL_RESET(resetMinimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
    OS_IMPL_RESET(resetMaximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)
#undef OS_IMPL_RESET

#define OS_IMPL_AUTOSIZE(method, field)                                                          \
  void HVACTemplateSystemVRF_Impl::method() {                                                    \
    const bool result = setString(openstudio::HVACTemplate_System_VRFFields::field, "Autosize"); \
    OS_ASSERT(result);                                                                           \
  }
    OS_IMPL_AUTOSIZE(autosizeGrossRatedTotalCoolingCapacity, GrossRatedTotalCoolingCapacity)
    OS_IMPL_AUTOSIZE(autosizeGrossRatedHeatingCapacity, GrossRatedHeatingCapacity)
    OS_IMPL_AUTOSIZE(autosizeResistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
    OS_IMPL_AUTOSIZE(autosizeWaterCondenserVolumeFlowRate, WaterCondenserVolumeFlowRate)
    OS_IMPL_AUTOSIZE(autosizeEvaporativeCondenserAirFlowRate, EvaporativeCondenserAirFlowRate)
    OS_IMPL_AUTOSIZE(autosizeEvaporativeCondenserPumpRatedPowerConsumption, EvaporativeCondenserPumpRatedPowerConsumption)
#undef OS_IMPL_AUTOSIZE

#define OS_IMPL_VALUES(method, field)                                                                     \
  std::vector<std::string> HVACTemplateSystemVRF_Impl::method() const {                                   \
    return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::HVACTemplate_System_VRF).get(), \
                          openstudio::HVACTemplate_System_VRFFields::field);                              \
  }
    OS_IMPL_VALUES(masterThermostatPriorityControlTypeValues, MasterThermostatPriorityControlType)
    OS_IMPL_VALUES(defrostStrategyValues, DefrostStrategy)
    OS_IMPL_VALUES(defrostControlValues, DefrostControl)
    OS_IMPL_VALUES(condenserTypeValues, CondenserType)
    OS_IMPL_VALUES(fuelTypeValues, FuelType)
#undef OS_IMPL_VALUES

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
