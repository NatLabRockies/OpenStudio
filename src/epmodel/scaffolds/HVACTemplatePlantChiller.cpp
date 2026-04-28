/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantChiller.hpp"
#include "HVACTemplatePlantChiller_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_Chiller_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplatePlantChiller::HVACTemplatePlantChiller(const Model& model) : ModelObject(HVACTemplatePlantChiller::iddObjectType(), model) {}

  HVACTemplatePlantChiller::HVACTemplatePlantChiller(std::shared_ptr<detail::HVACTemplatePlantChiller_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplatePlantChiller::iddObjectType() {
    return IddObjectType::HVACTemplate_Plant_Chiller;
  }

  std::vector<std::string> HVACTemplatePlantChiller::chillerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_ChillerFields::ChillerType);
  }

  std::vector<std::string> HVACTemplatePlantChiller::condenserTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_ChillerFields::CondenserType);
  }

  std::string HVACTemplatePlantChiller::chillerType() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->chillerType();
  }

  bool HVACTemplatePlantChiller::setChillerType(const std::string& chillerType) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setChillerType(chillerType);
  }

  boost::optional<double> HVACTemplatePlantChiller::capacity() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->capacity();
  }

  bool HVACTemplatePlantChiller::isCapacityDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isCapacityDefaulted();
  }

  bool HVACTemplatePlantChiller::isCapacityAutosized() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isCapacityAutosized();
  }

  bool HVACTemplatePlantChiller::setCapacity(double capacity) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setCapacity(capacity);
  }

  void HVACTemplatePlantChiller::resetCapacity() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetCapacity();
  }

  void HVACTemplatePlantChiller::autosizeCapacity() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->autosizeCapacity();
  }

  double HVACTemplatePlantChiller::nominalCOP() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->nominalCOP();
  }

  bool HVACTemplatePlantChiller::setNominalCOP(double nominalCOP) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setNominalCOP(nominalCOP);
  }

  std::string HVACTemplatePlantChiller::condenserType() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->condenserType();
  }

  bool HVACTemplatePlantChiller::isCondenserTypeDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isCondenserTypeDefaulted();
  }

  bool HVACTemplatePlantChiller::setCondenserType(const std::string& condenserType) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setCondenserType(condenserType);
  }

  void HVACTemplatePlantChiller::resetCondenserType() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetCondenserType();
  }

  boost::optional<std::string> HVACTemplatePlantChiller::priority() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->priority();
  }

  bool HVACTemplatePlantChiller::setPriority(const std::string& priority) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setPriority(priority);
  }

  void HVACTemplatePlantChiller::resetPriority() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetPriority();
  }

  double HVACTemplatePlantChiller::sizingFactor() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->sizingFactor();
  }

  bool HVACTemplatePlantChiller::isSizingFactorDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isSizingFactorDefaulted();
  }

  bool HVACTemplatePlantChiller::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setSizingFactor(sizingFactor);
  }

  void HVACTemplatePlantChiller::resetSizingFactor() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetSizingFactor();
  }

  double HVACTemplatePlantChiller::minimumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->minimumPartLoadRatio();
  }

  bool HVACTemplatePlantChiller::isMinimumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isMinimumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantChiller::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  void HVACTemplatePlantChiller::resetMinimumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetMinimumPartLoadRatio();
  }

  double HVACTemplatePlantChiller::maximumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->maximumPartLoadRatio();
  }

  bool HVACTemplatePlantChiller::isMaximumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isMaximumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantChiller::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  void HVACTemplatePlantChiller::resetMaximumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetMaximumPartLoadRatio();
  }

  double HVACTemplatePlantChiller::optimumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->optimumPartLoadRatio();
  }

  bool HVACTemplatePlantChiller::isOptimumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isOptimumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantChiller::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  void HVACTemplatePlantChiller::resetOptimumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetOptimumPartLoadRatio();
  }

  double HVACTemplatePlantChiller::minimumUnloadingRatio() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->minimumUnloadingRatio();
  }

  bool HVACTemplatePlantChiller::isMinimumUnloadingRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isMinimumUnloadingRatioDefaulted();
  }

  bool HVACTemplatePlantChiller::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setMinimumUnloadingRatio(minimumUnloadingRatio);
  }

  void HVACTemplatePlantChiller::resetMinimumUnloadingRatio() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetMinimumUnloadingRatio();
  }

  double HVACTemplatePlantChiller::leavingChilledWaterLowerTemperatureLimit() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->leavingChilledWaterLowerTemperatureLimit();
  }

  bool HVACTemplatePlantChiller::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->isLeavingChilledWaterLowerTemperatureLimitDefaulted();
  }

  bool HVACTemplatePlantChiller::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
    return getImpl<detail::HVACTemplatePlantChiller_Impl>()->setLeavingChilledWaterLowerTemperatureLimit(leavingChilledWaterLowerTemperatureLimit);
  }

  void HVACTemplatePlantChiller::resetLeavingChilledWaterLowerTemperatureLimit() {
    getImpl<detail::HVACTemplatePlantChiller_Impl>()->resetLeavingChilledWaterLowerTemperatureLimit();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HVACTemplatePlantChiller_Impl::chillerType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChillerFields::ChillerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::setChillerType(const std::string& chillerType) {
      return setString(openstudio::HVACTemplate_Plant_ChillerFields::ChillerType, chillerType);
    }

    boost::optional<double> HVACTemplatePlantChiller_Impl::capacity() const {
      return getDouble(openstudio::HVACTemplate_Plant_ChillerFields::Capacity, true);
    }

    bool HVACTemplatePlantChiller_Impl::isCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::Capacity);
    }

    bool HVACTemplatePlantChiller_Impl::isCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_ChillerFields::Capacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantChiller_Impl::setCapacity(double capacity) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::Capacity, capacity);
    }

    void HVACTemplatePlantChiller_Impl::resetCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::Capacity, ""));
    }

    void HVACTemplatePlantChiller_Impl::autosizeCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::Capacity, "autosize"));
    }

    double HVACTemplatePlantChiller_Impl::nominalCOP() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::NominalCOP, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::setNominalCOP(double nominalCOP) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::NominalCOP, nominalCOP);
    }

    std::string HVACTemplatePlantChiller_Impl::condenserType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_ChillerFields::CondenserType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isCondenserTypeDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::CondenserType);
    }

    bool HVACTemplatePlantChiller_Impl::setCondenserType(const std::string& condenserType) {
      return setString(openstudio::HVACTemplate_Plant_ChillerFields::CondenserType, condenserType);
    }

    void HVACTemplatePlantChiller_Impl::resetCondenserType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::CondenserType, ""));
    }

    boost::optional<std::string> HVACTemplatePlantChiller_Impl::priority() const {
      return getString(openstudio::HVACTemplate_Plant_ChillerFields::Priority, true);
    }

    bool HVACTemplatePlantChiller_Impl::setPriority(const std::string& priority) {
      const bool result = setString(openstudio::HVACTemplate_Plant_ChillerFields::Priority, priority);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplatePlantChiller_Impl::resetPriority() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::Priority, ""));
    }

    double HVACTemplatePlantChiller_Impl::sizingFactor() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::SizingFactor);
    }

    bool HVACTemplatePlantChiller_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::SizingFactor, sizingFactor);
    }

    void HVACTemplatePlantChiller_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::SizingFactor, ""));
    }

    double HVACTemplatePlantChiller_Impl::minimumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::MinimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isMinimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::MinimumPartLoadRatio);
    }

    bool HVACTemplatePlantChiller_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    void HVACTemplatePlantChiller_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::MinimumPartLoadRatio, ""));
    }

    double HVACTemplatePlantChiller_Impl::maximumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::MaximumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isMaximumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::MaximumPartLoadRatio);
    }

    bool HVACTemplatePlantChiller_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    void HVACTemplatePlantChiller_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::MaximumPartLoadRatio, ""));
    }

    double HVACTemplatePlantChiller_Impl::optimumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::OptimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isOptimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::OptimumPartLoadRatio);
    }

    bool HVACTemplatePlantChiller_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    void HVACTemplatePlantChiller_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::OptimumPartLoadRatio, ""));
    }

    double HVACTemplatePlantChiller_Impl::minimumUnloadingRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::MinimumUnloadingRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isMinimumUnloadingRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::MinimumUnloadingRatio);
    }

    bool HVACTemplatePlantChiller_Impl::setMinimumUnloadingRatio(double minimumUnloadingRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_ChillerFields::MinimumUnloadingRatio, minimumUnloadingRatio);
    }

    void HVACTemplatePlantChiller_Impl::resetMinimumUnloadingRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::MinimumUnloadingRatio, ""));
    }

    double HVACTemplatePlantChiller_Impl::leavingChilledWaterLowerTemperatureLimit() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_ChillerFields::LeavingChilledWaterLowerTemperatureLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantChiller_Impl::isLeavingChilledWaterLowerTemperatureLimitDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_ChillerFields::LeavingChilledWaterLowerTemperatureLimit);
    }

    bool HVACTemplatePlantChiller_Impl::setLeavingChilledWaterLowerTemperatureLimit(double leavingChilledWaterLowerTemperatureLimit) {
      const bool result =
        setDouble(openstudio::HVACTemplate_Plant_ChillerFields::LeavingChilledWaterLowerTemperatureLimit, leavingChilledWaterLowerTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplatePlantChiller_Impl::resetLeavingChilledWaterLowerTemperatureLimit() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_ChillerFields::LeavingChilledWaterLowerTemperatureLimit, ""));
    }

    std::vector<std::string> HVACTemplatePlantChiller_Impl::chillerTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChiller::chillerTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantChiller_Impl::condenserTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantChiller::condenserTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
