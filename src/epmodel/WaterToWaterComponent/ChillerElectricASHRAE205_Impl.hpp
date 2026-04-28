/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICASHRAE205_IMPL_HPP
#define EPMODEL_CHILLERELECTRICASHRAE205_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
class PlantLoop;
class Schedule;
class ThermalZone;

  namespace detail {

  class EPMODEL_API ChillerElectricASHRAE205_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~ChillerElectricASHRAE205_Impl() override = default;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      unsigned tertiaryInletPort() const override;
      unsigned tertiaryOutletPort() const override;

      std::vector<std::string> performanceInterpolationMethodValues() const;
      std::vector<std::string> ambientTemperatureIndicatorValues() const;
      std::vector<std::string> chillerFlowModeValues() const;

      std::string performanceInterpolationMethod() const;
      bool setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod);

      boost::optional<double> ratedCapacity() const;
      bool isRatedCapacityAutosized() const;
      bool setRatedCapacity(double ratedCapacity);
      void autosizeRatedCapacity();

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);

      std::string ambientTemperatureIndicator() const;
      boost::optional<Schedule> ambientTemperatureSchedule() const;
      bool setAmbientTemperatureSchedule(Schedule& schedule);
      void resetAmbientTemperatureSchedule();
      boost::optional<ThermalZone> ambientTemperatureZone() const;
      bool setAmbientTemperatureZone(const ThermalZone& thermalZone);
      void resetAmbientTemperatureZone();

      boost::optional<std::string> ambientTemperatureOutdoorAirNodeName() const;
      bool setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName);
      void resetAmbientTemperatureOutdoorAirNodeName();

      boost::optional<double> chilledWaterMaximumRequestedFlowRate() const;
      bool isChilledWaterMaximumRequestedFlowRateAutosized() const;
      bool setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate);
      void autosizeChilledWaterMaximumRequestedFlowRate();

      boost::optional<double> condenserMaximumRequestedFlowRate() const;
      bool isCondenserMaximumRequestedFlowRateAutosized() const;
      bool setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate);
      void autosizeCondenserMaximumRequestedFlowRate();

      std::string chillerFlowMode() const;
      bool setChillerFlowMode(const std::string& chillerFlowMode);

      boost::optional<double> oilCoolerDesignFlowRate() const;
      bool setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate);
      void resetOilCoolerDesignFlowRate();

      boost::optional<double> auxiliaryCoolingDesignFlowRate() const;
      bool setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate);
      void resetAuxiliaryCoolingDesignFlowRate();

      std::string endUseSubcategory() const;
      bool isEndUseSubcategoryDefaulted() const;
      bool setEndUseSubcategory(const std::string& endUseSubcategory);
      void resetEndUseSubcategory();

      boost::optional<double> autosizedRatedCapacity() const;
      boost::optional<double> autosizedChilledWaterMaximumRequestedFlowRate() const;
      boost::optional<double> autosizedCondenserMaximumRequestedFlowRate() const;

      boost::optional<PlantLoop> chilledWaterLoop() const;
      boost::optional<Node> chilledWaterInletNode() const;
      boost::optional<Node> chilledWaterOutletNode() const;

      boost::optional<PlantLoop> condenserWaterLoop() const;
      boost::optional<Node> condenserInletNode() const;
      boost::optional<Node> condenserOutletNode() const;

      boost::optional<PlantLoop> heatRecoveryLoop() const;
      boost::optional<Node> heatRecoveryInletNode() const;
      boost::optional<Node> heatRecoveryOutletNode() const;

      unsigned oilCoolerInletPort() const;
      boost::optional<ModelObject> oilCoolerInletModelObject() const;
      boost::optional<Node> oilCoolerInletNode() const;
      unsigned oilCoolerOutletPort() const;
      boost::optional<ModelObject> oilCoolerOutletModelObject() const;
      boost::optional<Node> oilCoolerOutletNode() const;
      boost::optional<PlantLoop> oilCoolerLoop() const;
      bool addDemandBranchOnOilCoolerLoop(PlantLoop& plantLoop);
      bool addToOilCoolerLoopNode(Node& node);
      bool removeFromOilCoolerLoop();

      unsigned auxiliaryInletPort() const;
      boost::optional<ModelObject> auxiliaryInletModelObject() const;
      boost::optional<Node> auxiliaryInletNode() const;
      unsigned auxiliaryOutletPort() const;
      boost::optional<ModelObject> auxiliaryOutletModelObject() const;
      boost::optional<Node> auxiliaryOutletNode() const;
      boost::optional<PlantLoop> auxiliaryLoop() const;
      bool addDemandBranchOnAuxiliaryLoop(PlantLoop& plantLoop);
      bool addToAuxiliaryLoopNode(Node& node);
      bool removeFromAuxiliaryLoop();

      bool addToNode(Node& node) override;
      bool addToTertiaryNode(Node& node) override;

      ComponentType componentType() const override;
      std::vector<FuelType> coolingFuelTypes() const override;
      std::vector<FuelType> heatingFuelTypes() const override;
      std::vector<AppGFuelType> appGHeatingFuelTypes() const override;

     private:
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
