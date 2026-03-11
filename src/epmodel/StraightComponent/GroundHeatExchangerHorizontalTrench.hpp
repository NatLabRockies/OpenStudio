/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP
#define EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatExchangerHorizontalTrench_Impl;
}

class EPMODEL_API GroundHeatExchangerHorizontalTrench : public StraightComponent
{
 public:
  explicit GroundHeatExchangerHorizontalTrench(const Model& model);

  virtual ~GroundHeatExchangerHorizontalTrench() override = default;
  GroundHeatExchangerHorizontalTrench(const GroundHeatExchangerHorizontalTrench& other) = default;
  GroundHeatExchangerHorizontalTrench(GroundHeatExchangerHorizontalTrench&& other) = default;
  GroundHeatExchangerHorizontalTrench& operator=(const GroundHeatExchangerHorizontalTrench&) = default;
  GroundHeatExchangerHorizontalTrench& operator=(GroundHeatExchangerHorizontalTrench&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::GroundHeatExchangerHorizontalTrench scalar accessor names/signatures.
  // - Field Mapping: preserved scalar APIs currently delegate directly to matching E+ GroundHeatExchanger:HorizontalTrench fields.
  // - Field Mapping: UndisturbedGroundTemperatureModelName, UndisturbedGroundTemperatureModelType, InletNodeName, and OutletNodeName are
  //   relationship-like fields and are intentionally excluded from this scalar-only scaffold.
  // - ForwardTranslator evidence: ForwardTranslateGroundHeatExchangerHorizontalTrench.cpp maps these preserved scalar APIs directly to same E+ fields.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  double designFlowRate() const;
  double trenchLengthinPipeAxialDirection() const;
  int numberofTrenches() const;
  double horizontalSpacingBetweenPipes() const;
  double pipeInnerDiameter() const;
  double pipeOuterDiameter() const;
  double burialDepth() const;
  double soilThermalConductivity() const;
  double soilDensity() const;
  double soilSpecificHeat() const;
  double pipeThermalConductivity() const;
  double pipeDensity() const;
  double pipeSpecificHeat() const;
  double soilMoistureContentPercent() const;
  double soilMoistureContentPercentatSaturation() const;
  double evapotranspirationGroundCoverParameter() const;

  bool setDesignFlowRate(double designFlowRate);
  bool setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection);
  bool setNumberofTrenches(int numberofTrenches);
  bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);
  bool setPipeInnerDiameter(double pipeInnerDiameter);
  bool setPipeOuterDiameter(double pipeOuterDiameter);
  bool setBurialDepth(double burialDepth);
  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setPipeThermalConductivity(double pipeThermalConductivity);
  bool setPipeDensity(double pipeDensity);
  bool setPipeSpecificHeat(double pipeSpecificHeat);
  bool setSoilMoistureContentPercent(double soilMoistureContentPercent);
  bool setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation);
  bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);

 protected:
  using ImplType = detail::GroundHeatExchangerHorizontalTrench_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatExchangerHorizontalTrench(std::shared_ptr<detail::GroundHeatExchangerHorizontalTrench_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
