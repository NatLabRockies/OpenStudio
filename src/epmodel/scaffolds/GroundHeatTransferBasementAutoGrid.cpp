/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementAutoGrid.hpp"
#include "GroundHeatTransferBasementAutoGrid_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_AutoGrid_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementAutoGrid::GroundHeatTransferBasementAutoGrid(const Model& model)
    : ModelObject(GroundHeatTransferBasementAutoGrid::iddObjectType(), model) {}

  GroundHeatTransferBasementAutoGrid::GroundHeatTransferBasementAutoGrid(std::shared_ptr<detail::GroundHeatTransferBasementAutoGrid_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementAutoGrid::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_AutoGrid;
  }

  double GroundHeatTransferBasementAutoGrid::clearanceDistancefromoutsideofwalltoedge() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->clearanceDistancefromoutsideofwalltoedge();
  }

  bool GroundHeatTransferBasementAutoGrid::isClearanceDistancefromoutsideofwalltoedgeDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->isClearanceDistancefromoutsideofwalltoedgeDefaulted();
  }

  bool GroundHeatTransferBasementAutoGrid::setClearanceDistancefromoutsideofwalltoedge(double clearanceDistancefromoutsideofwalltoedge) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setClearanceDistancefromoutsideofwalltoedge(
      clearanceDistancefromoutsideofwalltoedge);
  }

  void GroundHeatTransferBasementAutoGrid::resetClearanceDistancefromoutsideofwalltoedge() {
    getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->resetClearanceDistancefromoutsideofwalltoedge();
  }

  double GroundHeatTransferBasementAutoGrid::slabxXdimensionofthebuildingslab() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->slabxXdimensionofthebuildingslab();
  }

  bool GroundHeatTransferBasementAutoGrid::setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setSlabxXdimensionofthebuildingslab(slabxXdimensionofthebuildingslab);
  }

  double GroundHeatTransferBasementAutoGrid::slabyYdimensionofthebuildingslab() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->slabyYdimensionofthebuildingslab();
  }

  bool GroundHeatTransferBasementAutoGrid::setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setSlabyYdimensionofthebuildingslab(slabyYdimensionofthebuildingslab);
  }

  double GroundHeatTransferBasementAutoGrid::concAGHeightHeightofthefoundationwallabovegrade() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->concAGHeightHeightofthefoundationwallabovegrade();
  }

  bool GroundHeatTransferBasementAutoGrid::isConcAGHeightHeightofthefoundationwallabovegradeDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->isConcAGHeightHeightofthefoundationwallabovegradeDefaulted();
  }

  bool
    GroundHeatTransferBasementAutoGrid::setConcAGHeightHeightofthefoundationwallabovegrade(double concAGHeightHeightofthefoundationwallabovegrade) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setConcAGHeightHeightofthefoundationwallabovegrade(
      concAGHeightHeightofthefoundationwallabovegrade);
  }

  void GroundHeatTransferBasementAutoGrid::resetConcAGHeightHeightofthefoundationwallabovegrade() {
    getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->resetConcAGHeightHeightofthefoundationwallabovegrade();
  }

  double GroundHeatTransferBasementAutoGrid::slabDepthThicknessofthefloorslab() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->slabDepthThicknessofthefloorslab();
  }

  bool GroundHeatTransferBasementAutoGrid::isSlabDepthThicknessofthefloorslabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->isSlabDepthThicknessofthefloorslabDefaulted();
  }

  bool GroundHeatTransferBasementAutoGrid::setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setSlabDepthThicknessofthefloorslab(slabDepthThicknessofthefloorslab);
  }

  void GroundHeatTransferBasementAutoGrid::resetSlabDepthThicknessofthefloorslab() {
    getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->resetSlabDepthThicknessofthefloorslab();
  }

  double GroundHeatTransferBasementAutoGrid::baseDepthDepthofthebasementwallbelowgrade() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->baseDepthDepthofthebasementwallbelowgrade();
  }

  bool GroundHeatTransferBasementAutoGrid::isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->isBaseDepthDepthofthebasementwallbelowgradeDefaulted();
  }

  bool GroundHeatTransferBasementAutoGrid::setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade) {
    return getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->setBaseDepthDepthofthebasementwallbelowgrade(
      baseDepthDepthofthebasementwallbelowgrade);
  }

  void GroundHeatTransferBasementAutoGrid::resetBaseDepthDepthofthebasementwallbelowgrade() {
    getImpl<detail::GroundHeatTransferBasementAutoGrid_Impl>()->resetBaseDepthDepthofthebasementwallbelowgrade();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferBasementAutoGrid_Impl::clearanceDistancefromoutsideofwalltoedge() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::CLEARANCE_Distancefromoutsideofwalltoedge, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::isClearanceDistancefromoutsideofwalltoedgeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_AutoGridFields::CLEARANCE_Distancefromoutsideofwalltoedge);
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setClearanceDistancefromoutsideofwalltoedge(double clearanceDistancefromoutsideofwalltoedge) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::CLEARANCE_Distancefromoutsideofwalltoedge,
                       clearanceDistancefromoutsideofwalltoedge);
    }

    void GroundHeatTransferBasementAutoGrid_Impl::resetClearanceDistancefromoutsideofwalltoedge() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_AutoGridFields::CLEARANCE_Distancefromoutsideofwalltoedge, ""));
    }

    double GroundHeatTransferBasementAutoGrid_Impl::slabxXdimensionofthebuildingslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SLABX_Xdimensionofthebuildingslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setSlabxXdimensionofthebuildingslab(double slabxXdimensionofthebuildingslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SLABX_Xdimensionofthebuildingslab, slabxXdimensionofthebuildingslab);
    }

    double GroundHeatTransferBasementAutoGrid_Impl::slabyYdimensionofthebuildingslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SLABY_Ydimensionofthebuildingslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setSlabyYdimensionofthebuildingslab(double slabyYdimensionofthebuildingslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SLABY_Ydimensionofthebuildingslab, slabyYdimensionofthebuildingslab);
    }

    double GroundHeatTransferBasementAutoGrid_Impl::concAGHeightHeightofthefoundationwallabovegrade() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::ConcAGHeight_Heightofthefoundationwallabovegrade, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::isConcAGHeightHeightofthefoundationwallabovegradeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_AutoGridFields::ConcAGHeight_Heightofthefoundationwallabovegrade);
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setConcAGHeightHeightofthefoundationwallabovegrade(
      double concAGHeightHeightofthefoundationwallabovegrade) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::ConcAGHeight_Heightofthefoundationwallabovegrade,
                       concAGHeightHeightofthefoundationwallabovegrade);
    }

    void GroundHeatTransferBasementAutoGrid_Impl::resetConcAGHeightHeightofthefoundationwallabovegrade() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_AutoGridFields::ConcAGHeight_Heightofthefoundationwallabovegrade, ""));
    }

    double GroundHeatTransferBasementAutoGrid_Impl::slabDepthThicknessofthefloorslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SlabDepth_Thicknessofthefloorslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::isSlabDepthThicknessofthefloorslabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SlabDepth_Thicknessofthefloorslab);
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setSlabDepthThicknessofthefloorslab(double slabDepthThicknessofthefloorslab) {
      const bool result =
        setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SlabDepth_Thicknessofthefloorslab, slabDepthThicknessofthefloorslab);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferBasementAutoGrid_Impl::resetSlabDepthThicknessofthefloorslab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_AutoGridFields::SlabDepth_Thicknessofthefloorslab, ""));
    }

    double GroundHeatTransferBasementAutoGrid_Impl::baseDepthDepthofthebasementwallbelowgrade() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::BaseDepth_Depthofthebasementwallbelowgrade, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::isBaseDepthDepthofthebasementwallbelowgradeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_AutoGridFields::BaseDepth_Depthofthebasementwallbelowgrade);
    }

    bool GroundHeatTransferBasementAutoGrid_Impl::setBaseDepthDepthofthebasementwallbelowgrade(double baseDepthDepthofthebasementwallbelowgrade) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_AutoGridFields::BaseDepth_Depthofthebasementwallbelowgrade,
                       baseDepthDepthofthebasementwallbelowgrade);
    }

    void GroundHeatTransferBasementAutoGrid_Impl::resetBaseDepthDepthofthebasementwallbelowgrade() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_AutoGridFields::BaseDepth_Depthofthebasementwallbelowgrade, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
