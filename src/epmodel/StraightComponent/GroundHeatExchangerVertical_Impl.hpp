/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
class WorkspaceObject;
namespace epmodel {
namespace detail {

class EPMODEL_API GroundHeatExchangerVertical_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~GroundHeatExchangerVertical_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  boost::optional<double> designFlowRate() const;
  boost::optional<double> groundThermalConductivity() const;
  boost::optional<double> groundThermalHeatCapacity() const;
  double boreHoleTopDepth() const;
  boost::optional<double> boreHoleLength() const;
  boost::optional<double> boreHoleRadius() const;
  boost::optional<double> groutThermalConductivity() const;
  boost::optional<double> pipeThermalConductivity() const;
  boost::optional<double> pipeOutDiameter() const;
  boost::optional<double> uTubeDistance() const;
  boost::optional<double> pipeThickness() const;

  bool setDesignFlowRate(double designFlowRate);
  bool setGroundThermalConductivity(double groundThermalConductivity);
  void resetGroundThermalConductivity();
  bool setGroundThermalHeatCapacity(double groundThermalHeatCapacity);
  void resetGroundThermalHeatCapacity();
  bool setBoreHoleTopDepth(double boreHoleTopDepth);
  bool setBoreHoleLength(double boreHoleLength);
  void resetBoreHoleLength();
  bool setBoreHoleRadius(double boreHoleRadius);
  void resetBoreHoleRadius();
  bool setGroutThermalConductivity(double groutThermalConductivity);
  void resetGroutThermalConductivity();
  bool setPipeThermalConductivity(double pipeThermalConductivity);
  void resetPipeThermalConductivity();
  bool setPipeOutDiameter(double pipeOutDiameter);
  void resetPipeOutDiameter();
  bool setUTubeDistance(double uTubeDistance);
  void resetUTubeDistance();
  bool setPipeThickness(double pipeThickness);
  void resetPipeThickness();

  boost::optional<int> numberofBoreHoles() const;
  bool setNumberofBoreHoles(int numberofBoreHoles);
  void resetNumberofBoreHoles();

  double gFunctionReferenceRatio() const;
  bool isGFunctionReferenceRatioDefaulted() const;
  bool setGFunctionReferenceRatio(double gFunctionReferenceRatio);
  void resetGFunctionReferenceRatio();

 private:
  boost::optional<openstudio::WorkspaceObject> groundHeatExchangerSystem() const;
  boost::optional<openstudio::WorkspaceObject> getOrCreateGroundHeatExchangerSystem();
  boost::optional<openstudio::WorkspaceObject> groundHeatExchangerVerticalProperties() const;
  boost::optional<openstudio::WorkspaceObject> getOrCreateGroundHeatExchangerVerticalProperties();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
