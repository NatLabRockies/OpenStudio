/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Material/Material.hpp"
#include "Material/Material_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    double Material_Impl::thickness() const {
      return 0.0;
    }

    bool Material_Impl::setThickness(double /*value*/) {
      return false;
    }

    boost::optional<double> Material_Impl::getVisibleTransmittance() const {
      return boost::none;
    }

    boost::optional<double> Material_Impl::interiorVisibleAbsorptance() const {
      return boost::none;
    }

    boost::optional<double> Material_Impl::exteriorVisibleAbsorptance() const {
      return boost::none;
    }

  }  // namespace detail

  Material::Material(IddObjectType type, const Model& model) : ResourceObject(type, model) {}

  Material::Material(std::shared_ptr<detail::Material_Impl> impl) : ResourceObject(std::move(impl)) {}

  double Material::thickness() const {
    return getImpl<detail::Material_Impl>()->thickness();
  }

  bool Material::setThickness(double value) {
    return getImpl<detail::Material_Impl>()->setThickness(value);
  }

  boost::optional<double> Material::getVisibleTransmittance() const {
    return getImpl<detail::Material_Impl>()->getVisibleTransmittance();
  }

  boost::optional<double> Material::interiorVisibleAbsorptance() const {
    return getImpl<detail::Material_Impl>()->interiorVisibleAbsorptance();
  }

  boost::optional<double> Material::exteriorVisibleAbsorptance() const {
    return getImpl<detail::Material_Impl>()->exteriorVisibleAbsorptance();
  }

}  // namespace epmodel
}  // namespace openstudio
