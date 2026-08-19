/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLHUMIDISTAT_HPP
#define EPMODEL_ZONECONTROLHUMIDISTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;
  class ThermalZone;

  namespace detail {
    class ZoneControlHumidistat_Impl;
  }

  /** \brief ZoneControlHumidistat.
   *
   * \par EnergyPlus object
   * \epobject{group-zone-controls-thermostats.html#zonecontrolhumidistat,ZoneControl:Humidistat}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneControlHumidistat</code>. The controlled-zone and humidifying/dehumidifying schedule relationships are exposed; schedule setters enforce their supported humidity limits.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneControlHumidistat : public ModelObject
  {
   public:
    explicit ZoneControlHumidistat(const Model& model);

    virtual ~ZoneControlHumidistat() override = default;
    ZoneControlHumidistat(const ZoneControlHumidistat& other) = default;
    ZoneControlHumidistat(ZoneControlHumidistat&& other) = default;
    ZoneControlHumidistat& operator=(const ZoneControlHumidistat&) = default;
    ZoneControlHumidistat& operator=(ZoneControlHumidistat&&) = default;

    static IddObjectType iddObjectType();
    boost::optional<ThermalZone> controlledZone() const;

    boost::optional<Schedule> humidifyingRelativeHumiditySetpointSchedule() const;
    boost::optional<Schedule> dehumidifyingRelativeHumiditySetpointSchedule() const;

    bool setHumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule);
    bool setDehumidifyingRelativeHumiditySetpointSchedule(Schedule& schedule);

    void resetHumidifyingRelativeHumiditySetpointSchedule();
    void resetDehumidifyingRelativeHumiditySetpointSchedule();

   protected:
    using ImplType = detail::ZoneControlHumidistat_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneControlHumidistat(std::shared_ptr<detail::ZoneControlHumidistat_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONECONTROLHUMIDISTAT_HPP
