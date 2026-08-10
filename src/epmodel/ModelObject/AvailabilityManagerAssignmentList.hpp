/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERASSIGNMENTLIST_HPP
#define EPMODEL_AVAILABILITYMANAGERASSIGNMENTLIST_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class AvailabilityManager;
  class AirLoopHVAC;
  class Loop;
  class Model;
  class PlantLoop;

  namespace detail {
    class AvailabilityManagerAssignmentList_Impl;
  }

  class EPMODEL_API AvailabilityManagerAssignmentList : public ModelObject
  {
   public:
    explicit AvailabilityManagerAssignmentList(const Model& model);

    virtual ~AvailabilityManagerAssignmentList() override = default;
    AvailabilityManagerAssignmentList(const AvailabilityManagerAssignmentList& other) = default;
    AvailabilityManagerAssignmentList(AvailabilityManagerAssignmentList&& other) = default;
    AvailabilityManagerAssignmentList& operator=(const AvailabilityManagerAssignmentList&) = default;
    AvailabilityManagerAssignmentList& operator=(AvailabilityManagerAssignmentList&&) = default;

    static IddObjectType iddObjectType();

    /** @name Availability manager priority */
    //@{
    unsigned availabilityManagerPriority(const AvailabilityManager& availabilityManager) const;
    bool setAvailabilityManagerPriority(const AvailabilityManager& availabilityManager, unsigned priority);
    //@}

    /** @name Availability manager assignments */
    //@{
    std::vector<AvailabilityManager> availabilityManagers() const;

    bool addAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool addAvailabilityManager(const AvailabilityManager& availabilityManager, unsigned priority);

    bool setAvailabilityManagers(const std::vector<AvailabilityManager>& availabilityManagers);
    void resetAvailabilityManagers();

    bool removeAvailabilityManager(const AvailabilityManager& availabilityManager);
    bool removeAvailabilityManager(unsigned priority);
    //@}

    /** @name Loop associations */
    //@{
    // Schema Alignment Notes:
    // - Canonical Counterpart: openstudio::model::AvailabilityManagerAssignmentList.
    // - Implemented Parity: Singular loop, air-loop, and plant-loop reverse discovery follows the canonical loop-owned assignment-list target.
    // - Field/Storage Mapping: AirLoopHVAC and PlantLoop store the EnergyPlus Availability Manager List Name; the list stores ordered manager rows.
    // - Remaining Parity Work: Multi-loop assignment ambiguity and ZoneHVAC assignment-list ownership are not characterized.
    boost::optional<Loop> loop() const;
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    boost::optional<PlantLoop> plantLoop() const;
    //@}

   protected:
    using ImplType = detail::AvailabilityManagerAssignmentList_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerAssignmentList(std::shared_ptr<detail::AvailabilityManagerAssignmentList_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
