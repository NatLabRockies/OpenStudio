/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilSystemCoolingDX.hpp"
#include "CoilSystemCoolingDX_Impl.hpp"

#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Branch.hpp"
#include "BranchList.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Loop/AirLoopHVAC_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "StraightComponent/CoilCoolingDX.hpp"
#include "StraightComponent/CoilCoolingDX_Impl.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_DX_TwoSpeed_FieldEnums.hxx>
#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  CoilSystemCoolingDX::CoilSystemCoolingDX(const Model& model) : StraightComponent(CoilSystemCoolingDX::iddObjectType(), model) {}

  CoilSystemCoolingDX::CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilSystemCoolingDX::iddObjectType() {
    return IddObjectType::CoilSystem_Cooling_DX;
  }

  std::vector<std::string> CoilSystemCoolingDX::coolingCoilObjectTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType);
  }

  std::vector<std::string> CoilSystemCoolingDX::dehumidificationControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType);
  }

  boost::optional<Node> CoilSystemCoolingDX::sensorNode() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->sensorNode();
  }

  boost::optional<ModelObject> CoilSystemCoolingDX::coolingCoil() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->coolingCoil();
  }

  std::string CoilSystemCoolingDX::coolingCoilObjectType() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->coolingCoilObjectType();
  }

  bool CoilSystemCoolingDX::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setCoolingCoilObjectType(coolingCoilObjectType);
  }

  std::string CoilSystemCoolingDX::dehumidificationControlType() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->dehumidificationControlType();
  }

  bool CoilSystemCoolingDX::isDehumidificationControlTypeDefaulted() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->isDehumidificationControlTypeDefaulted();
  }

  bool CoilSystemCoolingDX::setDehumidificationControlType(const std::string& dehumidificationControlType) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setDehumidificationControlType(dehumidificationControlType);
  }

  void CoilSystemCoolingDX::resetDehumidificationControlType() {
    getImpl<detail::CoilSystemCoolingDX_Impl>()->resetDehumidificationControlType();
  }

  bool CoilSystemCoolingDX::runonSensibleLoad() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->runonSensibleLoad();
  }

  bool CoilSystemCoolingDX::isRunonSensibleLoadDefaulted() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->isRunonSensibleLoadDefaulted();
  }

  bool CoilSystemCoolingDX::setRunonSensibleLoad(bool runonSensibleLoad) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setRunonSensibleLoad(runonSensibleLoad);
  }

  void CoilSystemCoolingDX::resetRunonSensibleLoad() {
    getImpl<detail::CoilSystemCoolingDX_Impl>()->resetRunonSensibleLoad();
  }

  bool CoilSystemCoolingDX::runonLatentLoad() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->runonLatentLoad();
  }

  bool CoilSystemCoolingDX::isRunonLatentLoadDefaulted() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->isRunonLatentLoadDefaulted();
  }

  bool CoilSystemCoolingDX::setRunonLatentLoad(bool runonLatentLoad) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setRunonLatentLoad(runonLatentLoad);
  }

  void CoilSystemCoolingDX::resetRunonLatentLoad() {
    getImpl<detail::CoilSystemCoolingDX_Impl>()->resetRunonLatentLoad();
  }

  bool CoilSystemCoolingDX::useOutdoorAirDXCoolingCoil() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->useOutdoorAirDXCoolingCoil();
  }

  bool CoilSystemCoolingDX::isUseOutdoorAirDXCoolingCoilDefaulted() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->isUseOutdoorAirDXCoolingCoilDefaulted();
  }

  bool CoilSystemCoolingDX::setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setUseOutdoorAirDXCoolingCoil(useOutdoorAirDXCoolingCoil);
  }

  void CoilSystemCoolingDX::resetUseOutdoorAirDXCoolingCoil() {
    getImpl<detail::CoilSystemCoolingDX_Impl>()->resetUseOutdoorAirDXCoolingCoil();
  }

  double CoilSystemCoolingDX::outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->outdoorAirDXCoolingCoilLeavingMinimumAirTemperature();
  }

  bool CoilSystemCoolingDX::isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted();
  }

  bool CoilSystemCoolingDX::setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature) {
    return getImpl<detail::CoilSystemCoolingDX_Impl>()->setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(
      outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
  }

  void CoilSystemCoolingDX::resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature() {
    getImpl<detail::CoilSystemCoolingDX_Impl>()->resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    namespace {

      bool getBooleanFieldValue(const ModelObject_Impl& impl, int fieldIndex) {
        const auto value = impl.getString(fieldIndex, true);
        OS_ASSERT(value);
        return openstudio::istringEqual(*value, "yes");
      }

      bool setBooleanFieldValue(ModelObject_Impl& impl, int fieldIndex, bool value) {
        return impl.setString(fieldIndex, value ? "Yes" : "No");
      }

    }  // namespace

    unsigned CoilSystemCoolingDX_Impl::inletPort() const {
      return openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemInletNodeName;
    }

    unsigned CoilSystemCoolingDX_Impl::outletPort() const {
      return openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemOutletNodeName;
    }

    boost::optional<AirLoopHVAC> CoilSystemCoolingDX_Impl::airLoopHVAC() const {
      const auto thisObject = getObject<ModelObject>();
      for (const auto& airLoop : model().getConcreteModelObjects<AirLoopHVAC>()) {
        const auto branches = airLoop.getImpl<AirLoopHVAC_Impl>()->branchList().branches();
        for (const auto& branch : branches) {
          const auto components = branch.components();
          if (std::ranges::find(components, thisObject) != components.end()) {
            return airLoop;
          }
        }
      }
      return boost::none;
    }

    boost::optional<AirLoopHVACOutdoorAirSystem> CoilSystemCoolingDX_Impl::airLoopHVACOutdoorAirSystem() const {
      const auto thisObject = getObject<ModelObject>();
      for (const auto& oaSystem : model().getConcreteModelObjects<AirLoopHVACOutdoorAirSystem>()) {
        auto oaSystemImpl = oaSystem.getImpl<AirLoopHVACOutdoorAirSystem_Impl>();
        OS_ASSERT(oaSystemImpl);
        if (oaSystemImpl->isOutdoorAirStreamComponent(thisObject.handle()) || oaSystemImpl->isReliefAirStreamComponent(thisObject.handle())) {
          return oaSystem;
        }
      }
      return boost::none;
    }

    bool CoilSystemCoolingDX_Impl::configureForCoolingCoilObject(StraightComponent& coil, unsigned scheduleFieldIndex) {
      if (coil.model() != model()) {
        return false;
      }
      if (auto existing = coolingCoil(); existing && existing->handle() != coil.handle()) {
        return false;
      }

      const auto schedule = coil.getTarget(scheduleFieldIndex);
      if (!schedule || !schedule->optionalCast<Schedule>()) {
        return false;
      }
      const auto adapter = getObject<ModelObject>();
      const auto oldType = getString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType);
      const auto oldCoil = adapter.getTarget(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName);
      const auto oldSchedule = adapter.getTarget(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName);

      if (!setString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, coil.iddObject().name())
          || !setPointer(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName, coil.handle(), false)
          || !setPointer(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName, schedule->handle(), false)) {
        OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, oldType.value_or("")));
        OS_ASSERT(setPointer(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName, oldCoil ? oldCoil->handle() : Handle(), false));
        OS_ASSERT(
          setPointer(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName, oldSchedule ? oldSchedule->handle() : Handle(), false));
        return false;
      }
      return true;
    }

    bool CoilSystemCoolingDX_Impl::configureForCoolingCoil(CoilCoolingDX& coil) {
      return configureForCoolingCoilObject(coil, openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
    }

    bool CoilSystemCoolingDX_Impl::configureForCoolingCoil(CoilCoolingDXTwoSpeed& coil) {
      return configureForCoolingCoilObject(coil, openstudio::Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName);
    }

    bool CoilSystemCoolingDX_Impl::isCoherentForCoolingCoilObject(const StraightComponent& coil, unsigned scheduleFieldIndex) const {
      const auto linkedCoil = coolingCoil();
      if (!linkedCoil || linkedCoil->handle() != coil.handle() || !openstudio::istringEqual(coolingCoilObjectType(), coil.iddObject().name())) {
        return false;
      }
      const auto schedule = getObject<ModelObject>().getTarget(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName);
      const auto coilSchedule = coil.getTarget(scheduleFieldIndex);
      if (!schedule || !coilSchedule || schedule->handle() != coilSchedule->handle()) {
        return false;
      }

      const auto adapterInlet = inletModelObject();
      const auto adapterOutlet = outletModelObject();
      const auto coilInlet = coil.inletModelObject();
      const auto coilOutlet = coil.outletModelObject();
      const auto sensor = sensorNode();
      const bool adapterHasTopology = adapterInlet || adapterOutlet || sensor;
      const bool coilHasTopology = coilInlet || coilOutlet;
      if (!adapterHasTopology && !coilHasTopology) {
        return true;
      }
      return adapterInlet && adapterOutlet && sensor && coilInlet && coilOutlet && adapterInlet->handle() == coilInlet->handle()
             && adapterOutlet->handle() == coilOutlet->handle() && sensor->handle() == adapterOutlet->handle();
    }

    bool CoilSystemCoolingDX_Impl::isCoherentForCoolingCoil(const CoilCoolingDX& coil) const {
      return isCoherentForCoolingCoilObject(coil, openstudio::Coil_Cooling_DXFields::AvailabilityScheduleName);
    }

    bool CoilSystemCoolingDX_Impl::isCoherentForCoolingCoil(const CoilCoolingDXTwoSpeed& coil) const {
      return isCoherentForCoolingCoilObject(coil, openstudio::Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName);
    }

    boost::optional<ModelObject> CoilSystemCoolingDX_Impl::projectedCoolingCoil() const {
      auto coolingCoilObject = coolingCoil();
      if (!coolingCoilObject) {
        return boost::none;
      }
      if (auto coolingCoil = coolingCoilObject->optionalCast<CoilCoolingDX>()) {
        if (isCoherentForCoolingCoil(*coolingCoil)) {
          return coolingCoil->cast<ModelObject>();
        }
      } else if (auto coolingCoil = coolingCoilObject->optionalCast<CoilCoolingDXTwoSpeed>()) {
        if (isCoherentForCoolingCoil(*coolingCoil)) {
          return coolingCoil->cast<ModelObject>();
        }
      }
      return boost::none;
    }

    bool CoilSystemCoolingDX_Impl::syncCoolingCoilNodes() {
      auto linkedCoil = coolingCoil();
      auto inlet = inletModelObject();
      auto outlet = outletModelObject();
      if (!linkedCoil || !inlet || !outlet) {
        return false;
      }
      boost::optional<StraightComponent> coil;
      if (auto curveFitCoil = linkedCoil->optionalCast<CoilCoolingDX>()) {
        coil = curveFitCoil->cast<StraightComponent>();
      } else if (auto twoSpeedCoil = linkedCoil->optionalCast<CoilCoolingDXTwoSpeed>()) {
        coil = twoSpeedCoil->cast<StraightComponent>();
      }
      if (!coil) {
        return false;
      }
      auto coilImpl = coil->getImpl<StraightComponent_Impl>();
      OS_ASSERT(coilImpl);
      return coilImpl->setPointer(coilImpl->inletPort(), inlet->handle(), false)
             && coilImpl->setPointer(coilImpl->outletPort(), outlet->handle(), false)
             && setPointer(openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName, outlet->handle(), false);
    }

    void CoilSystemCoolingDX_Impl::clearTopologyPointers() {
      if (auto linkedCoil = coolingCoil()) {
        boost::optional<StraightComponent> coil;
        if (auto curveFitCoil = linkedCoil->optionalCast<CoilCoolingDX>()) {
          coil = curveFitCoil->cast<StraightComponent>();
        } else if (auto twoSpeedCoil = linkedCoil->optionalCast<CoilCoolingDXTwoSpeed>()) {
          coil = twoSpeedCoil->cast<StraightComponent>();
        }
        if (coil) {
          auto coilImpl = coil->getImpl<StraightComponent_Impl>();
          OS_ASSERT(coilImpl);
          OS_ASSERT(coilImpl->setPointer(coilImpl->inletPort(), Handle(), false));
          OS_ASSERT(coilImpl->setPointer(coilImpl->outletPort(), Handle(), false));
        }
      }
      OS_ASSERT(setPointer(inletPort(), Handle(), false));
      OS_ASSERT(setPointer(outletPort(), Handle(), false));
      OS_ASSERT(setPointer(openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName, Handle(), false));
    }

    bool CoilSystemCoolingDX_Impl::addToNode(Node& node) {
      auto linkedCoil = coolingCoil();
      const bool coherent =
        linkedCoil
        && ((linkedCoil->optionalCast<CoilCoolingDX>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDX>()))
            || (linkedCoil->optionalCast<CoilCoolingDXTwoSpeed>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDXTwoSpeed>())));
      if (!coherent) {
        return false;
      }
      const auto airLoop = node.airLoopHVAC();
      const auto oaSystem = node.airLoopHVACOutdoorAirSystem();
      const bool onAirLoopSupply = airLoop && airLoop->supplyComponent(node.handle());
      const bool onDedicatedOutdoorAirSystem = oaSystem && oaSystem->airLoopHVACDedicatedOutdoorAirSystem();
      if (!onAirLoopSupply && !onDedicatedOutdoorAirSystem) {
        return false;
      }
      if (!StraightComponent_Impl::addToNode(node)) {
        return false;
      }
      if (syncCoolingCoilNodes()) {
        return true;
      }
      (void)StraightComponent_Impl::removeFromLoop();
      clearTopologyPointers();
      return false;
    }

    bool CoilSystemCoolingDX_Impl::removeFromLoop() {
      if (!airLoopHVAC() && !airLoopHVACOutdoorAirSystem()) {
        return false;
      }
      auto linkedCoil = coolingCoil();
      const bool coherent =
        linkedCoil
        && ((linkedCoil->optionalCast<CoilCoolingDX>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDX>()))
            || (linkedCoil->optionalCast<CoilCoolingDXTwoSpeed>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDXTwoSpeed>())));
      if (!coherent) {
        return false;
      }
      if (!StraightComponent_Impl::removeFromLoop()) {
        return false;
      }
      clearTopologyPointers();
      return true;
    }

    void CoilSystemCoolingDX_Impl::disconnect() {
      if (airLoopHVAC() || airLoopHVACOutdoorAirSystem()) {
        (void)removeFromLoop();
      } else {
        clearTopologyPointers();
      }
    }

    std::vector<IdfObject> CoilSystemCoolingDX_Impl::remove() {
      if (airLoopHVAC() || airLoopHVACOutdoorAirSystem()) {
        auto linkedCoil = coolingCoil();
        const bool coherent =
          linkedCoil
          && ((linkedCoil->optionalCast<CoilCoolingDX>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDX>()))
              || (linkedCoil->optionalCast<CoilCoolingDXTwoSpeed>() && isCoherentForCoolingCoil(linkedCoil->cast<CoilCoolingDXTwoSpeed>())));
        if (!coherent) {
          return {};
        }
      }
      return HVACComponent_Impl::remove();
    }

    std::string CoilSystemCoolingDX_Impl::coolingCoilObjectType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingDX_Impl::setCoolingCoilObjectType(const std::string& coolingCoilObjectType) {
      return setString(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilObjectType, coolingCoilObjectType);
    }

    std::string CoilSystemCoolingDX_Impl::dehumidificationControlType() const {
      const auto value = getString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingDX_Impl::isDehumidificationControlTypeDefaulted() const {
      return isEmpty(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType);
    }

    bool CoilSystemCoolingDX_Impl::setDehumidificationControlType(const std::string& dehumidificationControlType) {
      return setString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, dehumidificationControlType);
    }

    void CoilSystemCoolingDX_Impl::resetDehumidificationControlType() {
      OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::DehumidificationControlType, ""));
    }

    bool CoilSystemCoolingDX_Impl::runonSensibleLoad() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad);
    }

    bool CoilSystemCoolingDX_Impl::isRunonSensibleLoadDefaulted() const {
      return isEmpty(openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad);
    }

    bool CoilSystemCoolingDX_Impl::setRunonSensibleLoad(bool runonSensibleLoad) {
      const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad, runonSensibleLoad);
      OS_ASSERT(result);
      return result;
    }

    void CoilSystemCoolingDX_Impl::resetRunonSensibleLoad() {
      OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::RunonSensibleLoad, ""));
    }

    bool CoilSystemCoolingDX_Impl::runonLatentLoad() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad);
    }

    bool CoilSystemCoolingDX_Impl::isRunonLatentLoadDefaulted() const {
      return isEmpty(openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad);
    }

    bool CoilSystemCoolingDX_Impl::setRunonLatentLoad(bool runonLatentLoad) {
      const bool result = setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad, runonLatentLoad);
      OS_ASSERT(result);
      return result;
    }

    void CoilSystemCoolingDX_Impl::resetRunonLatentLoad() {
      OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::RunonLatentLoad, ""));
    }

    bool CoilSystemCoolingDX_Impl::useOutdoorAirDXCoolingCoil() const {
      return getBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil);
    }

    bool CoilSystemCoolingDX_Impl::isUseOutdoorAirDXCoolingCoilDefaulted() const {
      return isEmpty(openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil);
    }

    bool CoilSystemCoolingDX_Impl::setUseOutdoorAirDXCoolingCoil(bool useOutdoorAirDXCoolingCoil) {
      const bool result =
        setBooleanFieldValue(*this, openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil, useOutdoorAirDXCoolingCoil);
      OS_ASSERT(result);
      return result;
    }

    void CoilSystemCoolingDX_Impl::resetUseOutdoorAirDXCoolingCoil() {
      OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::UseOutdoorAirDXCoolingCoil, ""));
    }

    double CoilSystemCoolingDX_Impl::outdoorAirDXCoolingCoilLeavingMinimumAirTemperature() const {
      const auto value = getDouble(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilSystemCoolingDX_Impl::isOutdoorAirDXCoolingCoilLeavingMinimumAirTemperatureDefaulted() const {
      return isEmpty(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
    }

    bool
      CoilSystemCoolingDX_Impl::setOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature(double outdoorAirDXCoolingCoilLeavingMinimumAirTemperature) {
      return setDouble(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature,
                       outdoorAirDXCoolingCoilLeavingMinimumAirTemperature);
    }

    void CoilSystemCoolingDX_Impl::resetOutdoorAirDXCoolingCoilLeavingMinimumAirTemperature() {
      OS_ASSERT(setString(openstudio::CoilSystem_Cooling_DXFields::OutdoorAirDXCoolingCoilLeavingMinimumAirTemperature, ""));
    }

    std::vector<std::string> CoilSystemCoolingDX_Impl::coolingCoilObjectTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingDX::coolingCoilObjectTypeValues();
    }

    std::vector<std::string> CoilSystemCoolingDX_Impl::dehumidificationControlTypeValues() const {
      return openstudio::epmodel::CoilSystemCoolingDX::dehumidificationControlTypeValues();
    }

    boost::optional<ModelObject> CoilSystemCoolingDX_Impl::coolingCoil() const {
      return getObject<ModelObject>().getModelObjectTarget<ModelObject>(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName);
    }

    boost::optional<Node> CoilSystemCoolingDX_Impl::sensorNode() const {
      return getObject<ModelObject>().getModelObjectTarget<Node>(openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
