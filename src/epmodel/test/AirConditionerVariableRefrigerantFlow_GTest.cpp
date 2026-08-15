/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Curve/CurveBicubic.hpp"
#include "../Curve/CurveBicubic_Impl.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadLinear.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow_Impl.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ModelObject/ModelObject_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idf/IdfObject_Impl.hpp>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include <array>
#include <utility>
#include <vector>

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

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlow::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), vrf.availabilitySchedule().handle());
  EXPECT_FALSE(vrf.zoneforMasterThermostatLocation());
  EXPECT_FALSE(vrf.thermostatPrioritySchedule());
  EXPECT_FALSE(vrf.basinHeaterOperatingSchedule());
  EXPECT_FALSE(vrf.coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.coolingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(vrf.coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioBoundaryCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_FALSE(vrf.coolingCombinationRatioCorrectionFactorCurve());
  EXPECT_FALSE(vrf.coolingPartLoadFractionCorrelationCurve());
  EXPECT_FALSE(vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.heatingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(vrf.heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioBoundaryCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_FALSE(vrf.heatingCombinationRatioCorrectionFactorCurve());
  EXPECT_FALSE(vrf.heatingPartLoadFractionCorrelationCurve());
  EXPECT_DOUBLE_EQ(30.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(10.0, vrf.verticalHeightusedforPipingCorrectionFactor());
  EXPECT_FALSE(vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  EXPECT_DOUBLE_EQ(-0.000386, vrf.pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(30.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_FALSE(vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());
  EXPECT_DOUBLE_EQ(0.0, vrf.pipingCorrectionFactorforHeightinHeatingModeCoefficient());
  EXPECT_DOUBLE_EQ(0.0, vrf.minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(20.0, vrf.maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_FALSE(vrf.heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_DOUBLE_EQ(0.5, vrf.initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, vrf.heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_FALSE(vrf.heatRecoveryCoolingEnergyModifierCurve());
  EXPECT_DOUBLE_EQ(1.0, vrf.initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, vrf.heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_FALSE(vrf.heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_DOUBLE_EQ(0.5, vrf.initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, vrf.heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_FALSE(vrf.heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_DOUBLE_EQ(0.5, vrf.initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, vrf.heatRecoveryHeatingEnergyTimeConstant());
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.terminals().empty());
  const auto lists = model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList);
  ASSERT_EQ(1u, lists.size());
  auto list = vrf.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  EXPECT_EQ(lists.front().handle(), list->handle());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_PipingFieldsValidateRoundtripAndResetExactly) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(41.0));
  EXPECT_TRUE(vrf.setVerticalHeightusedforPipingCorrectionFactor(-7.5));
  EXPECT_TRUE(vrf.setPipingCorrectionFactorforHeightinCoolingModeCoefficient(-0.0012));
  EXPECT_TRUE(vrf.setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(43.0));
  EXPECT_TRUE(vrf.setPipingCorrectionFactorforHeightinHeatingModeCoefficient(0.0023));
  EXPECT_DOUBLE_EQ(41.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(-7.5, vrf.verticalHeightusedforPipingCorrectionFactor());
  EXPECT_DOUBLE_EQ(-0.0012, vrf.pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(43.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_DOUBLE_EQ(0.0023, vrf.pipingCorrectionFactorforHeightinHeatingModeCoefficient());

  CurveQuadratic coolingUnivariate(model);
  CurveBiquadratic coolingBivariate(model);
  CurveQuadratic heatingUnivariate(model);
  CurveBiquadratic heatingBivariate(model);
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(coolingUnivariate));
  ASSERT_TRUE(vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  EXPECT_EQ(coolingUnivariate, *vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(coolingBivariate));
  EXPECT_EQ(coolingBivariate, *vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinHeatingModeCurve(heatingUnivariate));
  ASSERT_TRUE(vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());
  EXPECT_EQ(heatingUnivariate, *vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinHeatingModeCurve(heatingBivariate));
  EXPECT_EQ(heatingBivariate, *vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());

  CurveQuadLinear wrongType(model);
  CurveQuadratic foreignUnivariate(foreignModel);
  CurveBiquadratic foreignBivariate(foreignModel);
  EXPECT_FALSE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(wrongType));
  EXPECT_FALSE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(foreignUnivariate));
  EXPECT_FALSE(vrf.setPipingCorrectionFactorforLengthinHeatingModeCurve(wrongType));
  EXPECT_FALSE(vrf.setPipingCorrectionFactorforLengthinHeatingModeCurve(foreignBivariate));
  EXPECT_EQ(coolingBivariate, *vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  EXPECT_EQ(heatingBivariate, *vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());

  // Deliberately seed unresolved imported text that the validated public setters cannot create.
  constexpr auto malformedField = openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName;
  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(malformedField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(malformedField, "Unresolved VRF Piping Curve", false));
  EXPECT_FALSE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(foreignUnivariate));
  EXPECT_EQ("Unresolved VRF Piping Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));

  vrf.resetPipingCorrectionFactorforLengthinCoolingModeCurve();
  vrf.resetPipingCorrectionFactorforLengthinHeatingModeCurve();
  EXPECT_FALSE(vrf.pipingCorrectionFactorforLengthinCoolingModeCurve());
  EXPECT_FALSE(vrf.pipingCorrectionFactorforLengthinHeatingModeCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CanonicalizationRepairsPipingScalarsFromConcreteStorage) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-piping-scalar-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  constexpr std::array<unsigned, 5> fields = {
    openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient,
  };

  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  // Deliberately blank concrete scalar storage that validated public setters cannot produce.
  for (const auto field : fields) {
    ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
    EXPECT_FALSE(workspaceImpl->getDouble(field, false));
  }

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 5u);
  EXPECT_DOUBLE_EQ(30.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(10.0, vrf.verticalHeightusedforPipingCorrectionFactor());
  EXPECT_DOUBLE_EQ(-0.000386, vrf.pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(30.0, vrf.equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_DOUBLE_EQ(0.0, vrf.pipingCorrectionFactorforHeightinHeatingModeCoefficient());
  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  ASSERT_EQ(1u, secondReport.infoCount);
  ASSERT_EQ(1u, secondReport.messages.size());
  EXPECT_NE(std::string::npos, secondReport.messages.front().find("Sanitization complete: infos=0"));

  Model reloadSource;
  AirConditionerVariableRefrigerantFlow blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank Piping Scalars On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  // Deliberately persist blanks to exercise load canonicalization rather than a normal public mutation.
  for (const auto field : fields) {
    ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  }
  ASSERT_TRUE(reloadSource.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Blank Piping Scalars On Load");
  ASSERT_TRUE(loadedVRF);
  EXPECT_DOUBLE_EQ(30.0, loadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(10.0, loadedVRF->verticalHeightusedforPipingCorrectionFactor());
  EXPECT_DOUBLE_EQ(-0.000386, loadedVRF->pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(30.0, loadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_DOUBLE_EQ(0.0, loadedVRF->pipingCorrectionFactorforHeightinHeatingModeCoefficient());
  const auto loadedSecondReport = loadedModel->canonicalize();
  EXPECT_EQ(0u, loadedSecondReport.errorCount);
  ASSERT_EQ(1u, loadedSecondReport.infoCount);
  ASSERT_EQ(1u, loadedSecondReport.messages.size());
  EXPECT_NE(std::string::npos, loadedSecondReport.messages.front().find("Sanitization complete: infos=0"));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_PipingFieldsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-piping-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-piping-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  CurveQuadratic coolingCurve(model);
  CurveBiquadratic heatingCurve(model);
  ASSERT_TRUE(vrf.setName("Piping Field VRF"));
  ASSERT_TRUE(terminal.setName("Piping Field VRF Terminal"));
  ASSERT_TRUE(coolingCurve.setName("Original VRF Cooling Piping Curve"));
  ASSERT_TRUE(heatingCurve.setName("Original VRF Heating Piping Curve"));
  ASSERT_TRUE(vrf.addTerminal(terminal));
  ASSERT_TRUE(vrf.setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(51.0));
  ASSERT_TRUE(vrf.setVerticalHeightusedforPipingCorrectionFactor(12.5));
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforHeightinCoolingModeCoefficient(-0.004));
  ASSERT_TRUE(vrf.setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(53.0));
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforHeightinHeatingModeCoefficient(0.006));
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinCoolingModeCurve(coolingCurve));
  ASSERT_TRUE(vrf.setPipingCorrectionFactorforLengthinHeatingModeCurve(heatingCurve));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Piping Field VRF");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Piping Field VRF Terminal");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  EXPECT_DOUBLE_EQ(51.0, loadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(12.5, loadedVRF->verticalHeightusedforPipingCorrectionFactor());
  EXPECT_DOUBLE_EQ(-0.004, loadedVRF->pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(53.0, loadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_DOUBLE_EQ(0.006, loadedVRF->pipingCorrectionFactorforHeightinHeatingModeCoefficient());
  ASSERT_TRUE(loadedVRF->pipingCorrectionFactorforLengthinCoolingModeCurve());
  ASSERT_TRUE(loadedVRF->pipingCorrectionFactorforLengthinHeatingModeCurve());
  EXPECT_EQ("Original VRF Cooling Piping Curve", loadedVRF->pipingCorrectionFactorforLengthinCoolingModeCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Piping Curve", loadedVRF->pipingCorrectionFactorforLengthinHeatingModeCurve()->nameString());

  CurveBiquadratic replacementCoolingCurve(*loadedModel);
  CurveQuadratic replacementHeatingCurve(*loadedModel);
  ASSERT_TRUE(replacementCoolingCurve.setName("Replacement VRF Cooling Piping Curve"));
  ASSERT_TRUE(replacementHeatingCurve.setName("Replacement VRF Heating Piping Curve"));
  ASSERT_TRUE(loadedVRF->setEquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode(61.0));
  ASSERT_TRUE(loadedVRF->setVerticalHeightusedforPipingCorrectionFactor(-13.5));
  ASSERT_TRUE(loadedVRF->setPipingCorrectionFactorforHeightinCoolingModeCoefficient(-0.008));
  ASSERT_TRUE(loadedVRF->setEquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode(63.0));
  ASSERT_TRUE(loadedVRF->setPipingCorrectionFactorforHeightinHeatingModeCoefficient(0.009));
  ASSERT_TRUE(loadedVRF->setPipingCorrectionFactorforLengthinCoolingModeCurve(replacementCoolingCurve));
  ASSERT_TRUE(loadedVRF->setPipingCorrectionFactorforLengthinHeatingModeCurve(replacementHeatingCurve));
  loadedVRF->resetPipingCorrectionFactorforLengthinHeatingModeCurve();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVRF = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Piping Field VRF");
  auto reloadedTerminal = reloadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Piping Field VRF Terminal");
  auto originalCoolingCurve = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original VRF Cooling Piping Curve");
  auto originalHeatingCurve = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Original VRF Heating Piping Curve");
  auto reloadedReplacementCoolingCurve = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement VRF Cooling Piping Curve");
  auto resetReplacementHeatingCurve = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Replacement VRF Heating Piping Curve");
  ASSERT_TRUE(reloadedVRF);
  ASSERT_TRUE(reloadedTerminal);
  ASSERT_TRUE(originalCoolingCurve);
  ASSERT_TRUE(originalHeatingCurve);
  ASSERT_TRUE(reloadedReplacementCoolingCurve);
  ASSERT_TRUE(resetReplacementHeatingCurve);
  EXPECT_DOUBLE_EQ(61.0, reloadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode());
  EXPECT_DOUBLE_EQ(-13.5, reloadedVRF->verticalHeightusedforPipingCorrectionFactor());
  EXPECT_DOUBLE_EQ(-0.008, reloadedVRF->pipingCorrectionFactorforHeightinCoolingModeCoefficient());
  EXPECT_DOUBLE_EQ(63.0, reloadedVRF->equivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode());
  EXPECT_DOUBLE_EQ(0.009, reloadedVRF->pipingCorrectionFactorforHeightinHeatingModeCoefficient());
  ASSERT_TRUE(reloadedVRF->pipingCorrectionFactorforLengthinCoolingModeCurve());
  EXPECT_EQ(reloadedReplacementCoolingCurve->handle(), reloadedVRF->pipingCorrectionFactorforLengthinCoolingModeCurve()->handle());
  EXPECT_FALSE(reloadedVRF->pipingCorrectionFactorforLengthinHeatingModeCurve());
  ASSERT_EQ(1u, reloadedVRF->terminals().size());
  EXPECT_EQ(reloadedTerminal->handle(), reloadedVRF->terminals().front().handle());

  auto terminalList =
    reloadedVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  const auto terminalListHandle = terminalList->handle();
  const auto systemHandle = reloadedVRF->handle();
  EXPECT_FALSE(reloadedVRF->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(systemHandle));
  EXPECT_FALSE(reloadedModel->getObject(terminalListHandle));
  EXPECT_TRUE(reloadedModel->getObject(reloadedTerminal->handle()));
  EXPECT_FALSE(reloadedTerminal->vrfSystem());
  EXPECT_TRUE(reloadedModel->getObject(originalCoolingCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(originalHeatingCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementCoolingCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(resetReplacementHeatingCurve->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_HeatRecoveryFieldsValidateRoundtripAndRemainIndependent) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(vrf.setMinimumOutdoorTemperatureinHeatRecoveryMode(-7.0));
  EXPECT_TRUE(vrf.setMaximumOutdoorTemperatureinHeatRecoveryMode(31.0));
  EXPECT_TRUE(vrf.setInitialHeatRecoveryCoolingCapacityFraction(0.61));
  EXPECT_TRUE(vrf.setHeatRecoveryCoolingCapacityTimeConstant(0.17));
  EXPECT_TRUE(vrf.setInitialHeatRecoveryCoolingEnergyFraction(1.21));
  EXPECT_TRUE(vrf.setHeatRecoveryCoolingEnergyTimeConstant(0.07));
  EXPECT_TRUE(vrf.setInitialHeatRecoveryHeatingCapacityFraction(0.62));
  EXPECT_TRUE(vrf.setHeatRecoveryHeatingCapacityTimeConstant(0.18));
  EXPECT_TRUE(vrf.setInitialHeatRecoveryHeatingEnergyFraction(0.63));
  EXPECT_TRUE(vrf.setHeatRecoveryHeatingEnergyTimeConstant(0.08));
  EXPECT_TRUE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_DOUBLE_EQ(-7.0, vrf.minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(31.0, vrf.maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.61, vrf.initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.17, vrf.heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.21, vrf.initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.07, vrf.heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.62, vrf.initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.18, vrf.heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.63, vrf.initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.08, vrf.heatRecoveryHeatingEnergyTimeConstant());

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(false));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_DOUBLE_EQ(-7.0, vrf.minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(31.0, vrf.maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.61, vrf.initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.17, vrf.heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.21, vrf.initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.07, vrf.heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.62, vrf.initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.18, vrf.heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.63, vrf.initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.08, vrf.heatRecoveryHeatingEnergyTimeConstant());

  CurveBiquadratic coolingCapacityBiquadratic(model);
  CurveBiquadratic coolingEnergyBiquadratic(model);
  CurveBiquadratic heatingCapacityBiquadratic(model);
  CurveBiquadratic heatingEnergyBiquadratic(model);
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(coolingCapacityBiquadratic));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingEnergyModifierCurve(coolingEnergyBiquadratic));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingCapacityModifierCurve(heatingCapacityBiquadratic));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingEnergyModifierCurve(heatingEnergyBiquadratic));
  ASSERT_TRUE(vrf.heatRecoveryCoolingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryCoolingEnergyModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_EQ(coolingCapacityBiquadratic, *vrf.heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_EQ(coolingEnergyBiquadratic, *vrf.heatRecoveryCoolingEnergyModifierCurve());
  EXPECT_EQ(heatingCapacityBiquadratic, *vrf.heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_EQ(heatingEnergyBiquadratic, *vrf.heatRecoveryHeatingEnergyModifierCurve());

  CurveBicubic coolingCapacityBicubic(model);
  CurveBicubic coolingEnergyBicubic(model);
  CurveBicubic heatingCapacityBicubic(model);
  CurveBicubic heatingEnergyBicubic(model);
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(coolingCapacityBicubic));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingEnergyModifierCurve(coolingEnergyBicubic));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingCapacityModifierCurve(heatingCapacityBicubic));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingEnergyModifierCurve(heatingEnergyBicubic));
  ASSERT_TRUE(vrf.heatRecoveryCoolingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryCoolingEnergyModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_EQ(coolingCapacityBicubic, *vrf.heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_EQ(coolingEnergyBicubic, *vrf.heatRecoveryCoolingEnergyModifierCurve());
  EXPECT_EQ(heatingCapacityBicubic, *vrf.heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_EQ(heatingEnergyBicubic, *vrf.heatRecoveryHeatingEnergyModifierCurve());

  CurveQuadratic wrongType(model);
  CurveBiquadratic foreignBiquadratic(foreignModel);
  CurveBicubic foreignBicubic(foreignModel);
  EXPECT_FALSE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(wrongType));
  EXPECT_FALSE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(foreignBiquadratic));
  EXPECT_FALSE(vrf.setHeatRecoveryCoolingEnergyModifierCurve(wrongType));
  EXPECT_FALSE(vrf.setHeatRecoveryCoolingEnergyModifierCurve(foreignBicubic));
  EXPECT_FALSE(vrf.setHeatRecoveryHeatingCapacityModifierCurve(wrongType));
  EXPECT_FALSE(vrf.setHeatRecoveryHeatingCapacityModifierCurve(foreignBiquadratic));
  EXPECT_FALSE(vrf.setHeatRecoveryHeatingEnergyModifierCurve(wrongType));
  EXPECT_FALSE(vrf.setHeatRecoveryHeatingEnergyModifierCurve(foreignBicubic));
  ASSERT_TRUE(vrf.heatRecoveryCoolingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryCoolingEnergyModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingCapacityModifierCurve());
  ASSERT_TRUE(vrf.heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_EQ(coolingCapacityBicubic, *vrf.heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_EQ(coolingEnergyBicubic, *vrf.heatRecoveryCoolingEnergyModifierCurve());
  EXPECT_EQ(heatingCapacityBicubic, *vrf.heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_EQ(heatingEnergyBicubic, *vrf.heatRecoveryHeatingEnergyModifierCurve());

  // Deliberately seed unresolved imported text that the validated public setters cannot create.
  constexpr auto malformedField = openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName;
  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(malformedField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(malformedField, "Unresolved VRF Heat Recovery Curve", false));
  EXPECT_FALSE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(foreignBiquadratic));
  EXPECT_EQ("Unresolved VRF Heat Recovery Curve",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));

  vrf.resetHeatRecoveryCoolingCapacityModifierCurve();
  vrf.resetHeatRecoveryCoolingEnergyModifierCurve();
  vrf.resetHeatRecoveryHeatingCapacityModifierCurve();
  vrf.resetHeatRecoveryHeatingEnergyModifierCurve();
  EXPECT_FALSE(vrf.heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_FALSE(vrf.heatRecoveryCoolingEnergyModifierCurve());
  EXPECT_FALSE(vrf.heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_FALSE(vrf.heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CanonicalizationRepairsOnlyBlankHeatRecoveryScalars) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-heat-recovery-scalar-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  constexpr std::array<unsigned, 10> fields = {
    openstudio::AirConditioner_VariableRefrigerantFlowFields::MinimumCondenserInletNodeTemperatureinHeatRecoveryMode,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::MaximumCondenserInletNodeTemperatureinHeatRecoveryMode,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction,
    openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant,
  };

  Model model;
  AirConditionerVariableRefrigerantFlow blank(model);
  AirConditionerVariableRefrigerantFlow explicitValues(model);
  ASSERT_TRUE(blank.setName("Blank Heat Recovery Scalars"));
  ASSERT_TRUE(explicitValues.setName("Explicit Heat Recovery Scalars"));
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  // Deliberately blank concrete scalar storage that validated public setters cannot produce.
  for (const auto field : fields) {
    ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  }
  ASSERT_TRUE(explicitValues.setMinimumOutdoorTemperatureinHeatRecoveryMode(-8.0));
  ASSERT_TRUE(explicitValues.setMaximumOutdoorTemperatureinHeatRecoveryMode(32.0));
  ASSERT_TRUE(explicitValues.setInitialHeatRecoveryCoolingCapacityFraction(0.64));
  ASSERT_TRUE(explicitValues.setHeatRecoveryCoolingCapacityTimeConstant(0.19));
  ASSERT_TRUE(explicitValues.setInitialHeatRecoveryCoolingEnergyFraction(1.24));
  ASSERT_TRUE(explicitValues.setHeatRecoveryCoolingEnergyTimeConstant(0.09));
  ASSERT_TRUE(explicitValues.setInitialHeatRecoveryHeatingCapacityFraction(0.65));
  ASSERT_TRUE(explicitValues.setHeatRecoveryHeatingCapacityTimeConstant(0.2));
  ASSERT_TRUE(explicitValues.setInitialHeatRecoveryHeatingEnergyFraction(0.66));
  ASSERT_TRUE(explicitValues.setHeatRecoveryHeatingEnergyTimeConstant(0.1));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 10u);
  EXPECT_DOUBLE_EQ(0.0, blank.minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(20.0, blank.maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.5, blank.initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, blank.heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.0, blank.initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, blank.heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.5, blank.initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, blank.heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.5, blank.initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, blank.heatRecoveryHeatingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(-8.0, explicitValues.minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(32.0, explicitValues.maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.64, explicitValues.initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.19, explicitValues.heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.24, explicitValues.initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.09, explicitValues.heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.65, explicitValues.initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.2, explicitValues.heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.66, explicitValues.initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.1, explicitValues.heatRecoveryHeatingEnergyTimeConstant());
  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  ASSERT_EQ(1u, secondReport.infoCount);
  ASSERT_EQ(1u, secondReport.messages.size());
  EXPECT_NE(std::string::npos, secondReport.messages.front().find("Sanitization complete: infos=0"));

  Model reloadSource;
  AirConditionerVariableRefrigerantFlow blankOnLoad(reloadSource);
  AirConditionerVariableRefrigerantFlow explicitOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank Heat Recovery Scalars On Load"));
  ASSERT_TRUE(explicitOnLoad.setName("Explicit Heat Recovery Scalars On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  // Deliberately persist blanks to exercise load canonicalization rather than a normal public mutation.
  for (const auto field : fields) {
    ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  }
  ASSERT_TRUE(explicitOnLoad.setMinimumOutdoorTemperatureinHeatRecoveryMode(-9.0));
  ASSERT_TRUE(explicitOnLoad.setMaximumOutdoorTemperatureinHeatRecoveryMode(33.0));
  ASSERT_TRUE(explicitOnLoad.setInitialHeatRecoveryCoolingCapacityFraction(0.67));
  ASSERT_TRUE(explicitOnLoad.setHeatRecoveryCoolingCapacityTimeConstant(0.21));
  ASSERT_TRUE(explicitOnLoad.setInitialHeatRecoveryCoolingEnergyFraction(1.27));
  ASSERT_TRUE(explicitOnLoad.setHeatRecoveryCoolingEnergyTimeConstant(0.11));
  ASSERT_TRUE(explicitOnLoad.setInitialHeatRecoveryHeatingCapacityFraction(0.68));
  ASSERT_TRUE(explicitOnLoad.setHeatRecoveryHeatingCapacityTimeConstant(0.22));
  ASSERT_TRUE(explicitOnLoad.setInitialHeatRecoveryHeatingEnergyFraction(0.69));
  ASSERT_TRUE(explicitOnLoad.setHeatRecoveryHeatingEnergyTimeConstant(0.12));
  ASSERT_TRUE(reloadSource.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Blank Heat Recovery Scalars On Load");
  auto loadedExplicit = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Explicit Heat Recovery Scalars On Load");
  ASSERT_TRUE(loadedBlank);
  ASSERT_TRUE(loadedExplicit);
  EXPECT_DOUBLE_EQ(0.0, loadedBlank->minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(20.0, loadedBlank->maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.5, loadedBlank->initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, loadedBlank->heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.0, loadedBlank->initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, loadedBlank->heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.5, loadedBlank->initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.083, loadedBlank->heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.5, loadedBlank->initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.0, loadedBlank->heatRecoveryHeatingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(-9.0, loadedExplicit->minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(33.0, loadedExplicit->maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.67, loadedExplicit->initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.21, loadedExplicit->heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.27, loadedExplicit->initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.11, loadedExplicit->heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.68, loadedExplicit->initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.22, loadedExplicit->heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.69, loadedExplicit->initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.12, loadedExplicit->heatRecoveryHeatingEnergyTimeConstant());
  const auto loadedSecondReport = loadedModel->canonicalize();
  EXPECT_EQ(0u, loadedSecondReport.errorCount);
  ASSERT_EQ(1u, loadedSecondReport.infoCount);
  ASSERT_EQ(1u, loadedSecondReport.messages.size());
  EXPECT_NE(std::string::npos, loadedSecondReport.messages.front().find("Sanitization complete: infos=0"));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_HeatRecoveryFieldsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-heat-recovery-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-heat-recovery-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  CurveBiquadratic coolingCapacityCurve(model);
  CurveBicubic coolingEnergyCurve(model);
  CurveBiquadratic heatingCapacityCurve(model);
  CurveBicubic heatingEnergyCurve(model);
  ASSERT_TRUE(vrf.setName("Heat Recovery Field VRF"));
  ASSERT_TRUE(terminal.setName("Heat Recovery Field VRF Terminal"));
  ASSERT_TRUE(coolingCapacityCurve.setName("Original VRF Heat Recovery Cooling Capacity Curve"));
  ASSERT_TRUE(coolingEnergyCurve.setName("Original VRF Heat Recovery Cooling Energy Curve"));
  ASSERT_TRUE(heatingCapacityCurve.setName("Original VRF Heat Recovery Heating Capacity Curve"));
  ASSERT_TRUE(heatingEnergyCurve.setName("Original VRF Heat Recovery Heating Energy Curve"));
  ASSERT_TRUE(vrf.addTerminal(terminal));
  ASSERT_TRUE(vrf.setMinimumOutdoorTemperatureinHeatRecoveryMode(-11.0));
  ASSERT_TRUE(vrf.setMaximumOutdoorTemperatureinHeatRecoveryMode(34.0));
  ASSERT_TRUE(vrf.setInitialHeatRecoveryCoolingCapacityFraction(0.71));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingCapacityTimeConstant(0.23));
  ASSERT_TRUE(vrf.setInitialHeatRecoveryCoolingEnergyFraction(1.31));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingEnergyTimeConstant(0.13));
  ASSERT_TRUE(vrf.setInitialHeatRecoveryHeatingCapacityFraction(0.72));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingCapacityTimeConstant(0.24));
  ASSERT_TRUE(vrf.setInitialHeatRecoveryHeatingEnergyFraction(0.73));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingEnergyTimeConstant(0.14));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingCapacityModifierCurve(coolingCapacityCurve));
  ASSERT_TRUE(vrf.setHeatRecoveryCoolingEnergyModifierCurve(coolingEnergyCurve));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingCapacityModifierCurve(heatingCapacityCurve));
  ASSERT_TRUE(vrf.setHeatRecoveryHeatingEnergyModifierCurve(heatingEnergyCurve));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Heat Recovery Field VRF");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Heat Recovery Field VRF Terminal");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  EXPECT_DOUBLE_EQ(-11.0, loadedVRF->minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(34.0, loadedVRF->maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.71, loadedVRF->initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.23, loadedVRF->heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.31, loadedVRF->initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.13, loadedVRF->heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.72, loadedVRF->initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.24, loadedVRF->heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.73, loadedVRF->initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.14, loadedVRF->heatRecoveryHeatingEnergyTimeConstant());
  ASSERT_TRUE(loadedVRF->heatRecoveryCoolingCapacityModifierCurve());
  ASSERT_TRUE(loadedVRF->heatRecoveryCoolingEnergyModifierCurve());
  ASSERT_TRUE(loadedVRF->heatRecoveryHeatingCapacityModifierCurve());
  ASSERT_TRUE(loadedVRF->heatRecoveryHeatingEnergyModifierCurve());
  EXPECT_EQ("Original VRF Heat Recovery Cooling Capacity Curve", loadedVRF->heatRecoveryCoolingCapacityModifierCurve()->nameString());
  EXPECT_EQ("Original VRF Heat Recovery Cooling Energy Curve", loadedVRF->heatRecoveryCoolingEnergyModifierCurve()->nameString());
  EXPECT_EQ("Original VRF Heat Recovery Heating Capacity Curve", loadedVRF->heatRecoveryHeatingCapacityModifierCurve()->nameString());
  EXPECT_EQ("Original VRF Heat Recovery Heating Energy Curve", loadedVRF->heatRecoveryHeatingEnergyModifierCurve()->nameString());

  CurveBicubic replacementCoolingCapacityCurve(*loadedModel);
  CurveBiquadratic replacementCoolingEnergyCurve(*loadedModel);
  CurveBicubic replacementHeatingCapacityCurve(*loadedModel);
  CurveBiquadratic replacementHeatingEnergyCurve(*loadedModel);
  ASSERT_TRUE(replacementCoolingCapacityCurve.setName("Replacement VRF Heat Recovery Cooling Capacity Curve"));
  ASSERT_TRUE(replacementCoolingEnergyCurve.setName("Replacement VRF Heat Recovery Cooling Energy Curve"));
  ASSERT_TRUE(replacementHeatingCapacityCurve.setName("Replacement VRF Heat Recovery Heating Capacity Curve"));
  ASSERT_TRUE(replacementHeatingEnergyCurve.setName("Replacement VRF Heat Recovery Heating Energy Curve"));
  ASSERT_TRUE(loadedVRF->setMinimumOutdoorTemperatureinHeatRecoveryMode(-12.0));
  ASSERT_TRUE(loadedVRF->setMaximumOutdoorTemperatureinHeatRecoveryMode(35.0));
  ASSERT_TRUE(loadedVRF->setInitialHeatRecoveryCoolingCapacityFraction(0.74));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryCoolingCapacityTimeConstant(0.25));
  ASSERT_TRUE(loadedVRF->setInitialHeatRecoveryCoolingEnergyFraction(1.34));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryCoolingEnergyTimeConstant(0.15));
  ASSERT_TRUE(loadedVRF->setInitialHeatRecoveryHeatingCapacityFraction(0.75));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryHeatingCapacityTimeConstant(0.26));
  ASSERT_TRUE(loadedVRF->setInitialHeatRecoveryHeatingEnergyFraction(0.76));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryHeatingEnergyTimeConstant(0.16));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryCoolingCapacityModifierCurve(replacementCoolingCapacityCurve));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryCoolingEnergyModifierCurve(replacementCoolingEnergyCurve));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryHeatingCapacityModifierCurve(replacementHeatingCapacityCurve));
  ASSERT_TRUE(loadedVRF->setHeatRecoveryHeatingEnergyModifierCurve(replacementHeatingEnergyCurve));
  loadedVRF->resetHeatRecoveryCoolingEnergyModifierCurve();
  loadedVRF->resetHeatRecoveryHeatingEnergyModifierCurve();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVRF = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Heat Recovery Field VRF");
  auto reloadedTerminal =
    reloadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Heat Recovery Field VRF Terminal");
  auto originalCoolingCapacityCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Original VRF Heat Recovery Cooling Capacity Curve");
  auto originalCoolingEnergyCurve = reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Original VRF Heat Recovery Cooling Energy Curve");
  auto originalHeatingCapacityCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Original VRF Heat Recovery Heating Capacity Curve");
  auto originalHeatingEnergyCurve = reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Original VRF Heat Recovery Heating Energy Curve");
  auto reloadedReplacementCoolingCapacityCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Replacement VRF Heat Recovery Cooling Capacity Curve");
  auto resetReplacementCoolingEnergyCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement VRF Heat Recovery Cooling Energy Curve");
  auto reloadedReplacementHeatingCapacityCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Replacement VRF Heat Recovery Heating Capacity Curve");
  auto resetReplacementHeatingEnergyCurve =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement VRF Heat Recovery Heating Energy Curve");
  ASSERT_TRUE(reloadedVRF);
  ASSERT_TRUE(reloadedTerminal);
  ASSERT_TRUE(originalCoolingCapacityCurve);
  ASSERT_TRUE(originalCoolingEnergyCurve);
  ASSERT_TRUE(originalHeatingCapacityCurve);
  ASSERT_TRUE(originalHeatingEnergyCurve);
  ASSERT_TRUE(reloadedReplacementCoolingCapacityCurve);
  ASSERT_TRUE(resetReplacementCoolingEnergyCurve);
  ASSERT_TRUE(reloadedReplacementHeatingCapacityCurve);
  ASSERT_TRUE(resetReplacementHeatingEnergyCurve);
  EXPECT_DOUBLE_EQ(-12.0, reloadedVRF->minimumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(35.0, reloadedVRF->maximumOutdoorTemperatureinHeatRecoveryMode());
  EXPECT_DOUBLE_EQ(0.74, reloadedVRF->initialHeatRecoveryCoolingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.25, reloadedVRF->heatRecoveryCoolingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(1.34, reloadedVRF->initialHeatRecoveryCoolingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.15, reloadedVRF->heatRecoveryCoolingEnergyTimeConstant());
  EXPECT_DOUBLE_EQ(0.75, reloadedVRF->initialHeatRecoveryHeatingCapacityFraction());
  EXPECT_DOUBLE_EQ(0.26, reloadedVRF->heatRecoveryHeatingCapacityTimeConstant());
  EXPECT_DOUBLE_EQ(0.76, reloadedVRF->initialHeatRecoveryHeatingEnergyFraction());
  EXPECT_DOUBLE_EQ(0.16, reloadedVRF->heatRecoveryHeatingEnergyTimeConstant());
  ASSERT_TRUE(reloadedVRF->heatRecoveryCoolingCapacityModifierCurve());
  EXPECT_EQ(reloadedReplacementCoolingCapacityCurve->handle(), reloadedVRF->heatRecoveryCoolingCapacityModifierCurve()->handle());
  EXPECT_FALSE(reloadedVRF->heatRecoveryCoolingEnergyModifierCurve());
  ASSERT_TRUE(reloadedVRF->heatRecoveryHeatingCapacityModifierCurve());
  EXPECT_EQ(reloadedReplacementHeatingCapacityCurve->handle(), reloadedVRF->heatRecoveryHeatingCapacityModifierCurve()->handle());
  EXPECT_FALSE(reloadedVRF->heatRecoveryHeatingEnergyModifierCurve());
  ASSERT_EQ(1u, reloadedVRF->terminals().size());
  EXPECT_EQ(reloadedTerminal->handle(), reloadedVRF->terminals().front().handle());

  auto terminalList =
    reloadedVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  const auto terminalListHandle = terminalList->handle();
  const auto systemHandle = reloadedVRF->handle();
  EXPECT_FALSE(reloadedVRF->remove().empty());
  EXPECT_FALSE(reloadedModel->getObject(systemHandle));
  EXPECT_FALSE(reloadedModel->getObject(terminalListHandle));
  EXPECT_TRUE(reloadedModel->getObject(reloadedTerminal->handle()));
  EXPECT_FALSE(reloadedTerminal->vrfSystem());
  EXPECT_TRUE(reloadedModel->getObject(originalCoolingCapacityCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(originalCoolingEnergyCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(originalHeatingCapacityCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(originalHeatingEnergyCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementCoolingCapacityCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(resetReplacementCoolingEnergyCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementHeatingCapacityCurve->handle()));
  EXPECT_TRUE(reloadedModel->getObject(resetReplacementHeatingEnergyCurve->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CoolingCurveRelationshipsValidateAndResetExactly) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);

  CurveBiquadratic capacityLow(model);
  CurveQuadratic capacityBoundary(model);
  CurveBicubic capacityHigh(model);
  CurveBiquadratic energyLow(model);
  CurveQuadratic energyBoundary(model);
  CurveBicubic energyHigh(model);
  CurveQuadratic energyLowPartLoad(model);
  CurveQuadratic energyHighPartLoad(model);
  CurveQuadratic combinationRatio(model);
  CurveQuadratic partLoadFraction(model);

  ASSERT_TRUE(vrf.setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityLow));
  ASSERT_TRUE(vrf.setCoolingCapacityRatioBoundaryCurve(capacityBoundary));
  ASSERT_TRUE(vrf.setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(capacityHigh));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(energyLow));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioBoundaryCurve(energyBoundary));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(energyHigh));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(energyLowPartLoad));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(energyHighPartLoad));
  ASSERT_TRUE(vrf.setCoolingCombinationRatioCorrectionFactorCurve(combinationRatio));
  ASSERT_TRUE(vrf.setCoolingPartLoadFractionCorrelationCurve(partLoadFraction));

  ASSERT_TRUE(vrf.coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(vrf.coolingCapacityRatioBoundaryCurve());
  ASSERT_TRUE(vrf.coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(vrf.coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(vrf.coolingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(vrf.coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(vrf.coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(vrf.coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(vrf.coolingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(vrf.coolingPartLoadFractionCorrelationCurve());
  EXPECT_EQ(capacityLow, *vrf.coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(capacityBoundary, *vrf.coolingCapacityRatioBoundaryCurve());
  EXPECT_EQ(capacityHigh, *vrf.coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_EQ(energyLow, *vrf.coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(energyBoundary, *vrf.coolingEnergyInputRatioBoundaryCurve());
  EXPECT_EQ(energyHigh, *vrf.coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_EQ(energyLowPartLoad, *vrf.coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_EQ(energyHighPartLoad, *vrf.coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_EQ(combinationRatio, *vrf.coolingCombinationRatioCorrectionFactorCurve());
  EXPECT_EQ(partLoadFraction, *vrf.coolingPartLoadFractionCorrelationCurve());

  CurveBiquadratic foreignBivariate(foreignModel);
  CurveQuadratic foreignUnivariate(foreignModel);
  EXPECT_FALSE(vrf.setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityBoundary));
  EXPECT_FALSE(vrf.setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(foreignBivariate));
  EXPECT_FALSE(vrf.setCoolingCapacityRatioBoundaryCurve(capacityLow));
  EXPECT_FALSE(vrf.setCoolingCapacityRatioBoundaryCurve(foreignUnivariate));
  EXPECT_EQ(capacityLow, *vrf.coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(capacityBoundary, *vrf.coolingCapacityRatioBoundaryCurve());

  // Deliberately seed unresolved imported text that the validated public setters cannot create.
  constexpr auto malformedField =
    openstudio::AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName;
  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(malformedField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(malformedField, "Unresolved VRF Cooling Curve", false));
  EXPECT_FALSE(vrf.setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(foreignBivariate));
  EXPECT_EQ("Unresolved VRF Cooling Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));

  vrf.resetCoolingCapacityRatioModifierFunctionofLowTemperatureCurve();
  vrf.resetCoolingCapacityRatioBoundaryCurve();
  vrf.resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve();
  vrf.resetCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  vrf.resetCoolingEnergyInputRatioBoundaryCurve();
  vrf.resetCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  vrf.resetCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  vrf.resetCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  vrf.resetCoolingCombinationRatioCorrectionFactorCurve();
  vrf.resetCoolingPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(vrf.coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.coolingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(vrf.coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioBoundaryCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_FALSE(vrf.coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_FALSE(vrf.coolingCombinationRatioCorrectionFactorCurve());
  EXPECT_FALSE(vrf.coolingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CoolingCurvesSurviveReloadReplacementResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-cooling-curves-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-cooling-curves-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(vrf.setName("Cooling Curve VRF"));
  ASSERT_TRUE(terminal.setName("Cooling Curve VRF Terminal"));
  ASSERT_TRUE(vrf.addTerminal(terminal));

  CurveBiquadratic capacityLow(model);
  CurveQuadratic capacityBoundary(model);
  CurveBicubic capacityHigh(model);
  CurveBiquadratic energyLow(model);
  CurveQuadratic energyBoundary(model);
  CurveBicubic energyHigh(model);
  CurveQuadratic energyLowPartLoad(model);
  CurveQuadratic energyHighPartLoad(model);
  CurveQuadratic combinationRatio(model);
  CurveQuadratic partLoadFraction(model);
  ASSERT_TRUE(capacityLow.setName("Original VRF Cooling Capacity Low Temperature"));
  ASSERT_TRUE(capacityBoundary.setName("Original VRF Cooling Capacity Boundary"));
  ASSERT_TRUE(capacityHigh.setName("Original VRF Cooling Capacity High Temperature"));
  ASSERT_TRUE(energyLow.setName("Original VRF Cooling EIR Low Temperature"));
  ASSERT_TRUE(energyBoundary.setName("Original VRF Cooling EIR Boundary"));
  ASSERT_TRUE(energyHigh.setName("Original VRF Cooling EIR High Temperature"));
  ASSERT_TRUE(energyLowPartLoad.setName("Original VRF Cooling EIR Low Part Load"));
  ASSERT_TRUE(energyHighPartLoad.setName("Original VRF Cooling EIR High Part Load"));
  ASSERT_TRUE(combinationRatio.setName("Original VRF Cooling Combination Ratio"));
  ASSERT_TRUE(partLoadFraction.setName("Original VRF Cooling Part Load Fraction"));
  ASSERT_TRUE(vrf.setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityLow));
  ASSERT_TRUE(vrf.setCoolingCapacityRatioBoundaryCurve(capacityBoundary));
  ASSERT_TRUE(vrf.setCoolingCapacityRatioModifierFunctionofHighTemperatureCurve(capacityHigh));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofLowTemperatureCurve(energyLow));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioBoundaryCurve(energyBoundary));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofHighTemperatureCurve(energyHigh));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(energyLowPartLoad));
  ASSERT_TRUE(vrf.setCoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(energyHighPartLoad));
  ASSERT_TRUE(vrf.setCoolingCombinationRatioCorrectionFactorCurve(combinationRatio));
  ASSERT_TRUE(vrf.setCoolingPartLoadFractionCorrelationCurve(partLoadFraction));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Cooling Curve VRF");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Cooling Curve VRF Terminal");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedVRF->coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(loadedVRF->coolingCapacityRatioBoundaryCurve());
  ASSERT_TRUE(loadedVRF->coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(loadedVRF->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(loadedVRF->coolingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(loadedVRF->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(loadedVRF->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(loadedVRF->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(loadedVRF->coolingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(loadedVRF->coolingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("Original VRF Cooling Capacity Low Temperature", loadedVRF->coolingCapacityRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Capacity Boundary", loadedVRF->coolingCapacityRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Capacity High Temperature", loadedVRF->coolingCapacityRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR Low Temperature", loadedVRF->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR Boundary", loadedVRF->coolingEnergyInputRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR High Temperature", loadedVRF->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR Low Part Load", loadedVRF->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR High Part Load", loadedVRF->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Combination Ratio", loadedVRF->coolingCombinationRatioCorrectionFactorCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Part Load Fraction", loadedVRF->coolingPartLoadFractionCorrelationCurve()->nameString());

  CurveBiquadratic replacementBivariate(*loadedModel);
  CurveQuadratic replacementUnivariate(*loadedModel);
  ASSERT_TRUE(replacementBivariate.setName("Replacement VRF Cooling Bivariate"));
  ASSERT_TRUE(replacementUnivariate.setName("Replacement VRF Cooling Univariate"));
  ASSERT_TRUE(loadedVRF->setCoolingCapacityRatioModifierFunctionofLowTemperatureCurve(replacementBivariate));
  ASSERT_TRUE(loadedVRF->setCoolingCapacityRatioBoundaryCurve(replacementUnivariate));
  loadedVRF->resetCoolingCapacityRatioModifierFunctionofHighTemperatureCurve();
  loadedVRF->resetCoolingEnergyInputRatioBoundaryCurve();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVRF = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Cooling Curve VRF");
  auto reloadedTerminal = reloadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Cooling Curve VRF Terminal");
  auto resetCapacityHigh = reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Original VRF Cooling Capacity High Temperature");
  auto resetEnergyBoundary = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original VRF Cooling EIR Boundary");
  ASSERT_TRUE(reloadedVRF);
  ASSERT_TRUE(reloadedTerminal);
  ASSERT_TRUE(resetCapacityHigh);
  ASSERT_TRUE(resetEnergyBoundary);
  ASSERT_TRUE(reloadedVRF->coolingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->coolingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(reloadedVRF->coolingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(reloadedVRF->coolingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(reloadedVRF->coolingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(reloadedVRF->coolingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("Replacement VRF Cooling Bivariate", reloadedVRF->coolingCapacityRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Replacement VRF Cooling Univariate", reloadedVRF->coolingCapacityRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR Low Temperature", reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR High Temperature", reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR Low Part Load", reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling EIR High Part Load", reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Combination Ratio", reloadedVRF->coolingCombinationRatioCorrectionFactorCurve()->nameString());
  EXPECT_EQ("Original VRF Cooling Part Load Fraction", reloadedVRF->coolingPartLoadFractionCorrelationCurve()->nameString());

  const std::vector<openstudio::Handle> attachedCurveHandles = {
    reloadedVRF->coolingCapacityRatioModifierFunctionofLowTemperatureCurve()->handle(),
    reloadedVRF->coolingCapacityRatioBoundaryCurve()->handle(),
    reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->handle(),
    reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->handle(),
    reloadedVRF->coolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->handle(),
    reloadedVRF->coolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->handle(),
    reloadedVRF->coolingCombinationRatioCorrectionFactorCurve()->handle(),
    reloadedVRF->coolingPartLoadFractionCorrelationCurve()->handle(),
  };
  auto terminalList =
    reloadedVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  EXPECT_FALSE(reloadedVRF->remove().empty());
  for (const auto& handle : attachedCurveHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
  EXPECT_TRUE(reloadedModel->getObject(resetCapacityHigh->handle()));
  EXPECT_TRUE(reloadedModel->getObject(resetEnergyBoundary->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedTerminal->handle()));
  EXPECT_FALSE(reloadedTerminal->vrfSystem());
  EXPECT_FALSE(reloadedModel->getObject(terminalList->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_HeatingCurveRelationshipsValidateAndResetExactly) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);

  CurveBiquadratic capacityLow(model);
  CurveQuadratic capacityBoundary(model);
  CurveBicubic capacityHigh(model);
  CurveBiquadratic energyLow(model);
  CurveQuadratic energyBoundary(model);
  CurveBicubic energyHigh(model);
  CurveQuadratic energyLowPartLoad(model);
  CurveQuadratic energyHighPartLoad(model);
  CurveQuadratic combinationRatio(model);
  CurveQuadratic partLoadFraction(model);

  ASSERT_TRUE(vrf.setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityLow));
  ASSERT_TRUE(vrf.setHeatingCapacityRatioBoundaryCurve(capacityBoundary));
  ASSERT_TRUE(vrf.setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(capacityHigh));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(energyLow));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioBoundaryCurve(energyBoundary));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(energyHigh));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(energyLowPartLoad));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(energyHighPartLoad));
  ASSERT_TRUE(vrf.setHeatingCombinationRatioCorrectionFactorCurve(combinationRatio));
  ASSERT_TRUE(vrf.setHeatingPartLoadFractionCorrelationCurve(partLoadFraction));

  ASSERT_TRUE(vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(vrf.heatingCapacityRatioBoundaryCurve());
  ASSERT_TRUE(vrf.heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(vrf.heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(vrf.heatingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(vrf.heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(vrf.heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(vrf.heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(vrf.heatingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(vrf.heatingPartLoadFractionCorrelationCurve());
  EXPECT_EQ(capacityLow, *vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(capacityBoundary, *vrf.heatingCapacityRatioBoundaryCurve());
  EXPECT_EQ(capacityHigh, *vrf.heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_EQ(energyLow, *vrf.heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(energyBoundary, *vrf.heatingEnergyInputRatioBoundaryCurve());
  EXPECT_EQ(energyHigh, *vrf.heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_EQ(energyLowPartLoad, *vrf.heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_EQ(energyHighPartLoad, *vrf.heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_EQ(combinationRatio, *vrf.heatingCombinationRatioCorrectionFactorCurve());
  EXPECT_EQ(partLoadFraction, *vrf.heatingPartLoadFractionCorrelationCurve());

  ASSERT_TRUE(vrf.setHeatingPerformanceCurveOutdoorTemperatureType("DryBulbTemperature"));
  EXPECT_EQ(capacityLow.handle(), vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve()->handle());
  EXPECT_EQ(capacityBoundary.handle(), vrf.heatingCapacityRatioBoundaryCurve()->handle());
  EXPECT_EQ(capacityHigh.handle(), vrf.heatingCapacityRatioModifierFunctionofHighTemperatureCurve()->handle());
  EXPECT_EQ(energyLow.handle(), vrf.heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->handle());
  EXPECT_EQ(energyBoundary.handle(), vrf.heatingEnergyInputRatioBoundaryCurve()->handle());
  EXPECT_EQ(energyHigh.handle(), vrf.heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->handle());
  EXPECT_EQ(energyLowPartLoad.handle(), vrf.heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->handle());
  EXPECT_EQ(energyHighPartLoad.handle(), vrf.heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->handle());
  EXPECT_EQ(combinationRatio.handle(), vrf.heatingCombinationRatioCorrectionFactorCurve()->handle());
  EXPECT_EQ(partLoadFraction.handle(), vrf.heatingPartLoadFractionCorrelationCurve()->handle());

  CurveBiquadratic foreignBivariate(foreignModel);
  CurveQuadratic foreignUnivariate(foreignModel);
  EXPECT_FALSE(vrf.setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityBoundary));
  EXPECT_FALSE(vrf.setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(foreignBivariate));
  EXPECT_FALSE(vrf.setHeatingCapacityRatioBoundaryCurve(capacityLow));
  EXPECT_FALSE(vrf.setHeatingCapacityRatioBoundaryCurve(foreignUnivariate));
  EXPECT_EQ(capacityLow, *vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_EQ(capacityBoundary, *vrf.heatingCapacityRatioBoundaryCurve());

  // Deliberately seed unresolved imported text that the validated public setters cannot create.
  constexpr auto malformedField =
    openstudio::AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName;
  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(malformedField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(malformedField, "Unresolved VRF Heating Curve", false));
  EXPECT_FALSE(vrf.setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(foreignBivariate));
  EXPECT_EQ("Unresolved VRF Heating Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));

  vrf.resetHeatingCapacityRatioModifierFunctionofLowTemperatureCurve();
  vrf.resetHeatingCapacityRatioBoundaryCurve();
  vrf.resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve();
  vrf.resetHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve();
  vrf.resetHeatingEnergyInputRatioBoundaryCurve();
  vrf.resetHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve();
  vrf.resetHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve();
  vrf.resetHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve();
  vrf.resetHeatingCombinationRatioCorrectionFactorCurve();
  vrf.resetHeatingPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(vrf.heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.heatingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(vrf.heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioBoundaryCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  EXPECT_FALSE(vrf.heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  EXPECT_FALSE(vrf.heatingCombinationRatioCorrectionFactorCurve());
  EXPECT_FALSE(vrf.heatingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(malformedField, false, true).value_or(""));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_HeatingCurvesSurviveReloadReplacementResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-heating-curves-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-heating-curves-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(vrf.setName("Heating Curve VRF"));
  ASSERT_TRUE(terminal.setName("Heating Curve VRF Terminal"));
  ASSERT_TRUE(vrf.addTerminal(terminal));

  CurveBiquadratic capacityLow(model);
  CurveQuadratic capacityBoundary(model);
  CurveBicubic capacityHigh(model);
  CurveBiquadratic energyLow(model);
  CurveQuadratic energyBoundary(model);
  CurveBicubic energyHigh(model);
  CurveQuadratic energyLowPartLoad(model);
  CurveQuadratic energyHighPartLoad(model);
  CurveQuadratic combinationRatio(model);
  CurveQuadratic partLoadFraction(model);
  ASSERT_TRUE(capacityLow.setName("Original VRF Heating Capacity Low Temperature"));
  ASSERT_TRUE(capacityBoundary.setName("Original VRF Heating Capacity Boundary"));
  ASSERT_TRUE(capacityHigh.setName("Original VRF Heating Capacity High Temperature"));
  ASSERT_TRUE(energyLow.setName("Original VRF Heating EIR Low Temperature"));
  ASSERT_TRUE(energyBoundary.setName("Original VRF Heating EIR Boundary"));
  ASSERT_TRUE(energyHigh.setName("Original VRF Heating EIR High Temperature"));
  ASSERT_TRUE(energyLowPartLoad.setName("Original VRF Heating EIR Low Part Load"));
  ASSERT_TRUE(energyHighPartLoad.setName("Original VRF Heating EIR High Part Load"));
  ASSERT_TRUE(combinationRatio.setName("Original VRF Heating Combination Ratio"));
  ASSERT_TRUE(partLoadFraction.setName("Original VRF Heating Part Load Fraction"));
  ASSERT_TRUE(vrf.setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(capacityLow));
  ASSERT_TRUE(vrf.setHeatingCapacityRatioBoundaryCurve(capacityBoundary));
  ASSERT_TRUE(vrf.setHeatingCapacityRatioModifierFunctionofHighTemperatureCurve(capacityHigh));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofLowTemperatureCurve(energyLow));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioBoundaryCurve(energyBoundary));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofHighTemperatureCurve(energyHigh));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve(energyLowPartLoad));
  ASSERT_TRUE(vrf.setHeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve(energyHighPartLoad));
  ASSERT_TRUE(vrf.setHeatingCombinationRatioCorrectionFactorCurve(combinationRatio));
  ASSERT_TRUE(vrf.setHeatingPartLoadFractionCorrelationCurve(partLoadFraction));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Heating Curve VRF");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Heating Curve VRF Terminal");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedVRF->heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(loadedVRF->heatingCapacityRatioBoundaryCurve());
  ASSERT_TRUE(loadedVRF->heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(loadedVRF->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(loadedVRF->heatingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(loadedVRF->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(loadedVRF->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(loadedVRF->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(loadedVRF->heatingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(loadedVRF->heatingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("Original VRF Heating Capacity Low Temperature", loadedVRF->heatingCapacityRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Capacity Boundary", loadedVRF->heatingCapacityRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Capacity High Temperature", loadedVRF->heatingCapacityRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR Low Temperature", loadedVRF->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR Boundary", loadedVRF->heatingEnergyInputRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR High Temperature", loadedVRF->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR Low Part Load", loadedVRF->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR High Part Load", loadedVRF->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Combination Ratio", loadedVRF->heatingCombinationRatioCorrectionFactorCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Part Load Fraction", loadedVRF->heatingPartLoadFractionCorrelationCurve()->nameString());

  CurveBiquadratic replacementBivariate(*loadedModel);
  CurveQuadratic replacementUnivariate(*loadedModel);
  ASSERT_TRUE(replacementBivariate.setName("Replacement VRF Heating Bivariate"));
  ASSERT_TRUE(replacementUnivariate.setName("Replacement VRF Heating Univariate"));
  ASSERT_TRUE(loadedVRF->setHeatingCapacityRatioModifierFunctionofLowTemperatureCurve(replacementBivariate));
  ASSERT_TRUE(loadedVRF->setHeatingCapacityRatioBoundaryCurve(replacementUnivariate));
  loadedVRF->resetHeatingCapacityRatioModifierFunctionofHighTemperatureCurve();
  loadedVRF->resetHeatingEnergyInputRatioBoundaryCurve();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVRF = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Heating Curve VRF");
  auto reloadedTerminal = reloadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Heating Curve VRF Terminal");
  auto resetCapacityHigh = reloadedModel->getConcreteModelObjectByName<CurveBicubic>("Original VRF Heating Capacity High Temperature");
  auto resetEnergyBoundary = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Original VRF Heating EIR Boundary");
  ASSERT_TRUE(reloadedVRF);
  ASSERT_TRUE(reloadedTerminal);
  ASSERT_TRUE(resetCapacityHigh);
  ASSERT_TRUE(resetEnergyBoundary);
  ASSERT_TRUE(reloadedVRF->heatingCapacityRatioModifierFunctionofLowTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->heatingCapacityRatioBoundaryCurve());
  EXPECT_FALSE(reloadedVRF->heatingCapacityRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve());
  EXPECT_FALSE(reloadedVRF->heatingEnergyInputRatioBoundaryCurve());
  ASSERT_TRUE(reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve());
  ASSERT_TRUE(reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve());
  ASSERT_TRUE(reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve());
  ASSERT_TRUE(reloadedVRF->heatingCombinationRatioCorrectionFactorCurve());
  ASSERT_TRUE(reloadedVRF->heatingPartLoadFractionCorrelationCurve());
  EXPECT_EQ("Replacement VRF Heating Bivariate", reloadedVRF->heatingCapacityRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Replacement VRF Heating Univariate", reloadedVRF->heatingCapacityRatioBoundaryCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR Low Temperature", reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR High Temperature", reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR Low Part Load", reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Heating EIR High Part Load", reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Combination Ratio", reloadedVRF->heatingCombinationRatioCorrectionFactorCurve()->nameString());
  EXPECT_EQ("Original VRF Heating Part Load Fraction", reloadedVRF->heatingPartLoadFractionCorrelationCurve()->nameString());

  const std::vector<openstudio::Handle> attachedCurveHandles = {
    reloadedVRF->heatingCapacityRatioModifierFunctionofLowTemperatureCurve()->handle(),
    reloadedVRF->heatingCapacityRatioBoundaryCurve()->handle(),
    reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowTemperatureCurve()->handle(),
    reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighTemperatureCurve()->handle(),
    reloadedVRF->heatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurve()->handle(),
    reloadedVRF->heatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurve()->handle(),
    reloadedVRF->heatingCombinationRatioCorrectionFactorCurve()->handle(),
    reloadedVRF->heatingPartLoadFractionCorrelationCurve()->handle(),
  };
  auto terminalList =
    reloadedVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  EXPECT_FALSE(reloadedVRF->remove().empty());
  for (const auto& handle : attachedCurveHandles) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
  EXPECT_TRUE(reloadedModel->getObject(resetCapacityHigh->handle()));
  EXPECT_TRUE(reloadedModel->getObject(resetEnergyBoundary->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedTerminal->handle()));
  EXPECT_FALSE(reloadedTerminal->vrfSystem());
  EXPECT_FALSE(reloadedModel->getObject(terminalList->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefrostEIRModifierCurve) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-defrost-eir-curve");
  const ScopedFileRemoval removeIdf(idfPath);
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow vrf(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  CurveBiquadratic initialCurve(model);
  CurveBiquadratic replacementCurve(model);
  CurveBicubic alternateAllowedCurve(model);
  CurveQuadratic disallowedCurve(model);
  CurveBiquadratic foreignCurve(foreignModel);
  ASSERT_TRUE(vrf.setName("Standard VRF Defrost EIR"));
  ASSERT_TRUE(terminal.setName("Standard VRF Defrost EIR Terminal"));
  ASSERT_TRUE(initialCurve.setName("Standard VRF Initial Defrost EIR"));
  ASSERT_TRUE(replacementCurve.setName("Standard VRF Replacement Defrost EIR"));
  ASSERT_TRUE(alternateAllowedCurve.setName("Standard VRF Alternate Defrost EIR"));
  ASSERT_TRUE(vrf.addTerminal(terminal));

  constexpr unsigned field = openstudio::AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName;
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(initialCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(initialCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(alternateAllowedCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(alternateAllowedCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_FALSE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(disallowedCurve));
  EXPECT_FALSE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(foreignCurve));
  ASSERT_TRUE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(alternateAllowedCurve, *vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());

  auto workspaceImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, "Unresolved Standard VRF Defrost EIR", false));
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  vrf.resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  EXPECT_FALSE(vrf.defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ("", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  ASSERT_TRUE(vrf.setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(initialCurve));
  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVRF = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Standard VRF Defrost EIR Terminal");
  auto loadedInitialCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Initial Defrost EIR");
  auto loadedReplacementCurve = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Replacement Defrost EIR");
  ASSERT_TRUE(loadedVRF);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedInitialCurve);
  ASSERT_TRUE(loadedReplacementCurve);
  ASSERT_TRUE(loadedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(*loadedInitialCurve, *loadedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  ASSERT_TRUE(loadedVRF->setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(*loadedReplacementCurve));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto replacedModel = Model::load(idfPath);
  ASSERT_TRUE(replacedModel);
  auto replacedVRF = replacedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto replacedCurve = replacedModel->getConcreteModelObjectByName<CurveBiquadratic>("Standard VRF Replacement Defrost EIR");
  ASSERT_TRUE(replacedVRF);
  ASSERT_TRUE(replacedCurve);
  ASSERT_TRUE(replacedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  EXPECT_EQ(*replacedCurve, *replacedVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  replacedVRF->resetDefrostEnergyInputRatioModifierFunctionofTemperatureCurve();
  ASSERT_TRUE(replacedModel->save(idfPath, true));

  auto resetModel = Model::load(idfPath);
  ASSERT_TRUE(resetModel);
  auto resetVRF = resetModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Standard VRF Defrost EIR");
  auto resetTerminal = resetModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Standard VRF Defrost EIR Terminal");
  ASSERT_TRUE(resetVRF);
  ASSERT_TRUE(resetTerminal);
  EXPECT_FALSE(resetVRF->defrostEnergyInputRatioModifierFunctionofTemperatureCurve());
  ASSERT_EQ(1u, resetVRF->terminals().size());
  EXPECT_EQ(*resetTerminal, resetVRF->terminals().front());
  auto terminalList = resetVRF->getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(terminalList);
  CurveBiquadratic retainedCurve(*resetModel);
  ASSERT_TRUE(resetVRF->setDefrostEnergyInputRatioModifierFunctionofTemperatureCurve(retainedCurve));
  EXPECT_FALSE(resetVRF->remove().empty());
  EXPECT_TRUE(resetModel->getObject(retainedCurve.handle()));
  EXPECT_TRUE(resetModel->getObject(resetTerminal->handle()));
  EXPECT_FALSE(resetTerminal->vrfSystem());
  EXPECT_FALSE(resetModel->getObject(terminalList->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setGrossRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(vrf.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, vrf.grossRatedTotalCoolingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  vrf.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(vrf.setGrossRatedCoolingCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, vrf.grossRatedCoolingCOP());

  EXPECT_TRUE(vrf.setGrossRatedHeatingCapacity(9876.0));
  ASSERT_TRUE(vrf.grossRatedHeatingCapacity());
  EXPECT_DOUBLE_EQ(9876.0, vrf.grossRatedHeatingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedHeatingCapacityAutosized());

  vrf.autosizeGrossRatedHeatingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedHeatingCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedHeatingCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, vrf.ratedHeatingCapacitySizingRatio());

  const auto heatingValues = AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
  ASSERT_FALSE(heatingValues.empty());
  EXPECT_TRUE(vrf.setHeatingPerformanceCurveOutdoorTemperatureType(heatingValues.front()));
  EXPECT_EQ(heatingValues.front(), vrf.heatingPerformanceCurveOutdoorTemperatureType());

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(false));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());

  EXPECT_TRUE(vrf.setNumberofCompressors(3));
  EXPECT_EQ(3, vrf.numberofCompressors());

  const auto defrostValues = AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
  ASSERT_FALSE(defrostValues.empty());
  EXPECT_TRUE(vrf.setDefrostStrategy(defrostValues.front()));
  EXPECT_EQ(defrostValues.front(), vrf.defrostStrategy());

  const auto condenserValues = AirConditionerVariableRefrigerantFlow::condenserTypeValues();
  ASSERT_FALSE(condenserValues.empty());
  EXPECT_TRUE(vrf.setCondenserType(condenserValues.front()));
  EXPECT_FALSE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ(condenserValues.front(), vrf.condenserType());
  vrf.resetCondenserType();
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ControlRelationshipsValidateAndResetExactly) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ScheduleConstant availability(model);
  ScheduleConstant basin(model);
  ASSERT_TRUE(availability.setScheduleTypeLimits(availabilityLimits));
  ASSERT_TRUE(basin.setScheduleTypeLimits(availabilityLimits));

  ScheduleTypeLimits controlModeLimits(model);
  ASSERT_TRUE(controlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(controlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(controlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(controlModeLimits.setUpperLimitValue(1.0));
  ScheduleConstant priority(model);
  ASSERT_TRUE(priority.setScheduleTypeLimits(controlModeLimits));

  ThermalZone zone(model);
  ASSERT_TRUE(vrf.setAvailabilitySchedule(availability));
  ASSERT_TRUE(vrf.setThermostatPrioritySchedule(priority));
  ASSERT_TRUE(vrf.setBasinHeaterOperatingSchedule(basin));
  ASSERT_TRUE(vrf.setZoneforMasterThermostatLocation(zone));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  ASSERT_TRUE(vrf.thermostatPrioritySchedule());
  ASSERT_TRUE(vrf.basinHeaterOperatingSchedule());
  ASSERT_TRUE(vrf.zoneforMasterThermostatLocation());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(zone.handle(), vrf.zoneforMasterThermostatLocation()->handle());

  ScheduleTypeLimits incompatibleLimits(model);
  ASSERT_TRUE(incompatibleLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleLimits.setUnitType("Temperature"));
  ScheduleConstant incompatible(model);
  ASSERT_TRUE(incompatible.setScheduleTypeLimits(incompatibleLimits));
  EXPECT_FALSE(vrf.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(vrf.setThermostatPrioritySchedule(incompatible));
  EXPECT_FALSE(vrf.setBasinHeaterOperatingSchedule(incompatible));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(vrf.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setThermostatPrioritySchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setBasinHeaterOperatingSchedule(foreignSchedule));
  EXPECT_FALSE(vrf.setZoneforMasterThermostatLocation(foreignZone));
  EXPECT_EQ(availability.handle(), vrf.availabilitySchedule().handle());
  EXPECT_EQ(priority.handle(), vrf.thermostatPrioritySchedule()->handle());
  EXPECT_EQ(basin.handle(), vrf.basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(zone.handle(), vrf.zoneforMasterThermostatLocation()->handle());

  AirConditionerVariableRefrigerantFlow unresolved(model);
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(unresolvedImpl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) {
    return unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or("");
  };
  constexpr unsigned availabilityField = openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName;
  constexpr unsigned priorityField = openstudio::AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName;
  constexpr unsigned basinField = openstudio::AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName;
  constexpr unsigned zoneField = openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation;
  setUnresolvedRaw(availabilityField, "Missing VRF Availability");
  setUnresolvedRaw(priorityField, "Missing VRF Thermostat Priority");
  setUnresolvedRaw(basinField, "Missing VRF Basin Schedule");
  setUnresolvedRaw(zoneField, "Missing VRF Master Zone");
  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatible));
  EXPECT_FALSE(unresolved.setThermostatPrioritySchedule(incompatible));
  EXPECT_FALSE(unresolved.setBasinHeaterOperatingSchedule(incompatible));
  EXPECT_FALSE(unresolved.setZoneforMasterThermostatLocation(foreignZone));
  EXPECT_EQ("Missing VRF Availability", rawValue(availabilityField));
  EXPECT_EQ("Missing VRF Thermostat Priority", rawValue(priorityField));
  EXPECT_EQ("Missing VRF Basin Schedule", rawValue(basinField));
  EXPECT_EQ("Missing VRF Master Zone", rawValue(zoneField));

  vrf.resetThermostatPrioritySchedule();
  vrf.resetBasinHeaterOperatingSchedule();
  vrf.resetZoneforMasterThermostatLocation();
  EXPECT_FALSE(vrf.thermostatPrioritySchedule());
  EXPECT_FALSE(vrf.basinHeaterOperatingSchedule());
  EXPECT_FALSE(vrf.zoneforMasterThermostatLocation());
  auto vrfImpl = vrf.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(vrfImpl);
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(priorityField, false, true).value_or(""));
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(basinField, false, true).value_or(""));
  EXPECT_EQ("", vrfImpl->openstudio::detail::IdfObject_Impl::getString(zoneField, false, true).value_or(""));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_CanonicalizationRepairsOnlyBlankAvailability) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow blank(model);
  AirConditionerVariableRefrigerantFlow unresolved(model);
  ASSERT_TRUE(blank.setName("Blank VRF Availability"));
  ASSERT_TRUE(unresolved.setName("Unresolved VRF Availability"));

  constexpr unsigned field = openstudio::AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing VRF Availability", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ("Missing VRF Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  Model reloadSource;
  AirConditionerVariableRefrigerantFlow blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank VRF Availability On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Blank VRF Availability On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ControlRelationshipsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-vrf-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-vrf-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setName("VRF Availability Limits"));
  ASSERT_TRUE(availabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(availabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(availabilityLimits.setUpperLimitValue(1.0));
  ScheduleTypeLimits controlModeLimits(model);
  ASSERT_TRUE(controlModeLimits.setName("VRF Control Mode Limits"));
  ASSERT_TRUE(controlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(controlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(controlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(controlModeLimits.setUpperLimitValue(1.0));

  ScheduleConstant availability(model);
  ScheduleConstant priority(model);
  ScheduleConstant basin(model);
  ASSERT_TRUE(availability.setName("Shared VRF Availability"));
  ASSERT_TRUE(priority.setName("Shared VRF Thermostat Priority"));
  ASSERT_TRUE(basin.setName("Shared VRF Basin Schedule"));
  ASSERT_TRUE(availability.setScheduleTypeLimits(availabilityLimits));
  ASSERT_TRUE(priority.setScheduleTypeLimits(controlModeLimits));
  ASSERT_TRUE(basin.setScheduleTypeLimits(availabilityLimits));
  ThermalZone zone(model);
  ASSERT_TRUE(zone.setName("Shared VRF Master Zone"));

  AirConditionerVariableRefrigerantFlow first(model);
  AirConditionerVariableRefrigerantFlow second(model);
  ASSERT_TRUE(first.setName("First Relationship VRF"));
  ASSERT_TRUE(second.setName("Second Relationship VRF"));
  for (auto* vrf : {&first, &second}) {
    ASSERT_TRUE(vrf->setAvailabilitySchedule(availability));
    ASSERT_TRUE(vrf->setThermostatPrioritySchedule(priority));
    ASSERT_TRUE(vrf->setBasinHeaterOperatingSchedule(basin));
    ASSERT_TRUE(vrf->setZoneforMasterThermostatLocation(zone));
  }
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirst = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("First Relationship VRF");
  auto loadedSecond = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Second Relationship VRF");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Availability");
  auto loadedPriority = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Thermostat Priority");
  auto loadedBasin = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Basin Schedule");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Shared VRF Master Zone");
  ASSERT_TRUE(loadedFirst);
  ASSERT_TRUE(loadedSecond);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedPriority);
  ASSERT_TRUE(loadedBasin);
  ASSERT_TRUE(loadedZone);
  EXPECT_EQ(loadedAvailability->handle(), loadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(loadedAvailability->handle(), loadedSecond->availabilitySchedule().handle());
  ASSERT_TRUE(loadedFirst->thermostatPrioritySchedule());
  ASSERT_TRUE(loadedFirst->basinHeaterOperatingSchedule());
  ASSERT_TRUE(loadedFirst->zoneforMasterThermostatLocation());
  ASSERT_TRUE(loadedSecond->thermostatPrioritySchedule());
  ASSERT_TRUE(loadedSecond->basinHeaterOperatingSchedule());
  ASSERT_TRUE(loadedSecond->zoneforMasterThermostatLocation());
  EXPECT_EQ(loadedPriority->handle(), loadedFirst->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(loadedBasin->handle(), loadedFirst->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedFirst->zoneforMasterThermostatLocation()->handle());
  EXPECT_EQ(loadedPriority->handle(), loadedSecond->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(loadedBasin->handle(), loadedSecond->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedSecond->zoneforMasterThermostatLocation()->handle());

  ScheduleTypeLimits replacementAvailabilityLimits(*loadedModel);
  ASSERT_TRUE(replacementAvailabilityLimits.setNumericType("Discrete"));
  ASSERT_TRUE(replacementAvailabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(replacementAvailabilityLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(replacementAvailabilityLimits.setUpperLimitValue(1.0));
  ScheduleTypeLimits replacementControlModeLimits(*loadedModel);
  ASSERT_TRUE(replacementControlModeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(replacementControlModeLimits.setUnitType("ControlMode"));
  ASSERT_TRUE(replacementControlModeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(replacementControlModeLimits.setUpperLimitValue(1.0));
  ScheduleConstant replacementAvailability(*loadedModel);
  ScheduleConstant replacementPriority(*loadedModel);
  ScheduleConstant replacementBasin(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement VRF Availability"));
  ASSERT_TRUE(replacementPriority.setName("Replacement VRF Thermostat Priority"));
  ASSERT_TRUE(replacementBasin.setName("Replacement VRF Basin Schedule"));
  ASSERT_TRUE(replacementAvailability.setScheduleTypeLimits(replacementAvailabilityLimits));
  ASSERT_TRUE(replacementPriority.setScheduleTypeLimits(replacementControlModeLimits));
  ASSERT_TRUE(replacementBasin.setScheduleTypeLimits(replacementAvailabilityLimits));
  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement VRF Master Zone"));
  ASSERT_TRUE(loadedFirst->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedFirst->setThermostatPrioritySchedule(replacementPriority));
  ASSERT_TRUE(loadedFirst->setBasinHeaterOperatingSchedule(replacementBasin));
  ASSERT_TRUE(loadedFirst->setZoneforMasterThermostatLocation(replacementZone));
  loadedFirst->resetThermostatPrioritySchedule();
  loadedFirst->resetBasinHeaterOperatingSchedule();
  loadedFirst->resetZoneforMasterThermostatLocation();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFirst = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("First Relationship VRF");
  auto reloadedSecond = reloadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Second Relationship VRF");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Availability");
  auto reloadedOriginalPriority = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Thermostat Priority");
  auto reloadedOriginalBasin = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared VRF Basin Schedule");
  auto reloadedOriginalZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Shared VRF Master Zone");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Availability");
  auto reloadedReplacementPriority = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Thermostat Priority");
  auto reloadedReplacementBasin = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement VRF Basin Schedule");
  auto reloadedReplacementZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement VRF Master Zone");
  ASSERT_TRUE(reloadedFirst);
  ASSERT_TRUE(reloadedSecond);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedOriginalPriority);
  ASSERT_TRUE(reloadedOriginalBasin);
  ASSERT_TRUE(reloadedOriginalZone);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedReplacementPriority);
  ASSERT_TRUE(reloadedReplacementBasin);
  ASSERT_TRUE(reloadedReplacementZone);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedFirst->availabilitySchedule().handle());
  EXPECT_FALSE(reloadedFirst->thermostatPrioritySchedule());
  EXPECT_FALSE(reloadedFirst->basinHeaterOperatingSchedule());
  EXPECT_FALSE(reloadedFirst->zoneforMasterThermostatLocation());
  EXPECT_EQ(reloadedOriginalAvailability->handle(), reloadedSecond->availabilitySchedule().handle());
  ASSERT_TRUE(reloadedSecond->thermostatPrioritySchedule());
  ASSERT_TRUE(reloadedSecond->basinHeaterOperatingSchedule());
  ASSERT_TRUE(reloadedSecond->zoneforMasterThermostatLocation());
  EXPECT_EQ(reloadedOriginalPriority->handle(), reloadedSecond->thermostatPrioritySchedule()->handle());
  EXPECT_EQ(reloadedOriginalBasin->handle(), reloadedSecond->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(reloadedOriginalZone->handle(), reloadedSecond->zoneforMasterThermostatLocation()->handle());

  EXPECT_FALSE(reloadedFirst->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementPriority->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementBasin->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedReplacementZone->handle()));
  EXPECT_FALSE(reloadedSecond->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalPriority->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalBasin->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedOriginalZone->handle()));
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_AddToNode_DemandSideDefaultedCondenserType) {
  Model model;
  PlantLoop plantLoop(model);
  AirConditionerVariableRefrigerantFlow vrf(model);

  Node supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(vrf.addToNode(supplyOutletNode));
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(vrf.addToNode(demandOutletNode));
  EXPECT_TRUE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("WaterCooled", vrf.condenserType());
  EXPECT_EQ(7u, plantLoop.demandComponents().size());
  EXPECT_EQ(1u, plantLoop.demandComponents(AirConditionerVariableRefrigerantFlow::iddObjectType()).size());

  ASSERT_TRUE(vrf.inletModelObject());
  ASSERT_TRUE(vrf.outletModelObject());
  EXPECT_NE(vrf.inletModelObject()->handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(demandOutletNode.handle(), vrf.outletModelObject()->handle());
  EXPECT_EQ(1u, plantLoop
                  .demandComponents(vrf.inletModelObject()->cast<Node>(), vrf.outletModelObject()->cast<Node>(),
                                    AirConditionerVariableRefrigerantFlow::iddObjectType())
                  .size());

  EXPECT_TRUE(vrf.removeFromLoop());
  EXPECT_FALSE(vrf.plantLoop());
  EXPECT_TRUE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ("AirCooled", vrf.condenserType());
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipIsExclusiveAndRenameSafe) {
  Model model;
  AirConditionerVariableRefrigerantFlow first(model);
  AirConditionerVariableRefrigerantFlow second(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);

  ASSERT_TRUE(first.setName("First VRF Outdoor Unit"));
  ASSERT_TRUE(second.setName("Second VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("VRF Indoor Terminal"));
  EXPECT_TRUE(first.addTerminal(terminal));
  EXPECT_TRUE(first.addTerminal(terminal));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  EXPECT_FALSE(second.addTerminal(terminal));
  EXPECT_TRUE(second.terminals().empty());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(first.handle(), terminal.vrfSystem()->handle());

  ASSERT_TRUE(terminal.setName("Renamed VRF Indoor Terminal"));
  ASSERT_EQ(1u, first.terminals().size());
  EXPECT_EQ(terminal.handle(), first.terminals().front().handle());
  auto list = first.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  ASSERT_EQ(1u, list->extensibleGroups().size());
  auto group = list->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  auto target = group->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
  ASSERT_TRUE(target);
  EXPECT_EQ(terminal.handle(), target->handle());

  first.removeTerminal(terminal);
  EXPECT_TRUE(first.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
  EXPECT_TRUE(second.addTerminal(terminal));
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(second.handle(), terminal.vrfSystem()->handle());
  second.removeAllTerminals();
  EXPECT_TRUE(second.terminals().empty());
  EXPECT_FALSE(terminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipRejectsForeignAndFluidControlTerminals) {
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow foreignTerminal(foreignModel);
  ZoneHVACTerminalUnitVariableRefrigerantFlow fluidTerminal(model, true);

  EXPECT_FALSE(system.addTerminal(foreignTerminal));
  EXPECT_FALSE(system.addTerminal(fluidTerminal));
  EXPECT_TRUE(system.terminals().empty());
  EXPECT_FALSE(fluidTerminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalRelationshipSurvivesReload) {
  const auto idfPath = uniqueIdfPath("epmodel-vrf-terminal-list-roundtrip");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  AirConditionerVariableRefrigerantFlow system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model);
  ASSERT_TRUE(system.setName("Roundtrip VRF Outdoor Unit"));
  ASSERT_TRUE(terminal.setName("Roundtrip VRF Indoor Terminal"));
  ASSERT_TRUE(system.addTerminal(terminal));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlow>("Roundtrip VRF Outdoor Unit");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Roundtrip VRF Indoor Terminal");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_EQ(1u, loadedSystem->terminals().size());
  EXPECT_EQ(loadedTerminal->handle(), loadedSystem->terminals().front().handle());
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(loadedSystem->handle(), loadedTerminal->vrfSystem()->handle());
  EXPECT_EQ(1u, loadedModel->getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_TerminalAndSystemRemovalOwnOnlyTheirTopology) {
  Model model;
  AirConditionerVariableRefrigerantFlow firstSystem(model);
  AirConditionerVariableRefrigerantFlow secondSystem(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow firstTerminal(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow secondTerminal(model);
  ASSERT_TRUE(firstSystem.addTerminal(firstTerminal));
  ASSERT_TRUE(secondSystem.addTerminal(secondTerminal));

  const auto firstTerminalHandle = firstTerminal.handle();
  EXPECT_FALSE(firstTerminal.remove().empty());
  EXPECT_FALSE(model.getObject(firstTerminalHandle));
  EXPECT_TRUE(firstSystem.terminals().empty());
  EXPECT_EQ(1u, secondSystem.terminals().size());
  EXPECT_EQ(2u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());

  const auto secondSystemHandle = secondSystem.handle();
  EXPECT_FALSE(secondSystem.remove().empty());
  EXPECT_FALSE(model.getObject(secondSystemHandle));
  EXPECT_TRUE(model.getObject(secondTerminal.handle()));
  EXPECT_FALSE(secondTerminal.vrfSystem());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
}
