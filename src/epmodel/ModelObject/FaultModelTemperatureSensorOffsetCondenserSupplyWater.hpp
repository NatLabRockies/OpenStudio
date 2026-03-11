/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCONDENSERSUPPLYWATER_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCONDENSERSUPPLYWATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl;
}

class EPMODEL_API FaultModelTemperatureSensorOffsetCondenserSupplyWater : public ModelObject
{
 public:
  explicit FaultModelTemperatureSensorOffsetCondenserSupplyWater(const Model& model);

  virtual ~FaultModelTemperatureSensorOffsetCondenserSupplyWater() override = default;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater(const FaultModelTemperatureSensorOffsetCondenserSupplyWater& other) = default;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater(FaultModelTemperatureSensorOffsetCondenserSupplyWater&& other) = default;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater& operator=(const FaultModelTemperatureSensorOffsetCondenserSupplyWater&) = default;
  FaultModelTemperatureSensorOffsetCondenserSupplyWater& operator=(FaultModelTemperatureSensorOffsetCondenserSupplyWater&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: referenceSensorOffset maps directly to EnergyPlus
  //   FaultModel:TemperatureSensorOffset:CondenserSupplyWater / Reference Sensor Offset.
  // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
  // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
  //   and Cooling Tower Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double referenceSensorOffset() const;
  bool isReferenceSensorOffsetDefaulted() const;
  bool setReferenceSensorOffset(double referenceSensorOffset);
  void resetReferenceSensorOffset();

 protected:
  using ImplType = detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelTemperatureSensorOffsetCondenserSupplyWater(
    std::shared_ptr<detail::FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
