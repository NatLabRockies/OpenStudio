/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEPTHP_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEPTHP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateZonePTHP_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateZonePTHP_Impl() override = default;

      boost::optional<double> coolingSupplyAirFlowRate() const;
      bool isCoolingSupplyAirFlowRateDefaulted() const;
      bool isCoolingSupplyAirFlowRateAutosized() const;
      bool setCoolingSupplyAirFlowRate(double coolingSupplyAirFlowRate);
      void resetCoolingSupplyAirFlowRate();
      void autosizeCoolingSupplyAirFlowRate();

      boost::optional<double> heatingSupplyAirFlowRate() const;
      bool isHeatingSupplyAirFlowRateDefaulted() const;
      bool isHeatingSupplyAirFlowRateAutosized() const;
      bool setHeatingSupplyAirFlowRate(double heatingSupplyAirFlowRate);
      void resetHeatingSupplyAirFlowRate();
      void autosizeHeatingSupplyAirFlowRate();

      boost::optional<double> noLoadSupplyAirFlowRate() const;
      bool isNoLoadSupplyAirFlowRateDefaulted() const;
      bool isNoLoadSupplyAirFlowRateAutosized() const;
      bool setNoLoadSupplyAirFlowRate(double noLoadSupplyAirFlowRate);
      void resetNoLoadSupplyAirFlowRate();
      void autosizeNoLoadSupplyAirFlowRate();

      boost::optional<double> zoneHeatingSizingFactor() const;
      bool isZoneHeatingSizingFactorDefaulted() const;
      bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
      void resetZoneHeatingSizingFactor();

      boost::optional<double> zoneCoolingSizingFactor() const;
      bool isZoneCoolingSizingFactorDefaulted() const;
      bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
      void resetZoneCoolingSizingFactor();

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

      std::string supplyFanPlacement() const;
      bool isSupplyFanPlacementDefaulted() const;
      bool setSupplyFanPlacement(const std::string& supplyFanPlacement);
      void resetSupplyFanPlacement();

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

      double coolingCoilGrossRatedCOP() const;
      bool isCoolingCoilGrossRatedCOPDefaulted() const;
      bool setCoolingCoilGrossRatedCOP(double coolingCoilGrossRatedCOP);
      void resetCoolingCoilGrossRatedCOP();

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

      double heatPumpHeatingCoilGrossRatedCOP() const;
      bool isHeatPumpHeatingCoilGrossRatedCOPDefaulted() const;
      bool setHeatPumpHeatingCoilGrossRatedCOP(double heatPumpHeatingCoilGrossRatedCOP);
      void resetHeatPumpHeatingCoilGrossRatedCOP();

      double heatPumpHeatingMinimumOutdoorDryBulbTemperature() const;
      bool isHeatPumpHeatingMinimumOutdoorDryBulbTemperatureDefaulted() const;
      bool setHeatPumpHeatingMinimumOutdoorDryBulbTemperature(double heatPumpHeatingMinimumOutdoorDryBulbTemperature);
      void resetHeatPumpHeatingMinimumOutdoorDryBulbTemperature();

      double heatPumpDefrostMaximumOutdoorDryBulbTemperature() const;
      bool isHeatPumpDefrostMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setHeatPumpDefrostMaximumOutdoorDryBulbTemperature(double heatPumpDefrostMaximumOutdoorDryBulbTemperature);
      void resetHeatPumpDefrostMaximumOutdoorDryBulbTemperature();

      std::string heatPumpDefrostStrategy() const;
      bool isHeatPumpDefrostStrategyDefaulted() const;
      bool setHeatPumpDefrostStrategy(const std::string& heatPumpDefrostStrategy);
      void resetHeatPumpDefrostStrategy();

      std::string heatPumpDefrostControl() const;
      bool isHeatPumpDefrostControlDefaulted() const;
      bool setHeatPumpDefrostControl(const std::string& heatPumpDefrostControl);
      void resetHeatPumpDefrostControl();

      double heatPumpDefrostTimePeriodFraction() const;
      bool isHeatPumpDefrostTimePeriodFractionDefaulted() const;
      bool setHeatPumpDefrostTimePeriodFraction(double heatPumpDefrostTimePeriodFraction);
      void resetHeatPumpDefrostTimePeriodFraction();

      std::string supplementalHeatingCoilType() const;
      bool isSupplementalHeatingCoilTypeDefaulted() const;
      bool setSupplementalHeatingCoilType(const std::string& supplementalHeatingCoilType);
      void resetSupplementalHeatingCoilType();

      boost::optional<double> supplementalHeatingCoilCapacity() const;
      bool isSupplementalHeatingCoilCapacityDefaulted() const;
      bool isSupplementalHeatingCoilCapacityAutosized() const;
      bool setSupplementalHeatingCoilCapacity(double supplementalHeatingCoilCapacity);
      void resetSupplementalHeatingCoilCapacity();
      void autosizeSupplementalHeatingCoilCapacity();

      double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature() const;
      bool isSupplementalHeatingCoilMaximumOutdoorDryBulbTemperatureDefaulted() const;
      bool setSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature(double supplementalHeatingCoilMaximumOutdoorDryBulbTemperature);
      void resetSupplementalHeatingCoilMaximumOutdoorDryBulbTemperature();

      double supplementalGasHeatingCoilEfficiency() const;
      bool isSupplementalGasHeatingCoilEfficiencyDefaulted() const;
      bool setSupplementalGasHeatingCoilEfficiency(double supplementalGasHeatingCoilEfficiency);
      void resetSupplementalGasHeatingCoilEfficiency();

      double supplementalGasHeatingCoilParasiticElectricLoad() const;
      bool isSupplementalGasHeatingCoilParasiticElectricLoadDefaulted() const;
      bool setSupplementalGasHeatingCoilParasiticElectricLoad(double supplementalGasHeatingCoilParasiticElectricLoad);
      void resetSupplementalGasHeatingCoilParasiticElectricLoad();

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

      std::string capacityControlMethod() const;
      bool isCapacityControlMethodDefaulted() const;
      bool setCapacityControlMethod(const std::string& capacityControlMethod);
      void resetCapacityControlMethod();

      std::vector<std::string> outdoorAirMethodValues() const;
      std::vector<std::string> supplyFanPlacementValues() const;
      std::vector<std::string> coolingCoilTypeValues() const;
      std::vector<std::string> heatPumpHeatingCoilTypeValues() const;
      std::vector<std::string> heatPumpDefrostStrategyValues() const;
      std::vector<std::string> heatPumpDefrostControlValues() const;
      std::vector<std::string> supplementalHeatingCoilTypeValues() const;
      std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> baseboardHeatingTypeValues() const;
      std::vector<std::string> capacityControlMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
