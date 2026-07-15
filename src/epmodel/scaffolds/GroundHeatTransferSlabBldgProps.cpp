/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "GroundHeatTransferSlabBldgProps.hpp"
#include "GroundHeatTransferSlabBldgProps_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/GroundHeatTransfer_Slab_BldgProps_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  GroundHeatTransferSlabBldgProps::GroundHeatTransferSlabBldgProps(const Model& model)
    : ModelObject(GroundHeatTransferSlabBldgProps::iddObjectType(), model) {}

  GroundHeatTransferSlabBldgProps::GroundHeatTransferSlabBldgProps(std::shared_ptr<detail::GroundHeatTransferSlabBldgProps_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType GroundHeatTransferSlabBldgProps::iddObjectType() {
    return IddObjectType::GroundHeatTransfer_Slab_BldgProps;
  }

  double GroundHeatTransferSlabBldgProps::iyrsNumberofyearstoiterate() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->iyrsNumberofyearstoiterate();
  }

  bool GroundHeatTransferSlabBldgProps::isIyrsNumberofyearstoiterateDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isIyrsNumberofyearstoiterateDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setIyrsNumberofyearstoiterate(double iyrsNumberofyearstoiterate) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setIyrsNumberofyearstoiterate(iyrsNumberofyearstoiterate);
  }

  void GroundHeatTransferSlabBldgProps::resetIyrsNumberofyearstoiterate() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetIyrsNumberofyearstoiterate();
  }

  boost::optional<double> GroundHeatTransferSlabBldgProps::shapeSlabshape() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->shapeSlabshape();
  }

  bool GroundHeatTransferSlabBldgProps::setShapeSlabshape(double shapeSlabshape) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setShapeSlabshape(shapeSlabshape);
  }

  void GroundHeatTransferSlabBldgProps::resetShapeSlabshape() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetShapeSlabshape();
  }

  boost::optional<double> GroundHeatTransferSlabBldgProps::hbldgBuildingheight() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->hbldgBuildingheight();
  }

  bool GroundHeatTransferSlabBldgProps::setHbldgBuildingheight(double hbldgBuildingheight) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setHbldgBuildingheight(hbldgBuildingheight);
  }

  void GroundHeatTransferSlabBldgProps::resetHbldgBuildingheight() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetHbldgBuildingheight();
  }

  double GroundHeatTransferSlabBldgProps::tin1JanuaryIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin1JanuaryIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin1JanuaryIndoorAverageTemperatureSetpoint(double tin1JanuaryIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin1JanuaryIndoorAverageTemperatureSetpoint(
      tin1JanuaryIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin1JanuaryIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin1JanuaryIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin2FebruaryIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin2FebruaryIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin2FebruaryIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin2FebruaryIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin2FebruaryIndoorAverageTemperatureSetpoint(double tin2FebruaryIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin2FebruaryIndoorAverageTemperatureSetpoint(
      tin2FebruaryIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin2FebruaryIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin2FebruaryIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin3MarchIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin3MarchIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin3MarchIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin3MarchIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin3MarchIndoorAverageTemperatureSetpoint(double tin3MarchIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin3MarchIndoorAverageTemperatureSetpoint(
      tin3MarchIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin3MarchIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin3MarchIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin4AprilIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin4AprilIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin4AprilIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin4AprilIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin4AprilIndoorAverageTemperatureSetpoint(double tin4AprilIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin4AprilIndoorAverageTemperatureSetpoint(
      tin4AprilIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin4AprilIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin4AprilIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin5MayIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin5MayIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin5MayIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin5MayIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin5MayIndoorAverageTemperatureSetpoint(double tin5MayIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin5MayIndoorAverageTemperatureSetpoint(
      tin5MayIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin5MayIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin5MayIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin6JuneIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin6JuneIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin6JuneIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin6JuneIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin6JuneIndoorAverageTemperatureSetpoint(double tin6JuneIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin6JuneIndoorAverageTemperatureSetpoint(
      tin6JuneIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin6JuneIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin6JuneIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin7JulyIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin7JulyIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin7JulyIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin7JulyIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin7JulyIndoorAverageTemperatureSetpoint(double tin7JulyIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin7JulyIndoorAverageTemperatureSetpoint(
      tin7JulyIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin7JulyIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin7JulyIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin8AugustIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin8AugustIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin8AugustIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin8AugustIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin8AugustIndoorAverageTemperatureSetpoint(double tin8AugustIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin8AugustIndoorAverageTemperatureSetpoint(
      tin8AugustIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin8AugustIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin8AugustIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin9SeptemberIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin9SeptemberIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin9SeptemberIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin9SeptemberIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin9SeptemberIndoorAverageTemperatureSetpoint(double tin9SeptemberIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin9SeptemberIndoorAverageTemperatureSetpoint(
      tin9SeptemberIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin9SeptemberIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin9SeptemberIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin10OctoberIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin10OctoberIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin10OctoberIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin10OctoberIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin10OctoberIndoorAverageTemperatureSetpoint(double tin10OctoberIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin10OctoberIndoorAverageTemperatureSetpoint(
      tin10OctoberIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin10OctoberIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin10OctoberIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin11NovemberIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin11NovemberIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin11NovemberIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin11NovemberIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin11NovemberIndoorAverageTemperatureSetpoint(double tin11NovemberIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin11NovemberIndoorAverageTemperatureSetpoint(
      tin11NovemberIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin11NovemberIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin11NovemberIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tin12DecemberIndoorAverageTemperatureSetpoint() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tin12DecemberIndoorAverageTemperatureSetpoint();
  }

  bool GroundHeatTransferSlabBldgProps::isTin12DecemberIndoorAverageTemperatureSetpointDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTin12DecemberIndoorAverageTemperatureSetpointDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTin12DecemberIndoorAverageTemperatureSetpoint(double tin12DecemberIndoorAverageTemperatureSetpoint) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTin12DecemberIndoorAverageTemperatureSetpoint(
      tin12DecemberIndoorAverageTemperatureSetpoint);
  }

  void GroundHeatTransferSlabBldgProps::resetTin12DecemberIndoorAverageTemperatureSetpoint() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTin12DecemberIndoorAverageTemperatureSetpoint();
  }

  double GroundHeatTransferSlabBldgProps::tinAmpDailyIndoorsinewavevariationamplitude() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->tinAmpDailyIndoorsinewavevariationamplitude();
  }

  bool GroundHeatTransferSlabBldgProps::isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setTinAmpDailyIndoorsinewavevariationamplitude(double tinAmpDailyIndoorsinewavevariationamplitude) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setTinAmpDailyIndoorsinewavevariationamplitude(
      tinAmpDailyIndoorsinewavevariationamplitude);
  }

  void GroundHeatTransferSlabBldgProps::resetTinAmpDailyIndoorsinewavevariationamplitude() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetTinAmpDailyIndoorsinewavevariationamplitude();
  }

  double GroundHeatTransferSlabBldgProps::convTolConvergenceTolerance() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->convTolConvergenceTolerance();
  }

  bool GroundHeatTransferSlabBldgProps::isConvTolConvergenceToleranceDefaulted() const {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->isConvTolConvergenceToleranceDefaulted();
  }

  bool GroundHeatTransferSlabBldgProps::setConvTolConvergenceTolerance(double convTolConvergenceTolerance) {
    return getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->setConvTolConvergenceTolerance(convTolConvergenceTolerance);
  }

  void GroundHeatTransferSlabBldgProps::resetConvTolConvergenceTolerance() {
    getImpl<detail::GroundHeatTransferSlabBldgProps_Impl>()->resetConvTolConvergenceTolerance();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double GroundHeatTransferSlabBldgProps_Impl::iyrsNumberofyearstoiterate() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::IYRS_Numberofyearstoiterate, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isIyrsNumberofyearstoiterateDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::IYRS_Numberofyearstoiterate);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setIyrsNumberofyearstoiterate(double iyrsNumberofyearstoiterate) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::IYRS_Numberofyearstoiterate, iyrsNumberofyearstoiterate);
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetIyrsNumberofyearstoiterate() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::IYRS_Numberofyearstoiterate, "");
      OS_ASSERT(result);
    }

    boost::optional<double> GroundHeatTransferSlabBldgProps_Impl::shapeSlabshape() const {
      return getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::Shape_Slabshape, true);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setShapeSlabshape(double shapeSlabshape) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::Shape_Slabshape, shapeSlabshape);
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetShapeSlabshape() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::Shape_Slabshape, "");
      OS_ASSERT(result);
    }

    boost::optional<double> GroundHeatTransferSlabBldgProps_Impl::hbldgBuildingheight() const {
      return getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::HBLDG_Buildingheight, true);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setHbldgBuildingheight(double hbldgBuildingheight) {
      return setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::HBLDG_Buildingheight, hbldgBuildingheight);
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetHbldgBuildingheight() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::HBLDG_Buildingheight, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin1JanuaryIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN1_JanuaryIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin1JanuaryIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN1_JanuaryIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin1JanuaryIndoorAverageTemperatureSetpoint(double tin1JanuaryIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN1_JanuaryIndoorAverageTemperatureSetpoint,
                                    tin1JanuaryIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin1JanuaryIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN1_JanuaryIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin2FebruaryIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN2_FebruaryIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin2FebruaryIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN2_FebruaryIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin2FebruaryIndoorAverageTemperatureSetpoint(double tin2FebruaryIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN2_FebruaryIndoorAverageTemperatureSetpoint,
                                    tin2FebruaryIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin2FebruaryIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN2_FebruaryIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin3MarchIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN3_MarchIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin3MarchIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN3_MarchIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin3MarchIndoorAverageTemperatureSetpoint(double tin3MarchIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN3_MarchIndoorAverageTemperatureSetpoint,
                                    tin3MarchIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin3MarchIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN3_MarchIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin4AprilIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN4_AprilIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin4AprilIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN4_AprilIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin4AprilIndoorAverageTemperatureSetpoint(double tin4AprilIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN4_AprilIndoorAverageTemperatureSetpoint,
                                    tin4AprilIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin4AprilIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN4_AprilIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin5MayIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN5_MayIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin5MayIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN5_MayIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin5MayIndoorAverageTemperatureSetpoint(double tin5MayIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN5_MayIndoorAverageTemperatureSetpoint,
                                    tin5MayIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin5MayIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN5_MayIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin6JuneIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN6_JuneIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin6JuneIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN6_JuneIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin6JuneIndoorAverageTemperatureSetpoint(double tin6JuneIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN6_JuneIndoorAverageTemperatureSetpoint,
                                    tin6JuneIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin6JuneIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN6_JuneIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin7JulyIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN7_JulyIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin7JulyIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN7_JulyIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin7JulyIndoorAverageTemperatureSetpoint(double tin7JulyIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN7_JulyIndoorAverageTemperatureSetpoint,
                                    tin7JulyIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin7JulyIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN7_JulyIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin8AugustIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN8_AugustIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin8AugustIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN8_AugustIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin8AugustIndoorAverageTemperatureSetpoint(double tin8AugustIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN8_AugustIndoorAverageTemperatureSetpoint,
                                    tin8AugustIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin8AugustIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN8_AugustIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin9SeptemberIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN9_SeptemberIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin9SeptemberIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN9_SeptemberIndoorAverageTemperatureSetpoint);
    }

    bool
      GroundHeatTransferSlabBldgProps_Impl::setTin9SeptemberIndoorAverageTemperatureSetpoint(double tin9SeptemberIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN9_SeptemberIndoorAverageTemperatureSetpoint,
                                    tin9SeptemberIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin9SeptemberIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN9_SeptemberIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin10OctoberIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN10_OctoberIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin10OctoberIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN10_OctoberIndoorAverageTemperatureSetpoint);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTin10OctoberIndoorAverageTemperatureSetpoint(double tin10OctoberIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN10_OctoberIndoorAverageTemperatureSetpoint,
                                    tin10OctoberIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin10OctoberIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN10_OctoberIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin11NovemberIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN11_NovemberIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin11NovemberIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN11_NovemberIndoorAverageTemperatureSetpoint);
    }

    bool
      GroundHeatTransferSlabBldgProps_Impl::setTin11NovemberIndoorAverageTemperatureSetpoint(double tin11NovemberIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN11_NovemberIndoorAverageTemperatureSetpoint,
                                    tin11NovemberIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin11NovemberIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN11_NovemberIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tin12DecemberIndoorAverageTemperatureSetpoint() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN12_DecemberIndoorAverageTemperatureSetpoint, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTin12DecemberIndoorAverageTemperatureSetpointDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN12_DecemberIndoorAverageTemperatureSetpoint);
    }

    bool
      GroundHeatTransferSlabBldgProps_Impl::setTin12DecemberIndoorAverageTemperatureSetpoint(double tin12DecemberIndoorAverageTemperatureSetpoint) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN12_DecemberIndoorAverageTemperatureSetpoint,
                                    tin12DecemberIndoorAverageTemperatureSetpoint);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTin12DecemberIndoorAverageTemperatureSetpoint() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TIN12_DecemberIndoorAverageTemperatureSetpoint, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::tinAmpDailyIndoorsinewavevariationamplitude() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TINAmp_DailyIndoorsinewavevariationamplitude, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isTinAmpDailyIndoorsinewavevariationamplitudeDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TINAmp_DailyIndoorsinewavevariationamplitude);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setTinAmpDailyIndoorsinewavevariationamplitude(double tinAmpDailyIndoorsinewavevariationamplitude) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TINAmp_DailyIndoorsinewavevariationamplitude,
                                    tinAmpDailyIndoorsinewavevariationamplitude);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetTinAmpDailyIndoorsinewavevariationamplitude() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::TINAmp_DailyIndoorsinewavevariationamplitude, "");
      OS_ASSERT(result);
    }

    double GroundHeatTransferSlabBldgProps_Impl::convTolConvergenceTolerance() const {
      const auto value = getDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::ConvTol_ConvergenceTolerance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool GroundHeatTransferSlabBldgProps_Impl::isConvTolConvergenceToleranceDefaulted() const {
      return isEmpty(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::ConvTol_ConvergenceTolerance);
    }

    bool GroundHeatTransferSlabBldgProps_Impl::setConvTolConvergenceTolerance(double convTolConvergenceTolerance) {
      const bool result = setDouble(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::ConvTol_ConvergenceTolerance, convTolConvergenceTolerance);
      OS_ASSERT(result);
      return result;
    }

    void GroundHeatTransferSlabBldgProps_Impl::resetConvTolConvergenceTolerance() {
      const bool result = setString(openstudio::GroundHeatTransfer_Slab_BldgPropsFields::ConvTol_ConvergenceTolerance, "");
      OS_ASSERT(result);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
