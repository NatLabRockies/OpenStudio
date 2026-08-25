/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOFVEGETATION_HPP
#define EPMODEL_ROOFVEGETATION_HPP

#include "EPModelAPI.hpp"
#include "OpaqueMaterial/OpaqueMaterial.hpp"

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

  /** \brief Represents a vegetated roof material layer.
   *
   * \par EnergyPlus object
   * \epobject{group-surface-construction-elements.html#materialroofvegetation,Material:RoofVegetation}.
   *
   * \par Important behavior
   * The generic thermal-conductivity, density, and specific-heat methods are
   * aliases for the corresponding dry-soil fields. Moisture-content and
   * diffusion settings remain separate fields on the same EnergyPlus object.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is
   * <code>openstudio::model::RoofVegetation</code>. EPModel adds direct
   * thermal/optical derived helpers and reflectance setters. Model's
   * <code>soilLayerName()</code> relationship is not available.
   *
   * \par Known limitations
   * The referenced soil-layer relationship cannot be assigned through this
   * wrapper.
   */
  class EPMODEL_API RoofVegetation : public OpaqueMaterial
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

    double heightofPlants() const;
    bool isHeightofPlantsDefaulted() const;
    bool setHeightofPlants(double heightofPlants);
    void resetHeightofPlants();

    double leafAreaIndex() const;
    bool isLeafAreaIndexDefaulted() const;
    bool setLeafAreaIndex(double leafAreaIndex);
    void resetLeafAreaIndex();

    double leafReflectivity() const;
    bool isLeafReflectivityDefaulted() const;
    bool setLeafReflectivity(double leafReflectivity);
    void resetLeafReflectivity();

    double leafEmissivity() const;
    bool isLeafEmissivityDefaulted() const;
    bool setLeafEmissivity(double leafEmissivity);
    void resetLeafEmissivity();

    double minimumStomatalResistance() const;
    bool isMinimumStomatalResistanceDefaulted() const;
    bool setMinimumStomatalResistance(double value);
    void resetMinimumStomatalResistance();

    std::string roughness() const;
    bool isRoughnessDefaulted() const;
    bool setRoughness(const std::string& value);
    void resetRoughness();

    double thickness() const;
    bool isThicknessDefaulted() const;
    bool setThickness(double thickness);
    void resetThickness();

    double thermalConductivity() const;
    double thermalConductance() const;
    double thermalResistivity() const;
    bool setThermalConductivity(double value);
    bool setThermalConductance(double value);
    bool setThermalResistivity(double value);

    double conductivityofDrySoil() const;
    bool isConductivityofDrySoilDefaulted() const;
    bool setConductivityofDrySoil(double conductivityofDrySoil);
    void resetConductivityofDrySoil();

    double density() const;
    double densityofDrySoil() const;
    bool isDensityofDrySoilDefaulted() const;
    bool setDensity(double value);
    bool setDensityofDrySoil(double densityofDrySoil);
    void resetDensityofDrySoil();

    double specificHeat() const;
    double specificHeatofDrySoil() const;
    bool isSpecificHeatofDrySoilDefaulted() const;
    bool setSpecificHeat(double value);
    bool setSpecificHeatofDrySoil(double specificHeatofDrySoil);
    void resetSpecificHeatofDrySoil();

    double thermalAbsorptance() const;
    bool isThermalAbsorptanceDefaulted() const;
    boost::optional<double> thermalReflectance() const;
    bool setThermalAbsorptance(double thermalAbsorptance);
    bool setThermalAbsorptance(boost::optional<double> value);
    void resetThermalAbsorptance();
    bool setThermalReflectance(boost::optional<double> value);

    double solarAbsorptance() const;
    bool isSolarAbsorptanceDefaulted() const;
    boost::optional<double> solarReflectance() const;
    bool setSolarAbsorptance(double solarAbsorptance);
    bool setSolarAbsorptance(boost::optional<double> value);
    void resetSolarAbsorptance();
    bool setSolarReflectance(boost::optional<double> value);

    double visibleAbsorptance() const;
    bool isVisibleAbsorptanceDefaulted() const;
    boost::optional<double> visibleReflectance() const;
    bool setVisibleAbsorptance(double visibleAbsorptance);
    bool setVisibleAbsorptance(boost::optional<double> value);
    void resetVisibleAbsorptance();
    bool setVisibleReflectance(boost::optional<double> value);

    double saturationVolumetricMoistureContent() const;
    bool setSaturationVolumetricMoistureContent(double value);

    double residualVolumetricMoistureContent() const;
    bool setResidualVolumetricMoistureContent(double value);

    double initialVolumetricMoistureContent() const;
    bool setInitialVolumetricMoistureContent(double value);

    double saturationVolumetricMoistureContentoftheSoilLayer() const;
    bool isSaturationVolumetricMoistureContentoftheSoilLayerDefaulted() const;
    bool setSaturationVolumetricMoistureContentoftheSoilLayer(double saturationVolumetricMoistureContentoftheSoilLayer);
    void resetSaturationVolumetricMoistureContentoftheSoilLayer();

    double residualVolumetricMoistureContentoftheSoilLayer() const;
    bool isResidualVolumetricMoistureContentoftheSoilLayerDefaulted() const;
    bool setResidualVolumetricMoistureContentoftheSoilLayer(double residualVolumetricMoistureContentoftheSoilLayer);
    void resetResidualVolumetricMoistureContentoftheSoilLayer();

    double initialVolumetricMoistureContentoftheSoilLayer() const;
    bool isInitialVolumetricMoistureContentoftheSoilLayerDefaulted() const;
    bool setInitialVolumetricMoistureContentoftheSoilLayer(double initialVolumetricMoistureContentoftheSoilLayer);
    void resetInitialVolumetricMoistureContentoftheSoilLayer();

    std::string moistureDiffusionCalculationMethod() const;
    bool isMoistureDiffusionCalculationMethodDefaulted() const;
    bool setMoistureDiffusionCalculationMethod(const std::string& value);
    void resetMoistureDiffusionCalculationMethod();

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
