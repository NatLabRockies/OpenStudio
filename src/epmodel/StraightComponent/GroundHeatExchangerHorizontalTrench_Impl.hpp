/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API GroundHeatExchangerHorizontalTrench_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~GroundHeatExchangerHorizontalTrench_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
