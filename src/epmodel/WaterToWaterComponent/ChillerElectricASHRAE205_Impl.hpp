/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CHILLERELECTRICASHRAE205_IMPL_HPP
#define EPMODEL_CHILLERELECTRICASHRAE205_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ChillerElectricASHRAE205_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ChillerElectricASHRAE205_Impl() override = default;

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

  std::vector<std::string> performanceInterpolationMethodValues() const;
  std::vector<std::string> ambientTemperatureIndicatorValues() const;
  std::vector<std::string> chillerFlowModeValues() const;

 private:
  bool setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
