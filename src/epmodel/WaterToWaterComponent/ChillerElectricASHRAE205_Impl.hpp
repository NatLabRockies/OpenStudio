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

     private:
      bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
