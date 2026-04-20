/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/DesignSpecificationZoneHVACSizing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, DesignSpecificationZoneHVACSizing_DefaultConstructor) {
  Model model;
  DesignSpecificationZoneHVACSizing object(model);
  EXPECT_EQ(DesignSpecificationZoneHVACSizing::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, DesignSpecificationZoneHVACSizing_ScalarAccessors_RoundTrip) {
  Model model;
  DesignSpecificationZoneHVACSizing object(model);

  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateMethodDefaulted());
  EXPECT_EQ("SupplyAirFlowRate", object.coolingSupplyAirFlowRateMethod());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRateMethod("FlowPerFloorArea"));
  EXPECT_EQ("FlowPerFloorArea", object.coolingSupplyAirFlowRateMethod());
  EXPECT_FALSE(object.isCoolingSupplyAirFlowRateMethodDefaulted());
  object.resetCoolingSupplyAirFlowRateMethod();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateMethodDefaulted());

  EXPECT_FALSE(object.coolingSupplyAirFlowRate());
  EXPECT_FALSE(object.isCoolingSupplyAirFlowRateAutosized());
  object.autosizeCoolingSupplyAirFlowRate();
  EXPECT_TRUE(object.isCoolingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRate(0.8));
  ASSERT_TRUE(object.coolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.8, *object.coolingSupplyAirFlowRate());
  EXPECT_FALSE(object.isCoolingSupplyAirFlowRateAutosized());
  object.resetCoolingSupplyAirFlowRate();
  EXPECT_FALSE(object.coolingSupplyAirFlowRate());

  EXPECT_FALSE(object.coolingSupplyAirFlowRatePerFloorArea());
  EXPECT_TRUE(object.setCoolingSupplyAirFlowRatePerFloorArea(0.0012));
  ASSERT_TRUE(object.coolingSupplyAirFlowRatePerFloorArea());
  EXPECT_DOUBLE_EQ(0.0012, *object.coolingSupplyAirFlowRatePerFloorArea());
  object.resetCoolingSupplyAirFlowRatePerFloorArea();
  EXPECT_FALSE(object.coolingSupplyAirFlowRatePerFloorArea());

  EXPECT_FALSE(object.coolingFractionofAutosizedCoolingSupplyAirFlowRate());
  EXPECT_TRUE(object.setCoolingFractionofAutosizedCoolingSupplyAirFlowRate(0.75));
  ASSERT_TRUE(object.coolingFractionofAutosizedCoolingSupplyAirFlowRate());
  EXPECT_DOUBLE_EQ(0.75, *object.coolingFractionofAutosizedCoolingSupplyAirFlowRate());

  EXPECT_TRUE(object.isNoLoadSupplyAirFlowRateMethodDefaulted());
  EXPECT_EQ("SupplyAirFlowRate", object.noLoadSupplyAirFlowRateMethod());
  EXPECT_TRUE(object.setNoLoadSupplyAirFlowRateMethod("FractionOfAutosizedHeatingAirflow"));
  EXPECT_EQ("FractionOfAutosizedHeatingAirflow", object.noLoadSupplyAirFlowRateMethod());

  EXPECT_FALSE(object.noLoadSupplyAirFlowRate());
  object.autosizeNoLoadSupplyAirFlowRate();
  EXPECT_TRUE(object.isNoLoadSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setNoLoadSupplyAirFlowRate(0.55));
  EXPECT_FALSE(object.isNoLoadSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateMethodDefaulted());
  EXPECT_EQ("SupplyAirFlowRate", object.heatingSupplyAirFlowRateMethod());
  EXPECT_TRUE(object.setHeatingSupplyAirFlowRateMethod("FlowPerHeatingCapacity"));
  EXPECT_EQ("FlowPerHeatingCapacity", object.heatingSupplyAirFlowRateMethod());

  EXPECT_FALSE(object.heatingSupplyAirFlowRate());
  object.autosizeHeatingSupplyAirFlowRate();
  EXPECT_TRUE(object.isHeatingSupplyAirFlowRateAutosized());
  EXPECT_TRUE(object.setHeatingSupplyAirFlowRate(0.62));
  EXPECT_FALSE(object.isHeatingSupplyAirFlowRateAutosized());

  EXPECT_TRUE(object.isCoolingDesignCapacityMethodDefaulted());
  EXPECT_EQ("None", object.coolingDesignCapacityMethod());
  EXPECT_TRUE(object.setCoolingDesignCapacityMethod("CoolingDesignCapacity"));
  EXPECT_EQ("CoolingDesignCapacity", object.coolingDesignCapacityMethod());

  EXPECT_FALSE(object.coolingDesignCapacity());
  object.autosizeCoolingDesignCapacity();
  EXPECT_TRUE(object.isCoolingDesignCapacityAutosized());
  EXPECT_TRUE(object.setCoolingDesignCapacity(8500.0));
  EXPECT_FALSE(object.isCoolingDesignCapacityAutosized());

  EXPECT_FALSE(object.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_TRUE(object.setFractionofAutosizedCoolingDesignCapacity(0.92));
  ASSERT_TRUE(object.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.92, *object.fractionofAutosizedCoolingDesignCapacity());

  EXPECT_TRUE(object.isHeatingDesignCapacityMethodDefaulted());
  EXPECT_EQ("None", object.heatingDesignCapacityMethod());
  EXPECT_TRUE(object.setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
  EXPECT_EQ("HeatingDesignCapacity", object.heatingDesignCapacityMethod());

  EXPECT_FALSE(object.heatingDesignCapacity());
  object.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(object.isHeatingDesignCapacityAutosized());
  EXPECT_TRUE(object.setHeatingDesignCapacity(9200.0));
  EXPECT_FALSE(object.isHeatingDesignCapacityAutosized());

  EXPECT_FALSE(object.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_TRUE(object.setFractionofAutosizedHeatingDesignCapacity(0.88));
  ASSERT_TRUE(object.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.88, *object.fractionofAutosizedHeatingDesignCapacity());
}
