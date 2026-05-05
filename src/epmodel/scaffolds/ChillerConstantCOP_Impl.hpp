/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERCONSTANTCOP_IMPL_HPP
#define EPMODEL_CHILLERCONSTANTCOP_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ChillerConstantCOP_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ChillerConstantCOP_Impl() override = default;

      std::vector<std::string> condenserTypeValues() const;
      std::vector<std::string> chillerFlowModeValues() const;

      boost::optional<double> nominalCapacity() const;
      bool setNominalCapacity(double nominalCapacity);
      bool isNominalCapacityAutosized() const;
      void autosizeNominalCapacity();

      double nominalCOP() const;
      bool setNominalCOP(double nominalCOP);

      boost::optional<double> designChilledWaterFlowRate() const;
      bool setDesignChilledWaterFlowRate(double designChilledWaterFlowRate);
      void resetDesignChilledWaterFlowRate();
      bool isDesignChilledWaterFlowRateAutosized() const;
      void autosizeDesignChilledWaterFlowRate();

      boost::optional<double> designCondenserWaterFlowRate() const;
      bool setDesignCondenserWaterFlowRate(double designCondenserWaterFlowRate);
      void resetDesignCondenserWaterFlowRate();
      bool isDesignCondenserWaterFlowRateAutosized() const;
      void autosizeDesignCondenserWaterFlowRate();

      std::string condenserType() const;
      bool setCondenserType(const std::string& condenserType);
      bool isCondenserTypeDefaulted() const;
      void resetCondenserType();

      std::string chillerFlowMode() const;
      bool setChillerFlowMode(const std::string& chillerFlowMode);
      bool isChillerFlowModeDefaulted() const;
      void resetChillerFlowMode();

      double sizingFactor() const;
      bool setSizingFactor(double sizingFactor);
      bool isSizingFactorDefaulted() const;
      void resetSizingFactor();

      double basinHeaterCapacity() const;
      bool setBasinHeaterCapacity(double basinHeaterCapacity);
      bool isBasinHeaterCapacityDefaulted() const;
      void resetBasinHeaterCapacity();

      double basinHeaterSetpointTemperature() const;
      bool setBasinHeaterSetpointTemperature(double basinHeaterSetpointTemperature);
      bool isBasinHeaterSetpointTemperatureDefaulted() const;
      void resetBasinHeaterSetpointTemperature();

      double thermosiphonMinimumTemperatureDifference() const;
      bool setThermosiphonMinimumTemperatureDifference(double thermosiphonMinimumTemperatureDifference);
      bool isThermosiphonMinimumTemperatureDifferenceDefaulted() const;
      void resetThermosiphonMinimumTemperatureDifference();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
