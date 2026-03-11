/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OutsideSurfaceConvectionAlgorithm.hpp"
#include "OutsideSurfaceConvectionAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Outside_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  OutsideSurfaceConvectionAlgorithm::OutsideSurfaceConvectionAlgorithm(const Model& model)
    : ModelObject(OutsideSurfaceConvectionAlgorithm::iddObjectType(), model) {
    OS_ASSERT(setAlgorithm("DOE-2"));
  }

  OutsideSurfaceConvectionAlgorithm::OutsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::OutsideSurfaceConvectionAlgorithm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType OutsideSurfaceConvectionAlgorithm::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Outside;
  }

  std::vector<std::string> OutsideSurfaceConvectionAlgorithm::validAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SurfaceConvectionAlgorithm_OutsideFields::Algorithm);
  }

  std::string OutsideSurfaceConvectionAlgorithm::algorithm() const {
    return getImpl<detail::OutsideSurfaceConvectionAlgorithm_Impl>()->algorithm();
  }

  bool OutsideSurfaceConvectionAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::OutsideSurfaceConvectionAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  bool OutsideSurfaceConvectionAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::OutsideSurfaceConvectionAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  void OutsideSurfaceConvectionAlgorithm::resetAlgorithm() {
    getImpl<detail::OutsideSurfaceConvectionAlgorithm_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string OutsideSurfaceConvectionAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceConvectionAlgorithm_OutsideFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool OutsideSurfaceConvectionAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceConvectionAlgorithm_OutsideFields::Algorithm);
    }

    bool OutsideSurfaceConvectionAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceConvectionAlgorithm_OutsideFields::Algorithm, algorithm);
    }

    void OutsideSurfaceConvectionAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceConvectionAlgorithm_OutsideFields::Algorithm, ""));
    }

    std::vector<std::string> OutsideSurfaceConvectionAlgorithm_Impl::validAlgorithmValues() const {
      return openstudio::epmodel::OutsideSurfaceConvectionAlgorithm::validAlgorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
