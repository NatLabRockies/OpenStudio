/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ElectricalStorage/ElectricLoadCenterStorageLiIonNMCBattery.hpp"
#include "ElectricalStorage/ElectricLoadCenterStorageLiIonNMCBattery_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/ElectricLoadCenter_Storage_LiIonNMCBattery_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

ElectricLoadCenterStorageLiIonNMCBattery::ElectricLoadCenterStorageLiIonNMCBattery(const Model& model)
  : ModelObject(ElectricLoadCenterStorageLiIonNMCBattery::iddObjectType(), model) {
  const bool ok1 = setNumberofCellsinSeries(139);
  OS_ASSERT(ok1);
  const bool ok2 = setNumberofStringsinParallel(25);
  OS_ASSERT(ok2);
  const bool ok3 = setBatteryMass(342.0);
  OS_ASSERT(ok3);
  const bool ok4 = setBatterySurfaceArea(4.26);
  OS_ASSERT(ok4);

  OS_ASSERT(setRadiativeFraction(0.0));
  OS_ASSERT(setLifetimeModel("KandlerSmith"));
  OS_ASSERT(setInitialFractionalStateofCharge(0.5));
  OS_ASSERT(setDCtoDCChargingEfficiency(0.95));
  OS_ASSERT(setBatterySpecificHeatCapacity(1500.0));
  OS_ASSERT(setHeatTransferCoefficientBetweenBatteryandAmbient(7.5));
  OS_ASSERT(setFullyChargedCellVoltage(4.2));
  OS_ASSERT(setCellVoltageatEndofExponentialZone(3.53));
  OS_ASSERT(setCellVoltageatEndofNominalZone(3.342));
  OS_ASSERT(setDefaultNominalCellVoltage(3.342));
  OS_ASSERT(setFullyChargedCellCapacity(3.2));
  OS_ASSERT(setFractionofCellCapacityRemovedattheEndofExponentialZone(0.8075));
  OS_ASSERT(setFractionofCellCapacityRemovedattheEndofNominalZone(0.976875));
  OS_ASSERT(setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(1.0));
  OS_ASSERT(setBatteryCellInternalElectricalResistance(0.09));
}

ElectricLoadCenterStorageLiIonNMCBattery::ElectricLoadCenterStorageLiIonNMCBattery(
  const Model& model, int numberofCellsinSeries, int numberofStringsinParallel, double batteryMass, double batterySurfaceArea)
  : ModelObject(ElectricLoadCenterStorageLiIonNMCBattery::iddObjectType(), model) {
  OS_ASSERT(setRadiativeFraction(0.0));
  OS_ASSERT(setLifetimeModel("KandlerSmith"));
  OS_ASSERT(setNumberofCellsinSeries(numberofCellsinSeries));
  OS_ASSERT(setNumberofStringsinParallel(numberofStringsinParallel));
  OS_ASSERT(setInitialFractionalStateofCharge(0.5));
  OS_ASSERT(setDCtoDCChargingEfficiency(0.95));
  OS_ASSERT(setBatteryMass(batteryMass));
  OS_ASSERT(setBatterySurfaceArea(batterySurfaceArea));
  OS_ASSERT(setBatterySpecificHeatCapacity(1500.0));
  OS_ASSERT(setHeatTransferCoefficientBetweenBatteryandAmbient(7.5));
  OS_ASSERT(setFullyChargedCellVoltage(4.2));
  OS_ASSERT(setCellVoltageatEndofExponentialZone(3.53));
  OS_ASSERT(setCellVoltageatEndofNominalZone(3.342));
  OS_ASSERT(setDefaultNominalCellVoltage(3.342));
  OS_ASSERT(setFullyChargedCellCapacity(3.2));
  OS_ASSERT(setFractionofCellCapacityRemovedattheEndofExponentialZone(0.8075));
  OS_ASSERT(setFractionofCellCapacityRemovedattheEndofNominalZone(0.976875));
  OS_ASSERT(setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(1.0));
  OS_ASSERT(setBatteryCellInternalElectricalResistance(0.09));
}

ElectricLoadCenterStorageLiIonNMCBattery::ElectricLoadCenterStorageLiIonNMCBattery(
  std::shared_ptr<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl> impl)
  : ModelObject(std::move(impl)) {}

IddObjectType ElectricLoadCenterStorageLiIonNMCBattery::iddObjectType() {
  return IddObjectType::ElectricLoadCenter_Storage_LiIonNMCBattery;
}

std::vector<std::string> ElectricLoadCenterStorageLiIonNMCBattery::lifetimeModelValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::LifetimeModel);
}

double ElectricLoadCenterStorageLiIonNMCBattery::radiativeFraction() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->radiativeFraction();
}

std::string ElectricLoadCenterStorageLiIonNMCBattery::lifetimeModel() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->lifetimeModel();
}

int ElectricLoadCenterStorageLiIonNMCBattery::numberofCellsinSeries() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->numberofCellsinSeries();
}

int ElectricLoadCenterStorageLiIonNMCBattery::numberofStringsinParallel() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->numberofStringsinParallel();
}

double ElectricLoadCenterStorageLiIonNMCBattery::initialFractionalStateofCharge() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->initialFractionalStateofCharge();
}

double ElectricLoadCenterStorageLiIonNMCBattery::dctoDCChargingEfficiency() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->dctoDCChargingEfficiency();
}

double ElectricLoadCenterStorageLiIonNMCBattery::batteryMass() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->batteryMass();
}

double ElectricLoadCenterStorageLiIonNMCBattery::batterySurfaceArea() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->batterySurfaceArea();
}

double ElectricLoadCenterStorageLiIonNMCBattery::batterySpecificHeatCapacity() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->batterySpecificHeatCapacity();
}

double ElectricLoadCenterStorageLiIonNMCBattery::heatTransferCoefficientBetweenBatteryandAmbient() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->heatTransferCoefficientBetweenBatteryandAmbient();
}

double ElectricLoadCenterStorageLiIonNMCBattery::fullyChargedCellVoltage() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->fullyChargedCellVoltage();
}

double ElectricLoadCenterStorageLiIonNMCBattery::cellVoltageatEndofExponentialZone() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->cellVoltageatEndofExponentialZone();
}

double ElectricLoadCenterStorageLiIonNMCBattery::cellVoltageatEndofNominalZone() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->cellVoltageatEndofNominalZone();
}

double ElectricLoadCenterStorageLiIonNMCBattery::defaultNominalCellVoltage() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->defaultNominalCellVoltage();
}

double ElectricLoadCenterStorageLiIonNMCBattery::fullyChargedCellCapacity() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->fullyChargedCellCapacity();
}

double ElectricLoadCenterStorageLiIonNMCBattery::fractionofCellCapacityRemovedattheEndofExponentialZone() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->fractionofCellCapacityRemovedattheEndofExponentialZone();
}

double ElectricLoadCenterStorageLiIonNMCBattery::fractionofCellCapacityRemovedattheEndofNominalZone() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->fractionofCellCapacityRemovedattheEndofNominalZone();
}

double ElectricLoadCenterStorageLiIonNMCBattery::chargeRateatWhichVoltagevsCapacityCurveWasGenerated() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->chargeRateatWhichVoltagevsCapacityCurveWasGenerated();
}

double ElectricLoadCenterStorageLiIonNMCBattery::batteryCellInternalElectricalResistance() const {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->batteryCellInternalElectricalResistance();
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setRadiativeFraction(double radiativeFraction) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setRadiativeFraction(radiativeFraction);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setLifetimeModel(const std::string& lifetimeModel) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setLifetimeModel(lifetimeModel);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setNumberofCellsinSeries(int numberofCellsinSeries) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setNumberofCellsinSeries(numberofCellsinSeries);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setNumberofStringsinParallel(int numberofStringsinParallel) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setNumberofStringsinParallel(numberofStringsinParallel);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setInitialFractionalStateofCharge(double initialFractionalStateofCharge) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setInitialFractionalStateofCharge(initialFractionalStateofCharge);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setDCtoDCChargingEfficiency(double dctoDCChargingEfficiency) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setDCtoDCChargingEfficiency(dctoDCChargingEfficiency);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setBatteryMass(double batteryMass) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setBatteryMass(batteryMass);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setBatterySurfaceArea(double batterySurfaceArea) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setBatterySurfaceArea(batterySurfaceArea);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setBatterySpecificHeatCapacity(double batterySpecificHeatCapacity) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setBatterySpecificHeatCapacity(batterySpecificHeatCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setHeatTransferCoefficientBetweenBatteryandAmbient(
  double heatTransferCoefficientBetweenBatteryandAmbient) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setHeatTransferCoefficientBetweenBatteryandAmbient(
    heatTransferCoefficientBetweenBatteryandAmbient);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setFullyChargedCellVoltage(double fullyChargedCellCapacity) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setFullyChargedCellVoltage(fullyChargedCellCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setCellVoltageatEndofExponentialZone(double cellVoltageatEndofExponentialZone) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setCellVoltageatEndofExponentialZone(cellVoltageatEndofExponentialZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setCellVoltageatEndofNominalZone(double cellVoltageatEndofNominalZone) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setCellVoltageatEndofNominalZone(cellVoltageatEndofNominalZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setDefaultNominalCellVoltage(double defaultNominalCellVoltage) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setDefaultNominalCellVoltage(defaultNominalCellVoltage);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setFullyChargedCellCapacity(double fullyChargedCellCapacity) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setFullyChargedCellCapacity(fullyChargedCellCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setFractionofCellCapacityRemovedattheEndofExponentialZone(
  double fractionofCellCapacityRemovedattheEndofExponentialZone) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setFractionofCellCapacityRemovedattheEndofExponentialZone(
    fractionofCellCapacityRemovedattheEndofExponentialZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setFractionofCellCapacityRemovedattheEndofNominalZone(
  double fractionofCellCapacityRemovedattheEndofNominalZone) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setFractionofCellCapacityRemovedattheEndofNominalZone(
    fractionofCellCapacityRemovedattheEndofNominalZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(
  double chargeRateatWhichVoltagevsCapacityCurveWasGenerated) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(
    chargeRateatWhichVoltagevsCapacityCurveWasGenerated);
}

bool ElectricLoadCenterStorageLiIonNMCBattery::setBatteryCellInternalElectricalResistance(double batteryCellInternalElectricalResistance) {
  return getImpl<detail::ElectricLoadCenterStorageLiIonNMCBattery_Impl>()->setBatteryCellInternalElectricalResistance(
    batteryCellInternalElectricalResistance);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::radiativeFraction() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::RadiativeFraction, true);
  OS_ASSERT(value);
  return *value;
}

std::string ElectricLoadCenterStorageLiIonNMCBattery_Impl::lifetimeModel() const {
  const auto value = getString(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::LifetimeModel, true);
  OS_ASSERT(value);
  return *value;
}

int ElectricLoadCenterStorageLiIonNMCBattery_Impl::numberofCellsinSeries() const {
  const auto value = getInt(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofCellsinSeries, true);
  OS_ASSERT(value);
  return *value;
}

int ElectricLoadCenterStorageLiIonNMCBattery_Impl::numberofStringsinParallel() const {
  const auto value = getInt(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofStringsinParallel, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::initialFractionalStateofCharge() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::InitialFractionalStateofCharge, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::dctoDCChargingEfficiency() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DCtoDCChargingEfficiency, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::batteryMass() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryMass, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::batterySurfaceArea() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySurfaceArea, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::batterySpecificHeatCapacity() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySpecificHeatCapacity, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::heatTransferCoefficientBetweenBatteryandAmbient() const {
  const auto value =
    getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::HeatTransferCoefficientBetweenBatteryandAmbient, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::fullyChargedCellVoltage() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellVoltage, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::cellVoltageatEndofExponentialZone() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofExponentialZone, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::cellVoltageatEndofNominalZone() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofNominalZone, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::defaultNominalCellVoltage() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DefaultNominalCellVoltage, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::fullyChargedCellCapacity() const {
  const auto value = getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellCapacity, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::fractionofCellCapacityRemovedattheEndofExponentialZone() const {
  const auto value =
    getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofExponentialZone, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::fractionofCellCapacityRemovedattheEndofNominalZone() const {
  const auto value =
    getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofNominalZone, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::chargeRateatWhichVoltagevsCapacityCurveWasGenerated() const {
  const auto value =
    getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ChargeRateatWhichVoltagevsCapacityCurveWasGenerated, true);
  OS_ASSERT(value);
  return *value;
}

double ElectricLoadCenterStorageLiIonNMCBattery_Impl::batteryCellInternalElectricalResistance() const {
  const auto value =
    getDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryCellInternalElectricalResistance, true);
  OS_ASSERT(value);
  return *value;
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setRadiativeFraction(double radiativeFraction) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::RadiativeFraction, radiativeFraction);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setLifetimeModel(const std::string& lifetimeModel) {
  return setString(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::LifetimeModel, lifetimeModel);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setNumberofCellsinSeries(int numberofCellsinSeries) {
  const bool result = setInt(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofCellsinSeries, numberofCellsinSeries);
  OS_ASSERT(result);
  return result;
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setNumberofStringsinParallel(int numberofStringsinParallel) {
  const bool result = setInt(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::NumberofStringsinParallel, numberofStringsinParallel);
  OS_ASSERT(result);
  return result;
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setInitialFractionalStateofCharge(double initialFractionalStateofCharge) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::InitialFractionalStateofCharge,
                   initialFractionalStateofCharge);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setDCtoDCChargingEfficiency(double dctoDCChargingEfficiency) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DCtoDCChargingEfficiency, dctoDCChargingEfficiency);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setBatteryMass(double batteryMass) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryMass, batteryMass);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setBatterySurfaceArea(double batterySurfaceArea) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySurfaceArea, batterySurfaceArea);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setBatterySpecificHeatCapacity(double batterySpecificHeatCapacity) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatterySpecificHeatCapacity, batterySpecificHeatCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setHeatTransferCoefficientBetweenBatteryandAmbient(
  double heatTransferCoefficientBetweenBatteryandAmbient) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::HeatTransferCoefficientBetweenBatteryandAmbient,
                   heatTransferCoefficientBetweenBatteryandAmbient);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setFullyChargedCellVoltage(double fullyChargedCellCapacity) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellVoltage, fullyChargedCellCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setCellVoltageatEndofExponentialZone(double cellVoltageatEndofExponentialZone) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofExponentialZone,
                   cellVoltageatEndofExponentialZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setCellVoltageatEndofNominalZone(double cellVoltageatEndofNominalZone) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::CellVoltageatEndofNominalZone,
                   cellVoltageatEndofNominalZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setDefaultNominalCellVoltage(double defaultNominalCellVoltage) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::DefaultNominalCellVoltage, defaultNominalCellVoltage);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setFullyChargedCellCapacity(double fullyChargedCellCapacity) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FullyChargedCellCapacity, fullyChargedCellCapacity);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setFractionofCellCapacityRemovedattheEndofExponentialZone(
  double fractionofCellCapacityRemovedattheEndofExponentialZone) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofExponentialZone,
                   fractionofCellCapacityRemovedattheEndofExponentialZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setFractionofCellCapacityRemovedattheEndofNominalZone(
  double fractionofCellCapacityRemovedattheEndofNominalZone) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::FractionofCellCapacityRemovedattheEndofNominalZone,
                   fractionofCellCapacityRemovedattheEndofNominalZone);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setChargeRateatWhichVoltagevsCapacityCurveWasGenerated(
  double chargeRateatWhichVoltagevsCapacityCurveWasGenerated) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::ChargeRateatWhichVoltagevsCapacityCurveWasGenerated,
                   chargeRateatWhichVoltagevsCapacityCurveWasGenerated);
}

bool ElectricLoadCenterStorageLiIonNMCBattery_Impl::setBatteryCellInternalElectricalResistance(double batteryCellInternalElectricalResistance) {
  return setDouble(openstudio::ElectricLoadCenter_Storage_LiIonNMCBatteryFields::BatteryCellInternalElectricalResistance,
                   batteryCellInternalElectricalResistance);
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
