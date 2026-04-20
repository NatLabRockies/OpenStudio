/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <sqlite3.h>

#include <cstdio>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerAbsorption.hpp"

#include <utilities/idd/Chiller_Absorption_FieldEnums.hxx>

#include "../../utilities/core/Path.hpp"
#include "../../utilities/core/UUID.hpp"
#include "../../utilities/sql/SqlFile.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

namespace {

std::string makeChillerAbsorptionAutosizeSql(const openstudio::path& sqlPath) {
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
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption','AUTOSIZED CHILLER','Design Size Nominal Capacity','W',111111.0);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption','AUTOSIZED CHILLER','Design Size Nominal Pumping Power','W',2222.0);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption','AUTOSIZED CHILLER','Design Size Design Chilled Water Flow Rate','m3/s',0.011);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption','AUTOSIZED CHILLER','Design Size Design Condenser Water Flow Rate','m3/s',0.022);
    INSERT INTO ComponentSizes VALUES ('Chiller:Absorption','AUTOSIZED CHILLER','Design Size Design Generator Fluid Flow Rate','m3/s',0.033);
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

TEST_F(EPModelFixture, ChillerAbsorption_DefaultConstructor) {
  Model model;
  ChillerAbsorption chiller(model);
  EXPECT_EQ(ChillerAbsorption::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::ChilledWaterInletNodeName, chiller.supplyInletPort());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::ChilledWaterOutletNodeName, chiller.supplyOutletPort());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::CondenserInletNodeName, chiller.demandInletPort());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::CondenserOutletNodeName, chiller.demandOutletPort());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::GeneratorInletNodeName, chiller.tertiaryInletPort());
  EXPECT_EQ(openstudio::Chiller_AbsorptionFields::GeneratorOutletNodeName, chiller.tertiaryOutletPort());
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());
  EXPECT_DOUBLE_EQ(0.15, chiller.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(1.0, chiller.maximumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.65, chiller.optimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(35.0, chiller.designCondenserInletTemperature());
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());
  EXPECT_DOUBLE_EQ(0.03303, chiller.coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(0.6852, chiller.coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(0.2818, chiller.coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(1.0, chiller.coefficient1ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(0.0, chiller.coefficient2ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(0.0, chiller.coefficient3ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(5.0, chiller.chilledWaterOutletTemperatureLowerLimit());
  EXPECT_EQ("NotModulated", chiller.chillerFlowMode());
  EXPECT_EQ("Steam", chiller.generatorHeatSourceType());
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());
  EXPECT_DOUBLE_EQ(1.0, chiller.degreeofSubcoolinginSteamGenerator());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.generatorLoop());
  EXPECT_FALSE(chiller.autosizedNominalCapacity());
  EXPECT_FALSE(chiller.autosizedNominalPumpingPower());
  EXPECT_FALSE(chiller.autosizedDesignChilledWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignCondenserWaterFlowRate());
  EXPECT_FALSE(chiller.autosizedDesignGeneratorFluidFlowRate());
}

TEST_F(EPModelFixture, ChillerAbsorption_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerAbsorption chiller(model);

  const auto chillerFlowModes = ChillerAbsorption::chillerFlowModeValues();
  EXPECT_FALSE(chillerFlowModes.empty());
  EXPECT_TRUE(std::find(chillerFlowModes.begin(), chillerFlowModes.end(), "ConstantFlow") != chillerFlowModes.end());

  const auto generatorHeatSourceTypes = ChillerAbsorption::generatorHeatSourceTypeValues();
  EXPECT_FALSE(generatorHeatSourceTypes.empty());
  EXPECT_TRUE(std::find(generatorHeatSourceTypes.begin(), generatorHeatSourceTypes.end(), "Steam") != generatorHeatSourceTypes.end());
  EXPECT_TRUE(std::find(generatorHeatSourceTypes.begin(), generatorHeatSourceTypes.end(), "HotWater") != generatorHeatSourceTypes.end());

  EXPECT_TRUE(chiller.setNominalCapacity(120000.0));
  ASSERT_TRUE(chiller.nominalCapacity());
  EXPECT_DOUBLE_EQ(120000.0, chiller.nominalCapacity().get());
  EXPECT_FALSE(chiller.isNominalCapacityAutosized());
  chiller.autosizeNominalCapacity();
  EXPECT_TRUE(chiller.isNominalCapacityAutosized());

  EXPECT_TRUE(chiller.setNominalPumpingPower(4200.0));
  ASSERT_TRUE(chiller.nominalPumpingPower());
  EXPECT_DOUBLE_EQ(4200.0, chiller.nominalPumpingPower().get());
  EXPECT_FALSE(chiller.isNominalPumpingPowerAutosized());
  chiller.autosizeNominalPumpingPower();
  EXPECT_TRUE(chiller.isNominalPumpingPowerAutosized());

  EXPECT_TRUE(chiller.setMinimumPartLoadRatio(0.2));
  EXPECT_DOUBLE_EQ(0.2, chiller.minimumPartLoadRatio());
  EXPECT_TRUE(chiller.setMaximumPartLoadRatio(0.95));
  EXPECT_DOUBLE_EQ(0.95, chiller.maximumPartLoadRatio());
  EXPECT_TRUE(chiller.setOptimumPartLoadRatio(0.7));
  EXPECT_DOUBLE_EQ(0.7, chiller.optimumPartLoadRatio());

  EXPECT_TRUE(chiller.setDesignCondenserInletTemperature(29.5));
  EXPECT_DOUBLE_EQ(29.5, chiller.designCondenserInletTemperature());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.011));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.011, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setDesignCondenserWaterFlowRate(0.022));
  ASSERT_TRUE(chiller.designCondenserWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.022, chiller.designCondenserWaterFlowRate().get());
  chiller.autosizeDesignCondenserWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignCondenserWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setCoefficient1oftheHotWaterorSteamUsePartLoadRatioCurve(0.03));
  EXPECT_DOUBLE_EQ(0.03, chiller.coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient2oftheHotWaterorSteamUsePartLoadRatioCurve(0.68));
  EXPECT_DOUBLE_EQ(0.68, chiller.coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient3oftheHotWaterorSteamUsePartLoadRatioCurve(0.29));
  EXPECT_DOUBLE_EQ(0.29, chiller.coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve());

  EXPECT_TRUE(chiller.setCoefficient1ofthePumpElectricUsePartLoadRatioCurve(1.0));
  EXPECT_DOUBLE_EQ(1.0, chiller.coefficient1ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient2ofthePumpElectricUsePartLoadRatioCurve(0.01));
  EXPECT_DOUBLE_EQ(0.01, chiller.coefficient2ofthePumpElectricUsePartLoadRatioCurve());
  EXPECT_TRUE(chiller.setCoefficient3ofthePumpElectricUsePartLoadRatioCurve(0.001));
  EXPECT_DOUBLE_EQ(0.001, chiller.coefficient3ofthePumpElectricUsePartLoadRatioCurve());

  EXPECT_TRUE(chiller.setChilledWaterOutletTemperatureLowerLimit(5.5));
  EXPECT_DOUBLE_EQ(5.5, chiller.chilledWaterOutletTemperatureLowerLimit());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());
  EXPECT_TRUE(chiller.setGeneratorHeatSourceType("HotWater"));
  EXPECT_EQ("HotWater", chiller.generatorHeatSourceType());

  EXPECT_TRUE(chiller.setDesignGeneratorFluidFlowRate(0.007));
  ASSERT_TRUE(chiller.designGeneratorFluidFlowRate());
  EXPECT_DOUBLE_EQ(0.007, chiller.designGeneratorFluidFlowRate().get());
  chiller.autosizeDesignGeneratorFluidFlowRate();
  EXPECT_TRUE(chiller.isDesignGeneratorFluidFlowRateAutosized());

  EXPECT_TRUE(chiller.setDegreeofSubcoolinginSteamGenerator(1.2));
  EXPECT_DOUBLE_EQ(1.2, chiller.degreeofSubcoolinginSteamGenerator());

  EXPECT_TRUE(chiller.setSizingFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, chiller.sizingFactor());
}

TEST_F(EPModelFixture, ChillerAbsorption_PlantLoopAttachmentParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserWaterLoop(model);
  PlantLoop generatorLoop(model);
  ChillerAbsorption chiller(model);

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
}

TEST_F(EPModelFixture, ChillerAbsorption_AddToNodeDemandRoutingParity) {
  Model model;
  ChillerAbsorption chiller(model);

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

TEST_F(EPModelFixture, ChillerAbsorption_AutosizedHelpersUseSqlFile) {
  Model model;
  ChillerAbsorption chiller(model);
  ASSERT_TRUE(chiller.setName("Autosized Chiller"));

  chiller.autosizeNominalCapacity();
  chiller.autosizeNominalPumpingPower();
  chiller.autosizeDesignChilledWaterFlowRate();
  chiller.autosizeDesignCondenserWaterFlowRate();
  chiller.autosizeDesignGeneratorFluidFlowRate();

  const openstudio::path sqlPath =
    openstudio::tempDir() / openstudio::toPath("epmodel_chiller_absorption_autosized_" + openstudio::createUUID().toString() + ".sqlite");
  ASSERT_TRUE(makeChillerAbsorptionAutosizeSql(sqlPath).empty());

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
