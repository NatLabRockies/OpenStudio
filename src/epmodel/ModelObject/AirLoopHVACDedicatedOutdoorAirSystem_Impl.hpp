/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_IMPL_HPP
#define EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVACOutdoorAirSystem;
  class Schedule;
  class AirLoopHVAC;
  class AirLoopHVACMixer;
  class AirLoopHVACSplitter;

  namespace detail {

    class EPMODEL_API AirLoopHVACDedicatedOutdoorAirSystem_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirLoopHVACDedicatedOutdoorAirSystem_Impl() override = default;

      openstudio::epmodel::AirLoopHVACOutdoorAirSystem airLoopHVACOutdoorAirSystem() const;
      openstudio::epmodel::Schedule availabilitySchedule() const;

      double preheatDesignTemperature() const;
      bool setPreheatDesignTemperature(double preheatDesignTemperature);

      double preheatDesignHumidityRatio() const;
      bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

      double precoolDesignTemperature() const;
      bool setPrecoolDesignTemperature(double precoolDesignTemperature);

      double precoolDesignHumidityRatio() const;
      bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

      unsigned int numberofAirLoops() const;
      std::vector<openstudio::epmodel::AirLoopHVAC> airLoops() const;
      boost::optional<unsigned> airLoopIndex(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC) const;

      bool setAirLoopHVACOutdoorAirSystem(const openstudio::epmodel::AirLoopHVACOutdoorAirSystem& airLoopHVACOutdoorAirSystem);
      bool setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule);
      bool addAirLoop(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC);
      std::vector<openstudio::IdfObject> remove() override;
      bool removeAirLoop(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC);
      bool removeAirLoop(unsigned groupIndex);
      void removeAllAirLoops();
      bool addAirLoops(const std::vector<openstudio::epmodel::AirLoopHVAC>& airLoopHVACs);

      boost::optional<openstudio::epmodel::AirLoopHVACMixer> airLoopHVACMixer() const;
      boost::optional<openstudio::epmodel::AirLoopHVACSplitter> airLoopHVACSplitter() const;

     private:
      bool ensureMixerAndSplitter();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
