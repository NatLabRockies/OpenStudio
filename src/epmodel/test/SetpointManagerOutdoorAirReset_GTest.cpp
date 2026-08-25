/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirReset.hpp"
#include "../SetpointManager/SetpointManagerOutdoorAirReset_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/SetpointManager_OutdoorAirReset_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedOutdoorAirResetFileRemoval
{
 public:
  explicit ScopedOutdoorAirResetFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedOutdoorAirResetFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueOutdoorAirResetIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_DefaultConstructor) {
  Model model;
  SetpointManagerOutdoorAirReset spm(model);
  EXPECT_EQ(SetpointManagerOutdoorAirReset::iddObjectType(), spm.iddObject().type());
  EXPECT_FALSE(spm.nameString().empty());
  EXPECT_FALSE(spm.schedule());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_ScalarAccessors_RoundTrip) {
  Model model;
  SetpointManagerOutdoorAirReset spm(model);

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_FALSE(spm.isControlVariableDefaulted());
  EXPECT_DOUBLE_EQ(22.0, spm.setpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.outdoorLowTemperature());
  EXPECT_DOUBLE_EQ(10.0, spm.setpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(24.0, spm.outdoorHighTemperature());
  EXPECT_FALSE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_FALSE(spm.outdoorLowTemperature2());
  EXPECT_FALSE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_FALSE(spm.outdoorHighTemperature2());

  const auto controlVariableValues = SetpointManagerOutdoorAirReset::controlVariableValues();
  EXPECT_FALSE(controlVariableValues.empty());

  EXPECT_TRUE(spm.setSetpointatOutdoorLowTemperature(12.5));
  EXPECT_TRUE(spm.setOutdoorLowTemperature(5.5));
  EXPECT_TRUE(spm.setSetpointatOutdoorHighTemperature(18.25));
  EXPECT_TRUE(spm.setOutdoorHighTemperature(30.75));
  EXPECT_TRUE(spm.setSetpointatOutdoorLowTemperature2(11.1));
  EXPECT_TRUE(spm.setOutdoorLowTemperature2(7.7));
  EXPECT_TRUE(spm.setSetpointatOutdoorHighTemperature2(19.9));
  EXPECT_TRUE(spm.setOutdoorHighTemperature2(27.3));

  EXPECT_DOUBLE_EQ(12.5, spm.setpointatOutdoorLowTemperature());
  EXPECT_DOUBLE_EQ(5.5, spm.outdoorLowTemperature());
  EXPECT_DOUBLE_EQ(18.25, spm.setpointatOutdoorHighTemperature());
  EXPECT_DOUBLE_EQ(30.75, spm.outdoorHighTemperature());
  ASSERT_TRUE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_DOUBLE_EQ(11.1, *spm.setpointatOutdoorLowTemperature2());
  ASSERT_TRUE(spm.outdoorLowTemperature2());
  EXPECT_DOUBLE_EQ(7.7, *spm.outdoorLowTemperature2());
  ASSERT_TRUE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_DOUBLE_EQ(19.9, *spm.setpointatOutdoorHighTemperature2());
  ASSERT_TRUE(spm.outdoorHighTemperature2());
  EXPECT_DOUBLE_EQ(27.3, *spm.outdoorHighTemperature2());

  spm.resetControlVariable();
  spm.resetSetpointatOutdoorLowTemperature2();
  spm.resetOutdoorLowTemperature2();
  spm.resetSetpointatOutdoorHighTemperature2();
  spm.resetOutdoorHighTemperature2();

  EXPECT_EQ("Temperature", spm.controlVariable());
  EXPECT_TRUE(spm.isControlVariableDefaulted());
  EXPECT_FALSE(spm.setpointatOutdoorLowTemperature2());
  EXPECT_FALSE(spm.outdoorLowTemperature2());
  EXPECT_FALSE(spm.setpointatOutdoorHighTemperature2());
  EXPECT_FALSE(spm.outdoorHighTemperature2());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_ScheduleRelationshipValidatesAndResets) {
  Model model;
  SetpointManagerOutdoorAirReset spm(model);
  ScheduleConstant accepted(model);
  ASSERT_TRUE(accepted.setValue(2.0));
  ASSERT_TRUE(spm.setSchedule(accepted));
  ASSERT_TRUE(spm.schedule());
  EXPECT_EQ(accepted.handle(), spm.schedule()->handle());
  ASSERT_TRUE(accepted.scheduleTypeLimits());
  ASSERT_TRUE(accepted.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", *accepted.scheduleTypeLimits()->numericType());
  ASSERT_TRUE(accepted.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *accepted.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(accepted.scheduleTypeLimits()->upperLimitValue());

  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ScheduleConstant incompatible(model);
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(discreteLimits));
  EXPECT_FALSE(spm.setSchedule(incompatible));
  EXPECT_EQ(accepted.handle(), spm.schedule()->handle());

  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ScheduleConstant wrongUnit(model);
  ASSERT_TRUE(wrongUnit.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(spm.setSchedule(wrongUnit));
  EXPECT_EQ(accepted.handle(), spm.schedule()->handle());

  ScheduleTypeLimits negativeLimits(model);
  ASSERT_TRUE(negativeLimits.setNumericType("Continuous"));
  ASSERT_TRUE(negativeLimits.setLowerLimitValue(-1.0));
  ScheduleConstant negative(model);
  ASSERT_TRUE(negative.setScheduleTypeLimits(negativeLimits));
  EXPECT_FALSE(spm.setSchedule(negative));
  EXPECT_EQ(accepted.handle(), spm.schedule()->handle());

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(spm.setSchedule(foreign));
  EXPECT_EQ(accepted.handle(), spm.schedule()->handle());

  spm.resetSchedule();
  EXPECT_FALSE(spm.schedule());
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_CanonicalizesOnlyUniquePersistedSchedule) {
  Model model;
  ScheduleConstant recoverable(model);
  ScheduleConstant duplicateFirst(model);
  ScheduleConstant duplicateSecond(model);
  ASSERT_TRUE(recoverable.setName("Recoverable Outdoor Air Reset Schedule"));
  ASSERT_TRUE(duplicateFirst.setName("Ambiguous Outdoor Air Reset Schedule"));
  auto duplicateSecondImpl = duplicateSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateSecondImpl);
  // Imported IDFs can contain duplicate names, while the public name setter deliberately disambiguates them.
  ASSERT_TRUE(duplicateSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Outdoor Air Reset Schedule", false));

  SetpointManagerOutdoorAirReset recoverableManager(model);
  SetpointManagerOutdoorAirReset missingManager(model);
  SetpointManagerOutdoorAirReset ambiguousManager(model);
  auto recoverableImpl = recoverableManager.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto missingImpl = missingManager.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguousManager.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(recoverableImpl);
  ASSERT_TRUE(missingImpl);
  ASSERT_TRUE(ambiguousImpl);
  constexpr auto scheduleField = openstudio::SetpointManager_OutdoorAirResetFields::ScheduleName;

  // These raw fields represent unresolved or ambiguous persisted state that validated public setters cannot create.
  ASSERT_TRUE(recoverableImpl->setPointer(scheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(recoverableImpl->openstudio::detail::IdfObject_Impl::setString(scheduleField, recoverable.nameString(), false));
  ASSERT_TRUE(missingImpl->setPointer(scheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(missingImpl->openstudio::detail::IdfObject_Impl::setString(scheduleField, "Missing Outdoor Air Reset Schedule", false));
  ASSERT_TRUE(ambiguousImpl->setPointer(scheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(ambiguousImpl->openstudio::detail::IdfObject_Impl::setString(scheduleField, "Ambiguous Outdoor Air Reset Schedule", false));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(recoverableManager.schedule());
  EXPECT_EQ(recoverable.handle(), recoverableManager.schedule()->handle());
  EXPECT_FALSE(missingManager.getField(scheduleField, false));
  EXPECT_EQ("Missing Outdoor Air Reset Schedule",
            missingImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));
  EXPECT_FALSE(ambiguousManager.getField(scheduleField, false));
  EXPECT_EQ("Ambiguous Outdoor Air Reset Schedule",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(missingManager.setSchedule(foreign));
  EXPECT_EQ("Missing Outdoor Air Reset Schedule",
            missingImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));
  missingManager.resetSchedule();
  EXPECT_EQ("", missingImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));
}

TEST_F(EPModelFixture, SetpointManagerOutdoorAirReset_ReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueOutdoorAirResetIdfPath("epmodel-outdoor-air-reset-first");
  const auto secondIdfPath = uniqueOutdoorAirResetIdfPath("epmodel-outdoor-air-reset-second");
  const ScopedOutdoorAirResetFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedOutdoorAirResetFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirLoopHVAC airLoop(model);
  SetpointManagerOutdoorAirReset spm(model);
  ScheduleConstant initial(model);
  ASSERT_TRUE(airLoop.setName("Outdoor Air Reset Air Loop"));
  ASSERT_TRUE(spm.setName("Outdoor Air Reset Manager"));
  ASSERT_TRUE(initial.setName("Initial Outdoor Air Reset Schedule"));
  ASSERT_TRUE(initial.setValue(1.0));
  ASSERT_TRUE(spm.setSchedule(initial));
  auto node = airLoop.supplyOutletNode();
  ASSERT_TRUE(spm.addToNode(node));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Outdoor Air Reset Air Loop");
  auto loadedManager = loadedModel->getConcreteModelObjectByName<SetpointManagerOutdoorAirReset>("Outdoor Air Reset Manager");
  auto loadedInitial = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Initial Outdoor Air Reset Schedule");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedManager);
  ASSERT_TRUE(loadedInitial);
  ASSERT_TRUE(loadedManager->schedule());
  EXPECT_EQ(loadedInitial->handle(), loadedManager->schedule()->handle());
  ASSERT_TRUE(loadedManager->setpointNode());
  EXPECT_EQ(loadedLoop->supplyOutletNode().handle(), loadedManager->setpointNode()->handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement Outdoor Air Reset Schedule"));
  ASSERT_TRUE(replacement.setValue(2.0));
  ASSERT_TRUE(loadedManager->setSchedule(replacement));
  loadedManager->resetSchedule();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedLoop = reloadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Outdoor Air Reset Air Loop");
  auto reloadedManager = reloadedModel->getConcreteModelObjectByName<SetpointManagerOutdoorAirReset>("Outdoor Air Reset Manager");
  auto reloadedInitial = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Initial Outdoor Air Reset Schedule");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Outdoor Air Reset Schedule");
  ASSERT_TRUE(reloadedLoop);
  ASSERT_TRUE(reloadedManager);
  ASSERT_TRUE(reloadedInitial);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_FALSE(reloadedManager->schedule());
  ASSERT_TRUE(reloadedManager->setSchedule(*reloadedReplacement));
  const auto reloadedNode = reloadedLoop->supplyOutletNode();
  EXPECT_FALSE(reloadedManager->remove().empty());
  EXPECT_TRUE(reloadedNode.setpointManagers().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedLoop->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedInitial->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
}
