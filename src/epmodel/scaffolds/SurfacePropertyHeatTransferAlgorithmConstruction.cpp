/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "SurfacePropertyHeatTransferAlgorithmConstruction.hpp"
#include "SurfacePropertyHeatTransferAlgorithmConstruction_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SurfaceProperty_HeatTransferAlgorithm_Construction_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SurfacePropertyHeatTransferAlgorithmConstruction::SurfacePropertyHeatTransferAlgorithmConstruction(const Model& model)
    : ModelObject(SurfacePropertyHeatTransferAlgorithmConstruction::iddObjectType(), model) {}

  SurfacePropertyHeatTransferAlgorithmConstruction::SurfacePropertyHeatTransferAlgorithmConstruction(
    std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfacePropertyHeatTransferAlgorithmConstruction::iddObjectType() {
    return IddObjectType::SurfaceProperty_HeatTransferAlgorithm_Construction;
  }

  std::vector<std::string> SurfacePropertyHeatTransferAlgorithmConstruction::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceProperty_HeatTransferAlgorithm_ConstructionFields::Algorithm);
  }

  std::string SurfacePropertyHeatTransferAlgorithmConstruction::algorithm() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl>()->algorithm();
  }

  bool SurfacePropertyHeatTransferAlgorithmConstruction::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl>()->setAlgorithm(algorithm);
  }

  bool SurfacePropertyHeatTransferAlgorithmConstruction::isAlgorithmDefaulted() const {
    return getImpl<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl>()->isAlgorithmDefaulted();
  }

  void SurfacePropertyHeatTransferAlgorithmConstruction::resetAlgorithm() {
    getImpl<detail::SurfacePropertyHeatTransferAlgorithmConstruction_Impl>()->resetAlgorithm();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfacePropertyHeatTransferAlgorithmConstruction_Impl::algorithm() const {
      const auto value = getString(openstudio::SurfaceProperty_HeatTransferAlgorithm_ConstructionFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SurfacePropertyHeatTransferAlgorithmConstruction_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_ConstructionFields::Algorithm, algorithm);
    }

    bool SurfacePropertyHeatTransferAlgorithmConstruction_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::SurfaceProperty_HeatTransferAlgorithm_ConstructionFields::Algorithm);
    }

    void SurfacePropertyHeatTransferAlgorithmConstruction_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::SurfaceProperty_HeatTransferAlgorithm_ConstructionFields::Algorithm, ""));
    }

    std::vector<std::string> SurfacePropertyHeatTransferAlgorithmConstruction_Impl::algorithmValues() const {
      return openstudio::epmodel::SurfacePropertyHeatTransferAlgorithmConstruction::algorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
