/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETOUTDOORAIR_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class FaultModelTemperatureSensorOffsetOutdoorAir_Impl;
}

class EPMODEL_API FaultModelTemperatureSensorOffsetOutdoorAir : public ModelObject
{
 public:
  explicit FaultModelTemperatureSensorOffsetOutdoorAir(const Model& model);

  virtual ~FaultModelTemperatureSensorOffsetOutdoorAir() override = default;
  FaultModelTemperatureSensorOffsetOutdoorAir(const FaultModelTemperatureSensorOffsetOutdoorAir& other) = default;
  FaultModelTemperatureSensorOffsetOutdoorAir(FaultModelTemperatureSensorOffsetOutdoorAir&& other) = default;
  FaultModelTemperatureSensorOffsetOutdoorAir& operator=(const FaultModelTemperatureSensorOffsetOutdoorAir&) = default;
  FaultModelTemperatureSensorOffsetOutdoorAir& operator=(FaultModelTemperatureSensorOffsetOutdoorAir&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: temperatureSensorOffset maps directly to EnergyPlus FaultModel:TemperatureSensorOffset:OutdoorAir /
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
  using ImplType = detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit FaultModelTemperatureSensorOffsetOutdoorAir(std::shared_ptr<detail::FaultModelTemperatureSensorOffsetOutdoorAir_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
