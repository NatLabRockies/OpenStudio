/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "StraightComponent/CoilHeatingGas.hpp"
#include "StraightComponent/CoilHeatingGas_Impl.hpp"

#include "Loop/AirLoopHVAC.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Model.hpp"
#include "Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

namespace openstudio {
namespace epmodel {

CoilHeatingGas::CoilHeatingGas(const Model& model) : StraightComponent(CoilHeatingGas::iddObjectType(), model) {
  auto impl = getImpl<detail::CoilHeatingGas_Impl>();
  OS_ASSERT(impl);

  // Preserve model counterpart defaults for required scalar fields.
  bool ok = true;
  ok = setGasBurnerEfficiency(0.8);
  OS_ASSERT(ok);
  ok = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "AutoSize");
  OS_ASSERT(ok);
  ok = setOnCycleParasiticElectricLoad(0.0);
  OS_ASSERT(ok);
  ok = setOffCycleParasiticGasLoad(0.0);
  OS_ASSERT(ok);

  detail::LoadContext context{const_cast<Model&>(model), SanitizationPolicy::Repair, SanitizationReport{}, {}};  // NOLINT
  impl->canonicalize(context);
}

CoilHeatingGas::CoilHeatingGas(std::shared_ptr<detail::CoilHeatingGas_Impl> impl) : StraightComponent(std::move(impl)) {}

IddObjectType CoilHeatingGas::iddObjectType() {
  return IddObjectType::Coil_Heating_Fuel;
}

bool CoilHeatingGas::addToNode(Node& node) {
  return getImpl<detail::CoilHeatingGas_Impl>()->addToNode(node);
}

std::vector<std::string> CoilHeatingGas::validFuelTypeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Coil_Heating_FuelFields::FuelType);
}

std::string CoilHeatingGas::fuelType() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->fuelType();
}

bool CoilHeatingGas::setFuelType(const std::string& fuelType) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setFuelType(fuelType);
}

void CoilHeatingGas::resetFuelType() {
  getImpl<detail::CoilHeatingGas_Impl>()->resetFuelType();
}

double CoilHeatingGas::gasBurnerEfficiency() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->gasBurnerEfficiency();
}

bool CoilHeatingGas::setGasBurnerEfficiency(double value) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setGasBurnerEfficiency(value);
}

double CoilHeatingGas::parasiticElectricLoad() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->parasiticElectricLoad();
}

double CoilHeatingGas::onCycleParasiticElectricLoad() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->onCycleParasiticElectricLoad();
}

bool CoilHeatingGas::setParasiticElectricLoad(double value) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticElectricLoad(value);
}

bool CoilHeatingGas::setOnCycleParasiticElectricLoad(double value) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setOnCycleParasiticElectricLoad(value);
}

double CoilHeatingGas::parasiticGasLoad() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->parasiticGasLoad();
}

double CoilHeatingGas::offCycleParasiticGasLoad() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->offCycleParasiticGasLoad();
}

bool CoilHeatingGas::setParasiticGasLoad(double value) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setParasiticGasLoad(value);
}

bool CoilHeatingGas::setOffCycleParasiticGasLoad(double value) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setOffCycleParasiticGasLoad(value);
}

boost::optional<double> CoilHeatingGas::nominalCapacity() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->nominalCapacity();
}

bool CoilHeatingGas::isNominalCapacityAutosized() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->isNominalCapacityAutosized();
}

bool CoilHeatingGas::setNominalCapacity(double nominalCapacity) {
  return getImpl<detail::CoilHeatingGas_Impl>()->setNominalCapacity(nominalCapacity);
}

void CoilHeatingGas::resetNominalCapacity() {
  getImpl<detail::CoilHeatingGas_Impl>()->resetNominalCapacity();
}

void CoilHeatingGas::autosizeNominalCapacity() {
  getImpl<detail::CoilHeatingGas_Impl>()->autosizeNominalCapacity();
}

boost::optional<double> CoilHeatingGas::autosizedNominalCapacity() const {
  return getImpl<detail::CoilHeatingGas_Impl>()->autosizedNominalCapacity();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

unsigned CoilHeatingGas_Impl::inletPort() const {
  return openstudio::Coil_Heating_FuelFields::AirInletNodeName;
}

unsigned CoilHeatingGas_Impl::outletPort() const {
  return openstudio::Coil_Heating_FuelFields::AirOutletNodeName;
}

bool CoilHeatingGas_Impl::addToNode(Node& node) {
  if (auto airLoop = node.airLoopHVAC()) {
    if (!airLoop->demandComponent(node.handle())) {
      return StraightComponent_Impl::addToNode(node);
    }
    return false;
  }

  // For current epmodel scope, OA-system insertion is allowed only when the
  // target node participates in modeled OA-system topology.
  if (node.airLoopHVACOutdoorAirSystem()) {
    return StraightComponent_Impl::addToNode(node);
  }

  return false;
}

std::string CoilHeatingGas_Impl::fuelType() const {
  const auto value = getString(openstudio::Coil_Heating_FuelFields::FuelType, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingGas_Impl::setFuelType(const std::string& fuelType) {
  return setString(openstudio::Coil_Heating_FuelFields::FuelType, fuelType);
}

void CoilHeatingGas_Impl::resetFuelType() {
  const bool result = setString(openstudio::Coil_Heating_FuelFields::FuelType, "");
  OS_ASSERT(result);
}

double CoilHeatingGas_Impl::gasBurnerEfficiency() const {
  const auto value = getDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingGas_Impl::setGasBurnerEfficiency(double value) {
  return setDouble(openstudio::Coil_Heating_FuelFields::BurnerEfficiency, value);
}

double CoilHeatingGas_Impl::parasiticElectricLoad() const {
  return onCycleParasiticElectricLoad();
}

double CoilHeatingGas_Impl::onCycleParasiticElectricLoad() const {
  const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingGas_Impl::setParasiticElectricLoad(double value) {
  return setOnCycleParasiticElectricLoad(value);
}

bool CoilHeatingGas_Impl::setOnCycleParasiticElectricLoad(double value) {
  return setDouble(openstudio::Coil_Heating_FuelFields::OnCycleParasiticElectricLoad, value);
}

double CoilHeatingGas_Impl::parasiticGasLoad() const {
  return offCycleParasiticGasLoad();
}

double CoilHeatingGas_Impl::offCycleParasiticGasLoad() const {
  const auto value = getDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, true);
  OS_ASSERT(value);
  return *value;
}

bool CoilHeatingGas_Impl::setParasiticGasLoad(double value) {
  return setOffCycleParasiticGasLoad(value);
}

bool CoilHeatingGas_Impl::setOffCycleParasiticGasLoad(double value) {
  return setDouble(openstudio::Coil_Heating_FuelFields::OffCycleParasiticFuelLoad, value);
}

boost::optional<double> CoilHeatingGas_Impl::nominalCapacity() const {
  return getDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, true);
}

bool CoilHeatingGas_Impl::isNominalCapacityAutosized() const {
  if (const auto value = getString(openstudio::Coil_Heating_FuelFields::NominalCapacity, true)) {
    return openstudio::istringEqual(*value, "autosize");
  }
  return false;
}

bool CoilHeatingGas_Impl::setNominalCapacity(double nominalCapacity) {
  return setDouble(openstudio::Coil_Heating_FuelFields::NominalCapacity, nominalCapacity);
}

void CoilHeatingGas_Impl::resetNominalCapacity() {
  const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "");
  OS_ASSERT(result);
}

void CoilHeatingGas_Impl::autosizeNominalCapacity() {
  const bool result = setString(openstudio::Coil_Heating_FuelFields::NominalCapacity, "Autosize");
  OS_ASSERT(result);
}

boost::optional<double> CoilHeatingGas_Impl::autosizedNominalCapacity() const {
  // epmodel does not currently resolve autosized values from SQL results.
  return boost::none;
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
