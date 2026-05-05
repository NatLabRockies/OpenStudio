/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRTEMPERATUREPATTERNUSERDEFINED_HPP
#define EPMODEL_ROOMAIRTEMPERATUREPATTERNUSERDEFINED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class RoomAirTemperaturePatternUserDefined_Impl;
  }

  class EPMODEL_API RoomAirTemperaturePatternUserDefined : public ModelObject
  {
   public:
    explicit RoomAirTemperaturePatternUserDefined(const Model& model);

    virtual ~RoomAirTemperaturePatternUserDefined() override = default;
    RoomAirTemperaturePatternUserDefined(const RoomAirTemperaturePatternUserDefined& other) = default;
    RoomAirTemperaturePatternUserDefined(RoomAirTemperaturePatternUserDefined&& other) = default;
    RoomAirTemperaturePatternUserDefined& operator=(const RoomAirTemperaturePatternUserDefined&) = default;
    RoomAirTemperaturePatternUserDefined& operator=(RoomAirTemperaturePatternUserDefined&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class naming.
    // - Field Mapping: This object has no class-specific simple non-name scalar fields.
    // - Field Mapping: Zone Name, Availability Schedule Name, and Pattern Control Schedule Name are object-list
    //   relationship fields and are intentionally excluded from scalar accessors in this scaffold pass.
    // - TODO(parity): Add typed relationship APIs for zone/schedule links after scalar saturation.

   protected:
    using ImplType = detail::RoomAirTemperaturePatternUserDefined_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit RoomAirTemperaturePatternUserDefined(std::shared_ptr<detail::RoomAirTemperaturePatternUserDefined_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
