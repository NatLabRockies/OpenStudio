/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_UTILITYCOSTQUALIFY_IMPL_HPP
#define EPMODEL_UTILITYCOSTQUALIFY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <string>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API UtilityCostQualify_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~UtilityCostQualify_Impl() override = default;

      std::string variableName() const;
      bool setVariableName(const std::string& variableName);

      std::string qualifyType() const;
      bool setQualifyType(const std::string& qualifyType);

      std::string thresholdValueorVariableName() const;
      bool setThresholdValueorVariableName(const std::string& thresholdValueorVariableName);

      std::string season() const;
      bool setSeason(const std::string& season);
      bool isSeasonDefaulted() const;
      void resetSeason();

      std::string thresholdTest() const;
      bool setThresholdTest(const std::string& thresholdTest);

      int numberOfMonths() const;
      bool isNumberOfMonthsDefaulted() const;
      bool setNumberOfMonths(int numberOfMonths);
      void resetNumberOfMonths();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
