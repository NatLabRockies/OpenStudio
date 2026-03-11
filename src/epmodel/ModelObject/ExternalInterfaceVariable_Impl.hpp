/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERNALINTERFACEVARIABLE_IMPL_HPP
#define EPMODEL_EXTERNALINTERFACEVARIABLE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API ExternalInterfaceVariable_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExternalInterfaceVariable_Impl() override = default;

  double initialValue() const;
  bool setInitialValue(double initialValue);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
