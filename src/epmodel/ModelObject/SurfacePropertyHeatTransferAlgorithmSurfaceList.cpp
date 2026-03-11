/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyHeatTransferAlgorithmSurfaceList.hpp"
#include "SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SurfaceProperty_HeatTransferAlgorithm_SurfaceList_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyHeatTransferAlgorithmSurfaceList::SurfacePropertyHeatTransferAlgorithmSurfaceList(const Model& model)
    : ModelObject(SurfacePropertyHeatTransferAlgorithmSurfaceList::iddObjectType(), model) {}

  SurfacePropertyHeatTransferAlgorithmSurfaceList::SurfacePropertyHeatTransferAlgorithmSurfaceList(
    std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyHeatTransferAlgorithmSurfaceList::iddObjectType() {
    return IddObjectType::SurfaceProperty_HeatTransferAlgorithm_SurfaceList;
  }

  std::vector<std::string> SurfacePropertyHeatTransferAlgorithmSurfaceList::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm);
  }

  std::string SurfacePropertyHeatTransferAlgorithmSurfaceList::algorithm() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl>()->algorithm();
  }

  bool SurfacePropertyHeatTransferAlgorithmSurfaceList::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl>()->setAlgorithm(algorithm);
  }

  bool SurfacePropertyHeatTransferAlgorithmSurfaceList::isAlgorithmDefaulted() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl>()->isAlgorithmDefaulted();
  }

  void SurfacePropertyHeatTransferAlgorithmSurfaceList::resetAlgorithm() {
    getImpl<detail::SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm, algorithm);
    }

    bool SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm);
    }

    void SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_SurfaceListFields::Algorithm, ""));
    }

    std::vector<std::string> SurfacePropertyHeatTransferAlgorithmSurfaceList_Impl::algorithmValues() const {
      return openstudio::epmodel::SurfacePropertyHeatTransferAlgorithmSurfaceList::algorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
