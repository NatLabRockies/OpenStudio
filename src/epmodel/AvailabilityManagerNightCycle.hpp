/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP
#define EPMODEL_AVAILABILITYMANAGERNIGHTCYCLE_HPP

#include "EPModelAPI.hpp"
#include "AvailabilityManager.hpp"

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;
class Model;

namespace detail {
class AvailabilityManagerNightCycle_Impl;
}

class EPMODEL_API AvailabilityManagerNightCycle : public AvailabilityManager
{
 public:
  explicit AvailabilityManagerNightCycle(const Model& model);

  virtual ~AvailabilityManagerNightCycle() override = default;
  AvailabilityManagerNightCycle(const AvailabilityManagerNightCycle& other) = default;
  AvailabilityManagerNightCycle(AvailabilityManagerNightCycle&& other) = default;
  AvailabilityManagerNightCycle& operator=(const AvailabilityManagerNightCycle&) = default;
  AvailabilityManagerNightCycle& operator=(AvailabilityManagerNightCycle&&) = default;

  static IddObjectType iddObjectType();
  static std::vector<std::string> controlTypeValues();

  boost::optional<AirLoopHVAC> airLoopHVAC() const;

  std::string controlType() const;
  bool setControlType(const std::string& controlType);
  void resetControlType();
  bool isControlTypeDefaulted() const;

 protected:
  using ImplType = detail::AvailabilityManagerNightCycle_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AvailabilityManagerNightCycle(std::shared_ptr<detail::AvailabilityManagerNightCycle_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
