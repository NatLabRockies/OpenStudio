/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/SwimmingPoolIndoor.hpp"
#include "../StraightComponent/SwimmingPoolIndoor_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/SwimmingPool_Indoor_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedSwimmingPoolFileRemoval
{
 public:
  explicit ScopedSwimmingPoolFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedSwimmingPoolFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueSwimmingPoolPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, SwimmingPoolIndoor_DefaultConstructor) {
  Model model;
  SwimmingPoolIndoor pool(model);
  EXPECT_EQ(SwimmingPoolIndoor::iddObjectType(), pool.iddObject().type());
  EXPECT_FALSE(pool.nameString().empty());
  EXPECT_DOUBLE_EQ(2.0, pool.averageDepth());
  EXPECT_DOUBLE_EQ(0.1, pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.0, pool.poolMiscellaneousEquipmentPower());
  EXPECT_DOUBLE_EQ(15.0, pool.maximumNumberofPeople());

  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), pool.activityFactorSchedule().handle());
  EXPECT_EQ(pool.activityFactorSchedule().handle(), pool.peopleSchedule().handle());

  auto activityAndPeople = pool.activityFactorSchedule().optionalCast<ScheduleConstant>();
  auto cover = pool.coverSchedule().optionalCast<ScheduleConstant>();
  auto makeup = pool.makeupWaterSupplySchedule().optionalCast<ScheduleConstant>();
  auto heatGain = pool.peopleHeatGainSchedule().optionalCast<ScheduleConstant>();
  auto setpoint = pool.setpointTemperatureSchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(activityAndPeople);
  ASSERT_TRUE(cover);
  ASSERT_TRUE(makeup);
  ASSERT_TRUE(heatGain);
  ASSERT_TRUE(setpoint);
  EXPECT_DOUBLE_EQ(0.0, cover->value());
  EXPECT_DOUBLE_EQ(16.67, makeup->value());
  EXPECT_DOUBLE_EQ(300.0, heatGain->value());
  EXPECT_DOUBLE_EQ(27.0, setpoint->value());
  EXPECT_EQ("Pool MakeUp Water Temperature Schedule", makeup->nameString());
  EXPECT_EQ("Pool People Heat Gain Schedule", heatGain->nameString());
  EXPECT_EQ("Pool Setpoint Temperature Schedule", setpoint->nameString());

  ASSERT_TRUE(activityAndPeople->scheduleTypeLimits());
  EXPECT_EQ("Discrete", activityAndPeople->scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", activityAndPeople->scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, activityAndPeople->scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, activityAndPeople->scheduleTypeLimits()->upperLimitValue().value_or(-1.0));
  ASSERT_TRUE(cover->scheduleTypeLimits());
  EXPECT_EQ("Continuous", cover->scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(cover->scheduleTypeLimits()->isUnitTypeDefaulted());
  EXPECT_DOUBLE_EQ(0.0, cover->scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, cover->scheduleTypeLimits()->upperLimitValue().value_or(-1.0));
  ASSERT_TRUE(makeup->scheduleTypeLimits());
  EXPECT_EQ("Continuous", makeup->scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Temperature", makeup->scheduleTypeLimits()->unitType());
  EXPECT_FALSE(makeup->scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(makeup->scheduleTypeLimits()->upperLimitValue());
  ASSERT_TRUE(heatGain->scheduleTypeLimits());
  EXPECT_EQ("Continuous", heatGain->scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("ActivityLevel", heatGain->scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, heatGain->scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_FALSE(heatGain->scheduleTypeLimits()->upperLimitValue());
  ASSERT_TRUE(setpoint->scheduleTypeLimits());
  EXPECT_EQ("Continuous", setpoint->scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Temperature", setpoint->scheduleTypeLimits()->unitType());
  EXPECT_FALSE(setpoint->scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(setpoint->scheduleTypeLimits()->upperLimitValue());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_ScheduleRelationshipsValidateAndPreserveCurrentTargets) {
  Model model;
  SwimmingPoolIndoor pool(model);

  ScheduleConstant activityFactor(model);
  ASSERT_TRUE(activityFactor.setValue(0.5));
  ASSERT_TRUE(pool.setActivityFactorSchedule(activityFactor));
  ASSERT_TRUE(activityFactor.scheduleTypeLimits());
  EXPECT_EQ("Continuous", activityFactor.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(activityFactor.scheduleTypeLimits()->isUnitTypeDefaulted());
  EXPECT_DOUBLE_EQ(0.0, activityFactor.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_FALSE(activityFactor.scheduleTypeLimits()->upperLimitValue());

  ScheduleConstant fraction(model);
  ASSERT_TRUE(fraction.setValue(0.5));
  ASSERT_TRUE(pool.setCoverSchedule(fraction));
  ASSERT_TRUE(pool.setPeopleSchedule(fraction));
  ASSERT_TRUE(fraction.scheduleTypeLimits());
  EXPECT_EQ("Continuous", fraction.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(fraction.scheduleTypeLimits()->isUnitTypeDefaulted());
  EXPECT_DOUBLE_EQ(0.0, fraction.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, fraction.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant temperature(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperature.setScheduleTypeLimits(temperatureLimits));
  ASSERT_TRUE(pool.setMakeupWaterSupplySchedule(temperature));
  ASSERT_TRUE(pool.setSetpointTemperatureSchedule(temperature));

  ScheduleConstant activity(model);
  ScheduleTypeLimits activityLimits(model);
  ASSERT_TRUE(activityLimits.setNumericType("Continuous"));
  ASSERT_TRUE(activityLimits.setUnitType("ActivityLevel"));
  ASSERT_TRUE(activityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(activity.setScheduleTypeLimits(activityLimits));
  ASSERT_TRUE(pool.setPeopleHeatGainSchedule(activity));

  const std::array<openstudio::Handle, 6> currentHandles{pool.activityFactorSchedule().handle(), pool.makeupWaterSupplySchedule().handle(),
                                                         pool.coverSchedule().handle(),          pool.setpointTemperatureSchedule().handle(),
                                                         pool.peopleSchedule().handle(),         pool.peopleHeatGainSchedule().handle()};

  EXPECT_FALSE(pool.setActivityFactorSchedule(temperature));
  EXPECT_FALSE(pool.setMakeupWaterSupplySchedule(fraction));
  EXPECT_FALSE(pool.setCoverSchedule(temperature));
  EXPECT_FALSE(pool.setSetpointTemperatureSchedule(fraction));
  EXPECT_FALSE(pool.setPeopleSchedule(temperature));
  EXPECT_FALSE(pool.setPeopleHeatGainSchedule(temperature));

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(pool.setActivityFactorSchedule(foreign));
  EXPECT_FALSE(pool.setMakeupWaterSupplySchedule(foreign));
  EXPECT_FALSE(pool.setCoverSchedule(foreign));
  EXPECT_FALSE(pool.setSetpointTemperatureSchedule(foreign));
  EXPECT_FALSE(pool.setPeopleSchedule(foreign));
  EXPECT_FALSE(pool.setPeopleHeatGainSchedule(foreign));

  EXPECT_EQ(currentHandles[0], pool.activityFactorSchedule().handle());
  EXPECT_EQ(currentHandles[1], pool.makeupWaterSupplySchedule().handle());
  EXPECT_EQ(currentHandles[2], pool.coverSchedule().handle());
  EXPECT_EQ(currentHandles[3], pool.setpointTemperatureSchedule().handle());
  EXPECT_EQ(currentHandles[4], pool.peopleSchedule().handle());
  EXPECT_EQ(currentHandles[5], pool.peopleHeatGainSchedule().handle());

  auto alwaysOn = model.alwaysOnDiscreteSchedule();
  EXPECT_TRUE(pool.setCoverSchedule(alwaysOn));
  EXPECT_EQ(alwaysOn.handle(), pool.coverSchedule().handle());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_CanonicalizesScheduleRelationshipsWithoutDestroyingRawEvidence) {
  Model model;
  ScheduleConstant recoverable(model);
  ScheduleConstant duplicateFirst(model);
  ScheduleConstant duplicateSecond(model);
  ScheduleConstant incompatible(model);
  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(recoverable.setName("Recoverable Pool Schedule"));
  ASSERT_TRUE(duplicateFirst.setName("Ambiguous Pool Schedule"));
  ASSERT_TRUE(incompatible.setName("Incompatible Pool Schedule"));
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(incompatibleLimits));
  auto duplicateSecondImpl = duplicateSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateSecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(duplicateSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Pool Schedule", false));

  SwimmingPoolIndoor blank(model);
  SwimmingPoolIndoor byName(model);
  SwimmingPoolIndoor missing(model);
  SwimmingPoolIndoor ambiguous(model);
  SwimmingPoolIndoor managedAmbiguous(model);
  SwimmingPoolIndoor managedIncompatible(model);
  SwimmingPoolIndoor rawIncompatible(model);
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto byNameImpl = byName.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto missingImpl = missing.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedAmbiguousImpl = managedAmbiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedIncompatibleImpl = managedIncompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto rawIncompatibleImpl = rawIncompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(byNameImpl);
  ASSERT_TRUE(missingImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(managedAmbiguousImpl);
  ASSERT_TRUE(managedIncompatibleImpl);
  ASSERT_TRUE(rawIncompatibleImpl);

  constexpr std::array<unsigned, 6> scheduleFields{
    openstudio::SwimmingPool_IndoorFields::ActivityFactorScheduleName,
    openstudio::SwimmingPool_IndoorFields::MakeupWaterSupplyScheduleName,
    openstudio::SwimmingPool_IndoorFields::CoverScheduleName,
    openstudio::SwimmingPool_IndoorFields::SetpointTemperatureSchedule,
    openstudio::SwimmingPool_IndoorFields::PeopleSchedule,
    openstudio::SwimmingPool_IndoorFields::PeopleHeatGainSchedule,
  };

  // Public APIs keep required schedules valid. These low-level writes model blank or malformed imported relationship storage.
  for (const auto field : scheduleFields) {
    ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  }
  const auto byNameField = openstudio::SwimmingPool_IndoorFields::ActivityFactorScheduleName;
  ASSERT_TRUE(byNameImpl->setPointer(byNameField, openstudio::Handle(), false));
  ASSERT_TRUE(byNameImpl->openstudio::detail::IdfObject_Impl::setString(byNameField, recoverable.nameString(), false));
  const auto missingField = openstudio::SwimmingPool_IndoorFields::CoverScheduleName;
  ASSERT_TRUE(missingImpl->setPointer(missingField, openstudio::Handle(), false));
  ASSERT_TRUE(missingImpl->openstudio::detail::IdfObject_Impl::setString(missingField, "Missing Pool Schedule", false));
  const auto ambiguousField = openstudio::SwimmingPool_IndoorFields::PeopleHeatGainSchedule;
  ASSERT_TRUE(ambiguousImpl->setPointer(ambiguousField, openstudio::Handle(), false));
  ASSERT_TRUE(ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(ambiguousField, "Ambiguous Pool Schedule", false));
  ASSERT_TRUE(managedAmbiguousImpl->setPointer(byNameField, duplicateFirst.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(byNameField, incompatible.handle(), false));
  ASSERT_TRUE(rawIncompatibleImpl->setPointer(byNameField, openstudio::Handle(), false));
  ASSERT_TRUE(rawIncompatibleImpl->openstudio::detail::IdfObject_Impl::setString(byNameField, incompatible.nameString(), false));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.warningCount, 5u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.activityFactorSchedule().handle());
  EXPECT_EQ(blank.activityFactorSchedule().handle(), blank.peopleSchedule().handle());
  EXPECT_DOUBLE_EQ(0.0, blank.coverSchedule().cast<ScheduleConstant>().value());
  EXPECT_DOUBLE_EQ(16.67, blank.makeupWaterSupplySchedule().cast<ScheduleConstant>().value());
  EXPECT_DOUBLE_EQ(27.0, blank.setpointTemperatureSchedule().cast<ScheduleConstant>().value());
  EXPECT_DOUBLE_EQ(300.0, blank.peopleHeatGainSchedule().cast<ScheduleConstant>().value());
  EXPECT_EQ(recoverable.handle(), byName.activityFactorSchedule().handle());
  ASSERT_TRUE(recoverable.scheduleTypeLimits());
  EXPECT_EQ("Continuous", recoverable.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_DOUBLE_EQ(0.0, recoverable.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_FALSE(recoverable.scheduleTypeLimits()->upperLimitValue());
  EXPECT_FALSE(missing.getModelObjectTarget<Schedule>(missingField));
  EXPECT_FALSE(ambiguous.getModelObjectTarget<Schedule>(ambiguousField));
  ASSERT_TRUE(managedAmbiguous.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ(duplicateFirst.handle(), managedAmbiguous.getModelObjectTarget<Schedule>(byNameField)->handle());
  EXPECT_FALSE(duplicateFirst.scheduleTypeLimits());
  ASSERT_TRUE(managedIncompatible.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ(incompatible.handle(), managedIncompatible.getModelObjectTarget<Schedule>(byNameField)->handle());
  EXPECT_FALSE(rawIncompatible.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ("Missing Pool Schedule", missingImpl->openstudio::detail::IdfObject_Impl::getString(missingField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Pool Schedule", ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(ambiguousField, false, true).value_or(""));
  EXPECT_EQ("Incompatible Pool Schedule", rawIncompatibleImpl->openstudio::detail::IdfObject_Impl::getString(byNameField, false, true).value_or(""));

  const auto scheduleCount = model.getConcreteModelObjects<ScheduleConstant>().size();
  const auto blankHandles = std::array<openstudio::Handle, 6>{blank.activityFactorSchedule().handle(), blank.makeupWaterSupplySchedule().handle(),
                                                              blank.coverSchedule().handle(),          blank.setpointTemperatureSchedule().handle(),
                                                              blank.peopleSchedule().handle(),         blank.peopleHeatGainSchedule().handle()};
  const auto secondReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(scheduleCount, model.getConcreteModelObjects<ScheduleConstant>().size());
  EXPECT_EQ(blankHandles[0], blank.activityFactorSchedule().handle());
  EXPECT_EQ(blankHandles[1], blank.makeupWaterSupplySchedule().handle());
  EXPECT_EQ(blankHandles[2], blank.coverSchedule().handle());
  EXPECT_EQ(blankHandles[3], blank.setpointTemperatureSchedule().handle());
  EXPECT_EQ(blankHandles[4], blank.peopleSchedule().handle());
  EXPECT_EQ(blankHandles[5], blank.peopleHeatGainSchedule().handle());
  EXPECT_EQ("Missing Pool Schedule", missingImpl->openstudio::detail::IdfObject_Impl::getString(missingField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Pool Schedule", ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(ambiguousField, false, true).value_or(""));
  ASSERT_TRUE(managedAmbiguous.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ(duplicateFirst.handle(), managedAmbiguous.getModelObjectTarget<Schedule>(byNameField)->handle());
  EXPECT_FALSE(duplicateFirst.scheduleTypeLimits());
  ASSERT_TRUE(managedIncompatible.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ(incompatible.handle(), managedIncompatible.getModelObjectTarget<Schedule>(byNameField)->handle());
  EXPECT_FALSE(rawIncompatible.getModelObjectTarget<Schedule>(byNameField));
  EXPECT_EQ("Incompatible Pool Schedule", rawIncompatibleImpl->openstudio::detail::IdfObject_Impl::getString(byNameField, false, true).value_or(""));
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_ScalarAccessors_RoundTrip) {
  Model model;
  SwimmingPoolIndoor pool(model);

  EXPECT_TRUE(pool.setAverageDepth(1.75));
  EXPECT_DOUBLE_EQ(1.75, pool.averageDepth());

  EXPECT_TRUE(pool.setCoverEvaporationFactor(0.3));
  EXPECT_DOUBLE_EQ(0.3, pool.coverEvaporationFactor());
  EXPECT_FALSE(pool.isCoverEvaporationFactorDefaulted());
  pool.resetCoverEvaporationFactor();
  EXPECT_TRUE(pool.isCoverEvaporationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverConvectionFactor(0.4));
  EXPECT_DOUBLE_EQ(0.4, pool.coverConvectionFactor());
  EXPECT_FALSE(pool.isCoverConvectionFactorDefaulted());
  pool.resetCoverConvectionFactor();
  EXPECT_TRUE(pool.isCoverConvectionFactorDefaulted());

  EXPECT_TRUE(pool.setCoverShortWavelengthRadiationFactor(0.1));
  EXPECT_DOUBLE_EQ(0.1, pool.coverShortWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverShortWavelengthRadiationFactorDefaulted());
  pool.resetCoverShortWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverShortWavelengthRadiationFactorDefaulted());

  EXPECT_TRUE(pool.setCoverLongWavelengthRadiationFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, pool.coverLongWavelengthRadiationFactor());
  EXPECT_FALSE(pool.isCoverLongWavelengthRadiationFactorDefaulted());
  pool.resetCoverLongWavelengthRadiationFactor();
  EXPECT_TRUE(pool.isCoverLongWavelengthRadiationFactorDefaulted());

  EXPECT_TRUE(pool.setPoolHeatingSystemMaximumWaterFlowRate(0.12));
  EXPECT_DOUBLE_EQ(0.12, pool.poolHeatingSystemMaximumWaterFlowRate());
  EXPECT_FALSE(pool.setPoolHeatingSystemMaximumWaterFlowRate(-10.0));
  EXPECT_DOUBLE_EQ(0.12, pool.poolHeatingSystemMaximumWaterFlowRate());

  EXPECT_TRUE(pool.setPoolMiscellaneousEquipmentPower(123.0));
  EXPECT_DOUBLE_EQ(123.0, pool.poolMiscellaneousEquipmentPower());
  EXPECT_FALSE(pool.setPoolMiscellaneousEquipmentPower(-10.0));
  EXPECT_DOUBLE_EQ(123.0, pool.poolMiscellaneousEquipmentPower());

  EXPECT_TRUE(pool.setMaximumNumberofPeople(25.0));
  EXPECT_DOUBLE_EQ(25.0, pool.maximumNumberofPeople());
  EXPECT_FALSE(pool.setMaximumNumberofPeople(-10.0));
  EXPECT_DOUBLE_EQ(25.0, pool.maximumNumberofPeople());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_AddToNode_PlantDemandOnlyAndDisconnect) {
  Model model;
  SwimmingPoolIndoor pool(model);

  Node orphanNode(model);
  EXPECT_FALSE(pool.addToNode(orphanNode));
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pool.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  auto airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pool.addToNode(airDemandNode));
  EXPECT_EQ(5u, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  auto plantSupplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(pool.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(5u, plantLoop.supplyComponents().size());
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());

  auto plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pool.addToNode(plantDemandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  ASSERT_TRUE(pool.plantLoop());
  EXPECT_EQ(plantLoop.handle(), pool.plantLoop()->handle());
  ASSERT_TRUE(pool.inletModelObject());
  ASSERT_TRUE(pool.outletModelObject());
  ASSERT_TRUE(pool.poolWaterInletNode());
  ASSERT_TRUE(pool.poolWaterOutletNode());
  EXPECT_EQ(pool.inletModelObject()->handle(), pool.poolWaterInletNode()->handle());
  EXPECT_EQ(pool.outletModelObject()->handle(), pool.poolWaterOutletNode()->handle());

  SwimmingPoolIndoor secondPool(model);
  EXPECT_FALSE(secondPool.poolWaterInletNode());
  EXPECT_FALSE(secondPool.poolWaterOutletNode());
  EXPECT_TRUE(secondPool.addToNode(plantDemandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
  ASSERT_TRUE(secondPool.plantLoop());
  EXPECT_EQ(plantLoop.handle(), secondPool.plantLoop()->handle());

  PlantLoop secondPlantLoop(model);
  auto secondDemandInletNode = secondPlantLoop.demandInletNode();
  EXPECT_TRUE(pool.addToNode(secondDemandInletNode));
  ASSERT_TRUE(pool.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), pool.plantLoop()->handle());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(7u, secondPlantLoop.demandComponents().size());
  ASSERT_TRUE(pool.poolWaterInletNode());
  ASSERT_TRUE(pool.poolWaterOutletNode());

  pool.disconnect();
  EXPECT_FALSE(pool.loop());
  EXPECT_FALSE(pool.inletModelObject());
  EXPECT_FALSE(pool.outletModelObject());
  EXPECT_FALSE(pool.poolWaterInletNode());
  EXPECT_FALSE(pool.poolWaterOutletNode());
  EXPECT_EQ(5u, secondPlantLoop.demandComponents().size());

  secondPool.disconnect();
  EXPECT_FALSE(secondPool.loop());
  EXPECT_FALSE(secondPool.inletModelObject());
  EXPECT_FALSE(secondPool.outletModelObject());
  EXPECT_FALSE(secondPool.poolWaterInletNode());
  EXPECT_FALSE(secondPool.poolWaterOutletNode());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, SwimmingPoolIndoor_SchedulesSurviveReloadReplacementDisconnectAndRemoval) {
  const auto firstPath = uniqueSwimmingPoolPath("epmodel-swimming-pool-schedules-first");
  const auto secondPath = uniqueSwimmingPoolPath("epmodel-swimming-pool-schedules-second");
  const ScopedSwimmingPoolFileRemoval removeFirst(firstPath);
  const ScopedSwimmingPoolFileRemoval removeSecond(secondPath);

  Model model;
  PlantLoop plantLoop(model);
  SwimmingPoolIndoor pool(model);
  ASSERT_TRUE(plantLoop.setName("Pool Schedule Plant Loop"));
  ASSERT_TRUE(pool.setName("Reloadable Swimming Pool"));

  ScheduleConstant activity(model);
  ScheduleConstant makeup(model);
  ScheduleConstant cover(model);
  ScheduleConstant setpoint(model);
  ScheduleConstant people(model);
  ScheduleConstant heatGain(model);
  ASSERT_TRUE(activity.setName("Original Pool Activity"));
  ASSERT_TRUE(makeup.setName("Original Pool Makeup"));
  ASSERT_TRUE(cover.setName("Original Pool Cover"));
  ASSERT_TRUE(setpoint.setName("Original Pool Setpoint"));
  ASSERT_TRUE(people.setName("Original Pool People"));
  ASSERT_TRUE(heatGain.setName("Original Pool Heat Gain"));
  ASSERT_TRUE(activity.setValue(0.8));
  ASSERT_TRUE(makeup.setValue(18.0));
  ASSERT_TRUE(cover.setValue(0.1));
  ASSERT_TRUE(setpoint.setValue(28.0));
  ASSERT_TRUE(people.setValue(0.7));
  ASSERT_TRUE(heatGain.setValue(325.0));
  ASSERT_TRUE(pool.setActivityFactorSchedule(activity));
  ASSERT_TRUE(pool.setMakeupWaterSupplySchedule(makeup));
  ASSERT_TRUE(pool.setCoverSchedule(cover));
  ASSERT_TRUE(pool.setSetpointTemperatureSchedule(setpoint));
  ASSERT_TRUE(pool.setPeopleSchedule(people));
  ASSERT_TRUE(pool.setPeopleHeatGainSchedule(heatGain));
  auto demandOutletNode = plantLoop.demandOutletNode();
  ASSERT_TRUE(pool.addToNode(demandOutletNode));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Pool Schedule Plant Loop");
  auto loadedPool = loadedModel->getConcreteModelObjectByName<SwimmingPoolIndoor>("Reloadable Swimming Pool");
  auto loadedActivity = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool Activity");
  auto loadedMakeup = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool Makeup");
  auto loadedCover = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool Cover");
  auto loadedSetpoint = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool Setpoint");
  auto loadedPeople = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool People");
  auto loadedHeatGain = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Pool Heat Gain");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedPool);
  ASSERT_TRUE(loadedActivity);
  ASSERT_TRUE(loadedMakeup);
  ASSERT_TRUE(loadedCover);
  ASSERT_TRUE(loadedSetpoint);
  ASSERT_TRUE(loadedPeople);
  ASSERT_TRUE(loadedHeatGain);
  EXPECT_EQ(loadedActivity->handle(), loadedPool->activityFactorSchedule().handle());
  EXPECT_EQ(loadedMakeup->handle(), loadedPool->makeupWaterSupplySchedule().handle());
  EXPECT_EQ(loadedCover->handle(), loadedPool->coverSchedule().handle());
  EXPECT_EQ(loadedSetpoint->handle(), loadedPool->setpointTemperatureSchedule().handle());
  EXPECT_EQ(loadedPeople->handle(), loadedPool->peopleSchedule().handle());
  EXPECT_EQ(loadedHeatGain->handle(), loadedPool->peopleHeatGainSchedule().handle());
  ASSERT_TRUE(loadedPool->plantLoop());
  EXPECT_EQ(loadedLoop->handle(), loadedPool->plantLoop()->handle());

  ScheduleConstant replacementActivity(*loadedModel);
  ScheduleConstant replacementMakeup(*loadedModel);
  ScheduleConstant replacementCover(*loadedModel);
  ScheduleConstant replacementSetpoint(*loadedModel);
  ScheduleConstant replacementPeople(*loadedModel);
  ScheduleConstant replacementHeatGain(*loadedModel);
  ASSERT_TRUE(replacementActivity.setName("Replacement Pool Activity"));
  ASSERT_TRUE(replacementMakeup.setName("Replacement Pool Makeup"));
  ASSERT_TRUE(replacementCover.setName("Replacement Pool Cover"));
  ASSERT_TRUE(replacementSetpoint.setName("Replacement Pool Setpoint"));
  ASSERT_TRUE(replacementPeople.setName("Replacement Pool People"));
  ASSERT_TRUE(replacementHeatGain.setName("Replacement Pool Heat Gain"));
  ASSERT_TRUE(loadedPool->setActivityFactorSchedule(replacementActivity));
  ASSERT_TRUE(loadedPool->setMakeupWaterSupplySchedule(replacementMakeup));
  ASSERT_TRUE(loadedPool->setCoverSchedule(replacementCover));
  ASSERT_TRUE(loadedPool->setSetpointTemperatureSchedule(replacementSetpoint));
  ASSERT_TRUE(loadedPool->setPeopleSchedule(replacementPeople));
  ASSERT_TRUE(loadedPool->setPeopleHeatGainSchedule(replacementHeatGain));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoop = reloadedModel->getConcreteModelObjectByName<PlantLoop>("Pool Schedule Plant Loop");
  auto reloadedPool = reloadedModel->getConcreteModelObjectByName<SwimmingPoolIndoor>("Reloadable Swimming Pool");
  auto reloadedActivity = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool Activity");
  auto reloadedMakeup = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool Makeup");
  auto reloadedCover = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool Cover");
  auto reloadedSetpoint = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool Setpoint");
  auto reloadedPeople = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool People");
  auto reloadedHeatGain = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Pool Heat Gain");
  ASSERT_TRUE(reloadedLoop);
  ASSERT_TRUE(reloadedPool);
  ASSERT_TRUE(reloadedActivity);
  ASSERT_TRUE(reloadedMakeup);
  ASSERT_TRUE(reloadedCover);
  ASSERT_TRUE(reloadedSetpoint);
  ASSERT_TRUE(reloadedPeople);
  ASSERT_TRUE(reloadedHeatGain);
  EXPECT_EQ(reloadedActivity->handle(), reloadedPool->activityFactorSchedule().handle());
  EXPECT_EQ(reloadedMakeup->handle(), reloadedPool->makeupWaterSupplySchedule().handle());
  EXPECT_EQ(reloadedCover->handle(), reloadedPool->coverSchedule().handle());
  EXPECT_EQ(reloadedSetpoint->handle(), reloadedPool->setpointTemperatureSchedule().handle());
  EXPECT_EQ(reloadedPeople->handle(), reloadedPool->peopleSchedule().handle());
  EXPECT_EQ(reloadedHeatGain->handle(), reloadedPool->peopleHeatGainSchedule().handle());

  const auto poolHandle = reloadedPool->handle();
  const std::array<openstudio::Handle, 6> scheduleHandles{reloadedActivity->handle(), reloadedMakeup->handle(), reloadedCover->handle(),
                                                          reloadedSetpoint->handle(), reloadedPeople->handle(), reloadedHeatGain->handle()};
  reloadedPool->disconnect();
  EXPECT_FALSE(reloadedPool->loop());
  EXPECT_EQ(5u, reloadedLoop->demandComponents().size());
  for (const auto& handle : scheduleHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }

  const auto removed = reloadedPool->remove();
  EXPECT_FALSE(removed.empty());
  EXPECT_FALSE(reloadedModel->getObject(poolHandle));
  for (const auto& handle : scheduleHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}
