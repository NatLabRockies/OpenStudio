/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATETHERMOSTAT_HPP
#define EPMODEL_HVACTEMPLATETHERMOSTAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateThermostat_Impl;
}

class EPMODEL_API HVACTemplateThermostat : public ModelObject
{
 public:
  explicit HVACTemplateThermostat(const Model& model);

  virtual ~HVACTemplateThermostat() override = default;
  HVACTemplateThermostat(const HVACTemplateThermostat& other) = default;
  HVACTemplateThermostat(HVACTemplateThermostat&& other) = default;
  HVACTemplateThermostat& operator=(const HVACTemplateThermostat&) = default;
  HVACTemplateThermostat& operator=(HVACTemplateThermostat&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: constantHeatingSetpoint and constantCoolingSetpoint map directly to
  //   EnergyPlus HVACTemplate:Thermostat scalar fields.
  // - Field Mapping: Heating/Cooling Setpoint Schedule Name fields are object-list relationship
  //   fields and are intentionally excluded from scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
  boost::optional<double> constantHeatingSetpoint() const;
  bool setConstantHeatingSetpoint(double constantHeatingSetpoint);
  void resetConstantHeatingSetpoint();

  boost::optional<double> constantCoolingSetpoint() const;
  bool setConstantCoolingSetpoint(double constantCoolingSetpoint);
  void resetConstantCoolingSetpoint();

 protected:
  using ImplType = detail::HVACTemplateThermostat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateThermostat(std::shared_ptr<detail::HVACTemplateThermostat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
