/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"
#include "StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "ModelObject.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit.hpp"
#include "ModelObject/ZoneHVACAirDistributionUnit_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "ModelObject/ZoneHVACEquipmentConnections_Impl.hpp"
#include "ModelObject/ZoneHVACEquipmentList.hpp"
#include "ModelObject/ZoneHVACEquipmentList_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "Mixer/AirLoopHVACZoneMixer.hpp"
#include "Mixer/AirLoopHVACZoneMixer_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Splitter/AirLoopHVACZoneSplitter.hpp"
#include "Splitter/AirLoopHVACZoneSplitter_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <algorithm>
#include <utilities/idd/OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeam_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_EquipmentConnections_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  namespace {

    void applyConstructorDefaults(AirTerminalSingleDuctConstantVolumeCooledBeam& terminal) {
      OS_ASSERT(terminal.setCooledBeamType("Passive"));
    }

    boost::optional<ThermalZone> owningThermalZoneForBranchNode(const Model& model, const Node& node) {
      for (const auto& connections : model.getConcreteModelObjects<ZoneHVACEquipmentConnections>()) {
        const auto inletNodes = connections.zoneAirInletNodes();
        if (std::ranges::find(inletNodes, node) != inletNodes.end()) {
          return connections.thermalZone();
        }
      }
      return boost::none;
    }

    bool isServedZoneReturnNode(const boost::optional<ThermalZone>& thermalZone, const ModelObject& nodeObject) {
      auto node = nodeObject.optionalCast<Node>();
      if (!thermalZone || !node) {
        return false;
      }

      auto zoneImpl = thermalZone->getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      auto connections = zoneImpl->zoneHVACEquipmentConnections();
      if (!connections) {
        return false;
      }

      const auto returnNodes = connections->zoneReturnAirNodes();
      return std::ranges::find(returnNodes, *node) != returnNodes.end();
    }

    boost::optional<ThermalZone> thermalZoneContainingTerminal(const Model& model, const ModelObject& terminal) {
      for (const auto& zone : model.getConcreteModelObjects<ThermalZone>()) {
        const auto equipment = zone.equipment();
        if (std::ranges::find(equipment, terminal) != equipment.end()) {
          return zone;
        }
      }
      return boost::none;
    }

    bool registerTerminalWithThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().addEquipment(terminal);
    }

    bool unregisterTerminalFromThermalZone(const ModelObject& terminal, ThermalZone& thermalZone) {
      auto zoneImpl = thermalZone.getImpl<detail::ThermalZone_Impl>();
      OS_ASSERT(zoneImpl);
      return zoneImpl->getZoneHVACEquipmentList().removeEquipment(terminal);
    }

  }  // namespace

  AirTerminalSingleDuctConstantVolumeCooledBeam::AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    if (!name()) {
      createName();
    }

    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeCooledBeam::AirTerminalSingleDuctConstantVolumeCooledBeam(const Model& model, Schedule& availabilitySchedule,
                                                                                               ModelObject& coilCoolingCooledBeam)
    : StraightComponent(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType(), model) {
    auto impl = getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>();
    OS_ASSERT(impl);
    detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
    impl->canonicalize(context);

    if (!name()) {
      createName();
    }

    OS_ASSERT(setAvailabilitySchedule(availabilitySchedule));
    OS_ASSERT(setCoolingCoil(coilCoolingCooledBeam));
    applyConstructorDefaults(*this);
  }

  AirTerminalSingleDuctConstantVolumeCooledBeam::AirTerminalSingleDuctConstantVolumeCooledBeam(
    std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl> impl)
    : StraightComponent(std::move(impl)) {}

  IddObjectType AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType() {
    return IddObjectType::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeam;
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::addToNode(Node& node) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->addToNode(node);
  }

  std::vector<std::string> AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType);
  }

  Schedule AirTerminalSingleDuctConstantVolumeCooledBeam::availabilitySchedule() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->availabilitySchedule();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setAvailabilitySchedule(schedule);
  }

  ModelObject AirTerminalSingleDuctConstantVolumeCooledBeam::coilCoolingCooledBeam() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->coilCoolingCooledBeam();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setCoolingCoil(ModelObject& coilCoolingCooledBeam) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setCoolingCoil(coilCoolingCooledBeam);
  }

  std::string AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamType() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->cooledBeamType();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setCooledBeamType(const std::string& cooledBeamType) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setCooledBeamType(cooledBeamType);
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::supplyAirVolumetricFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->supplyAirVolumetricFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isSupplyAirVolumetricFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isSupplyAirVolumetricFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isSupplyAirVolumetricFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isSupplyAirVolumetricFlowRateAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setSupplyAirVolumetricFlowRate(supplyAirVolumetricFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetSupplyAirVolumetricFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetSupplyAirVolumetricFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeSupplyAirVolumetricFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeSupplyAirVolumetricFlowRate();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::maximumTotalChilledWaterVolumetricFlowRate() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->maximumTotalChilledWaterVolumetricFlowRate();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isMaximumTotalChilledWaterVolumetricFlowRateDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isMaximumTotalChilledWaterVolumetricFlowRateAutosized();
  }

  bool
    AirTerminalSingleDuctConstantVolumeCooledBeam::setMaximumTotalChilledWaterVolumetricFlowRate(double maximumTotalChilledWaterVolumetricFlowRate) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setMaximumTotalChilledWaterVolumetricFlowRate(
      maximumTotalChilledWaterVolumetricFlowRate);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetMaximumTotalChilledWaterVolumetricFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetMaximumTotalChilledWaterVolumetricFlowRate();
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeMaximumTotalChilledWaterVolumetricFlowRate() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeMaximumTotalChilledWaterVolumetricFlowRate();
  }

  boost::optional<int> AirTerminalSingleDuctConstantVolumeCooledBeam::numberofBeams() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->numberofBeams();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isNumberofBeamsDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isNumberofBeamsDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isNumberofBeamsAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isNumberofBeamsAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setNumberofBeams(int numberofBeams) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setNumberofBeams(numberofBeams);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetNumberofBeams() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetNumberofBeams();
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeNumberofBeams() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeNumberofBeams();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::beamLength() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->beamLength();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isBeamLengthDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isBeamLengthDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isBeamLengthAutosized() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isBeamLengthAutosized();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setBeamLength(double beamLength) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setBeamLength(beamLength);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetBeamLength() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetBeamLength();
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::autosizeBeamLength() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autosizeBeamLength();
  }

  double AirTerminalSingleDuctConstantVolumeCooledBeam::designInletWaterTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->designInletWaterTemperature();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isDesignInletWaterTemperatureDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isDesignInletWaterTemperatureDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setDesignInletWaterTemperature(double designInletWaterTemperature) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setDesignInletWaterTemperature(designInletWaterTemperature);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetDesignInletWaterTemperature() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetDesignInletWaterTemperature();
  }

  double AirTerminalSingleDuctConstantVolumeCooledBeam::designOutletWaterTemperature() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->designOutletWaterTemperature();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isDesignOutletWaterTemperatureDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isDesignOutletWaterTemperatureDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setDesignOutletWaterTemperature(double designOutletWaterTemperature) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setDesignOutletWaterTemperature(designOutletWaterTemperature);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetDesignOutletWaterTemperature() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetDesignOutletWaterTemperature();
  }

  boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam::coefficientofInductionKin() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->coefficientofInductionKin();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isCoefficientofInductionKinDefaulted() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isCoefficientofInductionKinDefaulted();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::isCoefficientofInductionKinAutocalculated() const {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->isCoefficientofInductionKinAutocalculated();
  }

  bool AirTerminalSingleDuctConstantVolumeCooledBeam::setCoefficientofInductionKin(double coefficientofInductionKin) {
    return getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->setCoefficientofInductionKin(coefficientofInductionKin);
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::resetCoefficientofInductionKin() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->resetCoefficientofInductionKin();
  }

  void AirTerminalSingleDuctConstantVolumeCooledBeam::autocalculateCoefficientofInductionKin() {
    getImpl<detail::AirTerminalSingleDuctConstantVolumeCooledBeam_Impl>()->autocalculateCoefficientofInductionKin();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::cooledBeamType() const {
      const auto value = getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, true);
      OS_ASSERT(value);
      return *value;
    }

    Schedule AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::availabilitySchedule() const {
      auto schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName);
      if (!schedule) {
        LOG_FREE(Error, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "Required availability schedule not set, repairing persisted state with the model always-on discrete schedule");
        schedule = model().alwaysOnDiscreteSchedule();
        const bool ok = const_cast<AirTerminalSingleDuctConstantVolumeCooledBeam_Impl*>(this)->setAvailabilitySchedule(*schedule);
        OS_ASSERT(ok);
        schedule = getObject<ModelObject>().getModelObjectTarget<Schedule>(
          openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName);
      }
      OS_ASSERT(schedule);
      return *schedule;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::AvailabilityScheduleName,
                                           "AirTerminalSingleDuctConstantVolumeCooledBeam", "Availability", schedule);
    }

    ModelObject AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::coilCoolingCooledBeam() const {
      auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName);
      OS_ASSERT(coil);
      return *coil;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setCoolingCoil(ModelObject& coolingCoilCooledBeam) {
      if (coolingCoilCooledBeam.model() != model()) {
        return false;
      }
      if (coolingCoilCooledBeam.iddObject().type() != IddObjectType::OS_Coil_Cooling_CooledBeam) {
        return false;
      }
      return setPointer(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName, coolingCoilCooledBeam.handle(),
                        false);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setCooledBeamType(const std::string& cooledBeamType) {
      return setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CooledBeamType, cooledBeamType);
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::supplyAirVolumetricFlowRate() const {
      return getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isSupplyAirVolumetricFlowRateDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isSupplyAirVolumetricFlowRateAutosized() const {
      if (auto value = getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setSupplyAirVolumetricFlowRate(double supplyAirVolumetricFlowRate) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate,
                       supplyAirVolumetricFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetSupplyAirVolumetricFlowRate() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeSupplyAirVolumetricFlowRate() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirVolumetricFlowRate, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::maximumTotalChilledWaterVolumetricFlowRate() const {
      return getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, true);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isMaximumTotalChilledWaterVolumetricFlowRateDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isMaximumTotalChilledWaterVolumetricFlowRateAutosized() const {
      if (auto value =
            getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setMaximumTotalChilledWaterVolumetricFlowRate(
      double maximumTotalChilledWaterVolumetricFlowRate) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate,
                       maximumTotalChilledWaterVolumetricFlowRate);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetMaximumTotalChilledWaterVolumetricFlowRate() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, ""));
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeMaximumTotalChilledWaterVolumetricFlowRate() {
      OS_ASSERT(
        setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::MaximumTotalChilledWaterVolumetricFlowRate, "autosize"));
    }

    boost::optional<int> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::numberofBeams() const {
      return getInt(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, true);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isNumberofBeamsDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isNumberofBeamsAutosized() const {
      if (auto value = getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setNumberofBeams(int numberofBeams) {
      return setInt(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, numberofBeams);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetNumberofBeams() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, ""));
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeNumberofBeams() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::NumberofBeams, "autosize"));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::beamLength() const {
      return getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, true);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isBeamLengthDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isBeamLengthAutosized() const {
      if (auto value = getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setBeamLength(double beamLength) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, beamLength);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetBeamLength() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, ""));
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autosizeBeamLength() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::BeamLength, "autosize"));
    }

    double AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::designInletWaterTemperature() const {
      const auto value = getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isDesignInletWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setDesignInletWaterTemperature(double designInletWaterTemperature) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature,
                       designInletWaterTemperature);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetDesignInletWaterTemperature() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignInletWaterTemperature, ""));
    }

    double AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::designOutletWaterTemperature() const {
      const auto value = getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isDesignOutletWaterTemperatureDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setDesignOutletWaterTemperature(double designOutletWaterTemperature) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature,
                       designOutletWaterTemperature);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetDesignOutletWaterTemperature() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::DesignOutletWaterTemperature, ""));
    }

    boost::optional<double> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::coefficientofInductionKin() const {
      return getDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, true);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isCoefficientofInductionKinDefaulted() const {
      return isEmpty(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::isCoefficientofInductionKinAutocalculated() const {
      if (auto value = getString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::setCoefficientofInductionKin(double coefficientofInductionKin) {
      return setDouble(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, coefficientofInductionKin);
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::resetCoefficientofInductionKin() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, ""));
    }

    void AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::autocalculateCoefficientofInductionKin() {
      OS_ASSERT(setString(openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoefficientofInductionKin, "autocalculate"));
    }

    boost::optional<ZoneHVACAirDistributionUnit> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::zoneHVACAirDistributionUnit() const {
      auto terminal = getObject<openstudio::epmodel::ModelObject>();
      for (const auto& source : terminal.getSources(openstudio::IddObjectType::ZoneHVAC_AirDistributionUnit)) {
        if (auto adu = source.optionalCast<openstudio::epmodel::ZoneHVACAirDistributionUnit>()) {
          return adu;
        }
      }
      return boost::none;
    }

    std::vector<ModelObject> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::children() const {
      std::vector<ModelObject> result;
      auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName);
      if (coil) {
        result.push_back(*coil);
      }
      return result;
    }

    std::vector<openstudio::IdfObject> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::remove() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto coilObject = thisObject.getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName);
      auto coil = coilObject ? coilObject->optionalCast<openstudio::epmodel::HVACComponent>() : boost::optional<openstudio::epmodel::HVACComponent>{};

      removeFromLoop();

      if (coil) {
        if (auto plantLoop = coil->plantLoop()) {
          plantLoop->removeDemandBranchWithComponent(*coil);
        }
      }

      return HVACComponent_Impl::remove();
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::removeFromLoop() {
      auto thisObject = getObject<openstudio::epmodel::ModelObject>();
      auto thermalZone = thermalZoneContainingTerminal(model(), thisObject);
      auto inletNode = inletModelObject();
      auto outletNode = outletModelObject();
      auto coilObject = thisObject.getModelObjectTarget<openstudio::epmodel::ModelObject>(
        openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::CoolingCoilName);
      auto coil = coilObject ? coilObject->optionalCast<openstudio::epmodel::HVACComponent>() : boost::optional<openstudio::epmodel::HVACComponent>{};
      auto plantLoop = coil ? coil->plantLoop() : boost::optional<openstudio::epmodel::PlantLoop>{};

      bool shouldRemoveTerminalInletNode = false;
      if (auto terminal = thisObject.optionalCast<openstudio::epmodel::HVACComponent>()) {
        if (auto airLoop = terminal->airLoopHVAC()) {
          if (inletNode && outletNode) {
            const auto splitter = airLoop->zoneSplitter();
            const auto mixer = airLoop->zoneMixer();
            const auto splitterBranchIndex = splitter.branchIndexForOutletModelObject(*inletNode);
            shouldRemoveTerminalInletNode =
              (splitter.outletModelObject(splitterBranchIndex) == *inletNode) && (mixer.inletModelObject(splitterBranchIndex) == *outletNode);
          }
        }
      }

      bool removedFromAirLoop = false;
      if (inletNode && outletNode) {
        if (!StraightComponent_Impl::removeFromLoop()) {
          return false;
        }
        removedFromAirLoop = true;
      }

      if (thermalZone && !unregisterTerminalFromThermalZone(thisObject, *thermalZone)) {
        return false;
      }

      if (auto adu = zoneHVACAirDistributionUnit()) {
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName, openstudio::Handle())) {
          return false;
        }
        if (!adu->setString(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType, "")) {
          return false;
        }
        if (!adu->setPointer(openstudio::ZoneHVAC_AirDistributionUnitFields::AirTerminalName, openstudio::Handle())) {
          return false;
        }
      }

      setPointer(inletPort(), openstudio::Handle(), false);
      setPointer(outletPort(), openstudio::Handle(), false);

      if (shouldRemoveTerminalInletNode) {
        if (auto node = inletNode->optionalCast<openstudio::epmodel::Node>()) {
          node->remove();
        }
      }

      if (plantLoop && coil && !plantLoop->removeDemandBranchWithComponent(*coil)) {
        return false;
      }

      return removedFromAirLoop || static_cast<bool>(thermalZone) || static_cast<bool>(plantLoop);
    }

    bool AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::addToNode(Node& node) {
      if (node.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "addToNode requires a node in the same model as the cooled beam.");
        return false;
      }

      if (getObject<openstudio::epmodel::HVACComponent>().loop()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "Refusing to add an already-connected cooled beam terminal.");
        return false;
      }

      const auto thisNode = node.cast<ModelObject>();
      auto airLoop = node.airLoopHVAC();
      if (!airLoop) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "addToNode requires a node that resolves to an AirLoopHVAC context.");
        return false;
      }

      auto zoneSplitter = airLoop->zoneSplitter();
      auto zoneMixer = airLoop->zoneMixer();
      const auto splitterOutlets = zoneSplitter.outletModelObjects();
      const auto splitterIt = std::ranges::find(splitterOutlets, thisNode);
      if (splitterIt == splitterOutlets.end()) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "addToNode requires the drop node to be a ZoneSplitter outlet node for the target AirLoopHVAC.");
        return false;
      }
      const auto splitterBranchIndex = static_cast<unsigned>(std::distance(splitterOutlets.begin(), splitterIt));

      auto mixerInlet = zoneMixer.inletModelObject(splitterBranchIndex);
      if (!mixerInlet) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "addToNode requires a corresponding ZoneMixer inlet for ZoneSplitter branch index " << splitterBranchIndex << ".");
        return false;
      }
      auto thermalZone = owningThermalZoneForBranchNode(model(), node);
      if ((*mixerInlet != thisNode) && !isServedZoneReturnNode(thermalZone, *mixerInlet)) {
        LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                 "addToNode requires the drop node to either feed the ZoneMixer directly or be the served zone inlet node.");
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

      if (auto adu = zoneHVACAirDistributionUnit()) {
        adu->getImpl<openstudio::epmodel::detail::ZoneHVACAirDistributionUnit_Impl>()->setOutletNode(node);
      }

      if (thermalZone) {
        if (!registerTerminalWithThermalZone(thisObject, *thermalZone)) {
          LOG_FREE(Warn, "openstudio.epmodel.AirTerminalSingleDuctConstantVolumeCooledBeam",
                   "addToNode failed to register the cooled beam with the owning thermal zone.");
          return false;
        }
      }

      return true;
    }

    std::vector<std::string> AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::cooledBeamTypeValues() const {
      return openstudio::epmodel::AirTerminalSingleDuctConstantVolumeCooledBeam::cooledBeamTypeValues();
    }

    unsigned AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::inletPort() const {
      return openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirInletNodeName;
    }

    unsigned AirTerminalSingleDuctConstantVolumeCooledBeam_Impl::outletPort() const {
      return openstudio::OS_AirTerminal_SingleDuct_ConstantVolume_CooledBeamFields::SupplyAirOutletNodeName;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
