/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SpaceList.hpp"
#include "SpaceList_Impl.hpp"
#include "BuildingStory.hpp"

#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SpaceList_FieldEnums.hxx>
#include <utilities/idf/IdfExtensibleGroup.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  SpaceList::SpaceList(const Model& model) : ModelObject(SpaceList::iddObjectType(), model) {}

  SpaceList::SpaceList(std::shared_ptr<detail::SpaceList_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SpaceList::iddObjectType() {
    return IddObjectType::SpaceList;
  }

  bool SpaceList::addSpace(const Space& space) {
    return getImpl<detail::SpaceList_Impl>()->addSpace(space);
  }

  std::vector<Space> SpaceList::spaces() const {
    return getImpl<detail::SpaceList_Impl>()->spaces();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool SpaceList_Impl::addSpace(const Space& space) {
      auto group = getObject<SpaceList>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
      return group.setPointer(openstudio::SpaceListExtensibleFields::SpaceName, space.handle());
    }

    std::vector<Space> SpaceList_Impl::spaces() const {
      std::vector<Space> result;
      for (const auto& eg : extensibleGroups()) {
        auto group = eg.cast<WorkspaceExtensibleGroup>();
        if (auto wo = group.getTarget(openstudio::SpaceListExtensibleFields::SpaceName)) {
          result.push_back(wo->cast<Space>());
        }
      }
      return result;
    }

    void SpaceList_Impl::doCanonicalize(LoadContext& /*context*/) {
      auto thisList = getObject<SpaceList>();
      BuildingStory::fromSpaceList(thisList);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
