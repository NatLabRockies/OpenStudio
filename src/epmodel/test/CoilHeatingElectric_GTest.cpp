/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/CoilHeatingElectric_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedElectricCoilFileRemoval
{
 public:
  explicit ScopedElectricCoilFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedElectricCoilFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueElectricCoilPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilHeatingElectric_DefaultConstructor) {
  Model model;
  CoilHeatingElectric coil(model);
  EXPECT_EQ(CoilHeatingElectric::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.temperatureSetpointNode());
}

TEST_F(EPModelFixture, CoilHeatingElectric_ScheduleConstructorAndValidation) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.75));
  CoilHeatingElectric coil(model, availability);
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, availability.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, availability.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant replacement(model);
  ASSERT_TRUE(replacement.setValue(1.0));
  ASSERT_TRUE(coil.setAvailabilitySchedule(replacement));
  EXPECT_EQ(replacement.handle(), coil.availabilitySchedule().handle());
  const auto replacementHandle = replacement.handle();

  ScheduleConstant incompatible(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatible));
  EXPECT_EQ(replacementHandle, coil.availabilitySchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignSchedule));
  EXPECT_EQ(replacementHandle, coil.availabilitySchedule().handle());
  const auto coilCount = model.getConcreteModelObjects<CoilHeatingElectric>().size();
  EXPECT_ANY_THROW({ CoilHeatingElectric rejected(model, foreignSchedule); });
  EXPECT_EQ(coilCount, model.getConcreteModelObjects<CoilHeatingElectric>().size());
}

TEST_F(EPModelFixture, CoilHeatingElectric_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingElectric coil(model);

  EXPECT_TRUE(coil.setEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, coil.efficiency());
  EXPECT_FALSE(coil.isEfficiencyDefaulted());
  coil.resetEfficiency();
  EXPECT_DOUBLE_EQ(1.0, coil.efficiency());
  EXPECT_TRUE(coil.isEfficiencyDefaulted());

  EXPECT_TRUE(coil.setNominalCapacity(4200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(4200.0, *coil.nominalCapacity());
  EXPECT_FALSE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());

  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  coil.resetNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityDefaulted());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());

  EXPECT_FALSE(coil.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, CoilHeatingElectric_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingElectric coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  Node setpointNode(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setTemperatureSetpointNode(setpointNode));
  ASSERT_TRUE(coil.temperatureSetpointNode());
  EXPECT_EQ(setpointNode.handle(), coil.temperatureSetpointNode()->handle());
  coil.resetTemperatureSetpointNode();
  EXPECT_FALSE(coil.temperatureSetpointNode());
}

TEST_F(EPModelFixture, CoilHeatingElectric_CanonicalizesOnlyUniqueEligibleAvailabilityEvidence) {
  Model model;
  ScheduleConstant recoverableAvailability(model);
  ScheduleConstant duplicateAvailabilityFirst(model);
  ScheduleConstant duplicateAvailabilitySecond(model);
  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(recoverableAvailability.setName("Recoverable Electric Coil Availability"));
  ASSERT_TRUE(duplicateAvailabilityFirst.setName("Ambiguous Electric Coil Availability"));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setName("Incompatible Electric Coil Availability"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));

  auto duplicateAvailabilitySecondImpl = duplicateAvailabilitySecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateAvailabilitySecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(duplicateAvailabilitySecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Electric Coil Availability", false));

  CoilHeatingElectric blank(model);
  CoilHeatingElectric recoverable(model);
  CoilHeatingElectric unresolved(model);
  CoilHeatingElectric ambiguous(model);
  CoilHeatingElectric incompatible(model);
  CoilHeatingElectric managedDuplicate(model);
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

  constexpr auto availabilityField = openstudio::Coil_Heating_ElectricFields::AvailabilityScheduleName;
  const auto setRawEvidence = [](const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& impl, unsigned field, const std::string& value) {
    return impl->setPointer(field, openstudio::Handle(), false) && impl->openstudio::detail::IdfObject_Impl::setString(field, value, false);
  };

  // These low-level writes intentionally model blank, unique, unresolved, ambiguous, incompatible, and managed-duplicate imported storage.
  ASSERT_TRUE(setRawEvidence(blankImpl, availabilityField, ""));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, availabilityField, recoverableAvailability.nameString()));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, availabilityField, "Missing Electric Coil Availability"));
  ASSERT_TRUE(setRawEvidence(ambiguousImpl, availabilityField, "Ambiguous Electric Coil Availability"));
  ASSERT_TRUE(setRawEvidence(incompatibleImpl, availabilityField, incompatibleAvailability.nameString()));
  ASSERT_TRUE(managedDuplicateImpl->setPointer(availabilityField, duplicateAvailabilityFirst.handle(), false));

  // Rejected public assignments leave deliberately malformed raw evidence intact.
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(foreignAvailability));
  EXPECT_EQ("Missing Electric Coil Availability",
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
  EXPECT_EQ("Missing Electric Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Electric Coil Availability",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Incompatible Electric Coil Availability",
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
  EXPECT_EQ("Missing Electric Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Electric Coil Availability",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Incompatible Electric Coil Availability",
            incompatibleImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(availabilityField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedDuplicateImpl->getTarget(availabilityField)->handle());
}

TEST_F(EPModelFixture, CoilHeatingElectric_AvailabilitySurvivesUUIDReloadReplacementAndRemoval) {
  const auto firstPath = uniqueElectricCoilPath("epmodel-electric-coil-availability-first");
  const auto secondPath = uniqueElectricCoilPath("epmodel-electric-coil-availability-second");
  const ScopedElectricCoilFileRemoval removeFirst(firstPath);
  const ScopedElectricCoilFileRemoval removeSecond(secondPath);

  Model model;
  ScheduleConstant originalAvailability(model);
  ASSERT_TRUE(originalAvailability.setName("Original Electric Coil Availability"));
  CoilHeatingElectric coil(model, originalAvailability);
  ASSERT_TRUE(coil.setName("Reloadable Electric Coil"));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Reloadable Electric Coil");
  auto loadedOriginalAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric Coil Availability");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedOriginalAvailability);
  EXPECT_EQ(loadedOriginalAvailability->handle(), loadedCoil->availabilitySchedule().handle());

  ScheduleConstant replacementAvailability(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Electric Coil Availability"));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementAvailability));
  EXPECT_EQ(replacementAvailability.handle(), loadedCoil->availabilitySchedule().handle());
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilHeatingElectric>("Reloadable Electric Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Electric Coil Availability");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Electric Coil Availability");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedReplacementAvailability);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedCoil->availabilitySchedule().handle());

  const std::array<openstudio::Handle, 2> scheduleHandles{reloadedOriginalAvailability->handle(), reloadedReplacementAvailability->handle()};
  EXPECT_FALSE(reloadedCoil->remove().empty());
  for (const auto& handle : scheduleHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}

TEST_F(EPModelFixture, CoilHeatingElectric_AddToNodeRejectsAirLoopDemandNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingElectric coil(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto demandBranchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));
  EXPECT_FALSE(coil.addToNode(*demandBranchNode));
}

TEST_F(EPModelFixture, CoilHeatingElectric_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingElectric coil(model);
  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
