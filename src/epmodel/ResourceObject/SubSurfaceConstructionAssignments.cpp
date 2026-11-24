/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/SubSurfaceConstructionAssignments.hpp"
#include "ResourceObject/SubSurfaceConstructionAssignments_Impl.hpp"

#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"
#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SubSurfaceConstructionAssignments_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SubSurfaceConstructionAssignments::SubSurfaceConstructionAssignments(const Model& model) : ResourceObject(SubSurfaceConstructionAssignments::iddObjectType(), model) {}

  SubSurfaceConstructionAssignments::SubSurfaceConstructionAssignments(std::shared_ptr<detail::SubSurfaceConstructionAssignments_Impl> impl) : ResourceObject(std::move(impl)) {}

  IddObjectType SubSurfaceConstructionAssignments::iddObjectType() {
    return IddObjectType::SubSurfaceConstructionAssignments;
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::fixedWindowConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->fixedWindowConstruction();
  }

  bool SubSurfaceConstructionAssignments::setFixedWindowConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setFixedWindowConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetFixedWindowConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetFixedWindowConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::operableWindowConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->operableWindowConstruction();
  }

  bool SubSurfaceConstructionAssignments::setOperableWindowConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setOperableWindowConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetOperableWindowConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetOperableWindowConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::doorConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->doorConstruction();
  }

  bool SubSurfaceConstructionAssignments::setDoorConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setDoorConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetDoorConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetDoorConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::glassDoorConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->glassDoorConstruction();
  }

  bool SubSurfaceConstructionAssignments::setGlassDoorConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setGlassDoorConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetGlassDoorConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetGlassDoorConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::overheadDoorConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->overheadDoorConstruction();
  }

  bool SubSurfaceConstructionAssignments::setOverheadDoorConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setOverheadDoorConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetOverheadDoorConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetOverheadDoorConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::skylightConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->skylightConstruction();
  }

  bool SubSurfaceConstructionAssignments::setSkylightConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setSkylightConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetSkylightConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetSkylightConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::tubularDaylightDomeConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->tubularDaylightDomeConstruction();
  }

  bool SubSurfaceConstructionAssignments::setTubularDaylightDomeConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setTubularDaylightDomeConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetTubularDaylightDomeConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetTubularDaylightDomeConstruction();
  }

  boost::optional<ConstructionBase> SubSurfaceConstructionAssignments::tubularDaylightDiffuserConstruction() const {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->tubularDaylightDiffuserConstruction();
  }

  bool SubSurfaceConstructionAssignments::setTubularDaylightDiffuserConstruction(const ConstructionBase& construction) {
    return getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->setTubularDaylightDiffuserConstruction(construction);
  }

  void SubSurfaceConstructionAssignments::resetTubularDaylightDiffuserConstruction() {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->resetTubularDaylightDiffuserConstruction();
  }

  void SubSurfaceConstructionAssignments::merge(const SubSurfaceConstructionAssignments& other) {
    getImpl<detail::SubSurfaceConstructionAssignments_Impl>()->merge(other);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::fixedWindowConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::FixedWindowConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setFixedWindowConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::FixedWindowConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetFixedWindowConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::FixedWindowConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::operableWindowConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::OperableWindowConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setOperableWindowConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::OperableWindowConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetOperableWindowConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::OperableWindowConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::doorConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::DoorConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setDoorConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::DoorConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetDoorConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::DoorConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::glassDoorConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::GlassDoorConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setGlassDoorConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::GlassDoorConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetGlassDoorConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::GlassDoorConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::overheadDoorConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::OverheadDoorConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setOverheadDoorConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::OverheadDoorConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetOverheadDoorConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::OverheadDoorConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::skylightConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::SkylightConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setSkylightConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::SkylightConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetSkylightConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::SkylightConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::tubularDaylightDomeConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDomeConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setTubularDaylightDomeConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDomeConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetTubularDaylightDomeConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDomeConstructionName, ""));
    }

    boost::optional<ConstructionBase> SubSurfaceConstructionAssignments_Impl::tubularDaylightDiffuserConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDiffuserConstructionName);
    }

    bool SubSurfaceConstructionAssignments_Impl::setTubularDaylightDiffuserConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDiffuserConstructionName, construction.handle());
    }

    void SubSurfaceConstructionAssignments_Impl::resetTubularDaylightDiffuserConstruction() {
      OS_ASSERT(setString(openstudio::SubSurfaceConstructionAssignmentsFields::TubularDaylightDiffuserConstructionName, ""));
    }

    void SubSurfaceConstructionAssignments_Impl::merge(const SubSurfaceConstructionAssignments& other) {
      if (!fixedWindowConstruction()) {
        if (auto construction = other.fixedWindowConstruction()) {
          setFixedWindowConstruction(*construction);
        }
      }

      if (!operableWindowConstruction()) {
        if (auto construction = other.operableWindowConstruction()) {
          setOperableWindowConstruction(*construction);
        }
      }

      if (!doorConstruction()) {
        if (auto construction = other.doorConstruction()) {
          setDoorConstruction(*construction);
        }
      }

      if (!glassDoorConstruction()) {
        if (auto construction = other.glassDoorConstruction()) {
          setGlassDoorConstruction(*construction);
        }
      }

      if (!overheadDoorConstruction()) {
        if (auto construction = other.overheadDoorConstruction()) {
          setOverheadDoorConstruction(*construction);
        }
      }

      if (!skylightConstruction()) {
        if (auto construction = other.skylightConstruction()) {
          setSkylightConstruction(*construction);
        }
      }

      if (!tubularDaylightDomeConstruction()) {
        if (auto construction = other.tubularDaylightDomeConstruction()) {
          setTubularDaylightDomeConstruction(*construction);
        }
      }

      if (!tubularDaylightDiffuserConstruction()) {
        if (auto construction = other.tubularDaylightDiffuserConstruction()) {
          setTubularDaylightDiffuserConstruction(*construction);
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
