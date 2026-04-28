/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZonePropertyLocalEnvironment.hpp"
#include "ZonePropertyLocalEnvironment_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZonePropertyLocalEnvironment::ZonePropertyLocalEnvironment(const Model& model)
    : ModelObject(ZonePropertyLocalEnvironment::iddObjectType(), model) {}

  ZonePropertyLocalEnvironment::ZonePropertyLocalEnvironment(std::shared_ptr<detail::ZonePropertyLocalEnvironment_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZonePropertyLocalEnvironment::iddObjectType() {
    return IddObjectType::ZoneProperty_LocalEnvironment;
  }

}  // namespace epmodel
}  // namespace openstudio
