/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "BuildingStory.hpp"
#include "BuildingStory_Impl.hpp"
#include "SpaceList.hpp"
#include "SpaceList_Impl.hpp"

#include "Model.hpp"
#include "PlanarSurfaceGroup/Space.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_BuildingStory_FieldEnums.hxx>

#include <fmt/format.h>

#include <sstream>

namespace openstudio {
namespace epmodel {

  BuildingStory::BuildingStory(const Model& model) : ModelObject(BuildingStory::iddObjectType(), model, false, true) {
    SpaceList spaceList(model);
    auto impl = getImpl<detail::BuildingStory_Impl>();
    impl->setSpaceListHandle(spaceList.handle());
    spaceList.setComment("BuildingStory()");
  }

  BuildingStory::BuildingStory(std::shared_ptr<detail::BuildingStory_Impl> impl) : ModelObject(std::move(impl)) {}

  BuildingStory::BuildingStory(const SpaceList& spaceList) : ModelObject(BuildingStory::iddObjectType(), spaceList.model(), false, true) {
    getImpl<detail::BuildingStory_Impl>()->setSpaceListHandle(spaceList.handle());
  }

  IddObjectType BuildingStory::iddObjectType() {
    return IddObjectType::OS_BuildingStory;
  }

  boost::optional<double> BuildingStory::nominalZCoordinate() const {
    return getImpl<detail::BuildingStory_Impl>()->nominalZCoordinate();
  }

  bool BuildingStory::setNominalZCoordinate(double nominalZCoordinate) {
    return getImpl<detail::BuildingStory_Impl>()->setNominalZCoordinate(nominalZCoordinate);
  }

  void BuildingStory::resetNominalZCoordinate() {
    getImpl<detail::BuildingStory_Impl>()->resetNominalZCoordinate();
  }

  boost::optional<double> BuildingStory::nominalFloortoFloorHeight() const {
    return getImpl<detail::BuildingStory_Impl>()->nominalFloortoFloorHeight();
  }

  bool BuildingStory::setNominalFloortoFloorHeight(double nominalFloortoFloorHeight) {
    return getImpl<detail::BuildingStory_Impl>()->setNominalFloortoFloorHeight(nominalFloortoFloorHeight);
  }

  void BuildingStory::resetNominalFloortoFloorHeight() {
    getImpl<detail::BuildingStory_Impl>()->resetNominalFloortoFloorHeight();
  }

  boost::optional<double> BuildingStory::nominalFloortoCeilingHeight() const {
    return getImpl<detail::BuildingStory_Impl>()->nominalFloortoCeilingHeight();
  }

  bool BuildingStory::setNominalFloortoCeilingHeight(double nominalFloortoCeilingHeight) {
    return getImpl<detail::BuildingStory_Impl>()->setNominalFloortoCeilingHeight(nominalFloortoCeilingHeight);
  }

  void BuildingStory::resetNominalFloortoCeilingHeight() {
    getImpl<detail::BuildingStory_Impl>()->resetNominalFloortoCeilingHeight();
  }

  SpaceList BuildingStory::spaceList() const {
    return getImpl<detail::BuildingStory_Impl>()->spaceList();
  }

  bool BuildingStory::addSpace(const Space& space) {
    return getImpl<detail::BuildingStory_Impl>()->addSpace(space);
  }

  std::vector<Space> BuildingStory::spaces() const {
    return getImpl<detail::BuildingStory_Impl>()->spaces();
  }

  boost::optional<BuildingStory> BuildingStory::fromSpaceList(const SpaceList& spaceList) {
    std::string comment = spaceList.comment();
    // strip "! " prefix if present
    if (comment.size() >= 2 && comment[0] == '!' && comment[1] == ' ') {
      comment = comment.substr(2);
    }

    static constexpr std::string_view prefix = "BuildingStory(";
    if (comment.substr(0, prefix.size()) != prefix || comment.back() != ')') {
      return boost::none;
    }

    // extract key=value pairs between "BuildingStory(" and ")"
    std::string inner = comment.substr(prefix.size(), comment.size() - prefix.size() - 1);

    BuildingStory story(spaceList);

    if (!inner.empty()) {
      std::istringstream ss(inner);
      std::string pair;
      while (std::getline(ss, pair, '|')) {
        const auto eq = pair.find('=');
        if (eq == std::string::npos) {
          continue;
        }
        const std::string key = pair.substr(0, eq);
        const double val = std::stod(pair.substr(eq + 1));
        if (key == "NominalZCoordinate") {
          story.getImpl<detail::BuildingStory_Impl>()->setNominalZCoordinate(val);
        } else if (key == "NominalFloortoFloorHeight") {
          story.getImpl<detail::BuildingStory_Impl>()->setNominalFloortoFloorHeight(val);
        } else if (key == "NominalFloortoCeilingHeight") {
          story.getImpl<detail::BuildingStory_Impl>()->setNominalFloortoCeilingHeight(val);
        }
      }
    }

    return story;
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    void BuildingStory_Impl::setSpaceListHandle(const Handle& handle) {
      m_spaceListHandle = handle;
    }

    void BuildingStory_Impl::updateSpaceListComment() {
      std::vector<std::string> parts;
      if (auto v = nominalZCoordinate()) {
        parts.push_back(fmt::format("NominalZCoordinate={:g}", *v));
      }
      if (auto v = nominalFloortoFloorHeight()) {
        parts.push_back(fmt::format("NominalFloortoFloorHeight={:g}", *v));
      }
      if (auto v = nominalFloortoCeilingHeight()) {
        parts.push_back(fmt::format("NominalFloortoCeilingHeight={:g}", *v));
      }

      std::string inner;
      for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) {
          inner += '|';
        }
        inner += parts[i];
      }
      spaceList().setComment("BuildingStory(" + inner + ")");
    }

    boost::optional<double> BuildingStory_Impl::nominalZCoordinate() const {
      return getDouble(openstudio::OS_BuildingStoryFields::NominalZCoordinate, true);
    }

    bool BuildingStory_Impl::setNominalZCoordinate(double nominalZCoordinate) {
      bool result = setDouble(openstudio::OS_BuildingStoryFields::NominalZCoordinate, nominalZCoordinate);
      if (result) {
        updateSpaceListComment();
      }
      return result;
    }

    void BuildingStory_Impl::resetNominalZCoordinate() {
      OS_ASSERT(setString(openstudio::OS_BuildingStoryFields::NominalZCoordinate, ""));
      updateSpaceListComment();
    }

    boost::optional<double> BuildingStory_Impl::nominalFloortoFloorHeight() const {
      return getDouble(openstudio::OS_BuildingStoryFields::NominalFloortoFloorHeight, true);
    }

    bool BuildingStory_Impl::setNominalFloortoFloorHeight(double nominalFloortoFloorHeight) {
      bool result = setDouble(openstudio::OS_BuildingStoryFields::NominalFloortoFloorHeight, nominalFloortoFloorHeight);
      if (result) {
        updateSpaceListComment();
      }
      return result;
    }

    void BuildingStory_Impl::resetNominalFloortoFloorHeight() {
      OS_ASSERT(setString(openstudio::OS_BuildingStoryFields::NominalFloortoFloorHeight, ""));
      updateSpaceListComment();
    }

    boost::optional<double> BuildingStory_Impl::nominalFloortoCeilingHeight() const {
      return getDouble(openstudio::OS_BuildingStoryFields::NominalFloortoCeilingHeight, true);
    }

    bool BuildingStory_Impl::setNominalFloortoCeilingHeight(double nominalFloortoCeilingHeight) {
      bool result = setDouble(openstudio::OS_BuildingStoryFields::NominalFloortoCeilingHeight, nominalFloortoCeilingHeight);
      if (result) {
        updateSpaceListComment();
      }
      return result;
    }

    void BuildingStory_Impl::resetNominalFloortoCeilingHeight() {
      OS_ASSERT(setString(openstudio::OS_BuildingStoryFields::NominalFloortoCeilingHeight, ""));
      updateSpaceListComment();
    }

    SpaceList BuildingStory_Impl::spaceList() const {
      auto obj = model().getObject(m_spaceListHandle);
      OS_ASSERT(obj);
      return obj->cast<SpaceList>();
    }

    bool BuildingStory_Impl::addSpace(const Space& space) {
      return spaceList().addSpace(space);
    }

    std::vector<Space> BuildingStory_Impl::spaces() const {
      return spaceList().spaces();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
