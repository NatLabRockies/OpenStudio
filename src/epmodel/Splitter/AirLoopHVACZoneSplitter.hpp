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

  /** \brief Represents the splitter that distributes supply air to zone branches.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvaczonesplitter,AirLoopHVAC:ZoneSplitter}.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACZoneSplitter</code>.
   * <b>Not yet available: <code>airflowNetworkDistributionNode()</code>, <code>getAirflowNetworkDistributionNode()</code>, and <code>thermalZones()</code>. Added: <code>airLoopHVAC()</code> and explicit outlet branch mutators.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
