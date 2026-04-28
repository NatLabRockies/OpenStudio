/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DuctLossLeakage.hpp"
#include "DuctLossLeakage_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DuctLossLeakage::DuctLossLeakage(const Model& model) : ModelObject(DuctLossLeakage::iddObjectType(), model) {}

DuctLossLeakage::DuctLossLeakage(std::shared_ptr<detail::DuctLossLeakage_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DuctLossLeakage::iddObjectType() {
  return IddObjectType::Duct_Loss_Leakage;
}

}  // namespace epmodel
}  // namespace openstudio
