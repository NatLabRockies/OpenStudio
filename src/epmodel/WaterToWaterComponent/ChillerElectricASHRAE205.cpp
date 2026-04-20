/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "WaterToWaterComponent/ChillerElectricASHRAE205.hpp"
#include "WaterToWaterComponent/ChillerElectricASHRAE205_Impl.hpp"

#include "HVACComponent/ThermalZone.hpp"
#include "HVACComponent/ThermalZone_Impl.hpp"
#include "Loop/PlantLoop.hpp"
#include "Loop/PlantLoop_Impl.hpp"
#include "Model.hpp"
#include "ModelObject/Branch.hpp"
#include "ModelObject/BranchList.hpp"
#include "ModelObject/BranchList_Impl.hpp"
#include "Mixer/ConnectorMixer.hpp"
#include "Mixer/ConnectorMixer_Impl.hpp"
#include "Schedule/Schedule.hpp"
#include "Schedule/Schedule_Impl.hpp"
#include "Splitter/ConnectorSplitter.hpp"
#include "Splitter/ConnectorSplitter_Impl.hpp"
#include "StraightComponent/Node.hpp"

#include <utilities/core/Assert.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/Chiller_Electric_ASHRAE205_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

#include <set>

namespace {

bool syncDemandConnectorPorts(openstudio::epmodel::PlantLoop& plantLoop, const std::vector<openstudio::epmodel::Branch>& equipmentBranches) {
  auto splitter = plantLoop.demandSplitter().cast<openstudio::epmodel::ConnectorSplitter>();
  auto mixer = plantLoop.demandMixer().cast<openstudio::epmodel::ConnectorMixer>();

  while (splitter.nextBranchIndex() > equipmentBranches.size()) {
    splitter.removePortForBranch(splitter.nextBranchIndex() - 1u);
  }
  while (mixer.nextBranchIndex() > equipmentBranches.size()) {
    mixer.removePortForBranch(mixer.nextBranchIndex() - 1u);
  }

  for (unsigned i = 0; i < equipmentBranches.size(); ++i) {
    if (!splitter.setOutletModelObject(i, equipmentBranches[i].cast<openstudio::epmodel::ModelObject>())) {
      return false;
    }
    if (!mixer.setInletModelObject(i, equipmentBranches[i].cast<openstudio::epmodel::ModelObject>())) {
      return false;
    }
  }

  return true;
}

}  // namespace

namespace openstudio {
namespace epmodel {

ChillerElectricASHRAE205::ChillerElectricASHRAE205(const Model& model)
  : WaterToWaterComponent(ChillerElectricASHRAE205::iddObjectType(), model) {
  OS_ASSERT(setPerformanceInterpolationMethod("Linear"));
  autosizeRatedCapacity();
  OS_ASSERT(setSizingFactor(1.0));
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, "Outdoors"));
  autosizeChilledWaterMaximumRequestedFlowRate();
  autosizeCondenserMaximumRequestedFlowRate();
  OS_ASSERT(setChillerFlowMode("NotModulated"));
  OS_ASSERT(setEndUseSubcategory("General"));
}

ChillerElectricASHRAE205::ChillerElectricASHRAE205(std::shared_ptr<detail::ChillerElectricASHRAE205_Impl> impl)
  : WaterToWaterComponent(std::move(impl)) {}

IddObjectType ChillerElectricASHRAE205::iddObjectType() {
  return IddObjectType::Chiller_Electric_ASHRAE205;
}

std::vector<std::string> ChillerElectricASHRAE205::performanceInterpolationMethodValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod);
}

std::vector<std::string> ChillerElectricASHRAE205::ambientTemperatureIndicatorValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator);
}

std::vector<std::string> ChillerElectricASHRAE205::chillerFlowModeValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode);
}

std::string ChillerElectricASHRAE205::performanceInterpolationMethod() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->performanceInterpolationMethod();
}

bool ChillerElectricASHRAE205::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setPerformanceInterpolationMethod(performanceInterpolationMethod);
}

boost::optional<double> ChillerElectricASHRAE205::ratedCapacity() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ratedCapacity();
}

bool ChillerElectricASHRAE205::isRatedCapacityAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isRatedCapacityAutosized();
}

bool ChillerElectricASHRAE205::setRatedCapacity(double ratedCapacity) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setRatedCapacity(ratedCapacity);
}

void ChillerElectricASHRAE205::autosizeRatedCapacity() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeRatedCapacity();
}

double ChillerElectricASHRAE205::sizingFactor() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->sizingFactor();
}

bool ChillerElectricASHRAE205::setSizingFactor(double sizingFactor) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setSizingFactor(sizingFactor);
}

std::string ChillerElectricASHRAE205::ambientTemperatureIndicator() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureIndicator();
}

boost::optional<Schedule> ChillerElectricASHRAE205::ambientTemperatureSchedule() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureSchedule();
}

bool ChillerElectricASHRAE205::setAmbientTemperatureSchedule(Schedule& schedule) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAmbientTemperatureSchedule(schedule);
}

void ChillerElectricASHRAE205::resetAmbientTemperatureSchedule() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAmbientTemperatureSchedule();
}

boost::optional<ThermalZone> ChillerElectricASHRAE205::ambientTemperatureZone() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureZone();
}

bool ChillerElectricASHRAE205::setAmbientTemperatureZone(const ThermalZone& thermalZone) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAmbientTemperatureZone(thermalZone);
}

void ChillerElectricASHRAE205::resetAmbientTemperatureZone() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAmbientTemperatureZone();
}

boost::optional<std::string> ChillerElectricASHRAE205::ambientTemperatureOutdoorAirNodeName() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->ambientTemperatureOutdoorAirNodeName();
}

bool ChillerElectricASHRAE205::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureOutdoorAirNodeName);
}

void ChillerElectricASHRAE205::resetAmbientTemperatureOutdoorAirNodeName() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAmbientTemperatureOutdoorAirNodeName();
}

boost::optional<double> ChillerElectricASHRAE205::chilledWaterMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chilledWaterMaximumRequestedFlowRate();
}

bool ChillerElectricASHRAE205::isChilledWaterMaximumRequestedFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isChilledWaterMaximumRequestedFlowRateAutosized();
}

bool ChillerElectricASHRAE205::setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setChilledWaterMaximumRequestedFlowRate(chilledWaterMaximumRequestedFlowRate);
}

void ChillerElectricASHRAE205::autosizeChilledWaterMaximumRequestedFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeChilledWaterMaximumRequestedFlowRate();
}

boost::optional<double> ChillerElectricASHRAE205::condenserMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->condenserMaximumRequestedFlowRate();
}

bool ChillerElectricASHRAE205::isCondenserMaximumRequestedFlowRateAutosized() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isCondenserMaximumRequestedFlowRateAutosized();
}

bool ChillerElectricASHRAE205::setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setCondenserMaximumRequestedFlowRate(condenserMaximumRequestedFlowRate);
}

void ChillerElectricASHRAE205::autosizeCondenserMaximumRequestedFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizeCondenserMaximumRequestedFlowRate();
}

std::string ChillerElectricASHRAE205::chillerFlowMode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chillerFlowMode();
}

bool ChillerElectricASHRAE205::setChillerFlowMode(const std::string& chillerFlowMode) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setChillerFlowMode(chillerFlowMode);
}

boost::optional<double> ChillerElectricASHRAE205::oilCoolerDesignFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerDesignFlowRate();
}

bool ChillerElectricASHRAE205::setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setOilCoolerDesignFlowRate(oilCoolerDesignFlowRate);
}

void ChillerElectricASHRAE205::resetOilCoolerDesignFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetOilCoolerDesignFlowRate();
}

boost::optional<double> ChillerElectricASHRAE205::auxiliaryCoolingDesignFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryCoolingDesignFlowRate();
}

bool ChillerElectricASHRAE205::setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setAuxiliaryCoolingDesignFlowRate(auxiliaryCoolingDesignFlowRate);
}

void ChillerElectricASHRAE205::resetAuxiliaryCoolingDesignFlowRate() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetAuxiliaryCoolingDesignFlowRate();
}

std::string ChillerElectricASHRAE205::endUseSubcategory() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->endUseSubcategory();
}

bool ChillerElectricASHRAE205::isEndUseSubcategoryDefaulted() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->isEndUseSubcategoryDefaulted();
}

bool ChillerElectricASHRAE205::setEndUseSubcategory(const std::string& endUseSubcategory) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->setEndUseSubcategory(endUseSubcategory);
}

void ChillerElectricASHRAE205::resetEndUseSubcategory() {
  getImpl<detail::ChillerElectricASHRAE205_Impl>()->resetEndUseSubcategory();
}

boost::optional<double> ChillerElectricASHRAE205::autosizedRatedCapacity() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizedRatedCapacity();
}

boost::optional<double> ChillerElectricASHRAE205::autosizedChilledWaterMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizedChilledWaterMaximumRequestedFlowRate();
}

boost::optional<double> ChillerElectricASHRAE205::autosizedCondenserMaximumRequestedFlowRate() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->autosizedCondenserMaximumRequestedFlowRate();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205::chilledWaterLoop() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chilledWaterLoop();
}

boost::optional<Node> ChillerElectricASHRAE205::chilledWaterInletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chilledWaterInletNode();
}

boost::optional<Node> ChillerElectricASHRAE205::chilledWaterOutletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->chilledWaterOutletNode();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205::condenserWaterLoop() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->condenserWaterLoop();
}

boost::optional<Node> ChillerElectricASHRAE205::condenserInletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->condenserInletNode();
}

boost::optional<Node> ChillerElectricASHRAE205::condenserOutletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->condenserOutletNode();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205::heatRecoveryLoop() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->heatRecoveryLoop();
}

boost::optional<Node> ChillerElectricASHRAE205::heatRecoveryInletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->heatRecoveryInletNode();
}

boost::optional<Node> ChillerElectricASHRAE205::heatRecoveryOutletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->heatRecoveryOutletNode();
}

unsigned ChillerElectricASHRAE205::oilCoolerInletPort() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerInletPort();
}

boost::optional<ModelObject> ChillerElectricASHRAE205::oilCoolerInletModelObject() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerInletModelObject();
}

boost::optional<Node> ChillerElectricASHRAE205::oilCoolerInletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerInletNode();
}

unsigned ChillerElectricASHRAE205::oilCoolerOutletPort() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerOutletPort();
}

boost::optional<ModelObject> ChillerElectricASHRAE205::oilCoolerOutletModelObject() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerOutletModelObject();
}

boost::optional<Node> ChillerElectricASHRAE205::oilCoolerOutletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerOutletNode();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205::oilCoolerLoop() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->oilCoolerLoop();
}

bool ChillerElectricASHRAE205::addDemandBranchOnOilCoolerLoop(PlantLoop& plantLoop) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->addDemandBranchOnOilCoolerLoop(plantLoop);
}

bool ChillerElectricASHRAE205::addToOilCoolerLoopNode(Node& node) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->addToOilCoolerLoopNode(node);
}

bool ChillerElectricASHRAE205::removeFromOilCoolerLoop() {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->removeFromOilCoolerLoop();
}

unsigned ChillerElectricASHRAE205::auxiliaryInletPort() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryInletPort();
}

boost::optional<ModelObject> ChillerElectricASHRAE205::auxiliaryInletModelObject() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryInletModelObject();
}

boost::optional<Node> ChillerElectricASHRAE205::auxiliaryInletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryInletNode();
}

unsigned ChillerElectricASHRAE205::auxiliaryOutletPort() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryOutletPort();
}

boost::optional<ModelObject> ChillerElectricASHRAE205::auxiliaryOutletModelObject() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryOutletModelObject();
}

boost::optional<Node> ChillerElectricASHRAE205::auxiliaryOutletNode() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryOutletNode();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205::auxiliaryLoop() const {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->auxiliaryLoop();
}

bool ChillerElectricASHRAE205::addDemandBranchOnAuxiliaryLoop(PlantLoop& plantLoop) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->addDemandBranchOnAuxiliaryLoop(plantLoop);
}

bool ChillerElectricASHRAE205::addToAuxiliaryLoopNode(Node& node) {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->addToAuxiliaryLoopNode(node);
}

bool ChillerElectricASHRAE205::removeFromAuxiliaryLoop() {
  return getImpl<detail::ChillerElectricASHRAE205_Impl>()->removeFromAuxiliaryLoop();
}

}  // namespace epmodel
}  // namespace openstudio

namespace openstudio {
namespace epmodel {
namespace detail {

std::string ChillerElectricASHRAE205_Impl::performanceInterpolationMethod() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setPerformanceInterpolationMethod(const std::string& performanceInterpolationMethod) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::PerformanceInterpolationMethod, performanceInterpolationMethod);
  return result;
}

boost::optional<double> ChillerElectricASHRAE205_Impl::ratedCapacity() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, true);
}

bool ChillerElectricASHRAE205_Impl::isRatedCapacityAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setRatedCapacity(double ratedCapacity) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, ratedCapacity);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeRatedCapacity() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::RatedCapacity, "Autosize"));
}

double ChillerElectricASHRAE205_Impl::sizingFactor() const {
  const auto value = getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::SizingFactor, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setSizingFactor(double sizingFactor) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::SizingFactor, sizingFactor);
  return result;
}

std::string ChillerElectricASHRAE205_Impl::ambientTemperatureIndicator() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureIndicator(const std::string& ambientTemperatureIndicator) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureIndicator, ambientTemperatureIndicator);
  return result;
}

boost::optional<Schedule> ChillerElectricASHRAE205_Impl::ambientTemperatureSchedule() const {
  return getObject<ModelObject>().getModelObjectTarget<Schedule>(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureScheduleName);
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureSchedule(Schedule& schedule) {
  const bool result =
    setSchedule(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureScheduleName, "ChillerElectricASHRAE205",
                "Ambient Temperature", schedule);
  if (result) {
    const bool ok = setAmbientTemperatureIndicator("Schedule");
    OS_ASSERT(ok);
  }
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAmbientTemperatureSchedule() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureScheduleName, ""));
  if (openstudio::istringEqual("Schedule", ambientTemperatureIndicator())) {
    OS_ASSERT(setAmbientTemperatureIndicator("Outdoors"));
  }
}

boost::optional<ThermalZone> ChillerElectricASHRAE205_Impl::ambientTemperatureZone() const {
  return getObject<ModelObject>().getModelObjectTarget<ThermalZone>(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureZoneName);
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureZone(const ThermalZone& thermalZone) {
  const bool result = setPointer(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureZoneName, thermalZone.handle());
  if (result) {
    const bool ok = setAmbientTemperatureIndicator("Zone");
    OS_ASSERT(ok);
  }
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAmbientTemperatureZone() {
  OS_ASSERT(setPointer(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureZoneName, Handle(), false));
  if (openstudio::istringEqual("Zone", ambientTemperatureIndicator())) {
    OS_ASSERT(setAmbientTemperatureIndicator("Outdoors"));
  }
}

boost::optional<std::string> ChillerElectricASHRAE205_Impl::ambientTemperatureOutdoorAirNodeName() const {
  auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, false, true);
  if (value && value->empty()) {
    return boost::none;
  }
  return value;
}

bool ChillerElectricASHRAE205_Impl::setAmbientTemperatureOutdoorAirNodeName(const std::string& ambientTemperatureOutdoorAirNodeName) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName,
                                ambientTemperatureOutdoorAirNodeName);
  if (result) {
    const bool ok = setAmbientTemperatureIndicator("Outdoors");
    OS_ASSERT(ok);
  }
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAmbientTemperatureOutdoorAirNodeName() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AmbientTemperatureOutdoorAirNodeName, ""));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::chilledWaterMaximumRequestedFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::isChilledWaterMaximumRequestedFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setChilledWaterMaximumRequestedFlowRate(double chilledWaterMaximumRequestedFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, chilledWaterMaximumRequestedFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeChilledWaterMaximumRequestedFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterMaximumRequestedFlowRate, "Autosize"));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::condenserMaximumRequestedFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::isCondenserMaximumRequestedFlowRateAutosized() const {
  if (auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, true)) {
    return openstudio::istringEqual(*value, "Autosize");
  }
  return false;
}

bool ChillerElectricASHRAE205_Impl::setCondenserMaximumRequestedFlowRate(double condenserMaximumRequestedFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, condenserMaximumRequestedFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::autosizeCondenserMaximumRequestedFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::CondenserMaximumRequestedFlowRate, "Autosize"));
}

std::string ChillerElectricASHRAE205_Impl::chillerFlowMode() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::setChillerFlowMode(const std::string& chillerFlowMode) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::ChillerFlowMode, chillerFlowMode);
  return result;
}

boost::optional<double> ChillerElectricASHRAE205_Impl::oilCoolerDesignFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::setOilCoolerDesignFlowRate(double oilCoolerDesignFlowRate) {
  const bool result = setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, oilCoolerDesignFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetOilCoolerDesignFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerDesignFlowRate, ""));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::auxiliaryCoolingDesignFlowRate() const {
  return getDouble(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, true);
}

bool ChillerElectricASHRAE205_Impl::setAuxiliaryCoolingDesignFlowRate(double auxiliaryCoolingDesignFlowRate) {
  const bool result =
    setDouble(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, auxiliaryCoolingDesignFlowRate);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetAuxiliaryCoolingDesignFlowRate() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryCoolingDesignFlowRate, ""));
}

std::string ChillerElectricASHRAE205_Impl::endUseSubcategory() const {
  const auto value = getString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, true);
  OS_ASSERT(value);
  return *value;
}

bool ChillerElectricASHRAE205_Impl::isEndUseSubcategoryDefaulted() const {
  return isEmpty(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory);
}

bool ChillerElectricASHRAE205_Impl::setEndUseSubcategory(const std::string& endUseSubcategory) {
  const bool result = setString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, endUseSubcategory);
  OS_ASSERT(result);
  return result;
}

void ChillerElectricASHRAE205_Impl::resetEndUseSubcategory() {
  OS_ASSERT(setString(openstudio::Chiller_Electric_ASHRAE205Fields::EndUseSubcategory, ""));
}

boost::optional<double> ChillerElectricASHRAE205_Impl::autosizedRatedCapacity() const {
  return getAutosizedValue("Design Size Rated Capacity", "W");
}

boost::optional<double> ChillerElectricASHRAE205_Impl::autosizedChilledWaterMaximumRequestedFlowRate() const {
  return getAutosizedValue("Design Size Chilled Water Maximum Requested Flow Rate", "m3/s");
}

boost::optional<double> ChillerElectricASHRAE205_Impl::autosizedCondenserMaximumRequestedFlowRate() const {
  return getAutosizedValue("Design Size Condenser Maximum Requested Flow Rate", "m3/s");
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::performanceInterpolationMethodValues() const {
  return ChillerElectricASHRAE205::performanceInterpolationMethodValues();
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::ambientTemperatureIndicatorValues() const {
  return ChillerElectricASHRAE205::ambientTemperatureIndicatorValues();
}

std::vector<std::string> ChillerElectricASHRAE205_Impl::chillerFlowModeValues() const {
  return ChillerElectricASHRAE205::chillerFlowModeValues();
}

boost::optional<PlantLoop> ChillerElectricASHRAE205_Impl::chilledWaterLoop() const {
  return plantLoop();
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::chilledWaterInletNode() const {
  if (auto mo = supplyInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::chilledWaterOutletNode() const {
  if (auto mo = supplyOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<PlantLoop> ChillerElectricASHRAE205_Impl::condenserWaterLoop() const {
  return secondaryPlantLoop();
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::condenserInletNode() const {
  if (auto mo = demandInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::condenserOutletNode() const {
  if (auto mo = demandOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<PlantLoop> ChillerElectricASHRAE205_Impl::heatRecoveryLoop() const {
  return tertiaryPlantLoop();
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::heatRecoveryInletNode() const {
  if (auto mo = tertiaryInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::heatRecoveryOutletNode() const {
  if (auto mo = tertiaryOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

unsigned ChillerElectricASHRAE205_Impl::supplyInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::supplyOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::ChilledWaterOutletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::demandInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::CondenserInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::demandOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::CondenserOutletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::tertiaryInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::HeatRecoveryInletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::tertiaryOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::HeatRecoveryOutletNodeName;
}

unsigned ChillerElectricASHRAE205_Impl::oilCoolerInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerInletNodeName;
}

boost::optional<ModelObject> ChillerElectricASHRAE205_Impl::oilCoolerInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(oilCoolerInletPort());
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::oilCoolerInletNode() const {
  if (auto mo = oilCoolerInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

unsigned ChillerElectricASHRAE205_Impl::oilCoolerOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::OilCoolerOutletNodeName;
}

boost::optional<ModelObject> ChillerElectricASHRAE205_Impl::oilCoolerOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(oilCoolerOutletPort());
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::oilCoolerOutletNode() const {
  if (auto mo = oilCoolerOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<PlantLoop> ChillerElectricASHRAE205_Impl::oilCoolerLoop() const {
  if (auto node = oilCoolerOutletNode()) {
    return node->plantLoop();
  }
  return boost::none;
}

bool ChillerElectricASHRAE205_Impl::removeFromOilCoolerLoop() {
  return removeFromBranch(oilCoolerInletPort(), oilCoolerOutletPort(), oilCoolerLoop());
}

bool ChillerElectricASHRAE205_Impl::addDemandBranchOnOilCoolerLoop(PlantLoop& plantLoop) {
  if (plantLoop.model() != model()) {
    return false;
  }

  auto equipmentBranches = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches();
  if ((equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
    auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
    return addToOilCoolerLoopNode(node);
  }

  auto branchList = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandBranchList();
  const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
  Branch branch(model());
  if (!branch.setName(plantLoop.nameString() + " Demand Branch " + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
    branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
  }
  if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
    return false;
  }

  equipmentBranches = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches();
  if (!syncDemandConnectorPorts(plantLoop, equipmentBranches)) {
    branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
    branch.remove();
    return false;
  }

  auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
  if (addToOilCoolerLoopNode(node)) {
    return true;
  }

  branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
  syncDemandConnectorPorts(plantLoop, plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches());
  branch.remove();
  node.remove();
  return false;
}

bool ChillerElectricASHRAE205_Impl::addToOilCoolerLoopNode(Node& node) {
  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
    return false;
  }

  auto branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  removeFromOilCoolerLoop();
  return insertOnBranch(node, *branch, oilCoolerInletPort(), oilCoolerOutletPort());
}

unsigned ChillerElectricASHRAE205_Impl::auxiliaryInletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryInletNodeName;
}

boost::optional<ModelObject> ChillerElectricASHRAE205_Impl::auxiliaryInletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(auxiliaryInletPort());
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::auxiliaryInletNode() const {
  if (auto mo = auxiliaryInletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

unsigned ChillerElectricASHRAE205_Impl::auxiliaryOutletPort() const {
  return openstudio::Chiller_Electric_ASHRAE205Fields::AuxiliaryOutletNodeName;
}

boost::optional<ModelObject> ChillerElectricASHRAE205_Impl::auxiliaryOutletModelObject() const {
  return getObject<ModelObject>().getModelObjectTarget<ModelObject>(auxiliaryOutletPort());
}

boost::optional<Node> ChillerElectricASHRAE205_Impl::auxiliaryOutletNode() const {
  if (auto mo = auxiliaryOutletModelObject()) {
    return mo->optionalCast<Node>();
  }
  return boost::none;
}

boost::optional<PlantLoop> ChillerElectricASHRAE205_Impl::auxiliaryLoop() const {
  if (auto node = auxiliaryOutletNode()) {
    return node->plantLoop();
  }
  return boost::none;
}

bool ChillerElectricASHRAE205_Impl::removeFromAuxiliaryLoop() {
  return removeFromBranch(auxiliaryInletPort(), auxiliaryOutletPort(), auxiliaryLoop());
}

bool ChillerElectricASHRAE205_Impl::addDemandBranchOnAuxiliaryLoop(PlantLoop& plantLoop) {
  if (plantLoop.model() != model()) {
    return false;
  }

  auto equipmentBranches = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches();
  if ((equipmentBranches.size() == 1u) && equipmentBranches.front().components().empty()) {
    auto node = model().getOrCreateTransientByName<Node>(equipmentBranches.front().nameString() + " Node");
    return addToAuxiliaryLoopNode(node);
  }

  auto branchList = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandBranchList();
  const auto insertIndex = static_cast<unsigned>(branchList.branches().size() - 1u);
  Branch branch(model());
  if (!branch.setName(plantLoop.nameString() + " Demand Branch " + std::to_string(static_cast<unsigned>(equipmentBranches.size() + 1u)))) {
    branch.setName(model().nextName(openstudio::IddObjectType::Branch, true));
  }
  if (!branchList.getImpl<detail::BranchList_Impl>()->insertBranch(insertIndex, branch)) {
    return false;
  }

  equipmentBranches = plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches();
  if (!syncDemandConnectorPorts(plantLoop, equipmentBranches)) {
    branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
    branch.remove();
    return false;
  }

  auto node = model().getOrCreateTransientByName<Node>(branch.nameString() + " Node");
  if (addToAuxiliaryLoopNode(node)) {
    return true;
  }

  branchList.getImpl<detail::BranchList_Impl>()->removeBranch(branch);
  syncDemandConnectorPorts(plantLoop, plantLoop.getImpl<detail::PlantLoop_Impl>()->demandEquipmentBranches());
  branch.remove();
  node.remove();
  return false;
}

bool ChillerElectricASHRAE205_Impl::addToAuxiliaryLoopNode(Node& node) {
  auto plantLoop_ = node.plantLoop();
  if (!plantLoop_ || !plantLoop_->demandComponent(node.handle())) {
    return false;
  }

  auto branch = plantLoop_->getImpl<detail::PlantLoop_Impl>()->branchForNode(node);
  if (!branch) {
    return false;
  }

  removeFromAuxiliaryLoop();
  return insertOnBranch(node, *branch, auxiliaryInletPort(), auxiliaryOutletPort());
}

bool ChillerElectricASHRAE205_Impl::addToNode(Node& node) {
  if (shouldRouteDemandSideNodeToTertiary(node)) {
    return false;
  }
  return WaterToWaterComponent_Impl::addToNode(node);
}

bool ChillerElectricASHRAE205_Impl::addToTertiaryNode(Node&) {
  return false;
}

ComponentType ChillerElectricASHRAE205_Impl::componentType() const {
  return ComponentType::Cooling;
}

std::vector<FuelType> ChillerElectricASHRAE205_Impl::coolingFuelTypes() const {
  std::set<FuelType> result{FuelType::Electricity};
  if (auto condenserLoop_ = condenserWaterLoop()) {
    for (const auto fuelType : condenserLoop_->coolingFuelTypes()) {
      result.insert(fuelType);
    }
  }
  return {result.begin(), result.end()};
}

std::vector<FuelType> ChillerElectricASHRAE205_Impl::heatingFuelTypes() const {
  return {};
}

std::vector<AppGFuelType> ChillerElectricASHRAE205_Impl::appGHeatingFuelTypes() const {
  return {};
}

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio
