/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_DUCT_IMPL_HPP
#define EPMODEL_DUCT_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API Duct_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~Duct_Impl() override = default;

  // Duct has no scalar IDD fields; only relationship-like node-link fields.
  unsigned inletPort() const override;
  unsigned outletPort() const override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
