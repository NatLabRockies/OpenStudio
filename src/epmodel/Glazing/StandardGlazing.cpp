/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Glazing/StandardGlazing.hpp"
#include "Glazing/StandardGlazing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/WindowMaterial_Glazing_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    std::string StandardGlazing_Impl::opticalDataType() const {
      auto value = getString(WindowMaterial_GlazingFields::OpticalDataType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setOpticalDataType(const std::string& opticalDataType) {
      return setString(WindowMaterial_GlazingFields::OpticalDataType, opticalDataType);
    }

    double StandardGlazing_Impl::thickness() const {
      auto value = getDouble(WindowMaterial_GlazingFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setThickness(double thickness) {
      return setDouble(WindowMaterial_GlazingFields::Thickness, thickness);
    }

    double StandardGlazing_Impl::solarTransmittance() const {
      auto value = getDouble(WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> StandardGlazing_Impl::solarTransmittanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setSolarTransmittance(double value) {
      return setDouble(WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, value);
    }

    bool StandardGlazing_Impl::setSolarTransmittanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetSolarTransmittanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, ""));
    }

    boost::optional<double> StandardGlazing_Impl::frontSideSolarReflectanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::FrontSideSolarReflectanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setFrontSideSolarReflectanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::FrontSideSolarReflectanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetFrontSideSolarReflectanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::FrontSideSolarReflectanceatNormalIncidence, ""));
    }

    boost::optional<double> StandardGlazing_Impl::backSideSolarReflectanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::BackSideSolarReflectanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setBackSideSolarReflectanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::BackSideSolarReflectanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetBackSideSolarReflectanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::BackSideSolarReflectanceatNormalIncidence, ""));
    }

    boost::optional<double> StandardGlazing_Impl::visibleTransmittanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setVisibleTransmittance(double value) {
      return setDouble(WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, value);
    }

    bool StandardGlazing_Impl::setVisibleTransmittanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetVisibleTransmittanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, ""));
    }

    boost::optional<double> StandardGlazing_Impl::frontSideVisibleReflectanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setFrontSideVisibleReflectanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetFrontSideVisibleReflectanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, ""));
    }

    boost::optional<double> StandardGlazing_Impl::backSideVisibleReflectanceatNormalIncidence() const {
      return getDouble(WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, true);
    }

    bool StandardGlazing_Impl::setBackSideVisibleReflectanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetBackSideVisibleReflectanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, ""));
    }

    double StandardGlazing_Impl::infraredTransmittance() const {
      auto value = getDouble(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    double StandardGlazing_Impl::infraredTransmittanceatNormalIncidence() const {
      auto value = getDouble(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setInfraredTransmittance(double value) {
      return setDouble(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, value);
    }

    bool StandardGlazing_Impl::setInfraredTransmittanceatNormalIncidence(double value) {
      return setDouble(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, value);
    }

    void StandardGlazing_Impl::resetInfraredTransmittanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, ""));
    }

    bool StandardGlazing_Impl::isInfraredTransmittanceatNormalIncidenceDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence);
    }

    double StandardGlazing_Impl::frontSideInfraredHemisphericalEmissivity() const {
      auto value = getDouble(WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setFrontSideInfraredHemisphericalEmissivity(double value) {
      return setDouble(WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity, value);
    }

    void StandardGlazing_Impl::resetFrontSideInfraredHemisphericalEmissivity() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity, ""));
    }

    bool StandardGlazing_Impl::isFrontSideInfraredHemisphericalEmissivityDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity);
    }

    double StandardGlazing_Impl::backSideInfraredHemisphericalEmissivity() const {
      auto value = getDouble(WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setBackSideInfraredHemisphericalEmissivity(double value) {
      return setDouble(WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity, value);
    }

    void StandardGlazing_Impl::resetBackSideInfraredHemisphericalEmissivity() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity, ""));
    }

    bool StandardGlazing_Impl::isBackSideInfraredHemisphericalEmissivityDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity);
    }

    double StandardGlazing_Impl::conductivity() const {
      auto value = getDouble(WindowMaterial_GlazingFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setConductivity(double value) {
      return setDouble(WindowMaterial_GlazingFields::Conductivity, value);
    }

    void StandardGlazing_Impl::resetConductivity() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::Conductivity, ""));
    }

    bool StandardGlazing_Impl::isConductivityDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::Conductivity);
    }

    double StandardGlazing_Impl::dirtCorrectionFactorforSolarandVisibleTransmittance() const {
      auto value = getDouble(WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool StandardGlazing_Impl::setDirtCorrectionFactorforSolarandVisibleTransmittance(double value) {
      return setDouble(WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance, value);
    }

    void StandardGlazing_Impl::resetDirtCorrectionFactorforSolarandVisibleTransmittance() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance, ""));
    }

    bool StandardGlazing_Impl::isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance);
    }

    bool StandardGlazing_Impl::solarDiffusing() const {
      auto value = getString(WindowMaterial_GlazingFields::SolarDiffusing, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool StandardGlazing_Impl::setSolarDiffusing(bool solarDiffusing) {
      return setString(WindowMaterial_GlazingFields::SolarDiffusing, solarDiffusing ? "Yes" : "No");
    }

    void StandardGlazing_Impl::resetSolarDiffusing() {
      OS_ASSERT(setString(WindowMaterial_GlazingFields::SolarDiffusing, ""));
    }

    bool StandardGlazing_Impl::isSolarDiffusingDefaulted() const {
      return isEmpty(WindowMaterial_GlazingFields::SolarDiffusing);
    }

    double StandardGlazing_Impl::thermalConductivity() const {
      auto value = getDouble(WindowMaterial_GlazingFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    double StandardGlazing_Impl::thermalConductance() const {
      return thermalConductivity() / thickness();
    }

    double StandardGlazing_Impl::thermalResistivity() const {
      return 1.0 / thermalConductivity();
    }

    double StandardGlazing_Impl::thermalResistance() const {
      return 1.0 / thermalConductance();
    }

    double StandardGlazing_Impl::interiorVisibleReflectance() const {
      auto value = getDouble(WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    double StandardGlazing_Impl::exteriorVisibleReflectance() const {
      auto value = getDouble(WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    boost::optional<double> StandardGlazing_Impl::interiorVisibleAbsorptance() const {
      auto vt = visibleTransmittanceatNormalIncidence();
      if (!vt) {
        return boost::none;
      }
      return 1.0 - (*vt + interiorVisibleReflectance());
    }

    boost::optional<double> StandardGlazing_Impl::exteriorVisibleAbsorptance() const {
      auto vt = visibleTransmittanceatNormalIncidence();
      if (!vt) {
        return boost::none;
      }
      return 1.0 - (*vt + exteriorVisibleReflectance());
    }

    bool StandardGlazing_Impl::setThermalConductivity(double value) {
      return setDouble(WindowMaterial_GlazingFields::Conductivity, value);
    }

    bool StandardGlazing_Impl::setThermalConductance(double value) {
      return setThickness(thermalConductivity() / value);
    }

    bool StandardGlazing_Impl::setThermalResistivity(double value) {
      return setThermalConductivity(1.0 / value);
    }

    bool StandardGlazing_Impl::setThermalResistance(double value) {
      return setThickness(value / thermalResistivity());
    }

    std::vector<std::string> StandardGlazing_Impl::opticalDataTypeValues() const {
      return StandardGlazing::opticalDataTypeValues();
    }

  }  // namespace detail

  StandardGlazing::StandardGlazing(const Model& model, const std::string& opticalDataType, double thickness)
    : ModelObject(StandardGlazing::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::StandardGlazing_Impl>());

    bool ok = true;
    ok = setOpticalDataType(opticalDataType);
    OS_ASSERT(ok);
    ok = setThickness(thickness);
    OS_ASSERT(ok);
  }

  StandardGlazing::StandardGlazing(std::shared_ptr<detail::StandardGlazing_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType StandardGlazing::iddObjectType() {
    return IddObjectType::WindowMaterial_Glazing;
  }

  std::vector<std::string> StandardGlazing::opticalDataTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), WindowMaterial_GlazingFields::OpticalDataType);
  }

  std::string StandardGlazing::opticalDataType() const {
    return getImpl<detail::StandardGlazing_Impl>()->opticalDataType();
  }

  double StandardGlazing::thickness() const {
    return getImpl<detail::StandardGlazing_Impl>()->thickness();
  }

  double StandardGlazing::solarTransmittance() const {
    return getImpl<detail::StandardGlazing_Impl>()->solarTransmittance();
  }

  boost::optional<double> StandardGlazing::solarTransmittanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->solarTransmittanceatNormalIncidence();
  }

  boost::optional<double> StandardGlazing::frontSideSolarReflectanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->frontSideSolarReflectanceatNormalIncidence();
  }

  boost::optional<double> StandardGlazing::backSideSolarReflectanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->backSideSolarReflectanceatNormalIncidence();
  }

  boost::optional<double> StandardGlazing::visibleTransmittanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->visibleTransmittanceatNormalIncidence();
  }

  boost::optional<double> StandardGlazing::frontSideVisibleReflectanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->frontSideVisibleReflectanceatNormalIncidence();
  }

  boost::optional<double> StandardGlazing::backSideVisibleReflectanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->backSideVisibleReflectanceatNormalIncidence();
  }

  double StandardGlazing::infraredTransmittance() const {
    return getImpl<detail::StandardGlazing_Impl>()->infraredTransmittance();
  }

  double StandardGlazing::infraredTransmittanceatNormalIncidence() const {
    return getImpl<detail::StandardGlazing_Impl>()->infraredTransmittanceatNormalIncidence();
  }

  bool StandardGlazing::isInfraredTransmittanceatNormalIncidenceDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isInfraredTransmittanceatNormalIncidenceDefaulted();
  }

  double StandardGlazing::frontSideInfraredHemisphericalEmissivity() const {
    return getImpl<detail::StandardGlazing_Impl>()->frontSideInfraredHemisphericalEmissivity();
  }

  bool StandardGlazing::isFrontSideInfraredHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isFrontSideInfraredHemisphericalEmissivityDefaulted();
  }

  double StandardGlazing::backSideInfraredHemisphericalEmissivity() const {
    return getImpl<detail::StandardGlazing_Impl>()->backSideInfraredHemisphericalEmissivity();
  }

  bool StandardGlazing::isBackSideInfraredHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isBackSideInfraredHemisphericalEmissivityDefaulted();
  }

  double StandardGlazing::conductivity() const {
    return getImpl<detail::StandardGlazing_Impl>()->conductivity();
  }

  bool StandardGlazing::isConductivityDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isConductivityDefaulted();
  }

  double StandardGlazing::dirtCorrectionFactorforSolarandVisibleTransmittance() const {
    return getImpl<detail::StandardGlazing_Impl>()->dirtCorrectionFactorforSolarandVisibleTransmittance();
  }

  bool StandardGlazing::isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted();
  }

  bool StandardGlazing::solarDiffusing() const {
    return getImpl<detail::StandardGlazing_Impl>()->solarDiffusing();
  }

  bool StandardGlazing::isSolarDiffusingDefaulted() const {
    return getImpl<detail::StandardGlazing_Impl>()->isSolarDiffusingDefaulted();
  }

  bool StandardGlazing::setOpticalDataType(const std::string& opticalDataType) {
    return getImpl<detail::StandardGlazing_Impl>()->setOpticalDataType(opticalDataType);
  }

  bool StandardGlazing::setThickness(double thickness) {
    return getImpl<detail::StandardGlazing_Impl>()->setThickness(thickness);
  }

  bool StandardGlazing::setSolarTransmittance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setSolarTransmittance(value);
  }

  bool StandardGlazing::setSolarTransmittanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setSolarTransmittanceatNormalIncidence(value);
  }

  void StandardGlazing::resetSolarTransmittanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetSolarTransmittanceatNormalIncidence();
  }

  bool StandardGlazing::setFrontSideSolarReflectanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setFrontSideSolarReflectanceatNormalIncidence(value);
  }

  void StandardGlazing::resetFrontSideSolarReflectanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetFrontSideSolarReflectanceatNormalIncidence();
  }

  bool StandardGlazing::setBackSideSolarReflectanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setBackSideSolarReflectanceatNormalIncidence(value);
  }

  void StandardGlazing::resetBackSideSolarReflectanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetBackSideSolarReflectanceatNormalIncidence();
  }

  bool StandardGlazing::setVisibleTransmittance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setVisibleTransmittance(value);
  }

  bool StandardGlazing::setVisibleTransmittanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setVisibleTransmittanceatNormalIncidence(value);
  }

  void StandardGlazing::resetVisibleTransmittanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetVisibleTransmittanceatNormalIncidence();
  }

  bool StandardGlazing::setFrontSideVisibleReflectanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setFrontSideVisibleReflectanceatNormalIncidence(value);
  }

  void StandardGlazing::resetFrontSideVisibleReflectanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetFrontSideVisibleReflectanceatNormalIncidence();
  }

  bool StandardGlazing::setBackSideVisibleReflectanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setBackSideVisibleReflectanceatNormalIncidence(value);
  }

  void StandardGlazing::resetBackSideVisibleReflectanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetBackSideVisibleReflectanceatNormalIncidence();
  }

  bool StandardGlazing::setInfraredTransmittance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setInfraredTransmittance(value);
  }

  bool StandardGlazing::setInfraredTransmittanceatNormalIncidence(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setInfraredTransmittanceatNormalIncidence(value);
  }

  void StandardGlazing::resetInfraredTransmittanceatNormalIncidence() {
    getImpl<detail::StandardGlazing_Impl>()->resetInfraredTransmittanceatNormalIncidence();
  }

  bool StandardGlazing::setFrontSideInfraredHemisphericalEmissivity(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setFrontSideInfraredHemisphericalEmissivity(value);
  }

  void StandardGlazing::resetFrontSideInfraredHemisphericalEmissivity() {
    getImpl<detail::StandardGlazing_Impl>()->resetFrontSideInfraredHemisphericalEmissivity();
  }

  bool StandardGlazing::setBackSideInfraredHemisphericalEmissivity(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setBackSideInfraredHemisphericalEmissivity(value);
  }

  void StandardGlazing::resetBackSideInfraredHemisphericalEmissivity() {
    getImpl<detail::StandardGlazing_Impl>()->resetBackSideInfraredHemisphericalEmissivity();
  }

  bool StandardGlazing::setConductivity(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setConductivity(value);
  }

  void StandardGlazing::resetConductivity() {
    getImpl<detail::StandardGlazing_Impl>()->resetConductivity();
  }

  bool StandardGlazing::setDirtCorrectionFactorforSolarandVisibleTransmittance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setDirtCorrectionFactorforSolarandVisibleTransmittance(value);
  }

  void StandardGlazing::resetDirtCorrectionFactorforSolarandVisibleTransmittance() {
    getImpl<detail::StandardGlazing_Impl>()->resetDirtCorrectionFactorforSolarandVisibleTransmittance();
  }

  bool StandardGlazing::setSolarDiffusing(bool solarDiffusing) {
    return getImpl<detail::StandardGlazing_Impl>()->setSolarDiffusing(solarDiffusing);
  }

  void StandardGlazing::setSolarDiffusingNoFail(bool solarDiffusing) {
    bool result = getImpl<detail::StandardGlazing_Impl>()->setSolarDiffusing(solarDiffusing);
    OS_ASSERT(result);
  }

  void StandardGlazing::resetSolarDiffusing() {
    getImpl<detail::StandardGlazing_Impl>()->resetSolarDiffusing();
  }

  double StandardGlazing::thermalConductivity() const {
    return getImpl<detail::StandardGlazing_Impl>()->thermalConductivity();
  }

  double StandardGlazing::thermalConductance() const {
    return getImpl<detail::StandardGlazing_Impl>()->thermalConductance();
  }

  double StandardGlazing::thermalResistivity() const {
    return getImpl<detail::StandardGlazing_Impl>()->thermalResistivity();
  }

  double StandardGlazing::thermalResistance() const {
    return getImpl<detail::StandardGlazing_Impl>()->thermalResistance();
  }

  double StandardGlazing::interiorVisibleReflectance() const {
    return getImpl<detail::StandardGlazing_Impl>()->interiorVisibleReflectance();
  }

  double StandardGlazing::exteriorVisibleReflectance() const {
    return getImpl<detail::StandardGlazing_Impl>()->exteriorVisibleReflectance();
  }

  boost::optional<double> StandardGlazing::interiorVisibleAbsorptance() const {
    return getImpl<detail::StandardGlazing_Impl>()->interiorVisibleAbsorptance();
  }

  boost::optional<double> StandardGlazing::exteriorVisibleAbsorptance() const {
    return getImpl<detail::StandardGlazing_Impl>()->exteriorVisibleAbsorptance();
  }

  bool StandardGlazing::setThermalConductivity(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setThermalConductivity(value);
  }

  bool StandardGlazing::setThermalConductance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setThermalConductance(value);
  }

  bool StandardGlazing::setThermalResistivity(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setThermalResistivity(value);
  }

  bool StandardGlazing::setThermalResistance(double value) {
    return getImpl<detail::StandardGlazing_Impl>()->setThermalResistance(value);
  }

}  // namespace epmodel
}  // namespace openstudio
