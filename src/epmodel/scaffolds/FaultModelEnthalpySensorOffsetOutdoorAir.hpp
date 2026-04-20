/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELENTHALPYSENSOROFFSETOUTDOORAIR_HPP
#define EPMODEL_FAULTMODELENTHALPYSENSOROFFSETOUTDOORAIR_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class FaultModelEnthalpySensorOffsetOutdoorAir_Impl;
  }

  class EPMODEL_API FaultModelEnthalpySensorOffsetOutdoorAir : public ModelObject
  {
   public:
    explicit FaultModelEnthalpySensorOffsetOutdoorAir(const Model& model);

    virtual ~FaultModelEnthalpySensorOffsetOutdoorAir() override = default;
    FaultModelEnthalpySensorOffsetOutdoorAir(const FaultModelEnthalpySensorOffsetOutdoorAir& other) = default;
    FaultModelEnthalpySensorOffsetOutdoorAir(FaultModelEnthalpySensorOffsetOutdoorAir&& other) = default;
    FaultModelEnthalpySensorOffsetOutdoorAir& operator=(const FaultModelEnthalpySensorOffsetOutdoorAir&) = default;
    FaultModelEnthalpySensorOffsetOutdoorAir& operator=(FaultModelEnthalpySensorOffsetOutdoorAir&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: enthalpySensorOffset maps directly to the EnergyPlus scalar field Enthalpy Sensor Offset.
    // - Field Mapping: Availability Schedule Name and Severity Schedule Name are object-list relationship fields,
    //   and Controller Object Type/Name are target-link fields, so they are intentionally excluded from scalar accessors.
    // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
    double enthalpySensorOffset() const;
    bool isEnthalpySensorOffsetDefaulted() const;
    bool setEnthalpySensorOffset(double enthalpySensorOffset);
    void resetEnthalpySensorOffset();

   protected:
    using ImplType = detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit FaultModelEnthalpySensorOffsetOutdoorAir(std::shared_ptr<detail::FaultModelEnthalpySensorOffsetOutdoorAir_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
