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

    class EPMODEL_API ZoneHVACEquipmentConnections_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneHVACEquipmentConnections_Impl() override = default;

      boost::optional<openstudio::epmodel::ThermalZone> thermalZone() const;
      boost::optional<openstudio::epmodel::ZoneHVACEquipmentList> zoneHVACEquipmentList() const;
      boost::optional<openstudio::epmodel::Node> zoneAirNode() const;
      std::vector<openstudio::epmodel::Node> zoneAirInletNodes() const;
      std::vector<openstudio::epmodel::Node> zoneAirExhaustNodes() const;
      std::vector<openstudio::epmodel::Node> zoneReturnAirNodes() const;

      bool setThermalZone(const openstudio::epmodel::ThermalZone& zone);
      bool setZoneHVACEquipmentList(const openstudio::epmodel::ZoneHVACEquipmentList& equipmentList);
      bool setZoneAirNode(const openstudio::epmodel::Node& node);
      bool addEquipment(const openstudio::epmodel::ModelObject& equipment, const std::vector<openstudio::epmodel::Node>& inletNodes,
                        const std::vector<openstudio::epmodel::Node>& exhaustNodes,
                        const std::vector<openstudio::epmodel::Node>& returnNodes);
      bool removeEquipment(const openstudio::epmodel::ModelObject& equipment, const std::vector<openstudio::epmodel::Node>& inletNodes,
                           const std::vector<openstudio::epmodel::Node>& exhaustNodes,
                           const std::vector<openstudio::epmodel::Node>& returnNodes);
      bool addZoneAirInletNode(const openstudio::epmodel::Node& node);
      bool removeZoneAirInletNode(const openstudio::epmodel::Node& node);
      bool addZoneAirExhaustNode(const openstudio::epmodel::Node& node);
      bool removeZoneAirExhaustNode(const openstudio::epmodel::Node& node);
      bool addZoneReturnAirNode(const openstudio::epmodel::Node& node);
      bool removeZoneReturnAirNode(const openstudio::epmodel::Node& node);

     private:
      bool setZoneAirInletNodes(const std::vector<openstudio::epmodel::Node>& nodes);
      bool setZoneAirExhaustNodes(const std::vector<openstudio::epmodel::Node>& nodes);
      bool setZoneReturnAirNodes(const std::vector<openstudio::epmodel::Node>& nodes);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
