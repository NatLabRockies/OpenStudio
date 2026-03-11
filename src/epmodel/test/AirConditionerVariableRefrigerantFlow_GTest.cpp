/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirConditionerVariableRefrigerantFlow.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);
  EXPECT_EQ(AirConditionerVariableRefrigerantFlow::iddObjectType(), vrf.iddObject().type());
  EXPECT_FALSE(vrf.nameString().empty());
}

TEST_F(EPModelFixture, AirConditionerVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  AirConditionerVariableRefrigerantFlow vrf(model);

  EXPECT_TRUE(vrf.setGrossRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(vrf.grossRatedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, vrf.grossRatedTotalCoolingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  vrf.autosizeGrossRatedTotalCoolingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(vrf.setGrossRatedCoolingCOP(3.4));
  EXPECT_DOUBLE_EQ(3.4, vrf.grossRatedCoolingCOP());

  EXPECT_TRUE(vrf.setGrossRatedHeatingCapacity(9876.0));
  ASSERT_TRUE(vrf.grossRatedHeatingCapacity());
  EXPECT_DOUBLE_EQ(9876.0, vrf.grossRatedHeatingCapacity().get());
  EXPECT_FALSE(vrf.isGrossRatedHeatingCapacityAutosized());

  vrf.autosizeGrossRatedHeatingCapacity();
  EXPECT_TRUE(vrf.isGrossRatedHeatingCapacityAutosized());

  EXPECT_TRUE(vrf.setRatedHeatingCapacitySizingRatio(1.15));
  EXPECT_DOUBLE_EQ(1.15, vrf.ratedHeatingCapacitySizingRatio());

  const auto heatingValues = AirConditionerVariableRefrigerantFlow::heatingPerformanceCurveOutdoorTemperatureTypeValues();
  ASSERT_FALSE(heatingValues.empty());
  EXPECT_TRUE(vrf.setHeatingPerformanceCurveOutdoorTemperatureType(heatingValues.front()));
  EXPECT_EQ(heatingValues.front(), vrf.heatingPerformanceCurveOutdoorTemperatureType());

  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(true));
  EXPECT_TRUE(vrf.heatPumpWasteHeatRecovery());
  EXPECT_TRUE(vrf.setHeatPumpWasteHeatRecovery(false));
  EXPECT_FALSE(vrf.heatPumpWasteHeatRecovery());

  EXPECT_TRUE(vrf.setNumberofCompressors(3));
  EXPECT_EQ(3, vrf.numberofCompressors());

  const auto defrostValues = AirConditionerVariableRefrigerantFlow::defrostStrategyValues();
  ASSERT_FALSE(defrostValues.empty());
  EXPECT_TRUE(vrf.setDefrostStrategy(defrostValues.front()));
  EXPECT_EQ(defrostValues.front(), vrf.defrostStrategy());

  const auto condenserValues = AirConditionerVariableRefrigerantFlow::condenserTypeValues();
  ASSERT_FALSE(condenserValues.empty());
  EXPECT_TRUE(vrf.setCondenserType(condenserValues.front()));
  EXPECT_FALSE(vrf.isCondenserTypeDefaulted());
  EXPECT_EQ(condenserValues.front(), vrf.condenserType());
  vrf.resetCondenserType();
  EXPECT_TRUE(vrf.condenserType().empty());
}
