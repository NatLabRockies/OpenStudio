/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTPARAMETERS_HPP
#define EPMODEL_LIFECYCLECOSTPARAMETERS_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {

class MonthOfYear;

namespace epmodel {

class Model;

namespace detail {
class LifeCycleCostParameters_Impl;
}

class EPMODEL_API LifeCycleCostParameters : public ParentObject
{
 public:
  explicit LifeCycleCostParameters(const Model& model);

  virtual ~LifeCycleCostParameters() override = default;
  LifeCycleCostParameters(const LifeCycleCostParameters& other) = default;
  LifeCycleCostParameters(LifeCycleCostParameters&& other) = default;
  LifeCycleCostParameters& operator=(const LifeCycleCostParameters&) = default;
  LifeCycleCostParameters& operator=(LifeCycleCostParameters&&) = default;

  static IddObjectType iddObjectType();

  static int nistYear();
  static double fempRealDiscountRate();
  static double fempNominalDiscountRate();
  static double fempInflation();

  static std::vector<std::string> validDiscountingConventionValues();
  static std::vector<std::string> validInflationApproachValues();
  static std::vector<std::string> validDepreciationMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::LifeCycleCostParameters scalar accessor names/signatures where mappable to EnergyPlus.
  // - Field Mapping: discountingConvention, inflationApproach, real/nominal discount rates, inflation, base/service date, length, tax,
  //   and depreciationMethod map directly to LifeCycleCost:Parameters scalar fields.
  // - ForwardTranslator evidence: ForwardTranslateLifeCycleCostParameters.cpp writes these same fields directly to
  //   LifeCycleCost:Parameters.
  // - Field Mapping: model-only APIs (analysisType / NIST escalation toggles / fuel-specific escalation rates) are not scalar fields on
  //   EnergyPlus LifeCycleCost:Parameters and are intentionally excluded from this scaffold pass.
  // - TODO(parity): Revisit model-only LCC abstractions if epmodel introduces cross-object helper behavior.
  std::string discountingConvention() const;
  bool isDiscountingConventionDefaulted() const;
  bool setDiscountingConvention(const std::string& discountingConvention);
  void resetDiscountingConvention();

  std::string inflationApproach() const;
  bool isInflationApproachDefaulted() const;
  bool setInflationApproach(const std::string& inflationApproach);
  void resetInflationApproach();

  bool isConstantDollarAnalysis() const;

  boost::optional<double> realDiscountRate() const;
  bool setRealDiscountRate(double realDiscountRate);

  boost::optional<double> nominalDiscountRate() const;
  bool setNominalDiscountRate(double nominalDiscountRate);

  boost::optional<double> inflation() const;
  bool setInflation(double inflation);

  MonthOfYear baseDateMonth() const;
  bool isBaseDateMonthDefaulted() const;
  bool setBaseDateMonth(const MonthOfYear& baseDateMonth);
  void resetBaseDateMonth();

  int baseDateYear() const;
  bool isBaseDateYearDefaulted() const;
  bool setBaseDateYear(int baseDateYear);
  void resetBaseDateYear();

  MonthOfYear serviceDateMonth() const;
  bool isServiceDateMonthDefaulted() const;
  bool setServiceDateMonth(const MonthOfYear& serviceDateMonth);
  void resetServiceDateMonth();

  int serviceDateYear() const;
  bool isServiceDateYearDefaulted() const;
  bool setServiceDateYear(int serviceDateYear);
  void resetServiceDateYear();

  int lengthOfStudyPeriodInYears() const;
  bool isLengthOfStudyPeriodInYearsDefaulted() const;
  bool setLengthOfStudyPeriodInYears(int lengthOfStudyPeriodInYears);
  void resetLengthOfStudyPeriodInYears();

  boost::optional<double> taxRate() const;
  bool setTaxRate(double taxRate);
  void resetTaxRate();

  std::string depreciationMethod() const;
  bool isDepreciationMethodDefaulted() const;
  bool setDepreciationMethod(const std::string& depreciationMethod);
  void resetDepreciationMethod();

 protected:
  using ImplType = detail::LifeCycleCostParameters_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit LifeCycleCostParameters(std::shared_ptr<detail::LifeCycleCostParameters_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
