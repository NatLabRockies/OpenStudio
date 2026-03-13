/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SolarCollectorPerformancePhotovoltaicThermalBIPVT.hpp"
#include "SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/SolarCollectorPerformance_PhotovoltaicThermal_BIPVT_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SolarCollectorPerformancePhotovoltaicThermalBIPVT::SolarCollectorPerformancePhotovoltaicThermalBIPVT(const Model& model)
    : ModelObject(SolarCollectorPerformancePhotovoltaicThermalBIPVT::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>());

    bool ok = true;
    ok = setEffectivePlenumGapThicknessBehindPVModules(0.1);
    OS_ASSERT(ok);
    ok = setPVCellNormalTransmittanceAbsorptanceProduct(0.957);
    OS_ASSERT(ok);
    ok = setBackingMaterialNormalTransmittanceAbsorptanceProduct(0.87);
    OS_ASSERT(ok);
    ok = setCladdingNormalTransmittanceAbsorptanceProduct(0.85);
    OS_ASSERT(ok);
    ok = setFractionofCollectorGrossAreaCoveredbyPVModule(0.85);
    OS_ASSERT(ok);
    ok = setFractionofPVCellAreatoPVModuleArea(0.9);
    OS_ASSERT(ok);
    ok = setPVModuleTopThermalResistance(0.0044);
    OS_ASSERT(ok);
    ok = setPVModuleBottomThermalResistance(0.0039);
    OS_ASSERT(ok);
    ok = setPVModuleFrontLongwaveEmissivity(0.85);
    OS_ASSERT(ok);
    ok = setPVModuleBackLongwaveEmissivity(0.9);
    OS_ASSERT(ok);
    ok = setGlassThickness(0.002);
    OS_ASSERT(ok);
    ok = setGlassRefractionIndex(1.526);
    OS_ASSERT(ok);
    ok = setGlassExtinctionCoefficient(4.0);
    OS_ASSERT(ok);
  }

  SolarCollectorPerformancePhotovoltaicThermalBIPVT::SolarCollectorPerformancePhotovoltaicThermalBIPVT(
    std::shared_ptr<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SolarCollectorPerformancePhotovoltaicThermalBIPVT::iddObjectType() {
    return IddObjectType::SolarCollectorPerformance_PhotovoltaicThermal_BIPVT;
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::effectivePlenumGapThicknessBehindPVModules() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->effectivePlenumGapThicknessBehindPVModules();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setEffectivePlenumGapThicknessBehindPVModules(
    double effectivePlenumGapThicknessBehindPVModules) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setEffectivePlenumGapThicknessBehindPVModules(
      effectivePlenumGapThicknessBehindPVModules);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::pVCellNormalTransmittanceAbsorptanceProduct() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->pVCellNormalTransmittanceAbsorptanceProduct();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setPVCellNormalTransmittanceAbsorptanceProduct(
    double pVCellNormalTransmittanceAbsorptanceProduct) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setPVCellNormalTransmittanceAbsorptanceProduct(
      pVCellNormalTransmittanceAbsorptanceProduct);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::backingMaterialNormalTransmittanceAbsorptanceProduct() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->backingMaterialNormalTransmittanceAbsorptanceProduct();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setBackingMaterialNormalTransmittanceAbsorptanceProduct(
    double backingMaterialNormalTransmittanceAbsorptanceProduct) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setBackingMaterialNormalTransmittanceAbsorptanceProduct(
      backingMaterialNormalTransmittanceAbsorptanceProduct);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::claddingNormalTransmittanceAbsorptanceProduct() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->claddingNormalTransmittanceAbsorptanceProduct();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setCladdingNormalTransmittanceAbsorptanceProduct(
    double claddingNormalTransmittanceAbsorptanceProduct) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setCladdingNormalTransmittanceAbsorptanceProduct(
      claddingNormalTransmittanceAbsorptanceProduct);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::fractionofCollectorGrossAreaCoveredbyPVModule() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->fractionofCollectorGrossAreaCoveredbyPVModule();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setFractionofCollectorGrossAreaCoveredbyPVModule(
    double fractionofCollectorGrossAreaCoveredbyPVModule) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setFractionofCollectorGrossAreaCoveredbyPVModule(
      fractionofCollectorGrossAreaCoveredbyPVModule);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::fractionofPVCellAreatoPVModuleArea() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->fractionofPVCellAreatoPVModuleArea();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setFractionofPVCellAreatoPVModuleArea(double fractionofPVCellAreatoPVModuleArea) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setFractionofPVCellAreatoPVModuleArea(
      fractionofPVCellAreatoPVModuleArea);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::pVModuleTopThermalResistance() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->pVModuleTopThermalResistance();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setPVModuleTopThermalResistance(double pVModuleTopThermalResistance) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setPVModuleTopThermalResistance(pVModuleTopThermalResistance);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::pVModuleBottomThermalResistance() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->pVModuleBottomThermalResistance();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setPVModuleBottomThermalResistance(double pVModuleBottomThermalResistance) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setPVModuleBottomThermalResistance(
      pVModuleBottomThermalResistance);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::pVModuleFrontLongwaveEmissivity() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->pVModuleFrontLongwaveEmissivity();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setPVModuleFrontLongwaveEmissivity(double pVModuleFrontLongwaveEmissivity) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setPVModuleFrontLongwaveEmissivity(
      pVModuleFrontLongwaveEmissivity);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::pVModuleBackLongwaveEmissivity() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->pVModuleBackLongwaveEmissivity();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setPVModuleBackLongwaveEmissivity(double pVModuleBackLongwaveEmissivity) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setPVModuleBackLongwaveEmissivity(
      pVModuleBackLongwaveEmissivity);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::glassThickness() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->glassThickness();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setGlassThickness(double glassThickness) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setGlassThickness(glassThickness);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::glassRefractionIndex() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->glassRefractionIndex();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setGlassRefractionIndex(double glassRefractionIndex) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setGlassRefractionIndex(glassRefractionIndex);
  }

  double SolarCollectorPerformancePhotovoltaicThermalBIPVT::glassExtinctionCoefficient() const {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->glassExtinctionCoefficient();
  }

  bool SolarCollectorPerformancePhotovoltaicThermalBIPVT::setGlassExtinctionCoefficient(double glassExtinctionCoefficient) {
    return getImpl<detail::SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl>()->setGlassExtinctionCoefficient(glassExtinctionCoefficient);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::effectivePlenumGapThicknessBehindPVModules() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::EffectivePlenumGapThicknessBehindPVModules, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::pVCellNormalTransmittanceAbsorptanceProduct() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVCellNormalTransmittanceAbsorptanceProduct, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::backingMaterialNormalTransmittanceAbsorptanceProduct() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::BackingMaterialNormalTransmittanceAbsorptanceProduct, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::claddingNormalTransmittanceAbsorptanceProduct() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::CladdingNormalTransmittanceAbsorptanceProduct, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::fractionofCollectorGrossAreaCoveredbyPVModule() const {
      const auto value =
        getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofCollectorGrossAreaCoveredbyPVModule, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::fractionofPVCellAreatoPVModuleArea() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofPVCellAreatoPVModuleArea, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::pVModuleTopThermalResistance() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleTopThermalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::pVModuleBottomThermalResistance() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBottomThermalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::pVModuleFrontLongwaveEmissivity() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleFrontLongwaveEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::pVModuleBackLongwaveEmissivity() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBackLongwaveEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::glassThickness() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassThickness, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::glassRefractionIndex() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassRefractionIndex, true);
      OS_ASSERT(value);
      return *value;
    }

    double SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::glassExtinctionCoefficient() const {
      const auto value = getDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassExtinctionCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setEffectivePlenumGapThicknessBehindPVModules(
      double effectivePlenumGapThicknessBehindPVModules) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::EffectivePlenumGapThicknessBehindPVModules,
                       effectivePlenumGapThicknessBehindPVModules);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setPVCellNormalTransmittanceAbsorptanceProduct(
      double pVCellNormalTransmittanceAbsorptanceProduct) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVCellNormalTransmittanceAbsorptanceProduct,
                       pVCellNormalTransmittanceAbsorptanceProduct);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setBackingMaterialNormalTransmittanceAbsorptanceProduct(
      double backingMaterialNormalTransmittanceAbsorptanceProduct) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::BackingMaterialNormalTransmittanceAbsorptanceProduct,
                       backingMaterialNormalTransmittanceAbsorptanceProduct);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setCladdingNormalTransmittanceAbsorptanceProduct(
      double claddingNormalTransmittanceAbsorptanceProduct) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::CladdingNormalTransmittanceAbsorptanceProduct,
                       claddingNormalTransmittanceAbsorptanceProduct);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setFractionofCollectorGrossAreaCoveredbyPVModule(
      double fractionofCollectorGrossAreaCoveredbyPVModule) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofCollectorGrossAreaCoveredbyPVModule,
                       fractionofCollectorGrossAreaCoveredbyPVModule);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setFractionofPVCellAreatoPVModuleArea(double fractionofPVCellAreatoPVModuleArea) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::FractionofPVCellAreatoPVModuleArea,
                       fractionofPVCellAreatoPVModuleArea);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setPVModuleTopThermalResistance(double pVModuleTopThermalResistance) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleTopThermalResistance,
                       pVModuleTopThermalResistance);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setPVModuleBottomThermalResistance(double pVModuleBottomThermalResistance) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBottomThermalResistance,
                       pVModuleBottomThermalResistance);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setPVModuleFrontLongwaveEmissivity(double pVModuleFrontLongwaveEmissivity) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleFrontLongwaveEmissivity,
                       pVModuleFrontLongwaveEmissivity);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setPVModuleBackLongwaveEmissivity(double pVModuleBackLongwaveEmissivity) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::PVModuleBackLongwaveEmissivity,
                       pVModuleBackLongwaveEmissivity);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setGlassThickness(double glassThickness) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassThickness, glassThickness);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setGlassRefractionIndex(double glassRefractionIndex) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassRefractionIndex, glassRefractionIndex);
    }

    bool SolarCollectorPerformancePhotovoltaicThermalBIPVT_Impl::setGlassExtinctionCoefficient(double glassExtinctionCoefficient) {
      return setDouble(openstudio::SolarCollectorPerformance_PhotovoltaicThermal_BIPVTFields::GlassExtinctionCoefficient, glassExtinctionCoefficient);
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
