/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP
#define EPMODEL_HEADEREDPUMPSCONSTANTSPEED_HPP

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
class HeaderedPumpsConstantSpeed_Impl;
}

class EPMODEL_API HeaderedPumpsConstantSpeed : public StraightComponent
{
 public:
  explicit HeaderedPumpsConstantSpeed(const Model& model);

  virtual ~HeaderedPumpsConstantSpeed() override = default;
  HeaderedPumpsConstantSpeed(const HeaderedPumpsConstantSpeed& other) = default;
  HeaderedPumpsConstantSpeed(HeaderedPumpsConstantSpeed&& other) = default;
  HeaderedPumpsConstantSpeed& operator=(const HeaderedPumpsConstantSpeed&) = default;
  HeaderedPumpsConstantSpeed& operator=(HeaderedPumpsConstantSpeed&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> flowSequencingControlSchemeValues();
  static std::vector<std::string> pumpControlTypeValues();
  static std::vector<std::string> designPowerSizingMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::HeaderedPumpsConstantSpeed scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: totalRatedFlowRate/ratedPumpHead/ratedPowerConsumption APIs map to E+ HeaderedPumps:ConstantSpeed TotalDesignFlowRate/DesignPumpHead/DesignPowerConsumption.
  // - Field Mapping: pumpFlowRateSchedule, thermalZone, and inlet/outlet node name fields are relationship-like fields and are excluded in this scalar-only pass.
  // - ForwardTranslator evidence: ForwardTranslateHeaderedPumpsConstantSpeed.cpp maps the preserved API names to these E+ fields.
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

  bool setPumpControlType(const std::string& pumpControlType);

  bool setSkinLossRadiativeFraction(double skinLossRadiativeFraction);

  bool setDesignPowerSizingMethod(const std::string& designPowerSizingMethod);

  bool setDesignElectricPowerPerUnitFlowRate(double designElectricPowerPerUnitFlowRate);

  bool setDesignShaftPowerPerUnitFlowRatePerUnitHead(double designShaftPowerPerUnitFlowRatePerUnitHead);

  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  boost::optional<double> autosizedTotalRatedFlowRate() const;

  boost::optional<double> autosizedRatedPowerConsumption() const;

 protected:
  using ImplType = detail::HeaderedPumpsConstantSpeed_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HeaderedPumpsConstantSpeed(std::shared_ptr<detail::HeaderedPumpsConstantSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
