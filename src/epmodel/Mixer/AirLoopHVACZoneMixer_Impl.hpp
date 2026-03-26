/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONEMIXER_IMPL_HPP
#define EPMODEL_AIRLOOPHVACZONEMIXER_IMPL_HPP

#include "Mixer/Mixer_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API AirLoopHVACZoneMixer_Impl : public Mixer_Impl
{
 public:
  using Mixer_Impl::Mixer_Impl;
  virtual ~AirLoopHVACZoneMixer_Impl() override = default;

  unsigned outletPort() const override;
  unsigned inletPort(unsigned branchIndex) const override;
  boost::optional<openstudio::epmodel::Node> outletNode() const;
  bool setOutletNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
