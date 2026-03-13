/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabAutoGrid.hpp"
#include "GroundHeatTransferSlabAutoGrid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_AutoGrid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabAutoGrid::GroundHeatTransferSlabAutoGrid(const Model& model)
    : ModelObject(GroundHeatTransferSlabAutoGrid::iddObjectType(), model) {}

  GroundHeatTransferSlabAutoGrid::GroundHeatTransferSlabAutoGrid(std::shared_ptr<detail::GroundHeatTransferSlabAutoGrid_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabAutoGrid::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_AutoGrid;
  }

  double GroundHeatTransferSlabAutoGrid::slabxXdimensionofthebuildingslab() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->slabxXdimensionofthebuildingslab();
  }

  bool GroundHeatTransferSlabAutoGrid::setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab) {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->setSlabxXdimensionofthebuildingslab(slabxXdimensionofthebuildingslab);
  }

  double GroundHeatTransferSlabAutoGrid::slabyYdimensionofthebuildingslab() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->slabyYdimensionofthebuildingslab();
  }

  bool GroundHeatTransferSlabAutoGrid::setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab) {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->setSlabyYdimensionofthebuildingslab(slabyYdimensionofthebuildingslab);
  }

  double GroundHeatTransferSlabAutoGrid::slabdepthThicknessofslabongrade() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->slabdepthThicknessofslabongrade();
  }

  bool GroundHeatTransferSlabAutoGrid::isSlabdepthThicknessofslabongradeDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->isSlabdepthThicknessofslabongradeDefaulted();
  }

  bool GroundHeatTransferSlabAutoGrid::setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade) {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->setSlabdepthThicknessofslabongrade(slabdepthThicknessofslabongrade);
  }

  void GroundHeatTransferSlabAutoGrid::resetSlabdepthThicknessofslabongrade() {
    getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->resetSlabdepthThicknessofslabongrade();
  }

  double GroundHeatTransferSlabAutoGrid::clearanceDistancefromedgeofslabtodomainedge() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->clearanceDistancefromedgeofslabtodomainedge();
  }

  bool GroundHeatTransferSlabAutoGrid::isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->isClearanceDistancefromedgeofslabtodomainedgeDefaulted();
  }

  bool GroundHeatTransferSlabAutoGrid::setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge) {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->setClearanceDistancefromedgeofslabtodomainedge(
      clearanceDistancefromedgeofslabtodomainedge);
  }

  void GroundHeatTransferSlabAutoGrid::resetClearanceDistancefromedgeofslabtodomainedge() {
    getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->resetClearanceDistancefromedgeofslabtodomainedge();
  }

  double GroundHeatTransferSlabAutoGrid::zclearanceDistancefrombottomofslabtodomainbottom() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->zclearanceDistancefrombottomofslabtodomainbottom();
  }

  bool GroundHeatTransferSlabAutoGrid::isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->isZclearanceDistancefrombottomofslabtodomainbottomDefaulted();
  }

  bool GroundHeatTransferSlabAutoGrid::setZclearanceDistancefrombottomofslabtodomainbottom(double zclearanceDistancefrombottomofslabtodomainbottom) {
    return getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->setZclearanceDistancefrombottomofslabtodomainbottom(
      zclearanceDistancefrombottomofslabtodomainbottom);
  }

  void GroundHeatTransferSlabAutoGrid::resetZclearanceDistancefrombottomofslabtodomainbottom() {
    getImpl<detail::GroundHeatTransferSlabAutoGrid_Impl>()->resetZclearanceDistancefrombottomofslabtodomainbottom();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferSlabAutoGrid_Impl::slabxXdimensionofthebuildingslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABX_Xdimensionofthebuildingslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABX_Xdimensionofthebuildingslab, slabxXdimensionofthebuildingslab);
    }

    double GroundHeatTransferSlabAutoGrid_Impl::slabyYdimensionofthebuildingslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABY_Ydimensionofthebuildingslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABY_Ydimensionofthebuildingslab, slabyYdimensionofthebuildingslab);
    }

    double GroundHeatTransferSlabAutoGrid_Impl::slabdepthThicknessofslabongrade() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABDEPTH_Thicknessofslabongrade, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::isSlabdepthThicknessofslabongradeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABDEPTH_Thicknessofslabongrade);
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade) {
      const bool result =
        setDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABDEPTH_Thicknessofslabongrade, slabdepthThicknessofslabongrade);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabAutoGrid_Impl::resetSlabdepthThicknessofslabongrade() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_AutoGridFields::SLABDEPTH_Thicknessofslabongrade, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabAutoGrid_Impl::clearanceDistancefromedgeofslabtodomainedge() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::CLEARANCE_Distancefromedgeofslabtodomainedge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_AutoGridFields::CLEARANCE_Distancefromedgeofslabtodomainedge);
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::CLEARANCE_Distancefromedgeofslabtodomainedge,
                                    clearanceDistancefromedgeofslabtodomainedge);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabAutoGrid_Impl::resetClearanceDistancefromedgeofslabtodomainedge() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_AutoGridFields::CLEARANCE_Distancefromedgeofslabtodomainedge, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabAutoGrid_Impl::zclearanceDistancefrombottomofslabtodomainbottom() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_AutoGridFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom);
    }

    bool GroundHeatTransferSlabAutoGrid_Impl::setZclearanceDistancefrombottomofslabtodomainbottom(
      double zclearanceDistancefrombottomofslabtodomainbottom) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_AutoGridFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom,
                                    zclearanceDistancefrombottomofslabtodomainbottom);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabAutoGrid_Impl::resetZclearanceDistancefrombottomofslabtodomainbottom() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_AutoGridFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
