/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP
#define EPMODEL_AIRLOOPHVACDEDICATEDOUTDOORAIRSYSTEM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class AirLoopHVACOutdoorAirSystem;
  class Schedule;
  class AirLoopHVAC;

  namespace detail {
    class AirLoopHVACDedicatedOutdoorAirSystem_Impl;
  }

  /** \brief Represents the EnergyPlus AirLoopHVAC:DedicatedOutdoorAirSystem object.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacdedicatedoutdoorairsystem,AirLoopHVAC:DedicatedOutdoorAirSystem}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACDedicatedOutdoorAirSystem</code>. <b>Changed:</b> EPModel also permits direct construction from <code>Model</code>. EPModel requires each served air loop to have its own outdoor-air system and retains that system when the DOAS is removed.
   *
   * \par Known limitations
   * Adding/removing air loops updates aligned EnergyPlus extensible rows and owned mixer/splitter topology; broader equipment lifecycle and clone workflows remain restricted.
   */
  class EPMODEL_API AirLoopHVACDedicatedOutdoorAirSystem : public ModelObject
  {
   public:
    explicit AirLoopHVACDedicatedOutdoorAirSystem(const Model& model);
    explicit AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& oaSystem);

    virtual ~AirLoopHVACDedicatedOutdoorAirSystem() override = default;
    AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACDedicatedOutdoorAirSystem& other) = default;
    AirLoopHVACDedicatedOutdoorAirSystem(AirLoopHVACDedicatedOutdoorAirSystem&& other) = default;
    AirLoopHVACDedicatedOutdoorAirSystem& operator=(const AirLoopHVACDedicatedOutdoorAirSystem&) = default;
    AirLoopHVACDedicatedOutdoorAirSystem& operator=(AirLoopHVACDedicatedOutdoorAirSystem&&) = default;

    static IddObjectType iddObjectType();

    AirLoopHVACOutdoorAirSystem airLoopHVACOutdoorAirSystem() const;
    Schedule availabilitySchedule() const;

    double preheatDesignTemperature() const;
    bool setPreheatDesignTemperature(double preheatDesignTemperature);

    double preheatDesignHumidityRatio() const;
    bool setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio);

    double precoolDesignTemperature() const;
    bool setPrecoolDesignTemperature(double precoolDesignTemperature);

    double precoolDesignHumidityRatio() const;
    bool setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio);

    unsigned int numberofAirLoops() const;
    std::vector<AirLoopHVAC> airLoops() const;
    boost::optional<unsigned> airLoopIndex(const AirLoopHVAC& airLoopHVAC) const;

    bool setAirLoopHVACOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& airLoopHVACOutdoorAirSystem);
    bool setAvailabilitySchedule(Schedule& schedule);
    bool addAirLoop(const AirLoopHVAC& airLoopHVAC);
    bool removeAirLoop(const AirLoopHVAC& airLoopHVAC);
    bool removeAirLoop(unsigned groupIndex);
    void removeAllAirLoops();
    bool addAirLoops(const std::vector<AirLoopHVAC>& airLoopHVACs);

   protected:
    using ImplType = detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACDedicatedOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
