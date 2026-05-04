/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONEMIXER_HPP
#define EPMODEL_AIRLOOPHVACZONEMIXER_HPP

#include "EPModelAPI.hpp"
#include "Mixer.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class AirLoopHVAC;
class Model;

namespace detail {
  class AirLoopHVACZoneMixer_Impl;
}

class EPMODEL_API AirLoopHVACZoneMixer : public Mixer
{
 public:
  explicit AirLoopHVACZoneMixer(const Model& model);

  virtual ~AirLoopHVACZoneMixer() override = default;
  AirLoopHVACZoneMixer(const AirLoopHVACZoneMixer& other) = default;
  AirLoopHVACZoneMixer(AirLoopHVACZoneMixer&& other) = default;
  AirLoopHVACZoneMixer& operator=(const AirLoopHVACZoneMixer&) = default;
  AirLoopHVACZoneMixer& operator=(AirLoopHVACZoneMixer&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - Status: Partial Parity. The zone-mixer topology surface is present, but the canonical wrapper exposes additional airflow-network convenience APIs.
  // - Canonical Counterpart: openstudio::model::AirLoopHVACZoneMixer.
  // - Implemented Parity: Outlet/inlet port access, branch indexing, inlet-object enumeration, branch removal, and inlet-object assignment preserve the canonical zone-mixer topology contract.
  // - Documented Delta: epmodel still omits the AirflowNetwork distribution-node convenience API present in the canonical wrapper.
  // - Field/Storage Mapping: `AirLoopHVAC:ZoneMixer` outlet-node and extensible inlet-node fields are represented as relationship fields.
  // - Evidence: `src/model/AirLoopHVACZoneMixer.hpp`, `src/energyplus/ForwardTranslator/ForwardTranslateAirLoopHVACZoneMixer.cpp`, and `src/epmodel/test/idf/IDF_SmallOffice_GTest.cpp` exercise the same branch-index and outlet-node behavior.
  // - Remaining Parity Work: Add the AirflowNetwork convenience wrappers only if epmodel needs to mirror that additional model-side surface.
  boost::optional<AirLoopHVAC> airLoopHVAC() const;
  unsigned outletPort() const override;
  unsigned inletPort(unsigned branchIndex) const override;
  unsigned nextInletPort() const override;
  std::vector<ModelObject> inletModelObjects() const override;
  unsigned nextBranchIndex() const override;
  void removePortForBranch(unsigned branchIndex) override;
  bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

 protected:
  using ImplType = detail::AirLoopHVACZoneMixer_Impl;

  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class Model;

  explicit AirLoopHVACZoneMixer(std::shared_ptr<detail::AirLoopHVACZoneMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
