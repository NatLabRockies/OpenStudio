/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELENTHALPYSENSOROFFSETRETURNAIR_IMPL_HPP
#define EPMODEL_FAULTMODELENTHALPYSENSOROFFSETRETURNAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelEnthalpySensorOffsetReturnAir_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelEnthalpySensorOffsetReturnAir_Impl() override = default;

  double enthalpySensorOffset() const;
  bool isEnthalpySensorOffsetDefaulted() const;
  bool setEnthalpySensorOffset(double enthalpySensorOffset);
  void resetEnthalpySensorOffset();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
