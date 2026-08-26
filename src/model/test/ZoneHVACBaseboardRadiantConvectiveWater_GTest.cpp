/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"

#include "../ZoneHVACBaseboardRadiantConvectiveWater.hpp"
#include "../ZoneHVACBaseboardRadiantConvectiveWater_Impl.hpp"
#include "../ThermalZone.hpp"
#include "../ThermalZone_Impl.hpp"
#include "../Schedule.hpp"
#include "../Schedule_Impl.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleConstant_Impl.hpp"
#include "../CoilHeatingWaterBaseboardRadiant.hpp"
#include "../CoilHeatingWaterBaseboardRadiant_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, ZoneHVACBaseboardRadiantConvectiveWater) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      ZoneHVACBaseboardRadiantConvectiveWater zonehvac(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

TEST_F(ModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_AddAndRemove) {
  Model m;
  ZoneHVACBaseboardRadiantConvectiveWater zonehvac(m);

  ThermalZone tz(m);
  ASSERT_TRUE(zonehvac.addToThermalZone(tz));
  ASSERT_TRUE(zonehvac.thermalZone());
  ASSERT_EQ(tz, zonehvac.thermalZone().get());
  ASSERT_EQ(1u, tz.equipment().size());
  zonehvac.removeFromThermalZone();
  ASSERT_EQ(0u, tz.equipment().size());

  ZoneHVACBaseboardRadiantConvectiveWater zonehvac2(m);
  zonehvac2.addToThermalZone(tz);
  zonehvac2.remove();
  ASSERT_EQ(0u, tz.equipment().size());
}

TEST_F(ModelFixture, ZoneHVACBaseboardRadiantConvectiveWater_SetGetFields) {
  Model m;
  ZoneHVACBaseboardRadiantConvectiveWater zonehvac(m);

  Schedule schedule = zonehvac.availabilitySchedule();
  boost::optional<ScheduleConstant> scheduleConstant = schedule.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(scheduleConstant);
  EXPECT_EQ((*scheduleConstant).value(), 1.0);
  EXPECT_EQ(0.3, zonehvac.fractionRadiant());
  EXPECT_EQ(0.3, zonehvac.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_EQ(0.05, zonehvac.fractionofRadiantEnergytoFloorSurfaces());
  EXPECT_EQ(0.55, zonehvac.fractionofRadiantEnergytoWallSurfaces());
  EXPECT_EQ(0.40, zonehvac.fractionofRadiantEnergytoCeilingSurfaces());
  HVACComponent coil = zonehvac.heatingCoil();
  boost::optional<CoilHeatingWaterBaseboardRadiant> coilHeating = coil.optionalCast<CoilHeatingWaterBaseboardRadiant>();
  ASSERT_TRUE(coilHeating);

  ScheduleConstant sched(m);
  sched.setValue(0.5);
  EXPECT_TRUE(zonehvac.setAvailabilitySchedule(sched));
  EXPECT_TRUE(zonehvac.setFractionRadiant(0.75));
  EXPECT_TRUE(zonehvac.setFractionofRadiantEnergyIncidentonPeople(0.35));
  EXPECT_TRUE(zonehvac.setFractionofRadiantEnergytoFloorSurfaces(0.4));
  EXPECT_TRUE(zonehvac.setFractionofRadiantEnergytoWallSurfaces(0.5));
  EXPECT_TRUE(zonehvac.setFractionofRadiantEnergytoCeilingSurfaces(0.6));
  CoilHeatingWaterBaseboardRadiant coilHeating2(m);
  EXPECT_TRUE(zonehvac.setHeatingCoil(coilHeating2));

  Schedule schedule2 = zonehvac.availabilitySchedule();
  boost::optional<ScheduleConstant> scheduleConstant2 = schedule2.optionalCast<ScheduleConstant>();
  ASSERT_TRUE(scheduleConstant2);
  EXPECT_EQ((*scheduleConstant2).value(), 0.5);
  EXPECT_EQ(0.75, zonehvac.fractionRadiant());
  EXPECT_EQ(0.35, zonehvac.fractionofRadiantEnergyIncidentonPeople());
  EXPECT_EQ(0.4, zonehvac.fractionofRadiantEnergytoFloorSurfaces());
  EXPECT_EQ(0.5, zonehvac.fractionofRadiantEnergytoWallSurfaces());
  EXPECT_EQ(0.6, zonehvac.fractionofRadiantEnergytoCeilingSurfaces());
  HVACComponent coil3 = zonehvac.heatingCoil();
  boost::optional<CoilHeatingWaterBaseboardRadiant> coilHeating3 = coil3.optionalCast<CoilHeatingWaterBaseboardRadiant>();
  ASSERT_TRUE(coilHeating3);
  EXPECT_EQ(coilHeating2.nameString(), coil3.nameString());
}
