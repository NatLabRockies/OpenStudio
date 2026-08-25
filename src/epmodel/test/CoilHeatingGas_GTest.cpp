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
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/CoilHeatingGas_Impl.hpp"
#include "../StraightComponent/Duct.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeReheat_Impl.hpp"

#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedGasCoilFileRemoval
{
 public:
  explicit ScopedGasCoilFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedGasCoilFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueGasCoilPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

}  // namespace

TEST_F(EPModelFixture, CoilHeatingGas_DefaultConstructor) {
  Model model;
  CoilHeatingGas coil(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_Heating_Fuel), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_FALSE(coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
}

TEST_F(EPModelFixture, CoilHeatingGas_ScheduleConstructorAliasesAndValidation) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.75));
  CoilHeatingGas coil(model, availability);
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(availability.handle(), coil.availableSchedule().handle());
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, availability.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, availability.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant replacement(model);
  ASSERT_TRUE(replacement.setValue(1.0));
  ASSERT_TRUE(coil.setAvailableSchedule(replacement));
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
  EXPECT_FALSE(coil.setAvailableSchedule(foreignSchedule));
  EXPECT_EQ(replacementHandle, coil.availabilitySchedule().handle());
  const auto coilCount = model.getConcreteModelObjects<CoilHeatingGas>().size();
  EXPECT_ANY_THROW({ CoilHeatingGas rejected(model, foreignSchedule); });
  EXPECT_EQ(coilCount, model.getConcreteModelObjects<CoilHeatingGas>().size());
}

TEST_F(EPModelFixture, CoilHeatingGas_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);

  EXPECT_FALSE(CoilHeatingGas::validFuelTypeValues().empty());
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setFuelType("Propane"));
  EXPECT_EQ("Propane", coil.fuelType());
  coil.resetFuelType();
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setGasBurnerEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, coil.gasBurnerEfficiency());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(10.5));
  EXPECT_DOUBLE_EQ(10.5, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(10.5, coil.parasiticElectricLoad());
  EXPECT_TRUE(coil.setParasiticElectricLoad(11.5));
  EXPECT_DOUBLE_EQ(11.5, coil.onCycleParasiticElectricLoad());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(2.25));
  EXPECT_DOUBLE_EQ(2.25, coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(2.25, coil.parasiticGasLoad());
  EXPECT_TRUE(coil.setParasiticGasLoad(3.25));
  EXPECT_DOUBLE_EQ(3.25, coil.offCycleParasiticGasLoad());

  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.setNominalCapacity(1200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(1200.0, coil.nominalCapacity().get());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  coil.resetNominalCapacity();
  EXPECT_FALSE(coil.nominalCapacity());
  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, CoilHeatingGas_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.4));
  CurveQuadratic plf(model);
  ASSERT_TRUE(plf.setCoefficient1Constant(0.8));
  ASSERT_TRUE(plf.setCoefficient2x(0.2));
  ASSERT_TRUE(plf.setCoefficient3xPOW2(0.0));
  CurveCubic cubic(model);
  CurveBiquadratic bivariate(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());

  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());
  Model foreignModel;
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

TEST_F(EPModelFixture, CoilHeatingGas_CanonicalizesOnlyUniqueEligibleRelationshipEvidence) {
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
  ASSERT_TRUE(recoverableAvailability.setName("Recoverable Gas Coil Availability"));
  ASSERT_TRUE(recoverableCurve.setName("Recoverable Gas Coil PLF"));
  ASSERT_TRUE(duplicateAvailabilityFirst.setName("Ambiguous Gas Coil Availability"));
  ASSERT_TRUE(duplicateCurveFirst.setName("Ambiguous Gas Coil PLF"));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));

  auto duplicateAvailabilitySecondImpl = duplicateAvailabilitySecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto duplicateCurveSecondImpl = duplicateCurveSecond.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(duplicateAvailabilitySecondImpl);
  ASSERT_TRUE(duplicateCurveSecondImpl);
  // Imported EnergyPlus files may contain duplicate eligible names; public name setters deliberately disambiguate them.
  ASSERT_TRUE(duplicateAvailabilitySecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Gas Coil Availability", false));
  ASSERT_TRUE(duplicateCurveSecondImpl->openstudio::detail::IdfObject_Impl::setString(0u, "Ambiguous Gas Coil PLF", false));

  CoilHeatingGas blank(model);
  CoilHeatingGas recoverable(model);
  CoilHeatingGas unresolved(model);
  CoilHeatingGas ambiguous(model);
  CoilHeatingGas managedAmbiguous(model);
  CoilHeatingGas managedIncompatible(model);
  CoilHeatingGas rawReset(model);
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto recoverableImpl = recoverable.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto ambiguousImpl = ambiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedAmbiguousImpl = managedAmbiguous.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto managedIncompatibleImpl = managedIncompatible.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto rawResetImpl = rawReset.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(recoverableImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(ambiguousImpl);
  ASSERT_TRUE(managedAmbiguousImpl);
  ASSERT_TRUE(managedIncompatibleImpl);
  ASSERT_TRUE(rawResetImpl);

  constexpr auto availabilityField = openstudio::Coil_Heating_FuelFields::AvailabilityScheduleName;
  constexpr auto curveField = openstudio::Coil_Heating_FuelFields::PartLoadFractionCorrelationCurveName;
  const auto setRawEvidence = [](const std::shared_ptr<openstudio::detail::WorkspaceObject_Impl>& impl, unsigned field, const std::string& value) {
    return impl->setPointer(field, openstudio::Handle(), false) && impl->openstudio::detail::IdfObject_Impl::setString(field, value, false);
  };

  // These low-level writes intentionally model blank, unique, unresolved, ambiguous, and incompatible imported relationship storage.
  ASSERT_TRUE(setRawEvidence(blankImpl, availabilityField, ""));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, availabilityField, recoverableAvailability.nameString()));
  ASSERT_TRUE(setRawEvidence(recoverableImpl, curveField, recoverableCurve.nameString()));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, availabilityField, "Missing Gas Coil Availability"));
  ASSERT_TRUE(setRawEvidence(unresolvedImpl, curveField, "Missing Gas Coil PLF"));
  ASSERT_TRUE(setRawEvidence(ambiguousImpl, availabilityField, "Ambiguous Gas Coil Availability"));
  ASSERT_TRUE(setRawEvidence(ambiguousImpl, curveField, "Ambiguous Gas Coil PLF"));
  ASSERT_TRUE(managedAmbiguousImpl->setPointer(availabilityField, duplicateAvailabilityFirst.handle(), false));
  ASSERT_TRUE(managedAmbiguousImpl->setPointer(curveField, duplicateCurveFirst.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(availabilityField, incompatibleAvailability.handle(), false));
  ASSERT_TRUE(managedIncompatibleImpl->setPointer(curveField, incompatibleCurve.handle(), false));
  ASSERT_TRUE(setRawEvidence(rawResetImpl, curveField, "Raw Gas Coil PLF To Reset"));
  rawReset.resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(rawResetImpl->getTarget(curveField));
  EXPECT_EQ("", rawResetImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));

  // Rejected public assignments leave deliberately malformed raw evidence intact.
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(incompatibleCurve));
  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveQuadratic foreignCurve(foreignModel);
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(foreignCurve));
  EXPECT_EQ("Missing Gas Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Gas Coil PLF", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));

  const auto report = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 3u);
  EXPECT_GE(report.warningCount, 6u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_FALSE(blank.partLoadFractionCorrelationCurve());
  EXPECT_EQ(recoverableAvailability.handle(), recoverable.availabilitySchedule().handle());
  ASSERT_TRUE(recoverable.partLoadFractionCorrelationCurve());
  EXPECT_EQ(recoverableCurve.handle(), recoverable.partLoadFractionCorrelationCurve()->handle());
  ASSERT_TRUE(recoverableAvailability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", recoverableAvailability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Missing Gas Coil Availability",
            unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Missing Gas Coil PLF", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Gas Coil Availability",
            ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Ambiguous Gas Coil PLF", ambiguousImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  ASSERT_TRUE(managedAmbiguousImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedAmbiguousImpl->getTarget(curveField));
  EXPECT_EQ(duplicateAvailabilityFirst.handle(), managedAmbiguousImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(duplicateCurveFirst.handle(), managedAmbiguousImpl->getTarget(curveField)->handle());
  EXPECT_FALSE(duplicateAvailabilityFirst.scheduleTypeLimits());
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(availabilityField));
  ASSERT_TRUE(managedIncompatibleImpl->getTarget(curveField));
  EXPECT_EQ(incompatibleAvailability.handle(), managedIncompatibleImpl->getTarget(availabilityField)->handle());
  EXPECT_EQ(incompatibleCurve.handle(), managedIncompatibleImpl->getTarget(curveField)->handle());

  const auto blankAvailabilityHandle = blank.availabilitySchedule().handle();
  const auto recoverableCurveHandle = recoverable.partLoadFractionCorrelationCurve()->handle();
  const auto secondReport = model.canonicalize(SanitizationPolicy::Repair);
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(blankAvailabilityHandle, blank.availabilitySchedule().handle());
  EXPECT_EQ(recoverableCurveHandle, recoverable.partLoadFractionCorrelationCurve()->handle());
}

TEST_F(EPModelFixture, CoilHeatingGas_RelationshipsSurviveReloadReplacementResetAndRemoval) {
  const auto firstPath = uniqueGasCoilPath("epmodel-gas-coil-relationships-first");
  const auto secondPath = uniqueGasCoilPath("epmodel-gas-coil-relationships-second");
  const ScopedGasCoilFileRemoval removeFirst(firstPath);
  const ScopedGasCoilFileRemoval removeSecond(secondPath);

  Model model;
  ScheduleConstant originalAvailability(model);
  CurveQuadratic originalCurve(model);
  ASSERT_TRUE(originalAvailability.setName("Original Gas Coil Availability"));
  ASSERT_TRUE(originalCurve.setName("Original Gas Coil PLF"));
  CoilHeatingGas coil(model, originalAvailability);
  ASSERT_TRUE(coil.setName("Reloadable Gas Coil"));
  ASSERT_TRUE(coil.setPartLoadFractionCorrelationCurve(originalCurve));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Reloadable Gas Coil");
  auto loadedOriginalAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Gas Coil Availability");
  auto loadedOriginalCurve = loadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original Gas Coil PLF");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedOriginalAvailability);
  ASSERT_TRUE(loadedOriginalCurve);
  EXPECT_EQ(loadedOriginalAvailability->handle(), loadedCoil->availabilitySchedule().handle());
  ASSERT_TRUE(loadedCoil->partLoadFractionCorrelationCurve());
  EXPECT_EQ(loadedOriginalCurve->handle(), loadedCoil->partLoadFractionCorrelationCurve()->handle());

  ScheduleConstant replacementAvailability(*loadedModel);
  CurveCubic replacementCurve(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Gas Coil Availability"));
  ASSERT_TRUE(replacementCurve.setName("Replacement Gas Coil PLF"));
  ASSERT_TRUE(loadedCoil->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedCoil->setPartLoadFractionCorrelationCurve(replacementCurve));
  loadedCoil->resetPartLoadFractionCorrelationCurve();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Reloadable Gas Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Gas Coil Availability");
  auto reloadedOriginalCurve = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original Gas Coil PLF");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Gas Coil Availability");
  auto reloadedReplacementCurve = reloadedModel->getConcreteModelObjectByName<CurveCubic>("Replacement Gas Coil PLF");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedOriginalCurve);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedReplacementCurve);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedCoil->availabilitySchedule().handle());
  EXPECT_FALSE(reloadedCoil->partLoadFractionCorrelationCurve());

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

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeRejectsAirLoopDemandNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingGas coil(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto demandBranchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));
  EXPECT_FALSE(coil.addToNode(*demandBranchNode));
}

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingGas supplyCoil(model);
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  EXPECT_EQ(5u, airLoop.supplyComponents().size());
  EXPECT_FALSE(oaSystem.component(supplyCoil.handle()));

  CoilHeatingGas coil(model);
  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());

  auto inletObject = coil.inletModelObject();
  auto outletObject = coil.outletModelObject();
  ASSERT_TRUE(inletObject);
  ASSERT_TRUE(outletObject);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(inletObject->handle(), coil.inletModelObject()->handle());
  EXPECT_EQ(outletObject->handle(), coil.outletModelObject()->handle());

  auto setpointNode = coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(coil.outletModelObject()->handle(), setpointNode->handle());
  EXPECT_TRUE(coil.removeFromLoop());
  EXPECT_FALSE(coil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
}

TEST_F(EPModelFixture, CoilHeatingGas_DualDuctSetpointNodeLifecycleAcrossReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-gas-coil-dual-duct.idf");

  Model model;
  AirLoopHVAC airLoop(model, true);
  ASSERT_TRUE(airLoop.setName("Gas Coil Dual Duct Loop"));
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());

  Duct hotDeckDuct(model);
  ASSERT_TRUE(hotDeckDuct.setName("Gas Coil Hot Deck Duct"));
  ASSERT_TRUE(hotDeckDuct.addToNode(deckOutlets[0]));

  CoilHeatingGas heatingCoil(model);
  ASSERT_TRUE(heatingCoil.setName("Gas Coil Hot Deck Heating Coil"));
  ASSERT_TRUE(heatingCoil.addToNode(deckOutlets[0]));

  Duct coldDeckDuct(model);
  ASSERT_TRUE(coldDeckDuct.setName("Gas Coil Cold Deck Duct"));
  ASSERT_TRUE(coldDeckDuct.addToNode(deckOutlets[1]));

  ASSERT_TRUE(heatingCoil.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), heatingCoil.airLoopHVAC()->handle());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  auto setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
  EXPECT_EQ(deckOutlets[0].handle(), setpointNode->handle());

  auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  ASSERT_EQ(2u, branches[1].components().size());
  EXPECT_EQ(hotDeckDuct.handle(), branches[1].components().front().handle());
  EXPECT_EQ(heatingCoil.handle(), branches[1].components().back().handle());
  ASSERT_EQ(1u, branches[2].components().size());
  EXPECT_EQ(coldDeckDuct.handle(), branches[2].components().front().handle());

  EXPECT_TRUE(heatingCoil.removeFromLoop());
  EXPECT_FALSE(heatingCoil.airLoopHVAC());
  EXPECT_FALSE(heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
  EXPECT_TRUE(hotDeckDuct.airLoopHVAC());
  EXPECT_TRUE(coldDeckDuct.airLoopHVAC());
  ASSERT_EQ(1u, branches[1].components().size());
  EXPECT_EQ(hotDeckDuct.handle(), branches[1].components().front().handle());

  ASSERT_TRUE(heatingCoil.addToNode(deckOutlets[0]));
  setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Gas Coil Dual Duct Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Gas Coil Hot Deck Heating Coil");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedCoil->airLoopHVAC());
  EXPECT_EQ(loadedLoop->handle(), loadedCoil->airLoopHVAC()->handle());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  const auto loadedSetpointNode = loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(loadedSetpointNode);
  EXPECT_EQ(loadedCoil->outletModelObject()->handle(), loadedSetpointNode->handle());

  const auto loadedCoilHandle = loadedCoil->handle();
  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedCoilHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilHeatingGas_SetpointNodeFollowsOutletRewiring) {
  Model model;
  AirLoopHVAC airLoop(model);
  auto supplyInlet = airLoop.supplyInletNode();

  CoilHeatingGas heatingCoil(model);
  ASSERT_TRUE(heatingCoil.addToNode(supplyInlet));
  ASSERT_TRUE(heatingCoil.outletModelObject());
  const auto originalOutlet = heatingCoil.outletModelObject()->handle();

  Duct downstreamDuct(model);
  auto heatingCoilOutlet = heatingCoil.outletModelObject()->cast<Node>();
  ASSERT_TRUE(downstreamDuct.addToNode(heatingCoilOutlet));
  ASSERT_TRUE(heatingCoil.outletModelObject());
  EXPECT_NE(originalOutlet, heatingCoil.outletModelObject()->handle());
  auto setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());

  EXPECT_TRUE(downstreamDuct.removeFromLoop());
  ASSERT_TRUE(heatingCoil.outletModelObject());
  setpointNode = heatingCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName);
  ASSERT_TRUE(setpointNode);
  EXPECT_EQ(heatingCoil.outletModelObject()->handle(), setpointNode->handle());
}

TEST_F(EPModelFixture, CoilHeatingGas_ParentContainedCoilDoesNotReceiveDirectBranchSetpointNode) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-contained-gas-coil.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ThermalZone zone(model);
  auto availability = model.alwaysOnDiscreteSchedule();
  CoilHeatingGas reheatCoil(model);
  ASSERT_TRUE(reheatCoil.setName("Contained Gas Reheat Coil"));
  AirTerminalSingleDuctConstantVolumeReheat terminal(model, availability, reheatCoil);
  ASSERT_TRUE(terminal.setName("Gas Reheat Terminal"));

  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));
  ASSERT_TRUE(reheatCoil.inletModelObject());
  ASSERT_TRUE(reheatCoil.outletModelObject());
  EXPECT_FALSE(reheatCoil.getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<AirTerminalSingleDuctConstantVolumeReheat>("Gas Reheat Terminal");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingGas>("Contained Gas Reheat Coil");
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedCoil->inletModelObject());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));

  ASSERT_TRUE(loadedTerminal->removeFromLoop());
  EXPECT_FALSE(loadedCoil->inletModelObject());
  EXPECT_FALSE(loadedCoil->outletModelObject());
  EXPECT_FALSE(loadedCoil->getTarget(openstudio::Coil_Heating_FuelFields::TemperatureSetpointNodeName));

  openstudio::filesystem::remove(idfPath);
}
