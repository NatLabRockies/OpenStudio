/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_HPP
#define EPMODEL_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkOccupantVentilationControl_Impl;
  }

  class EPMODEL_API AirflowNetworkOccupantVentilationControl : public ModelObject
  {
   public:
    explicit AirflowNetworkOccupantVentilationControl(const Model& model);

    virtual ~AirflowNetworkOccupantVentilationControl() override = default;
    AirflowNetworkOccupantVentilationControl(const AirflowNetworkOccupantVentilationControl& other) = default;
    AirflowNetworkOccupantVentilationControl(AirflowNetworkOccupantVentilationControl&& other) = default;
    AirflowNetworkOccupantVentilationControl& operator=(const AirflowNetworkOccupantVentilationControl&) = default;
    AirflowNetworkOccupantVentilationControl& operator=(AirflowNetworkOccupantVentilationControl&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve existing openstudio::model scalar accessor names/signatures for this counterpart type.
    // - Field Mapping: maximumPredictedPercentageofDissatisfiedThreshold maps to the EnergyPlus field
    //   Maximum Threshold for Persons Dissatisfied PPD.
    // - Field Mapping: Relationship-like reference fields are intentionally excluded from scalar scaffold accessors:
    //   Thermal Comfort Low Temperature Curve Name, Thermal Comfort High Temperature Curve Name,
    //   Opening Probability Schedule Name, and Closing Probability Schedule Name.
    // - ForwardTranslator evidence: translateAirflowNetworkOccupantVentilationControl writes the same scalar fields
    //   (minimum/maximum thresholds, boundary point, occupancy check) directly to EnergyPlus.
    // - TODO(parity): Add relationship APIs in a follow-up parity pass if needed.
    double minimumOpeningTime() const;
    bool isMinimumOpeningTimeDefaulted() const;
    bool setMinimumOpeningTime(double minimumOpeningTime);
    void resetMinimumOpeningTime();

    double minimumClosingTime() const;
    bool isMinimumClosingTimeDefaulted() const;
    bool setMinimumClosingTime(double minimumClosingTime);
    void resetMinimumClosingTime();

    double thermalComfortTemperatureBoundaryPoint() const;
    bool isThermalComfortTemperatureBoundaryPointDefaulted() const;
    bool setThermalComfortTemperatureBoundaryPoint(double thermalComfortTemperatureBoundaryPoint);
    void resetThermalComfortTemperatureBoundaryPoint();

    double maximumPredictedPercentageofDissatisfiedThreshold() const;
    bool isMaximumPredictedPercentageofDissatisfiedThresholdDefaulted() const;
    bool setMaximumPredictedPercentageofDissatisfiedThreshold(double maximumPredictedPercentageofDissatisfiedThreshold);
    void resetMaximumPredictedPercentageofDissatisfiedThreshold();

    bool occupancyCheck() const;
    bool isOccupancyCheckDefaulted() const;
    void setOccupancyCheck(bool occupancyCheck);
    void resetOccupancyCheck();

   protected:
    using ImplType = detail::AirflowNetworkOccupantVentilationControl_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkOccupantVentilationControl(std::shared_ptr<detail::AirflowNetworkOccupantVentilationControl_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
