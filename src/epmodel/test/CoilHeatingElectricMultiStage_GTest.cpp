/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingElectricMultiStage.hpp"
#include "../StraightComponent/CoilHeatingElectricMultiStage_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Electric_MultiStage_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedElectricMultiStageCoilFileRemoval
{
 public:
  explicit ScopedElectricMultiStageCoilFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedElectricMultiStageCoilFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueElectricMultiStageCoilPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_DefaultConstructor) {
  Model model;
  CoilHeatingElectricMultiStage coil(model);
  EXPECT_EQ(CoilHeatingElectricMultiStage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_EQ(1u, coil.numberOfStages());
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_AvailabilitySetterValidatesAndInfers) {
  Model model;
  CoilHeatingElectricMultiStage coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.3));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, availability.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, availability.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));
  const auto availabilityHandle = availability.handle();

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatible));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignAvailability));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_CanonicalizesOnlyUniqueEligibleAvailabilityEvidence) {
  Model model;
  ScheduleConstant recoverableAvailability(model);
  ScheduleConstant duplicateAvailabilityFirst(model);
  ScheduleConstant duplicateAvailabilitySecond(model);
  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(recoverableAvailability.setName("Recoverable Electric MultiStage Coil Availability"));
  ASSERT_TRUE(duplicateAvailabilityFirst.setName("Ambiguous Electric MultiStage Coil Availability"));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setName("Incompatible Electric MultiStage Coil Availability"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));

  auto duplicateAvailabilitySecondImpl = duplicateAvailabilitySecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateAvailabilitySecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(
    duplicateAvailabilitySecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Electric MultiStage Coil Availability", false));

  CoilHeatingElectricMultiStage blank(model);
  CoilHeatingElectricMultiStage recoverable(model);
  CoilHeatingElectricMultiStage unresolved(model);
  CoilHeatingElectricMultiStage ambiguous(model);
  CoilHeatingElectricMultiStage incompatible(model);
  CoilHeatingElectricMultiStage managedDuplicate(model);
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto recoverableImpl = recoverable.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto incompatibleImpl = incompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedDuplicateImpl = managedDuplicate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(recoverableImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(incompatibleImpl);
  ASSERT_TRUE(managedDuplicateImpl);

  constexpr auto availabilityField = openstudio::Coil_Heating_Electric_MultiStageFields::AvailabilityScheduleName;
  const auto setRawEvidence = [](const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& impl, unsigned field, const std::string& value) {
    return impl->setPointer(field, openstudio::Handle(), false) && impl->openstudio::detail::IdfObject_Impl::setString(field, value, false);
  };

  // These low-level writes intentionally model blank, unique, unresolved, ambiguous, incompatible, and managed-duplicate imported storage.
  ASSERT_TRUE(setRawEvidence(blankImpl, availabilityField, ""));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, availabilityField, recoverableAvailability.nameString()));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, availabilityField, "Missing Electric MultiStage Coil Availability"));
  ASSERT_TRUE(setRawEvidence(ambiguousImpl, availabilityField, "Ambiguous Electric MultiStage Coil Availability"));
  ASSERT_TRUE(setRawEvidence(incompatibleImpl, availabilityField, incompatibleAvailability.nameString()));
  ASSERT_TRUE(managedDuplicateImpl->setPointer(availabilityField, duplicateAvailabilityFirst.handle(), false));

  // Rejected public assignments leave deliberately malformed raw evidence intact.
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(foreignAvailability));
  EXPECT_EQ("Missing Electric MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));

  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(0u, reportOnly.errorCount);
  EXPECT_GE(reportOnly.warningCount, 1u);
  EXPECT_FALSE(blankImpl->getTarget(availabilityField));
  EXPECT_EQ("", blankImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 2u);
  EXPECT_GE(report.warningCount, 4u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ(recoverableAvailability.handle(), recoverable.availabilitySchedule().handle());
  ASSERT_TRUE(recoverableAvailability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", recoverableAvailability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", recoverableAvailability.scheduleTypeLimits()->unitType());
  EXPECT_EQ("Missing Electric MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Electric MultiStage Coil Availability",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Incompatible Electric MultiStage Coil Availability",
            incompatibleImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(availabilityField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedDuplicateImpl->getTarget(availabilityField)->handle());
  EXPECT_FALSE(duplicateAvailabilityFirst.scheduleTypeLimits());

  const auto blankAvailabilityHandle = blank.availabilitySchedule().handle();
  const auto recoverableAvailabilityHandle = recoverable.availabilitySchedule().handle();
  const auto secondReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(blankAvailabilityHandle, blank.availabilitySchedule().handle());
  EXPECT_EQ(recoverableAvailabilityHandle, recoverable.availabilitySchedule().handle());
  EXPECT_EQ("Missing Electric MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Electric MultiStage Coil Availability",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Incompatible Electric MultiStage Coil Availability",
            incompatibleImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(availabilityField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedDuplicateImpl->getTarget(availabilityField)->handle());
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_AvailabilitySurvivesReloadReplacementAndRemoval) {
  const auto firstPath = uniqueElectricMultiStageCoilPath("epmodel-electric-multistage-coil-availability-first");
  const auto secondPath = uniqueElectricMultiStageCoilPath("epmodel-electric-multistage-coil-availability-second");
  const ScopedElectricMultiStageCoilFileRemoval removeFirst(firstPath);
  const ScopedElectricMultiStageCoilFileRemoval removeSecond(secondPath);

  Model model;
  ScheduleConstant originalAvailability(model);
  ASSERT_TRUE(originalAvailability.setName("Original Electric MultiStage Coil Availability"));
  CoilHeatingElectricMultiStage coil(model);
  ASSERT_TRUE(coil.setName("Reloadable Electric MultiStage Coil"));
  ASSERT_TRUE(coil.setAvailabilitySchedule(originalAvailability));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingElectricMultiStage>("Reloadable Electric MultiStage Coil");
  auto loadedOriginalAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric MultiStage Coil Availability");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedOriginalAvailability);
  EXPECT_EQ(loadedOriginalAvailability->handle(), loadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(1u, loadedCoil->numberOfStages());

  ScheduleConstant replacementAvailability(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Electric MultiStage Coil Availability"));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementAvailability));
  EXPECT_EQ(replacementAvailability.handle(), loadedCoil->availabilitySchedule().handle());
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilHeatingElectricMultiStage>("Reloadable Electric MultiStage Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric MultiStage Coil Availability");
  auto reloadedReplacementAvailability =
    reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Electric MultiStage Coil Availability");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedReplacementAvailability);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedCoil->availabilitySchedule().handle());
  EXPECT_EQ(1u, reloadedCoil->numberOfStages());

  const std::array<openstudio::Handle, 2> scheduleHandles{reloadedOriginalAvailability->handle(), reloadedReplacementAvailability->handle()};
  EXPECT_FALSE(reloadedCoil->remove().empty());
  for (const auto& handle : scheduleHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}

TEST_F(EPModelFixture, CoilHeatingElectricMultiStage_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilHeatingElectricMultiStage supplyCoil(model);
  CoilHeatingElectricMultiStage demandCoil(model);
  CoilHeatingElectricMultiStage standaloneCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(supplyCoil.addToNode(supplyInletNode));
  EXPECT_FALSE(supplyCoil.inletModelObject());
  EXPECT_FALSE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  ASSERT_TRUE(oaSystem.outboardOANode());
  auto oaNode = oaSystem.outboardOANode();
  ASSERT_TRUE(oaNode);
  EXPECT_FALSE(standaloneCoil.addToNode(*oaNode));
  Node orphanNode(model);
  EXPECT_FALSE(standaloneCoil.addToNode(orphanNode));
  EXPECT_FALSE(standaloneCoil.airLoopHVAC());
}
