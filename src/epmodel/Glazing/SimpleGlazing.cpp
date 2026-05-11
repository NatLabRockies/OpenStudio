/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Glazing/SimpleGlazing.hpp"
#include "Glazing/SimpleGlazing_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/WindowMaterial_SimpleGlazingSystem_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  namespace detail {

    double SimpleGlazing_Impl::uFactor() const {
      auto value = getDouble(WindowMaterial_SimpleGlazingSystemFields::UFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SimpleGlazing_Impl::setUFactor(double uFactor) {
      return setDouble(WindowMaterial_SimpleGlazingSystemFields::UFactor, uFactor);
    }

    double SimpleGlazing_Impl::solarHeatGainCoefficient() const {
      auto value = getDouble(WindowMaterial_SimpleGlazingSystemFields::SolarHeatGainCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SimpleGlazing_Impl::setSolarHeatGainCoefficient(double solarHeatGainCoefficient) {
      return setDouble(WindowMaterial_SimpleGlazingSystemFields::SolarHeatGainCoefficient, solarHeatGainCoefficient);
    }

    boost::optional<double> SimpleGlazing_Impl::visibleTransmittance() const {
      return getDouble(WindowMaterial_SimpleGlazingSystemFields::VisibleTransmittance, true);
    }

    bool SimpleGlazing_Impl::setVisibleTransmittance(boost::optional<double> visibleTransmittance) {
      bool result(false);
      if (visibleTransmittance) {
        result = setDouble(WindowMaterial_SimpleGlazingSystemFields::VisibleTransmittance, visibleTransmittance.get());
      } else {
        resetVisibleTransmittance();
        result = true;
      }
      return result;
    }

    void SimpleGlazing_Impl::resetVisibleTransmittance() {
      const bool result = setString(WindowMaterial_SimpleGlazingSystemFields::VisibleTransmittance, "");
      OS_ASSERT(result);
    }

  }  // namespace detail

  SimpleGlazing::SimpleGlazing(const Model& model, double uFactor, double solarHeatGainCoefficient)
    : Material(SimpleGlazing::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SimpleGlazing_Impl>());

    bool ok = true;
    ok = setUFactor(uFactor);
    OS_ASSERT(ok);
    ok = setSolarHeatGainCoefficient(solarHeatGainCoefficient);
    OS_ASSERT(ok);
  }

  SimpleGlazing::SimpleGlazing(std::shared_ptr<detail::SimpleGlazing_Impl> impl) : Material(std::move(impl)) {}

  IddObjectType SimpleGlazing::iddObjectType() {
    return {IddObjectType::WindowMaterial_SimpleGlazingSystem};
  }

  double SimpleGlazing::uFactor() const {
    return getImpl<detail::SimpleGlazing_Impl>()->uFactor();
  }

  bool SimpleGlazing::setUFactor(double uFactor) {
    return getImpl<detail::SimpleGlazing_Impl>()->setUFactor(uFactor);
  }

  double SimpleGlazing::solarHeatGainCoefficient() const {
    return getImpl<detail::SimpleGlazing_Impl>()->solarHeatGainCoefficient();
  }

  bool SimpleGlazing::setSolarHeatGainCoefficient(double solarHeatGainCoefficient) {
    return getImpl<detail::SimpleGlazing_Impl>()->setSolarHeatGainCoefficient(solarHeatGainCoefficient);
  }

  boost::optional<double> SimpleGlazing::visibleTransmittance() const {
    return getImpl<detail::SimpleGlazing_Impl>()->visibleTransmittance();
  }

  bool SimpleGlazing::setVisibleTransmittance(double visibleTransmittance) {
    return getImpl<detail::SimpleGlazing_Impl>()->setVisibleTransmittance(visibleTransmittance);
  }

  void SimpleGlazing::resetVisibleTransmittance() {
    getImpl<detail::SimpleGlazing_Impl>()->resetVisibleTransmittance();
  }

}  // namespace epmodel
}  // namespace openstudio
