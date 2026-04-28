/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMINSIDEADAPTIVEMODELSELECTIONS_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMINSIDEADAPTIVEMODELSELECTIONS_HPP

#include "../EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl;
  }

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to SurfaceConvectionAlgorithm:Inside:AdaptiveModelSelections choice fields.
  // - Field Mapping: User Curve Name fields (object-list UserConvectionInsideModels) are excluded as relationship fields.
  // - TODO(parity): Add relationship APIs for user curve linkage after scalar saturation.
  class EPMODEL_API SurfaceConvectionAlgorithmInsideAdaptiveModelSelections : public ModelObject
  {
   public:
    explicit SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(const Model& model);

    virtual ~SurfaceConvectionAlgorithmInsideAdaptiveModelSelections() override = default;
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(const SurfaceConvectionAlgorithmInsideAdaptiveModelSelections& other) = default;
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(SurfaceConvectionAlgorithmInsideAdaptiveModelSelections&& other) = default;
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections& operator=(const SurfaceConvectionAlgorithmInsideAdaptiveModelSelections&) = default;
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections& operator=(SurfaceConvectionAlgorithmInsideAdaptiveModelSelections&&) = default;

    static IddObjectType iddObjectType();

    // Choice values helpers
    static std::vector<std::string> simpleBuoyancyVerticalWallEquationSourceValues();
    static std::vector<std::string> simpleBuoyancyStableHorizontalEquationSourceValues();
    static std::vector<std::string> simpleBuoyancyUnstableHorizontalEquationSourceValues();
    static std::vector<std::string> simpleBuoyancyStableTiltedEquationSourceValues();
    static std::vector<std::string> simpleBuoyancyUnstableTiltedEquationSourceValues();
    static std::vector<std::string> simpleBuoyancyWindowsEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolVerticalWallEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolStableHorizontalEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolUnstableHorizontalEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolHeatedFloorEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolChilledCeilingEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolStableTiltedEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolUnstableTiltedEquationSourceValues();
    static std::vector<std::string> floorHeatCeilingCoolWindowEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingVerticalWallEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingHeatedWallEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingStableHorizontalEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingUnstableHorizontalEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingStableTiltedEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingUnstableTiltedEquationSourceValues();
    static std::vector<std::string> wallPanelHeatingWindowEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterVerticalWallEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterVerticalWallsNearHeaterEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterStableHorizontalEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterUnstableHorizontalEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterStableTiltedEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterUnstableTiltedEquationSourceValues();
    static std::vector<std::string> convectiveZoneHeaterWindowsEquationSourceValues();
    static std::vector<std::string> centralAirDiffuserWallEquationSourceValues();
    static std::vector<std::string> centralAirDiffuserCeilingEquationSourceValues();
    static std::vector<std::string> centralAirDiffuserFloorEquationSourceValues();
    static std::vector<std::string> centralAirDiffuserWindowEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationVerticalWallEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationStableHorizontalEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationUnstableHorizontalEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationStableTiltedEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationUnstableTiltedEquationSourceValues();
    static std::vector<std::string> mechanicalZoneFanCirculationWindowEquationSourceValues();
    static std::vector<std::string> mixedRegimeBuoyancyAssistingFlowonWallsEquationSourceValues();
    static std::vector<std::string> mixedRegimeBuoyancyOpposingFlowonWallsEquationSourceValues();
    static std::vector<std::string> mixedRegimeStableFloorEquationSourceValues();
    static std::vector<std::string> mixedRegimeUnstableFloorEquationSourceValues();
    static std::vector<std::string> mixedRegimeStableCeilingEquationSourceValues();
    static std::vector<std::string> mixedRegimeUnstableCeilingEquationSourceValues();
    static std::vector<std::string> mixedRegimeWindowEquationSourceValues();

    // Simple Buoyancy fields
    std::string simpleBuoyancyVerticalWallEquationSource() const;
    bool setSimpleBuoyancyVerticalWallEquationSource(const std::string& simpleBuoyancyVerticalWallEquationSource);
    bool isSimpleBuoyancyVerticalWallEquationSourceDefaulted() const;
    void resetSimpleBuoyancyVerticalWallEquationSource();

    std::string simpleBuoyancyStableHorizontalEquationSource() const;
    bool setSimpleBuoyancyStableHorizontalEquationSource(const std::string& simpleBuoyancyStableHorizontalEquationSource);
    bool isSimpleBuoyancyStableHorizontalEquationSourceDefaulted() const;
    void resetSimpleBuoyancyStableHorizontalEquationSource();

    std::string simpleBuoyancyUnstableHorizontalEquationSource() const;
    bool setSimpleBuoyancyUnstableHorizontalEquationSource(const std::string& simpleBuoyancyUnstableHorizontalEquationSource);
    bool isSimpleBuoyancyUnstableHorizontalEquationSourceDefaulted() const;
    void resetSimpleBuoyancyUnstableHorizontalEquationSource();

    std::string simpleBuoyancyStableTiltedEquationSource() const;
    bool setSimpleBuoyancyStableTiltedEquationSource(const std::string& simpleBuoyancyStableTiltedEquationSource);
    bool isSimpleBuoyancyStableTiltedEquationSourceDefaulted() const;
    void resetSimpleBuoyancyStableTiltedEquationSource();

    std::string simpleBuoyancyUnstableTiltedEquationSource() const;
    bool setSimpleBuoyancyUnstableTiltedEquationSource(const std::string& simpleBuoyancyUnstableTiltedEquationSource);
    bool isSimpleBuoyancyUnstableTiltedEquationSourceDefaulted() const;
    void resetSimpleBuoyancyUnstableTiltedEquationSource();

    std::string simpleBuoyancyWindowsEquationSource() const;
    bool setSimpleBuoyancyWindowsEquationSource(const std::string& simpleBuoyancyWindowsEquationSource);
    bool isSimpleBuoyancyWindowsEquationSourceDefaulted() const;
    void resetSimpleBuoyancyWindowsEquationSource();

    // Floor Heat Ceiling Cool fields
    std::string floorHeatCeilingCoolVerticalWallEquationSource() const;
    bool setFloorHeatCeilingCoolVerticalWallEquationSource(const std::string& floorHeatCeilingCoolVerticalWallEquationSource);
    bool isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolVerticalWallEquationSource();

    std::string floorHeatCeilingCoolStableHorizontalEquationSource() const;
    bool setFloorHeatCeilingCoolStableHorizontalEquationSource(const std::string& floorHeatCeilingCoolStableHorizontalEquationSource);
    bool isFloorHeatCeilingCoolStableHorizontalEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolStableHorizontalEquationSource();

    std::string floorHeatCeilingCoolUnstableHorizontalEquationSource() const;
    bool setFloorHeatCeilingCoolUnstableHorizontalEquationSource(const std::string& floorHeatCeilingCoolUnstableHorizontalEquationSource);
    bool isFloorHeatCeilingCoolUnstableHorizontalEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolUnstableHorizontalEquationSource();

    std::string floorHeatCeilingCoolHeatedFloorEquationSource() const;
    bool setFloorHeatCeilingCoolHeatedFloorEquationSource(const std::string& floorHeatCeilingCoolHeatedFloorEquationSource);
    bool isFloorHeatCeilingCoolHeatedFloorEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolHeatedFloorEquationSource();

    std::string floorHeatCeilingCoolChilledCeilingEquationSource() const;
    bool setFloorHeatCeilingCoolChilledCeilingEquationSource(const std::string& floorHeatCeilingCoolChilledCeilingEquationSource);
    bool isFloorHeatCeilingCoolChilledCeilingEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolChilledCeilingEquationSource();

    std::string floorHeatCeilingCoolStableTiltedEquationSource() const;
    bool setFloorHeatCeilingCoolStableTiltedEquationSource(const std::string& floorHeatCeilingCoolStableTiltedEquationSource);
    bool isFloorHeatCeilingCoolStableTiltedEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolStableTiltedEquationSource();

    std::string floorHeatCeilingCoolUnstableTiltedEquationSource() const;
    bool setFloorHeatCeilingCoolUnstableTiltedEquationSource(const std::string& floorHeatCeilingCoolUnstableTiltedEquationSource);
    bool isFloorHeatCeilingCoolUnstableTiltedEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolUnstableTiltedEquationSource();

    std::string floorHeatCeilingCoolWindowEquationSource() const;
    bool setFloorHeatCeilingCoolWindowEquationSource(const std::string& floorHeatCeilingCoolWindowEquationSource);
    bool isFloorHeatCeilingCoolWindowEquationSourceDefaulted() const;
    void resetFloorHeatCeilingCoolWindowEquationSource();

    // Wall Panel Heating fields
    std::string wallPanelHeatingVerticalWallEquationSource() const;
    bool setWallPanelHeatingVerticalWallEquationSource(const std::string& wallPanelHeatingVerticalWallEquationSource);
    bool isWallPanelHeatingVerticalWallEquationSourceDefaulted() const;
    void resetWallPanelHeatingVerticalWallEquationSource();

    std::string wallPanelHeatingHeatedWallEquationSource() const;
    bool setWallPanelHeatingHeatedWallEquationSource(const std::string& wallPanelHeatingHeatedWallEquationSource);
    bool isWallPanelHeatingHeatedWallEquationSourceDefaulted() const;
    void resetWallPanelHeatingHeatedWallEquationSource();

    std::string wallPanelHeatingStableHorizontalEquationSource() const;
    bool setWallPanelHeatingStableHorizontalEquationSource(const std::string& wallPanelHeatingStableHorizontalEquationSource);
    bool isWallPanelHeatingStableHorizontalEquationSourceDefaulted() const;
    void resetWallPanelHeatingStableHorizontalEquationSource();

    std::string wallPanelHeatingUnstableHorizontalEquationSource() const;
    bool setWallPanelHeatingUnstableHorizontalEquationSource(const std::string& wallPanelHeatingUnstableHorizontalEquationSource);
    bool isWallPanelHeatingUnstableHorizontalEquationSourceDefaulted() const;
    void resetWallPanelHeatingUnstableHorizontalEquationSource();

    std::string wallPanelHeatingStableTiltedEquationSource() const;
    bool setWallPanelHeatingStableTiltedEquationSource(const std::string& wallPanelHeatingStableTiltedEquationSource);
    bool isWallPanelHeatingStableTiltedEquationSourceDefaulted() const;
    void resetWallPanelHeatingStableTiltedEquationSource();

    std::string wallPanelHeatingUnstableTiltedEquationSource() const;
    bool setWallPanelHeatingUnstableTiltedEquationSource(const std::string& wallPanelHeatingUnstableTiltedEquationSource);
    bool isWallPanelHeatingUnstableTiltedEquationSourceDefaulted() const;
    void resetWallPanelHeatingUnstableTiltedEquationSource();

    std::string wallPanelHeatingWindowEquationSource() const;
    bool setWallPanelHeatingWindowEquationSource(const std::string& wallPanelHeatingWindowEquationSource);
    bool isWallPanelHeatingWindowEquationSourceDefaulted() const;
    void resetWallPanelHeatingWindowEquationSource();

    // Convective Zone Heater fields
    std::string convectiveZoneHeaterVerticalWallEquationSource() const;
    bool setConvectiveZoneHeaterVerticalWallEquationSource(const std::string& convectiveZoneHeaterVerticalWallEquationSource);
    bool isConvectiveZoneHeaterVerticalWallEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterVerticalWallEquationSource();

    std::string convectiveZoneHeaterVerticalWallsNearHeaterEquationSource() const;
    bool setConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource(const std::string& convectiveZoneHeaterVerticalWallsNearHeaterEquationSource);
    bool isConvectiveZoneHeaterVerticalWallsNearHeaterEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource();

    std::string convectiveZoneHeaterStableHorizontalEquationSource() const;
    bool setConvectiveZoneHeaterStableHorizontalEquationSource(const std::string& convectiveZoneHeaterStableHorizontalEquationSource);
    bool isConvectiveZoneHeaterStableHorizontalEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterStableHorizontalEquationSource();

    std::string convectiveZoneHeaterUnstableHorizontalEquationSource() const;
    bool setConvectiveZoneHeaterUnstableHorizontalEquationSource(const std::string& convectiveZoneHeaterUnstableHorizontalEquationSource);
    bool isConvectiveZoneHeaterUnstableHorizontalEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterUnstableHorizontalEquationSource();

    std::string convectiveZoneHeaterStableTiltedEquationSource() const;
    bool setConvectiveZoneHeaterStableTiltedEquationSource(const std::string& convectiveZoneHeaterStableTiltedEquationSource);
    bool isConvectiveZoneHeaterStableTiltedEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterStableTiltedEquationSource();

    std::string convectiveZoneHeaterUnstableTiltedEquationSource() const;
    bool setConvectiveZoneHeaterUnstableTiltedEquationSource(const std::string& convectiveZoneHeaterUnstableTiltedEquationSource);
    bool isConvectiveZoneHeaterUnstableTiltedEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterUnstableTiltedEquationSource();

    std::string convectiveZoneHeaterWindowsEquationSource() const;
    bool setConvectiveZoneHeaterWindowsEquationSource(const std::string& convectiveZoneHeaterWindowsEquationSource);
    bool isConvectiveZoneHeaterWindowsEquationSourceDefaulted() const;
    void resetConvectiveZoneHeaterWindowsEquationSource();

    // Central Air Diffuser fields
    std::string centralAirDiffuserWallEquationSource() const;
    bool setCentralAirDiffuserWallEquationSource(const std::string& centralAirDiffuserWallEquationSource);
    bool isCentralAirDiffuserWallEquationSourceDefaulted() const;
    void resetCentralAirDiffuserWallEquationSource();

    std::string centralAirDiffuserCeilingEquationSource() const;
    bool setCentralAirDiffuserCeilingEquationSource(const std::string& centralAirDiffuserCeilingEquationSource);
    bool isCentralAirDiffuserCeilingEquationSourceDefaulted() const;
    void resetCentralAirDiffuserCeilingEquationSource();

    std::string centralAirDiffuserFloorEquationSource() const;
    bool setCentralAirDiffuserFloorEquationSource(const std::string& centralAirDiffuserFloorEquationSource);
    bool isCentralAirDiffuserFloorEquationSourceDefaulted() const;
    void resetCentralAirDiffuserFloorEquationSource();

    std::string centralAirDiffuserWindowEquationSource() const;
    bool setCentralAirDiffuserWindowEquationSource(const std::string& centralAirDiffuserWindowEquationSource);
    bool isCentralAirDiffuserWindowEquationSourceDefaulted() const;
    void resetCentralAirDiffuserWindowEquationSource();

    // Mechanical Zone Fan Circulation fields
    std::string mechanicalZoneFanCirculationVerticalWallEquationSource() const;
    bool setMechanicalZoneFanCirculationVerticalWallEquationSource(const std::string& mechanicalZoneFanCirculationVerticalWallEquationSource);
    bool isMechanicalZoneFanCirculationVerticalWallEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationVerticalWallEquationSource();

    std::string mechanicalZoneFanCirculationStableHorizontalEquationSource() const;
    bool setMechanicalZoneFanCirculationStableHorizontalEquationSource(const std::string& mechanicalZoneFanCirculationStableHorizontalEquationSource);
    bool isMechanicalZoneFanCirculationStableHorizontalEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationStableHorizontalEquationSource();

    std::string mechanicalZoneFanCirculationUnstableHorizontalEquationSource() const;
    bool setMechanicalZoneFanCirculationUnstableHorizontalEquationSource(
      const std::string& mechanicalZoneFanCirculationUnstableHorizontalEquationSource);
    bool isMechanicalZoneFanCirculationUnstableHorizontalEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationUnstableHorizontalEquationSource();

    std::string mechanicalZoneFanCirculationStableTiltedEquationSource() const;
    bool setMechanicalZoneFanCirculationStableTiltedEquationSource(const std::string& mechanicalZoneFanCirculationStableTiltedEquationSource);
    bool isMechanicalZoneFanCirculationStableTiltedEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationStableTiltedEquationSource();

    std::string mechanicalZoneFanCirculationUnstableTiltedEquationSource() const;
    bool setMechanicalZoneFanCirculationUnstableTiltedEquationSource(const std::string& mechanicalZoneFanCirculationUnstableTiltedEquationSource);
    bool isMechanicalZoneFanCirculationUnstableTiltedEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationUnstableTiltedEquationSource();

    std::string mechanicalZoneFanCirculationWindowEquationSource() const;
    bool setMechanicalZoneFanCirculationWindowEquationSource(const std::string& mechanicalZoneFanCirculationWindowEquationSource);
    bool isMechanicalZoneFanCirculationWindowEquationSourceDefaulted() const;
    void resetMechanicalZoneFanCirculationWindowEquationSource();

    // Mixed Regime fields
    std::string mixedRegimeBuoyancyAssistingFlowonWallsEquationSource() const;
    bool setMixedRegimeBuoyancyAssistingFlowonWallsEquationSource(const std::string& mixedRegimeBuoyancyAssistingFlowonWallsEquationSource);
    bool isMixedRegimeBuoyancyAssistingFlowonWallsEquationSourceDefaulted() const;
    void resetMixedRegimeBuoyancyAssistingFlowonWallsEquationSource();

    std::string mixedRegimeBuoyancyOpposingFlowonWallsEquationSource() const;
    bool setMixedRegimeBuoyancyOpposingFlowonWallsEquationSource(const std::string& mixedRegimeBuoyancyOpposingFlowonWallsEquationSource);
    bool isMixedRegimeBuoyancyOpposingFlowonWallsEquationSourceDefaulted() const;
    void resetMixedRegimeBuoyancyOpposingFlowonWallsEquationSource();

    std::string mixedRegimeStableFloorEquationSource() const;
    bool setMixedRegimeStableFloorEquationSource(const std::string& mixedRegimeStableFloorEquationSource);
    bool isMixedRegimeStableFloorEquationSourceDefaulted() const;
    void resetMixedRegimeStableFloorEquationSource();

    std::string mixedRegimeUnstableFloorEquationSource() const;
    bool setMixedRegimeUnstableFloorEquationSource(const std::string& mixedRegimeUnstableFloorEquationSource);
    bool isMixedRegimeUnstableFloorEquationSourceDefaulted() const;
    void resetMixedRegimeUnstableFloorEquationSource();

    std::string mixedRegimeStableCeilingEquationSource() const;
    bool setMixedRegimeStableCeilingEquationSource(const std::string& mixedRegimeStableCeilingEquationSource);
    bool isMixedRegimeStableCeilingEquationSourceDefaulted() const;
    void resetMixedRegimeStableCeilingEquationSource();

    std::string mixedRegimeUnstableCeilingEquationSource() const;
    bool setMixedRegimeUnstableCeilingEquationSource(const std::string& mixedRegimeUnstableCeilingEquationSource);
    bool isMixedRegimeUnstableCeilingEquationSourceDefaulted() const;
    void resetMixedRegimeUnstableCeilingEquationSource();

    std::string mixedRegimeWindowEquationSource() const;
    bool setMixedRegimeWindowEquationSource(const std::string& mixedRegimeWindowEquationSource);
    bool isMixedRegimeWindowEquationSourceDefaulted() const;
    void resetMixedRegimeWindowEquationSource();

   protected:
    using ImplType = detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(
      std::shared_ptr<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
