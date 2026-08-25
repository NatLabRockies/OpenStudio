/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ControllerMechanicalVentilation.hpp"
#include "../ModelObject/ControllerMechanicalVentilation_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <algorithm>
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

TEST_F(EPModelFixture, ControllerMechanicalVentilation_DefaultConstructor) {
  Model model;
  ControllerMechanicalVentilation cmv(model);

  EXPECT_EQ(ControllerMechanicalVentilation::iddObjectType(), cmv.iddObject().type());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), cmv.availabilitySchedule());
  EXPECT_FALSE(cmv.demandControlledVentilation());
  EXPECT_EQ("Standard62.1VentilationRateProcedure", cmv.systemOutdoorAirMethod());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_ScalarAccessors_RoundTrip) {
  Model model;
  ControllerMechanicalVentilation cmv(model);

  auto outdoorAirMethodValues = ControllerMechanicalVentilation::systemOutdoorAirMethodValues();
  ASSERT_FALSE(outdoorAirMethodValues.empty());
  EXPECT_NE(std::find(outdoorAirMethodValues.cbegin(), outdoorAirMethodValues.cend(), "Standard62.1VentilationRateProcedure"),
            outdoorAirMethodValues.cend());

  EXPECT_TRUE(cmv.setDemandControlledVentilation(true));
  EXPECT_TRUE(cmv.demandControlledVentilation());
  cmv.setDemandControlledVentilationNoFail(false);
  EXPECT_FALSE(cmv.demandControlledVentilation());

  EXPECT_TRUE(cmv.setSystemOutdoorAirMethod("ZoneSum"));
  EXPECT_EQ("ZoneSum", cmv.systemOutdoorAirMethod());

  cmv.resetDemandControlledVentilation();
  EXPECT_TRUE(cmv.isDemandControlledVentilationDefaulted());
  EXPECT_FALSE(cmv.demandControlledVentilation());

  cmv.resetSystemOutdoorAirMethod();
  EXPECT_TRUE(cmv.isSystemOutdoorAirMethodDefaulted());
  EXPECT_EQ("Standard62.1VentilationRateProcedure", cmv.systemOutdoorAirMethod());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_AvailabilityScheduleAddsCanonicalTypeLimits) {
  Model model;
  ControllerMechanicalVentilation cmv(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));

  ASSERT_TRUE(cmv.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability, cmv.availabilitySchedule());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  const auto limits = *availability.scheduleTypeLimits();
  ASSERT_TRUE(limits.numericType());
  EXPECT_EQ("Discrete", *limits.numericType());
  EXPECT_EQ("Availability", limits.unitType());
  ASSERT_TRUE(limits.lowerLimitValue());
  ASSERT_TRUE(limits.upperLimitValue());
  EXPECT_DOUBLE_EQ(0.0, *limits.lowerLimitValue());
  EXPECT_DOUBLE_EQ(1.0, *limits.upperLimitValue());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_AvailabilityScheduleRejectionPreservesTargetAndRawText) {
  Model model;
  ControllerMechanicalVentilation cmv(model);
  ScheduleConstant accepted(model);
  ASSERT_TRUE(accepted.setValue(1.0));
  ASSERT_TRUE(cmv.setAvailabilitySchedule(accepted));

  Model foreignModel;
  ScheduleConstant foreign(foreignModel);
  EXPECT_FALSE(cmv.setAvailabilitySchedule(foreign));
  EXPECT_EQ(accepted, cmv.availabilitySchedule());

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(cmv.setAvailabilitySchedule(incompatible));
  EXPECT_EQ(accepted, cmv.availabilitySchedule());

  auto workspaceImpl = cmv.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr unsigned field = openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved CMV Availability", false));
  EXPECT_FALSE(cmv.setAvailabilitySchedule(incompatible));
  EXPECT_EQ("Unresolved CMV Availability", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_LoadRepairsRequiredAvailabilitySchedule) {
  const auto idfPath = uniqueIdfPath("epmodel-cmv-required-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  ControllerMechanicalVentilation cmv(model);
  ControllerMechanicalVentilation incompatibleCMV(model);
  ScheduleConstant incompatibleSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(cmv.setName("CMV Missing Availability"));
  ASSERT_TRUE(incompatibleCMV.setName("CMV Incompatible Availability"));
  ASSERT_TRUE(incompatibleSchedule.setName("Incompatible CMV Availability"));
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleSchedule.setScheduleTypeLimits(temperatureLimits));
  auto workspaceImpl = cmv.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto incompatibleWorkspaceImpl = incompatibleCMV.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(incompatibleWorkspaceImpl);
  constexpr unsigned field = openstudio::Controller_MechanicalVentilationFields::AvailabilityScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing CMV Availability", false));
  ASSERT_TRUE(incompatibleWorkspaceImpl->setPointer(field, incompatibleSchedule.handle(), false));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCMV = loadedModel->getConcreteModelObjectByName<ControllerMechanicalVentilation>("CMV Missing Availability");
  auto loadedIncompatibleCMV = loadedModel->getConcreteModelObjectByName<ControllerMechanicalVentilation>("CMV Incompatible Availability");
  auto loadedIncompatibleSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Incompatible CMV Availability");
  ASSERT_TRUE(loadedCMV);
  ASSERT_TRUE(loadedIncompatibleCMV);
  ASSERT_TRUE(loadedIncompatibleSchedule);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule(), loadedCMV->availabilitySchedule());
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule(), loadedIncompatibleCMV->availabilitySchedule());
  EXPECT_TRUE(loadedModel->getObject(loadedIncompatibleSchedule->handle()));
  const auto repairedSchedule = loadedCMV->availabilitySchedule().handle();
  const auto scheduleCount = loadedModel->getModelObjects<Schedule>().size();

  const auto report = loadedModel->canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_EQ(repairedSchedule, loadedCMV->availabilitySchedule().handle());
  EXPECT_EQ(repairedSchedule, loadedIncompatibleCMV->availabilitySchedule().handle());
  EXPECT_EQ(scheduleCount, loadedModel->getModelObjects<Schedule>().size());
}

TEST_F(EPModelFixture, ControllerMechanicalVentilation_AvailabilityScheduleSurvivesReloadMutationAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-cmv-availability-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-cmv-availability-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ControllerMechanicalVentilation cmv(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(cmv.setName("Reload CMV"));
  ASSERT_TRUE(availability.setName("Reload CMV Availability"));
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(cmv.setAvailabilitySchedule(availability));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCMV = loadedModel->getConcreteModelObjectByName<ControllerMechanicalVentilation>("Reload CMV");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Reload CMV Availability");
  ASSERT_TRUE(loadedCMV);
  ASSERT_TRUE(loadedAvailability);
  EXPECT_EQ(loadedAvailability->handle(), loadedCMV->availabilitySchedule().handle());

  ScheduleConstant replacement(*loadedModel);
  ASSERT_TRUE(replacement.setName("Replacement CMV Availability"));
  ASSERT_TRUE(replacement.setValue(1.0));
  ASSERT_TRUE(loadedCMV->setAvailabilitySchedule(replacement));
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCMV = reloadedModel->getConcreteModelObjectByName<ControllerMechanicalVentilation>("Reload CMV");
  auto reloadedReplacement = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement CMV Availability");
  ASSERT_TRUE(reloadedCMV);
  ASSERT_TRUE(reloadedReplacement);
  EXPECT_EQ(reloadedReplacement->handle(), reloadedCMV->availabilitySchedule().handle());
  EXPECT_FALSE(reloadedCMV->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacement->handle()));
}
