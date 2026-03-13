/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEINTEGRALCOLLECTORSTORAGE_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEINTEGRALCOLLECTORSTORAGE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SolarCollectorPerformanceIntegralCollectorStorage_Impl;
  }

  class EPMODEL_API SolarCollectorPerformanceIntegralCollectorStorage : public ModelObject
  {
   public:
    explicit SolarCollectorPerformanceIntegralCollectorStorage(const Model& model);

    virtual ~SolarCollectorPerformanceIntegralCollectorStorage() override = default;
    SolarCollectorPerformanceIntegralCollectorStorage(const SolarCollectorPerformanceIntegralCollectorStorage& other) = default;
    SolarCollectorPerformanceIntegralCollectorStorage(SolarCollectorPerformanceIntegralCollectorStorage&& other) = default;
    SolarCollectorPerformanceIntegralCollectorStorage& operator=(const SolarCollectorPerformanceIntegralCollectorStorage&) = default;
    SolarCollectorPerformanceIntegralCollectorStorage& operator=(SolarCollectorPerformanceIntegralCollectorStorage&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> iCSCollectorTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::SolarCollectorPerformanceIntegralCollectorStorage scalar accessor names/signatures, including iCS/ICS naming.
    // - Field Mapping: All scalar APIs map directly to E+ SolarCollectorPerformance:IntegralCollectorStorage fields.
    // - ForwardTranslator evidence: ForwardTranslateSolarCollectorPerformanceIntegralCollectorStorage.cpp writes these exact getters to matching IDF fields.
    // - TODO(parity): Keep scalar parity stable while relationship/extensible behavior is added separately.
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

   protected:
    using ImplType = detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SolarCollectorPerformanceIntegralCollectorStorage(std::shared_ptr<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
