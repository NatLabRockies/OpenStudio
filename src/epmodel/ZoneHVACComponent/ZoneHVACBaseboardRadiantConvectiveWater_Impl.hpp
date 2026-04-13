/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_IMPL_HPP
#define EPMODEL_ZONEHVACBASEBOARDRADIANTCONVECTIVEWATER_IMPL_HPP

#include "ZoneHVACComponent/ZoneHVACComponent_Impl.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp"

#include <boost/optional.hpp>
#include <string>

namespace openstudio {
namespace epmodel {

  class HVACComponent;
  class ModelObject;
  class Schedule;
  class CoilHeatingWaterBaseboardRadiant;

  namespace detail {

    class CoilHeatingWaterBaseboardRadiant_Impl;

    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACBaseboardRadiantConvectiveWater& parent);

    class EPMODEL_API ZoneHVACBaseboardRadiantConvectiveWater_Impl : public ZoneHVACComponent_Impl
    {
     public:
      using ZoneHVACComponent_Impl::ZoneHVACComponent_Impl;
      virtual ~ZoneHVACBaseboardRadiantConvectiveWater_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;

      Schedule availabilitySchedule() const;
      bool setAvailabilitySchedule(Schedule& schedule);

      double fractionRadiant() const;
      bool setFractionRadiant(double fractionRadiant);

      double fractionofRadiantEnergyIncidentonPeople() const;
      bool setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople);

      CoilHeatingWaterBaseboardRadiant heatingCoil() const;
      bool setHeatingCoil(HVACComponent& heatingCoil);

      std::vector<ModelObject> children() const override;
      void doCanonicalize(LoadContext& context) override;

      boost::optional<double> ratedAverageWaterTemperature() const;
      bool isRatedAverageWaterTemperatureDefaulted() const;
      bool setRatedAverageWaterTemperature(double ratedAverageWaterTemperature);
      void resetRatedAverageWaterTemperature();

      boost::optional<double> ratedWaterMassFlowRate() const;
      bool isRatedWaterMassFlowRateDefaulted() const;
      bool setRatedWaterMassFlowRate(double ratedWaterMassFlowRate);
      void resetRatedWaterMassFlowRate();

      boost::optional<double> heatingDesignCapacity() const;
      bool isHeatingDesignCapacityAutosized() const;
      bool setHeatingDesignCapacity(double heatingDesignCapacity);
      void autosizeHeatingDesignCapacity();

      boost::optional<double> maximumWaterFlowRate() const;
      bool isMaximumWaterFlowRateAutosized() const;
      bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
      void autosizeMaximumWaterFlowRate();

     private:
      friend class openstudio::epmodel::ZoneHVACBaseboardRadiantConvectiveWater;
      friend class CoilHeatingWaterBaseboardRadiant_Impl;

      boost::optional<ZoneHVACBaseboardRadiantConvectiveWaterDesign> designObject() const;
      ZoneHVACBaseboardRadiantConvectiveWaterDesign ensureDesignObject();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
