/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_IMPL_HPP
#define EPMODEL_ZONEHVACEQUIPMENTCONNECTIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {
  class ModelObject;
  class Node;
  class ThermalZone;
  class ZoneHVACEquipmentList;
  namespace detail {
    struct LoadContext;

    class EPMODEL_API ZoneHVACEquipmentConnections_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACEquipmentConnections_Impl() override = default;

      openstudio::epmodel::ThermalZone thermalZone() const;
      openstudio::epmodel::ZoneHVACEquipmentList zoneHVACEquipmentList() const;
      openstudio::epmodel::Node zoneAirNode() const;
      std::vector<openstudio::epmodel::Node> zoneAirInletNodes() const;
      std::vector<openstudio::epmodel::Node> zoneAirExhaustNodes() const;
      std::vector<openstudio::epmodel::Node> zoneReturnAirNodes() const;

      bool setThermalZone(const openstudio::epmodel::ThermalZone& zone);
      bool setZoneHVACEquipmentList(const openstudio::epmodel::ZoneHVACEquipmentList& equipmentList);
      bool addZoneAirInletNode(const openstudio::epmodel::Node& node);
      bool removeZoneAirInletNode(const openstudio::epmodel::Node& node);
      bool addZoneAirExhaustNode(const openstudio::epmodel::Node& node);
      bool removeZoneAirExhaustNode(const openstudio::epmodel::Node& node);
      bool addZoneReturnAirNode(const openstudio::epmodel::Node& node);
      bool removeZoneReturnAirNode(const openstudio::epmodel::Node& node);

     private:
      void doCanonicalize(LoadContext& context) override;

      bool setZoneAirInletNodes(const std::vector<openstudio::epmodel::Node>& nodes);
      bool setZoneAirExhaustNodes(const std::vector<openstudio::epmodel::Node>& nodes);
      bool setZoneReturnAirNodes(const std::vector<openstudio::epmodel::Node>& nodes);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
