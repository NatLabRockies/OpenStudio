/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkMultiZoneWindPressureCoefficientArray.hpp"
#include "AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  AirflowNetworkMultiZoneWindPressureCoefficientArray::AirflowNetworkMultiZoneWindPressureCoefficientArray(const Model& model)
    : ModelObject(AirflowNetworkMultiZoneWindPressureCoefficientArray::iddObjectType(), model) {}

  AirflowNetworkMultiZoneWindPressureCoefficientArray::AirflowNetworkMultiZoneWindPressureCoefficientArray(
    std::shared_ptr<detail::AirflowNetworkMultiZoneWindPressureCoefficientArray_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType AirflowNetworkMultiZoneWindPressureCoefficientArray::iddObjectType() {
    return IddObjectType::AirflowNetwork_MultiZone_WindPressureCoefficientArray;
  }

}  // namespace epmodel
}  // namespace openstudio
