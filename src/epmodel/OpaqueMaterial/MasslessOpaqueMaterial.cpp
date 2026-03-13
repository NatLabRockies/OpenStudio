/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OpaqueMaterial/MasslessOpaqueMaterial.hpp"
#include "OpaqueMaterial/MasslessOpaqueMaterial_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Material_NoMass_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  MasslessOpaqueMaterial::MasslessOpaqueMaterial(const Model& model, const std::string& roughness, double thermalResistance)
    : ModelObject(MasslessOpaqueMaterial::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::MasslessOpaqueMaterial_Impl>());

    bool ok = true;
    ok = setRoughness(roughness);
    OS_ASSERT(ok);
    ok = setThermalResistance(thermalResistance);
    OS_ASSERT(ok);
  }

  MasslessOpaqueMaterial::MasslessOpaqueMaterial(std::shared_ptr<detail::MasslessOpaqueMaterial_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType MasslessOpaqueMaterial::iddObjectType() {
    return IddObjectType::Material_NoMass;
  }

  std::vector<std::string> MasslessOpaqueMaterial::roughnessValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Material_NoMassFields::Roughness);
  }

  std::string MasslessOpaqueMaterial::roughness() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->roughness();
  }

  double MasslessOpaqueMaterial::thermalResistance() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->thermalResistance();
  }

  boost::optional<double> MasslessOpaqueMaterial::thermalAbsorptance() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->thermalAbsorptance();
  }

  bool MasslessOpaqueMaterial::isThermalAbsorptanceDefaulted() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->isThermalAbsorptanceDefaulted();
  }

  boost::optional<double> MasslessOpaqueMaterial::solarAbsorptance() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->solarAbsorptance();
  }

  bool MasslessOpaqueMaterial::isSolarAbsorptanceDefaulted() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->isSolarAbsorptanceDefaulted();
  }

  boost::optional<double> MasslessOpaqueMaterial::visibleAbsorptance() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->visibleAbsorptance();
  }

  bool MasslessOpaqueMaterial::isVisibleAbsorptanceDefaulted() const {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->isVisibleAbsorptanceDefaulted();
  }

  bool MasslessOpaqueMaterial::setRoughness(const std::string& roughness) {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->setRoughness(roughness);
  }

  bool MasslessOpaqueMaterial::setThermalResistance(double thermalResistance) {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->setThermalResistance(thermalResistance);
  }

  bool MasslessOpaqueMaterial::setThermalAbsorptance(double thermalAbsorptance) {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->setThermalAbsorptance(thermalAbsorptance);
  }

  void MasslessOpaqueMaterial::resetThermalAbsorptance() {
    getImpl<detail::MasslessOpaqueMaterial_Impl>()->resetThermalAbsorptance();
  }

  bool MasslessOpaqueMaterial::setSolarAbsorptance(double solarAbsorptance) {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->setSolarAbsorptance(solarAbsorptance);
  }

  void MasslessOpaqueMaterial::resetSolarAbsorptance() {
    getImpl<detail::MasslessOpaqueMaterial_Impl>()->resetSolarAbsorptance();
  }

  bool MasslessOpaqueMaterial::setVisibleAbsorptance(double visibleAbsorptance) {
    return getImpl<detail::MasslessOpaqueMaterial_Impl>()->setVisibleAbsorptance(visibleAbsorptance);
  }

  void MasslessOpaqueMaterial::resetVisibleAbsorptance() {
    getImpl<detail::MasslessOpaqueMaterial_Impl>()->resetVisibleAbsorptance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string MasslessOpaqueMaterial_Impl::roughness() const {
      const auto value = getString(openstudio::Material_NoMassFields::Roughness, true);
      OS_ASSERT(value);
      return *value;
    }

    double MasslessOpaqueMaterial_Impl::thermalResistance() const {
      const auto value = getDouble(openstudio::Material_NoMassFields::ThermalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> MasslessOpaqueMaterial_Impl::thermalAbsorptance() const {
      return getDouble(openstudio::Material_NoMassFields::ThermalAbsorptance, true);
    }

    bool MasslessOpaqueMaterial_Impl::isThermalAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_NoMassFields::ThermalAbsorptance);
    }

    boost::optional<double> MasslessOpaqueMaterial_Impl::solarAbsorptance() const {
      return getDouble(openstudio::Material_NoMassFields::SolarAbsorptance, true);
    }

    bool MasslessOpaqueMaterial_Impl::isSolarAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_NoMassFields::SolarAbsorptance);
    }

    boost::optional<double> MasslessOpaqueMaterial_Impl::visibleAbsorptance() const {
      return getDouble(openstudio::Material_NoMassFields::VisibleAbsorptance, true);
    }

    bool MasslessOpaqueMaterial_Impl::isVisibleAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_NoMassFields::VisibleAbsorptance);
    }

    bool MasslessOpaqueMaterial_Impl::setRoughness(const std::string& roughness) {
      return setString(openstudio::Material_NoMassFields::Roughness, roughness);
    }

    bool MasslessOpaqueMaterial_Impl::setThermalResistance(double thermalResistance) {
      return setDouble(openstudio::Material_NoMassFields::ThermalResistance, thermalResistance);
    }

    bool MasslessOpaqueMaterial_Impl::setThermalAbsorptance(double thermalAbsorptance) {
      return setDouble(openstudio::Material_NoMassFields::ThermalAbsorptance, thermalAbsorptance);
    }

    void MasslessOpaqueMaterial_Impl::resetThermalAbsorptance() {
      const bool result = setString(openstudio::Material_NoMassFields::ThermalAbsorptance, "");
      OS_ASSERT(result);
    }

    bool MasslessOpaqueMaterial_Impl::setSolarAbsorptance(double solarAbsorptance) {
      return setDouble(openstudio::Material_NoMassFields::SolarAbsorptance, solarAbsorptance);
    }

    void MasslessOpaqueMaterial_Impl::resetSolarAbsorptance() {
      const bool result = setString(openstudio::Material_NoMassFields::SolarAbsorptance, "");
      OS_ASSERT(result);
    }

    bool MasslessOpaqueMaterial_Impl::setVisibleAbsorptance(double visibleAbsorptance) {
      return setDouble(openstudio::Material_NoMassFields::VisibleAbsorptance, visibleAbsorptance);
    }

    void MasslessOpaqueMaterial_Impl::resetVisibleAbsorptance() {
      const bool result = setString(openstudio::Material_NoMassFields::VisibleAbsorptance, "");
      OS_ASSERT(result);
    }

    std::vector<std::string> MasslessOpaqueMaterial_Impl::roughnessValues() const {
      return openstudio::epmodel::MasslessOpaqueMaterial::roughnessValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
