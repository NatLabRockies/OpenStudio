/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEPLANTBOILER_IMPL_HPP
#define EPMODEL_HVACTEMPLATEPLANTBOILER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API HVACTemplatePlantBoiler_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~HVACTemplatePlantBoiler_Impl() override = default;

      std::vector<std::string> boilerTypeValues() const;
      std::vector<std::string> fuelTypeValues() const;
      std::vector<std::string> templatePlantLoopTypeValues() const;

      std::string boilerType() const;
      bool setBoilerType(const std::string& boilerType);

      boost::optional<double> capacity() const;
      bool isCapacityDefaulted() const;
      bool isCapacityAutosized() const;
      bool setCapacity(double capacity);
      void resetCapacity();
      void autosizeCapacity();

      double efficiency() const;
      bool isEfficiencyDefaulted() const;
      bool setEfficiency(double efficiency);
      void resetEfficiency();

      boost::optional<std::string> fuelType() const;
      bool setFuelType(const std::string& fuelType);
      void resetFuelType();

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

      double waterOutletUpperTemperatureLimit() const;
      bool isWaterOutletUpperTemperatureLimitDefaulted() const;
      bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
      void resetWaterOutletUpperTemperatureLimit();

      boost::optional<std::string> templatePlantLoopType() const;
      bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);
      void resetTemplatePlantLoopType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
