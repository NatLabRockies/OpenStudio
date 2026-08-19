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

  /** \brief Represents the mixer that combines zone return-air branches.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvaczonemixer,AirLoopHVAC:ZoneMixer}.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACZoneMixer</code>.
   * <b>Not yet available: <code>airflowNetworkDistributionNode()</code> and <code>getAirflowNetworkDistributionNode()</code>. Added: <code>airLoopHVAC()</code> and explicit inlet branch enumeration, assignment, and removal methods.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
