/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "PipingSystemUndergroundDomain.hpp"
#include "PipingSystemUndergroundDomain_Impl.hpp"

#include "Model.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/PipingSystem_Underground_Domain_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  PipingSystemUndergroundDomain::PipingSystemUndergroundDomain(const Model& model)
    : ModelObject(PipingSystemUndergroundDomain::iddObjectType(), model) {}

  PipingSystemUndergroundDomain::PipingSystemUndergroundDomain(std::shared_ptr<detail::PipingSystemUndergroundDomain_Impl> impl)
    : ModelObject(std::move(impl)) {}

  IddObjectType PipingSystemUndergroundDomain::iddObjectType() {
    return IddObjectType::PipingSystem_Underground_Domain;
  }

  std::vector<std::string> PipingSystemUndergroundDomain::xDirectionMeshTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshType);
  }

  std::vector<std::string> PipingSystemUndergroundDomain::yDirectionMeshTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshType);
  }

  std::vector<std::string> PipingSystemUndergroundDomain::zDirectionMeshTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshType);
  }

  std::vector<std::string> PipingSystemUndergroundDomain::undisturbedGroundTemperatureModelTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          openstudio::PipingSystem_Underground_DomainFields::UndisturbedGroundTemperatureModelType);
  }

  double PipingSystemUndergroundDomain::xmax() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->xmax();
  }

  bool PipingSystemUndergroundDomain::setXmax(double xmax) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setXmax(xmax);
  }

  double PipingSystemUndergroundDomain::ymax() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->ymax();
  }

  bool PipingSystemUndergroundDomain::setYmax(double ymax) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setYmax(ymax);
  }

  double PipingSystemUndergroundDomain::zmax() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->zmax();
  }

  bool PipingSystemUndergroundDomain::setZmax(double zmax) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setZmax(zmax);
  }

  int PipingSystemUndergroundDomain::xDirectionMeshDensityParameter() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->xDirectionMeshDensityParameter();
  }

  bool PipingSystemUndergroundDomain::setXDirectionMeshDensityParameter(int xDirectionMeshDensityParameter) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setXDirectionMeshDensityParameter(xDirectionMeshDensityParameter);
  }

  bool PipingSystemUndergroundDomain::isXDirectionMeshDensityParameterDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isXDirectionMeshDensityParameterDefaulted();
  }

  void PipingSystemUndergroundDomain::resetXDirectionMeshDensityParameter() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetXDirectionMeshDensityParameter();
  }

  std::string PipingSystemUndergroundDomain::xDirectionMeshType() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->xDirectionMeshType();
  }

  bool PipingSystemUndergroundDomain::setXDirectionMeshType(const std::string& xDirectionMeshType) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setXDirectionMeshType(xDirectionMeshType);
  }

  double PipingSystemUndergroundDomain::xDirectionGeometricCoefficient() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->xDirectionGeometricCoefficient();
  }

  bool PipingSystemUndergroundDomain::setXDirectionGeometricCoefficient(double xDirectionGeometricCoefficient) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setXDirectionGeometricCoefficient(xDirectionGeometricCoefficient);
  }

  bool PipingSystemUndergroundDomain::isXDirectionGeometricCoefficientDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isXDirectionGeometricCoefficientDefaulted();
  }

  void PipingSystemUndergroundDomain::resetXDirectionGeometricCoefficient() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetXDirectionGeometricCoefficient();
  }

  int PipingSystemUndergroundDomain::yDirectionMeshDensityParameter() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->yDirectionMeshDensityParameter();
  }

  bool PipingSystemUndergroundDomain::setYDirectionMeshDensityParameter(int yDirectionMeshDensityParameter) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setYDirectionMeshDensityParameter(yDirectionMeshDensityParameter);
  }

  bool PipingSystemUndergroundDomain::isYDirectionMeshDensityParameterDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isYDirectionMeshDensityParameterDefaulted();
  }

  void PipingSystemUndergroundDomain::resetYDirectionMeshDensityParameter() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetYDirectionMeshDensityParameter();
  }

  std::string PipingSystemUndergroundDomain::yDirectionMeshType() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->yDirectionMeshType();
  }

  bool PipingSystemUndergroundDomain::setYDirectionMeshType(const std::string& yDirectionMeshType) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setYDirectionMeshType(yDirectionMeshType);
  }

  double PipingSystemUndergroundDomain::yDirectionGeometricCoefficient() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->yDirectionGeometricCoefficient();
  }

  bool PipingSystemUndergroundDomain::setYDirectionGeometricCoefficient(double yDirectionGeometricCoefficient) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setYDirectionGeometricCoefficient(yDirectionGeometricCoefficient);
  }

  bool PipingSystemUndergroundDomain::isYDirectionGeometricCoefficientDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isYDirectionGeometricCoefficientDefaulted();
  }

  void PipingSystemUndergroundDomain::resetYDirectionGeometricCoefficient() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetYDirectionGeometricCoefficient();
  }

  int PipingSystemUndergroundDomain::zDirectionMeshDensityParameter() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->zDirectionMeshDensityParameter();
  }

  bool PipingSystemUndergroundDomain::setZDirectionMeshDensityParameter(int zDirectionMeshDensityParameter) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setZDirectionMeshDensityParameter(zDirectionMeshDensityParameter);
  }

  bool PipingSystemUndergroundDomain::isZDirectionMeshDensityParameterDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isZDirectionMeshDensityParameterDefaulted();
  }

  void PipingSystemUndergroundDomain::resetZDirectionMeshDensityParameter() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetZDirectionMeshDensityParameter();
  }

  std::string PipingSystemUndergroundDomain::zDirectionMeshType() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->zDirectionMeshType();
  }

  bool PipingSystemUndergroundDomain::setZDirectionMeshType(const std::string& zDirectionMeshType) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setZDirectionMeshType(zDirectionMeshType);
  }

  double PipingSystemUndergroundDomain::zDirectionGeometricCoefficient() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->zDirectionGeometricCoefficient();
  }

  bool PipingSystemUndergroundDomain::setZDirectionGeometricCoefficient(double zDirectionGeometricCoefficient) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setZDirectionGeometricCoefficient(zDirectionGeometricCoefficient);
  }

  bool PipingSystemUndergroundDomain::isZDirectionGeometricCoefficientDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isZDirectionGeometricCoefficientDefaulted();
  }

  void PipingSystemUndergroundDomain::resetZDirectionGeometricCoefficient() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetZDirectionGeometricCoefficient();
  }

  double PipingSystemUndergroundDomain::soilThermalConductivity() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->soilThermalConductivity();
  }

  bool PipingSystemUndergroundDomain::setSoilThermalConductivity(double soilThermalConductivity) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setSoilThermalConductivity(soilThermalConductivity);
  }

  double PipingSystemUndergroundDomain::soilDensity() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->soilDensity();
  }

  bool PipingSystemUndergroundDomain::setSoilDensity(double soilDensity) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setSoilDensity(soilDensity);
  }

  double PipingSystemUndergroundDomain::soilSpecificHeat() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->soilSpecificHeat();
  }

  bool PipingSystemUndergroundDomain::setSoilSpecificHeat(double soilSpecificHeat) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setSoilSpecificHeat(soilSpecificHeat);
  }

  double PipingSystemUndergroundDomain::soilMoistureContentVolumeFraction() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->soilMoistureContentVolumeFraction();
  }

  bool PipingSystemUndergroundDomain::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setSoilMoistureContentVolumeFraction(soilMoistureContentVolumeFraction);
  }

  bool PipingSystemUndergroundDomain::isSoilMoistureContentVolumeFractionDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isSoilMoistureContentVolumeFractionDefaulted();
  }

  void PipingSystemUndergroundDomain::resetSoilMoistureContentVolumeFraction() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetSoilMoistureContentVolumeFraction();
  }

  double PipingSystemUndergroundDomain::soilMoistureContentVolumeFractionatSaturation() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->soilMoistureContentVolumeFractionatSaturation();
  }

  bool PipingSystemUndergroundDomain::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setSoilMoistureContentVolumeFractionatSaturation(
      soilMoistureContentVolumeFractionatSaturation);
  }

  bool PipingSystemUndergroundDomain::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isSoilMoistureContentVolumeFractionatSaturationDefaulted();
  }

  void PipingSystemUndergroundDomain::resetSoilMoistureContentVolumeFractionatSaturation() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetSoilMoistureContentVolumeFractionatSaturation();
  }

  std::string PipingSystemUndergroundDomain::undisturbedGroundTemperatureModelType() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->undisturbedGroundTemperatureModelType();
  }

  bool PipingSystemUndergroundDomain::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setUndisturbedGroundTemperatureModelType(undisturbedGroundTemperatureModelType);
  }

  bool PipingSystemUndergroundDomain::thisDomainIncludesBasementSurfaceInteraction() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->thisDomainIncludesBasementSurfaceInteraction();
  }

  bool PipingSystemUndergroundDomain::setThisDomainIncludesBasementSurfaceInteraction(bool thisDomainIncludesBasementSurfaceInteraction) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setThisDomainIncludesBasementSurfaceInteraction(
      thisDomainIncludesBasementSurfaceInteraction);
  }

  bool PipingSystemUndergroundDomain::isThisDomainIncludesBasementSurfaceInteractionDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isThisDomainIncludesBasementSurfaceInteractionDefaulted();
  }

  void PipingSystemUndergroundDomain::resetThisDomainIncludesBasementSurfaceInteraction() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetThisDomainIncludesBasementSurfaceInteraction();
  }

  boost::optional<double> PipingSystemUndergroundDomain::widthofBasementFloorinGroundDomain() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->widthofBasementFloorinGroundDomain();
  }

  bool PipingSystemUndergroundDomain::setWidthofBasementFloorinGroundDomain(double widthofBasementFloorinGroundDomain) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setWidthofBasementFloorinGroundDomain(widthofBasementFloorinGroundDomain);
  }

  void PipingSystemUndergroundDomain::resetWidthofBasementFloorinGroundDomain() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetWidthofBasementFloorinGroundDomain();
  }

  boost::optional<double> PipingSystemUndergroundDomain::depthofBasementWallInGroundDomain() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->depthofBasementWallInGroundDomain();
  }

  bool PipingSystemUndergroundDomain::setDepthofBasementWallInGroundDomain(double depthofBasementWallInGroundDomain) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setDepthofBasementWallInGroundDomain(depthofBasementWallInGroundDomain);
  }

  void PipingSystemUndergroundDomain::resetDepthofBasementWallInGroundDomain() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetDepthofBasementWallInGroundDomain();
  }

  boost::optional<bool> PipingSystemUndergroundDomain::shiftPipeXCoordinatesByBasementWidth() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->shiftPipeXCoordinatesByBasementWidth();
  }

  bool PipingSystemUndergroundDomain::setShiftPipeXCoordinatesByBasementWidth(boost::optional<bool> shiftPipeXCoordinatesByBasementWidth) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setShiftPipeXCoordinatesByBasementWidth(shiftPipeXCoordinatesByBasementWidth);
  }

  void PipingSystemUndergroundDomain::resetShiftPipeXCoordinatesByBasementWidth() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetShiftPipeXCoordinatesByBasementWidth();
  }

  double PipingSystemUndergroundDomain::convergenceCriterionfortheOuterCartesianDomainIterationLoop() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->convergenceCriterionfortheOuterCartesianDomainIterationLoop();
  }

  bool PipingSystemUndergroundDomain::setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(
    double convergenceCriterionfortheOuterCartesianDomainIterationLoop) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(
      convergenceCriterionfortheOuterCartesianDomainIterationLoop);
  }

  bool PipingSystemUndergroundDomain::isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted();
  }

  void PipingSystemUndergroundDomain::resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop();
  }

  int PipingSystemUndergroundDomain::maximumIterationsintheOuterCartesianDomainIterationLoop() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->maximumIterationsintheOuterCartesianDomainIterationLoop();
  }

  bool PipingSystemUndergroundDomain::setMaximumIterationsintheOuterCartesianDomainIterationLoop(
    int maximumIterationsintheOuterCartesianDomainIterationLoop) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setMaximumIterationsintheOuterCartesianDomainIterationLoop(
      maximumIterationsintheOuterCartesianDomainIterationLoop);
  }

  bool PipingSystemUndergroundDomain::isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted();
  }

  void PipingSystemUndergroundDomain::resetMaximumIterationsintheOuterCartesianDomainIterationLoop() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetMaximumIterationsintheOuterCartesianDomainIterationLoop();
  }

  double PipingSystemUndergroundDomain::evapotranspirationGroundCoverParameter() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->evapotranspirationGroundCoverParameter();
  }

  bool PipingSystemUndergroundDomain::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setEvapotranspirationGroundCoverParameter(evapotranspirationGroundCoverParameter);
  }

  bool PipingSystemUndergroundDomain::isEvapotranspirationGroundCoverParameterDefaulted() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->isEvapotranspirationGroundCoverParameterDefaulted();
  }

  void PipingSystemUndergroundDomain::resetEvapotranspirationGroundCoverParameter() {
    getImpl<detail::PipingSystemUndergroundDomain_Impl>()->resetEvapotranspirationGroundCoverParameter();
  }

  int PipingSystemUndergroundDomain::numberofPipeCircuitsEnteredforthisDomain() const {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->numberofPipeCircuitsEnteredforthisDomain();
  }

  bool PipingSystemUndergroundDomain::setNumberofPipeCircuitsEnteredforthisDomain(int numberofPipeCircuitsEnteredforthisDomain) {
    return getImpl<detail::PipingSystemUndergroundDomain_Impl>()->setNumberofPipeCircuitsEnteredforthisDomain(
      numberofPipeCircuitsEnteredforthisDomain);
  }

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
  namespace detail {

    double PipingSystemUndergroundDomain_Impl::xmax() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::Xmax, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setXmax(double xmax) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::Xmax, xmax);
    }

    double PipingSystemUndergroundDomain_Impl::ymax() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::Ymax, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setYmax(double ymax) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::Ymax, ymax);
    }

    double PipingSystemUndergroundDomain_Impl::zmax() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::Zmax, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setZmax(double zmax) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::Zmax, zmax);
    }

    int PipingSystemUndergroundDomain_Impl::xDirectionMeshDensityParameter() const {
      const auto value = getInt(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshDensityParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setXDirectionMeshDensityParameter(int xDirectionMeshDensityParameter) {
      return setInt(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshDensityParameter, xDirectionMeshDensityParameter);
    }

    bool PipingSystemUndergroundDomain_Impl::isXDirectionMeshDensityParameterDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshDensityParameter);
    }

    void PipingSystemUndergroundDomain_Impl::resetXDirectionMeshDensityParameter() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshDensityParameter, ""));
    }

    std::string PipingSystemUndergroundDomain_Impl::xDirectionMeshType() const {
      const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setXDirectionMeshType(const std::string& xDirectionMeshType) {
      return setString(openstudio::PipingSystem_Underground_DomainFields::XDirectionMeshType, xDirectionMeshType);
    }

    double PipingSystemUndergroundDomain_Impl::xDirectionGeometricCoefficient() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::XDirectionGeometricCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setXDirectionGeometricCoefficient(double xDirectionGeometricCoefficient) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::XDirectionGeometricCoefficient, xDirectionGeometricCoefficient);
    }

    bool PipingSystemUndergroundDomain_Impl::isXDirectionGeometricCoefficientDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::XDirectionGeometricCoefficient);
    }

    void PipingSystemUndergroundDomain_Impl::resetXDirectionGeometricCoefficient() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::XDirectionGeometricCoefficient, ""));
    }

    int PipingSystemUndergroundDomain_Impl::yDirectionMeshDensityParameter() const {
      const auto value = getInt(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshDensityParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setYDirectionMeshDensityParameter(int yDirectionMeshDensityParameter) {
      return setInt(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshDensityParameter, yDirectionMeshDensityParameter);
    }

    bool PipingSystemUndergroundDomain_Impl::isYDirectionMeshDensityParameterDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshDensityParameter);
    }

    void PipingSystemUndergroundDomain_Impl::resetYDirectionMeshDensityParameter() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshDensityParameter, ""));
    }

    std::string PipingSystemUndergroundDomain_Impl::yDirectionMeshType() const {
      const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setYDirectionMeshType(const std::string& yDirectionMeshType) {
      return setString(openstudio::PipingSystem_Underground_DomainFields::YDirectionMeshType, yDirectionMeshType);
    }

    double PipingSystemUndergroundDomain_Impl::yDirectionGeometricCoefficient() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::YDirectionGeometricCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setYDirectionGeometricCoefficient(double yDirectionGeometricCoefficient) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::YDirectionGeometricCoefficient, yDirectionGeometricCoefficient);
    }

    bool PipingSystemUndergroundDomain_Impl::isYDirectionGeometricCoefficientDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::YDirectionGeometricCoefficient);
    }

    void PipingSystemUndergroundDomain_Impl::resetYDirectionGeometricCoefficient() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::YDirectionGeometricCoefficient, ""));
    }

    int PipingSystemUndergroundDomain_Impl::zDirectionMeshDensityParameter() const {
      const auto value = getInt(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshDensityParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setZDirectionMeshDensityParameter(int zDirectionMeshDensityParameter) {
      return setInt(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshDensityParameter, zDirectionMeshDensityParameter);
    }

    bool PipingSystemUndergroundDomain_Impl::isZDirectionMeshDensityParameterDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshDensityParameter);
    }

    void PipingSystemUndergroundDomain_Impl::resetZDirectionMeshDensityParameter() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshDensityParameter, ""));
    }

    std::string PipingSystemUndergroundDomain_Impl::zDirectionMeshType() const {
      const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setZDirectionMeshType(const std::string& zDirectionMeshType) {
      return setString(openstudio::PipingSystem_Underground_DomainFields::ZDirectionMeshType, zDirectionMeshType);
    }

    double PipingSystemUndergroundDomain_Impl::zDirectionGeometricCoefficient() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::ZDirectionGeometricCoefficient, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setZDirectionGeometricCoefficient(double zDirectionGeometricCoefficient) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::ZDirectionGeometricCoefficient, zDirectionGeometricCoefficient);
    }

    bool PipingSystemUndergroundDomain_Impl::isZDirectionGeometricCoefficientDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::ZDirectionGeometricCoefficient);
    }

    void PipingSystemUndergroundDomain_Impl::resetZDirectionGeometricCoefficient() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::ZDirectionGeometricCoefficient, ""));
    }

    double PipingSystemUndergroundDomain_Impl::soilThermalConductivity() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::SoilThermalConductivity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setSoilThermalConductivity(double soilThermalConductivity) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::SoilThermalConductivity, soilThermalConductivity);
    }

    double PipingSystemUndergroundDomain_Impl::soilDensity() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::SoilDensity, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setSoilDensity(double soilDensity) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::SoilDensity, soilDensity);
    }

    double PipingSystemUndergroundDomain_Impl::soilSpecificHeat() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::SoilSpecificHeat, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setSoilSpecificHeat(double soilSpecificHeat) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::SoilSpecificHeat, soilSpecificHeat);
    }

    double PipingSystemUndergroundDomain_Impl::soilMoistureContentVolumeFraction() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFraction, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setSoilMoistureContentVolumeFraction(double soilMoistureContentVolumeFraction) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFraction, soilMoistureContentVolumeFraction);
    }

    bool PipingSystemUndergroundDomain_Impl::isSoilMoistureContentVolumeFractionDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFraction);
    }

    void PipingSystemUndergroundDomain_Impl::resetSoilMoistureContentVolumeFraction() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFraction, ""));
    }

    double PipingSystemUndergroundDomain_Impl::soilMoistureContentVolumeFractionatSaturation() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFractionatSaturation, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setSoilMoistureContentVolumeFractionatSaturation(double soilMoistureContentVolumeFractionatSaturation) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFractionatSaturation,
                       soilMoistureContentVolumeFractionatSaturation);
    }

    bool PipingSystemUndergroundDomain_Impl::isSoilMoistureContentVolumeFractionatSaturationDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFractionatSaturation);
    }

    void PipingSystemUndergroundDomain_Impl::resetSoilMoistureContentVolumeFractionatSaturation() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::SoilMoistureContentVolumeFractionatSaturation, ""));
    }

    std::string PipingSystemUndergroundDomain_Impl::undisturbedGroundTemperatureModelType() const {
      const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::UndisturbedGroundTemperatureModelType, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setUndisturbedGroundTemperatureModelType(const std::string& undisturbedGroundTemperatureModelType) {
      return setString(openstudio::PipingSystem_Underground_DomainFields::UndisturbedGroundTemperatureModelType,
                       undisturbedGroundTemperatureModelType);
    }

    bool PipingSystemUndergroundDomain_Impl::thisDomainIncludesBasementSurfaceInteraction() const {
      const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::ThisDomainIncludesBasementSurfaceInteraction, true);
      OS_ASSERT(value);
      return openstudio::istringEqual(*value, "Yes");
    }

    bool PipingSystemUndergroundDomain_Impl::setThisDomainIncludesBasementSurfaceInteraction(bool thisDomainIncludesBasementSurfaceInteraction) {
      const bool result = setString(openstudio::PipingSystem_Underground_DomainFields::ThisDomainIncludesBasementSurfaceInteraction,
                                    thisDomainIncludesBasementSurfaceInteraction ? "Yes" : "No");
      OS_ASSERT(result);
      return result;
    }

    bool PipingSystemUndergroundDomain_Impl::isThisDomainIncludesBasementSurfaceInteractionDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::ThisDomainIncludesBasementSurfaceInteraction);
    }

    void PipingSystemUndergroundDomain_Impl::resetThisDomainIncludesBasementSurfaceInteraction() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::ThisDomainIncludesBasementSurfaceInteraction, ""));
    }

    boost::optional<double> PipingSystemUndergroundDomain_Impl::widthofBasementFloorinGroundDomain() const {
      return getDouble(openstudio::PipingSystem_Underground_DomainFields::WidthofBasementFloorinGroundDomain, true);
    }

    bool PipingSystemUndergroundDomain_Impl::setWidthofBasementFloorinGroundDomain(double widthofBasementFloorinGroundDomain) {
      const bool result =
        setDouble(openstudio::PipingSystem_Underground_DomainFields::WidthofBasementFloorinGroundDomain, widthofBasementFloorinGroundDomain);
      OS_ASSERT(result);
      return result;
    }

    void PipingSystemUndergroundDomain_Impl::resetWidthofBasementFloorinGroundDomain() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::WidthofBasementFloorinGroundDomain, ""));
    }

    boost::optional<double> PipingSystemUndergroundDomain_Impl::depthofBasementWallInGroundDomain() const {
      return getDouble(openstudio::PipingSystem_Underground_DomainFields::DepthofBasementWallInGroundDomain, true);
    }

    bool PipingSystemUndergroundDomain_Impl::setDepthofBasementWallInGroundDomain(double depthofBasementWallInGroundDomain) {
      const bool result =
        setDouble(openstudio::PipingSystem_Underground_DomainFields::DepthofBasementWallInGroundDomain, depthofBasementWallInGroundDomain);
      OS_ASSERT(result);
      return result;
    }

    void PipingSystemUndergroundDomain_Impl::resetDepthofBasementWallInGroundDomain() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::DepthofBasementWallInGroundDomain, ""));
    }

    boost::optional<bool> PipingSystemUndergroundDomain_Impl::shiftPipeXCoordinatesByBasementWidth() const {
      boost::optional<bool> result;
      if (const auto value = getString(openstudio::PipingSystem_Underground_DomainFields::ShiftPipeXCoordinatesByBasementWidth, true)) {
        result = openstudio::istringEqual(*value, "Yes");
      }
      return result;
    }

    bool PipingSystemUndergroundDomain_Impl::setShiftPipeXCoordinatesByBasementWidth(boost::optional<bool> shiftPipeXCoordinatesByBasementWidth) {
      bool result = false;
      if (shiftPipeXCoordinatesByBasementWidth) {
        result = setString(openstudio::PipingSystem_Underground_DomainFields::ShiftPipeXCoordinatesByBasementWidth,
                           shiftPipeXCoordinatesByBasementWidth.get() ? "Yes" : "No");
      } else {
        resetShiftPipeXCoordinatesByBasementWidth();
        result = true;
      }
      OS_ASSERT(result);
      return result;
    }

    void PipingSystemUndergroundDomain_Impl::resetShiftPipeXCoordinatesByBasementWidth() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::ShiftPipeXCoordinatesByBasementWidth, ""));
    }

    double PipingSystemUndergroundDomain_Impl::convergenceCriterionfortheOuterCartesianDomainIterationLoop() const {
      const auto value =
        getDouble(openstudio::PipingSystem_Underground_DomainFields::ConvergenceCriterionfortheOuterCartesianDomainIterationLoop, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setConvergenceCriterionfortheOuterCartesianDomainIterationLoop(
      double convergenceCriterionfortheOuterCartesianDomainIterationLoop) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::ConvergenceCriterionfortheOuterCartesianDomainIterationLoop,
                       convergenceCriterionfortheOuterCartesianDomainIterationLoop);
    }

    bool PipingSystemUndergroundDomain_Impl::isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::ConvergenceCriterionfortheOuterCartesianDomainIterationLoop);
    }

    void PipingSystemUndergroundDomain_Impl::resetConvergenceCriterionfortheOuterCartesianDomainIterationLoop() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::ConvergenceCriterionfortheOuterCartesianDomainIterationLoop, ""));
    }

    int PipingSystemUndergroundDomain_Impl::maximumIterationsintheOuterCartesianDomainIterationLoop() const {
      const auto value = getInt(openstudio::PipingSystem_Underground_DomainFields::MaximumIterationsintheOuterCartesianDomainIterationLoop, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setMaximumIterationsintheOuterCartesianDomainIterationLoop(
      int maximumIterationsintheOuterCartesianDomainIterationLoop) {
      return setInt(openstudio::PipingSystem_Underground_DomainFields::MaximumIterationsintheOuterCartesianDomainIterationLoop,
                    maximumIterationsintheOuterCartesianDomainIterationLoop);
    }

    bool PipingSystemUndergroundDomain_Impl::isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::MaximumIterationsintheOuterCartesianDomainIterationLoop);
    }

    void PipingSystemUndergroundDomain_Impl::resetMaximumIterationsintheOuterCartesianDomainIterationLoop() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::MaximumIterationsintheOuterCartesianDomainIterationLoop, ""));
    }

    double PipingSystemUndergroundDomain_Impl::evapotranspirationGroundCoverParameter() const {
      const auto value = getDouble(openstudio::PipingSystem_Underground_DomainFields::EvapotranspirationGroundCoverParameter, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setEvapotranspirationGroundCoverParameter(double evapotranspirationGroundCoverParameter) {
      return setDouble(openstudio::PipingSystem_Underground_DomainFields::EvapotranspirationGroundCoverParameter,
                       evapotranspirationGroundCoverParameter);
    }

    bool PipingSystemUndergroundDomain_Impl::isEvapotranspirationGroundCoverParameterDefaulted() const {
      return isEmpty(openstudio::PipingSystem_Underground_DomainFields::EvapotranspirationGroundCoverParameter);
    }

    void PipingSystemUndergroundDomain_Impl::resetEvapotranspirationGroundCoverParameter() {
      OS_ASSERT(setString(openstudio::PipingSystem_Underground_DomainFields::EvapotranspirationGroundCoverParameter, ""));
    }

    int PipingSystemUndergroundDomain_Impl::numberofPipeCircuitsEnteredforthisDomain() const {
      const auto value = getInt(openstudio::PipingSystem_Underground_DomainFields::NumberofPipeCircuitsEnteredforthisDomain, true);
      OS_ASSERT(value);
      return *value;
    }

    bool PipingSystemUndergroundDomain_Impl::setNumberofPipeCircuitsEnteredforthisDomain(int numberofPipeCircuitsEnteredforthisDomain) {
      return setInt(openstudio::PipingSystem_Underground_DomainFields::NumberofPipeCircuitsEnteredforthisDomain,
                    numberofPipeCircuitsEnteredforthisDomain);
    }

    std::vector<std::string> PipingSystemUndergroundDomain_Impl::xDirectionMeshTypeValues() const {
      return openstudio::epmodel::PipingSystemUndergroundDomain::xDirectionMeshTypeValues();
    }

    std::vector<std::string> PipingSystemUndergroundDomain_Impl::yDirectionMeshTypeValues() const {
      return openstudio::epmodel::PipingSystemUndergroundDomain::yDirectionMeshTypeValues();
    }

    std::vector<std::string> PipingSystemUndergroundDomain_Impl::zDirectionMeshTypeValues() const {
      return openstudio::epmodel::PipingSystemUndergroundDomain::zDirectionMeshTypeValues();
    }

    std::vector<std::string> PipingSystemUndergroundDomain_Impl::undisturbedGroundTemperatureModelTypeValues() const {
      return openstudio::epmodel::PipingSystemUndergroundDomain::undisturbedGroundTemperatureModelTypeValues();
    }

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
