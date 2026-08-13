/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"

#include "Model.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitSpeed_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_OperatingMode_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  CoilCoolingDXCurveFitOperatingMode::CoilCoolingDXCurveFitOperatingMode(const Model& model)
    : ModelObject(CoilCoolingDXCurveFitOperatingMode::iddObjectType(), model) {
    autosizeRatedGrossTotalCoolingCapacity();
    autosizeRatedEvaporatorAirFlowRate();
    autosizeRatedCondenserAirFlowRate();
    OS_ASSERT(setMaximumCyclingRate(0.0));
    OS_ASSERT(setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(0.0));
    OS_ASSERT(setLatentCapacityTimeConstant(0.0));
    OS_ASSERT(setNominalTimeforCondensateRemovaltoBegin(0.0));
    OS_ASSERT(setApplyLatentDegradationtoSpeedsGreaterthan1(false));
    OS_ASSERT(setCondenserType("AirCooled"));
    autosizeNominalEvaporativeCondenserPumpPower();
  }

  CoilCoolingDXCurveFitOperatingMode::CoilCoolingDXCurveFitOperatingMode(std::shared_ptr<detail::CoilCoolingDXCurveFitOperatingMode_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoilCoolingDXCurveFitOperatingMode::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX_CurveFit_OperatingMode;
  }

  std::vector<std::string> CoilCoolingDXCurveFitOperatingMode::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType);
  }

  boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedGrossTotalCoolingCapacity() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedGrossTotalCoolingCapacity();
  }

  bool CoilCoolingDXCurveFitOperatingMode::isRatedGrossTotalCoolingCapacityAutosized() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedGrossTotalCoolingCapacityAutosized();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedGrossTotalCoolingCapacity(ratedGrossTotalCoolingCapacity);
  }

  void CoilCoolingDXCurveFitOperatingMode::autosizeRatedGrossTotalCoolingCapacity() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedGrossTotalCoolingCapacity();
  }

  boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedEvaporatorAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedEvaporatorAirFlowRate();
  }

  bool CoilCoolingDXCurveFitOperatingMode::isRatedEvaporatorAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedEvaporatorAirFlowRateAutosized();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedEvaporatorAirFlowRate(ratedEvaporatorAirFlowRate);
  }

  void CoilCoolingDXCurveFitOperatingMode::autosizeRatedEvaporatorAirFlowRate() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedEvaporatorAirFlowRate();
  }

  boost::optional<double> CoilCoolingDXCurveFitOperatingMode::ratedCondenserAirFlowRate() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratedCondenserAirFlowRate();
  }

  bool CoilCoolingDXCurveFitOperatingMode::isRatedCondenserAirFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isRatedCondenserAirFlowRateAutosized();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatedCondenserAirFlowRate(ratedCondenserAirFlowRate);
  }

  void CoilCoolingDXCurveFitOperatingMode::autosizeRatedCondenserAirFlowRate() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeRatedCondenserAirFlowRate();
  }

  double CoilCoolingDXCurveFitOperatingMode::maximumCyclingRate() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->maximumCyclingRate();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setMaximumCyclingRate(double maximumCyclingRate) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setMaximumCyclingRate(maximumCyclingRate);
  }

  double CoilCoolingDXCurveFitOperatingMode::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
    double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
  }

  double CoilCoolingDXCurveFitOperatingMode::latentCapacityTimeConstant() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->latentCapacityTimeConstant();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setLatentCapacityTimeConstant(latentCapacityTimeConstant);
  }

  double CoilCoolingDXCurveFitOperatingMode::nominalTimeforCondensateRemovaltoBegin() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalTimeforCondensateRemovaltoBegin();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalTimeforCondensateRemovaltoBegin(
      nominalTimeforCondensateRemovaltoBegin);
  }

  bool CoilCoolingDXCurveFitOperatingMode::applyLatentDegradationtoSpeedsGreaterthan1() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->applyLatentDegradationtoSpeedsGreaterthan1();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setApplyLatentDegradationtoSpeedsGreaterthan1(
      applyLatentDegradationtoSpeedsGreaterthan1);
  }

  std::string CoilCoolingDXCurveFitOperatingMode::condenserType() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->condenserType();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setCondenserType(condenserType);
  }

  boost::optional<double> CoilCoolingDXCurveFitOperatingMode::nominalEvaporativeCondenserPumpPower() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalEvaporativeCondenserPumpPower();
  }

  bool CoilCoolingDXCurveFitOperatingMode::isNominalEvaporativeCondenserPumpPowerAutosized() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isNominalEvaporativeCondenserPumpPowerAutosized();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalEvaporativeCondenserPumpPower(nominalEvaporativeCondenserPumpPower);
  }

  void CoilCoolingDXCurveFitOperatingMode::autosizeNominalEvaporativeCondenserPumpPower() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->autosizeNominalEvaporativeCondenserPumpPower();
  }

  unsigned CoilCoolingDXCurveFitOperatingMode::nominalSpeedNumber() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->nominalSpeedNumber();
  }

  bool CoilCoolingDXCurveFitOperatingMode::isNominalSpeedNumberDefaulted() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->isNominalSpeedNumberDefaulted();
  }

  bool CoilCoolingDXCurveFitOperatingMode::setNominalSpeedNumber(unsigned nominalSpeedNumber) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setNominalSpeedNumber(nominalSpeedNumber);
  }

  void CoilCoolingDXCurveFitOperatingMode::resetNominalSpeedNumber() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->resetNominalSpeedNumber();
  }

  std::vector<CoilCoolingDXCurveFitSpeed> CoilCoolingDXCurveFitOperatingMode::speeds() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->speeds();
  }

  unsigned CoilCoolingDXCurveFitOperatingMode::numberOfSpeeds() const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->numberOfSpeeds();
  }

  boost::optional<unsigned> CoilCoolingDXCurveFitOperatingMode::speedIndex(const CoilCoolingDXCurveFitSpeed& speed) const {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->speedIndex(speed);
  }

  bool CoilCoolingDXCurveFitOperatingMode::addSpeed(const CoilCoolingDXCurveFitSpeed& speed) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->addSpeed(speed);
  }

  bool CoilCoolingDXCurveFitOperatingMode::addSpeed(const CoilCoolingDXCurveFitSpeed& speed, unsigned index) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->addSpeed(speed, index);
  }

  bool CoilCoolingDXCurveFitOperatingMode::setSpeedIndex(const CoilCoolingDXCurveFitSpeed& speed, unsigned index) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setSpeedIndex(speed, index);
  }

  bool CoilCoolingDXCurveFitOperatingMode::setSpeeds(const std::vector<CoilCoolingDXCurveFitSpeed>& speeds) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->setSpeeds(speeds);
  }

  void CoilCoolingDXCurveFitOperatingMode::removeAllSpeeds() {
    getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->removeAllSpeeds();
  }

  bool CoilCoolingDXCurveFitOperatingMode::removeSpeed(const CoilCoolingDXCurveFitSpeed& speed) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->removeSpeed(speed);
  }

  bool CoilCoolingDXCurveFitOperatingMode::removeSpeed(unsigned index) {
    return getImpl<detail::CoilCoolingDXCurveFitOperatingMode_Impl>()->removeSpeed(index);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedGrossTotalCoolingCapacity() const {
      return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, true);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedGrossTotalCoolingCapacityAutosized() const {
      if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedGrossTotalCoolingCapacity(double ratedGrossTotalCoolingCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, ratedGrossTotalCoolingCapacity);
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedGrossTotalCoolingCapacity() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedGrossTotalCoolingCapacity, "autosize"));
    }

    boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedEvaporatorAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, true);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedEvaporatorAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedEvaporatorAirFlowRate(double ratedEvaporatorAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, ratedEvaporatorAirFlowRate);
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedEvaporatorAirFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedEvaporatorAirFlowRate, "autosize"));
    }

    boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::ratedCondenserAirFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, true);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::isRatedCondenserAirFlowRateAutosized() const {
      if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatedCondenserAirFlowRate(double ratedCondenserAirFlowRate) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, ratedCondenserAirFlowRate);
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeRatedCondenserAirFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatedCondenserAirFlowRate, "autosize"));
    }

    double CoilCoolingDXCurveFitOperatingMode_Impl::maximumCyclingRate() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::MaximumCyclingRate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setMaximumCyclingRate(double maximumCyclingRate) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::MaximumCyclingRate, maximumCyclingRate);
    }

    double CoilCoolingDXCurveFitOperatingMode_Impl::ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity() const {
      const auto value =
        getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(
      double ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity,
                       ratioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity);
    }

    double CoilCoolingDXCurveFitOperatingMode_Impl::latentCapacityTimeConstant() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::LatentCapacityTimeConstant, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setLatentCapacityTimeConstant(double latentCapacityTimeConstant) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::LatentCapacityTimeConstant, latentCapacityTimeConstant);
    }

    double CoilCoolingDXCurveFitOperatingMode_Impl::nominalTimeforCondensateRemovaltoBegin() const {
      const auto value = getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalTimeforCondensateRemovaltoBegin, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalTimeforCondensateRemovaltoBegin(double nominalTimeforCondensateRemovaltoBegin) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalTimeforCondensateRemovaltoBegin,
                       nominalTimeforCondensateRemovaltoBegin);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::applyLatentDegradationtoSpeedsGreaterthan1() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::ApplyLatentDegradationtoSpeedsGreaterthan1, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setApplyLatentDegradationtoSpeedsGreaterthan1(bool applyLatentDegradationtoSpeedsGreaterthan1) {
      const bool result = setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::ApplyLatentDegradationtoSpeedsGreaterthan1,
                                    applyLatentDegradationtoSpeedsGreaterthan1 ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    std::string CoilCoolingDXCurveFitOperatingMode_Impl::condenserType() const {
      const auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::CondenserType, condenserType);
    }

    boost::optional<double> CoilCoolingDXCurveFitOperatingMode_Impl::nominalEvaporativeCondenserPumpPower() const {
      return getDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, true);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::isNominalEvaporativeCondenserPumpPowerAutosized() const {
      if (auto value = getString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalEvaporativeCondenserPumpPower(double nominalEvaporativeCondenserPumpPower) {
      return setDouble(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower,
                       nominalEvaporativeCondenserPumpPower);
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::autosizeNominalEvaporativeCondenserPumpPower() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalEvaporativeCondenserPumpPower, "autosize"));
    }

    unsigned CoilCoolingDXCurveFitOperatingMode_Impl::nominalSpeedNumber() const {
      if (isNominalSpeedNumberDefaulted()) {
        return numberOfSpeeds();
      }

      const auto value = getInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, false);
      OS_ASSERT(value);
      return static_cast<unsigned>(*value);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::isNominalSpeedNumberDefaulted() const {
      return !getInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, false);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setNominalSpeedNumber(unsigned nominalSpeedNumber) {
      if (nominalSpeedNumber > numberOfSpeeds()) {
        return false;
      }
      return setInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, static_cast<int>(nominalSpeedNumber));
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::resetNominalSpeedNumber() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, ""));
    }

    std::vector<CoilCoolingDXCurveFitSpeed> CoilCoolingDXCurveFitOperatingMode_Impl::speeds() const {
      std::vector<CoilCoolingDXCurveFitSpeed> result;
      for (const auto& extensibleGroup : extensibleGroups()) {
        const auto group = extensibleGroup.cast<WorkspaceExtensibleGroup>();
        if (auto target = group.getTarget(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields::SpeedName)) {
          if (auto speed = target->optionalCast<CoilCoolingDXCurveFitSpeed>()) {
            result.push_back(*speed);
          }
        }
      }
      return result;
    }

    unsigned CoilCoolingDXCurveFitOperatingMode_Impl::numberOfSpeeds() const {
      return numExtensibleGroups();
    }

    boost::optional<unsigned> CoilCoolingDXCurveFitOperatingMode_Impl::speedIndex(const CoilCoolingDXCurveFitSpeed& speed) const {
      if (speed.model() != model()) {
        return boost::none;
      }

      const auto groups = extensibleGroups();
      for (unsigned i = 0; i < groups.size(); ++i) {
        const auto group = groups[i].cast<WorkspaceExtensibleGroup>();
        if (auto target = group.getTarget(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields::SpeedName)) {
          if (target->handle() == speed.handle()) {
            return i + 1;
          }
        }
      }
      return boost::none;
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::addSpeed(const CoilCoolingDXCurveFitSpeed& speed) {
      auto newSpeeds = speeds();
      newSpeeds.push_back(speed);
      return setSpeeds(newSpeeds);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::addSpeed(const CoilCoolingDXCurveFitSpeed& speed, unsigned index) {
      if (speed.model() != model() || speedIndex(speed)) {
        return false;
      }

      auto newSpeeds = speeds();
      index = std::max(1u, std::min(index, static_cast<unsigned>(newSpeeds.size() + 1u)));
      newSpeeds.insert(newSpeeds.begin() + index - 1u, speed);
      return setSpeeds(newSpeeds);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setSpeedIndex(const CoilCoolingDXCurveFitSpeed& speed, unsigned index) {
      const auto oldIndex = speedIndex(speed);
      if (!oldIndex) {
        return false;
      }

      auto newSpeeds = speeds();
      index = std::max(1u, std::min(index, static_cast<unsigned>(newSpeeds.size())));
      newSpeeds.erase(newSpeeds.begin() + *oldIndex - 1u);
      newSpeeds.insert(newSpeeds.begin() + index - 1u, speed);
      return setSpeeds(newSpeeds);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::setSpeeds(const std::vector<CoilCoolingDXCurveFitSpeed>& newSpeeds) {
      for (unsigned i = 0; i < newSpeeds.size(); ++i) {
        if (newSpeeds[i].model() != model()) {
          return false;
        }
        for (unsigned j = 0; j < i; ++j) {
          if (newSpeeds[i].handle() == newSpeeds[j].handle()) {
            return false;
          }
        }
      }

      const auto oldSpeeds = speeds();
      const auto oldNominalSpeedNumber = getInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, false);
      auto operatingMode = getObject<ModelObject>();
      operatingMode.clearExtensibleGroups();

      for (const auto& speed : newSpeeds) {
        auto group = operatingMode.pushExtensibleGroup().optionalCast<WorkspaceExtensibleGroup>();
        if (!group || !group->setPointer(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields::SpeedName, speed.handle())) {
          operatingMode.clearExtensibleGroups();
          for (const auto& oldSpeed : oldSpeeds) {
            auto restoredGroup = operatingMode.pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
            OS_ASSERT(restoredGroup.setPointer(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeExtensibleFields::SpeedName, oldSpeed.handle()));
          }
          if (oldNominalSpeedNumber) {
            OS_ASSERT(setInt(openstudio::Coil_Cooling_DX_CurveFit_OperatingModeFields::NominalSpeedNumber, *oldNominalSpeedNumber));
          } else {
            resetNominalSpeedNumber();
          }
          return false;
        }
      }

      if (oldNominalSpeedNumber && static_cast<unsigned>(*oldNominalSpeedNumber) > newSpeeds.size()) {
        resetNominalSpeedNumber();
      }
      return true;
    }

    void CoilCoolingDXCurveFitOperatingMode_Impl::removeAllSpeeds() {
      getObject<ModelObject>().clearExtensibleGroups();
      resetNominalSpeedNumber();
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::removeSpeed(const CoilCoolingDXCurveFitSpeed& speed) {
      const auto index = speedIndex(speed);
      return index && removeSpeed(*index);
    }

    bool CoilCoolingDXCurveFitOperatingMode_Impl::removeSpeed(unsigned index) {
      auto newSpeeds = speeds();
      if (index == 0u || index > newSpeeds.size()) {
        return false;
      }
      newSpeeds.erase(newSpeeds.begin() + index - 1u);
      return setSpeeds(newSpeeds);
    }

    std::vector<std::string> CoilCoolingDXCurveFitOperatingMode_Impl::condenserTypeValues() const {
      return openstudio::epmodel::CoilCoolingDXCurveFitOperatingMode::condenserTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
