/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/HumidifierSteamElectric.hpp"
#include "StraightComponent/HumidifierSteamElectric_Impl.hpp"

#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "Model.hpp"
#include "ModelObject.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Humidifier_Steam_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  HumidifierSteamElectric::HumidifierSteamElectric(const Model& model) : StraightComponent(HumidifierSteamElectric::iddObjectType(), model) {
    autosizeRatedCapacity();
    setRatedPower(10200.0);
    setString(openstudio::Humidifier_Steam_ElectricFields::WaterStorageTankName, "");
  }

  HumidifierSteamElectric::HumidifierSteamElectric(std::shared_ptr<detail::HumidifierSteamElectric_Impl> impl) : StraightComponent(std::move(impl)) {}

  IddObjectType HumidifierSteamElectric::iddObjectType() {
    return IddObjectType::Humidifier_Steam_Electric;
  }

  bool HumidifierSteamElectric::addToNode(Node& node) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->addToNode(node);
  }

  boost::optional<Schedule> HumidifierSteamElectric::availabilitySchedule() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->availabilitySchedule();
  }

  bool HumidifierSteamElectric::setAvailabilitySchedule(Schedule& schedule) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->setAvailabilitySchedule(schedule);
  }

  void HumidifierSteamElectric::resetAvailabilitySchedule() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->resetAvailabilitySchedule();
  }

  boost::optional<double> HumidifierSteamElectric::ratedCapacity() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->ratedCapacity();
  }

  bool HumidifierSteamElectric::isRatedCapacityAutosized() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->isRatedCapacityAutosized();
  }

  bool HumidifierSteamElectric::setRatedCapacity(double ratedCapacity) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->setRatedCapacity(ratedCapacity);
  }

  void HumidifierSteamElectric::autosizeRatedCapacity() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->autosizeRatedCapacity();
  }

  boost::optional<double> HumidifierSteamElectric::ratedPower() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->ratedPower();
  }

  bool HumidifierSteamElectric::isRatedPowerAutosized() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->isRatedPowerAutosized();
  }

  bool HumidifierSteamElectric::setRatedPower(double ratedPower) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->setRatedPower(ratedPower);
  }

  void HumidifierSteamElectric::resetRatedPower() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->resetRatedPower();
  }

  void HumidifierSteamElectric::autosizeRatedPower() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->autosizeRatedPower();
  }

  boost::optional<double> HumidifierSteamElectric::ratedFanPower() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->ratedFanPower();
  }

  bool HumidifierSteamElectric::setRatedFanPower(double ratedFanPower) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->setRatedFanPower(ratedFanPower);
  }

  void HumidifierSteamElectric::resetRatedFanPower() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->resetRatedFanPower();
  }

  boost::optional<double> HumidifierSteamElectric::standbyPower() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->standbyPower();
  }

  bool HumidifierSteamElectric::setStandbyPower(double standbyPower) {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->setStandbyPower(standbyPower);
  }

  void HumidifierSteamElectric::resetStandbyPower() {
    getImpl<detail::HumidifierSteamElectric_Impl>()->resetStandbyPower();
  }

  boost::optional<double> HumidifierSteamElectric::autosizedRatedCapacity() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->autosizedRatedCapacity();
  }

  boost::optional<double> HumidifierSteamElectric::autosizedRatedPower() const {
    return getImpl<detail::HumidifierSteamElectric_Impl>()->autosizedRatedPower();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    unsigned HumidifierSteamElectric_Impl::inletPort() const {
      return openstudio::Humidifier_Steam_ElectricFields::AirInletNodeName;
    }

    unsigned HumidifierSteamElectric_Impl::outletPort() const {
      return openstudio::Humidifier_Steam_ElectricFields::AirOutletNodeName;
    }

    bool HumidifierSteamElectric_Impl::addToNode(Node& node) {
      if (node.airLoopHVACOutdoorAirSystem()) {
        return StraightComponent_Impl::addToNode(node);
      }

      auto airLoop = node.airLoopHVAC();

      // This family is intentionally limited to air-loop supply placement unless it is being
      // inserted onto an OA-system outboard stream node through the shared straight-component path.
      if (!(airLoop && airLoop->supplyComponent(node.handle()))) {
        return false;
      }

      return StraightComponent_Impl::addToNode(node);
    }

    boost::optional<Schedule> HumidifierSteamElectric_Impl::availabilitySchedule() const {
      return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Humidifier_Steam_ElectricFields::AvailabilityScheduleName);
    }

    bool HumidifierSteamElectric_Impl::setAvailabilitySchedule(Schedule& schedule) {
      return ModelObject_Impl::setSchedule(openstudio::Humidifier_Steam_ElectricFields::AvailabilityScheduleName, "HumidifierSteamElectric",
                                           "Availability", schedule);
    }

    void HumidifierSteamElectric_Impl::resetAvailabilitySchedule() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::AvailabilityScheduleName, ""));
    }

    boost::optional<double> HumidifierSteamElectric_Impl::ratedCapacity() const {
      return getDouble(openstudio::Humidifier_Steam_ElectricFields::RatedCapacity, true);
    }

    bool HumidifierSteamElectric_Impl::isRatedCapacityAutosized() const {
      if (auto value = getString(openstudio::Humidifier_Steam_ElectricFields::RatedCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> HumidifierSteamElectric_Impl::ratedPower() const {
      return getDouble(openstudio::Humidifier_Steam_ElectricFields::RatedPower, true);
    }

    bool HumidifierSteamElectric_Impl::isRatedPowerAutosized() const {
      if (auto value = getString(openstudio::Humidifier_Steam_ElectricFields::RatedPower, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    boost::optional<double> HumidifierSteamElectric_Impl::ratedFanPower() const {
      return getDouble(openstudio::Humidifier_Steam_ElectricFields::RatedFanPower, true);
    }

    boost::optional<double> HumidifierSteamElectric_Impl::standbyPower() const {
      return getDouble(openstudio::Humidifier_Steam_ElectricFields::StandbyPower, true);
    }

    bool HumidifierSteamElectric_Impl::setRatedCapacity(double ratedCapacity) {
      return setDouble(openstudio::Humidifier_Steam_ElectricFields::RatedCapacity, ratedCapacity);
    }

    void HumidifierSteamElectric_Impl::autosizeRatedCapacity() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::RatedCapacity, "Autosize"));
    }

    bool HumidifierSteamElectric_Impl::setRatedPower(double ratedPower) {
      return setDouble(openstudio::Humidifier_Steam_ElectricFields::RatedPower, ratedPower);
    }

    void HumidifierSteamElectric_Impl::resetRatedPower() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::RatedPower, ""));
    }

    void HumidifierSteamElectric_Impl::autosizeRatedPower() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::RatedPower, "Autosize"));
    }

    bool HumidifierSteamElectric_Impl::setRatedFanPower(double ratedFanPower) {
      return setDouble(openstudio::Humidifier_Steam_ElectricFields::RatedFanPower, ratedFanPower);
    }

    void HumidifierSteamElectric_Impl::resetRatedFanPower() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::RatedFanPower, ""));
    }

    bool HumidifierSteamElectric_Impl::setStandbyPower(double standbyPower) {
      return setDouble(openstudio::Humidifier_Steam_ElectricFields::StandbyPower, standbyPower);
    }

    void HumidifierSteamElectric_Impl::resetStandbyPower() {
      OS_ASSERT(setString(openstudio::Humidifier_Steam_ElectricFields::StandbyPower, ""));
    }

    boost::optional<double> HumidifierSteamElectric_Impl::autosizedRatedCapacity() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

    boost::optional<double> HumidifierSteamElectric_Impl::autosizedRatedPower() const {
      // epmodel does not currently resolve autosized values from SQL results.
      return boost::none;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
