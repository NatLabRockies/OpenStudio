/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILUSERDEFINED_IMPL_HPP
#define EPMODEL_COILUSERDEFINED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API CoilUserDefined_Impl : public ModelObject_Impl
{
 public:
  // Scalar-only scaffold: relationship-like fields are intentionally excluded for this cycle.
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~CoilUserDefined_Impl() override = default;

  int numberofAirConnections() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
