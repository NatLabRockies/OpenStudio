/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "RoomAirTemperaturePatternUserDefined.hpp"
#include "RoomAirTemperaturePatternUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

RoomAirTemperaturePatternUserDefined::RoomAirTemperaturePatternUserDefined(const Model& model)
  : ModelObject(RoomAirTemperaturePatternUserDefined::iddObjectType(), model) {}

RoomAirTemperaturePatternUserDefined::RoomAirTemperaturePatternUserDefined(
  std::shared_ptr<detail::RoomAirTemperaturePatternUserDefined_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType RoomAirTemperaturePatternUserDefined::iddObjectType() {
  return IddObjectType::RoomAir_TemperaturePattern_UserDefined;
}

}  // namespace epmodel
}  // namespace openstudio
