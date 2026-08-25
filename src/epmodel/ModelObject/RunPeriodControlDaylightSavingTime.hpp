/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_HPP
#define EPMODEL_RUNPERIODCONTROLDAYLIGHTSAVINGTIME_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RunPeriodControlDaylightSavingTime_Impl;
  }

  /** \brief RunPeriodControlDaylightSavingTime.
   *
   * \par EnergyPlus object
   * \epobject{group-location-climate-weather-file-access.html#runperiodcontroldaylightsavingtime,RunPeriodControl:DaylightSavingTime}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RunPeriodControlDaylightSavingTime</code>. EPModel accepts the start and end dates as strings. Model additionally provides date and nth-weekday overloads and <code>ensureNoLeapDays()</code>.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API RunPeriodControlDaylightSavingTime : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~RunPeriodControlDaylightSavingTime() override = default;
    RunPeriodControlDaylightSavingTime(const RunPeriodControlDaylightSavingTime& other) = default;
    RunPeriodControlDaylightSavingTime(RunPeriodControlDaylightSavingTime&& other) = default;
    RunPeriodControlDaylightSavingTime& operator=(const RunPeriodControlDaylightSavingTime&) = default;
    RunPeriodControlDaylightSavingTime& operator=(RunPeriodControlDaylightSavingTime&&) = default;

    static IddObjectType iddObjectType();
    std::string startDate() const;
    bool setStartDate(const std::string& startDate);

    std::string endDate() const;
    bool setEndDate(const std::string& endDate);

   protected:
    explicit RunPeriodControlDaylightSavingTime(const Model& model);

    using ImplType = detail::RunPeriodControlDaylightSavingTime_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RunPeriodControlDaylightSavingTime(std::shared_ptr<detail::RunPeriodControlDaylightSavingTime_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
