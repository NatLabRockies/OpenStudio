/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKINTRAZONENODE_HPP
#define EPMODEL_AIRFLOWNETWORKINTRAZONENODE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirflowNetworkIntraZoneNode_Impl;
  }

  class EPMODEL_API AirflowNetworkIntraZoneNode : public ModelObject
  {
   public:
    explicit AirflowNetworkIntraZoneNode(const Model& model);

    virtual ~AirflowNetworkIntraZoneNode() override = default;
    AirflowNetworkIntraZoneNode(const AirflowNetworkIntraZoneNode& other) = default;
    AirflowNetworkIntraZoneNode(AirflowNetworkIntraZoneNode&& other) = default;
    AirflowNetworkIntraZoneNode& operator=(const AirflowNetworkIntraZoneNode&) = default;
    AirflowNetworkIntraZoneNode& operator=(AirflowNetworkIntraZoneNode&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
    // - Field Mapping: nodeHeight maps directly to the EnergyPlus AirflowNetwork:IntraZone:Node
    //   scalar field Node Height.
    // - Field Mapping: RoomAir:Node:AirflowNetwork Name and Zone Name are relationship-like fields
    //   (\object-list target links) and are intentionally excluded from scalar accessors.
    // - TODO(parity): Add typed relationship APIs for linked RoomAir and zone objects after scalar
    //   scaffold saturation.
    double nodeHeight() const;
    bool setNodeHeight(double nodeHeight);
    bool isNodeHeightDefaulted() const;
    void resetNodeHeight();

   protected:
    using ImplType = detail::AirflowNetworkIntraZoneNode_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirflowNetworkIntraZoneNode(std::shared_ptr<detail::AirflowNetworkIntraZoneNode_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
