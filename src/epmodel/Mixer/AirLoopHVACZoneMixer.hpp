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
  // - API: Preserves existing model-counterpart behavior focused on topology, not dedicated scalar fields.
  // - Field Mapping: AirLoopHVAC:ZoneMixer Outlet Node Name and extensible Inlet Node Name rows are relationship fields.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add explicit scalar APIs only if a future counterpart change introduces non-relationship scalar fields.
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
  friend class openstudio::epmodel::Model;

  explicit AirLoopHVACZoneMixer(std::shared_ptr<detail::AirLoopHVACZoneMixer_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
