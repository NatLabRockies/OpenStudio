/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SurfaceConvectionAlgorithmInsideAdaptiveModelSelections.hpp"
#include "SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelections_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>

namespace openstudio {
namespace epmodel {

  SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(const Model& model)
    : ModelObject(SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::iddObjectType(), model) {}

  SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections(
    std::shared_ptr<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::iddObjectType() {
    return IddObjectType::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelections;
  }

  // ===== Static Values helpers =====

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyVerticalWallEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyVerticalWallEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyStableHorizontalEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyStableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyUnstableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyStableTiltedEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyStableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyUnstableTiltedEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyUnstableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyWindowsEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::SimpleBuoyancyWindowsEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolVerticalWallEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolVerticalWallEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolStableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolHeatedFloorEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolHeatedFloorEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolChilledCeilingEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolChilledCeilingEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolStableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolStableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolUnstableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolUnstableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolWindowEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::FloorHeatCeilingCoolWindowEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingVerticalWallEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingVerticalWallEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingHeatedWallEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingHeatedWallEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingStableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingStableTiltedEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingStableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingUnstableTiltedEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingUnstableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingWindowEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::WallPanelHeatingWindowEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterVerticalWallEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallEquationSource);
  }

  std::vector<std::string>
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterVerticalWallsNearHeaterEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterStableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterStableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterStableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterUnstableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterUnstableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterWindowsEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::ConvectiveZoneHeaterWindowsEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserWallEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWallEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserCeilingEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserCeilingEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserFloorEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserFloorEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserWindowEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::CentralAirDiffuserWindowEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationVerticalWallEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationVerticalWallEquationSource);
  }

  std::vector<std::string>
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationStableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableHorizontalEquationSource);
  }

  std::vector<std::string>
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationUnstableHorizontalEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableHorizontalEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationStableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationStableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationUnstableTiltedEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationUnstableTiltedEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationWindowEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MechanicalZoneFanCirculationWindowEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeBuoyancyAssistingFlowonWallsEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBuoyancyAssistingFlowonWallsEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeBuoyancyOpposingFlowonWallsEquationSourceValues() {
    return getIddKeyNames(
      IddFactory::instance().getObject(iddObjectType()).get(),
      openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeBuoyancyOpposingFlowonWallsEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeStableFloorEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableFloorEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeUnstableFloorEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableFloorEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeStableCeilingEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeStableCeilingEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeUnstableCeilingEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeUnstableCeilingEquationSource);
  }

  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeWindowEquationSourceValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields::MixedRegimeWindowEquationSource);
  }

  // ===== Public API delegating to Impl =====

  // Simple Buoyancy
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyVerticalWallEquationSource(
    const std::string& simpleBuoyancyVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyVerticalWallEquationSource(
      simpleBuoyancyVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isSimpleBuoyancyVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyVerticalWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyStableHorizontalEquationSource(
    const std::string& simpleBuoyancyStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyStableHorizontalEquationSource(
      simpleBuoyancyStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isSimpleBuoyancyStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyStableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyUnstableHorizontalEquationSource(
    const std::string& simpleBuoyancyUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyUnstableHorizontalEquationSource(
      simpleBuoyancyUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isSimpleBuoyancyUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyUnstableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyStableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyStableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyStableTiltedEquationSource(
    const std::string& simpleBuoyancyStableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyStableTiltedEquationSource(
      simpleBuoyancyStableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyStableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isSimpleBuoyancyStableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyStableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyStableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyUnstableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyUnstableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyUnstableTiltedEquationSource(
    const std::string& simpleBuoyancyUnstableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyUnstableTiltedEquationSource(
      simpleBuoyancyUnstableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyUnstableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isSimpleBuoyancyUnstableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyUnstableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyUnstableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::simpleBuoyancyWindowsEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->simpleBuoyancyWindowsEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setSimpleBuoyancyWindowsEquationSource(
    const std::string& simpleBuoyancyWindowsEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setSimpleBuoyancyWindowsEquationSource(
      simpleBuoyancyWindowsEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isSimpleBuoyancyWindowsEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isSimpleBuoyancyWindowsEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetSimpleBuoyancyWindowsEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetSimpleBuoyancyWindowsEquationSource();
  }

  // Floor Heat Ceiling Cool
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolVerticalWallEquationSource(
    const std::string& floorHeatCeilingCoolVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolVerticalWallEquationSource(
      floorHeatCeilingCoolVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolVerticalWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolStableHorizontalEquationSource(
    const std::string& floorHeatCeilingCoolStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolStableHorizontalEquationSource(
      floorHeatCeilingCoolStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolStableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolUnstableHorizontalEquationSource(
    const std::string& floorHeatCeilingCoolUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolUnstableHorizontalEquationSource(
      floorHeatCeilingCoolUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolUnstableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolHeatedFloorEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolHeatedFloorEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolHeatedFloorEquationSource(
    const std::string& floorHeatCeilingCoolHeatedFloorEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolHeatedFloorEquationSource(
      floorHeatCeilingCoolHeatedFloorEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolHeatedFloorEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolHeatedFloorEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolHeatedFloorEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolHeatedFloorEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolChilledCeilingEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolChilledCeilingEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolChilledCeilingEquationSource(
    const std::string& floorHeatCeilingCoolChilledCeilingEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolChilledCeilingEquationSource(
      floorHeatCeilingCoolChilledCeilingEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolChilledCeilingEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolChilledCeilingEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolChilledCeilingEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolChilledCeilingEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolStableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolStableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolStableTiltedEquationSource(
    const std::string& floorHeatCeilingCoolStableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolStableTiltedEquationSource(
      floorHeatCeilingCoolStableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolStableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolStableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolStableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolStableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolUnstableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolUnstableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolUnstableTiltedEquationSource(
    const std::string& floorHeatCeilingCoolUnstableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolUnstableTiltedEquationSource(
      floorHeatCeilingCoolUnstableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolUnstableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isFloorHeatCeilingCoolUnstableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolUnstableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolUnstableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::floorHeatCeilingCoolWindowEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->floorHeatCeilingCoolWindowEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setFloorHeatCeilingCoolWindowEquationSource(
    const std::string& floorHeatCeilingCoolWindowEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setFloorHeatCeilingCoolWindowEquationSource(
      floorHeatCeilingCoolWindowEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isFloorHeatCeilingCoolWindowEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isFloorHeatCeilingCoolWindowEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetFloorHeatCeilingCoolWindowEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetFloorHeatCeilingCoolWindowEquationSource();
  }

  // Wall Panel Heating
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingVerticalWallEquationSource(
    const std::string& wallPanelHeatingVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingVerticalWallEquationSource(
      wallPanelHeatingVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isWallPanelHeatingVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingVerticalWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingHeatedWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingHeatedWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingHeatedWallEquationSource(
    const std::string& wallPanelHeatingHeatedWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingHeatedWallEquationSource(
      wallPanelHeatingHeatedWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingHeatedWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isWallPanelHeatingHeatedWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingHeatedWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingHeatedWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingStableHorizontalEquationSource(
    const std::string& wallPanelHeatingStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingStableHorizontalEquationSource(
      wallPanelHeatingStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isWallPanelHeatingStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingStableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingUnstableHorizontalEquationSource(
    const std::string& wallPanelHeatingUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingUnstableHorizontalEquationSource(
      wallPanelHeatingUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isWallPanelHeatingUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingUnstableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingStableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingStableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingStableTiltedEquationSource(
    const std::string& wallPanelHeatingStableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingStableTiltedEquationSource(
      wallPanelHeatingStableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingStableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isWallPanelHeatingStableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingStableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingStableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingUnstableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingUnstableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingUnstableTiltedEquationSource(
    const std::string& wallPanelHeatingUnstableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingUnstableTiltedEquationSource(
      wallPanelHeatingUnstableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingUnstableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isWallPanelHeatingUnstableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingUnstableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingUnstableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::wallPanelHeatingWindowEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->wallPanelHeatingWindowEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setWallPanelHeatingWindowEquationSource(
    const std::string& wallPanelHeatingWindowEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setWallPanelHeatingWindowEquationSource(
      wallPanelHeatingWindowEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isWallPanelHeatingWindowEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isWallPanelHeatingWindowEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetWallPanelHeatingWindowEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetWallPanelHeatingWindowEquationSource();
  }

  // Convective Zone Heater
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterVerticalWallEquationSource(
    const std::string& convectiveZoneHeaterVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterVerticalWallEquationSource(
      convectiveZoneHeaterVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterVerticalWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterVerticalWallsNearHeaterEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->convectiveZoneHeaterVerticalWallsNearHeaterEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource(
    const std::string& convectiveZoneHeaterVerticalWallsNearHeaterEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->setConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource(convectiveZoneHeaterVerticalWallsNearHeaterEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterVerticalWallsNearHeaterEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterVerticalWallsNearHeaterEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterStableHorizontalEquationSource(
    const std::string& convectiveZoneHeaterStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterStableHorizontalEquationSource(
      convectiveZoneHeaterStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterStableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterUnstableHorizontalEquationSource(
    const std::string& convectiveZoneHeaterUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterUnstableHorizontalEquationSource(
      convectiveZoneHeaterUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterUnstableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterStableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterStableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterStableTiltedEquationSource(
    const std::string& convectiveZoneHeaterStableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterStableTiltedEquationSource(
      convectiveZoneHeaterStableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterStableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterStableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterStableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterStableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterUnstableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterUnstableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterUnstableTiltedEquationSource(
    const std::string& convectiveZoneHeaterUnstableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterUnstableTiltedEquationSource(
      convectiveZoneHeaterUnstableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterUnstableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isConvectiveZoneHeaterUnstableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterUnstableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterUnstableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::convectiveZoneHeaterWindowsEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->convectiveZoneHeaterWindowsEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setConvectiveZoneHeaterWindowsEquationSource(
    const std::string& convectiveZoneHeaterWindowsEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setConvectiveZoneHeaterWindowsEquationSource(
      convectiveZoneHeaterWindowsEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isConvectiveZoneHeaterWindowsEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isConvectiveZoneHeaterWindowsEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetConvectiveZoneHeaterWindowsEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetConvectiveZoneHeaterWindowsEquationSource();
  }

  // Central Air Diffuser
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->centralAirDiffuserWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setCentralAirDiffuserWallEquationSource(
    const std::string& centralAirDiffuserWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setCentralAirDiffuserWallEquationSource(
      centralAirDiffuserWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isCentralAirDiffuserWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isCentralAirDiffuserWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetCentralAirDiffuserWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetCentralAirDiffuserWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserCeilingEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->centralAirDiffuserCeilingEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setCentralAirDiffuserCeilingEquationSource(
    const std::string& centralAirDiffuserCeilingEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setCentralAirDiffuserCeilingEquationSource(
      centralAirDiffuserCeilingEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isCentralAirDiffuserCeilingEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isCentralAirDiffuserCeilingEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetCentralAirDiffuserCeilingEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetCentralAirDiffuserCeilingEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserFloorEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->centralAirDiffuserFloorEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setCentralAirDiffuserFloorEquationSource(
    const std::string& centralAirDiffuserFloorEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setCentralAirDiffuserFloorEquationSource(
      centralAirDiffuserFloorEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isCentralAirDiffuserFloorEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isCentralAirDiffuserFloorEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetCentralAirDiffuserFloorEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetCentralAirDiffuserFloorEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::centralAirDiffuserWindowEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->centralAirDiffuserWindowEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setCentralAirDiffuserWindowEquationSource(
    const std::string& centralAirDiffuserWindowEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setCentralAirDiffuserWindowEquationSource(
      centralAirDiffuserWindowEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isCentralAirDiffuserWindowEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isCentralAirDiffuserWindowEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetCentralAirDiffuserWindowEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetCentralAirDiffuserWindowEquationSource();
  }

  // Mechanical Zone Fan Circulation
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationVerticalWallEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mechanicalZoneFanCirculationVerticalWallEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationVerticalWallEquationSource(
    const std::string& mechanicalZoneFanCirculationVerticalWallEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMechanicalZoneFanCirculationVerticalWallEquationSource(
      mechanicalZoneFanCirculationVerticalWallEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationVerticalWallEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationVerticalWallEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationVerticalWallEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMechanicalZoneFanCirculationVerticalWallEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationStableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->mechanicalZoneFanCirculationStableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationStableHorizontalEquationSource(
    const std::string& mechanicalZoneFanCirculationStableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->setMechanicalZoneFanCirculationStableHorizontalEquationSource(mechanicalZoneFanCirculationStableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationStableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationStableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationStableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->resetMechanicalZoneFanCirculationStableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationUnstableHorizontalEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->mechanicalZoneFanCirculationUnstableHorizontalEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationUnstableHorizontalEquationSource(
    const std::string& mechanicalZoneFanCirculationUnstableHorizontalEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->setMechanicalZoneFanCirculationUnstableHorizontalEquationSource(mechanicalZoneFanCirculationUnstableHorizontalEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationUnstableHorizontalEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationUnstableHorizontalEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationUnstableHorizontalEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->resetMechanicalZoneFanCirculationUnstableHorizontalEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationStableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mechanicalZoneFanCirculationStableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationStableTiltedEquationSource(
    const std::string& mechanicalZoneFanCirculationStableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMechanicalZoneFanCirculationStableTiltedEquationSource(
      mechanicalZoneFanCirculationStableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationStableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationStableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationStableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMechanicalZoneFanCirculationStableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationUnstableTiltedEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->mechanicalZoneFanCirculationUnstableTiltedEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationUnstableTiltedEquationSource(
    const std::string& mechanicalZoneFanCirculationUnstableTiltedEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->setMechanicalZoneFanCirculationUnstableTiltedEquationSource(mechanicalZoneFanCirculationUnstableTiltedEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationUnstableTiltedEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationUnstableTiltedEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationUnstableTiltedEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMechanicalZoneFanCirculationUnstableTiltedEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mechanicalZoneFanCirculationWindowEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mechanicalZoneFanCirculationWindowEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMechanicalZoneFanCirculationWindowEquationSource(
    const std::string& mechanicalZoneFanCirculationWindowEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMechanicalZoneFanCirculationWindowEquationSource(
      mechanicalZoneFanCirculationWindowEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMechanicalZoneFanCirculationWindowEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMechanicalZoneFanCirculationWindowEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMechanicalZoneFanCirculationWindowEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMechanicalZoneFanCirculationWindowEquationSource();
  }

  // Mixed Regime
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeBuoyancyAssistingFlowonWallsEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeBuoyancyAssistingFlowonWallsEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeBuoyancyAssistingFlowonWallsEquationSource(
    const std::string& mixedRegimeBuoyancyAssistingFlowonWallsEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeBuoyancyAssistingFlowonWallsEquationSource(
      mixedRegimeBuoyancyAssistingFlowonWallsEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeBuoyancyAssistingFlowonWallsEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMixedRegimeBuoyancyAssistingFlowonWallsEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeBuoyancyAssistingFlowonWallsEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeBuoyancyAssistingFlowonWallsEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeBuoyancyOpposingFlowonWallsEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeBuoyancyOpposingFlowonWallsEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeBuoyancyOpposingFlowonWallsEquationSource(
    const std::string& mixedRegimeBuoyancyOpposingFlowonWallsEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeBuoyancyOpposingFlowonWallsEquationSource(
      mixedRegimeBuoyancyOpposingFlowonWallsEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeBuoyancyOpposingFlowonWallsEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()
      ->isMixedRegimeBuoyancyOpposingFlowonWallsEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeBuoyancyOpposingFlowonWallsEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeBuoyancyOpposingFlowonWallsEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeStableFloorEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeStableFloorEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeStableFloorEquationSource(
    const std::string& mixedRegimeStableFloorEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeStableFloorEquationSource(
      mixedRegimeStableFloorEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeStableFloorEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isMixedRegimeStableFloorEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeStableFloorEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeStableFloorEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeUnstableFloorEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeUnstableFloorEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeUnstableFloorEquationSource(
    const std::string& mixedRegimeUnstableFloorEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeUnstableFloorEquationSource(
      mixedRegimeUnstableFloorEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeUnstableFloorEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isMixedRegimeUnstableFloorEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeUnstableFloorEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeUnstableFloorEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeStableCeilingEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeStableCeilingEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeStableCeilingEquationSource(
    const std::string& mixedRegimeStableCeilingEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeStableCeilingEquationSource(
      mixedRegimeStableCeilingEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeStableCeilingEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isMixedRegimeStableCeilingEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeStableCeilingEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeStableCeilingEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeUnstableCeilingEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeUnstableCeilingEquationSource();
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeUnstableCeilingEquationSource(
    const std::string& mixedRegimeUnstableCeilingEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeUnstableCeilingEquationSource(
      mixedRegimeUnstableCeilingEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeUnstableCeilingEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isMixedRegimeUnstableCeilingEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeUnstableCeilingEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeUnstableCeilingEquationSource();
  }

  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::mixedRegimeWindowEquationSource() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->mixedRegimeWindowEquationSource();
  }
  bool
    SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::setMixedRegimeWindowEquationSource(const std::string& mixedRegimeWindowEquationSource) {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->setMixedRegimeWindowEquationSource(
      mixedRegimeWindowEquationSource);
  }
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::isMixedRegimeWindowEquationSourceDefaulted() const {
    return getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->isMixedRegimeWindowEquationSourceDefaulted();
  }
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::resetMixedRegimeWindowEquationSource() {
    getImpl<detail::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl>()->resetMixedRegimeWindowEquationSource();
  }

}  // namespace epmodel
}  // namespace openstudio

// ===== Impl definitions =====

namespace openstudio {
namespace epmodel {
  namespace detail {

    using F = openstudio::SurfaceConvectionAlgorithm_Inside_AdaptiveModelSelectionsFields;

// Macro to reduce boilerplate for choice fields with default
#define CHOICE_GETTER(FieldName, FieldEnum)                                                     \
  std::string SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl::FieldName() const { \
    const auto value = getString(F::FieldEnum, true);                                           \
    OS_ASSERT(value);                                                                           \
    return *value;                                                                              \
  }

#define CHOICE_SETTER(FieldName, FieldEnum)                                                                   \
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl::set##FieldName(const std::string& val) { \
    return setString(F::FieldEnum, val);                                                                      \
  }

#define CHOICE_ISDEFAULTED(FieldName, FieldEnum)                                                        \
  bool SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl::is##FieldName##Defaulted() const { \
    return isEmpty(F::FieldEnum);                                                                       \
  }

#define CHOICE_RESET(FieldName, FieldEnum)                                                \
  void SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl::reset##FieldName() { \
    OS_ASSERT(setString(F::FieldEnum, ""));                                               \
  }

#define CHOICE_VALUES(fieldName, FieldEnum)                                                                          \
  std::vector<std::string> SurfaceConvectionAlgorithmInsideAdaptiveModelSelections_Impl::fieldName##Values() const { \
    return openstudio::epmodel::SurfaceConvectionAlgorithmInsideAdaptiveModelSelections::fieldName##Values();        \
  }

#define CHOICE_FIELD(FieldName, fieldName, FieldEnum) \
  CHOICE_GETTER(fieldName, FieldEnum)                 \
  CHOICE_SETTER(FieldName, FieldEnum)                 \
  CHOICE_ISDEFAULTED(FieldName, FieldEnum)            \
  CHOICE_RESET(FieldName, FieldEnum)                  \
  CHOICE_VALUES(fieldName, FieldEnum)

    // Simple Buoyancy
    CHOICE_FIELD(SimpleBuoyancyVerticalWallEquationSource, simpleBuoyancyVerticalWallEquationSource, SimpleBuoyancyVerticalWallEquationSource)
    CHOICE_FIELD(SimpleBuoyancyStableHorizontalEquationSource, simpleBuoyancyStableHorizontalEquationSource,
                 SimpleBuoyancyStableHorizontalEquationSource)
    CHOICE_FIELD(SimpleBuoyancyUnstableHorizontalEquationSource, simpleBuoyancyUnstableHorizontalEquationSource,
                 SimpleBuoyancyUnstableHorizontalEquationSource)
    CHOICE_FIELD(SimpleBuoyancyStableTiltedEquationSource, simpleBuoyancyStableTiltedEquationSource, SimpleBuoyancyStableTiltedEquationSource)
    CHOICE_FIELD(SimpleBuoyancyUnstableTiltedEquationSource, simpleBuoyancyUnstableTiltedEquationSource, SimpleBuoyancyUnstableTiltedEquationSource)
    CHOICE_FIELD(SimpleBuoyancyWindowsEquationSource, simpleBuoyancyWindowsEquationSource, SimpleBuoyancyWindowsEquationSource)

    // Floor Heat Ceiling Cool
    CHOICE_FIELD(FloorHeatCeilingCoolVerticalWallEquationSource, floorHeatCeilingCoolVerticalWallEquationSource,
                 FloorHeatCeilingCoolVerticalWallEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolStableHorizontalEquationSource, floorHeatCeilingCoolStableHorizontalEquationSource,
                 FloorHeatCeilingCoolStableHorizontalEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolUnstableHorizontalEquationSource, floorHeatCeilingCoolUnstableHorizontalEquationSource,
                 FloorHeatCeilingCoolUnstableHorizontalEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolHeatedFloorEquationSource, floorHeatCeilingCoolHeatedFloorEquationSource,
                 FloorHeatCeilingCoolHeatedFloorEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolChilledCeilingEquationSource, floorHeatCeilingCoolChilledCeilingEquationSource,
                 FloorHeatCeilingCoolChilledCeilingEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolStableTiltedEquationSource, floorHeatCeilingCoolStableTiltedEquationSource,
                 FloorHeatCeilingCoolStableTiltedEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolUnstableTiltedEquationSource, floorHeatCeilingCoolUnstableTiltedEquationSource,
                 FloorHeatCeilingCoolUnstableTiltedEquationSource)
    CHOICE_FIELD(FloorHeatCeilingCoolWindowEquationSource, floorHeatCeilingCoolWindowEquationSource, FloorHeatCeilingCoolWindowEquationSource)

    // Wall Panel Heating
    CHOICE_FIELD(WallPanelHeatingVerticalWallEquationSource, wallPanelHeatingVerticalWallEquationSource, WallPanelHeatingVerticalWallEquationSource)
    CHOICE_FIELD(WallPanelHeatingHeatedWallEquationSource, wallPanelHeatingHeatedWallEquationSource, WallPanelHeatingHeatedWallEquationSource)
    CHOICE_FIELD(WallPanelHeatingStableHorizontalEquationSource, wallPanelHeatingStableHorizontalEquationSource,
                 WallPanelHeatingStableHorizontalEquationSource)
    CHOICE_FIELD(WallPanelHeatingUnstableHorizontalEquationSource, wallPanelHeatingUnstableHorizontalEquationSource,
                 WallPanelHeatingUnstableHorizontalEquationSource)
    CHOICE_FIELD(WallPanelHeatingStableTiltedEquationSource, wallPanelHeatingStableTiltedEquationSource, WallPanelHeatingStableTiltedEquationSource)
    CHOICE_FIELD(WallPanelHeatingUnstableTiltedEquationSource, wallPanelHeatingUnstableTiltedEquationSource,
                 WallPanelHeatingUnstableTiltedEquationSource)
    CHOICE_FIELD(WallPanelHeatingWindowEquationSource, wallPanelHeatingWindowEquationSource, WallPanelHeatingWindowEquationSource)

    // Convective Zone Heater
    CHOICE_FIELD(ConvectiveZoneHeaterVerticalWallEquationSource, convectiveZoneHeaterVerticalWallEquationSource,
                 ConvectiveZoneHeaterVerticalWallEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource, convectiveZoneHeaterVerticalWallsNearHeaterEquationSource,
                 ConvectiveZoneHeaterVerticalWallsNearHeaterEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterStableHorizontalEquationSource, convectiveZoneHeaterStableHorizontalEquationSource,
                 ConvectiveZoneHeaterStableHorizontalEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterUnstableHorizontalEquationSource, convectiveZoneHeaterUnstableHorizontalEquationSource,
                 ConvectiveZoneHeaterUnstableHorizontalEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterStableTiltedEquationSource, convectiveZoneHeaterStableTiltedEquationSource,
                 ConvectiveZoneHeaterStableTiltedEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterUnstableTiltedEquationSource, convectiveZoneHeaterUnstableTiltedEquationSource,
                 ConvectiveZoneHeaterUnstableTiltedEquationSource)
    CHOICE_FIELD(ConvectiveZoneHeaterWindowsEquationSource, convectiveZoneHeaterWindowsEquationSource, ConvectiveZoneHeaterWindowsEquationSource)

    // Central Air Diffuser
    CHOICE_FIELD(CentralAirDiffuserWallEquationSource, centralAirDiffuserWallEquationSource, CentralAirDiffuserWallEquationSource)
    CHOICE_FIELD(CentralAirDiffuserCeilingEquationSource, centralAirDiffuserCeilingEquationSource, CentralAirDiffuserCeilingEquationSource)
    CHOICE_FIELD(CentralAirDiffuserFloorEquationSource, centralAirDiffuserFloorEquationSource, CentralAirDiffuserFloorEquationSource)
    CHOICE_FIELD(CentralAirDiffuserWindowEquationSource, centralAirDiffuserWindowEquationSource, CentralAirDiffuserWindowEquationSource)

    // Mechanical Zone Fan Circulation
    CHOICE_FIELD(MechanicalZoneFanCirculationVerticalWallEquationSource, mechanicalZoneFanCirculationVerticalWallEquationSource,
                 MechanicalZoneFanCirculationVerticalWallEquationSource)
    CHOICE_FIELD(MechanicalZoneFanCirculationStableHorizontalEquationSource, mechanicalZoneFanCirculationStableHorizontalEquationSource,
                 MechanicalZoneFanCirculationStableHorizontalEquationSource)
    CHOICE_FIELD(MechanicalZoneFanCirculationUnstableHorizontalEquationSource, mechanicalZoneFanCirculationUnstableHorizontalEquationSource,
                 MechanicalZoneFanCirculationUnstableHorizontalEquationSource)
    CHOICE_FIELD(MechanicalZoneFanCirculationStableTiltedEquationSource, mechanicalZoneFanCirculationStableTiltedEquationSource,
                 MechanicalZoneFanCirculationStableTiltedEquationSource)
    CHOICE_FIELD(MechanicalZoneFanCirculationUnstableTiltedEquationSource, mechanicalZoneFanCirculationUnstableTiltedEquationSource,
                 MechanicalZoneFanCirculationUnstableTiltedEquationSource)
    CHOICE_FIELD(MechanicalZoneFanCirculationWindowEquationSource, mechanicalZoneFanCirculationWindowEquationSource,
                 MechanicalZoneFanCirculationWindowEquationSource)

    // Mixed Regime
    CHOICE_FIELD(MixedRegimeBuoyancyAssistingFlowonWallsEquationSource, mixedRegimeBuoyancyAssistingFlowonWallsEquationSource,
                 MixedRegimeBuoyancyAssistingFlowonWallsEquationSource)
    CHOICE_FIELD(MixedRegimeBuoyancyOpposingFlowonWallsEquationSource, mixedRegimeBuoyancyOpposingFlowonWallsEquationSource,
                 MixedRegimeBuoyancyOpposingFlowonWallsEquationSource)
    CHOICE_FIELD(MixedRegimeStableFloorEquationSource, mixedRegimeStableFloorEquationSource, MixedRegimeStableFloorEquationSource)
    CHOICE_FIELD(MixedRegimeUnstableFloorEquationSource, mixedRegimeUnstableFloorEquationSource, MixedRegimeUnstableFloorEquationSource)
    CHOICE_FIELD(MixedRegimeStableCeilingEquationSource, mixedRegimeStableCeilingEquationSource, MixedRegimeStableCeilingEquationSource)
    CHOICE_FIELD(MixedRegimeUnstableCeilingEquationSource, mixedRegimeUnstableCeilingEquationSource, MixedRegimeUnstableCeilingEquationSource)
    CHOICE_FIELD(MixedRegimeWindowEquationSource, mixedRegimeWindowEquationSource, MixedRegimeWindowEquationSource)

#undef CHOICE_GETTER
#undef CHOICE_SETTER
#undef CHOICE_ISDEFAULTED
#undef CHOICE_RESET
#undef CHOICE_VALUES
#undef CHOICE_FIELD

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
