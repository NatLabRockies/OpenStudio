/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PLANTLOOP_IMPL_HPP
#define EPMODEL_PLANTLOOP_IMPL_HPP

#include "Loop/Loop_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API PlantLoop_Impl : public Loop_Impl
{
 public:
  using Loop_Impl::Loop_Impl;
  virtual ~PlantLoop_Impl() override = default;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
