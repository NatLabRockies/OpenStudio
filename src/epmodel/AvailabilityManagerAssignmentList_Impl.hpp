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

namespace detail {

class EPMODEL_API AvailabilityManagerAssignmentList_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~AvailabilityManagerAssignmentList_Impl() override = default;

  unsigned availabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager) const;
  std::vector<openstudio::epmodel::AvailabilityManager> availabilityManagers() const;

  boost::optional<openstudio::epmodel::Loop> loop() const;
  boost::optional<openstudio::epmodel::AirLoopHVAC> airLoopHVAC() const;

  bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
  bool addAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);

  bool setAvailabilityManagers(const std::vector<openstudio::epmodel::AvailabilityManager>& availabilityManagers);
  void resetAvailabilityManagers();

  bool removeAvailabilityManager(const openstudio::epmodel::AvailabilityManager& availabilityManager);
  bool removeAvailabilityManager(unsigned priority);

  bool setAvailabilityManagerPriority(const openstudio::epmodel::AvailabilityManager& availabilityManager, unsigned priority);

  void doCanonicalize(LoadContext& context) override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
