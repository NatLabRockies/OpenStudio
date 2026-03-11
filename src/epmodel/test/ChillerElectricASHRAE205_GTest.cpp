/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../WaterToWaterComponent/ChillerElectricASHRAE205.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerElectricASHRAE205_DefaultConstructor) {
  Model model;
  ChillerElectricASHRAE205 chiller(model);
  EXPECT_EQ(ChillerElectricASHRAE205::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerElectricASHRAE205_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerElectricASHRAE205 chiller(model);

  EXPECT_TRUE(chiller.setPerformanceInterpolationMethod("Linear"));
  EXPECT_EQ("Linear", chiller.performanceInterpolationMethod());

  EXPECT_TRUE(chiller.setRatedCapacity(810000.0));
  ASSERT_TRUE(chiller.ratedCapacity());
  EXPECT_DOUBLE_EQ(810000.0, chiller.ratedCapacity().get());
  EXPECT_FALSE(chiller.isRatedCapacityAutosized());
  chiller.autosizeRatedCapacity();
  EXPECT_TRUE(chiller.isRatedCapacityAutosized());

  EXPECT_TRUE(chiller.setSizingFactor(1.08));
  EXPECT_DOUBLE_EQ(1.08, chiller.sizingFactor());

  EXPECT_TRUE(chiller.setAmbientTemperatureOutdoorAirNodeName("ASHRAE205 OA Node"));
  ASSERT_TRUE(chiller.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ("ASHRAE205 OA Node", chiller.ambientTemperatureOutdoorAirNodeName().get());
  EXPECT_EQ("Outdoors", chiller.ambientTemperatureIndicator());
  chiller.resetAmbientTemperatureOutdoorAirNodeName();
  EXPECT_TRUE(chiller.ambientTemperatureOutdoorAirNodeName());

  EXPECT_TRUE(chiller.setChilledWaterMaximumRequestedFlowRate(0.11));
  ASSERT_TRUE(chiller.chilledWaterMaximumRequestedFlowRate());
  EXPECT_DOUBLE_EQ(0.11, chiller.chilledWaterMaximumRequestedFlowRate().get());
  EXPECT_FALSE(chiller.isChilledWaterMaximumRequestedFlowRateAutosized());
  chiller.autosizeChilledWaterMaximumRequestedFlowRate();
  EXPECT_TRUE(chiller.isChilledWaterMaximumRequestedFlowRateAutosized());

  EXPECT_TRUE(chiller.setCondenserMaximumRequestedFlowRate(0.16));
  ASSERT_TRUE(chiller.condenserMaximumRequestedFlowRate());
  EXPECT_DOUBLE_EQ(0.16, chiller.condenserMaximumRequestedFlowRate().get());
  EXPECT_FALSE(chiller.isCondenserMaximumRequestedFlowRateAutosized());
  chiller.autosizeCondenserMaximumRequestedFlowRate();
  EXPECT_TRUE(chiller.isCondenserMaximumRequestedFlowRateAutosized());

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
