/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILSYSTEMCOOLINGDX_HPP
#define EPMODEL_COILSYSTEMCOOLINGDX_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilSystemCoolingDX_Impl;
}

class EPMODEL_API CoilSystemCoolingDX : public StraightComponent
{
 public:
  explicit CoilSystemCoolingDX(const Model& model);

  virtual ~CoilSystemCoolingDX() override = default;
  CoilSystemCoolingDX(const CoilSystemCoolingDX& other) = default;
  CoilSystemCoolingDX(CoilSystemCoolingDX&& other) = default;
  CoilSystemCoolingDX& operator=(const CoilSystemCoolingDX&) = default;
  CoilSystemCoolingDX& operator=(CoilSystemCoolingDX&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilSystemCoolingDX_Impl;

  friend class Model;

  explicit CoilSystemCoolingDX(std::shared_ptr<detail::CoilSystemCoolingDX_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
