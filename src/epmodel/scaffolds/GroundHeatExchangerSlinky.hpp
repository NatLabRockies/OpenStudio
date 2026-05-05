/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATEXCHANGERSLINKY_HPP
#define EPMODEL_GROUNDHEATEXCHANGERSLINKY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatExchangerSlinky_Impl;
  }

  class EPMODEL_API GroundHeatExchangerSlinky : public ModelObject
  {
   public:
    explicit GroundHeatExchangerSlinky(const Model& model);

    virtual ~GroundHeatExchangerSlinky() override = default;
    GroundHeatExchangerSlinky(const GroundHeatExchangerSlinky& other) = default;
    GroundHeatExchangerSlinky(GroundHeatExchangerSlinky&& other) = default;
    GroundHeatExchangerSlinky& operator=(const GroundHeatExchangerSlinky&) = default;
    GroundHeatExchangerSlinky& operator=(GroundHeatExchangerSlinky&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> heatExchangerConfigurationValues();
    static std::vector<std::string> undisturbedGroundTemperatureModelTypeValues();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatExchanger:Slinky numeric/choice fields.
    // - Field Mapping: Inlet Node Name, Outlet Node Name, and Undisturbed Ground Temperature Model Name are relationship-like fields and excluded.
    // - TODO(parity): Add relationship APIs incrementally after scalar saturation.
    double designFlowRate() const;
    bool isDesignFlowRateDefaulted() const;
    bool setDesignFlowRate(double designFlowRate);
    void resetDesignFlowRate();

    double soilThermalConductivity() const;
    bool isSoilThermalConductivityDefaulted() const;
    bool setSoilThermalConductivity(double soilThermalConductivity);
    void resetSoilThermalConductivity();

    double soilDensity() const;
    bool isSoilDensityDefaulted() const;
    bool setSoilDensity(double soilDensity);
    void resetSoilDensity();

    double soilSpecificHeat() const;
    bool isSoilSpecificHeatDefaulted() const;
    bool setSoilSpecificHeat(double soilSpecificHeat);
    void resetSoilSpecificHeat();

    double pipeThermalConductivity() const;
    bool isPipeThermalConductivityDefaulted() const;
    bool setPipeThermalConductivity(double pipeThermalConductivity);
    void resetPipeThermalConductivity();

    double pipeDensity() const;
    bool isPipeDensityDefaulted() const;
    bool setPipeDensity(double pipeDensity);
    void resetPipeDensity();

    double pipeSpecificHeat() const;
    bool isPipeSpecificHeatDefaulted() const;
    bool setPipeSpecificHeat(double pipeSpecificHeat);
    void resetPipeSpecificHeat();

    double pipeOuterDiameter() const;
    bool isPipeOuterDiameterDefaulted() const;
    bool setPipeOuterDiameter(double pipeOuterDiameter);
    void resetPipeOuterDiameter();

    double pipeThickness() const;
    bool isPipeThicknessDefaulted() const;
    bool setPipeThickness(double pipeThickness);
    void resetPipeThickness();

    boost::optional<std::string> heatExchangerConfiguration() const;
    bool setHeatExchangerConfiguration(const std::string& heatExchangerConfiguration);
    void resetHeatExchangerConfiguration();

    double coilDiameter() const;
    bool isCoilDiameterDefaulted() const;
    bool setCoilDiameter(double coilDiameter);
    void resetCoilDiameter();

    double coilPitch() const;
    bool isCoilPitchDefaulted() const;
    bool setCoilPitch(double coilPitch);
    void resetCoilPitch();

    double trenchDepth() const;
    bool isTrenchDepthDefaulted() const;
    bool setTrenchDepth(double trenchDepth);
    void resetTrenchDepth();

    double trenchLength() const;
    bool isTrenchLengthDefaulted() const;
    bool setTrenchLength(double trenchLength);
    void resetTrenchLength();

    int numberofTrenches() const;
    bool isNumberofTrenchesDefaulted() const;
    bool setNumberofTrenches(int numberofTrenches);
    void resetNumberofTrenches();

    double horizontalSpacingBetweenPipes() const;
    bool isHorizontalSpacingBetweenPipesDefaulted() const;
    bool setHorizontalSpacingBetweenPipes(double horizontalSpacingBetweenPipes);
    void resetHorizontalSpacingBetweenPipes();

    std::string undisturbedGroundTemperatureModelType() const;
    bool setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType);

    boost::optional<double> maximumLengthofSimulation() const;
    bool setMaximumLengthofSimulation(double maximumLengthofSimulation);
    void resetMaximumLengthofSimulation();

   protected:
    using ImplType = detail::GroundHeatExchangerSlinky_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatExchangerSlinky(std::shared_ptr<detail::GroundHeatExchangerSlinky_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
