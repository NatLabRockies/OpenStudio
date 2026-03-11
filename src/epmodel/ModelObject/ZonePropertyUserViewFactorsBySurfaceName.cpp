/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZonePropertyUserViewFactorsBySurfaceName.hpp"
#include "ZonePropertyUserViewFactorsBySurfaceName_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZonePropertyUserViewFactorsBySurfaceName::ZonePropertyUserViewFactorsBySurfaceName(const Model& model)
    : ModelObject(ZonePropertyUserViewFactorsBySurfaceName::iddObjectType(), model) {}

  ZonePropertyUserViewFactorsBySurfaceName::ZonePropertyUserViewFactorsBySurfaceName(
    std::shared_ptr<detail::ZonePropertyUserViewFactorsBySurfaceName_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZonePropertyUserViewFactorsBySurfaceName::iddObjectType() {
    return IddObjectType::ZoneProperty_UserViewFactors_BySurfaceName;
  }

}  // namespace epmodel
}  // namespace openstudio
