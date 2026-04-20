/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONECONTROLTHERMOSTATOPERATIVETEMPERATURE_HPP
#define EPMODEL_ZONECONTROLTHERMOSTATOPERATIVETEMPERATURE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ZoneControlThermostatOperativeTemperature_Impl;
}

class EPMODEL_API ZoneControlThermostatOperativeTemperature : public ModelObject
{
 public:
  explicit ZoneControlThermostatOperativeTemperature(const Model& model);

  virtual ~ZoneControlThermostatOperativeTemperature() override = default;
  ZoneControlThermostatOperativeTemperature(const ZoneControlThermostatOperativeTemperature& other) = default;
  ZoneControlThermostatOperativeTemperature(ZoneControlThermostatOperativeTemperature&& other) = default;
  ZoneControlThermostatOperativeTemperature& operator=(const ZoneControlThermostatOperativeTemperature&) = default;
  ZoneControlThermostatOperativeTemperature& operator=(ZoneControlThermostatOperativeTemperature&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> radiativeFractionInputModeValues();
  static std::vector<std::string> adaptiveComfortModelTypeValues();

  // Schema Alignment Notes:
  // - API: Scalar accessors map directly to ZoneControl:Thermostat:OperativeTemperature fields (Radiative Fraction Input Mode, Fixed Radiative Fraction, Adaptive Comfort Model Type).
  // - Field Mapping: Thermostat Name and Radiative Fraction Schedule Name are relationship-like object-list fields and remain excluded.
  // - TODO(parity): Provide relationship/schedule helpers once scalar saturation is complete.
  std::string radiativeFractionInputMode() const;
  bool setRadiativeFractionInputMode(const std::string& radiativeFractionInputMode);

  boost::optional<double> fixedRadiativeFraction() const;
  bool setFixedRadiativeFraction(double fixedRadiativeFraction);

  std::string adaptiveComfortModelType() const;
  bool setAdaptiveComfortModelType(const std::string& adaptiveComfortModelType);
  bool isAdaptiveComfortModelTypeDefaulted() const;
  void resetAdaptiveComfortModelType();

 protected:
  using ImplType = detail::ZoneControlThermostatOperativeTemperature_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ZoneControlThermostatOperativeTemperature(std::shared_ptr<detail::ZoneControlThermostatOperativeTemperature_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
