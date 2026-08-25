/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONNECTORMIXER_HPP
#define EPMODEL_CONNECTORMIXER_HPP

#include "EPModelAPI.hpp"
#include "Mixer.hpp"

#include "../utilities/idd/IddEnums.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ConnectorMixer_Impl;
  }

  /** \brief Represents an EnergyPlus connector that combines branch flows.
   *
   * \par EnergyPlus object
   * \epobject{group-node-branch-management.html#connectormixer,Connector:Mixer}.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ConnectorMixer</code>.
   * <b>Added: explicit inlet-object enumeration, assignment, and branch removal methods such as <code>inletModelObjects()</code>, <code>setInletModelObject()</code>, and <code>removePortForBranch()</code>.</b>
   *
   * \par Known limitations
   * Connector relationships are represented through EnergyPlus branch topology.
   */
  class EPMODEL_API ConnectorMixer : public Mixer
  {
   public:
    explicit ConnectorMixer(const Model& model);

    virtual ~ConnectorMixer() override = default;
    ConnectorMixer(const ConnectorMixer& other) = default;
    ConnectorMixer(ConnectorMixer&& other) = default;
    ConnectorMixer& operator=(const ConnectorMixer&) = default;
    ConnectorMixer& operator=(ConnectorMixer&&) = default;

    static IddObjectType iddObjectType();

    unsigned outletPort() const override;
    unsigned inletPort(unsigned branchIndex) const override;
    unsigned nextInletPort() const override;
    boost::optional<ModelObject> outletModelObject() const override;
    std::vector<ModelObject> inletModelObjects() const override;
    unsigned nextBranchIndex() const override;
    void removePortForBranch(unsigned branchIndex) override;
    bool setInletModelObject(unsigned branchIndex, const ModelObject& modelObject) override;

   protected:
    using ImplType = detail::ConnectorMixer_Impl;

    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
    friend class Model;

    explicit ConnectorMixer(std::shared_ptr<detail::ConnectorMixer_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
