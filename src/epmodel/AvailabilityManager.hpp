/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGER_HPP
#define EPMODEL_AVAILABILITYMANAGER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Loop;
class Model;

namespace detail {
class AvailabilityManager_Impl;
}

class EPMODEL_API AvailabilityManager : public ModelObject
{
 public:
  virtual ~AvailabilityManager() override = default;
  AvailabilityManager(const AvailabilityManager& other) = default;
  AvailabilityManager(AvailabilityManager&& other) = default;
  AvailabilityManager& operator=(const AvailabilityManager&) = default;
  AvailabilityManager& operator=(AvailabilityManager&&) = default;

  boost::optional<Loop> loop() const;

 protected:
  using ImplType = detail::AvailabilityManager_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  AvailabilityManager(IddObjectType type, const Model& model);
  explicit AvailabilityManager(std::shared_ptr<detail::AvailabilityManager_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
