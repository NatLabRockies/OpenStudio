/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../StraightComponent/BoilerSteam.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, BoilerSteam_DefaultConstructor) {
  Model model;
  BoilerSteam boiler(model);
  EXPECT_EQ(BoilerSteam::iddObjectType(), boiler.iddObject().type());
  EXPECT_FALSE(boiler.nameString().empty());
}

TEST_F(EPModelFixture, BoilerSteam_ScalarAccessors_RoundTrip) {
  Model model;
  BoilerSteam boiler(model);

  EXPECT_TRUE(boiler.setFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", boiler.fuelType());

  EXPECT_TRUE(boiler.setMaximumOperatingPressure(170000.0));
  ASSERT_TRUE(boiler.maximumOperatingPressure());
  EXPECT_DOUBLE_EQ(170000.0, boiler.maximumOperatingPressure().get());
  boiler.resetMaximumOperatingPressure();
  ASSERT_TRUE(boiler.maximumOperatingPressure());
  EXPECT_NE(170000.0, boiler.maximumOperatingPressure().get());

  EXPECT_TRUE(boiler.setNominalCapacity(12000.0));
  ASSERT_TRUE(boiler.nominalCapacity());
  EXPECT_DOUBLE_EQ(12000.0, boiler.nominalCapacity().get());
  EXPECT_FALSE(boiler.isNominalCapacityAutosized());
  boiler.autosizeNominalCapacity();
  EXPECT_TRUE(boiler.isNominalCapacityAutosized());
  EXPECT_FALSE(boiler.autosizedNominalCapacity());

  EXPECT_TRUE(boiler.setMinimumPartLoadRatio(0.15));
  ASSERT_TRUE(boiler.minimumPartLoadRatio());
  EXPECT_DOUBLE_EQ(0.15, boiler.minimumPartLoadRatio().get());

  EXPECT_TRUE(boiler.setCoefficient1ofFuelUseFunctionofPartLoadRatioCurve(0.9));
  ASSERT_TRUE(boiler.coefficient1ofFuelUseFunctionofPartLoadRatioCurve());
  EXPECT_DOUBLE_EQ(0.9, boiler.coefficient1ofFuelUseFunctionofPartLoadRatioCurve().get());

  EXPECT_TRUE(boiler.setSizingFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, boiler.sizingFactor());

  EXPECT_TRUE(boiler.setEndUseSubcategory("Boiler"));
  EXPECT_EQ("Boiler", boiler.endUseSubcategory());
}

TEST_F(EPModelFixture, BoilerSteam_AddToNode_PlantSupplyOnly) {
  Model model;
  BoilerSteam boiler(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(boiler.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(boiler.addToNode(supplyOutletNode));
  EXPECT_EQ("Steam", plantLoop.fluidType());
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_FALSE(boiler.addToNode(demandOutletNode));
  EXPECT_EQ(5u, plantLoop.demandComponents().size());
}
