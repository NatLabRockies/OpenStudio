/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABYFACE_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABYFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabYFACE_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabYFACE_Impl() override = default;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
