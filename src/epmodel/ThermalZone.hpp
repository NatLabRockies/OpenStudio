/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_THERMALZONE_HPP
#define EPMODEL_THERMALZONE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class SizingZone;

namespace detail {
  class ThermalZone_Impl;
}

class EPMODEL_API ThermalZone : public ModelObject
{
 public:
  explicit ThermalZone(const Model& model);

  virtual ~ThermalZone() override = default;
  ThermalZone(const ThermalZone& other) = default;
  ThermalZone(ThermalZone&& other) = default;
  ThermalZone& operator=(const ThermalZone&) = default;
  ThermalZone& operator=(ThermalZone&&) = default;

  static IddObjectType iddObjectType();
  bool addToNode(Node& node);
  SizingZone sizingZone() const;

 protected:
  using ImplType = detail::ThermalZone_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ThermalZone(std::shared_ptr<detail::ThermalZone_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
