/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_HPP
#define EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

class Model;
class Node;
class ThermalZone;

namespace detail {
class ZoneHVACEquipmentConnections_Impl;
}

class EPMODEL_API ZoneHVACEquipmentConnections : public ModelObject
{
 public:
  explicit ZoneHVACEquipmentConnections(const Model& model);

  virtual ~ZoneHVACEquipmentConnections() override = default;
  ZoneHVACEquipmentConnections(const ZoneHVACEquipmentConnections& other) = default;
  ZoneHVACEquipmentConnections(ZoneHVACEquipmentConnections&& other) = default;
  ZoneHVACEquipmentConnections& operator=(const ZoneHVACEquipmentConnections&) = default;
  ZoneHVACEquipmentConnections& operator=(ZoneHVACEquipmentConnections&&) = default;

  static IddObjectType iddObjectType();

  boost::optional<ThermalZone> thermalZone() const;

  boost::optional<Node> zoneAirInletNode() const;
  std::vector<Node> zoneAirInletNodes() const;

  boost::optional<Node> zoneReturnAirNode() const;
  std::vector<Node> zoneReturnAirNodes() const;

 protected:
  using ImplType = detail::ZoneHVACEquipmentConnections_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class openstudio::epmodel::Model;

  explicit ZoneHVACEquipmentConnections(std::shared_ptr<detail::ZoneHVACEquipmentConnections_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
