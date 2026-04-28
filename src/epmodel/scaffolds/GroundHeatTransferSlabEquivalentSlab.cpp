/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabEquivalentSlab.hpp"
#include "GroundHeatTransferSlabEquivalentSlab_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_EquivalentSlab_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabEquivalentSlab::GroundHeatTransferSlabEquivalentSlab(const Model& model)
    : ModelObject(GroundHeatTransferSlabEquivalentSlab::iddObjectType(), model) {}

  GroundHeatTransferSlabEquivalentSlab::GroundHeatTransferSlabEquivalentSlab(std::shared_ptr<detail::GroundHeatTransferSlabEquivalentSlab_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabEquivalentSlab::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_EquivalentSlab;
  }

  double GroundHeatTransferSlabEquivalentSlab::apratioTheareatoperimeterratioforthisslab() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->apratioTheareatoperimeterratioforthisslab();
  }

  bool GroundHeatTransferSlabEquivalentSlab::setApratioTheareatoperimeterratioforthisslab(double apratioTheareatoperimeterratioforthisslab) {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->setApratioTheareatoperimeterratioforthisslab(
      apratioTheareatoperimeterratioforthisslab);
  }

  double GroundHeatTransferSlabEquivalentSlab::slabdepthThicknessofslabongrade() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->slabdepthThicknessofslabongrade();
  }

  bool GroundHeatTransferSlabEquivalentSlab::isSlabdepthThicknessofslabongradeDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->isSlabdepthThicknessofslabongradeDefaulted();
  }

  bool GroundHeatTransferSlabEquivalentSlab::setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade) {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->setSlabdepthThicknessofslabongrade(slabdepthThicknessofslabongrade);
  }

  void GroundHeatTransferSlabEquivalentSlab::resetSlabdepthThicknessofslabongrade() {
    getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->resetSlabdepthThicknessofslabongrade();
  }

  double GroundHeatTransferSlabEquivalentSlab::clearanceDistancefromedgeofslabtodomainedge() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->clearanceDistancefromedgeofslabtodomainedge();
  }

  bool GroundHeatTransferSlabEquivalentSlab::isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->isClearanceDistancefromedgeofslabtodomainedgeDefaulted();
  }

  bool GroundHeatTransferSlabEquivalentSlab::setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge) {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->setClearanceDistancefromedgeofslabtodomainedge(
      clearanceDistancefromedgeofslabtodomainedge);
  }

  void GroundHeatTransferSlabEquivalentSlab::resetClearanceDistancefromedgeofslabtodomainedge() {
    getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->resetClearanceDistancefromedgeofslabtodomainedge();
  }

  double GroundHeatTransferSlabEquivalentSlab::zclearanceDistancefrombottomofslabtodomainbottom() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->zclearanceDistancefrombottomofslabtodomainbottom();
  }

  bool GroundHeatTransferSlabEquivalentSlab::isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->isZclearanceDistancefrombottomofslabtodomainbottomDefaulted();
  }

  bool GroundHeatTransferSlabEquivalentSlab::setZclearanceDistancefrombottomofslabtodomainbottom(
    double zclearanceDistancefrombottomofslabtodomainbottom) {
    return getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->setZclearanceDistancefrombottomofslabtodomainbottom(
      zclearanceDistancefrombottomofslabtodomainbottom);
  }

  void GroundHeatTransferSlabEquivalentSlab::resetZclearanceDistancefrombottomofslabtodomainbottom() {
    getImpl<detail::GroundHeatTransferSlabEquivalentSlab_Impl>()->resetZclearanceDistancefrombottomofslabtodomainbottom();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferSlabEquivalentSlab_Impl::apratioTheareatoperimeterratioforthisslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::APRatio_Theareatoperimeterratioforthisslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::setApratioTheareatoperimeterratioforthisslab(double apratioTheareatoperimeterratioforthisslab) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::APRatio_Theareatoperimeterratioforthisslab,
                       apratioTheareatoperimeterratioforthisslab);
    }

    double GroundHeatTransferSlabEquivalentSlab_Impl::slabdepthThicknessofslabongrade() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::SLABDEPTH_Thicknessofslabongrade, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::isSlabdepthThicknessofslabongradeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::SLABDEPTH_Thicknessofslabongrade);
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::setSlabdepthThicknessofslabongrade(double slabdepthThicknessofslabongrade) {
      const bool result =
        setDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::SLABDEPTH_Thicknessofslabongrade, slabdepthThicknessofslabongrade);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabEquivalentSlab_Impl::resetSlabdepthThicknessofslabongrade() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::SLABDEPTH_Thicknessofslabongrade, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabEquivalentSlab_Impl::clearanceDistancefromedgeofslabtodomainedge() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::CLEARANCE_Distancefromedgeofslabtodomainedge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::isClearanceDistancefromedgeofslabtodomainedgeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::CLEARANCE_Distancefromedgeofslabtodomainedge);
    }

    bool
      GroundHeatTransferSlabEquivalentSlab_Impl::setClearanceDistancefromedgeofslabtodomainedge(double clearanceDistancefromedgeofslabtodomainedge) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::CLEARANCE_Distancefromedgeofslabtodomainedge,
                                    clearanceDistancefromedgeofslabtodomainedge);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabEquivalentSlab_Impl::resetClearanceDistancefromedgeofslabtodomainedge() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::CLEARANCE_Distancefromedgeofslabtodomainedge, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabEquivalentSlab_Impl::zclearanceDistancefrombottomofslabtodomainbottom() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::isZclearanceDistancefrombottomofslabtodomainbottomDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom);
    }

    bool GroundHeatTransferSlabEquivalentSlab_Impl::setZclearanceDistancefrombottomofslabtodomainbottom(
      double zclearanceDistancefrombottomofslabtodomainbottom) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom,
                                    zclearanceDistancefrombottomofslabtodomainbottom);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabEquivalentSlab_Impl::resetZclearanceDistancefrombottomofslabtodomainbottom() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_EquivalentSlabFields::ZCLEARANCE_Distancefrombottomofslabtodomainbottom, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
