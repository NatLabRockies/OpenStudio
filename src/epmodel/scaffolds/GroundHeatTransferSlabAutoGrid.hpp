/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABAUTOGRID_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABAUTOGRID_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabAutoGrid_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabAutoGrid : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabAutoGrid(const Model& model);

    virtual ~GroundHeatTransferSlabAutoGrid() override = default;
    GroundHeatTransferSlabAutoGrid(const GroundHeatTransferSlabAutoGrid& other) = default;
    GroundHeatTransferSlabAutoGrid(GroundHeatTransferSlabAutoGrid&& other) = default;
    GroundHeatTransferSlabAutoGrid& operator=(const GroundHeatTransferSlabAutoGrid&) = default;
    GroundHeatTransferSlabAutoGrid& operator=(GroundHeatTransferSlabAutoGrid&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:AutoGrid numeric fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.

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

   protected:
    using ImplType = detail::GroundHeatTransferSlabAutoGrid_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabAutoGrid(std::shared_ptr<detail::GroundHeatTransferSlabAutoGrid_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
