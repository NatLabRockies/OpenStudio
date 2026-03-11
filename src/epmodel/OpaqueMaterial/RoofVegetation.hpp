/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOFVEGETATION_HPP
#define EPMODEL_ROOFVEGETATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class RoofVegetation_Impl;
}

class EPMODEL_API RoofVegetation : public ModelObject
{
 public:
  explicit RoofVegetation(const Model& model, const std::string& roughness = "Smooth");

  virtual ~RoofVegetation() override = default;
  RoofVegetation(const RoofVegetation& other) = default;
  RoofVegetation(RoofVegetation&& other) = default;
  RoofVegetation& operator=(const RoofVegetation&) = default;
  RoofVegetation& operator=(RoofVegetation&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> roughnessValues();
  static std::vector<std::string> moistureDiffusionCalculationMethodValues();

  // Schema Alignment Notes:
  // - API: Preserves openstudio::model::RoofVegetation scalar accessor names/signatures.
  // - Field Mapping: APIs map directly to E+ Material:RoofVegetation scalar fields.
  // - Field Mapping: thermalConductivity aliases ConductivityofDrySoil, and density/specificHeat aliases dry-soil fields.
  // - ForwardTranslator evidence: ForwardTranslateRoofVegetation.cpp writes these scalar APIs directly to Material:RoofVegetation fields.
  // - Exclusion: relationship-like SoilLayerName field accessors are intentionally excluded in this scalar-only scaffold pass.
  // - TODO(parity): add relationship field APIs in a dedicated parity pass.
  double heightofPlants() const;
  bool isHeightofPlantsDefaulted() const;

  double leafAreaIndex() const;
  bool isLeafAreaIndexDefaulted() const;

  double leafReflectivity() const;
  bool isLeafReflectivityDefaulted() const;

  double leafEmissivity() const;
  bool isLeafEmissivityDefaulted() const;

  double minimumStomatalResistance() const;
  bool isMinimumStomatalResistanceDefaulted() const;

  std::string roughness() const;
  bool isRoughnessDefaulted() const;

  double thickness() const;
  bool isThicknessDefaulted() const;

  double thermalConductivity() const;
  double thermalConductance() const;
  double thermalResistivity() const;
  double thermalResistance() const;

  double conductivityofDrySoil() const;
  bool isConductivityofDrySoilDefaulted() const;

  double density() const;
  double densityofDrySoil() const;
  bool isDensityofDrySoilDefaulted() const;

  double specificHeat() const;
  double specificHeatofDrySoil() const;
  bool isSpecificHeatofDrySoilDefaulted() const;

  boost::optional<double> thermalAbsorptance() const;
  bool isThermalAbsorptanceDefaulted() const;
  boost::optional<double> thermalReflectance() const;

  boost::optional<double> solarAbsorptance() const;
  bool isSolarAbsorptanceDefaulted() const;
  boost::optional<double> solarReflectance() const;

  boost::optional<double> visibleAbsorptance() const;
  bool isVisibleAbsorptanceDefaulted() const;
  boost::optional<double> visibleReflectance() const;

  double saturationVolumetricMoistureContent() const;
  double residualVolumetricMoistureContent() const;
  double initialVolumetricMoistureContent() const;

  double saturationVolumetricMoistureContentoftheSoilLayer() const;
  bool isSaturationVolumetricMoistureContentoftheSoilLayerDefaulted() const;

  double residualVolumetricMoistureContentoftheSoilLayer() const;
  bool isResidualVolumetricMoistureContentoftheSoilLayerDefaulted() const;

  double initialVolumetricMoistureContentoftheSoilLayer() const;
  bool isInitialVolumetricMoistureContentoftheSoilLayerDefaulted() const;

  std::string moistureDiffusionCalculationMethod() const;
  bool isMoistureDiffusionCalculationMethodDefaulted() const;

  bool setHeightofPlants(double heightofPlants);
  void resetHeightofPlants();

  bool setLeafAreaIndex(double leafAreaIndex);
  void resetLeafAreaIndex();

  bool setLeafReflectivity(double leafReflectivity);
  void resetLeafReflectivity();

  bool setLeafEmissivity(double leafEmissivity);
  void resetLeafEmissivity();

  bool setMinimumStomatalResistance(double value);
  void resetMinimumStomatalResistance();

  bool setRoughness(const std::string& value);
  void resetRoughness();

  bool setThickness(double thickness);
  void resetThickness();

  bool setThermalConductivity(double value);
  bool setThermalConductance(double value);
  bool setThermalResistivity(double value);
  bool setThermalResistance(double value);

  bool setConductivityofDrySoil(double conductivityofDrySoil);
  void resetConductivityofDrySoil();

  bool setDensity(double value);
  bool setDensityofDrySoil(double densityofDrySoil);
  void resetDensityofDrySoil();

  bool setSpecificHeat(double value);
  bool setSpecificHeatofDrySoil(double specificHeatofDrySoil);
  void resetSpecificHeatofDrySoil();

  bool setThermalAbsorptance(double thermalAbsorptance);
  bool setThermalAbsorptance(boost::optional<double> value);
  void resetThermalAbsorptance();
  bool setThermalReflectance(boost::optional<double> value);

  bool setSolarAbsorptance(double solarAbsorptance);
  bool setSolarAbsorptance(boost::optional<double> value);
  void resetSolarAbsorptance();
  bool setSolarReflectance(boost::optional<double> value);

  bool setVisibleAbsorptance(double visibleAbsorptance);
  bool setVisibleAbsorptance(boost::optional<double> value);
  void resetVisibleAbsorptance();
  bool setVisibleReflectance(boost::optional<double> value);

  bool setSaturationVolumetricMoistureContent(double value);
  bool setResidualVolumetricMoistureContent(double value);
  bool setInitialVolumetricMoistureContent(double value);

  bool setSaturationVolumetricMoistureContentoftheSoilLayer(double saturationVolumetricMoistureContentoftheSoilLayer);
  void resetSaturationVolumetricMoistureContentoftheSoilLayer();

  bool setResidualVolumetricMoistureContentoftheSoilLayer(double residualVolumetricMoistureContentoftheSoilLayer);
  void resetResidualVolumetricMoistureContentoftheSoilLayer();

  bool setInitialVolumetricMoistureContentoftheSoilLayer(double initialVolumetricMoistureContentoftheSoilLayer);
  void resetInitialVolumetricMoistureContentoftheSoilLayer();

  bool setMoistureDiffusionCalculationMethod(const std::string& value);
  void resetMoistureDiffusionCalculationMethod();

  // Preserve existing model API typo/signature for compatibility.
  bool setInitialVolumetricMoistureConent(double value);

  boost::optional<double> heatCapacity() const;

 protected:
  using ImplType = detail::RoofVegetation_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit RoofVegetation(std::shared_ptr<detail::RoofVegetation_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
