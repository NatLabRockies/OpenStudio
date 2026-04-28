/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabManualGrid.hpp"
#include "GroundHeatTransferSlabManualGrid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_ManualGrid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabManualGrid::GroundHeatTransferSlabManualGrid(const Model& model)
    : ModelObject(GroundHeatTransferSlabManualGrid::iddObjectType(), model) {}

  GroundHeatTransferSlabManualGrid::GroundHeatTransferSlabManualGrid(std::shared_ptr<detail::GroundHeatTransferSlabManualGrid_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabManualGrid::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_ManualGrid;
  }

  int GroundHeatTransferSlabManualGrid::nXNumberofcellsintheXdirection() const {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->nXNumberofcellsintheXdirection();
  }

  bool GroundHeatTransferSlabManualGrid::setNXNumberofcellsintheXdirection(int nXNumberofcellsintheXdirection) {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->setNXNumberofcellsintheXdirection(nXNumberofcellsintheXdirection);
  }

  int GroundHeatTransferSlabManualGrid::nYNumberofcellsintheYdirection() const {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->nYNumberofcellsintheYdirection();
  }

  bool GroundHeatTransferSlabManualGrid::setNYNumberofcellsintheYdirection(int nYNumberofcellsintheYdirection) {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->setNYNumberofcellsintheYdirection(nYNumberofcellsintheYdirection);
  }

  int GroundHeatTransferSlabManualGrid::nZNumberofcellsintheZdirection() const {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->nZNumberofcellsintheZdirection();
  }

  bool GroundHeatTransferSlabManualGrid::setNZNumberofcellsintheZdirection(int nZNumberofcellsintheZdirection) {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->setNZNumberofcellsintheZdirection(nZNumberofcellsintheZdirection);
  }

  int GroundHeatTransferSlabManualGrid::iBOXXdirectioncellindicatorofslabedge() const {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->iBOXXdirectioncellindicatorofslabedge();
  }

  bool GroundHeatTransferSlabManualGrid::setIBOXXdirectioncellindicatorofslabedge(int iBOXXdirectioncellindicatorofslabedge) {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->setIBOXXdirectioncellindicatorofslabedge(iBOXXdirectioncellindicatorofslabedge);
  }

  int GroundHeatTransferSlabManualGrid::jBOXYdirectioncellindicatorofslabedge() const {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->jBOXYdirectioncellindicatorofslabedge();
  }

  bool GroundHeatTransferSlabManualGrid::setJBOXYdirectioncellindicatorofslabedge(int jBOXYdirectioncellindicatorofslabedge) {
    return getImpl<detail::GroundHeatTransferSlabManualGrid_Impl>()->setJBOXYdirectioncellindicatorofslabedge(jBOXYdirectioncellindicatorofslabedge);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    int GroundHeatTransferSlabManualGrid_Impl::nXNumberofcellsintheXdirection() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NX_NumberofcellsintheXdirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabManualGrid_Impl::setNXNumberofcellsintheXdirection(int nXNumberofcellsintheXdirection) {
      return setInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NX_NumberofcellsintheXdirection, nXNumberofcellsintheXdirection);
    }

    int GroundHeatTransferSlabManualGrid_Impl::nYNumberofcellsintheYdirection() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NY_NumberofcellsintheYdirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabManualGrid_Impl::setNYNumberofcellsintheYdirection(int nYNumberofcellsintheYdirection) {
      return setInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NY_NumberofcellsintheYdirection, nYNumberofcellsintheYdirection);
    }

    int GroundHeatTransferSlabManualGrid_Impl::nZNumberofcellsintheZdirection() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NZ_NumberofcellsintheZdirection, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabManualGrid_Impl::setNZNumberofcellsintheZdirection(int nZNumberofcellsintheZdirection) {
      return setInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::NZ_NumberofcellsintheZdirection, nZNumberofcellsintheZdirection);
    }

    int GroundHeatTransferSlabManualGrid_Impl::iBOXXdirectioncellindicatorofslabedge() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::IBOX_Xdirectioncellindicatorofslabedge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabManualGrid_Impl::setIBOXXdirectioncellindicatorofslabedge(int iBOXXdirectioncellindicatorofslabedge) {
      const bool result =
        setInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::IBOX_Xdirectioncellindicatorofslabedge, iBOXXdirectioncellindicatorofslabedge);
      OS_ASSERT(result);
      return result;
    }

    int GroundHeatTransferSlabManualGrid_Impl::jBOXYdirectioncellindicatorofslabedge() const {
      const auto value = getInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::JBOX_Ydirectioncellindicatorofslabedge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabManualGrid_Impl::setJBOXYdirectioncellindicatorofslabedge(int jBOXYdirectioncellindicatorofslabedge) {
      const bool result =
        setInt(openstudio::GroundHeatTransfer_Slab_ManualGridFields::JBOX_Ydirectioncellindicatorofslabedge, jBOXYdirectioncellindicatorofslabedge);
      OS_ASSERT(result);
      return result;
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
