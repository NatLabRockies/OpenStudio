/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_IMPL_HPP
#define EPMODEL_GROUNDHEATEXCHANGERHORIZONTALTRENCH_IMPL_HPP

#include "StraightComponent/StraightComponent_Impl.hpp"

namespace openstudio {
namespace epmodel {
  class ModelObject;
  namespace detail {

    class EPMODEL_API GroundHeatExchangerHorizontalTrench_Impl : public StraightComponent_Impl
    {
     public:
      using StraightComponent_Impl::StraightComponent_Impl;
      virtual ~GroundHeatExchangerHorizontalTrench_Impl() override = default;

      unsigned inletPort() const override;
      unsigned outletPort() const override;
      bool addToNode(Node& node) override;

      double designFlowRate() const;
      bool setDesignFlowRate(double designFlowRate);

      double trenchLengthinPipeAxialDirection() const;
      bool setTrenchLengthinPipeAxialDirection(double trenchLengthinPipeAxialDirection);

      int numberofTrenches() const;
      bool setNumberofTrenches(int numberofTrenches);

      double horizontalSpacingBetweenPipes() const;
      bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);

      double pipeInnerDiameter() const;
      bool setPipeInnerDiameter(double pipeInnerDiameter);

      double pipeOuterDiameter() const;
      bool setPipeOuterDiameter(double pipeOuterDiameter);

      double burialDepth() const;
      bool setBurialDepth(double burialDepth);

      double soilThermalConductivity() const;
      bool setSoilThermalConductivity(double soilThermalConductivity);

      double soilDensity() const;
      bool setSoilDensity(double soilDensity);

      double soilSpecificHeat() const;
      bool setSoilSpecificHeat(double soilSpecificHeat);

      double pipeThermalConductivity() const;
      bool setPipeThermalConductivity(double pipeThermalConductivity);

      double pipeDensity() const;
      bool setPipeDensity(double pipeDensity);

      double pipeSpecificHeat() const;
      bool setPipeSpecificHeat(double pipeSpecificHeat);

      double soilMoistureContentPercent() const;
      bool setSoilMoistureContentPercent(double soilMoistureContentPercent);

      double soilMoistureContentPercentatSaturation() const;
      bool setSoilMoistureContentPercentatSaturation(double soilMoistureContentPercentatSaturation);

      double evapotranspirationGroundCoverParameter() const;
      bool setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter);

      ModelObject undisturbedGroundTemperatureModel() const;
      bool setUndisturbedGroundTemperatureModel(const ModelObject& undisturbedGroundTemperatureModel);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
