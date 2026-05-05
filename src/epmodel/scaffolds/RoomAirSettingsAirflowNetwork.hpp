/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSAIRFLOWNETWORK_HPP
#define EPMODEL_ROOMAIRSETTINGSAIRFLOWNETWORK_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirSettingsAirflowNetwork_Impl;
  }

  class EPMODEL_API RoomAirSettingsAirflowNetwork : public ModelObject
  {
   public:
    explicit RoomAirSettingsAirflowNetwork(const Model& model);

    virtual ~RoomAirSettingsAirflowNetwork() override = default;
    RoomAirSettingsAirflowNetwork(const RoomAirSettingsAirflowNetwork& other) = default;
    RoomAirSettingsAirflowNetwork(RoomAirSettingsAirflowNetwork&& other) = default;
    RoomAirSettingsAirflowNetwork& operator=(const RoomAirSettingsAirflowNetwork&) = default;
    RoomAirSettingsAirflowNetwork& operator=(RoomAirSettingsAirflowNetwork&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart epmodel type uses IDD-derived class naming.
    // - Field Mapping: Name remains available via base ModelObject name APIs.
    // - Field Mapping: Zone Name, Control Point RoomAirflowNetwork:Node Name, and extensible
    //   RoomAirflowNetwork:Node Name are relationship-like object-list fields and intentionally
    //   excluded from scalar accessors in this scaffold pass.
    // - TODO(parity): Add typed relationship APIs after scalar scaffold saturation.

   protected:
    using ImplType = detail::RoomAirSettingsAirflowNetwork_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirSettingsAirflowNetwork(std::shared_ptr<detail::RoomAirSettingsAirflowNetwork_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
