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

/** \brief Defines the global economic assumptions for life-cycle cost analysis.
 *
 * \par EnergyPlus object
 * \epobject{lifecyclecost-parameters.html#lifecyclecostparameters,LifeCycleCost:Parameters}
 *
 * \par Important behavior
 * Discounting, inflation, analysis-period, tax, electricity-cost, and constant-dollar fields are stored directly on the object.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::LifeCycleCostParameters</code>.
 * <b>Not yet available:</b> Model's analysis-type, NIST, and fuel-specific inflation helpers are not exposed.
 *
 * \par Known limitations
 * This wrapper stores assumptions only; life-cycle cost calculations and component costs are handled by EnergyPlus and related objects.
 */
  class EPMODEL_API LifeCycleCostParameters : public ParentObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

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
    explicit LifeCycleCostParameters(const Model& model);

    using ImplType = detail::LifeCycleCostParameters_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit LifeCycleCostParameters(std::shared_ptr<detail::LifeCycleCostParameters_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
