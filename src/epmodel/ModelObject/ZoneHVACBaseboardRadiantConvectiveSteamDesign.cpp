/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/ZoneHVACBaseboardRadiantConvectiveSteamDesign.hpp"
#include "ModelObject/ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Steam_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardRadiantConvectiveSteamDesign::ZoneHVACBaseboardRadiantConvectiveSteamDesign(const Model& model)
    : ModelObject(ZoneHVACBaseboardRadiantConvectiveSteamDesign::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>());

    OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
    OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(1.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setFractionRadiant(0.2));
    OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(0.3));
  }

  ZoneHVACBaseboardRadiantConvectiveSteamDesign::ZoneHVACBaseboardRadiantConvectiveSteamDesign(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveSteamDesign::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Steam_Design;
  }

  std::vector<std::string> ZoneHVACBaseboardRadiantConvectiveSteamDesign::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityMethod);
  }

  std::string ZoneHVACBaseboardRadiantConvectiveSteamDesign::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteamDesign::resetHeatingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->resetHeatingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteamDesign::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setHeatingDesignCapacityPerFloorArea(
      heatingDesignCapacityPerFloorArea);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteamDesign::resetHeatingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->resetHeatingDesignCapacityPerFloorArea();
  }

  double ZoneHVACBaseboardRadiantConvectiveSteamDesign::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteamDesign::resetFractionofAutosizedHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
  }

  double ZoneHVACBaseboardRadiantConvectiveSteamDesign::convergenceTolerance() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->convergenceTolerance();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteamDesign::resetConvergenceTolerance() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->resetConvergenceTolerance();
  }

  double ZoneHVACBaseboardRadiantConvectiveSteamDesign::fractionRadiant() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->fractionRadiant();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setFractionRadiant(fractionRadiant);
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteamDesign::fractionofRadiantEnergyIncidentonPeople() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->fractionofRadiantEnergyIncidentonPeople();
  }

  bool ZoneHVACBaseboardRadiantConvectiveSteamDesign::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
      fractionofRadiantEnergyIncidentonPeople);
  }

  void ZoneHVACBaseboardRadiantConvectiveSteamDesign::resetFractionofRadiantEnergyIncidentonPeople() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl>()->resetFractionofRadiantEnergyIncidentonPeople();
  }

  namespace detail {

    std::string ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::heatingDesignCapacityMethod() const {
      boost::optional<std::string> value = getString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      const bool result =
        setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::resetHeatingDesignCapacityMethod() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityMethod, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::heatingDesignCapacityPerFloorArea() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityPerFloorArea, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      const bool result =
        setDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::resetHeatingDesignCapacityPerFloorArea() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::HeatingDesignCapacityPerFloorArea, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofAutosizedHeatingDesignCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofAutosizedHeatingDesignCapacity);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setFractionofAutosizedHeatingDesignCapacity(
      double fractionofAutosizedHeatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofAutosizedHeatingDesignCapacity,
                                    fractionofAutosizedHeatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofAutosizedHeatingDesignCapacity, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::convergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::ConvergenceTolerance);
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setConvergenceTolerance(double convergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::ConvergenceTolerance, convergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::ConvergenceTolerance, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::fractionRadiant() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionRadiant, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setFractionRadiant(double fractionRadiant) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionRadiant, fractionRadiant);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::fractionofRadiantEnergyIncidentonPeople() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofRadiantEnergyIncidentonPeople, true);
    }

    bool
      ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofRadiantEnergyIncidentonPeople,
                                    fractionofRadiantEnergyIncidentonPeople);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveSteamDesign_Impl::resetFractionofRadiantEnergyIncidentonPeople() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Steam_DesignFields::FractionofRadiantEnergyIncidentonPeople, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
