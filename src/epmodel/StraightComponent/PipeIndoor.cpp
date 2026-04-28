/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/PipeIndoor.hpp"
#include "StraightComponent/PipeIndoor_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "LayeredConstruction/Construction.hpp"
#include "LayeredConstruction/Construction_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Node.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Pipe_Indoor_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PipeIndoor::PipeIndoor(const Model& model) : StraightComponent(PipeIndoor::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::PipeIndoor_Impl>());

    bool ok = true;
    ok = setEnvironmentType("Zone");
    OS_ASSERT(ok);
    ok = setPipeInsideDiameter(0.05);
    OS_ASSERT(ok);
    ok = setPipeLength(100.0);
    OS_ASSERT(ok);
  }

  PipeIndoor::PipeIndoor(std::shared_ptr<detail::PipeIndoor_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType PipeIndoor::iddObjectType() {
    return IddObjectType::Pipe_Indoor;
  }

  std::vector<std::string> PipeIndoor::environmentTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Pipe_IndoorFields::EnvironmentType);
  }

  bool PipeIndoor::addToNode(Node& node) {
    return getImpl<detail::PipeIndoor_Impl>()->addToNode(node);
  }

  boost::optional<Construction> PipeIndoor::construction() const {
    return getImpl<detail::PipeIndoor_Impl>()->construction();
  }

  bool PipeIndoor::setConstruction(const Construction& construction) {
    return getImpl<detail::PipeIndoor_Impl>()->setConstruction(construction);
  }

  void PipeIndoor::resetConstruction() {
    getImpl<detail::PipeIndoor_Impl>()->resetConstruction();
  }

  std::string PipeIndoor::environmentType() const {
    return getImpl<detail::PipeIndoor_Impl>()->environmentType();
  }

  bool PipeIndoor::setEnvironmentType(const std::string& environmentType) {
    return getImpl<detail::PipeIndoor_Impl>()->setEnvironmentType(environmentType);
  }

  boost::optional<ThermalZone> PipeIndoor::ambientTemperatureZone() const {
    return getImpl<detail::PipeIndoor_Impl>()->ambientTemperatureZone();
  }

  bool PipeIndoor::setAmbientTemperatureZone(const ThermalZone& thermalZone) {
    return getImpl<detail::PipeIndoor_Impl>()->setAmbientTemperatureZone(thermalZone);
  }

  void PipeIndoor::resetAmbientTemperatureZone() {
    getImpl<detail::PipeIndoor_Impl>()->resetAmbientTemperatureZone();
  }

  boost::optional<Schedule> PipeIndoor::ambientTemperatureSchedule() const {
    return getImpl<detail::PipeIndoor_Impl>()->ambientTemperatureSchedule();
  }

  bool PipeIndoor::setAmbientTemperatureSchedule(Schedule& schedule) {
    return getImpl<detail::PipeIndoor_Impl>()->setAmbientTemperatureSchedule(schedule);
  }

  void PipeIndoor::resetAmbientTemperatureSchedule() {
    getImpl<detail::PipeIndoor_Impl>()->resetAmbientTemperatureSchedule();
  }

  boost::optional<Schedule> PipeIndoor::ambientAirVelocitySchedule() const {
    return getImpl<detail::PipeIndoor_Impl>()->ambientAirVelocitySchedule();
  }

  bool PipeIndoor::setAmbientAirVelocitySchedule(Schedule& schedule) {
    return getImpl<detail::PipeIndoor_Impl>()->setAmbientAirVelocitySchedule(schedule);
  }

  void PipeIndoor::resetAmbientAirVelocitySchedule() {
    getImpl<detail::PipeIndoor_Impl>()->resetAmbientAirVelocitySchedule();
  }

  double PipeIndoor::pipeInsideDiameter() const {
    return getImpl<detail::PipeIndoor_Impl>()->pipeInsideDiameter();
  }

  bool PipeIndoor::setPipeInsideDiameter(double pipeInsideDiameter) {
    return getImpl<detail::PipeIndoor_Impl>()->setPipeInsideDiameter(pipeInsideDiameter);
  }

  double PipeIndoor::pipeLength() const {
    return getImpl<detail::PipeIndoor_Impl>()->pipeLength();
  }

  bool PipeIndoor::setPipeLength(double pipeLength) {
    return getImpl<detail::PipeIndoor_Impl>()->setPipeLength(pipeLength);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> PipeIndoor_Impl::environmentTypeValues() const {
      return openstudio::epmodel::PipeIndoor::environmentTypeValues();
    }

    unsigned PipeIndoor_Impl::inletPort() const {
      return openstudio::Pipe_IndoorFields::FluidInletNodeName;
    }

    unsigned PipeIndoor_Impl::outletPort() const {
      return openstudio::Pipe_IndoorFields::FluidOutletNodeName;
    }

    bool PipeIndoor_Impl::addToNode(Node& node) {
      if (node.plantLoop()) {
        return StraightComponent_Impl::addToNode(node);
      }

      return false;
    }

    boost::optional<Construction> PipeIndoor_Impl::construction() const {
      return getObject<ModelObject>().getModelObjectTarget<Construction>(openstudio::Pipe_IndoorFields::ConstructionName);
    }

    bool PipeIndoor_Impl::setConstruction(const Construction& construction) {
      return setPointer(openstudio::Pipe_IndoorFields::ConstructionName, construction.handle());
    }

    void PipeIndoor_Impl::resetConstruction() {
      OS_ASSERT(setString(openstudio::Pipe_IndoorFields::ConstructionName, ""));
    }

    std::string PipeIndoor_Impl::environmentType() const {
      const auto value = getString(openstudio::Pipe_IndoorFields::EnvironmentType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipeIndoor_Impl::setEnvironmentType(const std::string& environmentType) {
      return setString(openstudio::Pipe_IndoorFields::EnvironmentType, environmentType);
    }

    boost::optional<ThermalZone> PipeIndoor_Impl::ambientTemperatureZone() const {
      return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Pipe_IndoorFields::AmbientTemperatureZoneName);
    }

    bool PipeIndoor_Impl::setAmbientTemperatureZone(const ThermalZone& thermalZone) {
      return setPointer(openstudio::Pipe_IndoorFields::AmbientTemperatureZoneName, thermalZone.handle());
    }

    void PipeIndoor_Impl::resetAmbientTemperatureZone() {
      OS_ASSERT(setString(openstudio::Pipe_IndoorFields::AmbientTemperatureZoneName, ""));
    }

    boost::optional<Schedule> PipeIndoor_Impl::ambientTemperatureSchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Pipe_IndoorFields::AmbientTemperatureScheduleName);
    }

    bool PipeIndoor_Impl::setAmbientTemperatureSchedule(Schedule& schedule) {
      return setSchedule(openstudio::Pipe_IndoorFields::AmbientTemperatureScheduleName, "PipeIndoor", "Ambient Temperature Schedule", schedule);
    }

    void PipeIndoor_Impl::resetAmbientTemperatureSchedule() {
      OS_ASSERT(setString(openstudio::Pipe_IndoorFields::AmbientTemperatureScheduleName, ""));
    }

    boost::optional<Schedule> PipeIndoor_Impl::ambientAirVelocitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Pipe_IndoorFields::AmbientAirVelocityScheduleName);
    }

    bool PipeIndoor_Impl::setAmbientAirVelocitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::Pipe_IndoorFields::AmbientAirVelocityScheduleName, "PipeIndoor", "Ambient Air Velocity Schedule", schedule);
    }

    void PipeIndoor_Impl::resetAmbientAirVelocitySchedule() {
      OS_ASSERT(setString(openstudio::Pipe_IndoorFields::AmbientAirVelocityScheduleName, ""));
    }

    double PipeIndoor_Impl::pipeInsideDiameter() const {
      const auto value = getDouble(openstudio::Pipe_IndoorFields::PipeInsideDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipeIndoor_Impl::setPipeInsideDiameter(double pipeInsideDiameter) {
      return setDouble(openstudio::Pipe_IndoorFields::PipeInsideDiameter, pipeInsideDiameter);
    }

    double PipeIndoor_Impl::pipeLength() const {
      const auto value = getDouble(openstudio::Pipe_IndoorFields::PipeLength, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipeIndoor_Impl::setPipeLength(double pipeLength) {
      return setDouble(openstudio::Pipe_IndoorFields::PipeLength, pipeLength);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
