/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABEQUIVALENTSLAB_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABEQUIVALENTSLAB_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferSlabEquivalentSlab_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferSlabEquivalentSlab_Impl() override = default;

      double apratioTheareatoperimeterratioforthisslab() const;
      bool setApratioTheareatoperimeterratioforthisslab(double apratioTheareatoperimeterratioforthisslab);

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
