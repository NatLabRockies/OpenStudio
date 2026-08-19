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

  /** \brief Base class for availability managers assigned to plant or air loops.
   *
   * \par EnergyPlus object
   * No single EnergyPlus object. The concrete wrappers represent
   * <code>AvailabilityManager:*</code> objects; only wrappers that expose the
   * typed availability-manager interface derive from this class.
   *
   * \par Important behavior
   * <code>loop()</code> discovers the owning loop from the model's
   * <code>AvailabilityManagerAssignmentList</code> objects.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::AvailabilityManager</code>. No known public API
   * differences.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
