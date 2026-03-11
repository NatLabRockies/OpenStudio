/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETRETURNAIR_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETRETURNAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelTemperatureSensorOffsetReturnAir_Impl;
}

class EPMODEL_API FaultModelTemperatureSensorOffsetReturnAir : public ModelObject
{
 public:
  explicit FaultModelTemperatureSensorOffsetReturnAir(const Model& model);

  virtual ~FaultModelTemperatureSensorOffsetReturnAir() override = default;
  FaultModelTemperatureSensorOffsetReturnAir(const FaultModelTemperatureSensorOffsetReturnAir& other) = default;
  FaultModelTemperatureSensorOffsetReturnAir(FaultModelTemperatureSensorOffsetReturnAir&& other) = default;
  FaultModelTemperatureSensorOffsetReturnAir& operator=(const FaultModelTemperatureSensorOffsetReturnAir&) = default;
  FaultModelTemperatureSensorOffsetReturnAir& operator=(FaultModelTemperatureSensorOffsetReturnAir&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: temperatureSensorOffset maps directly to EnergyPlus FaultModel:TemperatureSensorOffset:ReturnAir /
  //   Temperature Sensor Offset.
  // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
  // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
  //   and Controller Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  double temperatureSensorOffset() const;
  bool isTemperatureSensorOffsetDefaulted() const;
  bool setTemperatureSensorOffset(double temperatureSensorOffset);
  void resetTemperatureSensorOffset();

 protected:
  using ImplType = detail::FaultModelTemperatureSensorOffsetReturnAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelTemperatureSensorOffsetReturnAir(std::shared_ptr<detail::FaultModelTemperatureSensorOffsetReturnAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
