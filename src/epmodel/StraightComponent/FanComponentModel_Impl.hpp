/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCOMPONENTMODEL_IMPL_HPP
#define EPMODEL_FANCOMPONENTMODEL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
class Schedule;
class Curve;
namespace detail {

class EPMODEL_API FanComponentModel_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FanComponentModel_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
  bool addToNode(Node& node) override;
  openstudio::epmodel::Schedule availabilitySchedule() const;
  bool setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);

  std::vector<std::string> vFDEfficiencyTypeValues() const;

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

  openstudio::epmodel::Curve fanPressureRiseCurve() const;
  bool setFanPressureRiseCurve(const openstudio::epmodel::Curve& bivariateFunctions);

  openstudio::epmodel::Curve ductStaticPressureResetCurve() const;
  bool setDuctStaticPressureResetCurve(const openstudio::epmodel::Curve& univariateFunctions);

  openstudio::epmodel::Curve normalizedFanStaticEfficiencyCurveNonStallRegion() const;
  bool setNormalizedFanStaticEfficiencyCurveNonStallRegion(const openstudio::epmodel::Curve& univariateFunctions);

  openstudio::epmodel::Curve normalizedFanStaticEfficiencyCurveStallRegion() const;
  bool setNormalizedFanStaticEfficiencyCurveStallRegion(const openstudio::epmodel::Curve& univariateFunctions);

  openstudio::epmodel::Curve normalizedDimensionlessAirflowCurveNonStallRegion() const;
  bool setNormalizedDimensionlessAirflowCurveNonStallRegion(const openstudio::epmodel::Curve& univariateFunctions);

  openstudio::epmodel::Curve normalizedDimensionlessAirflowCurveStallRegion() const;
  bool setNormalizedDimensionlessAirflowCurveStallRegion(const openstudio::epmodel::Curve& univariateFunctions);

  boost::optional<openstudio::epmodel::Curve> maximumBeltEfficiencyCurve() const;
  bool setMaximumBeltEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions);
  void resetMaximumBeltEfficiencyCurve();

  boost::optional<openstudio::epmodel::Curve> normalizedBeltEfficiencyCurveRegion1() const;
  bool setNormalizedBeltEfficiencyCurveRegion1(const openstudio::epmodel::Curve& univariateFunctions);
  void resetNormalizedBeltEfficiencyCurveRegion1();

  boost::optional<openstudio::epmodel::Curve> normalizedBeltEfficiencyCurveRegion2() const;
  bool setNormalizedBeltEfficiencyCurveRegion2(const openstudio::epmodel::Curve& univariateFunctions);
  void resetNormalizedBeltEfficiencyCurveRegion2();

  boost::optional<openstudio::epmodel::Curve> normalizedBeltEfficiencyCurveRegion3() const;
  bool setNormalizedBeltEfficiencyCurveRegion3(const openstudio::epmodel::Curve& univariateFunctions);
  void resetNormalizedBeltEfficiencyCurveRegion3();

  boost::optional<openstudio::epmodel::Curve> maximumMotorEfficiencyCurve() const;
  bool setMaximumMotorEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions);
  void resetMaximumMotorEfficiencyCurve();

  boost::optional<openstudio::epmodel::Curve> normalizedMotorEfficiencyCurve() const;
  bool setNormalizedMotorEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions);
  void resetNormalizedMotorEfficiencyCurve();

  boost::optional<openstudio::epmodel::Curve> vFDEfficiencyCurve() const;
  bool setVFDEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions);
  void resetVFDEfficiencyCurve();

  std::string endUseSubcategory() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
