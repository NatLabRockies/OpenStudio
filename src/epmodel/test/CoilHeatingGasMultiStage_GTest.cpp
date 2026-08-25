/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Curve/CurveCubic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "EPModelFixture.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingGasMultiStage.hpp"
#include "../StraightComponent/CoilHeatingGasMultiStage_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_Gas_MultiStage_FieldEnums.hxx>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedGasMultiStageCoilFileRemoval
{
 public:
  explicit ScopedGasMultiStageCoilFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedGasMultiStageCoilFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueGasMultiStageCoilPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_DefaultConstructor) {
  Model model;
  CoilHeatingGasMultiStage coil(model);
  EXPECT_EQ(CoilHeatingGasMultiStage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_EQ(1u, coil.numberOfStages());
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());
  EXPECT_FALSE(coil.parasiticGasLoad());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_ReportOnlyPreservesBlankAvailabilityAndRepairCanonicalizesIt) {
  Model model;
  CoilHeatingGasMultiStage coil(model);
  auto coilImpl = coil.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(coilImpl);
  constexpr auto availabilityField = openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName;

  // This low-level write intentionally models an imported blank availability field without invoking the public getter.
  ASSERT_TRUE(coilImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(coilImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "", false));

  const auto reportOnly = model.canonicalize(SanitizationPolicy::ReportOnly);
  EXPECT_EQ(0u, reportOnly.errorCount);
  EXPECT_GE(reportOnly.warningCount, 1u);
  EXPECT_FALSE(coilImpl->getTarget(availabilityField));
  EXPECT_EQ("", coilImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(1u, coil.numberOfStages());

  const auto repair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, repair.errorCount);
  EXPECT_GE(repair.infoCount, 1u);
  const auto repairedAvailability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(repairedAvailability);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), repairedAvailability->handle());
  EXPECT_DOUBLE_EQ(1.0, repairedAvailability->value());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(1u, coil.numberOfStages());

  const auto repairedHandle = repairedAvailability->handle();
  const auto secondRepair = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondRepair.errorCount);
  EXPECT_EQ(repairedHandle, coil.availabilitySchedule().handle());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_RelationshipSettersValidateInferResetAndPreserve) {
  Model model;
  CoilHeatingGasMultiStage coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.3));
  CurveQuadratic plf(model);
  ASSERT_TRUE(plf.setCoefficient1Constant(0.7));
  ASSERT_TRUE(plf.setCoefficient2x(0.3));
  ASSERT_TRUE(plf.setCoefficient3xPOW2(0.0));
  CurveCubic cubic(model);
  CurveBiquadratic bivariate(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, availability.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, availability.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));
  const auto availabilityHandle = availability.handle();

  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignAvailability));
  EXPECT_EQ(availabilityHandle, coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());
  CurveQuadratic foreignCurve(foreignModel);
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(foreignCurve));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());

  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(cubic));
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(cubic.handle(), coil.partLoadFractionCorrelationCurve()->handle());
  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(cubic.handle(), children[0].handle());

  coil.resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingGasMultiStage coil(model);

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(12.5));
  ASSERT_TRUE(coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(12.5, *coil.offCycleParasiticGasLoad());
  ASSERT_TRUE(coil.parasiticGasLoad());
  EXPECT_DOUBLE_EQ(12.5, *coil.parasiticGasLoad());

  EXPECT_TRUE(coil.setParasiticGasLoad(9.75));
  ASSERT_TRUE(coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(9.75, *coil.offCycleParasiticGasLoad());

  coil.resetParasiticGasLoad();
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(3.2));
  coil.resetOffCycleParasiticGasLoad();
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_CanonicalizesOnlyUniqueEligibleRelationshipEvidence) {
  Model model;
  ScheduleConstant recoverableAvailability(model);
  CurveQuadratic recoverableCurve(model);
  ScheduleConstant duplicateAvailabilityFirst(model);
  ScheduleConstant duplicateAvailabilitySecond(model);
  CurveQuadratic duplicateCurveFirst(model);
  CurveQuadratic duplicateCurveSecond(model);
  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  CurveBiquadratic incompatibleCurve(model);
  ASSERT_TRUE(recoverableAvailability.setName("Recoverable Gas MultiStage Coil Availability"));
  ASSERT_TRUE(recoverableCurve.setName("Recoverable Gas MultiStage Coil PLF"));
  ASSERT_TRUE(duplicateAvailabilityFirst.setName("Ambiguous Gas MultiStage Coil Availability"));
  ASSERT_TRUE(duplicateCurveFirst.setName("Ambiguous Gas MultiStage Coil PLF"));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));

  auto duplicateAvailabilitySecondImpl = duplicateAvailabilitySecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto duplicateCurveSecondImpl = duplicateCurveSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateAvailabilitySecondImpl);
  ASSERT_TRUE(duplicateCurveSecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(
    duplicateAvailabilitySecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Gas MultiStage Coil Availability", false));
  ASSERT_TRUE(duplicateCurveSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Gas MultiStage Coil PLF", false));

  CoilHeatingGasMultiStage recoverable(model);
  CoilHeatingGasMultiStage unresolved(model);
  CoilHeatingGasMultiStage rawDuplicate(model);
  CoilHeatingGasMultiStage managedDuplicate(model);
  CoilHeatingGasMultiStage managedIncompatible(model);
  CoilHeatingGasMultiStage rawReset(model);
  auto recoverableImpl = recoverable.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto rawDuplicateImpl = rawDuplicate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedDuplicateImpl = managedDuplicate.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedIncompatibleImpl = managedIncompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto rawResetImpl = rawReset.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(recoverableImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(rawDuplicateImpl);
  ASSERT_TRUE(managedDuplicateImpl);
  ASSERT_TRUE(managedIncompatibleImpl);
  ASSERT_TRUE(rawResetImpl);

  constexpr auto availabilityField = openstudio::Coil_Heating_Gas_MultiStageFields::AvailabilityScheduleName;
  constexpr auto curveField = openstudio::Coil_Heating_Gas_MultiStageFields::PartLoadFractionCorrelationCurveName;
  const auto setRawEvidence = [](const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& impl, unsigned field, const std::string& value) {
    return impl->setPointer(field, openstudio::Handle(), false) && impl->openstudio::detail::IdfObject_Impl::setString(field, value, false);
  };

  // These low-level writes intentionally model unique, unresolved, raw-duplicate, managed-duplicate, and incompatible imported storage.
  ASSERT_TRUE(setRawEvidence(recoverableImpl, availabilityField, recoverableAvailability.nameString()));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, curveField, recoverableCurve.nameString()));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, availabilityField, "Missing Gas MultiStage Coil Availability"));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, curveField, "Missing Gas MultiStage Coil PLF"));
  ASSERT_TRUE(setRawEvidence(rawDuplicateImpl, availabilityField, "Ambiguous Gas MultiStage Coil Availability"));
  ASSERT_TRUE(setRawEvidence(rawDuplicateImpl, curveField, "Ambiguous Gas MultiStage Coil PLF"));
  ASSERT_TRUE(managedDuplicateImpl->setPointer(availabilityField, duplicateAvailabilityFirst.handle(), false));
  ASSERT_TRUE(managedDuplicateImpl->setPointer(curveField, duplicateCurveFirst.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(availabilityField, incompatibleAvailability.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(curveField, incompatibleCurve.handle(), false));
  ASSERT_TRUE(setRawEvidence(rawResetImpl, curveField, "Raw Gas MultiStage Coil PLF To Reset"));
  rawReset.resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(rawResetImpl->getTarget(curveField));
  EXPECT_EQ("", rawResetImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));

  // Rejected public assignments leave deliberately malformed raw evidence intact.
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(incompatibleCurve));
  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  CurveQuadratic foreignCurve(foreignModel);
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(foreignAvailability));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(foreignCurve));
  EXPECT_EQ("Missing Gas MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Gas MultiStage Coil PLF", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 2u);
  EXPECT_GE(report.warningCount, 8u);
  EXPECT_EQ(recoverableAvailability.handle(), recoverable.availabilitySchedule().handle());
  ASSERT_TRUE(recoverable.partLoadFractionCorrelationCurve());
  EXPECT_EQ(recoverableCurve.handle(), recoverable.partLoadFractionCorrelationCurve()->handle());
  ASSERT_TRUE(recoverableAvailability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", recoverableAvailability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", recoverableAvailability.scheduleTypeLimits()->unitType());
  EXPECT_EQ("Missing Gas MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Gas MultiStage Coil PLF", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Gas MultiStage Coil Availability",
            rawDuplicateImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Gas MultiStage Coil PLF",
            rawDuplicateImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(curveField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedDuplicateImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(duplicateCurveFirst.handle(), managedDuplicateImpl->getTarget(curveField)->handle());
  EXPECT_FALSE(duplicateAvailabilityFirst.scheduleTypeLimits());
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(curveField));
  EXPECT_EQ(incompatibleAvailability.handle(), managedIncompatibleImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(incompatibleCurve.handle(), managedIncompatibleImpl->getTarget(curveField)->handle());
  EXPECT_FALSE(rawReset.partLoadFractionCorrelationCurve());

  const auto recoverableAvailabilityHandle = recoverable.availabilitySchedule().handle();
  const auto recoverableCurveHandle = recoverable.partLoadFractionCorrelationCurve()->handle();
  const auto secondReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(recoverableAvailabilityHandle, recoverable.availabilitySchedule().handle());
  EXPECT_EQ(recoverableCurveHandle, recoverable.partLoadFractionCorrelationCurve()->handle());
  EXPECT_EQ("Missing Gas MultiStage Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Gas MultiStage Coil PLF", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedDuplicateImpl->getTarget(curveField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedDuplicateImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(duplicateCurveFirst.handle(), managedDuplicateImpl->getTarget(curveField)->handle());
  EXPECT_FALSE(rawReset.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_RelationshipsSurviveReloadResetReattachAndRemoval) {
  const auto firstPath = uniqueGasMultiStageCoilPath("epmodel-gas-multistage-coil-relationships-first");
  const auto secondPath = uniqueGasMultiStageCoilPath("epmodel-gas-multistage-coil-relationships-second");
  const ScopedGasMultiStageCoilFileRemoval removeFirst(firstPath);
  const ScopedGasMultiStageCoilFileRemoval removeSecond(secondPath);

  Model model;
  ScheduleConstant originalAvailability(model);
  CurveQuadratic originalCurve(model);
  ASSERT_TRUE(originalAvailability.setName("Original Gas MultiStage Coil Availability"));
  ASSERT_TRUE(originalCurve.setName("Original Gas MultiStage Coil PLF"));
  CoilHeatingGasMultiStage coil(model);
  ASSERT_TRUE(coil.setName("Reloadable Gas MultiStage Coil"));
  ASSERT_TRUE(coil.setAvailabilitySchedule(originalAvailability));
  ASSERT_TRUE(coil.setPartLoadFractionCorrelationCurve(originalCurve));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGasMultiStage>("Reloadable Gas MultiStage Coil");
  auto loadedOriginalAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Gas MultiStage Coil Availability");
  auto loadedOriginalCurve = loadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original Gas MultiStage Coil PLF");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedOriginalAvailability);
  ASSERT_TRUE(loadedOriginalCurve);
  EXPECT_EQ(loadedOriginalAvailability->handle(), loadedCoil->availabilitySchedule().handle());
  ASSERT_TRUE(loadedCoil->partLoadFractionCorrelationCurve());
  EXPECT_EQ(loadedOriginalCurve->handle(), loadedCoil->partLoadFractionCorrelationCurve()->handle());
  const auto loadedChildren = loadedCoil->children();
  ASSERT_EQ(1u, loadedChildren.size());
  EXPECT_EQ(loadedOriginalCurve->handle(), loadedChildren.front().handle());
  EXPECT_EQ(1u, loadedCoil->numberOfStages());

  ScheduleConstant replacementAvailability(*loadedModel);
  CurveCubic replacementCurve(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Gas MultiStage Coil Availability"));
  ASSERT_TRUE(replacementCurve.setName("Replacement Gas MultiStage Coil PLF"));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedCoil->setPartLoadFractionCorrelationCurve(replacementCurve));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilHeatingGasMultiStage>("Reloadable Gas MultiStage Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Gas MultiStage Coil Availability");
  auto reloadedOriginalCurve = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original Gas MultiStage Coil PLF");
  auto reloadedReplacementAvailability =
    reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Gas MultiStage Coil Availability");
  auto reloadedReplacementCurve = reloadedModel->getConcreteModelObjectByName<CurveCubic>("Replacement Gas MultiStage Coil PLF");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedOriginalCurve);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedReplacementCurve);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedCoil->availabilitySchedule().handle());
  ASSERT_TRUE(reloadedCoil->partLoadFractionCorrelationCurve());
  EXPECT_EQ(reloadedReplacementCurve->handle(), reloadedCoil->partLoadFractionCorrelationCurve()->handle());
  EXPECT_EQ(1u, reloadedCoil->numberOfStages());

  reloadedCoil->resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(reloadedCoil->partLoadFractionCorrelationCurve());
  EXPECT_TRUE(reloadedCoil->children().empty());
  ASSERT_TRUE(reloadedCoil->setPartLoadFractionCorrelationCurve(*reloadedReplacementCurve));
  const auto currentChildren = reloadedCoil->children();
  ASSERT_EQ(1u, currentChildren.size());
  EXPECT_EQ(reloadedReplacementCurve->handle(), currentChildren.front().handle());

  const std::array<openstudio::Handle, 4> resourceHandles{reloadedOriginalAvailability->handle(), reloadedOriginalCurve->handle(),
                                                          reloadedReplacementAvailability->handle(), reloadedReplacementCurve->handle()};
  EXPECT_FALSE(reloadedCoil->remove().empty());
  for (const auto& handle : resourceHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilHeatingGasMultiStage supplyCoil(model);
  CoilHeatingGasMultiStage demandCoil(model);
  CoilHeatingGasMultiStage oaCoil(model);
  CoilHeatingGasMultiStage standaloneCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_FALSE(supplyCoil.addToNode(supplyInletNode));
  EXPECT_FALSE(supplyCoil.inletModelObject());
  EXPECT_FALSE(supplyCoil.outletModelObject());
  EXPECT_FALSE(supplyCoil.airLoopHVAC());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());
  EXPECT_FALSE(demandCoil.inletModelObject());
  EXPECT_FALSE(demandCoil.outletModelObject());

  ASSERT_TRUE(oaSystem.outboardOANode());
  auto oaNode = oaSystem.outboardOANode();
  EXPECT_FALSE(oaCoil.addToNode(*oaNode));
  EXPECT_FALSE(oaCoil.inletModelObject());
  EXPECT_FALSE(oaCoil.outletModelObject());
  EXPECT_FALSE(oaCoil.airLoopHVAC());

  Node orphanNode(model);
  EXPECT_FALSE(standaloneCoil.addToNode(orphanNode));
  EXPECT_FALSE(standaloneCoil.inletModelObject());
  EXPECT_FALSE(standaloneCoil.outletModelObject());
  EXPECT_FALSE(standaloneCoil.airLoopHVAC());
}
