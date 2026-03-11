/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirNodeAirflowNetwork.hpp"
#include "RoomAirNodeAirflowNetwork_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/RoomAir_Node_AirflowNetwork_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoomAirNodeAirflowNetwork::RoomAirNodeAirflowNetwork(const Model& model) : ModelObject(RoomAirNodeAirflowNetwork::iddObjectType(), model) {}

  RoomAirNodeAirflowNetwork::RoomAirNodeAirflowNetwork(std::shared_ptr<detail::RoomAirNodeAirflowNetwork_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RoomAirNodeAirflowNetwork::iddObjectType() {
    return IddObjectType::RoomAir_Node_AirflowNetwork;
  }

  boost::optional<double> RoomAirNodeAirflowNetwork::fractionOfZoneAirVolume() const {
    return getImpl<detail::RoomAirNodeAirflowNetwork_Impl>()->fractionOfZoneAirVolume();
  }

  bool RoomAirNodeAirflowNetwork::isFractionOfZoneAirVolumeDefaulted() const {
    return getImpl<detail::RoomAirNodeAirflowNetwork_Impl>()->isFractionOfZoneAirVolumeDefaulted();
  }

  bool RoomAirNodeAirflowNetwork::setFractionOfZoneAirVolume(double fractionOfZoneAirVolume) {
    return getImpl<detail::RoomAirNodeAirflowNetwork_Impl>()->setFractionOfZoneAirVolume(fractionOfZoneAirVolume);
  }

  void RoomAirNodeAirflowNetwork::resetFractionOfZoneAirVolume() {
    getImpl<detail::RoomAirNodeAirflowNetwork_Impl>()->resetFractionOfZoneAirVolume();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> RoomAirNodeAirflowNetwork_Impl::fractionOfZoneAirVolume() const {
      return getDouble(openstudio::RoomAir_Node_AirflowNetworkFields::FractionofZoneAirVolume, true);
    }

    bool RoomAirNodeAirflowNetwork_Impl::isFractionOfZoneAirVolumeDefaulted() const {
      return isEmpty(openstudio::RoomAir_Node_AirflowNetworkFields::FractionofZoneAirVolume);
    }

    bool RoomAirNodeAirflowNetwork_Impl::setFractionOfZoneAirVolume(double fractionOfZoneAirVolume) {
      return setDouble(openstudio::RoomAir_Node_AirflowNetworkFields::FractionofZoneAirVolume, fractionOfZoneAirVolume);
    }

    void RoomAirNodeAirflowNetwork_Impl::resetFractionOfZoneAirVolume() {
      OS_ASSERT(setString(openstudio::RoomAir_Node_AirflowNetworkFields::FractionofZoneAirVolume, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
