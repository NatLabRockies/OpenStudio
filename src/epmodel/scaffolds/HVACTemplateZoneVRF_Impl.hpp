/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVRF_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEVRF_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateZoneVRF_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateZoneVRF_Impl() override = default;

      std::vector<std::string> outdoorAirMethodValues() const;
      std::vector<std::string> supplyAirFanplacementValues() const;
      std::vector<std::string> coolingCoilTypeValues() const;
      std::vector<std::string> heatPumpHeatingCoilTypeValues() const;
      std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> baseboardHeatingTypeValues() const;

      boost::optional<double> zoneHeatingSizingFactor() const;
      bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
      void resetZoneHeatingSizingFactor();

      boost::optional<double> zoneCoolingSizingFactor() const;
      bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
      void resetZoneCoolingSizingFactor();

      double ratedTotalHeatingCapacitySizingRatio() const;
      bool isRatedTotalHeatingCapacitySizingRatioDefaulted() const;
      bool setRatedTotalHeatingCapacitySizingRatio(double ratedTotalHeatingCapacitySizingRatio);
      void resetRatedTotalHeatingCapacitySizingRatio();

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool isCoolingSupplyAirFlowRateDefaulted() const;
      bool isCoolingSupplyAirFlowRateAutosized() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      void resetCoolingSupplyAirFlowRate();
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> noCoolingSupplyAirFlowRate() const;
      bool isNoCoolingSupplyAirFlowRateDefaulted() const;
      bool isNoCoolingSupplyAirFlowRateAutosized() const;
      bool setNoCoolingSupplyAirFlowRate(double noCoolingSupplyAirFlowRate);
      void resetNoCoolingSupplyAirFlowRate();
      void autosizeNoCoolingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool isHeatingSupplyAirFlowRateDefaulted() const;
      bool isHeatingSupplyAirFlowRateAutosized() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      void resetHeatingSupplyAirFlowRate();
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> noHeatingSupplyAirFlowRate() const;
      bool isNoHeatingSupplyAirFlowRateDefaulted() const;
      bool isNoHeatingSupplyAirFlowRateAutosized() const;
      bool setNoHeatingSupplyAirFlowRate(double noHeatingSupplyAirFlowRate);
      void resetNoHeatingSupplyAirFlowRate();
      void autosizeNoHeatingSupplyAirFlowRate();

      boost::optional<double> coolingOutdoorAirFlowRate() const;
      bool isCoolingOutdoorAirFlowRateDefaulted() const;
      bool isCoolingOutdoorAirFlowRateAutosized() const;
      bool setCoolingOutdoorAirFlowRate(double coolingOutdoorAirFlowRate);
      void resetCoolingOutdoorAirFlowRate();
      void autosizeCoolingOutdoorAirFlowRate();

      boost::optional<double> heatingOutdoorAirFlowRate() const;
      bool isHeatingOutdoorAirFlowRateDefaulted() const;
      bool isHeatingOutdoorAirFlowRateAutosized() const;
      bool setHeatingOutdoorAirFlowRate(double heatingOutdoorAirFlowRate);
      void resetHeatingOutdoorAirFlowRate();
      void autosizeHeatingOutdoorAirFlowRate();

      boost::optional<double> noLoadOutdoorAirFlowRate() const;
      bool isNoLoadOutdoorAirFlowRateDefaulted() const;
      bool isNoLoadOutdoorAirFlowRateAutosized() const;
      bool setNoLoadOutdoorAirFlowRate(double noLoadOutdoorAirFlowRate);
      void resetNoLoadOutdoorAirFlowRate();
      void autosizeNoLoadOutdoorAirFlowRate();

      std::string outdoorAirMethod() const;
      bool isOutdoorAirMethodDefaulted() const;
      bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
      void resetOutdoorAirMethod();

      double outdoorAirFlowRateperPerson() const;
      bool isOutdoorAirFlowRateperPersonDefaulted() const;
      bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
      void resetOutdoorAirFlowRateperPerson();

      double outdoorAirFlowRateperZoneFloorArea() const;
      bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
      bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
      void resetOutdoorAirFlowRateperZoneFloorArea();

      double outdoorAirFlowRateperZone() const;
      bool isOutdoorAirFlowRateperZoneDefaulted() const;
      bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);
      void resetOutdoorAirFlowRateperZone();

      std::string supplyAirFanplacement() const;
      bool isSupplyAirFanplacementDefaulted() const;
      bool setSupplyAirFanplacement(const std::string& supplyAirFanplacement);
      void resetSupplyAirFanplacement();

      double supplyFanTotalEfficiency() const;
      bool isSupplyFanTotalEfficiencyDefaulted() const;
      bool setSupplyFanTotalEfficiency(double supplyFanTotalEfficiency);
      void resetSupplyFanTotalEfficiency();

      double supplyFanDeltaPressure() const;
      bool isSupplyFanDeltaPressureDefaulted() const;
      bool setSupplyFanDeltaPressure(double supplyFanDeltaPressure);
      void resetSupplyFanDeltaPressure();

      double supplyFanMotorEfficiency() const;
      bool isSupplyFanMotorEfficiencyDefaulted() const;
      bool setSupplyFanMotorEfficiency(double supplyFanMotorEfficiency);
      void resetSupplyFanMotorEfficiency();

      std::string coolingCoilType() const;
      bool isCoolingCoilTypeDefaulted() const;
      bool setCoolingCoilType(const std::string& coolingCoilType);
      void resetCoolingCoilType();

      boost::optional<double> coolingCoilGrossRatedTotalCapacity() const;
      bool isCoolingCoilGrossRatedTotalCapacityDefaulted() const;
      bool isCoolingCoilGrossRatedTotalCapacityAutosized() const;
      bool setCoolingCoilGrossRatedTotalCapacity(double coolingCoilGrossRatedTotalCapacity);
      void resetCoolingCoilGrossRatedTotalCapacity();
      void autosizeCoolingCoilGrossRatedTotalCapacity();

      boost::optional<double> coolingCoilGrossRatedSensibleHeatRatio() const;
      bool isCoolingCoilGrossRatedSensibleHeatRatioDefaulted() const;
      bool isCoolingCoilGrossRatedSensibleHeatRatioAutosized() const;
      bool setCoolingCoilGrossRatedSensibleHeatRatio(double coolingCoilGrossRatedSensibleHeatRatio);
      void resetCoolingCoilGrossRatedSensibleHeatRatio();
      void autosizeCoolingCoilGrossRatedSensibleHeatRatio();

      std::string heatPumpHeatingCoilType() const;
      bool isHeatPumpHeatingCoilTypeDefaulted() const;
      bool setHeatPumpHeatingCoilType(const std::string& heatPumpHeatingCoilType);
      void resetHeatPumpHeatingCoilType();

      boost::optional<double> heatPumpHeatingCoilGrossRatedCapacity() const;
      bool isHeatPumpHeatingCoilGrossRatedCapacityDefaulted() const;
      bool isHeatPumpHeatingCoilGrossRatedCapacityAutosized() const;
      bool setHeatPumpHeatingCoilGrossRatedCapacity(double heatPumpHeatingCoilGrossRatedCapacity);
      void resetHeatPumpHeatingCoilGrossRatedCapacity();
      void autosizeHeatPumpHeatingCoilGrossRatedCapacity();

      double zoneTerminalUnitOnParasiticElectricEnergyUse() const;
      bool isZoneTerminalUnitOnParasiticElectricEnergyUseDefaulted() const;
      bool setZoneTerminalUnitOnParasiticElectricEnergyUse(double zoneTerminalUnitOnParasiticElectricEnergyUse);
      void resetZoneTerminalUnitOnParasiticElectricEnergyUse();

      double zoneTerminalUnitOffParasiticElectricEnergyUse() const;
      bool isZoneTerminalUnitOffParasiticElectricEnergyUseDefaulted() const;
      bool setZoneTerminalUnitOffParasiticElectricEnergyUse(double zoneTerminalUnitOffParasiticElectricEnergyUse);
      void resetZoneTerminalUnitOffParasiticElectricEnergyUse();

      std::string zoneCoolingDesignSupplyAirTemperatureInputMethod() const;
      bool isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const;
      bool setZoneCoolingDesignSupplyAirTemperatureInputMethod(const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod);
      void resetZoneCoolingDesignSupplyAirTemperatureInputMethod();

      double zoneCoolingDesignSupplyAirTemperature() const;
      bool isZoneCoolingDesignSupplyAirTemperatureDefaulted() const;
      bool setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature);
      void resetZoneCoolingDesignSupplyAirTemperature();

      double zoneCoolingDesignSupplyAirTemperatureDifference() const;
      bool isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const;
      bool setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference);
      void resetZoneCoolingDesignSupplyAirTemperatureDifference();

      std::string zoneHeatingDesignSupplyAirTemperatureInputMethod() const;
      bool isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const;
      bool setZoneHeatingDesignSupplyAirTemperatureInputMethod(const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod);
      void resetZoneHeatingDesignSupplyAirTemperatureInputMethod();

      double zoneHeatingDesignSupplyAirTemperature() const;
      bool isZoneHeatingDesignSupplyAirTemperatureDefaulted() const;
      bool setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature);
      void resetZoneHeatingDesignSupplyAirTemperature();

      double zoneHeatingDesignSupplyAirTemperatureDifference() const;
      bool isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const;
      bool setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference);
      void resetZoneHeatingDesignSupplyAirTemperatureDifference();

      std::string baseboardHeatingType() const;
      bool isBaseboardHeatingTypeDefaulted() const;
      bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
      void resetBaseboardHeatingType();

      boost::optional<double> baseboardHeatingCapacity() const;
      bool isBaseboardHeatingCapacityDefaulted() const;
      bool isBaseboardHeatingCapacityAutosized() const;
      bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
      void resetBaseboardHeatingCapacity();
      void autosizeBaseboardHeatingCapacity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
