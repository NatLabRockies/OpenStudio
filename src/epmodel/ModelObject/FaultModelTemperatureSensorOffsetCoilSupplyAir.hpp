/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCOILSUPPLYAIR_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCOILSUPPLYAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl;
  }

  class EPMODEL_API FaultModelTemperatureSensorOffsetCoilSupplyAir : public ModelObject
  {
   public:
    explicit FaultModelTemperatureSensorOffsetCoilSupplyAir(const Model& model);

    virtual ~FaultModelTemperatureSensorOffsetCoilSupplyAir() override = default;
    FaultModelTemperatureSensorOffsetCoilSupplyAir(const FaultModelTemperatureSensorOffsetCoilSupplyAir& other) = default;
    FaultModelTemperatureSensorOffsetCoilSupplyAir(FaultModelTemperatureSensorOffsetCoilSupplyAir&& other) = default;
    FaultModelTemperatureSensorOffsetCoilSupplyAir& operator=(const FaultModelTemperatureSensorOffsetCoilSupplyAir&) = default;
    FaultModelTemperatureSensorOffsetCoilSupplyAir& operator=(FaultModelTemperatureSensorOffsetCoilSupplyAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: referenceSensorOffset maps directly to EnergyPlus
    //   FaultModel:TemperatureSensorOffset:CoilSupplyAir / Reference Sensor Offset.
    // - Field Mapping: Name is provided by base ModelObject naming API and is intentionally not duplicated here.
    // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
    //   and Coil Object Type/Name and Water Coil Controller Name are target-link fields, so they are intentionally excluded
    //   from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    /** @name Reference Sensor Offset */
    //@{
    double referenceSensorOffset() const;
    bool isReferenceSensorOffsetDefaulted() const;
    bool setReferenceSensorOffset(double referenceSensorOffset);
    void resetReferenceSensorOffset();
    //@}

   protected:
    using ImplType = detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelTemperatureSensorOffsetCoilSupplyAir(std::shared_ptr<detail::FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
