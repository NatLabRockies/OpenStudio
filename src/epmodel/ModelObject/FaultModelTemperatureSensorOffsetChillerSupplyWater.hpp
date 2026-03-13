/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCHILLERSUPPLYWATER_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCHILLERSUPPLYWATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl;
  }

  class EPMODEL_API FaultModelTemperatureSensorOffsetChillerSupplyWater : public ModelObject
  {
   public:
    explicit FaultModelTemperatureSensorOffsetChillerSupplyWater(const Model& model);

    virtual ~FaultModelTemperatureSensorOffsetChillerSupplyWater() override = default;
    FaultModelTemperatureSensorOffsetChillerSupplyWater(const FaultModelTemperatureSensorOffsetChillerSupplyWater& other) = default;
    FaultModelTemperatureSensorOffsetChillerSupplyWater(FaultModelTemperatureSensorOffsetChillerSupplyWater&& other) = default;
    FaultModelTemperatureSensorOffsetChillerSupplyWater& operator=(const FaultModelTemperatureSensorOffsetChillerSupplyWater&) = default;
    FaultModelTemperatureSensorOffsetChillerSupplyWater& operator=(FaultModelTemperatureSensorOffsetChillerSupplyWater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: referenceSensorOffset maps directly to EnergyPlus
    //   FaultModel:TemperatureSensorOffset:ChillerSupplyWater / Reference Sensor Offset.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
    //   and Chiller Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    double referenceSensorOffset() const;
    bool setReferenceSensorOffset(double referenceSensorOffset);
    bool isReferenceSensorOffsetDefaulted() const;
    void resetReferenceSensorOffset();

   protected:
    using ImplType = detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelTemperatureSensorOffsetChillerSupplyWater(
      std::shared_ptr<detail::FaultModelTemperatureSensorOffsetChillerSupplyWater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
