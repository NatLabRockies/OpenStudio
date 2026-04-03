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
class Schedule;

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
  // - Status: Partial Parity. The core fan-component scalar surface, availability-schedule wiring, and node insertion are aligned, but the canonical curve topology is still absent.
  // - Canonical Counterpart: openstudio::model::FanComponentModel.
  // - Implemented Parity: The availability-schedule plus scalar sizing, pulley/belt, efficiency, VFD, and end-use-subcategory accessors preserve the canonical field behavior exposed by `openstudio::model::FanComponentModel`.
  // - Documented Delta: Epmodel still omits the required and optional curve relationships that remain central to `openstudio::model`.
  // - Field/Storage Mapping: The availability schedule is represented as a typed `Schedule` relationship, while the scalar fields map directly to `Fan:ComponentModel` storage in EnergyPlus.
  // - Evidence: `src/model/FanComponentModel.hpp`, `src/model/FanComponentModel.cpp`, `src/model/test/FanComponentModel_GTest.cpp`, and `src/energyplus/ForwardTranslator/ForwardTranslateFanComponentModel.cpp` anchor the canonical API and translation behavior.
  // - Remaining Parity Work: Add the curve relationship APIs, plus any derived helper surface, once epmodel relationship support can represent them without weakening canonical semantics.
  Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(Schedule& schedule);

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
