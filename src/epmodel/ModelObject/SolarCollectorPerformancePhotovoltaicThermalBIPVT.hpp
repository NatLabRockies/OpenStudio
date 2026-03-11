/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl;
}

class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalBIPVT : public ModelObject
{
 public:
  explicit SolarCollectorPerformancePhotovoltaicThermalBIPVT(const Model& model);

  virtual ~SolarCollectorPerformancePhotovoltaicThermalBIPVT() override = default;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT(const SolarCollectorPerformancePhotovoltaicThermalBIPVT& other) = default;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT(SolarCollectorPerformancePhotovoltaicThermalBIPVT&& other) = default;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT& operator=(const SolarCollectorPerformancePhotovoltaicThermalBIPVT&) = default;
  SolarCollectorPerformancePhotovoltaicThermalBIPVT& operator=(SolarCollectorPerformancePhotovoltaicThermalBIPVT&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::SolarCollectorPerformancePhotovoltaicThermalBIPVT scalar accessor names/signatures.
  // - Field Mapping: Scalar APIs map directly to E+ SolarCollectorPerformance:PhotovoltaicThermal:BIPVT fields.
  // - ForwardTranslator evidence: ForwardTranslateSolarCollectorPerformancePhotovoltaicThermalBIPVT.cpp writes these exact getters to matching IDF fields.
  // - Field Mapping: BoundaryConditionsModelName and AvailabilityScheduleName remain excluded in epmodel scalar scaffold as relationship fields.
  // - TODO(parity): Add relationship APIs incrementally without changing these scalar signatures.
  double effectivePlenumGapThicknessBehindPVModules() const;
  double pVCellNormalTransmittanceAbsorptanceProduct() const;
  double backingMaterialNormalTransmittanceAbsorptanceProduct() const;
  double claddingNormalTransmittanceAbsorptanceProduct() const;
  double fractionofCollectorGrossAreaCoveredbyPVModule() const;
  double fractionofPVCellAreatoPVModuleArea() const;
  double pVModuleTopThermalResistance() const;
  double pVModuleBottomThermalResistance() const;
  double pVModuleFrontLongwaveEmissivity() const;
  double pVModuleBackLongwaveEmissivity() const;
  double glassThickness() const;
  double glassRefractionIndex() const;
  double glassExtinctionCoefficient() const;

  bool setEffectivePlenumGapThicknessBehindPVModules(double effectivePlenumGapThicknessBehindPVModules);
  bool setPVCellNormalTransmittanceAbsorptanceProduct(double pVCellNormalTransmittanceAbsorptanceProduct);
  bool setBackingMaterialNormalTransmittanceAbsorptanceProduct(double backingMaterialNormalTransmittanceAbsorptanceProduct);
  bool setCladdingNormalTransmittanceAbsorptanceProduct(double claddingNormalTransmittanceAbsorptanceProduct);
  bool setFractionofCollectorGrossAreaCoveredbyPVModule(double fractionofCollectorGrossAreaCoveredbyPVModule);
  bool setFractionofPVCellAreatoPVModuleArea(double fractionofPVCellAreatoPVModuleArea);
  bool setPVModuleTopThermalResistance(double pVModuleTopThermalResistance);
  bool setPVModuleBottomThermalResistance(double pVModuleBottomThermalResistance);
  bool setPVModuleFrontLongwaveEmissivity(double pVModuleFrontLongwaveEmissivity);
  bool setPVModuleBackLongwaveEmissivity(double pVModuleBackLongwaveEmissivity);
  bool setGlassThickness(double glassThickness);
  bool setGlassRefractionIndex(double glassRefractionIndex);
  bool setGlassExtinctionCoefficient(double glassExtinctionCoefficient);

 protected:
  using ImplType = detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SolarCollectorPerformancePhotovoltaicThermalBIPVT(
    std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
