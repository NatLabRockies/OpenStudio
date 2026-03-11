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
  double slabDepthThicknessofthefloorslab() const;
  double baseDepthDepthofthebasementwallbelowgrade() const;

  bool isClearanceDistancefromoutsideofwalltoedgeof3DgrounddomainDefaulted() const;
  bool isSlabDepthThicknessofthefloorslabDefaulted() const;
  bool isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const;

  bool setClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain(double clearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain);
  bool setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab);
  bool setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade);

  void resetClearanceDistancefromoutsideofwalltoedgeof3Dgrounddomain();
  void resetSlabDepthThicknessofthefloorslab();
  void resetBaseDepthDepthofthebasementwallbelowgrade();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
