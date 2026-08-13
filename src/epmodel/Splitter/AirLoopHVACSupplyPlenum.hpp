/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP
#define EPMODEL_AIRLOOPHVACSUPPLYPLENUM_HPP

#include "EPModelAPI.hpp"
#include "Splitter.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;
  class Node;
  class ThermalZone;

  namespace detail {
    class AirLoopHVACSupplyPlenum_Impl;
  }

  class EPMODEL_API AirLoopHVACSupplyPlenum : public Splitter
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
    // - Status: Partial Parity. The supply plenum now has canonical Splitter behavior, a plenum-zone relationship, and insertion into existing AirLoopHVAC zone branches.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACSupplyPlenum.
    // - Implemented Parity: `thermalZone`, `setThermalZone`, `resetThermalZone`, `addToNode`, inlet/outlet port access, and Splitter branch mutation map directly to the EnergyPlus supply-plenum object.
    // - Documented Delta: Adding a brand-new zone branch through the plenum, branch-index/multi-loop variants, and the AirflowNetwork convenience surface remain deferred.
    // - Field/Storage Mapping: The plenum zone relationship is maintained through EnergyPlus-backed node and branch topology rather than through a separate scalar field.
    // - Evidence: `src/model/AirLoopHVACSupplyPlenum.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACSupplyPlenum.cpp`, and `src/epmodel/test/AirLoopHVACSupplyPlenum_GTest.cpp` cover the same zone-plenum behavior.
    // - Remaining Parity Work: Add new-zone branch creation through an installed plenum and explicit branch-index variants.
    boost::optional<ThermalZone> thermalZone() const;
    bool setThermalZone(const ThermalZone& thermalZone);
    void resetThermalZone();
    bool addToNode(Node& node);

    unsigned inletPort() const override;
    unsigned outletPort(unsigned branchIndex) const override;
    unsigned nextOutletPort() const override;
    std::vector<ModelObject> outletModelObjects() const override;
    unsigned nextBranchIndex() const override;
    void removePortForBranch(unsigned branchIndex) override;
    bool setInletModelObject(const ModelObject& modelObject);
    bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

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
