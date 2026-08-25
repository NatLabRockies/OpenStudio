/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/idd/EvaporativeFluidCooler_TwoSpeed_FieldEnums.hxx>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerTwoSpeed.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerTwoSpeed_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedTwoSpeedCoolerFileRemoval
{
 public:
  explicit ScopedTwoSpeedCoolerFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedTwoSpeedCoolerFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueTwoSpeedCoolerPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_DefaultConstructor) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  EXPECT_EQ(EvaporativeFluidCoolerTwoSpeed::iddObjectType(), evap.iddObject().type());
  EXPECT_FALSE(evap.nameString().empty());

  EXPECT_FALSE(evap.highFanSpeedAirFlowRate());
  EXPECT_TRUE(evap.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_FALSE(evap.highFanSpeedFanPower());
  EXPECT_TRUE(evap.isHighFanSpeedFanPowerAutosized());

  EXPECT_FALSE(evap.lowFanSpeedAirFlowRate());
  EXPECT_TRUE(evap.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.5, evap.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_FALSE(evap.lowFanSpeedFanPower());
  EXPECT_TRUE(evap.isLowFanSpeedFanPowerAutosized());

  EXPECT_DOUBLE_EQ(0.5, evap.lowFanSpeedFanPowerSizingFactor());
  EXPECT_DOUBLE_EQ(0.002208, evap.designSprayWaterFlowRate());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());
  EXPECT_DOUBLE_EQ(1.25, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_FALSE(evap.highSpeedStandardDesignCapacity());
  EXPECT_FALSE(evap.lowSpeedStandardDesignCapacity());
  EXPECT_TRUE(evap.isLowSpeedStandardDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.5, evap.lowSpeedStandardCapacitySizingFactor());

  EXPECT_FALSE(evap.highFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(evap.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_FALSE(evap.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_TRUE(evap.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_DOUBLE_EQ(0.6, evap.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_FALSE(evap.designWaterFlowRate());
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_FALSE(evap.highSpeedUserSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.lowSpeedUserSpecifiedDesignCapacity());
  EXPECT_TRUE(evap.isLowSpeedUserSpecifiedDesignCapacityAutosized());
  EXPECT_DOUBLE_EQ(0.5, evap.lowSpeedUserSpecifiedDesignCapacitySizingFactor());

  EXPECT_FALSE(evap.designEnteringWaterTemperature());
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_DOUBLE_EQ(35.0, evap.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, evap.designEnteringAirWetbulbTemperature());
  EXPECT_DOUBLE_EQ(1.0, evap.highSpeedSizingFactor());
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());
  EXPECT_FALSE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.008, evap.driftLossPercent());
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
  EXPECT_DOUBLE_EQ(3.0, evap.blowdownConcentrationRatio());
  EXPECT_FALSE(evap.blowdownMakeupWaterUsageSchedule());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_BlowdownScheduleValidationAndReset) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed cooler(model);
  ScheduleConstant schedule(model);
  ASSERT_TRUE(schedule.setValue(0.0001));
  ASSERT_TRUE(cooler.setBlowdownMakeupWaterUsageSchedule(schedule));
  ASSERT_TRUE(cooler.blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(schedule.handle(), cooler.blowdownMakeupWaterUsageSchedule()->handle());
  ASSERT_TRUE(schedule.scheduleTypeLimits());
  ASSERT_TRUE(schedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", schedule.scheduleTypeLimits()->numericType().get());
  EXPECT_EQ("VolumetricFlowRate", schedule.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(schedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, schedule.scheduleTypeLimits()->lowerLimitValue().get());
  EXPECT_FALSE(schedule.scheduleTypeLimits()->upperLimitValue());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(incompatibleLimits));
  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(cooler.setBlowdownMakeupWaterUsageSchedule(incompatible));
  EXPECT_FALSE(cooler.setBlowdownMakeupWaterUsageSchedule(foreign));
  EXPECT_EQ(schedule.handle(), cooler.blowdownMakeupWaterUsageSchedule()->handle());

  constexpr auto field = openstudio::EvaporativeFluidCooler_TwoSpeedFields::BlowdownMakeupWaterUsageScheduleName;
  auto workspaceImpl = cooler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Two Speed Blowdown", false));
  EXPECT_FALSE(cooler.setBlowdownMakeupWaterUsageSchedule(incompatible));
  EXPECT_EQ("Unresolved Two Speed Blowdown", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  cooler.resetBlowdownMakeupWaterUsageSchedule();
  EXPECT_FALSE(cooler.blowdownMakeupWaterUsageSchedule());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_BlowdownScheduleSurvivesReloadReplacementAndRemoval) {
  const auto firstPath = uniqueTwoSpeedCoolerPath("epmodel-evaporative-fluid-cooler-two-first");
  const auto secondPath = uniqueTwoSpeedCoolerPath("epmodel-evaporative-fluid-cooler-two-second");
  const ScopedTwoSpeedCoolerFileRemoval removeFirst(firstPath);
  const ScopedTwoSpeedCoolerFileRemoval removeSecond(secondPath);

  Model model;
  EvaporativeFluidCoolerTwoSpeed cooler(model);
  ScheduleConstant original(model);
  ASSERT_TRUE(cooler.setName("Reloadable Two Speed Evaporative Fluid Cooler"));
  ASSERT_TRUE(original.setName("Original Two Speed Blowdown"));
  ASSERT_TRUE(original.setValue(0.0001));
  ASSERT_TRUE(cooler.setBlowdownMakeupWaterUsageSchedule(original));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCooler = loadedModel->getConcreteModelObjectByName<EvaporativeFluidCoolerTwoSpeed>("Reloadable Two Speed Evaporative Fluid Cooler");
  auto loadedOriginal = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Two Speed Blowdown");
  ASSERT_TRUE(loadedCooler);
  ASSERT_TRUE(loadedOriginal);
  ASSERT_TRUE(loadedCooler->blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(loadedOriginal->handle(), loadedCooler->blowdownMakeupWaterUsageSchedule()->handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement Two Speed Blowdown"));
  ASSERT_TRUE(replacement.setValue(0.0002));
  ASSERT_TRUE(loadedCooler->setBlowdownMakeupWaterUsageSchedule(replacement));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCooler = reloadedModel->getConcreteModelObjectByName<EvaporativeFluidCoolerTwoSpeed>("Reloadable Two Speed Evaporative Fluid Cooler");
  auto reloadedOriginal = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Two Speed Blowdown");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Two Speed Blowdown");
  ASSERT_TRUE(reloadedCooler);
  ASSERT_TRUE(reloadedOriginal);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_EQ(reloadedReplacement->handle(), reloadedCooler->blowdownMakeupWaterUsageSchedule()->handle());
  reloadedCooler->resetBlowdownMakeupWaterUsageSchedule();
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetCooler = resetModel->getConcreteModelObjectByName<EvaporativeFluidCoolerTwoSpeed>("Reloadable Two Speed Evaporative Fluid Cooler");
  auto resetOriginal = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Original Two Speed Blowdown");
  auto resetReplacement = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Two Speed Blowdown");
  ASSERT_TRUE(resetCooler);
  ASSERT_TRUE(resetOriginal);
  ASSERT_TRUE(resetReplacement);
  EXPECT_FALSE(resetCooler->blowdownMakeupWaterUsageSchedule());
  EXPECT_FALSE(resetCooler->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetOriginal->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacement->handle()));
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::performanceInputMethodValues().empty());
  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::evaporationLossModeValues().empty());
  EXPECT_FALSE(EvaporativeFluidCoolerTwoSpeed::blowdownCalculationModeValues().empty());

  EXPECT_TRUE(evap.setHighFanSpeedAirFlowRate(4.1));
  ASSERT_TRUE(evap.highFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(4.1, *evap.highFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.isHighFanSpeedAirFlowRateAutosized());
  evap.autosizeHighFanSpeedAirFlowRate();
  EXPECT_TRUE(evap.isHighFanSpeedAirFlowRateAutosized());

  EXPECT_TRUE(evap.setHighFanSpeedFanPower(1400.0));
  ASSERT_TRUE(evap.highFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(1400.0, *evap.highFanSpeedFanPower());
  evap.autosizeHighFanSpeedFanPower();
  EXPECT_TRUE(evap.isHighFanSpeedFanPowerAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedAirFlowRate(2.3));
  ASSERT_TRUE(evap.lowFanSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(2.3, *evap.lowFanSpeedAirFlowRate());
  evap.autosizeLowFanSpeedAirFlowRate();
  EXPECT_TRUE(evap.isLowFanSpeedAirFlowRateAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedAirFlowRateSizingFactor(0.55));
  EXPECT_DOUBLE_EQ(0.55, evap.lowFanSpeedAirFlowRateSizingFactor());

  EXPECT_TRUE(evap.setLowFanSpeedFanPower(600.0));
  ASSERT_TRUE(evap.lowFanSpeedFanPower());
  EXPECT_DOUBLE_EQ(600.0, *evap.lowFanSpeedFanPower());
  evap.autosizeLowFanSpeedFanPower();
  EXPECT_TRUE(evap.isLowFanSpeedFanPowerAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedFanPowerSizingFactor(0.52));
  EXPECT_DOUBLE_EQ(0.52, evap.lowFanSpeedFanPowerSizingFactor());

  EXPECT_TRUE(evap.setDesignSprayWaterFlowRate(0.004));
  EXPECT_DOUBLE_EQ(0.004, evap.designSprayWaterFlowRate());

  EXPECT_TRUE(evap.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_EQ("StandardDesignCapacity", evap.performanceInputMethod());

  EXPECT_TRUE(evap.setHeatRejectionCapacityandNominalCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_TRUE(evap.setHighSpeedStandardDesignCapacity(9500.0));
  ASSERT_TRUE(evap.highSpeedStandardDesignCapacity());
  EXPECT_DOUBLE_EQ(9500.0, *evap.highSpeedStandardDesignCapacity());
  evap.resetHighSpeedStandardDesignCapacity();
  EXPECT_FALSE(evap.highSpeedStandardDesignCapacity());

  EXPECT_TRUE(evap.setLowSpeedStandardDesignCapacity(4200.0));
  ASSERT_TRUE(evap.lowSpeedStandardDesignCapacity());
  EXPECT_DOUBLE_EQ(4200.0, *evap.lowSpeedStandardDesignCapacity());
  evap.resetLowSpeedStandardDesignCapacity();
  EXPECT_FALSE(evap.lowSpeedStandardDesignCapacity());
  evap.autosizeLowSpeedStandardDesignCapacity();
  EXPECT_TRUE(evap.isLowSpeedStandardDesignCapacityAutosized());

  EXPECT_TRUE(evap.setLowSpeedStandardCapacitySizingFactor(0.48));
  EXPECT_DOUBLE_EQ(0.48, evap.lowSpeedStandardCapacitySizingFactor());

  EXPECT_TRUE(evap.setHighFanSpeedUfactorTimesAreaValue(2800.0));
  ASSERT_TRUE(evap.highFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2800.0, *evap.highFanSpeedUfactorTimesAreaValue());
  evap.resetHighFanSpeedUfactorTimesAreaValue();
  EXPECT_FALSE(evap.highFanSpeedUfactorTimesAreaValue());
  evap.autosizeHighFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(evap.isHighFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedUfactorTimesAreaValue(1500.0));
  ASSERT_TRUE(evap.lowFanSpeedUfactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(1500.0, *evap.lowFanSpeedUfactorTimesAreaValue());
  evap.resetLowFanSpeedUfactorTimesAreaValue();
  EXPECT_FALSE(evap.lowFanSpeedUfactorTimesAreaValue());
  evap.autosizeLowFanSpeedUfactorTimesAreaValue();
  EXPECT_TRUE(evap.isLowFanSpeedUfactorTimesAreaValueAutosized());

  EXPECT_TRUE(evap.setLowFanSpeedUFactorTimesAreaSizingFactor(0.61));
  EXPECT_DOUBLE_EQ(0.61, evap.lowFanSpeedUFactorTimesAreaSizingFactor());

  EXPECT_TRUE(evap.setDesignWaterFlowRate(0.03));
  ASSERT_TRUE(evap.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.03, *evap.designWaterFlowRate());
  evap.resetDesignWaterFlowRate();
  EXPECT_FALSE(evap.designWaterFlowRate());
  evap.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_TRUE(evap.setHighSpeedUserSpecifiedDesignCapacity(13000.0));
  ASSERT_TRUE(evap.highSpeedUserSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(13000.0, *evap.highSpeedUserSpecifiedDesignCapacity());
  evap.resetHighSpeedUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.highSpeedUserSpecifiedDesignCapacity());

  EXPECT_TRUE(evap.setLowSpeedUserSpecifiedDesignCapacity(6800.0));
  ASSERT_TRUE(evap.lowSpeedUserSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(6800.0, *evap.lowSpeedUserSpecifiedDesignCapacity());
  evap.resetLowSpeedUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.lowSpeedUserSpecifiedDesignCapacity());
  evap.autosizeLowSpeedUserSpecifiedDesignCapacity();
  EXPECT_TRUE(evap.isLowSpeedUserSpecifiedDesignCapacityAutosized());

  EXPECT_TRUE(evap.setLowSpeedUserSpecifiedDesignCapacitySizingFactor(0.46));
  EXPECT_DOUBLE_EQ(0.46, evap.lowSpeedUserSpecifiedDesignCapacitySizingFactor());

  EXPECT_TRUE(evap.setDesignEnteringWaterTemperature(30.5));
  ASSERT_TRUE(evap.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(30.5, *evap.designEnteringWaterTemperature());
  evap.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_TRUE(evap.setDesignEnteringAirTemperature(33.4));
  EXPECT_DOUBLE_EQ(33.4, evap.designEnteringAirTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirWetbulbTemperature(23.7));
  EXPECT_DOUBLE_EQ(23.7, evap.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(evap.setHighSpeedSizingFactor(1.08));
  EXPECT_DOUBLE_EQ(1.08, evap.highSpeedSizingFactor());

  EXPECT_TRUE(evap.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", evap.evaporationLossMode());

  EXPECT_TRUE(evap.setEvaporationLossFactor(0.23));
  ASSERT_TRUE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.23, *evap.evaporationLossFactor());
  evap.resetEvaporationLossFactor();
  EXPECT_FALSE(evap.evaporationLossFactor());

  EXPECT_TRUE(evap.setDriftLossPercent(0.007));
  EXPECT_DOUBLE_EQ(0.007, evap.driftLossPercent());

  EXPECT_TRUE(evap.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_EQ("ScheduledRate", evap.blowdownCalculationMode());

  EXPECT_TRUE(evap.setBlowdownConcentrationRatio(4.2));
  EXPECT_DOUBLE_EQ(4.2, evap.blowdownConcentrationRatio());

  EXPECT_FALSE(evap.autosizedHighFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.autosizedHighFanSpeedFanPower());
  EXPECT_FALSE(evap.autosizedLowFanSpeedAirFlowRate());
  EXPECT_FALSE(evap.autosizedLowFanSpeedFanPower());
  EXPECT_FALSE(evap.autosizedLowSpeedStandardDesignCapacity());
  EXPECT_FALSE(evap.autosizedHighFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(evap.autosizedLowFanSpeedUfactorTimesAreaValue());
  EXPECT_FALSE(evap.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(evap.autosizedLowSpeedUserSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.autosizedDesignEnteringWaterTemperature());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerTwoSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  EvaporativeFluidCoolerTwoSpeed evap(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(evap.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());
  EXPECT_FALSE(evap.loop());
  EXPECT_FALSE(evap.inletModelObject());
  EXPECT_FALSE(evap.outletModelObject());

  auto splitterBranch = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(splitterBranch);
  auto demandBranchNode = splitterBranch->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);
  EXPECT_FALSE(evap.addToNode(*demandBranchNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());
  EXPECT_FALSE(evap.loop());
  EXPECT_FALSE(evap.inletModelObject());
  EXPECT_FALSE(evap.outletModelObject());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(evap.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(evap.loop());
  EXPECT_EQ(plantLoop.handle(), evap.loop()->handle());
  ASSERT_TRUE(evap.inletModelObject());
  ASSERT_TRUE(evap.outletModelObject());

  auto inletNode = evap.getModelObjectTarget<Node>(openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterInletNodeName);
  auto outletNode = evap.getModelObjectTarget<Node>(openstudio::EvaporativeFluidCooler_TwoSpeedFields::WaterOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_EQ(evap.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(evap.outletModelObject()->handle(), outletNode->handle());

  EvaporativeFluidCoolerTwoSpeed secondEvap(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondEvap.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondEvap.loop());
  EXPECT_FALSE(secondEvap.inletModelObject());
  EXPECT_FALSE(secondEvap.outletModelObject());
}
