/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilCoolingDX.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ModelObject/CoilSystemCoolingDX.hpp"
#include "ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "ThermalZone.hpp"
#include "ThermalZone_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    std::vector<CoilSystemCoolingDX> coilSystemsFor(const Model& model, const Handle& coilHandle) {
      std::vector<CoilSystemCoolingDX> result;
      for (const auto& system : model.getConcreteModelObjects<CoilSystemCoolingDX>()) {
        auto linkedCoil = system.coolingCoil();
        if (linkedCoil && linkedCoil->handle() == coilHandle) {
          result.push_back(system);
        }
      }
      return result;
    }

    void applyConstructorDefaults(CoilCoolingDX& coil) {
      ScheduleConstant alwaysOn(coil.model());
      OS_ASSERT(alwaysOn.setValue(1.0));
      OS_ASSERT(coil.setAvailabilitySchedule(alwaysOn));
    }

    void applyDefaultPerformanceDefaults(CoilCoolingDXCurveFitPerformance& performance, const Model& model) {
      CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
      baseOperatingMode.autosizeRatedGrossTotalCoolingCapacity();
      baseOperatingMode.autosizeRatedEvaporatorAirFlowRate();
      baseOperatingMode.autosizeRatedCondenserAirFlowRate();
      OS_ASSERT(baseOperatingMode.setMaximumCyclingRate(0.0));
      OS_ASSERT(baseOperatingMode.setRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity(0.0));
      OS_ASSERT(baseOperatingMode.setLatentCapacityTimeConstant(0.0));
      OS_ASSERT(baseOperatingMode.setNominalTimeforCondensateRemovaltoBegin(0.0));
      OS_ASSERT(!baseOperatingMode.applyLatentDegradationtoSpeedsGreaterthan1());
      OS_ASSERT(baseOperatingMode.setCondenserType("AirCooled"));
      baseOperatingMode.autosizeNominalEvaporativeCondenserPumpPower();

      OS_ASSERT(performance.setCrankcaseHeaterCapacity(0.0));
      OS_ASSERT(performance.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-25.0));
      OS_ASSERT(performance.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(10.0));
      OS_ASSERT(performance.setUnitInternalStaticAirPressure(773.3));
      OS_ASSERT(performance.setCapacityControlMethod("Discrete"));
      OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterCapacity(0.0));
      OS_ASSERT(performance.setEvaporativeCondenserBasinHeaterSetpointTemperature(2.0));
      auto heaterSchedule = model.alwaysOnDiscreteSchedule();
      OS_ASSERT(performance.getImpl<detail::CoilCoolingDXCurveFitPerformance_Impl>()->setPointer(
        openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName, heaterSchedule.handle(),
        false));
      OS_ASSERT(performance.setCompressorFuelType("Electricity"));
      OS_ASSERT(performance.setBaseOperatingMode(baseOperatingMode));
    }

  }  // namespace

  CoilCoolingDX::CoilCoolingDX(const Model& model) : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);

    CoilCoolingDXCurveFitPerformance performance(model);
    applyDefaultPerformanceDefaults(performance, model);
    OS_ASSERT(setPerformanceObject(performance));
  }

  CoilCoolingDX::CoilCoolingDX(const Model& model, const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance)
    : StraightComponent(CoilCoolingDX::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilCoolingDX_Impl>());

    applyConstructorDefaults(*this);
    OS_ASSERT(setPerformanceObject(coilCoolingDXCurveFitPerformance));
  }

  CoilCoolingDX::CoilCoolingDX(std::shared_ptr<detail::CoilCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilCoolingDX::iddObjectType() {
    return IddObjectType::Coil_Cooling_DX;
  }

  bool CoilCoolingDX::addToNode(Node& node) {
    return getImpl<detail::CoilCoolingDX_Impl>()->addToNode(node);
  }

  Schedule CoilCoolingDX::availabilitySchedule() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->availabilitySchedule();
  }

  bool CoilCoolingDX::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setAvailabilitySchedule(schedule);
  }

  boost::optional<ThermalZone> CoilCoolingDX::condenserZone() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserZone();
  }

  bool CoilCoolingDX::setCondenserZone(const ThermalZone& thermalZone) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserZone(thermalZone);
  }

  void CoilCoolingDX::resetCondenserZone() {
    getImpl<detail::CoilCoolingDX_Impl>()->resetCondenserZone();
  }

  CoilCoolingDXCurveFitPerformance CoilCoolingDX::performanceObject() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->performanceObject();
  }

  bool CoilCoolingDX::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setPerformanceObject(coilCoolingDXCurveFitPerformance);
  }

  std::string CoilCoolingDX::condenserInletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserInletNodeName();
  }

  bool CoilCoolingDX::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserInletNodeName(condenserInletNodeName);
  }

  std::string CoilCoolingDX::condenserOutletNodeName() const {
    return getImpl<detail::CoilCoolingDX_Impl>()->condenserOutletNodeName();
  }

  bool CoilCoolingDX::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
    return getImpl<detail::CoilCoolingDX_Impl>()->setCondenserOutletNodeName(condenserOutletNodeName);
  }
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilCoolingDX_Impl::inletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName;
    }

    unsigned CoilCoolingDX_Impl::outletPort() const {
      return openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName;
    }

    bool CoilCoolingDX_Impl::addToNode(Node& node) {
      auto thisCoil = getObject<CoilCoolingDX>();
      if (thisCoil.containingHVACComponent()) {
        return false;
      }

      auto airLoop = node.airLoopHVAC();

      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }

      boost::optional<CoilSystemCoolingDX> system;
      bool createdSystem = false;
      if (systems.empty()) {
        // A bare DX coil is not valid branch equipment in EnergyPlus. Refuse
        // to replace legacy live topology unless the adapter already owns it.
        if (StraightComponent_Impl::airLoopHVAC()) {
          return false;
        }

        CoilSystemCoolingDX newSystem(model());
        if (!newSystem.setName(thisCoil.nameString() + " CoilSystem")) {
          newSystem.remove();
          return false;
        }
        auto systemImpl = newSystem.getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->configureForCoolingCoil(thisCoil)) {
          newSystem.remove();
          return false;
        }
        system = newSystem;
        createdSystem = true;
      } else {
        system = systems.front();
        auto systemImpl = system->getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return false;
        }
      }

      if (system->addToNode(node)) {
        return true;
      }
      if (createdSystem) {
        system->remove();
      }
      return false;
    }

    boost::optional<CoilSystemCoolingDX> CoilCoolingDX_Impl::coilSystemCoolingDX() const {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() == 1u) {
        return systems.front();
      }
      return boost::none;
    }

    bool CoilCoolingDX_Impl::removeFromLoop() {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }
      if (systems.empty()) {
        return StraightComponent_Impl::removeFromLoop();
      }
      auto thisCoil = getObject<CoilCoolingDX>();
      auto systemImpl = systems.front().getImpl<CoilSystemCoolingDX_Impl>();
      OS_ASSERT(systemImpl);
      if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
        return false;
      }
      return systems.front().removeFromLoop();
    }

    void CoilCoolingDX_Impl::disconnect() {
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return;
      }
      if (systems.size() == 1u) {
        auto thisCoil = getObject<CoilCoolingDX>();
        auto systemImpl = systems.front().getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return;
        }
        systems.front().disconnect();
        return;
      }
      StraightComponent_Impl::disconnect();
    }

    std::vector<IdfObject> CoilCoolingDX_Impl::remove() {
      if (!isRemovable()) {
        return {};
      }

      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return {};
      }

      std::vector<IdfObject> result;
      if (systems.size() == 1u) {
        auto system = systems.front();
        auto thisCoil = getObject<CoilCoolingDX>();
        auto systemImpl = system.getImpl<CoilSystemCoolingDX_Impl>();
        OS_ASSERT(systemImpl);
        if (!systemImpl->isCoherentForCoolingCoil(thisCoil)) {
          return {};
        }
        if (system.airLoopHVAC() && !system.removeFromLoop()) {
          return {};
        }
        auto removedSystem = system.remove();
        if (model().getObject(system.handle())) {
          return {};
        }
        result.insert(result.end(), removedSystem.begin(), removedSystem.end());
      }

      auto removedCoil = HVACComponent_Impl::remove();
      result.insert(result.end(), removedCoil.begin(), removedCoil.end());
      return result;
    }

    std::vector<ModelObject> CoilCoolingDX_Impl::children() const {
      return {performanceObject()};
    }

    Schedule CoilCoolingDX_Impl::availabilitySchedule() const {
      auto value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      if (!value) {
        value = this->model().alwaysOnDiscreteSchedule();
        OS_ASSERT(value);
        const_cast<CoilCoolingDX_Impl*>(this)->setAvailabilitySchedule(*value);
        value = getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      }
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setAvailabilitySchedule(Schedule& schedule) {
      if (schedule.model() != model()) {
        return false;
      }
      auto systems = coilSystemsFor(model(), handle());
      if (systems.size() > 1u) {
        return false;
      }

      const auto thisCoil = getObject<ModelObject>();
      const auto oldSchedule = thisCoil.getTarget(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
      if (!setPointer(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName, schedule.handle(), false)) {
        return false;
      }
      if (systems.size() == 1u && !systems.front().setPointer(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName, schedule.handle())) {
        OS_ASSERT(setPointer(openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName, oldSchedule ? oldSchedule->handle() : Handle(), false));
        return false;
      }
      return true;
    }

    boost::optional<ThermalZone> CoilCoolingDX_Impl::condenserZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Coil_Cooling_DXFields::CondenserZoneName);
    }

    bool CoilCoolingDX_Impl::setCondenserZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::Coil_Cooling_DXFields::CondenserZoneName, thermalZone.handle());
    }

    void CoilCoolingDX_Impl::resetCondenserZone() {
      bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserZoneName, "");
      OS_ASSERT(result);
    }

    CoilCoolingDXCurveFitPerformance CoilCoolingDX_Impl::performanceObject() const {
      auto value =
        getObject<ModelObject>().getModelObjectTarget<CoilCoolingDXCurveFitPerformance>(openstudio::Coil_Cooling_DXFields::PerformanceObjectName);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setPerformanceObject(const CoilCoolingDXCurveFitPerformance& coilCoolingDXCurveFitPerformance) {
      return coilCoolingDXCurveFitPerformance.model() == model()
             && setPointer(openstudio::Coil_Cooling_DXFields::PerformanceObjectName, coilCoolingDXCurveFitPerformance.handle());
    }

    // Condenser inlet node name
    std::string CoilCoolingDX_Impl::condenserInletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserInletNodeName(const std::string& condenserInletNodeName) {
      const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserInletNodeName, condenserInletNodeName);
      OS_ASSERT(result);
      return result;
    }

    // Condenser outlet node name
    std::string CoilCoolingDX_Impl::condenserOutletNodeName() const {
      const auto value = getString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingDX_Impl::setCondenserOutletNodeName(const std::string& condenserOutletNodeName) {
      const bool result = setString(openstudio::Coil_Cooling_DXFields::CondenserOutletNodeName, condenserOutletNodeName);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
