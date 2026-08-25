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

  /** \brief Represents an air-loop supply plenum serving a thermal zone.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacsupplyplenum,AirLoopHVAC:SupplyPlenum}.
   *
   * \par Important behavior
   * Relationships are projected from EnergyPlus branch and node topology and mutators maintain that topology.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACSupplyPlenum</code>.
   * <b>Not yet available: <code>addBranchForZone()</code> and AirflowNetwork distribution-node conveniences. Added: explicit outlet branch enumeration, assignment, and removal methods.</b>
   *
   * \par Known limitations
   * A new zone branch cannot currently be created through an installed plenum.
   */
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
