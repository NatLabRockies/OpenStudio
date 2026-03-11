/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfacePropertyHeatBalanceSourceTerm.hpp"
#include "SurfacePropertyHeatBalanceSourceTerm_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyHeatBalanceSourceTerm::SurfacePropertyHeatBalanceSourceTerm(const Model& model)
    : ModelObject(SurfacePropertyHeatBalanceSourceTerm::iddObjectType(), model) {}

  SurfacePropertyHeatBalanceSourceTerm::SurfacePropertyHeatBalanceSourceTerm(std::shared_ptr<detail::SurfacePropertyHeatBalanceSourceTerm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyHeatBalanceSourceTerm::iddObjectType() {
    return IddObjectType::SurfaceProperty_HeatBalanceSourceTerm;
  }

}  // namespace epmodel
}  // namespace openstudio
