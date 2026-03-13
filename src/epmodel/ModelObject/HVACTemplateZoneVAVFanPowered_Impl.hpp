/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEVAVFANPOWERED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplateZoneVAVFanPowered_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplateZoneVAVFanPowered_Impl() override = default;

      boost::optional<double> primarySupplyAirMaximumFlowRate() const;
      bool isPrimarySupplyAirMaximumFlowRateDefaulted() const;
      bool isPrimarySupplyAirMaximumFlowRateAutosized() const;
      bool setPrimarySupplyAirMaximumFlowRate(double primarySupplyAirMaximumFlowRate);
      void resetPrimarySupplyAirMaximumFlowRate();
      void autosizePrimarySupplyAirMaximumFlowRate();

      boost::optional<double> zoneHeatingSizingFactor() const;
      bool isZoneHeatingSizingFactorDefaulted() const;
      bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
      void resetZoneHeatingSizingFactor();

      boost::optional<double> zoneCoolingSizingFactor() const;
      bool isZoneCoolingSizingFactorDefaulted() const;
      bool setZoneCoolingSizingFactor(double zoneCoolingSizingFactor);
      void resetZoneCoolingSizingFactor();

      boost::optional<double> primarySupplyAirMinimumFlowFraction() const;
      bool isPrimarySupplyAirMinimumFlowFractionDefaulted() const;
      bool isPrimarySupplyAirMinimumFlowFractionAutosized() const;
      bool setPrimarySupplyAirMinimumFlowFraction(double primarySupplyAirMinimumFlowFraction);
      void resetPrimarySupplyAirMinimumFlowFraction();
      void autosizePrimarySupplyAirMinimumFlowFraction();

      boost::optional<double> secondarySupplyAirMaximumFlowRate() const;
      bool isSecondarySupplyAirMaximumFlowRateDefaulted() const;
      bool isSecondarySupplyAirMaximumFlowRateAutosized() const;
      bool setSecondarySupplyAirMaximumFlowRate(double secondarySupplyAirMaximumFlowRate);
      void resetSecondarySupplyAirMaximumFlowRate();
      void autosizeSecondarySupplyAirMaximumFlowRate();

      std::string flowType() const;
      bool isFlowTypeDefaulted() const;
      bool setFlowType(const std::string& flowType);
      void resetFlowType();

      boost::optional<double> parallelFanOnFlowFraction() const;
      bool isParallelFanOnFlowFractionDefaulted() const;
      bool isParallelFanOnFlowFractionAutosized() const;
      bool setParallelFanOnFlowFraction(double parallelFanOnFlowFraction);
      void resetParallelFanOnFlowFraction();
      void autosizeParallelFanOnFlowFraction();

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

      std::string reheatCoilType() const;
      bool isReheatCoilTypeDefaulted() const;
      bool setReheatCoilType(const std::string& reheatCoilType);
      void resetReheatCoilType();

      double fanTotalEfficiency() const;
      bool isFanTotalEfficiencyDefaulted() const;
      bool setFanTotalEfficiency(double fanTotalEfficiency);
      void resetFanTotalEfficiency();

      double fanDeltaPressure() const;
      bool isFanDeltaPressureDefaulted() const;
      bool setFanDeltaPressure(double fanDeltaPressure);
      void resetFanDeltaPressure();

      double fanMotorEfficiency() const;
      bool isFanMotorEfficiencyDefaulted() const;
      bool setFanMotorEfficiency(double fanMotorEfficiency);
      void resetFanMotorEfficiency();

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

      std::vector<std::string> flowTypeValues() const;
      std::vector<std::string> outdoorAirMethodValues() const;
      std::vector<std::string> reheatCoilTypeValues() const;
      std::vector<std::string> baseboardHeatingTypeValues() const;
      std::vector<std::string> zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const;
      std::vector<std::string> zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
