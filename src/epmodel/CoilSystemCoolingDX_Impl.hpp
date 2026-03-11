/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDX_IMPL_HPP
#define EPMODEL_COILSYSTEMCOOLINGDX_IMPL_HPP

#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
class ModelObject;
namespace detail {

class EPMODEL_API CoilSystemCoolingDX_Impl : public StraightComponent_Impl
{
 public:
  using StraightComponent_Impl::StraightComponent_Impl;
  virtual ~CoilSystemCoolingDX_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort() const override;

  bool addToNode(Node& node);
  boost::optional<ModelObject> coolingCoil() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
