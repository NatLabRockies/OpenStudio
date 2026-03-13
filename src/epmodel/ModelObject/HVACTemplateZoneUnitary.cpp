/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneUnitary.hpp"
#include "HVACTemplateZoneUnitary_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_Unitary_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateZoneUnitary::HVACTemplateZoneUnitary(const Model& model) : ModelObject(HVACTemplateZoneUnitary::iddObjectType(), model) {}

  HVACTemplateZoneUnitary::HVACTemplateZoneUnitary(std::shared_ptr<detail::HVACTemplateZoneUnitary_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateZoneUnitary::iddObjectType() {
    return IddObjectType::HVACTemplate_Zone_Unitary;
  }

  std::vector<std::string> HVACTemplateZoneUnitary::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod);
  }

  std::vector<std::string> HVACTemplateZoneUnitary::baseboardHeatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType);
  }

  std::vector<std::string> HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  std::vector<std::string> HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  boost::optional<double> HVACTemplateZoneUnitary::supplyAirMaximumFlowRate() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->supplyAirMaximumFlowRate();
  }

  bool HVACTemplateZoneUnitary::isSupplyAirMaximumFlowRateDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isSupplyAirMaximumFlowRateDefaulted();
  }

  bool HVACTemplateZoneUnitary::isSupplyAirMaximumFlowRateAutosized() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isSupplyAirMaximumFlowRateAutosized();
  }

  bool HVACTemplateZoneUnitary::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setSupplyAirMaximumFlowRate(supplyAirMaximumFlowRate);
  }

  void HVACTemplateZoneUnitary::resetSupplyAirMaximumFlowRate() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetSupplyAirMaximumFlowRate();
  }

  void HVACTemplateZoneUnitary::autosizeSupplyAirMaximumFlowRate() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->autosizeSupplyAirMaximumFlowRate();
  }

  boost::optional<double> HVACTemplateZoneUnitary::zoneHeatingSizingFactor() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingSizingFactor();
  }

  bool HVACTemplateZoneUnitary::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
  }

  void HVACTemplateZoneUnitary::resetZoneHeatingSizingFactor() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingSizingFactor();
  }

  boost::optional<double> HVACTemplateZoneUnitary::zoneCoolingSizingFactor() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingSizingFactor();
  }

  bool HVACTemplateZoneUnitary::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingSizingFactor(zoneCoolingSizingFactor);
  }

  void HVACTemplateZoneUnitary::resetZoneCoolingSizingFactor() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingSizingFactor();
  }

  std::string HVACTemplateZoneUnitary::outdoorAirMethod() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirMethod();
  }

  bool HVACTemplateZoneUnitary::isOutdoorAirMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirMethodDefaulted();
  }

  bool HVACTemplateZoneUnitary::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
  }

  void HVACTemplateZoneUnitary::resetOutdoorAirMethod() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirMethod();
  }

  double HVACTemplateZoneUnitary::outdoorAirFlowRateperPerson() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperPerson();
  }

  bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperPersonDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
  }

  bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
  }

  void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperPerson() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperPerson();
  }

  double HVACTemplateZoneUnitary::outdoorAirFlowRateperZoneFloorArea() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperZoneFloorArea();
  }

  bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
  }

  bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
  }

  void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperZoneFloorArea() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
  }

  double HVACTemplateZoneUnitary::outdoorAirFlowRateperZone() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->outdoorAirFlowRateperZone();
  }

  bool HVACTemplateZoneUnitary::isOutdoorAirFlowRateperZoneDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
  }

  bool HVACTemplateZoneUnitary::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
  }

  void HVACTemplateZoneUnitary::resetOutdoorAirFlowRateperZone() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetOutdoorAirFlowRateperZone();
  }

  std::string HVACTemplateZoneUnitary::baseboardHeatingType() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->baseboardHeatingType();
  }

  bool HVACTemplateZoneUnitary::isBaseboardHeatingTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingTypeDefaulted();
  }

  bool HVACTemplateZoneUnitary::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
  }

  void HVACTemplateZoneUnitary::resetBaseboardHeatingType() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetBaseboardHeatingType();
  }

  boost::optional<double> HVACTemplateZoneUnitary::baseboardHeatingCapacity() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->baseboardHeatingCapacity();
  }

  bool HVACTemplateZoneUnitary::isBaseboardHeatingCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingCapacityDefaulted();
  }

  bool HVACTemplateZoneUnitary::isBaseboardHeatingCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isBaseboardHeatingCapacityAutosized();
  }

  bool HVACTemplateZoneUnitary::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
  }

  void HVACTemplateZoneUnitary::resetBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetBaseboardHeatingCapacity();
  }

  void HVACTemplateZoneUnitary::autosizeBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->autosizeBaseboardHeatingCapacity();
  }

  std::string HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
    const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      zoneCoolingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperature(zoneCoolingDesignSupplyAirTemperature);
  }

  void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperature();
  }

  double HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneCoolingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZoneUnitary::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneCoolingDesignSupplyAirTemperatureDifference(
      zoneCoolingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZoneUnitary::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneCoolingDesignSupplyAirTemperatureDifference();
  }

  std::string HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
    const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      zoneHeatingDesignSupplyAirTemperatureInputMethod);
  }

  void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureInputMethod();
  }

  double HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperature() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperature();
  }

  bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperature(zoneHeatingDesignSupplyAirTemperature);
  }

  void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperature() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperature();
  }

  double HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureDifference() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->zoneHeatingDesignSupplyAirTemperatureDifference();
  }

  bool HVACTemplateZoneUnitary::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted();
  }

  bool HVACTemplateZoneUnitary::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
    return getImpl<detail::HVACTemplateZoneUnitary_Impl>()->setZoneHeatingDesignSupplyAirTemperatureDifference(
      zoneHeatingDesignSupplyAirTemperatureDifference);
  }

  void HVACTemplateZoneUnitary::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
    getImpl<detail::HVACTemplateZoneUnitary_Impl>()->resetZoneHeatingDesignSupplyAirTemperatureDifference();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HVACTemplateZoneUnitary_Impl::supplyAirMaximumFlowRate() const {
      return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, true);
    }

    bool HVACTemplateZoneUnitary_Impl::isSupplyAirMaximumFlowRateDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate);
    }

    bool HVACTemplateZoneUnitary_Impl::isSupplyAirMaximumFlowRateAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZoneUnitary_Impl::setSupplyAirMaximumFlowRate(double supplyAirMaximumFlowRate) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, supplyAirMaximumFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetSupplyAirMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, ""));
    }

    void HVACTemplateZoneUnitary_Impl::autosizeSupplyAirMaximumFlowRate() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::SupplyAirMaximumFlowRate, "autosize"));
    }

    boost::optional<double> HVACTemplateZoneUnitary_Impl::zoneHeatingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, true);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingSizingFactor, ""));
    }

    boost::optional<double> HVACTemplateZoneUnitary_Impl::zoneCoolingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, true);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneCoolingSizingFactor(double zoneCoolingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, zoneCoolingSizingFactor);
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneCoolingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingSizingFactor, ""));
    }

    std::string HVACTemplateZoneUnitary_Impl::outdoorAirMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isOutdoorAirMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod);
    }

    bool HVACTemplateZoneUnitary_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
      return setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, outdoorAirMethod);
    }

    void HVACTemplateZoneUnitary_Impl::resetOutdoorAirMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirMethod, ""));
    }

    double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperPerson() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson);
    }

    bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperPerson() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperPerson, ""));
    }

    double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperZoneFloorArea() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea);
    }

    bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZoneFloorArea, ""));
    }

    double HVACTemplateZoneUnitary_Impl::outdoorAirFlowRateperZone() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone);
    }

    bool HVACTemplateZoneUnitary_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetOutdoorAirFlowRateperZone() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::OutdoorAirFlowRateperZone, ""));
    }

    std::string HVACTemplateZoneUnitary_Impl::baseboardHeatingType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType);
    }

    bool HVACTemplateZoneUnitary_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
      return setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, baseboardHeatingType);
    }

    void HVACTemplateZoneUnitary_Impl::resetBaseboardHeatingType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingType, ""));
    }

    boost::optional<double> HVACTemplateZoneUnitary_Impl::baseboardHeatingCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, true);
    }

    bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity);
    }

    bool HVACTemplateZoneUnitary_Impl::isBaseboardHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZoneUnitary_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, ""));
    }

    void HVACTemplateZoneUnitary_Impl::autosizeBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::BaseboardHeatingCapacity, "autosize"));
    }

    std::string HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneCoolingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod,
                       zoneCoolingDesignSupplyAirTemperatureInputMethod);
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, ""));
    }

    double HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperature(double zoneCoolingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, zoneCoolingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperature, ""));
    }

    double HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneCoolingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneCoolingDesignSupplyAirTemperatureDifference(double zoneCoolingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference,
                                    zoneCoolingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneCoolingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneCoolingDesignSupplyAirTemperatureDifference, ""));
    }

    std::string HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureInputMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperatureInputMethod(
      const std::string& zoneHeatingDesignSupplyAirTemperatureInputMethod) {
      return setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod,
                       zoneHeatingDesignSupplyAirTemperatureInputMethod);
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperatureInputMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, ""));
    }

    double HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperature() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperature(double zoneHeatingDesignSupplyAirTemperature) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, zoneHeatingDesignSupplyAirTemperature);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperature() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperature, ""));
    }

    double HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureDifference() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneUnitary_Impl::isZoneHeatingDesignSupplyAirTemperatureDifferenceDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference);
    }

    bool HVACTemplateZoneUnitary_Impl::setZoneHeatingDesignSupplyAirTemperatureDifference(double zoneHeatingDesignSupplyAirTemperatureDifference) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference,
                                    zoneHeatingDesignSupplyAirTemperatureDifference);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneUnitary_Impl::resetZoneHeatingDesignSupplyAirTemperatureDifference() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_UnitaryFields::ZoneHeatingDesignSupplyAirTemperatureDifference, ""));
    }

    std::vector<std::string> HVACTemplateZoneUnitary_Impl::outdoorAirMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneUnitary::outdoorAirMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneUnitary_Impl::baseboardHeatingTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneUnitary::baseboardHeatingTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneUnitary_Impl::zoneCoolingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneUnitary::zoneCoolingDesignSupplyAirTemperatureInputMethodValues();
    }

    std::vector<std::string> HVACTemplateZoneUnitary_Impl::zoneHeatingDesignSupplyAirTemperatureInputMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneUnitary::zoneHeatingDesignSupplyAirTemperatureInputMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
