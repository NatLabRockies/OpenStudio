/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanOnOff.hpp"
#include "StraightComponent/FanOnOff_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveExponent.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  FanOnOff::FanOnOff(const Model& model) : StraightComponent(FanOnOff::iddObjectType(), model) {
    auto impl = getImpl<detail::FanOnOff_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    ScheduleConstant schedule(model);
    OS_ASSERT(schedule.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(schedule));
    OS_ASSERT(setFanTotalEfficiency(0.6));
    OS_ASSERT(setPressureRise(300.0));
    autosizeMaximumFlowRate();
    OS_ASSERT(setMotorEfficiency(0.8));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));

    CurveExponent fanPowerCurve(model);
    fanPowerCurve.setName("Fan On Off Power Curve");
    OS_ASSERT(fanPowerCurve.setCoefficient1Constant(1.0));
    OS_ASSERT(fanPowerCurve.setCoefficient2Constant(0.0));
    OS_ASSERT(fanPowerCurve.setCoefficient3Constant(0.0));
    OS_ASSERT(setFanPowerRatioFunctionofSpeedRatioCurve(fanPowerCurve));

    CurveCubic fanEfficiencyCurve(model);
    fanEfficiencyCurve.setName("Fan On Off Efficiency Curve");
    OS_ASSERT(fanEfficiencyCurve.setCoefficient1Constant(1.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient2x(0.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient4xPOW3(0.0));
    OS_ASSERT(setFanEfficiencyRatioFunctionofSpeedRatioCurve(fanEfficiencyCurve));
  }

  FanOnOff::FanOnOff(const Model& model, Schedule& availabilitySchedule) : StraightComponent(FanOnOff::iddObjectType(), model) {
    auto impl = getImpl<detail::FanOnOff_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setFanTotalEfficiency(0.6));
    OS_ASSERT(setPressureRise(300.0));
    autosizeMaximumFlowRate();
    OS_ASSERT(setMotorEfficiency(0.8));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));

    CurveExponent fanPowerCurve(model);
    fanPowerCurve.setName("Fan On Off Power Curve");
    OS_ASSERT(fanPowerCurve.setCoefficient1Constant(1.0));
    OS_ASSERT(fanPowerCurve.setCoefficient2Constant(0.0));
    OS_ASSERT(fanPowerCurve.setCoefficient3Constant(0.0));
    OS_ASSERT(setFanPowerRatioFunctionofSpeedRatioCurve(fanPowerCurve));

    CurveCubic fanEfficiencyCurve(model);
    fanEfficiencyCurve.setName("Fan On Off Efficiency Curve");
    OS_ASSERT(fanEfficiencyCurve.setCoefficient1Constant(1.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient2x(0.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient3xPOW2(0.0));
    OS_ASSERT(fanEfficiencyCurve.setCoefficient4xPOW3(0.0));
    OS_ASSERT(setFanEfficiencyRatioFunctionofSpeedRatioCurve(fanEfficiencyCurve));
  }

  FanOnOff::FanOnOff(const Model& model, Schedule& availabilitySchedule, Curve& fanPowerRatioFunctionofSpeedRatioCurve,
                     Curve& fanEfficiencyRatioFunctionofSpeedRatioCurve)
    : StraightComponent(FanOnOff::iddObjectType(), model) {
    auto impl = getImpl<detail::FanOnOff_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setFanTotalEfficiency(0.6));
    OS_ASSERT(setPressureRise(300.0));
    autosizeMaximumFlowRate();
    OS_ASSERT(setMotorEfficiency(0.8));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));
    OS_ASSERT(setFanPowerRatioFunctionofSpeedRatioCurve(fanPowerRatioFunctionofSpeedRatioCurve));
    OS_ASSERT(setFanEfficiencyRatioFunctionofSpeedRatioCurve(fanEfficiencyRatioFunctionofSpeedRatioCurve));
  }

  FanOnOff::FanOnOff(std::shared_ptr<detail::FanOnOff_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FanOnOff::iddObjectType() {
    return IddObjectType::Fan_OnOff;
  }

  bool FanOnOff::addToNode(Node& node) {
    return getImpl<detail::FanOnOff_Impl>()->addToNode(node);
  }

  Schedule FanOnOff::availabilitySchedule() const {
    return getImpl<detail::FanOnOff_Impl>()->availabilitySchedule();
  }

  bool FanOnOff::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::FanOnOff_Impl>()->setAvailabilitySchedule(schedule);
  }

  double FanOnOff::fanTotalEfficiency() const {
    return getImpl<detail::FanOnOff_Impl>()->fanTotalEfficiency();
  }

  bool FanOnOff::isFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::FanOnOff_Impl>()->isFanTotalEfficiencyDefaulted();
  }

  bool FanOnOff::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanOnOff_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  void FanOnOff::resetFanTotalEfficiency() {
    getImpl<detail::FanOnOff_Impl>()->resetFanTotalEfficiency();
  }

  double FanOnOff::fanEfficiency() const {
    return getImpl<detail::FanOnOff_Impl>()->fanTotalEfficiency();
  }

  bool FanOnOff::isFanEfficiencyDefaulted() const {
    return getImpl<detail::FanOnOff_Impl>()->isFanTotalEfficiencyDefaulted();
  }

  bool FanOnOff::setFanEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanOnOff_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  void FanOnOff::resetFanEfficiency() {
    getImpl<detail::FanOnOff_Impl>()->resetFanTotalEfficiency();
  }

  double FanOnOff::pressureRise() const {
    return getImpl<detail::FanOnOff_Impl>()->pressureRise();
  }

  bool FanOnOff::setPressureRise(double pressureRise) {
    return getImpl<detail::FanOnOff_Impl>()->setPressureRise(pressureRise);
  }

  boost::optional<double> FanOnOff::maximumFlowRate() const {
    return getImpl<detail::FanOnOff_Impl>()->maximumFlowRate();
  }

  bool FanOnOff::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::FanOnOff_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void FanOnOff::resetMaximumFlowRate() {
    getImpl<detail::FanOnOff_Impl>()->resetMaximumFlowRate();
  }

  void FanOnOff::autosizeMaximumFlowRate() {
    getImpl<detail::FanOnOff_Impl>()->autosizeMaximumFlowRate();
  }

  bool FanOnOff::isMaximumFlowRateAutosized() const {
    return getImpl<detail::FanOnOff_Impl>()->isMaximumFlowRateAutosized();
  }

  double FanOnOff::motorEfficiency() const {
    return getImpl<detail::FanOnOff_Impl>()->motorEfficiency();
  }

  bool FanOnOff::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::FanOnOff_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool FanOnOff::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::FanOnOff_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void FanOnOff::resetMotorEfficiency() {
    getImpl<detail::FanOnOff_Impl>()->resetMotorEfficiency();
  }

  boost::optional<double> FanOnOff::motorInAirstreamFraction() const {
    return getImpl<detail::FanOnOff_Impl>()->motorInAirstreamFraction();
  }

  bool FanOnOff::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
    return getImpl<detail::FanOnOff_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
  }

  void FanOnOff::resetMotorInAirstreamFraction() {
    getImpl<detail::FanOnOff_Impl>()->resetMotorInAirstreamFraction();
  }

  std::string FanOnOff::endUseSubcategory() const {
    return getImpl<detail::FanOnOff_Impl>()->endUseSubcategory();
  }

  bool FanOnOff::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::FanOnOff_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool FanOnOff::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::FanOnOff_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void FanOnOff::resetEndUseSubcategory() {
    getImpl<detail::FanOnOff_Impl>()->resetEndUseSubcategory();
  }

  Curve FanOnOff::fanPowerRatioFunctionofSpeedRatioCurve() const {
    return getImpl<detail::FanOnOff_Impl>()->fanPowerRatioFunctionofSpeedRatioCurve();
  }

  bool FanOnOff::setFanPowerRatioFunctionofSpeedRatioCurve(const Curve& curve) {
    return getImpl<detail::FanOnOff_Impl>()->setFanPowerRatioFunctionofSpeedRatioCurve(curve);
  }

  Curve FanOnOff::fanEfficiencyRatioFunctionofSpeedRatioCurve() const {
    return getImpl<detail::FanOnOff_Impl>()->fanEfficiencyRatioFunctionofSpeedRatioCurve();
  }

  bool FanOnOff::setFanEfficiencyRatioFunctionofSpeedRatioCurve(const Curve& curve) {
    return getImpl<detail::FanOnOff_Impl>()->setFanEfficiencyRatioFunctionofSpeedRatioCurve(curve);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FanOnOff_Impl::inletPort() const {
      return openstudio::Fan_OnOffFields::AirInletNodeName;
    }

    unsigned FanOnOff_Impl::outletPort() const {
      return openstudio::Fan_OnOffFields::AirOutletNodeName;
    }

    bool FanOnOff_Impl::addToNode(Node& node) {
      if (node.loop()) {
        return false;
      }
      if (node.airLoopHVACOutdoorAirSystem()) {
        return false;
      }
      return StraightComponent_Impl::addToNode(node);
    }

    openstudio::epmodel::Schedule FanOnOff_Impl::availabilitySchedule() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::Fan_OnOffFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool FanOnOff_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Fan_OnOffFields::AvailabilityScheduleName, "FanOnOff", "Availability", schedule);
    }

    double FanOnOff_Impl::fanTotalEfficiency() const {
      const auto value = getDouble(openstudio::Fan_OnOffFields::FanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanOnOff_Impl::isFanTotalEfficiencyDefaulted() const {
      return isEmpty(openstudio::Fan_OnOffFields::FanTotalEfficiency);
    }

    bool FanOnOff_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      return setDouble(openstudio::Fan_OnOffFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    void FanOnOff_Impl::resetFanTotalEfficiency() {
      const bool result = setString(openstudio::Fan_OnOffFields::FanTotalEfficiency, "");
      OS_ASSERT(result);
    }

    double FanOnOff_Impl::pressureRise() const {
      const auto value = getDouble(openstudio::Fan_OnOffFields::PressureRise, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanOnOff_Impl::setPressureRise(double pressureRise) {
      return setDouble(openstudio::Fan_OnOffFields::PressureRise, pressureRise);
    }

    boost::optional<double> FanOnOff_Impl::maximumFlowRate() const {
      return getDouble(openstudio::Fan_OnOffFields::MaximumFlowRate, true);
    }

    bool FanOnOff_Impl::setMaximumFlowRate(double maximumFlowRate) {
      return setDouble(openstudio::Fan_OnOffFields::MaximumFlowRate, maximumFlowRate);
    }

    void FanOnOff_Impl::resetMaximumFlowRate() {
      const bool result = setString(openstudio::Fan_OnOffFields::MaximumFlowRate, "");
      OS_ASSERT(result);
    }

    void FanOnOff_Impl::autosizeMaximumFlowRate() {
      const bool result = setString(openstudio::Fan_OnOffFields::MaximumFlowRate, "autosize");
      OS_ASSERT(result);
    }

    bool FanOnOff_Impl::isMaximumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Fan_OnOffFields::MaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    double FanOnOff_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::Fan_OnOffFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanOnOff_Impl::isMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::Fan_OnOffFields::MotorEfficiency);
    }

    bool FanOnOff_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::Fan_OnOffFields::MotorEfficiency, motorEfficiency);
    }

    void FanOnOff_Impl::resetMotorEfficiency() {
      const bool result = setString(openstudio::Fan_OnOffFields::MotorEfficiency, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanOnOff_Impl::motorInAirstreamFraction() const {
      return getDouble(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, true);
    }

    bool FanOnOff_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
      return setDouble(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, motorInAirstreamFraction);
    }

    void FanOnOff_Impl::resetMotorInAirstreamFraction() {
      const bool result = setString(openstudio::Fan_OnOffFields::MotorInAirstreamFraction, "");
      OS_ASSERT(result);
    }

    std::string FanOnOff_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Fan_OnOffFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanOnOff_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Fan_OnOffFields::EndUseSubcategory);
    }

    bool FanOnOff_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Fan_OnOffFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void FanOnOff_Impl::resetEndUseSubcategory() {
      const bool result = setString(openstudio::Fan_OnOffFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

    openstudio::epmodel::Curve FanOnOff_Impl::fanPowerRatioFunctionofSpeedRatioCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_OnOffFields::FanPowerRatioFunctionofSpeedRatioCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanOnOff_Impl::setFanPowerRatioFunctionofSpeedRatioCurve(const openstudio::epmodel::Curve& curve) {
      return setPointer(openstudio::Fan_OnOffFields::FanPowerRatioFunctionofSpeedRatioCurveName, curve.handle());
    }

    openstudio::epmodel::Curve FanOnOff_Impl::fanEfficiencyRatioFunctionofSpeedRatioCurve() const {
      auto curve = getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Curve>(
        openstudio::Fan_OnOffFields::FanEfficiencyRatioFunctionofSpeedRatioCurveName);
      OS_ASSERT(curve);
      return *curve;
    }

    bool FanOnOff_Impl::setFanEfficiencyRatioFunctionofSpeedRatioCurve(const openstudio::epmodel::Curve& curve) {
      return setPointer(openstudio::Fan_OnOffFields::FanEfficiencyRatioFunctionofSpeedRatioCurveName, curve.handle());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
