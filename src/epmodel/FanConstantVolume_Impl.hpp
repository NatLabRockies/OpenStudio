/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_IMPL_HPP
#define EPMODEL_FANCONSTANTVOLUME_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"
#include "Node.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API FanConstantVolume_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~FanConstantVolume_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  bool addToNode(Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
