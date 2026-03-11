/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceConvectionAlgorithmOutsideUserCurve.hpp"
#include "SurfaceConvectionAlgorithmOutsideUserCurve_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Outside_UserCurve_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceConvectionAlgorithmOutsideUserCurve::SurfaceConvectionAlgorithmOutsideUserCurve(const Model& model)
    : ModelObject(SurfaceConvectionAlgorithmOutsideUserCurve::iddObjectType(), model) {}

  SurfaceConvectionAlgorithmOutsideUserCurve::SurfaceConvectionAlgorithmOutsideUserCurve(
    std::shared_ptr<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceConvectionAlgorithmOutsideUserCurve::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Outside_UserCurve;
  }

  std::vector<std::string> SurfaceConvectionAlgorithmOutsideUserCurve::windSpeedTypeforCurveValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Outside_UserCurveFields::WindSpeedTypeforCurve);
  }

  std::string SurfaceConvectionAlgorithmOutsideUserCurve::windSpeedTypeforCurve() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl>()->windSpeedTypeforCurve();
  }

  bool SurfaceConvectionAlgorithmOutsideUserCurve::isWindSpeedTypeforCurveDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl>()->isWindSpeedTypeforCurveDefaulted();
  }

  bool SurfaceConvectionAlgorithmOutsideUserCurve::setWindSpeedTypeforCurve(const std::string& windSpeedTypeforCurve) {
    return getImpl<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl>()->setWindSpeedTypeforCurve(windSpeedTypeforCurve);
  }

  void SurfaceConvectionAlgorithmOutsideUserCurve::resetWindSpeedTypeforCurve() {
    getImpl<detail::SurfaceConvectionAlgorithmOutsideUserCurve_Impl>()->resetWindSpeedTypeforCurve();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string SurfaceConvectionAlgorithmOutsideUserCurve_Impl::windSpeedTypeforCurve() const {
      auto value = getString(openstudio::SurfaceConvectionAlgorithm_Outside_UserCurveFields::WindSpeedTypeforCurve, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool SurfaceConvectionAlgorithmOutsideUserCurve_Impl::isWindSpeedTypeforCurveDefaulted() const {
      return isEmpty(openstudio::SurfaceConvectionAlgorithm_Outside_UserCurveFields::WindSpeedTypeforCurve);
    }

    bool SurfaceConvectionAlgorithmOutsideUserCurve_Impl::setWindSpeedTypeforCurve(const std::string& windSpeedTypeforCurve) {
      return setString(openstudio::SurfaceConvectionAlgorithm_Outside_UserCurveFields::WindSpeedTypeforCurve, windSpeedTypeforCurve);
    }

    void SurfaceConvectionAlgorithmOutsideUserCurve_Impl::resetWindSpeedTypeforCurve() {
      OS_ASSERT(setString(openstudio::SurfaceConvectionAlgorithm_Outside_UserCurveFields::WindSpeedTypeforCurve, ""));
    }

    std::vector<std::string> SurfaceConvectionAlgorithmOutsideUserCurve_Impl::windSpeedTypeforCurveValues() const {
      return openstudio::epmodel::SurfaceConvectionAlgorithmOutsideUserCurve::windSpeedTypeforCurveValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
