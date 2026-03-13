/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEINTEGRALCOLLECTORSTORAGE_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEINTEGRALCOLLECTORSTORAGE_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SolarCollectorPerformanceIntegralCollectorStorage_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SolarCollectorPerformanceIntegralCollectorStorage_Impl() override = default;

      std::string iCSCollectorType() const;
      bool isICSCollectorTypeDefaulted() const;
      bool setICSCollectorType(const std::string& iCSCollectorType);
      void resetICSCollectorType();

      double grossArea() const;
      bool setGrossArea(double grossArea);

      double collectorWaterVolume() const;
      bool setCollectorWaterVolume(double collectorWaterVolume);

      double bottomHeatLossConductance() const;
      bool isBottomHeatLossConductanceDefaulted() const;
      bool setBottomHeatLossConductance(double bottomHeatLossConductance);
      void resetBottomHeatLossConductance();

      double sideHeatLossConductance() const;
      bool isSideHeatLossConductanceDefaulted() const;
      bool setSideHeatLossConductance(double sideHeatLossConductance);
      void resetSideHeatLossConductance();

      double aspectRatio() const;
      bool isAspectRatioDefaulted() const;
      bool setAspectRatio(double aspectRatio);
      void resetAspectRatio();

      double collectorSideHeight() const;
      bool isCollectorSideHeightDefaulted() const;
      bool setCollectorSideHeight(double collectorSideHeight);
      void resetCollectorSideHeight();

      double thermalMassOfAbsorberPlate() const;
      bool isThermalMassOfAbsorberPlateDefaulted() const;
      bool setThermalMassOfAbsorberPlate(double thermalMassOfAbsorberPlate);
      void resetThermalMassOfAbsorberPlate();

      int numberOfCovers() const;
      bool isNumberOfCoversDefaulted() const;
      bool setNumberOfCovers(int numberOfCovers);
      void resetNumberOfCovers();

      double coverSpacing() const;
      bool isCoverSpacingDefaulted() const;
      bool setCoverSpacing(double coverSpacing);
      void resetCoverSpacing();

      double refractiveIndexOfOuterCover() const;
      bool isRefractiveIndexOfOuterCoverDefaulted() const;
      bool setRefractiveIndexOfOuterCover(double refractiveIndexOfOuterCover);
      void resetRefractiveIndexOfOuterCover();

      double extinctionCoefficientTimesThicknessOfOuterCover() const;
      bool isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted() const;
      bool setExtinctionCoefficientTimesThicknessOfOuterCover(double extinctionCoefficientTimesThicknessOfOuterCover);
      void resetExtinctionCoefficientTimesThicknessOfOuterCover();

      double emissivityOfOuterCover() const;
      bool isEmissivityOfOuterCoverDefaulted() const;
      bool setEmissivityOfOuterCover(double emissivityOfOuterCover);
      void resetEmissivityOfOuterCover();

      double refractiveIndexOfInnerCover() const;
      bool isRefractiveIndexOfInnerCoverDefaulted() const;
      bool setRefractiveIndexOfInnerCover(double refractiveIndexOfInnerCover);
      void resetRefractiveIndexOfInnerCover();

      double extinctionCoefficientTimesThicknessOfTheInnerCover() const;
      bool isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted() const;
      bool setExtinctionCoefficientTimesThicknessOfTheInnerCover(double extinctionCoefficientTimesThicknessOfTheInnerCover);
      void resetExtinctionCoefficientTimesThicknessOfTheInnerCover();

      double emissivityOfInnerCover() const;
      bool isEmissivityOfInnerCoverDefaulted() const;
      bool setEmissivityOfInnerCover(double emissivityOfInnerCover);
      void resetEmissivityOfInnerCover();

      double absorptanceOfAbsorberPlate() const;
      bool isAbsorptanceOfAbsorberPlateDefaulted() const;
      bool setAbsorptanceOfAbsorberPlate(double absorptanceOfAbsorberPlate);
      void resetAbsorptanceOfAbsorberPlate();

      double emissivityOfAbsorberPlate() const;
      bool isEmissivityOfAbsorberPlateDefaulted() const;
      bool setEmissivityOfAbsorberPlate(double emissivityOfAbsorberPlate);
      void resetEmissivityOfAbsorberPlate();

      std::vector<std::string> iCSCollectorTypeValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
