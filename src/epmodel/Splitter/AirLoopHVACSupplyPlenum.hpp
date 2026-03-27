/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class AirLoopHVACSupplyPlenum_Impl;
}

class EPMODEL_API AirLoopHVACSupplyPlenum : public ModelObject
{
 public:
  explicit AirLoopHVACSupplyPlenum(const Model& model);

  virtual ~AirLoopHVACSupplyPlenum() override = default;
  AirLoopHVACSupplyPlenum(const AirLoopHVACSupplyPlenum& other) = default;
  AirLoopHVACSupplyPlenum(AirLoopHVACSupplyPlenum&& other) = default;
  AirLoopHVACSupplyPlenum& operator=(const AirLoopHVACSupplyPlenum&) = default;
  AirLoopHVACSupplyPlenum& operator=(AirLoopHVACSupplyPlenum&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The supply-plenum topology surface is present, but the canonical wrapper exposes additional zone-attachment convenience and airflow-network behavior.
  // - Canonical Counterpart: openstudio::model::AirLoopHVACSupplyPlenum.
  // - Implemented Parity: `thermalZone`, `setThermalZone`, `resetThermalZone`, port access, and branch insertion preserve the main canonical supply-plenum contract.
  // - Documented Delta: epmodel keeps this object as topology-focused storage and does not yet expose the full AirflowNetwork convenience surface present in the canonical wrapper.
  // - Field/Storage Mapping: The plenum zone relationship is maintained through EnergyPlus-backed node and branch topology rather than through a separate scalar field.
  // - Evidence: `src/model/AirLoopHVACSupplyPlenum.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACSupplyPlenum.cpp`, and `src/epmodel/test/AirLoopHVACSupplyPlenum_GTest.cpp` cover the same zone-plenum behavior.
  // - Remaining Parity Work: Add any remaining model-side convenience APIs only if the epmodel topology layer needs them explicitly.

 protected:
  using ImplType = detail::AirLoopHVACSupplyPlenum_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit AirLoopHVACSupplyPlenum(std::shared_ptr<detail::AirLoopHVACSupplyPlenum_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
