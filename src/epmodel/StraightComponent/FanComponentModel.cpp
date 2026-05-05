/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanComponentModel.hpp"
#include "StraightComponent/FanComponentModel_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveExponentialDecay.hpp"
#include "Curve/CurveExponentialSkewNormal.hpp"
#include "Curve/CurveFanPressureRise.hpp"
#include "Curve/CurveLinear.hpp"
#include "Curve/CurveQuartic.hpp"
#include "Curve/CurveRectangularHyperbola1.hpp"
#include "Curve/CurveRectangularHyperbola2.hpp"
#include "Curve/CurveSigmoid.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_ComponentModel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FanComponentModel::FanComponentModel(const Model& model) : StraightComponent(FanComponentModel::iddObjectType(), model) {
    auto impl = getImpl<detail::FanComponentModel_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    ScheduleConstant schedule(model);
    OS_ASSERT(schedule.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(schedule));
    autosizeMaximumFlowRate();
    autosizeMinimumFlowRate();
    OS_ASSERT(setFanSizingFactor(1.0));
    autosizeMotorFanPulleyRatio();
    OS_ASSERT(setBeltSizingFactor(1.0));
    OS_ASSERT(setBeltFractionalTorqueTransition(0.167));
    OS_ASSERT(setMotorSizingFactor(1.0));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));
    OS_ASSERT(setVFDSizingFactor(1.0));
    OS_ASSERT(setEndUseSubcategory("General"));
    OS_ASSERT(setFanWheelDiameter(0.3048));
    OS_ASSERT(setFanOutletArea(0.0873288576));
    OS_ASSERT(setMaximumFanStaticEfficiency(0.514));
    OS_ASSERT(setEulerNumberatMaximumFanStaticEfficiency(9.76));
    OS_ASSERT(setMaximumDimensionlessFanAirflow(0.160331811647483));
    autosizeBeltMaximumTorque();
    OS_ASSERT(setMotorMaximumSpeed(1800.0));
    autosizeMaximumMotorOutputPower();
    autosizeMaximumVFDOutputPower();
    OS_ASSERT(setVFDEfficiencyType("Power"));

    CurveFanPressureRise fanPressureRiseCurve(model);
    OS_ASSERT(fanPressureRiseCurve.setName("VSD Example"));
    OS_ASSERT(fanPressureRiseCurve.setCoefficient1C1(1446.75833497653));
    OS_ASSERT(fanPressureRiseCurve.setCoefficient2C2(0.0));
    OS_ASSERT(fanPressureRiseCurve.setCoefficient3C3(0.0));
    OS_ASSERT(fanPressureRiseCurve.setCoefficient4C4(1.0));
    OS_ASSERT(fanPressureRiseCurve.setMinimumValueofQfan(0.0));
    OS_ASSERT(fanPressureRiseCurve.setMaximumValueofQfan(100.0));
    OS_ASSERT(fanPressureRiseCurve.setMinimumValueofPsm(62.5));
    OS_ASSERT(fanPressureRiseCurve.setMaximumValueofPsm(300.0));
    OS_ASSERT(fanPressureRiseCurve.setMinimumCurveOutput(0.0));
    OS_ASSERT(fanPressureRiseCurve.setMaximumCurveOutput(5000.0));
    OS_ASSERT(setFanPressureRiseCurve(fanPressureRiseCurve));

    CurveLinear ductStaticPressureResetCurve(model);
    OS_ASSERT(ductStaticPressureResetCurve.setName("DiagnosticSPR"));
    OS_ASSERT(ductStaticPressureResetCurve.setCoefficient1Constant(248.84));
    OS_ASSERT(ductStaticPressureResetCurve.setCoefficient2x(0.0));
    OS_ASSERT(ductStaticPressureResetCurve.setMinimumValueofx(0.0));
    OS_ASSERT(ductStaticPressureResetCurve.setMaximumValueofx(100.0));
    OS_ASSERT(ductStaticPressureResetCurve.setMinimumCurveOutput(62.5));
    OS_ASSERT(ductStaticPressureResetCurve.setMaximumCurveOutput(248.84));
    OS_ASSERT(setDuctStaticPressureResetCurve(ductStaticPressureResetCurve));

    CurveExponentialSkewNormal normalEfficiencyCurve(model);
    OS_ASSERT(normalEfficiencyCurve.setName("FanEff120CPLANormal"));
    OS_ASSERT(normalEfficiencyCurve.setCoefficient1C1(0.072613));
    OS_ASSERT(normalEfficiencyCurve.setCoefficient2C2(0.833213));
    OS_ASSERT(normalEfficiencyCurve.setCoefficient3C3(0.0));
    OS_ASSERT(normalEfficiencyCurve.setCoefficient4C4(0.013911));
    OS_ASSERT(normalEfficiencyCurve.setMinimumValueofx(-4.0));
    OS_ASSERT(normalEfficiencyCurve.setMaximumValueofx(5.0));
    OS_ASSERT(normalEfficiencyCurve.setMinimumCurveOutput(0.1));
    OS_ASSERT(normalEfficiencyCurve.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedFanStaticEfficiencyCurveNonStallRegion(normalEfficiencyCurve));

    CurveExponentialSkewNormal stallEfficiencyCurve(model);
    OS_ASSERT(stallEfficiencyCurve.setName("FanEff120CPLAStall"));
    OS_ASSERT(stallEfficiencyCurve.setCoefficient1C1(-1.674931));
    OS_ASSERT(stallEfficiencyCurve.setCoefficient2C2(1.980182));
    OS_ASSERT(stallEfficiencyCurve.setCoefficient3C3(0.0));
    OS_ASSERT(stallEfficiencyCurve.setCoefficient4C4(1.84495));
    OS_ASSERT(stallEfficiencyCurve.setMinimumValueofx(-4.0));
    OS_ASSERT(stallEfficiencyCurve.setMaximumValueofx(5.0));
    OS_ASSERT(stallEfficiencyCurve.setMinimumCurveOutput(0.1));
    OS_ASSERT(stallEfficiencyCurve.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedFanStaticEfficiencyCurveStallRegion(stallEfficiencyCurve));

    CurveSigmoid normalAirflowCurve(model);
    OS_ASSERT(normalAirflowCurve.setName("FanDimFlowNormal"));
    OS_ASSERT(normalAirflowCurve.setCoefficient1C1(0.0));
    OS_ASSERT(normalAirflowCurve.setCoefficient2C2(1.001423));
    OS_ASSERT(normalAirflowCurve.setCoefficient3C3(0.123935));
    OS_ASSERT(normalAirflowCurve.setCoefficient4C4(-0.476026));
    OS_ASSERT(normalAirflowCurve.setCoefficient5C5(1.0));
    OS_ASSERT(normalAirflowCurve.setMinimumValueofx(-4.0));
    OS_ASSERT(normalAirflowCurve.setMaximumValueofx(5.0));
    OS_ASSERT(normalAirflowCurve.setMinimumCurveOutput(0.05));
    OS_ASSERT(normalAirflowCurve.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedDimensionlessAirflowCurveNonStallRegion(normalAirflowCurve));

    CurveSigmoid stallAirflowCurve(model);
    OS_ASSERT(stallAirflowCurve.setName("FanDimFlowStall"));
    OS_ASSERT(stallAirflowCurve.setCoefficient1C1(0.0));
    OS_ASSERT(stallAirflowCurve.setCoefficient2C2(5.924993));
    OS_ASSERT(stallAirflowCurve.setCoefficient3C3(-1.91636));
    OS_ASSERT(stallAirflowCurve.setCoefficient4C4(-0.851779));
    OS_ASSERT(stallAirflowCurve.setCoefficient5C5(1.0));
    OS_ASSERT(stallAirflowCurve.setMinimumValueofx(-4.0));
    OS_ASSERT(stallAirflowCurve.setMaximumValueofx(5.0));
    OS_ASSERT(stallAirflowCurve.setMinimumCurveOutput(0.05));
    OS_ASSERT(stallAirflowCurve.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedDimensionlessAirflowCurveStallRegion(stallAirflowCurve));
  }

  FanComponentModel::FanComponentModel(const Model& model, const Curve& fanPressureRiseCurve, const Curve& ductStaticPressureResetCurve,
                                       const Curve& normalizedFanStaticEfficiencyCurveNonStallRegion,
                                       const Curve& normalizedFanStaticEfficiencyCurveStallRegion,
                                       const Curve& normalizedDimensionlessAirflowCurveNonStallRegion,
                                       const Curve& normalizedDimensionlessAirflowCurveStallRegion)
    : StraightComponent(FanComponentModel::iddObjectType(), model) {
    auto impl = getImpl<detail::FanComponentModel_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    ScheduleConstant schedule(model);
    OS_ASSERT(schedule.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(schedule));
    autosizeMaximumFlowRate();
    autosizeMinimumFlowRate();
    OS_ASSERT(setFanSizingFactor(1.0));
    autosizeMotorFanPulleyRatio();
    OS_ASSERT(setBeltSizingFactor(1.0));
    OS_ASSERT(setBeltFractionalTorqueTransition(0.167));
    OS_ASSERT(setMotorSizingFactor(1.0));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));
    OS_ASSERT(setVFDSizingFactor(1.0));
    OS_ASSERT(setEndUseSubcategory("General"));
    OS_ASSERT(setFanWheelDiameter(0.3048));
    OS_ASSERT(setFanOutletArea(0.0873288576));
    OS_ASSERT(setMaximumFanStaticEfficiency(0.514));
    OS_ASSERT(setEulerNumberatMaximumFanStaticEfficiency(9.76));
    OS_ASSERT(setMaximumDimensionlessFanAirflow(0.160331811647483));
    autosizeBeltMaximumTorque();
    OS_ASSERT(setMotorMaximumSpeed(1800.0));
    autosizeMaximumMotorOutputPower();
    autosizeMaximumVFDOutputPower();
    OS_ASSERT(setVFDEfficiencyType("Power"));
    OS_ASSERT(setFanPressureRiseCurve(fanPressureRiseCurve));
    OS_ASSERT(setDuctStaticPressureResetCurve(ductStaticPressureResetCurve));
    OS_ASSERT(setNormalizedFanStaticEfficiencyCurveNonStallRegion(normalizedFanStaticEfficiencyCurveNonStallRegion));
    OS_ASSERT(setNormalizedFanStaticEfficiencyCurveStallRegion(normalizedFanStaticEfficiencyCurveStallRegion));
    OS_ASSERT(setNormalizedDimensionlessAirflowCurveNonStallRegion(normalizedDimensionlessAirflowCurveNonStallRegion));
    OS_ASSERT(setNormalizedDimensionlessAirflowCurveStallRegion(normalizedDimensionlessAirflowCurveStallRegion));
  }

  FanComponentModel::FanComponentModel(std::shared_ptr<detail::FanComponentModel_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FanComponentModel::iddObjectType() {
    return IddObjectType::Fan_ComponentModel;
  }

  bool FanComponentModel::addToNode(Node& node) {
    return getImpl<detail::FanComponentModel_Impl>()->addToNode(node);
  }

  Schedule FanComponentModel::availabilitySchedule() const {
    return getImpl<detail::FanComponentModel_Impl>()->availabilitySchedule();
  }

  bool FanComponentModel::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::FanComponentModel_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::vector<std::string> FanComponentModel::vFDEfficiencyTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Fan_ComponentModelFields::VFDEfficiencyType);
  }

  boost::optional<double> FanComponentModel::maximumFlowRate() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumFlowRate();
  }

  bool FanComponentModel::isMaximumFlowRateAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isMaximumFlowRateAutosized();
  }

  bool FanComponentModel::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void FanComponentModel::autosizeMaximumFlowRate() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumFlowRate();
  }

  boost::optional<double> FanComponentModel::minimumFlowRate() const {
    return getImpl<detail::FanComponentModel_Impl>()->minimumFlowRate();
  }

  bool FanComponentModel::isMinimumFlowRateAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isMinimumFlowRateAutosized();
  }

  bool FanComponentModel::setMinimumFlowRate(double minimumFlowRate) {
    return getImpl<detail::FanComponentModel_Impl>()->setMinimumFlowRate(minimumFlowRate);
  }

  void FanComponentModel::autosizeMinimumFlowRate() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeMinimumFlowRate();
  }

  double FanComponentModel::fanSizingFactor() const {
    return getImpl<detail::FanComponentModel_Impl>()->fanSizingFactor();
  }

  bool FanComponentModel::setFanSizingFactor(double fanSizingFactor) {
    return getImpl<detail::FanComponentModel_Impl>()->setFanSizingFactor(fanSizingFactor);
  }

  double FanComponentModel::fanWheelDiameter() const {
    return getImpl<detail::FanComponentModel_Impl>()->fanWheelDiameter();
  }

  bool FanComponentModel::setFanWheelDiameter(double fanWheelDiameter) {
    return getImpl<detail::FanComponentModel_Impl>()->setFanWheelDiameter(fanWheelDiameter);
  }

  double FanComponentModel::fanOutletArea() const {
    return getImpl<detail::FanComponentModel_Impl>()->fanOutletArea();
  }

  bool FanComponentModel::setFanOutletArea(double fanOutletArea) {
    return getImpl<detail::FanComponentModel_Impl>()->setFanOutletArea(fanOutletArea);
  }

  double FanComponentModel::maximumFanStaticEfficiency() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumFanStaticEfficiency();
  }

  bool FanComponentModel::setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumFanStaticEfficiency(maximumFanStaticEfficiency);
  }

  double FanComponentModel::eulerNumberatMaximumFanStaticEfficiency() const {
    return getImpl<detail::FanComponentModel_Impl>()->eulerNumberatMaximumFanStaticEfficiency();
  }

  bool FanComponentModel::setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency) {
    return getImpl<detail::FanComponentModel_Impl>()->setEulerNumberatMaximumFanStaticEfficiency(eulerNumberatMaximumFanStaticEfficiency);
  }

  double FanComponentModel::maximumDimensionlessFanAirflow() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumDimensionlessFanAirflow();
  }

  bool FanComponentModel::setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumDimensionlessFanAirflow(maximumDimensionlessFanAirflow);
  }

  boost::optional<double> FanComponentModel::motorFanPulleyRatio() const {
    return getImpl<detail::FanComponentModel_Impl>()->motorFanPulleyRatio();
  }

  bool FanComponentModel::isMotorFanPulleyRatioAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isMotorFanPulleyRatioAutosized();
  }

  bool FanComponentModel::setMotorFanPulleyRatio(double motorFanPulleyRatio) {
    return getImpl<detail::FanComponentModel_Impl>()->setMotorFanPulleyRatio(motorFanPulleyRatio);
  }

  void FanComponentModel::autosizeMotorFanPulleyRatio() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeMotorFanPulleyRatio();
  }

  boost::optional<double> FanComponentModel::beltMaximumTorque() const {
    return getImpl<detail::FanComponentModel_Impl>()->beltMaximumTorque();
  }

  bool FanComponentModel::isBeltMaximumTorqueAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isBeltMaximumTorqueAutosized();
  }

  bool FanComponentModel::setBeltMaximumTorque(double beltMaximumTorque) {
    return getImpl<detail::FanComponentModel_Impl>()->setBeltMaximumTorque(beltMaximumTorque);
  }

  void FanComponentModel::autosizeBeltMaximumTorque() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeBeltMaximumTorque();
  }

  double FanComponentModel::beltSizingFactor() const {
    return getImpl<detail::FanComponentModel_Impl>()->beltSizingFactor();
  }

  bool FanComponentModel::setBeltSizingFactor(double beltSizingFactor) {
    return getImpl<detail::FanComponentModel_Impl>()->setBeltSizingFactor(beltSizingFactor);
  }

  double FanComponentModel::beltFractionalTorqueTransition() const {
    return getImpl<detail::FanComponentModel_Impl>()->beltFractionalTorqueTransition();
  }

  bool FanComponentModel::setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition) {
    return getImpl<detail::FanComponentModel_Impl>()->setBeltFractionalTorqueTransition(beltFractionalTorqueTransition);
  }

  double FanComponentModel::motorMaximumSpeed() const {
    return getImpl<detail::FanComponentModel_Impl>()->motorMaximumSpeed();
  }

  bool FanComponentModel::setMotorMaximumSpeed(double motorMaximumSpeed) {
    return getImpl<detail::FanComponentModel_Impl>()->setMotorMaximumSpeed(motorMaximumSpeed);
  }

  boost::optional<double> FanComponentModel::maximumMotorOutputPower() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumMotorOutputPower();
  }

  bool FanComponentModel::isMaximumMotorOutputPowerAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isMaximumMotorOutputPowerAutosized();
  }

  bool FanComponentModel::setMaximumMotorOutputPower(double maximumMotorOutputPower) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumMotorOutputPower(maximumMotorOutputPower);
  }

  void FanComponentModel::autosizeMaximumMotorOutputPower() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumMotorOutputPower();
  }

  double FanComponentModel::motorSizingFactor() const {
    return getImpl<detail::FanComponentModel_Impl>()->motorSizingFactor();
  }

  bool FanComponentModel::setMotorSizingFactor(double motorSizingFactor) {
    return getImpl<detail::FanComponentModel_Impl>()->setMotorSizingFactor(motorSizingFactor);
  }

  double FanComponentModel::motorInAirstreamFraction() const {
    return getImpl<detail::FanComponentModel_Impl>()->motorInAirstreamFraction();
  }

  bool FanComponentModel::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
    return getImpl<detail::FanComponentModel_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
  }

  std::string FanComponentModel::vFDEfficiencyType() const {
    return getImpl<detail::FanComponentModel_Impl>()->vFDEfficiencyType();
  }

  bool FanComponentModel::setVFDEfficiencyType(const std::string& vFDEfficiencyType) {
    return getImpl<detail::FanComponentModel_Impl>()->setVFDEfficiencyType(vFDEfficiencyType);
  }

  boost::optional<double> FanComponentModel::maximumVFDOutputPower() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumVFDOutputPower();
  }

  bool FanComponentModel::isMaximumVFDOutputPowerAutosized() const {
    return getImpl<detail::FanComponentModel_Impl>()->isMaximumVFDOutputPowerAutosized();
  }

  bool FanComponentModel::setMaximumVFDOutputPower(double maximumVFDOutputPower) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumVFDOutputPower(maximumVFDOutputPower);
  }

  void FanComponentModel::autosizeMaximumVFDOutputPower() {
    getImpl<detail::FanComponentModel_Impl>()->autosizeMaximumVFDOutputPower();
  }

  double FanComponentModel::vFDSizingFactor() const {
    return getImpl<detail::FanComponentModel_Impl>()->vFDSizingFactor();
  }

  bool FanComponentModel::setVFDSizingFactor(double vFDSizingFactor) {
    return getImpl<detail::FanComponentModel_Impl>()->setVFDSizingFactor(vFDSizingFactor);
  }

  Curve FanComponentModel::fanPressureRiseCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->fanPressureRiseCurve();
  }

  bool FanComponentModel::setFanPressureRiseCurve(const Curve& bivariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setFanPressureRiseCurve(bivariateFunctions);
  }

  Curve FanComponentModel::ductStaticPressureResetCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->ductStaticPressureResetCurve();
  }

  bool FanComponentModel::setDuctStaticPressureResetCurve(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setDuctStaticPressureResetCurve(univariateFunctions);
  }

  Curve FanComponentModel::normalizedFanStaticEfficiencyCurveNonStallRegion() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedFanStaticEfficiencyCurveNonStallRegion();
  }

  bool FanComponentModel::setNormalizedFanStaticEfficiencyCurveNonStallRegion(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedFanStaticEfficiencyCurveNonStallRegion(univariateFunctions);
  }

  Curve FanComponentModel::normalizedFanStaticEfficiencyCurveStallRegion() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedFanStaticEfficiencyCurveStallRegion();
  }

  bool FanComponentModel::setNormalizedFanStaticEfficiencyCurveStallRegion(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedFanStaticEfficiencyCurveStallRegion(univariateFunctions);
  }

  Curve FanComponentModel::normalizedDimensionlessAirflowCurveNonStallRegion() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedDimensionlessAirflowCurveNonStallRegion();
  }

  bool FanComponentModel::setNormalizedDimensionlessAirflowCurveNonStallRegion(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedDimensionlessAirflowCurveNonStallRegion(univariateFunctions);
  }

  Curve FanComponentModel::normalizedDimensionlessAirflowCurveStallRegion() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedDimensionlessAirflowCurveStallRegion();
  }

  bool FanComponentModel::setNormalizedDimensionlessAirflowCurveStallRegion(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedDimensionlessAirflowCurveStallRegion(univariateFunctions);
  }

  boost::optional<Curve> FanComponentModel::maximumBeltEfficiencyCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumBeltEfficiencyCurve();
  }

  bool FanComponentModel::setMaximumBeltEfficiencyCurve(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumBeltEfficiencyCurve(univariateFunctions);
  }

  void FanComponentModel::resetMaximumBeltEfficiencyCurve() {
    getImpl<detail::FanComponentModel_Impl>()->resetMaximumBeltEfficiencyCurve();
  }

  boost::optional<Curve> FanComponentModel::normalizedBeltEfficiencyCurveRegion1() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedBeltEfficiencyCurveRegion1();
  }

  bool FanComponentModel::setNormalizedBeltEfficiencyCurveRegion1(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedBeltEfficiencyCurveRegion1(univariateFunctions);
  }

  void FanComponentModel::resetNormalizedBeltEfficiencyCurveRegion1() {
    getImpl<detail::FanComponentModel_Impl>()->resetNormalizedBeltEfficiencyCurveRegion1();
  }

  boost::optional<Curve> FanComponentModel::normalizedBeltEfficiencyCurveRegion2() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedBeltEfficiencyCurveRegion2();
  }

  bool FanComponentModel::setNormalizedBeltEfficiencyCurveRegion2(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedBeltEfficiencyCurveRegion2(univariateFunctions);
  }

  void FanComponentModel::resetNormalizedBeltEfficiencyCurveRegion2() {
    getImpl<detail::FanComponentModel_Impl>()->resetNormalizedBeltEfficiencyCurveRegion2();
  }

  boost::optional<Curve> FanComponentModel::normalizedBeltEfficiencyCurveRegion3() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedBeltEfficiencyCurveRegion3();
  }

  bool FanComponentModel::setNormalizedBeltEfficiencyCurveRegion3(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedBeltEfficiencyCurveRegion3(univariateFunctions);
  }

  void FanComponentModel::resetNormalizedBeltEfficiencyCurveRegion3() {
    getImpl<detail::FanComponentModel_Impl>()->resetNormalizedBeltEfficiencyCurveRegion3();
  }

  boost::optional<Curve> FanComponentModel::maximumMotorEfficiencyCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->maximumMotorEfficiencyCurve();
  }

  bool FanComponentModel::setMaximumMotorEfficiencyCurve(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setMaximumMotorEfficiencyCurve(univariateFunctions);
  }

  void FanComponentModel::resetMaximumMotorEfficiencyCurve() {
    getImpl<detail::FanComponentModel_Impl>()->resetMaximumMotorEfficiencyCurve();
  }

  boost::optional<Curve> FanComponentModel::normalizedMotorEfficiencyCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->normalizedMotorEfficiencyCurve();
  }

  bool FanComponentModel::setNormalizedMotorEfficiencyCurve(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setNormalizedMotorEfficiencyCurve(univariateFunctions);
  }

  void FanComponentModel::resetNormalizedMotorEfficiencyCurve() {
    getImpl<detail::FanComponentModel_Impl>()->resetNormalizedMotorEfficiencyCurve();
  }

  boost::optional<Curve> FanComponentModel::vFDEfficiencyCurve() const {
    return getImpl<detail::FanComponentModel_Impl>()->vFDEfficiencyCurve();
  }

  bool FanComponentModel::setVFDEfficiencyCurve(const Curve& univariateFunctions) {
    return getImpl<detail::FanComponentModel_Impl>()->setVFDEfficiencyCurve(univariateFunctions);
  }

  void FanComponentModel::resetVFDEfficiencyCurve() {
    getImpl<detail::FanComponentModel_Impl>()->resetVFDEfficiencyCurve();
  }

  std::string FanComponentModel::endUseSubcategory() const {
    return getImpl<detail::FanComponentModel_Impl>()->endUseSubcategory();
  }

  bool FanComponentModel::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::FanComponentModel_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  bool FanComponentModel::assignDefaultOptionalCurves() {
    CurveQuartic maximumBeltEfficiency(model());
    OS_ASSERT(maximumBeltEfficiency.setName("BeltMaxEffMedium"));
    OS_ASSERT(maximumBeltEfficiency.setCoefficient1Constant(-0.09504));
    OS_ASSERT(maximumBeltEfficiency.setCoefficient2x(0.03415));
    OS_ASSERT(maximumBeltEfficiency.setCoefficient3xPOW2(-0.008897));
    OS_ASSERT(maximumBeltEfficiency.setCoefficient4xPOW3(0.001159));
    OS_ASSERT(maximumBeltEfficiency.setCoefficient5xPOW4(-6.132e-05));
    OS_ASSERT(maximumBeltEfficiency.setMinimumValueofx(-1.2));
    OS_ASSERT(maximumBeltEfficiency.setMaximumValueofx(6.2));
    OS_ASSERT(maximumBeltEfficiency.setMinimumCurveOutput(-4.6));
    OS_ASSERT(maximumBeltEfficiency.setMaximumCurveOutput(0.0));
    OS_ASSERT(setMaximumBeltEfficiencyCurve(maximumBeltEfficiency));

    CurveRectangularHyperbola2 beltEfficiencyRegion1(model());
    OS_ASSERT(beltEfficiencyRegion1.setName("BeltPartLoadRegion1"));
    OS_ASSERT(beltEfficiencyRegion1.setCoefficient1C1(0.920797));
    OS_ASSERT(beltEfficiencyRegion1.setCoefficient2C2(0.0262686));
    OS_ASSERT(beltEfficiencyRegion1.setCoefficient3C3(0.151594));
    OS_ASSERT(beltEfficiencyRegion1.setMinimumValueofx(0.0));
    OS_ASSERT(beltEfficiencyRegion1.setMaximumValueofx(1.0));
    OS_ASSERT(beltEfficiencyRegion1.setMinimumCurveOutput(0.01));
    OS_ASSERT(beltEfficiencyRegion1.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedBeltEfficiencyCurveRegion1(beltEfficiencyRegion1));

    CurveExponentialDecay beltEfficiencyRegion2(model());
    OS_ASSERT(beltEfficiencyRegion2.setName("BeltPartLoadRegion2"));
    OS_ASSERT(beltEfficiencyRegion2.setCoefficient1C1(1.011965));
    OS_ASSERT(beltEfficiencyRegion2.setCoefficient2C2(-0.339038));
    OS_ASSERT(beltEfficiencyRegion2.setCoefficient3C3(-3.43626));
    OS_ASSERT(beltEfficiencyRegion2.setMinimumValueofx(0.0));
    OS_ASSERT(beltEfficiencyRegion2.setMaximumValueofx(1.0));
    OS_ASSERT(beltEfficiencyRegion2.setMinimumCurveOutput(0.01));
    OS_ASSERT(beltEfficiencyRegion2.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedBeltEfficiencyCurveRegion2(beltEfficiencyRegion2));

    CurveRectangularHyperbola2 beltEfficiencyRegion3(model());
    OS_ASSERT(beltEfficiencyRegion3.setName("BeltPartLoadRegion3"));
    OS_ASSERT(beltEfficiencyRegion3.setCoefficient1C1(1.037778));
    OS_ASSERT(beltEfficiencyRegion3.setCoefficient2C2(0.0103068));
    OS_ASSERT(beltEfficiencyRegion3.setCoefficient3C3(-0.0268146));
    OS_ASSERT(beltEfficiencyRegion3.setMinimumValueofx(0.0));
    OS_ASSERT(beltEfficiencyRegion3.setMaximumValueofx(1.0));
    OS_ASSERT(beltEfficiencyRegion3.setMinimumCurveOutput(0.01));
    OS_ASSERT(beltEfficiencyRegion3.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedBeltEfficiencyCurveRegion3(beltEfficiencyRegion3));

    CurveRectangularHyperbola1 maximumMotorEfficiency(model());
    OS_ASSERT(maximumMotorEfficiency.setName("MotorMaxEffAvg"));
    OS_ASSERT(maximumMotorEfficiency.setCoefficient1C1(0.29228));
    OS_ASSERT(maximumMotorEfficiency.setCoefficient2C2(3.368739));
    OS_ASSERT(maximumMotorEfficiency.setCoefficient3C3(0.762471));
    OS_ASSERT(maximumMotorEfficiency.setMinimumValueofx(0.0));
    OS_ASSERT(maximumMotorEfficiency.setMaximumValueofx(7.6));
    OS_ASSERT(maximumMotorEfficiency.setMinimumCurveOutput(0.01));
    OS_ASSERT(maximumMotorEfficiency.setMaximumCurveOutput(1.0));
    OS_ASSERT(setMaximumMotorEfficiencyCurve(maximumMotorEfficiency));

    CurveRectangularHyperbola2 normalizedMotorEfficiency(model());
    OS_ASSERT(normalizedMotorEfficiency.setName("MotorPartLoad"));
    OS_ASSERT(normalizedMotorEfficiency.setCoefficient1C1(1.137209));
    OS_ASSERT(normalizedMotorEfficiency.setCoefficient2C2(0.0502359));
    OS_ASSERT(normalizedMotorEfficiency.setCoefficient3C3(-0.0891503));
    OS_ASSERT(normalizedMotorEfficiency.setMinimumValueofx(0.0));
    OS_ASSERT(normalizedMotorEfficiency.setMaximumValueofx(1.0));
    OS_ASSERT(normalizedMotorEfficiency.setMinimumCurveOutput(0.01));
    OS_ASSERT(normalizedMotorEfficiency.setMaximumCurveOutput(1.0));
    OS_ASSERT(setNormalizedMotorEfficiencyCurve(normalizedMotorEfficiency));

    CurveRectangularHyperbola2 vfdEfficiency(model());
    OS_ASSERT(vfdEfficiency.setName("VFDPartLoad"));
    OS_ASSERT(vfdEfficiency.setCoefficient1C1(0.987405));
    OS_ASSERT(vfdEfficiency.setCoefficient2C2(0.0155361));
    OS_ASSERT(vfdEfficiency.setCoefficient3C3(-0.0059365));
    OS_ASSERT(vfdEfficiency.setMinimumValueofx(0.0));
    OS_ASSERT(vfdEfficiency.setMaximumValueofx(1.0));
    OS_ASSERT(vfdEfficiency.setMinimumCurveOutput(0.01));
    OS_ASSERT(vfdEfficiency.setMaximumCurveOutput(1.0));
    OS_ASSERT(setVFDEfficiencyCurve(vfdEfficiency));

    return true;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FanComponentModel_Impl::inletPort() const {
      return openstudio::Fan_ComponentModelFields::AirInletNodeName;
    }

    unsigned FanComponentModel_Impl::outletPort() const {
      return openstudio::Fan_ComponentModelFields::AirOutletNodeName;
    }

    bool FanComponentModel_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      if (!StraightComponent_Impl::addToNode(node)) {
        return false;
      }

      auto airLoopImpl = airLoop->getImpl<detail::AirLoopHVAC_Impl>();
      OS_ASSERT(airLoopImpl);
      airLoopImpl->syncSetpointManagerMixedAirFanNodes();

      return true;
    }

    std::vector<std::string> FanComponentModel_Impl::vFDEfficiencyTypeValues() const {
      return FanComponentModel::vFDEfficiencyTypeValues();
    }

    boost::optional<double> FanComponentModel_Impl::maximumFlowRate() const {
      return getDouble(openstudio::Fan_ComponentModelFields::MaximumFlowRate, true);
    }

    bool FanComponentModel_Impl::isMaximumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    openstudio::epmodel::Schedule FanComponentModel_Impl::availabilitySchedule() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::Fan_ComponentModelFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Fan_ComponentModelFields::AvailabilityScheduleName, "FanComponentModel", "Availability",
                                           schedule);
    }

    bool FanComponentModel_Impl::setMaximumFlowRate(double maximumFlowRate) {
      return setDouble(openstudio::Fan_ComponentModelFields::MaximumFlowRate, maximumFlowRate);
    }

    void FanComponentModel_Impl::autosizeMaximumFlowRate() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumFlowRate, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> FanComponentModel_Impl::minimumFlowRate() const {
      return getDouble(openstudio::Fan_ComponentModelFields::MinimumFlowRate, true);
    }

    bool FanComponentModel_Impl::isMinimumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::MinimumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanComponentModel_Impl::setMinimumFlowRate(double minimumFlowRate) {
      return setDouble(openstudio::Fan_ComponentModelFields::MinimumFlowRate, minimumFlowRate);
    }

    void FanComponentModel_Impl::autosizeMinimumFlowRate() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MinimumFlowRate, "autosize");
      OS_ASSERT(result);
    }

    double FanComponentModel_Impl::fanSizingFactor() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setFanSizingFactor(double fanSizingFactor) {
      return setDouble(openstudio::Fan_ComponentModelFields::FanSizingFactor, fanSizingFactor);
    }

    double FanComponentModel_Impl::fanWheelDiameter() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanWheelDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setFanWheelDiameter(double fanWheelDiameter) {
      return setDouble(openstudio::Fan_ComponentModelFields::FanWheelDiameter, fanWheelDiameter);
    }

    double FanComponentModel_Impl::fanOutletArea() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::FanOutletArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setFanOutletArea(double fanOutletArea) {
      return setDouble(openstudio::Fan_ComponentModelFields::FanOutletArea, fanOutletArea);
    }

    double FanComponentModel_Impl::maximumFanStaticEfficiency() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::MaximumFanStaticEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setMaximumFanStaticEfficiency(double maximumFanStaticEfficiency) {
      return setDouble(openstudio::Fan_ComponentModelFields::MaximumFanStaticEfficiency, maximumFanStaticEfficiency);
    }

    double FanComponentModel_Impl::eulerNumberatMaximumFanStaticEfficiency() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setEulerNumberatMaximumFanStaticEfficiency(double eulerNumberatMaximumFanStaticEfficiency) {
      return setDouble(openstudio::Fan_ComponentModelFields::EulerNumberatMaximumFanStaticEfficiency, eulerNumberatMaximumFanStaticEfficiency);
    }

    double FanComponentModel_Impl::maximumDimensionlessFanAirflow() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setMaximumDimensionlessFanAirflow(double maximumDimensionlessFanAirflow) {
      return setDouble(openstudio::Fan_ComponentModelFields::MaximumDimensionlessFanAirflow, maximumDimensionlessFanAirflow);
    }

    boost::optional<double> FanComponentModel_Impl::motorFanPulleyRatio() const {
      return getDouble(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, true);
    }

    bool FanComponentModel_Impl::isMotorFanPulleyRatioAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanComponentModel_Impl::setMotorFanPulleyRatio(double motorFanPulleyRatio) {
      return setDouble(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, motorFanPulleyRatio);
    }

    void FanComponentModel_Impl::autosizeMotorFanPulleyRatio() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MotorFanPulleyRatio, "autosize");
      OS_ASSERT(result);
    }

    boost::optional<double> FanComponentModel_Impl::beltMaximumTorque() const {
      return getDouble(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, true);
    }

    bool FanComponentModel_Impl::isBeltMaximumTorqueAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanComponentModel_Impl::setBeltMaximumTorque(double beltMaximumTorque) {
      return setDouble(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, beltMaximumTorque);
    }

    void FanComponentModel_Impl::autosizeBeltMaximumTorque() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::BeltMaximumTorque, "autosize");
      OS_ASSERT(result);
    }

    double FanComponentModel_Impl::beltSizingFactor() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::BeltSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setBeltSizingFactor(double beltSizingFactor) {
      return setDouble(openstudio::Fan_ComponentModelFields::BeltSizingFactor, beltSizingFactor);
    }

    double FanComponentModel_Impl::beltFractionalTorqueTransition() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::BeltFractionalTorqueTransition, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setBeltFractionalTorqueTransition(double beltFractionalTorqueTransition) {
      return setDouble(openstudio::Fan_ComponentModelFields::BeltFractionalTorqueTransition, beltFractionalTorqueTransition);
    }

    double FanComponentModel_Impl::motorMaximumSpeed() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorMaximumSpeed, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setMotorMaximumSpeed(double motorMaximumSpeed) {
      return setDouble(openstudio::Fan_ComponentModelFields::MotorMaximumSpeed, motorMaximumSpeed);
    }

    boost::optional<double> FanComponentModel_Impl::maximumMotorOutputPower() const {
      return getDouble(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, true);
    }

    bool FanComponentModel_Impl::isMaximumMotorOutputPowerAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanComponentModel_Impl::setMaximumMotorOutputPower(double maximumMotorOutputPower) {
      return setDouble(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, maximumMotorOutputPower);
    }

    void FanComponentModel_Impl::autosizeMaximumMotorOutputPower() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumMotorOutputPower, "autosize");
      OS_ASSERT(result);
    }

    double FanComponentModel_Impl::motorSizingFactor() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setMotorSizingFactor(double motorSizingFactor) {
      return setDouble(openstudio::Fan_ComponentModelFields::MotorSizingFactor, motorSizingFactor);
    }

    double FanComponentModel_Impl::motorInAirstreamFraction() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::MotorInAirstreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
      return setDouble(openstudio::Fan_ComponentModelFields::MotorInAirstreamFraction, motorInAirstreamFraction);
    }

    std::string FanComponentModel_Impl::vFDEfficiencyType() const {
      const auto value = getString(openstudio::Fan_ComponentModelFields::VFDEfficiencyType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setVFDEfficiencyType(const std::string& vFDEfficiencyType) {
      return setString(openstudio::Fan_ComponentModelFields::VFDEfficiencyType, vFDEfficiencyType);
    }

    boost::optional<double> FanComponentModel_Impl::maximumVFDOutputPower() const {
      return getDouble(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, true);
    }

    bool FanComponentModel_Impl::isMaximumVFDOutputPowerAutosized() const {
      if (const auto value = getString(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool FanComponentModel_Impl::setMaximumVFDOutputPower(double maximumVFDOutputPower) {
      return setDouble(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, maximumVFDOutputPower);
    }

    void FanComponentModel_Impl::autosizeMaximumVFDOutputPower() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumVFDOutputPower, "autosize");
      OS_ASSERT(result);
    }

    double FanComponentModel_Impl::vFDSizingFactor() const {
      const auto value = getDouble(openstudio::Fan_ComponentModelFields::VFDSizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setVFDSizingFactor(double vFDSizingFactor) {
      return setDouble(openstudio::Fan_ComponentModelFields::VFDSizingFactor, vFDSizingFactor);
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::fanPressureRiseCurve() const {
      auto curve =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(openstudio::Fan_ComponentModelFields::FanPressureRiseCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setFanPressureRiseCurve(const openstudio::epmodel::Curve& bivariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::FanPressureRiseCurveName, bivariateFunctions.handle());
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::ductStaticPressureResetCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::DuctStaticPressureResetCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setDuctStaticPressureResetCurve(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::DuctStaticPressureResetCurveName, univariateFunctions.handle());
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::normalizedFanStaticEfficiencyCurveNonStallRegion() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameNonStallRegion);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setNormalizedFanStaticEfficiencyCurveNonStallRegion(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameNonStallRegion, univariateFunctions.handle());
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::normalizedFanStaticEfficiencyCurveStallRegion() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameStallRegion);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setNormalizedFanStaticEfficiencyCurveStallRegion(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedFanStaticEfficiencyCurveNameStallRegion, univariateFunctions.handle());
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::normalizedDimensionlessAirflowCurveNonStallRegion() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameNonStallRegion);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setNormalizedDimensionlessAirflowCurveNonStallRegion(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameNonStallRegion, univariateFunctions.handle());
    }

    openstudio::epmodel::Curve FanComponentModel_Impl::normalizedDimensionlessAirflowCurveStallRegion() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameStallRegion);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanComponentModel_Impl::setNormalizedDimensionlessAirflowCurveStallRegion(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedDimensionlessAirflowCurveNameStallRegion, univariateFunctions.handle());
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::maximumBeltEfficiencyCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::MaximumBeltEfficiencyCurveName);
    }

    bool FanComponentModel_Impl::setMaximumBeltEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::MaximumBeltEfficiencyCurveName, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetMaximumBeltEfficiencyCurve() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumBeltEfficiencyCurveName, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::normalizedBeltEfficiencyCurveRegion1() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion1);
    }

    bool FanComponentModel_Impl::setNormalizedBeltEfficiencyCurveRegion1(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion1, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetNormalizedBeltEfficiencyCurveRegion1() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion1, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::normalizedBeltEfficiencyCurveRegion2() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion2);
    }

    bool FanComponentModel_Impl::setNormalizedBeltEfficiencyCurveRegion2(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion2, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetNormalizedBeltEfficiencyCurveRegion2() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion2, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::normalizedBeltEfficiencyCurveRegion3() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion3);
    }

    bool FanComponentModel_Impl::setNormalizedBeltEfficiencyCurveRegion3(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion3, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetNormalizedBeltEfficiencyCurveRegion3() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::NormalizedBeltEfficiencyCurveNameRegion3, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::maximumMotorEfficiencyCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::MaximumMotorEfficiencyCurveName);
    }

    bool FanComponentModel_Impl::setMaximumMotorEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::MaximumMotorEfficiencyCurveName, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetMaximumMotorEfficiencyCurve() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::MaximumMotorEfficiencyCurveName, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::normalizedMotorEfficiencyCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_ComponentModelFields::NormalizedMotorEfficiencyCurveName);
    }

    bool FanComponentModel_Impl::setNormalizedMotorEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::NormalizedMotorEfficiencyCurveName, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetNormalizedMotorEfficiencyCurve() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::NormalizedMotorEfficiencyCurveName, "");
      OS_ASSERT(result);
    }

    boost::optional<openstudio::epmodel::Curve> FanComponentModel_Impl::vFDEfficiencyCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(openstudio::Fan_ComponentModelFields::VFDEfficiencyCurveName);
    }

    bool FanComponentModel_Impl::setVFDEfficiencyCurve(const openstudio::epmodel::Curve& univariateFunctions) {
      return setPointer(openstudio::Fan_ComponentModelFields::VFDEfficiencyCurveName, univariateFunctions.handle());
    }

    void FanComponentModel_Impl::resetVFDEfficiencyCurve() {
      const bool result = setString(openstudio::Fan_ComponentModelFields::VFDEfficiencyCurveName, "");
      OS_ASSERT(result);
    }

    std::string FanComponentModel_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Fan_ComponentModelFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanComponentModel_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Fan_ComponentModelFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
