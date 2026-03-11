/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SolarCollectorPerformanceFlatPlate.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SolarCollectorPerformanceFlatPlate_DefaultConstructor) {
  Model model;
  SolarCollectorPerformanceFlatPlate object(model);
  EXPECT_EQ(SolarCollectorPerformanceFlatPlate::iddObjectType(), object.iddObject().type());
  EXPECT_FALSE(object.nameString().empty());
}

TEST_F(EPModelFixture, SolarCollectorPerformanceFlatPlate_ScalarAccessors_RoundTrip) {
  Model model;
  SolarCollectorPerformanceFlatPlate object(model);

  EXPECT_TRUE(object.setGrossArea(2.9));
  EXPECT_DOUBLE_EQ(2.9, object.grossArea());

  const auto testFluidValues = SolarCollectorPerformanceFlatPlate::testFluidValues();
  EXPECT_FALSE(testFluidValues.empty());
  EXPECT_TRUE(object.setTestFluid(testFluidValues.front()));
  EXPECT_EQ(testFluidValues.front(), object.testFluid());
  EXPECT_FALSE(object.isTestFluidDefaulted());
  object.resetTestFluid();
  EXPECT_TRUE(object.isTestFluidDefaulted());

  EXPECT_TRUE(object.setTestFlowRate(0.0000388));
  EXPECT_DOUBLE_EQ(0.0000388, object.testFlowRate());

  const auto testCorrelationTypeValues = SolarCollectorPerformanceFlatPlate::testCorrelationTypeValues();
  EXPECT_FALSE(testCorrelationTypeValues.empty());
  EXPECT_TRUE(object.setTestCorrelationType(testCorrelationTypeValues.front()));
  EXPECT_EQ(testCorrelationTypeValues.front(), object.testCorrelationType());

  EXPECT_TRUE(object.setCoefficient1ofEfficiencyEquation(0.691));
  EXPECT_DOUBLE_EQ(0.691, object.coefficient1ofEfficiencyEquation());

  EXPECT_TRUE(object.setCoefficient2ofEfficiencyEquation(-3.396));
  EXPECT_DOUBLE_EQ(-3.396, object.coefficient2ofEfficiencyEquation());

  EXPECT_FALSE(object.coefficient3ofEfficiencyEquation());
  EXPECT_TRUE(object.setCoefficient3ofEfficiencyEquation(-0.00193));
  ASSERT_TRUE(object.coefficient3ofEfficiencyEquation());
  EXPECT_DOUBLE_EQ(-0.00193, object.coefficient3ofEfficiencyEquation().get());
  object.resetCoefficient3ofEfficiencyEquation();
  EXPECT_FALSE(object.coefficient3ofEfficiencyEquation());

  EXPECT_FALSE(object.coefficient2ofIncidentAngleModifier());
  EXPECT_TRUE(object.setCoefficient2ofIncidentAngleModifier(-0.1939));
  ASSERT_TRUE(object.coefficient2ofIncidentAngleModifier());
  EXPECT_DOUBLE_EQ(-0.1939, object.coefficient2ofIncidentAngleModifier().get());
  object.resetCoefficient2ofIncidentAngleModifier();
  EXPECT_FALSE(object.coefficient2ofIncidentAngleModifier());

  EXPECT_FALSE(object.coefficient3ofIncidentAngleModifier());
  EXPECT_TRUE(object.setCoefficient3ofIncidentAngleModifier(-0.0055));
  ASSERT_TRUE(object.coefficient3ofIncidentAngleModifier());
  EXPECT_DOUBLE_EQ(-0.0055, object.coefficient3ofIncidentAngleModifier().get());
  object.resetCoefficient3ofIncidentAngleModifier();
  EXPECT_FALSE(object.coefficient3ofIncidentAngleModifier());
}
