/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULECONSTANT_HPP
#define EPMODEL_SCHEDULECONSTANT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleConstant_Impl;
  }

  class EPMODEL_API ScheduleConstant : public ModelObject
  {
   public:
    explicit ScheduleConstant(const Model& model);

    virtual ~ScheduleConstant() override = default;
    ScheduleConstant(const ScheduleConstant& other) = default;
    ScheduleConstant(ScheduleConstant&& other) = default;
    ScheduleConstant& operator=(const ScheduleConstant&) = default;
    ScheduleConstant& operator=(ScheduleConstant&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ScheduleConstant scalar API names/signatures where mappable in epmodel.
    // - Field Mapping: value/setValue map to EnergyPlus Schedule:Constant field Hourly Value.
    // - Field Mapping: scheduleTypeLimits is relationship-like (Schedule Type Limits Name object-list target) and excluded.
    // - ForwardTranslator evidence: ForwardTranslateScheduleConstant.cpp writes ScheduleTypeLimitsName and value -> HourlyValue.
    // - TODO(parity): Add relationship APIs incrementally without changing preserved scalar signatures.
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
