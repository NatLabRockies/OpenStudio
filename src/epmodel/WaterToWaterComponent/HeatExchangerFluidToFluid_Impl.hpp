/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERFLUIDTOFLUID_IMPL_HPP
#define EPMODEL_HEATEXCHANGERFLUIDTOFLUID_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatExchangerFluidToFluid_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatExchangerFluidToFluid_Impl() override = default;

  boost::optional<double> loopDemandSideDesignFlowRate() const;
  bool isLoopDemandSideDesignFlowRateAutosized() const;
  bool setLoopDemandSideDesignFlowRate(double loopDemandSideDesignFlowRate);
  void autosizeLoopDemandSideDesignFlowRate();

  boost::optional<double> loopSupplySideDesignFlowRate() const;
  bool isLoopSupplySideDesignFlowRateAutosized() const;
  bool setLoopSupplySideDesignFlowRate(double loopSupplySideDesignFlowRate);
  void autosizeLoopSupplySideDesignFlowRate();

  std::string heatExchangeModelType() const;
  bool isHeatExchangeModelTypeDefaulted() const;
  bool setHeatExchangeModelType(const std::string& heatExchangeModelType);
  void resetHeatExchangeModelType();

  boost::optional<double> heatExchangerUFactorTimesAreaValue() const;
  bool isHeatExchangerUFactorTimesAreaValueAutosized() const;
  bool setHeatExchangerUFactorTimesAreaValue(double heatExchangerUFactorTimesAreaValue);
  void autosizeHeatExchangerUFactorTimesAreaValue();

  std::string controlType() const;
  bool isControlTypeDefaulted() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();

  double minimumTemperatureDifferencetoActivateHeatExchanger() const;
  bool isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted() const;
  bool setMinimumTemperatureDifferencetoActivateHeatExchanger(double minimumTemperatureDifferencetoActivateHeatExchanger);
  void resetMinimumTemperatureDifferencetoActivateHeatExchanger();

  std::string heatTransferMeteringEndUseType() const;
  bool isHeatTransferMeteringEndUseTypeDefaulted() const;
  bool setHeatTransferMeteringEndUseType(const std::string& heatTransferMeteringEndUseType);
  void resetHeatTransferMeteringEndUseType();

  std::string componentOverrideCoolingControlTemperatureMode() const;
  bool isComponentOverrideCoolingControlTemperatureModeDefaulted() const;
  bool setComponentOverrideCoolingControlTemperatureMode(const std::string& componentOverrideCoolingControlTemperatureMode);
  void resetComponentOverrideCoolingControlTemperatureMode();

  double sizingFactor() const;
  bool isSizingFactorDefaulted() const;
  bool setSizingFactor(double sizingFactor);
  void resetSizingFactor();

  boost::optional<double> operationMinimumTemperatureLimit() const;
  bool setOperationMinimumTemperatureLimit(double operationMinimumTemperatureLimit);
  void resetOperationMinimumTemperatureLimit();

  boost::optional<double> operationMaximumTemperatureLimit() const;
  bool setOperationMaximumTemperatureLimit(double operationMaximumTemperatureLimit);
  void resetOperationMaximumTemperatureLimit();

  boost::optional<double> autosizedLoopDemandSideDesignFlowRate() const;
  boost::optional<double> autosizedLoopSupplySideDesignFlowRate() const;
  boost::optional<double> autosizedHeatExchangerUFactorTimesAreaValue() const;

  std::vector<std::string> heatExchangeModelTypeValues() const;
  std::vector<std::string> controlTypeValues() const;
  std::vector<std::string> heatTransferMeteringEndUseTypeValues() const;
  std::vector<std::string> componentOverrideCoolingControlTemperatureModeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
