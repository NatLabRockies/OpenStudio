/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/FanVariableVolume.hpp"
#include "StraightComponent/FanVariableVolume_Impl.hpp"

#include "Curve/CurveQuartic.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/FanSystemModel.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Fan_VariableVolume_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  FanVariableVolume::FanVariableVolume(const Model& model) : StraightComponent(FanVariableVolume::iddObjectType(), model) {
    auto impl = getImpl<detail::FanVariableVolume_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    ScheduleConstant schedule(model);
    OS_ASSERT(schedule.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(schedule));
    OS_ASSERT(setEndUseSubcategory(""));
    OS_ASSERT(setFanTotalEfficiency(0.6045));
    OS_ASSERT(setPressureRise(1017.592));
    autosizeMaximumFlowRate();
    OS_ASSERT(setFanPowerMinimumFlowRateInputMethod("FixedFlowRate"));
    OS_ASSERT(setFanPowerMinimumFlowFraction(0.0));
    OS_ASSERT(setFanPowerMinimumAirFlowRate(0.0));
    OS_ASSERT(setMotorEfficiency(0.93));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));
    OS_ASSERT(setFanPowerCoefficient1(0.0407598940));
    OS_ASSERT(setFanPowerCoefficient2(0.08804497));
    OS_ASSERT(setFanPowerCoefficient3(-0.072926120));
    OS_ASSERT(setFanPowerCoefficient4(0.9437398230));
    OS_ASSERT(setFanPowerCoefficient5(0.0));
  }

  FanVariableVolume::FanVariableVolume(const Model& model, Schedule& schedule) : StraightComponent(FanVariableVolume::iddObjectType(), model) {
    auto impl = getImpl<detail::FanVariableVolume_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setAvailabilitySchedule(schedule));
    OS_ASSERT(setEndUseSubcategory(""));
    OS_ASSERT(setFanTotalEfficiency(0.6045));
    OS_ASSERT(setPressureRise(1017.592));
    autosizeMaximumFlowRate();
    OS_ASSERT(setFanPowerMinimumFlowRateInputMethod("FixedFlowRate"));
    OS_ASSERT(setFanPowerMinimumFlowFraction(0.0));
    OS_ASSERT(setFanPowerMinimumAirFlowRate(0.0));
    OS_ASSERT(setMotorEfficiency(0.93));
    OS_ASSERT(setMotorInAirstreamFraction(1.0));
    OS_ASSERT(setFanPowerCoefficient1(0.0407598940));
    OS_ASSERT(setFanPowerCoefficient2(0.08804497));
    OS_ASSERT(setFanPowerCoefficient3(-0.072926120));
    OS_ASSERT(setFanPowerCoefficient4(0.9437398230));
    OS_ASSERT(setFanPowerCoefficient5(0.0));
  }

  FanVariableVolume::FanVariableVolume(std::shared_ptr<detail::FanVariableVolume_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType FanVariableVolume::iddObjectType() {
    return IddObjectType::Fan_VariableVolume;
  }

  bool FanVariableVolume::addToNode(Node& node) {
    return getImpl<detail::FanVariableVolume_Impl>()->addToNode(node);
  }

  Schedule FanVariableVolume::availabilitySchedule() const {
    return getImpl<detail::FanVariableVolume_Impl>()->availabilitySchedule();
  }

  bool FanVariableVolume::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::FanVariableVolume_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::vector<std::string> FanVariableVolume::fanPowerMinimumFlowRateInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod);
  }

  std::vector<std::string> FanVariableVolume::validFanPowerMinimumFlowRateInputMethodValues() {
    return FanVariableVolume::fanPowerMinimumFlowRateInputMethodValues();
  }

  double FanVariableVolume::fanTotalEfficiency() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanTotalEfficiency();
  }

  bool FanVariableVolume::isFanTotalEfficiencyDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isFanTotalEfficiencyDefaulted();
  }

  bool FanVariableVolume::setFanTotalEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  void FanVariableVolume::resetFanTotalEfficiency() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanTotalEfficiency();
  }

  double FanVariableVolume::fanEfficiency() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanTotalEfficiency();
  }

  bool FanVariableVolume::isFanEfficiencyDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isFanTotalEfficiencyDefaulted();
  }

  bool FanVariableVolume::setFanEfficiency(double fanTotalEfficiency) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanTotalEfficiency(fanTotalEfficiency);
  }

  void FanVariableVolume::resetFanEfficiency() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanTotalEfficiency();
  }

  double FanVariableVolume::pressureRise() const {
    return getImpl<detail::FanVariableVolume_Impl>()->pressureRise();
  }

  bool FanVariableVolume::setPressureRise(double pressureRise) {
    return getImpl<detail::FanVariableVolume_Impl>()->setPressureRise(pressureRise);
  }

  boost::optional<double> FanVariableVolume::maximumFlowRate() const {
    return getImpl<detail::FanVariableVolume_Impl>()->maximumFlowRate();
  }

  bool FanVariableVolume::isMaximumFlowRateAutosized() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isMaximumFlowRateAutosized();
  }

  bool FanVariableVolume::setMaximumFlowRate(double maximumFlowRate) {
    return getImpl<detail::FanVariableVolume_Impl>()->setMaximumFlowRate(maximumFlowRate);
  }

  void FanVariableVolume::resetMaximumFlowRate() {
    getImpl<detail::FanVariableVolume_Impl>()->resetMaximumFlowRate();
  }

  void FanVariableVolume::autosizeMaximumFlowRate() {
    getImpl<detail::FanVariableVolume_Impl>()->autosizeMaximumFlowRate();
  }

  std::string FanVariableVolume::fanPowerMinimumFlowRateInputMethod() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerMinimumFlowRateInputMethod();
  }

  bool FanVariableVolume::isFanPowerMinimumFlowRateInputMethodDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isFanPowerMinimumFlowRateInputMethodDefaulted();
  }

  bool FanVariableVolume::setFanPowerMinimumFlowRateInputMethod(const std::string& fanPowerMinimumFlowRateInputMethod) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerMinimumFlowRateInputMethod(fanPowerMinimumFlowRateInputMethod);
  }

  void FanVariableVolume::resetFanPowerMinimumFlowRateInputMethod() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerMinimumFlowRateInputMethod();
  }

  double FanVariableVolume::fanPowerMinimumFlowFraction() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerMinimumFlowFraction();
  }

  bool FanVariableVolume::isFanPowerMinimumFlowFractionDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isFanPowerMinimumFlowFractionDefaulted();
  }

  bool FanVariableVolume::setFanPowerMinimumFlowFraction(double fanPowerMinimumFlowFraction) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerMinimumFlowFraction(fanPowerMinimumFlowFraction);
  }

  void FanVariableVolume::resetFanPowerMinimumFlowFraction() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerMinimumFlowFraction();
  }

  boost::optional<double> FanVariableVolume::fanPowerMinimumAirFlowRate() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerMinimumAirFlowRate();
  }

  bool FanVariableVolume::setFanPowerMinimumAirFlowRate(double fanPowerMinimumAirFlowRate) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerMinimumAirFlowRate(fanPowerMinimumAirFlowRate);
  }

  void FanVariableVolume::resetFanPowerMinimumAirFlowRate() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerMinimumAirFlowRate();
  }

  double FanVariableVolume::motorEfficiency() const {
    return getImpl<detail::FanVariableVolume_Impl>()->motorEfficiency();
  }

  bool FanVariableVolume::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool FanVariableVolume::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::FanVariableVolume_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void FanVariableVolume::resetMotorEfficiency() {
    getImpl<detail::FanVariableVolume_Impl>()->resetMotorEfficiency();
  }

  double FanVariableVolume::motorInAirstreamFraction() const {
    return getImpl<detail::FanVariableVolume_Impl>()->motorInAirstreamFraction();
  }

  bool FanVariableVolume::isMotorInAirstreamFractionDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isMotorInAirstreamFractionDefaulted();
  }

  bool FanVariableVolume::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
    return getImpl<detail::FanVariableVolume_Impl>()->setMotorInAirstreamFraction(motorInAirstreamFraction);
  }

  void FanVariableVolume::resetMotorInAirstreamFraction() {
    getImpl<detail::FanVariableVolume_Impl>()->resetMotorInAirstreamFraction();
  }

  boost::optional<double> FanVariableVolume::fanPowerCoefficient1() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerCoefficient1();
  }

  bool FanVariableVolume::setFanPowerCoefficient1(double fanPowerCoefficient1) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerCoefficient1(fanPowerCoefficient1);
  }

  void FanVariableVolume::resetFanPowerCoefficient1() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerCoefficient1();
  }

  boost::optional<double> FanVariableVolume::fanPowerCoefficient2() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerCoefficient2();
  }

  bool FanVariableVolume::setFanPowerCoefficient2(double fanPowerCoefficient2) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerCoefficient2(fanPowerCoefficient2);
  }

  void FanVariableVolume::resetFanPowerCoefficient2() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerCoefficient2();
  }

  boost::optional<double> FanVariableVolume::fanPowerCoefficient3() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerCoefficient3();
  }

  bool FanVariableVolume::setFanPowerCoefficient3(double fanPowerCoefficient3) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerCoefficient3(fanPowerCoefficient3);
  }

  void FanVariableVolume::resetFanPowerCoefficient3() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerCoefficient3();
  }

  boost::optional<double> FanVariableVolume::fanPowerCoefficient4() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerCoefficient4();
  }

  bool FanVariableVolume::setFanPowerCoefficient4(double fanPowerCoefficient4) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerCoefficient4(fanPowerCoefficient4);
  }

  void FanVariableVolume::resetFanPowerCoefficient4() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerCoefficient4();
  }

  boost::optional<double> FanVariableVolume::fanPowerCoefficient5() const {
    return getImpl<detail::FanVariableVolume_Impl>()->fanPowerCoefficient5();
  }

  bool FanVariableVolume::setFanPowerCoefficient5(double fanPowerCoefficient5) {
    return getImpl<detail::FanVariableVolume_Impl>()->setFanPowerCoefficient5(fanPowerCoefficient5);
  }

  void FanVariableVolume::resetFanPowerCoefficient5() {
    getImpl<detail::FanVariableVolume_Impl>()->resetFanPowerCoefficient5();
  }

  std::string FanVariableVolume::endUseSubcategory() const {
    return getImpl<detail::FanVariableVolume_Impl>()->endUseSubcategory();
  }

  bool FanVariableVolume::isEndUseSubcategoryDefaulted() const {
    return getImpl<detail::FanVariableVolume_Impl>()->isEndUseSubcategoryDefaulted();
  }

  bool FanVariableVolume::setEndUseSubcategory(const std::string& endUseSubcategory) {
    return getImpl<detail::FanVariableVolume_Impl>()->setEndUseSubcategory(endUseSubcategory);
  }

  void FanVariableVolume::resetEndUseSubcategory() {
    getImpl<detail::FanVariableVolume_Impl>()->resetEndUseSubcategory();
  }

  FanSystemModel FanVariableVolume::convertToFanSystemModel() const {
    FanSystemModel fan(model());
    OS_ASSERT(fan.setName(nameString() + " FanSystemModel"));
    auto availability = availabilitySchedule();
    OS_ASSERT(fan.setAvailabilitySchedule(availability));
    OS_ASSERT(fan.setFanTotalEfficiency(fanTotalEfficiency()));
    OS_ASSERT(fan.setDesignPressureRise(pressureRise()));
    if (isMaximumFlowRateAutosized()) {
      fan.autosizeDesignMaximumAirFlowRate();
    } else if (auto value = maximumFlowRate()) {
      OS_ASSERT(fan.setDesignMaximumAirFlowRate(*value));
    }
    OS_ASSERT(fan.setMotorEfficiency(motorEfficiency()));
    OS_ASSERT(fan.setMotorInAirStreamFraction(motorInAirstreamFraction()));
    OS_ASSERT(fan.setSpeedControlMethod("Continuous"));
    OS_ASSERT(fan.setElectricPowerMinimumFlowRateFraction(0.0));
    fan.autosizeDesignElectricPowerConsumption();
    OS_ASSERT(fan.setDesignPowerSizingMethod("TotalEfficiencyAndPressure"));
    OS_ASSERT(fan.setEndUseSubcategory(endUseSubcategory()));

    CurveQuartic curve(model());
    OS_ASSERT(curve.setName(fan.nameString() + " Curve"));
    if (auto value = fanPowerCoefficient1()) {
      OS_ASSERT(curve.setCoefficient1Constant(*value));
    }
    if (auto value = fanPowerCoefficient2()) {
      OS_ASSERT(curve.setCoefficient2x(*value));
    }
    if (auto value = fanPowerCoefficient3()) {
      OS_ASSERT(curve.setCoefficient3xPOW2(*value));
    }
    if (auto value = fanPowerCoefficient4()) {
      OS_ASSERT(curve.setCoefficient4xPOW3(*value));
    }
    if (auto value = fanPowerCoefficient5()) {
      OS_ASSERT(curve.setCoefficient5xPOW4(*value));
    }
    OS_ASSERT(curve.setMinimumValueofx(0.0));
    OS_ASSERT(curve.setMaximumValueofx(1.0));
    OS_ASSERT(curve.setMinimumCurveOutput(0.0));
    OS_ASSERT(curve.setMaximumCurveOutput(5.0));
    OS_ASSERT(curve.setInputUnitTypeforX("Dimensionless"));
    OS_ASSERT(curve.setOutputUnitType("Dimensionless"));
    OS_ASSERT(fan.setElectricPowerFunctionofFlowFractionCurve(curve));

    return fan;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned FanVariableVolume_Impl::inletPort() const {
      return openstudio::Fan_VariableVolumeFields::AirInletNodeName;
    }

    unsigned FanVariableVolume_Impl::outletPort() const {
      return openstudio::Fan_VariableVolumeFields::AirOutletNodeName;
    }

    bool FanVariableVolume_Impl::addToNode(Node& node) {
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

    std::vector<std::string> FanVariableVolume_Impl::fanPowerMinimumFlowRateInputMethodValues() const {
      return FanVariableVolume::fanPowerMinimumFlowRateInputMethodValues();
    }

    double FanVariableVolume_Impl::fanTotalEfficiency() const {
      const auto value = getDouble(openstudio::Fan_VariableVolumeFields::FanTotalEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isFanTotalEfficiencyDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::FanTotalEfficiency);
    }

    bool FanVariableVolume_Impl::setFanTotalEfficiency(double fanTotalEfficiency) {
      return setDouble(openstudio::Fan_VariableVolumeFields::FanTotalEfficiency, fanTotalEfficiency);
    }

    void FanVariableVolume_Impl::resetFanTotalEfficiency() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanTotalEfficiency, "");
      OS_ASSERT(result);
    }

    double FanVariableVolume_Impl::pressureRise() const {
      const auto value = getDouble(openstudio::Fan_VariableVolumeFields::PressureRise, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::setPressureRise(double pressureRise) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::PressureRise, pressureRise);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> FanVariableVolume_Impl::maximumFlowRate() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::MaximumFlowRate, true);
    }

    bool FanVariableVolume_Impl::isMaximumFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Fan_VariableVolumeFields::MaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    openstudio::epmodel::Schedule FanVariableVolume_Impl::availabilitySchedule() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(openstudio::Fan_VariableVolumeFields::AvailabilityScheduleName);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Fan_VariableVolumeFields::AvailabilityScheduleName, "FanVariableVolume", "Availability",
                                           schedule);
    }

    bool FanVariableVolume_Impl::setMaximumFlowRate(double maximumFlowRate) {
      return setDouble(openstudio::Fan_VariableVolumeFields::MaximumFlowRate, maximumFlowRate);
    }

    void FanVariableVolume_Impl::resetMaximumFlowRate() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::MaximumFlowRate, "");
      OS_ASSERT(result);
    }

    void FanVariableVolume_Impl::autosizeMaximumFlowRate() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::MaximumFlowRate, "autosize");
      OS_ASSERT(result);
    }

    std::string FanVariableVolume_Impl::fanPowerMinimumFlowRateInputMethod() const {
      const auto value = getString(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isFanPowerMinimumFlowRateInputMethodDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod);
    }

    bool FanVariableVolume_Impl::setFanPowerMinimumFlowRateInputMethod(const std::string& fanPowerMinimumFlowRateInputMethod) {
      return setString(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, fanPowerMinimumFlowRateInputMethod);
    }

    void FanVariableVolume_Impl::resetFanPowerMinimumFlowRateInputMethod() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowRateInputMethod, "");
      OS_ASSERT(result);
    }

    double FanVariableVolume_Impl::fanPowerMinimumFlowFraction() const {
      const auto value = getDouble(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isFanPowerMinimumFlowFractionDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowFraction);
    }

    bool FanVariableVolume_Impl::setFanPowerMinimumFlowFraction(double fanPowerMinimumFlowFraction) {
      return setDouble(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, fanPowerMinimumFlowFraction);
    }

    void FanVariableVolume_Impl::resetFanPowerMinimumFlowFraction() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerMinimumFlowFraction, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerMinimumAirFlowRate() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, true);
    }

    bool FanVariableVolume_Impl::setFanPowerMinimumAirFlowRate(double fanPowerMinimumAirFlowRate) {
      return setDouble(openstudio::Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, fanPowerMinimumAirFlowRate);
    }

    void FanVariableVolume_Impl::resetFanPowerMinimumAirFlowRate() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerMinimumAirFlowRate, "");
      OS_ASSERT(result);
    }

    double FanVariableVolume_Impl::motorEfficiency() const {
      const auto value = getDouble(openstudio::Fan_VariableVolumeFields::MotorEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isMotorEfficiencyDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::MotorEfficiency);
    }

    bool FanVariableVolume_Impl::setMotorEfficiency(double motorEfficiency) {
      return setDouble(openstudio::Fan_VariableVolumeFields::MotorEfficiency, motorEfficiency);
    }

    void FanVariableVolume_Impl::resetMotorEfficiency() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::MotorEfficiency, "");
      OS_ASSERT(result);
    }

    double FanVariableVolume_Impl::motorInAirstreamFraction() const {
      const auto value = getDouble(openstudio::Fan_VariableVolumeFields::MotorInAirstreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isMotorInAirstreamFractionDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::MotorInAirstreamFraction);
    }

    bool FanVariableVolume_Impl::setMotorInAirstreamFraction(double motorInAirstreamFraction) {
      return setDouble(openstudio::Fan_VariableVolumeFields::MotorInAirstreamFraction, motorInAirstreamFraction);
    }

    void FanVariableVolume_Impl::resetMotorInAirstreamFraction() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::MotorInAirstreamFraction, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerCoefficient1() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient1, true);
    }

    bool FanVariableVolume_Impl::setFanPowerCoefficient1(double fanPowerCoefficient1) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient1, fanPowerCoefficient1);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetFanPowerCoefficient1() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient1, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerCoefficient2() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient2, true);
    }

    bool FanVariableVolume_Impl::setFanPowerCoefficient2(double fanPowerCoefficient2) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient2, fanPowerCoefficient2);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetFanPowerCoefficient2() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient2, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerCoefficient3() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient3, true);
    }

    bool FanVariableVolume_Impl::setFanPowerCoefficient3(double fanPowerCoefficient3) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient3, fanPowerCoefficient3);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetFanPowerCoefficient3() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient3, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerCoefficient4() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient4, true);
    }

    bool FanVariableVolume_Impl::setFanPowerCoefficient4(double fanPowerCoefficient4) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient4, fanPowerCoefficient4);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetFanPowerCoefficient4() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient4, "");
      OS_ASSERT(result);
    }

    boost::optional<double> FanVariableVolume_Impl::fanPowerCoefficient5() const {
      return getDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient5, true);
    }

    bool FanVariableVolume_Impl::setFanPowerCoefficient5(double fanPowerCoefficient5) {
      const bool result = setDouble(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient5, fanPowerCoefficient5);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetFanPowerCoefficient5() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::FanPowerCoefficient5, "");
      OS_ASSERT(result);
    }

    std::string FanVariableVolume_Impl::endUseSubcategory() const {
      const auto value = getString(openstudio::Fan_VariableVolumeFields::EndUseSubcategory, true);
      OS_ASSERT(value);
      return *value;
    }

    bool FanVariableVolume_Impl::isEndUseSubcategoryDefaulted() const {
      return isEmpty(openstudio::Fan_VariableVolumeFields::EndUseSubcategory);
    }

    bool FanVariableVolume_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::EndUseSubcategory, endUseSubcategory);
      OS_ASSERT(result);
      return result;
    }

    void FanVariableVolume_Impl::resetEndUseSubcategory() {
      const bool result = setString(openstudio::Fan_VariableVolumeFields::EndUseSubcategory, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
