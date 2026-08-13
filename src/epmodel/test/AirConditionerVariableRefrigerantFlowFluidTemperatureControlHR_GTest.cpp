/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_Impl.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../Schedule/Schedule.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HR_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <array>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), vrf.availabilitySchedule());
  EXPECT_TRUE(vrf.terminals().empty());
  EXPECT_EQ("R410a", vrf.refrigerantType());
  EXPECT_EQ((std::vector<std::string>{"R11", "R12", "R22", "R123", "R134a", "R404a", "R407a", "R410a", "NH3", "R507a", "R744"}),
            AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR::refrigerantTypeValues());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::FluidProperties_Name).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList).size());
  EXPECT_EQ(2u, model.getConcreteModelObjects<CurveQuadratic>().size());
  EXPECT_EQ(6u, model.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_TRUE(vrf.outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(vrf.outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve().optionalCast<CurveQuadratic>());
  EXPECT_EQ(
    3, vrf.getInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::NumberofCompressorLoadingIndexEntries).get());
  ASSERT_EQ(3u, vrf.extensibleGroups().size());
  const std::array<double, 3> expectedSpeeds = {1500.0, 3600.0, 6000.0};
  for (size_t i = 0; i < expectedSpeeds.size(); ++i) {
    auto group = vrf.extensibleGroups()[i].cast<openstudio::WorkspaceExtensibleGroup>();
    EXPECT_DOUBLE_EQ(
      expectedSpeeds[i],
      group.getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::CompressorSpeedatLoadingIndex)
        .get());
    auto capacityCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::
                                           LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName);
    auto powerCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::
                                        LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName);
    ASSERT_TRUE(capacityCurve);
    ASSERT_TRUE(powerCurve);
    EXPECT_TRUE(capacityCurve->optionalCast<CurveBiquadratic>());
    EXPECT_TRUE(powerCurve->optionalCast<CurveBiquadratic>());
  }
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_TerminalLifecycleSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-fluid-vrf-hr-terminal-lifecycle.idf");
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR firstSystem(model);
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR secondSystem(model);
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl nonHeatRecoverySystem(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, true);
  ZoneHVACTerminalUnitVariableRefrigerantFlow secondTerminal(model, true);
  ZoneHVACTerminalUnitVariableRefrigerantFlow standardTerminal(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow foreignTerminal(foreignModel, true);
  ASSERT_TRUE(firstSystem.setName("First Heat Recovery FTC System"));
  ASSERT_TRUE(secondSystem.setName("Second Heat Recovery FTC System"));
  ASSERT_TRUE(terminal.setName("Heat Recovery FTC Terminal"));
  ASSERT_TRUE(secondTerminal.setName("Second Heat Recovery FTC Terminal"));

  EXPECT_FALSE(firstSystem.addTerminal(standardTerminal));
  EXPECT_FALSE(firstSystem.addTerminal(foreignTerminal));
  EXPECT_TRUE(firstSystem.addTerminal(terminal));
  EXPECT_TRUE(firstSystem.addTerminal(terminal));
  EXPECT_TRUE(firstSystem.addTerminal(secondTerminal));
  ASSERT_EQ(2u, firstSystem.terminals().size());
  EXPECT_EQ(terminal, firstSystem.terminals()[0]);
  EXPECT_EQ(secondTerminal, firstSystem.terminals()[1]);
  EXPECT_FALSE(secondSystem.addTerminal(terminal));
  EXPECT_FALSE(nonHeatRecoverySystem.addTerminal(terminal));
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(firstSystem, *terminal.vrfSystem());

  auto list = firstSystem.getModelObjectTarget<ModelObject>(
    openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  ASSERT_EQ(2u, list->extensibleGroups().size());
  auto group = list->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  auto target = group->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
  ASSERT_TRUE(target);
  EXPECT_EQ(terminal.handle(), target->handle());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirstSystem =
    loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR>("First Heat Recovery FTC System");
  auto loadedSecondSystem =
    loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR>("Second Heat Recovery FTC System");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Heat Recovery FTC Terminal");
  auto loadedSecondTerminal =
    loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Second Heat Recovery FTC Terminal");
  ASSERT_TRUE(loadedFirstSystem);
  ASSERT_TRUE(loadedSecondSystem);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_TRUE(loadedSecondTerminal);
  ASSERT_EQ(2u, loadedFirstSystem->terminals().size());
  EXPECT_EQ(*loadedTerminal, loadedFirstSystem->terminals()[0]);
  EXPECT_EQ(*loadedSecondTerminal, loadedFirstSystem->terminals()[1]);
  EXPECT_TRUE(loadedFirstSystem->outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(loadedFirstSystem->outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve().optionalCast<CurveQuadratic>());
  ASSERT_EQ(3u, loadedFirstSystem->extensibleGroups().size());
  for (const auto& extensibleGroup : loadedFirstSystem->extensibleGroups()) {
    auto group = extensibleGroup.cast<openstudio::WorkspaceExtensibleGroup>();
    EXPECT_TRUE(group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::
                                  LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName));
    EXPECT_TRUE(group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::
                                  LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName));
  }
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(*loadedFirstSystem, *loadedTerminal->vrfSystem());

  loadedFirstSystem->removeTerminal(*loadedTerminal);
  ASSERT_EQ(1u, loadedFirstSystem->terminals().size());
  EXPECT_EQ(*loadedSecondTerminal, loadedFirstSystem->terminals().front());
  EXPECT_FALSE(loadedTerminal->vrfSystem());
  ASSERT_TRUE(loadedSecondSystem->addTerminal(*loadedTerminal));
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(*loadedSecondSystem, *loadedTerminal->vrfSystem());
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_TRUE(loadedSecondSystem->terminals().empty());
  EXPECT_FALSE(loadedSecondTerminal->remove().empty());
  EXPECT_TRUE(loadedFirstSystem->terminals().empty());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_RemovalKeepsTerminals) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, true);
  ASSERT_TRUE(system.addTerminal(terminal));
  const auto list = system.getModelObjectTarget<ModelObject>(
    openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  const auto evaporatingCurve = system.outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve();
  const auto condensingCurve = system.outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve();
  EXPECT_EQ(4u, model.getConcreteModelObjects<CurveQuadratic>().size());  // two outdoor-unit curves and two terminal-coil curves
  EXPECT_EQ(6u, model.getConcreteModelObjects<CurveBiquadratic>().size());

  EXPECT_FALSE(system.remove().empty());
  EXPECT_FALSE(model.getObject(system.handle()));
  EXPECT_FALSE(model.getObject(list->handle()));
  EXPECT_FALSE(model.getObject(evaporatingCurve.handle()));
  EXPECT_FALSE(model.getObject(condensingCurve.handle()));
  EXPECT_EQ(2u, model.getConcreteModelObjects<CurveQuadratic>().size());
  EXPECT_TRUE(model.getConcreteModelObjects<CurveBiquadratic>().empty());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControlHR vrf(model);

  EXPECT_FALSE(vrf.refrigerantType().empty());

  EXPECT_TRUE(vrf.setRatedEvaporativeCapacity(45678.0));
  ASSERT_TRUE(vrf.ratedEvaporativeCapacity());
  EXPECT_DOUBLE_EQ(45678.0, vrf.ratedEvaporativeCapacity().get());
  EXPECT_FALSE(vrf.isRatedEvaporativeCapacityAutosized());
  vrf.autosizeRatedEvaporativeCapacity();
  EXPECT_TRUE(vrf.isRatedEvaporativeCapacityAutosized());

  EXPECT_TRUE(vrf.setMinimumOutdoorTemperatureinHeatRecoveryMode(-25.0));
  EXPECT_DOUBLE_EQ(-25.0, vrf.minimumOutdoorTemperatureinHeatRecoveryMode());

  EXPECT_TRUE(vrf.setDefrostStrategy("Resistive"));
  EXPECT_EQ("Resistive", vrf.defrostStrategy());

  EXPECT_TRUE(vrf.setDefrostControl("Timed"));
  EXPECT_EQ("Timed", vrf.defrostControl());

  EXPECT_TRUE(vrf.setResistiveDefrostHeaterCapacity(123.0));
  ASSERT_TRUE(vrf.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(123.0, vrf.resistiveDefrostHeaterCapacity().get());
  EXPECT_FALSE(vrf.isResistiveDefrostHeaterCapacityAutosized());
  vrf.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(vrf.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(vrf.setInitialHeatRecoveryCoolingCapacityFraction(0.55));
  EXPECT_DOUBLE_EQ(0.55, vrf.initialHeatRecoveryCoolingCapacityFraction());

  EXPECT_TRUE(vrf.setHeatRecoveryHeatingEnergyTimeConstant(22.0));
  EXPECT_DOUBLE_EQ(22.0, vrf.heatRecoveryHeatingEnergyTimeConstant());

  EXPECT_TRUE(vrf.setCompressorMaximumDeltaPressure(4.1e6));
  EXPECT_DOUBLE_EQ(4.1e6, vrf.compressorMaximumDeltaPressure());

  EXPECT_TRUE(vrf.setCompressorInverterEfficiency(0.95));
  EXPECT_DOUBLE_EQ(0.95, vrf.compressorInverterEfficiency());
}
