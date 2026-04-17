/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctInletSideMixer.hpp"
#include "StraightComponent/AirTerminalSingleDuctInletSideMixer_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_Mixer_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(const Model& model)
    : StraightComponent(AirTerminalSingleDuctInletSideMixer::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);
    OS_ASSERT(setPerPersonVentilationRateMode("CurrentOccupancy"));
  }

  AirTerminalSingleDuctInletSideMixer::AirTerminalSingleDuctInletSideMixer(std::shared_ptr<detail::AirTerminalSingleDuctInletSideMixer_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctInletSideMixer::iddObjectType() {
    return IddObjectType::AirTerminal_SingleDuct_Mixer;
  }

  std::vector<std::string> AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode);
  }

  bool AirTerminalSingleDuctInletSideMixer::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->addToNode(node);
  }

  std::string AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateMode() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->perPersonVentilationRateMode();
  }

  bool AirTerminalSingleDuctInletSideMixer::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->setPerPersonVentilationRateMode(perPersonVentilationRateMode);
  }

  unsigned AirTerminalSingleDuctInletSideMixer::secondaryAirInletPort() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->secondaryAirInletPort();
  }

  boost::optional<Node> AirTerminalSingleDuctInletSideMixer::secondaryAirInletNode() const {
    return getImpl<detail::AirTerminalSingleDuctInletSideMixer_Impl>()->secondaryAirInletNode();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    bool AirTerminalSingleDuctInletSideMixer_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a node in the same model as the inlet-side mixer terminal.");
        return false;
      }

      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto thisNode = node.cast<ModelObject>();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::find(splitterOutlets.begin(), splitterOutlets.end(), thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      if (!zoneMixer.inletModelObject(splitterBranchIndex)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }

      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
        if (!thisObject.name()) {
          return false;
        }
      }

      const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
      auto inletNode = model().getOrCreateTransientByName<Node>(inletNodeName);
      if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
        return false;
      }

      if (!setPointer(inletPort(), inletNode.handle(), false)) {
        return false;
      }

      if (!setPointer(outletPort(), node.handle(), false)) {
        return false;
      }

      for (const auto& source : thisObject.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        auto adu = source.optionalCast<ZoneHVACAirDistributionUnit>();
        if (!adu) {
          continue;
        }
        adu->getImpl<detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
        break;
      }

      for (auto& thermalZone : model().getConcreteModelObjects<ThermalZone>()) {
        if (thermalZone.zoneAirNode() != node) {
          continue;
        }

        auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
        OS_ASSERT(zoneImpl);

        auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
        auto equipmentList = zoneImpl->zoneHVACEquipmentList();
        if (!equipmentList) {
          ZoneHVACEquipmentList newEquipmentList(thermalZone.model());
          if (!newEquipmentList.name()) {
            newEquipmentList.createName();
          }
          if (!zoneConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName,
                                          newEquipmentList.handle())) {
            return false;
          }
          equipmentList = newEquipmentList;
        }

        auto equipmentListImpl = equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>();
        OS_ASSERT(equipmentListImpl);
        if (!equipmentListImpl->addEquipment(thisObject)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctInletSideMixer",
                   "addToNode failed to register the inlet-side mixer terminal with the owning thermal zone.");
          return false;
        }
        break;
      }

      return true;
    }

    std::string AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateMode() const {
      const auto value = getString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctInletSideMixer_Impl::setPerPersonVentilationRateMode(const std::string& perPersonVentilationRateMode) {
      return setString(openstudio::AirTerminal_SingleDuct_MixerFields::PerPersonVentilationRateMode, perPersonVentilationRateMode);
    }

    std::vector<std::string> AirTerminalSingleDuctInletSideMixer_Impl::perPersonVentilationRateModeValues() const {
      return AirTerminalSingleDuctInletSideMixer::perPersonVentilationRateModeValues();
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::inletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerPrimaryAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::outletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerOutletNodeName;
    }

    unsigned AirTerminalSingleDuctInletSideMixer_Impl::secondaryAirInletPort() const {
      return openstudio::AirTerminal_SingleDuct_MixerFields::MixerSecondaryAirInletNodeName;
    }

    boost::optional<Node> AirTerminalSingleDuctInletSideMixer_Impl::secondaryAirInletNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(secondaryAirInletPort());
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
