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

CoilUserDefined::CoilUserDefined(const Model& model) : ModelObject(CoilUserDefined::iddObjectType(), model) {}

CoilUserDefined::CoilUserDefined(std::shared_ptr<detail::CoilUserDefined_Impl> impl) : ModelObject(std::move(impl)) {}

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

int CoilUserDefined_Impl::numberofAirConnections() const {
  const auto value = getInt(openstudio::Coil_UserDefinedFields::NumberofAirConnections, true);
  OS_ASSERT(value);
  return *value;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
