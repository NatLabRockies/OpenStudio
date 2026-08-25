/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_RUNPERIODCONTROLSPECIALDAYS_HPP
#define EPMODEL_RUNPERIODCONTROLSPECIALDAYS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RunPeriodControlSpecialDays_Impl;
  }

  /** \brief RunPeriodControlSpecialDays.
   *
   * \par EnergyPlus object
   * \epobject{group-location-climate-weather-file-access.html#runperiodcontrolspecialdays,RunPeriodControl:SpecialDays}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::RunPeriodControlSpecialDays</code>. EPModel accepts the start date as a string and does not provide Model's date/nth-weekday overloads or <code>ensureNoLeapDays()</code>. EnergyPlus uses <code>Last</code> for a fifth-weekday date; translation of Model input performs that text conversion.
   *
   * \par Known limitations
   * Only the fields and relationships listed in this wrapper are available; broader Model-only helpers are not exposed.
   */
  class EPMODEL_API RunPeriodControlSpecialDays : public ModelObject
  {
   public:
    explicit RunPeriodControlSpecialDays(const Model& model);

    virtual ~RunPeriodControlSpecialDays() override = default;
    RunPeriodControlSpecialDays(const RunPeriodControlSpecialDays& other) = default;
    RunPeriodControlSpecialDays(RunPeriodControlSpecialDays&& other) = default;
    RunPeriodControlSpecialDays& operator=(const RunPeriodControlSpecialDays&) = default;
    RunPeriodControlSpecialDays& operator=(RunPeriodControlSpecialDays&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> specialDayTypeValues();
    static std::vector<std::string> validSpecialDayTypeValues();
    std::string startDate() const;
    bool setStartDate(const std::string& startDate);

    unsigned duration() const;
    bool setDuration(unsigned duration);

    std::string specialDayType() const;
    bool setSpecialDayType(const std::string& specialDayType);

   protected:
    using ImplType = detail::RunPeriodControlSpecialDays_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RunPeriodControlSpecialDays(std::shared_ptr<detail::RunPeriodControlSpecialDays_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
