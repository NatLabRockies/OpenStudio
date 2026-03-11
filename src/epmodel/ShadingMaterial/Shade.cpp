/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "Shade.hpp"
#include "Shade_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_Shade_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  Shade::Shade(const Model& model) : ModelObject(Shade::iddObjectType(), model) {}

  Shade::Shade(std::shared_ptr<detail::Shade_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType Shade::iddObjectType() {
    return IddObjectType::WindowMaterial_Shade;
  }

  double Shade::thermalConductivity() const {
    return getImpl<detail::Shade_Impl>()->thermalConductivity();
  }

  double Shade::thermalConductance() const {
    return getImpl<detail::Shade_Impl>()->thermalConductance();
  }

  double Shade::thermalResistivity() const {
    return getImpl<detail::Shade_Impl>()->thermalResistivity();
  }

  double Shade::thermalResistance() const {
    return getImpl<detail::Shade_Impl>()->thermalResistance();
  }

  double Shade::solarTransmittance() const {
    return getImpl<detail::Shade_Impl>()->solarTransmittance();
  }

  double Shade::solarReflectance() const {
    return getImpl<detail::Shade_Impl>()->solarReflectance();
  }

  double Shade::visibleTransmittance() const {
    return getImpl<detail::Shade_Impl>()->visibleTransmittance();
  }

  double Shade::visibleReflectance() const {
    return getImpl<detail::Shade_Impl>()->visibleReflectance();
  }

  double Shade::thermalHemisphericalEmissivity() const {
    return getImpl<detail::Shade_Impl>()->thermalHemisphericalEmissivity();
  }

  double Shade::thermalTransmittance() const {
    return getImpl<detail::Shade_Impl>()->thermalTransmittance();
  }

  double Shade::solarAbsorptance() const {
    return getImpl<detail::Shade_Impl>()->solarAbsorptance();
  }

  double Shade::visibleAbsorptance() const {
    return getImpl<detail::Shade_Impl>()->visibleAbsorptance();
  }

  double Shade::thickness() const {
    return getImpl<detail::Shade_Impl>()->thickness();
  }

  double Shade::conductivity() const {
    return getImpl<detail::Shade_Impl>()->conductivity();
  }

  double Shade::shadetoGlassDistance() const {
    return getImpl<detail::Shade_Impl>()->shadetoGlassDistance();
  }

  bool Shade::isShadetoGlassDistanceDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isShadetoGlassDistanceDefaulted();
  }

  double Shade::topOpeningMultiplier() const {
    return getImpl<detail::Shade_Impl>()->topOpeningMultiplier();
  }

  bool Shade::isTopOpeningMultiplierDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isTopOpeningMultiplierDefaulted();
  }

  double Shade::bottomOpeningMultiplier() const {
    return getImpl<detail::Shade_Impl>()->bottomOpeningMultiplier();
  }

  bool Shade::isBottomOpeningMultiplierDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isBottomOpeningMultiplierDefaulted();
  }

  double Shade::leftSideOpeningMultiplier() const {
    return getImpl<detail::Shade_Impl>()->leftSideOpeningMultiplier();
  }

  bool Shade::isLeftSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isLeftSideOpeningMultiplierDefaulted();
  }

  double Shade::rightSideOpeningMultiplier() const {
    return getImpl<detail::Shade_Impl>()->rightSideOpeningMultiplier();
  }

  bool Shade::isRightSideOpeningMultiplierDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isRightSideOpeningMultiplierDefaulted();
  }

  double Shade::airflowPermeability() const {
    return getImpl<detail::Shade_Impl>()->airflowPermeability();
  }

  bool Shade::isAirflowPermeabilityDefaulted() const {
    return getImpl<detail::Shade_Impl>()->isAirflowPermeabilityDefaulted();
  }

  bool Shade::setThermalConductivity(double value) {
    return getImpl<detail::Shade_Impl>()->setThermalConductivity(value);
  }

  bool Shade::setThermalConductance(double value) {
    return getImpl<detail::Shade_Impl>()->setThermalConductance(value);
  }

  bool Shade::setThermalResistivity(double value) {
    return getImpl<detail::Shade_Impl>()->setThermalResistivity(value);
  }

  bool Shade::setThermalResistance(double value) {
    return getImpl<detail::Shade_Impl>()->setThermalResistance(value);
  }

  bool Shade::setThermalTransmittance(double thermalTransmittance) {
    return getImpl<detail::Shade_Impl>()->setThermalTransmittance(thermalTransmittance);
  }

  bool Shade::setSolarTransmittance(double solarTransmittance) {
    return getImpl<detail::Shade_Impl>()->setSolarTransmittance(solarTransmittance);
  }

  bool Shade::setSolarReflectance(double solarReflectance) {
    return getImpl<detail::Shade_Impl>()->setSolarReflectance(solarReflectance);
  }

  bool Shade::setVisibleTransmittance(double visibleTransmittance) {
    return getImpl<detail::Shade_Impl>()->setVisibleTransmittance(visibleTransmittance);
  }

  bool Shade::setVisibleReflectance(double visibleReflectance) {
    return getImpl<detail::Shade_Impl>()->setVisibleReflectance(visibleReflectance);
  }

  bool Shade::setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity) {
    return getImpl<detail::Shade_Impl>()->setThermalHemisphericalEmissivity(thermalHemisphericalEmissivity);
  }

  bool Shade::setThickness(double thickness) {
    return getImpl<detail::Shade_Impl>()->setThickness(thickness);
  }

  bool Shade::setConductivity(double conductivity) {
    return getImpl<detail::Shade_Impl>()->setConductivity(conductivity);
  }

  bool Shade::setShadetoGlassDistance(double shadetoGlassDistance) {
    return getImpl<detail::Shade_Impl>()->setShadetoGlassDistance(shadetoGlassDistance);
  }

  void Shade::resetShadetoGlassDistance() {
    getImpl<detail::Shade_Impl>()->resetShadetoGlassDistance();
  }

  bool Shade::setTopOpeningMultiplier(double topOpeningMultiplier) {
    return getImpl<detail::Shade_Impl>()->setTopOpeningMultiplier(topOpeningMultiplier);
  }

  void Shade::resetTopOpeningMultiplier() {
    getImpl<detail::Shade_Impl>()->resetTopOpeningMultiplier();
  }

  bool Shade::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
    return getImpl<detail::Shade_Impl>()->setBottomOpeningMultiplier(bottomOpeningMultiplier);
  }

  void Shade::resetBottomOpeningMultiplier() {
    getImpl<detail::Shade_Impl>()->resetBottomOpeningMultiplier();
  }

  bool Shade::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
    return getImpl<detail::Shade_Impl>()->setLeftSideOpeningMultiplier(leftSideOpeningMultiplier);
  }

  void Shade::resetLeftSideOpeningMultiplier() {
    getImpl<detail::Shade_Impl>()->resetLeftSideOpeningMultiplier();
  }

  bool Shade::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
    return getImpl<detail::Shade_Impl>()->setRightSideOpeningMultiplier(rightSideOpeningMultiplier);
  }

  void Shade::resetRightSideOpeningMultiplier() {
    getImpl<detail::Shade_Impl>()->resetRightSideOpeningMultiplier();
  }

  bool Shade::setAirflowPermeability(double airflowPermeability) {
    return getImpl<detail::Shade_Impl>()->setAirflowPermeability(airflowPermeability);
  }

  void Shade::resetAirflowPermeability() {
    getImpl<detail::Shade_Impl>()->resetAirflowPermeability();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double Shade_Impl::thermalConductivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::Conductivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::thermalConductance() const {
      const double value = thickness();
      OS_ASSERT(value > 0.0);
      return thermalConductivity() / value;
    }

    double Shade_Impl::thermalResistivity() const {
      const double value = thermalConductivity();
      OS_ASSERT(value > 0.0);
      return 1.0 / value;
    }

    double Shade_Impl::thermalResistance() const {
      const double value = thermalConductance();
      OS_ASSERT(value > 0.0);
      return 1.0 / value;
    }

    double Shade_Impl::solarTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::SolarTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::solarReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::SolarReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::visibleTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::VisibleTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::visibleReflectance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::VisibleReflectance, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::thermalHemisphericalEmissivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::InfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::thermalTransmittance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::InfraredTransmittance, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::solarAbsorptance() const {
      return 1.0 - solarTransmittance() - solarReflectance();
    }

    double Shade_Impl::visibleAbsorptance() const {
      return 1.0 - visibleTransmittance() - visibleReflectance();
    }

    double Shade_Impl::thickness() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::Thickness, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::conductivity() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::Conductivity, true);
      OS_ASSERT(value);
      return value.get();
    }

    double Shade_Impl::shadetoGlassDistance() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::ShadetoGlassDistance, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isShadetoGlassDistanceDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::ShadetoGlassDistance);
    }

    double Shade_Impl::topOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::TopOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isTopOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::TopOpeningMultiplier);
    }

    double Shade_Impl::bottomOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::BottomOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isBottomOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::BottomOpeningMultiplier);
    }

    double Shade_Impl::leftSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::LeftSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isLeftSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::LeftSideOpeningMultiplier);
    }

    double Shade_Impl::rightSideOpeningMultiplier() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::RightSideOpeningMultiplier, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isRightSideOpeningMultiplierDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::RightSideOpeningMultiplier);
    }

    double Shade_Impl::airflowPermeability() const {
      boost::optional<double> value = getDouble(openstudio::WindowMaterial_ShadeFields::AirflowPermeability, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool Shade_Impl::isAirflowPermeabilityDefaulted() const {
      return isEmpty(openstudio::WindowMaterial_ShadeFields::AirflowPermeability);
    }

    bool Shade_Impl::setThermalConductivity(double value) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::Conductivity, value);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setThermalConductance(double value) {
      OS_ASSERT(value != 0.0);
      return setThickness(thermalConductivity() / value);
    }

    bool Shade_Impl::setThermalResistivity(double value) {
      OS_ASSERT(value != 0.0);
      return setThermalConductivity(1.0 / value);
    }

    bool Shade_Impl::setThermalResistance(double value) {
      OS_ASSERT(value != 0.0);
      return setThickness(value / thermalResistivity());
    }

    bool Shade_Impl::setThermalTransmittance(double thermalTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::InfraredTransmittance, thermalTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setSolarTransmittance(double solarTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::SolarTransmittance, solarTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setSolarReflectance(double solarReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::SolarReflectance, solarReflectance);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setVisibleTransmittance(double visibleTransmittance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::VisibleTransmittance, visibleTransmittance);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setVisibleReflectance(double visibleReflectance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::VisibleReflectance, visibleReflectance);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::InfraredHemisphericalEmissivity, thermalHemisphericalEmissivity);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setThickness(double thickness) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::Thickness, thickness);
      OS_ASSERT(result);
      return result;
    }

    bool Shade_Impl::setConductivity(double conductivity) {
      return setThermalConductivity(conductivity);
    }

    bool Shade_Impl::setShadetoGlassDistance(double shadetoGlassDistance) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::ShadetoGlassDistance, shadetoGlassDistance);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetShadetoGlassDistance() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::ShadetoGlassDistance, ""));
    }

    bool Shade_Impl::setTopOpeningMultiplier(double topOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::TopOpeningMultiplier, topOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetTopOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::TopOpeningMultiplier, ""));
    }

    bool Shade_Impl::setBottomOpeningMultiplier(double bottomOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::BottomOpeningMultiplier, bottomOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetBottomOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::BottomOpeningMultiplier, ""));
    }

    bool Shade_Impl::setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::LeftSideOpeningMultiplier, leftSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetLeftSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::LeftSideOpeningMultiplier, ""));
    }

    bool Shade_Impl::setRightSideOpeningMultiplier(double rightSideOpeningMultiplier) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::RightSideOpeningMultiplier, rightSideOpeningMultiplier);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetRightSideOpeningMultiplier() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::RightSideOpeningMultiplier, ""));
    }

    bool Shade_Impl::setAirflowPermeability(double airflowPermeability) {
      const bool result = setDouble(openstudio::WindowMaterial_ShadeFields::AirflowPermeability, airflowPermeability);
      OS_ASSERT(result);
      return result;
    }

    void Shade_Impl::resetAirflowPermeability() {
      OS_ASSERT(setString(openstudio::WindowMaterial_ShadeFields::AirflowPermeability, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
