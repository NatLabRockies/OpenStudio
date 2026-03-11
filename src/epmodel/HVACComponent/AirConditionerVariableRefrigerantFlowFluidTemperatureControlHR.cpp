/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp"
#include "HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(const Model& model)
  : ModelObject(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType(), model) {}

AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR(
  std::shared_ptr<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType() {
  return IddObjectType::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR;
}

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantType);
}

std::vector<std::string>
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() {
  return getIddKeyNames(
    IddFactory::instance().getObject(iddObjectType()).get(),
    openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit);
}

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostStrategyValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostStrategy);
}

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostControlValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostControl);
}

#define FORWARD_GETTER(ReturnType, Method)                                                                                           \
  ReturnType AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::Method() const {                                        \
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->Method();                         \
  }

#define FORWARD_SETTER(ArgType, Method)                                                                                               \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::Method(ArgType value) {                                       \
    return getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->Method(value);                    \
  }

FORWARD_GETTER(std::string, refrigerantType)
FORWARD_SETTER(const std::string&, setRefrigerantType)

FORWARD_GETTER(boost::optional<double>, ratedEvaporativeCapacity)
FORWARD_GETTER(bool, isRatedEvaporativeCapacityAutosized)
FORWARD_SETTER(double, setRatedEvaporativeCapacity)
void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::autosizeRatedEvaporativeCapacity() {
  getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->autosizeRatedEvaporativeCapacity();
}

FORWARD_GETTER(double, ratedCompressorPowerPerUnitofRatedEvaporativeCapacity)
FORWARD_SETTER(double, setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity)
FORWARD_GETTER(double, minimumOutdoorAirTemperatureinCoolingOnlyMode)
FORWARD_SETTER(double, setMinimumOutdoorAirTemperatureinCoolingOnlyMode)
FORWARD_GETTER(double, maximumOutdoorAirTemperatureinCoolingOnlyMode)
FORWARD_SETTER(double, setMaximumOutdoorAirTemperatureinCoolingOnlyMode)
FORWARD_GETTER(double, minimumOutdoorAirTemperatureinHeatingOnlyMode)
FORWARD_SETTER(double, setMinimumOutdoorAirTemperatureinHeatingOnlyMode)
FORWARD_GETTER(double, maximumOutdoorAirTemperatureinHeatingOnlyMode)
FORWARD_SETTER(double, setMaximumOutdoorAirTemperatureinHeatingOnlyMode)
FORWARD_GETTER(double, minimumOutdoorTemperatureinHeatRecoveryMode)
FORWARD_SETTER(double, setMinimumOutdoorTemperatureinHeatRecoveryMode)
FORWARD_GETTER(double, maximumOutdoorTemperatureinHeatRecoveryMode)
FORWARD_SETTER(double, setMaximumOutdoorTemperatureinHeatRecoveryMode)
FORWARD_GETTER(std::string, refrigerantTemperatureControlAlgorithmforIndoorUnit)
FORWARD_SETTER(const std::string&, setRefrigerantTemperatureControlAlgorithmforIndoorUnit)
FORWARD_GETTER(double, referenceEvaporatingTemperatureforIndoorUnit)
FORWARD_SETTER(double, setReferenceEvaporatingTemperatureforIndoorUnit)
FORWARD_GETTER(double, referenceCondensingTemperatureforIndoorUnit)
FORWARD_SETTER(double, setReferenceCondensingTemperatureforIndoorUnit)
FORWARD_GETTER(double, variableEvaporatingTemperatureMinimumforIndoorUnit)
FORWARD_SETTER(double, setVariableEvaporatingTemperatureMinimumforIndoorUnit)
FORWARD_GETTER(double, variableEvaporatingTemperatureMaximumforIndoorUnit)
FORWARD_SETTER(double, setVariableEvaporatingTemperatureMaximumforIndoorUnit)
FORWARD_GETTER(double, variableCondensingTemperatureMinimumforIndoorUnit)
FORWARD_SETTER(double, setVariableCondensingTemperatureMinimumforIndoorUnit)
FORWARD_GETTER(double, variableCondensingTemperatureMaximumforIndoorUnit)
FORWARD_SETTER(double, setVariableCondensingTemperatureMaximumforIndoorUnit)
FORWARD_GETTER(double, outdoorUnitEvaporatorReferenceSuperheating)
FORWARD_SETTER(double, setOutdoorUnitEvaporatorReferenceSuperheating)
FORWARD_GETTER(double, outdoorUnitCondenserReferenceSubcooling)
FORWARD_SETTER(double, setOutdoorUnitCondenserReferenceSubcooling)
FORWARD_GETTER(double, outdoorUnitEvaporatorRatedBypassFactor)
FORWARD_SETTER(double, setOutdoorUnitEvaporatorRatedBypassFactor)
FORWARD_GETTER(double, outdoorUnitCondenserRatedBypassFactor)
FORWARD_SETTER(double, setOutdoorUnitCondenserRatedBypassFactor)
FORWARD_GETTER(double, differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
FORWARD_SETTER(double, setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
FORWARD_GETTER(double, outdoorUnitHeatExchangerCapacityRatio)
FORWARD_SETTER(double, setOutdoorUnitHeatExchangerCapacityRatio)
FORWARD_GETTER(double, outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
FORWARD_SETTER(double, setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
FORWARD_GETTER(double, outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
FORWARD_SETTER(double, setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
FORWARD_GETTER(double, diameterofMainPipeforSuctionGas)
FORWARD_SETTER(double, setDiameterofMainPipeforSuctionGas)
FORWARD_GETTER(double, diameterofMainPipeforDischargeGas)
FORWARD_SETTER(double, setDiameterofMainPipeforDischargeGas)
FORWARD_GETTER(double, lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
FORWARD_SETTER(double, setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
FORWARD_GETTER(double, equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
FORWARD_SETTER(double, setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
FORWARD_GETTER(double, heightDifferenceBetweenOutdoorUnitandIndoorUnits)
FORWARD_SETTER(double, setHeightDifferenceBetweenOutdoorUnitandIndoorUnits)
FORWARD_GETTER(double, mainPipeInsulationThickness)
FORWARD_SETTER(double, setMainPipeInsulationThickness)
FORWARD_GETTER(double, mainPipeInsulationThermalConductivity)
FORWARD_SETTER(double, setMainPipeInsulationThermalConductivity)
FORWARD_GETTER(double, crankcaseHeaterPowerperCompressor)
FORWARD_SETTER(double, setCrankcaseHeaterPowerperCompressor)
FORWARD_GETTER(int, numberofCompressors)
FORWARD_SETTER(int, setNumberofCompressors)
FORWARD_GETTER(double, ratioofCompressorSizetoTotalCompressorCapacity)
FORWARD_SETTER(double, setRatioofCompressorSizetoTotalCompressorCapacity)
FORWARD_GETTER(double, maximumOutdoorDryBulbTemperatureforCrankcaseHeater)
FORWARD_SETTER(double, setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater)
FORWARD_GETTER(std::string, defrostStrategy)
FORWARD_SETTER(const std::string&, setDefrostStrategy)
FORWARD_GETTER(std::string, defrostControl)
FORWARD_SETTER(const std::string&, setDefrostControl)
FORWARD_GETTER(double, defrostTimePeriodFraction)
FORWARD_SETTER(double, setDefrostTimePeriodFraction)
FORWARD_GETTER(boost::optional<double>, resistiveDefrostHeaterCapacity)
FORWARD_GETTER(bool, isResistiveDefrostHeaterCapacityAutosized)
FORWARD_SETTER(double, setResistiveDefrostHeaterCapacity)
void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::autosizeResistiveDefrostHeaterCapacity() {
  getImpl<detail::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl>()->autosizeResistiveDefrostHeaterCapacity();
}
FORWARD_GETTER(double, maximumOutdoorDrybulbTemperatureforDefrostOperation)
FORWARD_SETTER(double, setMaximumOutdoorDrybulbTemperatureforDefrostOperation)
FORWARD_GETTER(double, initialHeatRecoveryCoolingCapacityFraction)
FORWARD_SETTER(double, setInitialHeatRecoveryCoolingCapacityFraction)
FORWARD_GETTER(double, heatRecoveryCoolingCapacityTimeConstant)
FORWARD_SETTER(double, setHeatRecoveryCoolingCapacityTimeConstant)
FORWARD_GETTER(double, initialHeatRecoveryCoolingEnergyFraction)
FORWARD_SETTER(double, setInitialHeatRecoveryCoolingEnergyFraction)
FORWARD_GETTER(double, heatRecoveryCoolingEnergyTimeConstant)
FORWARD_SETTER(double, setHeatRecoveryCoolingEnergyTimeConstant)
FORWARD_GETTER(double, initialHeatRecoveryHeatingCapacityFraction)
FORWARD_SETTER(double, setInitialHeatRecoveryHeatingCapacityFraction)
FORWARD_GETTER(double, heatRecoveryHeatingCapacityTimeConstant)
FORWARD_SETTER(double, setHeatRecoveryHeatingCapacityTimeConstant)
FORWARD_GETTER(double, initialHeatRecoveryHeatingEnergyFraction)
FORWARD_SETTER(double, setInitialHeatRecoveryHeatingEnergyFraction)
FORWARD_GETTER(double, heatRecoveryHeatingEnergyTimeConstant)
FORWARD_SETTER(double, setHeatRecoveryHeatingEnergyTimeConstant)
FORWARD_GETTER(double, compressorMaximumDeltaPressure)
FORWARD_SETTER(double, setCompressorMaximumDeltaPressure)
FORWARD_GETTER(double, compressorInverterEfficiency)
FORWARD_SETTER(double, setCompressorInverterEfficiency)
FORWARD_GETTER(double, compressorEvaporativeCapacityCorrectionFactor)
FORWARD_SETTER(double, setCompressorEvaporativeCapacityCorrectionFactor)

#undef FORWARD_GETTER
#undef FORWARD_SETTER

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

#define REQUIRED_STRING_GETTER(Method, Field)                                                                                         \
  std::string AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                  \
    const auto value = getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
    OS_ASSERT(value);                                                                                                                  \
    return *value;                                                                                                                     \
  }

#define REQUIRED_DOUBLE_GETTER(Method, Field)                                                                                         \
  double AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                       \
    const auto value = getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true); \
    OS_ASSERT(value);                                                                                                                  \
    return *value;                                                                                                                     \
  }

#define REQUIRED_INT_GETTER(Method, Field)                                                                                             \
  int AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                                          \
    const auto value = getInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true);    \
    OS_ASSERT(value);                                                                                                                  \
    return *value;                                                                                                                     \
  }

#define OPTIONAL_DOUBLE_GETTER(Method, Field)                                                                                          \
  boost::optional<double> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method() const {                      \
    return getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, true);             \
  }

#define STRING_SETTER(Method, Field)                                                                                                   \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(const std::string& value) {                       \
    return setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value);            \
  }

#define DOUBLE_SETTER(Method, Field)                                                                                                   \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(double value) {                                   \
    return setDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value);            \
  }

#define INT_SETTER(Method, Field)                                                                                                      \
  bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::Method(int value) {                                      \
    return setInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Field, value);               \
  }

REQUIRED_STRING_GETTER(refrigerantType, RefrigerantType)
STRING_SETTER(setRefrigerantType, RefrigerantType)

OPTIONAL_DOUBLE_GETTER(ratedEvaporativeCapacity, RatedEvaporativeCapacity)
bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::isRatedEvaporativeCapacityAutosized() const {
  if (auto value =
        getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedEvaporativeCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}
DOUBLE_SETTER(setRatedEvaporativeCapacity, RatedEvaporativeCapacity)
void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::autosizeRatedEvaporativeCapacity() {
  OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedEvaporativeCapacity,
                      "autosize"));
}

REQUIRED_DOUBLE_GETTER(ratedCompressorPowerPerUnitofRatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity)
DOUBLE_SETTER(setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity)
REQUIRED_DOUBLE_GETTER(minimumOutdoorAirTemperatureinCoolingOnlyMode, MinimumOutdoorAirTemperatureinCoolingOnlyMode)
DOUBLE_SETTER(setMinimumOutdoorAirTemperatureinCoolingOnlyMode, MinimumOutdoorAirTemperatureinCoolingOnlyMode)
REQUIRED_DOUBLE_GETTER(maximumOutdoorAirTemperatureinCoolingOnlyMode, MaximumOutdoorAirTemperatureinCoolingOnlyMode)
DOUBLE_SETTER(setMaximumOutdoorAirTemperatureinCoolingOnlyMode, MaximumOutdoorAirTemperatureinCoolingOnlyMode)
REQUIRED_DOUBLE_GETTER(minimumOutdoorAirTemperatureinHeatingOnlyMode, MinimumOutdoorAirTemperatureinHeatingOnlyMode)
DOUBLE_SETTER(setMinimumOutdoorAirTemperatureinHeatingOnlyMode, MinimumOutdoorAirTemperatureinHeatingOnlyMode)
REQUIRED_DOUBLE_GETTER(maximumOutdoorAirTemperatureinHeatingOnlyMode, MaximumOutdoorAirTemperatureinHeatingOnlyMode)
DOUBLE_SETTER(setMaximumOutdoorAirTemperatureinHeatingOnlyMode, MaximumOutdoorAirTemperatureinHeatingOnlyMode)
REQUIRED_DOUBLE_GETTER(minimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
DOUBLE_SETTER(setMinimumOutdoorTemperatureinHeatRecoveryMode, MinimumOutdoorTemperatureinHeatRecoveryMode)
REQUIRED_DOUBLE_GETTER(maximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)
DOUBLE_SETTER(setMaximumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode)
REQUIRED_STRING_GETTER(refrigerantTemperatureControlAlgorithmforIndoorUnit, RefrigerantTemperatureControlAlgorithmforIndoorUnit)
STRING_SETTER(setRefrigerantTemperatureControlAlgorithmforIndoorUnit, RefrigerantTemperatureControlAlgorithmforIndoorUnit)
REQUIRED_DOUBLE_GETTER(referenceEvaporatingTemperatureforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit)
DOUBLE_SETTER(setReferenceEvaporatingTemperatureforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit)
REQUIRED_DOUBLE_GETTER(referenceCondensingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit)
DOUBLE_SETTER(setReferenceCondensingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit)
REQUIRED_DOUBLE_GETTER(variableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit)
DOUBLE_SETTER(setVariableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit)
REQUIRED_DOUBLE_GETTER(variableEvaporatingTemperatureMaximumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit)
DOUBLE_SETTER(setVariableEvaporatingTemperatureMaximumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit)
REQUIRED_DOUBLE_GETTER(variableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit)
DOUBLE_SETTER(setVariableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit)
REQUIRED_DOUBLE_GETTER(variableCondensingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit)
DOUBLE_SETTER(setVariableCondensingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit)
REQUIRED_DOUBLE_GETTER(outdoorUnitEvaporatorReferenceSuperheating, OutdoorUnitEvaporatorReferenceSuperheating)
DOUBLE_SETTER(setOutdoorUnitEvaporatorReferenceSuperheating, OutdoorUnitEvaporatorReferenceSuperheating)
REQUIRED_DOUBLE_GETTER(outdoorUnitCondenserReferenceSubcooling, OutdoorUnitCondenserReferenceSubcooling)
DOUBLE_SETTER(setOutdoorUnitCondenserReferenceSubcooling, OutdoorUnitCondenserReferenceSubcooling)
REQUIRED_DOUBLE_GETTER(outdoorUnitEvaporatorRatedBypassFactor, OutdoorUnitEvaporatorRatedBypassFactor)
DOUBLE_SETTER(setOutdoorUnitEvaporatorRatedBypassFactor, OutdoorUnitEvaporatorRatedBypassFactor)
REQUIRED_DOUBLE_GETTER(outdoorUnitCondenserRatedBypassFactor, OutdoorUnitCondenserRatedBypassFactor)
DOUBLE_SETTER(setOutdoorUnitCondenserRatedBypassFactor, OutdoorUnitCondenserRatedBypassFactor)
REQUIRED_DOUBLE_GETTER(differencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode,
                       DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
DOUBLE_SETTER(setDifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode,
              DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode)
REQUIRED_DOUBLE_GETTER(outdoorUnitHeatExchangerCapacityRatio, OutdoorUnitHeatExchangerCapacityRatio)
DOUBLE_SETTER(setOutdoorUnitHeatExchangerCapacityRatio, OutdoorUnitHeatExchangerCapacityRatio)
REQUIRED_DOUBLE_GETTER(outdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
DOUBLE_SETTER(setOutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity)
REQUIRED_DOUBLE_GETTER(outdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
DOUBLE_SETTER(setOutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity)
REQUIRED_DOUBLE_GETTER(diameterofMainPipeforSuctionGas, DiameterofMainPipeforSuctionGas)
DOUBLE_SETTER(setDiameterofMainPipeforSuctionGas, DiameterofMainPipeforSuctionGas)
REQUIRED_DOUBLE_GETTER(diameterofMainPipeforDischargeGas, DiameterofMainPipeforDischargeGas)
DOUBLE_SETTER(setDiameterofMainPipeforDischargeGas, DiameterofMainPipeforDischargeGas)
REQUIRED_DOUBLE_GETTER(lengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
DOUBLE_SETTER(setLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
REQUIRED_DOUBLE_GETTER(equivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
                       EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
DOUBLE_SETTER(setEquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint,
              EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint)
REQUIRED_DOUBLE_GETTER(heightDifferenceBetweenOutdoorUnitandIndoorUnits, HeightDifferenceBetweenOutdoorUnitandIndoorUnits)
DOUBLE_SETTER(setHeightDifferenceBetweenOutdoorUnitandIndoorUnits, HeightDifferenceBetweenOutdoorUnitandIndoorUnits)
REQUIRED_DOUBLE_GETTER(mainPipeInsulationThickness, MainPipeInsulationThickness)
DOUBLE_SETTER(setMainPipeInsulationThickness, MainPipeInsulationThickness)
REQUIRED_DOUBLE_GETTER(mainPipeInsulationThermalConductivity, MainPipeInsulationThermalConductivity)
DOUBLE_SETTER(setMainPipeInsulationThermalConductivity, MainPipeInsulationThermalConductivity)
REQUIRED_DOUBLE_GETTER(crankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
DOUBLE_SETTER(setCrankcaseHeaterPowerperCompressor, CrankcaseHeaterPowerperCompressor)
REQUIRED_INT_GETTER(numberofCompressors, NumberofCompressors)
INT_SETTER(setNumberofCompressors, NumberofCompressors)
REQUIRED_DOUBLE_GETTER(ratioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
DOUBLE_SETTER(setRatioofCompressorSizetoTotalCompressorCapacity, RatioofCompressorSizetoTotalCompressorCapacity)
REQUIRED_DOUBLE_GETTER(maximumOutdoorDryBulbTemperatureforCrankcaseHeater, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater)
DOUBLE_SETTER(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeater, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater)
REQUIRED_STRING_GETTER(defrostStrategy, DefrostStrategy)
STRING_SETTER(setDefrostStrategy, DefrostStrategy)
REQUIRED_STRING_GETTER(defrostControl, DefrostControl)
STRING_SETTER(setDefrostControl, DefrostControl)
REQUIRED_DOUBLE_GETTER(defrostTimePeriodFraction, DefrostTimePeriodFraction)
DOUBLE_SETTER(setDefrostTimePeriodFraction, DefrostTimePeriodFraction)
OPTIONAL_DOUBLE_GETTER(resistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
bool AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
  if (auto value =
        getString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ResistiveDefrostHeaterCapacity,
                  true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}
DOUBLE_SETTER(setResistiveDefrostHeaterCapacity, ResistiveDefrostHeaterCapacity)
void AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::autosizeResistiveDefrostHeaterCapacity() {
  OS_ASSERT(setString(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ResistiveDefrostHeaterCapacity,
                      "autosize"));
}
REQUIRED_DOUBLE_GETTER(maximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
DOUBLE_SETTER(setMaximumOutdoorDrybulbTemperatureforDefrostOperation, MaximumOutdoorDrybulbTemperatureforDefrostOperation)
REQUIRED_DOUBLE_GETTER(initialHeatRecoveryCoolingCapacityFraction, InitialHeatRecoveryCoolingCapacityFraction)
DOUBLE_SETTER(setInitialHeatRecoveryCoolingCapacityFraction, InitialHeatRecoveryCoolingCapacityFraction)
REQUIRED_DOUBLE_GETTER(heatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingCapacityTimeConstant)
DOUBLE_SETTER(setHeatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingCapacityTimeConstant)
REQUIRED_DOUBLE_GETTER(initialHeatRecoveryCoolingEnergyFraction, InitialHeatRecoveryCoolingEnergyFraction)
DOUBLE_SETTER(setInitialHeatRecoveryCoolingEnergyFraction, InitialHeatRecoveryCoolingEnergyFraction)
REQUIRED_DOUBLE_GETTER(heatRecoveryCoolingEnergyTimeConstant, HeatRecoveryCoolingEnergyTimeConstant)
DOUBLE_SETTER(setHeatRecoveryCoolingEnergyTimeConstant, HeatRecoveryCoolingEnergyTimeConstant)
REQUIRED_DOUBLE_GETTER(initialHeatRecoveryHeatingCapacityFraction, InitialHeatRecoveryHeatingCapacityFraction)
DOUBLE_SETTER(setInitialHeatRecoveryHeatingCapacityFraction, InitialHeatRecoveryHeatingCapacityFraction)
REQUIRED_DOUBLE_GETTER(heatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingCapacityTimeConstant)
DOUBLE_SETTER(setHeatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingCapacityTimeConstant)
REQUIRED_DOUBLE_GETTER(initialHeatRecoveryHeatingEnergyFraction, InitialHeatRecoveryHeatingEnergyFraction)
DOUBLE_SETTER(setInitialHeatRecoveryHeatingEnergyFraction, InitialHeatRecoveryHeatingEnergyFraction)
REQUIRED_DOUBLE_GETTER(heatRecoveryHeatingEnergyTimeConstant, HeatRecoveryHeatingEnergyTimeConstant)
DOUBLE_SETTER(setHeatRecoveryHeatingEnergyTimeConstant, HeatRecoveryHeatingEnergyTimeConstant)

// Field-enum spelling drift: use E+ enum token CompressormaximumdeltaPressure while preserving API name.
REQUIRED_DOUBLE_GETTER(compressorMaximumDeltaPressure, CompressormaximumdeltaPressure)
DOUBLE_SETTER(setCompressorMaximumDeltaPressure, CompressormaximumdeltaPressure)
REQUIRED_DOUBLE_GETTER(compressorInverterEfficiency, CompressorInverterEfficiency)
DOUBLE_SETTER(setCompressorInverterEfficiency, CompressorInverterEfficiency)
REQUIRED_DOUBLE_GETTER(compressorEvaporativeCapacityCorrectionFactor, CompressorEvaporativeCapacityCorrectionFactor)
DOUBLE_SETTER(setCompressorEvaporativeCapacityCorrectionFactor, CompressorEvaporativeCapacityCorrectionFactor)

#undef REQUIRED_STRING_GETTER
#undef REQUIRED_DOUBLE_GETTER
#undef REQUIRED_INT_GETTER
#undef OPTIONAL_DOUBLE_GETTER
#undef STRING_SETTER
#undef DOUBLE_SETTER
#undef INT_SETTER

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::refrigerantTypeValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTypeValues();
}

std::vector<std::string>
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::refrigerantTemperatureControlAlgorithmforIndoorUnitValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::
    refrigerantTemperatureControlAlgorithmforIndoorUnitValues();
}

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::defrostStrategyValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostStrategyValues();
}

std::vector<std::string> AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl::defrostControlValues() const {
  return openstudio::epmodel::AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::defrostControlValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
