/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OpaqueMaterial/StandardOpaqueMaterial.hpp"
#include "OpaqueMaterial/StandardOpaqueMaterial_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Material_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  StandardOpaqueMaterial::StandardOpaqueMaterial(const Model& model, const std::string& roughness, double thickness, double conductivity,
                                                 double density, double specificHeat)
    : Material(StandardOpaqueMaterial::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::StandardOpaqueMaterial_Impl>());

    bool ok = true;
    ok = setRoughness(roughness);
    OS_ASSERT(ok);
    ok = setThickness(thickness);
    OS_ASSERT(ok);
    ok = setConductivity(conductivity);
    OS_ASSERT(ok);
    ok = setDensity(density);
    OS_ASSERT(ok);
    ok = setSpecificHeat(specificHeat);
    OS_ASSERT(ok);
  }

  StandardOpaqueMaterial::StandardOpaqueMaterial(std::shared_ptr<detail::StandardOpaqueMaterial_Impl> impl) : Material(std::move(impl)) {}

  IddObjectType StandardOpaqueMaterial::iddObjectType() {
    return IddObjectType::Material;
  }

  std::vector<std::string> StandardOpaqueMaterial::roughnessValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::MaterialFields::Roughness);
  }

  std::string StandardOpaqueMaterial::roughness() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->roughness();
  }

  bool StandardOpaqueMaterial::setRoughness(const std::string& roughness) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setRoughness(roughness);
  }

  double StandardOpaqueMaterial::thickness() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thickness();
  }

  bool StandardOpaqueMaterial::setThickness(double thickness) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThickness(thickness);
  }

  double StandardOpaqueMaterial::conductivity() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->conductivity();
  }

  double StandardOpaqueMaterial::thermalConductivity() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalConductivity();
  }

  double StandardOpaqueMaterial::thermalConductance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalConductance();
  }

  double StandardOpaqueMaterial::thermalResistivity() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalResistivity();
  }

  double StandardOpaqueMaterial::thermalResistance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalResistance();
  }

  bool StandardOpaqueMaterial::setConductivity(double conductivity) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setConductivity(conductivity);
  }

  bool StandardOpaqueMaterial::setThermalConductivity(double value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalConductivity(value);
  }

  bool StandardOpaqueMaterial::setThermalConductance(double value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalConductance(value);
  }

  bool StandardOpaqueMaterial::setThermalResistivity(double value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalResistivity(value);
  }

  bool StandardOpaqueMaterial::setThermalResistance(double value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalResistance(value);
  }

  double StandardOpaqueMaterial::density() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->density();
  }

  bool StandardOpaqueMaterial::setDensity(double density) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setDensity(density);
  }

  double StandardOpaqueMaterial::specificHeat() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->specificHeat();
  }

  bool StandardOpaqueMaterial::setSpecificHeat(double specificHeat) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setSpecificHeat(specificHeat);
  }

  boost::optional<double> StandardOpaqueMaterial::heatCapacity() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->heatCapacity();
  }

  double StandardOpaqueMaterial::thermalAbsorptance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalAbsorptance();
  }

  bool StandardOpaqueMaterial::isThermalAbsorptanceDefaulted() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->isThermalAbsorptanceDefaulted();
  }

  bool StandardOpaqueMaterial::setThermalAbsorptance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalAbsorptance(value);
  }

  bool StandardOpaqueMaterial::setThermalAbsorptance(double thermalAbsorptance) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalAbsorptance(thermalAbsorptance);
  }

  void StandardOpaqueMaterial::resetThermalAbsorptance() {
    getImpl<detail::StandardOpaqueMaterial_Impl>()->resetThermalAbsorptance();
  }

  boost::optional<double> StandardOpaqueMaterial::thermalReflectance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->thermalReflectance();
  }

  bool StandardOpaqueMaterial::setThermalReflectance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setThermalReflectance(value);
  }

  double StandardOpaqueMaterial::solarAbsorptance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->solarAbsorptance();
  }

  bool StandardOpaqueMaterial::isSolarAbsorptanceDefaulted() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->isSolarAbsorptanceDefaulted();
  }

  bool StandardOpaqueMaterial::setSolarAbsorptance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setSolarAbsorptance(value);
  }

  bool StandardOpaqueMaterial::setSolarAbsorptance(double solarAbsorptance) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setSolarAbsorptance(solarAbsorptance);
  }

  void StandardOpaqueMaterial::resetSolarAbsorptance() {
    getImpl<detail::StandardOpaqueMaterial_Impl>()->resetSolarAbsorptance();
  }

  boost::optional<double> StandardOpaqueMaterial::solarReflectance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->solarReflectance();
  }

  bool StandardOpaqueMaterial::setSolarReflectance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setSolarReflectance(value);
  }

  double StandardOpaqueMaterial::visibleAbsorptance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->visibleAbsorptance();
  }

  bool StandardOpaqueMaterial::isVisibleAbsorptanceDefaulted() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->isVisibleAbsorptanceDefaulted();
  }

  bool StandardOpaqueMaterial::setVisibleAbsorptance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setVisibleAbsorptance(value);
  }

  bool StandardOpaqueMaterial::setVisibleAbsorptance(double visibleAbsorptance) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setVisibleAbsorptance(visibleAbsorptance);
  }

  void StandardOpaqueMaterial::resetVisibleAbsorptance() {
    getImpl<detail::StandardOpaqueMaterial_Impl>()->resetVisibleAbsorptance();
  }

  boost::optional<double> StandardOpaqueMaterial::visibleReflectance() const {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->visibleReflectance();
  }

  bool StandardOpaqueMaterial::setVisibleReflectance(boost::optional<double> value) {
    return getImpl<detail::StandardOpaqueMaterial_Impl>()->setVisibleReflectance(value);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string StandardOpaqueMaterial_Impl::roughness() const {
      const auto value = getString(openstudio::MaterialFields::Roughness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::setRoughness(const std::string& roughness) {
      return setString(openstudio::MaterialFields::Roughness, roughness);
    }

    double StandardOpaqueMaterial_Impl::thickness() const {
      const auto value = getDouble(openstudio::MaterialFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::setThickness(double thickness) {
      return setDouble(openstudio::MaterialFields::Thickness, thickness);
    }

    double StandardOpaqueMaterial_Impl::conductivity() const {
      const auto value = getDouble(openstudio::MaterialFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::setConductivity(double conductivity) {
      return setDouble(openstudio::MaterialFields::Conductivity, conductivity);
    }

    double StandardOpaqueMaterial_Impl::thermalConductivity() const {
      const auto value = getDouble(openstudio::MaterialFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    double StandardOpaqueMaterial_Impl::thermalConductance() const {
      return thermalConductivity() / thickness();
    }

    double StandardOpaqueMaterial_Impl::thermalResistivity() const {
      return 1.0 / thermalConductivity();
    }

    double StandardOpaqueMaterial_Impl::thermalResistance() const {
      return thermalResistivity() * thickness();
    }

    bool StandardOpaqueMaterial_Impl::setThermalConductivity(double value) {
      return setDouble(openstudio::MaterialFields::Conductivity, value);
    }

    bool StandardOpaqueMaterial_Impl::setThermalConductance(double value) {
      return setThickness(thermalConductivity() / value);
    }

    bool StandardOpaqueMaterial_Impl::setThermalResistivity(double value) {
      return setThermalConductivity(1.0 / value);
    }

    bool StandardOpaqueMaterial_Impl::setThermalResistance(double value) {
      return setThickness(value / thermalResistivity());
    }

    double StandardOpaqueMaterial_Impl::density() const {
      const auto value = getDouble(openstudio::MaterialFields::Density, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::setDensity(double density) {
      return setDouble(openstudio::MaterialFields::Density, density);
    }

    double StandardOpaqueMaterial_Impl::specificHeat() const {
      const auto value = getDouble(openstudio::MaterialFields::SpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::setSpecificHeat(double specificHeat) {
      return setDouble(openstudio::MaterialFields::SpecificHeat, specificHeat);
    }

    boost::optional<double> StandardOpaqueMaterial_Impl::heatCapacity() const {
      return specificHeat() * density() * thickness();
    }

    double StandardOpaqueMaterial_Impl::thermalAbsorptance() const {
      const auto value = getDouble(openstudio::MaterialFields::ThermalAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::isThermalAbsorptanceDefaulted() const {
      return isEmpty(openstudio::MaterialFields::ThermalAbsorptance);
    }

    bool StandardOpaqueMaterial_Impl::setThermalAbsorptance(boost::optional<double> value) {
      if (!value) {
        resetThermalAbsorptance();
        return true;
      }
      return setThermalAbsorptance(*value);
    }

    bool StandardOpaqueMaterial_Impl::setThermalAbsorptance(double thermalAbsorptance) {
      return setDouble(openstudio::MaterialFields::ThermalAbsorptance, thermalAbsorptance);
    }

    void StandardOpaqueMaterial_Impl::resetThermalAbsorptance() {
      OS_ASSERT(setString(openstudio::MaterialFields::ThermalAbsorptance, ""));
    }

    boost::optional<double> StandardOpaqueMaterial_Impl::thermalReflectance() const {
      return 1.0 - thermalAbsorptance();
    }

    bool StandardOpaqueMaterial_Impl::setThermalReflectance(boost::optional<double> value) {
      if (!value) {
        resetThermalAbsorptance();
        return true;
      }
      return setThermalAbsorptance(1.0 - *value);
    }

    double StandardOpaqueMaterial_Impl::solarAbsorptance() const {
      const auto value = getDouble(openstudio::MaterialFields::SolarAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::isSolarAbsorptanceDefaulted() const {
      return isEmpty(openstudio::MaterialFields::SolarAbsorptance);
    }

    bool StandardOpaqueMaterial_Impl::setSolarAbsorptance(boost::optional<double> value) {
      if (!value) {
        return setString(openstudio::MaterialFields::SolarAbsorptance, "");
      }
      return setDouble(openstudio::MaterialFields::SolarAbsorptance, *value);
    }

    bool StandardOpaqueMaterial_Impl::setSolarAbsorptance(double solarAbsorptance) {
      return setDouble(openstudio::MaterialFields::SolarAbsorptance, solarAbsorptance);
    }

    void StandardOpaqueMaterial_Impl::resetSolarAbsorptance() {
      OS_ASSERT(setString(openstudio::MaterialFields::SolarAbsorptance, ""));
    }

    boost::optional<double> StandardOpaqueMaterial_Impl::solarReflectance() const {
      return 1.0 - solarAbsorptance();
    }

    bool StandardOpaqueMaterial_Impl::setSolarReflectance(boost::optional<double> value) {
      if (!value) {
        return setSolarAbsorptance(value);
      }
      return setSolarAbsorptance(1.0 - *value);
    }

    double StandardOpaqueMaterial_Impl::visibleAbsorptance() const {
      const auto value = getDouble(openstudio::MaterialFields::VisibleAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardOpaqueMaterial_Impl::isVisibleAbsorptanceDefaulted() const {
      return isEmpty(openstudio::MaterialFields::VisibleAbsorptance);
    }

    bool StandardOpaqueMaterial_Impl::setVisibleAbsorptance(boost::optional<double> value) {
      if (!value) {
        return setString(openstudio::MaterialFields::VisibleAbsorptance, "");
      }
      return setDouble(openstudio::MaterialFields::VisibleAbsorptance, *value);
    }

    bool StandardOpaqueMaterial_Impl::setVisibleAbsorptance(double visibleAbsorptance) {
      return setDouble(openstudio::MaterialFields::VisibleAbsorptance, visibleAbsorptance);
    }

    void StandardOpaqueMaterial_Impl::resetVisibleAbsorptance() {
      OS_ASSERT(setString(openstudio::MaterialFields::VisibleAbsorptance, ""));
    }

    boost::optional<double> StandardOpaqueMaterial_Impl::visibleReflectance() const {
      return 1.0 - visibleAbsorptance();
    }

    bool StandardOpaqueMaterial_Impl::setVisibleReflectance(boost::optional<double> value) {
      if (!value) {
        return setVisibleAbsorptance(value);
      }
      return setVisibleAbsorptance(1.0 - *value);
    }

    std::vector<std::string> StandardOpaqueMaterial_Impl::roughnessValues() const {
      return openstudio::epmodel::StandardOpaqueMaterial::roughnessValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
