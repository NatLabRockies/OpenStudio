/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToAirComponent/CoilUserDefined.hpp"
#include "WaterToAirComponent/CoilUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Coil_UserDefined_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CoilUserDefined::CoilUserDefined(const Model& model) : WaterToAirComponent(CoilUserDefined::iddObjectType(), model) {}

CoilUserDefined::CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl) : WaterToAirComponent(std::move(impl)) {}

IddObjectType CoilUserDefined::iddObjectType() {
  return IddObjectType::Coil_UserDefined;
}

int CoilUserDefined::numberofAirConnections() const {
  return getImpl<detail::CoilUserDefined_Impl>()->numberofAirConnections();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilUserDefined_Impl::airInletPort() const {
  return openstudio::Coil_UserDefinedFields::AirConnection1InletNodeName;
}

unsigned CoilUserDefined_Impl::airOutletPort() const {
  return openstudio::Coil_UserDefinedFields::AirConnection1OutletNodeName;
}

unsigned CoilUserDefined_Impl::waterInletPort() const {
  return openstudio::Coil_UserDefinedFields::PlantConnectionInletNodeName;
}

unsigned CoilUserDefined_Impl::waterOutletPort() const {
  return openstudio::Coil_UserDefinedFields::PlantConnectionOutletNodeName;
}

int CoilUserDefined_Impl::numberofAirConnections() const {
  const auto value = getInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, true);
  OS_ASSERT(value);
  return *value;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
