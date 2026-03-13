/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGSYSTEM_IMPL_HPP
#define EPMODEL_SIZINGSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;

  namespace detail {

    class EPMODEL_API SizingSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SizingSystem_Impl() override = default;

      std::string typeofLoadtoSizeOn() const;
      bool isTypeofLoadtoSizeOnDefaulted() const;
      bool setTypeofLoadtoSizeOn(const std::string& typeofLoadtoSizeOn);
      void resetTypeofLoadtoSizeOn();

      boost::optional<double> designOutdoorAirFlowRate() const;
      bool isDesignOutdoorAirFlowRateDefaulted() const;
      bool isDesignOutdoorAirFlowRateAutosized() const;
      bool setDesignOutdoorAirFlowRate(boost::optional<double> designOutdoorAirFlowRate);
      void resetDesignOutdoorAirFlowRate();
      void autosizeDesignOutdoorAirFlowRate();

      boost::optional<double> centralHeatingMaximumSystemAirFlowRatio() const;
      bool isCentralHeatingMaximumSystemAirFlowRatioDefaulted() const;
      bool isCentralHeatingMaximumSystemAirFlowRatioAutosized() const;
      bool setCentralHeatingMaximumSystemAirFlowRatio(boost::optional<double> centralHeatingMaximumSystemAirFlowRatio);
      void resetCentralHeatingMaximumSystemAirFlowRatio();
      void autosizeCentralHeatingMaximumSystemAirFlowRatio();

      double preheatDesignTemperature() const;
      bool setPreheatDesignTemperature(double preheatDesignTemperature);

      double preheatDesignHumidityRatio() const;
      bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

      double precoolDesignTemperature() const;
      bool setPrecoolDesignTemperature(double precoolDesignTemperature);

      double precoolDesignHumidityRatio() const;
      bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

      double centralCoolingDesignSupplyAirTemperature() const;
      bool setCentralCoolingDesignSupplyAirTemperature(double centralCoolingDesignSupplyAirTemperature);

      double centralHeatingDesignSupplyAirTemperature() const;
      bool setCentralHeatingDesignSupplyAirTemperature(double centralHeatingDesignSupplyAirTemperature);

      std::string sizingOption() const;
      bool isSizingOptionDefaulted() const;
      bool setSizingOption(const std::string& sizingOption);
      void resetSizingOption();

      bool allOutdoorAirinCooling() const;
      bool isAllOutdoorAirinCoolingDefaulted() const;
      bool setAllOutdoorAirinCooling(bool allOutdoorAirinCooling);
      void resetAllOutdoorAirinCooling();

      bool allOutdoorAirinHeating() const;
      bool isAllOutdoorAirinHeatingDefaulted() const;
      bool setAllOutdoorAirinHeating(bool allOutdoorAirinHeating);
      void resetAllOutdoorAirinHeating();

      double centralCoolingDesignSupplyAirHumidityRatio() const;
      bool isCentralCoolingDesignSupplyAirHumidityRatioDefaulted() const;
      bool setCentralCoolingDesignSupplyAirHumidityRatio(double centralCoolingDesignSupplyAirHumidityRatio);
      void resetCentralCoolingDesignSupplyAirHumidityRatio();

      double centralHeatingDesignSupplyAirHumidityRatio() const;
      bool isCentralHeatingDesignSupplyAirHumidityRatioDefaulted() const;
      bool setCentralHeatingDesignSupplyAirHumidityRatio(double centralHeatingDesignSupplyAirHumidityRatio);
      void resetCentralHeatingDesignSupplyAirHumidityRatio();

      std::string coolingDesignAirFlowMethod() const;
      bool isCoolingDesignAirFlowMethodDefaulted() const;
      bool setCoolingDesignAirFlowMethod(const std::string& coolingDesignAirFlowMethod);
      void resetCoolingDesignAirFlowMethod();

      double coolingDesignAirFlowRate() const;
      bool isCoolingDesignAirFlowRateDefaulted() const;
      bool setCoolingDesignAirFlowRate(double coolingDesignAirFlowRate);
      void resetCoolingDesignAirFlowRate();

      std::string heatingDesignAirFlowMethod() const;
      bool isHeatingDesignAirFlowMethodDefaulted() const;
      bool setHeatingDesignAirFlowMethod(const std::string& heatingDesignAirFlowMethod);
      void resetHeatingDesignAirFlowMethod();

      double heatingDesignAirFlowRate() const;
      bool isHeatingDesignAirFlowRateDefaulted() const;
      bool setHeatingDesignAirFlowRate(double heatingDesignAirFlowRate);
      void resetHeatingDesignAirFlowRate();

      std::string systemOutdoorAirMethod() const;
      bool isSystemOutdoorAirMethodDefaulted() const;
      bool setSystemOutdoorAirMethod(const std::string& systemOutdoorAirMethod);
      void resetSystemOutdoorAirMethod();

      double zoneMaximumOutdoorAirFraction() const;
      bool setZoneMaximumOutdoorAirFraction(double zoneMaximumOutdoorAirFraction);

      double coolingSupplyAirFlowRatePerFloorArea() const;
      bool setCoolingSupplyAirFlowRatePerFloorArea(double coolingSupplyAirFlowRatePerFloorArea);

      double coolingFractionofAutosizedCoolingSupplyAirFlowRate() const;
      bool setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(double coolingFractionofAutosizedCoolingSupplyAirFlowRate);

      double coolingSupplyAirFlowRatePerUnitCoolingCapacity() const;
      bool setCoolingSupplyAirFlowRatePerUnitCoolingCapacity(double coolingSupplyAirFlowRatePerUnitCoolingCapacity);

      double heatingSupplyAirFlowRatePerFloorArea() const;
      bool setHeatingSupplyAirFlowRatePerFloorArea(double heatingSupplyAirFlowRatePerFloorArea);

      double heatingFractionofAutosizedHeatingSupplyAirFlowRate() const;
      bool setHeatingFractionofAutosizedHeatingSupplyAirFlowRate(double heatingFractionofAutosizedHeatingSupplyAirFlowRate);

      double heatingFractionofAutosizedCoolingSupplyAirFlowRate() const;
      bool setHeatingFractionofAutosizedCoolingSupplyAirFlowRate(double heatingFractionofAutosizedCoolingSupplyAirFlowRate);

      double heatingSupplyAirFlowRatePerUnitHeatingCapacity() const;
      bool setHeatingSupplyAirFlowRatePerUnitHeatingCapacity(double heatingSupplyAirFlowRatePerUnitHeatingCapacity);

      std::string coolingDesignCapacityMethod() const;
      bool setCoolingDesignCapacityMethod(const std::string& coolingDesignCapacityMethod);

      boost::optional<double> coolingDesignCapacity() const;
      bool isCoolingDesignCapacityAutosized() const;
      bool setCoolingDesignCapacity(boost::optional<double> coolingDesignCapacity);
      void autosizeCoolingDesignCapacity();

      double coolingDesignCapacityPerFloorArea() const;
      bool setCoolingDesignCapacityPerFloorArea(double coolingDesignCapacityPerFloorArea);

      double fractionofAutosizedCoolingDesignCapacity() const;
      bool setFractionofAutosizedCoolingDesignCapacity(double fractionofAutosizedCoolingDesignCapacity);

      std::string heatingDesignCapacityMethod() const;
      bool setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod);

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(boost::optional<double> heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();

      double heatingDesignCapacityPerFloorArea() const;
      bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

      double fractionofAutosizedHeatingDesignCapacity() const;
      bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

      std::string centralCoolingCapacityControlMethod() const;
      bool setCentralCoolingCapacityControlMethod(const std::string& centralCoolingCapacityControlMethod);

      boost::optional<double> occupantDiversity() const;
      bool isOccupantDiversityAutosized() const;
      bool setOccupantDiversity(double occupantDiversity);
      void autosizeOccupantDiversity();

      std::string heatingCoilSizingMethod() const;
      bool setHeatingCoilSizingMethod(const std::string& heatingCoilSizingMethod);

      double maximumHeatingCapacityToCoolingCapacitySizingRatio() const;
      bool setMaximumHeatingCapacityToCoolingCapacitySizingRatio(double maximumHeatingCapacityToCoolingCapacitySizingRatio);

      bool setAirLoopHVAC(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
