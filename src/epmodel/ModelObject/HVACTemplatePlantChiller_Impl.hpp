/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTCHILLER_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTCHILLER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantChiller_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantChiller_Impl() override = default;

      std::vector<std::string> chillerTypeValues() const;
      std::vector<std::string> condenserTypeValues() const;

      std::string chillerType() const;
      bool setChillerType(const std::string& chillerType);

      boost::optional<double> capacity() const;
      bool isCapacityDefaulted() const;
      bool isCapacityAutosized() const;
      bool setCapacity(double capacity);
      void resetCapacity();
      void autosizeCapacity();

      double nominalCOP() const;
      bool setNominalCOP(double nominalCOP);

      std::string condenserType() const;
      bool isCondenserTypeDefaulted() const;
      bool setCondenserType(const std::string& condenserType);
      void resetCondenserType();

      boost::optional<std::string> priority() const;
      bool setPriority(const std::string& priority);
      void resetPriority();

      double sizingFactor() const;
      bool isSizingFactorDefaulted() const;
      bool setSizingFactor(double sizingFactor);
      void resetSizingFactor();

      double minimumPartLoadRatio() const;
      bool isMinimumPartLoadRatioDefaulted() const;
      bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
      void resetMinimumPartLoadRatio();

      double maximumPartLoadRatio() const;
      bool isMaximumPartLoadRatioDefaulted() const;
      bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
      void resetMaximumPartLoadRatio();

      double optimumPartLoadRatio() const;
      bool isOptimumPartLoadRatioDefaulted() const;
      bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
      void resetOptimumPartLoadRatio();

      double minimumUnloadingRatio() const;
      bool isMinimumUnloadingRatioDefaulted() const;
      bool setMinimumUnloadingRatio(double minimumUnloadingRatio);
      void resetMinimumUnloadingRatio();

      double leavingChilledWaterLowerTemperatureLimit() const;
      bool isLeavingChilledWaterLowerTemperatureLimitDefaulted() const;
      bool setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit);
      void resetLeavingChilledWaterLowerTemperatureLimit();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
