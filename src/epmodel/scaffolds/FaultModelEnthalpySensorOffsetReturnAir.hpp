/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELENTHALPYSENSOROFFSETRETURNAIR_HPP
#define EPMODEL_FAULTMODELENTHALPYSENSOROFFSETRETURNAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelEnthalpySensorOffsetReturnAir_Impl;
  }

  class EPMODEL_API FaultModelEnthalpySensorOffsetReturnAir : public ModelObject
  {
   public:
    explicit FaultModelEnthalpySensorOffsetReturnAir(const Model& model);

    virtual ~FaultModelEnthalpySensorOffsetReturnAir() override = default;
    FaultModelEnthalpySensorOffsetReturnAir(const FaultModelEnthalpySensorOffsetReturnAir& other) = default;
    FaultModelEnthalpySensorOffsetReturnAir(FaultModelEnthalpySensorOffsetReturnAir&& other) = default;
    FaultModelEnthalpySensorOffsetReturnAir& operator=(const FaultModelEnthalpySensorOffsetReturnAir&) = default;
    FaultModelEnthalpySensorOffsetReturnAir& operator=(FaultModelEnthalpySensorOffsetReturnAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: enthalpySensorOffset maps directly to the EnergyPlus scalar field Enthalpy Sensor Offset.
    // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
    //   and Controller Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    double enthalpySensorOffset() const;
    bool setEnthalpySensorOffset(double enthalpySensorOffset);
    bool isEnthalpySensorOffsetDefaulted() const;
    void resetEnthalpySensorOffset();

   protected:
    using ImplType = detail::FaultModelEnthalpySensorOffsetReturnAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelEnthalpySensorOffsetReturnAir(std::shared_ptr<detail::FaultModelEnthalpySensorOffsetReturnAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
