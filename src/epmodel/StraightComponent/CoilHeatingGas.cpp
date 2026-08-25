/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGas.hpp"
#include "StraightComponent/CoilHeatingGas_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Node.hpp"
#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <algorithm>
#include <utilities/core/Assert.hpp>
#include <utilities/core/Logger.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>

namespace openstudio {
namespace epmodel {

  CoilHeatingGas::CoilHeatingGas(const Model& model) : StraightComponent(CoilHeatingGas::iddObjectType(), model) {
    auto impl = getImpl<detail::CoilHeatingGas_Impl>();
    OS_ASSERT(impl);

    // Preserve model counterpart defaults for required scalar fields.
    bool ok = true;
    ok = setGasBurnerEfficiency(0.8);
    OS_ASSERT(ok);
    ok = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "AutoSize");
    OS_ASSERT(ok);
    ok = setOnCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
    ok = setOffCycleParasiticGasLoad(0.0);
    OS_ASSERT(ok);
    auto alwaysOn = model.alwaysOnDiscreteSchedule();
    ok = setAvailabilitySchedule(alwaysOn);
    OS_ASSERT(ok);
  }

  CoilHeatingGas::CoilHeatingGas(const Model& model, Schedule& schedule) : StraightComponent(CoilHeatingGas::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::CoilHeatingGas_Impl>());
    if (!setAvailabilitySchedule(schedule)) {
      remove();
      throw openstudio::Exception("Unable to set " + briefDescription() + "'s availability schedule to " + schedule.briefDescription() + ".");
    }

    bool ok = setGasBurnerEfficiency(0.8);
    OS_ASSERT(ok);
    ok = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "AutoSize");
    OS_ASSERT(ok);
    ok = setOnCycleParasiticElectricLoad(0.0);
    OS_ASSERT(ok);
    ok = setOffCycleParasiticGasLoad(0.0);
    OS_ASSERT(ok);
  }

  CoilHeatingGas::CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType CoilHeatingGas::iddObjectType() {
    return IddObjectType::Coil_Heating_Fuel;
  }

  bool CoilHeatingGas::addToNode(Node& node) {
    return getImpl<detail::CoilHeatingGas_Impl>()->addToNode(node);
  }

  Schedule CoilHeatingGas::availabilitySchedule() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->availabilitySchedule();
  }

  Schedule CoilHeatingGas::availableSchedule() const {
    return availabilitySchedule();
  }

  bool CoilHeatingGas::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setAvailabilitySchedule(schedule);
  }

  bool CoilHeatingGas::setAvailableSchedule(Schedule& schedule) {
    return setAvailabilitySchedule(schedule);
  }

  boost::optional<Curve> CoilHeatingGas::partLoadFractionCorrelationCurve() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->partLoadFractionCorrelationCurve();
  }

  bool CoilHeatingGas::setPartLoadFractionCorrelationCurve(const Curve& curve) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setPartLoadFractionCorrelationCurve(curve);
  }

  void CoilHeatingGas::resetPartLoadFractionCorrelationCurve() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetPartLoadFractionCorrelationCurve();
  }

  std::vector<std::string> CoilHeatingGas::validFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_FuelFields::FuelType);
  }

  std::string CoilHeatingGas::fuelType() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->fuelType();
  }

  bool CoilHeatingGas::setFuelType(const std::string& fuelType) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setFuelType(fuelType);
  }

  void CoilHeatingGas::resetFuelType() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetFuelType();
  }

  double CoilHeatingGas::gasBurnerEfficiency() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->gasBurnerEfficiency();
  }

  bool CoilHeatingGas::setGasBurnerEfficiency(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setGasBurnerEfficiency(value);
  }

  double CoilHeatingGas::parasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->parasiticElectricLoad();
  }

  bool CoilHeatingGas::setParasiticElectricLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticElectricLoad(value);
  }

  double CoilHeatingGas::onCycleParasiticElectricLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->onCycleParasiticElectricLoad();
  }

  bool CoilHeatingGas::setOnCycleParasiticElectricLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setOnCycleParasiticElectricLoad(value);
  }

  double CoilHeatingGas::parasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->parasiticGasLoad();
  }

  bool CoilHeatingGas::setParasiticGasLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticGasLoad(value);
  }

  double CoilHeatingGas::offCycleParasiticGasLoad() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->offCycleParasiticGasLoad();
  }

  bool CoilHeatingGas::setOffCycleParasiticGasLoad(double value) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setOffCycleParasiticGasLoad(value);
  }

  boost::optional<double> CoilHeatingGas::nominalCapacity() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->nominalCapacity();
  }

  boost::optional<double> CoilHeatingGas::autosizedNominalCapacity() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->autosizedNominalCapacity();
  }

  bool CoilHeatingGas::isNominalCapacityAutosized() const {
    return getImpl<detail::CoilHeatingGas_Impl>()->isNominalCapacityAutosized();
  }

  bool CoilHeatingGas::setNominalCapacity(double nominalCapacity) {
    return getImpl<detail::CoilHeatingGas_Impl>()->setNominalCapacity(nominalCapacity);
  }

  void CoilHeatingGas::resetNominalCapacity() {
    getImpl<detail::CoilHeatingGas_Impl>()->resetNominalCapacity();
  }

  void CoilHeatingGas::autosizeNominalCapacity() {
    getImpl<detail::CoilHeatingGas_Impl>()->autosizeNominalCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned CoilHeatingGas_Impl::inletPort() const {
      return openstudio::Coil_Heating_FuelFields::AirInletNodeName;
    }

    unsigned CoilHeatingGas_Impl::outletPort() const {
      return openstudio::Coil_Heating_FuelFields::AirOutletNodeName;
    }

    std::vector<ModelObject> CoilHeatingGas_Impl::children() const {
      std::vector<ModelObject> result;
      if (auto partLoadCurve = partLoadFractionCorrelationCurve()) {
        result.push_back(*partLoadCurve);
      }
      return result;
    }

    bool CoilHeatingGas_Impl::addToNode(Node& node) {
      bool added = false;
      if (node.airLoopHVACOutdoorAirSystem()) {
        added = StraightComponent_Impl::addToNode(node);
      } else {
        auto airLoop = node.airLoopHVAC();
        if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
          return false;
        }
        added = StraightComponent_Impl::addToNode(node);
      }

      if (!added) {
        return false;
      }

      // Successful direct placement always supplies a same-model Node in this
      // IDD node field. Treat synchronization as a topology invariant: there
      // is no recoverable failure to report after the branch has mutated.
      syncTemperatureSetpointNode();
      return true;
    }

    bool CoilHeatingGas_Impl::removeFromLoop() {
      if (!StraightComponent_Impl::removeFromLoop()) {
        return false;
      }
      clearTemperatureSetpointNode();
      return true;
    }

    void CoilHeatingGas_Impl::syncTemperatureSetpointNode() {
      const auto outletObject = outletModelObject();
      const auto outletNode = outletObject ? outletObject->optionalCast<Node>() : boost::optional<Node>();
      if (!outletNode) {
        OS_ASSERT(false);
        return;
      }
      const bool result = setPointer(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName, outletNode->handle(), false);
      OS_ASSERT(result);
    }

    void CoilHeatingGas_Impl::clearTemperatureSetpointNode() {
      const bool result = setPointer(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName, Handle(), false);
      OS_ASSERT(result);
    }

    Schedule CoilHeatingGas_Impl::availabilitySchedule() const {
      constexpr auto field = openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName;
      const auto managedValue = getObject<ModelObject>().getField(field, false);
      OS_ASSERT(managedValue && !managedValue->empty());
      const auto targetHandle = openstudio::toUUID(*managedValue);
      OS_ASSERT(!targetHandle.isNull());
      const auto value = model().getModelObject<Schedule>(targetHandle);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName, "CoilHeatingGas", "Availability", schedule);
    }

    boost::optional<Curve> CoilHeatingGas_Impl::partLoadFractionCorrelationCurve() const {
      return getObject<ModelObject>().getModelObjectTarget<Curve>(openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName);
    }

    bool CoilHeatingGas_Impl::setPartLoadFractionCorrelationCurve(const Curve& curve) {
      constexpr auto field = openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName;
      if (curve.model() != model()) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingGas",
                 "Cannot set the part-load fraction correlation curve because the curve belongs to a different model.");
        return false;
      }
      if (!model().canBeTarget(curve.handle(), iddObject().objectLists(field))) {
        LOG_FREE(Warn, "openstudio.epmodel.CoilHeatingGas",
                 "Cannot set the part-load fraction correlation curve because curve type '" << curve.iddObject().type().valueName()
                                                                                            << "' is not accepted by Coil:Heating:Fuel.");
        return false;
      }
      return setPointer(field, curve.handle(), false);
    }

    void CoilHeatingGas_Impl::resetPartLoadFractionCorrelationCurve() {
      constexpr auto field = openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName;
      OS_ASSERT(setPointer(field, Handle(), false));
      OS_ASSERT(openstudio::detail::IdfObject_Impl::setString(field, "", false));
    }

    void CoilHeatingGas_Impl::doCanonicalize(LoadContext& context) {
      StraightComponent_Impl::doCanonicalize(context);

      const auto coil = getObject<ModelObject>();
      const auto coilName = coil.nameString();

      {
        constexpr auto field = openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName;
        const auto managedValue = coil.getField(field, false);
        const auto managedHandle = managedValue ? openstudio::toUUID(*managedValue) : Handle{};
        if (!managedHandle.isNull()) {
          auto schedule = model().getModelObject<Schedule>(managedHandle);
          boost::optional<Schedule> uniqueEligibleSchedule;
          bool ambiguous = false;
          if (schedule) {
            for (const auto& candidate : model().getObjectsByName(schedule->nameString(), true)) {
              if (auto namedSchedule = candidate.optionalCast<Schedule>()) {
                if (!model().canBeTarget(namedSchedule->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleSchedule) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleSchedule = *namedSchedule;
              }
            }
          }

          if (schedule && !ambiguous && uniqueEligibleSchedule && (uniqueEligibleSchedule->handle() == schedule->handle())
              && setAvailabilitySchedule(*schedule)) {
            // The managed relationship is already canonical.
          } else {
            detail::addLoadWarning(context, "Preserved an unresolved, ambiguous, ineligible, or incompatible availability schedule on "
                                            "Coil:Heating:Fuel '"
                                              + coilName + "'.");
          }
        } else {
          const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
          if (rawName && !rawName->empty()) {
            boost::optional<Schedule> uniqueEligibleSchedule;
            bool ambiguous = false;
            for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
              if (auto schedule = candidate.optionalCast<Schedule>()) {
                if (!model().canBeTarget(schedule->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleSchedule) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleSchedule = *schedule;
              }
            }

            if (uniqueEligibleSchedule && !ambiguous) {
              if (setAvailabilitySchedule(*uniqueEligibleSchedule)) {
                detail::addLoadInfo(context, "Reattached availability schedule '" + uniqueEligibleSchedule->nameString() + "' to Coil:Heating:Fuel '"
                                               + coilName + "'.");
              } else {
                detail::addLoadWarning(context, "Preserved incompatible availability schedule reference '" + *rawName + "' on Coil:Heating:Fuel '"
                                                  + coilName + "'.");
              }
            } else {
              detail::addLoadWarning(context, "Preserved unresolved or ambiguous availability schedule reference '" + *rawName
                                                + "' on Coil:Heating:Fuel '" + coilName + "'.");
            }
          } else if (context.repairEnabled()) {
            auto alwaysOn = model().alwaysOnDiscreteSchedule();
            if (setAvailabilitySchedule(alwaysOn)) {
              detail::addLoadInfo(context, "Attached the always-on availability schedule to Coil:Heating:Fuel '" + coilName + "'.");
            } else {
              detail::addLoadError(context, "Failed to attach the always-on availability schedule to Coil:Heating:Fuel '" + coilName + "'.");
            }
          } else {
            detail::addLoadWarning(context, "Coil:Heating:Fuel '" + coilName + "' has a blank availability schedule.");
          }
        }
      }

      {
        constexpr auto field = openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName;
        const auto managedValue = coil.getField(field, false);
        const auto managedHandle = managedValue ? openstudio::toUUID(*managedValue) : Handle{};
        if (!managedHandle.isNull()) {
          const auto curve = model().getModelObject<Curve>(managedHandle);
          boost::optional<Curve> uniqueEligibleCurve;
          bool ambiguous = false;
          if (curve) {
            for (const auto& candidate : model().getObjectsByName(curve->nameString(), true)) {
              if (auto namedCurve = candidate.optionalCast<Curve>()) {
                if (!model().canBeTarget(namedCurve->handle(), iddObject().objectLists(field))) {
                  continue;
                }
                if (uniqueEligibleCurve) {
                  ambiguous = true;
                  break;
                }
                uniqueEligibleCurve = *namedCurve;
              }
            }
          }

          if (curve && !ambiguous && uniqueEligibleCurve && (uniqueEligibleCurve->handle() == curve->handle())
              && setPartLoadFractionCorrelationCurve(*curve)) {
            return;
          }
          detail::addLoadWarning(context, "Preserved an unresolved, ambiguous, or ineligible part-load fraction correlation curve on "
                                          "Coil:Heating:Fuel '"
                                            + coilName + "'.");
          return;
        }

        const auto rawName = openstudio::detail::IdfObject_Impl::getString(field, false, true);
        if (!(rawName && !rawName->empty())) {
          return;
        }

        boost::optional<Curve> uniqueEligibleCurve;
        bool ambiguous = false;
        for (const auto& candidate : model().getObjectsByName(*rawName, true)) {
          if (auto curve = candidate.optionalCast<Curve>()) {
            if (!model().canBeTarget(curve->handle(), iddObject().objectLists(field))) {
              continue;
            }
            if (uniqueEligibleCurve) {
              ambiguous = true;
              break;
            }
            uniqueEligibleCurve = *curve;
          }
        }

        if (uniqueEligibleCurve && !ambiguous) {
          if (setPartLoadFractionCorrelationCurve(*uniqueEligibleCurve)) {
            detail::addLoadInfo(context, "Reattached part-load fraction correlation curve '" + uniqueEligibleCurve->nameString()
                                           + "' to Coil:Heating:Fuel '" + coilName + "'.");
          } else {
            detail::addLoadWarning(context, "Preserved incompatible part-load fraction correlation curve reference '" + *rawName
                                              + "' on Coil:Heating:Fuel '" + coilName + "'.");
          }
        } else {
          detail::addLoadWarning(context, "Preserved unresolved, ambiguous, or ineligible part-load fraction correlation curve reference '" + *rawName
                                            + "' on Coil:Heating:Fuel '" + coilName + "'.");
        }
      }
    }

    std::string CoilHeatingGas_Impl::fuelType() const {
      const auto value = getString(openstudio::Coil_Heating_FuelFields::FuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::Coil_Heating_FuelFields::FuelType, fuelType);
    }

    void CoilHeatingGas_Impl::resetFuelType() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::FuelType, "");
      OS_ASSERT(result);
    }

    double CoilHeatingGas_Impl::gasBurnerEfficiency() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setGasBurnerEfficiency(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, value);
    }

    double CoilHeatingGas_Impl::parasiticElectricLoad() const {
      return onCycleParasiticElectricLoad();
    }

    bool CoilHeatingGas_Impl::setParasiticElectricLoad(double value) {
      return setOnCycleParasiticElectricLoad(value);
    }

    double CoilHeatingGas_Impl::onCycleParasiticElectricLoad() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setOnCycleParasiticElectricLoad(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, value);
    }

    double CoilHeatingGas_Impl::parasiticGasLoad() const {
      return offCycleParasiticGasLoad();
    }

    bool CoilHeatingGas_Impl::setParasiticGasLoad(double value) {
      return setOffCycleParasiticGasLoad(value);
    }

    double CoilHeatingGas_Impl::offCycleParasiticGasLoad() const {
      const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilHeatingGas_Impl::setOffCycleParasiticGasLoad(double value) {
      return setDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, value);
    }

    boost::optional<double> CoilHeatingGas_Impl::nominalCapacity() const {
      return getDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, true);
    }

    boost::optional<double> CoilHeatingGas_Impl::autosizedNominalCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    bool CoilHeatingGas_Impl::isNominalCapacityAutosized() const {
      if (const auto value = getString(openstudio::Coil_Heating_FuelFields::NominalCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool CoilHeatingGas_Impl::setNominalCapacity(double nominalCapacity) {
      return setDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, nominalCapacity);
    }

    void CoilHeatingGas_Impl::resetNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "");
      OS_ASSERT(result);
    }

    void CoilHeatingGas_Impl::autosizeNominalCapacity() {
      const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "Autosize");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
