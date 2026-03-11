/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPECIRCUIT_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDPIPECIRCUIT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipingSystemUndergroundPipeCircuit_Impl;
}

class EPMODEL_API PipingSystemUndergroundPipeCircuit : public ModelObject
{
 public:
  explicit PipingSystemUndergroundPipeCircuit(const Model& model);

  virtual ~PipingSystemUndergroundPipeCircuit() override = default;
  PipingSystemUndergroundPipeCircuit(const PipingSystemUndergroundPipeCircuit& other) = default;
  PipingSystemUndergroundPipeCircuit(PipingSystemUndergroundPipeCircuit&& other) = default;
  PipingSystemUndergroundPipeCircuit& operator=(const PipingSystemUndergroundPipeCircuit&) = default;
  PipingSystemUndergroundPipeCircuit& operator=(PipingSystemUndergroundPipeCircuit&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to PipingSystem:Underground:PipeCircuit scalar fields.
  // - Field Mapping: Name remains available via base ModelObject API.
  // - Field Mapping: Circuit Inlet Node, Circuit Outlet Node, and extensible Pipe Segment object-list fields
  //   are relationship/link fields and are excluded from scalar accessors.
  // - TODO(parity): Add typed relationship/extensible APIs after scalar scaffold saturation.
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

 protected:
  using ImplType = detail::PipingSystemUndergroundPipeCircuit_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipingSystemUndergroundPipeCircuit(std::shared_ptr<detail::PipingSystemUndergroundPipeCircuit_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
