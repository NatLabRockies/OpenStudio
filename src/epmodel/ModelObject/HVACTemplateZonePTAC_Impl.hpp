/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEPTAC_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEPTAC_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateZonePTAC_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateZonePTAC_Impl() override = default;

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

      double coolingCoilGrossRatedCoolingCOP() const;
      bool isCoolingCoilGrossRatedCoolingCOPDefaulted() const;
      bool setCoolingCoilGrossRatedCoolingCOP(double coolingCoilGrossRatedCoolingCOP);
      void resetCoolingCoilGrossRatedCoolingCOP();

      std::string heatingCoilType() const;
      bool isHeatingCoilTypeDefaulted() const;
      bool setHeatingCoilType(const std::string& heatingCoilType);
      void resetHeatingCoilType();

      boost::optional<double> heatingCoilCapacity() const;
      bool isHeatingCoilCapacityDefaulted() const;
      bool isHeatingCoilCapacityAutosized() const;
      bool setHeatingCoilCapacity(double heatingCoilCapacity);
      void resetHeatingCoilCapacity();
      void autosizeHeatingCoilCapacity();

      double gasHeatingCoilEfficiency() const;
      bool isGasHeatingCoilEfficiencyDefaulted() const;
      bool setGasHeatingCoilEfficiency(double gasHeatingCoilEfficiency);
      void resetGasHeatingCoilEfficiency();

      double gasHeatingCoilParasiticElectricLoad() const;
      bool isGasHeatingCoilParasiticElectricLoadDefaulted() const;
      bool setGasHeatingCoilParasiticElectricLoad(double gasHeatingCoilParasiticElectricLoad);
      void resetGasHeatingCoilParasiticElectricLoad();

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
      std::vector<std::string> heatingCoilTypeValues() const;
      std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> baseboardHeatingTypeValues() const;
      std::vector<std::string> capacityControlMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
