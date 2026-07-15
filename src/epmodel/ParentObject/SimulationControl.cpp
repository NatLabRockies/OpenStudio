/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/SimulationControl.hpp"
#include "ParentObject/SimulationControl_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SimulationControl_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SimulationControl::SimulationControl(const Model& model) : ParentObject(SimulationControl::iddObjectType(), model) {}

  SimulationControl::SimulationControl(std::shared_ptr<detail::SimulationControl_Impl> impl) : ParentObject(std::move(impl)) {}

  IddObjectType SimulationControl::iddObjectType() {
    return IddObjectType::SimulationControl;
  }

  bool SimulationControl::doZoneSizingCalculation() const {
    return getImpl<detail::SimulationControl_Impl>()->doZoneSizingCalculation();
  }

  bool SimulationControl::isDoZoneSizingCalculationDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isDoZoneSizingCalculationDefaulted();
  }

  bool SimulationControl::setDoZoneSizingCalculation(bool doZoneSizingCalculation) {
    return getImpl<detail::SimulationControl_Impl>()->setDoZoneSizingCalculation(doZoneSizingCalculation);
  }

  void SimulationControl::setDoZoneSizingCalculationNoFail(bool doZoneSizingCalculation) {
    const bool result = setDoZoneSizingCalculation(doZoneSizingCalculation);
    OS_ASSERT(result);
  }

  void SimulationControl::resetDoZoneSizingCalculation() {
    getImpl<detail::SimulationControl_Impl>()->resetDoZoneSizingCalculation();
  }

  bool SimulationControl::doSystemSizingCalculation() const {
    return getImpl<detail::SimulationControl_Impl>()->doSystemSizingCalculation();
  }

  bool SimulationControl::isDoSystemSizingCalculationDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isDoSystemSizingCalculationDefaulted();
  }

  bool SimulationControl::setDoSystemSizingCalculation(bool doSystemSizingCalculation) {
    return getImpl<detail::SimulationControl_Impl>()->setDoSystemSizingCalculation(doSystemSizingCalculation);
  }

  void SimulationControl::setDoSystemSizingCalculationNoFail(bool doSystemSizingCalculation) {
    const bool result = setDoSystemSizingCalculation(doSystemSizingCalculation);
    OS_ASSERT(result);
  }

  void SimulationControl::resetDoSystemSizingCalculation() {
    getImpl<detail::SimulationControl_Impl>()->resetDoSystemSizingCalculation();
  }

  bool SimulationControl::doPlantSizingCalculation() const {
    return getImpl<detail::SimulationControl_Impl>()->doPlantSizingCalculation();
  }

  bool SimulationControl::isDoPlantSizingCalculationDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isDoPlantSizingCalculationDefaulted();
  }

  bool SimulationControl::setDoPlantSizingCalculation(bool doPlantSizingCalculation) {
    return getImpl<detail::SimulationControl_Impl>()->setDoPlantSizingCalculation(doPlantSizingCalculation);
  }

  void SimulationControl::setDoPlantSizingCalculationNoFail(bool doPlantSizingCalculation) {
    const bool result = setDoPlantSizingCalculation(doPlantSizingCalculation);
    OS_ASSERT(result);
  }

  void SimulationControl::resetDoPlantSizingCalculation() {
    getImpl<detail::SimulationControl_Impl>()->resetDoPlantSizingCalculation();
  }

  bool SimulationControl::runSimulationforSizingPeriods() const {
    return getImpl<detail::SimulationControl_Impl>()->runSimulationforSizingPeriods();
  }

  bool SimulationControl::isRunSimulationforSizingPeriodsDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isRunSimulationforSizingPeriodsDefaulted();
  }

  bool SimulationControl::setRunSimulationforSizingPeriods(bool runSimulationforSizingPeriods) {
    return getImpl<detail::SimulationControl_Impl>()->setRunSimulationforSizingPeriods(runSimulationforSizingPeriods);
  }

  void SimulationControl::setRunSimulationforSizingPeriodsNoFail(bool runSimulationforSizingPeriods) {
    const bool result = setRunSimulationforSizingPeriods(runSimulationforSizingPeriods);
    OS_ASSERT(result);
  }

  void SimulationControl::resetRunSimulationforSizingPeriods() {
    getImpl<detail::SimulationControl_Impl>()->resetRunSimulationforSizingPeriods();
  }

  bool SimulationControl::runSimulationforWeatherFileRunPeriods() const {
    return getImpl<detail::SimulationControl_Impl>()->runSimulationforWeatherFileRunPeriods();
  }

  bool SimulationControl::isRunSimulationforWeatherFileRunPeriodsDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isRunSimulationforWeatherFileRunPeriodsDefaulted();
  }

  bool SimulationControl::setRunSimulationforWeatherFileRunPeriods(bool runSimulationforWeatherFileRunPeriods) {
    return getImpl<detail::SimulationControl_Impl>()->setRunSimulationforWeatherFileRunPeriods(runSimulationforWeatherFileRunPeriods);
  }

  void SimulationControl::setRunSimulationforWeatherFileRunPeriodsNoFail(bool runSimulationforWeatherFileRunPeriods) {
    const bool result = setRunSimulationforWeatherFileRunPeriods(runSimulationforWeatherFileRunPeriods);
    OS_ASSERT(result);
  }

  void SimulationControl::resetRunSimulationforWeatherFileRunPeriods() {
    getImpl<detail::SimulationControl_Impl>()->resetRunSimulationforWeatherFileRunPeriods();
  }

  bool SimulationControl::doHVACSizingSimulationforSizingPeriods() const {
    return getImpl<detail::SimulationControl_Impl>()->doHVACSizingSimulationforSizingPeriods();
  }

  bool SimulationControl::isDoHVACSizingSimulationforSizingPeriodsDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isDoHVACSizingSimulationforSizingPeriodsDefaulted();
  }

  bool SimulationControl::setDoHVACSizingSimulationforSizingPeriods(bool doHVACSizingSimulationforSizingPeriods) {
    return getImpl<detail::SimulationControl_Impl>()->setDoHVACSizingSimulationforSizingPeriods(doHVACSizingSimulationforSizingPeriods);
  }

  void SimulationControl::setDoHVACSizingSimulationforSizingPeriodsNoFail(bool doHVACSizingSimulationforSizingPeriods) {
    const bool result = setDoHVACSizingSimulationforSizingPeriods(doHVACSizingSimulationforSizingPeriods);
    OS_ASSERT(result);
  }

  void SimulationControl::resetDoHVACSizingSimulationforSizingPeriods() {
    getImpl<detail::SimulationControl_Impl>()->resetDoHVACSizingSimulationforSizingPeriods();
  }

  int SimulationControl::maximumNumberofHVACSizingSimulationPasses() const {
    return getImpl<detail::SimulationControl_Impl>()->maximumNumberofHVACSizingSimulationPasses();
  }

  bool SimulationControl::isMaximumNumberofHVACSizingSimulationPassesDefaulted() const {
    return getImpl<detail::SimulationControl_Impl>()->isMaximumNumberofHVACSizingSimulationPassesDefaulted();
  }

  bool SimulationControl::setMaximumNumberofHVACSizingSimulationPasses(int maximumNumberofHVACSizingSimulationPasses) {
    return getImpl<detail::SimulationControl_Impl>()->setMaximumNumberofHVACSizingSimulationPasses(maximumNumberofHVACSizingSimulationPasses);
  }

  void SimulationControl::resetMaximumNumberofHVACSizingSimulationPasses() {
    getImpl<detail::SimulationControl_Impl>()->resetMaximumNumberofHVACSizingSimulationPasses();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SimulationControl_Impl::doZoneSizingCalculation() const {
      const auto value = getString(openstudio::SimulationControlFields::DoZoneSizingCalculation, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isDoZoneSizingCalculationDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::DoZoneSizingCalculation);
    }

    bool SimulationControl_Impl::setDoZoneSizingCalculation(bool doZoneSizingCalculation) {
      const bool result = setString(openstudio::SimulationControlFields::DoZoneSizingCalculation, doZoneSizingCalculation ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetDoZoneSizingCalculation() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::DoZoneSizingCalculation, ""));
    }

    bool SimulationControl_Impl::doSystemSizingCalculation() const {
      const auto value = getString(openstudio::SimulationControlFields::DoSystemSizingCalculation, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isDoSystemSizingCalculationDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::DoSystemSizingCalculation);
    }

    bool SimulationControl_Impl::setDoSystemSizingCalculation(bool doSystemSizingCalculation) {
      const bool result = setString(openstudio::SimulationControlFields::DoSystemSizingCalculation, doSystemSizingCalculation ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetDoSystemSizingCalculation() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::DoSystemSizingCalculation, ""));
    }

    bool SimulationControl_Impl::doPlantSizingCalculation() const {
      const auto value = getString(openstudio::SimulationControlFields::DoPlantSizingCalculation, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isDoPlantSizingCalculationDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::DoPlantSizingCalculation);
    }

    bool SimulationControl_Impl::setDoPlantSizingCalculation(bool doPlantSizingCalculation) {
      const bool result = setString(openstudio::SimulationControlFields::DoPlantSizingCalculation, doPlantSizingCalculation ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetDoPlantSizingCalculation() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::DoPlantSizingCalculation, ""));
    }

    bool SimulationControl_Impl::runSimulationforSizingPeriods() const {
      const auto value = getString(openstudio::SimulationControlFields::RunSimulationforSizingPeriods, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isRunSimulationforSizingPeriodsDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::RunSimulationforSizingPeriods);
    }

    bool SimulationControl_Impl::setRunSimulationforSizingPeriods(bool runSimulationforSizingPeriods) {
      const bool result = setString(openstudio::SimulationControlFields::RunSimulationforSizingPeriods, runSimulationforSizingPeriods ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetRunSimulationforSizingPeriods() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::RunSimulationforSizingPeriods, ""));
    }

    bool SimulationControl_Impl::runSimulationforWeatherFileRunPeriods() const {
      const auto value = getString(openstudio::SimulationControlFields::RunSimulationforWeatherFileRunPeriods, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isRunSimulationforWeatherFileRunPeriodsDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::RunSimulationforWeatherFileRunPeriods);
    }

    bool SimulationControl_Impl::setRunSimulationforWeatherFileRunPeriods(bool runSimulationforWeatherFileRunPeriods) {
      const bool result =
        setString(openstudio::SimulationControlFields::RunSimulationforWeatherFileRunPeriods, runSimulationforWeatherFileRunPeriods ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetRunSimulationforWeatherFileRunPeriods() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::RunSimulationforWeatherFileRunPeriods, ""));
    }

    bool SimulationControl_Impl::doHVACSizingSimulationforSizingPeriods() const {
      const auto value = getString(openstudio::SimulationControlFields::DoHVACSizingSimulationforSizingPeriods, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SimulationControl_Impl::isDoHVACSizingSimulationforSizingPeriodsDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::DoHVACSizingSimulationforSizingPeriods);
    }

    bool SimulationControl_Impl::setDoHVACSizingSimulationforSizingPeriods(bool doHVACSizingSimulationforSizingPeriods) {
      const bool result =
        setString(openstudio::SimulationControlFields::DoHVACSizingSimulationforSizingPeriods, doHVACSizingSimulationforSizingPeriods ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SimulationControl_Impl::resetDoHVACSizingSimulationforSizingPeriods() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::DoHVACSizingSimulationforSizingPeriods, ""));
    }

    int SimulationControl_Impl::maximumNumberofHVACSizingSimulationPasses() const {
      const auto value = getInt(openstudio::SimulationControlFields::MaximumNumberofHVACSizingSimulationPasses, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SimulationControl_Impl::isMaximumNumberofHVACSizingSimulationPassesDefaulted() const {
      return isEmpty(openstudio::SimulationControlFields::MaximumNumberofHVACSizingSimulationPasses);
    }

    bool SimulationControl_Impl::setMaximumNumberofHVACSizingSimulationPasses(int maximumNumberofHVACSizingSimulationPasses) {
      return setInt(openstudio::SimulationControlFields::MaximumNumberofHVACSizingSimulationPasses, maximumNumberofHVACSizingSimulationPasses);
    }

    void SimulationControl_Impl::resetMaximumNumberofHVACSizingSimulationPasses() {
      OS_ASSERT(setString(openstudio::SimulationControlFields::MaximumNumberofHVACSizingSimulationPasses, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
