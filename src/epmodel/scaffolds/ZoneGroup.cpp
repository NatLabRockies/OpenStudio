/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneGroup.hpp"
#include "ZoneGroup_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneGroup_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

#include <utility>

namespace openstudio {
namespace epmodel {

  ZoneGroup::ZoneGroup(const Model& model) : ModelObject(ZoneGroup::iddObjectType(), model) {}

  ZoneGroup::ZoneGroup(std::shared_ptr<detail::ZoneGroup_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneGroup::iddObjectType() {
    return IddObjectType::ZoneGroup;
  }

  int ZoneGroup::zoneListMultiplier() const {
    return getImpl<detail::ZoneGroup_Impl>()->zoneListMultiplier();
  }

  bool ZoneGroup::setZoneListMultiplier(int zoneListMultiplier) {
    return getImpl<detail::ZoneGroup_Impl>()->setZoneListMultiplier(zoneListMultiplier);
  }

  bool ZoneGroup::isZoneListMultiplierDefaulted() const {
    return getImpl<detail::ZoneGroup_Impl>()->isZoneListMultiplierDefaulted();
  }

  void ZoneGroup::resetZoneListMultiplier() {
    getImpl<detail::ZoneGroup_Impl>()->resetZoneListMultiplier();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int ZoneGroup_Impl::zoneListMultiplier() const {
      const auto value = getInt(openstudio::ZoneGroupFields::ZoneListMultiplier, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneGroup_Impl::setZoneListMultiplier(int zoneListMultiplier) {
      return setInt(openstudio::ZoneGroupFields::ZoneListMultiplier, zoneListMultiplier);
    }

    bool ZoneGroup_Impl::isZoneListMultiplierDefaulted() const {
      return isEmpty(openstudio::ZoneGroupFields::ZoneListMultiplier);
    }

    void ZoneGroup_Impl::resetZoneListMultiplier() {
      const bool result = setString(openstudio::ZoneGroupFields::ZoneListMultiplier, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
