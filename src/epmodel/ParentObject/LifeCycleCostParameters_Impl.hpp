/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOSTPARAMETERS_IMPL_HPP
#define EPMODEL_LIFECYCLECOSTPARAMETERS_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <vector>

namespace openstudio {

class MonthOfYear;

namespace epmodel {
  namespace detail {

    class EPMODEL_API LifeCycleCostParameters_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~LifeCycleCostParameters_Impl() override = default;

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

      std::vector<std::string> validDiscountingConventionValues() const;
      std::vector<std::string> validInflationApproachValues() const;
      std::vector<std::string> validDepreciationMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
