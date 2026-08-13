/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "AirLoopHVACDedicatedOutdoorAirSystem_Impl.hpp"

#include "AirLoopHVACMixer.hpp"
#include "AirLoopHVACMixer_Impl.hpp"
#include "AirLoopHVACSplitter.hpp"
#include "AirLoopHVACSplitter_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <algorithm>
#include <stdexcept>
#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirLoopHVAC_DedicatedOutdoorAirSystem_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Mixer_FieldEnums.hxx>
#include <utilities/idd/AirLoopHVAC_Splitter_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  AirLoopHVACDedicatedOutdoorAirSystem::AirLoopHVACDedicatedOutdoorAirSystem(const Model& model)
    : ModelObject(AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType(), model) {
    // Keep required scalar fields populated for strict non-optional getters.
    OS_ASSERT(setPreheatDesignTemperature(4.5));
    OS_ASSERT(setPreheatDesignHumidityRatio(0.004));
    OS_ASSERT(setPrecoolDesignTemperature(17.5));
    OS_ASSERT(setPrecoolDesignHumidityRatio(0.012));
    OS_ASSERT(setInt(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC, 0));
  }

  AirLoopHVACDedicatedOutdoorAirSystem::AirLoopHVACDedicatedOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& oaSystem)
    : AirLoopHVACDedicatedOutdoorAirSystem(oaSystem.model()) {
    auto schedule = oaSystem.model().alwaysOnDiscreteSchedule();
    if (!setAirLoopHVACOutdoorAirSystem(oaSystem) || !setAvailabilitySchedule(schedule)) {
      remove();
      throw std::runtime_error("Unable to construct a dedicated outdoor air system from the requested outdoor air system.");
    }
  }

  AirLoopHVACDedicatedOutdoorAirSystem::AirLoopHVACDedicatedOutdoorAirSystem(std::shared_ptr<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirLoopHVACDedicatedOutdoorAirSystem::iddObjectType() {
    return IddObjectType::AirLoopHVAC_DedicatedOutdoorAirSystem;
  }

  AirLoopHVACOutdoorAirSystem AirLoopHVACDedicatedOutdoorAirSystem::airLoopHVACOutdoorAirSystem() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->airLoopHVACOutdoorAirSystem();
  }

  Schedule AirLoopHVACDedicatedOutdoorAirSystem::availabilitySchedule() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->availabilitySchedule();
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::preheatDesignTemperature() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->preheatDesignTemperature();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPreheatDesignTemperature(double preheatDesignTemperature) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPreheatDesignTemperature(preheatDesignTemperature);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::preheatDesignHumidityRatio() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->preheatDesignHumidityRatio();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPreheatDesignHumidityRatio(preheatDesignHumidityRatio);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::precoolDesignTemperature() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->precoolDesignTemperature();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPrecoolDesignTemperature(double precoolDesignTemperature) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPrecoolDesignTemperature(precoolDesignTemperature);
  }

  double AirLoopHVACDedicatedOutdoorAirSystem::precoolDesignHumidityRatio() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->precoolDesignHumidityRatio();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setPrecoolDesignHumidityRatio(precoolDesignHumidityRatio);
  }

  unsigned int AirLoopHVACDedicatedOutdoorAirSystem::numberofAirLoops() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->numberofAirLoops();
  }

  std::vector<AirLoopHVAC> AirLoopHVACDedicatedOutdoorAirSystem::airLoops() const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->airLoops();
  }

  boost::optional<unsigned> AirLoopHVACDedicatedOutdoorAirSystem::airLoopIndex(const AirLoopHVAC& airLoopHVAC) const {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->airLoopIndex(airLoopHVAC);
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setAirLoopHVACOutdoorAirSystem(const AirLoopHVACOutdoorAirSystem& airLoopHVACOutdoorAirSystem) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setAirLoopHVACOutdoorAirSystem(airLoopHVACOutdoorAirSystem);
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->setAvailabilitySchedule(schedule);
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::addAirLoop(const AirLoopHVAC& airLoopHVAC) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->addAirLoop(airLoopHVAC);
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::removeAirLoop(const AirLoopHVAC& airLoopHVAC) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->removeAirLoop(airLoopHVAC);
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::removeAirLoop(unsigned groupIndex) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->removeAirLoop(groupIndex);
  }

  void AirLoopHVACDedicatedOutdoorAirSystem::removeAllAirLoops() {
    getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->removeAllAirLoops();
  }

  bool AirLoopHVACDedicatedOutdoorAirSystem::addAirLoops(const std::vector<AirLoopHVAC>& airLoopHVACs) {
    return getImpl<detail::AirLoopHVACDedicatedOutdoorAirSystem_Impl>()->addAirLoops(airLoopHVACs);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    openstudio::epmodel::AirLoopHVACOutdoorAirSystem AirLoopHVACDedicatedOutdoorAirSystem_Impl::airLoopHVACOutdoorAirSystem() const {
      auto result = getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName);
      OS_ASSERT(result);
      return *result;
    }

    openstudio::epmodel::Schedule AirLoopHVACDedicatedOutdoorAirSystem_Impl::availabilitySchedule() const {
      auto result = getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::Schedule>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AvailabilityScheduleName);
      OS_ASSERT(result);
      return *result;
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::preheatDesignTemperature() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPreheatDesignTemperature(double preheatDesignTemperature) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, preheatDesignTemperature);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::preheatDesignHumidityRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPreheatDesignHumidityRatio(double preheatDesignHumidityRatio) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, preheatDesignHumidityRatio);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::precoolDesignTemperature() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPrecoolDesignTemperature(double precoolDesignTemperature) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, precoolDesignTemperature);
    }

    double AirLoopHVACDedicatedOutdoorAirSystem_Impl::precoolDesignHumidityRatio() const {
      const auto value = getDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setPrecoolDesignHumidityRatio(double precoolDesignHumidityRatio) {
      return setDouble(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, precoolDesignHumidityRatio);
    }

    unsigned int AirLoopHVACDedicatedOutdoorAirSystem_Impl::numberofAirLoops() const {
      return numExtensibleGroups();
    }

    std::vector<openstudio::epmodel::AirLoopHVAC> AirLoopHVACDedicatedOutdoorAirSystem_Impl::airLoops() const {
      std::vector<openstudio::epmodel::AirLoopHVAC> result;
      for (const auto& group : extensibleGroups()) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        if (auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoopHVACName)) {
          if (auto airLoop = target->optionalCast<openstudio::epmodel::AirLoopHVAC>()) {
            result.push_back(*airLoop);
          }
        }
      }
      return result;
    }

    boost::optional<unsigned> AirLoopHVACDedicatedOutdoorAirSystem_Impl::airLoopIndex(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC) const {
      const auto groups = extensibleGroups();
      for (std::size_t i = 0; i < groups.size(); ++i) {
        auto workspaceGroup = groups[i].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoopHVACName);
        if (target && (*target == airLoopHVAC)) {
          return static_cast<unsigned>(i + 1u);
        }
      }
      return boost::none;
    }

    boost::optional<openstudio::epmodel::AirLoopHVACMixer> AirLoopHVACDedicatedOutdoorAirSystem_Impl::airLoopHVACMixer() const {
      return getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::AirLoopHVACMixer>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName);
    }

    boost::optional<openstudio::epmodel::AirLoopHVACSplitter> AirLoopHVACDedicatedOutdoorAirSystem_Impl::airLoopHVACSplitter() const {
      return getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::AirLoopHVACSplitter>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName);
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::ensureMixerAndSplitter() {
      auto doas = getObject<openstudio::epmodel::ModelObject>();
      auto oaSystem = doas.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName);
      if (!oaSystem) {
        return false;
      }
      auto splitterInlet = oaSystem->outdoorAirModelObject();
      if (!splitterInlet) {
        return false;
      }

      bool createdMixer = false;
      auto mixer = airLoopHVACMixer();
      if (!mixer) {
        mixer = openstudio::epmodel::AirLoopHVACMixer(model());
        mixer->setName(doas.nameString() + " Mixer");
        createdMixer = true;
        auto outletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(doas.nameString() + " Mixer Outlet");
        if (!mixer->getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::AirLoopHVAC_MixerFields::OutletNodeName, outletNode.handle(),
                                                                    false)) {
          mixer->remove();
          return false;
        }
        if (!doas.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName, mixer->handle())) {
          mixer->remove();
          return false;
        }
      } else if (!mixer->getModelObjectTarget<openstudio::epmodel::Node>(openstudio::AirLoopHVAC_MixerFields::OutletNodeName)) {
        auto outletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(doas.nameString() + " Mixer Outlet");
        if (!mixer->getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::AirLoopHVAC_MixerFields::OutletNodeName, outletNode.handle(),
                                                                    false)) {
          return false;
        }
      }

      auto splitter = airLoopHVACSplitter();
      if (!splitter) {
        splitter = openstudio::epmodel::AirLoopHVACSplitter(model());
        splitter->setName(doas.nameString() + " Splitter");
        if (!splitter->getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::AirLoopHVAC_SplitterFields::InletNodeName, splitterInlet->handle(),
                                                                       false)) {
          splitter->remove();
          if (createdMixer) {
            mixer->remove();
          }
          return false;
        }
        if (!doas.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName, splitter->handle())) {
          splitter->remove();
          if (createdMixer) {
            mixer->remove();
          }
          return false;
        }
      } else if (!splitter->getImpl<detail::ModelObject_Impl>()->setPointer(openstudio::AirLoopHVAC_SplitterFields::InletNodeName,
                                                                            splitterInlet->handle(), false)) {
        return false;
      }

      return true;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setAirLoopHVACOutdoorAirSystem(
      const openstudio::epmodel::AirLoopHVACOutdoorAirSystem& airLoopHVACOutdoorAirSystem) {
      if (airLoopHVACOutdoorAirSystem.model() != model()) {
        return false;
      }
      // A central DOAS outdoor-air system is not installed on any one served
      // air loop. Projecting an already-installed system would remove the
      // mixer and controller required by that loop's own OA branch.
      if (airLoopHVACOutdoorAirSystem.airLoopHVAC()) {
        return false;
      }
      for (const auto& doas : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACDedicatedOutdoorAirSystem>()) {
        auto target = doas.getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(
          openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName);
        if (target && (*target == airLoopHVACOutdoorAirSystem) && (doas.handle() != handle())) {
          return false;
        }
      }

      auto doas = getObject<openstudio::epmodel::ModelObject>();
      const auto oldTarget = doas.getTarget(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName);
      auto oldOASystem = oldTarget ? oldTarget->optionalCast<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>() : boost::none;
      if (oldOASystem && (*oldOASystem == airLoopHVACOutdoorAirSystem)) {
        return ensureMixerAndSplitter()
               && airLoopHVACOutdoorAirSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()
                    ->setDedicatedOutdoorAirSystemMode(true);
      }

      if (oldOASystem
          && !oldOASystem->getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(false)) {
        return false;
      }
      if (!doas.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName,
                           airLoopHVACOutdoorAirSystem.handle())) {
        if (oldOASystem) {
          OS_ASSERT(oldOASystem->getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(true));
        }
        return false;
      }
      if (ensureMixerAndSplitter()
          && airLoopHVACOutdoorAirSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(
            true)) {
        return true;
      }

      airLoopHVACOutdoorAirSystem.getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(false);
      if (oldTarget) {
        OS_ASSERT(doas.setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName, oldTarget->handle()));
        OS_ASSERT(ensureMixerAndSplitter());
        OS_ASSERT(oldOASystem);
        OS_ASSERT(oldOASystem->getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(true));
      } else {
        OS_ASSERT(doas.getImpl<detail::ModelObject_Impl>()->setPointer(
          openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName, Handle(), false));
      }
      return false;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::setAvailabilitySchedule(openstudio::epmodel::Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      return setSchedule(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AvailabilityScheduleName, "AirLoopHVACDedicatedOutdoorAirSystem",
                         "Availability Schedule", schedule);
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::addAirLoop(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC) {
      if (airLoopHVAC.model() != model()) {
        return false;
      }
      if (airLoopIndex(airLoopHVAC)) {
        return true;
      }
      for (const auto& doas : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACDedicatedOutdoorAirSystem>()) {
        if ((doas.handle() != handle()) && doas.airLoopIndex(airLoopHVAC)) {
          return false;
        }
      }

      auto oaSystem = airLoopHVAC.airLoopHVACOutdoorAirSystem();
      if (!oaSystem) {
        return false;
      }
      auto reliefNode = oaSystem->outboardReliefNode();
      auto outdoorAirNode = oaSystem->outboardOANode();
      if (!reliefNode || !outdoorAirNode) {
        return false;
      }
      auto mixer = airLoopHVACMixer();
      auto splitter = airLoopHVACSplitter();
      if (!mixer || !splitter) {
        return false;
      }

      auto doas = getObject<openstudio::epmodel::ModelObject>();
      const unsigned doasCount = doas.numExtensibleGroups();
      const unsigned mixerCount = mixer->numExtensibleGroups();
      const unsigned splitterCount = splitter->numExtensibleGroups();
      if ((doasCount != mixerCount) || (doasCount != splitterCount)) {
        return false;
      }

      auto doasGroup = doas.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      auto mixerGroup = mixer->pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      auto splitterGroup = splitter->pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      const bool linked =
        doasGroup && mixerGroup && splitterGroup
        && doasGroup->setPointer(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoopHVACName, airLoopHVAC.handle())
        && mixerGroup->setPointer(openstudio::AirLoopHVAC_MixerExtensibleFields::InletNodeName, reliefNode->handle(), false)
        && splitterGroup->setPointer(openstudio::AirLoopHVAC_SplitterExtensibleFields::OutletNodeName, outdoorAirNode->handle(), false);
      if (!linked) {
        while (doas.numExtensibleGroups() > doasCount) {
          doas.eraseExtensibleGroup(doas.numExtensibleGroups() - 1u);
        }
        while (mixer->numExtensibleGroups() > mixerCount) {
          mixer->eraseExtensibleGroup(mixer->numExtensibleGroups() - 1u);
        }
        while (splitter->numExtensibleGroups() > splitterCount) {
          splitter->eraseExtensibleGroup(splitter->numExtensibleGroups() - 1u);
        }
        return false;
      }

      OS_ASSERT(setInt(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC, static_cast<int>(doas.numExtensibleGroups())));
      return true;
    }

    std::vector<openstudio::IdfObject> AirLoopHVACDedicatedOutdoorAirSystem_Impl::remove() {
      auto owningModel = model();
      auto oaSystem = getObject<openstudio::epmodel::ModelObject>().getModelObjectTarget<openstudio::epmodel::AirLoopHVACOutdoorAirSystem>(
        openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName);
      if (oaSystem && !oaSystem->getImpl<openstudio::epmodel::detail::AirLoopHVACOutdoorAirSystem_Impl>()->setDedicatedOutdoorAirSystemMode(false)) {
        return {};
      }
      auto mixer = airLoopHVACMixer();
      auto splitter = airLoopHVACSplitter();
      boost::optional<openstudio::epmodel::Node> mixerOutlet;
      if (mixer) {
        mixerOutlet = mixer->getModelObjectTarget<openstudio::epmodel::Node>(openstudio::AirLoopHVAC_MixerFields::OutletNodeName);
      }
      auto removedParent = ModelObject_Impl::remove();
      if (removedParent.empty()) {
        return {};
      }

      std::vector<openstudio::IdfObject> result;
      bool removedMixer = false;
      if (mixer && owningModel.getObject(mixer->handle()) && mixer->sources().empty()) {
        auto removed = mixer->remove();
        removedMixer = !removed.empty();
        result.insert(result.end(), removed.begin(), removed.end());
      }
      if (splitter && owningModel.getObject(splitter->handle()) && splitter->sources().empty()) {
        auto removed = splitter->remove();
        result.insert(result.end(), removed.begin(), removed.end());
      }
      if (removedMixer && mixerOutlet && owningModel.getObject(mixerOutlet->handle()) && mixerOutlet->sources().empty()) {
        auto removed = mixerOutlet->remove();
        result.insert(result.end(), removed.begin(), removed.end());
      }
      result.insert(result.end(), removedParent.begin(), removedParent.end());
      return result;
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::removeAirLoop(const openstudio::epmodel::AirLoopHVAC& airLoopHVAC) {
      const auto index = airLoopIndex(airLoopHVAC);
      if (!index) {
        return false;
      }
      return removeAirLoop(*index);
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::removeAirLoop(unsigned groupIndex) {
      if ((groupIndex == 0u) || (groupIndex > numberofAirLoops())) {
        return false;
      }
      auto mixer = airLoopHVACMixer();
      auto splitter = airLoopHVACSplitter();
      if (!mixer || !splitter || (mixer->numExtensibleGroups() != numberofAirLoops()) || (splitter->numExtensibleGroups() != numberofAirLoops())) {
        return false;
      }

      const unsigned zeroBasedIndex = groupIndex - 1u;
      auto doas = getObject<openstudio::epmodel::ModelObject>();
      OS_ASSERT(!doas.eraseExtensibleGroup(zeroBasedIndex).empty());
      OS_ASSERT(!mixer->eraseExtensibleGroup(zeroBasedIndex).empty());
      OS_ASSERT(!splitter->eraseExtensibleGroup(zeroBasedIndex).empty());
      OS_ASSERT(setInt(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC, static_cast<int>(doas.numExtensibleGroups())));
      return true;
    }

    void AirLoopHVACDedicatedOutdoorAirSystem_Impl::removeAllAirLoops() {
      getObject<openstudio::epmodel::ModelObject>().clearExtensibleGroups();
      if (auto mixer = airLoopHVACMixer()) {
        mixer->clearExtensibleGroups();
      }
      if (auto splitter = airLoopHVACSplitter()) {
        splitter->clearExtensibleGroups();
      }
      OS_ASSERT(setInt(openstudio::AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC, 0));
    }

    bool AirLoopHVACDedicatedOutdoorAirSystem_Impl::addAirLoops(const std::vector<openstudio::epmodel::AirLoopHVAC>& airLoopHVACs) {
      std::vector<openstudio::epmodel::AirLoopHVAC> toAdd;
      for (const auto& airLoop : airLoopHVACs) {
        if (airLoop.model() != model()) {
          return false;
        }
        if (airLoopIndex(airLoop) || (std::ranges::find(toAdd, airLoop) != toAdd.end())) {
          continue;
        }
        for (const auto& doas : model().getConcreteModelObjects<openstudio::epmodel::AirLoopHVACDedicatedOutdoorAirSystem>()) {
          if ((doas.handle() != handle()) && doas.airLoopIndex(airLoop)) {
            return false;
          }
        }
        auto oaSystem = airLoop.airLoopHVACOutdoorAirSystem();
        if (!oaSystem || !oaSystem->outboardReliefNode() || !oaSystem->outboardOANode()) {
          return false;
        }
        toAdd.push_back(airLoop);
      }

      unsigned added = 0u;
      for (const auto& airLoop : toAdd) {
        if (!addAirLoop(airLoop)) {
          while (added > 0u) {
            OS_ASSERT(removeAirLoop(numberofAirLoops()));
            --added;
          }
          return false;
        }
        ++added;
      }
      return true;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
