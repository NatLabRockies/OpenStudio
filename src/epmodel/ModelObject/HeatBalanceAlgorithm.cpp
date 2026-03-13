/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelObject/HeatBalanceAlgorithm.hpp"
#include "ModelObject/HeatBalanceAlgorithm_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/HeatBalanceAlgorithm_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HeatBalanceAlgorithm::HeatBalanceAlgorithm(const Model& model) : ModelObject(HeatBalanceAlgorithm::iddObjectType(), model) {
    OS_ASSERT(setAlgorithm("ConductionTransferFunction"));
    OS_ASSERT(setSurfaceTemperatureUpperLimit(200.0));
  }

  HeatBalanceAlgorithm::HeatBalanceAlgorithm(std::shared_ptr<detail::HeatBalanceAlgorithm_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HeatBalanceAlgorithm::iddObjectType() {
    return IddObjectType::HeatBalanceAlgorithm;
  }

  std::vector<std::string> HeatBalanceAlgorithm::algorithmValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HeatBalanceAlgorithmFields::Algorithm);
  }

  std::string HeatBalanceAlgorithm::algorithm() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->algorithm();
  }

  bool HeatBalanceAlgorithm::isAlgorithmDefaulted() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->isAlgorithmDefaulted();
  }

  bool HeatBalanceAlgorithm::setAlgorithm(const std::string& algorithm) {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->setAlgorithm(algorithm);
  }

  void HeatBalanceAlgorithm::resetAlgorithm() {
    getImpl<detail::HeatBalanceAlgorithm_Impl>()->resetAlgorithm();
  }

  double HeatBalanceAlgorithm::surfaceTemperatureUpperLimit() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->surfaceTemperatureUpperLimit();
  }

  bool HeatBalanceAlgorithm::isSurfaceTemperatureUpperLimitDefaulted() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->isSurfaceTemperatureUpperLimitDefaulted();
  }

  bool HeatBalanceAlgorithm::setSurfaceTemperatureUpperLimit(double surfaceTemperatureUpperLimit) {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->setSurfaceTemperatureUpperLimit(surfaceTemperatureUpperLimit);
  }

  void HeatBalanceAlgorithm::resetSurfaceTemperatureUpperLimit() {
    getImpl<detail::HeatBalanceAlgorithm_Impl>()->resetSurfaceTemperatureUpperLimit();
  }

  double HeatBalanceAlgorithm::minimumSurfaceConvectionHeatTransferCoefficientValue() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->minimumSurfaceConvectionHeatTransferCoefficientValue();
  }

  bool HeatBalanceAlgorithm::isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted();
  }

  bool HeatBalanceAlgorithm::setMinimumSurfaceConvectionHeatTransferCoefficientValue(double minimumSurfaceConvectionHeatTransferCoefficientValue) {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->setMinimumSurfaceConvectionHeatTransferCoefficientValue(
      minimumSurfaceConvectionHeatTransferCoefficientValue);
  }

  void HeatBalanceAlgorithm::resetMinimumSurfaceConvectionHeatTransferCoefficientValue() {
    getImpl<detail::HeatBalanceAlgorithm_Impl>()->resetMinimumSurfaceConvectionHeatTransferCoefficientValue();
  }

  double HeatBalanceAlgorithm::maximumSurfaceConvectionHeatTransferCoefficientValue() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->maximumSurfaceConvectionHeatTransferCoefficientValue();
  }

  bool HeatBalanceAlgorithm::isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted();
  }

  bool HeatBalanceAlgorithm::setMaximumSurfaceConvectionHeatTransferCoefficientValue(double maximumSurfaceConvectionHeatTransferCoefficientValue) {
    return getImpl<detail::HeatBalanceAlgorithm_Impl>()->setMaximumSurfaceConvectionHeatTransferCoefficientValue(
      maximumSurfaceConvectionHeatTransferCoefficientValue);
  }

  void HeatBalanceAlgorithm::resetMaximumSurfaceConvectionHeatTransferCoefficientValue() {
    getImpl<detail::HeatBalanceAlgorithm_Impl>()->resetMaximumSurfaceConvectionHeatTransferCoefficientValue();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HeatBalanceAlgorithm_Impl::algorithm() const {
      const auto value = getString(openstudio::HeatBalanceAlgorithmFields::Algorithm, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceAlgorithm_Impl::isAlgorithmDefaulted() const {
      return isEmpty(openstudio::HeatBalanceAlgorithmFields::Algorithm);
    }

    double HeatBalanceAlgorithm_Impl::surfaceTemperatureUpperLimit() const {
      const auto value = getDouble(openstudio::HeatBalanceAlgorithmFields::SurfaceTemperatureUpperLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceAlgorithm_Impl::isSurfaceTemperatureUpperLimitDefaulted() const {
      return isEmpty(openstudio::HeatBalanceAlgorithmFields::SurfaceTemperatureUpperLimit);
    }

    double HeatBalanceAlgorithm_Impl::minimumSurfaceConvectionHeatTransferCoefficientValue() const {
      const auto value = getDouble(openstudio::HeatBalanceAlgorithmFields::MinimumSurfaceConvectionHeatTransferCoefficientValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceAlgorithm_Impl::isMinimumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const {
      return isEmpty(openstudio::HeatBalanceAlgorithmFields::MinimumSurfaceConvectionHeatTransferCoefficientValue);
    }

    double HeatBalanceAlgorithm_Impl::maximumSurfaceConvectionHeatTransferCoefficientValue() const {
      const auto value = getDouble(openstudio::HeatBalanceAlgorithmFields::MaximumSurfaceConvectionHeatTransferCoefficientValue, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HeatBalanceAlgorithm_Impl::isMaximumSurfaceConvectionHeatTransferCoefficientValueDefaulted() const {
      return isEmpty(openstudio::HeatBalanceAlgorithmFields::MaximumSurfaceConvectionHeatTransferCoefficientValue);
    }

    bool HeatBalanceAlgorithm_Impl::setAlgorithm(const std::string& algorithm) {
      return setString(openstudio::HeatBalanceAlgorithmFields::Algorithm, algorithm);
    }

    void HeatBalanceAlgorithm_Impl::resetAlgorithm() {
      OS_ASSERT(setString(openstudio::HeatBalanceAlgorithmFields::Algorithm, ""));
    }

    bool HeatBalanceAlgorithm_Impl::setSurfaceTemperatureUpperLimit(double surfaceTemperatureUpperLimit) {
      return setDouble(openstudio::HeatBalanceAlgorithmFields::SurfaceTemperatureUpperLimit, surfaceTemperatureUpperLimit);
    }

    void HeatBalanceAlgorithm_Impl::resetSurfaceTemperatureUpperLimit() {
      OS_ASSERT(setString(openstudio::HeatBalanceAlgorithmFields::SurfaceTemperatureUpperLimit, ""));
    }

    bool HeatBalanceAlgorithm_Impl::setMinimumSurfaceConvectionHeatTransferCoefficientValue(
      double minimumSurfaceConvectionHeatTransferCoefficientValue) {
      return setDouble(openstudio::HeatBalanceAlgorithmFields::MinimumSurfaceConvectionHeatTransferCoefficientValue,
                       minimumSurfaceConvectionHeatTransferCoefficientValue);
    }

    void HeatBalanceAlgorithm_Impl::resetMinimumSurfaceConvectionHeatTransferCoefficientValue() {
      OS_ASSERT(setString(openstudio::HeatBalanceAlgorithmFields::MinimumSurfaceConvectionHeatTransferCoefficientValue, ""));
    }

    bool HeatBalanceAlgorithm_Impl::setMaximumSurfaceConvectionHeatTransferCoefficientValue(
      double maximumSurfaceConvectionHeatTransferCoefficientValue) {
      return setDouble(openstudio::HeatBalanceAlgorithmFields::MaximumSurfaceConvectionHeatTransferCoefficientValue,
                       maximumSurfaceConvectionHeatTransferCoefficientValue);
    }

    void HeatBalanceAlgorithm_Impl::resetMaximumSurfaceConvectionHeatTransferCoefficientValue() {
      OS_ASSERT(setString(openstudio::HeatBalanceAlgorithmFields::MaximumSurfaceConvectionHeatTransferCoefficientValue, ""));
    }

    std::vector<std::string> HeatBalanceAlgorithm_Impl::algorithmValues() const {
      return openstudio::epmodel::HeatBalanceAlgorithm::algorithmValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
