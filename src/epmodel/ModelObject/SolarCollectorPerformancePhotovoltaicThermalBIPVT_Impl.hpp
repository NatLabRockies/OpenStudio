/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_IMPL_HPP
#define EPMODEL_SOLARCOLLECTORPERFORMANCEPHOTOVOLTAICTHERMALBIPVT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl() override = default;

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
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
