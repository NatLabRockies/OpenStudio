/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "CoilCoolingWaterDetailedGeometry.hpp"
#include "CoilCoolingWaterDetailedGeometry_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/Coil_Cooling_Water_DetailedGeometry_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

  CoilCoolingWaterDetailedGeometry::CoilCoolingWaterDetailedGeometry(const Model& model)
    : ModelObject(CoilCoolingWaterDetailedGeometry::iddObjectType(), model) {}

  CoilCoolingWaterDetailedGeometry::CoilCoolingWaterDetailedGeometry(std::shared_ptr<detail::CoilCoolingWaterDetailedGeometry_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType CoilCoolingWaterDetailedGeometry::iddObjectType() {
    return IddObjectType::Coil_Cooling_Water_DetailedGeometry;
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::maximumWaterFlowRate() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->maximumWaterFlowRate();
  }

  bool CoilCoolingWaterDetailedGeometry::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setMaximumWaterFlowRate(maximumWaterFlowRate);
  }

  bool CoilCoolingWaterDetailedGeometry::isMaximumWaterFlowRateAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isMaximumWaterFlowRateAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeMaximumWaterFlowRate() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeMaximumWaterFlowRate();
  }

  void CoilCoolingWaterDetailedGeometry::resetMaximumWaterFlowRate() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetMaximumWaterFlowRate();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::tubeOutsideSurfaceArea() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->tubeOutsideSurfaceArea();
  }

  bool CoilCoolingWaterDetailedGeometry::setTubeOutsideSurfaceArea(double tubeOutsideSurfaceArea) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTubeOutsideSurfaceArea(tubeOutsideSurfaceArea);
  }

  bool CoilCoolingWaterDetailedGeometry::isTubeOutsideSurfaceAreaAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTubeOutsideSurfaceAreaAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeTubeOutsideSurfaceArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeTubeOutsideSurfaceArea();
  }

  void CoilCoolingWaterDetailedGeometry::resetTubeOutsideSurfaceArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTubeOutsideSurfaceArea();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::totalTubeInsideArea() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->totalTubeInsideArea();
  }

  bool CoilCoolingWaterDetailedGeometry::setTotalTubeInsideArea(double totalTubeInsideArea) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTotalTubeInsideArea(totalTubeInsideArea);
  }

  bool CoilCoolingWaterDetailedGeometry::isTotalTubeInsideAreaAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTotalTubeInsideAreaAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeTotalTubeInsideArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeTotalTubeInsideArea();
  }

  void CoilCoolingWaterDetailedGeometry::resetTotalTubeInsideArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTotalTubeInsideArea();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::finSurfaceArea() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->finSurfaceArea();
  }

  bool CoilCoolingWaterDetailedGeometry::setFinSurfaceArea(double finSurfaceArea) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setFinSurfaceArea(finSurfaceArea);
  }

  bool CoilCoolingWaterDetailedGeometry::isFinSurfaceAreaAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isFinSurfaceAreaAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeFinSurfaceArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeFinSurfaceArea();
  }

  void CoilCoolingWaterDetailedGeometry::resetFinSurfaceArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetFinSurfaceArea();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::minimumAirflowArea() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->minimumAirflowArea();
  }

  bool CoilCoolingWaterDetailedGeometry::setMinimumAirflowArea(double minimumAirflowArea) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setMinimumAirflowArea(minimumAirflowArea);
  }

  bool CoilCoolingWaterDetailedGeometry::isMinimumAirflowAreaAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isMinimumAirflowAreaAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeMinimumAirflowArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeMinimumAirflowArea();
  }

  void CoilCoolingWaterDetailedGeometry::resetMinimumAirflowArea() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetMinimumAirflowArea();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::coilDepth() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->coilDepth();
  }

  bool CoilCoolingWaterDetailedGeometry::setCoilDepth(double coilDepth) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setCoilDepth(coilDepth);
  }

  bool CoilCoolingWaterDetailedGeometry::isCoilDepthAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isCoilDepthAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeCoilDepth() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeCoilDepth();
  }

  void CoilCoolingWaterDetailedGeometry::resetCoilDepth() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetCoilDepth();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::finDiameter() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->finDiameter();
  }

  bool CoilCoolingWaterDetailedGeometry::setFinDiameter(double finDiameter) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setFinDiameter(finDiameter);
  }

  bool CoilCoolingWaterDetailedGeometry::isFinDiameterAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isFinDiameterAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeFinDiameter() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeFinDiameter();
  }

  void CoilCoolingWaterDetailedGeometry::resetFinDiameter() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetFinDiameter();
  }

  double CoilCoolingWaterDetailedGeometry::finThickness() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->finThickness();
  }

  bool CoilCoolingWaterDetailedGeometry::isFinThicknessDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isFinThicknessDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setFinThickness(double finThickness) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setFinThickness(finThickness);
  }

  void CoilCoolingWaterDetailedGeometry::resetFinThickness() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetFinThickness();
  }

  double CoilCoolingWaterDetailedGeometry::tubeInsideDiameter() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->tubeInsideDiameter();
  }

  bool CoilCoolingWaterDetailedGeometry::isTubeInsideDiameterDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTubeInsideDiameterDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setTubeInsideDiameter(double tubeInsideDiameter) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTubeInsideDiameter(tubeInsideDiameter);
  }

  void CoilCoolingWaterDetailedGeometry::resetTubeInsideDiameter() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTubeInsideDiameter();
  }

  double CoilCoolingWaterDetailedGeometry::tubeOutsideDiameter() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->tubeOutsideDiameter();
  }

  bool CoilCoolingWaterDetailedGeometry::isTubeOutsideDiameterDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTubeOutsideDiameterDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setTubeOutsideDiameter(double tubeOutsideDiameter) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTubeOutsideDiameter(tubeOutsideDiameter);
  }

  void CoilCoolingWaterDetailedGeometry::resetTubeOutsideDiameter() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTubeOutsideDiameter();
  }

  double CoilCoolingWaterDetailedGeometry::tubeThermalConductivity() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->tubeThermalConductivity();
  }

  bool CoilCoolingWaterDetailedGeometry::isTubeThermalConductivityDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTubeThermalConductivityDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setTubeThermalConductivity(double tubeThermalConductivity) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTubeThermalConductivity(tubeThermalConductivity);
  }

  void CoilCoolingWaterDetailedGeometry::resetTubeThermalConductivity() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTubeThermalConductivity();
  }

  double CoilCoolingWaterDetailedGeometry::finThermalConductivity() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->finThermalConductivity();
  }

  bool CoilCoolingWaterDetailedGeometry::isFinThermalConductivityDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isFinThermalConductivityDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setFinThermalConductivity(double finThermalConductivity) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setFinThermalConductivity(finThermalConductivity);
  }

  void CoilCoolingWaterDetailedGeometry::resetFinThermalConductivity() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetFinThermalConductivity();
  }

  double CoilCoolingWaterDetailedGeometry::finSpacing() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->finSpacing();
  }

  bool CoilCoolingWaterDetailedGeometry::isFinSpacingDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isFinSpacingDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setFinSpacing(double finSpacing) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setFinSpacing(finSpacing);
  }

  void CoilCoolingWaterDetailedGeometry::resetFinSpacing() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetFinSpacing();
  }

  double CoilCoolingWaterDetailedGeometry::tubeDepthSpacing() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->tubeDepthSpacing();
  }

  bool CoilCoolingWaterDetailedGeometry::isTubeDepthSpacingDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isTubeDepthSpacingDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setTubeDepthSpacing(double tubeDepthSpacing) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setTubeDepthSpacing(tubeDepthSpacing);
  }

  void CoilCoolingWaterDetailedGeometry::resetTubeDepthSpacing() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetTubeDepthSpacing();
  }

  double CoilCoolingWaterDetailedGeometry::numberofTubeRows() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->numberofTubeRows();
  }

  bool CoilCoolingWaterDetailedGeometry::isNumberofTubeRowsDefaulted() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isNumberofTubeRowsDefaulted();
  }

  bool CoilCoolingWaterDetailedGeometry::setNumberofTubeRows(double numberofTubeRows) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setNumberofTubeRows(numberofTubeRows);
  }

  void CoilCoolingWaterDetailedGeometry::resetNumberofTubeRows() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetNumberofTubeRows();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::numberofTubesperRow() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->numberofTubesperRow();
  }

  bool CoilCoolingWaterDetailedGeometry::setNumberofTubesperRow(double numberofTubesperRow) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setNumberofTubesperRow(numberofTubesperRow);
  }

  bool CoilCoolingWaterDetailedGeometry::isNumberofTubesperRowAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isNumberofTubesperRowAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeNumberofTubesperRow() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeNumberofTubesperRow();
  }

  void CoilCoolingWaterDetailedGeometry::resetNumberofTubesperRow() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetNumberofTubesperRow();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::designWaterTemperatureDifference() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->designWaterTemperatureDifference();
  }

  bool CoilCoolingWaterDetailedGeometry::setDesignWaterTemperatureDifference(double designWaterTemperatureDifference) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setDesignWaterTemperatureDifference(designWaterTemperatureDifference);
  }

  void CoilCoolingWaterDetailedGeometry::resetDesignWaterTemperatureDifference() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetDesignWaterTemperatureDifference();
  }

  boost::optional<double> CoilCoolingWaterDetailedGeometry::designInletWaterTemperature() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->designInletWaterTemperature();
  }

  bool CoilCoolingWaterDetailedGeometry::setDesignInletWaterTemperature(double designInletWaterTemperature) {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->setDesignInletWaterTemperature(designInletWaterTemperature);
  }

  bool CoilCoolingWaterDetailedGeometry::isDesignInletWaterTemperatureAutosized() const {
    return getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->isDesignInletWaterTemperatureAutosized();
  }

  void CoilCoolingWaterDetailedGeometry::autosizeDesignInletWaterTemperature() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->autosizeDesignInletWaterTemperature();
  }

  void CoilCoolingWaterDetailedGeometry::resetDesignInletWaterTemperature() {
    getImpl<detail::CoilCoolingWaterDetailedGeometry_Impl>()->resetDesignInletWaterTemperature();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::maximumWaterFlowRate() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setMaximumWaterFlowRate(double maximumWaterFlowRate) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, maximumWaterFlowRate);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isMaximumWaterFlowRateAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeMaximumWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetMaximumWaterFlowRate() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MaximumWaterFlowRate, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::tubeOutsideSurfaceArea() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTubeOutsideSurfaceArea(double tubeOutsideSurfaceArea) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, tubeOutsideSurfaceArea);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTubeOutsideSurfaceAreaAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeTubeOutsideSurfaceArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTubeOutsideSurfaceArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideSurfaceArea, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::totalTubeInsideArea() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTotalTubeInsideArea(double totalTubeInsideArea) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, totalTubeInsideArea);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTotalTubeInsideAreaAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeTotalTubeInsideArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTotalTubeInsideArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TotalTubeInsideArea, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::finSurfaceArea() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setFinSurfaceArea(double finSurfaceArea) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, finSurfaceArea);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isFinSurfaceAreaAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeFinSurfaceArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetFinSurfaceArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSurfaceArea, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::minimumAirflowArea() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setMinimumAirflowArea(double minimumAirflowArea) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, minimumAirflowArea);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isMinimumAirflowAreaAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeMinimumAirflowArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetMinimumAirflowArea() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::MinimumAirflowArea, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::coilDepth() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setCoilDepth(double coilDepth) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, coilDepth);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isCoilDepthAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeCoilDepth() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetCoilDepth() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::CoilDepth, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::finDiameter() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setFinDiameter(double finDiameter) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, finDiameter);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isFinDiameterAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeFinDiameter() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetFinDiameter() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinDiameter, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::finThickness() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isFinThicknessDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThickness);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setFinThickness(double finThickness) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThickness, finThickness);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetFinThickness() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThickness, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::tubeInsideDiameter() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeInsideDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTubeInsideDiameterDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeInsideDiameter);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTubeInsideDiameter(double tubeInsideDiameter) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeInsideDiameter, tubeInsideDiameter);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTubeInsideDiameter() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeInsideDiameter, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::tubeOutsideDiameter() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideDiameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTubeOutsideDiameterDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideDiameter);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTubeOutsideDiameter(double tubeOutsideDiameter) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideDiameter, tubeOutsideDiameter);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTubeOutsideDiameter() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeOutsideDiameter, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::tubeThermalConductivity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTubeThermalConductivityDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeThermalConductivity);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTubeThermalConductivity(double tubeThermalConductivity) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeThermalConductivity, tubeThermalConductivity);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTubeThermalConductivity() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeThermalConductivity, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::finThermalConductivity() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isFinThermalConductivityDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThermalConductivity);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setFinThermalConductivity(double finThermalConductivity) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThermalConductivity, finThermalConductivity);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetFinThermalConductivity() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinThermalConductivity, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::finSpacing() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSpacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isFinSpacingDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSpacing);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setFinSpacing(double finSpacing) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSpacing, finSpacing);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetFinSpacing() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::FinSpacing, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::tubeDepthSpacing() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeDepthSpacing, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isTubeDepthSpacingDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeDepthSpacing);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setTubeDepthSpacing(double tubeDepthSpacing) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeDepthSpacing, tubeDepthSpacing);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetTubeDepthSpacing() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::TubeDepthSpacing, ""));
    }

    double CoilCoolingWaterDetailedGeometry_Impl::numberofTubeRows() const {
      const auto value = getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubeRows, true);
      OS_ASSERT(value);
      return *value;
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isNumberofTubeRowsDefaulted() const {
      return isEmpty(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubeRows);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setNumberofTubeRows(double numberofTubeRows) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubeRows, numberofTubeRows);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetNumberofTubeRows() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubeRows, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::numberofTubesperRow() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setNumberofTubesperRow(double numberofTubesperRow) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, numberofTubesperRow);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isNumberofTubesperRowAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeNumberofTubesperRow() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetNumberofTubesperRow() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::NumberofTubesperRow, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::designWaterTemperatureDifference() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignWaterTemperatureDifference, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setDesignWaterTemperatureDifference(double designWaterTemperatureDifference) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignWaterTemperatureDifference, designWaterTemperatureDifference);
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetDesignWaterTemperatureDifference() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignWaterTemperatureDifference, ""));
    }

    boost::optional<double> CoilCoolingWaterDetailedGeometry_Impl::designInletWaterTemperature() const {
      return getDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignInletWaterTemperature, true);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::setDesignInletWaterTemperature(double designInletWaterTemperature) {
      return setDouble(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignInletWaterTemperature, designInletWaterTemperature);
    }

    bool CoilCoolingWaterDetailedGeometry_Impl::isDesignInletWaterTemperatureAutosized() const {
      if (const auto value = getString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignInletWaterTemperature, true)) {
        return openstudio::istringEqual(*value, "autosize");
      }
      return false;
    }

    void CoilCoolingWaterDetailedGeometry_Impl::autosizeDesignInletWaterTemperature() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignInletWaterTemperature, "autosize"));
    }

    void CoilCoolingWaterDetailedGeometry_Impl::resetDesignInletWaterTemperature() {
      OS_ASSERT(setString(openstudio::Coil_Cooling_Water_DetailedGeometryFields::DesignInletWaterTemperature, ""));
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
