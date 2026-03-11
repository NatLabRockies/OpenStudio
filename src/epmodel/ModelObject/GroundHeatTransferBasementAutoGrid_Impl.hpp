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
  double slabxXdimensionofthebuildingslab() const;
  double slabyYdimensionofthebuildingslab() const;
  double concAGHeightHeightofthefoundationwallabovegrade() const;
  double slabDepthThicknessofthefloorslab() const;
  double baseDepthDepthofthebasementwallbelowgrade() const;

  bool isClearanceDistancefromoutsideofwalltoedgeDefaulted() const;
  bool isConcAGHeightHeightofthefoundationwallabovegradeDefaulted() const;
  bool isSlabDepthThicknessofthefloorslabDefaulted() const;
  bool isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const;

  bool setClearanceDistancefromoutsideofwalltoedge(double clearanceDistancefromoutsideofwalltoedge);
  bool setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab);
  bool setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab);
  bool setConcAGHeightHeightofthefoundationwallabovegrade(double concAGHeightHeightofthefoundationwallabovegrade);
  bool setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab);
  bool setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade);

  void resetClearanceDistancefromoutsideofwalltoedge();
  void resetConcAGHeightHeightofthefoundationwallabovegrade();
  void resetSlabDepthThicknessofthefloorslab();
  void resetBaseDepthDepthofthebasementwallbelowgrade();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
