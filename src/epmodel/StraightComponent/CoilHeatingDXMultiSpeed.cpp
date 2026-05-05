/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingDXMultiSpeed.hpp"
#include "StraightComponent/CoilHeatingDXMultiSpeed_Impl.hpp"

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_DX_MultiSpeed_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingDXMultiSpeed::CoilHeatingDXMultiSpeed(const Model& model) : StraightComponent(CoilHeatingDXMultiSpeed::iddObjectType(), model) {
    // Preserve model-constructor scalar defaults while excluding relationship and stage fields.
    auto availabilitySchedule = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-8.0));
    OS_ASSERT(setCrankcaseHeaterCapacity(0.0));
    OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
    OS_ASSERT(setMaximumOutdoorDryBulbTemperatureforDefrostOperation(5.0));
    OS_ASSERT(setDefrostStrategy("Resistive"));
    OS_ASSERT(setDefrostControl("OnDemand"));
    OS_ASSERT(setDefrostTimePeriodFraction(0.058333));
    autosizeResistiveDefrostHeaterCapacity();
    OS_ASSERT(setApplyPartLoadFractiontoSpeedsGreaterthan1(false));
    OS_ASSERT(setFuelType("NaturalGas"));
    OS_ASSERT(setRegionnumberforCalculatingHSPF(4));
  }

  CoilHeatingDXMultiSpeed::CoilHeatingDXMultiSpeed(std::shared_ptr<detail::CoilHeatingDXMultiSpeed_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingDXMultiSpeed::iddObjectType() {
    return IddObjectType::Coil_Heating_DX_MultiSpeed;
  }

  std::vector<std::string> CoilHeatingDXMultiSpeed::defrostStrategyValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostStrategy);
  }

  std::vector<std::string> CoilHeatingDXMultiSpeed::defrostControlValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostControl);
  }

  std::vector<std::string> CoilHeatingDXMultiSpeed::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_DX_MultiSpeedFields::FuelType);
  }

  bool CoilHeatingDXMultiSpeed::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> CoilHeatingDXMultiSpeed::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->availabilitySchedule();
  }

  bool CoilHeatingDXMultiSpeed::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setAvailabilitySchedule(schedule);
  }

  void CoilHeatingDXMultiSpeed::resetAvailabilitySchedule() {
    getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<Curve> CoilHeatingDXMultiSpeed::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->defrostEnergyInputRatioFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXMultiSpeed::setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setDefrostEnergyInputRatioFunctionofTemperatureCurve(curve);
  }

  void CoilHeatingDXMultiSpeed::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
    getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  }

  boost::optional<Curve> CoilHeatingDXMultiSpeed::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->crankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  bool CoilHeatingDXMultiSpeed::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(curve);
  }

  void CoilHeatingDXMultiSpeed::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
    getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  }

  double CoilHeatingDXMultiSpeed::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->minimumOutdoorDryBulbTemperatureforCompressorOperation();
  }

  bool CoilHeatingDXMultiSpeed::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
    double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      minimumOutdoorDryBulbTemperatureforCompressorOperation);
  }

  boost::optional<double> CoilHeatingDXMultiSpeed::outdoorDryBulbTemperaturetoTurnOnCompressor() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->outdoorDryBulbTemperaturetoTurnOnCompressor();
  }

  bool CoilHeatingDXMultiSpeed::setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setOutdoorDryBulbTemperaturetoTurnOnCompressor(
      outdoorDryBulbTemperaturetoTurnOnCompressor);
  }

  void CoilHeatingDXMultiSpeed::resetOutdoorDryBulbTemperaturetoTurnOnCompressor() {
    getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->resetOutdoorDryBulbTemperaturetoTurnOnCompressor();
  }

  double CoilHeatingDXMultiSpeed::crankcaseHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->crankcaseHeaterCapacity();
  }

  bool CoilHeatingDXMultiSpeed::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setCrankcaseHeaterCapacity(crankcaseHeaterCapacity);
  }

  double CoilHeatingDXMultiSpeed::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  }

  bool CoilHeatingDXMultiSpeed::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
    double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
  }

  double CoilHeatingDXMultiSpeed::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->maximumOutdoorDryBulbTemperatureforDefrostOperation();
  }

  bool CoilHeatingDXMultiSpeed::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      maximumOutdoorDryBulbTemperatureforDefrostOperation);
  }

  std::string CoilHeatingDXMultiSpeed::defrostStrategy() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->defrostStrategy();
  }

  bool CoilHeatingDXMultiSpeed::setDefrostStrategy(const std::string& defrostStrategy) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setDefrostStrategy(defrostStrategy);
  }

  std::string CoilHeatingDXMultiSpeed::defrostControl() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->defrostControl();
  }

  bool CoilHeatingDXMultiSpeed::setDefrostControl(const std::string& defrostControl) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setDefrostControl(defrostControl);
  }

  double CoilHeatingDXMultiSpeed::defrostTimePeriodFraction() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->defrostTimePeriodFraction();
  }

  bool CoilHeatingDXMultiSpeed::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setDefrostTimePeriodFraction(defrostTimePeriodFraction);
  }

  boost::optional<double> CoilHeatingDXMultiSpeed::resistiveDefrostHeaterCapacity() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->resistiveDefrostHeaterCapacity();
  }

  bool CoilHeatingDXMultiSpeed::isResistiveDefrostHeaterCapacityAutosized() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->isResistiveDefrostHeaterCapacityAutosized();
  }

  bool CoilHeatingDXMultiSpeed::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setResistiveDefrostHeaterCapacity(resistiveDefrostHeaterCapacity);
  }

  void CoilHeatingDXMultiSpeed::autosizeResistiveDefrostHeaterCapacity() {
    getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->autosizeResistiveDefrostHeaterCapacity();
  }

  bool CoilHeatingDXMultiSpeed::applyPartLoadFractiontoSpeedsGreaterthan1() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->applyPartLoadFractiontoSpeedsGreaterthan1();
  }

  bool CoilHeatingDXMultiSpeed::setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setApplyPartLoadFractiontoSpeedsGreaterthan1(applyPartLoadFractiontoSpeedsGreaterthan1);
  }

  std::string CoilHeatingDXMultiSpeed::fuelType() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->fuelType();
  }

  bool CoilHeatingDXMultiSpeed::setFuelType(const std::string& fuelType) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setFuelType(fuelType);
  }

  int CoilHeatingDXMultiSpeed::regionnumberforCalculatingHSPF() const {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->regionnumberforCalculatingHSPF();
  }

  bool CoilHeatingDXMultiSpeed::setRegionnumberforCalculatingHSPF(int regionnumberforCalculatingHSPF) {
    return getImpl<detail::CoilHeatingDXMultiSpeed_Impl>()->setRegionnumberforCalculatingHSPF(regionnumberforCalculatingHSPF);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingDXMultiSpeed_Impl::inletPort() const {
      return openstudio::Coil_Heating_DX_MultiSpeedFields::AirInletNodeName;
    }

    unsigned CoilHeatingDXMultiSpeed_Impl::outletPort() const {
      return openstudio::Coil_Heating_DX_MultiSpeedFields::AirOutletNodeName;
    }

    bool CoilHeatingDXMultiSpeed_Impl::addToNode(Node& node) {
      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    boost::optional<Schedule> CoilHeatingDXMultiSpeed_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName);
    }

    bool CoilHeatingDXMultiSpeed_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName, schedule.handle(), false);
    }

    void CoilHeatingDXMultiSpeed_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::AvailabilityScheduleName, openstudio::Handle(), false));
    }

    boost::optional<Curve> CoilHeatingDXMultiSpeed_Impl::defrostEnergyInputRatioFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName);
    }

    bool CoilHeatingDXMultiSpeed_Impl::setDefrostEnergyInputRatioFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilHeatingDXMultiSpeed_Impl::resetDefrostEnergyInputRatioFunctionofTemperatureCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, openstudio::Handle(), false));
    }

    boost::optional<Curve> CoilHeatingDXMultiSpeed_Impl::crankcaseHeaterCapacityFunctionofTemperatureCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(
        openstudio::Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName);
    }

    bool CoilHeatingDXMultiSpeed_Impl::setCrankcaseHeaterCapacityFunctionofTemperatureCurve(const Curve& curve) {
      return setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, curve.handle(), false);
    }

    void CoilHeatingDXMultiSpeed_Impl::resetCrankcaseHeaterCapacityFunctionofTemperatureCurve() {
      OS_ASSERT(
        setPointer(openstudio::Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, openstudio::Handle(), false));
    }

    double CoilHeatingDXMultiSpeed_Impl::minimumOutdoorDryBulbTemperatureforCompressorOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setMinimumOutdoorDryBulbTemperatureforCompressorOperation(
      double minimumOutdoorDryBulbTemperatureforCompressorOperation) {
      const bool result = setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation,
                                    minimumOutdoorDryBulbTemperatureforCompressorOperation);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> CoilHeatingDXMultiSpeed_Impl::outdoorDryBulbTemperaturetoTurnOnCompressor() const {
      return getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, true);
    }

    bool CoilHeatingDXMultiSpeed_Impl::setOutdoorDryBulbTemperaturetoTurnOnCompressor(double outdoorDryBulbTemperaturetoTurnOnCompressor) {
      const bool result = setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor,
                                    outdoorDryBulbTemperaturetoTurnOnCompressor);
      OS_ASSERT(result);
      return result;
    }

    void CoilHeatingDXMultiSpeed_Impl::resetOutdoorDryBulbTemperaturetoTurnOnCompressor() {
      const bool result = setString(openstudio::Coil_Heating_DX_MultiSpeedFields::OutdoorDryBulbTemperaturetoTurnOnCompressor, "");
      OS_ASSERT(result);
    }

    double CoilHeatingDXMultiSpeed_Impl::crankcaseHeaterCapacity() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setCrankcaseHeaterCapacity(double crankcaseHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::CrankcaseHeaterCapacity, crankcaseHeaterCapacity);
    }

    double CoilHeatingDXMultiSpeed_Impl::maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(
      double maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation) {
      return setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,
                       maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation);
    }

    double CoilHeatingDXMultiSpeed_Impl::maximumOutdoorDryBulbTemperatureforDefrostOperation() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setMaximumOutdoorDryBulbTemperatureforDefrostOperation(
      double maximumOutdoorDryBulbTemperatureforDefrostOperation) {
      return setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforDefrostOperation,
                       maximumOutdoorDryBulbTemperatureforDefrostOperation);
    }

    std::string CoilHeatingDXMultiSpeed_Impl::defrostStrategy() const {
      const auto value = getString(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostStrategy, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setDefrostStrategy(const std::string& defrostStrategy) {
      return setString(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostStrategy, defrostStrategy);
    }

    std::string CoilHeatingDXMultiSpeed_Impl::defrostControl() const {
      const auto value = getString(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostControl, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setDefrostControl(const std::string& defrostControl) {
      return setString(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostControl, defrostControl);
    }

    double CoilHeatingDXMultiSpeed_Impl::defrostTimePeriodFraction() const {
      const auto value = getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostTimePeriodFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setDefrostTimePeriodFraction(double defrostTimePeriodFraction) {
      return setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::DefrostTimePeriodFraction, defrostTimePeriodFraction);
    }

    boost::optional<double> CoilHeatingDXMultiSpeed_Impl::resistiveDefrostHeaterCapacity() const {
      return getDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, true);
    }

    bool CoilHeatingDXMultiSpeed_Impl::isResistiveDefrostHeaterCapacityAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setResistiveDefrostHeaterCapacity(double resistiveDefrostHeaterCapacity) {
      return setDouble(openstudio::Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, resistiveDefrostHeaterCapacity);
    }

    void CoilHeatingDXMultiSpeed_Impl::autosizeResistiveDefrostHeaterCapacity() {
      const bool result = setString(openstudio::Coil_Heating_DX_MultiSpeedFields::ResistiveDefrostHeaterCapacity, "autosize");
      OS_ASSERT(result);
    }

    bool CoilHeatingDXMultiSpeed_Impl::applyPartLoadFractiontoSpeedsGreaterthan1() const {
      const auto value = getString(openstudio::Coil_Heating_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool CoilHeatingDXMultiSpeed_Impl::setApplyPartLoadFractiontoSpeedsGreaterthan1(bool applyPartLoadFractiontoSpeedsGreaterthan1) {
      return setString(openstudio::Coil_Heating_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1,
                       applyPartLoadFractiontoSpeedsGreaterthan1 ? "Yes" : "No");
    }

    std::string CoilHeatingDXMultiSpeed_Impl::fuelType() const {
      const auto value = getString(openstudio::Coil_Heating_DX_MultiSpeedFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Coil_Heating_DX_MultiSpeedFields::FuelType, fuelType);
    }

    int CoilHeatingDXMultiSpeed_Impl::regionnumberforCalculatingHSPF() const {
      const auto value = getInt(openstudio::Coil_Heating_DX_MultiSpeedFields::RegionnumberforCalculatingHSPF, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingDXMultiSpeed_Impl::setRegionnumberforCalculatingHSPF(int regionnumberforCalculatingHSPF) {
      return setInt(openstudio::Coil_Heating_DX_MultiSpeedFields::RegionnumberforCalculatingHSPF, regionnumberforCalculatingHSPF);
    }

    std::vector<ModelObject> CoilHeatingDXMultiSpeed_Impl::children() const {
      std::vector<ModelObject> children;

      if (auto defrostCurve = defrostEnergyInputRatioFunctionofTemperatureCurve()) {
        children.emplace_back(std::move(*defrostCurve));
      }

      if (auto crankcaseCurve = crankcaseHeaterCapacityFunctionofTemperatureCurve()) {
        children.emplace_back(std::move(*crankcaseCurve));
      }

      return children;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
