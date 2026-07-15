/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKSIMULATIONCONTROL_HPP
#define EPMODEL_AIRFLOWNETWORKSIMULATIONCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkSimulationControl_Impl;
  }

  class EPMODEL_API AirflowNetworkSimulationControl : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~AirflowNetworkSimulationControl() override = default;
    AirflowNetworkSimulationControl(const AirflowNetworkSimulationControl& other) = default;
    AirflowNetworkSimulationControl(AirflowNetworkSimulationControl&& other) = default;
    AirflowNetworkSimulationControl& operator=(const AirflowNetworkSimulationControl&) = default;
    AirflowNetworkSimulationControl& operator=(AirflowNetworkSimulationControl&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> airflowNetworkControlValues();
    static std::vector<std::string> windPressureCoefficientTypeValues();
    static std::vector<std::string> heightSelectionforLocalWindPressureCalculationValues();
    static std::vector<std::string> buildingTypeValues();
    static std::vector<std::string> initializationTypeValues();
    static std::vector<std::string> solverValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: All scalar accessors map directly to EnergyPlus AirflowNetwork:SimulationControl fields.
    // - Field Mapping: Name is handled by base ModelObject naming API and is intentionally not duplicated here.
    // - ForwardTranslator evidence: model::AirflowNetworkSimulationControl uses alias buildingAspectRatio for
    //   field Ratio of Building Width Along Short Axis to Width Along Long Axis; epmodel keeps IDD-derived naming.
    // - TODO(parity): Revisit cross-layer naming aliasing only if epmodel adopts model-counterpart naming policy.
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

   protected:
    explicit AirflowNetworkSimulationControl(const Model& model);

    using ImplType = detail::AirflowNetworkSimulationControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkSimulationControl(std::shared_ptr<detail::AirflowNetworkSimulationControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
