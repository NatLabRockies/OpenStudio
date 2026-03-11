/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_IMPL_HPP
#define EPMODEL_FFACTORGROUNDFLOORCONSTRUCTION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FFactorGroundFloorConstruction_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FFactorGroundFloorConstruction_Impl() override = default;

  double fFactor() const;
  bool setFFactor(double fFactor);

  double area() const;
  bool setArea(double area);

  double perimeterExposed() const;
  bool setPerimeterExposed(double perimeterExposed);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
