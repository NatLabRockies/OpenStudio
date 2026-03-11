/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_IMPL_HPP
#define EPMODEL_HVACCOMPONENT_IMPL_HPP

#include "ParentObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
class AirLoopHVAC;
class Loop;
namespace detail {

class EPMODEL_API HVACComponent_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~HVACComponent_Impl() override = default;

  virtual boost::optional<Loop> loop() const;
 virtual boost::optional<AirLoopHVAC> airLoopHVAC() const;

 virtual bool addToNode(Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
