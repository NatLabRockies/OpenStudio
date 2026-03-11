/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ModelObject/RefrigerationWalkIn.hpp"
#include "ModelObject/RefrigerationWalkIn_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_WalkIn_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RefrigerationWalkIn::RefrigerationWalkIn(const Model& model) : ModelObject(RefrigerationWalkIn::iddObjectType(), model) {
    OS_ASSERT(setRatedCoilCoolingCapacity(4690.0));
    OS_ASSERT(setOperatingTemperature(-2.22));
    OS_ASSERT(setRatedCoolingSourceTemperature(-6.67));
    OS_ASSERT(setRatedTotalHeatingPower(0.0));
    OS_ASSERT(setRatedCoolingCoilFanPower(735.0));
    OS_ASSERT(setRatedCirculationFanPower(0.0));
    OS_ASSERT(setRatedTotalLightingPower(120.0));
    OS_ASSERT(setDefrostType("Electric"));
    OS_ASSERT(setDefrostControlType("TimeSchedule"));
    OS_ASSERT(setDefrostPower(5512.0));
    OS_ASSERT(setInsulatedFloorSurfaceArea(13.0));
    OS_ASSERT(setInsulatedFloorUValue(0.207));
  }

  RefrigerationWalkIn::RefrigerationWalkIn(std::shared_ptr<detail::RefrigerationWalkIn_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RefrigerationWalkIn::iddObjectType() {
    return IddObjectType::Refrigeration_WalkIn;
  }

  std::vector<std::string> RefrigerationWalkIn::defrostTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Refrigeration_WalkInFields::DefrostType);
  }

  std::vector<std::string> RefrigerationWalkIn::defrostControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Refrigeration_WalkInFields::DefrostControlType);
  }

  double RefrigerationWalkIn::ratedCoilCoolingCapacity() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoilCoolingCapacity();
  }

  bool RefrigerationWalkIn::setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoilCoolingCapacity(ratedCoilCoolingCapacity);
  }

  double RefrigerationWalkIn::operatingTemperature() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->operatingTemperature();
  }

  bool RefrigerationWalkIn::setOperatingTemperature(double operatingTemperature) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setOperatingTemperature(operatingTemperature);
  }

  double RefrigerationWalkIn::ratedCoolingSourceTemperature() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoolingSourceTemperature();
  }

  bool RefrigerationWalkIn::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoolingSourceTemperature(ratedCoolingSourceTemperature);
  }

  double RefrigerationWalkIn::ratedTotalHeatingPower() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedTotalHeatingPower();
  }

  bool RefrigerationWalkIn::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedTotalHeatingPower(ratedTotalHeatingPower);
  }

  double RefrigerationWalkIn::ratedCoolingCoilFanPower() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCoolingCoilFanPower();
  }

  bool RefrigerationWalkIn::setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCoolingCoilFanPower(ratedCoolingCoilFanPower);
  }

  bool RefrigerationWalkIn::isRatedCoolingCoilFanPowerDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isRatedCoolingCoilFanPowerDefaulted();
  }

  void RefrigerationWalkIn::resetRatedCoolingCoilFanPower() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetRatedCoolingCoilFanPower();
  }

  double RefrigerationWalkIn::ratedCirculationFanPower() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedCirculationFanPower();
  }

  bool RefrigerationWalkIn::setRatedCirculationFanPower(double ratedCirculationFanPower) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedCirculationFanPower(ratedCirculationFanPower);
  }

  bool RefrigerationWalkIn::isRatedCirculationFanPowerDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isRatedCirculationFanPowerDefaulted();
  }

  void RefrigerationWalkIn::resetRatedCirculationFanPower() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetRatedCirculationFanPower();
  }

  double RefrigerationWalkIn::ratedTotalLightingPower() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->ratedTotalLightingPower();
  }

  bool RefrigerationWalkIn::setRatedTotalLightingPower(double ratedTotalLightingPower) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setRatedTotalLightingPower(ratedTotalLightingPower);
  }

  std::string RefrigerationWalkIn::defrostType() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostType();
  }

  bool RefrigerationWalkIn::setDefrostType(const std::string& defrostType) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostType(defrostType);
  }

  bool RefrigerationWalkIn::isDefrostTypeDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isDefrostTypeDefaulted();
  }

  void RefrigerationWalkIn::resetDefrostType() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostType();
  }

  std::string RefrigerationWalkIn::defrostControlType() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostControlType();
  }

  bool RefrigerationWalkIn::setDefrostControlType(const std::string& defrostControlType) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostControlType(defrostControlType);
  }

  bool RefrigerationWalkIn::isDefrostControlTypeDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isDefrostControlTypeDefaulted();
  }

  void RefrigerationWalkIn::resetDefrostControlType() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostControlType();
  }

  boost::optional<double> RefrigerationWalkIn::defrostPower() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->defrostPower();
  }

  bool RefrigerationWalkIn::setDefrostPower(double defrostPower) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setDefrostPower(defrostPower);
  }

  void RefrigerationWalkIn::resetDefrostPower() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetDefrostPower();
  }

  boost::optional<double> RefrigerationWalkIn::temperatureTerminationDefrostFractiontoIce() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->temperatureTerminationDefrostFractiontoIce();
  }

  bool RefrigerationWalkIn::setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setTemperatureTerminationDefrostFractiontoIce(temperatureTerminationDefrostFractiontoIce);
  }

  void RefrigerationWalkIn::resetTemperatureTerminationDefrostFractiontoIce() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetTemperatureTerminationDefrostFractiontoIce();
  }

  double RefrigerationWalkIn::averageRefrigerantChargeInventory() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->averageRefrigerantChargeInventory();
  }

  bool RefrigerationWalkIn::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setAverageRefrigerantChargeInventory(averageRefrigerantChargeInventory);
  }

  bool RefrigerationWalkIn::isAverageRefrigerantChargeInventoryDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isAverageRefrigerantChargeInventoryDefaulted();
  }

  void RefrigerationWalkIn::resetAverageRefrigerantChargeInventory() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetAverageRefrigerantChargeInventory();
  }

  double RefrigerationWalkIn::insulatedFloorSurfaceArea() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->insulatedFloorSurfaceArea();
  }

  bool RefrigerationWalkIn::setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setInsulatedFloorSurfaceArea(insulatedFloorSurfaceArea);
  }

  double RefrigerationWalkIn::insulatedFloorUValue() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->insulatedFloorUValue();
  }

  bool RefrigerationWalkIn::setInsulatedFloorUValue(double insulatedFloorUValue) {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->setInsulatedFloorUValue(insulatedFloorUValue);
  }

  bool RefrigerationWalkIn::isInsulatedFloorUValueDefaulted() const {
    return getImpl<detail::RefrigerationWalkIn_Impl>()->isInsulatedFloorUValueDefaulted();
  }

  void RefrigerationWalkIn::resetInsulatedFloorUValue() {
    getImpl<detail::RefrigerationWalkIn_Impl>()->resetInsulatedFloorUValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double RefrigerationWalkIn_Impl::ratedCoilCoolingCapacity() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedCoilCoolingCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedCoilCoolingCapacity(double ratedCoilCoolingCapacity) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedCoilCoolingCapacity, ratedCoilCoolingCapacity);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationWalkIn_Impl::operatingTemperature() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::OperatingTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setOperatingTemperature(double operatingTemperature) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::OperatingTemperature, operatingTemperature);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationWalkIn_Impl::ratedCoolingSourceTemperature() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedCoolingSourceTemperature, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedCoolingSourceTemperature(double ratedCoolingSourceTemperature) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedCoolingSourceTemperature, ratedCoolingSourceTemperature);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationWalkIn_Impl::ratedTotalHeatingPower() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedTotalHeatingPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedTotalHeatingPower(double ratedTotalHeatingPower) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedTotalHeatingPower, ratedTotalHeatingPower);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationWalkIn_Impl::ratedCoolingCoilFanPower() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedCoolingCoilFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedCoolingCoilFanPower(double ratedCoolingCoilFanPower) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedCoolingCoilFanPower, ratedCoolingCoilFanPower);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isRatedCoolingCoilFanPowerDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::RatedCoolingCoilFanPower);
    }

    void RefrigerationWalkIn_Impl::resetRatedCoolingCoilFanPower() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::RatedCoolingCoilFanPower, "");
      OS_ASSERT(result);
    }

    double RefrigerationWalkIn_Impl::ratedCirculationFanPower() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedCirculationFanPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedCirculationFanPower(double ratedCirculationFanPower) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedCirculationFanPower, ratedCirculationFanPower);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isRatedCirculationFanPowerDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::RatedCirculationFanPower);
    }

    void RefrigerationWalkIn_Impl::resetRatedCirculationFanPower() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::RatedCirculationFanPower, "");
      OS_ASSERT(result);
    }

    double RefrigerationWalkIn_Impl::ratedTotalLightingPower() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::RatedTotalLightingPower, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setRatedTotalLightingPower(double ratedTotalLightingPower) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::RatedTotalLightingPower, ratedTotalLightingPower);
      OS_ASSERT(result);
      return result;
    }

    std::string RefrigerationWalkIn_Impl::defrostType() const {
      auto value = getString(openstudio::Refrigeration_WalkInFields::DefrostType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setDefrostType(const std::string& defrostType) {
      bool result = setString(openstudio::Refrigeration_WalkInFields::DefrostType, defrostType);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isDefrostTypeDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::DefrostType);
    }

    void RefrigerationWalkIn_Impl::resetDefrostType() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::DefrostType, "");
      OS_ASSERT(result);
    }

    std::string RefrigerationWalkIn_Impl::defrostControlType() const {
      auto value = getString(openstudio::Refrigeration_WalkInFields::DefrostControlType, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setDefrostControlType(const std::string& defrostControlType) {
      bool result = setString(openstudio::Refrigeration_WalkInFields::DefrostControlType, defrostControlType);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isDefrostControlTypeDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::DefrostControlType);
    }

    void RefrigerationWalkIn_Impl::resetDefrostControlType() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::DefrostControlType, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationWalkIn_Impl::defrostPower() const {
      return getDouble(openstudio::Refrigeration_WalkInFields::DefrostPower, true);
    }

    bool RefrigerationWalkIn_Impl::setDefrostPower(double defrostPower) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::DefrostPower, defrostPower);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationWalkIn_Impl::resetDefrostPower() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::DefrostPower, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RefrigerationWalkIn_Impl::temperatureTerminationDefrostFractiontoIce() const {
      return getDouble(openstudio::Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, true);
    }

    bool RefrigerationWalkIn_Impl::setTemperatureTerminationDefrostFractiontoIce(double temperatureTerminationDefrostFractiontoIce) {
      bool result =
        setDouble(openstudio::Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, temperatureTerminationDefrostFractiontoIce);
      OS_ASSERT(result);
      return result;
    }

    void RefrigerationWalkIn_Impl::resetTemperatureTerminationDefrostFractiontoIce() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::TemperatureTerminationDefrostFractiontoIce, "");
      OS_ASSERT(result);
    }

    double RefrigerationWalkIn_Impl::averageRefrigerantChargeInventory() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setAverageRefrigerantChargeInventory(double averageRefrigerantChargeInventory) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, averageRefrigerantChargeInventory);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isAverageRefrigerantChargeInventoryDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::AverageRefrigerantChargeInventory);
    }

    void RefrigerationWalkIn_Impl::resetAverageRefrigerantChargeInventory() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::AverageRefrigerantChargeInventory, "");
      OS_ASSERT(result);
    }

    double RefrigerationWalkIn_Impl::insulatedFloorSurfaceArea() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::InsulatedFloorSurfaceArea, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setInsulatedFloorSurfaceArea(double insulatedFloorSurfaceArea) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::InsulatedFloorSurfaceArea, insulatedFloorSurfaceArea);
      OS_ASSERT(result);
      return result;
    }

    double RefrigerationWalkIn_Impl::insulatedFloorUValue() const {
      auto value = getDouble(openstudio::Refrigeration_WalkInFields::InsulatedFloorUValue, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool RefrigerationWalkIn_Impl::setInsulatedFloorUValue(double insulatedFloorUValue) {
      bool result = setDouble(openstudio::Refrigeration_WalkInFields::InsulatedFloorUValue, insulatedFloorUValue);
      OS_ASSERT(result);
      return result;
    }

    bool RefrigerationWalkIn_Impl::isInsulatedFloorUValueDefaulted() const {
      return isEmpty(openstudio::Refrigeration_WalkInFields::InsulatedFloorUValue);
    }

    void RefrigerationWalkIn_Impl::resetInsulatedFloorUValue() {
      bool result = setString(openstudio::Refrigeration_WalkInFields::InsulatedFloorUValue, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
