/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Splitter/AirLoopHVACSupplyPlenum.hpp"
#include "Splitter/AirLoopHVACSupplyPlenum_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Mixer/AirLoopHVACReturnPlenum.hpp"
#include "Mixer/AirLoopHVACReturnPlenum_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/AirLoopHVACSupplyPath.hpp"
#include "ModelObject/AirLoopHVACSupplyPath_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_SupplyPlenum_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>

namespace openstudio {
namespace epmodel {

  AirLoopHVACSupplyPlenum::AirLoopHVACSupplyPlenum(const Model& model) : Splitter(AirLoopHVACSupplyPlenum::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::AirLoopHVACSupplyPlenum_Impl>());
  }

  AirLoopHVACSupplyPlenum::AirLoopHVACSupplyPlenum(std::shared_ptr<detail::AirLoopHVACSupplyPlenum_Impl> impl) : Splitter(std::move(impl)) {}

  IddObjectType AirLoopHVACSupplyPlenum::iddObjectType() {
    return IddObjectType::AirLoopHVAC_SupplyPlenum;
  }

  boost::optional<ThermalZone> AirLoopHVACSupplyPlenum::thermalZone() const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->thermalZone();
  }

  bool AirLoopHVACSupplyPlenum::setThermalZone(const ThermalZone& thermalZone) {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->setThermalZone(thermalZone);
  }

  void AirLoopHVACSupplyPlenum::resetThermalZone() {
    getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->resetThermalZone();
  }

  bool AirLoopHVACSupplyPlenum::addToNode(Node& node) {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->addToNode(node);
  }

  unsigned AirLoopHVACSupplyPlenum::inletPort() const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->inletPort();
  }

  unsigned AirLoopHVACSupplyPlenum::outletPort(unsigned branchIndex) const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->outletPort(branchIndex);
  }

  unsigned AirLoopHVACSupplyPlenum::nextOutletPort() const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->nextOutletPort();
  }

  std::vector<ModelObject> AirLoopHVACSupplyPlenum::outletModelObjects() const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->outletModelObjects();
  }

  unsigned AirLoopHVACSupplyPlenum::nextBranchIndex() const {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->nextBranchIndex();
  }

  void AirLoopHVACSupplyPlenum::removePortForBranch(unsigned branchIndex) {
    getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->removePortForBranch(branchIndex);
  }

  bool AirLoopHVACSupplyPlenum::setInletModelObject(const ModelObject& modelObject) {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->setInletModelObject(modelObject);
  }

  bool AirLoopHVACSupplyPlenum::setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) {
    return getImpl<detail::AirLoopHVACSupplyPlenum_Impl>()->setOutletModelObject(branchIndex, modelObject);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<openstudio::epmodel::ThermalZone> AirLoopHVACSupplyPlenum_Impl::thermalZone() const {
      return getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>().getModelObjectTarget<openstudio::epmodel::ThermalZone>(
        openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneName);
    }

    bool AirLoopHVACSupplyPlenum_Impl::setThermalZone(const openstudio::epmodel::ThermalZone& thermalZone) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>();
      if (thermalZone.model() != plenum.model()) {
        return false;
      }
      if (!thermalZone.equipment().empty() || thermalZone.airLoopHVAC()) {
        return false;
      }
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACSupplyPlenum>()) {
        if (candidate == plenum) {
          continue;
        }
        const auto candidateZone = candidate.thermalZone();
        if (candidateZone && (*candidateZone == thermalZone)) {
          return false;
        }
      }
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACReturnPlenum>()) {
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
      const auto oldZoneNode = plenum.getModelObjectTarget<openstudio::epmodel::Node>(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName);
      if (!setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneName, thermalZone.handle(), false)) {
        return false;
      }
      if (!setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName, zoneNode->handle(), false)) {
        setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneName, oldZone ? oldZone->handle() : Handle(), false);
        setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName, oldZoneNode ? oldZoneNode->handle() : Handle(), false);
        return false;
      }

      thermalZoneImpl->clearConditioningForPlenum();
      return true;
    }

    void AirLoopHVACSupplyPlenum_Impl::resetThermalZone() {
      setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneName, Handle(), false);
      setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::ZoneNodeName, Handle(), false);
    }

    bool AirLoopHVACSupplyPlenum_Impl::addToNode(openstudio::epmodel::Node& node) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>();
      const auto currentOutlets = outletModelObjects();
      if ((node.model() != plenum.model()) || !thermalZone()
          || (std::ranges::find(currentOutlets, node.cast<openstudio::epmodel::ModelObject>()) != currentOutlets.end())) {
        return false;
      }

      boost::optional<openstudio::epmodel::AirLoopHVACZoneSplitter> zoneSplitter;
      boost::optional<unsigned> branchIndex;
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACZoneSplitter>()) {
        const auto outlets = candidate.outletModelObjects();
        const auto outlet = std::ranges::find(outlets, node.cast<openstudio::epmodel::ModelObject>());
        if (outlet != outlets.end()) {
          zoneSplitter = candidate;
          branchIndex = static_cast<unsigned>(std::distance(outlets.begin(), outlet));
          break;
        }
      }
      if (!(zoneSplitter && branchIndex)) {
        return false;
      }

      const auto airLoop = zoneSplitter->airLoopHVAC();
      if (!airLoop) {
        return false;
      }

      boost::optional<openstudio::epmodel::AirLoopHVACSupplyPath> supplyPath;
      for (const auto& candidate : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACSupplyPath>()) {
        const auto candidateLoop = candidate.airLoopHVAC();
        if (candidateLoop && (*candidateLoop == *airLoop)) {
          supplyPath = candidate;
          break;
        }
      }
      if (!supplyPath) {
        return false;
      }

      if (const auto currentInlet = inletModelObject()) {
        const auto splitterOutlets = zoneSplitter->outletModelObjects();
        if (std::ranges::find(splitterOutlets, *currentInlet) == splitterOutlets.end()) {
          return false;
        }
        const auto outletIndex = nextBranchIndex();
        if (!setOutletModelObject(outletIndex, node)) {
          return false;
        }
        zoneSplitter->removePortForBranch(*branchIndex);
        return true;
      }

      if (!currentOutlets.empty()) {
        return false;
      }

      openstudio::epmodel::Node inlet(model());
      inlet.setName(plenum.nameString() + " Inlet Node");
      if (!setInletModelObject(inlet)) {
        inlet.remove();
        return false;
      }
      if (!setOutletModelObject(0u, node)) {
        setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName, Handle(), false);
        inlet.remove();
        return false;
      }
      if (!zoneSplitter->setOutletModelObject(*branchIndex, inlet)) {
        removePortForBranch(0u);
        setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName, Handle(), false);
        inlet.remove();
        return false;
      }
      auto supplyPathImpl = supplyPath->getImpl<openstudio::epmodel::detail::AirLoopHVACSupplyPath_Impl>();
      OS_ASSERT(supplyPathImpl);
      if (!supplyPathImpl->addComponent(plenum)) {
        zoneSplitter->setOutletModelObject(*branchIndex, node);
        removePortForBranch(0u);
        setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName, Handle(), false);
        inlet.remove();
        return false;
      }
      return true;
    }

    unsigned AirLoopHVACSupplyPlenum_Impl::inletPort() const {
      return static_cast<unsigned>(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName);
    }

    unsigned AirLoopHVACSupplyPlenum_Impl::outletPort(unsigned branchIndex) const {
      return getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>().numNonextensibleFields() + branchIndex;
    }

    void AirLoopHVACSupplyPlenum_Impl::removePortForBranch(unsigned branchIndex) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>();
      if (branchIndex < plenum.extensibleGroups().size()) {
        plenum.eraseExtensibleGroup(branchIndex);
      }
    }

    bool AirLoopHVACSupplyPlenum_Impl::setInletModelObject(const openstudio::epmodel::ModelObject& modelObject) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>();
      if (modelObject.model() != plenum.model()) {
        return false;
      }
      return setPointer(openstudio::AirLoopHVAC_SupplyPlenumFields::InletNodeName, modelObject.handle(), false);
    }

    bool AirLoopHVACSupplyPlenum_Impl::setOutletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) {
      auto plenum = getObject<openstudio::epmodel::AirLoopHVACSupplyPlenum>();
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
      return workspaceGroup->setPointer(openstudio::AirLoopHVAC_SupplyPlenumExtensibleFields::OutletNodeName, modelObject.handle(), false);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
