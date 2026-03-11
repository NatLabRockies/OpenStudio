/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign.hpp"
#include "ZoneHVACComponent/ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_Baseboard_RadiantConvective_Water_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACBaseboardRadiantConvectiveWaterDesign::ZoneHVACBaseboardRadiantConvectiveWaterDesign(const Model& model)
    : ModelObject(ZoneHVACBaseboardRadiantConvectiveWaterDesign::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>());

    OS_ASSERT(setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
    OS_ASSERT(setFractionofAutosizedHeatingDesignCapacity(1.0));
    OS_ASSERT(setConvergenceTolerance(0.001));
    OS_ASSERT(setFractionRadiant(0.2));
    OS_ASSERT(setFractionofRadiantEnergyIncidentonPeople(0.3));
  }

  ZoneHVACBaseboardRadiantConvectiveWaterDesign::ZoneHVACBaseboardRadiantConvectiveWaterDesign(
    std::shared_ptr<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACBaseboardRadiantConvectiveWaterDesign::iddObjectType() {
    return IddObjectType::ZoneHVAC_Baseboard_RadiantConvective_Water_Design;
  }

  std::vector<std::string> ZoneHVACBaseboardRadiantConvectiveWaterDesign::heatingDesignCapacityMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityMethod);
  }

  std::string ZoneHVACBaseboardRadiantConvectiveWaterDesign::heatingDesignCapacityMethod() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->heatingDesignCapacityMethod();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setHeatingDesignCapacityMethod(heatingDesignCapacityMethod);
  }

  void ZoneHVACBaseboardRadiantConvectiveWaterDesign::resetHeatingDesignCapacityMethod() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->resetHeatingDesignCapacityMethod();
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWaterDesign::heatingDesignCapacityPerFloorArea() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->heatingDesignCapacityPerFloorArea();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setHeatingDesignCapacityPerFloorArea(
      heatingDesignCapacityPerFloorArea);
  }

  void ZoneHVACBaseboardRadiantConvectiveWaterDesign::resetHeatingDesignCapacityPerFloorArea() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->resetHeatingDesignCapacityPerFloorArea();
  }

  double ZoneHVACBaseboardRadiantConvectiveWaterDesign::fractionofAutosizedHeatingDesignCapacity() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->fractionofAutosizedHeatingDesignCapacity();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->isFractionofAutosizedHeatingDesignCapacityDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setFractionofAutosizedHeatingDesignCapacity(
      fractionofAutosizedHeatingDesignCapacity);
  }

  void ZoneHVACBaseboardRadiantConvectiveWaterDesign::resetFractionofAutosizedHeatingDesignCapacity() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->resetFractionofAutosizedHeatingDesignCapacity();
  }

  double ZoneHVACBaseboardRadiantConvectiveWaterDesign::convergenceTolerance() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->convergenceTolerance();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::isConvergenceToleranceDefaulted() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->isConvergenceToleranceDefaulted();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setConvergenceTolerance(double convergenceTolerance) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setConvergenceTolerance(convergenceTolerance);
  }

  void ZoneHVACBaseboardRadiantConvectiveWaterDesign::resetConvergenceTolerance() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->resetConvergenceTolerance();
  }

  double ZoneHVACBaseboardRadiantConvectiveWaterDesign::fractionRadiant() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->fractionRadiant();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setFractionRadiant(double fractionRadiant) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setFractionRadiant(fractionRadiant);
  }

  boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWaterDesign::fractionofRadiantEnergyIncidentonPeople() const {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->fractionofRadiantEnergyIncidentonPeople();
  }

  bool ZoneHVACBaseboardRadiantConvectiveWaterDesign::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
    return getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->setFractionofRadiantEnergyIncidentonPeople(
      fractionofRadiantEnergyIncidentonPeople);
  }

  void ZoneHVACBaseboardRadiantConvectiveWaterDesign::resetFractionofRadiantEnergyIncidentonPeople() {
    getImpl<detail::ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl>()->resetFractionofRadiantEnergyIncidentonPeople();
  }

  namespace detail {

    std::string ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::heatingDesignCapacityMethod() const {
      boost::optional<std::string> value = getString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityMethod, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setHeatingDesignCapacityMethod(const std::string& heatingDesignCapacityMethod) {
      const bool result =
        setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityMethod, heatingDesignCapacityMethod);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::resetHeatingDesignCapacityMethod() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityMethod, ""));
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::heatingDesignCapacityPerFloorArea() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityPerFloorArea, true);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea) {
      const bool result =
        setDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityPerFloorArea, heatingDesignCapacityPerFloorArea);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::resetHeatingDesignCapacityPerFloorArea() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::HeatingDesignCapacityPerFloorArea, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::fractionofAutosizedHeatingDesignCapacity() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofAutosizedHeatingDesignCapacity, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::isFractionofAutosizedHeatingDesignCapacityDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofAutosizedHeatingDesignCapacity);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setFractionofAutosizedHeatingDesignCapacity(
      double fractionofAutosizedHeatingDesignCapacity) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofAutosizedHeatingDesignCapacity,
                                    fractionofAutosizedHeatingDesignCapacity);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::resetFractionofAutosizedHeatingDesignCapacity() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofAutosizedHeatingDesignCapacity, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::convergenceTolerance() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::ConvergenceTolerance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::isConvergenceToleranceDefaulted() const {
      return isEmpty(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::ConvergenceTolerance);
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setConvergenceTolerance(double convergenceTolerance) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::ConvergenceTolerance, convergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::resetConvergenceTolerance() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::ConvergenceTolerance, ""));
    }

    double ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::fractionRadiant() const {
      auto value = getDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionRadiant, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setFractionRadiant(double fractionRadiant) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionRadiant, fractionRadiant);
      OS_ASSERT(result);
      return result;
    }

    boost::optional<double> ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::fractionofRadiantEnergyIncidentonPeople() const {
      return getDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofRadiantEnergyIncidentonPeople, true);
    }

    bool
      ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::setFractionofRadiantEnergyIncidentonPeople(double fractionofRadiantEnergyIncidentonPeople) {
      const bool result = setDouble(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofRadiantEnergyIncidentonPeople,
                                    fractionofRadiantEnergyIncidentonPeople);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACBaseboardRadiantConvectiveWaterDesign_Impl::resetFractionofRadiantEnergyIncidentonPeople() {
      OS_ASSERT(setString(ZoneHVAC_Baseboard_RadiantConvective_Water_DesignFields::FractionofRadiantEnergyIncidentonPeople, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
