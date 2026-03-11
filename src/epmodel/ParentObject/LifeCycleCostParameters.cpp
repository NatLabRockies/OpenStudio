/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ParentObject/LifeCycleCostParameters.hpp"
#include "ParentObject/LifeCycleCostParameters_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/LifeCycleCost_Parameters_FieldEnums.hxx>
#include <utilities/time/Date.hpp>

namespace openstudio {
namespace epmodel {

LifeCycleCostParameters::LifeCycleCostParameters(const Model& model) : ParentObject(LifeCycleCostParameters::iddObjectType(), model) {}

LifeCycleCostParameters::LifeCycleCostParameters(std::shared_ptr<detail::LifeCycleCostParameters_Impl> impl) : ParentObject(std::move(impl)) {}

IddObjectType LifeCycleCostParameters::iddObjectType() {
  return IddObjectType::LifeCycleCost_Parameters;
}

int LifeCycleCostParameters::nistYear() {
  return 2011;
}

double LifeCycleCostParameters::fempRealDiscountRate() {
  return 0.03;
}

double LifeCycleCostParameters::fempNominalDiscountRate() {
  return 0.035;
}

double LifeCycleCostParameters::fempInflation() {
  return 0.005;
}

std::vector<std::string> LifeCycleCostParameters::validDiscountingConventionValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::LifeCycleCost_ParametersFields::DiscountingConvention);
}

std::vector<std::string> LifeCycleCostParameters::validInflationApproachValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::LifeCycleCost_ParametersFields::InflationApproach);
}

std::vector<std::string> LifeCycleCostParameters::validDepreciationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::LifeCycleCost_ParametersFields::DepreciationMethod);
}

std::string LifeCycleCostParameters::discountingConvention() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->discountingConvention();
}

bool LifeCycleCostParameters::isDiscountingConventionDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isDiscountingConventionDefaulted();
}

bool LifeCycleCostParameters::setDiscountingConvention(const std::string& discountingConvention) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setDiscountingConvention(discountingConvention);
}

void LifeCycleCostParameters::resetDiscountingConvention() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetDiscountingConvention();
}

std::string LifeCycleCostParameters::inflationApproach() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->inflationApproach();
}

bool LifeCycleCostParameters::isInflationApproachDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isInflationApproachDefaulted();
}

bool LifeCycleCostParameters::setInflationApproach(const std::string& inflationApproach) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setInflationApproach(inflationApproach);
}

void LifeCycleCostParameters::resetInflationApproach() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetInflationApproach();
}

bool LifeCycleCostParameters::isConstantDollarAnalysis() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isConstantDollarAnalysis();
}

boost::optional<double> LifeCycleCostParameters::realDiscountRate() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->realDiscountRate();
}

bool LifeCycleCostParameters::setRealDiscountRate(double realDiscountRate) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setRealDiscountRate(realDiscountRate);
}

boost::optional<double> LifeCycleCostParameters::nominalDiscountRate() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->nominalDiscountRate();
}

bool LifeCycleCostParameters::setNominalDiscountRate(double nominalDiscountRate) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setNominalDiscountRate(nominalDiscountRate);
}

boost::optional<double> LifeCycleCostParameters::inflation() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->inflation();
}

bool LifeCycleCostParameters::setInflation(double inflation) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setInflation(inflation);
}

MonthOfYear LifeCycleCostParameters::baseDateMonth() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->baseDateMonth();
}

bool LifeCycleCostParameters::isBaseDateMonthDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isBaseDateMonthDefaulted();
}

bool LifeCycleCostParameters::setBaseDateMonth(const MonthOfYear& baseDateMonth) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setBaseDateMonth(baseDateMonth);
}

void LifeCycleCostParameters::resetBaseDateMonth() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetBaseDateMonth();
}

int LifeCycleCostParameters::baseDateYear() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->baseDateYear();
}

bool LifeCycleCostParameters::isBaseDateYearDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isBaseDateYearDefaulted();
}

bool LifeCycleCostParameters::setBaseDateYear(int baseDateYear) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setBaseDateYear(baseDateYear);
}

void LifeCycleCostParameters::resetBaseDateYear() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetBaseDateYear();
}

MonthOfYear LifeCycleCostParameters::serviceDateMonth() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->serviceDateMonth();
}

bool LifeCycleCostParameters::isServiceDateMonthDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isServiceDateMonthDefaulted();
}

bool LifeCycleCostParameters::setServiceDateMonth(const MonthOfYear& serviceDateMonth) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setServiceDateMonth(serviceDateMonth);
}

void LifeCycleCostParameters::resetServiceDateMonth() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetServiceDateMonth();
}

int LifeCycleCostParameters::serviceDateYear() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->serviceDateYear();
}

bool LifeCycleCostParameters::isServiceDateYearDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isServiceDateYearDefaulted();
}

bool LifeCycleCostParameters::setServiceDateYear(int serviceDateYear) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setServiceDateYear(serviceDateYear);
}

void LifeCycleCostParameters::resetServiceDateYear() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetServiceDateYear();
}

int LifeCycleCostParameters::lengthOfStudyPeriodInYears() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->lengthOfStudyPeriodInYears();
}

bool LifeCycleCostParameters::isLengthOfStudyPeriodInYearsDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isLengthOfStudyPeriodInYearsDefaulted();
}

bool LifeCycleCostParameters::setLengthOfStudyPeriodInYears(int lengthOfStudyPeriodInYears) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setLengthOfStudyPeriodInYears(lengthOfStudyPeriodInYears);
}

void LifeCycleCostParameters::resetLengthOfStudyPeriodInYears() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetLengthOfStudyPeriodInYears();
}

boost::optional<double> LifeCycleCostParameters::taxRate() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->taxRate();
}

bool LifeCycleCostParameters::setTaxRate(double taxRate) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setTaxRate(taxRate);
}

void LifeCycleCostParameters::resetTaxRate() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetTaxRate();
}

std::string LifeCycleCostParameters::depreciationMethod() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->depreciationMethod();
}

bool LifeCycleCostParameters::isDepreciationMethodDefaulted() const {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->isDepreciationMethodDefaulted();
}

bool LifeCycleCostParameters::setDepreciationMethod(const std::string& depreciationMethod) {
  return getImpl<detail::LifeCycleCostParameters_Impl>()->setDepreciationMethod(depreciationMethod);
}

void LifeCycleCostParameters::resetDepreciationMethod() {
  getImpl<detail::LifeCycleCostParameters_Impl>()->resetDepreciationMethod();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::vector<std::string> LifeCycleCostParameters_Impl::validDiscountingConventionValues() const {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::LifeCycleCost_Parameters).get(),
                        openstudio::LifeCycleCost_ParametersFields::DiscountingConvention);
}

std::vector<std::string> LifeCycleCostParameters_Impl::validInflationApproachValues() const {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::LifeCycleCost_Parameters).get(),
                        openstudio::LifeCycleCost_ParametersFields::InflationApproach);
}

std::vector<std::string> LifeCycleCostParameters_Impl::validDepreciationMethodValues() const {
  return getIddKeyNames(IddFactory::instance().getObject(IddObjectType::LifeCycleCost_Parameters).get(),
                        openstudio::LifeCycleCost_ParametersFields::DepreciationMethod);
}

std::string LifeCycleCostParameters_Impl::discountingConvention() const {
  const auto value = getString(openstudio::LifeCycleCost_ParametersFields::DiscountingConvention, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostParameters_Impl::isDiscountingConventionDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::DiscountingConvention);
}

bool LifeCycleCostParameters_Impl::setDiscountingConvention(const std::string& discountingConvention) {
  return setString(openstudio::LifeCycleCost_ParametersFields::DiscountingConvention, discountingConvention);
}

void LifeCycleCostParameters_Impl::resetDiscountingConvention() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::DiscountingConvention, ""));
}

std::string LifeCycleCostParameters_Impl::inflationApproach() const {
  const auto value = getString(openstudio::LifeCycleCost_ParametersFields::InflationApproach, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostParameters_Impl::isInflationApproachDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::InflationApproach);
}

bool LifeCycleCostParameters_Impl::setInflationApproach(const std::string& inflationApproach) {
  return setString(openstudio::LifeCycleCost_ParametersFields::InflationApproach, inflationApproach);
}

void LifeCycleCostParameters_Impl::resetInflationApproach() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::InflationApproach, ""));
}

bool LifeCycleCostParameters_Impl::isConstantDollarAnalysis() const {
  return (inflationApproach() == "ConstantDollar");
}

boost::optional<double> LifeCycleCostParameters_Impl::realDiscountRate() const {
  if (!isConstantDollarAnalysis()) {
    return boost::none;
  }
  return getDouble(openstudio::LifeCycleCost_ParametersFields::RealDiscountRate, true);
}

bool LifeCycleCostParameters_Impl::setRealDiscountRate(double realDiscountRate) {
  if (!isConstantDollarAnalysis()) {
    return false;
  }
  return setDouble(openstudio::LifeCycleCost_ParametersFields::RealDiscountRate, realDiscountRate);
}

boost::optional<double> LifeCycleCostParameters_Impl::nominalDiscountRate() const {
  if (isConstantDollarAnalysis()) {
    return boost::none;
  }
  return getDouble(openstudio::LifeCycleCost_ParametersFields::NominalDiscountRate, true);
}

bool LifeCycleCostParameters_Impl::setNominalDiscountRate(double nominalDiscountRate) {
  if (isConstantDollarAnalysis()) {
    return false;
  }
  return setDouble(openstudio::LifeCycleCost_ParametersFields::NominalDiscountRate, nominalDiscountRate);
}

boost::optional<double> LifeCycleCostParameters_Impl::inflation() const {
  if (isConstantDollarAnalysis()) {
    return boost::none;
  }
  return getDouble(openstudio::LifeCycleCost_ParametersFields::Inflation, true);
}

bool LifeCycleCostParameters_Impl::setInflation(double inflation) {
  if (isConstantDollarAnalysis()) {
    return false;
  }
  return setDouble(openstudio::LifeCycleCost_ParametersFields::Inflation, inflation);
}

MonthOfYear LifeCycleCostParameters_Impl::baseDateMonth() const {
  const auto value = getString(openstudio::LifeCycleCost_ParametersFields::BaseDateMonth, true);
  OS_ASSERT(value);
  return MonthOfYear(*value);
}

bool LifeCycleCostParameters_Impl::isBaseDateMonthDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::BaseDateMonth);
}

bool LifeCycleCostParameters_Impl::setBaseDateMonth(const MonthOfYear& baseDateMonth) {
  const bool result = setString(openstudio::LifeCycleCost_ParametersFields::BaseDateMonth, baseDateMonth.valueDescription());
  OS_ASSERT(result);
  return result;
}

void LifeCycleCostParameters_Impl::resetBaseDateMonth() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::BaseDateMonth, ""));
}

int LifeCycleCostParameters_Impl::baseDateYear() const {
  auto value = getInt(openstudio::LifeCycleCost_ParametersFields::BaseDateYear, true);
  if (!value) {
    value = LifeCycleCostParameters::nistYear();
  }
  return *value;
}

bool LifeCycleCostParameters_Impl::isBaseDateYearDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::BaseDateYear);
}

bool LifeCycleCostParameters_Impl::setBaseDateYear(int baseDateYear) {
  return setInt(openstudio::LifeCycleCost_ParametersFields::BaseDateYear, baseDateYear);
}

void LifeCycleCostParameters_Impl::resetBaseDateYear() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::BaseDateYear, ""));
}

MonthOfYear LifeCycleCostParameters_Impl::serviceDateMonth() const {
  const auto value = getString(openstudio::LifeCycleCost_ParametersFields::ServiceDateMonth, true);
  OS_ASSERT(value);
  return MonthOfYear(*value);
}

bool LifeCycleCostParameters_Impl::isServiceDateMonthDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::ServiceDateMonth);
}

bool LifeCycleCostParameters_Impl::setServiceDateMonth(const MonthOfYear& serviceDateMonth) {
  const bool result = setString(openstudio::LifeCycleCost_ParametersFields::ServiceDateMonth, serviceDateMonth.valueDescription());
  OS_ASSERT(result);
  return result;
}

void LifeCycleCostParameters_Impl::resetServiceDateMonth() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::ServiceDateMonth, ""));
}

int LifeCycleCostParameters_Impl::serviceDateYear() const {
  auto value = getInt(openstudio::LifeCycleCost_ParametersFields::ServiceDateYear, true);
  if (!value) {
    value = LifeCycleCostParameters::nistYear();
  }
  return *value;
}

bool LifeCycleCostParameters_Impl::isServiceDateYearDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::ServiceDateYear);
}

bool LifeCycleCostParameters_Impl::setServiceDateYear(int serviceDateYear) {
  return setInt(openstudio::LifeCycleCost_ParametersFields::ServiceDateYear, serviceDateYear);
}

void LifeCycleCostParameters_Impl::resetServiceDateYear() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::ServiceDateYear, ""));
}

int LifeCycleCostParameters_Impl::lengthOfStudyPeriodInYears() const {
  const auto value = getInt(openstudio::LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostParameters_Impl::isLengthOfStudyPeriodInYearsDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears);
}

bool LifeCycleCostParameters_Impl::setLengthOfStudyPeriodInYears(int lengthOfStudyPeriodInYears) {
  return setInt(openstudio::LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears, lengthOfStudyPeriodInYears);
}

void LifeCycleCostParameters_Impl::resetLengthOfStudyPeriodInYears() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::LengthofStudyPeriodinYears, ""));
}

boost::optional<double> LifeCycleCostParameters_Impl::taxRate() const {
  return getDouble(openstudio::LifeCycleCost_ParametersFields::Taxrate, true);
}

bool LifeCycleCostParameters_Impl::setTaxRate(double taxRate) {
  return setDouble(openstudio::LifeCycleCost_ParametersFields::Taxrate, taxRate);
}

void LifeCycleCostParameters_Impl::resetTaxRate() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::Taxrate, ""));
}

std::string LifeCycleCostParameters_Impl::depreciationMethod() const {
  const auto value = getString(openstudio::LifeCycleCost_ParametersFields::DepreciationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool LifeCycleCostParameters_Impl::isDepreciationMethodDefaulted() const {
  return isEmpty(openstudio::LifeCycleCost_ParametersFields::DepreciationMethod);
}

bool LifeCycleCostParameters_Impl::setDepreciationMethod(const std::string& depreciationMethod) {
  return setString(openstudio::LifeCycleCost_ParametersFields::DepreciationMethod, depreciationMethod);
}

void LifeCycleCostParameters_Impl::resetDepreciationMethod() {
  OS_ASSERT(setString(openstudio::LifeCycleCost_ParametersFields::DepreciationMethod, ""));
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
