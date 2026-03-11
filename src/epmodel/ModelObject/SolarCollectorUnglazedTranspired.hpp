/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIRED_HPP
#define EPMODEL_SOLARCOLLECTORUNGLAZEDTRANSPIRED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorUnglazedTranspired_Impl;
}

class EPMODEL_API SolarCollectorUnglazedTranspired : public ModelObject
{
 public:
  explicit SolarCollectorUnglazedTranspired(const Model& model);

  virtual ~SolarCollectorUnglazedTranspired() override = default;
  SolarCollectorUnglazedTranspired(const SolarCollectorUnglazedTranspired& other) = default;
  SolarCollectorUnglazedTranspired(SolarCollectorUnglazedTranspired&& other) = default;
  SolarCollectorUnglazedTranspired& operator=(const SolarCollectorUnglazedTranspired&) = default;
  SolarCollectorUnglazedTranspired& operator=(SolarCollectorUnglazedTranspired&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> holeLayoutPatternforPitchValues();
  static std::vector<std::string> heatExchangeEffectivenessCorrelationValues();
  static std::vector<std::string> roughnessofCollectorValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to SolarCollector:UnglazedTranspired numeric/choice fields.
  // - Field Mapping: Boundary Conditions Model Name, schedule names, node names, and extensible Surface N Name links are excluded as relationship fields.
  // - TODO(parity): Add relationship/extensible field APIs after scalar saturation without changing scalar signatures.
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
  bool setDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow(
    double dischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow);
  bool isDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlowDefaulted() const;
  void resetDischargeCoefficientforOpeningswithRespecttoBuoyancyDrivenFlow();

 protected:
  using ImplType = detail::SolarCollectorUnglazedTranspired_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorUnglazedTranspired(std::shared_ptr<detail::SolarCollectorUnglazedTranspired_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
