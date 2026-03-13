/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SCHEDULEDAYLIST_HPP
#define EPMODEL_SCHEDULEDAYLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ScheduleDayList_Impl;
  }

  class EPMODEL_API ScheduleDayList : public ModelObject
  {
   public:
    explicit ScheduleDayList(const Model& model);

    virtual ~ScheduleDayList() override = default;
    ScheduleDayList(const ScheduleDayList& other) = default;
    ScheduleDayList(ScheduleDayList&& other) = default;
    ScheduleDayList& operator=(const ScheduleDayList&) = default;
    ScheduleDayList& operator=(ScheduleDayList&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> interpolatetoTimestepValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: interpolatetoTimestep and minutesperItem map directly to EnergyPlus Schedule:Day:List
    //   fields Interpolate to Timestep and Minutes per Item.
    // - Field Mapping: Schedule Type Limits Name is an object-list relationship field and is intentionally excluded.
    // - Field Mapping: extensible Value fields are intentionally excluded in this scalar-only scaffold pass.
    // - Field Mapping: Name remains provided by base ModelObject naming APIs.
    // - TODO(parity): Add relationship/extensible value APIs incrementally after scalar saturation.
    std::string interpolatetoTimestep() const;
    bool isInterpolatetoTimestepDefaulted() const;
    bool setInterpolatetoTimestep(const std::string& interpolatetoTimestep);
    void resetInterpolatetoTimestep();

    boost::optional<int> minutesperItem() const;
    bool setMinutesperItem(int minutesperItem);
    void resetMinutesperItem();

   protected:
    using ImplType = detail::ScheduleDayList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ScheduleDayList(std::shared_ptr<detail::ScheduleDayList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
