/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../HVACComponent/AirConditionerVariableRefrigerantFlowFluidTemperatureControl_Impl.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../Schedule/Schedule.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow.hpp"
#include "../ZoneHVACComponent/ZoneHVACTerminalUnitVariableRefrigerantFlow_Impl.hpp"

#include <utilities/idd/AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneTerminalUnitList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <array>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule(), vrf.availabilitySchedule());
  EXPECT_TRUE(vrf.terminals().empty());
  const auto lists = model.getObjectsByType(openstudio::IddObjectType::ZoneTerminalUnitList);
  ASSERT_EQ(1u, lists.size());
  auto list =
    vrf.getModelObjectTarget<ModelObject>(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  EXPECT_EQ(lists.front(), *list);

  const auto evaporatingCurve = vrf.outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(0.0, evaporatingCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(0.605, evaporatingCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(0.025, evaporatingCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, evaporatingCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(15.0, evaporatingCurve.maximumValueofx());

  const auto condensingCurve = vrf.outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve().cast<CurveQuadratic>();
  EXPECT_DOUBLE_EQ(0.0, condensingCurve.coefficient1Constant());
  EXPECT_DOUBLE_EQ(-2.91, condensingCurve.coefficient2x());
  EXPECT_DOUBLE_EQ(1.180, condensingCurve.coefficient3xPOW2());
  EXPECT_DOUBLE_EQ(0.0, condensingCurve.minimumValueofx());
  EXPECT_DOUBLE_EQ(5.0, condensingCurve.maximumValueofx());

  EXPECT_EQ(2u, model.getConcreteModelObjects<CurveQuadratic>().size());
  EXPECT_EQ(6u, model.getConcreteModelObjects<CurveBiquadratic>().size());
  EXPECT_EQ(
    3, vrf.getInt(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressorLoadingIndexEntries).get());

  const std::array<double, 3> expectedSpeeds = {1500.0, 3600.0, 6000.0};
  std::vector<CurveBiquadratic> loadingCurves;
  ASSERT_EQ(expectedSpeeds.size(), vrf.extensibleGroups().size());
  for (size_t i = 0; i < expectedSpeeds.size(); ++i) {
    auto group = vrf.extensibleGroups()[i].cast<openstudio::WorkspaceExtensibleGroup>();
    EXPECT_DOUBLE_EQ(
      expectedSpeeds[i],
      group.getDouble(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::CompressorSpeedatLoadingIndex)
        .get());
    auto capacityCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                           LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName);
    auto powerCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                        LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName);
    ASSERT_TRUE(capacityCurve);
    ASSERT_TRUE(powerCurve);
    EXPECT_TRUE(capacityCurve->optionalCast<CurveBiquadratic>());
    EXPECT_TRUE(powerCurve->optionalCast<CurveBiquadratic>());
    loadingCurves.push_back(capacityCurve->cast<CurveBiquadratic>());
    loadingCurves.push_back(powerCurve->cast<CurveBiquadratic>());
  }

  const std::array<std::array<double, 6>, 6> expectedCoefficients = {{
    {0.319, -0.00126, -0.0000215, 0.012, 0.000105, -0.0000866},
    {0.0879, -0.000172, 0.0000693, -0.0000338, -0.00000810, -0.0000104},
    {0.812, -0.00423, -0.0000411, 0.0297, 0.000267, -0.000223},
    {0.326, -0.00220, 0.000142, 0.00282, 0.0000286, -0.0000350},
    {1.32, -0.00620, -0.0000710, 0.0489, 0.000459, -0.000367},
    {0.656, -0.00371, 0.000207, 0.0105, 0.0000736, -0.000157},
  }};
  ASSERT_EQ(expectedCoefficients.size(), loadingCurves.size());
  for (size_t i = 0; i < expectedCoefficients.size(); ++i) {
    const auto& curve = loadingCurves[i];
    const auto& coefficients = expectedCoefficients[i];
    EXPECT_DOUBLE_EQ(coefficients[0], curve.coefficient1Constant());
    EXPECT_DOUBLE_EQ(coefficients[1], curve.coefficient2x());
    EXPECT_DOUBLE_EQ(coefficients[2], curve.coefficient3xPOW2());
    EXPECT_DOUBLE_EQ(coefficients[3], curve.coefficient4y());
    EXPECT_DOUBLE_EQ(coefficients[4], curve.coefficient5yPOW2());
    EXPECT_DOUBLE_EQ(coefficients[5], curve.coefficient6xTIMESY());
    EXPECT_DOUBLE_EQ(15.0, curve.minimumValueofx());
    EXPECT_DOUBLE_EQ(65.0, curve.maximumValueofx());
    EXPECT_DOUBLE_EQ(-30.0, curve.minimumValueofy());
    EXPECT_DOUBLE_EQ(15.0, curve.maximumValueofy());
  }
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_TerminalLifecycleSurvivesReload) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-fluid-vrf-terminal-lifecycle.idf");
  Model model;
  Model foreignModel;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl firstSystem(model);
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl secondSystem(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, true);
  ZoneHVACTerminalUnitVariableRefrigerantFlow standardTerminal(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow foreignTerminal(foreignModel, true);
  ASSERT_TRUE(firstSystem.setName("First Fluid VRF System"));
  ASSERT_TRUE(secondSystem.setName("Second Fluid VRF System"));
  ASSERT_TRUE(terminal.setName("Fluid VRF Terminal"));

  EXPECT_FALSE(firstSystem.addTerminal(standardTerminal));
  EXPECT_FALSE(firstSystem.addTerminal(foreignTerminal));
  EXPECT_TRUE(firstSystem.addTerminal(terminal));
  EXPECT_TRUE(firstSystem.addTerminal(terminal));
  ASSERT_EQ(1u, firstSystem.terminals().size());
  EXPECT_EQ(terminal, firstSystem.terminals().front());
  EXPECT_FALSE(secondSystem.addTerminal(terminal));
  EXPECT_TRUE(secondSystem.terminals().empty());
  ASSERT_TRUE(terminal.vrfSystem());
  EXPECT_EQ(firstSystem, *terminal.vrfSystem());

  auto list = firstSystem.getModelObjectTarget<ModelObject>(
    openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  ASSERT_EQ(1u, list->extensibleGroups().size());
  auto group = list->extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  auto target = group->getTarget(openstudio::ZoneTerminalUnitListExtensibleFields::ZoneTerminalUnitName);
  ASSERT_TRUE(target);
  EXPECT_EQ(terminal.handle(), target->handle());

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirstSystem =
    loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlowFluidTemperatureControl>("First Fluid VRF System");
  auto loadedSecondSystem =
    loadedModel->getConcreteModelObjectByName<AirConditionerVariableRefrigerantFlowFluidTemperatureControl>("Second Fluid VRF System");
  auto loadedTerminal = loadedModel->getConcreteModelObjectByName<ZoneHVACTerminalUnitVariableRefrigerantFlow>("Fluid VRF Terminal");
  ASSERT_TRUE(loadedFirstSystem);
  ASSERT_TRUE(loadedSecondSystem);
  ASSERT_TRUE(loadedTerminal);
  ASSERT_EQ(1u, loadedFirstSystem->terminals().size());
  EXPECT_EQ(*loadedTerminal, loadedFirstSystem->terminals().front());
  EXPECT_EQ(3u, loadedFirstSystem->extensibleGroups().size());
  EXPECT_TRUE(loadedFirstSystem->outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(loadedFirstSystem->outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve().optionalCast<CurveQuadratic>());
  for (const auto& extensibleGroup : loadedFirstSystem->extensibleGroups()) {
    auto group = extensibleGroup.cast<openstudio::WorkspaceExtensibleGroup>();
    auto capacityCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                           LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName);
    auto powerCurve = group.getTarget(openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::
                                        LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName);
    ASSERT_TRUE(capacityCurve);
    ASSERT_TRUE(powerCurve);
    EXPECT_TRUE(capacityCurve->optionalCast<CurveBiquadratic>());
    EXPECT_TRUE(powerCurve->optionalCast<CurveBiquadratic>());
  }
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(*loadedFirstSystem, *loadedTerminal->vrfSystem());

  loadedFirstSystem->removeTerminal(*loadedTerminal);
  EXPECT_TRUE(loadedFirstSystem->terminals().empty());
  EXPECT_FALSE(loadedTerminal->vrfSystem());
  ASSERT_TRUE(loadedSecondSystem->addTerminal(*loadedTerminal));
  ASSERT_TRUE(loadedTerminal->vrfSystem());
  EXPECT_EQ(*loadedSecondSystem, *loadedTerminal->vrfSystem());
  EXPECT_FALSE(loadedTerminal->remove().empty());
  EXPECT_TRUE(loadedSecondSystem->terminals().empty());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_RemovalKeepsTerminals) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl system(model);
  ZoneHVACTerminalUnitVariableRefrigerantFlow terminal(model, true);
  ASSERT_TRUE(system.addTerminal(terminal));
  const auto list = system.getModelObjectTarget<ModelObject>(
    openstudio::AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName);
  ASSERT_TRUE(list);
  const auto evaporatingCurve = system.outdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurve();
  const auto condensingCurve = system.outdoorUnitCondensingTemperatureFunctionofSubcoolingCurve();

  EXPECT_FALSE(system.remove().empty());
  EXPECT_FALSE(model.getObject(system.handle()));
  EXPECT_FALSE(model.getObject(list->handle()));
  EXPECT_FALSE(model.getObject(evaporatingCurve.handle()));
  EXPECT_FALSE(model.getObject(condensingCurve.handle()));
  EXPECT_TRUE(model.getConcreteModelObjects<CurveBiquadratic>().empty());
  EXPECT_TRUE(model.getObject(terminal.handle()));
  EXPECT_FALSE(terminal.vrfSystem());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlowFluidTemperatureControl vrf(model);

  EXPECT_FALSE(vrf.refrigerantType().empty());

  EXPECT_TRUE(vrf.setRatedEvaporativeCapacity(45678.0));
  ASSERT_TRUE(vrf.ratedEvaporativeCapacity());
  EXPECT_DOUBLE_EQ(45678.0, vrf.ratedEvaporativeCapacity().get());
  EXPECT_FALSE(vrf.isRatedEvaporativeCapacityAutosized());
  vrf.autosizeRatedEvaporativeCapacity();
  EXPECT_TRUE(vrf.isRatedEvaporativeCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedCompressorPowerPerUnitofRatedEvaporativeCapacity(0.41));
  EXPECT_DOUBLE_EQ(0.41, vrf.ratedCompressorPowerPerUnitofRatedEvaporativeCapacity());

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

  EXPECT_TRUE(vrf.setCompressorMaximumDeltaPressure(4.1e6));
  EXPECT_DOUBLE_EQ(4.1e6, vrf.compressorMaximumDeltaPressure());
}
