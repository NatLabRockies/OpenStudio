/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOFVEGETATION_IMPL_HPP
#define EPMODEL_ROOFVEGETATION_IMPL_HPP

#include "OpaqueMaterial/OpaqueMaterial_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API RoofVegetation_Impl : public OpaqueMaterial_Impl
    {
     public:
      using OpaqueMaterial_Impl::OpaqueMaterial_Impl;
      virtual ~RoofVegetation_Impl() override = default;

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

      double thickness() const override;
      bool isThicknessDefaulted() const;
      bool setThickness(double thickness) override;
      void resetThickness();

      double thermalConductivity() const override;
      bool setThermalConductivity(double value) override;

      double thermalConductance() const override;
      bool setThermalConductance(double value) override;

      double thermalResistivity() const override;
      bool setThermalResistivity(double value) override;

      double thermalResistance() const override;
      bool setThermalResistance(double value) override;

      double conductivityofDrySoil() const;
      bool isConductivityofDrySoilDefaulted() const;
      bool setConductivityofDrySoil(double conductivityofDrySoil);
      void resetConductivityofDrySoil();

      double density() const;
      bool setDensity(double value);

      double densityofDrySoil() const;
      bool isDensityofDrySoilDefaulted() const;
      bool setDensityofDrySoil(double densityofDrySoil);
      void resetDensityofDrySoil();

      double specificHeat() const;
      bool setSpecificHeat(double value);

      double specificHeatofDrySoil() const;
      bool isSpecificHeatofDrySoilDefaulted() const;
      bool setSpecificHeatofDrySoil(double specificHeatofDrySoil);
      void resetSpecificHeatofDrySoil();

      double thermalAbsorptance() const override;
      bool isThermalAbsorptanceDefaulted() const;
      bool setThermalAbsorptance(double thermalAbsorptance) override;
      bool setThermalAbsorptance(boost::optional<double> value);
      void resetThermalAbsorptance();
      boost::optional<double> thermalReflectance() const override;
      bool setThermalReflectance(boost::optional<double> value) override;

      double solarAbsorptance() const override;
      bool isSolarAbsorptanceDefaulted() const;
      bool setSolarAbsorptance(double solarAbsorptance);
      bool setSolarAbsorptance(boost::optional<double> value) override;
      void resetSolarAbsorptance();
      boost::optional<double> solarReflectance() const override;
      bool setSolarReflectance(boost::optional<double> value) override;

      double visibleAbsorptance() const override;
      bool isVisibleAbsorptanceDefaulted() const;
      bool setVisibleAbsorptance(double visibleAbsorptance);
      bool setVisibleAbsorptance(boost::optional<double> value) override;
      void resetVisibleAbsorptance();
      boost::optional<double> visibleReflectance() const override;
      bool setVisibleReflectance(boost::optional<double> value) override;

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

      boost::optional<double> heatCapacity() const override;

      std::vector<std::string> roughnessValues() const;
      std::vector<std::string> moistureDiffusionCalculationMethodValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
