/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceConvectionAlgorithmInsideUserCurve.hpp"
#include "SurfaceConvectionAlgorithmInsideUserCurve_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Inside_UserCurve_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceConvectionAlgorithmInsideUserCurve::SurfaceConvectionAlgorithmInsideUserCurve(const Model& model)
    : ModelObject(SurfaceConvectionAlgorithmInsideUserCurve::iddObjectType(), model) {}

  SurfaceConvectionAlgorithmInsideUserCurve::SurfaceConvectionAlgorithmInsideUserCurve(
    std::shared_ptr<detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceConvectionAlgorithmInsideUserCurve::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Inside_UserCurve;
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideUserCurve::referenceTemperatureforConvectionHeatTransferValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_UserCurveFields::ReferenceTemperatureforConvectionHeatTransfer);
  }

  boost::optional<std::string> SurfaceConvectionAlgorithmInsideUserCurve::referenceTemperatureforConvectionHeatTransfer() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl>()->referenceTemperatureforConvectionHeatTransfer();
  }

  bool SurfaceConvectionAlgorithmInsideUserCurve::setReferenceTemperatureforConvectionHeatTransfer(
    const std::string& referenceTemperatureforConvectionHeatTransfer) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl>()->setReferenceTemperatureforConvectionHeatTransfer(
      referenceTemperatureforConvectionHeatTransfer);
  }

  void SurfaceConvectionAlgorithmInsideUserCurve::resetReferenceTemperatureforConvectionHeatTransfer() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideUserCurve_Impl>()->resetReferenceTemperatureforConvectionHeatTransfer();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> SurfaceConvectionAlgorithmInsideUserCurve_Impl::referenceTemperatureforConvectionHeatTransfer() const {
      return getString(openstudio::SurfaceConvectionAlgorithm_Inside_UserCurveFields::ReferenceTemperatureforConvectionHeatTransfer, true);
    }

    bool SurfaceConvectionAlgorithmInsideUserCurve_Impl::setReferenceTemperatureforConvectionHeatTransfer(
      const std::string& referenceTemperatureforConvectionHeatTransfer) {
      return setString(openstudio::SurfaceConvectionAlgorithm_Inside_UserCurveFields::ReferenceTemperatureforConvectionHeatTransfer,
                       referenceTemperatureforConvectionHeatTransfer);
    }

    void SurfaceConvectionAlgorithmInsideUserCurve_Impl::resetReferenceTemperatureforConvectionHeatTransfer() {
      OS_ASSERT(setString(openstudio::SurfaceConvectionAlgorithm_Inside_UserCurveFields::ReferenceTemperatureforConvectionHeatTransfer, ""));
    }

    std::vector<std::string> SurfaceConvectionAlgorithmInsideUserCurve_Impl::referenceTemperatureforConvectionHeatTransferValues() const {
      return openstudio::epmodel::SurfaceConvectionAlgorithmInsideUserCurve::referenceTemperatureforConvectionHeatTransferValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
