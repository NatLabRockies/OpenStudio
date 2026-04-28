/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALSTORAGEICEDETAILED_IMPL_HPP
#define EPMODEL_THERMALSTORAGEICEDETAILED_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <boost/optional.hpp>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {
  class Node;
  class Schedule;
  class Curve;
  namespace detail {

    class EPMODEL_API ThermalStorageIceDetailed_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;

      virtual ~ThermalStorageIceDetailed_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      std::vector<ModelObject> children() const override;

      bool addToNode(Node& node) override;

      boost::optional<Schedule> availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);
      void resetAvailabilitySchedule();

      Curve dischargingCurve() const;
      bool setDischargingCurve(const Curve& dischargingCurve);

      Curve chargingCurve() const;
      bool setChargingCurve(const Curve& chargingCurve);

      double capacity() const;
      bool setCapacity(double capacity);
      bool isCapacityAutosized() const;
      void autosizeCapacity();

      std::string dischargingCurveVariableSpecifications() const;
      bool setDischargingCurveVariableSpecifications(const std::string& dischargingCurveVariableSpecifications);

      std::string chargingCurveVariableSpecifications() const;
      bool setChargingCurveVariableSpecifications(const std::string& chargingCurveVariableSpecifications);

      boost::optional<double> timestepoftheCurveData() const;
      bool setTimestepoftheCurveData(double timestepoftheCurveData);
      void resetTimestepoftheCurveData();

      boost::optional<double> parasiticElectricLoadDuringDischarging() const;
      bool setParasiticElectricLoadDuringDischarging(double parasiticElectricLoadDuringDischarging);
      void resetParasiticElectricLoadDuringDischarging();

      boost::optional<double> parasiticElectricLoadDuringCharging() const;
      bool setParasiticElectricLoadDuringCharging(double parasiticElectricLoadDuringCharging);
      void resetParasiticElectricLoadDuringCharging();

      boost::optional<double> tankLossCoefficient() const;
      bool setTankLossCoefficient(double tankLossCoefficient);
      void resetTankLossCoefficient();

      double freezingTemperatureofStorageMedium() const;
      bool setFreezingTemperatureofStorageMedium(double freezingTemperatureofStorageMedium);
      bool isFreezingTemperatureofStorageMediumDefaulted() const;
      void resetFreezingTemperatureofStorageMedium();

      std::string thawProcessIndicator() const;
      bool setThawProcessIndicator(const std::string& thawProcessIndicator);
      bool isThawProcessIndicatorDefaulted() const;
      void resetThawProcessIndicator();

     private:
      boost::optional<Curve> optionalDischargingCurve() const;
      boost::optional<Curve> optionalChargingCurve() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_THERMALSTORAGEICEDETAILED_IMPL_HPP
