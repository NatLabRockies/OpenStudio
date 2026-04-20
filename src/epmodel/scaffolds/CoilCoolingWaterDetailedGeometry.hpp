/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERDETAILEDGEOMETRY_HPP
#define EPMODEL_COILCOOLINGWATERDETAILEDGEOMETRY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class CoilCoolingWaterDetailedGeometry_Impl;
}

class EPMODEL_API CoilCoolingWaterDetailedGeometry : public ModelObject
{
 public:
  explicit CoilCoolingWaterDetailedGeometry(const Model& model);

  virtual ~CoilCoolingWaterDetailedGeometry() override = default;
  CoilCoolingWaterDetailedGeometry(const CoilCoolingWaterDetailedGeometry& other) = default;
  CoilCoolingWaterDetailedGeometry(CoilCoolingWaterDetailedGeometry&& other) = default;
  CoilCoolingWaterDetailedGeometry& operator=(const CoilCoolingWaterDetailedGeometry&) = default;
  CoilCoolingWaterDetailedGeometry& operator=(CoilCoolingWaterDetailedGeometry&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart epmodel type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to EnergyPlus Coil:Cooling:Water:DetailedGeometry numeric fields.
  // - Field Mapping: Availability Schedule Name, Water/Air Inlet/Outlet Node Name, and
  //   Condensate Collection Water Storage Tank Name are relationship-like fields and excluded.
  // - TODO(parity): Add relationship APIs after scalar scaffold saturation.
  boost::optional<double> maximumWaterFlowRate() const;
  bool setMaximumWaterFlowRate(double maximumWaterFlowRate);
  bool isMaximumWaterFlowRateAutosized() const;
  void autosizeMaximumWaterFlowRate();
  void resetMaximumWaterFlowRate();

  boost::optional<double> tubeOutsideSurfaceArea() const;
  bool setTubeOutsideSurfaceArea(double tubeOutsideSurfaceArea);
  bool isTubeOutsideSurfaceAreaAutosized() const;
  void autosizeTubeOutsideSurfaceArea();
  void resetTubeOutsideSurfaceArea();

  boost::optional<double> totalTubeInsideArea() const;
  bool setTotalTubeInsideArea(double totalTubeInsideArea);
  bool isTotalTubeInsideAreaAutosized() const;
  void autosizeTotalTubeInsideArea();
  void resetTotalTubeInsideArea();

  boost::optional<double> finSurfaceArea() const;
  bool setFinSurfaceArea(double finSurfaceArea);
  bool isFinSurfaceAreaAutosized() const;
  void autosizeFinSurfaceArea();
  void resetFinSurfaceArea();

  boost::optional<double> minimumAirflowArea() const;
  bool setMinimumAirflowArea(double minimumAirflowArea);
  bool isMinimumAirflowAreaAutosized() const;
  void autosizeMinimumAirflowArea();
  void resetMinimumAirflowArea();

  boost::optional<double> coilDepth() const;
  bool setCoilDepth(double coilDepth);
  bool isCoilDepthAutosized() const;
  void autosizeCoilDepth();
  void resetCoilDepth();

  boost::optional<double> finDiameter() const;
  bool setFinDiameter(double finDiameter);
  bool isFinDiameterAutosized() const;
  void autosizeFinDiameter();
  void resetFinDiameter();

  double finThickness() const;
  bool isFinThicknessDefaulted() const;
  bool setFinThickness(double finThickness);
  void resetFinThickness();

  double tubeInsideDiameter() const;
  bool isTubeInsideDiameterDefaulted() const;
  bool setTubeInsideDiameter(double tubeInsideDiameter);
  void resetTubeInsideDiameter();

  double tubeOutsideDiameter() const;
  bool isTubeOutsideDiameterDefaulted() const;
  bool setTubeOutsideDiameter(double tubeOutsideDiameter);
  void resetTubeOutsideDiameter();

  double tubeThermalConductivity() const;
  bool isTubeThermalConductivityDefaulted() const;
  bool setTubeThermalConductivity(double tubeThermalConductivity);
  void resetTubeThermalConductivity();

  double finThermalConductivity() const;
  bool isFinThermalConductivityDefaulted() const;
  bool setFinThermalConductivity(double finThermalConductivity);
  void resetFinThermalConductivity();

  double finSpacing() const;
  bool isFinSpacingDefaulted() const;
  bool setFinSpacing(double finSpacing);
  void resetFinSpacing();

  double tubeDepthSpacing() const;
  bool isTubeDepthSpacingDefaulted() const;
  bool setTubeDepthSpacing(double tubeDepthSpacing);
  void resetTubeDepthSpacing();

  double numberofTubeRows() const;
  bool isNumberofTubeRowsDefaulted() const;
  bool setNumberofTubeRows(double numberofTubeRows);
  void resetNumberofTubeRows();

  boost::optional<double> numberofTubesperRow() const;
  bool setNumberofTubesperRow(double numberofTubesperRow);
  bool isNumberofTubesperRowAutosized() const;
  void autosizeNumberofTubesperRow();
  void resetNumberofTubesperRow();

  boost::optional<double> designWaterTemperatureDifference() const;
  bool setDesignWaterTemperatureDifference(double designWaterTemperatureDifference);
  void resetDesignWaterTemperatureDifference();

  boost::optional<double> designInletWaterTemperature() const;
  bool setDesignInletWaterTemperature(double designInletWaterTemperature);
  bool isDesignInletWaterTemperatureAutosized() const;
  void autosizeDesignInletWaterTemperature();
  void resetDesignInletWaterTemperature();

 protected:
  using ImplType = detail::CoilCoolingWaterDetailedGeometry_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit CoilCoolingWaterDetailedGeometry(std::shared_ptr<detail::CoilCoolingWaterDetailedGeometry_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
