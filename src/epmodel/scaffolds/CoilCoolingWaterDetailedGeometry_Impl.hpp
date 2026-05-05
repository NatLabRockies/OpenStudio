/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_COILCOOLINGWATERDETAILEDGEOMETRY_IMPL_HPP
#define EPMODEL_COILCOOLINGWATERDETAILEDGEOMETRY_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API CoilCoolingWaterDetailedGeometry_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~CoilCoolingWaterDetailedGeometry_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
