/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Space.hpp"
#include "Space_Impl.hpp"

#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "DesignSpecificationOutdoorAirSpaceList.hpp"
#include "DesignSpecificationOutdoorAirSpaceList_Impl.hpp"
#include "SizingZone.hpp"
#include "SizingZone_Impl.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
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

      boost::optional<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList> findListContainingSpace(
        const openstudio::epmodel::Model& model, const openstudio::epmodel::Space& space) {
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
        if (auto existing = model.getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
          return *existing;
        }
        auto created = openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList(model);
        created.setName(orphanDSOASpaceListName);
        return created;
      }

      openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList
        getOrCreateZoneSpaceList(const openstudio::epmodel::ThermalZone& zone) {
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
      for (const auto& [list, dsoa] : assignments) {
        if (list.handle() == canonicalList.handle()) {
          canonicalDSOA = dsoa;
          break;
        }
      }

      OS_ASSERT(canonicalList.getImpl<openstudio::epmodel::detail::DesignSpecificationOutdoorAirSpaceList_Impl>()
                  ->setDesignSpecificationOutdoorAir(thisSpace, canonicalDSOA));
      removeSpaceFromAllListsExcept(thisSpace, canonicalList.handle());

      if (assignments.size() > 1u) {
        detail::addLoadInfo(context, "Normalized duplicate DSOA assignments for Space '" + thisSpace.nameString()
                                       + "' into DesignSpecification:OutdoorAir:SpaceList '" + canonicalList.nameString() + "'.");
      }

      if (auto orphanList = model().getConcreteModelObjectByName<openstudio::epmodel::DesignSpecificationOutdoorAirSpaceList>(orphanDSOASpaceListName)) {
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
