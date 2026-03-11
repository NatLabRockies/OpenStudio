/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PIPEADIABATIC_IMPL_HPP
#define EPMODEL_PIPEADIABATIC_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API PipeAdiabatic_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~PipeAdiabatic_Impl() override = default;

  // Pipe:Adiabatic has no type-specific scalar fields; only relationship-like node-link fields.
  unsigned inletPort() const override;
  unsigned outletPort() const override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
