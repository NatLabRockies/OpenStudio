/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Glazing/StandardGlazing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, StandardGlazing_DefaultConstructor) {
  Model model;
  StandardGlazing glazing(model);

  EXPECT_EQ(StandardGlazing::iddObjectType(), glazing.iddObject().type());
  EXPECT_FALSE(StandardGlazing::opticalDataTypeValues().empty());
  EXPECT_EQ("SpectralAverage", glazing.opticalDataType());
  EXPECT_DOUBLE_EQ(0.1, glazing.thickness());
}

TEST_F(EPModelFixture, StandardGlazing_ScalarAccessors_RoundTrip) {
  Model model;
  StandardGlazing glazing(model);

  EXPECT_TRUE(glazing.setSolarTransmittance(0.58));
  EXPECT_DOUBLE_EQ(0.58, glazing.solarTransmittance());

  EXPECT_TRUE(glazing.setSolarTransmittanceatNormalIncidence(0.62));
  ASSERT_TRUE(glazing.solarTransmittanceatNormalIncidence());
  EXPECT_DOUBLE_EQ(0.62, glazing.solarTransmittanceatNormalIncidence().get());
  glazing.resetSolarTransmittanceatNormalIncidence();
  EXPECT_FALSE(glazing.solarTransmittanceatNormalIncidence());
  EXPECT_TRUE(glazing.setSolarTransmittanceatNormalIncidence(0.37));

  EXPECT_TRUE(glazing.setFrontSideSolarReflectanceatNormalIncidence(0.12));
  ASSERT_TRUE(glazing.frontSideSolarReflectanceatNormalIncidence());
  EXPECT_DOUBLE_EQ(0.12, glazing.frontSideSolarReflectanceatNormalIncidence().get());
  glazing.resetFrontSideSolarReflectanceatNormalIncidence();
  EXPECT_FALSE(glazing.frontSideSolarReflectanceatNormalIncidence());
  EXPECT_TRUE(glazing.setFrontSideSolarReflectanceatNormalIncidence(0.18));

  EXPECT_TRUE(glazing.setBackSideSolarReflectanceatNormalIncidence(0.05));
  ASSERT_TRUE(glazing.backSideSolarReflectanceatNormalIncidence());
  EXPECT_DOUBLE_EQ(0.05, glazing.backSideSolarReflectanceatNormalIncidence().get());
  glazing.resetBackSideSolarReflectanceatNormalIncidence();
  EXPECT_FALSE(glazing.backSideSolarReflectanceatNormalIncidence());
  EXPECT_TRUE(glazing.setBackSideSolarReflectanceatNormalIncidence(0.08));

  EXPECT_TRUE(glazing.setVisibleTransmittance(0.26));
  EXPECT_TRUE(glazing.setVisibleTransmittanceatNormalIncidence(0.26));
  ASSERT_TRUE(glazing.visibleTransmittanceatNormalIncidence());
  EXPECT_DOUBLE_EQ(0.26, glazing.visibleTransmittanceatNormalIncidence().get());
  glazing.resetVisibleTransmittanceatNormalIncidence();
  EXPECT_FALSE(glazing.visibleTransmittanceatNormalIncidence());
  EXPECT_TRUE(glazing.setVisibleTransmittanceatNormalIncidence(0.22));

  EXPECT_TRUE(glazing.setFrontSideVisibleReflectanceatNormalIncidence(0.14));
  EXPECT_TRUE(glazing.setBackSideVisibleReflectanceatNormalIncidence(0.09));

  EXPECT_TRUE(glazing.setInfraredTransmittance(0.2));
  EXPECT_TRUE(glazing.setInfraredTransmittanceatNormalIncidence(0.21));
  EXPECT_DOUBLE_EQ(0.21, glazing.infraredTransmittanceatNormalIncidence());
  glazing.resetInfraredTransmittanceatNormalIncidence();
  EXPECT_TRUE(glazing.isInfraredTransmittanceatNormalIncidenceDefaulted());

  EXPECT_TRUE(glazing.setFrontSideInfraredHemisphericalEmissivity(0.17));
  EXPECT_DOUBLE_EQ(0.17, glazing.frontSideInfraredHemisphericalEmissivity());
  glazing.resetFrontSideInfraredHemisphericalEmissivity();
  EXPECT_TRUE(glazing.isFrontSideInfraredHemisphericalEmissivityDefaulted());
  EXPECT_TRUE(glazing.setFrontSideInfraredHemisphericalEmissivity(0.19));

  EXPECT_TRUE(glazing.setBackSideInfraredHemisphericalEmissivity(0.22));
  EXPECT_DOUBLE_EQ(0.22, glazing.backSideInfraredHemisphericalEmissivity());
  glazing.resetBackSideInfraredHemisphericalEmissivity();
  EXPECT_TRUE(glazing.isBackSideInfraredHemisphericalEmissivityDefaulted());
  EXPECT_TRUE(glazing.setBackSideInfraredHemisphericalEmissivity(0.24));

  EXPECT_TRUE(glazing.setConductivity(2.9));
  EXPECT_DOUBLE_EQ(2.9, glazing.conductivity());
  EXPECT_DOUBLE_EQ(2.9, glazing.thermalConductivity());
  EXPECT_TRUE(glazing.setThermalConductance(4.0));
  EXPECT_DOUBLE_EQ(4.0, glazing.thermalConductance());
  EXPECT_TRUE(glazing.setThermalResistivity(6.0));
  EXPECT_NEAR(6.0, glazing.thermalResistivity(), 1e-8);
  EXPECT_TRUE(glazing.setThermalResistance(0.5));
  EXPECT_DOUBLE_EQ(0.5, glazing.thermalResistance());
  glazing.resetConductivity();
  EXPECT_TRUE(glazing.isConductivityDefaulted());

  EXPECT_TRUE(glazing.setDirtCorrectionFactorforSolarandVisibleTransmittance(0.33));
  EXPECT_DOUBLE_EQ(0.33, glazing.dirtCorrectionFactorforSolarandVisibleTransmittance());
  glazing.resetDirtCorrectionFactorforSolarandVisibleTransmittance();
  EXPECT_TRUE(glazing.isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted());

  EXPECT_TRUE(glazing.setSolarDiffusing(true));
  EXPECT_TRUE(glazing.solarDiffusing());
  EXPECT_FALSE(glazing.isSolarDiffusingDefaulted());
  glazing.setSolarDiffusingNoFail(false);
  EXPECT_FALSE(glazing.solarDiffusing());
  glazing.resetSolarDiffusing();
  EXPECT_TRUE(glazing.isSolarDiffusingDefaulted());

  EXPECT_TRUE(glazing.setVisibleTransmittanceatNormalIncidence(0.28));
  EXPECT_TRUE(glazing.setBackSideVisibleReflectanceatNormalIncidence(0.12));
  EXPECT_TRUE(glazing.setFrontSideVisibleReflectanceatNormalIncidence(0.14));
  ASSERT_TRUE(glazing.interiorVisibleAbsorptance());
  EXPECT_DOUBLE_EQ(1.0 - (glazing.visibleTransmittanceatNormalIncidence().get() + glazing.backSideVisibleReflectanceatNormalIncidence().get()),
                   glazing.interiorVisibleAbsorptance().get());
  ASSERT_TRUE(glazing.exteriorVisibleAbsorptance());
  EXPECT_DOUBLE_EQ(1.0 - (glazing.visibleTransmittanceatNormalIncidence().get() + glazing.frontSideVisibleReflectanceatNormalIncidence().get()),
                   glazing.exteriorVisibleAbsorptance().get());
}
