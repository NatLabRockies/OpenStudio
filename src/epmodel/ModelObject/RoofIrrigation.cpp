/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "RoofIrrigation.hpp"
#include "RoofIrrigation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/RoofIrrigation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoofIrrigation::RoofIrrigation(const Model& model) : ModelObject(RoofIrrigation::iddObjectType(), model) {}

  RoofIrrigation::RoofIrrigation(std::shared_ptr<detail::RoofIrrigation_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType RoofIrrigation::iddObjectType() {
    return IddObjectType::RoofIrrigation;
  }

  std::vector<std::string> RoofIrrigation::irrigationModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::RoofIrrigationFields::IrrigationModelType);
  }

  boost::optional<std::string> RoofIrrigation::irrigationModelType() const {
    return getImpl<detail::RoofIrrigation_Impl>()->irrigationModelType();
  }

  bool RoofIrrigation::setIrrigationModelType(const std::string& irrigationModelType) {
    return getImpl<detail::RoofIrrigation_Impl>()->setIrrigationModelType(irrigationModelType);
  }

  void RoofIrrigation::resetIrrigationModelType() {
    getImpl<detail::RoofIrrigation_Impl>()->resetIrrigationModelType();
  }

  double RoofIrrigation::irrigationMaximumSaturationThreshold() const {
    return getImpl<detail::RoofIrrigation_Impl>()->irrigationMaximumSaturationThreshold();
  }

  bool RoofIrrigation::isIrrigationMaximumSaturationThresholdDefaulted() const {
    return getImpl<detail::RoofIrrigation_Impl>()->isIrrigationMaximumSaturationThresholdDefaulted();
  }

  bool RoofIrrigation::setIrrigationMaximumSaturationThreshold(double irrigationMaximumSaturationThreshold) {
    return getImpl<detail::RoofIrrigation_Impl>()->setIrrigationMaximumSaturationThreshold(irrigationMaximumSaturationThreshold);
  }

  void RoofIrrigation::resetIrrigationMaximumSaturationThreshold() {
    getImpl<detail::RoofIrrigation_Impl>()->resetIrrigationMaximumSaturationThreshold();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<std::string> RoofIrrigation_Impl::irrigationModelType() const {
      return getString(openstudio::RoofIrrigationFields::IrrigationModelType, true);
    }

    bool RoofIrrigation_Impl::setIrrigationModelType(const std::string& irrigationModelType) {
      return setString(openstudio::RoofIrrigationFields::IrrigationModelType, irrigationModelType);
    }

    void RoofIrrigation_Impl::resetIrrigationModelType() {
      OS_ASSERT(setString(openstudio::RoofIrrigationFields::IrrigationModelType, ""));
    }

    double RoofIrrigation_Impl::irrigationMaximumSaturationThreshold() const {
      const auto value = getDouble(openstudio::RoofIrrigationFields::IrrigationMaximumSaturationThreshold, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofIrrigation_Impl::isIrrigationMaximumSaturationThresholdDefaulted() const {
      return isEmpty(openstudio::RoofIrrigationFields::IrrigationMaximumSaturationThreshold);
    }

    bool RoofIrrigation_Impl::setIrrigationMaximumSaturationThreshold(double irrigationMaximumSaturationThreshold) {
      const bool result = setDouble(openstudio::RoofIrrigationFields::IrrigationMaximumSaturationThreshold, irrigationMaximumSaturationThreshold);
      OS_ASSERT(result);
      return result;
    }

    void RoofIrrigation_Impl::resetIrrigationMaximumSaturationThreshold() {
      OS_ASSERT(setString(openstudio::RoofIrrigationFields::IrrigationMaximumSaturationThreshold, ""));
    }

    std::vector<std::string> RoofIrrigation_Impl::irrigationModelTypeValues() const {
      return openstudio::epmodel::RoofIrrigation::irrigationModelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
