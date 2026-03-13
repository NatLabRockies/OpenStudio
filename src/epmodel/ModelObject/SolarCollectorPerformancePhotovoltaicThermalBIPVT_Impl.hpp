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
      bool setEffectivePlenumGapThicknessBehindPVModules(double effectivePlenumGapThicknessBehindPVModules);

      double pVCellNormalTransmittanceAbsorptanceProduct() const;
      bool setPVCellNormalTransmittanceAbsorptanceProduct(double pVCellNormalTransmittanceAbsorptanceProduct);

      double backingMaterialNormalTransmittanceAbsorptanceProduct() const;
      bool setBackingMaterialNormalTransmittanceAbsorptanceProduct(double backingMaterialNormalTransmittanceAbsorptanceProduct);

      double claddingNormalTransmittanceAbsorptanceProduct() const;
      bool setCladdingNormalTransmittanceAbsorptanceProduct(double claddingNormalTransmittanceAbsorptanceProduct);

      double fractionofCollectorGrossAreaCoveredbyPVModule() const;
      bool setFractionofCollectorGrossAreaCoveredbyPVModule(double fractionofCollectorGrossAreaCoveredbyPVModule);

      double fractionofPVCellAreatoPVModuleArea() const;
      bool setFractionofPVCellAreatoPVModuleArea(double fractionofPVCellAreatoPVModuleArea);

      double pVModuleTopThermalResistance() const;
      bool setPVModuleTopThermalResistance(double pVModuleTopThermalResistance);

      double pVModuleBottomThermalResistance() const;
      bool setPVModuleBottomThermalResistance(double pVModuleBottomThermalResistance);

      double pVModuleFrontLongwaveEmissivity() const;
      bool setPVModuleFrontLongwaveEmissivity(double pVModuleFrontLongwaveEmissivity);

      double pVModuleBackLongwaveEmissivity() const;
      bool setPVModuleBackLongwaveEmissivity(double pVModuleBackLongwaveEmissivity);

      double glassThickness() const;
      bool setGlassThickness(double glassThickness);

      double glassRefractionIndex() const;
      bool setGlassRefractionIndex(double glassRefractionIndex);

      double glassExtinctionCoefficient() const;
      bool setGlassExtinctionCoefficient(double glassExtinctionCoefficient);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
