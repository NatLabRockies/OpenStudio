/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include "ZoneHVACHybridUnitaryHVAC.hpp"
#include "ZoneHVACHybridUnitaryHVAC_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_HybridUnitaryHVAC_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACHybridUnitaryHVAC::ZoneHVACHybridUnitaryHVAC(const Model& model) : ModelObject(ZoneHVACHybridUnitaryHVAC::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>());
  }

  ZoneHVACHybridUnitaryHVAC::ZoneHVACHybridUnitaryHVAC(std::shared_ptr<detail::ZoneHVACHybridUnitaryHVAC_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType ZoneHVACHybridUnitaryHVAC::iddObjectType() {
    return IddObjectType::ZoneHVAC_HybridUnitaryHVAC;
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::methodToChooseControlledInputsAndPartRuntimeFractionValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction);
  }

  std::string ZoneHVACHybridUnitaryHVAC::methodToChooseControlledInputsAndPartRuntimeFraction() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->methodToChooseControlledInputsAndPartRuntimeFraction();
  }

  bool ZoneHVACHybridUnitaryHVAC::setMethodToChooseControlledInputsAndPartRuntimeFraction(
    const std::string& methodToChooseControlledInputsAndPartRuntimeFraction) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setMethodToChooseControlledInputsAndPartRuntimeFraction(
      methodToChooseControlledInputsAndPartRuntimeFraction);
  }

  bool ZoneHVACHybridUnitaryHVAC::isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetMethodToChooseControlledInputsAndPartRuntimeFraction() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetMethodToChooseControlledInputsAndPartRuntimeFraction();
  }

  boost::optional<double> ZoneHVACHybridUnitaryHVAC::systemMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->systemMaximumSupplyAirFlowRate();
  }

  bool ZoneHVACHybridUnitaryHVAC::setSystemMaximumSupplyAirFlowRate(double systemMaximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setSystemMaximumSupplyAirFlowRate(systemMaximumSupplyAirFlowRate);
  }

  void ZoneHVACHybridUnitaryHVAC::resetSystemMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetSystemMaximumSupplyAirFlowRate();
  }

  boost::optional<double> ZoneHVACHybridUnitaryHVAC::externalStaticPressureAtSystemMaximumSupplyAirFlowRate() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->externalStaticPressureAtSystemMaximumSupplyAirFlowRate();
  }

  bool ZoneHVACHybridUnitaryHVAC::setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(
    double externalStaticPressureAtSystemMaximumSupplyAirFlowRate) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(
      externalStaticPressureAtSystemMaximumSupplyAirFlowRate);
  }

  void ZoneHVACHybridUnitaryHVAC::resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::fanHeatIncludedInLookupTablesValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables);
  }

  std::string ZoneHVACHybridUnitaryHVAC::fanHeatIncludedInLookupTables() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->fanHeatIncludedInLookupTables();
  }

  bool ZoneHVACHybridUnitaryHVAC::setFanHeatIncludedInLookupTables(const std::string& fanHeatIncludedInLookupTables) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setFanHeatIncludedInLookupTables(fanHeatIncludedInLookupTables);
  }

  bool ZoneHVACHybridUnitaryHVAC::isFanHeatIncludedInLookupTablesDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isFanHeatIncludedInLookupTablesDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetFanHeatIncludedInLookupTables() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetFanHeatIncludedInLookupTables();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::fanHeatGainLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation);
  }

  std::string ZoneHVACHybridUnitaryHVAC::fanHeatGainLocation() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->fanHeatGainLocation();
  }

  bool ZoneHVACHybridUnitaryHVAC::setFanHeatGainLocation(const std::string& fanHeatGainLocation) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setFanHeatGainLocation(fanHeatGainLocation);
  }

  bool ZoneHVACHybridUnitaryHVAC::isFanHeatGainLocationDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isFanHeatGainLocationDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetFanHeatGainLocation() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetFanHeatGainLocation();
  }

  double ZoneHVACHybridUnitaryHVAC::fanHeatInAirStreamFraction() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->fanHeatInAirStreamFraction();
  }

  bool ZoneHVACHybridUnitaryHVAC::setFanHeatInAirStreamFraction(double fanHeatInAirStreamFraction) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setFanHeatInAirStreamFraction(fanHeatInAirStreamFraction);
  }

  bool ZoneHVACHybridUnitaryHVAC::isFanHeatInAirStreamFractionDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isFanHeatInAirStreamFractionDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetFanHeatInAirStreamFraction() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetFanHeatInAirStreamFraction();
  }

  double ZoneHVACHybridUnitaryHVAC::scalingFactor() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->scalingFactor();
  }

  bool ZoneHVACHybridUnitaryHVAC::setScalingFactor(double scalingFactor) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setScalingFactor(scalingFactor);
  }

  bool ZoneHVACHybridUnitaryHVAC::isScalingFactorDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isScalingFactorDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetScalingFactor() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetScalingFactor();
  }

  double ZoneHVACHybridUnitaryHVAC::minimumTimeBetweenModeChange() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->minimumTimeBetweenModeChange();
  }

  bool ZoneHVACHybridUnitaryHVAC::setMinimumTimeBetweenModeChange(double minimumTimeBetweenModeChange) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setMinimumTimeBetweenModeChange(minimumTimeBetweenModeChange);
  }

  bool ZoneHVACHybridUnitaryHVAC::isMinimumTimeBetweenModeChangeDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isMinimumTimeBetweenModeChangeDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetMinimumTimeBetweenModeChange() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetMinimumTimeBetweenModeChange();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::firstFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType);
  }

  std::string ZoneHVACHybridUnitaryHVAC::firstFuelType() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->firstFuelType();
  }

  bool ZoneHVACHybridUnitaryHVAC::setFirstFuelType(const std::string& firstFuelType) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setFirstFuelType(firstFuelType);
  }

  bool ZoneHVACHybridUnitaryHVAC::isFirstFuelTypeDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isFirstFuelTypeDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetFirstFuelType() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetFirstFuelType();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::secondFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType);
  }

  std::string ZoneHVACHybridUnitaryHVAC::secondFuelType() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->secondFuelType();
  }

  bool ZoneHVACHybridUnitaryHVAC::setSecondFuelType(const std::string& secondFuelType) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setSecondFuelType(secondFuelType);
  }

  bool ZoneHVACHybridUnitaryHVAC::isSecondFuelTypeDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isSecondFuelTypeDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetSecondFuelType() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetSecondFuelType();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::thirdFuelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType);
  }

  std::string ZoneHVACHybridUnitaryHVAC::thirdFuelType() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->thirdFuelType();
  }

  bool ZoneHVACHybridUnitaryHVAC::setThirdFuelType(const std::string& thirdFuelType) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setThirdFuelType(thirdFuelType);
  }

  bool ZoneHVACHybridUnitaryHVAC::isThirdFuelTypeDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isThirdFuelTypeDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetThirdFuelType() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetThirdFuelType();
  }

  std::vector<std::string> ZoneHVACHybridUnitaryHVAC::objectiveFunctionToMinimizeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize);
  }

  std::string ZoneHVACHybridUnitaryHVAC::objectiveFunctionToMinimize() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->objectiveFunctionToMinimize();
  }

  bool ZoneHVACHybridUnitaryHVAC::setObjectiveFunctionToMinimize(const std::string& objectiveFunctionToMinimize) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setObjectiveFunctionToMinimize(objectiveFunctionToMinimize);
  }

  bool ZoneHVACHybridUnitaryHVAC::isObjectiveFunctionToMinimizeDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isObjectiveFunctionToMinimizeDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetObjectiveFunctionToMinimize() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetObjectiveFunctionToMinimize();
  }

  double ZoneHVACHybridUnitaryHVAC::mode0OutdoorAirFraction() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->mode0OutdoorAirFraction();
  }

  bool ZoneHVACHybridUnitaryHVAC::setMode0OutdoorAirFraction(double mode0OutdoorAirFraction) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setMode0OutdoorAirFraction(mode0OutdoorAirFraction);
  }

  bool ZoneHVACHybridUnitaryHVAC::isMode0OutdoorAirFractionDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isMode0OutdoorAirFractionDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetMode0OutdoorAirFraction() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetMode0OutdoorAirFraction();
  }

  double ZoneHVACHybridUnitaryHVAC::mode0SupplyAirMassFlowRateRatio() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->mode0SupplyAirMassFlowRateRatio();
  }

  bool ZoneHVACHybridUnitaryHVAC::setMode0SupplyAirMassFlowRateRatio(double mode0SupplyAirMassFlowRateRatio) {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->setMode0SupplyAirMassFlowRateRatio(mode0SupplyAirMassFlowRateRatio);
  }

  bool ZoneHVACHybridUnitaryHVAC::isMode0SupplyAirMassFlowRateRatioDefaulted() const {
    return getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->isMode0SupplyAirMassFlowRateRatioDefaulted();
  }

  void ZoneHVACHybridUnitaryHVAC::resetMode0SupplyAirMassFlowRateRatio() {
    getImpl<detail::ZoneHVACHybridUnitaryHVAC_Impl>()->resetMode0SupplyAirMassFlowRateRatio();
  }

  namespace detail {

    std::string ZoneHVACHybridUnitaryHVAC_Impl::methodToChooseControlledInputsAndPartRuntimeFraction() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isMethodToChooseControlledInputsAndPartRuntimeFractionDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setMethodToChooseControlledInputsAndPartRuntimeFraction(
      const std::string& methodToChooseControlledInputsAndPartRuntimeFraction) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction,
                                    methodToChooseControlledInputsAndPartRuntimeFraction, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetMethodToChooseControlledInputsAndPartRuntimeFraction() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::methodToChooseControlledInputsAndPartRuntimeFractionValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::methodToChooseControlledInputsAndPartRuntimeFractionValues();
    }

    boost::optional<double> ZoneHVACHybridUnitaryHVAC_Impl::systemMaximumSupplyAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SystemMaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setSystemMaximumSupplyAirFlowRate(double systemMaximumSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SystemMaximumSupplyAirFlowRate, systemMaximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetSystemMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SystemMaximumSupplyAirFlowRate, ""));
    }

    boost::optional<double> ZoneHVACHybridUnitaryHVAC_Impl::externalStaticPressureAtSystemMaximumSupplyAirFlowRate() const {
      return getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ExternalStaticPressureatSystemMaximumSupplyAirFlowRate, true);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setExternalStaticPressureAtSystemMaximumSupplyAirFlowRate(
      double externalStaticPressureAtSystemMaximumSupplyAirFlowRate) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ExternalStaticPressureatSystemMaximumSupplyAirFlowRate,
                                    externalStaticPressureAtSystemMaximumSupplyAirFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetExternalStaticPressureAtSystemMaximumSupplyAirFlowRate() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ExternalStaticPressureatSystemMaximumSupplyAirFlowRate, ""));
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::fanHeatIncludedInLookupTables() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isFanHeatIncludedInLookupTablesDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setFanHeatIncludedInLookupTables(const std::string& fanHeatIncludedInLookupTables) {
      const bool result =
        setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables, fanHeatIncludedInLookupTables, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetFanHeatIncludedInLookupTables() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::fanHeatIncludedInLookupTablesValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::fanHeatIncludedInLookupTablesValues();
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::fanHeatGainLocation() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isFanHeatGainLocationDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setFanHeatGainLocation(const std::string& fanHeatGainLocation) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation, fanHeatGainLocation, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetFanHeatGainLocation() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::fanHeatGainLocationValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::fanHeatGainLocationValues();
    }

    double ZoneHVACHybridUnitaryHVAC_Impl::fanHeatInAirStreamFraction() const {
      const auto value = getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatInAirStreamFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setFanHeatInAirStreamFraction(double fanHeatInAirStreamFraction) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatInAirStreamFraction, fanHeatInAirStreamFraction);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isFanHeatInAirStreamFractionDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatInAirStreamFraction);
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetFanHeatInAirStreamFraction() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FanHeatInAirStreamFraction, ""));
    }

    double ZoneHVACHybridUnitaryHVAC_Impl::scalingFactor() const {
      const auto value = getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ScalingFactor, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setScalingFactor(double scalingFactor) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ScalingFactor, scalingFactor);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isScalingFactorDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ScalingFactor);
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetScalingFactor() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ScalingFactor, ""));
    }

    double ZoneHVACHybridUnitaryHVAC_Impl::minimumTimeBetweenModeChange() const {
      const auto value = getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MinimumTimeBetweenModeChange, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setMinimumTimeBetweenModeChange(double minimumTimeBetweenModeChange) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MinimumTimeBetweenModeChange, minimumTimeBetweenModeChange);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isMinimumTimeBetweenModeChangeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MinimumTimeBetweenModeChange);
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetMinimumTimeBetweenModeChange() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::MinimumTimeBetweenModeChange, ""));
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::firstFuelType() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isFirstFuelTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setFirstFuelType(const std::string& firstFuelType) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType, firstFuelType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetFirstFuelType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::firstFuelTypeValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::firstFuelTypeValues();
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::secondFuelType() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isSecondFuelTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setSecondFuelType(const std::string& secondFuelType) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType, secondFuelType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetSecondFuelType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::secondFuelTypeValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::secondFuelTypeValues();
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::thirdFuelType() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isThirdFuelTypeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setThirdFuelType(const std::string& thirdFuelType) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType, thirdFuelType, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetThirdFuelType() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::thirdFuelTypeValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::thirdFuelTypeValues();
    }

    std::string ZoneHVACHybridUnitaryHVAC_Impl::objectiveFunctionToMinimize() const {
      const auto value = getString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isObjectiveFunctionToMinimizeDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize);
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setObjectiveFunctionToMinimize(const std::string& objectiveFunctionToMinimize) {
      const bool result = setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize, objectiveFunctionToMinimize, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetObjectiveFunctionToMinimize() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize, "", false));
    }

    std::vector<std::string> ZoneHVACHybridUnitaryHVAC_Impl::objectiveFunctionToMinimizeValues() const {
      return openstudio::epmodel::ZoneHVACHybridUnitaryHVAC::objectiveFunctionToMinimizeValues();
    }

    double ZoneHVACHybridUnitaryHVAC_Impl::mode0OutdoorAirFraction() const {
      const auto value = getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0OutdoorAirFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setMode0OutdoorAirFraction(double mode0OutdoorAirFraction) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0OutdoorAirFraction, mode0OutdoorAirFraction);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isMode0OutdoorAirFractionDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0OutdoorAirFraction);
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetMode0OutdoorAirFraction() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0OutdoorAirFraction, ""));
    }

    double ZoneHVACHybridUnitaryHVAC_Impl::mode0SupplyAirMassFlowRateRatio() const {
      const auto value = getDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirMassFlowRateRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::setMode0SupplyAirMassFlowRateRatio(double mode0SupplyAirMassFlowRateRatio) {
      const bool result = setDouble(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirMassFlowRateRatio, mode0SupplyAirMassFlowRateRatio);
      OS_ASSERT(result);
      return result;
    }

    bool ZoneHVACHybridUnitaryHVAC_Impl::isMode0SupplyAirMassFlowRateRatioDefaulted() const {
      return isEmpty(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirMassFlowRateRatio);
    }

    void ZoneHVACHybridUnitaryHVAC_Impl::resetMode0SupplyAirMassFlowRateRatio() {
      OS_ASSERT(setString(openstudio::ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirMassFlowRateRatio, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
