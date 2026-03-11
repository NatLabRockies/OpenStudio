/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "AirflowNetworkZoneControlPressureController.hpp"
#include "AirflowNetworkZoneControlPressureController_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/AirflowNetwork_ZoneControl_PressureController_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

AirflowNetworkZoneControlPressureController::AirflowNetworkZoneControlPressureController(const Model& model)
  : ModelObject(AirflowNetworkZoneControlPressureController::iddObjectType(), model) {}

AirflowNetworkZoneControlPressureController::AirflowNetworkZoneControlPressureController(
  std::shared_ptr<detail::AirflowNetworkZoneControlPressureController_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType AirflowNetworkZoneControlPressureController::iddObjectType() {
  return IddObjectType::AirflowNetwork_ZoneControl_PressureController;
}

std::vector<std::string> AirflowNetworkZoneControlPressureController::controlObjectTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::AirflowNetwork_ZoneControl_PressureControllerFields::ControlObjectType);
}

std::string AirflowNetworkZoneControlPressureController::controlObjectType() const {
  return getImpl<detail::AirflowNetworkZoneControlPressureController_Impl>()->controlObjectType();
}

bool AirflowNetworkZoneControlPressureController::setControlObjectType(const std::string& controlObjectType) {
  return getImpl<detail::AirflowNetworkZoneControlPressureController_Impl>()->setControlObjectType(controlObjectType);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string AirflowNetworkZoneControlPressureController_Impl::controlObjectType() const {
  const auto value = getString(openstudio::AirflowNetwork_ZoneControl_PressureControllerFields::ControlObjectType, true);
  OS_ASSERT(value);
  return *value;
}

bool AirflowNetworkZoneControlPressureController_Impl::setControlObjectType(const std::string& controlObjectType) {
  return setString(openstudio::AirflowNetwork_ZoneControl_PressureControllerFields::ControlObjectType, controlObjectType);
}

std::vector<std::string> AirflowNetworkZoneControlPressureController_Impl::controlObjectTypeValues() const {
  return openstudio::epmodel::AirflowNetworkZoneControlPressureController::controlObjectTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
