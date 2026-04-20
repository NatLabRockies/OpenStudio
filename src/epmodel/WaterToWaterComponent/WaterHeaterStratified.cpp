/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/WaterHeaterStratified.hpp"
#include "WaterToWaterComponent/WaterHeaterStratified_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/WaterHeaterSizing.hpp"
#include "ModelObject/WaterHeaterSizing_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/Node_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPump_Impl.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser.hpp"
#include "ZoneHVACComponent/WaterHeaterHeatPumpWrappedCondenser_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WaterHeater_Stratified_FieldEnums.hxx>

#include <utility>

#include <set>
#include <stdexcept>

namespace openstudio {
namespace epmodel {

  WaterHeaterStratified::WaterHeaterStratified(const Model& model)
    : WaterToWaterComponent(WaterHeaterStratified::iddObjectType(), model) {
    setTankVolume(0.1893);
    setTankHeight(1.4);
    setTankShape("VerticalCylinder");
    setMaximumTemperatureLimit(82.22);
    setHeaterPriorityControl("MasterSlave");

    ScheduleConstant heater1Setpoint(model);
    ScheduleConstant heater2Setpoint(model);
    ScheduleConstant ambientSchedule(model);
    OS_ASSERT(heater1Setpoint.setValue(48.89));
    OS_ASSERT(heater2Setpoint.setValue(48.89));
    OS_ASSERT(ambientSchedule.setValue(22.0));

    OS_ASSERT(setHeater1SetpointTemperatureSchedule(heater1Setpoint));
    setHeater1DeadbandTemperatureDifference(2.0);
    setHeater1Capacity(4500.0);
    setHeater1Height(1.0);

    OS_ASSERT(setHeater2SetpointTemperatureSchedule(heater2Setpoint));
    setHeater2DeadbandTemperatureDifference(5.0);
    setHeater2Capacity(4500.0);
    setHeater2Height(0.0);

    setHeaterFuelType(FuelType::Electricity);
    setHeaterThermalEfficiency(0.98);
    setOffCycleParasiticFuelConsumptionRate(10.0);
    setOffCycleParasiticFuelType(FuelType::Electricity);
    setOffCycleParasiticHeatFractiontoTank(0.0);
    setOffCycleParasiticHeight(0.0);
    setOnCycleParasiticFuelConsumptionRate(10.0);
    setOnCycleParasiticFuelType(FuelType::Electricity);
    setOnCycleParasiticHeatFractiontoTank(0.0);
    setOnCycleParasiticHeight(0.0);
    setAmbientTemperatureIndicator("Schedule");
    OS_ASSERT(setAmbientTemperatureSchedule(ambientSchedule));
    setSkinLossFractiontoZone(1.0);
    setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(0.846);
    setOffCycleFlueLossCoefficienttoAmbientTemperature(0.0);
    setOffCycleFlueLossFractiontoZone(1.0);
    setUseSideEffectiveness(1.0);
    setUseSideInletHeight(0.0);
    autocalculateUseSideOutletHeight();
    setSourceSideEffectiveness(1.0);
    autocalculateSourceSideInletHeight();
    setSourceSideOutletHeight(0.0);
    setInletMode("Fixed");
    autosizeUseSideDesignFlowRate();
    autosizeSourceSideDesignFlowRate();
    setIndirectWaterHeatingRecoveryTime(1.5);
    setEndUseSubcategory("General");
    setNumberofNodes(6);
    setAdditionalDestratificationConductivity(0.1);
    setNode1AdditionalLossCoefficient(0.15);
    setNode2AdditionalLossCoefficient(0.0);
    setNode3AdditionalLossCoefficient(0.0);
    setNode4AdditionalLossCoefficient(0.0);
    setNode5AdditionalLossCoefficient(0.0);
    setNode6AdditionalLossCoefficient(0.1);
    setNode7AdditionalLossCoefficient(0.0);
    setNode8AdditionalLossCoefficient(0.0);
    setNode9AdditionalLossCoefficient(0.0);
    setNode10AdditionalLossCoefficient(0.0);
    setNode11AdditionalLossCoefficient(0.0);
    setNode12AdditionalLossCoefficient(0.0);
    setSourceSideFlowControlMode("IndirectHeatPrimarySetpoint");

    WaterHeaterSizing waterHeaterSizing(*this);
  }

  WaterHeaterStratified::WaterHeaterStratified(std::shared_ptr<detail::WaterHeaterStratified_Impl> impl)
    : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType WaterHeaterStratified::iddObjectType() {
    return IddObjectType::WaterHeater_Stratified;
  }

  std::vector<std::string> WaterHeaterStratified::tankShapeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::TankShape);
  }

  std::vector<std::string> WaterHeaterStratified::heaterPriorityControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::HeaterPriorityControl);
  }

  std::vector<std::string> WaterHeaterStratified::heaterFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::HeaterFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::offCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::OffCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::onCycleParasiticFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::OnCycleParasiticFuelType);
  }

  std::vector<std::string> WaterHeaterStratified::ambientTemperatureIndicatorValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator);
  }

  std::vector<std::string> WaterHeaterStratified::inletModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::WaterHeater_StratifiedFields::InletMode);
  }

  std::vector<std::string> WaterHeaterStratified::sourceSideFlowControlModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterHeater_StratifiedFields::SourceSideFlowControlMode);
  }

#define EPM_FORWARD_GET(ReturnType, Method)                         \
  ReturnType WaterHeaterStratified::Method() const {                \
    return getImpl<detail::WaterHeaterStratified_Impl>()->Method(); \
  }

#define EPM_FORWARD_SET(ReturnType, Method, ArgList, CallArgs)             \
  ReturnType WaterHeaterStratified::Method ArgList {                       \
    return getImpl<detail::WaterHeaterStratified_Impl>()->Method CallArgs; \
  }

#define EPM_FORWARD_VOID(Method, ArgList, CallArgs)                 \
  void WaterHeaterStratified::Method ArgList {                      \
    getImpl<detail::WaterHeaterStratified_Impl>()->Method CallArgs; \
  }

  EPM_FORWARD_GET(std::string, endUseSubcategory)
  EPM_FORWARD_SET(bool, setEndUseSubcategory, (const std::string& endUseSubcategory), (endUseSubcategory))

  EPM_FORWARD_GET(boost::optional<double>, tankVolume)
  EPM_FORWARD_SET(bool, setTankVolume, (double tankVolume), (tankVolume))
  EPM_FORWARD_VOID(autosizeTankVolume, (), ())
  EPM_FORWARD_GET(bool, isTankVolumeAutosized)
  EPM_FORWARD_GET(boost::optional<double>, autosizedTankVolume)

  EPM_FORWARD_GET(boost::optional<double>, tankHeight)
  EPM_FORWARD_SET(bool, setTankHeight, (double tankHeight), (tankHeight))
  EPM_FORWARD_VOID(autosizeTankHeight, (), ())
  EPM_FORWARD_GET(bool, isTankHeightAutosized)
  EPM_FORWARD_GET(boost::optional<double>, autosizedTankHeight)

  EPM_FORWARD_GET(std::string, tankShape)
  EPM_FORWARD_SET(bool, setTankShape, (const std::string& tankShape), (tankShape))

  EPM_FORWARD_GET(boost::optional<double>, tankPerimeter)
  EPM_FORWARD_SET(bool, setTankPerimeter, (double tankPerimeter), (tankPerimeter))
  EPM_FORWARD_VOID(resetTankPerimeter, (), ())

  EPM_FORWARD_GET(double, maximumTemperatureLimit)
  EPM_FORWARD_SET(bool, setMaximumTemperatureLimit, (double maximumTemperatureLimit), (maximumTemperatureLimit))

  EPM_FORWARD_GET(std::string, heaterPriorityControl)
  EPM_FORWARD_SET(bool, setHeaterPriorityControl, (const std::string& heaterPriorityControl), (heaterPriorityControl))

  EPM_FORWARD_GET(boost::optional<Schedule>, heater1SetpointTemperatureSchedule)
  EPM_FORWARD_SET(bool, setHeater1SetpointTemperatureSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetHeater1SetpointTemperatureSchedule, (), ())

  EPM_FORWARD_GET(double, heater1DeadbandTemperatureDifference)
  EPM_FORWARD_SET(bool, setHeater1DeadbandTemperatureDifference, (double heater1DeadbandTemperatureDifference),
                  (heater1DeadbandTemperatureDifference))

  EPM_FORWARD_GET(boost::optional<double>, heater1Capacity)
  EPM_FORWARD_SET(bool, setHeater1Capacity, (double heater1Capacity), (heater1Capacity))
  EPM_FORWARD_VOID(autosizeHeater1Capacity, (), ())
  EPM_FORWARD_GET(bool, isHeater1CapacityAutosized)
  EPM_FORWARD_GET(boost::optional<double>, autosizedHeater1Capacity)

  EPM_FORWARD_GET(double, heater1Height)
  EPM_FORWARD_SET(bool, setHeater1Height, (double heater1Height), (heater1Height))

  EPM_FORWARD_GET(boost::optional<Schedule>, heater2SetpointTemperatureSchedule)
  EPM_FORWARD_SET(bool, setHeater2SetpointTemperatureSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetHeater2SetpointTemperatureSchedule, (), ())

  EPM_FORWARD_GET(double, heater2DeadbandTemperatureDifference)
  EPM_FORWARD_SET(bool, setHeater2DeadbandTemperatureDifference, (double heater2DeadbandTemperatureDifference),
                  (heater2DeadbandTemperatureDifference))

  EPM_FORWARD_GET(double, heater2Capacity)
  EPM_FORWARD_SET(bool, setHeater2Capacity, (double heater2Capacity), (heater2Capacity))

  EPM_FORWARD_GET(double, heater2Height)
  EPM_FORWARD_SET(bool, setHeater2Height, (double heater2Height), (heater2Height))

  EPM_FORWARD_GET(std::string, heaterFuelType)

  EPM_FORWARD_GET(double, heaterThermalEfficiency)
  EPM_FORWARD_SET(bool, setHeaterThermalEfficiency, (double heaterThermalEfficiency), (heaterThermalEfficiency))

  EPM_FORWARD_GET(double, offCycleParasiticFuelConsumptionRate)
  EPM_FORWARD_SET(bool, setOffCycleParasiticFuelConsumptionRate, (double offCycleParasiticFuelConsumptionRate),
                  (offCycleParasiticFuelConsumptionRate))

  EPM_FORWARD_GET(std::string, offCycleParasiticFuelType)

  EPM_FORWARD_GET(double, offCycleParasiticHeatFractiontoTank)
  EPM_FORWARD_SET(bool, setOffCycleParasiticHeatFractiontoTank, (double offCycleParasiticHeatFractiontoTank), (offCycleParasiticHeatFractiontoTank))

  EPM_FORWARD_GET(double, offCycleParasiticHeight)
  EPM_FORWARD_SET(bool, setOffCycleParasiticHeight, (double offCycleParasiticHeight), (offCycleParasiticHeight))

  EPM_FORWARD_GET(double, onCycleParasiticFuelConsumptionRate)
  EPM_FORWARD_SET(bool, setOnCycleParasiticFuelConsumptionRate, (double onCycleParasiticFuelConsumptionRate), (onCycleParasiticFuelConsumptionRate))

  EPM_FORWARD_GET(std::string, onCycleParasiticFuelType)

  EPM_FORWARD_GET(double, onCycleParasiticHeatFractiontoTank)
  EPM_FORWARD_SET(bool, setOnCycleParasiticHeatFractiontoTank, (double onCycleParasiticHeatFractiontoTank), (onCycleParasiticHeatFractiontoTank))

  EPM_FORWARD_GET(double, onCycleParasiticHeight)
  EPM_FORWARD_SET(bool, setOnCycleParasiticHeight, (double onCycleParasiticHeight), (onCycleParasiticHeight))

  EPM_FORWARD_GET(std::string, ambientTemperatureIndicator)
  EPM_FORWARD_SET(bool, setAmbientTemperatureIndicator, (const std::string& ambientTemperatureIndicator), (ambientTemperatureIndicator))

  EPM_FORWARD_GET(boost::optional<Schedule>, ambientTemperatureSchedule)
  EPM_FORWARD_SET(bool, setAmbientTemperatureSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetAmbientTemperatureSchedule, (), ())

  EPM_FORWARD_GET(boost::optional<ThermalZone>, ambientTemperatureThermalZone)
  EPM_FORWARD_SET(bool, setAmbientTemperatureThermalZone, (const ThermalZone& thermalZone), (thermalZone))
  EPM_FORWARD_VOID(resetAmbientTemperatureThermalZone, (), ())

  EPM_FORWARD_GET(boost::optional<std::string>, ambientTemperatureOutdoorAirNodeName)
  EPM_FORWARD_SET(bool, setAmbientTemperatureOutdoorAirNodeName, (const std::string& ambientTemperatureOutdoorAirNodeName),
                  (ambientTemperatureOutdoorAirNodeName))
  EPM_FORWARD_VOID(resetAmbientTemperatureOutdoorAirNodeName, (), ())

  EPM_FORWARD_GET(boost::optional<double>, uniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
  EPM_FORWARD_SET(bool, setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature,
                  (double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature), (uniformSkinLossCoefficientperUnitAreatoAmbientTemperature))
  EPM_FORWARD_VOID(resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature, (), ())

  EPM_FORWARD_GET(double, skinLossFractiontoZone)
  EPM_FORWARD_SET(bool, setSkinLossFractiontoZone, (double skinLossFractiontoZone), (skinLossFractiontoZone))

  EPM_FORWARD_GET(boost::optional<double>, offCycleFlueLossCoefficienttoAmbientTemperature)
  EPM_FORWARD_SET(bool, setOffCycleFlueLossCoefficienttoAmbientTemperature, (double offCycleFlueLossCoefficienttoAmbientTemperature),
                  (offCycleFlueLossCoefficienttoAmbientTemperature))
  EPM_FORWARD_VOID(resetOffCycleFlueLossCoefficienttoAmbientTemperature, (), ())

  EPM_FORWARD_GET(double, offCycleFlueLossFractiontoZone)
  EPM_FORWARD_SET(bool, setOffCycleFlueLossFractiontoZone, (double offCycleFlueLossFractiontoZone), (offCycleFlueLossFractiontoZone))

  EPM_FORWARD_GET(boost::optional<double>, peakUseFlowRate)
  EPM_FORWARD_SET(bool, setPeakUseFlowRate, (double peakUseFlowRate), (peakUseFlowRate))
  EPM_FORWARD_VOID(resetPeakUseFlowRate, (), ())

  EPM_FORWARD_GET(boost::optional<Schedule>, useFlowRateFractionSchedule)
  EPM_FORWARD_SET(bool, setUseFlowRateFractionSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetUseFlowRateFractionSchedule, (), ())

  EPM_FORWARD_GET(boost::optional<Schedule>, coldWaterSupplyTemperatureSchedule)
  EPM_FORWARD_SET(bool, setColdWaterSupplyTemperatureSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetColdWaterSupplyTemperatureSchedule, (), ())

  EPM_FORWARD_GET(double, useSideEffectiveness)
  EPM_FORWARD_SET(bool, setUseSideEffectiveness, (double useSideEffectiveness), (useSideEffectiveness))

  EPM_FORWARD_GET(double, useSideInletHeight)
  EPM_FORWARD_SET(bool, setUseSideInletHeight, (double useSideInletHeight), (useSideInletHeight))

  EPM_FORWARD_GET(boost::optional<double>, useSideOutletHeight)
  EPM_FORWARD_SET(bool, setUseSideOutletHeight, (double useSideOutletHeight), (useSideOutletHeight))
  EPM_FORWARD_VOID(autocalculateUseSideOutletHeight, (), ())
  EPM_FORWARD_GET(bool, isUseSideOutletHeightAutocalculated)

  EPM_FORWARD_GET(double, sourceSideEffectiveness)
  EPM_FORWARD_SET(bool, setSourceSideEffectiveness, (double sourceSideEffectiveness), (sourceSideEffectiveness))

  EPM_FORWARD_GET(boost::optional<double>, sourceSideInletHeight)
  EPM_FORWARD_SET(bool, setSourceSideInletHeight, (double sourceSideInletHeight), (sourceSideInletHeight))
  EPM_FORWARD_VOID(autocalculateSourceSideInletHeight, (), ())
  EPM_FORWARD_GET(bool, isSourceSideInletHeightAutocalculated)

  EPM_FORWARD_GET(double, sourceSideOutletHeight)
  EPM_FORWARD_SET(bool, setSourceSideOutletHeight, (double sourceSideOutletHeight), (sourceSideOutletHeight))

  EPM_FORWARD_GET(std::string, inletMode)
  EPM_FORWARD_SET(bool, setInletMode, (const std::string& inletMode), (inletMode))

  EPM_FORWARD_GET(boost::optional<double>, useSideDesignFlowRate)
  EPM_FORWARD_SET(bool, setUseSideDesignFlowRate, (double useSideDesignFlowRate), (useSideDesignFlowRate))
  EPM_FORWARD_VOID(autosizeUseSideDesignFlowRate, (), ())
  EPM_FORWARD_GET(bool, isUseSideDesignFlowRateAutosized)
  EPM_FORWARD_GET(boost::optional<double>, autosizedUseSideDesignFlowRate)

  EPM_FORWARD_GET(boost::optional<double>, sourceSideDesignFlowRate)
  EPM_FORWARD_SET(bool, setSourceSideDesignFlowRate, (double sourceSideDesignFlowRate), (sourceSideDesignFlowRate))
  EPM_FORWARD_VOID(autosizeSourceSideDesignFlowRate, (), ())
  EPM_FORWARD_GET(bool, isSourceSideDesignFlowRateAutosized)
  EPM_FORWARD_GET(boost::optional<double>, autosizedSourceSideDesignFlowRate)

  EPM_FORWARD_GET(double, indirectWaterHeatingRecoveryTime)
  EPM_FORWARD_SET(bool, setIndirectWaterHeatingRecoveryTime, (double indirectWaterHeatingRecoveryTime), (indirectWaterHeatingRecoveryTime))

  EPM_FORWARD_GET(int, numberofNodes)
  EPM_FORWARD_SET(bool, setNumberofNodes, (int numberofNodes), (numberofNodes))

  EPM_FORWARD_GET(double, additionalDestratificationConductivity)
  EPM_FORWARD_SET(bool, setAdditionalDestratificationConductivity, (double additionalDestratificationConductivity),
                  (additionalDestratificationConductivity))

  EPM_FORWARD_GET(double, node1AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode1AdditionalLossCoefficient, (double node1AdditionalLossCoefficient), (node1AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node2AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode2AdditionalLossCoefficient, (double node2AdditionalLossCoefficient), (node2AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node3AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode3AdditionalLossCoefficient, (double node3AdditionalLossCoefficient), (node3AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node4AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode4AdditionalLossCoefficient, (double node4AdditionalLossCoefficient), (node4AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node5AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode5AdditionalLossCoefficient, (double node5AdditionalLossCoefficient), (node5AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node6AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode6AdditionalLossCoefficient, (double node6AdditionalLossCoefficient), (node6AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node7AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode7AdditionalLossCoefficient, (double node7AdditionalLossCoefficient), (node7AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node8AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode8AdditionalLossCoefficient, (double node8AdditionalLossCoefficient), (node8AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node9AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode9AdditionalLossCoefficient, (double node9AdditionalLossCoefficient), (node9AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node10AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode10AdditionalLossCoefficient, (double node10AdditionalLossCoefficient), (node10AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node11AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode11AdditionalLossCoefficient, (double node11AdditionalLossCoefficient), (node11AdditionalLossCoefficient))

  EPM_FORWARD_GET(double, node12AdditionalLossCoefficient)
  EPM_FORWARD_SET(bool, setNode12AdditionalLossCoefficient, (double node12AdditionalLossCoefficient), (node12AdditionalLossCoefficient))

  EPM_FORWARD_GET(std::string, sourceSideFlowControlMode)
  EPM_FORWARD_SET(bool, setSourceSideFlowControlMode, (const std::string& sourceSideFlowControlMode), (sourceSideFlowControlMode))

  EPM_FORWARD_GET(boost::optional<Schedule>, indirectAlternateSetpointTemperatureSchedule)
  EPM_FORWARD_SET(bool, setIndirectAlternateSetpointTemperatureSchedule, (Schedule& schedule), (schedule))
  EPM_FORWARD_VOID(resetIndirectAlternateSetpointTemperatureSchedule, (), ())

  EPM_FORWARD_GET(WaterHeaterSizing, waterHeaterSizing)

  ModelObject WaterHeaterStratified::clone(Model model) const {
    return getImpl<detail::WaterHeaterStratified_Impl>()->clone(model);
  }
  EPM_FORWARD_SET(bool, addToSourceSideNode, (Node& node), (node))

  boost::optional<PlantLoop> WaterHeaterStratified::useSidePlantLoop() const {
    return plantLoop();
  }

  boost::optional<PlantLoop> WaterHeaterStratified::sourceSidePlantLoop() const {
    return secondaryPlantLoop();
  }

  bool WaterHeaterStratified::removeFromSourceSidePlantLoop() {
    return removeFromSecondaryPlantLoop();
  }

  boost::optional<ModelObject> WaterHeaterStratified::useSideInletModelObject() const {
    return supplyInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::useSideOutletModelObject() const {
    return supplyOutletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::sourceSideInletModelObject() const {
    return demandInletModelObject();
  }

  boost::optional<ModelObject> WaterHeaterStratified::sourceSideOutletModelObject() const {
    return demandOutletModelObject();
  }

  bool WaterHeaterStratified::setHeaterFuelType(const FuelType& heaterFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setHeaterFuelType(heaterFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setHeaterFuelType(const std::string& heaterFuelType) {
    try {
      return setHeaterFuelType(FuelType{heaterFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  bool WaterHeaterStratified::setOffCycleParasiticFuelType(const FuelType& offCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOffCycleParasiticFuelType(offCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setOffCycleParasiticFuelType(const std::string& offCycleParasiticFuelType) {
    try {
      return setOffCycleParasiticFuelType(FuelType{offCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

  bool WaterHeaterStratified::setOnCycleParasiticFuelType(const FuelType& onCycleParasiticFuelType) {
    return getImpl<detail::WaterHeaterStratified_Impl>()->setOnCycleParasiticFuelType(onCycleParasiticFuelType.valueDescription());
  }

  bool WaterHeaterStratified::setOnCycleParasiticFuelType(const std::string& onCycleParasiticFuelType) {
    try {
      return setOnCycleParasiticFuelType(FuelType{onCycleParasiticFuelType});
    } catch (const std::runtime_error&) {
      return false;
    }
  }

#undef EPM_FORWARD_GET
#undef EPM_FORWARD_SET
#undef EPM_FORWARD_VOID

  namespace detail {

    namespace {

      bool isAutosize(const ModelObject_Impl& impl, int fieldIndex) {
        if (auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autosize");
        }
        return false;
      }

      bool isAutocalculate(const ModelObject_Impl& impl, int fieldIndex) {
        if (auto value = impl.getString(fieldIndex, true)) {
          return openstudio::istringEqual(*value, "autocalculate");
        }
        return false;
      }

    }  // namespace

    std::vector<ModelObject> WaterHeaterStratified_Impl::children() const {
      return {waterHeaterSizing()};
    }

    ModelObject WaterHeaterStratified_Impl::clone(Model model) const {
      auto heaterCloneObject = model.addObject(idfObject());
      OS_ASSERT(heaterCloneObject);
      auto heaterClone = heaterCloneObject->cast<WaterHeaterStratified>();

      OS_ASSERT(heaterClone.setString(heaterClone.supplyInletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.supplyOutletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.demandInletPort(), ""));
      OS_ASSERT(heaterClone.setString(heaterClone.demandOutletPort(), ""));

      auto sizingCloneObject = model.addObject(waterHeaterSizing().idfObject());
      OS_ASSERT(sizingCloneObject);
      auto sizingClone = sizingCloneObject->cast<WaterHeaterSizing>();
      OS_ASSERT(sizingClone.getImpl<WaterHeaterSizing_Impl>()->setWaterHeater(heaterClone));

      return heaterClone;
    }

#define OS_IMPL_OPTIONAL_DOUBLE(method, field)                               \
  boost::optional<double> WaterHeaterStratified_Impl::method() const {       \
    return getDouble(openstudio::WaterHeater_StratifiedFields::field, true); \
  }

#define OS_IMPL_REQUIRED_DOUBLE(method, field)                                           \
  double WaterHeaterStratified_Impl::method() const {                                    \
    const auto value = getDouble(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                    \
    return *value;                                                                       \
  }

#define OS_IMPL_OPTIONAL_STRING(method, field)                                     \
  boost::optional<std::string> WaterHeaterStratified_Impl::method() const {        \
    return getString(openstudio::WaterHeater_StratifiedFields::field, true, true); \
  }

#define OS_IMPL_REQUIRED_STRING(method, field)                                           \
  std::string WaterHeaterStratified_Impl::method() const {                               \
    const auto value = getString(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                    \
    return *value;                                                                       \
  }

#define OS_IMPL_IS_AUTOSIZED(method, field)                                    \
  bool WaterHeaterStratified_Impl::method() const {                            \
    return isAutosize(*this, openstudio::WaterHeater_StratifiedFields::field); \
  }

#define OS_IMPL_IS_AUTOCALCULATED(method, field)                                    \
  bool WaterHeaterStratified_Impl::method() const {                                 \
    return isAutocalculate(*this, openstudio::WaterHeater_StratifiedFields::field); \
  }

#define OS_IMPL_SET_DOUBLE(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(double value) {                     \
    return setDouble(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_SET_STRING(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(const std::string& value) {         \
    return setString(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_SET_INT(method, field)                                     \
  bool WaterHeaterStratified_Impl::method(int value) {                     \
    return setInt(openstudio::WaterHeater_StratifiedFields::field, value); \
  }

#define OS_IMPL_REQUIRED_INT(method, field)                                           \
  int WaterHeaterStratified_Impl::method() const {                                    \
    const auto value = getInt(openstudio::WaterHeater_StratifiedFields::field, true); \
    OS_ASSERT(value);                                                                 \
    return *value;                                                                    \
  }

#define OS_IMPL_RESET(method, field)                                                    \
  void WaterHeaterStratified_Impl::method() {                                           \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, ""); \
    OS_ASSERT(result);                                                                  \
  }

#define OS_IMPL_AUTOSIZE(method, field)                                                         \
  void WaterHeaterStratified_Impl::method() {                                                   \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, "autosize"); \
    OS_ASSERT(result);                                                                          \
  }

#define OS_IMPL_AUTOCALCULATE(method, field)                                                         \
  void WaterHeaterStratified_Impl::method() {                                                        \
    const bool result = setString(openstudio::WaterHeater_StratifiedFields::field, "autocalculate"); \
    OS_ASSERT(result);                                                                               \
  }

    OS_IMPL_OPTIONAL_DOUBLE(tankVolume, TankVolume)
    OS_IMPL_IS_AUTOSIZED(isTankVolumeAutosized, TankVolume)
    OS_IMPL_OPTIONAL_DOUBLE(tankHeight, TankHeight)
    OS_IMPL_IS_AUTOSIZED(isTankHeightAutosized, TankHeight)
    OS_IMPL_REQUIRED_STRING(tankShape, TankShape)
    OS_IMPL_OPTIONAL_DOUBLE(tankPerimeter, TankPerimeter)
    OS_IMPL_REQUIRED_DOUBLE(maximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_REQUIRED_STRING(heaterPriorityControl, HeaterPriorityControl)
    boost::optional<Schedule> WaterHeaterStratified_Impl::heater1SetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(heater1DeadbandTemperatureDifference, Heater1DeadbandTemperatureDifference)
    OS_IMPL_OPTIONAL_DOUBLE(heater1Capacity, Heater1Capacity)
    OS_IMPL_IS_AUTOSIZED(isHeater1CapacityAutosized, Heater1Capacity)
    OS_IMPL_REQUIRED_DOUBLE(heater1Height, Heater1Height)
    boost::optional<Schedule> WaterHeaterStratified_Impl::heater2SetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(heater2DeadbandTemperatureDifference, Heater2DeadbandTemperatureDifference)
    OS_IMPL_REQUIRED_DOUBLE(heater2Capacity, Heater2Capacity)
    OS_IMPL_REQUIRED_DOUBLE(heater2Height, Heater2Height)
    OS_IMPL_REQUIRED_STRING(heaterFuelType, HeaterFuelType)
    OS_IMPL_REQUIRED_DOUBLE(heaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_REQUIRED_STRING(offCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_REQUIRED_DOUBLE(offCycleParasiticHeight, OffCycleParasiticHeight)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_REQUIRED_STRING(onCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_REQUIRED_DOUBLE(onCycleParasiticHeight, OnCycleParasiticHeight)
    std::string WaterHeaterStratified_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::WaterHeater_StratifiedFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }
    std::string WaterHeaterStratified_Impl::ambientTemperatureIndicator() const {
      const auto value = getString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator, true);
      OS_ASSERT(value);
      if (openstudio::istringEqual(*value, "Zone")) {
        return "ThermalZone";
      }
      return *value;
    }
    boost::optional<Schedule> WaterHeaterStratified_Impl::ambientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName);
    }
    boost::optional<ThermalZone> WaterHeaterStratified_Impl::ambientTemperatureThermalZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName);
    }
    OS_IMPL_OPTIONAL_STRING(ambientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_OPTIONAL_DOUBLE(uniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(skinLossFractiontoZone, SkinLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(offCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_REQUIRED_DOUBLE(offCycleFlueLossFractiontoZone, OffCycleFlueLossFractiontoZone)
    OS_IMPL_OPTIONAL_DOUBLE(peakUseFlowRate, PeakUseFlowRate)
    boost::optional<Schedule> WaterHeaterStratified_Impl::useFlowRateFractionSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName);
    }
    boost::optional<Schedule> WaterHeaterStratified_Impl::coldWaterSupplyTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName);
    }
    OS_IMPL_REQUIRED_DOUBLE(useSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_REQUIRED_DOUBLE(useSideInletHeight, UseSideInletHeight)
    OS_IMPL_OPTIONAL_DOUBLE(useSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_IS_AUTOCALCULATED(isUseSideOutletHeightAutocalculated, UseSideOutletHeight)
    OS_IMPL_REQUIRED_DOUBLE(sourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_OPTIONAL_DOUBLE(sourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_IS_AUTOCALCULATED(isSourceSideInletHeightAutocalculated, SourceSideInletHeight)
    OS_IMPL_REQUIRED_DOUBLE(sourceSideOutletHeight, SourceSideOutletHeight)
    OS_IMPL_REQUIRED_STRING(inletMode, InletMode)
    OS_IMPL_OPTIONAL_DOUBLE(useSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_IS_AUTOSIZED(isUseSideDesignFlowRateAutosized, UseSideDesignFlowRate)
    OS_IMPL_OPTIONAL_DOUBLE(sourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_IS_AUTOSIZED(isSourceSideDesignFlowRateAutosized, SourceSideDesignFlowRate)
    OS_IMPL_REQUIRED_DOUBLE(indirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_REQUIRED_INT(numberofNodes, NumberofNodes)
    OS_IMPL_REQUIRED_DOUBLE(additionalDestratificationConductivity, AdditionalDestratificationConductivity)
    OS_IMPL_REQUIRED_DOUBLE(node1AdditionalLossCoefficient, Node1AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node2AdditionalLossCoefficient, Node2AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node3AdditionalLossCoefficient, Node3AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node4AdditionalLossCoefficient, Node4AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node5AdditionalLossCoefficient, Node5AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node6AdditionalLossCoefficient, Node6AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node7AdditionalLossCoefficient, Node7AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node8AdditionalLossCoefficient, Node8AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node9AdditionalLossCoefficient, Node9AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node10AdditionalLossCoefficient, Node10AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node11AdditionalLossCoefficient, Node11AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_DOUBLE(node12AdditionalLossCoefficient, Node12AdditionalLossCoefficient)
    OS_IMPL_REQUIRED_STRING(sourceSideFlowControlMode, SourceSideFlowControlMode)
    boost::optional<Schedule> WaterHeaterStratified_Impl::indirectAlternateSetpointTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName);
    }

    boost::optional<double> WaterHeaterStratified_Impl::autosizedTankVolume() const {
      return getAutosizedValue("Design Size Tank Volume", "m3");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedTankHeight() const {
      return getAutosizedValue("Design Size Tank Height", "m");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedHeater1Capacity() const {
      return getAutosizedValue("Design Size Heater 1 Capacity", "W");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedUseSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Use Side Design Flow Rate", "m3/s");
    }
    boost::optional<double> WaterHeaterStratified_Impl::autosizedSourceSideDesignFlowRate() const {
      return getAutosizedValue("Design Size Source Side Design Flow Rate", "m3/s");
    }

    OS_IMPL_SET_STRING(setEndUseSubcategory, EndUseSubcategory)
    OS_IMPL_SET_DOUBLE(setTankVolume, TankVolume)
    OS_IMPL_AUTOSIZE(autosizeTankVolume, TankVolume)
    OS_IMPL_SET_DOUBLE(setTankHeight, TankHeight)
    OS_IMPL_AUTOSIZE(autosizeTankHeight, TankHeight)
    OS_IMPL_SET_STRING(setTankShape, TankShape)
    OS_IMPL_SET_DOUBLE(setTankPerimeter, TankPerimeter)
    OS_IMPL_RESET(resetTankPerimeter, TankPerimeter)
    OS_IMPL_SET_DOUBLE(setMaximumTemperatureLimit, MaximumTemperatureLimit)
    OS_IMPL_SET_STRING(setHeaterPriorityControl, HeaterPriorityControl)
    bool WaterHeaterStratified_Impl::setHeater1SetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Heater 1 Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetHeater1SetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setHeater1DeadbandTemperatureDifference, Heater1DeadbandTemperatureDifference)
    OS_IMPL_SET_DOUBLE(setHeater1Capacity, Heater1Capacity)
    OS_IMPL_AUTOSIZE(autosizeHeater1Capacity, Heater1Capacity)
    OS_IMPL_SET_DOUBLE(setHeater1Height, Heater1Height)
    bool WaterHeaterStratified_Impl::setHeater2SetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Heater 2 Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetHeater2SetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setHeater2DeadbandTemperatureDifference, Heater2DeadbandTemperatureDifference)
    OS_IMPL_SET_DOUBLE(setHeater2Capacity, Heater2Capacity)
    OS_IMPL_SET_DOUBLE(setHeater2Height, Heater2Height)
    OS_IMPL_SET_STRING(setHeaterFuelType, HeaterFuelType)
    OS_IMPL_SET_DOUBLE(setHeaterThermalEfficiency, HeaterThermalEfficiency)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOffCycleParasiticFuelType, OffCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOffCycleParasiticHeight, OffCycleParasiticHeight)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelConsumptionRate)
    OS_IMPL_SET_STRING(setOnCycleParasiticFuelType, OnCycleParasiticFuelType)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeatFractiontoTank)
    OS_IMPL_SET_DOUBLE(setOnCycleParasiticHeight, OnCycleParasiticHeight)
    bool WaterHeaterStratified_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
      auto normalized = ambientTemperatureIndicator;
      if (openstudio::istringEqual(ambientTemperatureIndicator, "ThermalZone")) {
        normalized = "Zone";
      }
      return setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureIndicator, normalized);
    }
    bool WaterHeaterStratified_Impl::setAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, "WaterHeaterStratified",
                         "Ambient Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetAmbientTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, ""));
    }
    bool WaterHeaterStratified_Impl::setAmbientTemperatureThermalZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName, thermalZone.handle());
    }
    void WaterHeaterStratified_Impl::resetAmbientTemperatureThermalZone() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::AmbientTemperatureZoneName, ""));
    }
    OS_IMPL_SET_STRING(setAmbientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_RESET(resetAmbientTemperatureOutdoorAirNodeName, AmbientTemperatureOutdoorAirNodeName)
    OS_IMPL_SET_DOUBLE(setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_RESET(resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setSkinLossFractiontoZone, SkinLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setOffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_RESET(resetOffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossCoefficienttoAmbientTemperature)
    OS_IMPL_SET_DOUBLE(setOffCycleFlueLossFractiontoZone, OffCycleFlueLossFractiontoZone)
    OS_IMPL_SET_DOUBLE(setPeakUseFlowRate, PeakUseFlowRate)
    OS_IMPL_RESET(resetPeakUseFlowRate, PeakUseFlowRate)
    bool WaterHeaterStratified_Impl::setUseFlowRateFractionSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, "WaterHeaterStratified",
                         "Use Flow Rate Fraction", schedule);
    }
    void WaterHeaterStratified_Impl::resetUseFlowRateFractionSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, ""));
    }
    bool WaterHeaterStratified_Impl::setColdWaterSupplyTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, "WaterHeaterStratified",
                         "Cold Water Supply Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetColdWaterSupplyTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, ""));
    }
    OS_IMPL_SET_DOUBLE(setUseSideEffectiveness, UseSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setUseSideInletHeight, UseSideInletHeight)
    OS_IMPL_SET_DOUBLE(setUseSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_AUTOCALCULATE(autocalculateUseSideOutletHeight, UseSideOutletHeight)
    OS_IMPL_SET_DOUBLE(setSourceSideEffectiveness, SourceSideEffectiveness)
    OS_IMPL_SET_DOUBLE(setSourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_AUTOCALCULATE(autocalculateSourceSideInletHeight, SourceSideInletHeight)
    OS_IMPL_SET_DOUBLE(setSourceSideOutletHeight, SourceSideOutletHeight)
    OS_IMPL_SET_STRING(setInletMode, InletMode)
    OS_IMPL_SET_DOUBLE(setUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_AUTOSIZE(autosizeUseSideDesignFlowRate, UseSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_AUTOSIZE(autosizeSourceSideDesignFlowRate, SourceSideDesignFlowRate)
    OS_IMPL_SET_DOUBLE(setIndirectWaterHeatingRecoveryTime, IndirectWaterHeatingRecoveryTime)
    OS_IMPL_SET_INT(setNumberofNodes, NumberofNodes)
    OS_IMPL_SET_DOUBLE(setAdditionalDestratificationConductivity, AdditionalDestratificationConductivity)
    OS_IMPL_SET_DOUBLE(setNode1AdditionalLossCoefficient, Node1AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode2AdditionalLossCoefficient, Node2AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode3AdditionalLossCoefficient, Node3AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode4AdditionalLossCoefficient, Node4AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode5AdditionalLossCoefficient, Node5AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode6AdditionalLossCoefficient, Node6AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode7AdditionalLossCoefficient, Node7AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode8AdditionalLossCoefficient, Node8AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode9AdditionalLossCoefficient, Node9AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode10AdditionalLossCoefficient, Node10AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode11AdditionalLossCoefficient, Node11AdditionalLossCoefficient)
    OS_IMPL_SET_DOUBLE(setNode12AdditionalLossCoefficient, Node12AdditionalLossCoefficient)
    OS_IMPL_SET_STRING(setSourceSideFlowControlMode, SourceSideFlowControlMode)
    bool WaterHeaterStratified_Impl::setIndirectAlternateSetpointTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, "WaterHeaterStratified",
                         "Indirect Alternate Setpoint Temperature", schedule);
    }
    void WaterHeaterStratified_Impl::resetIndirectAlternateSetpointTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, ""));
    }

#undef OS_IMPL_OPTIONAL_DOUBLE
#undef OS_IMPL_REQUIRED_DOUBLE
#undef OS_IMPL_OPTIONAL_STRING
#undef OS_IMPL_REQUIRED_STRING
#undef OS_IMPL_IS_AUTOSIZED
#undef OS_IMPL_IS_AUTOCALCULATED
#undef OS_IMPL_SET_DOUBLE
#undef OS_IMPL_SET_STRING
#undef OS_IMPL_SET_INT
#undef OS_IMPL_REQUIRED_INT
#undef OS_IMPL_RESET
#undef OS_IMPL_AUTOSIZE
#undef OS_IMPL_AUTOCALCULATE

    unsigned WaterHeaterStratified_Impl::supplyInletPort() const {
      return openstudio::WaterHeater_StratifiedFields::UseSideInletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::supplyOutletPort() const {
      return openstudio::WaterHeater_StratifiedFields::UseSideOutletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::demandInletPort() const {
      return openstudio::WaterHeater_StratifiedFields::SourceSideInletNodeName;
    }

    unsigned WaterHeaterStratified_Impl::demandOutletPort() const {
      return openstudio::WaterHeater_StratifiedFields::SourceSideOutletNodeName;
    }

    WaterHeaterSizing WaterHeaterStratified_Impl::waterHeaterSizing() const {
      for (const auto& sizing : model().getConcreteModelObjects<WaterHeaterSizing>()) {
        if (sizing.waterHeater().handle() == handle()) {
          return sizing;
        }
      }
      throw std::runtime_error("WaterHeaterStratified missing WaterHeater:Sizing object.");
    }

    boost::optional<PlantLoop> WaterHeaterStratified_Impl::plantLoop() const {
      if (auto sourceSidePlantLoop = secondaryPlantLoop()) {
        for (const auto& plantLoop : model().getConcreteModelObjects<PlantLoop>()) {
          const auto supplyComponents = plantLoop.supplyComponents(openstudio::IddObjectType::Catchall);
          const auto matchesSourceLoop =
            std::find_if(supplyComponents.begin(), supplyComponents.end(), [&](const auto& component) { return component.handle() == handle(); });
          if (matchesSourceLoop != supplyComponents.end() && plantLoop.handle() != sourceSidePlantLoop->handle()) {
            return plantLoop;
          }
        }
      }

      return WaterToWaterComponent_Impl::plantLoop();
    }

    boost::optional<PlantLoop> WaterHeaterStratified_Impl::secondaryPlantLoop() const {
      if (auto secondaryLoop = WaterToWaterComponent_Impl::secondaryPlantLoop()) {
        return secondaryLoop;
      }

      auto sourceSideOutletModelObject_ = demandOutletModelObject();
      if (!sourceSideOutletModelObject_) {
        return boost::none;
      }

      auto sourceSideOutletNode_ = sourceSideOutletModelObject_->optionalCast<Node>();
      if (!sourceSideOutletNode_) {
        return boost::none;
      }

      if (auto sourceSidePlantLoop = sourceSideOutletNode_->plantLoop()) {
        const auto supplyComponents = sourceSidePlantLoop->supplyComponents(openstudio::IddObjectType::Catchall);
        const auto matchesSourceLoop = std::find_if(supplyComponents.begin(), supplyComponents.end(),
                                                    [&](const auto& component) { return component.handle() == handle(); });
        if (matchesSourceLoop != supplyComponents.end()) {
          return sourceSidePlantLoop;
        }
      }

      return boost::none;
    }

    bool WaterHeaterStratified_Impl::removeFromSecondaryPlantLoop() {
      return removeFromBranch(demandInletPort(), demandOutletPort(), secondaryPlantLoop());
    }

    bool WaterHeaterStratified_Impl::addToNode(Node& node) {
      auto t_plantLoop = node.plantLoop();
      if (t_plantLoop && t_plantLoop->supplyComponent(node.handle())) {
        if (auto useSidePlant = plantLoop()) {
          if (t_plantLoop->handle() != useSidePlant->handle()) {
            return addToSourceSideNode(node);
          }
        }
      }

      return WaterToWaterComponent_Impl::addToNode(node);
    }

    bool WaterHeaterStratified_Impl::addToSourceSideNode(Node& node) {
      auto t_plantLoop = node.plantLoop();
      if (!t_plantLoop) {
        return false;
      }

      auto branch = t_plantLoop->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
      if (!branch) {
        return false;
      }

      const auto branchComponents = branch->components();
      if (std::ranges::find_if(branchComponents, [&](const auto& component) { return component.handle() == handle(); }) != branchComponents.end()) {
        return false;
      }

      if (t_plantLoop->supplyComponent(node.handle()) || t_plantLoop->demandComponent(node.handle())) {
        removeFromSecondaryPlantLoop();
        return insertOnBranch(node, *branch, demandInletPort(), demandOutletPort());
      }

      return false;
    }

    openstudio::ComponentType WaterHeaterStratified_Impl::componentType() const {
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        return openstudio::ComponentType::Heating;
      }

      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        return sourceSidePlantLoop_->componentType();
      }

      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          return openstudio::ComponentType::Heating;
        }
      }

      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          return openstudio::ComponentType::Heating;
        }
      }

      return openstudio::ComponentType::None;
    }

    std::vector<openstudio::FuelType> WaterHeaterStratified_Impl::coolingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->coolingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::FuelType> WaterHeaterStratified_Impl::heatingFuelTypes() const {
      std::set<openstudio::FuelType> result;
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        result.insert(openstudio::FuelType(heaterFuelType()));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->heatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::FuelType::Electricity);
        }
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::FuelType::Electricity);
        }
      }
      return {result.begin(), result.end()};
    }

    std::vector<openstudio::AppGFuelType> WaterHeaterStratified_Impl::appGHeatingFuelTypes() const {
      std::set<openstudio::AppGFuelType> result;
      if (isHeater1CapacityAutosized() || ((heater1Capacity().get() + heater2Capacity()) > 0.01)) {
        result.insert(openstudio::convertFuelTypeToAppG(openstudio::FuelType(heaterFuelType())));
      }
      if (auto sourceSidePlantLoop_ = secondaryPlantLoop()) {
        const auto plantFuelTypes = sourceSidePlantLoop_->appGHeatingFuelTypes();
        result.insert(plantFuelTypes.begin(), plantFuelTypes.end());
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPump>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::AppGFuelType::HeatPump);
        }
      }
      for (const auto& hpwh : model().getConcreteModelObjects<WaterHeaterHeatPumpWrappedCondenser>()) {
        if (hpwh.tank().handle() == handle()) {
          result.insert(openstudio::AppGFuelType::HeatPump);
        }
      }
      return {result.begin(), result.end()};
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
