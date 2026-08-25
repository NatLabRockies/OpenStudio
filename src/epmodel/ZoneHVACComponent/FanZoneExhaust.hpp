/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANZONEEXHAUST_HPP
#define EPMODEL_FANZONEEXHAUST_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;
  class Schedule;

  namespace detail {
    class FanZoneExhaust_Impl;
  }

/** \brief An exhaust fan serving a thermal zone.
 *
 * \par EnergyPlus object
 * \epobject{group-fans.html#fanzoneexhaust,Fan:ZoneExhaust}
 *
 * \par Important behavior
 * Zone attachment is represented through the EnergyPlus zone equipment list and exhaust-node fields; orphaned transient inlet and outlet nodes are removed on detachment.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::FanZoneExhaust</code>.
 *
 * \par Known limitations
 * AirflowNetwork helpers and separate air-loop exhaust-system ownership are not exposed.
 */
  class EPMODEL_API FanZoneExhaust : public ZoneHVACComponent
  {
   public:
    explicit FanZoneExhaust(const Model& model);

    virtual ~FanZoneExhaust() override = default;
    FanZoneExhaust(const FanZoneExhaust& other) = default;
    FanZoneExhaust(FanZoneExhaust&& other) = default;
    FanZoneExhaust& operator=(const FanZoneExhaust&) = default;
    FanZoneExhaust& operator=(FanZoneExhaust&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> systemAvailabilityManagerCouplingModeValues();

    boost::optional<Schedule> availabilitySchedule() const;
    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    double fanTotalEfficiency() const;
    bool setFanTotalEfficiency(double fanTotalEfficiency);

    double fanEfficiency() const;
    bool setFanEfficiency(double fanTotalEfficiency);

    double pressureRise() const;
    bool setPressureRise(double pressureRise);

    boost::optional<double> maximumFlowRate() const;
    bool setMaximumFlowRate(double maximumFlowRate);
    void resetMaximumFlowRate();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);

    boost::optional<Schedule> flowFractionSchedule() const;
    bool setFlowFractionSchedule(Schedule& schedule);
    void resetFlowFractionSchedule();

    std::string systemAvailabilityManagerCouplingMode() const;
    bool setSystemAvailabilityManagerCouplingMode(const std::string& systemAvailabilityManagerCouplingMode);

    boost::optional<Schedule> minimumZoneTemperatureLimitSchedule() const;
    bool setMinimumZoneTemperatureLimitSchedule(Schedule& schedule);
    void resetMinimumZoneTemperatureLimitSchedule();

    boost::optional<Schedule> balancedExhaustFractionSchedule() const;
    bool setBalancedExhaustFractionSchedule(Schedule& schedule);
    void resetBalancedExhaustFractionSchedule();

   protected:
    using ImplType = detail::FanZoneExhaust_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FanZoneExhaust(std::shared_ptr<detail::FanZoneExhaust_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
