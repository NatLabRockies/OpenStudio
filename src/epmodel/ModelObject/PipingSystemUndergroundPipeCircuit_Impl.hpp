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
      bool setPipeThermalConductivity(double pipeThermalConductivity);

      double pipeDensity() const;
      bool setPipeDensity(double pipeDensity);

      double pipeSpecificHeat() const;
      bool setPipeSpecificHeat(double pipeSpecificHeat);

      double pipeInnerDiameter() const;
      bool setPipeInnerDiameter(double pipeInnerDiameter);

      double pipeOuterDiameter() const;
      bool setPipeOuterDiameter(double pipeOuterDiameter);

      double designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);

      double convergenceCriterionfortheInnerRadialIterationLoop() const;
      bool isConvergenceCriterionfortheInnerRadialIterationLoopDefaulted() const;
      bool setConvergenceCriterionfortheInnerRadialIterationLoop(double convergenceCriterionfortheInnerRadialIterationLoop);
      void resetConvergenceCriterionfortheInnerRadialIterationLoop();

      int maximumIterationsintheInnerRadialIterationLoop() const;
      bool isMaximumIterationsintheInnerRadialIterationLoopDefaulted() const;
      bool setMaximumIterationsintheInnerRadialIterationLoop(int maximumIterationsintheInnerRadialIterationLoop);
      void resetMaximumIterationsintheInnerRadialIterationLoop();

      int numberofSoilNodesintheInnerRadialNearPipeMeshRegion() const;
      bool isNumberofSoilNodesintheInnerRadialNearPipeMeshRegionDefaulted() const;
      bool setNumberofSoilNodesintheInnerRadialNearPipeMeshRegion(int numberofSoilNodesintheInnerRadialNearPipeMeshRegion);
      void resetNumberofSoilNodesintheInnerRadialNearPipeMeshRegion();

      double radialThicknessofInnerRadialNearPipeMeshRegion() const;
      bool setRadialThicknessofInnerRadialNearPipeMeshRegion(double radialThicknessofInnerRadialNearPipeMeshRegion);

      int numberofPipeSegmentsEnteredforthisPipeCircuit() const;
      bool setNumberofPipeSegmentsEnteredforthisPipeCircuit(int numberofPipeSegmentsEnteredforthisPipeCircuit);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
