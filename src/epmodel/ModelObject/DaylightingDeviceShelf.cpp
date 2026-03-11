/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "DaylightingDeviceShelf.hpp"
#include "DaylightingDeviceShelf_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/DaylightingDevice_Shelf_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

DaylightingDeviceShelf::DaylightingDeviceShelf(const Model& model) : ModelObject(DaylightingDeviceShelf::iddObjectType(), model) {}

DaylightingDeviceShelf::DaylightingDeviceShelf(std::shared_ptr<detail::DaylightingDeviceShelf_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType DaylightingDeviceShelf::iddObjectType() {
  return IddObjectType::DaylightingDevice_Shelf;
}

boost::optional<double> DaylightingDeviceShelf::viewFactortoOutsideShelf() const {
  return getImpl<detail::DaylightingDeviceShelf_Impl>()->viewFactortoOutsideShelf();
}

bool DaylightingDeviceShelf::setViewFactortoOutsideShelf(double viewFactortoOutsideShelf) {
  return getImpl<detail::DaylightingDeviceShelf_Impl>()->setViewFactortoOutsideShelf(viewFactortoOutsideShelf);
}

void DaylightingDeviceShelf::resetViewFactortoOutsideShelf() {
  getImpl<detail::DaylightingDeviceShelf_Impl>()->resetViewFactortoOutsideShelf();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<double> DaylightingDeviceShelf_Impl::viewFactortoOutsideShelf() const {
  return getDouble(openstudio::DaylightingDevice_ShelfFields::ViewFactortoOutsideShelf, true);
}

bool DaylightingDeviceShelf_Impl::setViewFactortoOutsideShelf(double viewFactortoOutsideShelf) {
  return setDouble(openstudio::DaylightingDevice_ShelfFields::ViewFactortoOutsideShelf, viewFactortoOutsideShelf);
}

void DaylightingDeviceShelf_Impl::resetViewFactortoOutsideShelf() {
  OS_ASSERT(setString(openstudio::DaylightingDevice_ShelfFields::ViewFactortoOutsideShelf, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
