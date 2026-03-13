/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplateZoneBaseboardHeat.hpp"
#include "HVACTemplateZoneBaseboardHeat_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Zone_BaseboardHeat_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplateZoneBaseboardHeat::HVACTemplateZoneBaseboardHeat(const Model& model)
    : ModelObject(HVACTemplateZoneBaseboardHeat::iddObjectType(), model) {}

  HVACTemplateZoneBaseboardHeat::HVACTemplateZoneBaseboardHeat(std::shared_ptr<detail::HVACTemplateZoneBaseboardHeat_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplateZoneBaseboardHeat::iddObjectType() {
    return IddObjectType::HVACTemplate_Zone_BaseboardHeat;
  }

  std::vector<std::string> HVACTemplateZoneBaseboardHeat::baseboardHeatingTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType);
  }

  std::vector<std::string> HVACTemplateZoneBaseboardHeat::outdoorAirMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod);
  }

  boost::optional<double> HVACTemplateZoneBaseboardHeat::zoneHeatingSizingFactor() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->zoneHeatingSizingFactor();
  }

  bool HVACTemplateZoneBaseboardHeat::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setZoneHeatingSizingFactor(zoneHeatingSizingFactor);
  }

  void HVACTemplateZoneBaseboardHeat::resetZoneHeatingSizingFactor() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetZoneHeatingSizingFactor();
  }

  std::string HVACTemplateZoneBaseboardHeat::baseboardHeatingType() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->baseboardHeatingType();
  }

  bool HVACTemplateZoneBaseboardHeat::isBaseboardHeatingTypeDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isBaseboardHeatingTypeDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setBaseboardHeatingType(baseboardHeatingType);
  }

  void HVACTemplateZoneBaseboardHeat::resetBaseboardHeatingType() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetBaseboardHeatingType();
  }

  boost::optional<double> HVACTemplateZoneBaseboardHeat::baseboardHeatingCapacity() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->baseboardHeatingCapacity();
  }

  bool HVACTemplateZoneBaseboardHeat::isBaseboardHeatingCapacityDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isBaseboardHeatingCapacityDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::isBaseboardHeatingCapacityAutosized() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isBaseboardHeatingCapacityAutosized();
  }

  bool HVACTemplateZoneBaseboardHeat::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setBaseboardHeatingCapacity(baseboardHeatingCapacity);
  }

  void HVACTemplateZoneBaseboardHeat::resetBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetBaseboardHeatingCapacity();
  }

  void HVACTemplateZoneBaseboardHeat::autosizeBaseboardHeatingCapacity() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->autosizeBaseboardHeatingCapacity();
  }

  std::string HVACTemplateZoneBaseboardHeat::outdoorAirMethod() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->outdoorAirMethod();
  }

  bool HVACTemplateZoneBaseboardHeat::isOutdoorAirMethodDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isOutdoorAirMethodDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setOutdoorAirMethod(outdoorAirMethod);
  }

  void HVACTemplateZoneBaseboardHeat::resetOutdoorAirMethod() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetOutdoorAirMethod();
  }

  double HVACTemplateZoneBaseboardHeat::outdoorAirFlowRateperPerson() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->outdoorAirFlowRateperPerson();
  }

  bool HVACTemplateZoneBaseboardHeat::isOutdoorAirFlowRateperPersonDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isOutdoorAirFlowRateperPersonDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setOutdoorAirFlowRateperPerson(outdoorAirFlowRateperPerson);
  }

  void HVACTemplateZoneBaseboardHeat::resetOutdoorAirFlowRateperPerson() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetOutdoorAirFlowRateperPerson();
  }

  double HVACTemplateZoneBaseboardHeat::outdoorAirFlowRateperZoneFloorArea() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->outdoorAirFlowRateperZoneFloorArea();
  }

  bool HVACTemplateZoneBaseboardHeat::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isOutdoorAirFlowRateperZoneFloorAreaDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setOutdoorAirFlowRateperZoneFloorArea(outdoorAirFlowRateperZoneFloorArea);
  }

  void HVACTemplateZoneBaseboardHeat::resetOutdoorAirFlowRateperZoneFloorArea() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetOutdoorAirFlowRateperZoneFloorArea();
  }

  double HVACTemplateZoneBaseboardHeat::outdoorAirFlowRateperZone() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->outdoorAirFlowRateperZone();
  }

  bool HVACTemplateZoneBaseboardHeat::isOutdoorAirFlowRateperZoneDefaulted() const {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->isOutdoorAirFlowRateperZoneDefaulted();
  }

  bool HVACTemplateZoneBaseboardHeat::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
    return getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->setOutdoorAirFlowRateperZone(outdoorAirFlowRateperZone);
  }

  void HVACTemplateZoneBaseboardHeat::resetOutdoorAirFlowRateperZone() {
    getImpl<detail::HVACTemplateZoneBaseboardHeat_Impl>()->resetOutdoorAirFlowRateperZone();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> HVACTemplateZoneBaseboardHeat_Impl::zoneHeatingSizingFactor() const {
      return getDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::ZoneHeatingSizingFactor, true);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setZoneHeatingSizingFactor(double zoneHeatingSizingFactor) {
      return setDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::ZoneHeatingSizingFactor, zoneHeatingSizingFactor);
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetZoneHeatingSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::ZoneHeatingSizingFactor, ""));
    }

    std::string HVACTemplateZoneBaseboardHeat_Impl::baseboardHeatingType() const {
      auto value = getString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isBaseboardHeatingTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setBaseboardHeatingType(const std::string& baseboardHeatingType) {
      return setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType, baseboardHeatingType);
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetBaseboardHeatingType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType, ""));
    }

    boost::optional<double> HVACTemplateZoneBaseboardHeat_Impl::baseboardHeatingCapacity() const {
      return getDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, true);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isBaseboardHeatingCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isBaseboardHeatingCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setBaseboardHeatingCapacity(double baseboardHeatingCapacity) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, baseboardHeatingCapacity);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, ""));
    }

    void HVACTemplateZoneBaseboardHeat_Impl::autosizeBaseboardHeatingCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, "autosize"));
    }

    std::string HVACTemplateZoneBaseboardHeat_Impl::outdoorAirMethod() const {
      auto value = getString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isOutdoorAirMethodDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setOutdoorAirMethod(const std::string& outdoorAirMethod) {
      return setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod, outdoorAirMethod);
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetOutdoorAirMethod() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod, ""));
    }

    double HVACTemplateZoneBaseboardHeat_Impl::outdoorAirFlowRateperPerson() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperPerson, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isOutdoorAirFlowRateperPersonDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperPerson);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperPerson, outdoorAirFlowRateperPerson);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetOutdoorAirFlowRateperPerson() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperPerson, ""));
    }

    double HVACTemplateZoneBaseboardHeat_Impl::outdoorAirFlowRateperZoneFloorArea() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZoneFloorArea, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZoneFloorArea);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZoneFloorArea, outdoorAirFlowRateperZoneFloorArea);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetOutdoorAirFlowRateperZoneFloorArea() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZoneFloorArea, ""));
    }

    double HVACTemplateZoneBaseboardHeat_Impl::outdoorAirFlowRateperZone() const {
      auto value = getDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZone, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::isOutdoorAirFlowRateperZoneDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZone);
    }

    bool HVACTemplateZoneBaseboardHeat_Impl::setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone) {
      const bool result = setDouble(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZone, outdoorAirFlowRateperZone);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplateZoneBaseboardHeat_Impl::resetOutdoorAirFlowRateperZone() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZone, ""));
    }

    std::vector<std::string> HVACTemplateZoneBaseboardHeat_Impl::baseboardHeatingTypeValues() const {
      return openstudio::epmodel::HVACTemplateZoneBaseboardHeat::baseboardHeatingTypeValues();
    }

    std::vector<std::string> HVACTemplateZoneBaseboardHeat_Impl::outdoorAirMethodValues() const {
      return openstudio::epmodel::HVACTemplateZoneBaseboardHeat::outdoorAirMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
