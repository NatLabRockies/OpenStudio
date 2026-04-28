/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTAUTOGRID_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementAutoGrid_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementAutoGrid_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
