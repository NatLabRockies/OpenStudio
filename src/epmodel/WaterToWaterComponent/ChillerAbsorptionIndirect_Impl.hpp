/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP
#define EPMODEL_CHILLERABSORPTIONINDIRECT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ChillerAbsorptionIndirect_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ChillerAbsorptionIndirect_Impl() override = default;

      std::vector<std::string> chillerFlowModeValues() const;
      std::vector<std::string> generatorHeatSourceTypeValues() const;

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

      double condenserInletTemperatureLowerLimit() const;
      bool setCondenserInletTemperatureLowerLimit(double condenserInletTemperatureLowerLimit);

      double chilledWaterOutletTemperatureLowerLimit() const;
      bool setChilledWaterOutletTemperatureLowerLimit(double chilledWaterOutletTemperatureLowerLimit);

      boost::optional<double> designChilledWaterFlowRate() const;
      bool isDesignChilledWaterFlowRateAutosized() const;
      bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
      void autosizeDesignChilledWaterFlowRate();

      boost::optional<double> designCondenserWaterFlowRate() const;
      bool isDesignCondenserWaterFlowRateAutosized() const;
      bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
      void autosizeDesignCondenserWaterFlowRate();

      std::string chillerFlowMode() const;
      bool setChillerFlowMode(const std::string& chillerFlowMode);

      std::string generatorHeatSourceType() const;
      bool setGeneratorHeatSourceType(const std::string& generatorHeatSourceType);

      boost::optional<double> designGeneratorFluidFlowRate() const;
      bool isDesignGeneratorFluidFlowRateAutosized() const;
      bool setDesignGeneratorFluidFlowRate(double designGeneratorFluidFlowRate);
      void autosizeDesignGeneratorFluidFlowRate();

      double temperatureLowerLimitGeneratorInlet() const;
      bool setTemperatureLowerLimitGeneratorInlet(double temperatureLowerLimitGeneratorInlet);

      double degreeofSubcoolinginSteamGenerator() const;
      bool setDegreeofSubcoolinginSteamGenerator(double degreeofSubcoolinginSteamGenerator);

      double degreeofSubcoolinginSteamCondensateLoop() const;
      bool setDegreeofSubcoolinginSteamCondensateLoop(double degreeofSubcoolinginSteamCondensateLoop);

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
