/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECONSTANT_HPP
#define EPMODEL_SCHEDULECONSTANT_HPP

#include "EPModelAPI.hpp"
#include "Schedule/Schedule.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleConstant_Impl;
  }

  /** \brief Provides one constant schedule value for the entire year.
   *
   * \par EnergyPlus object
   * \epobject{group-schedules.html#scheduleconstant,Schedule:Constant}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::ScheduleConstant</code>. No known public API
   * differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ScheduleConstant : public Schedule
  {
   public:
    explicit ScheduleConstant(const Model& model);

    virtual ~ScheduleConstant() override = default;
    ScheduleConstant(const ScheduleConstant& other) = default;
    ScheduleConstant(ScheduleConstant&& other) = default;
    ScheduleConstant& operator=(const ScheduleConstant&) = default;
    ScheduleConstant& operator=(ScheduleConstant&&) = default;

    static IddObjectType iddObjectType();

    /** @name Accessors */
    //@{
    double value() const;
    bool setValue(double value);
    //@}

   protected:
    using ImplType = detail::ScheduleConstant_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleConstant(std::shared_ptr<detail::ScheduleConstant_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
