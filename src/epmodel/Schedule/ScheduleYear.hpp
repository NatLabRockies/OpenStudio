/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEYEAR_HPP
#define EPMODEL_SCHEDULEYEAR_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleYear_Impl;
  }

  /** \brief Selects a schedule week for each part of a year.
   *
   * \par EnergyPlus object
   * \epobject{group-schedules.html#scheduleyear,Schedule:Year}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleYear</code>.
   *
   * - <b>Not yet available:</b> <code>dates()</code>,
   *   <code>scheduleWeeks()</code>, <code>addScheduleWeek(...)</code>,
   *   <code>clearScheduleWeeks()</code>, and
   *   <code>getScheduleWeek(...)</code>.
   *
   * \par Known limitations
   * EPModel can load and preserve a <code>Schedule:Year</code> object, but its
   * public typed API cannot create or edit the date-to-week assignments that
   * determine which schedule applies during the year.
   */
  class EPMODEL_API ScheduleYear : public Schedule
  {
   public:
    explicit ScheduleYear(const Model& model);

    virtual ~ScheduleYear() override = default;
    ScheduleYear(const ScheduleYear& other) = default;
    ScheduleYear(ScheduleYear&& other) = default;
    ScheduleYear& operator=(const ScheduleYear&) = default;
    ScheduleYear& operator=(ScheduleYear&&) = default;

    static IddObjectType iddObjectType();

   protected:
    using ImplType = detail::ScheduleYear_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleYear(std::shared_ptr<detail::ScheduleYear_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
