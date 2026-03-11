/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ZoneControlContaminantController.hpp"
#include "ZoneControlContaminantController_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneControlContaminantController::ZoneControlContaminantController(const Model& model)
    : ModelObject(ZoneControlContaminantController::iddObjectType(), model) {}

  ZoneControlContaminantController::ZoneControlContaminantController(std::shared_ptr<detail::ZoneControlContaminantController_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType ZoneControlContaminantController::iddObjectType() {
    return IddObjectType::ZoneControl_ContaminantController;
  }

}  // namespace epmodel
}  // namespace openstudio
