/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/GeneratorFuelCellExhaustGasToWaterHeatExchanger.hpp"
#include "StraightComponent/GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl.hpp"

#include "Generator/GeneratorFuelCell.hpp"
#include "Generator/GeneratorFuelCell_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Model.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Generator_FuelCell_ExhaustGasToWaterHeatExchanger_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

GeneratorFuelCellExhaustGasToWaterHeatExchanger::GeneratorFuelCellExhaustGasToWaterHeatExchanger(const Model& model, const Node& exhaustOutletAirNode)
  : StraightComponent(GeneratorFuelCellExhaustGasToWaterHeatExchanger::iddObjectType(), model) {
  OS_ASSERT(setExhaustOutletAirNode(exhaustOutletAirNode));
  OS_ASSERT(setHeatRecoveryWaterMaximumFlowRate(0.0004));
  OS_ASSERT(setHeatExchangerCalculationMethod("FixedEffectiveness"));
}

GeneratorFuelCellExhaustGasToWaterHeatExchanger::GeneratorFuelCellExhaustGasToWaterHeatExchanger(const Model& model)
  : StraightComponent(GeneratorFuelCellExhaustGasToWaterHeatExchanger::iddObjectType(), model) {
  OS_ASSERT(setHeatRecoveryWaterMaximumFlowRate(0.0004));
  OS_ASSERT(setHeatExchangerCalculationMethod("Condensing"));
  OS_ASSERT(setMethod2Parameterhxs0(83.1));
  OS_ASSERT(setMethod2Parameterhxs1(4798.0));
  OS_ASSERT(setMethod2Parameterhxs2(-138e3));
  OS_ASSERT(setMethod2Parameterhxs3(-353.8e3));
  OS_ASSERT(setMethod2Parameterhxs4(5.15e8));
  OS_ASSERT(setMethod4hxl1Coefficient(-0.000196));
  OS_ASSERT(setMethod4hxl2Coefficient(0.0031));
  OS_ASSERT(setMethod4CondensationThreshold(35.0));
}

GeneratorFuelCellExhaustGasToWaterHeatExchanger::GeneratorFuelCellExhaustGasToWaterHeatExchanger(
  std::shared_ptr<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl> impl)
  : StraightComponent(std::move(impl)) {}

IddObjectType GeneratorFuelCellExhaustGasToWaterHeatExchanger::iddObjectType() {
  return IddObjectType::Generator_FuelCell_ExhaustGasToWaterHeatExchanger;
}

std::vector<std::string> GeneratorFuelCellExhaustGasToWaterHeatExchanger::heatExchangerCalculationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatExchangerCalculationMethod);
}

double GeneratorFuelCellExhaustGasToWaterHeatExchanger::heatRecoveryWaterMaximumFlowRate() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->heatRecoveryWaterMaximumFlowRate();
}

boost::optional<Node> GeneratorFuelCellExhaustGasToWaterHeatExchanger::exhaustOutletAirNode() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->exhaustOutletAirNode();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setHeatRecoveryWaterMaximumFlowRate(double heatRecoveryWaterMaximumFlowRate) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setHeatRecoveryWaterMaximumFlowRate(
    heatRecoveryWaterMaximumFlowRate);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetHeatRecoveryWaterMaximumFlowRate() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetHeatRecoveryWaterMaximumFlowRate();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setExhaustOutletAirNode(const Node& node) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setExhaustOutletAirNode(node);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetExhaustOutletAirNode() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetExhaustOutletAirNode();
}

std::string GeneratorFuelCellExhaustGasToWaterHeatExchanger::heatExchangerCalculationMethod() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->heatExchangerCalculationMethod();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setHeatExchangerCalculationMethod(const std::string& heatExchangerCalculationMethod) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setHeatExchangerCalculationMethod(
    heatExchangerCalculationMethod);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetHeatExchangerCalculationMethod() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetHeatExchangerCalculationMethod();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method1HeatExchangerEffectiveness() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method1HeatExchangerEffectiveness();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod1HeatExchangerEffectiveness(double method1HeatExchangerEffectiveness) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod1HeatExchangerEffectiveness(
    method1HeatExchangerEffectiveness);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod1HeatExchangerEffectiveness() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod1HeatExchangerEffectiveness();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method2Parameterhxs0() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method2Parameterhxs0();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod2Parameterhxs0(double method2Parameterhxs0) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod2Parameterhxs0(method2Parameterhxs0);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod2Parameterhxs0() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod2Parameterhxs0();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method2Parameterhxs1() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method2Parameterhxs1();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod2Parameterhxs1(double method2Parameterhxs1) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod2Parameterhxs1(method2Parameterhxs1);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod2Parameterhxs1() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod2Parameterhxs1();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method2Parameterhxs2() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method2Parameterhxs2();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod2Parameterhxs2(double method2Parameterhxs2) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod2Parameterhxs2(method2Parameterhxs2);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod2Parameterhxs2() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod2Parameterhxs2();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method2Parameterhxs3() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method2Parameterhxs3();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod2Parameterhxs3(double method2Parameterhxs3) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod2Parameterhxs3(method2Parameterhxs3);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod2Parameterhxs3() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod2Parameterhxs3();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method2Parameterhxs4() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method2Parameterhxs4();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod2Parameterhxs4(double method2Parameterhxs4) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod2Parameterhxs4(method2Parameterhxs4);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod2Parameterhxs4() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod2Parameterhxs4();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3h0GasCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3h0GasCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3h0GasCoefficient(double method3h0GasCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3h0GasCoefficient(method3h0GasCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3h0GasCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3h0GasCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3NdotGasRefCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3NdotGasRefCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3NdotGasRefCoefficient(double method3NdotGasRefCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3NdotGasRefCoefficient(
    method3NdotGasRefCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3NdotGasRefCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3NdotGasRefCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3nCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3nCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3nCoefficient(double method3nCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3nCoefficient(method3nCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3nCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3nCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3GasArea() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3GasArea();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3GasArea(double method3GasArea) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3GasArea(method3GasArea);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3GasArea() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3GasArea();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3h0WaterCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3h0WaterCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3h0WaterCoefficient(double method3h0WaterCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3h0WaterCoefficient(method3h0WaterCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3h0WaterCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3h0WaterCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3NdotWaterrefCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3NdotWaterrefCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3NdotWaterrefCoefficient(double method3NdotWaterrefCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3NdotWaterrefCoefficient(
    method3NdotWaterrefCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3NdotWaterrefCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3NdotWaterrefCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3mCoefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3mCoefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3mCoefficient(double method3mCoefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3mCoefficient(method3mCoefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3mCoefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3mCoefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3WaterArea() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3WaterArea();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3WaterArea(double method3WaterArea) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3WaterArea(method3WaterArea);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3WaterArea() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3WaterArea();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method3FAdjustmentFactor() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method3FAdjustmentFactor();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod3FAdjustmentFactor(double method3FAdjustmentFactor) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod3FAdjustmentFactor(method3FAdjustmentFactor);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod3FAdjustmentFactor() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod3FAdjustmentFactor();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method4hxl1Coefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method4hxl1Coefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod4hxl1Coefficient(double method4hxl1Coefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod4hxl1Coefficient(method4hxl1Coefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod4hxl1Coefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod4hxl1Coefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method4hxl2Coefficient() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method4hxl2Coefficient();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod4hxl2Coefficient(double method4hxl2Coefficient) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod4hxl2Coefficient(method4hxl2Coefficient);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod4hxl2Coefficient() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod4hxl2Coefficient();
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger::method4CondensationThreshold() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->method4CondensationThreshold();
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger::setMethod4CondensationThreshold(double method4CondensationThreshold) {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->setMethod4CondensationThreshold(
    method4CondensationThreshold);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger::resetMethod4CondensationThreshold() {
  getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->resetMethod4CondensationThreshold();
}

boost::optional<GeneratorFuelCell> GeneratorFuelCellExhaustGasToWaterHeatExchanger::fuelCell() const {
  return getImpl<detail::GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl>()->fuelCell();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::inletPort() const {
  // Relationship mapping only: Heat Recovery Water Inlet Node Name
  return openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterInletNodeName;
}

unsigned GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::outletPort() const {
  // Relationship mapping only: Heat Recovery Water Outlet Node Name
  return openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterOutletNodeName;
}

double GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::heatRecoveryWaterMaximumFlowRate() const {
  const auto value = getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterMaximumFlowRate, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setHeatRecoveryWaterMaximumFlowRate(double heatRecoveryWaterMaximumFlowRate) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterMaximumFlowRate,
              heatRecoveryWaterMaximumFlowRate);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetHeatRecoveryWaterMaximumFlowRate() {
  OS_ASSERT(setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatRecoveryWaterMaximumFlowRate, 0.0));
}

boost::optional<openstudio::epmodel::Node> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::exhaustOutletAirNode() const {
  return getObject<ModelObject>().getModelObjectTarget<openstudio::epmodel::Node>(
    openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::ExhaustOutletAirNodeName);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setExhaustOutletAirNode(const openstudio::epmodel::Node& node) {
  return setPointer(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::ExhaustOutletAirNodeName, node.handle(), false);
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetExhaustOutletAirNode() {
  OS_ASSERT(setPointer(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::ExhaustOutletAirNodeName, Handle(), false));
}

std::string GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::heatExchangerCalculationMethod() const {
  const auto value = getString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatExchangerCalculationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setHeatExchangerCalculationMethod(const std::string& heatExchangerCalculationMethod) {
  bool result =
    setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::HeatExchangerCalculationMethod,
              heatExchangerCalculationMethod);

  if (openstudio::istringEqual(heatExchangerCalculationMethod, "FixedEffectiveness")) {
    setMethod1HeatExchangerEffectiveness(1.0);
  } else if (openstudio::istringEqual(heatExchangerCalculationMethod, "EmpiricalUAeff")) {
    setMethod2Parameterhxs0(1.0);
    setMethod2Parameterhxs1(0.0);
    setMethod2Parameterhxs2(0.0);
    setMethod2Parameterhxs3(0.0);
    setMethod2Parameterhxs4(0.0);
  } else if (openstudio::istringEqual(heatExchangerCalculationMethod, "FundementalUAeff")) {
    setMethod3FAdjustmentFactor(0.0);
    setMethod3GasArea(1.0);
    setMethod3h0GasCoefficient(1.0);
    setMethod3h0WaterCoefficient(1.0);
    setMethod3mCoefficient(1.0);
    setMethod3nCoefficient(1.0);
    setMethod3NdotGasRefCoefficient(1.0);
    setMethod3NdotWaterrefCoefficient(1.0);
    setMethod3WaterArea(1.0);
  } else if (openstudio::istringEqual(heatExchangerCalculationMethod, "Condensing")) {
    setMethod4CondensationThreshold(35.0);
    setMethod4hxl1Coefficient(1.0);
    setMethod4hxl2Coefficient(1.0);
  }

  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetHeatExchangerCalculationMethod() {
  const bool result = setHeatExchangerCalculationMethod("FixedEffectiveness");
  OS_ASSERT(result);
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method1HeatExchangerEffectiveness() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method1HeatExchangerEffectiveness, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod1HeatExchangerEffectiveness(double method1HeatExchangerEffectiveness) {
  const bool result =
    setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method1HeatExchangerEffectiveness,
              method1HeatExchangerEffectiveness);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod1HeatExchangerEffectiveness() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method1HeatExchangerEffectiveness, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method2Parameterhxs0() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs0, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod2Parameterhxs0(double method2Parameterhxs0) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs0, method2Parameterhxs0);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod2Parameterhxs0() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs0, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method2Parameterhxs1() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs1, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod2Parameterhxs1(double method2Parameterhxs1) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs1, method2Parameterhxs1);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod2Parameterhxs1() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs1, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method2Parameterhxs2() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs2, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod2Parameterhxs2(double method2Parameterhxs2) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs2, method2Parameterhxs2);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod2Parameterhxs2() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs2, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method2Parameterhxs3() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs3, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod2Parameterhxs3(double method2Parameterhxs3) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs3, method2Parameterhxs3);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod2Parameterhxs3() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs3, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method2Parameterhxs4() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs4, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod2Parameterhxs4(double method2Parameterhxs4) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs4, method2Parameterhxs4);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod2Parameterhxs4() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method2Parameterhxs4, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3h0GasCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0GasCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3h0GasCoefficient(double method3h0GasCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0GasCoefficient,
                                method3h0GasCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3h0GasCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0GasCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3NdotGasRefCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotGasRefCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3NdotGasRefCoefficient(double method3NdotGasRefCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotGasRefCoefficient,
                                method3NdotGasRefCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3NdotGasRefCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotGasRefCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3nCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3nCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3nCoefficient(double method3nCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3nCoefficient, method3nCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3nCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3nCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3GasArea() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3GasArea, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3GasArea(double method3GasArea) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3GasArea, method3GasArea);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3GasArea() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3GasArea, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3h0WaterCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0WaterCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3h0WaterCoefficient(double method3h0WaterCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0WaterCoefficient,
                                method3h0WaterCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3h0WaterCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3h0WaterCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3NdotWaterrefCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotWaterrefCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3NdotWaterrefCoefficient(double method3NdotWaterrefCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotWaterrefCoefficient,
                                method3NdotWaterrefCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3NdotWaterrefCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3NdotWaterrefCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3mCoefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3mCoefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3mCoefficient(double method3mCoefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3mCoefficient, method3mCoefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3mCoefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3mCoefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3WaterArea() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3WaterArea, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3WaterArea(double method3WaterArea) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3WaterArea, method3WaterArea);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3WaterArea() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3WaterArea, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method3FAdjustmentFactor() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3FAdjustmentFactor, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod3FAdjustmentFactor(double method3FAdjustmentFactor) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3FAdjustmentFactor,
                                method3FAdjustmentFactor);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod3FAdjustmentFactor() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method3FAdjustmentFactor, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method4hxl1Coefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl1Coefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod4hxl1Coefficient(double method4hxl1Coefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl1Coefficient,
                                method4hxl1Coefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod4hxl1Coefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl1Coefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method4hxl2Coefficient() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl2Coefficient, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod4hxl2Coefficient(double method4hxl2Coefficient) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl2Coefficient,
                                method4hxl2Coefficient);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod4hxl2Coefficient() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4hxl2Coefficient, ""));
}

boost::optional<double> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::method4CondensationThreshold() const {
  return getDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4CondensationThreshold, true);
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::setMethod4CondensationThreshold(double method4CondensationThreshold) {
  const bool result = setDouble(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4CondensationThreshold,
                                method4CondensationThreshold);
  OS_ASSERT(result);
  return result;
}

void GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::resetMethod4CondensationThreshold() {
  OS_ASSERT(setString(openstudio::Generator_FuelCell_ExhaustGasToWaterHeatExchangerFields::Method4CondensationThreshold, ""));
}

boost::optional<openstudio::epmodel::GeneratorFuelCell> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::fuelCell() const {
  boost::optional<openstudio::epmodel::GeneratorFuelCell> result;
  unsigned count = 0;

  for (const auto& source : getObject<ModelObject>().sources()) {
    if (auto generator = source.optionalCast<openstudio::epmodel::GeneratorFuelCell>()) {
      ++count;
      if (!result) {
        result = generator;
      }
    }
  }

  if (count > 1u) {
    LOG_FREE(Error, "openstudio.epmodel.GeneratorFuelCellExhaustGasToWaterHeatExchanger",
             briefDescription() << " is referenced by more than one GeneratorFuelCell, returning the first");
  }

  return result;
}

bool GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::addToNode(Node& node) {
  if (node.plantLoop()) {
    return StraightComponent_Impl::addToNode(node);
  }

  return false;
}

std::vector<std::string> GeneratorFuelCellExhaustGasToWaterHeatExchanger_Impl::heatExchangerCalculationMethodValues() const {
  return openstudio::epmodel::GeneratorFuelCellExhaustGasToWaterHeatExchanger::heatExchangerCalculationMethodValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
