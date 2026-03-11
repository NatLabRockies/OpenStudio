/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTHERMOSTATOFFSET_HPP
#define EPMODEL_FAULTMODELTHERMOSTATOFFSET_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelThermostatOffset_Impl;
}

class EPMODEL_API FaultModelThermostatOffset : public ModelObject
{
 public:
  explicit FaultModelThermostatOffset(const Model& model);

  virtual ~FaultModelThermostatOffset() override = default;
  FaultModelThermostatOffset(const FaultModelThermostatOffset& other) = default;
  FaultModelThermostatOffset(FaultModelThermostatOffset&& other) = default;
  FaultModelThermostatOffset& operator=(const FaultModelThermostatOffset&) = default;
  FaultModelThermostatOffset& operator=(FaultModelThermostatOffset&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: referenceThermostatOffset maps directly to EnergyPlus FaultModel:ThermostatOffset /
  //   Reference Thermostat Offset.
  // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
  // - Field Mapping: Thermostat Name, Availability Schedule Name, and Severity Schedule Name are object-list
  //   relationship fields and intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double referenceThermostatOffset() const;
  bool isReferenceThermostatOffsetDefaulted() const;
  bool setReferenceThermostatOffset(double referenceThermostatOffset);
  void resetReferenceThermostatOffset();

 protected:
  using ImplType = detail::FaultModelThermostatOffset_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelThermostatOffset(std::shared_ptr<detail::FaultModelThermostatOffset_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
