/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONVECTIONALGORITHMINSIDEADAPTIVEMODELSELECTIONS_IMPL_HPP
#define EPMODEL_SURFACECONVECTIONALGORITHMINSIDEADAPTIVEMODELSELECTIONS_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl() override = default;

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
      bool
        setMechanicalZoneFanCirculationStableHorizontalEquationSource(const std::string& mechanicalZoneFanCirculationStableHorizontalEquationSource);
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

      // Choice values helpers (instance delegates to static)
      std::vector<std::string> simpleBuoyancyVerticalWallEquationSourceValues() const;
      std::vector<std::string> simpleBuoyancyStableHorizontalEquationSourceValues() const;
      std::vector<std::string> simpleBuoyancyUnstableHorizontalEquationSourceValues() const;
      std::vector<std::string> simpleBuoyancyStableTiltedEquationSourceValues() const;
      std::vector<std::string> simpleBuoyancyUnstableTiltedEquationSourceValues() const;
      std::vector<std::string> simpleBuoyancyWindowsEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolVerticalWallEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolStableHorizontalEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolUnstableHorizontalEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolHeatedFloorEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolChilledCeilingEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolStableTiltedEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolUnstableTiltedEquationSourceValues() const;
      std::vector<std::string> floorHeatCeilingCoolWindowEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingVerticalWallEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingHeatedWallEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingStableHorizontalEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingUnstableHorizontalEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingStableTiltedEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingUnstableTiltedEquationSourceValues() const;
      std::vector<std::string> wallPanelHeatingWindowEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterVerticalWallEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterVerticalWallsNearHeaterEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterStableHorizontalEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterUnstableHorizontalEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterStableTiltedEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterUnstableTiltedEquationSourceValues() const;
      std::vector<std::string> convectiveZoneHeaterWindowsEquationSourceValues() const;
      std::vector<std::string> centralAirDiffuserWallEquationSourceValues() const;
      std::vector<std::string> centralAirDiffuserCeilingEquationSourceValues() const;
      std::vector<std::string> centralAirDiffuserFloorEquationSourceValues() const;
      std::vector<std::string> centralAirDiffuserWindowEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationVerticalWallEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationStableHorizontalEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationUnstableHorizontalEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationStableTiltedEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationUnstableTiltedEquationSourceValues() const;
      std::vector<std::string> mechanicalZoneFanCirculationWindowEquationSourceValues() const;
      std::vector<std::string> mixedRegimeBuoyancyAssistingFlowonWallsEquationSourceValues() const;
      std::vector<std::string> mixedRegimeBuoyancyOpposingFlowonWallsEquationSourceValues() const;
      std::vector<std::string> mixedRegimeStableFloorEquationSourceValues() const;
      std::vector<std::string> mixedRegimeUnstableFloorEquationSourceValues() const;
      std::vector<std::string> mixedRegimeStableCeilingEquationSourceValues() const;
      std::vector<std::string> mixedRegimeUnstableCeilingEquationSourceValues() const;
      std::vector<std::string> mixedRegimeWindowEquationSourceValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
