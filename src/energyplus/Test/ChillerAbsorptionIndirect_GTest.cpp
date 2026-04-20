/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/ChillerAbsorptionIndirect.hpp"
#include "../../model/CurveCubic.hpp"
#include "../../model/CurveQuadratic.hpp"
#include "../../model/Model.hpp"
#include "../../model/PlantLoop.hpp"

#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

#include <utilities/idd/BranchExtensibleFields.hxx>
#include <utilities/idd/BranchList_FieldEnums.hxx>
#include <utilities/idd/Chiller_Absorption_Indirect_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/PlantLoop_FieldEnums.hxx>

#include <array>
#include <string>
#include <string_view>

using namespace openstudio;
using namespace openstudio::energyplus;
using namespace openstudio::model;

TEST_F(EnergyPlusFixture, ForwardTranslator_ChillerAbsorptionIndirect) {
  ForwardTranslator ft;
  Model m;

  auto createLoop = [&m](const std::string& prefix) {
    PlantLoop p(m);
    static constexpr std::array<std::string_view, 10> compNames = {
      "Supply Inlet", "Supply Splitter", "Supply Connection Node", "Supply Mixer", "Supply Outlet",
      "Demand Inlet", "Demand Splitter", "Demand Connection Node", "Demand Mixer", "Demand Outlet",
    };
    p.setName(prefix);
    for (size_t i = 0; auto& comp : p.components()) {
      comp.setName(prefix + " " + std::string{compNames[i++]});
    }
    return p;
  };

  ChillerAbsorptionIndirect chiller(m);
  ASSERT_TRUE(chiller.setName("My ChillerAbsorptionIndirect"));

  ASSERT_TRUE(chiller.setNominalCapacity(31000.0));
  ASSERT_TRUE(chiller.setNominalPumpingPower(4100.0));
  ASSERT_TRUE(chiller.setMinimumPartLoadRatio(0.2));
  ASSERT_TRUE(chiller.setMaximumPartLoadRatio(0.95));
  ASSERT_TRUE(chiller.setOptimumPartLoadRatio(0.7));
  ASSERT_TRUE(chiller.setDesignCondenserInletTemperature(31.0));
  ASSERT_TRUE(chiller.setCondenserInletTemperatureLowerLimit(12.0));
  ASSERT_TRUE(chiller.setChilledWaterOutletTemperatureLowerLimit(4.0));
  ASSERT_TRUE(chiller.setDesignChilledWaterFlowRate(0.011));
  ASSERT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));

  auto generatorHeatInputCurve = chiller.generatorHeatInputFunctionofPartLoadRatioCurve().cast<CurveCubic>();
  generatorHeatInputCurve.setName("generatorHeatInputCurve");
  auto pumpElectricCurve = chiller.pumpElectricInputFunctionofPartLoadRatioCurve().cast<CurveQuadratic>();
  pumpElectricCurve.setName("pumpElectricCurve");
  auto capacityCondCurve = chiller.capacityCorrectionFunctionofCondenserTemperatureCurve().cast<CurveCubic>();
  capacityCondCurve.setName("capacityCondCurve");
  auto capacityChwCurve = chiller.capacityCorrectionFunctionofChilledWaterTemperatureCurve().cast<CurveCubic>();
  capacityChwCurve.setName("capacityChwCurve");
  auto capacityGeneratorCurve = chiller.capacityCorrectionFunctionofGeneratorTemperatureCurve().cast<CurveCubic>();
  capacityGeneratorCurve.setName("capacityGeneratorCurve");
  auto generatorHeatCondCurve = chiller.generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve().cast<CurveCubic>();
  generatorHeatCondCurve.setName("generatorHeatCondCurve");
  auto generatorHeatChwCurve = chiller.generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve().cast<CurveCubic>();
  generatorHeatChwCurve.setName("generatorHeatChwCurve");

  auto chilledWaterLoop = createLoop("Chilled Water Loop");
  auto condenserWaterLoop = createLoop("Condenser Water Loop");
  auto generatorLoop = createLoop("Generator Loop");

  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(generatorLoop.addDemandBranchForComponent(chiller));

  chiller.supplyInletModelObject()->setName("Chilled Water Inlet Node");
  chiller.supplyOutletModelObject()->setName("Chilled Water Outlet Node");
  chiller.demandInletModelObject()->setName("Condenser Inlet Node");
  chiller.demandOutletModelObject()->setName("Condenser Outlet Node");
  chiller.tertiaryInletModelObject()->setName("Generator Inlet Node");
  chiller.tertiaryOutletModelObject()->setName("Generator Outlet Node");

  ASSERT_TRUE(chiller.setDesignGeneratorFluidFlowRate(0.033));
  ASSERT_TRUE(chiller.setTemperatureLowerLimitGeneratorInlet(30.5));
  ASSERT_TRUE(chiller.setDegreeofSubcoolinginSteamGenerator(2.2));
  ASSERT_TRUE(chiller.setDegreeofSubcoolinginSteamCondensateLoop(11.5));
  ASSERT_TRUE(chiller.setSizingFactor(1.15));

  Workspace w = ft.translateModel(m);

  ASSERT_EQ(1u, w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect).size());
  const auto idfObject = w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect)[0];

  EXPECT_EQ("My ChillerAbsorptionIndirect", idfObject.getString(Chiller_Absorption_IndirectFields::Name).get());
  EXPECT_EQ("Chilled Water Inlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::ChilledWaterInletNodeName).get());
  EXPECT_EQ("Chilled Water Outlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::ChilledWaterOutletNodeName).get());
  EXPECT_EQ("Condenser Inlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::CondenserInletNodeName).get());
  EXPECT_EQ("Condenser Outlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::CondenserOutletNodeName).get());
  EXPECT_EQ("Generator Inlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorInletNodeName).get());
  EXPECT_EQ("Generator Outlet Node", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorOutletNodeName).get());
  EXPECT_DOUBLE_EQ(31000.0, idfObject.getDouble(Chiller_Absorption_IndirectFields::NominalCapacity).get());
  EXPECT_DOUBLE_EQ(4100.0, idfObject.getDouble(Chiller_Absorption_IndirectFields::NominalPumpingPower).get());
  EXPECT_DOUBLE_EQ(0.2, idfObject.getDouble(Chiller_Absorption_IndirectFields::MinimumPartLoadRatio).get());
  EXPECT_DOUBLE_EQ(0.95, idfObject.getDouble(Chiller_Absorption_IndirectFields::MaximumPartLoadRatio).get());
  EXPECT_DOUBLE_EQ(0.7, idfObject.getDouble(Chiller_Absorption_IndirectFields::OptimumPartLoadRatio).get());
  EXPECT_DOUBLE_EQ(31.0, idfObject.getDouble(Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature).get());
  EXPECT_DOUBLE_EQ(12.0, idfObject.getDouble(Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit).get());
  EXPECT_DOUBLE_EQ(4.0, idfObject.getDouble(Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit).get());
  EXPECT_DOUBLE_EQ(0.011, idfObject.getDouble(Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate).get());
  EXPECT_DOUBLE_EQ(0.022, idfObject.getDouble(Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate).get());
  EXPECT_EQ("ConstantFlow", idfObject.getString(Chiller_Absorption_IndirectFields::ChillerFlowMode).get());
  EXPECT_EQ("generatorHeatInputCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorHeatInputFunctionofPartLoadRatioCurveName).get());
  EXPECT_EQ("pumpElectricCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::PumpElectricInputFunctionofPartLoadRatioCurveName).get());
  EXPECT_EQ("capacityCondCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofCondenserTemperatureCurveName).get());
  EXPECT_EQ("capacityChwCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofChilledWaterTemperatureCurveName).get());
  EXPECT_EQ("capacityGeneratorCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofGeneratorTemperatureCurveName).get());
  EXPECT_EQ("generatorHeatCondCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName).get());
  EXPECT_EQ("generatorHeatChwCurve",
            idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName)
              .get());
  EXPECT_EQ("HotWater", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorHeatSourceType).get());
  EXPECT_DOUBLE_EQ(0.033, idfObject.getDouble(Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate).get());
  EXPECT_DOUBLE_EQ(30.5, idfObject.getDouble(Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet).get());
  EXPECT_DOUBLE_EQ(2.2, idfObject.getDouble(Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator).get());
  EXPECT_DOUBLE_EQ(11.5, idfObject.getDouble(Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop).get());
  EXPECT_DOUBLE_EQ(1.15, idfObject.getDouble(Chiller_Absorption_IndirectFields::SizingFactor).get());

  auto plant = w.getObjectByTypeAndName(IddObjectType::PlantLoop, generatorLoop.name().get());
  ASSERT_TRUE(plant);
  auto branchList = plant->getTarget(PlantLoopFields::DemandSideBranchListName);
  ASSERT_TRUE(branchList);
  ASSERT_EQ(4u, branchList->extensibleGroups().size());
  auto branch = branchList->extensibleGroups()[1].cast<WorkspaceExtensibleGroup>().getTarget(BranchListExtensibleFields::BranchName);
  ASSERT_TRUE(branch);
  ASSERT_EQ(1u, branch->extensibleGroups().size());
  const auto branchGroup = branch->extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
  EXPECT_EQ(chiller.nameString(), branchGroup.getString(BranchExtensibleFields::ComponentName).get());
  EXPECT_EQ("Generator Inlet Node", branchGroup.getString(BranchExtensibleFields::ComponentInletNodeName).get());
  EXPECT_EQ("Generator Outlet Node", branchGroup.getString(BranchExtensibleFields::ComponentOutletNodeName).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_ChillerAbsorptionIndirect_WithoutGeneratorLoopClearsGeneratorFields) {
  ForwardTranslator ft;
  Model m;

  ChillerAbsorptionIndirect chiller(m);
  PlantLoop chilledWaterLoop(m);
  PlantLoop condenserWaterLoop(m);

  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  chiller.autosizeDesignGeneratorFluidFlowRate();

  Workspace w = ft.translateModel(m);

  ASSERT_EQ(1u, w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect).size());
  const auto idfObject = w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect)[0];

  EXPECT_EQ("", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorInletNodeName, false).get());
  EXPECT_EQ("", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorOutletNodeName, false).get());
  EXPECT_EQ("", idfObject.getString(Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, false).get());
  EXPECT_EQ("Steam", idfObject.getString(Chiller_Absorption_IndirectFields::GeneratorHeatSourceType).get());
}

TEST_F(EnergyPlusFixture, ForwardTranslator_ChillerAbsorptionIndirect_WithGeneratorLoopAutosizesGeneratorFlowField) {
  ForwardTranslator ft;
  Model m;

  ChillerAbsorptionIndirect chiller(m);
  PlantLoop chilledWaterLoop(m);
  PlantLoop condenserWaterLoop(m);
  PlantLoop generatorLoop(m);

  ASSERT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(generatorLoop.addDemandBranchForComponent(chiller));
  chiller.autosizeDesignGeneratorFluidFlowRate();

  Workspace w = ft.translateModel(m);

  ASSERT_EQ(1u, w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect).size());
  const auto idfObject = w.getObjectsByType(IddObjectType::Chiller_Absorption_Indirect)[0];

  EXPECT_EQ("Autosize", idfObject.getString(Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate).get());
}
