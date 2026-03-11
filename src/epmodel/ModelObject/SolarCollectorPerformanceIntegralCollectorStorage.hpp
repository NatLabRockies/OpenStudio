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

  double grossArea() const;
  double collectorWaterVolume() const;

  double bottomHeatLossConductance() const;
  bool isBottomHeatLossConductanceDefaulted() const;

  double sideHeatLossConductance() const;
  bool isSideHeatLossConductanceDefaulted() const;

  double aspectRatio() const;
  bool isAspectRatioDefaulted() const;

  double collectorSideHeight() const;
  bool isCollectorSideHeightDefaulted() const;

  double thermalMassOfAbsorberPlate() const;
  bool isThermalMassOfAbsorberPlateDefaulted() const;

  int numberOfCovers() const;
  bool isNumberOfCoversDefaulted() const;

  double coverSpacing() const;
  bool isCoverSpacingDefaulted() const;

  double refractiveIndexOfOuterCover() const;
  bool isRefractiveIndexOfOuterCoverDefaulted() const;

  double extinctionCoefficientTimesThicknessOfOuterCover() const;
  bool isExtinctionCoefficientTimesThicknessOfOuterCoverDefaulted() const;

  double emissivityOfOuterCover() const;
  bool isEmissivityOfOuterCoverDefaulted() const;

  double refractiveIndexOfInnerCover() const;
  bool isRefractiveIndexOfInnerCoverDefaulted() const;

  double extinctionCoefficientTimesThicknessOfTheInnerCover() const;
  bool isExtinctionCoefficientTimesThicknessOfTheInnerCoverDefaulted() const;

  double emissivityOfInnerCover() const;
  bool isEmissivityOfInnerCoverDefaulted() const;

  double absorptanceOfAbsorberPlate() const;
  bool isAbsorptanceOfAbsorberPlateDefaulted() const;

  double emissivityOfAbsorberPlate() const;
  bool isEmissivityOfAbsorberPlateDefaulted() const;

  bool setICSCollectorType(const std::string& iCSCollectorType);
  void resetICSCollectorType();

  bool setGrossArea(double grossArea);
  bool setCollectorWaterVolume(double collectorWaterVolume);

  bool setBottomHeatLossConductance(double bottomHeatLossConductance);
  void resetBottomHeatLossConductance();

  bool setSideHeatLossConductance(double sideHeatLossConductance);
  void resetSideHeatLossConductance();

  bool setAspectRatio(double aspectRatio);
  void resetAspectRatio();

  bool setCollectorSideHeight(double collectorSideHeight);
  void resetCollectorSideHeight();

  bool setThermalMassOfAbsorberPlate(double thermalMassOfAbsorberPlate);
  void resetThermalMassOfAbsorberPlate();

  bool setNumberOfCovers(int numberOfCovers);
  void resetNumberOfCovers();

  bool setCoverSpacing(double coverSpacing);
  void resetCoverSpacing();

  bool setRefractiveIndexOfOuterCover(double refractiveIndexOfOuterCover);
  void resetRefractiveIndexOfOuterCover();

  bool setExtinctionCoefficientTimesThicknessOfOuterCover(double extinctionCoefficientTimesThicknessOfOuterCover);
  void resetExtinctionCoefficientTimesThicknessOfOuterCover();

  bool setEmissivityOfOuterCover(double emissivityOfOuterCover);
  void resetEmissivityOfOuterCover();

  bool setRefractiveIndexOfInnerCover(double refractiveIndexOfInnerCover);
  void resetRefractiveIndexOfInnerCover();

  bool setExtinctionCoefficientTimesThicknessOfTheInnerCover(double extinctionCoefficientTimesThicknessOfTheInnerCover);
  void resetExtinctionCoefficientTimesThicknessOfTheInnerCover();

  bool setEmissivityOfInnerCover(double emissivityOfInnerCover);
  void resetEmissivityOfInnerCover();

  bool setAbsorptanceOfAbsorberPlate(double absorptanceOfAbsorberPlate);
  void resetAbsorptanceOfAbsorberPlate();

  bool setEmissivityOfAbsorberPlate(double emissivityOfAbsorberPlate);
  void resetEmissivityOfAbsorberPlate();

 protected:
  using ImplType = detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorPerformanceIntegralCollectorStorage(
    std::shared_ptr<detail::SolarCollectorPerformanceIntegralCollectorStorage_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
