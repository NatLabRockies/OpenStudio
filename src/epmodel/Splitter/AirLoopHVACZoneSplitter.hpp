/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRLOOPHVACZONESPLITTER_HPP
#define EPMODEL_AIRLOOPHVACZONESPLITTER_HPP

#include "EPModelAPI.hpp"
#include "Splitter.hpp"

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
  // - API: Preserves existing model-counterpart behavior focused on topology, not dedicated scalar fields.
  // - Field Mapping: AirLoopHVAC:ZoneSplitter Inlet Node Name and extensible Outlet Node Name rows are relationship fields.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add explicit scalar APIs only if a future counterpart change introduces non-relationship scalar fields.
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
  friend class openstudio::epmodel::Model;

  explicit AirLoopHVACZoneSplitter(std::shared_ptr<detail::AirLoopHVACZoneSplitter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
