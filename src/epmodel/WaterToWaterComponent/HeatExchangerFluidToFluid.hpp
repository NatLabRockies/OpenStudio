/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP
#define EPMODEL_HEATEXCHANGERFLUIDTOFLUID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeatExchangerFluidToFluid_Impl;
}

class EPMODEL_API HeatExchangerFluidToFluid : public ModelObject
{
 public:
  explicit HeatExchangerFluidToFluid(const Model& model);

  virtual ~HeatExchangerFluidToFluid() override = default;
  HeatExchangerFluidToFluid(const HeatExchangerFluidToFluid& other) = default;
  HeatExchangerFluidToFluid(HeatExchangerFluidToFluid&& other) = default;
  HeatExchangerFluidToFluid& operator=(const HeatExchangerFluidToFluid&) = default;
  HeatExchangerFluidToFluid& operator=(HeatExchangerFluidToFluid&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> heatExchangeModelTypeValues();
  static std::vector<std::string> controlTypeValues();
  static std::vector<std::string> heatTransferMeteringEndUseTypeValues();
  static std::vector<std::string> componentOverrideCoolingControlTemperatureModeValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
  // - Field Mapping: Preserved scalar APIs map directly to E+ HeatExchanger:FluidToFluid scalar fields.
  // - Field Mapping: Relationship/node/reference fields are intentionally excluded from this scalar-only scaffold.
  // - Field Mapping: ForwardTranslator evidence confirms direct field mapping and Autosize string behavior.
  // - TODO(parity): Add excluded non-scalar APIs and loop-coupling behavior in a dedicated parity pass.
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

 protected:
  using ImplType = detail::HeatExchangerFluidToFluid_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeatExchangerFluidToFluid(std::shared_ptr<detail::HeatExchangerFluidToFluid_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
