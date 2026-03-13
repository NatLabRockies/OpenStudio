/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "HVACTemplatePlantBoiler.hpp"
#include "HVACTemplatePlantBoiler_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/HVACTemplate_Plant_Boiler_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  HVACTemplatePlantBoiler::HVACTemplatePlantBoiler(const Model& model) : ModelObject(HVACTemplatePlantBoiler::iddObjectType(), model) {}

  HVACTemplatePlantBoiler::HVACTemplatePlantBoiler(std::shared_ptr<detail::HVACTemplatePlantBoiler_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType HVACTemplatePlantBoiler::iddObjectType() {
    return IddObjectType::HVACTemplate_Plant_Boiler;
  }

  std::vector<std::string> HVACTemplatePlantBoiler::boilerTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_BoilerFields::BoilerType);
  }

  std::vector<std::string> HVACTemplatePlantBoiler::fuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::HVACTemplate_Plant_BoilerFields::FuelType);
  }

  std::vector<std::string> HVACTemplatePlantBoiler::templatePlantLoopTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::HVACTemplate_Plant_BoilerFields::TemplatePlantLoopType);
  }

  std::string HVACTemplatePlantBoiler::boilerType() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->boilerType();
  }

  boost::optional<double> HVACTemplatePlantBoiler::capacity() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->capacity();
  }

  double HVACTemplatePlantBoiler::efficiency() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->efficiency();
  }

  boost::optional<std::string> HVACTemplatePlantBoiler::fuelType() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->fuelType();
  }

  boost::optional<std::string> HVACTemplatePlantBoiler::priority() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->priority();
  }

  double HVACTemplatePlantBoiler::sizingFactor() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->sizingFactor();
  }

  double HVACTemplatePlantBoiler::minimumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->minimumPartLoadRatio();
  }

  double HVACTemplatePlantBoiler::maximumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->maximumPartLoadRatio();
  }

  double HVACTemplatePlantBoiler::optimumPartLoadRatio() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->optimumPartLoadRatio();
  }

  double HVACTemplatePlantBoiler::waterOutletUpperTemperatureLimit() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->waterOutletUpperTemperatureLimit();
  }

  boost::optional<std::string> HVACTemplatePlantBoiler::templatePlantLoopType() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->templatePlantLoopType();
  }

  bool HVACTemplatePlantBoiler::isCapacityDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isCapacityDefaulted();
  }

  bool HVACTemplatePlantBoiler::isCapacityAutosized() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isCapacityAutosized();
  }

  bool HVACTemplatePlantBoiler::isEfficiencyDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isEfficiencyDefaulted();
  }

  bool HVACTemplatePlantBoiler::isSizingFactorDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isSizingFactorDefaulted();
  }

  bool HVACTemplatePlantBoiler::isMinimumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isMinimumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantBoiler::isMaximumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isMaximumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantBoiler::isOptimumPartLoadRatioDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isOptimumPartLoadRatioDefaulted();
  }

  bool HVACTemplatePlantBoiler::isWaterOutletUpperTemperatureLimitDefaulted() const {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->isWaterOutletUpperTemperatureLimitDefaulted();
  }

  bool HVACTemplatePlantBoiler::setBoilerType(const std::string& boilerType) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setBoilerType(boilerType);
  }

  bool HVACTemplatePlantBoiler::setCapacity(double capacity) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setCapacity(capacity);
  }

  bool HVACTemplatePlantBoiler::setEfficiency(double efficiency) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setEfficiency(efficiency);
  }

  bool HVACTemplatePlantBoiler::setFuelType(const std::string& fuelType) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setFuelType(fuelType);
  }

  bool HVACTemplatePlantBoiler::setPriority(const std::string& priority) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setPriority(priority);
  }

  bool HVACTemplatePlantBoiler::setSizingFactor(double sizingFactor) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setSizingFactor(sizingFactor);
  }

  bool HVACTemplatePlantBoiler::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setMinimumPartLoadRatio(minimumPartLoadRatio);
  }

  bool HVACTemplatePlantBoiler::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setMaximumPartLoadRatio(maximumPartLoadRatio);
  }

  bool HVACTemplatePlantBoiler::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setOptimumPartLoadRatio(optimumPartLoadRatio);
  }

  bool HVACTemplatePlantBoiler::setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setWaterOutletUpperTemperatureLimit(waterOutletUpperTemperatureLimit);
  }

  bool HVACTemplatePlantBoiler::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
    return getImpl<detail::HVACTemplatePlantBoiler_Impl>()->setTemplatePlantLoopType(templatePlantLoopType);
  }

  void HVACTemplatePlantBoiler::resetCapacity() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetCapacity();
  }

  void HVACTemplatePlantBoiler::autosizeCapacity() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->autosizeCapacity();
  }

  void HVACTemplatePlantBoiler::resetEfficiency() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetEfficiency();
  }

  void HVACTemplatePlantBoiler::resetFuelType() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetFuelType();
  }

  void HVACTemplatePlantBoiler::resetPriority() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetPriority();
  }

  void HVACTemplatePlantBoiler::resetSizingFactor() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetSizingFactor();
  }

  void HVACTemplatePlantBoiler::resetMinimumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetMinimumPartLoadRatio();
  }

  void HVACTemplatePlantBoiler::resetMaximumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetMaximumPartLoadRatio();
  }

  void HVACTemplatePlantBoiler::resetOptimumPartLoadRatio() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetOptimumPartLoadRatio();
  }

  void HVACTemplatePlantBoiler::resetWaterOutletUpperTemperatureLimit() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetWaterOutletUpperTemperatureLimit();
  }

  void HVACTemplatePlantBoiler::resetTemplatePlantLoopType() {
    getImpl<detail::HVACTemplatePlantBoiler_Impl>()->resetTemplatePlantLoopType();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    std::string HVACTemplatePlantBoiler_Impl::boilerType() const {
      auto value = getString(openstudio::HVACTemplate_Plant_BoilerFields::BoilerType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::setBoilerType(const std::string& boilerType) {
      return setString(openstudio::HVACTemplate_Plant_BoilerFields::BoilerType, boilerType);
    }

    boost::optional<double> HVACTemplatePlantBoiler_Impl::capacity() const {
      return getDouble(openstudio::HVACTemplate_Plant_BoilerFields::Capacity, true);
    }

    bool HVACTemplatePlantBoiler_Impl::isCapacityDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::Capacity);
    }

    bool HVACTemplatePlantBoiler_Impl::isCapacityAutosized() const {
      if (auto value = getString(openstudio::HVACTemplate_Plant_BoilerFields::Capacity, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    bool HVACTemplatePlantBoiler_Impl::setCapacity(double capacity) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::Capacity, capacity);
    }

    void HVACTemplatePlantBoiler_Impl::resetCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::Capacity, ""));
    }

    void HVACTemplatePlantBoiler_Impl::autosizeCapacity() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::Capacity, "autosize"));
    }

    double HVACTemplatePlantBoiler_Impl::efficiency() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::Efficiency, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isEfficiencyDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::Efficiency);
    }

    bool HVACTemplatePlantBoiler_Impl::setEfficiency(double efficiency) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::Efficiency, efficiency);
    }

    void HVACTemplatePlantBoiler_Impl::resetEfficiency() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::Efficiency, ""));
    }

    boost::optional<std::string> HVACTemplatePlantBoiler_Impl::fuelType() const {
      return getString(openstudio::HVACTemplate_Plant_BoilerFields::FuelType, true);
    }

    bool HVACTemplatePlantBoiler_Impl::setFuelType(const std::string& fuelType) {
      return setString(openstudio::HVACTemplate_Plant_BoilerFields::FuelType, fuelType);
    }

    void HVACTemplatePlantBoiler_Impl::resetFuelType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::FuelType, ""));
    }

    boost::optional<std::string> HVACTemplatePlantBoiler_Impl::priority() const {
      return getString(openstudio::HVACTemplate_Plant_BoilerFields::Priority, true);
    }

    bool HVACTemplatePlantBoiler_Impl::setPriority(const std::string& priority) {
      const bool result = setString(openstudio::HVACTemplate_Plant_BoilerFields::Priority, priority);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplatePlantBoiler_Impl::resetPriority() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::Priority, ""));
    }

    double HVACTemplatePlantBoiler_Impl::sizingFactor() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::SizingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isSizingFactorDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::SizingFactor);
    }

    bool HVACTemplatePlantBoiler_Impl::setSizingFactor(double sizingFactor) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::SizingFactor, sizingFactor);
    }

    void HVACTemplatePlantBoiler_Impl::resetSizingFactor() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::SizingFactor, ""));
    }

    double HVACTemplatePlantBoiler_Impl::minimumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::MinimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isMinimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::MinimumPartLoadRatio);
    }

    bool HVACTemplatePlantBoiler_Impl::setMinimumPartLoadRatio(double minimumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::MinimumPartLoadRatio, minimumPartLoadRatio);
    }

    void HVACTemplatePlantBoiler_Impl::resetMinimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::MinimumPartLoadRatio, ""));
    }

    double HVACTemplatePlantBoiler_Impl::maximumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::MaximumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isMaximumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::MaximumPartLoadRatio);
    }

    bool HVACTemplatePlantBoiler_Impl::setMaximumPartLoadRatio(double maximumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::MaximumPartLoadRatio, maximumPartLoadRatio);
    }

    void HVACTemplatePlantBoiler_Impl::resetMaximumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::MaximumPartLoadRatio, ""));
    }

    double HVACTemplatePlantBoiler_Impl::optimumPartLoadRatio() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::OptimumPartLoadRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isOptimumPartLoadRatioDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::OptimumPartLoadRatio);
    }

    bool HVACTemplatePlantBoiler_Impl::setOptimumPartLoadRatio(double optimumPartLoadRatio) {
      return setDouble(openstudio::HVACTemplate_Plant_BoilerFields::OptimumPartLoadRatio, optimumPartLoadRatio);
    }

    void HVACTemplatePlantBoiler_Impl::resetOptimumPartLoadRatio() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::OptimumPartLoadRatio, ""));
    }

    double HVACTemplatePlantBoiler_Impl::waterOutletUpperTemperatureLimit() const {
      auto value = getDouble(openstudio::HVACTemplate_Plant_BoilerFields::WaterOutletUpperTemperatureLimit, true);
      OS_ASSERT(value);
      return *value;
    }

    bool HVACTemplatePlantBoiler_Impl::isWaterOutletUpperTemperatureLimitDefaulted() const {
      return isEmpty(openstudio::HVACTemplate_Plant_BoilerFields::WaterOutletUpperTemperatureLimit);
    }

    bool HVACTemplatePlantBoiler_Impl::setWaterOutletUpperTemperatureLimit(double waterOutletUpperTemperatureLimit) {
      const bool result = setDouble(openstudio::HVACTemplate_Plant_BoilerFields::WaterOutletUpperTemperatureLimit, waterOutletUpperTemperatureLimit);
      OS_ASSERT(result);
      return result;
    }

    void HVACTemplatePlantBoiler_Impl::resetWaterOutletUpperTemperatureLimit() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::WaterOutletUpperTemperatureLimit, ""));
    }

    boost::optional<std::string> HVACTemplatePlantBoiler_Impl::templatePlantLoopType() const {
      return getString(openstudio::HVACTemplate_Plant_BoilerFields::TemplatePlantLoopType, true);
    }

    bool HVACTemplatePlantBoiler_Impl::setTemplatePlantLoopType(const std::string& templatePlantLoopType) {
      return setString(openstudio::HVACTemplate_Plant_BoilerFields::TemplatePlantLoopType, templatePlantLoopType);
    }

    void HVACTemplatePlantBoiler_Impl::resetTemplatePlantLoopType() {
      OS_ASSERT(setString(openstudio::HVACTemplate_Plant_BoilerFields::TemplatePlantLoopType, ""));
    }

    std::vector<std::string> HVACTemplatePlantBoiler_Impl::boilerTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantBoiler::boilerTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantBoiler_Impl::fuelTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantBoiler::fuelTypeValues();
    }

    std::vector<std::string> HVACTemplatePlantBoiler_Impl::templatePlantLoopTypeValues() const {
      return openstudio::epmodel::HVACTemplatePlantBoiler::templatePlantLoopTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
