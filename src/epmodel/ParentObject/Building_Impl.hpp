/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BUILDING_IMPL_HPP
#define EPMODEL_BUILDING_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API Building_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~Building_Impl() override = default;

  double northAxis() const;
  bool isNorthAxisDefaulted() const;
  bool setNorthAxis(double northAxis);
  void resetNorthAxis();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
