/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "SiteGroundDomainSlab.hpp"
#include "SiteGroundDomainSlab_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Site_GroundDomain_Slab_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  SiteGroundDomainSlab::SiteGroundDomainSlab(const Model& model) : ModelObject(SiteGroundDomainSlab::iddObjectType(), model) {}

  SiteGroundDomainSlab::SiteGroundDomainSlab(std::shared_ptr<detail::SiteGroundDomainSlab_Impl> impl) : ModelObject(std::move(impl)) {}

  IddObjectType SiteGroundDomainSlab::iddObjectType() {
    return IddObjectType::Site_GroundDomain_Slab;
  }

  std::vector<std::string> SiteGroundDomainSlab::undisturbedGroundTemperatureModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Site_GroundDomain_SlabFields::UndisturbedGroundTemperatureModelType);
  }

  std::vector<std::string> SiteGroundDomainSlab::slabLocationValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Site_GroundDomain_SlabFields::SlabLocation);
  }

  std::vector<std::string> SiteGroundDomainSlab::horizontalInsulationExtentsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::Site_GroundDomain_SlabFields::HorizontalInsulationExtents);
  }

  std::vector<std::string> SiteGroundDomainSlab::simulationTimestepValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(), openstudio::Site_GroundDomain_SlabFields::SimulationTimestep);
  }

  double SiteGroundDomainSlab::groundDomainDepth() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->groundDomainDepth();
  }

  bool SiteGroundDomainSlab::isGroundDomainDepthDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isGroundDomainDepthDefaulted();
  }

  bool SiteGroundDomainSlab::setGroundDomainDepth(double groundDomainDepth) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setGroundDomainDepth(groundDomainDepth);
  }

  void SiteGroundDomainSlab::resetGroundDomainDepth() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetGroundDomainDepth();
  }

  double SiteGroundDomainSlab::aspectRatio() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->aspectRatio();
  }

  bool SiteGroundDomainSlab::isAspectRatioDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isAspectRatioDefaulted();
  }

  bool SiteGroundDomainSlab::setAspectRatio(double aspectRatio) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setAspectRatio(aspectRatio);
  }

  void SiteGroundDomainSlab::resetAspectRatio() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetAspectRatio();
  }

  double SiteGroundDomainSlab::perimeterOffset() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->perimeterOffset();
  }

  bool SiteGroundDomainSlab::isPerimeterOffsetDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isPerimeterOffsetDefaulted();
  }

  bool SiteGroundDomainSlab::setPerimeterOffset(double perimeterOffset) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setPerimeterOffset(perimeterOffset);
  }

  void SiteGroundDomainSlab::resetPerimeterOffset() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetPerimeterOffset();
  }

  double SiteGroundDomainSlab::soilThermalConductivity() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->soilThermalConductivity();
  }

  bool SiteGroundDomainSlab::isSoilThermalConductivityDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSoilThermalConductivityDefaulted();
  }

  bool SiteGroundDomainSlab::setSoilThermalConductivity(double soilThermalConductivity) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
  }

  void SiteGroundDomainSlab::resetSoilThermalConductivity() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSoilThermalConductivity();
  }

  double SiteGroundDomainSlab::soilDensity() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->soilDensity();
  }

  bool SiteGroundDomainSlab::isSoilDensityDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSoilDensityDefaulted();
  }

  bool SiteGroundDomainSlab::setSoilDensity(double soilDensity) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSoilDensity(soilDensity);
  }

  void SiteGroundDomainSlab::resetSoilDensity() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSoilDensity();
  }

  double SiteGroundDomainSlab::soilSpecificHeat() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->soilSpecificHeat();
  }

  bool SiteGroundDomainSlab::isSoilSpecificHeatDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSoilSpecificHeatDefaulted();
  }

  bool SiteGroundDomainSlab::setSoilSpecificHeat(double soilSpecificHeat) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
  }

  void SiteGroundDomainSlab::resetSoilSpecificHeat() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSoilSpecificHeat();
  }

  double SiteGroundDomainSlab::soilMoistureContentVolumeFraction() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->soilMoistureContentVolumeFraction();
  }

  bool SiteGroundDomainSlab::isSoilMoistureContentVolumeFractionDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSoilMoistureContentVolumeFractionDefaulted();
  }

  bool SiteGroundDomainSlab::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSoilMoistureContentVolumeFraction(soilMoistureContentVolumeFraction);
  }

  void SiteGroundDomainSlab::resetSoilMoistureContentVolumeFraction() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSoilMoistureContentVolumeFraction();
  }

  double SiteGroundDomainSlab::soilMoistureContentVolumeFractionatSaturation() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->soilMoistureContentVolumeFractionatSaturation();
  }

  bool SiteGroundDomainSlab::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSoilMoistureContentVolumeFractionatSaturationDefaulted();
  }

  bool SiteGroundDomainSlab::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSoilMoistureContentVolumeFractionatSaturation(
      soilMoistureContentVolumeFractionatSaturation);
  }

  void SiteGroundDomainSlab::resetSoilMoistureContentVolumeFractionatSaturation() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSoilMoistureContentVolumeFractionatSaturation();
  }

  std::string SiteGroundDomainSlab::undisturbedGroundTemperatureModelType() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->undisturbedGroundTemperatureModelType();
  }

  bool SiteGroundDomainSlab::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setUndisturbedGroundTemperatureModelType(undisturbedGroundTemperatureModelType);
  }

  double SiteGroundDomainSlab::evapotranspirationGroundCoverParameter() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->evapotranspirationGroundCoverParameter();
  }

  bool SiteGroundDomainSlab::isEvapotranspirationGroundCoverParameterDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isEvapotranspirationGroundCoverParameterDefaulted();
  }

  bool SiteGroundDomainSlab::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setEvapotranspirationGroundCoverParameter(evapotranspirationGroundCoverParameter);
  }

  void SiteGroundDomainSlab::resetEvapotranspirationGroundCoverParameter() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetEvapotranspirationGroundCoverParameter();
  }

  std::string SiteGroundDomainSlab::slabLocation() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->slabLocation();
  }

  bool SiteGroundDomainSlab::setSlabLocation(const std::string& slabLocation) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSlabLocation(slabLocation);
  }

  bool SiteGroundDomainSlab::horizontalInsulation() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->horizontalInsulation();
  }

  bool SiteGroundDomainSlab::isHorizontalInsulationDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isHorizontalInsulationDefaulted();
  }

  bool SiteGroundDomainSlab::setHorizontalInsulation(bool horizontalInsulation) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setHorizontalInsulation(horizontalInsulation);
  }

  void SiteGroundDomainSlab::resetHorizontalInsulation() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetHorizontalInsulation();
  }

  std::string SiteGroundDomainSlab::horizontalInsulationExtents() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->horizontalInsulationExtents();
  }

  bool SiteGroundDomainSlab::isHorizontalInsulationExtentsDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isHorizontalInsulationExtentsDefaulted();
  }

  bool SiteGroundDomainSlab::setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setHorizontalInsulationExtents(horizontalInsulationExtents);
  }

  void SiteGroundDomainSlab::resetHorizontalInsulationExtents() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetHorizontalInsulationExtents();
  }

  boost::optional<double> SiteGroundDomainSlab::perimeterInsulationWidth() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->perimeterInsulationWidth();
  }

  bool SiteGroundDomainSlab::setPerimeterInsulationWidth(double perimeterInsulationWidth) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setPerimeterInsulationWidth(perimeterInsulationWidth);
  }

  void SiteGroundDomainSlab::resetPerimeterInsulationWidth() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetPerimeterInsulationWidth();
  }

  double SiteGroundDomainSlab::geometricMeshCoefficient() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->geometricMeshCoefficient();
  }

  bool SiteGroundDomainSlab::isGeometricMeshCoefficientDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isGeometricMeshCoefficientDefaulted();
  }

  bool SiteGroundDomainSlab::setGeometricMeshCoefficient(double geometricMeshCoefficient) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setGeometricMeshCoefficient(geometricMeshCoefficient);
  }

  void SiteGroundDomainSlab::resetGeometricMeshCoefficient() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetGeometricMeshCoefficient();
  }

  bool SiteGroundDomainSlab::verticalInsulation() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->verticalInsulation();
  }

  bool SiteGroundDomainSlab::isVerticalInsulationDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isVerticalInsulationDefaulted();
  }

  bool SiteGroundDomainSlab::setVerticalInsulation(bool verticalInsulation) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setVerticalInsulation(verticalInsulation);
  }

  void SiteGroundDomainSlab::resetVerticalInsulation() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetVerticalInsulation();
  }

  boost::optional<double> SiteGroundDomainSlab::verticalInsulationDepth() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->verticalInsulationDepth();
  }

  bool SiteGroundDomainSlab::setVerticalInsulationDepth(double verticalInsulationDepth) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setVerticalInsulationDepth(verticalInsulationDepth);
  }

  void SiteGroundDomainSlab::resetVerticalInsulationDepth() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetVerticalInsulationDepth();
  }

  std::string SiteGroundDomainSlab::simulationTimestep() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->simulationTimestep();
  }

  bool SiteGroundDomainSlab::isSimulationTimestepDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isSimulationTimestepDefaulted();
  }

  bool SiteGroundDomainSlab::setSimulationTimestep(const std::string& simulationTimestep) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setSimulationTimestep(simulationTimestep);
  }

  void SiteGroundDomainSlab::resetSimulationTimestep() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetSimulationTimestep();
  }

  int SiteGroundDomainSlab::meshDensityParameter() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->meshDensityParameter();
  }

  bool SiteGroundDomainSlab::isMeshDensityParameterDefaulted() const {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->isMeshDensityParameterDefaulted();
  }

  bool SiteGroundDomainSlab::setMeshDensityParameter(int meshDensityParameter) {
    return getImpl<detail::SiteGroundDomainSlab_Impl>()->setMeshDensityParameter(meshDensityParameter);
  }

  void SiteGroundDomainSlab::resetMeshDensityParameter() {
    getImpl<detail::SiteGroundDomainSlab_Impl>()->resetMeshDensityParameter();
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double SiteGroundDomainSlab_Impl::groundDomainDepth() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::GroundDomainDepth, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isGroundDomainDepthDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::GroundDomainDepth);
    }

    bool SiteGroundDomainSlab_Impl::setGroundDomainDepth(double groundDomainDepth) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::GroundDomainDepth, groundDomainDepth);
    }

    void SiteGroundDomainSlab_Impl::resetGroundDomainDepth() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::GroundDomainDepth, ""));
    }

    double SiteGroundDomainSlab_Impl::aspectRatio() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::AspectRatio, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isAspectRatioDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::AspectRatio);
    }

    bool SiteGroundDomainSlab_Impl::setAspectRatio(double aspectRatio) {
      const bool result = setDouble(openstudio::Site_GroundDomain_SlabFields::AspectRatio, aspectRatio);
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundDomainSlab_Impl::resetAspectRatio() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::AspectRatio, ""));
    }

    double SiteGroundDomainSlab_Impl::perimeterOffset() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::PerimeterOffset, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isPerimeterOffsetDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::PerimeterOffset);
    }

    bool SiteGroundDomainSlab_Impl::setPerimeterOffset(double perimeterOffset) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::PerimeterOffset, perimeterOffset);
    }

    void SiteGroundDomainSlab_Impl::resetPerimeterOffset() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::PerimeterOffset, ""));
    }

    double SiteGroundDomainSlab_Impl::soilThermalConductivity() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::SoilThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSoilThermalConductivityDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SoilThermalConductivity);
    }

    bool SiteGroundDomainSlab_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::SoilThermalConductivity, soilThermalConductivity);
    }

    void SiteGroundDomainSlab_Impl::resetSoilThermalConductivity() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SoilThermalConductivity, ""));
    }

    double SiteGroundDomainSlab_Impl::soilDensity() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::SoilDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSoilDensityDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SoilDensity);
    }

    bool SiteGroundDomainSlab_Impl::setSoilDensity(double soilDensity) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::SoilDensity, soilDensity);
    }

    void SiteGroundDomainSlab_Impl::resetSoilDensity() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SoilDensity, ""));
    }

    double SiteGroundDomainSlab_Impl::soilSpecificHeat() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::SoilSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSoilSpecificHeatDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SoilSpecificHeat);
    }

    bool SiteGroundDomainSlab_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::SoilSpecificHeat, soilSpecificHeat);
    }

    void SiteGroundDomainSlab_Impl::resetSoilSpecificHeat() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SoilSpecificHeat, ""));
    }

    double SiteGroundDomainSlab_Impl::soilMoistureContentVolumeFraction() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSoilMoistureContentVolumeFractionDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFraction);
    }

    bool SiteGroundDomainSlab_Impl::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFraction, soilMoistureContentVolumeFraction);
    }

    void SiteGroundDomainSlab_Impl::resetSoilMoistureContentVolumeFraction() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFraction, ""));
    }

    double SiteGroundDomainSlab_Impl::soilMoistureContentVolumeFractionatSaturation() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFractionatSaturation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFractionatSaturation);
    }

    bool SiteGroundDomainSlab_Impl::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFractionatSaturation,
                       soilMoistureContentVolumeFractionatSaturation);
    }

    void SiteGroundDomainSlab_Impl::resetSoilMoistureContentVolumeFractionatSaturation() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFractionatSaturation, ""));
    }

    std::string SiteGroundDomainSlab_Impl::undisturbedGroundTemperatureModelType() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::UndisturbedGroundTemperatureModelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
      return setString(openstudio::Site_GroundDomain_SlabFields::UndisturbedGroundTemperatureModelType, undisturbedGroundTemperatureModelType);
    }

    double SiteGroundDomainSlab_Impl::evapotranspirationGroundCoverParameter() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::EvapotranspirationGroundCoverParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isEvapotranspirationGroundCoverParameterDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::EvapotranspirationGroundCoverParameter);
    }

    bool SiteGroundDomainSlab_Impl::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::EvapotranspirationGroundCoverParameter, evapotranspirationGroundCoverParameter);
    }

    void SiteGroundDomainSlab_Impl::resetEvapotranspirationGroundCoverParameter() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::EvapotranspirationGroundCoverParameter, ""));
    }

    std::string SiteGroundDomainSlab_Impl::slabLocation() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::SlabLocation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::setSlabLocation(const std::string& slabLocation) {
      return setString(openstudio::Site_GroundDomain_SlabFields::SlabLocation, slabLocation);
    }

    bool SiteGroundDomainSlab_Impl::horizontalInsulation() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulation, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SiteGroundDomainSlab_Impl::isHorizontalInsulationDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulation);
    }

    bool SiteGroundDomainSlab_Impl::setHorizontalInsulation(bool horizontalInsulation) {
      const bool result = setString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulation, horizontalInsulation ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundDomainSlab_Impl::resetHorizontalInsulation() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulation, ""));
    }

    std::string SiteGroundDomainSlab_Impl::horizontalInsulationExtents() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulationExtents, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isHorizontalInsulationExtentsDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulationExtents);
    }

    bool SiteGroundDomainSlab_Impl::setHorizontalInsulationExtents(const std::string& horizontalInsulationExtents) {
      return setString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulationExtents, horizontalInsulationExtents);
    }

    void SiteGroundDomainSlab_Impl::resetHorizontalInsulationExtents() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::HorizontalInsulationExtents, ""));
    }

    boost::optional<double> SiteGroundDomainSlab_Impl::perimeterInsulationWidth() const {
      return getDouble(openstudio::Site_GroundDomain_SlabFields::PerimeterInsulationWidth, true);
    }

    bool SiteGroundDomainSlab_Impl::setPerimeterInsulationWidth(double perimeterInsulationWidth) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::PerimeterInsulationWidth, perimeterInsulationWidth);
    }

    void SiteGroundDomainSlab_Impl::resetPerimeterInsulationWidth() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::PerimeterInsulationWidth, ""));
    }

    double SiteGroundDomainSlab_Impl::geometricMeshCoefficient() const {
      const auto value = getDouble(openstudio::Site_GroundDomain_SlabFields::GeometricMeshCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isGeometricMeshCoefficientDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::GeometricMeshCoefficient);
    }

    bool SiteGroundDomainSlab_Impl::setGeometricMeshCoefficient(double geometricMeshCoefficient) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::GeometricMeshCoefficient, geometricMeshCoefficient);
    }

    void SiteGroundDomainSlab_Impl::resetGeometricMeshCoefficient() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::GeometricMeshCoefficient, ""));
    }

    bool SiteGroundDomainSlab_Impl::verticalInsulation() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::VerticalInsulation, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool SiteGroundDomainSlab_Impl::isVerticalInsulationDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::VerticalInsulation);
    }

    bool SiteGroundDomainSlab_Impl::setVerticalInsulation(bool verticalInsulation) {
      const bool result = setString(openstudio::Site_GroundDomain_SlabFields::VerticalInsulation, verticalInsulation ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    void SiteGroundDomainSlab_Impl::resetVerticalInsulation() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::VerticalInsulation, ""));
    }

    boost::optional<double> SiteGroundDomainSlab_Impl::verticalInsulationDepth() const {
      return getDouble(openstudio::Site_GroundDomain_SlabFields::VerticalInsulationDepth, true);
    }

    bool SiteGroundDomainSlab_Impl::setVerticalInsulationDepth(double verticalInsulationDepth) {
      return setDouble(openstudio::Site_GroundDomain_SlabFields::VerticalInsulationDepth, verticalInsulationDepth);
    }

    void SiteGroundDomainSlab_Impl::resetVerticalInsulationDepth() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::VerticalInsulationDepth, ""));
    }

    std::string SiteGroundDomainSlab_Impl::simulationTimestep() const {
      const auto value = getString(openstudio::Site_GroundDomain_SlabFields::SimulationTimestep, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isSimulationTimestepDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::SimulationTimestep);
    }

    bool SiteGroundDomainSlab_Impl::setSimulationTimestep(const std::string& simulationTimestep) {
      return setString(openstudio::Site_GroundDomain_SlabFields::SimulationTimestep, simulationTimestep);
    }

    void SiteGroundDomainSlab_Impl::resetSimulationTimestep() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::SimulationTimestep, ""));
    }

    int SiteGroundDomainSlab_Impl::meshDensityParameter() const {
      const auto value = getInt(openstudio::Site_GroundDomain_SlabFields::MeshDensityParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool SiteGroundDomainSlab_Impl::isMeshDensityParameterDefaulted() const {
      return isEmpty(openstudio::Site_GroundDomain_SlabFields::MeshDensityParameter);
    }

    bool SiteGroundDomainSlab_Impl::setMeshDensityParameter(int meshDensityParameter) {
      return setInt(openstudio::Site_GroundDomain_SlabFields::MeshDensityParameter, meshDensityParameter);
    }

    void SiteGroundDomainSlab_Impl::resetMeshDensityParameter() {
      OS_ASSERT(setString(openstudio::Site_GroundDomain_SlabFields::MeshDensityParameter, ""));
    }

    std::vector<std::string> SiteGroundDomainSlab_Impl::undisturbedGroundTemperatureModelTypeValues() const {
      return openstudio::epmodel::SiteGroundDomainSlab::undisturbedGroundTemperatureModelTypeValues();
    }

    std::vector<std::string> SiteGroundDomainSlab_Impl::slabLocationValues() const {
      return openstudio::epmodel::SiteGroundDomainSlab::slabLocationValues();
    }

    std::vector<std::string> SiteGroundDomainSlab_Impl::horizontalInsulationExtentsValues() const {
      return openstudio::epmodel::SiteGroundDomainSlab::horizontalInsulationExtentsValues();
    }

    std::vector<std::string> SiteGroundDomainSlab_Impl::simulationTimestepValues() const {
      return openstudio::epmodel::SiteGroundDomainSlab::simulationTimestepValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
