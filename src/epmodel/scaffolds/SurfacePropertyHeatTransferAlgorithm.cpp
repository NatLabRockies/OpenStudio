/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyHeatTransferAlgorithm.hpp"
#include "SurfacePropertyHeatTransferAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceProperty_HeatTransferAlgorithm_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfacePropertyHeatTransferAlgorithm::SurfacePropertyHeatTransferAlgorithm(const Model& model)
    : ModelObject(SurfacePropertyHeatTransferAlgorithm::iddObjectType(), model) {}

  SurfacePropertyHeatTransferAlgorithm::SurfacePropertyHeatTransferAlgorithm(std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyHeatTransferAlgorithm::iddObjectType() {
    return IddObjectType::SurfaceProperty_HeatTransferAlgorithm;
  }

  std::vector<std::string> SurfacePropertyHeatTransferAlgorithm::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_HeatTransferAlgorithmFields::Algorithm);
  }

  std::string SurfacePropertyHeatTransferAlgorithm::algorithm() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithm_Impl>()->algorithm();
  }

  bool SurfacePropertyHeatTransferAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  bool SurfacePropertyHeatTransferAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  void SurfacePropertyHeatTransferAlgorithm::resetAlgorithm() {
    getImpl<detail::SurfacePropertyHeatTransferAlgorithm_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::vector<std::string> SurfacePropertyHeatTransferAlgorithm_Impl::algorithmValues() const {
      return openstudio::epmodel::SurfacePropertyHeatTransferAlgorithm::algorithmValues();
    }

    std::string SurfacePropertyHeatTransferAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceProperty_HeatTransferAlgorithmFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyHeatTransferAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceProperty_HeatTransferAlgorithmFields::Algorithm, algorithm);
    }

    bool SurfacePropertyHeatTransferAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_HeatTransferAlgorithmFields::Algorithm);
    }

    void SurfacePropertyHeatTransferAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_HeatTransferAlgorithmFields::Algorithm, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
