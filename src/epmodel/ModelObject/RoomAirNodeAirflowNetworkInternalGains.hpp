/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRNODEAIRFLOWNETWORKINTERNALGAINS_HPP
#define EPMODEL_ROOMAIRNODEAIRFLOWNETWORKINTERNALGAINS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirNodeAirflowNetworkInternalGains_Impl;
  }

  class EPMODEL_API RoomAirNodeAirflowNetworkInternalGains : public ModelObject
  {
   public:
    explicit RoomAirNodeAirflowNetworkInternalGains(const Model& model);

    virtual ~RoomAirNodeAirflowNetworkInternalGains() override = default;
    RoomAirNodeAirflowNetworkInternalGains(const RoomAirNodeAirflowNetworkInternalGains& other) = default;
    RoomAirNodeAirflowNetworkInternalGains(RoomAirNodeAirflowNetworkInternalGains&& other) = default;
    RoomAirNodeAirflowNetworkInternalGains& operator=(const RoomAirNodeAirflowNetworkInternalGains&) = default;
    RoomAirNodeAirflowNetworkInternalGains& operator=(RoomAirNodeAirflowNetworkInternalGains&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: RoomAir:Node:AirflowNetwork:InternalGains has no openstudio::model counterpart so the class name mirrors the IDD.
    // - Field Mapping: Name remains available through the base ModelObject scalar API while the internal-gain extensible
    //   groups (Internal Gain Object Type/Name/Fraction of Gains) represent relationship-like references and stay excluded
    //   from this scalar-only pass. The scalar fields for Internal Gain Object 1 Type/Name and Fraction of Gains to Node 1 are
    //   exposed through this API.
    // - TODO(parity): Add typed helpers for the extensible internal-gain entries and RoomAirNodeGains linkage once scalar
    //   saturation is complete.

    boost::optional<std::string> internalGainObject1Type() const;
    bool setInternalGainObject1Type(const std::string& internalGainObject1Type);
    void resetInternalGainObject1Type();

    boost::optional<std::string> internalGainObject1Name() const;
    bool setInternalGainObject1Name(const std::string& internalGainObject1Name);
    void resetInternalGainObject1Name();

    boost::optional<double> fractionOfGainsToNode1() const;
    bool setFractionOfGainsToNode1(double fractionOfGainsToNode1);
    void resetFractionOfGainsToNode1();

   protected:
    using ImplType = detail::RoomAirNodeAirflowNetworkInternalGains_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirNodeAirflowNetworkInternalGains(std::shared_ptr<detail::RoomAirNodeAirflowNetworkInternalGains_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
