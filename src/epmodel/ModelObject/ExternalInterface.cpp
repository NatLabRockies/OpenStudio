/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ExternalInterface.hpp"
#include "ExternalInterface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ExternalInterface_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ExternalInterface::ExternalInterface(const Model& model) : ModelObject(ExternalInterface::iddObjectType(), model) {
  // Preserve model counterpart behavior for this required choice field.
  OS_ASSERT(setNameofExternalInterface("PtolemyServer"));
}

ExternalInterface::ExternalInterface(std::shared_ptr<detail::ExternalInterface_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ExternalInterface::iddObjectType() {
  return IddObjectType::ExternalInterface;
}

std::vector<std::string> ExternalInterface::nameofExternalInterfaceValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ExternalInterfaceFields::NameofExternalInterface);
}

std::string ExternalInterface::nameofExternalInterface() const {
  return getImpl<detail::ExternalInterface_Impl>()->nameofExternalInterface();
}

bool ExternalInterface::setNameofExternalInterface(const std::string& nameofExternalInterface) {
  return getImpl<detail::ExternalInterface_Impl>()->setNameofExternalInterface(nameofExternalInterface);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ExternalInterface_Impl::nameofExternalInterface() const {
  const auto value = getString(openstudio::ExternalInterfaceFields::NameofExternalInterface, true);
  OS_ASSERT(value);
  return *value;
}

bool ExternalInterface_Impl::setNameofExternalInterface(const std::string& nameofExternalInterface) {
  return setString(openstudio::ExternalInterfaceFields::NameofExternalInterface, nameofExternalInterface);
}

std::vector<std::string> ExternalInterface_Impl::nameofExternalInterfaceValues() const {
  return openstudio::epmodel::ExternalInterface::nameofExternalInterfaceValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
