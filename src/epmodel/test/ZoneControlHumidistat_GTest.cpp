/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneControlHumidistat.hpp"
#include "../ModelObject/ZoneControlHumidistat_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, ZoneControlHumidistat_DefaultConstructor) {
  Model model;
  ZoneControlHumidistat humidistat(model);
  EXPECT_EQ(ZoneControlHumidistat::iddObjectType(), humidistat.iddObject().type());
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneControlHumidistat humidistat(model);

  EXPECT_TRUE(humidistat.setName("Zone Humidistat"));
  EXPECT_EQ("Zone Humidistat", humidistat.nameString());
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ScheduleRelationshipsAndControlledZone_RoundTrip) {
  Model model;
  ZoneControlHumidistat humidistat(model);
  ThermalZone zone(model);
  ScheduleConstant humidifying(model);
  ScheduleConstant dehumidifying(model);
  ASSERT_TRUE(humidifying.setValue(40.0));
  ASSERT_TRUE(dehumidifying.setValue(60.0));

  EXPECT_FALSE(humidistat.controlledZone());
  ASSERT_TRUE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(humidifying));
  ASSERT_TRUE(humidistat.setDehumidifyingRelativeHumiditySetpointSchedule(dehumidifying));
  ASSERT_TRUE(humidistat.humidifyingRelativeHumiditySetpointSchedule());
  ASSERT_TRUE(humidistat.dehumidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ(humidifying.handle(), humidistat.humidifyingRelativeHumiditySetpointSchedule()->handle());
  EXPECT_EQ(dehumidifying.handle(), humidistat.dehumidifyingRelativeHumiditySetpointSchedule()->handle());

  for (const auto& schedule : {humidifying, dehumidifying}) {
    ASSERT_TRUE(schedule.scheduleTypeLimits());
    const auto limits = *schedule.scheduleTypeLimits();
    ASSERT_TRUE(limits.numericType());
    EXPECT_EQ("Continuous", *limits.numericType());
    EXPECT_EQ("Percent", limits.unitType());
    ASSERT_TRUE(limits.lowerLimitValue());
    ASSERT_TRUE(limits.upperLimitValue());
    EXPECT_DOUBLE_EQ(0.0, *limits.lowerLimitValue());
    EXPECT_DOUBLE_EQ(100.0, *limits.upperLimitValue());
  }

  ASSERT_TRUE(zone.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(humidistat.controlledZone());
  EXPECT_EQ(zone.handle(), humidistat.controlledZone()->handle());

  humidistat.resetHumidifyingRelativeHumiditySetpointSchedule();
  EXPECT_FALSE(humidistat.humidifyingRelativeHumiditySetpointSchedule());
  ASSERT_TRUE(humidistat.dehumidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ(dehumidifying.handle(), humidistat.dehumidifyingRelativeHumiditySetpointSchedule()->handle());

  humidistat.resetDehumidifyingRelativeHumiditySetpointSchedule();
  EXPECT_FALSE(humidistat.dehumidifyingRelativeHumiditySetpointSchedule());
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ScheduleRelationships_RejectIncompatibleAndForeignSchedulesWithoutMutation) {
  Model model;
  ZoneControlHumidistat humidistat(model);
  ScheduleConstant accepted(model);
  ASSERT_TRUE(accepted.setValue(40.0));
  ASSERT_TRUE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(accepted));

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(incompatible));
  ASSERT_TRUE(humidistat.humidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ(accepted.handle(), humidistat.humidifyingRelativeHumiditySetpointSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  ASSERT_TRUE(foreign.setValue(50.0));
  EXPECT_FALSE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(foreign));
  ASSERT_TRUE(humidistat.humidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ(accepted.handle(), humidistat.humidifyingRelativeHumiditySetpointSchedule()->handle());
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ThermalZoneOwnershipClonesAndDeletesHumidistatsButNotSchedules) {
  Model model;
  ThermalZone firstZone(model);
  ThermalZone secondZone(model);
  ThermalZone removedZone(model);
  ZoneControlHumidistat humidistat(model);
  ScheduleConstant humidifying(model);
  ScheduleConstant dehumidifying(model);
  ASSERT_TRUE(humidifying.setValue(40.0));
  ASSERT_TRUE(dehumidifying.setValue(60.0));
  ASSERT_TRUE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(humidifying));
  ASSERT_TRUE(humidistat.setDehumidifyingRelativeHumiditySetpointSchedule(dehumidifying));
  ASSERT_TRUE(firstZone.setZoneControlHumidistat(humidistat));
  EXPECT_TRUE(firstZone.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(firstZone.zoneControlHumidistat());
  EXPECT_EQ(humidistat.handle(), firstZone.zoneControlHumidistat()->handle());

  ASSERT_TRUE(secondZone.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(secondZone.zoneControlHumidistat());
  const auto clonedHumidistat = *secondZone.zoneControlHumidistat();
  EXPECT_NE(humidistat.handle(), clonedHumidistat.handle());
  ASSERT_TRUE(clonedHumidistat.humidifyingRelativeHumiditySetpointSchedule());
  ASSERT_TRUE(clonedHumidistat.dehumidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ(humidifying.handle(), clonedHumidistat.humidifyingRelativeHumiditySetpointSchedule()->handle());
  EXPECT_EQ(dehumidifying.handle(), clonedHumidistat.dehumidifyingRelativeHumiditySetpointSchedule()->handle());

  const auto originalHumidistatHandle = humidistat.handle();
  ZoneControlHumidistat replacement(model);
  ASSERT_TRUE(firstZone.setZoneControlHumidistat(replacement));
  EXPECT_FALSE(model.getModelObject<ZoneControlHumidistat>(originalHumidistatHandle));
  ASSERT_TRUE(replacement.controlledZone());
  EXPECT_EQ(firstZone.handle(), replacement.controlledZone()->handle());

  const auto clonedHumidistatHandle = clonedHumidistat.handle();
  secondZone.resetZoneControlHumidistat();
  EXPECT_FALSE(model.getModelObject<ZoneControlHumidistat>(clonedHumidistatHandle));
  EXPECT_TRUE(model.getModelObject<ScheduleConstant>(humidifying.handle()));
  EXPECT_TRUE(model.getModelObject<ScheduleConstant>(dehumidifying.handle()));

  ZoneControlHumidistat zoneOwned(model);
  ASSERT_TRUE(zoneOwned.setHumidifyingRelativeHumiditySetpointSchedule(humidifying));
  ASSERT_TRUE(removedZone.setZoneControlHumidistat(zoneOwned));
  const auto zoneOwnedHandle = zoneOwned.handle();
  EXPECT_FALSE(removedZone.remove().empty());
  EXPECT_FALSE(model.getModelObject<ZoneControlHumidistat>(zoneOwnedHandle));
  EXPECT_TRUE(model.getModelObject<ScheduleConstant>(humidifying.handle()));
}

TEST_F(EPModelFixture, ZoneControlHumidistat_ScheduleRelationshipsAndOwnerSurviveReload) {
  const auto idfPath = uniqueIdfPath("epmodel-zone-control-humidistat-relationships");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  ThermalZone zone(model);
  ZoneControlHumidistat humidistat(model);
  ScheduleConstant humidifying(model);
  ScheduleConstant dehumidifying(model);
  ASSERT_TRUE(zone.setName("Humidistat Roundtrip Zone"));
  ASSERT_TRUE(humidistat.setName("Humidistat Roundtrip Controller"));
  ASSERT_TRUE(humidifying.setName("Humidistat Roundtrip Humidifying"));
  ASSERT_TRUE(dehumidifying.setName("Humidistat Roundtrip Dehumidifying"));
  ASSERT_TRUE(humidifying.setValue(40.0));
  ASSERT_TRUE(dehumidifying.setValue(60.0));
  ASSERT_TRUE(humidistat.setHumidifyingRelativeHumiditySetpointSchedule(humidifying));
  ASSERT_TRUE(humidistat.setDehumidifyingRelativeHumiditySetpointSchedule(dehumidifying));
  ASSERT_TRUE(zone.setZoneControlHumidistat(humidistat));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Humidistat Roundtrip Zone");
  auto loadedHumidistat = loadedModel->getConcreteModelObjectByName<ZoneControlHumidistat>("Humidistat Roundtrip Controller");
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedHumidistat);
  ASSERT_TRUE(loadedZone->zoneControlHumidistat());
  EXPECT_EQ(loadedHumidistat->handle(), loadedZone->zoneControlHumidistat()->handle());
  ASSERT_TRUE(loadedHumidistat->controlledZone());
  EXPECT_EQ(loadedZone->handle(), loadedHumidistat->controlledZone()->handle());
  ASSERT_TRUE(loadedHumidistat->humidifyingRelativeHumiditySetpointSchedule());
  ASSERT_TRUE(loadedHumidistat->dehumidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ("Humidistat Roundtrip Humidifying", loadedHumidistat->humidifyingRelativeHumiditySetpointSchedule()->nameString());
  EXPECT_EQ("Humidistat Roundtrip Dehumidifying", loadedHumidistat->dehumidifyingRelativeHumiditySetpointSchedule()->nameString());

  ScheduleConstant replacementHumidifying(*loadedModel);
  ASSERT_TRUE(replacementHumidifying.setName("Humidistat Roundtrip Replacement Humidifying"));
  ASSERT_TRUE(replacementHumidifying.setValue(45.0));
  ASSERT_TRUE(loadedHumidistat->setHumidifyingRelativeHumiditySetpointSchedule(replacementHumidifying));
  loadedHumidistat->resetDehumidifyingRelativeHumiditySetpointSchedule();
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Humidistat Roundtrip Zone");
  auto reloadedHumidistat = reloadedModel->getConcreteModelObjectByName<ZoneControlHumidistat>("Humidistat Roundtrip Controller");
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedHumidistat);
  ASSERT_TRUE(reloadedZone->zoneControlHumidistat());
  EXPECT_EQ(reloadedHumidistat->handle(), reloadedZone->zoneControlHumidistat()->handle());
  ASSERT_TRUE(reloadedHumidistat->controlledZone());
  EXPECT_EQ(reloadedZone->handle(), reloadedHumidistat->controlledZone()->handle());
  ASSERT_TRUE(reloadedHumidistat->humidifyingRelativeHumiditySetpointSchedule());
  EXPECT_EQ("Humidistat Roundtrip Replacement Humidifying", reloadedHumidistat->humidifyingRelativeHumiditySetpointSchedule()->nameString());
  EXPECT_FALSE(reloadedHumidistat->dehumidifyingRelativeHumiditySetpointSchedule());
}
