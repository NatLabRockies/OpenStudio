/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneHVACForcedAirUserDefined.hpp"
#include "ZoneHVACForcedAirUserDefined_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ZoneHVAC_ForcedAir_UserDefined_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACForcedAirUserDefined::ZoneHVACForcedAirUserDefined(const Model& model)
    : ModelObject(ZoneHVACForcedAirUserDefined::iddObjectType(), model) {}

  ZoneHVACForcedAirUserDefined::ZoneHVACForcedAirUserDefined(std::shared_ptr<detail::ZoneHVACForcedAirUserDefined_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACForcedAirUserDefined::iddObjectType() {
    return IddObjectType::ZoneHVAC_ForcedAir_UserDefined;
  }

  int ZoneHVACForcedAirUserDefined::numberofPlantLoopConnections() const {
    return getImpl<detail::ZoneHVACForcedAirUserDefined_Impl>()->numberofPlantLoopConnections();
  }

  bool ZoneHVACForcedAirUserDefined::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
    return getImpl<detail::ZoneHVACForcedAirUserDefined_Impl>()->setNumberofPlantLoopConnections(numberofPlantLoopConnections);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int ZoneHVACForcedAirUserDefined_Impl::numberofPlantLoopConnections() const {
      const auto value = getInt(openstudio::ZoneHVAC_ForcedAir_UserDefinedFields::NumberofPlantLoopConnections, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACForcedAirUserDefined_Impl::setNumberofPlantLoopConnections(int numberofPlantLoopConnections) {
      return setInt(openstudio::ZoneHVAC_ForcedAir_UserDefinedFields::NumberofPlantLoopConnections, numberofPlantLoopConnections);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
