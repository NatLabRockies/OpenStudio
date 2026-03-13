/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CURVE_IMPL_HPP
#define EPMODEL_CURVE_IMPL_HPP

#include "EPModelAPI.hpp"
#include "ResourceObject/ResourceObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API Curve_Impl : public ResourceObject_Impl
{
 public:
  Curve_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
  Curve_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
  virtual ~Curve_Impl() override = default;

  virtual int numVariables() const;
  virtual double evaluate(const std::vector<double>& x) const;

  double evaluate(double x) const;
  double evaluate(double x, double y) const;
  double evaluate(double x, double y, double z) const;
  double evaluate(double w, double x, double y, double z) const;
  double evaluate(double v, double w, double x, double y, double z) const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
