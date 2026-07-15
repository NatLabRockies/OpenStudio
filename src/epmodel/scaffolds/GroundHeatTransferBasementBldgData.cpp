/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferBasementBldgData.hpp"
#include "GroundHeatTransferBasementBldgData_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Basement_BldgData_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferBasementBldgData::GroundHeatTransferBasementBldgData(const Model& model)
    : ModelObject(GroundHeatTransferBasementBldgData::iddObjectType(), model) {}

  GroundHeatTransferBasementBldgData::GroundHeatTransferBasementBldgData(std::shared_ptr<detail::GroundHeatTransferBasementBldgData_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferBasementBldgData::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Basement_BldgData;
  }

  double GroundHeatTransferBasementBldgData::dwallWallthickness() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->dwallWallthickness();
  }

  bool GroundHeatTransferBasementBldgData::isDwallWallthicknessDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->isDwallWallthicknessDefaulted();
  }

  bool GroundHeatTransferBasementBldgData::setDwallWallthickness(double dwallWallthickness) {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->setDwallWallthickness(dwallWallthickness);
  }

  void GroundHeatTransferBasementBldgData::resetDwallWallthickness() {
    getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->resetDwallWallthickness();
  }

  double GroundHeatTransferBasementBldgData::dslabFloorslabthickness() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->dslabFloorslabthickness();
  }

  bool GroundHeatTransferBasementBldgData::isDslabFloorslabthicknessDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->isDslabFloorslabthicknessDefaulted();
  }

  bool GroundHeatTransferBasementBldgData::setDslabFloorslabthickness(double dslabFloorslabthickness) {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->setDslabFloorslabthickness(dslabFloorslabthickness);
  }

  void GroundHeatTransferBasementBldgData::resetDslabFloorslabthickness() {
    getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->resetDslabFloorslabthickness();
  }

  double GroundHeatTransferBasementBldgData::dgravxyWidthofgravelpitbesidebasementwall() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->dgravxyWidthofgravelpitbesidebasementwall();
  }

  bool GroundHeatTransferBasementBldgData::isDgravxyWidthofgravelpitbesidebasementwallDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->isDgravxyWidthofgravelpitbesidebasementwallDefaulted();
  }

  bool GroundHeatTransferBasementBldgData::setDgravxyWidthofgravelpitbesidebasementwall(double dgravxyWidthofgravelpitbesidebasementwall) {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->setDgravxyWidthofgravelpitbesidebasementwall(
      dgravxyWidthofgravelpitbesidebasementwall);
  }

  void GroundHeatTransferBasementBldgData::resetDgravxyWidthofgravelpitbesidebasementwall() {
    getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->resetDgravxyWidthofgravelpitbesidebasementwall();
  }

  double GroundHeatTransferBasementBldgData::dgravznGraveldepthextendingabovethefloorslab() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->dgravznGraveldepthextendingabovethefloorslab();
  }

  bool GroundHeatTransferBasementBldgData::isDgravznGraveldepthextendingabovethefloorslabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->isDgravznGraveldepthextendingabovethefloorslabDefaulted();
  }

  bool GroundHeatTransferBasementBldgData::setDgravznGraveldepthextendingabovethefloorslab(double dgravznGraveldepthextendingabovethefloorslab) {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->setDgravznGraveldepthextendingabovethefloorslab(
      dgravznGraveldepthextendingabovethefloorslab);
  }

  void GroundHeatTransferBasementBldgData::resetDgravznGraveldepthextendingabovethefloorslab() {
    getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->resetDgravznGraveldepthextendingabovethefloorslab();
  }

  double GroundHeatTransferBasementBldgData::dgravzpGraveldepthbelowthefloorslab() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->dgravzpGraveldepthbelowthefloorslab();
  }

  bool GroundHeatTransferBasementBldgData::isDgravzpGraveldepthbelowthefloorslabDefaulted() const {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->isDgravzpGraveldepthbelowthefloorslabDefaulted();
  }

  bool GroundHeatTransferBasementBldgData::setDgravzpGraveldepthbelowthefloorslab(double dgravzpGraveldepthbelowthefloorslab) {
    return getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->setDgravzpGraveldepthbelowthefloorslab(dgravzpGraveldepthbelowthefloorslab);
  }

  void GroundHeatTransferBasementBldgData::resetDgravzpGraveldepthbelowthefloorslab() {
    getImpl<detail::GroundHeatTransferBasementBldgData_Impl>()->resetDgravzpGraveldepthbelowthefloorslab();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferBasementBldgData_Impl::dwallWallthickness() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DWALL_Wallthickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementBldgData_Impl::isDwallWallthicknessDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DWALL_Wallthickness);
    }

    bool GroundHeatTransferBasementBldgData_Impl::setDwallWallthickness(double dwallWallthickness) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DWALL_Wallthickness, dwallWallthickness);
    }

    void GroundHeatTransferBasementBldgData_Impl::resetDwallWallthickness() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DWALL_Wallthickness, ""));
    }

    double GroundHeatTransferBasementBldgData_Impl::dslabFloorslabthickness() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DSLAB_Floorslabthickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementBldgData_Impl::isDslabFloorslabthicknessDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DSLAB_Floorslabthickness);
    }

    bool GroundHeatTransferBasementBldgData_Impl::setDslabFloorslabthickness(double dslabFloorslabthickness) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DSLAB_Floorslabthickness, dslabFloorslabthickness);
    }

    void GroundHeatTransferBasementBldgData_Impl::resetDslabFloorslabthickness() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DSLAB_Floorslabthickness, ""));
    }

    double GroundHeatTransferBasementBldgData_Impl::dgravxyWidthofgravelpitbesidebasementwall() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVXY_Widthofgravelpitbesidebasementwall, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementBldgData_Impl::isDgravxyWidthofgravelpitbesidebasementwallDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVXY_Widthofgravelpitbesidebasementwall);
    }

    bool GroundHeatTransferBasementBldgData_Impl::setDgravxyWidthofgravelpitbesidebasementwall(double dgravxyWidthofgravelpitbesidebasementwall) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVXY_Widthofgravelpitbesidebasementwall,
                       dgravxyWidthofgravelpitbesidebasementwall);
    }

    void GroundHeatTransferBasementBldgData_Impl::resetDgravxyWidthofgravelpitbesidebasementwall() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVXY_Widthofgravelpitbesidebasementwall, ""));
    }

    double GroundHeatTransferBasementBldgData_Impl::dgravznGraveldepthextendingabovethefloorslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZN_Graveldepthextendingabovethefloorslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementBldgData_Impl::isDgravznGraveldepthextendingabovethefloorslabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZN_Graveldepthextendingabovethefloorslab);
    }

    bool
      GroundHeatTransferBasementBldgData_Impl::setDgravznGraveldepthextendingabovethefloorslab(double dgravznGraveldepthextendingabovethefloorslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZN_Graveldepthextendingabovethefloorslab,
                       dgravznGraveldepthextendingabovethefloorslab);
    }

    void GroundHeatTransferBasementBldgData_Impl::resetDgravznGraveldepthextendingabovethefloorslab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZN_Graveldepthextendingabovethefloorslab, ""));
    }

    double GroundHeatTransferBasementBldgData_Impl::dgravzpGraveldepthbelowthefloorslab() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZP_Graveldepthbelowthefloorslab, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferBasementBldgData_Impl::isDgravzpGraveldepthbelowthefloorslabDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZP_Graveldepthbelowthefloorslab);
    }

    bool GroundHeatTransferBasementBldgData_Impl::setDgravzpGraveldepthbelowthefloorslab(double dgravzpGraveldepthbelowthefloorslab) {
      return setDouble(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZP_Graveldepthbelowthefloorslab,
                       dgravzpGraveldepthbelowthefloorslab);
    }

    void GroundHeatTransferBasementBldgData_Impl::resetDgravzpGraveldepthbelowthefloorslab() {
      OS_ASSERT(setString(openstudio::GroundHeatTransfer_Basement_BldgDataFields::DGRAVZP_Graveldepthbelowthefloorslab, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
