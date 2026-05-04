/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONESPLITTER_HPP
#define EPMODEL_AIRLOOPHVACZONESPLITTER_HPP

#include "EPModelAPI.hpp"
#include "Splitter/Splitter.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class AirLoopHVAC;
  class Model;

  namespace detail {
    class AirLoopHVACZoneSplitter_Impl;
  }

  class EPMODEL_API AirLoopHVACZoneSplitter : public Splitter
  {
   public:
    explicit AirLoopHVACZoneSplitter(const Model& model);

    virtual ~AirLoopHVACZoneSplitter() override = default;
    AirLoopHVACZoneSplitter(const AirLoopHVACZoneSplitter& other) = default;
    AirLoopHVACZoneSplitter(AirLoopHVACZoneSplitter&& other) = default;
    AirLoopHVACZoneSplitter& operator=(const AirLoopHVACZoneSplitter&) = default;
    AirLoopHVACZoneSplitter& operator=(AirLoopHVACZoneSplitter&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The zone-splitter topology surface is present, but the canonical wrapper exposes additional airflow-network convenience APIs.
    // - Canonical Counterpart: openstudio::model::AirLoopHVACZoneSplitter.
    // - Implemented Parity: Inlet/outlet port access, branch indexing, outlet-object enumeration, branch removal, and outlet-object assignment preserve the canonical zone-splitter topology contract.
    // - Documented Delta: epmodel still omits the AirflowNetwork distribution-node convenience API present in the canonical wrapper.
    // - Field/Storage Mapping: `AirLoopHVAC:ZoneSplitter` inlet-node and extensible outlet-node fields are represented as relationship fields.
    // - Evidence: `src/model/AirLoopHVACZoneSplitter.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACZoneSplitter.cpp`, and `src/epmodel/test/idf/IDF_SmallOffice_GTest.cpp` exercise the same branch-index and inlet-node behavior.
    // - Remaining Parity Work: Add the AirflowNetwork convenience wrappers only if epmodel needs to mirror that additional model-side surface.
    boost::optional<AirLoopHVAC> airLoopHVAC() const;
    unsigned inletPort() const override;
    unsigned outletPort(unsigned branchIndex) const override;
    unsigned nextOutletPort() const override;
    std::vector<ModelObject> outletModelObjects() const override;
    unsigned nextBranchIndex() const override;
    void removePortForBranch(unsigned branchIndex) override;
    bool setOutletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

   protected:
    using ImplType = detail::AirLoopHVACZoneSplitter_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit AirLoopHVACZoneSplitter(std::shared_ptr<detail::AirLoopHVACZoneSplitter_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
