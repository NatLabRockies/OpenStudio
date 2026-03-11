/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGDXSINGLESPEED_HPP
#define EPMODEL_COILCOOLINGDXSINGLESPEED_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilCoolingDXSingleSpeed_Impl;
}

class EPMODEL_API CoilCoolingDXSingleSpeed : public StraightComponent
{
 public:
  explicit CoilCoolingDXSingleSpeed(const Model& model);

  virtual ~CoilCoolingDXSingleSpeed() override = default;
  CoilCoolingDXSingleSpeed(const CoilCoolingDXSingleSpeed& other) = default;
  CoilCoolingDXSingleSpeed(CoilCoolingDXSingleSpeed&& other) = default;
  CoilCoolingDXSingleSpeed& operator=(const CoilCoolingDXSingleSpeed&) = default;
  CoilCoolingDXSingleSpeed& operator=(CoilCoolingDXSingleSpeed&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilCoolingDXSingleSpeed_Impl;

  friend class Model;

  explicit CoilCoolingDXSingleSpeed(std::shared_ptr<detail::CoilCoolingDXSingleSpeed_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
