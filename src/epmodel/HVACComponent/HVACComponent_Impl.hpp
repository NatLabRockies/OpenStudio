/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACCOMPONENT_IMPL_HPP
#define EPMODEL_HVACCOMPONENT_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"
#include "../utilities/idf/IdfObject.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
class Node;
class AirLoopHVAC;
class Loop;
class PlantLoop;
class Splitter;
namespace detail {

class EPMODEL_API HVACComponent_Impl : public ParentObject_Impl
{
 public:
  using ParentObject_Impl::ParentObject_Impl;
  virtual ~HVACComponent_Impl() override = default;

  virtual boost::optional<Loop> loop() const;
  virtual boost::optional<AirLoopHVAC> airLoopHVAC() const;
  virtual boost::optional<PlantLoop> plantLoop() const;

  virtual bool addToNode(Node& node);
  virtual bool addToSplitter(Splitter& splitter);
  virtual void disconnect();
  virtual bool isRemovable() const;
  virtual std::vector<IdfObject> remove();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
