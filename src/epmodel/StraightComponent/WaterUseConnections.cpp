/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/WaterUseConnections.hpp"
#include "StraightComponent/WaterUseConnections_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "SpaceLoadInstance/WaterUseEquipment.hpp"
#include "SpaceLoadInstance/WaterUseEquipment_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WaterUse_Connections_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

namespace openstudio {
namespace epmodel {

  WaterUseConnections::WaterUseConnections(const Model& model) : StraightComponent(WaterUseConnections::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::WaterUseConnections_Impl>());

    setDrainWaterHeatExchangerType("None");
    setDrainWaterHeatExchangerDestination("Plant");
  }

  WaterUseConnections::WaterUseConnections(std::shared_ptr<detail::WaterUseConnections_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType WaterUseConnections::iddObjectType() {
    return IddObjectType::WaterUse_Connections;
  }

  std::vector<std::string> WaterUseConnections::drainWaterHeatExchangerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerType);
  }

  std::vector<std::string> WaterUseConnections::drainWaterHeatExchangerDestinationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination);
  }

  boost::optional<Schedule> WaterUseConnections::hotWaterSupplyTemperatureSchedule() const {
    return getImpl<detail::WaterUseConnections_Impl>()->hotWaterSupplyTemperatureSchedule();
  }

  bool WaterUseConnections::setHotWaterSupplyTemperatureSchedule(Schedule& hotWaterSupplyTemperatureSchedule) {
    return getImpl<detail::WaterUseConnections_Impl>()->setHotWaterSupplyTemperatureSchedule(hotWaterSupplyTemperatureSchedule);
  }

  void WaterUseConnections::resetHotWaterSupplyTemperatureSchedule() {
    getImpl<detail::WaterUseConnections_Impl>()->resetHotWaterSupplyTemperatureSchedule();
  }

  boost::optional<Schedule> WaterUseConnections::coldWaterSupplyTemperatureSchedule() const {
    return getImpl<detail::WaterUseConnections_Impl>()->coldWaterSupplyTemperatureSchedule();
  }

  bool WaterUseConnections::setColdWaterSupplyTemperatureSchedule(Schedule& coldWaterSupplyTemperatureSchedule) {
    return getImpl<detail::WaterUseConnections_Impl>()->setColdWaterSupplyTemperatureSchedule(coldWaterSupplyTemperatureSchedule);
  }

  void WaterUseConnections::resetColdWaterSupplyTemperatureSchedule() {
    getImpl<detail::WaterUseConnections_Impl>()->resetColdWaterSupplyTemperatureSchedule();
  }

  std::vector<WaterUseEquipment> WaterUseConnections::waterUseEquipment() const {
    return getImpl<detail::WaterUseConnections_Impl>()->waterUseEquipment();
  }

  bool WaterUseConnections::addWaterUseEquipment(const WaterUseEquipment& waterUseEquipment) {
    return getImpl<detail::WaterUseConnections_Impl>()->addWaterUseEquipment(waterUseEquipment);
  }

  bool WaterUseConnections::removeWaterUseEquipment(WaterUseEquipment& waterUseEquipment) {
    return getImpl<detail::WaterUseConnections_Impl>()->removeWaterUseEquipment(waterUseEquipment);
  }

  std::string WaterUseConnections::drainWaterHeatExchangerType() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerType();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerType(drainWaterHeatExchangerType);
  }

  std::string WaterUseConnections::drainWaterHeatExchangerDestination() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerDestination();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerDestination(drainWaterHeatExchangerDestination);
  }

  boost::optional<double> WaterUseConnections::drainWaterHeatExchangerUFactorTimesArea() const {
    return getImpl<detail::WaterUseConnections_Impl>()->drainWaterHeatExchangerUFactorTimesArea();
  }

  bool WaterUseConnections::setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea) {
    return getImpl<detail::WaterUseConnections_Impl>()->setDrainWaterHeatExchangerUFactorTimesArea(drainWaterHeatExchangerUFactorTimesArea);
  }

  void WaterUseConnections::resetDrainWaterHeatExchangerUFactorTimesArea() {
    getImpl<detail::WaterUseConnections_Impl>()->resetDrainWaterHeatExchangerUFactorTimesArea();
  }

  namespace detail {

    boost::optional<Schedule> WaterUseConnections_Impl::hotWaterSupplyTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterUse_ConnectionsFields::HotWaterSupplyTemperatureScheduleName);
    }

    bool WaterUseConnections_Impl::setHotWaterSupplyTemperatureSchedule(Schedule& hotWaterSupplyTemperatureSchedule) {
      return setSchedule(openstudio::WaterUse_ConnectionsFields::HotWaterSupplyTemperatureScheduleName, "WaterUseConnections",
                         "Hot Water Supply Temperature", hotWaterSupplyTemperatureSchedule);
    }

    void WaterUseConnections_Impl::resetHotWaterSupplyTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterUse_ConnectionsFields::HotWaterSupplyTemperatureScheduleName, ""));
    }

    boost::optional<Schedule> WaterUseConnections_Impl::coldWaterSupplyTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::WaterUse_ConnectionsFields::ColdWaterSupplyTemperatureScheduleName);
    }

    bool WaterUseConnections_Impl::setColdWaterSupplyTemperatureSchedule(Schedule& coldWaterSupplyTemperatureSchedule) {
      return setSchedule(openstudio::WaterUse_ConnectionsFields::ColdWaterSupplyTemperatureScheduleName, "WaterUseConnections",
                         "Cold Water Supply Temperature", coldWaterSupplyTemperatureSchedule);
    }

    void WaterUseConnections_Impl::resetColdWaterSupplyTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::WaterUse_ConnectionsFields::ColdWaterSupplyTemperatureScheduleName, ""));
    }

    std::vector<WaterUseEquipment> WaterUseConnections_Impl::waterUseEquipment() const {
      std::vector<WaterUseEquipment> result;
      auto object = getObject<ModelObject>();
      auto groups = object.extensibleGroups();
      result.reserve(groups.size());
      for (const auto& group : groups) {
        auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        if (auto target = workspaceGroup->getTarget(openstudio::WaterUse_ConnectionsExtensibleFields::WaterUseEquipmentName)) {
          if (auto equipment = target->optionalCast<WaterUseEquipment>()) {
            result.emplace_back(*equipment);
          }
        }
      }
      return result;
    }

    bool WaterUseConnections_Impl::addWaterUseEquipment(const WaterUseEquipment& waterUseEquipment) {
      if (waterUseEquipment.model() != model()) {
        return false;
      }

      auto group = getObject<ModelObject>().pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!group) {
        return false;
      }

      return group->setPointer(openstudio::WaterUse_ConnectionsExtensibleFields::WaterUseEquipmentName, waterUseEquipment.handle());
    }

    bool WaterUseConnections_Impl::removeWaterUseEquipment(WaterUseEquipment& waterUseEquipment) {
      auto object = getObject<ModelObject>();
      auto groups = object.extensibleGroups();
      for (unsigned index = 0; index < groups.size(); ++index) {
        auto workspaceGroup = groups[index].optionalCast<openstudio::WorkspaceExtensibleGroup>();
        if (!workspaceGroup) {
          continue;
        }
        auto target = workspaceGroup->getTarget(openstudio::WaterUse_ConnectionsExtensibleFields::WaterUseEquipmentName);
        if (target && target->handle() == waterUseEquipment.handle()) {
          object.eraseExtensibleGroup(index);
          return true;
        }
      }
      return false;
    }

    std::string WaterUseConnections_Impl::drainWaterHeatExchangerType() const {
      const auto value = getString(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerType(const std::string& drainWaterHeatExchangerType) {
      return setString(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerType, drainWaterHeatExchangerType);
    }

    std::string WaterUseConnections_Impl::drainWaterHeatExchangerDestination() const {
      const auto value = getString(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination, true);
      OS_ASSERT(value);
      return *value;
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerDestination(const std::string& drainWaterHeatExchangerDestination) {
      return setString(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerDestination, drainWaterHeatExchangerDestination);
    }

    boost::optional<double> WaterUseConnections_Impl::drainWaterHeatExchangerUFactorTimesArea() const {
      return getDouble(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, true);
    }

    bool WaterUseConnections_Impl::setDrainWaterHeatExchangerUFactorTimesArea(double drainWaterHeatExchangerUFactorTimesArea) {
      return setDouble(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, drainWaterHeatExchangerUFactorTimesArea);
    }

    void WaterUseConnections_Impl::resetDrainWaterHeatExchangerUFactorTimesArea() {
      OS_ASSERT(setString(openstudio::WaterUse_ConnectionsFields::DrainWaterHeatExchangerUFactorTimesArea, ""));
    }

    std::vector<std::string> WaterUseConnections_Impl::drainWaterHeatExchangerTypeValues() const {
      return openstudio::epmodel::WaterUseConnections::drainWaterHeatExchangerTypeValues();
    }

    std::vector<std::string> WaterUseConnections_Impl::drainWaterHeatExchangerDestinationValues() const {
      return openstudio::epmodel::WaterUseConnections::drainWaterHeatExchangerDestinationValues();
    }

    bool WaterUseConnections_Impl::addToNode(Node& node) {
      if (auto plantLoop = node.plantLoop()) {
        if (plantLoop->demandComponent(node.handle())) {
          return StraightComponent_Impl::addToNode(node);
        }
      }
      return false;
    }

    unsigned WaterUseConnections_Impl::inletPort() const {
      return openstudio::WaterUse_ConnectionsFields::InletNodeName;
    }

    unsigned WaterUseConnections_Impl::outletPort() const {
      return openstudio::WaterUse_ConnectionsFields::OutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
