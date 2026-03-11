/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "FuelFactors.hpp"
#include "FuelFactors_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/FuelFactors_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

FuelFactors::FuelFactors(const Model& model) : ModelObject(FuelFactors::iddObjectType(), model) {
  // Preserve model counterpart constructor defaults for required scalar fields.
  OS_ASSERT(setExistingFuelResourceName("Electricity"));
  OS_ASSERT(setSourceEnergyFactor(2.253));
  OS_ASSERT(setCO2EmissionFactor(168.33317));
  OS_ASSERT(setCOEmissionFactor(4.20616E-02));
  OS_ASSERT(setCH4EmissionFactor(1.39858E-03));
  OS_ASSERT(setNOxEmissionFactor(4.10753E-01));
  OS_ASSERT(setN2OEmissionFactor(2.41916E-03));
  OS_ASSERT(setSO2EmissionFactor(8.65731E-01));
  OS_ASSERT(setPMEmissionFactor(2.95827E-02));
  OS_ASSERT(setPM10EmissionFactor(1.80450E-02));
  OS_ASSERT(setPM25EmissionFactor(1.15377E-02));
  OS_ASSERT(setNH3EmissionFactor(1.10837E-03));
  OS_ASSERT(setNMVOCEmissionFactor(3.72332E-03));
  OS_ASSERT(setHgEmissionFactor(3.36414E-06));
  OS_ASSERT(setPbEmissionFactor(0.0));
  OS_ASSERT(setWaterEmissionFactor(2.10074));
  OS_ASSERT(setNuclearHighLevelEmissionFactor(0.0));
  OS_ASSERT(setNuclearLowLevelEmissionFactor(0.0));
}

FuelFactors::FuelFactors(std::shared_ptr<detail::FuelFactors_Impl> impl) : ModelObject(std::move(impl)) {}

IddObjectType FuelFactors::iddObjectType() {
  return IddObjectType::FuelFactors;
}

std::vector<std::string> FuelFactors::existingFuelResourceNameValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::FuelFactorsFields::ExistingFuelResourceName);
}

std::string FuelFactors::existingFuelResourceName() const {
  return getImpl<detail::FuelFactors_Impl>()->existingFuelResourceName();
}

double FuelFactors::sourceEnergyFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->sourceEnergyFactor();
}

double FuelFactors::cO2EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->cO2EmissionFactor();
}

double FuelFactors::cOEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->cOEmissionFactor();
}

double FuelFactors::cH4EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->cH4EmissionFactor();
}

double FuelFactors::nOxEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->nOxEmissionFactor();
}

double FuelFactors::n2OEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->n2OEmissionFactor();
}

double FuelFactors::sO2EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->sO2EmissionFactor();
}

double FuelFactors::pMEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->pMEmissionFactor();
}

double FuelFactors::pM10EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->pM10EmissionFactor();
}

double FuelFactors::pM25EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->pM25EmissionFactor();
}

double FuelFactors::nH3EmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->nH3EmissionFactor();
}

double FuelFactors::nMVOCEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->nMVOCEmissionFactor();
}

double FuelFactors::hgEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->hgEmissionFactor();
}

double FuelFactors::pbEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->pbEmissionFactor();
}

double FuelFactors::waterEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->waterEmissionFactor();
}

double FuelFactors::nuclearHighLevelEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->nuclearHighLevelEmissionFactor();
}

double FuelFactors::nuclearLowLevelEmissionFactor() const {
  return getImpl<detail::FuelFactors_Impl>()->nuclearLowLevelEmissionFactor();
}

bool FuelFactors::setExistingFuelResourceName(const std::string& existingFuelResourceName) {
  return getImpl<detail::FuelFactors_Impl>()->setExistingFuelResourceName(existingFuelResourceName);
}

bool FuelFactors::setSourceEnergyFactor(double sourceEnergyFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setSourceEnergyFactor(sourceEnergyFactor);
}

bool FuelFactors::setCO2EmissionFactor(double cO2EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setCO2EmissionFactor(cO2EmissionFactor);
}

bool FuelFactors::setCOEmissionFactor(double cOEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setCOEmissionFactor(cOEmissionFactor);
}

bool FuelFactors::setCH4EmissionFactor(double cH4EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setCH4EmissionFactor(cH4EmissionFactor);
}

bool FuelFactors::setNOxEmissionFactor(double nOxEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setNOxEmissionFactor(nOxEmissionFactor);
}

bool FuelFactors::setN2OEmissionFactor(double n2OEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setN2OEmissionFactor(n2OEmissionFactor);
}

bool FuelFactors::setSO2EmissionFactor(double sO2EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setSO2EmissionFactor(sO2EmissionFactor);
}

bool FuelFactors::setPMEmissionFactor(double pMEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setPMEmissionFactor(pMEmissionFactor);
}

bool FuelFactors::setPM10EmissionFactor(double pM10EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setPM10EmissionFactor(pM10EmissionFactor);
}

bool FuelFactors::setPM25EmissionFactor(double pM25EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setPM25EmissionFactor(pM25EmissionFactor);
}

bool FuelFactors::setNH3EmissionFactor(double nH3EmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setNH3EmissionFactor(nH3EmissionFactor);
}

bool FuelFactors::setNMVOCEmissionFactor(double nMVOCEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setNMVOCEmissionFactor(nMVOCEmissionFactor);
}

bool FuelFactors::setHgEmissionFactor(double hgEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setHgEmissionFactor(hgEmissionFactor);
}

bool FuelFactors::setPbEmissionFactor(double pbEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setPbEmissionFactor(pbEmissionFactor);
}

bool FuelFactors::setWaterEmissionFactor(double waterEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setWaterEmissionFactor(waterEmissionFactor);
}

bool FuelFactors::setNuclearHighLevelEmissionFactor(double nuclearHighLevelEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setNuclearHighLevelEmissionFactor(nuclearHighLevelEmissionFactor);
}

bool FuelFactors::setNuclearLowLevelEmissionFactor(double nuclearLowLevelEmissionFactor) {
  return getImpl<detail::FuelFactors_Impl>()->setNuclearLowLevelEmissionFactor(nuclearLowLevelEmissionFactor);
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string FuelFactors_Impl::existingFuelResourceName() const {
  const auto value = getString(openstudio::FuelFactorsFields::ExistingFuelResourceName, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::sourceEnergyFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::SourceEnergyFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::cO2EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::CO2EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::cOEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::COEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::cH4EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::CH4EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::nOxEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::NOxEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::n2OEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::N2OEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::sO2EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::SO2EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::pMEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::PMEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::pM10EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::PM10EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::pM25EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::PM25EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::nH3EmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::NH3EmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::nMVOCEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::NMVOCEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::hgEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::HgEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::pbEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::PbEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::waterEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::WaterEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::nuclearHighLevelEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::NuclearHighLevelEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

double FuelFactors_Impl::nuclearLowLevelEmissionFactor() const {
  const auto value = getDouble(openstudio::FuelFactorsFields::NuclearLowLevelEmissionFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool FuelFactors_Impl::setExistingFuelResourceName(const std::string& existingFuelResourceName) {
  return setString(openstudio::FuelFactorsFields::ExistingFuelResourceName, existingFuelResourceName);
}

bool FuelFactors_Impl::setSourceEnergyFactor(double sourceEnergyFactor) {
  return setDouble(openstudio::FuelFactorsFields::SourceEnergyFactor, sourceEnergyFactor);
}

bool FuelFactors_Impl::setCO2EmissionFactor(double cO2EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::CO2EmissionFactor, cO2EmissionFactor);
}

bool FuelFactors_Impl::setCOEmissionFactor(double cOEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::COEmissionFactor, cOEmissionFactor);
}

bool FuelFactors_Impl::setCH4EmissionFactor(double cH4EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::CH4EmissionFactor, cH4EmissionFactor);
}

bool FuelFactors_Impl::setNOxEmissionFactor(double nOxEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::NOxEmissionFactor, nOxEmissionFactor);
}

bool FuelFactors_Impl::setN2OEmissionFactor(double n2OEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::N2OEmissionFactor, n2OEmissionFactor);
}

bool FuelFactors_Impl::setSO2EmissionFactor(double sO2EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::SO2EmissionFactor, sO2EmissionFactor);
}

bool FuelFactors_Impl::setPMEmissionFactor(double pMEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::PMEmissionFactor, pMEmissionFactor);
}

bool FuelFactors_Impl::setPM10EmissionFactor(double pM10EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::PM10EmissionFactor, pM10EmissionFactor);
}

bool FuelFactors_Impl::setPM25EmissionFactor(double pM25EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::PM25EmissionFactor, pM25EmissionFactor);
}

bool FuelFactors_Impl::setNH3EmissionFactor(double nH3EmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::NH3EmissionFactor, nH3EmissionFactor);
}

bool FuelFactors_Impl::setNMVOCEmissionFactor(double nMVOCEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::NMVOCEmissionFactor, nMVOCEmissionFactor);
}

bool FuelFactors_Impl::setHgEmissionFactor(double hgEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::HgEmissionFactor, hgEmissionFactor);
}

bool FuelFactors_Impl::setPbEmissionFactor(double pbEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::PbEmissionFactor, pbEmissionFactor);
}

bool FuelFactors_Impl::setWaterEmissionFactor(double waterEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::WaterEmissionFactor, waterEmissionFactor);
}

bool FuelFactors_Impl::setNuclearHighLevelEmissionFactor(double nuclearHighLevelEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::NuclearHighLevelEmissionFactor, nuclearHighLevelEmissionFactor);
}

bool FuelFactors_Impl::setNuclearLowLevelEmissionFactor(double nuclearLowLevelEmissionFactor) {
  return setDouble(openstudio::FuelFactorsFields::NuclearLowLevelEmissionFactor, nuclearLowLevelEmissionFactor);
}

std::vector<std::string> FuelFactors_Impl::existingFuelResourceNameValues() const {
  return openstudio::epmodel::FuelFactors::existingFuelResourceNameValues();
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
