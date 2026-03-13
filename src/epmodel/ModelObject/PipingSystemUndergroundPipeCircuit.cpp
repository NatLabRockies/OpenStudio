/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PipingSystemUndergroundPipeCircuit.hpp"
#include "PipingSystemUndergroundPipeCircuit_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PipingSystem_Underground_PipeCircuit_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

PipingSystemUndergroundPipeCircuit::PipingSystemUndergroundPipeCircuit(const Model& model)
  : ModelObject(PipingSystemUndergroundPipeCircuit::iddObjectType(), model) {}

PipingSystemUndergroundPipeCircuit::PipingSystemUndergroundPipeCircuit(std::shared_ptr<detail::PipingSystemUndergroundPipeCircuit_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType PipingSystemUndergroundPipeCircuit::iddObjectType() {
  return IddObjectType::PipingSystem_Underground_PipeCircuit;
}

double PipingSystemUndergroundPipeCircuit::pipeThermalConductivity() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->pipeThermalConductivity();
}

bool PipingSystemUndergroundPipeCircuit::setPipeThermalConductivity(double pipeThermalConductivity) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setPipeThermalConductivity(pipeThermalConductivity);
}

double PipingSystemUndergroundPipeCircuit::pipeDensity() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->pipeDensity();
}

bool PipingSystemUndergroundPipeCircuit::setPipeDensity(double pipeDensity) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setPipeDensity(pipeDensity);
}

double PipingSystemUndergroundPipeCircuit::pipeSpecificHeat() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->pipeSpecificHeat();
}

bool PipingSystemUndergroundPipeCircuit::setPipeSpecificHeat(double pipeSpecificHeat) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setPipeSpecificHeat(pipeSpecificHeat);
}

double PipingSystemUndergroundPipeCircuit::pipeInnerDiameter() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->pipeInnerDiameter();
}

bool PipingSystemUndergroundPipeCircuit::setPipeInnerDiameter(double pipeInnerDiameter) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setPipeInnerDiameter(pipeInnerDiameter);
}

double PipingSystemUndergroundPipeCircuit::pipeOuterDiameter() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->pipeOuterDiameter();
}

bool PipingSystemUndergroundPipeCircuit::setPipeOuterDiameter(double pipeOuterDiameter) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setPipeOuterDiameter(pipeOuterDiameter);
}

double PipingSystemUndergroundPipeCircuit::designFlowRate() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->designFlowRate();
}

bool PipingSystemUndergroundPipeCircuit::setDesignFlowRate(double designFlowRate) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setDesignFlowRate(designFlowRate);
}

double PipingSystemUndergroundPipeCircuit::convergenceCriterionfortheInnerRadialIterationLoop() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->convergenceCriterionfortheInnerRadialIterationLoop();
}

bool PipingSystemUndergroundPipeCircuit::isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted();
}

bool PipingSystemUndergroundPipeCircuit::setConvergenceCriterionfortheInnerRadialIterationLoop(
  double convergenceCriterionfortheInnerRadialIterationLoop) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setConvergenceCriterionfortheInnerRadialIterationLoop(
    convergenceCriterionfortheInnerRadialIterationLoop);
}

void PipingSystemUndergroundPipeCircuit::resetConvergenceCriterionfortheInnerRadialIterationLoop() {
  getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->resetConvergenceCriterionfortheInnerRadialIterationLoop();
}

int PipingSystemUndergroundPipeCircuit::maximumIterationsintheInnerRadialIterationLoop() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->maximumIterationsintheInnerRadialIterationLoop();
}

bool PipingSystemUndergroundPipeCircuit::isMaximumIterationsintheInnerRadialIterationLoopDefaulted() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->isMaximumIterationsintheInnerRadialIterationLoopDefaulted();
}

bool PipingSystemUndergroundPipeCircuit::setMaximumIterationsintheInnerRadialIterationLoop(int maximumIterationsintheInnerRadialIterationLoop) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setMaximumIterationsintheInnerRadialIterationLoop(
    maximumIterationsintheInnerRadialIterationLoop);
}

void PipingSystemUndergroundPipeCircuit::resetMaximumIterationsintheInnerRadialIterationLoop() {
  getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->resetMaximumIterationsintheInnerRadialIterationLoop();
}

int PipingSystemUndergroundPipeCircuit::numberofSoilNodesintheInnerRadialNearPipeMeshRegion() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->numberofSoilNodesintheInnerRadialNearPipeMeshRegion();
}

bool PipingSystemUndergroundPipeCircuit::isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted();
}

bool PipingSystemUndergroundPipeCircuit::setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(
  int numberofSoilNodesintheInnerRadialNearPipeMeshRegion) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(
    numberofSoilNodesintheInnerRadialNearPipeMeshRegion);
}

void PipingSystemUndergroundPipeCircuit::resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion() {
  getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion();
}

double PipingSystemUndergroundPipeCircuit::radialThicknessofInnerRadialNearPipeMeshRegion() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->radialThicknessofInnerRadialNearPipeMeshRegion();
}

bool PipingSystemUndergroundPipeCircuit::setRadialThicknessofInnerRadialNearPipeMeshRegion(double radialThicknessofInnerRadialNearPipeMeshRegion) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setRadialThicknessofInnerRadialNearPipeMeshRegion(
    radialThicknessofInnerRadialNearPipeMeshRegion);
}

int PipingSystemUndergroundPipeCircuit::numberofPipeSegmentsEnteredforthisPipeCircuit() const {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->numberofPipeSegmentsEnteredforthisPipeCircuit();
}

bool PipingSystemUndergroundPipeCircuit::setNumberofPipeSegmentsEnteredforthisPipeCircuit(int numberofPipeSegmentsEnteredforthisPipeCircuit) {
  return getImpl<detail::PipingSystemUndergroundPipeCircuit_Impl>()->setNumberofPipeSegmentsEnteredforthisPipeCircuit(
    numberofPipeSegmentsEnteredforthisPipeCircuit);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

  double PipingSystemUndergroundPipeCircuit_Impl::pipeThermalConductivity() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeThermalConductivity, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setPipeThermalConductivity(double pipeThermalConductivity) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeThermalConductivity, pipeThermalConductivity);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::pipeDensity() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeDensity, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setPipeDensity(double pipeDensity) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeDensity, pipeDensity);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::pipeSpecificHeat() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeSpecificHeat, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setPipeSpecificHeat(double pipeSpecificHeat) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeSpecificHeat, pipeSpecificHeat);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::pipeInnerDiameter() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeInnerDiameter, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setPipeInnerDiameter(double pipeInnerDiameter) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeInnerDiameter, pipeInnerDiameter);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::pipeOuterDiameter() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeOuterDiameter, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setPipeOuterDiameter(double pipeOuterDiameter) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::PipeOuterDiameter, pipeOuterDiameter);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::designFlowRate() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::DesignFlowRate, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setDesignFlowRate(double designFlowRate) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::DesignFlowRate, designFlowRate);
  }

  double PipingSystemUndergroundPipeCircuit_Impl::convergenceCriterionfortheInnerRadialIterationLoop() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::ConvergenceCriterionfortheInnerRadialIterationLoop, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted() const {
    return isEmpty(openstudio::PipingSystem_Underground_PipeCircuitFields::ConvergenceCriterionfortheInnerRadialIterationLoop);
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setConvergenceCriterionfortheInnerRadialIterationLoop(
    double convergenceCriterionfortheInnerRadialIterationLoop) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::ConvergenceCriterionfortheInnerRadialIterationLoop,
                     convergenceCriterionfortheInnerRadialIterationLoop);
  }

  void PipingSystemUndergroundPipeCircuit_Impl::resetConvergenceCriterionfortheInnerRadialIterationLoop() {
    OS_ASSERT(setString(openstudio::PipingSystem_Underground_PipeCircuitFields::ConvergenceCriterionfortheInnerRadialIterationLoop, ""));
  }

  int PipingSystemUndergroundPipeCircuit_Impl::maximumIterationsintheInnerRadialIterationLoop() const {
    const auto value = getInt(openstudio::PipingSystem_Underground_PipeCircuitFields::MaximumIterationsintheInnerRadialIterationLoop, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::isMaximumIterationsintheInnerRadialIterationLoopDefaulted() const {
    return isEmpty(openstudio::PipingSystem_Underground_PipeCircuitFields::MaximumIterationsintheInnerRadialIterationLoop);
  }

  bool
    PipingSystemUndergroundPipeCircuit_Impl::setMaximumIterationsintheInnerRadialIterationLoop(int maximumIterationsintheInnerRadialIterationLoop) {
    return setInt(openstudio::PipingSystem_Underground_PipeCircuitFields::MaximumIterationsintheInnerRadialIterationLoop,
                  maximumIterationsintheInnerRadialIterationLoop);
  }

  void PipingSystemUndergroundPipeCircuit_Impl::resetMaximumIterationsintheInnerRadialIterationLoop() {
    OS_ASSERT(setString(openstudio::PipingSystem_Underground_PipeCircuitFields::MaximumIterationsintheInnerRadialIterationLoop, ""));
  }

  int PipingSystemUndergroundPipeCircuit_Impl::numberofSoilNodesintheInnerRadialNearPipeMeshRegion() const {
    const auto value = getInt(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofSoilNodesintheInnerRadialNearPipeMeshRegion, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted() const {
    return isEmpty(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofSoilNodesintheInnerRadialNearPipeMeshRegion);
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(
    int numberofSoilNodesintheInnerRadialNearPipeMeshRegion) {
    return setInt(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofSoilNodesintheInnerRadialNearPipeMeshRegion,
                  numberofSoilNodesintheInnerRadialNearPipeMeshRegion);
  }

  void PipingSystemUndergroundPipeCircuit_Impl::resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion() {
    OS_ASSERT(setString(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofSoilNodesintheInnerRadialNearPipeMeshRegion, ""));
  }

  double PipingSystemUndergroundPipeCircuit_Impl::radialThicknessofInnerRadialNearPipeMeshRegion() const {
    const auto value = getDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::RadialThicknessofInnerRadialNearPipeMeshRegion, true);
    OS_ASSERT(value);
    return *value;
  }

  bool PipingSystemUndergroundPipeCircuit_Impl::setRadialThicknessofInnerRadialNearPipeMeshRegion(
    double radialThicknessofInnerRadialNearPipeMeshRegion) {
    return setDouble(openstudio::PipingSystem_Underground_PipeCircuitFields::RadialThicknessofInnerRadialNearPipeMeshRegion,
                     radialThicknessofInnerRadialNearPipeMeshRegion);
  }

  int PipingSystemUndergroundPipeCircuit_Impl::numberofPipeSegmentsEnteredforthisPipeCircuit() const {
    const auto value = getInt(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofPipeSegmentsEnteredforthisPipeCircuit, true);
    OS_ASSERT(value);
    return *value;
  }

  bool
    PipingSystemUndergroundPipeCircuit_Impl::setNumberofPipeSegmentsEnteredforthisPipeCircuit(int numberofPipeSegmentsEnteredforthisPipeCircuit) {
    return setInt(openstudio::PipingSystem_Underground_PipeCircuitFields::NumberofPipeSegmentsEnteredforthisPipeCircuit,
                  numberofPipeSegmentsEnteredforthisPipeCircuit);
  }

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
