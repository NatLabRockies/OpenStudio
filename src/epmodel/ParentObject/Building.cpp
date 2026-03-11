/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/Building.hpp"
#include "ParentObject/Building_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/Building_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

Building::Building(const Model& model) : ModelObject(Building::iddObjectType(), model) {}

Building::Building(std::shared_ptr<detail::Building_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType Building::iddObjectType() {
  return IddObjectType::Building;
}

double Building::northAxis() const {
  return getImpl<detail::Building_Impl>()->northAxis();
}

bool Building::isNorthAxisDefaulted() const {
  return getImpl<detail::Building_Impl>()->isNorthAxisDefaulted();
}

bool Building::setNorthAxis(double northAxis) {
  return getImpl<detail::Building_Impl>()->setNorthAxis(northAxis);
}

void Building::resetNorthAxis() {
  getImpl<detail::Building_Impl>()->resetNorthAxis();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double Building_Impl::northAxis() const {
  const auto value = getDouble(openstudio::BuildingFields::NorthAxis, true);
  OS_ASSERT(value);
  return *value;
}

bool Building_Impl::isNorthAxisDefaulted() const {
  return !getDouble(openstudio::BuildingFields::NorthAxis, false);
}

bool Building_Impl::setNorthAxis(double northAxis) {
  return setDouble(openstudio::BuildingFields::NorthAxis, northAxis);
}

void Building_Impl::resetNorthAxis() {
  OS_ASSERT(setString(openstudio::BuildingFields::NorthAxis, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
