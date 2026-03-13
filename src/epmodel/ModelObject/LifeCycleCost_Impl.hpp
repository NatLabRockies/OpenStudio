/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_LIFECYCLECOST_IMPL_HPP
#define EPMODEL_LIFECYCLECOST_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API LifeCycleCost_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~LifeCycleCost_Impl() override = default;

      std::string category() const;
      bool setCategory(const std::string& category);

      double cost() const;
      bool setCost(double cost);

      std::string startOfCosts() const;
      bool isStartOfCostsDefaulted() const;
      bool setStartOfCosts(const std::string& startOfCosts);
      void resetStartOfCosts();

      int yearsFromStart() const;
      bool isYearsFromStartDefaulted() const;
      bool setYearsFromStart(int yearsFromStart);
      void resetYearsFromStart();

      int monthsFromStart() const;
      bool isMonthsFromStartDefaulted() const;
      bool setMonthsFromStart(int monthsFromStart);
      void resetMonthsFromStart();

      int repeatPeriodYears() const;
      bool isRepeatPeriodYearsDefaulted() const;
      bool setRepeatPeriodYears(int repeatPeriodYears);
      void resetRepeatPeriodYears();

      int repeatPeriodMonths() const;
      bool isRepeatPeriodMonthsDefaulted() const;
      bool setRepeatPeriodMonths(int repeatPeriodMonths);
      void resetRepeatPeriodMonths();

      std::vector<std::string> validCategoryValues() const;
      std::vector<std::string> validStartOfCostsValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
