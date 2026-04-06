/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../AvailabilityManager/AvailabilityManagerScheduledOff.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Schedule/ScheduleYear.hpp"

#include <utilities/idd/AvailabilityManager_ScheduledOff_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_DefaultConstructor) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);
  EXPECT_EQ(AvailabilityManagerScheduledOff::iddObjectType(), availabilityManagerScheduledOff.iddObject().type());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_ScalarAccessors_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);

  EXPECT_TRUE(availabilityManagerScheduledOff.setName("AvailabilityManager Scheduled Off 1"));
  EXPECT_EQ("AvailabilityManager Scheduled Off 1", availabilityManagerScheduledOff.nameString());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_ScheduleRelationship_RoundTrip) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);

  auto defaultSchedule = availabilityManagerScheduledOff.schedule();
  auto defaultConstant = defaultSchedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultConstant);
  EXPECT_DOUBLE_EQ(0.0, defaultConstant->value());

  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.25));
  EXPECT_TRUE(availabilityManagerScheduledOff.setSchedule(compactSchedule));
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), availabilityManagerScheduledOff.schedule().cast<ModelObject>());
  ASSERT_TRUE(compactSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", compactSchedule.scheduleTypeLimits()->unitType());

  ScheduleYear yearSchedule(model);
  EXPECT_TRUE(availabilityManagerScheduledOff.setSchedule(yearSchedule));
  EXPECT_EQ(yearSchedule.cast<ModelObject>(), availabilityManagerScheduledOff.schedule().cast<ModelObject>());
  ASSERT_TRUE(yearSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", yearSchedule.scheduleTypeLimits()->unitType());
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_ScheduleRelationship_RejectsIncompatibleScheduleTypeLimits) {
  Model model;
  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);
  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(19.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(temperatureLimits));

  EXPECT_FALSE(availabilityManagerScheduledOff.setSchedule(wrongSchedule));
}

TEST_F(EPModelFixture, AvailabilityManagerScheduledOff_CanonicalizeReattachesNamedSchedule) {
  Model model;
  ScheduleCompact compactSchedule(model);
  ASSERT_TRUE(compactSchedule.setName("Loop Availability Off"));
  ASSERT_TRUE(compactSchedule.setToConstantValue(0.25));

  AvailabilityManagerScheduledOff availabilityManagerScheduledOff(model);
  ASSERT_TRUE(availabilityManagerScheduledOff.setString(openstudio::AvailabilityManager_ScheduledOffFields::ScheduleName, compactSchedule.nameString()));

  auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(compactSchedule.cast<ModelObject>(), availabilityManagerScheduledOff.schedule().cast<ModelObject>());
}
