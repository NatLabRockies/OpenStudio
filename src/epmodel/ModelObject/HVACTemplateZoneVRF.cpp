/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneVRF.hpp"
#include "HVACTemplateZoneVRF_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_VRF_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateZoneVRF::HVACTemplateZoneVRF(const Model& model) : ModelObject(HVACTemplateZoneVRF::iddObjectType(), model) {}

  HVACTemplateZoneVRF::HVACTemplateZoneVRF(std::shared_ptr<detail::HVACTemplateZoneVRF_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateZoneVRF::iddObjectType() {
    return IddObjectType::HVACTemplate_Zone_VRF;
  }

  std::vector<std::string> HVACTemplateZoneVRF::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VRFFields::OutdoorAirMethod);
  }

  std::vector<std::string> HVACTemplateZoneVRF::supplyAirFanplacementValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VRFFields::SupplyAirFanplacement);
  }

  std::vector<std::string> HVACTemplateZoneVRF::coolingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VRFFields::CoolingCoilType);
  }

  std::vector<std::string> HVACTemplateZoneVRF::heatPumpHeatingCoilTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VRFFields::HeatPumpHeatingCoilType);
  }

  std::vector<std::string> HVACTemplateZoneVRF::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_VRFFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZoneVRF::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_VRFFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZoneVRF::baseboardHeatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_VRFFields::BaseboardHeatingType);
  }

#define VRF_FORWARD_GETTER(returnType, name)                    \
  returnType HVACTemplateZoneVRF::name() const {                \
    return getImpl<detail::HVACTemplateZoneVRF_Impl>()->name(); \
  }

#define VRF_FORWARD_BOOL(name)                                  \
  bool HVACTemplateZoneVRF::name() const {                      \
    return getImpl<detail::HVACTemplateZoneVRF_Impl>()->name(); \
  }

#define VRF_FORWARD_SETTER(argType, name, arg)                     \
  bool HVACTemplateZoneVRF::name(argType arg) {                    \
    return getImpl<detail::HVACTemplateZoneVRF_Impl>()->name(arg); \
  }

#define VRF_FORWARD_RESET(name)                          \
  void HVACTemplateZoneVRF::name() {                     \
    getImpl<detail::HVACTemplateZoneVRF_Impl>()->name(); \
  }

  VRF_FORWARD_GETTER(boost::optional<double>, zoneHeatingSizingFactor)
  VRF_FORWARD_SETTER(double, setZoneHeatingSizingFactor, zoneHeatingSizingFactor)
  VRF_FORWARD_RESET(resetZoneHeatingSizingFactor)

  VRF_FORWARD_GETTER(boost::optional<double>, zoneCoolingSizingFactor)
  VRF_FORWARD_SETTER(double, setZoneCoolingSizingFactor, zoneCoolingSizingFactor)
  VRF_FORWARD_RESET(resetZoneCoolingSizingFactor)

  VRF_FORWARD_GETTER(double, ratedTotalHeatingCapacitySizingRatio)
  VRF_FORWARD_BOOL(isRatedTotalHeatingCapacitySizingRatioDefaulted)
  VRF_FORWARD_SETTER(double, setRatedTotalHeatingCapacitySizingRatio, ratedTotalHeatingCapacitySizingRatio)
  VRF_FORWARD_RESET(resetRatedTotalHeatingCapacitySizingRatio)

  VRF_FORWARD_GETTER(boost::optional<double>, coolingSupplyAirFlowRate)
  VRF_FORWARD_BOOL(isCoolingSupplyAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isCoolingSupplyAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setCoolingSupplyAirFlowRate, coolingSupplyAirFlowRate)
  VRF_FORWARD_RESET(resetCoolingSupplyAirFlowRate)
  VRF_FORWARD_RESET(autosizeCoolingSupplyAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, noCoolingSupplyAirFlowRate)
  VRF_FORWARD_BOOL(isNoCoolingSupplyAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isNoCoolingSupplyAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setNoCoolingSupplyAirFlowRate, noCoolingSupplyAirFlowRate)
  VRF_FORWARD_RESET(resetNoCoolingSupplyAirFlowRate)
  VRF_FORWARD_RESET(autosizeNoCoolingSupplyAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, heatingSupplyAirFlowRate)
  VRF_FORWARD_BOOL(isHeatingSupplyAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isHeatingSupplyAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setHeatingSupplyAirFlowRate, heatingSupplyAirFlowRate)
  VRF_FORWARD_RESET(resetHeatingSupplyAirFlowRate)
  VRF_FORWARD_RESET(autosizeHeatingSupplyAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, noHeatingSupplyAirFlowRate)
  VRF_FORWARD_BOOL(isNoHeatingSupplyAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isNoHeatingSupplyAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setNoHeatingSupplyAirFlowRate, noHeatingSupplyAirFlowRate)
  VRF_FORWARD_RESET(resetNoHeatingSupplyAirFlowRate)
  VRF_FORWARD_RESET(autosizeNoHeatingSupplyAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, coolingOutdoorAirFlowRate)
  VRF_FORWARD_BOOL(isCoolingOutdoorAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isCoolingOutdoorAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setCoolingOutdoorAirFlowRate, coolingOutdoorAirFlowRate)
  VRF_FORWARD_RESET(resetCoolingOutdoorAirFlowRate)
  VRF_FORWARD_RESET(autosizeCoolingOutdoorAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, heatingOutdoorAirFlowRate)
  VRF_FORWARD_BOOL(isHeatingOutdoorAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isHeatingOutdoorAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setHeatingOutdoorAirFlowRate, heatingOutdoorAirFlowRate)
  VRF_FORWARD_RESET(resetHeatingOutdoorAirFlowRate)
  VRF_FORWARD_RESET(autosizeHeatingOutdoorAirFlowRate)

  VRF_FORWARD_GETTER(boost::optional<double>, noLoadOutdoorAirFlowRate)
  VRF_FORWARD_BOOL(isNoLoadOutdoorAirFlowRateDefaulted)
  VRF_FORWARD_BOOL(isNoLoadOutdoorAirFlowRateAutosized)
  VRF_FORWARD_SETTER(double, setNoLoadOutdoorAirFlowRate, noLoadOutdoorAirFlowRate)
  VRF_FORWARD_RESET(resetNoLoadOutdoorAirFlowRate)
  VRF_FORWARD_RESET(autosizeNoLoadOutdoorAirFlowRate)

  VRF_FORWARD_GETTER(std::string, outdoorAirMethod)
  VRF_FORWARD_BOOL(isOutdoorAirMethodDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setOutdoorAirMethod, outdoorAirMethod)
  VRF_FORWARD_RESET(resetOutdoorAirMethod)

  VRF_FORWARD_GETTER(double, outdoorAirFlowRateperPerson)
  VRF_FORWARD_BOOL(isOutdoorAirFlowRateperPersonDefaulted)
  VRF_FORWARD_SETTER(double, setOutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson)
  VRF_FORWARD_RESET(resetOutdoorAirFlowRateperPerson)

  VRF_FORWARD_GETTER(double, outdoorAirFlowRateperZoneFloorArea)
  VRF_FORWARD_BOOL(isOutdoorAirFlowRateperZoneFloorAreaDefaulted)
  VRF_FORWARD_SETTER(double, setOutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea)
  VRF_FORWARD_RESET(resetOutdoorAirFlowRateperZoneFloorArea)

  VRF_FORWARD_GETTER(double, outdoorAirFlowRateperZone)
  VRF_FORWARD_BOOL(isOutdoorAirFlowRateperZoneDefaulted)
  VRF_FORWARD_SETTER(double, setOutdoorAirFlowRateperZone, outdoorAirFlowRateperZone)
  VRF_FORWARD_RESET(resetOutdoorAirFlowRateperZone)

  VRF_FORWARD_GETTER(std::string, supplyAirFanplacement)
  VRF_FORWARD_BOOL(isSupplyAirFanplacementDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setSupplyAirFanplacement, supplyAirFanplacement)
  VRF_FORWARD_RESET(resetSupplyAirFanplacement)

  VRF_FORWARD_GETTER(double, supplyFanTotalEfficiency)
  VRF_FORWARD_BOOL(isSupplyFanTotalEfficiencyDefaulted)
  VRF_FORWARD_SETTER(double, setSupplyFanTotalEfficiency, supplyFanTotalEfficiency)
  VRF_FORWARD_RESET(resetSupplyFanTotalEfficiency)

  VRF_FORWARD_GETTER(double, supplyFanDeltaPressure)
  VRF_FORWARD_BOOL(isSupplyFanDeltaPressureDefaulted)
  VRF_FORWARD_SETTER(double, setSupplyFanDeltaPressure, supplyFanDeltaPressure)
  VRF_FORWARD_RESET(resetSupplyFanDeltaPressure)

  VRF_FORWARD_GETTER(double, supplyFanMotorEfficiency)
  VRF_FORWARD_BOOL(isSupplyFanMotorEfficiencyDefaulted)
  VRF_FORWARD_SETTER(double, setSupplyFanMotorEfficiency, supplyFanMotorEfficiency)
  VRF_FORWARD_RESET(resetSupplyFanMotorEfficiency)

  VRF_FORWARD_GETTER(std::string, coolingCoilType)
  VRF_FORWARD_BOOL(isCoolingCoilTypeDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setCoolingCoilType, coolingCoilType)
  VRF_FORWARD_RESET(resetCoolingCoilType)

  VRF_FORWARD_GETTER(boost::optional<double>, coolingCoilGrossRatedTotalCapacity)
  VRF_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityDefaulted)
  VRF_FORWARD_BOOL(isCoolingCoilGrossRatedTotalCapacityAutosized)
  VRF_FORWARD_SETTER(double, setCoolingCoilGrossRatedTotalCapacity, coolingCoilGrossRatedTotalCapacity)
  VRF_FORWARD_RESET(resetCoolingCoilGrossRatedTotalCapacity)
  VRF_FORWARD_RESET(autosizeCoolingCoilGrossRatedTotalCapacity)

  VRF_FORWARD_GETTER(boost::optional<double>, coolingCoilGrossRatedSensibleHeatRatio)
  VRF_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted)
  VRF_FORWARD_BOOL(isCoolingCoilGrossRatedSensibleHeatRatioAutosized)
  VRF_FORWARD_SETTER(double, setCoolingCoilGrossRatedSensibleHeatRatio, coolingCoilGrossRatedSensibleHeatRatio)
  VRF_FORWARD_RESET(resetCoolingCoilGrossRatedSensibleHeatRatio)
  VRF_FORWARD_RESET(autosizeCoolingCoilGrossRatedSensibleHeatRatio)

  VRF_FORWARD_GETTER(std::string, heatPumpHeatingCoilType)
  VRF_FORWARD_BOOL(isHeatPumpHeatingCoilTypeDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setHeatPumpHeatingCoilType, heatPumpHeatingCoilType)
  VRF_FORWARD_RESET(resetHeatPumpHeatingCoilType)

  VRF_FORWARD_GETTER(boost::optional<double>, heatPumpHeatingCoilGrossRatedCapacity)
  VRF_FORWARD_BOOL(isHeatPumpHeatingCoilGrossRatedCapacityDefaulted)
  VRF_FORWARD_BOOL(isHeatPumpHeatingCoilGrossRatedCapacityAutosized)
  VRF_FORWARD_SETTER(double, setHeatPumpHeatingCoilGrossRatedCapacity, heatPumpHeatingCoilGrossRatedCapacity)
  VRF_FORWARD_RESET(resetHeatPumpHeatingCoilGrossRatedCapacity)
  VRF_FORWARD_RESET(autosizeHeatPumpHeatingCoilGrossRatedCapacity)

  VRF_FORWARD_GETTER(double, zoneTerminalUnitOnParasiticElectricEnergyUse)
  VRF_FORWARD_BOOL(isZoneTerminalUnitOnParasiticElectricEnergyUseDefaulted)
  VRF_FORWARD_SETTER(double, setZoneTerminalUnitOnParasiticElectricEnergyUse, zoneTerminalUnitOnParasiticElectricEnergyUse)
  VRF_FORWARD_RESET(resetZoneTerminalUnitOnParasiticElectricEnergyUse)

  VRF_FORWARD_GETTER(double, zoneTerminalUnitOffParasiticElectricEnergyUse)
  VRF_FORWARD_BOOL(isZoneTerminalUnitOffParasiticElectricEnergyUseDefaulted)
  VRF_FORWARD_SETTER(double, setZoneTerminalUnitOffParasiticElectricEnergyUse, zoneTerminalUnitOffParasiticElectricEnergyUse)
  VRF_FORWARD_RESET(resetZoneTerminalUnitOffParasiticElectricEnergyUse)

  VRF_FORWARD_GETTER(std::string, zoneCoolingDesignSupplyAirTemperatureInputMethod)
  VRF_FORWARD_BOOL(isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setZoneCoolingDesignSupplyAirTemperatureInputMethod, zoneCoolingDesignSupplyAirTemperatureInputMethod)
  VRF_FORWARD_RESET(resetZoneCoolingDesignSupplyAirTemperatureInputMethod)

  VRF_FORWARD_GETTER(double, zoneCoolingDesignSupplyAirTemperature)
  VRF_FORWARD_BOOL(isZoneCoolingDesignSupplyAirTemperatureDefaulted)
  VRF_FORWARD_SETTER(double, setZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature)
  VRF_FORWARD_RESET(resetZoneCoolingDesignSupplyAirTemperature)

  VRF_FORWARD_GETTER(double, zoneCoolingDesignSupplyAirTemperatureDifference)
  VRF_FORWARD_BOOL(isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted)
  VRF_FORWARD_SETTER(double, setZoneCoolingDesignSupplyAirTemperatureDifference, zoneCoolingDesignSupplyAirTemperatureDifference)
  VRF_FORWARD_RESET(resetZoneCoolingDesignSupplyAirTemperatureDifference)

  VRF_FORWARD_GETTER(std::string, zoneHeatingDesignSupplyAirTemperatureInputMethod)
  VRF_FORWARD_BOOL(isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setZoneHeatingDesignSupplyAirTemperatureInputMethod, zoneHeatingDesignSupplyAirTemperatureInputMethod)
  VRF_FORWARD_RESET(resetZoneHeatingDesignSupplyAirTemperatureInputMethod)

  VRF_FORWARD_GETTER(double, zoneHeatingDesignSupplyAirTemperature)
  VRF_FORWARD_BOOL(isZoneHeatingDesignSupplyAirTemperatureDefaulted)
  VRF_FORWARD_SETTER(double, setZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature)
  VRF_FORWARD_RESET(resetZoneHeatingDesignSupplyAirTemperature)

  VRF_FORWARD_GETTER(double, zoneHeatingDesignSupplyAirTemperatureDifference)
  VRF_FORWARD_BOOL(isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted)
  VRF_FORWARD_SETTER(double, setZoneHeatingDesignSupplyAirTemperatureDifference, zoneHeatingDesignSupplyAirTemperatureDifference)
  VRF_FORWARD_RESET(resetZoneHeatingDesignSupplyAirTemperatureDifference)

  VRF_FORWARD_GETTER(std::string, baseboardHeatingType)
  VRF_FORWARD_BOOL(isBaseboardHeatingTypeDefaulted)
  VRF_FORWARD_SETTER(const std::string&, setBaseboardHeatingType, baseboardHeatingType)
  VRF_FORWARD_RESET(resetBaseboardHeatingType)

  VRF_FORWARD_GETTER(boost::optional<double>, baseboardHeatingCapacity)
  VRF_FORWARD_BOOL(isBaseboardHeatingCapacityDefaulted)
  VRF_FORWARD_BOOL(isBaseboardHeatingCapacityAutosized)
  VRF_FORWARD_SETTER(double, setBaseboardHeatingCapacity, baseboardHeatingCapacity)
  VRF_FORWARD_RESET(resetBaseboardHeatingCapacity)
  VRF_FORWARD_RESET(autosizeBaseboardHeatingCapacity)

#undef VRF_FORWARD_GETTER
#undef VRF_FORWARD_BOOL
#undef VRF_FORWARD_SETTER
#undef VRF_FORWARD_RESET

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

#define VRF_OPTIONAL_DOUBLE_GETTER(name, fieldEnum)                             \
  boost::optional<double> HVACTemplateZoneVRF_Impl::name() const {              \
    return getDouble(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, true); \
  }

#define VRF_REQUIRED_DOUBLE_GETTER(name, fieldEnum)                                   \
  double HVACTemplateZoneVRF_Impl::name() const {                                     \
    auto value = getDouble(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, true); \
    OS_ASSERT(value);                                                                 \
    return *value;                                                                    \
  }

#define VRF_REQUIRED_STRING_GETTER(name, fieldEnum)                                   \
  std::string HVACTemplateZoneVRF_Impl::name() const {                                \
    auto value = getString(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, true); \
    OS_ASSERT(value);                                                                 \
    return *value;                                                                    \
  }

    VRF_OPTIONAL_DOUBLE_GETTER(zoneHeatingSizingFactor, ZoneHeatingSizingFactor)
    VRF_OPTIONAL_DOUBLE_GETTER(zoneCoolingSizingFactor, ZoneCoolingSizingFactor)
    VRF_REQUIRED_DOUBLE_GETTER(ratedTotalHeatingCapacitySizingRatio, RatedTotalHeatingCapacitySizingRatio)
    VRF_OPTIONAL_DOUBLE_GETTER(coolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(noCoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(heatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(noHeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(coolingOutdoorAirFlowRate, CoolingOutdoorAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(heatingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate)
    VRF_OPTIONAL_DOUBLE_GETTER(noLoadOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate)
    VRF_REQUIRED_STRING_GETTER(outdoorAirMethod, OutdoorAirMethod)
    VRF_REQUIRED_DOUBLE_GETTER(outdoorAirFlowRateperPerson, OutdoorAirFlowRateperPerson)
    VRF_REQUIRED_DOUBLE_GETTER(outdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZoneFloorArea)
    VRF_REQUIRED_DOUBLE_GETTER(outdoorAirFlowRateperZone, OutdoorAirFlowRateperZone)
    VRF_REQUIRED_STRING_GETTER(supplyAirFanplacement, SupplyAirFanplacement)
    VRF_REQUIRED_DOUBLE_GETTER(supplyFanTotalEfficiency, SupplyFanTotalEfficiency)
    VRF_REQUIRED_DOUBLE_GETTER(supplyFanDeltaPressure, SupplyFanDeltaPressure)
    VRF_REQUIRED_DOUBLE_GETTER(supplyFanMotorEfficiency, SupplyFanMotorEfficiency)
    VRF_REQUIRED_STRING_GETTER(coolingCoilType, CoolingCoilType)
    VRF_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)
    VRF_OPTIONAL_DOUBLE_GETTER(coolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)
    VRF_REQUIRED_STRING_GETTER(heatPumpHeatingCoilType, HeatPumpHeatingCoilType)
    VRF_OPTIONAL_DOUBLE_GETTER(heatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)
    VRF_REQUIRED_DOUBLE_GETTER(zoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOnParasiticElectricEnergyUse)
    VRF_REQUIRED_DOUBLE_GETTER(zoneTerminalUnitOffParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse)
    VRF_REQUIRED_STRING_GETTER(zoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperatureInputMethod)
    VRF_REQUIRED_DOUBLE_GETTER(zoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperature)
    VRF_REQUIRED_DOUBLE_GETTER(zoneCoolingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirTemperatureDifference)
    VRF_REQUIRED_STRING_GETTER(zoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperatureInputMethod)
    VRF_REQUIRED_DOUBLE_GETTER(zoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperature)
    VRF_REQUIRED_DOUBLE_GETTER(zoneHeatingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureDifference)
    VRF_REQUIRED_STRING_GETTER(baseboardHeatingType, BaseboardHeatingType)
    VRF_OPTIONAL_DOUBLE_GETTER(baseboardHeatingCapacity, BaseboardHeatingCapacity)

#undef VRF_OPTIONAL_DOUBLE_GETTER
#undef VRF_REQUIRED_DOUBLE_GETTER
#undef VRF_REQUIRED_STRING_GETTER

#define VRF_DEFAULTED(name, fieldEnum)                                  \
  bool HVACTemplateZoneVRF_Impl::name() const {                         \
    return isEmpty(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum); \
  }

    VRF_DEFAULTED(isRatedTotalHeatingCapacitySizingRatioDefaulted, RatedTotalHeatingCapacitySizingRatio)
    VRF_DEFAULTED(isCoolingSupplyAirFlowRateDefaulted, CoolingSupplyAirFlowRate)
    VRF_DEFAULTED(isNoCoolingSupplyAirFlowRateDefaulted, NoCoolingSupplyAirFlowRate)
    VRF_DEFAULTED(isHeatingSupplyAirFlowRateDefaulted, HeatingSupplyAirFlowRate)
    VRF_DEFAULTED(isNoHeatingSupplyAirFlowRateDefaulted, NoHeatingSupplyAirFlowRate)
    VRF_DEFAULTED(isCoolingOutdoorAirFlowRateDefaulted, CoolingOutdoorAirFlowRate)
    VRF_DEFAULTED(isHeatingOutdoorAirFlowRateDefaulted, HeatingOutdoorAirFlowRate)
    VRF_DEFAULTED(isNoLoadOutdoorAirFlowRateDefaulted, NoLoadOutdoorAirFlowRate)
    VRF_DEFAULTED(isOutdoorAirMethodDefaulted, OutdoorAirMethod)
    VRF_DEFAULTED(isOutdoorAirFlowRateperPersonDefaulted, OutdoorAirFlowRateperPerson)
    VRF_DEFAULTED(isOutdoorAirFlowRateperZoneFloorAreaDefaulted, OutdoorAirFlowRateperZoneFloorArea)
    VRF_DEFAULTED(isOutdoorAirFlowRateperZoneDefaulted, OutdoorAirFlowRateperZone)
    VRF_DEFAULTED(isSupplyAirFanplacementDefaulted, SupplyAirFanplacement)
    VRF_DEFAULTED(isSupplyFanTotalEfficiencyDefaulted, SupplyFanTotalEfficiency)
    VRF_DEFAULTED(isSupplyFanDeltaPressureDefaulted, SupplyFanDeltaPressure)
    VRF_DEFAULTED(isSupplyFanMotorEfficiencyDefaulted, SupplyFanMotorEfficiency)
    VRF_DEFAULTED(isCoolingCoilTypeDefaulted, CoolingCoilType)
    VRF_DEFAULTED(isCoolingCoilGrossRatedTotalCapacityDefaulted, CoolingCoilGrossRatedTotalCapacity)
    VRF_DEFAULTED(isCoolingCoilGrossRatedSensibleHeatRatioDefaulted, CoolingCoilGrossRatedSensibleHeatRatio)
    VRF_DEFAULTED(isHeatPumpHeatingCoilTypeDefaulted, HeatPumpHeatingCoilType)
    VRF_DEFAULTED(isHeatPumpHeatingCoilGrossRatedCapacityDefaulted, HeatPumpHeatingCoilGrossRatedCapacity)
    VRF_DEFAULTED(isZoneTerminalUnitOnParasiticElectricEnergyUseDefaulted, ZoneTerminalUnitOnParasiticElectricEnergyUse)
    VRF_DEFAULTED(isZoneTerminalUnitOffParasiticElectricEnergyUseDefaulted, ZoneTerminalUnitOffParasiticElectricEnergyUse)
    VRF_DEFAULTED(isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted, ZoneCoolingDesignSupplyAirTemperatureInputMethod)
    VRF_DEFAULTED(isZoneCoolingDesignSupplyAirTemperatureDefaulted, ZoneCoolingDesignSupplyAirTemperature)
    VRF_DEFAULTED(isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted, ZoneCoolingDesignSupplyAirTemperatureDifference)
    VRF_DEFAULTED(isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted, ZoneHeatingDesignSupplyAirTemperatureInputMethod)
    VRF_DEFAULTED(isZoneHeatingDesignSupplyAirTemperatureDefaulted, ZoneHeatingDesignSupplyAirTemperature)
    VRF_DEFAULTED(isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted, ZoneHeatingDesignSupplyAirTemperatureDifference)
    VRF_DEFAULTED(isBaseboardHeatingTypeDefaulted, BaseboardHeatingType)
    VRF_DEFAULTED(isBaseboardHeatingCapacityDefaulted, BaseboardHeatingCapacity)

#undef VRF_DEFAULTED

#define VRF_AUTOSIZED(name, fieldEnum)                                                                        \
  bool HVACTemplateZoneVRF_Impl::name() const {                                                               \
    bool result = false;                                                                                      \
    boost::optional<std::string> value = getString(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, true); \
    if (value) {                                                                                              \
      result = openstudio::istringEqual(value.get(), "autosize");                                             \
    }                                                                                                         \
    return result;                                                                                            \
  }

    VRF_AUTOSIZED(isCoolingSupplyAirFlowRateAutosized, CoolingSupplyAirFlowRate)
    VRF_AUTOSIZED(isNoCoolingSupplyAirFlowRateAutosized, NoCoolingSupplyAirFlowRate)
    VRF_AUTOSIZED(isHeatingSupplyAirFlowRateAutosized, HeatingSupplyAirFlowRate)
    VRF_AUTOSIZED(isNoHeatingSupplyAirFlowRateAutosized, NoHeatingSupplyAirFlowRate)
    VRF_AUTOSIZED(isCoolingOutdoorAirFlowRateAutosized, CoolingOutdoorAirFlowRate)
    VRF_AUTOSIZED(isHeatingOutdoorAirFlowRateAutosized, HeatingOutdoorAirFlowRate)
    VRF_AUTOSIZED(isNoLoadOutdoorAirFlowRateAutosized, NoLoadOutdoorAirFlowRate)
    VRF_AUTOSIZED(isCoolingCoilGrossRatedTotalCapacityAutosized, CoolingCoilGrossRatedTotalCapacity)
    VRF_AUTOSIZED(isCoolingCoilGrossRatedSensibleHeatRatioAutosized, CoolingCoilGrossRatedSensibleHeatRatio)
    VRF_AUTOSIZED(isHeatPumpHeatingCoilGrossRatedCapacityAutosized, HeatPumpHeatingCoilGrossRatedCapacity)
    VRF_AUTOSIZED(isBaseboardHeatingCapacityAutosized, BaseboardHeatingCapacity)

#undef VRF_AUTOSIZED

#define VRF_SET_DOUBLE_CANFAIL(name, fieldEnum, arg)                           \
  bool HVACTemplateZoneVRF_Impl::name(double arg) {                            \
    return setDouble(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, arg); \
  }

#define VRF_SET_DOUBLE_ASSERT(name, fieldEnum, arg)                                         \
  bool HVACTemplateZoneVRF_Impl::name(double arg) {                                         \
    const bool result = setDouble(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, arg); \
    OS_ASSERT(result);                                                                      \
    return result;                                                                          \
  }

#define VRF_SET_STRING(name, fieldEnum, arg)                                   \
  bool HVACTemplateZoneVRF_Impl::name(const std::string& arg) {                \
    return setString(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, arg); \
  }

    VRF_SET_DOUBLE_CANFAIL(setZoneHeatingSizingFactor, ZoneHeatingSizingFactor, zoneHeatingSizingFactor)
    VRF_SET_DOUBLE_CANFAIL(setZoneCoolingSizingFactor, ZoneCoolingSizingFactor, zoneCoolingSizingFactor)
    VRF_SET_DOUBLE_CANFAIL(setRatedTotalHeatingCapacitySizingRatio, RatedTotalHeatingCapacitySizingRatio, ratedTotalHeatingCapacitySizingRatio)
    VRF_SET_DOUBLE_CANFAIL(setCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate, coolingSupplyAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setNoCoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate, noCoolingSupplyAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate, heatingSupplyAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setNoHeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate, noHeatingSupplyAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setCoolingOutdoorAirFlowRate, CoolingOutdoorAirFlowRate, coolingOutdoorAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setHeatingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, heatingOutdoorAirFlowRate)
    VRF_SET_DOUBLE_CANFAIL(setNoLoadOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, noLoadOutdoorAirFlowRate)
    VRF_SET_STRING(setOutdoorAirMethod, OutdoorAirMethod, outdoorAirMethod)
    VRF_SET_DOUBLE_ASSERT(setOutdoorAirFlowRateperPerson, OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson)
    VRF_SET_DOUBLE_ASSERT(setOutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea)
    VRF_SET_DOUBLE_ASSERT(setOutdoorAirFlowRateperZone, OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone)
    VRF_SET_STRING(setSupplyAirFanplacement, SupplyAirFanplacement, supplyAirFanplacement)
    VRF_SET_DOUBLE_CANFAIL(setSupplyFanTotalEfficiency, SupplyFanTotalEfficiency, supplyFanTotalEfficiency)
    VRF_SET_DOUBLE_CANFAIL(setSupplyFanDeltaPressure, SupplyFanDeltaPressure, supplyFanDeltaPressure)
    VRF_SET_DOUBLE_CANFAIL(setSupplyFanMotorEfficiency, SupplyFanMotorEfficiency, supplyFanMotorEfficiency)
    VRF_SET_STRING(setCoolingCoilType, CoolingCoilType, coolingCoilType)
    VRF_SET_DOUBLE_CANFAIL(setCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity, coolingCoilGrossRatedTotalCapacity)
    VRF_SET_DOUBLE_CANFAIL(setCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio, coolingCoilGrossRatedSensibleHeatRatio)
    VRF_SET_STRING(setHeatPumpHeatingCoilType, HeatPumpHeatingCoilType, heatPumpHeatingCoilType)
    VRF_SET_DOUBLE_CANFAIL(setHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity, heatPumpHeatingCoilGrossRatedCapacity)
    VRF_SET_DOUBLE_CANFAIL(setZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOnParasiticElectricEnergyUse,
                           zoneTerminalUnitOnParasiticElectricEnergyUse)
    VRF_SET_DOUBLE_CANFAIL(setZoneTerminalUnitOffParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse,
                           zoneTerminalUnitOffParasiticElectricEnergyUse)
    VRF_SET_STRING(setZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                   zoneCoolingDesignSupplyAirTemperatureInputMethod)
    VRF_SET_DOUBLE_ASSERT(setZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature)
    VRF_SET_DOUBLE_ASSERT(setZoneCoolingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirTemperatureDifference,
                          zoneCoolingDesignSupplyAirTemperatureDifference)
    VRF_SET_STRING(setZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                   zoneHeatingDesignSupplyAirTemperatureInputMethod)
    VRF_SET_DOUBLE_ASSERT(setZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature)
    VRF_SET_DOUBLE_ASSERT(setZoneHeatingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureDifference,
                          zoneHeatingDesignSupplyAirTemperatureDifference)
    VRF_SET_STRING(setBaseboardHeatingType, BaseboardHeatingType, baseboardHeatingType)
    VRF_SET_DOUBLE_ASSERT(setBaseboardHeatingCapacity, BaseboardHeatingCapacity, baseboardHeatingCapacity)

#undef VRF_SET_DOUBLE_CANFAIL
#undef VRF_SET_DOUBLE_ASSERT
#undef VRF_SET_STRING

#define VRF_RESET(name, fieldEnum)                                                         \
  void HVACTemplateZoneVRF_Impl::name() {                                                  \
    const bool result = setString(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, ""); \
    OS_ASSERT(result);                                                                     \
  }

#define VRF_AUTOSIZE(name, fieldEnum)                                                              \
  void HVACTemplateZoneVRF_Impl::name() {                                                          \
    const bool result = setString(openstudio::HVACTemplate_Zone_VRFFields::fieldEnum, "autosize"); \
    OS_ASSERT(result);                                                                             \
  }

    VRF_RESET(resetZoneHeatingSizingFactor, ZoneHeatingSizingFactor)
    VRF_RESET(resetZoneCoolingSizingFactor, ZoneCoolingSizingFactor)
    VRF_RESET(resetRatedTotalHeatingCapacitySizingRatio, RatedTotalHeatingCapacitySizingRatio)
    VRF_RESET(resetCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)
    VRF_AUTOSIZE(autosizeCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRate)
    VRF_RESET(resetNoCoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate)
    VRF_AUTOSIZE(autosizeNoCoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate)
    VRF_RESET(resetHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)
    VRF_AUTOSIZE(autosizeHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRate)
    VRF_RESET(resetNoHeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate)
    VRF_AUTOSIZE(autosizeNoHeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate)
    VRF_RESET(resetCoolingOutdoorAirFlowRate, CoolingOutdoorAirFlowRate)
    VRF_AUTOSIZE(autosizeCoolingOutdoorAirFlowRate, CoolingOutdoorAirFlowRate)
    VRF_RESET(resetHeatingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate)
    VRF_AUTOSIZE(autosizeHeatingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate)
    VRF_RESET(resetNoLoadOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate)
    VRF_AUTOSIZE(autosizeNoLoadOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate)
    VRF_RESET(resetOutdoorAirMethod, OutdoorAirMethod)
    VRF_RESET(resetOutdoorAirFlowRateperPerson, OutdoorAirFlowRateperPerson)
    VRF_RESET(resetOutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZoneFloorArea)
    VRF_RESET(resetOutdoorAirFlowRateperZone, OutdoorAirFlowRateperZone)
    VRF_RESET(resetSupplyAirFanplacement, SupplyAirFanplacement)
    VRF_RESET(resetSupplyFanTotalEfficiency, SupplyFanTotalEfficiency)
    VRF_RESET(resetSupplyFanDeltaPressure, SupplyFanDeltaPressure)
    VRF_RESET(resetSupplyFanMotorEfficiency, SupplyFanMotorEfficiency)
    VRF_RESET(resetCoolingCoilType, CoolingCoilType)
    VRF_RESET(resetCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)
    VRF_AUTOSIZE(autosizeCoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedTotalCapacity)
    VRF_RESET(resetCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)
    VRF_AUTOSIZE(autosizeCoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedSensibleHeatRatio)
    VRF_RESET(resetHeatPumpHeatingCoilType, HeatPumpHeatingCoilType)
    VRF_RESET(resetHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)
    VRF_AUTOSIZE(autosizeHeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCapacity)
    VRF_RESET(resetZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOnParasiticElectricEnergyUse)
    VRF_RESET(resetZoneTerminalUnitOffParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse)
    VRF_RESET(resetZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperatureInputMethod)
    VRF_RESET(resetZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperature)
    VRF_RESET(resetZoneCoolingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirTemperatureDifference)
    VRF_RESET(resetZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperatureInputMethod)
    VRF_RESET(resetZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperature)
    VRF_RESET(resetZoneHeatingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureDifference)
    VRF_RESET(resetBaseboardHeatingType, BaseboardHeatingType)
    VRF_RESET(resetBaseboardHeatingCapacity, BaseboardHeatingCapacity)
    VRF_AUTOSIZE(autosizeBaseboardHeatingCapacity, BaseboardHeatingCapacity)

#undef VRF_RESET
#undef VRF_AUTOSIZE

    std::vector<std::string> HVACTemplateZoneVRF_Impl::outdoorAirMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::outdoorAirMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::supplyAirFanplacementValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::supplyAirFanplacementValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::coolingCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::coolingCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::heatPumpHeatingCoilTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::heatPumpHeatingCoilTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneVRF_Impl::baseboardHeatingTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneVRF::baseboardHeatingTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
