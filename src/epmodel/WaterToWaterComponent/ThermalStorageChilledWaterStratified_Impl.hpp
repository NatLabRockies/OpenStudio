/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGECHILLEDBWATERSTRATIFIED_IMPL_HPP
#define EPMODEL_THERMALSTORAGECHILLEDBWATERSTRATIFIED_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class Schedule;
  class ThermalZone;
  class WaterHeaterSizing;

  namespace detail {

    class EPMODEL_API ThermalStorageChilledWaterStratified_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~ThermalStorageChilledWaterStratified_Impl() override = default;

      void doCanonicalize(LoadContext& context) override;
      std::vector<ModelObject> children() const override;
      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      ComponentType componentType() const override;
      std::vector<FuelType> coolingFuelTypes() const override;
      std::vector<FuelType> heatingFuelTypes() const override;
      std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

      double tankVolume() const;
      bool setTankVolume(double tankVolume);

      double tankHeight() const;
      bool setTankHeight(double tankHeight);

      std::string tankShape() const;
      bool setTankShape(const std::string& tankShape);

      boost::optional<double> tankPerimeter() const;
      bool setTankPerimeter(double tankPerimeter);
      void resetTankPerimeter();

      boost::optional<Schedule> setpointTemperatureSchedule() const;
      bool setSetpointTemperatureSchedule(Schedule& schedule);
      void resetSetpointTemperatureSchedule();

      double deadbandTemperatureDifference() const;
      bool setDeadbandTemperatureDifference(double deadbandTemperatureDifference);

      boost::optional<double> temperatureSensorHeight() const;
      bool setTemperatureSensorHeight(double temperatureSensorHeight);
      void resetTemperatureSensorHeight();

      boost::optional<double> minimumTemperatureLimit() const;
      bool setMinimumTemperatureLimit(double minimumTemperatureLimit);
      void resetMinimumTemperatureLimit();

      boost::optional<double> nominalCoolingCapacity() const;
      bool setNominalCoolingCapacity(double nominalCoolingCapacity);
      bool isNominalCoolingCapacityAutosized() const;
      void autosizeNominalCoolingCapacity();

      std::string ambientTemperatureIndicator() const;
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);

      boost::optional<Schedule> ambientTemperatureSchedule() const;
      bool setAmbientTemperatureSchedule(Schedule& schedule);
      void resetAmbientTemperatureSchedule();

      boost::optional<ThermalZone> ambientTemperatureThermalZone() const;
      bool setAmbientTemperatureThermalZone(const ThermalZone& thermalZone);
      void resetAmbientTemperatureThermalZone();

      boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
      bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
      void resetAmbientTemperatureOutdoorAirNodeName();

      boost::optional<double> uniformSkinLossCoefficientperUnitAreatoAmbientTemperature() const;
      bool setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(double uniformSkinLossCoefficientperUnitAreatoAmbientTemperature);
      void resetUniformSkinLossCoefficientperUnitAreatoAmbientTemperature();

      double useSideHeatTransferEffectiveness() const;
      bool setUseSideHeatTransferEffectiveness(double useSideHeatTransferEffectiveness);
      bool isUseSideHeatTransferEffectivenessDefaulted() const;
      void resetUseSideHeatTransferEffectiveness();

      boost::optional<Schedule> useSideAvailabilitySchedule() const;
      bool setUseSideAvailabilitySchedule(Schedule& schedule);
      void resetUseSideAvailabilitySchedule();

      boost::optional<double> useSideInletHeight() const;
      bool setUseSideInletHeight(double useSideInletHeight);
      bool isUseSideInletHeightAutocalculated() const;
      void autocalculateUseSideInletHeight();

      double useSideOutletHeight() const;
      bool setUseSideOutletHeight(double useSideOutletHeight);

      boost::optional<double> useSideDesignFlowRate() const;
      bool setUseSideDesignFlowRate(double useSideDesignFlowRate);
      bool isUseSideDesignFlowRateDefaulted() const;
      bool isUseSideDesignFlowRateAutosized() const;
      void resetUseSideDesignFlowRate();
      void autosizeUseSideDesignFlowRate();

      double sourceSideHeatTransferEffectiveness() const;
      bool setSourceSideHeatTransferEffectiveness(double sourceSideHeatTransferEffectiveness);
      bool isSourceSideHeatTransferEffectivenessDefaulted() const;
      void resetSourceSideHeatTransferEffectiveness();

      boost::optional<Schedule> sourceSideAvailabilitySchedule() const;
      bool setSourceSideAvailabilitySchedule(Schedule& schedule);
      void resetSourceSideAvailabilitySchedule();

      double sourceSideInletHeight() const;
      bool setSourceSideInletHeight(double sourceSideInletHeight);

      boost::optional<double> sourceSideOutletHeight() const;
      bool setSourceSideOutletHeight(double sourceSideOutletHeight);
      bool isSourceSideOutletHeightAutocalculated() const;
      void autocalculateSourceSideOutletHeight();

      boost::optional<double> sourceSideDesignFlowRate() const;
      bool setSourceSideDesignFlowRate(double sourceSideDesignFlowRate);
      bool isSourceSideDesignFlowRateDefaulted() const;
      bool isSourceSideDesignFlowRateAutosized() const;
      void resetSourceSideDesignFlowRate();
      void autosizeSourceSideDesignFlowRate();

      double tankRecoveryTime() const;
      bool setTankRecoveryTime(double tankRecoveryTime);

      std::string inletMode() const;
      bool setInletMode(const std::string& inletMode);

      int numberofNodes() const;
      bool setNumberofNodes(int numberofNodes);

      double additionalDestratificationConductivity() const;
      bool setAdditionalDestratificationConductivity(double additionalDestratificationConductivity);

      double node1AdditionalLossCoefficient() const;
      bool setNode1AdditionalLossCoefficient(double node1AdditionalLossCoefficient);

      double node2AdditionalLossCoefficient() const;
      bool setNode2AdditionalLossCoefficient(double node2AdditionalLossCoefficient);

      double node3AdditionalLossCoefficient() const;
      bool setNode3AdditionalLossCoefficient(double node3AdditionalLossCoefficient);

      double node4AdditionalLossCoefficient() const;
      bool setNode4AdditionalLossCoefficient(double node4AdditionalLossCoefficient);

      double node5AdditionalLossCoefficient() const;
      bool setNode5AdditionalLossCoefficient(double node5AdditionalLossCoefficient);

      double node6AdditionalLossCoefficient() const;
      bool setNode6AdditionalLossCoefficient(double node6AdditionalLossCoefficient);

      double node7AdditionalLossCoefficient() const;
      bool setNode7AdditionalLossCoefficient(double node7AdditionalLossCoefficient);

      double node8AdditionalLossCoefficient() const;
      bool setNode8AdditionalLossCoefficient(double node8AdditionalLossCoefficient);

      double node9AdditionalLossCoefficient() const;
      bool setNode9AdditionalLossCoefficient(double node9AdditionalLossCoefficient);

      double node10AdditionalLossCoefficient() const;
      bool setNode10AdditionalLossCoefficient(double node10AdditionalLossCoefficient);

      WaterHeaterSizing waterHeaterSizing() const;
      boost::optional<double> autosizedNominalCoolingCapacity() const;
      boost::optional<double> autosizedUseSideDesignFlowRate() const;
      boost::optional<double> autosizedSourceSideDesignFlowRate() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
