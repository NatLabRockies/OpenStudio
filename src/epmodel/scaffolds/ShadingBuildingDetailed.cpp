/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingBuildingDetailed.hpp"
#include "ShadingBuildingDetailed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Building_Detailed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ShadingBuildingDetailed::ShadingBuildingDetailed(const Model& model) : ModelObject(ShadingBuildingDetailed::iddObjectType(), model) {}

  ShadingBuildingDetailed::ShadingBuildingDetailed(std::shared_ptr<detail::ShadingBuildingDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ShadingBuildingDetailed::iddObjectType() {
    return IddObjectType::Shading_Building_Detailed;
  }

  boost::optional<int> ShadingBuildingDetailed::numberofVertices() const {
    return getImpl<detail::ShadingBuildingDetailed_Impl>()->numberofVertices();
  }

  bool ShadingBuildingDetailed::setNumberofVertices(int numberofVertices) {
    return getImpl<detail::ShadingBuildingDetailed_Impl>()->setNumberofVertices(numberofVertices);
  }

  bool ShadingBuildingDetailed::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::ShadingBuildingDetailed_Impl>()->isNumberofVerticesAutocalculated();
  }

  void ShadingBuildingDetailed::autocalculateNumberofVertices() {
    getImpl<detail::ShadingBuildingDetailed_Impl>()->autocalculateNumberofVertices();
  }

  void ShadingBuildingDetailed::resetNumberofVertices() {
    getImpl<detail::ShadingBuildingDetailed_Impl>()->resetNumberofVertices();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<int> ShadingBuildingDetailed_Impl::numberofVertices() const {
      return getInt(openstudio::Shading_Building_DetailedFields::NumberofVertices, true);
    }

    bool ShadingBuildingDetailed_Impl::setNumberofVertices(int numberofVertices) {
      return setInt(openstudio::Shading_Building_DetailedFields::NumberofVertices, numberofVertices);
    }

    bool ShadingBuildingDetailed_Impl::isNumberofVerticesAutocalculated() const {
      if (const auto value = getString(openstudio::Shading_Building_DetailedFields::NumberofVertices, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ShadingBuildingDetailed_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::Shading_Building_DetailedFields::NumberofVertices, "autocalculate"));
    }

    void ShadingBuildingDetailed_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::Shading_Building_DetailedFields::NumberofVertices, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
