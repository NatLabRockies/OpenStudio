/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEINDOOR_IMPL_HPP
#define EPMODEL_PIPEINDOOR_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class Construction;
  class Schedule;
  class ThermalZone;
  namespace detail {

    class EPMODEL_API PipeIndoor_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~PipeIndoor_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      boost::optional<Construction> construction() const;
      bool setConstruction(const Construction& construction);
      void resetConstruction();

      std::string environmentType() const;
      bool setEnvironmentType(const std::string& environmentType);

      boost::optional<ThermalZone> ambientTemperatureZone() const;
      bool setAmbientTemperatureZone(const ThermalZone& thermalZone);
      void resetAmbientTemperatureZone();

      boost::optional<Schedule> ambientTemperatureSchedule() const;
      bool setAmbientTemperatureSchedule(Schedule& schedule);
      void resetAmbientTemperatureSchedule();

      boost::optional<Schedule> ambientAirVelocitySchedule() const;
      bool setAmbientAirVelocitySchedule(Schedule& schedule);
      void resetAmbientAirVelocitySchedule();

      double pipeInsideDiameter() const;
      bool setPipeInsideDiameter(double pipeInsideDiameter);

      double pipeLength() const;
      bool setPipeLength(double pipeLength);

      std::vector<std::string> environmentTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
