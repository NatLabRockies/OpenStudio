/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerSingleSpeed.hpp"
#include "../StraightComponent/EvaporativeFluidCoolerSingleSpeed_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/EvaporativeFluidCooler_SingleSpeed_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedSingleSpeedCoolerFileRemoval
{
 public:
  explicit ScopedSingleSpeedCoolerFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedSingleSpeedCoolerFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueSingleSpeedCoolerPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_DefaultConstructor) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_EQ(EvaporativeFluidCoolerSingleSpeed::iddObjectType(), evap.iddObject().type());
  EXPECT_FALSE(evap.nameString().empty());

  EXPECT_FALSE(evap.designAirFlowRate());
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.fanPoweratDesignAirFlowRate());
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());

  EXPECT_DOUBLE_EQ(0.03, evap.designSprayWaterFlowRate());
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());
  EXPECT_DOUBLE_EQ(1.25, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_FALSE(evap.standardDesignCapacity());
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_TRUE(evap.isUfactorTimesAreaValueatDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.designWaterFlowRate());
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());

  EXPECT_FALSE(evap.userSpecifiedDesignCapacity());
  EXPECT_FALSE(evap.designEnteringWaterTemperature());
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());

  EXPECT_DOUBLE_EQ(35.0, evap.designEnteringAirTemperature());
  EXPECT_DOUBLE_EQ(25.6, evap.designEnteringAirWetbulbTemperature());
  EXPECT_EQ("FanCycling", evap.capacityControl());
  EXPECT_DOUBLE_EQ(1.0, evap.sizingFactor());
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());
  EXPECT_FALSE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.008, evap.driftLossPercent());
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
  EXPECT_DOUBLE_EQ(3.0, evap.blowdownConcentrationRatio());
  EXPECT_FALSE(evap.blowdownMakeupWaterUsageSchedule());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_BlowdownScheduleValidationAndReset) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed cooler(model);
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

  constexpr auto field = openstudio::EvaporativeFluidCooler_SingleSpeedFields::BlowdownMakeupWaterUsageScheduleName;
  auto workspaceImpl = cooler.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Single Speed Blowdown", false));
  EXPECT_FALSE(cooler.setBlowdownMakeupWaterUsageSchedule(incompatible));
  EXPECT_EQ("Unresolved Single Speed Blowdown", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  cooler.resetBlowdownMakeupWaterUsageSchedule();
  EXPECT_FALSE(cooler.blowdownMakeupWaterUsageSchedule());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_BlowdownScheduleSurvivesReloadReplacementAndRemoval) {
  const auto firstPath = uniqueSingleSpeedCoolerPath("epmodel-evaporative-fluid-cooler-single-first");
  const auto secondPath = uniqueSingleSpeedCoolerPath("epmodel-evaporative-fluid-cooler-single-second");
  const ScopedSingleSpeedCoolerFileRemoval removeFirst(firstPath);
  const ScopedSingleSpeedCoolerFileRemoval removeSecond(secondPath);

  Model model;
  EvaporativeFluidCoolerSingleSpeed cooler(model);
  ScheduleConstant original(model);
  ASSERT_TRUE(cooler.setName("Reloadable Single Speed Evaporative Fluid Cooler"));
  ASSERT_TRUE(original.setName("Original Single Speed Blowdown"));
  ASSERT_TRUE(original.setValue(0.0001));
  ASSERT_TRUE(cooler.setBlowdownMakeupWaterUsageSchedule(original));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCooler =
    loadedModel->getConcreteModelObjectByName<EvaporativeFluidCoolerSingleSpeed>("Reloadable Single Speed Evaporative Fluid Cooler");
  auto loadedOriginal = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Single Speed Blowdown");
  ASSERT_TRUE(loadedCooler);
  ASSERT_TRUE(loadedOriginal);
  ASSERT_TRUE(loadedCooler->blowdownMakeupWaterUsageSchedule());
  EXPECT_EQ(loadedOriginal->handle(), loadedCooler->blowdownMakeupWaterUsageSchedule()->handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement Single Speed Blowdown"));
  ASSERT_TRUE(replacement.setValue(0.0002));
  ASSERT_TRUE(loadedCooler->setBlowdownMakeupWaterUsageSchedule(replacement));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCooler =
    reloadedModel->getConcreteModelObjectByName<EvaporativeFluidCoolerSingleSpeed>("Reloadable Single Speed Evaporative Fluid Cooler");
  auto reloadedOriginal = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Single Speed Blowdown");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Single Speed Blowdown");
  ASSERT_TRUE(reloadedCooler);
  ASSERT_TRUE(reloadedOriginal);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_EQ(reloadedReplacement->handle(), reloadedCooler->blowdownMakeupWaterUsageSchedule()->handle());
  reloadedCooler->resetBlowdownMakeupWaterUsageSchedule();
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetCooler = resetModel->getConcreteModelObjectByName<EvaporativeFluidCoolerSingleSpeed>("Reloadable Single Speed Evaporative Fluid Cooler");
  auto resetOriginal = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Original Single Speed Blowdown");
  auto resetReplacement = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Single Speed Blowdown");
  ASSERT_TRUE(resetCooler);
  ASSERT_TRUE(resetOriginal);
  ASSERT_TRUE(resetReplacement);
  EXPECT_FALSE(resetCooler->blowdownMakeupWaterUsageSchedule());
  EXPECT_FALSE(resetCooler->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetOriginal->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacement->handle()));
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_TRUE(evap.setDesignAirFlowRate(1.35));
  ASSERT_TRUE(evap.designAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, *evap.designAirFlowRate());
  EXPECT_FALSE(evap.isDesignAirFlowRateAutosized());
  evap.autosizeDesignAirFlowRate();
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.designAirFlowRate());

  EXPECT_TRUE(evap.setFanPoweratDesignAirFlowRate(210.0));
  ASSERT_TRUE(evap.fanPoweratDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(210.0, *evap.fanPoweratDesignAirFlowRate());
  evap.autosizeFanPoweratDesignAirFlowRate();
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.fanPoweratDesignAirFlowRate());

  EXPECT_TRUE(evap.setDesignSprayWaterFlowRate(0.06));
  EXPECT_DOUBLE_EQ(0.06, evap.designSprayWaterFlowRate());

  EXPECT_TRUE(evap.setPerformanceInputMethod("StandardDesignCapacity"));
  EXPECT_EQ("StandardDesignCapacity", evap.performanceInputMethod());

  EXPECT_TRUE(evap.setHeatRejectionCapacityandNominalCapacitySizingRatio(1.2));
  EXPECT_DOUBLE_EQ(1.2, evap.heatRejectionCapacityandNominalCapacitySizingRatio());

  EXPECT_TRUE(evap.setStandardDesignCapacity(9000.0));
  ASSERT_TRUE(evap.standardDesignCapacity());
  EXPECT_DOUBLE_EQ(9000.0, *evap.standardDesignCapacity());
  evap.resetStandardDesignCapacity();
  EXPECT_FALSE(evap.standardDesignCapacity());

  EXPECT_TRUE(evap.setUfactorTimesAreaValueatDesignAirFlowRate(1800.0));
  ASSERT_TRUE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_DOUBLE_EQ(1800.0, *evap.ufactorTimesAreaValueatDesignAirFlowRate());
  evap.resetUfactorTimesAreaValueatDesignAirFlowRate();
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());
  evap.autosizeUfactorTimesAreaValueatDesignAirFlowRate();
  EXPECT_TRUE(evap.isUfactorTimesAreaValueatDesignAirFlowRateAutosized());
  EXPECT_FALSE(evap.ufactorTimesAreaValueatDesignAirFlowRate());

  EXPECT_TRUE(evap.setDesignWaterFlowRate(0.04));
  ASSERT_TRUE(evap.designWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.04, *evap.designWaterFlowRate());
  evap.resetDesignWaterFlowRate();
  EXPECT_FALSE(evap.designWaterFlowRate());
  evap.autosizeDesignWaterFlowRate();
  EXPECT_TRUE(evap.isDesignWaterFlowRateAutosized());
  EXPECT_FALSE(evap.designWaterFlowRate());

  EXPECT_TRUE(evap.setUserSpecifiedDesignCapacity(10000.0));
  ASSERT_TRUE(evap.userSpecifiedDesignCapacity());
  EXPECT_DOUBLE_EQ(10000.0, *evap.userSpecifiedDesignCapacity());
  evap.resetUserSpecifiedDesignCapacity();
  EXPECT_FALSE(evap.userSpecifiedDesignCapacity());

  EXPECT_TRUE(evap.setDesignEnteringWaterTemperature(30.2));
  ASSERT_TRUE(evap.designEnteringWaterTemperature());
  EXPECT_DOUBLE_EQ(30.2, *evap.designEnteringWaterTemperature());
  EXPECT_FALSE(evap.isDesignEnteringWaterTemperatureAutosized());
  evap.autosizeDesignEnteringWaterTemperature();
  EXPECT_TRUE(evap.isDesignEnteringWaterTemperatureAutosized());
  EXPECT_FALSE(evap.designEnteringWaterTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirTemperature(33.1));
  EXPECT_DOUBLE_EQ(33.1, evap.designEnteringAirTemperature());

  EXPECT_TRUE(evap.setDesignEnteringAirWetbulbTemperature(22.4));
  EXPECT_DOUBLE_EQ(22.4, evap.designEnteringAirWetbulbTemperature());

  EXPECT_TRUE(evap.setCapacityControl("FluidBypass"));
  EXPECT_EQ("FluidBypass", evap.capacityControl());
  evap.resetCapacityControl();
  EXPECT_TRUE(evap.isCapacityControlDefaulted());

  EXPECT_TRUE(evap.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, evap.sizingFactor());
  evap.resetSizingFactor();
  EXPECT_TRUE(evap.isSizingFactorDefaulted());

  EXPECT_TRUE(evap.setEvaporationLossMode("LossFactor"));
  EXPECT_EQ("LossFactor", evap.evaporationLossMode());
  evap.resetEvaporationLossMode();
  EXPECT_TRUE(evap.isEvaporationLossModeDefaulted());

  EXPECT_TRUE(evap.setEvaporationLossFactor(0.25));
  ASSERT_TRUE(evap.evaporationLossFactor());
  EXPECT_DOUBLE_EQ(0.25, *evap.evaporationLossFactor());
  evap.resetEvaporationLossFactor();
  EXPECT_FALSE(evap.evaporationLossFactor());

  EXPECT_TRUE(evap.setDriftLossPercent(0.007));
  EXPECT_DOUBLE_EQ(0.007, evap.driftLossPercent());
  evap.resetDriftLossPercent();
  EXPECT_TRUE(evap.isDriftLossPercentDefaulted());

  EXPECT_TRUE(evap.setBlowdownCalculationMode("ScheduledRate"));
  EXPECT_EQ("ScheduledRate", evap.blowdownCalculationMode());
  evap.resetBlowdownCalculationMode();
  EXPECT_TRUE(evap.isBlowdownCalculationModeDefaulted());

  EXPECT_TRUE(evap.setBlowdownConcentrationRatio(4.1));
  EXPECT_DOUBLE_EQ(4.1, evap.blowdownConcentrationRatio());
  evap.resetBlowdownConcentrationRatio();
  EXPECT_TRUE(evap.isBlowdownConcentrationRatioDefaulted());

  EXPECT_FALSE(evap.autosizedDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedFanPoweratDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedUfactorTimesAreaValueatDesignAirFlowRate());
  EXPECT_FALSE(evap.autosizedDesignWaterFlowRate());
  EXPECT_FALSE(evap.autosizedDesignEnteringWaterTemperature());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_AddToNode_PlantSupplyOnly) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
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
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(evap.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());
  ASSERT_TRUE(evap.loop());
  EXPECT_EQ(plantLoop.handle(), evap.loop()->handle());
  ASSERT_TRUE(evap.inletModelObject());
  ASSERT_TRUE(evap.outletModelObject());

  EvaporativeFluidCoolerSingleSpeed secondEvap(model);
  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(secondEvap.addToNode(plantDemandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
  EXPECT_FALSE(secondEvap.loop());
  EXPECT_FALSE(secondEvap.inletModelObject());
  EXPECT_FALSE(secondEvap.outletModelObject());
}

TEST_F(EPModelFixture, EvaporativeFluidCoolerSingleSpeed_InvalidInputsRejected) {
  Model model;
  EvaporativeFluidCoolerSingleSpeed evap(model);

  EXPECT_FALSE(evap.setDesignAirFlowRate(0.0));
  EXPECT_FALSE(evap.setDesignAirFlowRate(-1.0));
  EXPECT_TRUE(evap.isDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.setFanPoweratDesignAirFlowRate(0.0));
  EXPECT_FALSE(evap.setFanPoweratDesignAirFlowRate(-1.0));
  EXPECT_TRUE(evap.isFanPoweratDesignAirFlowRateAutosized());

  EXPECT_FALSE(evap.setDesignSprayWaterFlowRate(0.0));
  EXPECT_FALSE(evap.setDesignSprayWaterFlowRate(-1.0));
  EXPECT_DOUBLE_EQ(0.03, evap.designSprayWaterFlowRate());

  EXPECT_FALSE(evap.setPerformanceInputMethod("Not Valid Entry"));
  EXPECT_EQ("UFactorTimesAreaAndDesignWaterFlowRate", evap.performanceInputMethod());

  EXPECT_FALSE(evap.setCapacityControl("Not Valid Entry"));
  EXPECT_EQ("FanCycling", evap.capacityControl());

  EXPECT_FALSE(evap.setEvaporationLossMode("Not Valid Entry"));
  EXPECT_EQ("SaturatedExit", evap.evaporationLossMode());

  EXPECT_FALSE(evap.setBlowdownCalculationMode("Not Valid Entry"));
  EXPECT_EQ("ConcentrationRatio", evap.blowdownCalculationMode());
}
