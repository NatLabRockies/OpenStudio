/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTION_IMPL_HPP
#define EPMODEL_CHILLERABSORPTION_IMPL_HPP

#include "WaterToWaterComponent/WaterToWaterComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ChillerAbsorption_Impl : public WaterToWaterComponent_Impl
    {
     public:
      using WaterToWaterComponent_Impl::WaterToWaterComponent_Impl;
      virtual ~ChillerAbsorption_Impl() override = default;

      unsigned supplyInletPort() const override;
      unsigned supplyOutletPort() const override;
      unsigned demandInletPort() const override;
      unsigned demandOutletPort() const override;
      unsigned tertiaryInletPort() const override;
      unsigned tertiaryOutletPort() const override;

      boost::optional<double> nominalCapacity() const;
      bool isNominalCapacityAutosized() const;
      bool setNominalCapacity(double nominalCapacity);
      void autosizeNominalCapacity();

      boost::optional<double> nominalPumpingPower() const;
      bool isNominalPumpingPowerAutosized() const;
      bool setNominalPumpingPower(double nominalPumpingPower);
      void autosizeNominalPumpingPower();

      double minimumPartLoadRatio() const;
      bool setMinimumPartLoadRatio(double minimumPartLoadRatio);

      double maximumPartLoadRatio() const;
      bool setMaximumPartLoadRatio(double maximumPartLoadRatio);

      double optimumPartLoadRatio() const;
      bool setOptimumPartLoadRatio(double optimumPartLoadRatio);

      double designCondenserInletTemperature() const;
      bool setDesignCondenserInletTemperature(double designCondenserInletTemperature);

      boost::optional<double> designChilledWaterFlowRate() const;
      bool isDesignChilledWaterFlowRateAutosized() const;
      bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
      void autosizeDesignChilledWaterFlowRate();

      boost::optional<double> designCondenserWaterFlowRate() const;
      bool isDesignCondenserWaterFlowRateAutosized() const;
      bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
      void autosizeDesignCondenserWaterFlowRate();

      double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve() const;
      bool setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve);

      double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve() const;
      bool setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve);

      double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve() const;
      bool setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(double coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve);

      double coefficient1ofthePumpElectricUsePartLoadRatioCurve() const;
      bool setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(double coefficient1ofthePumpElectricUsePartLoadRatioCurve);

      double coefficient2ofthePumpElectricUsePartLoadRatioCurve() const;
      bool setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(double coefficient2ofthePumpElectricUsePartLoadRatioCurve);

      double coefficient3ofthePumpElectricUsePartLoadRatioCurve() const;
      bool setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(double coefficient3ofthePumpElectricUsePartLoadRatioCurve);

      double chilledWaterOutletTemperatureLowerLimit() const;
      bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

      std::string chillerFlowMode() const;
      bool setChillerFlowMode(const std::string& chillerFlowMode);
      std::vector<std::string> chillerFlowModeValues() const;

      std::string generatorHeatSourceType() const;
      bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);
      std::vector<std::string> generatorHeatSourceTypeValues() const;

      boost::optional<double> designGeneratorFluidFlowRate() const;
      bool isDesignGeneratorFluidFlowRateAutosized() const;
      bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
      void autosizeDesignGeneratorFluidFlowRate();

      double degreeofSubcoolinginSteamGenerator() const;
      bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
