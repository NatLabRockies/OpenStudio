/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPINGSYSTEMUNDERGROUNDDOMAIN_HPP
#define EPMODEL_PIPINGSYSTEMUNDERGROUNDDOMAIN_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class PipingSystemUndergroundDomain_Impl;
}

class EPMODEL_API PipingSystemUndergroundDomain : public ModelObject
{
 public:
  explicit PipingSystemUndergroundDomain(const Model& model);

  virtual ~PipingSystemUndergroundDomain() override = default;
  PipingSystemUndergroundDomain(const PipingSystemUndergroundDomain& other) = default;
  PipingSystemUndergroundDomain(PipingSystemUndergroundDomain&& other) = default;
  PipingSystemUndergroundDomain& operator=(const PipingSystemUndergroundDomain&) = default;
  PipingSystemUndergroundDomain& operator=(PipingSystemUndergroundDomain&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> xDirectionMeshTypeValues();
  static std::vector<std::string> yDirectionMeshTypeValues();
  static std::vector<std::string> zDirectionMeshTypeValues();
  static std::vector<std::string> undisturbedGroundTemperatureModelTypeValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to PipingSystem:Underground:Domain scalar fields.
  // - Field Mapping: UndisturbedGroundTemperatureModelName, basement boundary condition model names,
  //   and extensible Pipe Circuit object-list fields are excluded as relationship/link fields.
  // - TODO(parity): Add typed relationship/extensible APIs after scalar scaffold saturation.
  double xmax() const;
  double ymax() const;
  double zmax() const;
  int xDirectionMeshDensityParameter() const;
  std::string xDirectionMeshType() const;
  double xDirectionGeometricCoefficient() const;
  int yDirectionMeshDensityParameter() const;
  std::string yDirectionMeshType() const;
  double yDirectionGeometricCoefficient() const;
  int zDirectionMeshDensityParameter() const;
  std::string zDirectionMeshType() const;
  double zDirectionGeometricCoefficient() const;
  double soilThermalConductivity() const;
  double soilDensity() const;
  double soilSpecificHeat() const;
  double soilMoistureContentVolumeFraction() const;
  double soilMoistureContentVolumeFractionatSaturation() const;
  std::string undisturbedGroundTemperatureModelType() const;
  bool thisDomainIncludesBasementSurfaceInteraction() const;
  boost::optional<double> widthofBasementFloorinGroundDomain() const;
  boost::optional<double> depthofBasementWallInGroundDomain() const;
  boost::optional<bool> shiftPipeXCoordinatesByBasementWidth() const;
  double convergenceCriterionfortheOuterCartesianDomainIterationLoop() const;
  int maximumIterationsintheOuterCartesianDomainIterationLoop() const;
  double evapotranspirationGroundCoverParameter() const;
  int numberofPipeCircuitsEnteredforthisDomain() const;

  bool isXDirectionMeshDensityParameterDefaulted() const;
  bool isXDirectionGeometricCoefficientDefaulted() const;
  bool isYDirectionMeshDensityParameterDefaulted() const;
  bool isYDirectionGeometricCoefficientDefaulted() const;
  bool isZDirectionMeshDensityParameterDefaulted() const;
  bool isZDirectionGeometricCoefficientDefaulted() const;
  bool isSoilMoistureContentVolumeFractionDefaulted() const;
  bool isSoilMoistureContentVolumeFractionatSaturationDefaulted() const;
  bool isThisDomainIncludesBasementSurfaceInteractionDefaulted() const;
  bool isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted() const;
  bool isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted() const;
  bool isEvapotranspirationGroundCoverParameterDefaulted() const;

  bool setXmax(double xmax);
  bool setYmax(double ymax);
  bool setZmax(double zmax);
  bool setXDirectionMeshDensityParameter(int xDirectionMeshDensityParameter);
  bool setXDirectionMeshType(const std::string& xDirectionMeshType);
  bool setXDirectionGeometricCoefficient(double xDirectionGeometricCoefficient);
  bool setYDirectionMeshDensityParameter(int yDirectionMeshDensityParameter);
  bool setYDirectionMeshType(const std::string& yDirectionMeshType);
  bool setYDirectionGeometricCoefficient(double yDirectionGeometricCoefficient);
  bool setZDirectionMeshDensityParameter(int zDirectionMeshDensityParameter);
  bool setZDirectionMeshType(const std::string& zDirectionMeshType);
  bool setZDirectionGeometricCoefficient(double zDirectionGeometricCoefficient);
  bool setSoilThermalConductivity(double soilThermalConductivity);
  bool setSoilDensity(double soilDensity);
  bool setSoilSpecificHeat(double soilSpecificHeat);
  bool setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction);
  bool setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation);
  bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);
  bool setThisDomainIncludesBasementSurfaceInteraction(bool thisDomainIncludesBasementSurfaceInteraction);
  bool setWidthofBasementFloorinGroundDomain(double widthofBasementFloorinGroundDomain);
  bool setDepthofBasementWallInGroundDomain(double depthofBasementWallInGroundDomain);
  bool setShiftPipeXCoordinatesByBasementWidth(boost::optional<bool> shiftPipeXCoordinatesByBasementWidth);
  bool setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(double convergenceCriterionfortheOuterCartesianDomainIterationLoop);
  bool setMaximumIterationsintheOuterCartesianDomainIterationLoop(int maximumIterationsintheOuterCartesianDomainIterationLoop);
  bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);
  bool setNumberofPipeCircuitsEnteredforthisDomain(int numberofPipeCircuitsEnteredforthisDomain);

  void resetXDirectionMeshDensityParameter();
  void resetXDirectionGeometricCoefficient();
  void resetYDirectionMeshDensityParameter();
  void resetYDirectionGeometricCoefficient();
  void resetZDirectionMeshDensityParameter();
  void resetZDirectionGeometricCoefficient();
  void resetSoilMoistureContentVolumeFraction();
  void resetSoilMoistureContentVolumeFractionatSaturation();
  void resetThisDomainIncludesBasementSurfaceInteraction();
  void resetWidthofBasementFloorinGroundDomain();
  void resetDepthofBasementWallInGroundDomain();
  void resetShiftPipeXCoordinatesByBasementWidth();
  void resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop();
  void resetMaximumIterationsintheOuterCartesianDomainIterationLoop();
  void resetEvapotranspirationGroundCoverParameter();

 protected:
  using ImplType = detail::PipingSystemUndergroundDomain_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit PipingSystemUndergroundDomain(std::shared_ptr<detail::PipingSystemUndergroundDomain_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
