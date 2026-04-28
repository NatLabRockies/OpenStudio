/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELHUMIDITYSENSOROFFSETOUTDOORAIR_IMPL_HPP
#define EPMODEL_FAULTMODELHUMIDITYSENSOROFFSETOUTDOORAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelHumiditySensorOffsetOutdoorAir_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelHumiditySensorOffsetOutdoorAir_Impl() override = default;

  double humiditySensorOffset() const;
  bool isHumiditySensorOffsetDefaulted() const;
  bool setHumiditySensorOffset(double humiditySensorOffset);
  void resetHumiditySensorOffset();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
