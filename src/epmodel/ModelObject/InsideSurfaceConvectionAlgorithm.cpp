/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "InsideSurfaceConvectionAlgorithm.hpp"
#include "InsideSurfaceConvectionAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Inside_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

  InsideSurfaceConvectionAlgorithm::InsideSurfaceConvectionAlgorithm(const Model& model)
    : ModelObject(InsideSurfaceConvectionAlgorithm::iddObjectType(), model) {
    OS_ASSERT(setAlgorithm("TARP"));
  }

  InsideSurfaceConvectionAlgorithm::InsideSurfaceConvectionAlgorithm(std::shared_ptr<detail::InsideSurfaceConvectionAlgorithm_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType InsideSurfaceConvectionAlgorithm::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Inside;
  }

  std::vector<std::string> InsideSurfaceConvectionAlgorithm::validAlgorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::SurfaceConvectionAlgorithm_InsideFields::Algorithm);
  }

  std::string InsideSurfaceConvectionAlgorithm::algorithm() const {
    return getImpl<detail::InsideSurfaceConvectionAlgorithm_Impl>()->algorithm();
  }

  bool InsideSurfaceConvectionAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::InsideSurfaceConvectionAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  bool InsideSurfaceConvectionAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::InsideSurfaceConvectionAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  void InsideSurfaceConvectionAlgorithm::resetAlgorithm() {
    getImpl<detail::InsideSurfaceConvectionAlgorithm_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string InsideSurfaceConvectionAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceConvectionAlgorithm_InsideFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool InsideSurfaceConvectionAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceConvectionAlgorithm_InsideFields::Algorithm);
    }

    bool InsideSurfaceConvectionAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceConvectionAlgorithm_InsideFields::Algorithm, algorithm);
    }

    void InsideSurfaceConvectionAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceConvectionAlgorithm_InsideFields::Algorithm, ""));
    }

    std::vector<std::string> InsideSurfaceConvectionAlgorithm_Impl::validAlgorithmValues() const {
      return openstudio::epmodel::InsideSurfaceConvectionAlgorithm::validAlgorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
