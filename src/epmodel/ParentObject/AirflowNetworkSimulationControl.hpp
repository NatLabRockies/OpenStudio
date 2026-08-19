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

/** \brief Controls the EnergyPlus AirflowNetwork simulation.
 *
 * \par EnergyPlus object
 * \epobject{group-airflow-network.html#airflownetworksimulationcontrol,AirflowNetwork:SimulationControl}
 *
 * \par Important behavior
 * The airflow-network, wind-pressure, initialization, convergence, and building-geometry controls are stored directly on this object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::AirflowNetworkSimulationControl</code>.
 * <b>Renamed:</b> EPModel's <code>ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis()</code> replaces Model's <code>buildingAspectRatio()</code>, with corresponding setter, default-check, and reset methods.
 *
 * \par Known limitations
 * This wrapper exposes the simulation-control object only; airflow-network surface, opening, and crack objects are separate types.
 */
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
