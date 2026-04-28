/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/GroundHeatExchangerPond.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatExchangerPond_DefaultConstructor) {
  Model model;
  GroundHeatExchangerPond ghx(model);
  EXPECT_EQ(GroundHeatExchangerPond::iddObjectType(), ghx.iddObject().type());
  EXPECT_FALSE(ghx.nameString().empty());

  EXPECT_DOUBLE_EQ(3.0, ghx.pondDepth());
  EXPECT_DOUBLE_EQ(100.0, ghx.pondArea());
  EXPECT_DOUBLE_EQ(0.02, ghx.hydronicTubingInsideDiameter());
  EXPECT_DOUBLE_EQ(0.025, ghx.hydronicTubingOutsideDiameter());
  EXPECT_DOUBLE_EQ(0.4, ghx.hydronicTubingThermalConductivity());
  EXPECT_DOUBLE_EQ(1.0, ghx.groundThermalConductivity());
  EXPECT_EQ(1, ghx.numberofTubingCircuits());
  EXPECT_DOUBLE_EQ(100.0, ghx.lengthofEachTubingCircuit());
}

TEST_F(EPModelFixture, GroundHeatExchangerPond_ScalarAccessors_RoundTrip) {
  Model model;
  GroundHeatExchangerPond ghx(model);

  EXPECT_TRUE(ghx.setPondDepth(4.0));
  EXPECT_DOUBLE_EQ(4.0, ghx.pondDepth());

  EXPECT_TRUE(ghx.setPondArea(250.0));
  EXPECT_DOUBLE_EQ(250.0, ghx.pondArea());

  EXPECT_TRUE(ghx.setHydronicTubingInsideDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, ghx.hydronicTubingInsideDiameter());

  EXPECT_TRUE(ghx.setHydronicTubingOutsideDiameter(0.035));
  EXPECT_DOUBLE_EQ(0.035, ghx.hydronicTubingOutsideDiameter());

  EXPECT_TRUE(ghx.setHydronicTubingThermalConductivity(0.55));
  EXPECT_DOUBLE_EQ(0.55, ghx.hydronicTubingThermalConductivity());

  EXPECT_TRUE(ghx.setGroundThermalConductivity(1.25));
  EXPECT_DOUBLE_EQ(1.25, ghx.groundThermalConductivity());

  EXPECT_TRUE(ghx.setNumberofTubingCircuits(3));
  EXPECT_EQ(3, ghx.numberofTubingCircuits());

  EXPECT_TRUE(ghx.setLengthofEachTubingCircuit(150.0));
  EXPECT_DOUBLE_EQ(150.0, ghx.lengthofEachTubingCircuit());
}
