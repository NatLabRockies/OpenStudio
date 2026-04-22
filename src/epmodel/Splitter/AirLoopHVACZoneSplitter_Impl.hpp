/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONESPLITTER_IMPL_HPP
#define EPMODEL_AIRLOOPHVACZONESPLITTER_IMPL_HPP

#include "Splitter/Splitter_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
namespace detail {

class EPMODEL_API AirLoopHVACZoneSplitter_Impl : public Splitter_Impl
{
 public:
  using Splitter_Impl::Splitter_Impl;
  virtual ~AirLoopHVACZoneSplitter_Impl() override = default;

  unsigned inletPort() const override;
  unsigned outletPort(unsigned branchIndex) const override;
  bool setOutletModelObject(unsigned branchIndex, const openstudio::epmodel::ModelObject& modelObject) override;
  boost::optional<openstudio::epmodel::Node> inletNode() const;
  bool setInletNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
