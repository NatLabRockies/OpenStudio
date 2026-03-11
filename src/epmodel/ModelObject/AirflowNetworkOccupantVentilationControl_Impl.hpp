/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKOCCUPANTVENTILATIONCONTROL_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API AirflowNetworkOccupantVentilationControl_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AirflowNetworkOccupantVentilationControl_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
