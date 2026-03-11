/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPECIRCUIT_IMPL_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPECIRCUIT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API PipingSystemUndergroundPipeCircuit_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~PipingSystemUndergroundPipeCircuit_Impl() override = default;

  double pipeThermalConductivity() const;
  double pipeDensity() const;
  double pipeSpecificHeat() const;
  double pipeInnerDiameter() const;
  double pipeOuterDiameter() const;
  double designFlowRate() const;
  double convergenceCriterionfortheInnerRadialIterationLoop() const;
  int maximumIterationsintheInnerRadialIterationLoop() const;
  int numberofSoilNodesintheInnerRadialNearPipeMeshRegion() const;
  double radialThicknessofInnerRadialNearPipeMeshRegion() const;
  int numberofPipeSegmentsEnteredforthisPipeCircuit() const;

  bool isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted() const;
  bool isMaximumIterationsintheInnerRadialIterationLoopDefaulted() const;
  bool isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted() const;

  bool setPipeThermalConductivity(double pipeThermalConductivity);
  bool setPipeDensity(double pipeDensity);
  bool setPipeSpecificHeat(double pipeSpecificHeat);
  bool setPipeInnerDiameter(double pipeInnerDiameter);
  bool setPipeOuterDiameter(double pipeOuterDiameter);
  bool setDesignFlowRate(double designFlowRate);
  bool setConvergenceCriterionfortheInnerRadialIterationLoop(double convergenceCriterionfortheInnerRadialIterationLoop);
  bool setMaximumIterationsintheInnerRadialIterationLoop(int maximumIterationsintheInnerRadialIterationLoop);
  bool setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(int numberofSoilNodesintheInnerRadialNearPipeMeshRegion);
  bool setRadialThicknessofInnerRadialNearPipeMeshRegion(double radialThicknessofInnerRadialNearPipeMeshRegion);
  bool setNumberofPipeSegmentsEnteredforthisPipeCircuit(int numberofPipeSegmentsEnteredforthisPipeCircuit);

  void resetConvergenceCriterionfortheInnerRadialIterationLoop();
  void resetMaximumIterationsintheInnerRadialIterationLoop();
  void resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
