/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowMaterialScreenEquivalentLayer.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowMaterialScreenEquivalentLayer_DefaultConstructor) {
  Model model;
  WindowMaterialScreenEquivalentLayer layer(model);
  EXPECT_EQ(WindowMaterialScreenEquivalentLayer::iddObjectType(), layer.iddObject().type());
  EXPECT_FALSE(layer.screenBeamBeamSolarTransmittance());
  EXPECT_TRUE(layer.isScreenBeamBeamSolarTransmittanceAutocalculated());
  EXPECT_DOUBLE_EQ(0.02, layer.screenInfraredTransmittance());
  EXPECT_DOUBLE_EQ(0.93, layer.screenInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.025, layer.screenWireSpacing());
  EXPECT_DOUBLE_EQ(0.005, layer.screenWireDiameter());
}

TEST_F(EPModelFixture, WindowMaterialScreenEquivalentLayer_ScalarAccessors_RoundTrip) {
  Model model;
  WindowMaterialScreenEquivalentLayer layer(model);

  EXPECT_TRUE(layer.setScreenBeamBeamSolarTransmittance(0.45));
  EXPECT_TRUE(layer.setScreenBeamDiffuseSolarTransmittance(0.17));
  EXPECT_TRUE(layer.setScreenBeamDiffuseSolarReflectance(0.12));
  EXPECT_TRUE(layer.setScreenBeamBeamVisibleSolarTransmittance(0.22));
  EXPECT_TRUE(layer.setScreenBeamDiffuseVisibleSolarTransmittance(0.08));
  EXPECT_TRUE(layer.setScreenBeamDiffuseVisibleSolarReflectance(0.05));
  EXPECT_TRUE(layer.setScreenInfraredTransmittance(0.11));
  EXPECT_TRUE(layer.setScreenInfraredEmissivity(0.88));
  EXPECT_TRUE(layer.setScreenWireSpacing(0.03));
  EXPECT_TRUE(layer.setScreenWireDiameter(0.004));

  ASSERT_TRUE(layer.screenBeamBeamSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.45, *layer.screenBeamBeamSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.17, layer.screenBeamDiffuseSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.12, layer.screenBeamDiffuseSolarReflectance());
  EXPECT_DOUBLE_EQ(0.22, layer.screenBeamBeamVisibleSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.08, layer.screenBeamDiffuseVisibleSolarTransmittance());
  EXPECT_DOUBLE_EQ(0.05, layer.screenBeamDiffuseVisibleSolarReflectance());
  EXPECT_DOUBLE_EQ(0.11, layer.screenInfraredTransmittance());
  EXPECT_DOUBLE_EQ(0.88, layer.screenInfraredEmissivity());
  EXPECT_DOUBLE_EQ(0.03, layer.screenWireSpacing());
  EXPECT_DOUBLE_EQ(0.004, layer.screenWireDiameter());
  EXPECT_FALSE(layer.isScreenBeamBeamSolarTransmittanceAutocalculated());

  layer.autocalculateScreenBeamBeamSolarTransmittance();
  EXPECT_TRUE(layer.isScreenBeamBeamSolarTransmittanceAutocalculated());
  EXPECT_FALSE(layer.screenBeamBeamSolarTransmittance());
}
