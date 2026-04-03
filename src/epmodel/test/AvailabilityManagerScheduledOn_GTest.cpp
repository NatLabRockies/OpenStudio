/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOn.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/ScheduleRuleset.hpp"

#include <utilities/idd/AvailabilityManager_ScheduledOn_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_DefaultConstructor) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);
  EXPECT_EQ(AvailabilityManagerScheduledOn::iddObjectType(), availabilityManagerScheduledOn.iddObject().type());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);

  EXPECT_TRUE(availabilityManagerScheduledOn.setName("AvailabilityManager Scheduled On 1"));
  EXPECT_EQ("AvailabilityManager Scheduled On 1", availabilityManagerScheduledOn.nameString());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_ScheduleRelationship_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);

  auto defaultSchedule = availabilityManagerScheduledOn.schedule();
  auto defaultConstant = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultConstant);
  EXPECT_DOUBLE_EQ(1.0, defaultConstant->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));
  EXPECT_TRUE(availabilityManagerScheduledOn.setSchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), availabilityManagerScheduledOn.schedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleRuleset rulesetSchedule(model);
  EXPECT_TRUE(availabilityManagerScheduledOn.setSchedule(rulesetSchedule));
  EXPECT_EQ(rulesetSchedule.cast<ModelObject>(), availabilityManagerScheduledOn.schedule().cast<ModelObject>());
  ASSERT_TRUE(rulesetSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", rulesetSchedule.scheduleTypeLimits()->unitType());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_ScheduleRelationship_RejectsIncompatibleScheduleTypeLimits) {
  Model model;
  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);
  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(21.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));

  EXPECT_FALSE(availabilityManagerScheduledOn.setSchedule(wrongSchedule));
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOn_CanonicalizeReattachesNamedSchedule) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setName("Loop Availability"));
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.5));

  AvailabilityManagerScheduledOn availabilityManagerScheduledOn(model);
  ASSERT_TRUE(availabilityManagerScheduledOn.setString(openstudio::AvailabilityManager_ScheduledOnFields::ScheduleName, compactSchedule.nameString()));

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), availabilityManagerScheduledOn.schedule().cast<ModelObject>());
}
