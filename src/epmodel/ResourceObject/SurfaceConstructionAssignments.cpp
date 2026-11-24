/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/SurfaceConstructionAssignments.hpp"
#include "ResourceObject/SurfaceConstructionAssignments_Impl.hpp"

#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SurfaceConstructionAssignments_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfaceConstructionAssignments::SurfaceConstructionAssignments(const Model& model)
    : ResourceObject(SurfaceConstructionAssignments::iddObjectType(), model) {}

  SurfaceConstructionAssignments::SurfaceConstructionAssignments(std::shared_ptr<detail::SurfaceConstructionAssignments_Impl> impl)
    : ResourceObject(std::move(impl)) {}

  IddObjectType SurfaceConstructionAssignments::iddObjectType() {
    return IddObjectType::SurfaceConstructionAssignments;
  }

  boost::optional<ConstructionBase> SurfaceConstructionAssignments::floorConstruction() const {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->floorConstruction();
  }

  bool SurfaceConstructionAssignments::setFloorConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->setFloorConstruction(construction);
  }

  void SurfaceConstructionAssignments::resetFloorConstruction() {
    getImpl<detail::SurfaceConstructionAssignments_Impl>()->resetFloorConstruction();
  }

  boost::optional<ConstructionBase> SurfaceConstructionAssignments::wallConstruction() const {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->wallConstruction();
  }

  bool SurfaceConstructionAssignments::setWallConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->setWallConstruction(construction);
  }

  void SurfaceConstructionAssignments::resetWallConstruction() {
    getImpl<detail::SurfaceConstructionAssignments_Impl>()->resetWallConstruction();
  }

  boost::optional<ConstructionBase> SurfaceConstructionAssignments::roofCeilingConstruction() const {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->roofCeilingConstruction();
  }

  bool SurfaceConstructionAssignments::setRoofCeilingConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SurfaceConstructionAssignments_Impl>()->setRoofCeilingConstruction(construction);
  }

  void SurfaceConstructionAssignments::resetRoofCeilingConstruction() {
    getImpl<detail::SurfaceConstructionAssignments_Impl>()->resetRoofCeilingConstruction();
  }

  void SurfaceConstructionAssignments::merge(const SurfaceConstructionAssignments& other) {
    getImpl<detail::SurfaceConstructionAssignments_Impl>()->merge(other);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ConstructionBase> SurfaceConstructionAssignments_Impl::floorConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SurfaceConstructionAssignmentsFields::FloorConstructionName);
    }

    bool SurfaceConstructionAssignments_Impl::setFloorConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SurfaceConstructionAssignmentsFields::FloorConstructionName, construction.handle());
    }

    void SurfaceConstructionAssignments_Impl::resetFloorConstruction() {
      OS_ASSERT(setString(openstudio::SurfaceConstructionAssignmentsFields::FloorConstructionName, ""));
    }

    boost::optional<ConstructionBase> SurfaceConstructionAssignments_Impl::wallConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SurfaceConstructionAssignmentsFields::WallConstructionName);
    }

    bool SurfaceConstructionAssignments_Impl::setWallConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SurfaceConstructionAssignmentsFields::WallConstructionName, construction.handle());
    }

    void SurfaceConstructionAssignments_Impl::resetWallConstruction() {
      OS_ASSERT(setString(openstudio::SurfaceConstructionAssignmentsFields::WallConstructionName, ""));
    }

    boost::optional<ConstructionBase> SurfaceConstructionAssignments_Impl::roofCeilingConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(
        openstudio::SurfaceConstructionAssignmentsFields::RoofCeilingConstructionName);
    }

    bool SurfaceConstructionAssignments_Impl::setRoofCeilingConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SurfaceConstructionAssignmentsFields::RoofCeilingConstructionName, construction.handle());
    }

    void SurfaceConstructionAssignments_Impl::resetRoofCeilingConstruction() {
      OS_ASSERT(setString(openstudio::SurfaceConstructionAssignmentsFields::RoofCeilingConstructionName, ""));
    }

    void SurfaceConstructionAssignments_Impl::merge(const SurfaceConstructionAssignments& other) {
      if (!floorConstruction()) {
        if (auto construction = other.floorConstruction()) {
          setFloorConstruction(*construction);
        }
      }

      if (!wallConstruction()) {
        if (auto construction = other.wallConstruction()) {
          setWallConstruction(*construction);
        }
      }

      if (!roofCeilingConstruction()) {
        if (auto construction = other.roofCeilingConstruction()) {
          setRoofCeilingConstruction(*construction);
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
