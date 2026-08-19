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

  /** \brief Represents an air-loop return plenum serving a thermal zone.
   *
   * \par EnergyPlus object
   * \epobject{group-air-path.html#airloophvacreturnplenum,AirLoopHVAC:ReturnPlenum}.
   *
   * \par Important behavior
   * The plenum zone and its inlet/outlet node topology are kept consistent when attached to or removed from an air loop.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::AirLoopHVACReturnPlenum</code>.
   * <b>Not yet available: <code>addBranchForZone()</code>, induced-air outlet conveniences, and AirflowNetwork distribution-node helpers.</b>
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
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
