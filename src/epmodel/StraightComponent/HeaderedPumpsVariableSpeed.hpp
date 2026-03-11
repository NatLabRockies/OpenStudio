/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSVARIABLESPEED_HPP
#define EPMODEL_HEADEREDPUMPSVARIABLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/optional.hpp>
#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HeaderedPumpsVariableSpeed_Impl;
}

class EPMODEL_API HeaderedPumpsVariableSpeed : public StraightComponent
{
 public:
  explicit HeaderedPumpsVariableSpeed(const Model& model);

  virtual ~HeaderedPumpsVariableSpeed() override = default;
  HeaderedPumpsVariableSpeed(const HeaderedPumpsVariableSpeed& other) = default;
  HeaderedPumpsVariableSpeed(HeaderedPumpsVariableSpeed&& other) = default;
  HeaderedPumpsVariableSpeed& operator=(const HeaderedPumpsVariableSpeed&) = default;
  HeaderedPumpsVariableSpeed& operator=(HeaderedPumpsVariableSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> flowSequencingControlSchemeValues();
  static std::vector<std::string> pumpControlTypeValues();
  static std::vector<std::string> designPowerSizingMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::HeaderedPumpsVariableSpeed scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: totalRatedFlowRate/ratedPumpHead/ratedPowerConsumption APIs map to E+ HeaderedPumps:VariableSpeed TotalDesignFlowRate/DesignPumpHead/DesignPowerConsumption.
  // - Field Mapping: pumpFlowRateSchedule, thermalZone, and inlet/outlet node name fields are relationship-like fields and are excluded in this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateHeaderedPumpsVariableSpeed.cpp maps the preserved API names to these E+ fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  boost::optional<double> totalRatedFlowRate() const;
  bool isTotalRatedFlowRateAutosized() const;

  int numberofPumpsinBank() const;

  std::string flowSequencingControlScheme() const;

  double ratedPumpHead() const;

  boost::optional<double> ratedPowerConsumption() const;
  bool isRatedPowerConsumptionAutosized() const;

  double motorEfficiency() const;

  double fractionofMotorInefficienciestoFluidStream() const;

  double coefficient1ofthePartLoadPerformanceCurve() const;

  double coefficient2ofthePartLoadPerformanceCurve() const;

  double coefficient3ofthePartLoadPerformanceCurve() const;

  double coefficient4ofthePartLoadPerformanceCurve() const;

  double minimumFlowRateFraction() const;

  std::string pumpControlType() const;

  double skinLossRadiativeFraction() const;

  std::string designPowerSizingMethod() const;

  double designElectricPowerPerUnitFlowRate() const;

  double designShaftPowerPerUnitFlowRatePerUnitHead() const;

  std::string endUseSubcategory() const;

  bool setTotalRatedFlowRate(double totalRatedFlowRate);
  void autosizeTotalRatedFlowRate();

  bool setNumberofPumpsinBank(int numberofPumpsinBank);

  bool setFlowSequencingControlScheme(const std::string& flowSequencingControlScheme);

  bool setRatedPumpHead(double ratedPumpHead);

  bool setRatedPowerConsumption(double ratedPowerConsumption);
  void autosizeRatedPowerConsumption();

  bool setMotorEfficiency(double motorEfficiency);

  bool setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream);

  bool setCoefficient1ofthePartLoadPerformanceCurve(double coefficient1ofthePartLoadPerformanceCurve);

  bool setCoefficient2ofthePartLoadPerformanceCurve(double coefficient2ofthePartLoadPerformanceCurve);

  bool setCoefficient3ofthePartLoadPerformanceCurve(double coefficient3ofthePartLoadPerformanceCurve);

  bool setCoefficient4ofthePartLoadPerformanceCurve(double coefficient4ofthePartLoadPerformanceCurve);

  bool setMinimumFlowRateFraction(double minimumFlowRateFraction);

  bool setPumpControlType(const std::string& pumpControlType);

  bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

  bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

  bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

  bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  boost::optional<double> autosizedTotalRatedFlowRate() const;

  boost::optional<double> autosizedRatedPowerConsumption() const;

 protected:
  using ImplType = detail::HeaderedPumpsVariableSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeaderedPumpsVariableSpeed(std::shared_ptr<detail::HeaderedPumpsVariableSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
