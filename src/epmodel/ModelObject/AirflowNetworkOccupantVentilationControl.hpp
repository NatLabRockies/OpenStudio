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

  /** \brief Represents the EnergyPlus AirflowNetwork:OccupantVentilationControl object.
   *
   * \par EnergyPlus object
   * \epobject{group-airflow-network.html#airflownetworkoccupantventilationcontrol,AirflowNetwork:OccupantVentilationControl}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirflowNetworkOccupantVentilationControl</code>. <b>Not yet available:</b> <code>thermalComfortLowTemperatureCurve()</code>, <code>thermalComfortHighTemperatureCurve()</code>, <code>openingProbabilitySchedule()</code>, <code>closingProbabilitySchedule()</code>, and their setters/resetters.
   *
   * \par Known limitations
   * The four curve/schedule relationships are not exposed by the EPModel wrapper.
   */
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
