/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementAutoGrid_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementAutoGrid : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementAutoGrid(const Model& model);

    virtual ~GroundHeatTransferBasementAutoGrid() override = default;
    GroundHeatTransferBasementAutoGrid(const GroundHeatTransferBasementAutoGrid& other) = default;
    GroundHeatTransferBasementAutoGrid(GroundHeatTransferBasementAutoGrid&& other) = default;
    GroundHeatTransferBasementAutoGrid& operator=(const GroundHeatTransferBasementAutoGrid&) = default;
    GroundHeatTransferBasementAutoGrid& operator=(GroundHeatTransferBasementAutoGrid&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:AutoGrid numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    double clearanceDistancefromoutsideofwalltoedge() const;
    bool isClearanceDistancefromoutsideofwalltoedgeDefaulted() const;
    bool setClearanceDistancefromoutsideofwalltoedge(double clearanceDistancefromoutsideofwalltoedge);
    void resetClearanceDistancefromoutsideofwalltoedge();

    double slabxXdimensionofthebuildingslab() const;
    bool setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab);

    double slabyYdimensionofthebuildingslab() const;
    bool setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab);

    double concAGHeightHeightofthefoundationwallabovegrade() const;
    bool isConcAGHeightHeightofthefoundationwallabovegradeDefaulted() const;
    bool setConcAGHeightHeightofthefoundationwallabovegrade(double concAGHeightHeightofthefoundationwallabovegrade);
    void resetConcAGHeightHeightofthefoundationwallabovegrade();

    double slabDepthThicknessofthefloorslab() const;
    bool isSlabDepthThicknessofthefloorslabDefaulted() const;
    bool setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab);
    void resetSlabDepthThicknessofthefloorslab();

    double baseDepthDepthofthebasementwallbelowgrade() const;
    bool isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const;
    bool setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade);
    void resetBaseDepthDepthofthebasementwallbelowgrade();

   protected:
    using ImplType = detail::GroundHeatTransferBasementAutoGrid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementAutoGrid(std::shared_ptr<detail::GroundHeatTransferBasementAutoGrid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
