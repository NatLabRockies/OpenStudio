/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERVERTICAL_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatExchangerVertical_Impl;
}

class EPMODEL_API GroundHeatExchangerVertical : public StraightComponent
{
 public:
  explicit GroundHeatExchangerVertical(const Model& model);

  virtual ~GroundHeatExchangerVertical() override = default;
  GroundHeatExchangerVertical(const GroundHeatExchangerVertical& other) = default;
  GroundHeatExchangerVertical(GroundHeatExchangerVertical&& other) = default;
  GroundHeatExchangerVertical& operator=(const GroundHeatExchangerVertical&) = default;
  GroundHeatExchangerVertical& operator=(GroundHeatExchangerVertical&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::GroundHeatExchangerVertical scalar accessor names/signatures for counterpart parity.
  // - Field Mapping: designFlowRate(), groundThermalConductivity(), and groundThermalHeatCapacity() delegate to
  //   GroundHeatExchanger:System fields DesignFlowRate, GroundThermalConductivity, and GroundThermalHeatCapacity via linked
  //   GroundHeatExchanger:System objects keyed by GHE:Vertical:ResponseFactors Object Name.
  // - Field Mapping: numberofBoreHoles() and gFunctionReferenceRatio() map to
  //   GroundHeatExchanger:ResponseFactors fields NumberofBoreholes and GFunctionReferenceRatio.
  // - Field Mapping: boreHoleTopDepth(), boreHoleLength(), boreHoleRadius(), groutThermalConductivity(),
  //   pipeThermalConductivity(), pipeOutDiameter(), uTubeDistance(), and pipeThickness() delegate to linked
  //   GroundHeatExchanger:Vertical:Properties fields (BoreholeRadius API maps to BoreholeDiameter / 2.0).
  // - Field Mapping: undisturbed ground model APIs are relationship-based via GroundHeatExchanger:System fields and remain excluded.
  // - Field Mapping: GFunction extensible pair entries are excluded from this scalar-only scaffold.
  // - TODO(parity): Add excluded relationship/extensible APIs while preserving these scalar signatures.
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

 protected:
  using ImplType = detail::GroundHeatExchangerVertical_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatExchangerVertical(std::shared_ptr<detail::GroundHeatExchangerVertical_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
