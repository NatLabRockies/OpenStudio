/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP
#define EPMODEL_AIRLOOPHVACRETURNPLENUM_HPP

#include "EPModelAPI.hpp"
#include "Mixer.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class ThermalZone;

  namespace detail {
    class AirLoopHVACReturnPlenum_Impl;
  }

  class EPMODEL_API AirLoopHVACReturnPlenum : public Mixer
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
    // - Status: Near Parity. The return-plenum mixer, plenum-zone relationships, and zone attachment/removal topology are present; induced-air behavior remains incomplete.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACReturnPlenum.
    // - Implemented Parity: `thermalZone`, `setThermalZone`, `resetThermalZone`, `addToNode`, shared `ThermalZone::setReturnPlenum` and `removeReturnPlenum` topology, outlet/inlet ports, and Mixer branch mutation map directly to the EnergyPlus return-plenum object.
    // - Documented Delta: addBranchForZone, induced-air outlets, and the AirflowNetwork convenience surface remain deferred.
    // - Field/Storage Mapping: The plenum zone, zone node, outlet node, and extensible inlet nodes are explicit EnergyPlus-backed relationships.
    // - Evidence: `src/model/AirLoopHVACReturnPlenum.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACReturnPlenum.cpp`, and `src/epmodel/test/AirLoopHVACReturnPlenum_GTest.cpp`.
    // - Remaining Parity Work: Add induced-air and AirflowNetwork conveniences when their adjacent topology is available.
    boost::optional<ThermalZone> thermalZone() const;
    bool setThermalZone(const ThermalZone& thermalZone);
    void resetThermalZone();

    bool addToNode(Node& node);

    unsigned outletPort() const override;
    unsigned inletPort(unsigned branchIndex) const override;
    unsigned nextInletPort() const override;
    std::vector<ModelObject> inletModelObjects() const override;
    unsigned nextBranchIndex() const override;
    void removePortForBranch(unsigned branchIndex) override;
    bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

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
