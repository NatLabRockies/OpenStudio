/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_NODE_HPP
#define EPMODEL_NODE_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
  class Node_Impl;
}

class EPMODEL_API Node : public StraightComponent
{
 public:
  virtual ~Node() = default;
  Node(const Node& other) = default;
  Node(Node&& other) = default;
  Node& operator=(const Node&) = default;
  Node& operator=(Node&&) = default;
  explicit Node(const Model& model);

  static IddObjectType iddObjectType();

 protected:
  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  using ImplType = detail::Node_Impl;

  explicit Node(std::shared_ptr<detail::Node_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
