/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACUnitHeater.hpp"
#include "ZoneHVACComponent/ZoneHVACUnitHeater_Impl.hpp"

#include "HVACComponent.hpp"
#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "StraightComponent/Node.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <boost/none.hpp>

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_UnitHeater_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACUnitHeater::ZoneHVACUnitHeater(const Model& model) : ZoneHVACComponent(ZoneHVACUnitHeater::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    autosizeMaximumSupplyAirFlowRate();
    OS_ASSERT(setFanControlType("No"));
    autosizeMaximumHotWaterFlowRate();
    OS_ASSERT(setMinimumHotWaterFlowRate(0.0));
    OS_ASSERT(setHeatingConvergenceTolerance(0.001));
  }

  ZoneHVACUnitHeater::ZoneHVACUnitHeater(std::shared_ptr<detail::ZoneHVACUnitHeater_Impl> impl) : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACUnitHeater::iddObjectType() {
    return IddObjectType::ZoneHVAC_UnitHeater;
  }

  std::vector<std::string> ZoneHVACUnitHeater::fanControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating);
  }

  Schedule ZoneHVACUnitHeater::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACUnitHeater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setAvailabilitySchedule(schedule);
  }

  HVACComponent ZoneHVACUnitHeater::supplyAirFan() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->supplyAirFan();
  }

  bool ZoneHVACUnitHeater::setSupplyAirFan(const HVACComponent& fan) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setSupplyAirFan(fan);
  }

  HVACComponent ZoneHVACUnitHeater::heatingCoil() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->heatingCoil();
  }

  bool ZoneHVACUnitHeater::setHeatingCoil(const HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setHeatingCoil(heatingCoil);
  }

  boost::optional<Node> ZoneHVACUnitHeater::fanOutletNode() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->fanOutletNode();
  }

  boost::optional<double> ZoneHVACUnitHeater::maximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->maximumSupplyAirFlowRate();
  }

  bool ZoneHVACUnitHeater::isMaximumSupplyAirFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMaximumSupplyAirFlowRateAutosized();
  }

  bool ZoneHVACUnitHeater::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMaximumSupplyAirFlowRate(maximumSupplyAirFlowRate);
  }

  void ZoneHVACUnitHeater::autosizeMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizeMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACUnitHeater::autosizedMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizedMaximumSupplyAirFlowRate();
  }

  std::string ZoneHVACUnitHeater::fanControlType() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->fanControlType();
  }

  bool ZoneHVACUnitHeater::setFanControlType(const std::string& fanControlType) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setFanControlType(fanControlType);
  }

  boost::optional<double> ZoneHVACUnitHeater::maximumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->maximumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::isMaximumHotWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMaximumHotWaterFlowRateAutosized();
  }

  bool ZoneHVACUnitHeater::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMaximumHotWaterFlowRate(maximumHotWaterFlowRate);
  }

  void ZoneHVACUnitHeater::resetMaximumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetMaximumHotWaterFlowRate();
  }

  void ZoneHVACUnitHeater::autosizeMaximumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizeMaximumHotWaterFlowRate();
  }

  boost::optional<double> ZoneHVACUnitHeater::autosizedMaximumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->autosizedMaximumHotWaterFlowRate();
  }

  double ZoneHVACUnitHeater::minimumHotWaterFlowRate() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->minimumHotWaterFlowRate();
  }

  bool ZoneHVACUnitHeater::isMinimumHotWaterFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isMinimumHotWaterFlowRateDefaulted();
  }

  bool ZoneHVACUnitHeater::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setMinimumHotWaterFlowRate(minimumHotWaterFlowRate);
  }

  void ZoneHVACUnitHeater::resetMinimumHotWaterFlowRate() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetMinimumHotWaterFlowRate();
  }

  double ZoneHVACUnitHeater::heatingConvergenceTolerance() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->heatingConvergenceTolerance();
  }

  bool ZoneHVACUnitHeater::isHeatingConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->isHeatingConvergenceToleranceDefaulted();
  }

  bool ZoneHVACUnitHeater::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
    return getImpl<detail::ZoneHVACUnitHeater_Impl>()->setHeatingConvergenceTolerance(heatingConvergenceTolerance);
  }

  void ZoneHVACUnitHeater::resetHeatingConvergenceTolerance() {
    getImpl<detail::ZoneHVACUnitHeater_Impl>()->resetHeatingConvergenceTolerance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<ModelObject> ZoneHVACUnitHeater_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto fan = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_UnitHeaterFields::SupplyAirFanName)) {
        result.push_back(*fan);
      }
      if (auto coil = getObject<ModelObject>().getModelObjectTarget<ModelObject>(ZoneHVAC_UnitHeaterFields::HeatingCoilName)) {
        result.push_back(*coil);
      }
      return result;
    }

    unsigned ZoneHVACUnitHeater_Impl::inletPort() const {
      return ZoneHVAC_UnitHeaterFields::AirInletNodeName;
    }

    unsigned ZoneHVACUnitHeater_Impl::outletPort() const {
      return ZoneHVAC_UnitHeaterFields::AirOutletNodeName;
    }

    bool ZoneHVACUnitHeater_Impl::addToThermalZone(ThermalZone& thermalZone) {
      if (!ZoneHVACComponent_Impl::addToThermalZone(thermalZone)) {
        return false;
      }

      maintainContainedAirPath();
      return true;
    }

    void ZoneHVACUnitHeater_Impl::removeFromThermalZone() {
      ZoneHVACComponent_Impl::removeFromThermalZone();
      maintainContainedAirPath();
    }

    void ZoneHVACUnitHeater_Impl::doCanonicalize(LoadContext& context) {
      repairContainedAirPath(context);
    }

    Schedule ZoneHVACUnitHeater_Impl::availabilitySchedule() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_UnitHeaterFields::AvailabilityScheduleName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitHeater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(ZoneHVAC_UnitHeaterFields::AvailabilityScheduleName, "ZoneHVACUnitHeater", "Availability", schedule);
    }

    HVACComponent ZoneHVACUnitHeater_Impl::supplyAirFan() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitHeaterFields::SupplyAirFanName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitHeater_Impl::setSupplyAirFan(const HVACComponent& fan) {
      if (fan.model() != model()) {
        return false;
      }
      if (!fan.optionalCast<StraightComponent>()) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_UnitHeaterFields::SupplyAirFanName, fan.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    HVACComponent ZoneHVACUnitHeater_Impl::heatingCoil() const {
      auto target = getObject<ModelObject>().getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitHeaterFields::HeatingCoilName);
      OS_ASSERT(target);
      return *target;
    }

    bool ZoneHVACUnitHeater_Impl::setHeatingCoil(const HVACComponent& heatingCoil) {
      if (heatingCoil.model() != model()) {
        return false;
      }
      if (!heatingCoil.optionalCast<StraightComponent>()) {
        return false;
      }

      const bool result = setPointer(ZoneHVAC_UnitHeaterFields::HeatingCoilName, heatingCoil.handle(), false);
      if (result) {
        maintainContainedAirPath();
      }
      return result;
    }

    boost::optional<Node> ZoneHVACUnitHeater_Impl::fanOutletNode() const {
      auto thisObject = getObject<ModelObject>();

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitHeaterFields::SupplyAirFanName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan) {
        return boost::none;
      }

      // The parent exposes the fan-outlet role even when it aliases the unit
      // outlet because there is no downstream heating coil yet.
      auto fanOutlet = fan->outletModelObject();
      return fanOutlet ? fanOutlet->optionalCast<Node>() : boost::none;
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::maximumSupplyAirFlowRate() const {
      return getDouble(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACUnitHeater_Impl::isMaximumSupplyAirFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitHeater_Impl::setMaximumSupplyAirFlowRate(double maximumSupplyAirFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, maximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::autosizeMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumSupplyAirFlowRate, "autosize"));
    }

    std::string ZoneHVACUnitHeater_Impl::fanControlType() const {
      auto value = getString(ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::setFanControlType(const std::string& fanControlType) {
      const bool result = setString(ZoneHVAC_UnitHeaterFields::SupplyAirFanOperationDuringNoHeating, fanControlType);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::maximumHotWaterFlowRate() const {
      return getDouble(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, true);
    }

    bool ZoneHVACUnitHeater_Impl::isMaximumHotWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACUnitHeater_Impl::setMaximumHotWaterFlowRate(double maximumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, maximumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, ""));
    }

    void ZoneHVACUnitHeater_Impl::autosizeMaximumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MaximumHotWaterorSteamFlowRate, "autosize"));
    }

    double ZoneHVACUnitHeater_Impl::minimumHotWaterFlowRate() const {
      auto value = getDouble(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::isMinimumHotWaterFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate);
    }

    bool ZoneHVACUnitHeater_Impl::setMinimumHotWaterFlowRate(double minimumHotWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, minimumHotWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetMinimumHotWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::MinimumHotWaterorSteamFlowRate, ""));
    }

    double ZoneHVACUnitHeater_Impl::heatingConvergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACUnitHeater_Impl::isHeatingConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance);
    }

    bool ZoneHVACUnitHeater_Impl::setHeatingConvergenceTolerance(double heatingConvergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, heatingConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACUnitHeater_Impl::resetHeatingConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_UnitHeaterFields::HeatingConvergenceTolerance, ""));
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::autosizedMaximumSupplyAirFlowRate() const {
      return boost::none;
    }

    boost::optional<double> ZoneHVACUnitHeater_Impl::autosizedMaximumHotWaterFlowRate() const {
      return boost::none;
    }

    bool ZoneHVACUnitHeater_Impl::maintainContainedAirPath() {
      return reconcileContainedAirPath(false, nullptr);
    }

    bool ZoneHVACUnitHeater_Impl::repairContainedAirPath(LoadContext& context) {
      return reconcileContainedAirPath(true, &context);
    }

    bool ZoneHVACUnitHeater_Impl::reconcileContainedAirPath(bool allowChildNodeRecovery, LoadContext* context) {
      auto thisObject = getObject<ModelObject>();
      if (!thisObject.name()) {
        thisObject.createName();
      }

      auto fanObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitHeaterFields::SupplyAirFanName);
      auto coilObject = thisObject.getModelObjectTarget<HVACComponent>(ZoneHVAC_UnitHeaterFields::HeatingCoilName);
      auto fan = fanObject ? fanObject->optionalCast<StraightComponent>() : boost::none;
      auto coil = coilObject ? coilObject->optionalCast<StraightComponent>() : boost::none;
      if (!fan && !coil) {
        return false;
      }

      const auto baseName = thisObject.nameString();
      auto inletNode = resolvedOrCreatedNodeTarget(inletPort(), baseName + " Air Inlet Node");
      auto outletNode = resolvedOrCreatedNodeTarget(outletPort(), baseName + " Air Outlet Node");

      bool changed = false;
      const auto currentInletTarget = thisObject.getModelObjectTarget<Node>(inletPort());
      const auto currentInletName = thisObject.getString(inletPort());
      if (!(currentInletTarget && (*currentInletTarget == inletNode) && currentInletName
            && openstudio::istringEqual(*currentInletName, inletNode.nameString()))) {
        OS_ASSERT(thisObject.setPointer(inletPort(), inletNode.handle()));
        changed = true;
      }

      const auto currentOutletTarget = thisObject.getModelObjectTarget<Node>(outletPort());
      const auto currentOutletName = thisObject.getString(outletPort());
      if (!(currentOutletTarget && (*currentOutletTarget == outletNode) && currentOutletName
            && openstudio::istringEqual(*currentOutletName, outletNode.nameString()))) {
        OS_ASSERT(thisObject.setPointer(outletPort(), outletNode.handle()));
        changed = true;
      }

      if (fan && coil) {
        boost::optional<Node> internalNode;
        if (!allowChildNodeRecovery) {
          auto currentFanOutlet = fan->outletModelObject() ? fan->outletModelObject()->optionalCast<Node>() : boost::none;
          auto currentCoilInlet = coil->inletModelObject() ? coil->inletModelObject()->optionalCast<Node>() : boost::none;
          if (currentFanOutlet && currentCoilInlet && (*currentFanOutlet == *currentCoilInlet) && (*currentFanOutlet != inletNode)
              && (*currentFanOutlet != outletNode)) {
            internalNode = currentFanOutlet;
          }
        } else {
          internalNode = fanOutletNode();
        }
        if (!internalNode && allowChildNodeRecovery) {
          // Canonicalization can recover a user-named internal node after raw
          // child-field drift. Ordinary owner mutations should not guess from
          // damaged child wiring; they restore the intended path directly.
          if (auto fanOutletName = fan->getString(fan->outletPort()); fanOutletName && !fanOutletName->empty()) {
            auto candidate = model().getOrCreateTransientByName<Node>(*fanOutletName);
            if ((candidate != inletNode) && (candidate != outletNode)) {
              internalNode = candidate;
            }
          }
        }
        if (!internalNode && allowChildNodeRecovery) {
          if (auto coilInletName = coil->getString(coil->inletPort()); coilInletName && !coilInletName->empty()) {
            auto candidate = model().getOrCreateTransientByName<Node>(*coilInletName);
            if ((candidate != inletNode) && (candidate != outletNode)) {
              internalNode = candidate;
            }
          }
        }
        if (!internalNode) {
          internalNode = model().getOrCreateTransientByName<Node>(baseName + " Fan Outlet Node");
        }

        // The unit heater owns this internal node. Reuse the existing node object if
        // one is already wired so user renames survive later reconciliation.
        const auto fanInletTarget = fan->getModelObjectTarget<Node>(fan->inletPort());
        const auto fanInletName = fan->getString(fan->inletPort());
        if (!(fanInletTarget && (*fanInletTarget == inletNode) && fanInletName
              && openstudio::istringEqual(*fanInletName, inletNode.nameString()))) {
          OS_ASSERT(fan->setPointer(fan->inletPort(), inletNode.handle()));
          changed = true;
        }

        const auto fanOutletTarget = fan->getModelObjectTarget<Node>(fan->outletPort());
        const auto fanOutletName = fan->getString(fan->outletPort());
        if (!(fanOutletTarget && (*fanOutletTarget == *internalNode) && fanOutletName
              && openstudio::istringEqual(*fanOutletName, internalNode->nameString()))) {
          OS_ASSERT(fan->setPointer(fan->outletPort(), internalNode->handle()));
          changed = true;
        }

        const auto coilInletTarget = coil->getModelObjectTarget<Node>(coil->inletPort());
        const auto coilInletName = coil->getString(coil->inletPort());
        if (!(coilInletTarget && (*coilInletTarget == *internalNode) && coilInletName
              && openstudio::istringEqual(*coilInletName, internalNode->nameString()))) {
          OS_ASSERT(coil->setPointer(coil->inletPort(), internalNode->handle()));
          changed = true;
        }

        const auto coilOutletTarget = coil->getModelObjectTarget<Node>(coil->outletPort());
        const auto coilOutletName = coil->getString(coil->outletPort());
        if (!(coilOutletTarget && (*coilOutletTarget == outletNode) && coilOutletName
              && openstudio::istringEqual(*coilOutletName, outletNode.nameString()))) {
          OS_ASSERT(coil->setPointer(coil->outletPort(), outletNode.handle()));
          changed = true;
        }
      } else if (fan) {
        const auto fanInletTarget = fan->getModelObjectTarget<Node>(fan->inletPort());
        const auto fanInletName = fan->getString(fan->inletPort());
        if (!(fanInletTarget && (*fanInletTarget == inletNode) && fanInletName
              && openstudio::istringEqual(*fanInletName, inletNode.nameString()))) {
          OS_ASSERT(fan->setPointer(fan->inletPort(), inletNode.handle()));
          changed = true;
        }

        const auto fanOutletTarget = fan->getModelObjectTarget<Node>(fan->outletPort());
        const auto fanOutletName = fan->getString(fan->outletPort());
        if (!(fanOutletTarget && (*fanOutletTarget == outletNode) && fanOutletName
              && openstudio::istringEqual(*fanOutletName, outletNode.nameString()))) {
          OS_ASSERT(fan->setPointer(fan->outletPort(), outletNode.handle()));
          changed = true;
        }
      } else {
        const auto coilInletTarget = coil->getModelObjectTarget<Node>(coil->inletPort());
        const auto coilInletName = coil->getString(coil->inletPort());
        if (!(coilInletTarget && (*coilInletTarget == inletNode) && coilInletName
              && openstudio::istringEqual(*coilInletName, inletNode.nameString()))) {
          OS_ASSERT(coil->setPointer(coil->inletPort(), inletNode.handle()));
          changed = true;
        }

        const auto coilOutletTarget = coil->getModelObjectTarget<Node>(coil->outletPort());
        const auto coilOutletName = coil->getString(coil->outletPort());
        if (!(coilOutletTarget && (*coilOutletTarget == outletNode) && coilOutletName
              && openstudio::istringEqual(*coilOutletName, outletNode.nameString()))) {
          OS_ASSERT(coil->setPointer(coil->outletPort(), outletNode.handle()));
          changed = true;
        }
      }

      if (changed && context) {
        detail::addLoadInfo(*context, "Reconciled internal node wiring for ZoneHVAC:UnitHeater '" + baseName + "'.");
      }

      return changed;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
