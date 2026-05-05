/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneWindPressureCoefficientValues.hpp"
#include "AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneWindPressureCoefficientValues::AirflowNetworkMultiZoneWindPressureCoefficientValues(const Model& model)
    : ModelObject(AirflowNetworkMultiZoneWindPressureCoefficientValues::iddObjectType(), model) {}

  AirflowNetworkMultiZoneWindPressureCoefficientValues::AirflowNetworkMultiZoneWindPressureCoefficientValues(
    std::shared_ptr<detail::AirflowNetworkMultiZoneWindPressureCoefficientValues_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneWindPressureCoefficientValues::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientValues;
  }

}  // namespace epmodel
}  // namespace openstudio
