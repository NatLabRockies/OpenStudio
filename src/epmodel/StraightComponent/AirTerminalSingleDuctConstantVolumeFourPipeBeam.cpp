/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <iterator>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeFourPipeBeam& terminal) {
      terminal.autosizeDesignPrimaryAirVolumeFlowRate();
      terminal.autosizeDesignChilledWaterVolumeFlowRate();
      terminal.autosizeDesignHotWaterVolumeFlowRate();
      terminal.autosizeZoneTotalBeamLength();
    }

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        if (zone.zoneAirNode() == node) {
          return zone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);

      auto zoneConnections = zoneImpl->getZoneHVACEquipmentConnections();
      auto equipmentList = zoneImpl->zoneHVACEquipmentList();
      if (!equipmentList) {
        ZoneHVACEquipmentList newEquipmentList(thermalZone.model());
        if (!newEquipmentList.name()) {
          newEquipmentList.createName();
        }
        if (!zoneConnections.setPointer(openstudio::ZoneHVAC_EquipmentConnectionsFields::ZoneConditioningEquipmentListName, newEquipmentList.handle())) {
          return false;
        }
        equipmentList = newEquipmentList;
      }

      auto equipmentListImpl = equipmentList->getImpl<detail::ZoneHVACEquipmentList_Impl>();
      OS_ASSERT(equipmentListImpl);
      return equipmentListImpl->addEquipment(terminal);
    }

  }  // namespace

AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(const Model& model)
  : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), model) {
  auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);

  if (!name()) {
    createName();
  }

  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setPrimaryAirAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setCoolingAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setHeatingAvailabilitySchedule(alwaysOn));

  applyConstructorDefaults(*this);
}

AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(
  const Model& model, ModelObject& coolingCoil, ModelObject& heatingCoil)
  : StraightComponent(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), model) {
  auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>();
  OS_ASSERT(impl);
  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);

  if (!name()) {
    createName();
  }

  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  OS_ASSERT(setPrimaryAirAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setCoolingAvailabilitySchedule(alwaysOn));
  OS_ASSERT(setHeatingAvailabilitySchedule(alwaysOn));
  applyConstructorDefaults(*this);

  if (!setCoolingCoil(coolingCoil)) {
    remove();
    LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                       "Cannot set the cooling coil, make sure you use OS_Coil_Cooling_FourPipeBeam");
  }
  if (!setHeatingCoil(heatingCoil)) {
    remove();
    LOG_FREE_AND_THROW("openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
                       "Cannot set the heating coil, make sure you use OS_Coil_Heating_FourPipeBeam");
  }
}

AirTerminalSingleDuctConstantVolumeFourPipeBeam::AirTerminalSingleDuctConstantVolumeFourPipeBeam(
  std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType() {
  return IddObjectType::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeam;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::addToNode(Node& node) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->addToNode(node);
}

Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::primaryAirAvailabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->primaryAirAvailabilitySchedule();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setPrimaryAirAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setPrimaryAirAvailabilitySchedule(schedule);
}

Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::coolingAvailabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->coolingAvailabilitySchedule();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setCoolingAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setCoolingAvailabilitySchedule(schedule);
}

Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam::heatingAvailabilitySchedule() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->heatingAvailabilitySchedule();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setHeatingAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setHeatingAvailabilitySchedule(schedule);
}

boost::optional<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam::coolingCoil() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->coolingCoil();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setCoolingCoil(ModelObject& coolingCoil) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setCoolingCoil(coolingCoil);
}

boost::optional<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam::heatingCoil() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->heatingCoil();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setHeatingCoil(ModelObject& heatingCoil) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setHeatingCoil(heatingCoil);
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designPrimaryAirVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designPrimaryAirVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignPrimaryAirVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignPrimaryAirVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignPrimaryAirVolumeFlowRate(designPrimaryAirVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignPrimaryAirVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignPrimaryAirVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designChilledWaterVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designChilledWaterVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignChilledWaterVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignChilledWaterVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignChilledWaterVolumeFlowRate(
    designChilledWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignChilledWaterVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignChilledWaterVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::designHotWaterVolumeFlowRate() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->designHotWaterVolumeFlowRate();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isDesignHotWaterVolumeFlowRateAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isDesignHotWaterVolumeFlowRateAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setDesignHotWaterVolumeFlowRate(designHotWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeDesignHotWaterVolumeFlowRate() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeDesignHotWaterVolumeFlowRate();
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam::zoneTotalBeamLength() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->zoneTotalBeamLength();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isZoneTotalBeamLengthAutosized() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isZoneTotalBeamLengthAutosized();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setZoneTotalBeamLength(double zoneTotalBeamLength) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setZoneTotalBeamLength(zoneTotalBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::autosizeZoneTotalBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->autosizeZoneTotalBeamLength();
}

double AirTerminalSingleDuctConstantVolumeFourPipeBeam::ratedPrimaryAirFlowRateperBeamLength() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->ratedPrimaryAirFlowRateperBeamLength();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->isRatedPrimaryAirFlowRateperBeamLengthDefaulted();
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
  return getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->setRatedPrimaryAirFlowRateperBeamLength(
    ratedPrimaryAirFlowRateperBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam::resetRatedPrimaryAirFlowRateperBeamLength() {
  getImpl<detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl>()->resetRatedPrimaryAirFlowRateperBeamLength();
}

unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::inletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirInletNodeName;
}

unsigned detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::outletPort() const {
  return openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirOutletNodeName;
}

bool detail::AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::addToNode(Node& node) {
  if (node.model() != model()) {
    LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
             "addToNode requires a node in the same model as the four-pipe beam.");
    return false;
  }

  auto airLoop = node.airLoopHVAC();
  if (!airLoop) {
    LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
             "addToNode requires a node that resolves to an AirLoopHVAC context.");
    return false;
  }

  auto zoneSplitter = airLoop->zoneSplitter();
  const auto thisNode = node.cast<ModelObject>();
  const auto splitterOutlets = zoneSplitter.outletModelObjects();
  const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
  if (splitterIt == splitterOutlets.end()) {
    LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
             "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
    return false;
  }
  const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

  if (!airLoop->zoneMixer().inletModelObject(splitterBranchIndex)) {
    LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
             "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
    return false;
  }

  auto thisObject = getObject<openstudio::epmodel::ModelObject>();
  if (!thisObject.name()) {
    thisObject.createName();
    if (!thisObject.name()) {
      return false;
    }
  }

  const std::string inletNodeName = node.nameString() + " - " + thisObject.nameString() + " Inlet Node";
  auto inletNode = model().getOrCreateTransientByName<openstudio::epmodel::Node>(inletNodeName);

  if (!zoneSplitter.setOutletModelObject(splitterBranchIndex, inletNode.cast<ModelObject>())) {
    return false;
  }

  if (!setPointer(inletPort(), inletNode.handle(), false)) {
    return false;
  }

  if (!setPointer(outletPort(), node.handle(), false)) {
    return false;
  }

  if (auto thermalZone = owningThermalZoneForBranchNode(model(), node)) {
    if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "addToNode failed to register the four-pipe beam with the owning thermal zone.");
      return false;
    }
  }

  return true;
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::primaryAirAvailabilitySchedule() const {
    auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
    if (!schedule) {
      LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Required primary air availability schedule not set, repairing persisted state with the model always-on discrete schedule");
      schedule = model().alwaysOnDiscreteSchedule();
      OS_ASSERT(schedule);
      const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setPrimaryAirAvailabilitySchedule(*schedule);
      OS_ASSERT(ok);
      schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName);
    }
    OS_ASSERT(schedule);
    return *schedule;
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setPrimaryAirAvailabilitySchedule(Schedule& schedule) {
    return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::PrimaryAirAvailabilityScheduleName,
                                         "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Primary Air Availability", schedule);
  }

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::coolingAvailabilitySchedule() const {
    auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
    if (!schedule) {
      LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Required cooling availability schedule not set, repairing persisted state with the model always-on discrete schedule");
      schedule = model().alwaysOnDiscreteSchedule();
      OS_ASSERT(schedule);
      const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setCoolingAvailabilitySchedule(*schedule);
      OS_ASSERT(ok);
      schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName);
    }
    OS_ASSERT(schedule);
    return *schedule;
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setCoolingAvailabilitySchedule(Schedule& schedule) {
    return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingAvailabilityScheduleName,
                                         "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Cooling Availability", schedule);
  }

  Schedule AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::heatingAvailabilitySchedule() const {
    auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
      openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);
    if (!schedule) {
      LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Required heating availability schedule not set, repairing persisted state with the model always-on discrete schedule");
      schedule = model().alwaysOnDiscreteSchedule();
      OS_ASSERT(schedule);
      const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl*>(this)->setHeatingAvailabilitySchedule(*schedule);
      OS_ASSERT(ok);
      schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName);
    }
    OS_ASSERT(schedule);
    return *schedule;
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setHeatingAvailabilitySchedule(Schedule& schedule) {
    return ModelObject_Impl::setSchedule(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingAvailabilityScheduleName,
                                         "AirTerminalSingleDuctConstantVolumeFourPipeBeam", "Heating Availability", schedule);
  }

  boost::optional<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::coolingCoil() const {
    return getObject<ModelObject>().getModelObjectTarget<ModelObject>(
      openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName);
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setCoolingCoil(ModelObject& coolingCoil) {
    if (coolingCoil.model() != model()) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Unsupported cooling coil from a different model for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
      return false;
    }
    if (coolingCoil.iddObject().type() != IddObjectType::OS_Coil_Cooling_FourPipeBeam) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Unsupported cooling coil type '" << coolingCoil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
      return false;
    }
    return setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::CoolingCoilName, coolingCoil.handle(), false);
  }

  boost::optional<ModelObject> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::heatingCoil() const {
    return getObject<ModelObject>().getModelObjectTarget<ModelObject>(
      openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName);
  }

  bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setHeatingCoil(ModelObject& heatingCoil) {
    if (heatingCoil.model() != model()) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Unsupported heating coil from a different model for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
      return false;
    }
    if (heatingCoil.iddObject().type() != IddObjectType::OS_Coil_Heating_FourPipeBeam) {
      LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeFourPipeBeam",
               "Unsupported heating coil type '" << heatingCoil.iddObject().name() << "' for AirTerminalSingleDuctConstantVolumeFourPipeBeam.");
      return false;
    }
    return setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::HeatingCoilName, heatingCoil.handle(), false);
  }

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designPrimaryAirVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignPrimaryAirVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignPrimaryAirVolumeFlowRate(double designPrimaryAirVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate,
                   designPrimaryAirVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignPrimaryAirVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignPrimaryAirVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designChilledWaterVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignChilledWaterVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignChilledWaterVolumeFlowRate(double designChilledWaterVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate,
                   designChilledWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignChilledWaterVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignChilledWaterVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::designHotWaterVolumeFlowRate() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isDesignHotWaterVolumeFlowRateAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setDesignHotWaterVolumeFlowRate(double designHotWaterVolumeFlowRate) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, designHotWaterVolumeFlowRate);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeDesignHotWaterVolumeFlowRate() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::DesignHotWaterVolumeFlowRate, "autosize"));
}

boost::optional<double> AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::zoneTotalBeamLength() const {
  return getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isZoneTotalBeamLengthAutosized() const {
  if (auto value = getString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setZoneTotalBeamLength(double zoneTotalBeamLength) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, zoneTotalBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::autosizeZoneTotalBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::ZoneTotalBeamLength, "autosize"));
}

double AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::ratedPrimaryAirFlowRateperBeamLength() const {
  const auto value = getDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, true);
  OS_ASSERT(value);
  return *value;
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::isRatedPrimaryAirFlowRateperBeamLengthDefaulted() const {
  return isEmpty(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength);
}

bool AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::setRatedPrimaryAirFlowRateperBeamLength(double ratedPrimaryAirFlowRateperBeamLength) {
  return setDouble(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength,
                   ratedPrimaryAirFlowRateperBeamLength);
}

void AirTerminalSingleDuctConstantVolumeFourPipeBeam_Impl::resetRatedPrimaryAirFlowRateperBeamLength() {
  OS_ASSERT(setString(openstudio::AirTerminal_SingleDuct_ConstantVolume_FourPipeBeamFields::RatedPrimaryAirFlowRateperBeamLength, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
