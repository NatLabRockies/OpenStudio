/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/ComplexFenestrationPropertySolarAbsorbedLayers.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ComplexFenestrationPropertySolarAbsorbedLayers_DefaultConstructor) {
  Model model;
  ComplexFenestrationPropertySolarAbsorbedLayers object(model);
  EXPECT_EQ(ComplexFenestrationPropertySolarAbsorbedLayers::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, ComplexFenestrationPropertySolarAbsorbedLayers_ScalarAccessors_RoundTrip) {
  Model model;
  ComplexFenestrationPropertySolarAbsorbedLayers object(model);

  EXPECT_TRUE(object.setName("CFP Solar Absorbed Layers 1"));
  EXPECT_EQ("CFP Solar Absorbed Layers 1", object.nameString());
}
