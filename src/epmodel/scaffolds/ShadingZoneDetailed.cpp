/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingZoneDetailed.hpp"
#include "ShadingZoneDetailed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Zone_Detailed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

ShadingZoneDetailed::ShadingZoneDetailed(const Model& model) : ModelObject(ShadingZoneDetailed::iddObjectType(), model) {}

ShadingZoneDetailed::ShadingZoneDetailed(std::shared_ptr<detail::ShadingZoneDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType ShadingZoneDetailed::iddObjectType() {
  return IddObjectType::Shading_Zone_Detailed;
}

boost::optional<int> ShadingZoneDetailed::numberofVertices() const {
  return getImpl<detail::ShadingZoneDetailed_Impl>()->numberofVertices();
}

bool ShadingZoneDetailed::setNumberofVertices(int numberofVertices) {
  return getImpl<detail::ShadingZoneDetailed_Impl>()->setNumberofVertices(numberofVertices);
}

bool ShadingZoneDetailed::isNumberofVerticesAutocalculated() const {
  return getImpl<detail::ShadingZoneDetailed_Impl>()->isNumberofVerticesAutocalculated();
}

void ShadingZoneDetailed::autocalculateNumberofVertices() {
  getImpl<detail::ShadingZoneDetailed_Impl>()->autocalculateNumberofVertices();
}

void ShadingZoneDetailed::resetNumberofVertices() {
  getImpl<detail::ShadingZoneDetailed_Impl>()->resetNumberofVertices();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

boost::optional<int> ShadingZoneDetailed_Impl::numberofVertices() const {
  return getInt(openstudio::Shading_Zone_DetailedFields::NumberofVertices, true);
}

bool ShadingZoneDetailed_Impl::setNumberofVertices(int numberofVertices) {
  return setInt(openstudio::Shading_Zone_DetailedFields::NumberofVertices, numberofVertices);
}

bool ShadingZoneDetailed_Impl::isNumberofVerticesAutocalculated() const {
  if (const auto value = getString(openstudio::Shading_Zone_DetailedFields::NumberofVertices, true)) {
    return openstudio::istringEqual(*value, "autocalculate");
  }
  return false;
}

void ShadingZoneDetailed_Impl::autocalculateNumberofVertices() {
  OS_ASSERT(setString(openstudio::Shading_Zone_DetailedFields::NumberofVertices, "autocalculate"));
}

void ShadingZoneDetailed_Impl::resetNumberofVertices() {
  OS_ASSERT(setString(openstudio::Shading_Zone_DetailedFields::NumberofVertices, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
