/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Glazing/RefractionExtinctionGlazing.hpp"
#include "Glazing/RefractionExtinctionGlazing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/Compare.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_Glazing_RefractionExtinctionMethod_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    double RefractionExtinctionGlazing_Impl::thickness() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::setThickness(double thickness) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Thickness, thickness);
    }

    double RefractionExtinctionGlazing_Impl::solarIndexofRefraction() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarIndexofRefraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::setSolarIndexofRefraction(double solarIndexofRefraction) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarIndexofRefraction, solarIndexofRefraction);
    }

    double RefractionExtinctionGlazing_Impl::solarExtinctionCoefficient() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarExtinctionCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::setSolarExtinctionCoefficient(double solarExtinctionCoefficient) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarExtinctionCoefficient, solarExtinctionCoefficient);
    }

    double RefractionExtinctionGlazing_Impl::visibleIndexofRefraction() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleIndexofRefraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::setVisibleIndexofRefraction(double visibleIndexofRefraction) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleIndexofRefraction, visibleIndexofRefraction);
    }

    double RefractionExtinctionGlazing_Impl::visibleExtinctionCoefficient() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleExtinctionCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::setVisibleExtinctionCoefficient(double visibleExtinctionCoefficient) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleExtinctionCoefficient, visibleExtinctionCoefficient);
    }

    double RefractionExtinctionGlazing_Impl::infraredTransmittanceatNormalIncidence() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredTransmittanceatNormalIncidence, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::isInfraredTransmittanceatNormalIncidenceDefaulted() const {
      return isEmpty(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredTransmittanceatNormalIncidence);
    }

    bool RefractionExtinctionGlazing_Impl::setInfraredTransmittanceatNormalIncidence(double infraredTransmittanceatNormalIncidence) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredTransmittanceatNormalIncidence,
                       infraredTransmittanceatNormalIncidence);
    }

    void RefractionExtinctionGlazing_Impl::resetInfraredTransmittanceatNormalIncidence() {
      OS_ASSERT(setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredTransmittanceatNormalIncidence, ""));
    }

    double RefractionExtinctionGlazing_Impl::infraredHemisphericalEmissivity() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredHemisphericalEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::isInfraredHemisphericalEmissivityDefaulted() const {
      return isEmpty(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredHemisphericalEmissivity);
    }

    bool RefractionExtinctionGlazing_Impl::setInfraredHemisphericalEmissivity(double infraredHemisphericalEmissivity) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredHemisphericalEmissivity, infraredHemisphericalEmissivity);
    }

    void RefractionExtinctionGlazing_Impl::resetInfraredHemisphericalEmissivity() {
      OS_ASSERT(setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredHemisphericalEmissivity, ""));
    }

    double RefractionExtinctionGlazing_Impl::conductivity() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Conductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::isConductivityDefaulted() const {
      return isEmpty(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Conductivity);
    }

    bool RefractionExtinctionGlazing_Impl::setConductivity(double conductivity) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Conductivity, conductivity);
    }

    void RefractionExtinctionGlazing_Impl::resetConductivity() {
      OS_ASSERT(setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::Conductivity, ""));
    }

    double RefractionExtinctionGlazing_Impl::dirtCorrectionFactorforSolarandVisibleTransmittance() const {
      auto value = getDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::DirtCorrectionFactorforSolarandVisibleTransmittance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RefractionExtinctionGlazing_Impl::isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const {
      return isEmpty(WindowMaterial_Glazing_RefractionExtinctionMethodFields::DirtCorrectionFactorforSolarandVisibleTransmittance);
    }

    bool RefractionExtinctionGlazing_Impl::setDirtCorrectionFactorforSolarandVisibleTransmittance(double dirtCorrectionFactor) {
      return setDouble(WindowMaterial_Glazing_RefractionExtinctionMethodFields::DirtCorrectionFactorforSolarandVisibleTransmittance,
                       dirtCorrectionFactor);
    }

    void RefractionExtinctionGlazing_Impl::resetDirtCorrectionFactorforSolarandVisibleTransmittance() {
      OS_ASSERT(setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::DirtCorrectionFactorforSolarandVisibleTransmittance, ""));
    }

    bool RefractionExtinctionGlazing_Impl::solarDiffusing() const {
      auto value = getString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarDiffusing, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool RefractionExtinctionGlazing_Impl::isSolarDiffusingDefaulted() const {
      return isEmpty(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarDiffusing);
    }

    bool RefractionExtinctionGlazing_Impl::setSolarDiffusing(bool solarDiffusing) {
      return setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarDiffusing, solarDiffusing ? "Yes" : "No");
    }

    void RefractionExtinctionGlazing_Impl::resetSolarDiffusing() {
      OS_ASSERT(setString(WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarDiffusing, ""));
    }

  }  // namespace detail

  RefractionExtinctionGlazing::RefractionExtinctionGlazing(const Model& model, double thickness, double solarIndexofRefraction,
                                                           double solarExtinctionCoefficient, double visibleIndexofRefraction,
                                                           double visibleExtinctionCoefficient)
    : Material(RefractionExtinctionGlazing::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RefractionExtinctionGlazing_Impl>());

    bool ok = true;
    ok = setThickness(thickness);
    OS_ASSERT(ok);
    ok = setSolarIndexofRefraction(solarIndexofRefraction);
    OS_ASSERT(ok);
    ok = setSolarExtinctionCoefficient(solarExtinctionCoefficient);
    OS_ASSERT(ok);
    ok = setVisibleIndexofRefraction(visibleIndexofRefraction);
    OS_ASSERT(ok);
    ok = setVisibleExtinctionCoefficient(visibleExtinctionCoefficient);
    OS_ASSERT(ok);
  }

  RefractionExtinctionGlazing::RefractionExtinctionGlazing(std::shared_ptr<detail::RefractionExtinctionGlazing_Impl> impl)
    : Material(std::move(impl)) {}

  IddObjectType RefractionExtinctionGlazing::iddObjectType() {
    return IddObjectType::WindowMaterial_Glazing_RefractionExtinctionMethod;
  }

  double RefractionExtinctionGlazing::thickness() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->thickness();
  }

  bool RefractionExtinctionGlazing::setThickness(double thickness) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setThickness(thickness);
  }

  double RefractionExtinctionGlazing::solarIndexofRefraction() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->solarIndexofRefraction();
  }

  bool RefractionExtinctionGlazing::setSolarIndexofRefraction(double solarIndexofRefraction) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setSolarIndexofRefraction(solarIndexofRefraction);
  }

  double RefractionExtinctionGlazing::solarExtinctionCoefficient() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->solarExtinctionCoefficient();
  }

  bool RefractionExtinctionGlazing::setSolarExtinctionCoefficient(double solarExtinctionCoefficient) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setSolarExtinctionCoefficient(solarExtinctionCoefficient);
  }

  double RefractionExtinctionGlazing::visibleIndexofRefraction() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->visibleIndexofRefraction();
  }

  bool RefractionExtinctionGlazing::setVisibleIndexofRefraction(double visibleIndexofRefraction) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setVisibleIndexofRefraction(visibleIndexofRefraction);
  }

  double RefractionExtinctionGlazing::visibleExtinctionCoefficient() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->visibleExtinctionCoefficient();
  }

  bool RefractionExtinctionGlazing::setVisibleExtinctionCoefficient(double visibleExtinctionCoefficient) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setVisibleExtinctionCoefficient(visibleExtinctionCoefficient);
  }

  double RefractionExtinctionGlazing::infraredTransmittanceatNormalIncidence() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->infraredTransmittanceatNormalIncidence();
  }

  bool RefractionExtinctionGlazing::isInfraredTransmittanceatNormalIncidenceDefaulted() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->isInfraredTransmittanceatNormalIncidenceDefaulted();
  }

  bool RefractionExtinctionGlazing::setInfraredTransmittanceatNormalIncidence(double infraredTransmittanceatNormalIncidence) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setInfraredTransmittanceatNormalIncidence(infraredTransmittanceatNormalIncidence);
  }

  void RefractionExtinctionGlazing::resetInfraredTransmittanceatNormalIncidence() {
    getImpl<detail::RefractionExtinctionGlazing_Impl>()->resetInfraredTransmittanceatNormalIncidence();
  }

  double RefractionExtinctionGlazing::infraredHemisphericalEmissivity() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->infraredHemisphericalEmissivity();
  }

  bool RefractionExtinctionGlazing::isInfraredHemisphericalEmissivityDefaulted() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->isInfraredHemisphericalEmissivityDefaulted();
  }

  bool RefractionExtinctionGlazing::setInfraredHemisphericalEmissivity(double infraredHemisphericalEmissivity) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setInfraredHemisphericalEmissivity(infraredHemisphericalEmissivity);
  }

  void RefractionExtinctionGlazing::resetInfraredHemisphericalEmissivity() {
    getImpl<detail::RefractionExtinctionGlazing_Impl>()->resetInfraredHemisphericalEmissivity();
  }

  double RefractionExtinctionGlazing::conductivity() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->conductivity();
  }

  bool RefractionExtinctionGlazing::isConductivityDefaulted() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->isConductivityDefaulted();
  }

  bool RefractionExtinctionGlazing::setConductivity(double conductivity) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setConductivity(conductivity);
  }

  void RefractionExtinctionGlazing::resetConductivity() {
    getImpl<detail::RefractionExtinctionGlazing_Impl>()->resetConductivity();
  }

  double RefractionExtinctionGlazing::dirtCorrectionFactorforSolarandVisibleTransmittance() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->dirtCorrectionFactorforSolarandVisibleTransmittance();
  }

  bool RefractionExtinctionGlazing::isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted();
  }

  bool RefractionExtinctionGlazing::setDirtCorrectionFactorforSolarandVisibleTransmittance(double dirtCorrectionFactor) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setDirtCorrectionFactorforSolarandVisibleTransmittance(dirtCorrectionFactor);
  }

  void RefractionExtinctionGlazing::resetDirtCorrectionFactorforSolarandVisibleTransmittance() {
    getImpl<detail::RefractionExtinctionGlazing_Impl>()->resetDirtCorrectionFactorforSolarandVisibleTransmittance();
  }

  bool RefractionExtinctionGlazing::solarDiffusing() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->solarDiffusing();
  }

  bool RefractionExtinctionGlazing::isSolarDiffusingDefaulted() const {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->isSolarDiffusingDefaulted();
  }

  bool RefractionExtinctionGlazing::setSolarDiffusing(bool solarDiffusing) {
    return getImpl<detail::RefractionExtinctionGlazing_Impl>()->setSolarDiffusing(solarDiffusing);
  }

  void RefractionExtinctionGlazing::setSolarDiffusingNoFail(bool solarDiffusing) {
    bool result = setSolarDiffusing(solarDiffusing);
    OS_ASSERT(result);
  }

  void RefractionExtinctionGlazing::resetSolarDiffusing() {
    getImpl<detail::RefractionExtinctionGlazing_Impl>()->resetSolarDiffusing();
  }

}  // namespace epmodel
}  // namespace openstudio
