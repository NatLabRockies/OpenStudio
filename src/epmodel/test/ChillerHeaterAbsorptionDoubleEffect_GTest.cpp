/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ChillerHeaterAbsorptionDoubleEffect.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ChillerHeaterAbsorptionDoubleEffect_DefaultConstructor) {
  Model model;
  ChillerHeaterAbsorptionDoubleEffect chiller(model);
  EXPECT_EQ(ChillerHeaterAbsorptionDoubleEffect::iddObjectType(), chiller.iddObject().type());
  EXPECT_FALSE(chiller.nameString().empty());
}

TEST_F(EPModelFixture, ChillerHeaterAbsorptionDoubleEffect_ScalarAccessors_RoundTrip) {
  Model model;
  ChillerHeaterAbsorptionDoubleEffect chiller(model);

  EXPECT_TRUE(chiller.setNominalCoolingCapacity(450000.0));
  ASSERT_TRUE(chiller.nominalCoolingCapacity());
  EXPECT_DOUBLE_EQ(450000.0, chiller.nominalCoolingCapacity().get());
  EXPECT_FALSE(chiller.isNominalCoolingCapacityAutosized());
  chiller.autosizeNominalCoolingCapacity();
  EXPECT_TRUE(chiller.isNominalCoolingCapacityAutosized());
  chiller.resetNominalCoolingCapacity();
  EXPECT_TRUE(chiller.isNominalCoolingCapacityDefaulted());

  EXPECT_TRUE(chiller.setHeatingtoCoolingCapacityRatio(0.92));
  EXPECT_DOUBLE_EQ(0.92, chiller.heatingtoCoolingCapacityRatio());

  EXPECT_TRUE(chiller.setThermalEnergyInputtoCoolingOutputRatio(0.98));
  EXPECT_DOUBLE_EQ(0.98, chiller.thermalEnergyInputtoCoolingOutputRatio());

  EXPECT_TRUE(chiller.setThermalEnergyInputtoHeatingOutputRatio(1.18));
  EXPECT_DOUBLE_EQ(1.18, chiller.thermalEnergyInputtoHeatingOutputRatio());

  EXPECT_TRUE(chiller.setDesignChilledWaterFlowRate(0.026));
  ASSERT_TRUE(chiller.designChilledWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.026, chiller.designChilledWaterFlowRate().get());
  chiller.autosizeDesignChilledWaterFlowRate();
  EXPECT_TRUE(chiller.isDesignChilledWaterFlowRateAutosized());

  EXPECT_TRUE(chiller.setTemperatureCurveInputVariable("LeavingCondenser"));
  EXPECT_EQ("LeavingCondenser", chiller.temperatureCurveInputVariable());

  EXPECT_TRUE(chiller.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", chiller.condenserType());

  EXPECT_TRUE(chiller.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, chiller.sizingFactor());
}
