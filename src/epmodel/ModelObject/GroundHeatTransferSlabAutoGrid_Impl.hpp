/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABAUTOGRID_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABAUTOGRID_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferSlabAutoGrid_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferSlabAutoGrid_Impl() override = default;

  double slabxXdimensionofthebuildingslab() const;
  double slabyYdimensionofthebuildingslab() const;
  double slabdepthThicknessofslabongrade() const;
  double clearanceDistancefromedgeofslabtodomainedge() const;
  double zclearanceDistancefrombottomofslabtodomainbottom() const;

  bool isSlabdepthThicknessofslabongradeDefaulted() const;
  bool isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const;
  bool isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const;

  bool setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab);
  bool setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab);
  bool setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade);
  bool setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge);
  bool setZclearanceDistancefrombottomofslabtodomainbottom(double zclearanceDistancefrombottomofslabtodomainbottom);

  void resetSlabdepthThicknessofslabongrade();
  void resetClearanceDistancefromedgeofslabtodomainedge();
  void resetZclearanceDistancefrombottomofslabtodomainbottom();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
