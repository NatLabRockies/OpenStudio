/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/CurrencyType.hpp"
#include "ParentObject/CurrencyType_Impl.hpp"

#include "Model.hpp"

#include <utilities/idd/CurrencyType_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

CurrencyType::CurrencyType(const Model& model) : ParentObject(CurrencyType::iddObjectType(), model) {}

CurrencyType::CurrencyType(std::shared_ptr<detail::CurrencyType_Impl> impl) : ParentObject(std::move(impl)) {}

IddObjectType CurrencyType::iddObjectType() {
  return IddObjectType::CurrencyType;
}

boost::optional<std::string> CurrencyType::monetaryUnit() const {
  return getImpl<detail::CurrencyType_Impl>()->monetaryUnit();
}

bool CurrencyType::setMonetaryUnit(const std::string& monetaryUnit) {
  return getImpl<detail::CurrencyType_Impl>()->setMonetaryUnit(monetaryUnit);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<std::string> CurrencyType_Impl::monetaryUnit() const {
  return getString(openstudio::CurrencyTypeFields::MonetaryUnit, true);
}

bool CurrencyType_Impl::setMonetaryUnit(const std::string& monetaryUnit) {
  return setString(openstudio::CurrencyTypeFields::MonetaryUnit, monetaryUnit);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
