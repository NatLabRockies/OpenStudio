/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_IMPL_HPP
#define EPMODEL_HEATEXCHANGERDESICCANTBALANCEDFLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HeatExchangerDesiccantBalancedFlow_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HeatExchangerDesiccantBalancedFlow_Impl() override = default;

  bool economizerLockout() const;

  bool setEconomizerLockout(bool economizerLockout);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
