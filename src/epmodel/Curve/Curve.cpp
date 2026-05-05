/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "Curve/Curve.hpp"
#include "Curve/Curve_Impl.hpp"

namespace openstudio {
namespace epmodel {

  Curve::Curve(IddObjectType type, const Model& model) : ResourceObject(type, model) {}

  Curve::Curve(std::shared_ptr<ImplType> impl) : ResourceObject(std::static_pointer_cast<detail::ResourceObject_Impl>(std::move(impl))) {}

  int Curve::numVariables() const {
    return getImpl<detail::Curve_Impl>()->numVariables();
  }

  double Curve::evaluate(const std::vector<double>& x) const {
    return getImpl<detail::Curve_Impl>()->evaluate(x);
  }

  double Curve::evaluate(double x) const {
    return getImpl<detail::Curve_Impl>()->evaluate(x);
  }

  double Curve::evaluate(double x, double y) const {
    return getImpl<detail::Curve_Impl>()->evaluate(x, y);
  }

  double Curve::evaluate(double x, double y, double z) const {
    return getImpl<detail::Curve_Impl>()->evaluate(x, y, z);
  }

  double Curve::evaluate(double w, double x, double y, double z) const {
    return getImpl<detail::Curve_Impl>()->evaluate(w, x, y, z);
  }

  double Curve::evaluate(double v, double w, double x, double y, double z) const {
    return getImpl<detail::Curve_Impl>()->evaluate(v, w, x, y, z);
  }

}  // namespace epmodel
}  // namespace openstudio
