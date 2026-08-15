/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ModelObject/ZoneHVACEquipmentConnections.hpp"
#include "../ModelObject/ZoneHVACEquipmentList.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveElectric_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneHVAC_Baseboard_Convective_Electric_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedElectricBaseboardFileRemoval
{
 public:
  explicit ScopedElectricBaseboardFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedElectricBaseboardFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueElectricBaseboardPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardConvectiveElectric baseboard(model);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), baseboard.availabilitySchedule().handle());
  EXPECT_TRUE(baseboard.isNominalCapacityAutosized());
  ASSERT_TRUE(baseboard.efficiency());
  EXPECT_DOUBLE_EQ(1.0, baseboard.efficiency().get());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_AvailabilityScheduleValidationPreservesZoneAttachment) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);
  ASSERT_TRUE(baseboard.addToThermalZone(zone));

  ScheduleConstant accepted(model);
  ASSERT_TRUE(accepted.setValue(1.0));
  ASSERT_TRUE(baseboard.setAvailabilitySchedule(accepted));
  EXPECT_EQ(accepted.handle(), baseboard.availabilitySchedule().handle());
  ASSERT_TRUE(accepted.scheduleTypeLimits());
  EXPECT_EQ("Availability", accepted.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(accepted.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", *accepted.scheduleTypeLimits()->numericType());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(baseboard.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(baseboard.setAvailabilitySchedule(foreign));
  EXPECT_EQ(accepted.handle(), baseboard.availabilitySchedule().handle());
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone.handle(), baseboard.thermalZone()->handle());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_CanonicalizationRepairsOnlyBlankAvailability) {
  constexpr auto field = openstudio::ZoneHVAC_Baseboard_Convective_ElectricFields::AvailabilityScheduleName;

  Model blankModel;
  ZoneHVACBaseboardConvectiveElectric blankBaseboard(blankModel);
  auto blankWorkspaceImpl = blankBaseboard.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankWorkspaceImpl);
  ASSERT_TRUE(blankWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  EXPECT_EQ(0u, blankModel.canonicalize().errorCount);
  EXPECT_EQ(blankModel.alwaysOnDiscreteSchedule().handle(), blankBaseboard.availabilitySchedule().handle());

  Model unresolvedModel;
  ZoneHVACBaseboardConvectiveElectric unresolvedBaseboard(unresolvedModel);
  auto unresolvedWorkspaceImpl = unresolvedBaseboard.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(unresolvedWorkspaceImpl);
  ASSERT_TRUE(unresolvedWorkspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Baseboard Availability", false));
  EXPECT_EQ(0u, unresolvedModel.canonicalize().errorCount);
  EXPECT_EQ("Unresolved Baseboard Availability",
            unresolvedWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_AvailabilitySurvivesReloadReplacementAndRemoval) {
  const auto firstPath = uniqueElectricBaseboardPath("epmodel-electric-convective-baseboard-first");
  const auto secondPath = uniqueElectricBaseboardPath("epmodel-electric-convective-baseboard-second");
  const ScopedElectricBaseboardFileRemoval removeFirst(firstPath);
  const ScopedElectricBaseboardFileRemoval removeSecond(secondPath);

  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);
  ScheduleConstant original(model);
  ASSERT_TRUE(zone.setName("Electric Baseboard Zone"));
  ASSERT_TRUE(baseboard.setName("Reloadable Electric Convective Baseboard"));
  ASSERT_TRUE(original.setName("Original Electric Baseboard Availability"));
  ASSERT_TRUE(original.setValue(1.0));
  ASSERT_TRUE(baseboard.setAvailabilitySchedule(original));
  ASSERT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBaseboard = loadedModel->getConcreteModelObjectByName<ZoneHVACBaseboardConvectiveElectric>("Reloadable Electric Convective Baseboard");
  auto loadedOriginal = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric Baseboard Availability");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Electric Baseboard Zone");
  ASSERT_TRUE(loadedBaseboard);
  ASSERT_TRUE(loadedOriginal);
  ASSERT_TRUE(loadedZone);
  EXPECT_EQ(loadedOriginal->handle(), loadedBaseboard->availabilitySchedule().handle());
  ASSERT_TRUE(loadedBaseboard->thermalZone());
  EXPECT_EQ(loadedZone->handle(), loadedBaseboard->thermalZone()->handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement Electric Baseboard Availability"));
  ASSERT_TRUE(replacement.setValue(0.0));
  ASSERT_TRUE(loadedBaseboard->setAvailabilitySchedule(replacement));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedBaseboard =
    reloadedModel->getConcreteModelObjectByName<ZoneHVACBaseboardConvectiveElectric>("Reloadable Electric Convective Baseboard");
  auto reloadedOriginal = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric Baseboard Availability");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Electric Baseboard Availability");
  ASSERT_TRUE(reloadedBaseboard);
  ASSERT_TRUE(reloadedOriginal);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_EQ(reloadedReplacement->handle(), reloadedBaseboard->availabilitySchedule().handle());
  EXPECT_FALSE(reloadedBaseboard->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginal->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardConvectiveElectric baseboard(model);

  EXPECT_TRUE(baseboard.setNominalCapacity(5000.0));
  ASSERT_TRUE(baseboard.nominalCapacity());
  EXPECT_DOUBLE_EQ(5000.0, baseboard.nominalCapacity().get());
  baseboard.autosizeNominalCapacity();
  EXPECT_TRUE(baseboard.isNominalCapacityAutosized());

  EXPECT_TRUE(baseboard.setEfficiency(0.85));
  ASSERT_TRUE(baseboard.efficiency());
  EXPECT_DOUBLE_EQ(0.85, baseboard.efficiency().get());
  baseboard.resetEfficiency();
  EXPECT_TRUE(baseboard.isEfficiencyDefaulted());
  ASSERT_TRUE(baseboard.efficiency());
  EXPECT_DOUBLE_EQ(1.0, baseboard.efficiency().get());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveElectric_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveElectric baseboard(model);

  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone, *baseboard.thermalZone());

  auto connections = zone.getImpl<detail::ThermalZone_Impl>()->zoneHVACEquipmentConnections();
  ASSERT_TRUE(connections);
  auto equipmentList = connections->zoneHVACEquipmentList();
  EXPECT_EQ(1u, equipmentList.equipment().size());

  baseboard.removeFromThermalZone();
  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_TRUE(equipmentList.equipment().empty());
}
