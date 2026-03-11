/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERSLINKY_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERSLINKY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatExchangerSlinky_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatExchangerSlinky_Impl() override = default;

  double designFlowRate() const;
  bool isDesignFlowRateDefaulted() const;
  bool setDesignFlowRate(double designFlowRate);
  void resetDesignFlowRate();

  double soilThermalConductivity() const;
  bool isSoilThermalConductivityDefaulted() const;
  bool setSoilThermalConductivity(double soilThermalConductivity);
  void resetSoilThermalConductivity();

  double soilDensity() const;
  bool isSoilDensityDefaulted() const;
  bool setSoilDensity(double soilDensity);
  void resetSoilDensity();

  double soilSpecificHeat() const;
  bool isSoilSpecificHeatDefaulted() const;
  bool setSoilSpecificHeat(double soilSpecificHeat);
  void resetSoilSpecificHeat();

  double pipeThermalConductivity() const;
  bool isPipeThermalConductivityDefaulted() const;
  bool setPipeThermalConductivity(double pipeThermalConductivity);
  void resetPipeThermalConductivity();

  double pipeDensity() const;
  bool isPipeDensityDefaulted() const;
  bool setPipeDensity(double pipeDensity);
  void resetPipeDensity();

  double pipeSpecificHeat() const;
  bool isPipeSpecificHeatDefaulted() const;
  bool setPipeSpecificHeat(double pipeSpecificHeat);
  void resetPipeSpecificHeat();

  double pipeOuterDiameter() const;
  bool isPipeOuterDiameterDefaulted() const;
  bool setPipeOuterDiameter(double pipeOuterDiameter);
  void resetPipeOuterDiameter();

  double pipeThickness() const;
  bool isPipeThicknessDefaulted() const;
  bool setPipeThickness(double pipeThickness);
  void resetPipeThickness();

  boost::optional<std::string> heatExchangerConfiguration() const;
  bool setHeatExchangerConfiguration(const std::string& heatExchangerConfiguration);
  void resetHeatExchangerConfiguration();

  double coilDiameter() const;
  bool isCoilDiameterDefaulted() const;
  bool setCoilDiameter(double coilDiameter);
  void resetCoilDiameter();

  double coilPitch() const;
  bool isCoilPitchDefaulted() const;
  bool setCoilPitch(double coilPitch);
  void resetCoilPitch();

  double trenchDepth() const;
  bool isTrenchDepthDefaulted() const;
  bool setTrenchDepth(double trenchDepth);
  void resetTrenchDepth();

  double trenchLength() const;
  bool isTrenchLengthDefaulted() const;
  bool setTrenchLength(double trenchLength);
  void resetTrenchLength();

  int numberofTrenches() const;
  bool isNumberofTrenchesDefaulted() const;
  bool setNumberofTrenches(int numberofTrenches);
  void resetNumberofTrenches();

  double horizontalSpacingBetweenPipes() const;
  bool isHorizontalSpacingBetweenPipesDefaulted() const;
  bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);
  void resetHorizontalSpacingBetweenPipes();

  std::string undisturbedGroundTemperatureModelType() const;
  bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);

  boost::optional<double> maximumLengthofSimulation() const;
  bool setMaximumLengthofSimulation(double maximumLengthofSimulation);
  void resetMaximumLengthofSimulation();

  std::vector<std::string> heatExchangerConfigurationValues() const;
  std::vector<std::string> undisturbedGroundTemperatureModelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
