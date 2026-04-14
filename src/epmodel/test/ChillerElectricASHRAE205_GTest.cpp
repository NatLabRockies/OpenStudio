/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/ChillerElectricASHRAE205.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricASHRAE205_DefaultConstructor) {
  Model model;
  ChillerElectricASHRAE205 chiller(model);

  EXPECT_EQ(ChillerElectricASHRAE205::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.demandInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.tertiaryInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.oilCoolerInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), chiller.auxiliaryInletPort());

  EXPECT_EQ("Linear", chiller.performanceInterpolationMethod());
  EXPECT_DOUBLE_EQ(1.0, chiller.sizingFactor());
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());
  EXPECT_FALSE(chiller.ambientTemperatureSchedule());
  EXPECT_FALSE(chiller.ambientTemperatureZone());
  EXPECT_FALSE(chiller.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("General", chiller.endUseSubcategory());
  EXPECT_TRUE(chiller.isEndUseSubcategoryDefaulted());
  EXPECT_FALSE(chiller.autosizedRatedCapacity());
  EXPECT_FALSE(chiller.autosizedChilledWaterMaximumRequestedFlowRate());
  EXPECT_FALSE(chiller.autosizedCondenserMaximumRequestedFlowRate());
  EXPECT_FALSE(chiller.chilledWaterLoop());
  EXPECT_FALSE(chiller.condenserWaterLoop());
  EXPECT_FALSE(chiller.heatRecoveryLoop());
  EXPECT_FALSE(chiller.oilCoolerLoop());
  EXPECT_FALSE(chiller.auxiliaryLoop());
}

TEST_F(EPModelFixture, ChillerElectricASHRAE205_ScalarAndAmbientParity) {
  Model model;
  ChillerElectricASHRAE205 chiller(model);
  ScheduleConstant ambientSchedule(model);
  ThermalZone thermalZone(model);

  EXPECT_TRUE(chiller.setPerformanceInterpolationMethod("Cubic"));
  EXPECT_EQ("Cubic", chiller.performanceInterpolationMethod());
  EXPECT_FALSE(chiller.setPerformanceInterpolationMethod("BADENUM"));
  EXPECT_EQ("Cubic", chiller.performanceInterpolationMethod());

  EXPECT_TRUE(chiller.setRatedCapacity(810000.0));
  ASSERT_TRUE(chiller.ratedCapacity());
  EXPECT_DOUBLE_EQ(810000.0, chiller.ratedCapacity().get());
  EXPECT_FALSE(chiller.isRatedCapacityAutosized());
  chiller.autosizeRatedCapacity();
  EXPECT_TRUE(chiller.isRatedCapacityAutosized());
  EXPECT_FALSE(chiller.autosizedRatedCapacity());

  EXPECT_TRUE(chiller.setSizingFactor(1.08));
  EXPECT_DOUBLE_EQ(1.08, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setAmbientTemperatureSchedule(ambientSchedule));
  ASSERT_TRUE(chiller.ambientTemperatureSchedule());
  EXPECT_EQ(ambientSchedule.handle(), chiller.ambientTemperatureSchedule()->handle());
  EXPECT_EQ("Schedule", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_EQ("Schedule", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureSchedule();
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());

  EXPECT_TRUE(chiller.setAmbientTemperatureZone(thermalZone));
  ASSERT_TRUE(chiller.ambientTemperatureZone());
  EXPECT_EQ(thermalZone.handle(), chiller.ambientTemperatureZone()->handle());
  EXPECT_EQ("Zone", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureSchedule();
  EXPECT_EQ("Zone", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureZone();
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());

  EXPECT_TRUE(chiller.setAmbientTemperatureZone(thermalZone));
  EXPECT_EQ("Zone", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_EQ("Zone", chiller.ambientTemperatureIndicator());

  EXPECT_TRUE(chiller.setAmbientTemperatureOutdoorAirNodeName("ASHRAE205 OA Node"));
  ASSERT_TRUE(chiller.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("ASHRAE205 OA Node", chiller.ambientTemperatureOutdoorAirNodeName().get());
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());

  EXPECT_TRUE(chiller.setChilledWaterMaximumRequestedFlowRate(0.11));
  ASSERT_TRUE(chiller.chilledWaterMaximumRequestedFlowRate());
  EXPECT_DOUBLE_EQ(0.11, chiller.chilledWaterMaximumRequestedFlowRate().get());
  EXPECT_FALSE(chiller.isChilledWaterMaximumRequestedFlowRateAutosized());
  chiller.autosizeChilledWaterMaximumRequestedFlowRate();
  EXPECT_TRUE(chiller.isChilledWaterMaximumRequestedFlowRateAutosized());
  EXPECT_FALSE(chiller.autosizedChilledWaterMaximumRequestedFlowRate());

  EXPECT_TRUE(chiller.setCondenserMaximumRequestedFlowRate(0.16));
  ASSERT_TRUE(chiller.condenserMaximumRequestedFlowRate());
  EXPECT_DOUBLE_EQ(0.16, chiller.condenserMaximumRequestedFlowRate().get());
  EXPECT_FALSE(chiller.isCondenserMaximumRequestedFlowRateAutosized());
  chiller.autosizeCondenserMaximumRequestedFlowRate();
  EXPECT_TRUE(chiller.isCondenserMaximumRequestedFlowRateAutosized());
  EXPECT_FALSE(chiller.autosizedCondenserMaximumRequestedFlowRate());

  EXPECT_TRUE(chiller.setChillerFlowMode("ConstantFlow"));
  EXPECT_EQ("ConstantFlow", chiller.chillerFlowMode());

  EXPECT_TRUE(chiller.setOilCoolerDesignFlowRate(0.01));
  ASSERT_TRUE(chiller.oilCoolerDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.01, chiller.oilCoolerDesignFlowRate().get());
  chiller.resetOilCoolerDesignFlowRate();
  EXPECT_FALSE(chiller.oilCoolerDesignFlowRate());

  EXPECT_TRUE(chiller.setAuxiliaryCoolingDesignFlowRate(0.02));
  ASSERT_TRUE(chiller.auxiliaryCoolingDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.02, chiller.auxiliaryCoolingDesignFlowRate().get());
  chiller.resetAuxiliaryCoolingDesignFlowRate();
  EXPECT_FALSE(chiller.auxiliaryCoolingDesignFlowRate());

  EXPECT_TRUE(chiller.setEndUseSubcategory("Cooling"));
  EXPECT_EQ("Cooling", chiller.endUseSubcategory());
  EXPECT_FALSE(chiller.isEndUseSubcategoryDefaulted());
  chiller.resetEndUseSubcategory();
  EXPECT_TRUE(chiller.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, ChillerElectricASHRAE205_PlantLoopParity) {
  Model model;
  PlantLoop chilledWaterLoop(model);
  PlantLoop condenserLoop(model);
  PlantLoop heatRecoveryLoop(model);
  PlantLoop oilCoolerLoop(model);
  PlantLoop auxiliaryLoop(model);
  ChillerElectricASHRAE205 chiller(model);

  EXPECT_TRUE(chilledWaterLoop.addSupplyBranchForComponent(chiller));
  ASSERT_TRUE(chiller.chilledWaterLoop());
  EXPECT_EQ(chilledWaterLoop.handle(), chiller.chilledWaterLoop()->handle());
  EXPECT_TRUE(chiller.chilledWaterInletNode());
  EXPECT_TRUE(chiller.chilledWaterOutletNode());

  EXPECT_TRUE(condenserLoop.addDemandBranchForComponent(chiller));
  ASSERT_TRUE(chiller.condenserWaterLoop());
  EXPECT_EQ(condenserLoop.handle(), chiller.condenserWaterLoop()->handle());
  EXPECT_TRUE(chiller.condenserInletNode());
  EXPECT_TRUE(chiller.condenserOutletNode());

  EXPECT_FALSE(heatRecoveryLoop.addDemandBranchForComponent(chiller));
  auto heatRecoveryDemandInletNode = heatRecoveryLoop.demandInletNode();
  EXPECT_FALSE(chiller.addToTertiaryNode(heatRecoveryDemandInletNode));
  EXPECT_FALSE(chiller.heatRecoveryLoop());

  EXPECT_TRUE(chiller.addDemandBranchOnOilCoolerLoop(oilCoolerLoop));
  ASSERT_TRUE(chiller.oilCoolerLoop());
  EXPECT_EQ(oilCoolerLoop.handle(), chiller.oilCoolerLoop()->handle());
  EXPECT_TRUE(chiller.oilCoolerInletNode());
  EXPECT_TRUE(chiller.oilCoolerOutletNode());

  EXPECT_TRUE(chiller.addDemandBranchOnAuxiliaryLoop(auxiliaryLoop));
  ASSERT_TRUE(chiller.auxiliaryLoop());
  EXPECT_EQ(auxiliaryLoop.handle(), chiller.auxiliaryLoop()->handle());
  EXPECT_TRUE(chiller.auxiliaryInletNode());
  EXPECT_TRUE(chiller.auxiliaryOutletNode());

  EXPECT_TRUE(chiller.removeFromOilCoolerLoop());
  EXPECT_FALSE(chiller.oilCoolerLoop());

  EXPECT_TRUE(chiller.removeFromAuxiliaryLoop());
  EXPECT_FALSE(chiller.auxiliaryLoop());
}
