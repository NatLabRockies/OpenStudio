/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyHeatTransferAlgorithmMultipleSurface.hpp"
#include "SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SurfaceProperty_HeatTransferAlgorithm_MultipleSurface_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyHeatTransferAlgorithmMultipleSurface::SurfacePropertyHeatTransferAlgorithmMultipleSurface(const Model& model)
    : ModelObject(SurfacePropertyHeatTransferAlgorithmMultipleSurface::iddObjectType(), model) {}

  SurfacePropertyHeatTransferAlgorithmMultipleSurface::SurfacePropertyHeatTransferAlgorithmMultipleSurface(
    std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyHeatTransferAlgorithmMultipleSurface::iddObjectType() {
    return IddObjectType::SurfaceProperty_HeatTransferAlgorithm_MultipleSurface;
  }

  std::vector<std::string> SurfacePropertyHeatTransferAlgorithmMultipleSurface::surfaceTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::SurfaceType);
  }

  std::vector<std::string> SurfacePropertyHeatTransferAlgorithmMultipleSurface::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::Algorithm);
  }

  std::string SurfacePropertyHeatTransferAlgorithmMultipleSurface::surfaceType() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->surfaceType();
  }

  bool SurfacePropertyHeatTransferAlgorithmMultipleSurface::setSurfaceType(const std::string& surfaceType) {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->setSurfaceType(surfaceType);
  }

  std::string SurfacePropertyHeatTransferAlgorithmMultipleSurface::algorithm() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->algorithm();
  }

  bool SurfacePropertyHeatTransferAlgorithmMultipleSurface::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->setAlgorithm(algorithm);
  }

  bool SurfacePropertyHeatTransferAlgorithmMultipleSurface::isAlgorithmDefaulted() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->isAlgorithmDefaulted();
  }

  void SurfacePropertyHeatTransferAlgorithmMultipleSurface::resetAlgorithm() {
    getImpl<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::surfaceType() const {
      const auto value = getString(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::SurfaceType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::setSurfaceType(const std::string& surfaceType) {
      return setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::SurfaceType, surfaceType);
    }

    std::string SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::Algorithm, algorithm);
    }

    bool SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::Algorithm);
    }

    void SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_MultipleSurfaceFields::Algorithm, ""));
    }

    std::vector<std::string> SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::surfaceTypeValues() const {
      return openstudio::epmodel::SurfacePropertyHeatTransferAlgorithmMultipleSurface::surfaceTypeValues();
    }

    std::vector<std::string> SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl::algorithmValues() const {
      return openstudio::epmodel::SurfacePropertyHeatTransferAlgorithmMultipleSurface::algorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
