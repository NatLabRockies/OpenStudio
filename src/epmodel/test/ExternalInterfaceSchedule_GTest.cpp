/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Schedule/ExternalInterfaceSchedule.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleRuleset.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceSchedule_Constructor) {
  Model model;
  ExternalInterfaceSchedule object(model);
  EXPECT_EQ(ExternalInterfaceSchedule::iddObjectType(), object.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, object.initialValue());

  ExternalInterfaceSchedule withInitial(model, 10.0);
  EXPECT_EQ(ExternalInterfaceSchedule::iddObjectType(), withInitial.iddObject().type());
  EXPECT_DOUBLE_EQ(10.0, withInitial.initialValue());
}

TEST_F(EPModelFixture, ExternalInterfaceSchedule_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceSchedule object(model);

  EXPECT_TRUE(object.setInitialValue(11.25));
  EXPECT_DOUBLE_EQ(11.25, object.initialValue());

  EXPECT_TRUE(object.setInitialValue(-0.5));
  EXPECT_DOUBLE_EQ(-0.5, object.initialValue());
}

TEST_F(EPModelFixture, ScheduleCompact_Constructor) {
  Model model;
  ScheduleCompact object(model);
  EXPECT_EQ(ScheduleCompact::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.isConstantValue());
  EXPECT_FALSE(object.constantValue().has_value());
}

TEST_F(EPModelFixture, ScheduleCompact_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleCompact object(model);

  EXPECT_TRUE(object.setToConstantValue(0.25));
  EXPECT_TRUE(object.isConstantValue());
  ASSERT_TRUE(object.constantValue().has_value());
  EXPECT_DOUBLE_EQ(0.25, *object.constantValue());

  EXPECT_TRUE(object.setToConstantValue(-1.5));
  EXPECT_TRUE(object.isConstantValue());
  ASSERT_TRUE(object.constantValue().has_value());
  EXPECT_DOUBLE_EQ(-1.5, *object.constantValue());
}

TEST_F(EPModelFixture, ScheduleConstant_Constructor) {
  Model model;
  ScheduleConstant object(model);
  EXPECT_EQ(ScheduleConstant::iddObjectType(), object.iddObject().type());
  EXPECT_DOUBLE_EQ(0.0, object.value());
}

TEST_F(EPModelFixture, ScheduleConstant_ScalarAccessors_RoundTrip) {
  Model model;
  ScheduleConstant object(model);

  EXPECT_TRUE(object.setValue(0.25));
  EXPECT_DOUBLE_EQ(0.25, object.value());

  EXPECT_TRUE(object.setValue(-1.5));
  EXPECT_DOUBLE_EQ(-1.5, object.value());
}

TEST_F(EPModelFixture, ScheduleBase_CastsAcrossConcreteScheduleTypes) {
  Model model;
  ScheduleConstant scheduleConstant(model);
  ScheduleCompact scheduleCompact(model);
  ScheduleRuleset scheduleRuleset(model);
  ExternalInterfaceSchedule externalSchedule(model);

  auto constantBase = scheduleConstant.optionalCast<Schedule>();
  ASSERT_TRUE(constantBase);
  EXPECT_EQ(scheduleConstant.cast<ModelObject>(), constantBase->cast<ModelObject>());

  auto compactBase = scheduleCompact.optionalCast<Schedule>();
  ASSERT_TRUE(compactBase);
  EXPECT_EQ(scheduleCompact.cast<ModelObject>(), compactBase->cast<ModelObject>());

  auto rulesetBase = scheduleRuleset.optionalCast<Schedule>();
  ASSERT_TRUE(rulesetBase);
  EXPECT_EQ(scheduleRuleset.cast<ModelObject>(), rulesetBase->cast<ModelObject>());

  auto externalBase = externalSchedule.optionalCast<Schedule>();
  ASSERT_TRUE(externalBase);
  EXPECT_EQ(externalSchedule.cast<ModelObject>(), externalBase->cast<ModelObject>());
}
