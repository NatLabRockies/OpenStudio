/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_IMPL_HPP
#define EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
class Node;
class ThermalZone;
namespace detail {

class EPMODEL_API ZoneHVACEquipmentConnections_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ZoneHVACEquipmentConnections_Impl() override = default;

  bool setThermalZone(const openstudio::epmodel::ThermalZone& zone);
  bool setZoneAirInletNode(const openstudio::epmodel::Node& node);
  bool setZoneReturnAirNode(const openstudio::epmodel::Node& node);
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
