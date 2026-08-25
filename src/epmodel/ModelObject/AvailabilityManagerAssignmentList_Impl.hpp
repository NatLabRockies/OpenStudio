/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERASSIGNMENTLIST_IMPL_HPP
#define EPMODEL_AVAILABILITYMANAGERASSIGNMENTLIST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class AvailabilityManager;
  class Loop;
  class PlantLoop;

  namespace detail {

    class EPMODEL_API AvailabilityManagerAssignmentList_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AvailabilityManagerAssignmentList_Impl() override = default;

      /** @name Availability manager priority */
      //@{
      unsigned availabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager) const;
      bool setAvailabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);
      //@}

      /** @name Availability manager assignments */
      //@{
      std::vector<openstudio::epmodel::AvailabilityManager> availabilityManagers() const;
      bool setAvailabilityManagers(const std::vector<openstudio::epmodel::AvailabilityManager>& availabilityManagers);
      void resetAvailabilityManagers();

      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);

      bool removeAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
      bool removeAvailabilityManager(unsigned priority);
      //@}

      /** @name Loop associations */
      //@{
      boost::optional<openstudio::epmodel::Loop> loop() const;
      boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;
      boost::optional<openstudio::epmodel::PlantLoop> plantLoop() const;
      //@}

      void doCanonicalize(LoadContext& context) override;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
