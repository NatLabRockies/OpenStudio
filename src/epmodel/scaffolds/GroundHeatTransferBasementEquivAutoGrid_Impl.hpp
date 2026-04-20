/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTEQUIVAUTOGRID_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTEQUIVAUTOGRID_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementEquivAutoGrid_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementEquivAutoGrid_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
