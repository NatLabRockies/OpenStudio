/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ShadingSiteDetailed.hpp"
#include "ShadingSiteDetailed_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Shading_Site_Detailed_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ShadingSiteDetailed::ShadingSiteDetailed(const Model& model) : ModelObject(ShadingSiteDetailed::iddObjectType(), model) {}

  ShadingSiteDetailed::ShadingSiteDetailed(std::shared_ptr<detail::ShadingSiteDetailed_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ShadingSiteDetailed::iddObjectType() {
    return IddObjectType::Shading_Site_Detailed;
  }

  boost::optional<int> ShadingSiteDetailed::numberofVertices() const {
    return getImpl<detail::ShadingSiteDetailed_Impl>()->numberofVertices();
  }

  bool ShadingSiteDetailed::setNumberofVertices(int numberofVertices) {
    return getImpl<detail::ShadingSiteDetailed_Impl>()->setNumberofVertices(numberofVertices);
  }

  void ShadingSiteDetailed::resetNumberofVertices() {
    getImpl<detail::ShadingSiteDetailed_Impl>()->resetNumberofVertices();
  }

  bool ShadingSiteDetailed::isNumberofVerticesAutocalculated() const {
    return getImpl<detail::ShadingSiteDetailed_Impl>()->isNumberofVerticesAutocalculated();
  }

  void ShadingSiteDetailed::autocalculateNumberofVertices() {
    getImpl<detail::ShadingSiteDetailed_Impl>()->autocalculateNumberofVertices();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<int> ShadingSiteDetailed_Impl::numberofVertices() const {
      return getInt(openstudio::Shading_Site_DetailedFields::NumberofVertices, true);
    }

    bool ShadingSiteDetailed_Impl::setNumberofVertices(int numberofVertices) {
      return setInt(openstudio::Shading_Site_DetailedFields::NumberofVertices, numberofVertices);
    }

    void ShadingSiteDetailed_Impl::resetNumberofVertices() {
      OS_ASSERT(setString(openstudio::Shading_Site_DetailedFields::NumberofVertices, ""));
    }

    bool ShadingSiteDetailed_Impl::isNumberofVerticesAutocalculated() const {
      if (const auto value = getString(openstudio::Shading_Site_DetailedFields::NumberofVertices, true)) {
        return openstudio::istringEqual(*value, "autocalculate");
      }
      return false;
    }

    void ShadingSiteDetailed_Impl::autocalculateNumberofVertices() {
      OS_ASSERT(setString(openstudio::Shading_Site_DetailedFields::NumberofVertices, "autocalculate"));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
