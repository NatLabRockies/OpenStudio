/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DuctLossMakeupAir.hpp"
#include "DuctLossMakeupAir_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DuctLossMakeupAir::DuctLossMakeupAir(const Model& model) : ModelObject(DuctLossMakeupAir::iddObjectType(), model) {}

DuctLossMakeupAir::DuctLossMakeupAir(std::shared_ptr<detail::DuctLossMakeupAir_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DuctLossMakeupAir::iddObjectType() {
  return IddObjectType::Duct_Loss_MakeupAir;
}

}  // namespace epmodel
}  // namespace openstudio
