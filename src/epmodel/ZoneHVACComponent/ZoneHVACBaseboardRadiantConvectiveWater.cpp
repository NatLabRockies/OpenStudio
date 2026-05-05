/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"

#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl.hpp"
#include "Model.hpp"
#include "HVACComponent/HVACComponent.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant.hpp"
#include "StraightComponent/CoilHeatingWaterBaseboardRadiant_Impl.hpp"
#include "StraightComponent/Node.hpp"
#include "HVACComponent/ThermalZone.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Water_FieldEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {
  namespace detail {

    // These companion coils are transient views over parent-owned storage, so they
    // still need a stable model-level identity while the parent exists. We key that
    // identity off the parent handle instead of the parent display name so a rename
    // does not orphan the transient child.
    std::string transientHeatingCoilName(const openstudio::epmodel::ZoneHVACBaseboardRadiantConvectiveWater& parent) {
      return "__transient__" + openstudio::toString(parent.handle()) + "__heating_water_baseboard_radiant";
    }

  }  // namespace detail

  ZoneHVACBaseboardRadiantConvectiveWater::ZoneHVACBaseboardRadiantConvectiveWater(const Model& model)
    : ZoneHVACComponent(ZoneHVACBaseboardRadiantConvectiveWater::iddObjectType(), model) {
    auto impl = getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>();
    OS_ASSERT(impl);
    impl->ensureDesignObject();

    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setFractionRadiant(0.3));
    OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(0.3));

    OS_ASSERT(setRatedAverageWaterTemperature(87.78));
    OS_ASSERT(setRatedWaterMassFlowRate(0.063));
    autosizeHeatingDesignCapacity();
    autosizeMaximumWaterFlowRate();
  }

  ZoneHVACBaseboardRadiantConvectiveWater::ZoneHVACBaseboardRadiantConvectiveWater(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveWater::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water;
  }

  Schedule ZoneHVACBaseboardRadiantConvectiveWater::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setAvailabilitySchedule(schedule);
  }

  double ZoneHVACBaseboardRadiantConvectiveWater::fractionRadiant() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->fractionRadiant();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setFractionRadiant(fractionRadiant);
  }

  double ZoneHVACBaseboardRadiantConvectiveWater::fractionofRadiantEnergyIncidentonPeople() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->fractionofRadiantEnergyIncidentonPeople();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
      fractionofRadiantEnergyIncidentonPeople);
  }

  CoilHeatingWaterBaseboardRadiant ZoneHVACBaseboardRadiantConvectiveWater::heatingCoil() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->heatingCoil();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setHeatingCoil(HVACComponent& heatingCoil) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setHeatingCoil(heatingCoil);
  }

  std::vector<ModelObject> ZoneHVACBaseboardRadiantConvectiveWater::children() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->children();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::ratedAverageWaterTemperature() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ratedAverageWaterTemperature();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isRatedAverageWaterTemperatureDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isRatedAverageWaterTemperatureDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setRatedAverageWaterTemperature(ratedAverageWaterTemperature);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::resetRatedAverageWaterTemperature() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resetRatedAverageWaterTemperature();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::ratedWaterMassFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->ratedWaterMassFlowRate();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isRatedWaterMassFlowRateDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isRatedWaterMassFlowRateDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setRatedWaterMassFlowRate(ratedWaterMassFlowRate);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::resetRatedWaterMassFlowRate() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->resetRatedWaterMassFlowRate();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater::maximumWaterFlowRate() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->maximumWaterFlowRate();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::isMaximumWaterFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->isMaximumWaterFlowRateAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::autosizeMaximumWaterFlowRate() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWater_Impl>()->autosizeMaximumWaterFlowRate();
  }

  boost::optional<ThermalZone> ZoneHVACBaseboardRadiantConvectiveWater::thermalZone() const {
    return ZoneHVACComponent::thermalZone();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWater::addToThermalZone(ThermalZone& thermalZone) {
    return ZoneHVACComponent::addToThermalZone(thermalZone);
  }

  void ZoneHVACBaseboardRadiantConvectiveWater::removeFromThermalZone() {
    ZoneHVACComponent::removeFromThermalZone();
  }

  namespace detail {

    unsigned ZoneHVACBaseboardRadiantConvectiveWater_Impl::inletPort() const {
      return 0u;
    }

    unsigned ZoneHVACBaseboardRadiantConvectiveWater_Impl::outletPort() const {
      return 0u;
    }

    Schedule ZoneHVACBaseboardRadiantConvectiveWater_Impl::availabilitySchedule() const {
      if (auto target = getObject<ModelObject>().getModelObjectTarget<Schedule>(
            openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::AvailabilityScheduleName)) {
        return *target;
      }
      throw std::runtime_error("Baseboard radiant convective water is missing its availability schedule.");
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::AvailabilityScheduleName,
                         "ZoneHVACBaseboardRadiantConvectiveWater", "Availability", schedule);
    }

    double ZoneHVACBaseboardRadiantConvectiveWater_Impl::fractionRadiant() const {
      if (auto design = designObject()) {
        return design->fractionRadiant();
      }
      throw std::runtime_error("Baseboard radiant design object is missing.");
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setFractionRadiant(double fractionRadiant) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setFractionRadiant(fractionRadiant);
    }

    double ZoneHVACBaseboardRadiantConvectiveWater_Impl::fractionofRadiantEnergyIncidentonPeople() const {
      if (auto design = designObject()) {
        if (auto value = design->fractionofRadiantEnergyIncidentonPeople()) {
          return *value;
        }
      }
      throw std::runtime_error("Baseboard radiant design object is missing its fraction-of-radiant-energy-incident-on-people value.");
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
      auto design = ensureDesignObject();
      return design.getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
        fractionofRadiantEnergyIncidentonPeople);
    }

    CoilHeatingWaterBaseboardRadiant ZoneHVACBaseboardRadiantConvectiveWater_Impl::heatingCoil() const {
      const auto parent = getObject<openstudio::epmodel::ZoneHVACBaseboardRadiantConvectiveWater>();
      return model().getOrCreateTransientByName<openstudio::epmodel::CoilHeatingWaterBaseboardRadiant>(detail::transientHeatingCoilName(parent));
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setHeatingCoil(HVACComponent& heatingCoil) {
      auto source = heatingCoil.optionalCast<CoilHeatingWaterBaseboardRadiant>();
      if (!source) {
        return false;
      }

      auto target = this->heatingCoil();
      bool result = true;

      result = target.setRatedAverageWaterTemperature(source->ratedAverageWaterTemperature()) && result;
      result = target.setRatedWaterMassFlowRate(source->ratedWaterMassFlowRate()) && result;
      result = target.setHeatingDesignCapacityMethod(source->heatingDesignCapacityMethod()) && result;
      if (source->heatingDesignCapacity()) {
        result = target.setHeatingDesignCapacity(*source->heatingDesignCapacity()) && result;
      } else {
        target.autosizeHeatingDesignCapacity();
      }
      result = target.setHeatingDesignCapacityPerFloorArea(source->heatingDesignCapacityPerFloorArea()) && result;
      result = target.setFractionofAutosizedHeatingDesignCapacity(source->fractionofAutosizedHeatingDesignCapacity()) && result;
      if (source->maximumWaterFlowRate()) {
        result = target.setMaximumWaterFlowRate(*source->maximumWaterFlowRate()) && result;
      } else {
        target.autosizeMaximumWaterFlowRate();
      }
      result = target.setConvergenceTolerance(source->convergenceTolerance()) && result;

      if (auto inlet = source->inletModelObject()) {
        if (auto node = inlet->optionalCast<Node>()) {
          result = setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::InletNodeName, Handle(), false) && result;
      }

      if (auto outlet = source->outletModelObject()) {
        if (auto node = outlet->optionalCast<Node>()) {
          result = setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName, node->handle(), false) && result;
        }
      } else {
        result = setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::OutletNodeName, Handle(), false) && result;
      }

      return result;
    }

    std::vector<ModelObject> ZoneHVACBaseboardRadiantConvectiveWater_Impl::children() const {
      return {heatingCoil().cast<ModelObject>()};
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::doCanonicalize(LoadContext& context) {
      if (context.repairEnabled()) {
        ensureDesignObject();
      }
    }

    boost::optional<ZoneHVACBaseboardRadiantConvectiveWaterDesign> ZoneHVACBaseboardRadiantConvectiveWater_Impl::designObject() const {
      if (auto target = getTarget(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject)) {
        if (auto typed = target->optionalCast<ZoneHVACBaseboardRadiantConvectiveWaterDesign>()) {
          return *typed;
        }
      }

      if (auto name = getString(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject, true); name && !name->empty()) {
        if (auto obj = workspace().getObjectByTypeAndName(IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water_Design, *name, true)) {
          if (auto typed = obj->optionalCast<ZoneHVACBaseboardRadiantConvectiveWaterDesign>()) {
            auto* self = const_cast<ZoneHVACBaseboardRadiantConvectiveWater_Impl*>(this);
            self->setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject, typed->handle(), false);
            return *typed;
          }
        }
      }

      return boost::none;
    }

    ZoneHVACBaseboardRadiantConvectiveWaterDesign ZoneHVACBaseboardRadiantConvectiveWater_Impl::ensureDesignObject() {
      if (auto existing = designObject()) {
        return *existing;
      }

      ZoneHVACBaseboardRadiantConvectiveWaterDesign created(model());
      if (const auto existingName = getString(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject, true);
          existingName && !existingName->empty()) {
        created.setName(*existingName);
      } else {
        created.setName(getObject<ModelObject>().nameString() + " Design");
      }
      OS_ASSERT(setPointer(openstudio::ZoneHVAC_Baseboard_RadiantConvective_WaterFields::DesignObject, created.handle(), false));
      return created;
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::ratedAverageWaterTemperature() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isRatedAverageWaterTemperatureDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setRatedAverageWaterTemperature(double ratedAverageWaterTemperature) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, ratedAverageWaterTemperature);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::resetRatedAverageWaterTemperature() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedAverageWaterTemperature, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::ratedWaterMassFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isRatedWaterMassFlowRateDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setRatedWaterMassFlowRate(double ratedWaterMassFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ratedWaterMassFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::resetRatedWaterMassFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::RatedWaterMassFlowRate, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isHeatingDesignCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::HeatingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWater_Impl::maximumWaterFlowRate() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::isMaximumWaterFlowRateAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveWater_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, maximumWaterFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWater_Impl::autosizeMaximumWaterFlowRate() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_WaterFields::MaximumWaterFlowRate, "autosize"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
