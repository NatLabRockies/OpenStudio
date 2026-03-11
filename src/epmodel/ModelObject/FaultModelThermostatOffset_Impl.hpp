/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTHERMOSTATOFFSET_IMPL_HPP
#define EPMODEL_FAULTMODELTHERMOSTATOFFSET_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FaultModelThermostatOffset_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~FaultModelThermostatOffset_Impl() override = default;

  double referenceThermostatOffset() const;
  bool isReferenceThermostatOffsetDefaulted() const;
  bool setReferenceThermostatOffset(double referenceThermostatOffset);
  void resetReferenceThermostatOffset();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
