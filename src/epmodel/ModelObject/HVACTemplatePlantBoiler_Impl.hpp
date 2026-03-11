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

  std::string boilerType() const;
  boost::optional<double> capacity() const;
  double efficiency() const;
  boost::optional<std::string> fuelType() const;
  boost::optional<std::string> priority() const;
  double sizingFactor() const;
  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double waterOutletUpperTemperatureLimit() const;
  boost::optional<std::string> templatePlantLoopType() const;

  bool isCapacityDefaulted() const;
  bool isCapacityAutosized() const;
  bool isEfficiencyDefaulted() const;
  bool isSizingFactorDefaulted() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool isWaterOutletUpperTemperatureLimitDefaulted() const;

  bool setBoilerType(const std::string& boilerType);
  bool setCapacity(double capacity);
  bool setEfficiency(double efficiency);
  bool setFuelType(const std::string& fuelType);
  bool setPriority(const std::string& priority);
  bool setSizingFactor(double sizingFactor);
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit);
  bool setTemplatePlantLoopType(const std::string& templatePlantLoopType);

  void resetCapacity();
  void autosizeCapacity();
  void resetEfficiency();
  void resetFuelType();
  void resetPriority();
  void resetSizingFactor();
  void resetMinimumPartLoadRatio();
  void resetMaximumPartLoadRatio();
  void resetOptimumPartLoadRatio();
  void resetWaterOutletUpperTemperatureLimit();
  void resetTemplatePlantLoopType();

  std::vector<std::string> boilerTypeValues() const;
  std::vector<std::string> fuelTypeValues() const;
  std::vector<std::string> templatePlantLoopTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
