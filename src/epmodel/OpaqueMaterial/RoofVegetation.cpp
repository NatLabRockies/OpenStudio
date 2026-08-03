/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "OpaqueMaterial/RoofVegetation.hpp"
#include "OpaqueMaterial/RoofVegetation_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Material_RoofVegetation_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  RoofVegetation::RoofVegetation(const Model& model, const std::string& roughness) : OpaqueMaterial(RoofVegetation::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::RoofVegetation_Impl>());

    bool ok = true;
    ok = setRoughness(roughness);
    OS_ASSERT(ok);
  }

  RoofVegetation::RoofVegetation(std::shared_ptr<detail::RoofVegetation_Impl> impl) : OpaqueMaterial(std::move(impl)) {}

  IddObjectType RoofVegetation::iddObjectType() {
    return IddObjectType::Material_RoofVegetation;
  }

  std::vector<std::string> RoofVegetation::roughnessValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Material_RoofVegetationFields::Roughness);
  }

  std::vector<std::string> RoofVegetation::moistureDiffusionCalculationMethodValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Material_RoofVegetationFields::MoistureDiffusionCalculationMethod);
  }

  double RoofVegetation::heightofPlants() const {
    return getImpl<detail::RoofVegetation_Impl>()->heightofPlants();
  }

  bool RoofVegetation::isHeightofPlantsDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isHeightofPlantsDefaulted();
  }

  bool RoofVegetation::setHeightofPlants(double heightofPlants) {
    return getImpl<detail::RoofVegetation_Impl>()->setHeightofPlants(heightofPlants);
  }

  void RoofVegetation::resetHeightofPlants() {
    getImpl<detail::RoofVegetation_Impl>()->resetHeightofPlants();
  }

  double RoofVegetation::leafAreaIndex() const {
    return getImpl<detail::RoofVegetation_Impl>()->leafAreaIndex();
  }

  bool RoofVegetation::isLeafAreaIndexDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isLeafAreaIndexDefaulted();
  }

  bool RoofVegetation::setLeafAreaIndex(double leafAreaIndex) {
    return getImpl<detail::RoofVegetation_Impl>()->setLeafAreaIndex(leafAreaIndex);
  }

  void RoofVegetation::resetLeafAreaIndex() {
    getImpl<detail::RoofVegetation_Impl>()->resetLeafAreaIndex();
  }

  double RoofVegetation::leafReflectivity() const {
    return getImpl<detail::RoofVegetation_Impl>()->leafReflectivity();
  }

  bool RoofVegetation::isLeafReflectivityDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isLeafReflectivityDefaulted();
  }

  bool RoofVegetation::setLeafReflectivity(double leafReflectivity) {
    return getImpl<detail::RoofVegetation_Impl>()->setLeafReflectivity(leafReflectivity);
  }

  void RoofVegetation::resetLeafReflectivity() {
    getImpl<detail::RoofVegetation_Impl>()->resetLeafReflectivity();
  }

  double RoofVegetation::leafEmissivity() const {
    return getImpl<detail::RoofVegetation_Impl>()->leafEmissivity();
  }

  bool RoofVegetation::isLeafEmissivityDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isLeafEmissivityDefaulted();
  }

  bool RoofVegetation::setLeafEmissivity(double leafEmissivity) {
    return getImpl<detail::RoofVegetation_Impl>()->setLeafEmissivity(leafEmissivity);
  }

  void RoofVegetation::resetLeafEmissivity() {
    getImpl<detail::RoofVegetation_Impl>()->resetLeafEmissivity();
  }

  double RoofVegetation::minimumStomatalResistance() const {
    return getImpl<detail::RoofVegetation_Impl>()->minimumStomatalResistance();
  }

  bool RoofVegetation::isMinimumStomatalResistanceDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isMinimumStomatalResistanceDefaulted();
  }

  bool RoofVegetation::setMinimumStomatalResistance(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setMinimumStomatalResistance(value);
  }

  void RoofVegetation::resetMinimumStomatalResistance() {
    getImpl<detail::RoofVegetation_Impl>()->resetMinimumStomatalResistance();
  }

  std::string RoofVegetation::roughness() const {
    return getImpl<detail::RoofVegetation_Impl>()->roughness();
  }

  bool RoofVegetation::isRoughnessDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isRoughnessDefaulted();
  }

  bool RoofVegetation::setRoughness(const std::string& value) {
    return getImpl<detail::RoofVegetation_Impl>()->setRoughness(value);
  }

  void RoofVegetation::resetRoughness() {
    getImpl<detail::RoofVegetation_Impl>()->resetRoughness();
  }

  double RoofVegetation::thickness() const {
    return getImpl<detail::RoofVegetation_Impl>()->thickness();
  }

  bool RoofVegetation::isThicknessDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isThicknessDefaulted();
  }

  bool RoofVegetation::setThickness(double thickness) {
    return getImpl<detail::RoofVegetation_Impl>()->setThickness(thickness);
  }

  void RoofVegetation::resetThickness() {
    getImpl<detail::RoofVegetation_Impl>()->resetThickness();
  }

  double RoofVegetation::thermalConductivity() const {
    return getImpl<detail::RoofVegetation_Impl>()->thermalConductivity();
  }

  double RoofVegetation::thermalConductance() const {
    return getImpl<detail::RoofVegetation_Impl>()->thermalConductance();
  }

  double RoofVegetation::thermalResistivity() const {
    return getImpl<detail::RoofVegetation_Impl>()->thermalResistivity();
  }

  bool RoofVegetation::setThermalConductivity(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalConductivity(value);
  }

  bool RoofVegetation::setThermalConductance(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalConductance(value);
  }

  bool RoofVegetation::setThermalResistivity(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalResistivity(value);
  }

  double RoofVegetation::conductivityofDrySoil() const {
    return getImpl<detail::RoofVegetation_Impl>()->conductivityofDrySoil();
  }

  bool RoofVegetation::isConductivityofDrySoilDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isConductivityofDrySoilDefaulted();
  }

  bool RoofVegetation::setConductivityofDrySoil(double conductivityofDrySoil) {
    return getImpl<detail::RoofVegetation_Impl>()->setConductivityofDrySoil(conductivityofDrySoil);
  }

  void RoofVegetation::resetConductivityofDrySoil() {
    getImpl<detail::RoofVegetation_Impl>()->resetConductivityofDrySoil();
  }

  double RoofVegetation::density() const {
    return getImpl<detail::RoofVegetation_Impl>()->density();
  }

  double RoofVegetation::densityofDrySoil() const {
    return getImpl<detail::RoofVegetation_Impl>()->densityofDrySoil();
  }

  bool RoofVegetation::isDensityofDrySoilDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isDensityofDrySoilDefaulted();
  }

  bool RoofVegetation::setDensity(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setDensity(value);
  }

  bool RoofVegetation::setDensityofDrySoil(double densityofDrySoil) {
    return getImpl<detail::RoofVegetation_Impl>()->setDensityofDrySoil(densityofDrySoil);
  }

  void RoofVegetation::resetDensityofDrySoil() {
    getImpl<detail::RoofVegetation_Impl>()->resetDensityofDrySoil();
  }

  double RoofVegetation::specificHeat() const {
    return getImpl<detail::RoofVegetation_Impl>()->specificHeat();
  }

  double RoofVegetation::specificHeatofDrySoil() const {
    return getImpl<detail::RoofVegetation_Impl>()->specificHeatofDrySoil();
  }

  bool RoofVegetation::isSpecificHeatofDrySoilDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isSpecificHeatofDrySoilDefaulted();
  }

  bool RoofVegetation::setSpecificHeat(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setSpecificHeat(value);
  }

  bool RoofVegetation::setSpecificHeatofDrySoil(double specificHeatofDrySoil) {
    return getImpl<detail::RoofVegetation_Impl>()->setSpecificHeatofDrySoil(specificHeatofDrySoil);
  }

  void RoofVegetation::resetSpecificHeatofDrySoil() {
    getImpl<detail::RoofVegetation_Impl>()->resetSpecificHeatofDrySoil();
  }

  boost::optional<double> RoofVegetation::heatCapacity() const {
    return getImpl<detail::RoofVegetation_Impl>()->heatCapacity();
  }

  double RoofVegetation::thermalAbsorptance() const {
    return getImpl<detail::RoofVegetation_Impl>()->thermalAbsorptance();
  }

  bool RoofVegetation::isThermalAbsorptanceDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isThermalAbsorptanceDefaulted();
  }

  bool RoofVegetation::setThermalAbsorptance(double thermalAbsorptance) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalAbsorptance(thermalAbsorptance);
  }

  bool RoofVegetation::setThermalAbsorptance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalAbsorptance(value);
  }

  void RoofVegetation::resetThermalAbsorptance() {
    getImpl<detail::RoofVegetation_Impl>()->resetThermalAbsorptance();
  }

  boost::optional<double> RoofVegetation::thermalReflectance() const {
    return getImpl<detail::RoofVegetation_Impl>()->thermalReflectance();
  }

  bool RoofVegetation::setThermalReflectance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setThermalReflectance(value);
  }

  double RoofVegetation::solarAbsorptance() const {
    return getImpl<detail::RoofVegetation_Impl>()->solarAbsorptance();
  }

  bool RoofVegetation::isSolarAbsorptanceDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isSolarAbsorptanceDefaulted();
  }

  bool RoofVegetation::setSolarAbsorptance(double solarAbsorptance) {
    return getImpl<detail::RoofVegetation_Impl>()->setSolarAbsorptance(solarAbsorptance);
  }

  bool RoofVegetation::setSolarAbsorptance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setSolarAbsorptance(value);
  }

  void RoofVegetation::resetSolarAbsorptance() {
    getImpl<detail::RoofVegetation_Impl>()->resetSolarAbsorptance();
  }

  boost::optional<double> RoofVegetation::solarReflectance() const {
    return getImpl<detail::RoofVegetation_Impl>()->solarReflectance();
  }

  bool RoofVegetation::setSolarReflectance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setSolarReflectance(value);
  }

  double RoofVegetation::visibleAbsorptance() const {
    return getImpl<detail::RoofVegetation_Impl>()->visibleAbsorptance();
  }

  bool RoofVegetation::isVisibleAbsorptanceDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isVisibleAbsorptanceDefaulted();
  }

  bool RoofVegetation::setVisibleAbsorptance(double visibleAbsorptance) {
    return getImpl<detail::RoofVegetation_Impl>()->setVisibleAbsorptance(visibleAbsorptance);
  }

  bool RoofVegetation::setVisibleAbsorptance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setVisibleAbsorptance(value);
  }

  void RoofVegetation::resetVisibleAbsorptance() {
    getImpl<detail::RoofVegetation_Impl>()->resetVisibleAbsorptance();
  }

  boost::optional<double> RoofVegetation::visibleReflectance() const {
    return getImpl<detail::RoofVegetation_Impl>()->visibleReflectance();
  }

  bool RoofVegetation::setVisibleReflectance(boost::optional<double> value) {
    return getImpl<detail::RoofVegetation_Impl>()->setVisibleReflectance(value);
  }

  double RoofVegetation::saturationVolumetricMoistureContent() const {
    return getImpl<detail::RoofVegetation_Impl>()->saturationVolumetricMoistureContent();
  }

  double RoofVegetation::residualVolumetricMoistureContent() const {
    return getImpl<detail::RoofVegetation_Impl>()->residualVolumetricMoistureContent();
  }

  double RoofVegetation::initialVolumetricMoistureContent() const {
    return getImpl<detail::RoofVegetation_Impl>()->initialVolumetricMoistureContent();
  }

  bool RoofVegetation::setSaturationVolumetricMoistureContent(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setSaturationVolumetricMoistureContent(value);
  }

  bool RoofVegetation::setResidualVolumetricMoistureContent(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setResidualVolumetricMoistureContent(value);
  }

  bool RoofVegetation::setInitialVolumetricMoistureContent(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setInitialVolumetricMoistureContent(value);
  }

  bool RoofVegetation::setInitialVolumetricMoistureConent(double value) {
    return getImpl<detail::RoofVegetation_Impl>()->setInitialVolumetricMoistureContent(value);
  }

  double RoofVegetation::saturationVolumetricMoistureContentoftheSoilLayer() const {
    return getImpl<detail::RoofVegetation_Impl>()->saturationVolumetricMoistureContentoftheSoilLayer();
  }

  bool RoofVegetation::isSaturationVolumetricMoistureContentoftheSoilLayerDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isSaturationVolumetricMoistureContentoftheSoilLayerDefaulted();
  }

  bool RoofVegetation::setSaturationVolumetricMoistureContentoftheSoilLayer(double saturationVolumetricMoistureContentoftheSoilLayer) {
    return getImpl<detail::RoofVegetation_Impl>()->setSaturationVolumetricMoistureContentoftheSoilLayer(
      saturationVolumetricMoistureContentoftheSoilLayer);
  }

  void RoofVegetation::resetSaturationVolumetricMoistureContentoftheSoilLayer() {
    getImpl<detail::RoofVegetation_Impl>()->resetSaturationVolumetricMoistureContentoftheSoilLayer();
  }

  double RoofVegetation::residualVolumetricMoistureContentoftheSoilLayer() const {
    return getImpl<detail::RoofVegetation_Impl>()->residualVolumetricMoistureContentoftheSoilLayer();
  }

  bool RoofVegetation::isResidualVolumetricMoistureContentoftheSoilLayerDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isResidualVolumetricMoistureContentoftheSoilLayerDefaulted();
  }

  bool RoofVegetation::setResidualVolumetricMoistureContentoftheSoilLayer(double residualVolumetricMoistureContentoftheSoilLayer) {
    return getImpl<detail::RoofVegetation_Impl>()->setResidualVolumetricMoistureContentoftheSoilLayer(
      residualVolumetricMoistureContentoftheSoilLayer);
  }

  void RoofVegetation::resetResidualVolumetricMoistureContentoftheSoilLayer() {
    getImpl<detail::RoofVegetation_Impl>()->resetResidualVolumetricMoistureContentoftheSoilLayer();
  }

  double RoofVegetation::initialVolumetricMoistureContentoftheSoilLayer() const {
    return getImpl<detail::RoofVegetation_Impl>()->initialVolumetricMoistureContentoftheSoilLayer();
  }

  bool RoofVegetation::isInitialVolumetricMoistureContentoftheSoilLayerDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isInitialVolumetricMoistureContentoftheSoilLayerDefaulted();
  }

  bool RoofVegetation::setInitialVolumetricMoistureContentoftheSoilLayer(double initialVolumetricMoistureContentoftheSoilLayer) {
    return getImpl<detail::RoofVegetation_Impl>()->setInitialVolumetricMoistureContentoftheSoilLayer(initialVolumetricMoistureContentoftheSoilLayer);
  }

  void RoofVegetation::resetInitialVolumetricMoistureContentoftheSoilLayer() {
    getImpl<detail::RoofVegetation_Impl>()->resetInitialVolumetricMoistureContentoftheSoilLayer();
  }

  std::string RoofVegetation::moistureDiffusionCalculationMethod() const {
    return getImpl<detail::RoofVegetation_Impl>()->moistureDiffusionCalculationMethod();
  }

  bool RoofVegetation::isMoistureDiffusionCalculationMethodDefaulted() const {
    return getImpl<detail::RoofVegetation_Impl>()->isMoistureDiffusionCalculationMethodDefaulted();
  }

  bool RoofVegetation::setMoistureDiffusionCalculationMethod(const std::string& value) {
    return getImpl<detail::RoofVegetation_Impl>()->setMoistureDiffusionCalculationMethod(value);
  }

  void RoofVegetation::resetMoistureDiffusionCalculationMethod() {
    getImpl<detail::RoofVegetation_Impl>()->resetMoistureDiffusionCalculationMethod();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double RoofVegetation_Impl::heightofPlants() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::HeightofPlants, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isHeightofPlantsDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::HeightofPlants);
    }

    double RoofVegetation_Impl::leafAreaIndex() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::LeafAreaIndex, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isLeafAreaIndexDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::LeafAreaIndex);
    }

    double RoofVegetation_Impl::leafReflectivity() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::LeafReflectivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isLeafReflectivityDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::LeafReflectivity);
    }

    double RoofVegetation_Impl::leafEmissivity() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::LeafEmissivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isLeafEmissivityDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::LeafEmissivity);
    }

    double RoofVegetation_Impl::minimumStomatalResistance() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::MinimumStomatalResistance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isMinimumStomatalResistanceDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::MinimumStomatalResistance);
    }

    std::string RoofVegetation_Impl::roughness() const {
      const auto value = getString(openstudio::Material_RoofVegetationFields::Roughness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isRoughnessDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::Roughness);
    }

    double RoofVegetation_Impl::thickness() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::Thickness, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isThicknessDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::Thickness);
    }

    double RoofVegetation_Impl::thermalConductivity() const {
      return conductivityofDrySoil();
    }

    double RoofVegetation_Impl::thermalConductance() const {
      return thermalConductivity() / thickness();
    }

    double RoofVegetation_Impl::thermalResistivity() const {
      return 1.0 / thermalConductivity();
    }

    double RoofVegetation_Impl::thermalResistance() const {
      return 1.0 / thermalConductance();
    }

    double RoofVegetation_Impl::conductivityofDrySoil() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::ConductivityofDrySoil, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isConductivityofDrySoilDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::ConductivityofDrySoil);
    }

    double RoofVegetation_Impl::density() const {
      return densityofDrySoil();
    }

    double RoofVegetation_Impl::densityofDrySoil() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::DensityofDrySoil, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isDensityofDrySoilDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::DensityofDrySoil);
    }

    double RoofVegetation_Impl::specificHeat() const {
      return specificHeatofDrySoil();
    }

    double RoofVegetation_Impl::specificHeatofDrySoil() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::SpecificHeatofDrySoil, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isSpecificHeatofDrySoilDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::SpecificHeatofDrySoil);
    }

    double RoofVegetation_Impl::thermalAbsorptance() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::ThermalAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isThermalAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::ThermalAbsorptance);
    }

    boost::optional<double> RoofVegetation_Impl::thermalReflectance() const {
      return 1.0 - thermalAbsorptance();
    }

    double RoofVegetation_Impl::solarAbsorptance() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::SolarAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isSolarAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::SolarAbsorptance);
    }

    boost::optional<double> RoofVegetation_Impl::solarReflectance() const {
      return 1.0 - solarAbsorptance();
    }

    double RoofVegetation_Impl::visibleAbsorptance() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::VisibleAbsorptance, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isVisibleAbsorptanceDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::VisibleAbsorptance);
    }

    boost::optional<double> RoofVegetation_Impl::visibleReflectance() const {
      return 1.0 - visibleAbsorptance();
    }

    double RoofVegetation_Impl::saturationVolumetricMoistureContent() const {
      return saturationVolumetricMoistureContentoftheSoilLayer();
    }

    double RoofVegetation_Impl::residualVolumetricMoistureContent() const {
      return residualVolumetricMoistureContentoftheSoilLayer();
    }

    double RoofVegetation_Impl::initialVolumetricMoistureContent() const {
      return initialVolumetricMoistureContentoftheSoilLayer();
    }

    double RoofVegetation_Impl::saturationVolumetricMoistureContentoftheSoilLayer() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isSaturationVolumetricMoistureContentoftheSoilLayerDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer);
    }

    double RoofVegetation_Impl::residualVolumetricMoistureContentoftheSoilLayer() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isResidualVolumetricMoistureContentoftheSoilLayerDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer);
    }

    double RoofVegetation_Impl::initialVolumetricMoistureContentoftheSoilLayer() const {
      const auto value = getDouble(openstudio::Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isInitialVolumetricMoistureContentoftheSoilLayerDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer);
    }

    std::string RoofVegetation_Impl::moistureDiffusionCalculationMethod() const {
      const auto value = getString(openstudio::Material_RoofVegetationFields::MoistureDiffusionCalculationMethod, true);
      OS_ASSERT(value);
      return *value;
    }

    bool RoofVegetation_Impl::isMoistureDiffusionCalculationMethodDefaulted() const {
      return isEmpty(openstudio::Material_RoofVegetationFields::MoistureDiffusionCalculationMethod);
    }

    bool RoofVegetation_Impl::setHeightofPlants(double heightofPlants) {
      return setDouble(openstudio::Material_RoofVegetationFields::HeightofPlants, heightofPlants);
    }

    void RoofVegetation_Impl::resetHeightofPlants() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::HeightofPlants, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setLeafAreaIndex(double leafAreaIndex) {
      return setDouble(openstudio::Material_RoofVegetationFields::LeafAreaIndex, leafAreaIndex);
    }

    void RoofVegetation_Impl::resetLeafAreaIndex() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::LeafAreaIndex, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setLeafReflectivity(double leafReflectivity) {
      return setDouble(openstudio::Material_RoofVegetationFields::LeafReflectivity, leafReflectivity);
    }

    void RoofVegetation_Impl::resetLeafReflectivity() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::LeafReflectivity, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setLeafEmissivity(double leafEmissivity) {
      return setDouble(openstudio::Material_RoofVegetationFields::LeafEmissivity, leafEmissivity);
    }

    void RoofVegetation_Impl::resetLeafEmissivity() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::LeafEmissivity, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setMinimumStomatalResistance(double value) {
      return setDouble(openstudio::Material_RoofVegetationFields::MinimumStomatalResistance, value);
    }

    void RoofVegetation_Impl::resetMinimumStomatalResistance() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::MinimumStomatalResistance, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setRoughness(const std::string& value) {
      return setString(openstudio::Material_RoofVegetationFields::Roughness, value);
    }

    void RoofVegetation_Impl::resetRoughness() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::Roughness, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setThickness(double thickness) {
      return setDouble(openstudio::Material_RoofVegetationFields::Thickness, thickness);
    }

    void RoofVegetation_Impl::resetThickness() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::Thickness, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setThermalConductivity(double value) {
      return setConductivityofDrySoil(value);
    }

    bool RoofVegetation_Impl::setThermalConductance(double value) {
      return setThickness(thermalConductivity() / value);
    }

    bool RoofVegetation_Impl::setThermalResistivity(double value) {
      return setThermalConductivity(1.0 / value);
    }

    bool RoofVegetation_Impl::setThermalResistance(double value) {
      return setThickness(value / thermalResistivity());
    }

    bool RoofVegetation_Impl::setConductivityofDrySoil(double conductivityofDrySoil) {
      return setDouble(openstudio::Material_RoofVegetationFields::ConductivityofDrySoil, conductivityofDrySoil);
    }

    void RoofVegetation_Impl::resetConductivityofDrySoil() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::ConductivityofDrySoil, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setDensity(double value) {
      return setDensityofDrySoil(value);
    }

    bool RoofVegetation_Impl::setDensityofDrySoil(double densityofDrySoil) {
      return setDouble(openstudio::Material_RoofVegetationFields::DensityofDrySoil, densityofDrySoil);
    }

    void RoofVegetation_Impl::resetDensityofDrySoil() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::DensityofDrySoil, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setSpecificHeat(double value) {
      return setSpecificHeatofDrySoil(value);
    }

    bool RoofVegetation_Impl::setSpecificHeatofDrySoil(double specificHeatofDrySoil) {
      return setDouble(openstudio::Material_RoofVegetationFields::SpecificHeatofDrySoil, specificHeatofDrySoil);
    }

    void RoofVegetation_Impl::resetSpecificHeatofDrySoil() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::SpecificHeatofDrySoil, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setThermalAbsorptance(double thermalAbsorptance) {
      return setDouble(openstudio::Material_RoofVegetationFields::ThermalAbsorptance, thermalAbsorptance);
    }

    bool RoofVegetation_Impl::setThermalAbsorptance(boost::optional<double> value) {
      if (!value) {
        return setString(openstudio::Material_RoofVegetationFields::ThermalAbsorptance, "");
      }
      return setDouble(openstudio::Material_RoofVegetationFields::ThermalAbsorptance, *value);
    }

    void RoofVegetation_Impl::resetThermalAbsorptance() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::ThermalAbsorptance, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setThermalReflectance(boost::optional<double> value) {
      if (!value) {
        return setThermalAbsorptance(boost::none);
      }
      return setThermalAbsorptance(1.0 - *value);
    }

    bool RoofVegetation_Impl::setSolarAbsorptance(double solarAbsorptance) {
      return setDouble(openstudio::Material_RoofVegetationFields::SolarAbsorptance, solarAbsorptance);
    }

    bool RoofVegetation_Impl::setSolarAbsorptance(boost::optional<double> value) {
      if (!value) {
        return setString(openstudio::Material_RoofVegetationFields::SolarAbsorptance, "");
      }
      return setDouble(openstudio::Material_RoofVegetationFields::SolarAbsorptance, *value);
    }

    void RoofVegetation_Impl::resetSolarAbsorptance() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::SolarAbsorptance, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setSolarReflectance(boost::optional<double> value) {
      if (!value) {
        return setSolarAbsorptance(boost::none);
      }
      return setSolarAbsorptance(1.0 - *value);
    }

    bool RoofVegetation_Impl::setVisibleAbsorptance(double visibleAbsorptance) {
      return setDouble(openstudio::Material_RoofVegetationFields::VisibleAbsorptance, visibleAbsorptance);
    }

    bool RoofVegetation_Impl::setVisibleAbsorptance(boost::optional<double> value) {
      if (!value) {
        return setString(openstudio::Material_RoofVegetationFields::VisibleAbsorptance, "");
      }
      return setDouble(openstudio::Material_RoofVegetationFields::VisibleAbsorptance, *value);
    }

    void RoofVegetation_Impl::resetVisibleAbsorptance() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::VisibleAbsorptance, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setVisibleReflectance(boost::optional<double> value) {
      if (!value) {
        return setVisibleAbsorptance(boost::none);
      }
      return setVisibleAbsorptance(1.0 - *value);
    }

    bool RoofVegetation_Impl::setSaturationVolumetricMoistureContent(double value) {
      return setDouble(openstudio::Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer, value);
    }

    bool RoofVegetation_Impl::setResidualVolumetricMoistureContent(double value) {
      return setDouble(openstudio::Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer, value);
    }

    bool RoofVegetation_Impl::setInitialVolumetricMoistureContent(double value) {
      return setDouble(openstudio::Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer, value);
    }

    bool RoofVegetation_Impl::setSaturationVolumetricMoistureContentoftheSoilLayer(double saturationVolumetricMoistureContentoftheSoilLayer) {
      return setDouble(openstudio::Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer,
                       saturationVolumetricMoistureContentoftheSoilLayer);
    }

    void RoofVegetation_Impl::resetSaturationVolumetricMoistureContentoftheSoilLayer() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setResidualVolumetricMoistureContentoftheSoilLayer(double residualVolumetricMoistureContentoftheSoilLayer) {
      return setDouble(openstudio::Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer,
                       residualVolumetricMoistureContentoftheSoilLayer);
    }

    void RoofVegetation_Impl::resetResidualVolumetricMoistureContentoftheSoilLayer() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setInitialVolumetricMoistureContentoftheSoilLayer(double initialVolumetricMoistureContentoftheSoilLayer) {
      return setDouble(openstudio::Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer,
                       initialVolumetricMoistureContentoftheSoilLayer);
    }

    void RoofVegetation_Impl::resetInitialVolumetricMoistureContentoftheSoilLayer() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer, "");
      OS_ASSERT(result);
    }

    bool RoofVegetation_Impl::setMoistureDiffusionCalculationMethod(const std::string& value) {
      return setString(openstudio::Material_RoofVegetationFields::MoistureDiffusionCalculationMethod, value);
    }

    void RoofVegetation_Impl::resetMoistureDiffusionCalculationMethod() {
      const bool result = setString(openstudio::Material_RoofVegetationFields::MoistureDiffusionCalculationMethod, "");
      OS_ASSERT(result);
    }

    boost::optional<double> RoofVegetation_Impl::heatCapacity() const {
      return specificHeat() * density() * thickness();
    }

    std::vector<std::string> RoofVegetation_Impl::roughnessValues() const {
      return openstudio::epmodel::RoofVegetation::roughnessValues();
    }

    std::vector<std::string> RoofVegetation_Impl::moistureDiffusionCalculationMethodValues() const {
      return openstudio::epmodel::RoofVegetation::moistureDiffusionCalculationMethodValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
