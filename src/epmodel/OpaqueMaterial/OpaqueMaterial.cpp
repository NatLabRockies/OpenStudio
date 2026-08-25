/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OpaqueMaterial/OpaqueMaterial.hpp"
#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    double OpaqueMaterial_Impl::thermalConductivity() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setThermalConductivity(double /*value*/) {
      return false;
    }

    double OpaqueMaterial_Impl::thermalConductance() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setThermalConductance(double /*value*/) {
      return false;
    }

    double OpaqueMaterial_Impl::thermalResistivity() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setThermalResistivity(double /*value*/) {
      return false;
    }

    double OpaqueMaterial_Impl::thermalAbsorptance() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setThermalAbsorptance(double /*value*/) {
      return false;
    }

    boost::optional<double> OpaqueMaterial_Impl::thermalReflectance() const {
      return boost::none;
    }

    bool OpaqueMaterial_Impl::setThermalReflectance(boost::optional<double> /*value*/) {
      return false;
    }

    double OpaqueMaterial_Impl::solarAbsorptance() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setSolarAbsorptance(boost::optional<double> /*value*/) {
      return false;
    }

    boost::optional<double> OpaqueMaterial_Impl::solarReflectance() const {
      return boost::none;
    }

    bool OpaqueMaterial_Impl::setSolarReflectance(boost::optional<double> /*value*/) {
      return false;
    }

    double OpaqueMaterial_Impl::visibleAbsorptance() const {
      return 0.0;
    }

    bool OpaqueMaterial_Impl::setVisibleAbsorptance(boost::optional<double> /*value*/) {
      return false;
    }

    boost::optional<double> OpaqueMaterial_Impl::visibleReflectance() const {
      return boost::none;
    }

    bool OpaqueMaterial_Impl::setVisibleReflectance(boost::optional<double> /*value*/) {
      return false;
    }

    boost::optional<double> OpaqueMaterial_Impl::heatCapacity() const {
      return boost::none;
    }

    boost::optional<double> OpaqueMaterial_Impl::getVisibleTransmittance() const {
      return 0.0;
    }

    boost::optional<double> OpaqueMaterial_Impl::interiorVisibleAbsorptance() const {
      return visibleAbsorptance();
    }

    boost::optional<double> OpaqueMaterial_Impl::exteriorVisibleAbsorptance() const {
      return visibleAbsorptance();
    }

  }  // namespace detail

  OpaqueMaterial::OpaqueMaterial(IddObjectType type, const Model& model) : Material(type, model) {}

  OpaqueMaterial::OpaqueMaterial(std::shared_ptr<detail::OpaqueMaterial_Impl> impl) : Material(std::move(impl)) {}

  double OpaqueMaterial::thermalConductivity() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalConductivity();
  }

  bool OpaqueMaterial::setThermalConductivity(double value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalConductivity(value);
  }

  double OpaqueMaterial::thermalConductance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalConductance();
  }

  bool OpaqueMaterial::setThermalConductance(double value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalConductance(value);
  }

  double OpaqueMaterial::thermalResistivity() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalResistivity();
  }

  bool OpaqueMaterial::setThermalResistivity(double value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalResistivity(value);
  }

  double OpaqueMaterial::thermalResistance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalResistance();
  }

  bool OpaqueMaterial::setThermalResistance(double value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalResistance(value);
  }

  double OpaqueMaterial::thermalAbsorptance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalAbsorptance();
  }

  bool OpaqueMaterial::setThermalAbsorptance(double value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalAbsorptance(value);
  }

  boost::optional<double> OpaqueMaterial::thermalReflectance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->thermalReflectance();
  }

  bool OpaqueMaterial::setThermalReflectance(boost::optional<double> value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setThermalReflectance(value);
  }

  double OpaqueMaterial::solarAbsorptance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->solarAbsorptance();
  }

  bool OpaqueMaterial::setSolarAbsorptance(boost::optional<double> value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setSolarAbsorptance(value);
  }

  boost::optional<double> OpaqueMaterial::solarReflectance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->solarReflectance();
  }

  bool OpaqueMaterial::setSolarReflectance(boost::optional<double> value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setSolarReflectance(value);
  }

  double OpaqueMaterial::visibleAbsorptance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->visibleAbsorptance();
  }

  bool OpaqueMaterial::setVisibleAbsorptance(boost::optional<double> value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setVisibleAbsorptance(value);
  }

  boost::optional<double> OpaqueMaterial::visibleReflectance() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->visibleReflectance();
  }

  bool OpaqueMaterial::setVisibleReflectance(boost::optional<double> value) {
    return getImpl<detail::OpaqueMaterial_Impl>()->setVisibleReflectance(value);
  }

  boost::optional<double> OpaqueMaterial::heatCapacity() const {
    return getImpl<detail::OpaqueMaterial_Impl>()->heatCapacity();
  }

}  // namespace epmodel
}  // namespace openstudio
