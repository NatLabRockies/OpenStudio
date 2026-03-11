/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/RefrigerationCompressorRack.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCompressorRack_DefaultConstructor) {
  Model model;
  RefrigerationCompressorRack rack(model);

  EXPECT_EQ(RefrigerationCompressorRack::iddObjectType(), rack.iddObjectType());
  EXPECT_EQ("Outdoors", rack.heatRejectionLocation());
  EXPECT_DOUBLE_EQ(2.0, rack.designCompressorRackCOP());
  EXPECT_DOUBLE_EQ(250.0, rack.designCondenserFanPower());
  EXPECT_EQ("AirCooled", rack.condenserType());
  EXPECT_EQ("VariableFlow", rack.waterCooledLoopFlowType());
  EXPECT_DOUBLE_EQ(55.0, rack.waterCooledCondenserMaximumWaterOutletTemperature());
  EXPECT_DOUBLE_EQ(10.0, rack.waterCooledCondenserMinimumWaterInletTemperature());
  EXPECT_DOUBLE_EQ(0.9, rack.evaporativeCondenserEffectiveness());
  EXPECT_FALSE(rack.waterCooledCondenserDesignFlowRate());
  EXPECT_FALSE(rack.waterCooledCondenserMaximumFlowRate());
  EXPECT_FALSE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_DOUBLE_EQ(200.0, rack.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, rack.basinHeaterSetpointTemperature());
  ASSERT_TRUE(rack.designEvaporativeCondenserWaterPumpPower());
  EXPECT_DOUBLE_EQ(1000.0, rack.designEvaporativeCondenserWaterPumpPower().value());
  EXPECT_FALSE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_EQ("General", rack.endUseSubcategory());
  EXPECT_TRUE(rack.isEndUseSubcategoryDefaulted());
}

TEST_F(EPModelFixture, RefrigerationCompressorRack_ScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCompressorRack rack(model);

  EXPECT_TRUE(rack.setHeatRejectionLocation("Zone"));
  EXPECT_TRUE(rack.setDesignCompressorRackCOP(2.5));
  EXPECT_TRUE(rack.setDesignCondenserFanPower(300.0));
  EXPECT_TRUE(rack.setCondenserType("EvaporativelyCooled"));
  EXPECT_TRUE(rack.setWaterCooledLoopFlowType("ConstantFlow"));
  EXPECT_TRUE(rack.setWaterCooledCondenserDesignFlowRate(0.002));
  EXPECT_TRUE(rack.setWaterCooledCondenserMaximumFlowRate(0.003));
  EXPECT_TRUE(rack.setWaterCooledCondenserMaximumWaterOutletTemperature(50.0));
  EXPECT_TRUE(rack.setWaterCooledCondenserMinimumWaterInletTemperature(12.0));
  EXPECT_TRUE(rack.setEvaporativeCondenserEffectiveness(0.8));
  EXPECT_TRUE(rack.setEvaporativeCondenserAirFlowRate(0.004));
  EXPECT_TRUE(rack.setBasinHeaterCapacity(220.0));
  EXPECT_TRUE(rack.setBasinHeaterSetpointTemperature(3.0));
  EXPECT_TRUE(rack.setDesignEvaporativeCondenserWaterPumpPower(1200.0));
  EXPECT_TRUE(rack.setEndUseSubcategory("Cooling"));

  EXPECT_EQ("Zone", rack.heatRejectionLocation());
  EXPECT_DOUBLE_EQ(2.5, rack.designCompressorRackCOP());
  EXPECT_DOUBLE_EQ(300.0, rack.designCondenserFanPower());
  EXPECT_EQ("EvaporativelyCooled", rack.condenserType());
  EXPECT_EQ("ConstantFlow", rack.waterCooledLoopFlowType());
  ASSERT_TRUE(rack.waterCooledCondenserDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.002, rack.waterCooledCondenserDesignFlowRate().value());
  ASSERT_TRUE(rack.waterCooledCondenserMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.003, rack.waterCooledCondenserMaximumFlowRate().value());
  EXPECT_DOUBLE_EQ(50.0, rack.waterCooledCondenserMaximumWaterOutletTemperature());
  EXPECT_DOUBLE_EQ(12.0, rack.waterCooledCondenserMinimumWaterInletTemperature());
  EXPECT_DOUBLE_EQ(0.8, rack.evaporativeCondenserEffectiveness());
  ASSERT_TRUE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.004, rack.evaporativeCondenserAirFlowRate().value());
  EXPECT_FALSE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_DOUBLE_EQ(220.0, rack.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(3.0, rack.basinHeaterSetpointTemperature());
  ASSERT_TRUE(rack.designEvaporativeCondenserWaterPumpPower());
  EXPECT_DOUBLE_EQ(1200.0, rack.designEvaporativeCondenserWaterPumpPower().value());
  EXPECT_FALSE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_EQ("Cooling", rack.endUseSubcategory());
  EXPECT_FALSE(rack.isEndUseSubcategoryDefaulted());

  rack.resetWaterCooledCondenserDesignFlowRate();
  EXPECT_FALSE(rack.waterCooledCondenserDesignFlowRate());
  rack.resetWaterCooledCondenserMaximumFlowRate();
  EXPECT_FALSE(rack.waterCooledCondenserMaximumFlowRate());
  EXPECT_TRUE(rack.autocalculateEvaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_FALSE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.autocalculateDesignEvaporativeCondenserWaterPumpPower());
  EXPECT_TRUE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_FALSE(rack.designEvaporativeCondenserWaterPumpPower());
  rack.resetEndUseSubcategory();
  EXPECT_TRUE(rack.isEndUseSubcategoryDefaulted());
}
