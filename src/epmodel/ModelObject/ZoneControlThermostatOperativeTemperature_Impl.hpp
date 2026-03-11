/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATOPERATIVETEMPERATURE_IMPL_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATOPERATIVETEMPERATURE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ZoneControlThermostatOperativeTemperature_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ZoneControlThermostatOperativeTemperature_Impl() override = default;

  std::string radiativeFractionInputMode() const;
  bool setRadiativeFractionInputMode(const std::string& radiativeFractionInputMode);

  boost::optional<double> fixedRadiativeFraction() const;
  bool setFixedRadiativeFraction(double fixedRadiativeFraction);

  std::string adaptiveComfortModelType() const;
  bool setAdaptiveComfortModelType(const std::string& adaptiveComfortModelType);
  bool isAdaptiveComfortModelTypeDefaulted() const;
  void resetAdaptiveComfortModelType();

  std::vector<std::string> radiativeFractionInputModeValues() const;
  std::vector<std::string> adaptiveComfortModelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
