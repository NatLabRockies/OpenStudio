/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorPerformancePhotovoltaicThermalSimple.hpp"
#include "SolarCollectorPerformancePhotovoltaicThermalSimple_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/SolarCollectorPerformance_PhotovoltaicThermal_Simple_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

SolarCollectorPerformancePhotovoltaicThermalSimple::SolarCollectorPerformancePhotovoltaicThermalSimple(const Model& model)
  : ModelObject(SolarCollectorPerformancePhotovoltaicThermalSimple::iddObjectType(), model) {
  OS_ASSERT(getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>());

  // Preserve model counterpart constructor behavior for scalar defaulting.
  bool ok = true;
  ok = setThermalConversionEfficiency(0.3);
  OS_ASSERT(ok);
}

SolarCollectorPerformancePhotovoltaicThermalSimple::SolarCollectorPerformancePhotovoltaicThermalSimple(
  std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType SolarCollectorPerformancePhotovoltaicThermalSimple::iddObjectType() {
  return IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_Simple;
}

std::vector<std::string> SolarCollectorPerformancePhotovoltaicThermalSimple::thermalConversionEfficiencyInputModeTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyInputModeType);
}

double SolarCollectorPerformancePhotovoltaicThermalSimple::fractionOfSurfaceAreaWithActiveThermalCollector() const {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->fractionOfSurfaceAreaWithActiveThermalCollector();
}

std::string SolarCollectorPerformancePhotovoltaicThermalSimple::thermalConversionEfficiencyInputModeType() const {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->thermalConversionEfficiencyInputModeType();
}

boost::optional<double> SolarCollectorPerformancePhotovoltaicThermalSimple::thermalConversionEfficiency() const {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->thermalConversionEfficiency();
}

double SolarCollectorPerformancePhotovoltaicThermalSimple::frontSurfaceEmittance() const {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->frontSurfaceEmittance();
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple::isFrontSurfaceEmittanceDefaulted() const {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->isFrontSurfaceEmittanceDefaulted();
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple::setFractionOfSurfaceAreaWithActiveThermalCollector(
  double fractionofSurfaceAreawithActiveThermalCollector) {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->setFractionOfSurfaceAreaWithActiveThermalCollector(
    fractionofSurfaceAreawithActiveThermalCollector);
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple::setThermalConversionEfficiency(double valueforThermalConversionEfficiencyifFixed) {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->setThermalConversionEfficiency(
    valueforThermalConversionEfficiencyifFixed);
}

void SolarCollectorPerformancePhotovoltaicThermalSimple::resetThermalConversionEfficiency() {
  getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->resetThermalConversionEfficiency();
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple::setFrontSurfaceEmittance(double frontSurfaceEmittance) {
  return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->setFrontSurfaceEmittance(frontSurfaceEmittance);
}

void SolarCollectorPerformancePhotovoltaicThermalSimple::resetFrontSurfaceEmittance() {
  getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalSimple_Impl>()->resetFrontSurfaceEmittance();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::fractionOfSurfaceAreaWithActiveThermalCollector() const {
  const auto value =
    getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FractionofSurfaceAreawithActiveThermalCollector, true);
  OS_ASSERT(value);
  return *value;
}

std::string SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::thermalConversionEfficiencyInputModeType() const {
  const auto value =
    getString(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyInputModeType, true);
  OS_ASSERT(value);
  return *value;
}

boost::optional<double> SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::thermalConversionEfficiency() const {
  boost::optional<double> result;
  if (istringEqual("Fixed", thermalConversionEfficiencyInputModeType())) {
    result =
      getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ValueforThermalConversionEfficiencyifFixed, true);
    if (!result) {
      result = 0.3;
    }
  }
  return result;
}

double SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::frontSurfaceEmittance() const {
  const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FrontSurfaceEmittance, true);
  OS_ASSERT(value);
  return *value;
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::isFrontSurfaceEmittanceDefaulted() const {
  return isEmpty(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FrontSurfaceEmittance);
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::setFractionOfSurfaceAreaWithActiveThermalCollector(
  double fractionofSurfaceAreawithActiveThermalCollector) {
  return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FractionofSurfaceAreawithActiveThermalCollector,
                   fractionofSurfaceAreawithActiveThermalCollector);
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::setThermalConversionEfficiency(
  double valueforThermalConversionEfficiencyifFixed) {
  bool result = setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ValueforThermalConversionEfficiencyifFixed,
                          valueforThermalConversionEfficiencyifFixed);
  if (result) {
    // Keep scalar input mode synchronized when fixed efficiency is set.
    result = setString(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyInputModeType,
                       "Fixed");
    OS_ASSERT(result);
    OS_ASSERT(setString(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ThermalConversionEfficiencyScheduleName, ""));
  }
  return result;
}

void SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::resetThermalConversionEfficiency() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::ValueforThermalConversionEfficiencyifFixed, ""));
}

bool SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::setFrontSurfaceEmittance(double frontSurfaceEmittance) {
  return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FrontSurfaceEmittance, frontSurfaceEmittance);
}

void SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::resetFrontSurfaceEmittance() {
  OS_ASSERT(setString(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_SimpleFields::FrontSurfaceEmittance, ""));
}

std::vector<std::string> SolarCollectorPerformancePhotovoltaicThermalSimple_Impl::thermalConversionEfficiencyInputModeTypeValues() const {
  return openstudio::epmodel::SolarCollectorPerformancePhotovoltaicThermalSimple::thermalConversionEfficiencyInputModeTypeValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
