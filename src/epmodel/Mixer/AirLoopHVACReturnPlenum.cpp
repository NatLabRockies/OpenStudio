/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Mixer/AirLoopHVACReturnPlenum.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/AirLoopHVACReturnPath.hpp"
#include "ModelObject/AirLoopHVACReturnPath_Impl.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_ReturnPlenum_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(const Model& model) : Mixer(AirLoopHVACReturnPlenum::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirLoopHVACReturnPlenum_Impl>());
  }

  AirLoopHVACReturnPlenum::AirLoopHVACReturnPlenum(std::shared_ptr<detail::AirLoopHVACReturnPlenum_Impl> impl) : Mixer(std::move(impl)) {}

  IddObjectType AirLoopHVACReturnPlenum::iddObjectType() {
    return IddObjectType::AirLoopHVAC_ReturnPlenum;
  }

  boost::optional<ThermalZone> AirLoopHVACReturnPlenum::thermalZone() const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->thermalZone();
  }

  bool AirLoopHVACReturnPlenum::setThermalZone(const ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->setThermalZone(thermalZone);
  }

  void AirLoopHVACReturnPlenum::resetThermalZone() {
    getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->resetThermalZone();
  }

  bool AirLoopHVACReturnPlenum::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->addToNode(node);
  }

  unsigned AirLoopHVACReturnPlenum::outletPort() const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->outletPort();
  }

  unsigned AirLoopHVACReturnPlenum::inletPort(unsigned branchIndex) const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->inletPort(branchIndex);
  }

  unsigned AirLoopHVACReturnPlenum::nextInletPort() const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->nextInletPort();
  }

  std::vector<ModelObject> AirLoopHVACReturnPlenum::inletModelObjects() const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->inletModelObjects();
  }

  unsigned AirLoopHVACReturnPlenum::nextBranchIndex() const {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->nextBranchIndex();
  }

  void AirLoopHVACReturnPlenum::removePortForBranch(unsigned branchIndex) {
    getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->removePortForBranch(branchIndex);
  }

  bool AirLoopHVACReturnPlenum::setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    return getImpl<detail::AirLoopHVACReturnPlenum_Impl>()->setInletModelObject(branchIndex, modelObject);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::ThermalZone> AirLoopHVACReturnPlenum_Impl::thermalZone() const {
      return getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneName);
    }

    bool AirLoopHVACReturnPlenum_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      if (!bindThermalZone(thermalZone)) {
        return false;
      }
      clearThermalZoneConditioning();
      return true;
    }

    bool AirLoopHVACReturnPlenum_Impl::bindThermalZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>();
      if (thermalZone.model() != plenum.model()) {
        return false;
      }
      if (!thermalZone.equipment().empty() || thermalZone.airLoopHVAC()) {
        return false;
      }
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACReturnPlenum>()) {
        if (candidate == plenum) {
          continue;
        }
        const auto candidateZone = candidate.thermalZone();
        if (candidateZone && (*candidateZone == thermalZone)) {
          return false;
        }
      }
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACSupplyPlenum>()) {
        const auto candidateZone = candidate.thermalZone();
        if (candidateZone && (*candidateZone == thermalZone)) {
          return false;
        }
      }

      auto thermalZoneImpl = thermalZone.getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
      OS_ASSERT(thermalZoneImpl);
      const auto zoneNode = thermalZoneImpl->plenumZoneNode();
      if (!zoneNode) {
        return false;
      }
      const auto oldZone = this->thermalZone();
      const auto oldZoneNode = plenum.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName);
      if (!setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneName, thermalZone.handle(), false)) {
        return false;
      }
      if (!setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName, zoneNode->handle(), false)) {
        setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneName, oldZone ? oldZone->handle() : Handle(), false);
        setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName, oldZoneNode ? oldZoneNode->handle() : Handle(), false);
        return false;
      }

      return true;
    }

    void AirLoopHVACReturnPlenum_Impl::clearThermalZoneConditioning() {
      if (auto zone = thermalZone()) {
        auto thermalZoneImpl = zone->getImpl<openstudio::epmodel::detail::ThermalZone_Impl>();
        OS_ASSERT(thermalZoneImpl);
        // EPModel is already the EnergyPlus representation, so remove sizing,
        // thermostat, and equipment connections that do not apply to plenums.
        thermalZoneImpl->clearConditioningForPlenum();
      }
    }

    void AirLoopHVACReturnPlenum_Impl::resetThermalZone() {
      setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneName, Handle(), false);
      setPointer(openstudio::AirLoopHVAC_ReturnPlenumFields::ZoneNodeName, Handle(), false);
    }

    bool AirLoopHVACReturnPlenum_Impl::addToNode(openstudio::epmodel::Node& node) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>();
      const auto currentInlets = inletModelObjects();
      if ((node.model() != plenum.model()) || !thermalZone()
          || (std::ranges::find(currentInlets, node.cast<openstudio::epmodel::ModelObject>()) != currentInlets.end())) {
        return false;
      }

      boost::optional<openstudio::epmodel::AirLoopHVACZoneMixer> zoneMixer;
      boost::optional<unsigned> branchIndex;
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACZoneMixer>()) {
        const auto inlets = candidate.inletModelObjects();
        const auto nodeObject = node.cast<openstudio::epmodel::ModelObject>();
        const auto matchCount = std::ranges::count(inlets, nodeObject);
        if (matchCount > 0) {
          if ((matchCount != 1) || zoneMixer) {
            return false;
          }
          const auto inlet = std::ranges::find(inlets, nodeObject);
          zoneMixer = candidate;
          branchIndex = static_cast<unsigned>(std::distance(inlets.begin(), inlet));
        }
      }
      if (!(zoneMixer && branchIndex)) {
        return false;
      }

      const auto airLoop = zoneMixer->airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      boost::optional<openstudio::epmodel::AirLoopHVACReturnPath> returnPath;
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACReturnPath>()) {
        const auto candidateLoop = candidate.airLoopHVAC();
        if (candidateLoop && (*candidateLoop == *airLoop)) {
          returnPath = candidate;
          break;
        }
      }
      if (!returnPath) {
        return false;
      }

      if (auto currentOutlet = outletModelObject()) {
        const auto mixerInlets = zoneMixer->inletModelObjects();
        if (std::ranges::find(mixerInlets, *currentOutlet) == mixerInlets.end()) {
          return false;
        }
        const auto inletIndex = nextBranchIndex();
        if (!setInletModelObject(inletIndex, node)) {
          return false;
        }
        zoneMixer->removePortForBranch(*branchIndex);
        return true;
      }

      if (!inletModelObjects().empty()) {
        return false;
      }

      openstudio::epmodel::Node outlet(model());
      outlet.setName(plenum.nameString() + " Outlet Node");
      if (!setInletModelObject(0u, node)) {
        outlet.remove();
        return false;
      }
      if (!setOutletModelObject(outlet)) {
        removePortForBranch(0u);
        outlet.remove();
        return false;
      }
      if (!zoneMixer->setInletModelObject(*branchIndex, outlet)) {
        resetOutletModelObject();
        removePortForBranch(0u);
        outlet.remove();
        return false;
      }
      if (!returnPath->addComponent(plenum)) {
        zoneMixer->setInletModelObject(*branchIndex, node);
        resetOutletModelObject();
        removePortForBranch(0u);
        outlet.remove();
        return false;
      }
      return true;
    }

    unsigned AirLoopHVACReturnPlenum_Impl::outletPort() const {
      return static_cast<unsigned>(openstudio::AirLoopHVAC_ReturnPlenumFields::OutletNodeName);
    }

    unsigned AirLoopHVACReturnPlenum_Impl::inletPort(unsigned branchIndex) const {
      return getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>().numNonextensibleFields() + branchIndex;
    }

    void AirLoopHVACReturnPlenum_Impl::removePortForBranch(unsigned branchIndex) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>();
      if (branchIndex < plenum.extensibleGroups().size()) {
        plenum.eraseExtensibleGroup(branchIndex);
      }
    }

    bool AirLoopHVACReturnPlenum_Impl::setInletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACReturnPlenum>();
      if (modelObject.model() != plenum.model()) {
        return false;
      }

      while (plenum.extensibleGroups().size() <= branchIndex) {
        plenum.pushExtensibleGroup();
      }
      const auto groups = plenum.extensibleGroups();
      auto workspaceGroup = groups[branchIndex].optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        return false;
      }
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_ReturnPlenumExtensibleFields::InletNodeName, modelObject.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
