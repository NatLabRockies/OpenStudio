/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveElectric.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveElectric_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "Model.hpp"
#include "ModelObject/ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/Schedule_Impl.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Electric_FieldEnums.hxx>

#include <stdexcept>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardRadiantConvectiveElectric::ZoneHVACBaseboardRadiantConvectiveElectric(const Model& model)
    : ZoneHVACComponent(ZoneHVACBaseboardRadiantConvectiveElectric::iddObjectType(), model) {
    ScheduleConstant alwaysOn(model);
    OS_ASSERT(alwaysOn.setValue(1.0));
    OS_ASSERT(setAvailabilitySchedule(alwaysOn));
    OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
    autosizeHeatingDesignCapacity();
    OS_ASSERT(setHeatingDesignCapacityPerFloorArea(0.0));
    OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(1.0));
    OS_ASSERT(setEfficiency(1.0));
    OS_ASSERT(setFractionRadiant(0.2));
    OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(0.3));
  }

  ZoneHVACBaseboardRadiantConvectiveElectric::ZoneHVACBaseboardRadiantConvectiveElectric(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveElectric::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Electric;
  }

  std::vector<std::string> ZoneHVACBaseboardRadiantConvectiveElectric::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityMethod);
  }

  Schedule ZoneHVACBaseboardRadiantConvectiveElectric::availabilitySchedule() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->availabilitySchedule();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setAvailabilitySchedule(schedule);
  }

  std::string ZoneHVACBaseboardRadiantConvectiveElectric::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveElectric::heatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->heatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::isHeatingDesignCapacityAutosized() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->isHeatingDesignCapacityAutosized();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setHeatingDesignCapacity(double heatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setHeatingDesignCapacity(heatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveElectric::autosizeHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->autosizeHeatingDesignCapacity();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveElectric::autosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->autosizedHeatingDesignCapacity();
  }

  double ZoneHVACBaseboardRadiantConvectiveElectric::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setHeatingDesignCapacityPerFloorArea(
      heatingDesignCapacityPerFloorArea);
  }

  double ZoneHVACBaseboardRadiantConvectiveElectric::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  double ZoneHVACBaseboardRadiantConvectiveElectric::efficiency() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->efficiency();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setEfficiency(double efficiency) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setEfficiency(efficiency);
  }

  double ZoneHVACBaseboardRadiantConvectiveElectric::fractionRadiant() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->fractionRadiant();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setFractionRadiant(fractionRadiant);
  }

  double ZoneHVACBaseboardRadiantConvectiveElectric::fractionofRadiantEnergyIncidentonPeople() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->fractionofRadiantEnergyIncidentonPeople();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveElectric_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
      fractionofRadiantEnergyIncidentonPeople);
  }

  boost::optional<ThermalZone> ZoneHVACBaseboardRadiantConvectiveElectric::thermalZone() const {
    return ZoneHVACComponent::thermalZone();
  }

  bool ZoneHVACBaseboardRadiantConvectiveElectric::addToThermalZone(ThermalZone& thermalZone) {
    return ZoneHVACComponent::addToThermalZone(thermalZone);
  }

  void ZoneHVACBaseboardRadiantConvectiveElectric::removeFromThermalZone() {
    ZoneHVACComponent::removeFromThermalZone();
  }

  namespace detail {

    Schedule ZoneHVACBaseboardRadiantConvectiveElectric_Impl::availabilitySchedule() const {
      if (auto target =
            getObject<ModelObject>().getModelObjectTarget<Schedule>(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::AvailabilityScheduleName)) {
        return *target;
      }
      throw std::runtime_error("Baseboard radiant convective electric is missing its availability schedule.");
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return setSchedule(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::AvailabilityScheduleName, "ZoneHVACBaseboardRadiantConvectiveElectric",
                         "Availability", schedule);
    }

    std::string ZoneHVACBaseboardRadiantConvectiveElectric_Impl::heatingDesignCapacityMethod() const {
      boost::optional<std::string> value = getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      const bool result = setString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveElectric_Impl::heatingDesignCapacity() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::isHeatingDesignCapacityAutosized() const {
      if (auto value = getString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity, true)) {
        return openstudio::istringEqual(value.get(), "autosize");
      }
      return false;
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setHeatingDesignCapacity(double heatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity, heatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveElectric_Impl::autosizeHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacity, "autosize"));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveElectric_Impl::autosizedHeatingDesignCapacity() const {
      return boost::none;
    }

    double ZoneHVACBaseboardRadiantConvectiveElectric_Impl::heatingDesignCapacityPerFloorArea() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityPerFloorArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      const bool result =
        setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardRadiantConvectiveElectric_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofAutosizedHeatingDesignCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool
      ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofAutosizedHeatingDesignCapacity,
                                    fractionofAutosizedHeatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardRadiantConvectiveElectric_Impl::efficiency() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::Efficiency, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setEfficiency(double efficiency) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::Efficiency, efficiency);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardRadiantConvectiveElectric_Impl::fractionRadiant() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionRadiant, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setFractionRadiant(double fractionRadiant) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionRadiant, fractionRadiant);
      OS_ASSERT(result);
      return result;
    }

    double ZoneHVACBaseboardRadiantConvectiveElectric_Impl::fractionofRadiantEnergyIncidentonPeople() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofRadiantEnergyIncidentonPeople, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveElectric_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_ElectricFields::FractionofRadiantEnergyIncidentonPeople,
                                    fractionofRadiantEnergyIncidentonPeople);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
