/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ConstructionBase/ConstructionBase.hpp"
#include "ConstructionBase/ConstructionBase_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    bool ConstructionBase_Impl::isGreenRoof() const {
      return false;
    }

  }  // namespace detail

  ConstructionBase::ConstructionBase(IddObjectType type, const Model& model) : ResourceObject(type, model) {}

  ConstructionBase::ConstructionBase(std::shared_ptr<detail::ConstructionBase_Impl> impl) : ResourceObject(std::move(impl)) {}

  bool ConstructionBase::isOpaque() const {
    return getImpl<detail::ConstructionBase_Impl>()->isOpaque();
  }

  bool ConstructionBase::isFenestration() const {
    return getImpl<detail::ConstructionBase_Impl>()->isFenestration();
  }

  bool ConstructionBase::isSolarDiffusing() const {
    return getImpl<detail::ConstructionBase_Impl>()->isSolarDiffusing();
  }

  bool ConstructionBase::isModelPartition() const {
    return getImpl<detail::ConstructionBase_Impl>()->isModelPartition();
  }

  bool ConstructionBase::isGreenRoof() const {
    return getImpl<detail::ConstructionBase_Impl>()->isGreenRoof();
  }

}  // namespace epmodel
}  // namespace openstudio
