/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_NODE_IMPL_HPP
#define EPMODEL_NODE_IMPL_HPP

#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class Model;
namespace detail {
  class Model_Impl;
}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API Node_Impl : public StraightComponent_Impl
{
 public:
  Node_Impl(const openstudio::IdfObject& idfObject, Model_Impl* model, bool keepHandle);
  Node_Impl(const openstudio::detail::WorkspaceObject_Impl& other, Model_Impl* model, bool keepHandle);
  Node_Impl(const Node_Impl& other, Model_Impl* model, bool keepHandle);
  virtual ~Node_Impl() override = default;

  boost::optional<AirLoopHVAC> airLoopHVAC() const override;
  boost::optional<ModelObject> inletModelObject() const override;
  boost::optional<ModelObject> outletModelObject() const override;

  unsigned inletPort() const override;
  unsigned outletPort() const override;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
