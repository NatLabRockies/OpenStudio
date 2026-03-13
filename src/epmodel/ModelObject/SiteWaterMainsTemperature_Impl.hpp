/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEWATERMAINSTEMPERATURE_IMPL_HPP
#define EPMODEL_SITEWATERMAINSTEMPERATURE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteWaterMainsTemperature_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteWaterMainsTemperature_Impl() override = default;

      std::vector<std::string> calculationMethodValues() const;

      std::string calculationMethod() const;
      bool setCalculationMethod(const std::string& calculationMethod);

      boost::optional<double> annualAverageOutdoorAirTemperature() const;
      bool setAnnualAverageOutdoorAirTemperature(double annualAverageOutdoorAirTemperature);
      void resetAnnualAverageOutdoorAirTemperature();

      boost::optional<double> maximumDifferenceInMonthlyAverageOutdoorAirTemperatures() const;
      bool setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(double maximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
      void resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures();

      double temperatureMultiplier() const;
      bool setTemperatureMultiplier(double temperatureMultiplier);

      double temperatureOffset() const;
      bool setTemperatureOffset(double temperatureOffset);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
