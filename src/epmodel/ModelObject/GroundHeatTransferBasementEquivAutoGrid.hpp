/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTEQUIVAUTOGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTEQUIVAUTOGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferBasementEquivAutoGrid_Impl;
  }

  class EPMODEL_API GroundHeatTransferBasementEquivAutoGrid : public ModelObject
  {
   public:
    explicit GroundHeatTransferBasementEquivAutoGrid(const Model& model);

    virtual ~GroundHeatTransferBasementEquivAutoGrid() override = default;
    GroundHeatTransferBasementEquivAutoGrid(const GroundHeatTransferBasementEquivAutoGrid& other) = default;
    GroundHeatTransferBasementEquivAutoGrid(GroundHeatTransferBasementEquivAutoGrid&& other) = default;
    GroundHeatTransferBasementEquivAutoGrid& operator=(const GroundHeatTransferBasementEquivAutoGrid&) = default;
    GroundHeatTransferBasementEquivAutoGrid& operator=(GroundHeatTransferBasementEquivAutoGrid&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:EquivAutoGrid numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    double clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain() const;
    bool isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted() const;
    bool setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(double clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain);
    void resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain();

    double slabDepthThicknessofthefloorslab() const;
    bool isSlabDepthThicknessofthefloorslabDefaulted() const;
    bool setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab);
    void resetSlabDepthThicknessofthefloorslab();

    double baseDepthDepthofthebasementwallbelowgrade() const;
    bool isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const;
    bool setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade);
    void resetBaseDepthDepthofthebasementwallbelowgrade();

   protected:
    using ImplType = detail::GroundHeatTransferBasementEquivAutoGrid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferBasementEquivAutoGrid(std::shared_ptr<detail::GroundHeatTransferBasementEquivAutoGrid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
