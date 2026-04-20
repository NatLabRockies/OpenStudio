/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <sqlite3.h>

#include <cstdio>

#include "EPModelFixture.hpp"
#include "../Curve/CurveCubic.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerAbsorptionIndirect.hpp"

#include <utilities/idd/Chiller_Absorption_Indirect_FieldEnums.hxx>

#include "../../utilities/core/Path.hpp"
#include "../../utilities/core/UUID.hpp"
#include "../../utilities/sql/SqlFile.hpp"

#include <algorithm>
#include <set>

using namespace openstudio::epmodel;

namespace {

std::string makeChillerAbsorptionIndirectAutosizeSql(const openstudio::path& sqlPath) {
  sqlite3* db = nullptr;
  if (sqlite3_open(openstudio::toString(sqlPath).c_str(), &db) != SQLITE_OK) {
    const std::string error = db ? sqlite3_errmsg(db) : "sqlite3_open failed";
    if (db) {
      sqlite3_close(db);
    }
    return error;
  }

  const char* sql = R"sql(
    CREATE TABLE ComponentSizes (CompType TEXT, CompName TEXT, Description TEXT, Units TEXT, Value REAL);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption:Indirect','AUTOSIZED INDIRECT CHILLER','Design Size Nominal Capacity','W',111111.0);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption:Indirect','AUTOSIZED INDIRECT CHILLER','Design Size Nominal Pumping Power','W',2222.0);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption:Indirect','AUTOSIZED INDIRECT CHILLER','Design Size Design Chilled Water Flow Rate','m3/s',0.011);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption:Indirect','AUTOSIZED INDIRECT CHILLER','Design Size Design Condenser Water Flow Rate','m3/s',0.022);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption:Indirect','AUTOSIZED INDIRECT CHILLER','Design Size Design Generator Fluid Flow Rate','m3/s',0.033);
  )sql";

  char* errorMessage = nullptr;
  const int execResult = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
  std::string result;
  if (execResult != SQLITE_OK) {
    result = errorMessage ? errorMessage : "sqlite3_exec failed";
  }

  sqlite3_free(errorMessage);
  sqlite3_close(db);
  return result;
}

}  // namespace

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_DefaultConstructor) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);
  EXPECT_EQ(ChillerAbsorptionIndirect::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterInletNodeName, chiller.supplyInletPort());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::ChilledWaterOutletNodeName, chiller.supplyOutletPort());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::CondenserInletNodeName, chiller.demandInletPort());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::CondenserOutletNodeName, chiller.demandOutletPort());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::GeneratorInletNodeName, chiller.tertiaryInletPort());
  EXPECT_EQ(openstudio::Chiller_Absorption_IndirectFields::GeneratorOutletNodeName, chiller.tertiaryOutletPort());
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, chiller.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.65, chiller.optimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(35.0, chiller.designCondenserInletTemperature());
  EXPECT_DOUBLE_EQ(10.0, chiller.condenserInletTemperatureLowerLimit());
  EXPECT_DOUBLE_EQ(5.0, chiller.chilledWaterOutletTemperatureLowerLimit());
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());
  EXPECT_DOUBLE_EQ(30.0, chiller.temperatureLowerLimitGeneratorInlet());
  EXPECT_DOUBLE_EQ(2.0, chiller.degreeofSubcoolinginSteamGenerator());
  EXPECT_DOUBLE_EQ(12.0, chiller.degreeofSubcoolinginSteamCondensateLoop());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.generatorHeatInputFunctionofPartLoadRatioCurve().iddObject().type());
  EXPECT_EQ(CurveQuadratic::iddObjectType(), chiller.pumpElectricInputFunctionofPartLoadRatioCurve().iddObject().type());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.capacityCorrectionFunctionofCondenserTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.capacityCorrectionFunctionofChilledWaterTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.capacityCorrectionFunctionofGeneratorTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve().iddObject().type());
  EXPECT_EQ(CurveCubic::iddObjectType(), chiller.generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve().iddObject().type());
  const auto children = chiller.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(chiller.generatorHeatInputFunctionofPartLoadRatioCurve().handle(), children[0].handle());
  EXPECT_EQ(chiller.pumpElectricInputFunctionofPartLoadRatioCurve().handle(), children[1].handle());
  EXPECT_EQ(chiller.capacityCorrectionFunctionofCondenserTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(chiller.capacityCorrectionFunctionofChilledWaterTemperatureCurve().handle(), children[3].handle());
  EXPECT_EQ(chiller.capacityCorrectionFunctionofGeneratorTemperatureCurve().handle(), children[4].handle());
  EXPECT_EQ(chiller.generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve().handle(), children[5].handle());
  EXPECT_EQ(chiller.generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve().handle(), children[6].handle());
  std::set<openstudio::Handle> childHandles;
  for (const auto& child : children) {
    childHandles.insert(child.handle());
  }
  EXPECT_EQ(children.size(), childHandles.size());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.generatorLoop());
  EXPECT_EQ(openstudio::ComponentType::Cooling, chiller.componentType());
  EXPECT_TRUE(chiller.coolingFuelTypes().empty());
  EXPECT_TRUE(chiller.heatingFuelTypes().empty());
  EXPECT_TRUE(chiller.appGHeatingFuelTypes().empty());
  EXPECT_FALSE(chiller.autosizedNominalCapacity());
  EXPECT_FALSE(chiller.autosizedNominalPumpingPower());
  EXPECT_FALSE(chiller.autosizedDesignChilledWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignCondenserWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignGeneratorFluidFlowRate());
}

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);
  CurveCubic cubicCurve(model);
  CurveQuadratic quadraticCurve(model);

  const auto chillerFlowModes = ChillerAbsorptionIndirect::chillerFlowModeValues();
  EXPECT_FALSE(chillerFlowModes.empty());
  EXPECT_TRUE(std::find(chillerFlowModes.begin(), chillerFlowModes.end(), "ConstantFlow") != chillerFlowModes.end());

  const auto generatorHeatSourceTypes = ChillerAbsorptionIndirect::generatorHeatSourceTypeValues();
  EXPECT_FALSE(generatorHeatSourceTypes.empty());
  EXPECT_TRUE(std::find(generatorHeatSourceTypes.begin(), generatorHeatSourceTypes.end(), "Steam") != generatorHeatSourceTypes.end());
  EXPECT_TRUE(std::find(generatorHeatSourceTypes.begin(), generatorHeatSourceTypes.end(), "HotWater") != generatorHeatSourceTypes.end());

  EXPECT_TRUE(chiller.setNominalCapacity(210000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(210000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalPumpingPower(7300.0));
  ASSERT_TRUE(chiller.nominalPumpingPower());
  EXPECT_DOUBLE_EQ(7300.0, chiller.nominalPumpingPower().get());
  EXPECT_FALSE(chiller.isNominalPumpingPowerAutosized());
  chiller.autosizeNominalPumpingPower();
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.15));
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(1.0));
  EXPECT_DOUBLE_EQ(1.0, chiller.maximumPartLoadRatio());
  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.65));
  EXPECT_DOUBLE_EQ(0.65, chiller.optimumPartLoadRatio());

  EXPECT_TRUE(chiller.setDesignCondenserInletTemperature(35.0));
  EXPECT_DOUBLE_EQ(35.0, chiller.designCondenserInletTemperature());
  EXPECT_TRUE(chiller.setCondenserInletTemperatureLowerLimit(10.0));
  EXPECT_DOUBLE_EQ(10.0, chiller.condenserInletTemperatureLowerLimit());
  EXPECT_TRUE(chiller.setChilledWaterOutletTemperatureLowerLimit(5.0));
  EXPECT_DOUBLE_EQ(5.0, chiller.chilledWaterOutletTemperatureLowerLimit());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.013));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.013, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.018));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.018, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setChillerFlowMode("NotModulated"));
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setGeneratorHeatInputFunctionofPartLoadRatioCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.generatorHeatInputFunctionofPartLoadRatioCurve().handle());
  EXPECT_TRUE(chiller.setPumpElectricInputFunctionofPartLoadRatioCurve(quadraticCurve));
  EXPECT_EQ(quadraticCurve.handle(), chiller.pumpElectricInputFunctionofPartLoadRatioCurve().handle());
  EXPECT_TRUE(chiller.setCapacityCorrectionFunctionofCondenserTemperatureCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.capacityCorrectionFunctionofCondenserTemperatureCurve().handle());
  EXPECT_TRUE(chiller.setCapacityCorrectionFunctionofChilledWaterTemperatureCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.capacityCorrectionFunctionofChilledWaterTemperatureCurve().handle());
  EXPECT_TRUE(chiller.setCapacityCorrectionFunctionofGeneratorTemperatureCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.capacityCorrectionFunctionofGeneratorTemperatureCurve().handle());
  EXPECT_TRUE(chiller.setGeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.generatorHeatInputCorrectionFunctionofCondenserTemperatureCurve().handle());
  EXPECT_TRUE(chiller.setGeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve(cubicCurve));
  EXPECT_EQ(cubicCurve.handle(), chiller.generatorHeatInputCorrectionFunctionofChilledWaterTemperatureCurve().handle());

  EXPECT_TRUE(chiller.setGeneratorHeatSourceType("Steam"));
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());

  EXPECT_TRUE(chiller.setDesignGeneratorFluidFlowRate(0.01));
  ASSERT_TRUE(chiller.designGeneratorFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.01, chiller.designGeneratorFluidFlowRate().get());
  chiller.autosizeDesignGeneratorFluidFlowRate();
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());

  EXPECT_TRUE(chiller.setTemperatureLowerLimitGeneratorInlet(30.0));
  EXPECT_DOUBLE_EQ(30.0, chiller.temperatureLowerLimitGeneratorInlet());
  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamGenerator(2.0));
  EXPECT_DOUBLE_EQ(2.0, chiller.degreeofSubcoolinginSteamGenerator());
  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamCondensateLoop(12.0));
  EXPECT_DOUBLE_EQ(12.0, chiller.degreeofSubcoolinginSteamCondensateLoop());
  EXPECT_TRUE(chiller.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, chiller.sizingFactor());
}

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop generatorLoop(model);
  ChillerAbsorptionIndirect chiller(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserWaterLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());

  EXPECT_TRUE(generatorLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.generatorLoop());
  EXPECT_EQ(generatorLoop.handle(), chiller.generatorLoop()->handle());
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());
  EXPECT_FALSE(chiller.setGeneratorHeatSourceType("Steam"));
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());
  EXPECT_EQ(openstudio::ComponentType::Cooling, chiller.componentType());
  EXPECT_EQ(generatorLoop.heatingFuelTypes(), chiller.coolingFuelTypes());
  EXPECT_TRUE(chiller.heatingFuelTypes().empty());
  EXPECT_TRUE(chiller.appGHeatingFuelTypes().empty());

  ASSERT_TRUE(chiller.supplyInletModelObject());
  ASSERT_TRUE(chiller.supplyOutletModelObject());
  ASSERT_TRUE(chiller.demandInletModelObject());
  ASSERT_TRUE(chiller.demandOutletModelObject());
  ASSERT_TRUE(chiller.tertiaryInletModelObject());
  ASSERT_TRUE(chiller.tertiaryOutletModelObject());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.supplyInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.supplyOutletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(condenserWaterLoop.handle(), chiller.demandInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(condenserWaterLoop.handle(), chiller.demandOutletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(generatorLoop.handle(), chiller.tertiaryInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(generatorLoop.handle(), chiller.tertiaryOutletModelObject()->cast<Node>().plantLoop()->handle());

  Node chilledSupplyOutletNode = chilledWaterLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(chilledSupplyOutletNode));

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.generatorLoop());
  EXPECT_FALSE(chiller.tertiaryInletModelObject());
  EXPECT_FALSE(chiller.tertiaryOutletModelObject());
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());
  EXPECT_TRUE(chiller.coolingFuelTypes().empty());
  EXPECT_TRUE(chiller.heatingFuelTypes().empty());
  EXPECT_TRUE(chiller.appGHeatingFuelTypes().empty());
}

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);

  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop replacementCondenserWaterLoop(model);
  PlantLoop generatorLoop(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.generatorLoop());

  EXPECT_TRUE(condenserWaterLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserWaterLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_FALSE(chiller.generatorLoop());

  EXPECT_TRUE(chiller.setGeneratorHeatSourceType("Steam"));
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());

  Node initialGeneratorDemandNode = generatorLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(initialGeneratorDemandNode));
  ASSERT_TRUE(chiller.generatorLoop());
  EXPECT_EQ(generatorLoop.handle(), chiller.generatorLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserWaterLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  ASSERT_TRUE(chiller.tertiaryInletModelObject());
  ASSERT_TRUE(chiller.tertiaryOutletModelObject());
  EXPECT_EQ(generatorLoop.handle(), chiller.tertiaryInletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ(generatorLoop.handle(), chiller.tertiaryOutletModelObject()->cast<Node>().plantLoop()->handle());
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());
  EXPECT_FALSE(chiller.setGeneratorHeatSourceType("Steam"));

  Node replacementCondenserDemandNode = replacementCondenserWaterLoop.demandOutletNode();
  EXPECT_TRUE(chiller.addToNode(replacementCondenserDemandNode));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserWaterLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.generatorLoop());
  EXPECT_EQ(generatorLoop.handle(), chiller.generatorLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());

  EXPECT_TRUE(chiller.removeFromTertiaryPlantLoop());
  EXPECT_FALSE(chiller.generatorLoop());
  EXPECT_FALSE(chiller.tertiaryInletModelObject());
  EXPECT_FALSE(chiller.tertiaryOutletModelObject());
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());
  EXPECT_TRUE(chiller.coolingFuelTypes().empty());

  Node generatorSupplyNode = generatorLoop.supplyOutletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(generatorSupplyNode));
  EXPECT_FALSE(chiller.generatorLoop());

  Node generatorDemandNode = generatorLoop.demandInletNode();
  EXPECT_TRUE(chiller.addToNode(generatorDemandNode));
  ASSERT_TRUE(chiller.generatorLoop());
  EXPECT_EQ(generatorLoop.handle(), chiller.generatorLoop()->handle());
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(replacementCondenserWaterLoop.handle(), chiller.condenserWaterLoop()->handle());
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());
}

TEST_F(EPModelFixture, ChillerAbsorptionIndirect_AutosizedHelpersUseSqlFile) {
  Model model;
  ChillerAbsorptionIndirect chiller(model);
  ASSERT_TRUE(chiller.setName("Autosized Indirect Chiller"));

  chiller.autosizeNominalCapacity();
  chiller.autosizeNominalPumpingPower();
  chiller.autosizeDesignChilledWaterFlowRate();
  chiller.autosizeDesignCondenserWaterFlowRate();
  chiller.autosizeDesignGeneratorFluidFlowRate();

  const openstudio::path sqlPath =
    openstudio::tempDir() / openstudio::toPath("epmodel_chiller_absorption_indirect_autosized_" + openstudio::createUUID().toString() + ".sqlite");
  ASSERT_TRUE(makeChillerAbsorptionIndirectAutosizeSql(sqlPath).empty());

  openstudio::SqlFile sqlFile(sqlPath);
  ASSERT_TRUE(sqlFile.connectionOpen());
  EXPECT_TRUE(model.setSqlFile(sqlFile));

  ASSERT_TRUE(chiller.autosizedNominalCapacity());
  EXPECT_DOUBLE_EQ(111111.0, *chiller.autosizedNominalCapacity());
  ASSERT_TRUE(chiller.autosizedNominalPumpingPower());
  EXPECT_DOUBLE_EQ(2222.0, *chiller.autosizedNominalPumpingPower());
  ASSERT_TRUE(chiller.autosizedDesignChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.011, *chiller.autosizedDesignChilledWaterFlowRate());
  ASSERT_TRUE(chiller.autosizedDesignCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, *chiller.autosizedDesignCondenserWaterFlowRate());
  ASSERT_TRUE(chiller.autosizedDesignGeneratorFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.033, *chiller.autosizedDesignGeneratorFluidFlowRate());

  EXPECT_TRUE(model.resetSqlFile());
  EXPECT_FALSE(chiller.autosizedNominalCapacity());
  EXPECT_FALSE(chiller.autosizedNominalPumpingPower());
  EXPECT_FALSE(chiller.autosizedDesignChilledWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignCondenserWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignGeneratorFluidFlowRate());

  EXPECT_EQ(0, std::remove(openstudio::toString(sqlPath).c_str()));
}
