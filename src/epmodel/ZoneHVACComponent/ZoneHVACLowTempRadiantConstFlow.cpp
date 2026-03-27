/***********************************************************************************************************************  
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.  
*  See also https://openstudio.net/license  
***********************************************************************************************************************/

#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"
#include "ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow_Impl.hpp"

#include "Model.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/core/Compare.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneHVAC_LowTemperatureRadiant_ConstantFlow_Design_FieldEnums.hxx>

namespace openstudio {
namespace epmodel {

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(const Model& model)
    : ZoneHVACComponent(ZoneHVACLowTempRadiantConstFlow::iddObjectType(), model) {
    OS_ASSERT(getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>());
  }

  ZoneHVACLowTempRadiantConstFlow::ZoneHVACLowTempRadiantConstFlow(std::shared_ptr<detail::ZoneHVACLowTempRadiantConstFlow_Impl> impl)
    : ZoneHVACComponent(std::move(impl)) {}

  IddObjectType ZoneHVACLowTempRadiantConstFlow::iddObjectType() {
    return IddObjectType::ZoneHVAC_LowTemperatureRadiant_ConstantFlow;
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::numberofCircuitsValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModelValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::FluidtoRadiantSurfaceHeatTransferModel);
  }

  std::vector<std::string> ZoneHVACLowTempRadiantConstFlow::temperatureControlTypeValues() {
    return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                          ZoneHVAC_LowTemperatureRadiant_ConstantFlow_DesignFields::TemperatureControlType);
  }

  unsigned detail::ZoneHVACLowTempRadiantConstFlow_Impl::inletPort() const {
    return 0u;
  }

  unsigned detail::ZoneHVACLowTempRadiantConstFlow_Impl::outletPort() const {
    return 0u;
  }

  std::string ZoneHVACLowTempRadiantConstFlow::fluidtoRadiantSurfaceHeatTransferModel() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fluidtoRadiantSurfaceHeatTransferModel();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFluidtoRadiantSurfaceHeatTransferModelDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setFluidtoRadiantSurfaceHeatTransferModel(const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFluidtoRadiantSurfaceHeatTransferModel(fluidtoRadiantSurfaceHeatTransferModel);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetFluidtoRadiantSurfaceHeatTransferModel() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFluidtoRadiantSurfaceHeatTransferModel();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingInsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingInsideDiameter();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingInsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingInsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingInsideDiameter(hydronicTubingInsideDiameter);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingInsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingInsideDiameter();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingOutsideDiameter() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingOutsideDiameter();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingOutsideDiameterDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingOutsideDiameterDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingOutsideDiameter(hydronicTubingOutsideDiameter);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingOutsideDiameter() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingOutsideDiameter();
  }

  double ZoneHVACLowTempRadiantConstFlow::hydronicTubingConductivity() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingConductivity();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingConductivityDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingConductivityDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingConductivity(double hydronicTubingConductivity) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingConductivity(hydronicTubingConductivity);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetHydronicTubingConductivity() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetHydronicTubingConductivity();
  }

  std::string ZoneHVACLowTempRadiantConstFlow::temperatureControlType() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->temperatureControlType();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isTemperatureControlTypeDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isTemperatureControlTypeDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setTemperatureControlType(const std::string& temperatureControlType) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setTemperatureControlType(temperatureControlType);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetTemperatureControlType() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetTemperatureControlType();
  }

  double ZoneHVACLowTempRadiantConstFlow::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->runningMeanOutdoorDryBulbTemperatureWeightingFactor();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
    double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
      runningMeanOutdoorDryBulbTemperatureWeightingFactor);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor();
  }

  double ZoneHVACLowTempRadiantConstFlow::motorEfficiency() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->motorEfficiency();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isMotorEfficiencyDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isMotorEfficiencyDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setMotorEfficiency(double motorEfficiency) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setMotorEfficiency(motorEfficiency);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetMotorEfficiency() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetMotorEfficiency();
  }

  double ZoneHVACLowTempRadiantConstFlow::fractionofMotorInefficienciestoFluidStream() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->fractionofMotorInefficienciestoFluidStream();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isFractionofMotorInefficienciestoFluidStreamDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setFractionofMotorInefficienciestoFluidStream(double fractionofMotorInefficienciestoFluidStream) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setFractionofMotorInefficienciestoFluidStream(
      fractionofMotorInefficienciestoFluidStream);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetFractionofMotorInefficienciestoFluidStream() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetFractionofMotorInefficienciestoFluidStream();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::hydronicTubingLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->hydronicTubingLength();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isHydronicTubingLengthAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isHydronicTubingLengthAutosized();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setHydronicTubingLength(double hydronicTubingLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setHydronicTubingLength(hydronicTubingLength);
  }

  void ZoneHVACLowTempRadiantConstFlow::autosizeHydronicTubingLength() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeHydronicTubingLength();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedFlowRate() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedFlowRate();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRatedFlowRateAutosized() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedFlowRateAutosized();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedFlowRate(double ratedFlowRate) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedFlowRate(ratedFlowRate);
  }

  void ZoneHVACLowTempRadiantConstFlow::autosizeRatedFlowRate() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->autosizeRatedFlowRate();
  }

  double ZoneHVACLowTempRadiantConstFlow::ratedPumpHead() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPumpHead();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isRatedPumpHeadDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isRatedPumpHeadDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedPumpHead(double ratedPumpHead) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPumpHead(ratedPumpHead);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRatedPumpHead() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPumpHead();
  }

  boost::optional<double> ZoneHVACLowTempRadiantConstFlow::ratedPowerConsumption() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->ratedPowerConsumption();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setRatedPowerConsumption(double ratedPowerConsumption) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setRatedPowerConsumption(ratedPowerConsumption);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetRatedPowerConsumption() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetRatedPowerConsumption();
  }

  std::string ZoneHVACLowTempRadiantConstFlow::numberofCircuits() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->numberofCircuits();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isNumberofCircuitsDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isNumberofCircuitsDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setNumberofCircuits(const std::string& numberofCircuits) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setNumberofCircuits(numberofCircuits);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetNumberofCircuits() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetNumberofCircuits();
  }

  double ZoneHVACLowTempRadiantConstFlow::circuitLength() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->circuitLength();
  }

  bool ZoneHVACLowTempRadiantConstFlow::isCircuitLengthDefaulted() const {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->isCircuitLengthDefaulted();
  }

  bool ZoneHVACLowTempRadiantConstFlow::setCircuitLength(double circuitLength) {
    return getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->setCircuitLength(circuitLength);
  }

  void ZoneHVACLowTempRadiantConstFlow::resetCircuitLength() {
    getImpl<detail::ZoneHVACLowTempRadiantConstFlow_Impl>()->resetCircuitLength();
  }

  namespace detail {

    namespace {
      constexpr const char* kDefaultFluidtoRadiantSurfaceHeatTransferModel = "ConvectionOnly";
      constexpr const char* kDefaultTemperatureControlType = "MeanAirTemperature";
      constexpr double kDefaultHydronicTubingInsideDiameter = 0.013;
      constexpr double kDefaultHydronicTubingOutsideDiameter = 0.016;
      constexpr double kDefaultHydronicTubingConductivity = 0.35;
      constexpr double kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor = 0.8;
      constexpr double kDefaultMotorEfficiency = 0.9;
      constexpr double kDefaultFractionofMotorInefficienciestoFluidStream = 0.0;
    }  // namespace

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::fluidtoRadiantSurfaceHeatTransferModel() const {
      return m_fluidtoRadiantSurfaceHeatTransferModel ? m_fluidtoRadiantSurfaceHeatTransferModel.get()
                                                       : kDefaultFluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isFluidtoRadiantSurfaceHeatTransferModelDefaulted() const {
      return !m_fluidtoRadiantSurfaceHeatTransferModel;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setFluidtoRadiantSurfaceHeatTransferModel(
      const std::string& fluidtoRadiantSurfaceHeatTransferModel) {
      m_fluidtoRadiantSurfaceHeatTransferModel = fluidtoRadiantSurfaceHeatTransferModel;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetFluidtoRadiantSurfaceHeatTransferModel() {
      m_fluidtoRadiantSurfaceHeatTransferModel = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingInsideDiameter() const {
      return m_hydronicTubingInsideDiameter ? m_hydronicTubingInsideDiameter.get() : kDefaultHydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingInsideDiameterDefaulted() const {
      return !m_hydronicTubingInsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingInsideDiameter(double hydronicTubingInsideDiameter) {
      m_hydronicTubingInsideDiameter = hydronicTubingInsideDiameter;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingInsideDiameter() {
      m_hydronicTubingInsideDiameter = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingOutsideDiameter() const {
      return m_hydronicTubingOutsideDiameter ? m_hydronicTubingOutsideDiameter.get() : kDefaultHydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingOutsideDiameterDefaulted() const {
      return !m_hydronicTubingOutsideDiameter;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingOutsideDiameter(double hydronicTubingOutsideDiameter) {
      m_hydronicTubingOutsideDiameter = hydronicTubingOutsideDiameter;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingOutsideDiameter() {
      m_hydronicTubingOutsideDiameter = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingConductivity() const {
      return m_hydronicTubingConductivity ? m_hydronicTubingConductivity.get() : kDefaultHydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingConductivityDefaulted() const {
      return !m_hydronicTubingConductivity;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingConductivity(double hydronicTubingConductivity) {
      m_hydronicTubingConductivity = hydronicTubingConductivity;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetHydronicTubingConductivity() {
      m_hydronicTubingConductivity = boost::none;
    }

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::temperatureControlType() const {
      return m_temperatureControlType ? m_temperatureControlType.get() : kDefaultTemperatureControlType;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isTemperatureControlTypeDefaulted() const {
      return !m_temperatureControlType;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setTemperatureControlType(const std::string& temperatureControlType) {
      m_temperatureControlType = temperatureControlType;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetTemperatureControlType() {
      m_temperatureControlType = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::runningMeanOutdoorDryBulbTemperatureWeightingFactor() const {
      return m_runningMeanOutdoorDryBulbTemperatureWeightingFactor ?
               m_runningMeanOutdoorDryBulbTemperatureWeightingFactor.get()
               : kDefaultRunningMeanOutdoorDryBulbTemperatureWeightingFactor;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRunningMeanOutdoorDryBulbTemperatureWeightingFactorDefaulted() const {
      return !m_runningMeanOutdoorDryBulbTemperatureWeightingFactor;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRunningMeanOutdoorDryBulbTemperatureWeightingFactor(
      double runningMeanOutdoorDryBulbTemperatureWeightingFactor) {
      m_runningMeanOutdoorDryBulbTemperatureWeightingFactor = runningMeanOutdoorDryBulbTemperatureWeightingFactor;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRunningMeanOutdoorDryBulbTemperatureWeightingFactor() {
      m_runningMeanOutdoorDryBulbTemperatureWeightingFactor = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::motorEfficiency() const {
      return m_motorEfficiency ? m_motorEfficiency.get() : kDefaultMotorEfficiency;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isMotorEfficiencyDefaulted() const {
      return !m_motorEfficiency;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setMotorEfficiency(double motorEfficiency) {
      m_motorEfficiency = motorEfficiency;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetMotorEfficiency() {
      m_motorEfficiency = boost::none;
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::fractionofMotorInefficienciestoFluidStream() const {
      return m_fractionofMotorInefficienciestoFluidStream ?
               m_fractionofMotorInefficienciestoFluidStream.get() : kDefaultFractionofMotorInefficienciestoFluidStream;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isFractionofMotorInefficienciestoFluidStreamDefaulted() const {
      return !m_fractionofMotorInefficienciestoFluidStream;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setFractionofMotorInefficienciestoFluidStream(
      double fractionofMotorInefficienciestoFluidStream) {
      m_fractionofMotorInefficienciestoFluidStream = fractionofMotorInefficienciestoFluidStream;
      return true;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetFractionofMotorInefficienciestoFluidStream() {
      m_fractionofMotorInefficienciestoFluidStream = boost::none;
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::hydronicTubingLength() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isHydronicTubingLengthAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setHydronicTubingLength(double hydronicTubingLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, hydronicTubingLength);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeHydronicTubingLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, "Autosize", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedFlowRate() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedFlowRateAutosized() const {
      bool result = false;
      if (auto value = getString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, true)) {
        result = openstudio::istringEqual(value.get(), "Autosize");
      }
      return result;
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedFlowRate(double ratedFlowRate) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, ratedFlowRate);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::autosizeRatedFlowRate() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, "Autosize", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::ratedPumpHead() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isRatedPumpHeadDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPumpHead(double ratedPumpHead) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, ratedPumpHead, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPumpHead() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, "", false);
      OS_ASSERT(result);
    }

    boost::optional<double> ZoneHVACLowTempRadiantConstFlow_Impl::ratedPowerConsumption() const {
      return getDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, true);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setRatedPowerConsumption(double ratedPowerConsumption) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, ratedPowerConsumption);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetRatedPowerConsumption() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, "", false);
      OS_ASSERT(result);
    }

    std::string ZoneHVACLowTempRadiantConstFlow_Impl::numberofCircuits() const {
      auto value = getString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isNumberofCircuitsDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setNumberofCircuits(const std::string& numberofCircuits) {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, numberofCircuits, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetNumberofCircuits() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, "", false);
      OS_ASSERT(result);
    }

    double ZoneHVACLowTempRadiantConstFlow_Impl::circuitLength() const {
      auto value = getDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, true);
      OS_ASSERT(value);
      return value.get();
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::isCircuitLengthDefaulted() const {
      return isEmpty(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength);
    }

    bool ZoneHVACLowTempRadiantConstFlow_Impl::setCircuitLength(double circuitLength) {
      const bool result = setDouble(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, circuitLength, false);
      OS_ASSERT(result);
      return result;
    }

    void ZoneHVACLowTempRadiantConstFlow_Impl::resetCircuitLength() {
      const bool result = setString(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, "", false);
      OS_ASSERT(result);
    }

  }  // namespace detail

}  // namespace epmodel
}  // namespace openstudio
