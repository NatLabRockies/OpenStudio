/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONESPLITTER_IMPL_HPP
#define EPMODEL_AIRLOOPHVACZONESPLITTER_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API AirLoopHVACZoneSplitter_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~AirLoopHVACZoneSplitter_Impl() override = default;

  boost::optional<openstudio::epmodel::Node> inletNode() const;
  bool setInletNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
