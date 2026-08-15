/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/Refrigeration_Condenser_EvaporativeCooled_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include "EPModelFixture.hpp"
#include "../ParentObject/RefrigerationCondenserEvaporativeCooled.hpp"
#include "../ParentObject/RefrigerationCondenserEvaporativeCooled_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedEvaporativeCondenserFileRemoval
{
 public:
  explicit ScopedEvaporativeCondenserFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedEvaporativeCondenserFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueEvaporativeCondenserPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_DefaultConstructor) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);
  EXPECT_EQ(RefrigerationCondenserEvaporativeCooled::iddObjectType(), openstudio::IddObjectType::Refrigeration_Condenser_EvaporativeCooled);
  EXPECT_FALSE(condenser.evaporativeCondenserAvailabilitySchedule());
}

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_AvailabilityScheduleValidationAndReset) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);

  ScheduleConstant validSchedule(model);
  ASSERT_TRUE(validSchedule.setValue(1.0));
  ASSERT_TRUE(condenser.setEvaporativeCondenserAvailabilitySchedule(validSchedule));
  ASSERT_TRUE(condenser.evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(validSchedule.handle(), condenser.evaporativeCondenserAvailabilitySchedule()->handle());
  ASSERT_TRUE(validSchedule.scheduleTypeLimits());
  EXPECT_EQ("Discrete", validSchedule.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", validSchedule.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, validSchedule.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, validSchedule.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant continuousSchedule(model);
  ScheduleTypeLimits continuousLimits(model);
  ASSERT_TRUE(continuousLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(continuousLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousSchedule.setScheduleTypeLimits(continuousLimits));

  ScheduleConstant temperatureSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureSchedule.setScheduleTypeLimits(temperatureLimits));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(condenser.setEvaporativeCondenserAvailabilitySchedule(continuousSchedule));
  EXPECT_FALSE(condenser.setEvaporativeCondenserAvailabilitySchedule(temperatureSchedule));
  EXPECT_FALSE(condenser.setEvaporativeCondenserAvailabilitySchedule(foreignSchedule));
  ASSERT_TRUE(condenser.evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(validSchedule.handle(), condenser.evaporativeCondenserAvailabilitySchedule()->handle());

  condenser.resetEvaporativeCondenserAvailabilitySchedule();
  EXPECT_FALSE(condenser.evaporativeCondenserAvailabilitySchedule());
}

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_UnresolvedRawPreservationAndReset) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);
  auto workspaceImpl = condenser.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto field = openstudio::Refrigeration_Condenser_EvaporativeCooledFields::EvaporativeCondenserAvailabilityScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Evaporative Condenser Schedule", false));

  ScheduleConstant invalidSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(invalidSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(condenser.setEvaporativeCondenserAvailabilitySchedule(invalidSchedule));
  EXPECT_EQ("Unresolved Evaporative Condenser Schedule",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  condenser.resetEvaporativeCondenserAvailabilitySchedule();
  EXPECT_FALSE(condenser.evaporativeCondenserAvailabilitySchedule());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_AvailabilityScheduleReloadReplacementAndResourceLifetime) {
  const auto firstPath = uniqueEvaporativeCondenserPath("epmodel-evaporative-condenser-schedule-first");
  const auto secondPath = uniqueEvaporativeCondenserPath("epmodel-evaporative-condenser-schedule-second");
  const ScopedEvaporativeCondenserFileRemoval removeFirst(firstPath);
  const ScopedEvaporativeCondenserFileRemoval removeSecond(secondPath);

  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);
  ScheduleConstant originalSchedule(model);
  ASSERT_TRUE(condenser.setName("Reloadable Evaporative Condenser"));
  ASSERT_TRUE(originalSchedule.setName("Original Evaporative Condenser Schedule"));
  ASSERT_TRUE(originalSchedule.setValue(1.0));
  ASSERT_TRUE(condenser.setEvaporativeCondenserAvailabilitySchedule(originalSchedule));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCondenser = loadedModel->getConcreteModelObjectByName<RefrigerationCondenserEvaporativeCooled>("Reloadable Evaporative Condenser");
  auto loadedOriginalSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Evaporative Condenser Schedule");
  ASSERT_TRUE(loadedCondenser);
  ASSERT_TRUE(loadedOriginalSchedule);
  ASSERT_TRUE(loadedCondenser->evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(loadedOriginalSchedule->handle(), loadedCondenser->evaporativeCondenserAvailabilitySchedule()->handle());

  ScheduleConstant replacementSchedule(*loadedModel);
  ASSERT_TRUE(replacementSchedule.setName("Replacement Evaporative Condenser Schedule"));
  ASSERT_TRUE(replacementSchedule.setValue(0.0));
  ASSERT_TRUE(loadedCondenser->setEvaporativeCondenserAvailabilitySchedule(replacementSchedule));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCondenser = reloadedModel->getConcreteModelObjectByName<RefrigerationCondenserEvaporativeCooled>("Reloadable Evaporative Condenser");
  auto reloadedReplacementSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Evaporative Condenser Schedule");
  ASSERT_TRUE(reloadedCondenser);
  ASSERT_TRUE(reloadedReplacementSchedule);
  ASSERT_TRUE(reloadedCondenser->evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(reloadedReplacementSchedule->handle(), reloadedCondenser->evaporativeCondenserAvailabilitySchedule()->handle());
  reloadedCondenser->resetEvaporativeCondenserAvailabilitySchedule();
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetCondenser = resetModel->getConcreteModelObjectByName<RefrigerationCondenserEvaporativeCooled>("Reloadable Evaporative Condenser");
  auto resetOriginalSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Original Evaporative Condenser Schedule");
  auto resetReplacementSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Evaporative Condenser Schedule");
  ASSERT_TRUE(resetCondenser);
  ASSERT_TRUE(resetOriginalSchedule);
  ASSERT_TRUE(resetReplacementSchedule);
  EXPECT_FALSE(resetCondenser->evaporativeCondenserAvailabilitySchedule());
  ASSERT_TRUE(resetCondenser->setEvaporativeCondenserAvailabilitySchedule(*resetReplacementSchedule));
  EXPECT_FALSE(resetCondenser->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetOriginalSchedule->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementSchedule->handle()));
}

TEST_F(EPModelFixture, RefrigerationCondenserEvaporativeCooled_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCondenserEvaporativeCooled condenser(model);

  EXPECT_TRUE(condenser.setRatedEffectiveTotalHeatRejectionRate(62000.0));
  EXPECT_DOUBLE_EQ(62000.0, condenser.ratedEffectiveTotalHeatRejectionRate());

  EXPECT_TRUE(condenser.setRatedSubcoolingTemperatureDifference(4.5));
  EXPECT_DOUBLE_EQ(4.5, condenser.ratedSubcoolingTemperatureDifference());
  EXPECT_FALSE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());
  condenser.resetRatedSubcoolingTemperatureDifference();
  EXPECT_TRUE(condenser.isRatedSubcoolingTemperatureDifferenceDefaulted());

  const auto fanSpeedTypes = RefrigerationCondenserEvaporativeCooled::fanSpeedControlTypeValues();
  ASSERT_FALSE(fanSpeedTypes.empty());
  EXPECT_TRUE(condenser.setFanSpeedControlType(fanSpeedTypes.front()));
  EXPECT_EQ(fanSpeedTypes.front(), condenser.fanSpeedControlType());
  condenser.resetFanSpeedControlType();
  EXPECT_TRUE(condenser.isFanSpeedControlTypeDefaulted());

  EXPECT_TRUE(condenser.setRatedFanPower(8700.0));
  EXPECT_DOUBLE_EQ(8700.0, condenser.ratedFanPower());

  EXPECT_TRUE(condenser.setMinimumFanAirFlowRatio(0.35));
  EXPECT_DOUBLE_EQ(0.35, condenser.minimumFanAirFlowRatio());
  condenser.resetMinimumFanAirFlowRatio();
  EXPECT_TRUE(condenser.isMinimumFanAirFlowRatioDefaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureConstantTerm(7.1));
  EXPECT_DOUBLE_EQ(7.1, condenser.approachTemperatureConstantTerm());
  condenser.resetApproachTemperatureConstantTerm();
  EXPECT_TRUE(condenser.isApproachTemperatureConstantTermDefaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient2(0.75));
  EXPECT_DOUBLE_EQ(0.75, condenser.approachTemperatureCoefficient2());
  condenser.resetApproachTemperatureCoefficient2();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient2Defaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient3(18.0));
  EXPECT_DOUBLE_EQ(18.0, condenser.approachTemperatureCoefficient3());
  condenser.resetApproachTemperatureCoefficient3();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient3Defaulted());

  EXPECT_TRUE(condenser.setApproachTemperatureCoefficient4(-0.18));
  EXPECT_DOUBLE_EQ(-0.18, condenser.approachTemperatureCoefficient4());
  condenser.resetApproachTemperatureCoefficient4();
  EXPECT_TRUE(condenser.isApproachTemperatureCoefficient4Defaulted());

  EXPECT_TRUE(condenser.setMinimumCapacityFactor(0.65));
  EXPECT_DOUBLE_EQ(0.65, condenser.minimumCapacityFactor());
  condenser.resetMinimumCapacityFactor();
  EXPECT_TRUE(condenser.isMinimumCapacityFactorDefaulted());

  EXPECT_TRUE(condenser.setMaximumCapacityFactor(3.5));
  EXPECT_DOUBLE_EQ(3.5, condenser.maximumCapacityFactor());
  condenser.resetMaximumCapacityFactor();
  EXPECT_TRUE(condenser.isMaximumCapacityFactorDefaulted());

  EXPECT_TRUE(condenser.setRatedAirFlowRate(2.65));
  ASSERT_TRUE(condenser.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(2.65, condenser.ratedAirFlowRate().get());
  EXPECT_FALSE(condenser.isRatedAirFlowRateAutocalculated());
  condenser.autocalculateRatedAirFlowRate();
  EXPECT_TRUE(condenser.isRatedAirFlowRateAutocalculated());
  condenser.resetRatedAirFlowRate();
  EXPECT_FALSE(condenser.ratedAirFlowRate());

  EXPECT_TRUE(condenser.setBasinHeaterCapacity(220.0));
  EXPECT_DOUBLE_EQ(220.0, condenser.basinHeaterCapacity());
  condenser.resetBasinHeaterCapacity();
  EXPECT_TRUE(condenser.isBasinHeaterCapacityDefaulted());

  EXPECT_TRUE(condenser.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, condenser.basinHeaterSetpointTemperature());
  condenser.resetBasinHeaterSetpointTemperature();
  EXPECT_TRUE(condenser.isBasinHeaterSetpointTemperatureDefaulted());

  EXPECT_TRUE(condenser.setRatedWaterPumpPower(1450.0));
  ASSERT_TRUE(condenser.ratedWaterPumpPower());
  EXPECT_DOUBLE_EQ(1450.0, condenser.ratedWaterPumpPower().get());
  EXPECT_FALSE(condenser.isRatedWaterPumpPowerAutocalculated());
  condenser.autocalculateRatedWaterPumpPower();
  EXPECT_TRUE(condenser.isRatedWaterPumpPowerAutocalculated());
  condenser.resetRatedWaterPumpPower();
  EXPECT_TRUE(condenser.isRatedWaterPumpPowerDefaulted());
  EXPECT_FALSE(condenser.isRatedWaterPumpPowerAutocalculated());

  EXPECT_TRUE(condenser.setEndUseSubcategory("RefrigCategory"));
  EXPECT_EQ("RefrigCategory", condenser.endUseSubcategory());
  condenser.resetEndUseSubcategory();
  EXPECT_TRUE(condenser.isEndUseSubcategoryDefaulted());

  EXPECT_TRUE(condenser.setCondenserRefrigerantOperatingChargeInventory(0.95));
  EXPECT_DOUBLE_EQ(0.95, condenser.condenserRefrigerantOperatingChargeInventory());
  condenser.resetCondenserRefrigerantOperatingChargeInventory();
  EXPECT_TRUE(condenser.isCondenserRefrigerantOperatingChargeInventoryDefaulted());

  EXPECT_TRUE(condenser.setCondensateReceiverRefrigerantInventory(1.8));
  EXPECT_DOUBLE_EQ(1.8, condenser.condensateReceiverRefrigerantInventory());
  condenser.resetCondensateReceiverRefrigerantInventory();
  EXPECT_TRUE(condenser.isCondensateReceiverRefrigerantInventoryDefaulted());

  EXPECT_TRUE(condenser.setCondensatePipingRefrigerantInventory(2.45));
  EXPECT_DOUBLE_EQ(2.45, condenser.condensatePipingRefrigerantInventory());
  condenser.resetCondensatePipingRefrigerantInventory();
  EXPECT_TRUE(condenser.isCondensatePipingRefrigerantInventoryDefaulted());
}
