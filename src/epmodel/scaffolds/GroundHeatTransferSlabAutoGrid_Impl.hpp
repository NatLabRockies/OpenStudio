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
      bool setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab);

      double slabyYdimensionofthebuildingslab() const;
      bool setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab);

      double slabdepthThicknessofslabongrade() const;
      bool isSlabdepthThicknessofslabongradeDefaulted() const;
      bool setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade);
      void resetSlabdepthThicknessofslabongrade();

      double clearanceDistancefromedgeofslabtodomainedge() const;
      bool isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const;
      bool setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge);
      void resetClearanceDistancefromedgeofslabtodomainedge();

      double zclearanceDistancefrombottomofslabtodomainbottom() const;
      bool isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const;
      bool setZclearanceDistancefrombottomofslabtodomainbottom(double zclearanceDistancefrombottomofslabtodomainbottom);
      void resetZclearanceDistancefrombottomofslabtodomainbottom();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
