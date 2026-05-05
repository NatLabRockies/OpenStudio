/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIRED_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIRED_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SolarCollectorUnglazedTranspired_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SolarCollectorUnglazedTranspired_Impl() override = default;

      double diameterofPerforationsinCollector() const;
      bool setDiameterofPerforationsinCollector(double diameterofPerforationsinCollector);

      double distanceBetweenPerforationsinCollector() const;
      bool setDistanceBetweenPerforationsinCollector(double distanceBetweenPerforationsinCollector);

      double thermalEmissivityofCollectorSurface() const;
      bool setThermalEmissivityofCollectorSurface(double thermalEmissivityofCollectorSurface);

      double solarAbsorbtivityofCollectorSurface() const;
      bool setSolarAbsorbtivityofCollectorSurface(double solarAbsorbtivityofCollectorSurface);

      double effectiveOverallHeightofCollector() const;
      bool setEffectiveOverallHeightofCollector(double effectiveOverallHeightofCollector);

      double effectiveGapThicknessofPlenumBehindCollector() const;
      bool setEffectiveGapThicknessofPlenumBehindCollector(double effectiveGapThicknessofPlenumBehindCollector);

      double effectiveCrossSectionAreaofPlenumBehindCollector() const;
      bool setEffectiveCrossSectionAreaofPlenumBehindCollector(double effectiveCrossSectionAreaofPlenumBehindCollector);

      std::string holeLayoutPatternforPitch() const;
      bool setHoleLayoutPatternforPitch(const std::string& holeLayoutPatternforPitch);
      bool isHoleLayoutPatternforPitchDefaulted() const;
      void resetHoleLayoutPatternforPitch();

      std::string heatExchangeEffectivenessCorrelation() const;
      bool setHeatExchangeEffectivenessCorrelation(const std::string& heatExchangeEffectivenessCorrelation);
      bool isHeatExchangeEffectivenessCorrelationDefaulted() const;
      void resetHeatExchangeEffectivenessCorrelation();

      double ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea() const;
      bool setRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea(double ratioofActualCollectorSurfaceAreatoProjectedSurfaceArea);
      bool isRatioofActualCollectorSurfaceAreatoProjectedSurfaceAreaDefaulted() const;
      void resetRatioofActualCollectorSurfaceAreatoProjectedSurfaceArea();

      std::string roughnessofCollector() const;
      bool setRoughnessofCollector(const std::string& roughnessofCollector);

      boost::optional<double> collectorThickness() const;
      bool setCollectorThickness(double collectorThickness);
      void resetCollectorThickness();

      double effectivenessforPerforationswithRespecttoWind() const;
      bool setEffectivenessforPerforationswithRespecttoWind(double effectivenessforPerforationswithRespecttoWind);
      bool isEffectivenessforPerforationswithRespecttoWindDefaulted() const;
      void resetEffectivenessforPerforationswithRespecttoWind();

      double dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow() const;
      bool setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(double dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
      bool isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted() const;
      void resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow();

      std::vector<std::string> holeLayoutPatternforPitchValues() const;
      std::vector<std::string> heatExchangeEffectivenessCorrelationValues() const;
      std::vector<std::string> roughnessofCollectorValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
