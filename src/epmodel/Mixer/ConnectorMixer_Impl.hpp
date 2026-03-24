/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORMIXER_IMPL_HPP
#define EPMODEL_CONNECTORMIXER_IMPL_HPP

#include "HVACComponent/HVACComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Branch;
namespace detail {

class EPMODEL_API ConnectorMixer_Impl : public HVACComponent_Impl
{
 public:
  using HVACComponent_Impl::HVACComponent_Impl;
  virtual ~ConnectorMixer_Impl() override = default;

  boost::optional<openstudio::epmodel::Branch> outletBranch() const;
  bool setOutletBranch(const openstudio::epmodel::Branch& branch);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
