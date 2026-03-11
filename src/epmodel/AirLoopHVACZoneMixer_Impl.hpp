/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONEMIXER_IMPL_HPP
#define EPMODEL_AIRLOOPHVACZONEMIXER_IMPL_HPP

#include "HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API AirLoopHVACZoneMixer_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~AirLoopHVACZoneMixer_Impl() override = default;

  boost::optional<openstudio::epmodel::Node> outletNode() const;
  bool setOutletNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
