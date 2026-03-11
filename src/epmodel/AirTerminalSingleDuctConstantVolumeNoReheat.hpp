/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP
#define EPMODEL_AIRTERMINALSINGLEDUCTCONSTANTVOLUMENOREHEAT_HPP

#include "EPModelAPI.hpp"
#include "StraightComponent.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;
class Node;

namespace detail {
  class AirTerminalSingleDuctConstantVolumeNoReheat_Impl;
}

class EPMODEL_API AirTerminalSingleDuctConstantVolumeNoReheat : public StraightComponent
{
 public:
  explicit AirTerminalSingleDuctConstantVolumeNoReheat(const Model& model);

  virtual ~AirTerminalSingleDuctConstantVolumeNoReheat() override = default;
  AirTerminalSingleDuctConstantVolumeNoReheat(const AirTerminalSingleDuctConstantVolumeNoReheat& other) = default;
  AirTerminalSingleDuctConstantVolumeNoReheat(AirTerminalSingleDuctConstantVolumeNoReheat&& other) = default;
  AirTerminalSingleDuctConstantVolumeNoReheat& operator=(const AirTerminalSingleDuctConstantVolumeNoReheat&) = default;
  AirTerminalSingleDuctConstantVolumeNoReheat& operator=(AirTerminalSingleDuctConstantVolumeNoReheat&&) = default;

  static IddObjectType iddObjectType();

  bool addToNode(Node& node);

 protected:
  using ImplType = detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl;

  friend class openstudio::epmodel::Model;

  explicit AirTerminalSingleDuctConstantVolumeNoReheat(std::shared_ptr<detail::AirTerminalSingleDuctConstantVolumeNoReheat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
