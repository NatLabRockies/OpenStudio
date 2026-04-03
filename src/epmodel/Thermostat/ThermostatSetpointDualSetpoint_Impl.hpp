/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_IMPL_HPP
#define EPMODEL_THERMOSTAT_THERMOSTATSETPOINTDUALSETPOINT_IMPL_HPP

#include "Thermostat/Thermostat_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Schedule;
  class ThermalZone;

  namespace detail {

    class EPMODEL_API ThermostatSetpointDualSetpoint_Impl : public Thermostat_Impl
    {
     public:
      ThermostatSetpointDualSetpoint_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);
      ThermostatSetpointDualSetpoint_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
      ThermostatSetpointDualSetpoint_Impl(const ThermostatSetpointDualSetpoint_Impl& other, Model_Impl* model, bool keepHandle);
      virtual ~ThermostatSetpointDualSetpoint_Impl() override = default;

      boost::optional<openstudio::epmodel::Schedule> heatingSetpointTemperatureSchedule() const;
      boost::optional<openstudio::epmodel::Schedule> coolingSetpointTemperatureSchedule() const;

      bool setHeatingSetpointTemperatureSchedule(openstudio::epmodel::Schedule& schedule);
      void resetHeatingSetpointTemperatureSchedule();

      bool setCoolingSetpointTemperatureSchedule(openstudio::epmodel::Schedule& schedule);
      void resetCoolingSetpointTemperatureSchedule();

      double temperatureDifferenceBetweenCutoutAndSetpoint() const;
      bool setTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT);
      bool isTemperatureDifferenceBetweenCutoutAndSetpointDefaulted() const;
      void applyTemperatureDifferenceBetweenCutoutAndSetpointToThermalZone(openstudio::epmodel::ThermalZone& thermalZone) const;
      void syncTemperatureDifferenceBetweenCutoutAndSetpointFromThermalZone(const openstudio::epmodel::ThermalZone& thermalZone);

     private:
      double storedTemperatureDifferenceBetweenCutoutAndSetpoint() const;
      bool hasStoredTemperatureDifferenceBetweenCutoutAndSetpoint() const;
      void setStoredTemperatureDifferenceBetweenCutoutAndSetpoint(double deltaT);
      void resetStoredTemperatureDifferenceBetweenCutoutAndSetpoint();

      boost::optional<double> m_temperatureDifferenceBetweenCutoutAndSetpoint;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
