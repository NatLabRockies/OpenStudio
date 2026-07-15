/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP
#define EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AirLoopHVACReturnPlenum_Impl;
  }

  class EPMODEL_API AirLoopHVACReturnPlenum : public ModelObject
  {
   public:
    explicit AirLoopHVACReturnPlenum(const Model& model);

    virtual ~AirLoopHVACReturnPlenum() override = default;
    AirLoopHVACReturnPlenum(const AirLoopHVACReturnPlenum& other) = default;
    AirLoopHVACReturnPlenum(AirLoopHVACReturnPlenum&& other) = default;
    AirLoopHVACReturnPlenum& operator=(const AirLoopHVACReturnPlenum&) = default;
    AirLoopHVACReturnPlenum& operator=(AirLoopHVACReturnPlenum&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The return-plenum topology surface is present, but the canonical wrapper exposes additional zone-attachment convenience and airflow-network behavior.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACReturnPlenum.
    // - Implemented Parity: `thermalZone`, `setThermalZone`, `resetThermalZone`, port access, and branch insertion preserve the main canonical return-plenum contract.
    // - Documented Delta: epmodel keeps this object as topology-focused storage and does not yet expose the full AirflowNetwork convenience surface present in the canonical wrapper.
    // - Field/Storage Mapping: The plenum zone relationship is maintained through EnergyPlus-backed node and branch topology rather than through a separate scalar field.
    // - Evidence: `src/model/AirLoopHVACReturnPlenum.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACReturnPlenum.cpp`, and `src/epmodel/test/AirLoopHVACReturnPlenum_GTest.cpp` cover the same zone-plenum behavior.
    // - Remaining Parity Work: Add any remaining model-side convenience APIs only if the epmodel topology layer needs them explicitly.

   protected:
    using ImplType = detail::AirLoopHVACReturnPlenum_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AirLoopHVACReturnPlenum(std::shared_ptr<detail::AirLoopHVACReturnPlenum_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
