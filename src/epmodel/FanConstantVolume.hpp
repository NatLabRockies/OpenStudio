/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FANCONSTANTVOLUME_HPP
#define EPMODEL_FANCONSTANTVOLUME_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent/StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
  class FanConstantVolume_Impl;
}

class EPMODEL_API FanConstantVolume : public StraightComponent
{
 public:
  explicit FanConstantVolume(const Model& model);

  virtual ~FanConstantVolume() override = default;
  FanConstantVolume(const FanConstantVolume& other) = default;
  FanConstantVolume(FanConstantVolume&& other) = default;
  FanConstantVolume& operator=(const FanConstantVolume&) = default;
  FanConstantVolume& operator=(FanConstantVolume&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::FanConstantVolume_Impl;

  friend class openstudio::epmodel::Model;

  explicit FanConstantVolume(std::shared_ptr<detail::FanConstantVolume_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
