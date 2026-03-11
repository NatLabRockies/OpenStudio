/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORK_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirNodeAirflowNetwork_Impl;
  }

  class EPMODEL_API RoomAirNodeAirflowNetwork : public ModelObject
  {
   public:
    explicit RoomAirNodeAirflowNetwork(const Model& model);

    virtual ~RoomAirNodeAirflowNetwork() override = default;
    RoomAirNodeAirflowNetwork(const RoomAirNodeAirflowNetwork& other) = default;
    RoomAirNodeAirflowNetwork(RoomAirNodeAirflowNetwork&& other) = default;
    RoomAirNodeAirflowNetwork& operator=(const RoomAirNodeAirflowNetwork&) = default;
    RoomAirNodeAirflowNetwork& operator=(RoomAirNodeAirflowNetwork&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: RoomAir:Node:AirflowNetwork is a no-counterpart type so the class name and accessor
    //   naming mirror the IDD.
    // - Field Mapping: fractionOfZoneAirVolume maps directly to EnergyPlus RoomAir:Node:AirflowNetwork
    //   Fraction of Zone Air Volume.
    // - Field Mapping: Name remains available via ModelObject base name APIs while Zone Name plus
    //   RoomAir:Node:AirflowNetwork:AdjacentSurfaceList Name, RoomAir:Node:AirflowNetwork:InternalGains Name,
    //   and RoomAir:Node:AirflowNetwork:HVACEquipment Name are relationship-like object lists intentionally
    //   excluded from this scalar-only pass.
    // - TODO(parity): Add typed relationship helpers for the excluded object lists after scalar saturation.
    boost::optional<double> fractionOfZoneAirVolume() const;
    bool isFractionOfZoneAirVolumeDefaulted() const;
    bool setFractionOfZoneAirVolume(double fractionOfZoneAirVolume);
    void resetFractionOfZoneAirVolume();

   protected:
    using ImplType = detail::RoomAirNodeAirflowNetwork_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirNodeAirflowNetwork(std::shared_ptr<detail::RoomAirNodeAirflowNetwork_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
