/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ResourceObject/ConstructionAssignmentSet.hpp"
#include "ResourceObject/ConstructionAssignmentSet_Impl.hpp"

#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"
#include "Model.hpp"
#include "ResourceObject/SubSurfaceConstructionAssignments.hpp"
#include "ResourceObject/SubSurfaceConstructionAssignments_Impl.hpp"
#include "ResourceObject/SurfaceConstructionAssignments.hpp"
#include "ResourceObject/SurfaceConstructionAssignments_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ConstructionAssignmentSet_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ConstructionAssignmentSet::ConstructionAssignmentSet(const Model& model) : ResourceObject(ConstructionAssignmentSet::iddObjectType(), model) {}

  ConstructionAssignmentSet::ConstructionAssignmentSet(std::shared_ptr<detail::ConstructionAssignmentSet_Impl> impl)
    : ResourceObject(std::move(impl)) {}

  IddObjectType ConstructionAssignmentSet::iddObjectType() {
    return IddObjectType::ConstructionAssignmentSet;
  }

  boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet::exteriorSurfaceConstructionAssignments() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->exteriorSurfaceConstructionAssignments();
  }

  bool ConstructionAssignmentSet::setExteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setExteriorSurfaceConstructionAssignments(surfaceConstructionAssignments);
  }

  void ConstructionAssignmentSet::resetExteriorSurfaceConstructionAssignments() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetExteriorSurfaceConstructionAssignments();
  }

  boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet::interiorSurfaceConstructionAssignments() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->interiorSurfaceConstructionAssignments();
  }

  bool ConstructionAssignmentSet::setInteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setInteriorSurfaceConstructionAssignments(surfaceConstructionAssignments);
  }

  void ConstructionAssignmentSet::resetInteriorSurfaceConstructionAssignments() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetInteriorSurfaceConstructionAssignments();
  }

  boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet::groundContactSurfaceConstructionAssignments() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->groundContactSurfaceConstructionAssignments();
  }

  bool
    ConstructionAssignmentSet::setGroundContactSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setGroundContactSurfaceConstructionAssignments(surfaceConstructionAssignments);
  }

  void ConstructionAssignmentSet::resetGroundContactSurfaceConstructionAssignments() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetGroundContactSurfaceConstructionAssignments();
  }

  boost::optional<SubSurfaceConstructionAssignments> ConstructionAssignmentSet::exteriorSubSurfaceConstructionAssignments() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->exteriorSubSurfaceConstructionAssignments();
  }

  bool ConstructionAssignmentSet::setExteriorSubSurfaceConstructionAssignments(
    const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setExteriorSubSurfaceConstructionAssignments(subSurfaceConstructionAssignments);
  }

  void ConstructionAssignmentSet::resetExteriorSubSurfaceConstructionAssignments() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetExteriorSubSurfaceConstructionAssignments();
  }

  boost::optional<SubSurfaceConstructionAssignments> ConstructionAssignmentSet::interiorSubSurfaceConstructionAssignments() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->interiorSubSurfaceConstructionAssignments();
  }

  bool ConstructionAssignmentSet::setInteriorSubSurfaceConstructionAssignments(
    const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setInteriorSubSurfaceConstructionAssignments(subSurfaceConstructionAssignments);
  }

  void ConstructionAssignmentSet::resetInteriorSubSurfaceConstructionAssignments() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetInteriorSubSurfaceConstructionAssignments();
  }

  boost::optional<ConstructionBase> ConstructionAssignmentSet::interiorPartitionConstruction() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->interiorPartitionConstruction();
  }

  bool ConstructionAssignmentSet::setInteriorPartitionConstruction(const ConstructionBase& construction) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setInteriorPartitionConstruction(construction);
  }

  void ConstructionAssignmentSet::resetInteriorPartitionConstruction() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetInteriorPartitionConstruction();
  }

  boost::optional<ConstructionBase> ConstructionAssignmentSet::adiabaticSurfaceConstruction() const {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->adiabaticSurfaceConstruction();
  }

  bool ConstructionAssignmentSet::setAdiabaticSurfaceConstruction(const ConstructionBase& construction) {
    return getImpl<detail::ConstructionAssignmentSet_Impl>()->setAdiabaticSurfaceConstruction(construction);
  }

  void ConstructionAssignmentSet::resetAdiabaticSurfaceConstruction() {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->resetAdiabaticSurfaceConstruction();
  }

  void ConstructionAssignmentSet::merge(const ConstructionAssignmentSet& other) {
    getImpl<detail::ConstructionAssignmentSet_Impl>()->merge(other);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet_Impl::exteriorSurfaceConstructionAssignments() const {
      return getObject<ModelObject>().getModelObjectTarget<SurfaceConstructionAssignments>(
        openstudio::ConstructionAssignmentSetFields::ExteriorSurfaceConstructionAssignmentsName);
    }

    bool ConstructionAssignmentSet_Impl::setExteriorSurfaceConstructionAssignments(
      const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::ExteriorSurfaceConstructionAssignmentsName,
                        surfaceConstructionAssignments.handle());
    }

    void ConstructionAssignmentSet_Impl::resetExteriorSurfaceConstructionAssignments() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::ExteriorSurfaceConstructionAssignmentsName, ""));
    }

    boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet_Impl::interiorSurfaceConstructionAssignments() const {
      return getObject<ModelObject>().getModelObjectTarget<SurfaceConstructionAssignments>(
        openstudio::ConstructionAssignmentSetFields::InteriorSurfaceConstructionAssignmentsName);
    }

    bool ConstructionAssignmentSet_Impl::setInteriorSurfaceConstructionAssignments(
      const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::InteriorSurfaceConstructionAssignmentsName,
                        surfaceConstructionAssignments.handle());
    }

    void ConstructionAssignmentSet_Impl::resetInteriorSurfaceConstructionAssignments() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::InteriorSurfaceConstructionAssignmentsName, ""));
    }

    boost::optional<SurfaceConstructionAssignments> ConstructionAssignmentSet_Impl::groundContactSurfaceConstructionAssignments() const {
      return getObject<ModelObject>().getModelObjectTarget<SurfaceConstructionAssignments>(
        openstudio::ConstructionAssignmentSetFields::GroundContactSurfaceConstructionAssignmentsName);
    }

    bool ConstructionAssignmentSet_Impl::setGroundContactSurfaceConstructionAssignments(
      const SurfaceConstructionAssignments& surfaceConstructionAssignments) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::GroundContactSurfaceConstructionAssignmentsName,
                        surfaceConstructionAssignments.handle());
    }

    void ConstructionAssignmentSet_Impl::resetGroundContactSurfaceConstructionAssignments() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::GroundContactSurfaceConstructionAssignmentsName, ""));
    }

    boost::optional<SubSurfaceConstructionAssignments> ConstructionAssignmentSet_Impl::exteriorSubSurfaceConstructionAssignments() const {
      return getObject<ModelObject>().getModelObjectTarget<SubSurfaceConstructionAssignments>(
        openstudio::ConstructionAssignmentSetFields::ExteriorSubSurfaceConstructionAssignmentsName);
    }

    bool ConstructionAssignmentSet_Impl::setExteriorSubSurfaceConstructionAssignments(
      const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::ExteriorSubSurfaceConstructionAssignmentsName,
                        subSurfaceConstructionAssignments.handle());
    }

    void ConstructionAssignmentSet_Impl::resetExteriorSubSurfaceConstructionAssignments() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::ExteriorSubSurfaceConstructionAssignmentsName, ""));
    }

    boost::optional<SubSurfaceConstructionAssignments> ConstructionAssignmentSet_Impl::interiorSubSurfaceConstructionAssignments() const {
      return getObject<ModelObject>().getModelObjectTarget<SubSurfaceConstructionAssignments>(
        openstudio::ConstructionAssignmentSetFields::InteriorSubSurfaceConstructionAssignmentsName);
    }

    bool ConstructionAssignmentSet_Impl::setInteriorSubSurfaceConstructionAssignments(
      const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::InteriorSubSurfaceConstructionAssignmentsName,
                        subSurfaceConstructionAssignments.handle());
    }

    void ConstructionAssignmentSet_Impl::resetInteriorSubSurfaceConstructionAssignments() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::InteriorSubSurfaceConstructionAssignmentsName, ""));
    }

    boost::optional<ConstructionBase> ConstructionAssignmentSet_Impl::interiorPartitionConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(
        openstudio::ConstructionAssignmentSetFields::InteriorPartitionConstructionName);
    }

    bool ConstructionAssignmentSet_Impl::setInteriorPartitionConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::InteriorPartitionConstructionName, construction.handle());
    }

    void ConstructionAssignmentSet_Impl::resetInteriorPartitionConstruction() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::InteriorPartitionConstructionName, ""));
    }

    boost::optional<ConstructionBase> ConstructionAssignmentSet_Impl::adiabaticSurfaceConstruction() const {
      return getObject<ModelObject>().getModelObjectTarget<ConstructionBase>(
        openstudio::ConstructionAssignmentSetFields::AdiabaticSurfaceConstructionName);
    }

    bool ConstructionAssignmentSet_Impl::setAdiabaticSurfaceConstruction(const ConstructionBase& construction) {
      return setPointer(openstudio::ConstructionAssignmentSetFields::AdiabaticSurfaceConstructionName, construction.handle());
    }

    void ConstructionAssignmentSet_Impl::resetAdiabaticSurfaceConstruction() {
      OS_ASSERT(setString(openstudio::ConstructionAssignmentSetFields::AdiabaticSurfaceConstructionName, ""));
    }

    void ConstructionAssignmentSet_Impl::merge(const ConstructionAssignmentSet& other) {
      boost::optional<SurfaceConstructionAssignments> thisSurfaceConstructions;
      boost::optional<SurfaceConstructionAssignments> otherSurfaceConstructions;
      boost::optional<SubSurfaceConstructionAssignments> thisSubSurfaceConstructions;
      boost::optional<SubSurfaceConstructionAssignments> otherSubSurfaceConstructions;

      // An assignments object referenced by more than this set is cloned before merging into it, so the other users keep their slots
      otherSurfaceConstructions = other.exteriorSurfaceConstructionAssignments();
      if (otherSurfaceConstructions) {
        thisSurfaceConstructions = exteriorSurfaceConstructionAssignments();
        if (!thisSurfaceConstructions) {
          setExteriorSurfaceConstructionAssignments(*otherSurfaceConstructions);
        } else if (*thisSurfaceConstructions != *otherSurfaceConstructions) {
          if (thisSurfaceConstructions->numSources() > 1) {
            auto clone = model().addObject(thisSurfaceConstructions->idfObject());
            OS_ASSERT(clone);
            thisSurfaceConstructions = clone->cast<SurfaceConstructionAssignments>();
            OS_ASSERT(setExteriorSurfaceConstructionAssignments(*thisSurfaceConstructions));
          }
          thisSurfaceConstructions->merge(*otherSurfaceConstructions);
        }
      }

      otherSurfaceConstructions = other.interiorSurfaceConstructionAssignments();
      if (otherSurfaceConstructions) {
        thisSurfaceConstructions = interiorSurfaceConstructionAssignments();
        if (!thisSurfaceConstructions) {
          setInteriorSurfaceConstructionAssignments(*otherSurfaceConstructions);
        } else if (*thisSurfaceConstructions != *otherSurfaceConstructions) {
          if (thisSurfaceConstructions->numSources() > 1) {
            auto clone = model().addObject(thisSurfaceConstructions->idfObject());
            OS_ASSERT(clone);
            thisSurfaceConstructions = clone->cast<SurfaceConstructionAssignments>();
            OS_ASSERT(setInteriorSurfaceConstructionAssignments(*thisSurfaceConstructions));
          }
          thisSurfaceConstructions->merge(*otherSurfaceConstructions);
        }
      }

      otherSurfaceConstructions = other.groundContactSurfaceConstructionAssignments();
      if (otherSurfaceConstructions) {
        thisSurfaceConstructions = groundContactSurfaceConstructionAssignments();
        if (!thisSurfaceConstructions) {
          setGroundContactSurfaceConstructionAssignments(*otherSurfaceConstructions);
        } else if (*thisSurfaceConstructions != *otherSurfaceConstructions) {
          if (thisSurfaceConstructions->numSources() > 1) {
            auto clone = model().addObject(thisSurfaceConstructions->idfObject());
            OS_ASSERT(clone);
            thisSurfaceConstructions = clone->cast<SurfaceConstructionAssignments>();
            OS_ASSERT(setGroundContactSurfaceConstructionAssignments(*thisSurfaceConstructions));
          }
          thisSurfaceConstructions->merge(*otherSurfaceConstructions);
        }
      }

      otherSubSurfaceConstructions = other.exteriorSubSurfaceConstructionAssignments();
      if (otherSubSurfaceConstructions) {
        thisSubSurfaceConstructions = exteriorSubSurfaceConstructionAssignments();
        if (!thisSubSurfaceConstructions) {
          setExteriorSubSurfaceConstructionAssignments(*otherSubSurfaceConstructions);
        } else if (*thisSubSurfaceConstructions != *otherSubSurfaceConstructions) {
          if (thisSubSurfaceConstructions->numSources() > 1) {
            auto clone = model().addObject(thisSubSurfaceConstructions->idfObject());
            OS_ASSERT(clone);
            thisSubSurfaceConstructions = clone->cast<SubSurfaceConstructionAssignments>();
            OS_ASSERT(setExteriorSubSurfaceConstructionAssignments(*thisSubSurfaceConstructions));
          }
          thisSubSurfaceConstructions->merge(*otherSubSurfaceConstructions);
        }
      }

      otherSubSurfaceConstructions = other.interiorSubSurfaceConstructionAssignments();
      if (otherSubSurfaceConstructions) {
        thisSubSurfaceConstructions = interiorSubSurfaceConstructionAssignments();
        if (!thisSubSurfaceConstructions) {
          setInteriorSubSurfaceConstructionAssignments(*otherSubSurfaceConstructions);
        } else if (*thisSubSurfaceConstructions != *otherSubSurfaceConstructions) {
          if (thisSubSurfaceConstructions->numSources() > 1) {
            auto clone = model().addObject(thisSubSurfaceConstructions->idfObject());
            OS_ASSERT(clone);
            thisSubSurfaceConstructions = clone->cast<SubSurfaceConstructionAssignments>();
            OS_ASSERT(setInteriorSubSurfaceConstructionAssignments(*thisSubSurfaceConstructions));
          }
          thisSubSurfaceConstructions->merge(*otherSubSurfaceConstructions);
        }
      }

      if (!interiorPartitionConstruction()) {
        if (auto construction = other.interiorPartitionConstruction()) {
          setInteriorPartitionConstruction(*construction);
        }
      }

      if (!adiabaticSurfaceConstruction()) {
        if (auto construction = other.adiabaticSurfaceConstruction()) {
          setAdiabaticSurfaceConstruction(*construction);
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
