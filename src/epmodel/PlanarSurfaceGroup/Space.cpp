/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PlanarSurfaceGroup/Space.hpp"
#include "PlanarSurfaceGroup/Space_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir.hpp"
#include "ResourceObject/DesignSpecificationOutdoorAir_Impl.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList.hpp"
#include "ModelObject/DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Sizing_Zone_FieldEnums.hxx>
#include <utilities/idd/Space_FieldEnums.hxx>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  Space::Space(const Model& model) : ModelObject(Space::iddObjectType(), model) {
    auto impl = getImpl<detail::Space_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
  }

  Space::Space(std::shared_ptr<detail::Space_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Space::iddObjectType() {
    return IddObjectType::Space;
  }

  double Space::ceilingHeight() const {
    return getImpl<detail::Space_Impl>()->ceilingHeight();
  }

  bool Space::isCeilingHeightDefaulted() const {
    return getImpl<detail::Space_Impl>()->isCeilingHeightDefaulted();
  }

  bool Space::isCeilingHeightAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isCeilingHeightAutocalculated();
  }

  bool Space::setCeilingHeight(double ceilingHeight) {
    return getImpl<detail::Space_Impl>()->setCeilingHeight(ceilingHeight);
  }

  void Space::autocalculateCeilingHeight() {
    getImpl<detail::Space_Impl>()->autocalculateCeilingHeight();
  }

  void Space::resetCeilingHeight() {
    getImpl<detail::Space_Impl>()->resetCeilingHeight();
  }

  double Space::volume() const {
    return getImpl<detail::Space_Impl>()->volume();
  }

  bool Space::isVolumeDefaulted() const {
    return getImpl<detail::Space_Impl>()->isVolumeDefaulted();
  }

  bool Space::isVolumeAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isVolumeAutocalculated();
  }

  bool Space::setVolume(double volume) {
    return getImpl<detail::Space_Impl>()->setVolume(volume);
  }

  void Space::autocalculateVolume() {
    getImpl<detail::Space_Impl>()->autocalculateVolume();
  }

  void Space::resetVolume() {
    getImpl<detail::Space_Impl>()->resetVolume();
  }

  double Space::floorArea() const {
    return getImpl<detail::Space_Impl>()->floorArea();
  }

  bool Space::isFloorAreaDefaulted() const {
    return getImpl<detail::Space_Impl>()->isFloorAreaDefaulted();
  }

  bool Space::isFloorAreaAutocalculated() const {
    return getImpl<detail::Space_Impl>()->isFloorAreaAutocalculated();
  }

  bool Space::setFloorArea(double floorArea) {
    return getImpl<detail::Space_Impl>()->setFloorArea(floorArea);
  }

  void Space::autocalculateFloorArea() {
    getImpl<detail::Space_Impl>()->autocalculateFloorArea();
  }

  void Space::resetFloorArea() {
    getImpl<detail::Space_Impl>()->resetFloorArea();
  }

  boost::optional<ThermalZone> Space::thermalZone() const {
    return getImpl<detail::Space_Impl>()->thermalZone();
  }

  bool Space::setThermalZone(const ThermalZone& thermalZone) {
    return getImpl<detail::Space_Impl>()->setThermalZone(thermalZone);
  }

  void Space::resetThermalZone() {
    return getImpl<detail::Space_Impl>()->resetThermalZone();
  }

  boost::optional<DesignSpecificationOutdoorAir> Space::designSpecificationOutdoorAir() const {
    return getImpl<detail::Space_Impl>()->designSpecificationOutdoorAir();
  }

  bool Space::setDesignSpecificationOutdoorAir(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
    return getImpl<detail::Space_Impl>()->setDesignSpecificationOutdoorAir(designSpecificationOutdoorAir);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      constexpr const char* orphanDSOASpaceListName = "Orphan Spaces DSOA Space List";

      void syncAllAirLoopCMVEntries(const openstudio::epmodel::Model& model) {
        for (const auto& airLoop : model.getConcreteModelObjects<openstudio::epmodel::AirLoopHVAC>()) {
          airLoop.getImpl<openstudio::epmodel::detail::AirLoopHVAC_Impl>()->syncControllerMechanicalVentilationZoneOutdoorAirEntries();
        }
      }

      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> findListContainingSpace(const openstudio::epmodel::Model& model,
                                                                                                           const openstudio::epmodel::Space& space) {
        boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> result;
        for (const auto& list : model.getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
          if (list.designSpecificationOutdoorAir(space)) {
            if (result) {
              OS_ASSERT(result->handle() == list.handle());
            }
            result = list;
          }
        }
        return result;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList getOrCreateOrphanSpaceList(const openstudio::epmodel::Model& model) {
        if (auto existing =
              model.getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
          return *existing;
        }
        auto created = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(model);
        created.setName(orphanDSOASpaceListName);
        return created;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList getOrCreateZoneSpaceList(const openstudio::epmodel::ThermalZone& zone) {
        auto sizingZone = zone.sizingZone();
        auto sizingZoneImpl = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>();
        OS_ASSERT(sizingZoneImpl);
        auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList();
        if (dsoaSpaceList) {
          return *dsoaSpaceList;
        }

        auto created = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(zone.model());
        created.setName(zone.nameString() + " DSOA Space List");
        OS_ASSERT(sizingZoneImpl->setDesignSpecificationOutdoorAirSpaceList(created));
        return created;
      }

      void removeSpaceFromAllListsExcept(const openstudio::epmodel::Space& space, openstudio::Handle keepListHandle) {
        for (const auto& list : space.model().getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
          if (list.handle() == keepListHandle) {
            continue;
          }
          list.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->removeSpace(space);
        }
      }

    }  // namespace

    double Space_Impl::ceilingHeight() const {
      auto value = getDouble(openstudio::SpaceFields::CeilingHeight, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Space_Impl::isCeilingHeightDefaulted() const {
      return isEmpty(openstudio::SpaceFields::CeilingHeight);
    }

    bool Space_Impl::isCeilingHeightAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::CeilingHeight, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    double Space_Impl::volume() const {
      auto value = getDouble(openstudio::SpaceFields::Volume, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Space_Impl::isVolumeDefaulted() const {
      return isEmpty(openstudio::SpaceFields::Volume);
    }

    bool Space_Impl::isVolumeAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::Volume, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    double Space_Impl::floorArea() const {
      auto value = getDouble(openstudio::SpaceFields::FloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool Space_Impl::isFloorAreaDefaulted() const {
      return isEmpty(openstudio::SpaceFields::FloorArea);
    }

    bool Space_Impl::isFloorAreaAutocalculated() const {
      if (auto value = getString(openstudio::SpaceFields::FloorArea, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool Space_Impl::setCeilingHeight(double ceilingHeight) {
      const bool result = setDouble(openstudio::SpaceFields::CeilingHeight, ceilingHeight);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateCeilingHeight() {
      OS_ASSERT(setString(openstudio::SpaceFields::CeilingHeight, "autocalculate"));
    }

    void Space_Impl::resetCeilingHeight() {
      OS_ASSERT(setString(openstudio::SpaceFields::CeilingHeight, ""));
    }

    bool Space_Impl::setVolume(double volume) {
      const bool result = setDouble(openstudio::SpaceFields::Volume, volume);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateVolume() {
      OS_ASSERT(setString(openstudio::SpaceFields::Volume, "autocalculate"));
    }

    void Space_Impl::resetVolume() {
      OS_ASSERT(setString(openstudio::SpaceFields::Volume, ""));
    }

    bool Space_Impl::setFloorArea(double floorArea) {
      const bool result = setDouble(openstudio::SpaceFields::FloorArea, floorArea);
      OS_ASSERT(result);
      return result;
    }

    void Space_Impl::autocalculateFloorArea() {
      OS_ASSERT(setString(openstudio::SpaceFields::FloorArea, "autocalculate"));
    }

    void Space_Impl::resetFloorArea() {
      OS_ASSERT(setString(openstudio::SpaceFields::FloorArea, ""));
    }

    boost::optional<openstudio::epmodel::ThermalZone> Space_Impl::thermalZone() const {
      return getObject<openstudio::epmodel::Space>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(openstudio::SpaceFields::ZoneName);
    }

    bool Space_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      auto currentDSOA = designSpecificationOutdoorAir();
      if (!setPointer(openstudio::SpaceFields::ZoneName, thermalZone.handle(), false)) {
        return false;
      }
      if (currentDSOA) {
        OS_ASSERT(setDesignSpecificationOutdoorAir(*currentDSOA));
      }
      return true;
    }

    void Space_Impl::resetThermalZone() {
      auto currentDSOA = designSpecificationOutdoorAir();
      OS_ASSERT(setString(openstudio::SpaceFields::ZoneName, ""));
      if (currentDSOA) {
        OS_ASSERT(setDesignSpecificationOutdoorAir(*currentDSOA));
      }
    }

    boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAir> Space_Impl::designSpecificationOutdoorAir() const {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      if (auto zone = thermalZone()) {
        auto sizingZone = zone->sizingZone();
        auto sizingZoneImpl = sizingZone.getImpl<openstudio::epmodel::detail::SizingZone_Impl>();
        OS_ASSERT(sizingZoneImpl);
        if (auto dsoaSpaceList = sizingZoneImpl->designSpecificationOutdoorAirSpaceList()) {
          if (auto dsoa = dsoaSpaceList->designSpecificationOutdoorAir(thisSpace)) {
            return dsoa;
          }
        }
      }
      if (auto list = findListContainingSpace(model(), thisSpace)) {
        return list->designSpecificationOutdoorAir(thisSpace);
      }
      return boost::none;
    }

    bool Space_Impl::setDesignSpecificationOutdoorAir(const openstudio::epmodel::DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      if (designSpecificationOutdoorAir.model() != thisSpace.model()) {
        return false;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList targetList =
        thermalZone() ? getOrCreateZoneSpaceList(*thermalZone()) : getOrCreateOrphanSpaceList(model());
      OS_ASSERT(targetList.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(
        thisSpace, designSpecificationOutdoorAir));

      removeSpaceFromAllListsExcept(thisSpace, targetList.handle());
      syncAllAirLoopCMVEntries(model());
      return true;
    }

    void Space_Impl::doCanonicalize(LoadContext& context) {
      auto thisSpace = getObject<openstudio::epmodel::Space>();
      auto zone = thermalZone();
      if (zone) {
        zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>()->canonicalize(context);
      }

      std::vector<std::pair<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList, openstudio::epmodel::DesignSpecificationOutdoorAir>>
        assignments;
      for (const auto& list : model().getConcreteModelObjects<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>()) {
        if (auto dsoa = list.designSpecificationOutdoorAir(thisSpace)) {
          assignments.emplace_back(list, *dsoa);
        }
      }
      if (assignments.empty()) {
        return;
      }

      std::sort(assignments.begin(), assignments.end(),
                [](const auto& lhs, const auto& rhs) { return lhs.first.nameString() < rhs.first.nameString(); });

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList canonicalList =
        zone ? getOrCreateZoneSpaceList(*zone) : getOrCreateOrphanSpaceList(model());
      auto canonicalDSOA = assignments.front().second;
      bool canonicalListHadAssignment = false;
      for (const auto& [list, dsoa] : assignments) {
        if (list.handle() == canonicalList.handle()) {
          canonicalListHadAssignment = true;
          canonicalDSOA = dsoa;
          break;
        }
      }

      OS_ASSERT(canonicalList.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()->setDesignSpecificationOutdoorAir(
        thisSpace, canonicalDSOA));
      removeSpaceFromAllListsExcept(thisSpace, canonicalList.handle());

      if (assignments.size() > 1u) {
        detail::addLoadInfo(context, "Normalized duplicate DSOA assignments for Space '" + thisSpace.nameString()
                                       + "' into DesignSpecification:OutdoorAir:SpaceList '" + canonicalList.nameString() + "'.");
        bool hasConflictingAssignments = false;
        for (const auto& [_, dsoa] : assignments) {
          if (dsoa.handle() != canonicalDSOA.handle()) {
            hasConflictingAssignments = true;
            break;
          }
        }
        if (hasConflictingAssignments) {
          detail::addLoadWarning(context, "Space '" + thisSpace.nameString()
                                            + "' had conflicting DSOA assignments across lists; canonicalization kept assignment from '"
                                            + canonicalList.nameString() + "'.");
        }
      }

      if (!canonicalListHadAssignment) {
        detail::addLoadInfo(context,
                            "Moved Space '" + thisSpace.nameString() + "' DSOA assignment into canonical list '" + canonicalList.nameString() + "'.");
      }

      if (auto orphanList =
            model().getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
        if (orphanList->numExtensibleGroups() == 0u) {
          orphanList->remove();
          detail::addLoadInfo(context,
                              std::string("Removed empty orphan DesignSpecification:OutdoorAir:SpaceList '") + orphanDSOASpaceListName + "'.");
        }
      }
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
