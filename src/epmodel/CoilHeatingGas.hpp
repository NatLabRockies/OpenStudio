/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILHEATINGGAS_HPP
#define EPMODEL_COILHEATINGGAS_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
class CoilHeatingGas_Impl;
}

class EPMODEL_API CoilHeatingGas : public StraightComponent
{
 public:
  explicit CoilHeatingGas(const Model& model);

  virtual ~CoilHeatingGas() override = default;
  CoilHeatingGas(const CoilHeatingGas& other) = default;
  CoilHeatingGas(CoilHeatingGas&& other) = default;
  CoilHeatingGas& operator=(const CoilHeatingGas&) = default;
  CoilHeatingGas& operator=(CoilHeatingGas&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::CoilHeatingGas_Impl;

  friend class Model;

  explicit CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
