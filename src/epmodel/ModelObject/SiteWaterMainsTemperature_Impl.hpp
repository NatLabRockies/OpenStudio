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

  std::string calculationMethod() const;
  boost::optional<double> annualAverageOutdoorAirTemperature() const;
  boost::optional<double> maximumDifferenceInMonthlyAverageOutdoorAirTemperatures() const;
  double temperatureMultiplier() const;
  double temperatureOffset() const;

  bool setCalculationMethod(const std::string& calculationMethod);
  bool setAnnualAverageOutdoorAirTemperature(double annualAverageOutdoorAirTemperature);
  void resetAnnualAverageOutdoorAirTemperature();
  bool setMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures(double maximumDifferenceInMonthlyAverageOutdoorAirTemperatures);
  void resetMaximumDifferenceInMonthlyAverageOutdoorAirTemperatures();
  bool setTemperatureMultiplier(double temperatureMultiplier);
  bool setTemperatureOffset(double temperatureOffset);

  std::vector<std::string> calculationMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
