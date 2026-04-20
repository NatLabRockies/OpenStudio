/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/CentralHeatPumpSystem.hpp"
#include "WaterToWaterComponent/CentralHeatPumpSystem_Impl.hpp"

#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/CentralHeatPumpSystem_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  CentralHeatPumpSystem::CentralHeatPumpSystem(const Model& model) : WaterToWaterComponent(CentralHeatPumpSystem::iddObjectType(), model) {
    // Keep required scalar fields populated for strict non-optional getters.
    OS_ASSERT(setControlMethod("SmartMixing"));
    OS_ASSERT(setAncillaryPower(0.0));
  }

  CentralHeatPumpSystem::CentralHeatPumpSystem(std::shared_ptr<detail::CentralHeatPumpSystem_Impl> impl) : WaterToWaterComponent(std::move(impl)) {}

  IddObjectType CentralHeatPumpSystem::iddObjectType() {
    return IddObjectType::CentralHeatPumpSystem;
  }

  std::vector<std::string> CentralHeatPumpSystem::controlMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CentralHeatPumpSystemFields::ControlMethod);
  }

  std::string CentralHeatPumpSystem::controlMethod() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->controlMethod();
  }

  bool CentralHeatPumpSystem::setControlMethod(const std::string& controlMethod) {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->setControlMethod(controlMethod);
  }

  double CentralHeatPumpSystem::ancillaryPower() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->ancillaryPower();
  }

  bool CentralHeatPumpSystem::setAncillaryPower(double ancillaryPower) {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->setAncillaryPower(ancillaryPower);
  }

  boost::optional<Schedule> CentralHeatPumpSystem::ancillaryOperationSchedule() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->ancillaryOperationSchedule();
  }

  bool CentralHeatPumpSystem::setAncillaryOperationSchedule(Schedule& schedule) {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->setAncillaryOperationSchedule(schedule);
  }

  void CentralHeatPumpSystem::resetAncillaryOperationSchedule() {
    getImpl<detail::CentralHeatPumpSystem_Impl>()->resetAncillaryOperationSchedule();
  }

  boost::optional<PlantLoop> CentralHeatPumpSystem::coolingPlantLoop() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->coolingPlantLoop();
  }

  boost::optional<PlantLoop> CentralHeatPumpSystem::sourcePlantLoop() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->sourcePlantLoop();
  }

  boost::optional<PlantLoop> CentralHeatPumpSystem::heatingPlantLoop() const {
    return getImpl<detail::CentralHeatPumpSystem_Impl>()->heatingPlantLoop();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string CentralHeatPumpSystem_Impl::controlMethod() const {
      const auto value = getString(openstudio::CentralHeatPumpSystemFields::ControlMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CentralHeatPumpSystem_Impl::setControlMethod(const std::string& controlMethod) {
      return setString(openstudio::CentralHeatPumpSystemFields::ControlMethod, controlMethod);
    }

    std::vector<std::string> CentralHeatPumpSystem_Impl::controlMethodValues() const {
      return openstudio::epmodel::CentralHeatPumpSystem::controlMethodValues();
    }

    double CentralHeatPumpSystem_Impl::ancillaryPower() const {
      const auto value = getDouble(openstudio::CentralHeatPumpSystemFields::AncillaryPower, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CentralHeatPumpSystem_Impl::setAncillaryPower(double ancillaryPower) {
      return setDouble(openstudio::CentralHeatPumpSystemFields::AncillaryPower, ancillaryPower);
    }

    boost::optional<Schedule> CentralHeatPumpSystem_Impl::ancillaryOperationSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::CentralHeatPumpSystemFields::AncillaryOperationScheduleName);
    }

    bool CentralHeatPumpSystem_Impl::setAncillaryOperationSchedule(Schedule& schedule) {
      return setSchedule(openstudio::CentralHeatPumpSystemFields::AncillaryOperationScheduleName, "CentralHeatPumpSystem", "Ancillary Operation",
                         schedule);
    }

    void CentralHeatPumpSystem_Impl::resetAncillaryOperationSchedule() {
      OS_ASSERT(setString(openstudio::CentralHeatPumpSystemFields::AncillaryOperationScheduleName, ""));
    }

    unsigned CentralHeatPumpSystem_Impl::supplyInletPort() const {
      return openstudio::CentralHeatPumpSystemFields::CoolingLoopInletNodeName;
    }

    unsigned CentralHeatPumpSystem_Impl::supplyOutletPort() const {
      return openstudio::CentralHeatPumpSystemFields::CoolingLoopOutletNodeName;
    }

    unsigned CentralHeatPumpSystem_Impl::demandInletPort() const {
      return openstudio::CentralHeatPumpSystemFields::SourceLoopInletNodeName;
    }

    unsigned CentralHeatPumpSystem_Impl::demandOutletPort() const {
      return openstudio::CentralHeatPumpSystemFields::SourceLoopOutletNodeName;
    }

    unsigned CentralHeatPumpSystem_Impl::tertiaryInletPort() const {
      return openstudio::CentralHeatPumpSystemFields::HeatingLoopInletNodeName;
    }

    unsigned CentralHeatPumpSystem_Impl::tertiaryOutletPort() const {
      return openstudio::CentralHeatPumpSystemFields::HeatingLoopOutletNodeName;
    }

    bool CentralHeatPumpSystem_Impl::addToNode(Node& node) {
      auto tPlantLoop = node.plantLoop();
      if (tPlantLoop && tPlantLoop->supplyComponent(node.handle())) {
        if (auto coolingPlant = coolingPlantLoop()) {
          if (tPlantLoop.get() != coolingPlant.get() && !heatingPlantLoop()) {
            return addToTertiaryNode(node);
          }
        }
      }
      return WaterToWaterComponent_Impl::addToNode(node);
    }

    bool CentralHeatPumpSystem_Impl::addToTertiaryNode(Node& node) {
      auto tPlantLoop = node.plantLoop();
      if (tPlantLoop && tPlantLoop->supplyComponent(node.handle())) {
        return WaterToWaterComponent_Impl::addToTertiaryNode(node);
      }
      return false;
    }

    boost::optional<PlantLoop> CentralHeatPumpSystem_Impl::coolingPlantLoop() const {
      return WaterToWaterComponent_Impl::plantLoop();
    }

    boost::optional<PlantLoop> CentralHeatPumpSystem_Impl::sourcePlantLoop() const {
      return WaterToWaterComponent_Impl::secondaryPlantLoop();
    }

    boost::optional<PlantLoop> CentralHeatPumpSystem_Impl::heatingPlantLoop() const {
      return WaterToWaterComponent_Impl::tertiaryPlantLoop();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
