/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCOMPONENTMODEL_HPP
#define EPMODEL_FANCOMPONENTMODEL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class FanComponentModel_Impl;
}

class EPMODEL_API FanComponentModel : public StraightComponent
{
 public:
  explicit FanComponentModel(const Model& model);

  virtual ~FanComponentModel() override = default;
  FanComponentModel(const FanComponentModel& other) = default;
  FanComponentModel(FanComponentModel&& other) = default;
  FanComponentModel& operator=(const FanComponentModel&) = default;
  FanComponentModel& operator=(FanComponentModel&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> vFDEfficiencyTypeValues();

  bool addToNode(Node& node);

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::FanComponentModel scalar accessor names/signatures.
  // - Field Mapping: Scalar APIs below map directly to Fan:ComponentModel scalar fields in EnergyPlus.
  // - Field Mapping: Relationship fields (schedule/curve/node links) are intentionally excluded in this scaffold pass.
  // - ForwardTranslator evidence: ForwardTranslateFanComponentModel.cpp writes these scalar fields directly.
  // - TODO(parity): Add relationship-style APIs without changing preserved scalar signatures.
  boost::optional<double> maximumFlowRate() const;
  bool isMaximumFlowRateAutosized() const;
  bool setMaximumFlowRate(double maximumFlowRate);
  void autosizeMaximumFlowRate();

  boost::optional<double> minimumFlowRate() const;
  bool isMinimumFlowRateAutosized() const;
  bool setMinimumFlowRate(double minimumFlowRate);
  void autosizeMinimumFlowRate();

  double fanSizingFactor() const;
  bool setFanSizingFactor(double fanSizingFactor);

  double fanWheelDiameter() const;
  bool setFanWheelDiameter(double fanWheelDiameter);

  double fanOutletArea() const;
  bool setFanOutletArea(double fanOutletArea);

  double maximumFanStaticEfficiency() const;
  bool setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency);

  double eulerNumberatMaximumFanStaticEfficiency() const;
  bool setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency);

  double maximumDimensionlessFanAirflow() const;
  bool setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow);

  boost::optional<double> motorFanPulleyRatio() const;
  bool isMotorFanPulleyRatioAutosized() const;
  bool setMotorFanPulleyRatio(double motorFanPulleyRatio);
  void autosizeMotorFanPulleyRatio();

  boost::optional<double> beltMaximumTorque() const;
  bool isBeltMaximumTorqueAutosized() const;
  bool setBeltMaximumTorque(double beltMaximumTorque);
  void autosizeBeltMaximumTorque();

  double beltSizingFactor() const;
  bool setBeltSizingFactor(double beltSizingFactor);

  double beltFractionalTorqueTransition() const;
  bool setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition);

  double motorMaximumSpeed() const;
  bool setMotorMaximumSpeed(double motorMaximumSpeed);

  boost::optional<double> maximumMotorOutputPower() const;
  bool isMaximumMotorOutputPowerAutosized() const;
  bool setMaximumMotorOutputPower(double maximumMotorOutputPower);
  void autosizeMaximumMotorOutputPower();

  double motorSizingFactor() const;
  bool setMotorSizingFactor(double motorSizingFactor);

  double motorInAirstreamFraction() const;
  bool setMotorInAirstreamFraction(double motorInAirstreamFraction);

  std::string vFDEfficiencyType() const;
  bool setVFDEfficiencyType(const std::string& vFDEfficiencyType);

  boost::optional<double> maximumVFDOutputPower() const;
  bool isMaximumVFDOutputPowerAutosized() const;
  bool setMaximumVFDOutputPower(double maximumVFDOutputPower);
  void autosizeMaximumVFDOutputPower();

  double vFDSizingFactor() const;
  bool setVFDSizingFactor(double vFDSizingFactor);

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);

 protected:
  using ImplType = detail::FanComponentModel_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FanComponentModel(std::shared_ptr<detail::FanComponentModel_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
