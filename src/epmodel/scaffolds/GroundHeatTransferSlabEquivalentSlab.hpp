/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABEQUIVALENTSLAB_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABEQUIVALENTSLAB_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabEquivalentSlab_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabEquivalentSlab : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabEquivalentSlab(const Model& model);

    virtual ~GroundHeatTransferSlabEquivalentSlab() override = default;
    GroundHeatTransferSlabEquivalentSlab(const GroundHeatTransferSlabEquivalentSlab& other) = default;
    GroundHeatTransferSlabEquivalentSlab(GroundHeatTransferSlabEquivalentSlab&& other) = default;
    GroundHeatTransferSlabEquivalentSlab& operator=(const GroundHeatTransferSlabEquivalentSlab&) = default;
    GroundHeatTransferSlabEquivalentSlab& operator=(GroundHeatTransferSlabEquivalentSlab&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:EquivalentSlab numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

   protected:
    using ImplType = detail::GroundHeatTransferSlabEquivalentSlab_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabEquivalentSlab(std::shared_ptr<detail::GroundHeatTransferSlabEquivalentSlab_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
