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

  std::string chillerType() const;
  boost::optional<double> capacity() const;
  double nominalCOP() const;
  std::string condenserType() const;
  boost::optional<std::string> priority() const;
  double sizingFactor() const;
  double minimumPartLoadRatio() const;
  double maximumPartLoadRatio() const;
  double optimumPartLoadRatio() const;
  double minimumUnloadingRatio() const;
  double leavingChilledWaterLowerTemperatureLimit() const;

  bool isCapacityDefaulted() const;
  bool isCapacityAutosized() const;
  bool isCondenserTypeDefaulted() const;
  bool isSizingFactorDefaulted() const;
  bool isMinimumPartLoadRatioDefaulted() const;
  bool isMaximumPartLoadRatioDefaulted() const;
  bool isOptimumPartLoadRatioDefaulted() const;
  bool isMinimumUnloadingRatioDefaulted() const;
  bool isLeavingChilledWaterLowerTemperatureLimitDefaulted() const;

  bool setChillerType(const std::string& chillerType);
  bool setCapacity(double capacity);
  bool setNominalCOP(double nominalCOP);
  bool setCondenserType(const std::string& condenserType);
  bool setPriority(const std::string& priority);
  bool setSizingFactor(double sizingFactor);
  bool setMinimumPartLoadRatio(double minimumPartLoadRatio);
  bool setMaximumPartLoadRatio(double maximumPartLoadRatio);
  bool setOptimumPartLoadRatio(double optimumPartLoadRatio);
  bool setMinimumUnloadingRatio(double minimumUnloadingRatio);
  bool setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit);

  void resetCapacity();
  void autosizeCapacity();
  void resetCondenserType();
  void resetPriority();
  void resetSizingFactor();
  void resetMinimumPartLoadRatio();
  void resetMaximumPartLoadRatio();
  void resetOptimumPartLoadRatio();
  void resetMinimumUnloadingRatio();
  void resetLeavingChilledWaterLowerTemperatureLimit();

  std::vector<std::string> chillerTypeValues() const;
  std::vector<std::string> condenserTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
