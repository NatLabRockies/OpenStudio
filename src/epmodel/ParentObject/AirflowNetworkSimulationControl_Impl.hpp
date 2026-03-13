/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKSIMULATIONCONTROL_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKSIMULATIONCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkSimulationControl_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkSimulationControl_Impl() override = default;

  std::vector<std::string> airflowNetworkControlValues() const;
  std::vector<std::string> windPressureCoefficientTypeValues() const;
  std::vector<std::string> heightSelectionforLocalWindPressureCalculationValues() const;
  std::vector<std::string> buildingTypeValues() const;
  std::vector<std::string> initializationTypeValues() const;
  std::vector<std::string> solverValues() const;

  std::string airflowNetworkControl() const;
  bool isAirflowNetworkControlDefaulted() const;
  bool setAirflowNetworkControl(const std::string& airflowNetworkControl);
  void resetAirflowNetworkControl();

  std::string windPressureCoefficientType() const;
  bool isWindPressureCoefficientTypeDefaulted() const;
  bool setWindPressureCoefficientType(const std::string& windPressureCoefficientType);
  void resetWindPressureCoefficientType();

  std::string heightSelectionforLocalWindPressureCalculation() const;
  bool isHeightSelectionforLocalWindPressureCalculationDefaulted() const;
  bool setHeightSelectionforLocalWindPressureCalculation(const std::string& heightSelectionforLocalWindPressureCalculation);
  void resetHeightSelectionforLocalWindPressureCalculation();

  std::string buildingType() const;
  bool isBuildingTypeDefaulted() const;
  bool setBuildingType(const std::string& buildingType);
  void resetBuildingType();

  int maximumNumberofIterations() const;
  bool isMaximumNumberofIterationsDefaulted() const;
  bool setMaximumNumberofIterations(int maximumNumberofIterations);
  void resetMaximumNumberofIterations();

  std::string initializationType() const;
  bool isInitializationTypeDefaulted() const;
  bool setInitializationType(const std::string& initializationType);
  void resetInitializationType();

  double relativeAirflowConvergenceTolerance() const;
  bool isRelativeAirflowConvergenceToleranceDefaulted() const;
  bool setRelativeAirflowConvergenceTolerance(double relativeAirflowConvergenceTolerance);
  void resetRelativeAirflowConvergenceTolerance();

  double absoluteAirflowConvergenceTolerance() const;
  bool isAbsoluteAirflowConvergenceToleranceDefaulted() const;
  bool setAbsoluteAirflowConvergenceTolerance(double absoluteAirflowConvergenceTolerance);
  void resetAbsoluteAirflowConvergenceTolerance();

  double convergenceAccelerationLimit() const;
  bool isConvergenceAccelerationLimitDefaulted() const;
  bool setConvergenceAccelerationLimit(double convergenceAccelerationLimit);
  void resetConvergenceAccelerationLimit();

  double azimuthAngleofLongAxisofBuilding() const;
  bool isAzimuthAngleofLongAxisofBuildingDefaulted() const;
  bool setAzimuthAngleofLongAxisofBuilding(double azimuthAngleofLongAxisofBuilding);
  void resetAzimuthAngleofLongAxisofBuilding();

  double ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis() const;
  bool isRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxisDefaulted() const;
  bool setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(double ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis);
  void resetRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis();

  bool heightDependenceofExternalNodeTemperature() const;
  bool isHeightDependenceofExternalNodeTemperatureDefaulted() const;
  void setHeightDependenceofExternalNodeTemperature(bool heightDependenceofExternalNodeTemperature);
  void resetHeightDependenceofExternalNodeTemperature();

  std::string solver() const;
  bool isSolverDefaulted() const;
  bool setSolver(const std::string& solver);
  void resetSolver();

  bool allowUnsupportedZoneEquipment() const;
  bool isAllowUnsupportedZoneEquipmentDefaulted() const;
  void setAllowUnsupportedZoneEquipment(bool allowUnsupportedZoneEquipment);
  void resetAllowUnsupportedZoneEquipment();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
