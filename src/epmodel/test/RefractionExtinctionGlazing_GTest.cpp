/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Glazing/RefractionExtinctionGlazing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefractionExtinctionGlazing_DefaultConstructor) {
  Model model;
  RefractionExtinctionGlazing glazing(model);

  EXPECT_EQ(RefractionExtinctionGlazing::iddObjectType(), glazing.iddObject().type());
  EXPECT_DOUBLE_EQ(0.1, glazing.thickness());
  EXPECT_DOUBLE_EQ(1.1, glazing.solarIndexofRefraction());
  EXPECT_DOUBLE_EQ(0.1, glazing.solarExtinctionCoefficient());
  EXPECT_DOUBLE_EQ(1.1, glazing.visibleIndexofRefraction());
  EXPECT_DOUBLE_EQ(0.1, glazing.visibleExtinctionCoefficient());
}

TEST_F(EPModelFixture, RefractionExtinctionGlazing_ScalarAccessors_RoundTrip) {
  Model model;
  RefractionExtinctionGlazing glazing(model);

  EXPECT_TRUE(glazing.setThickness(0.12));
  EXPECT_DOUBLE_EQ(0.12, glazing.thickness());

  EXPECT_TRUE(glazing.setSolarIndexofRefraction(1.2));
  EXPECT_DOUBLE_EQ(1.2, glazing.solarIndexofRefraction());

  EXPECT_TRUE(glazing.setSolarExtinctionCoefficient(0.3));
  EXPECT_DOUBLE_EQ(0.3, glazing.solarExtinctionCoefficient());

  EXPECT_TRUE(glazing.setVisibleIndexofRefraction(1.3));
  EXPECT_DOUBLE_EQ(1.3, glazing.visibleIndexofRefraction());

  EXPECT_TRUE(glazing.setVisibleExtinctionCoefficient(0.28));
  EXPECT_DOUBLE_EQ(0.28, glazing.visibleExtinctionCoefficient());

  EXPECT_TRUE(glazing.setInfraredTransmittanceatNormalIncidence(0.35));
  EXPECT_DOUBLE_EQ(0.35, glazing.infraredTransmittanceatNormalIncidence());
  glazing.resetInfraredTransmittanceatNormalIncidence();
  EXPECT_TRUE(glazing.isInfraredTransmittanceatNormalIncidenceDefaulted());

  EXPECT_TRUE(glazing.setInfraredHemisphericalEmissivity(0.22));
  EXPECT_DOUBLE_EQ(0.22, glazing.infraredHemisphericalEmissivity());
  glazing.resetInfraredHemisphericalEmissivity();
  EXPECT_TRUE(glazing.isInfraredHemisphericalEmissivityDefaulted());

  EXPECT_TRUE(glazing.setConductivity(0.92));
  EXPECT_DOUBLE_EQ(0.92, glazing.conductivity());
  glazing.resetConductivity();
  EXPECT_TRUE(glazing.isConductivityDefaulted());

  EXPECT_TRUE(glazing.setDirtCorrectionFactorforSolarandVisibleTransmittance(0.9));
  EXPECT_DOUBLE_EQ(0.9, glazing.dirtCorrectionFactorforSolarandVisibleTransmittance());
  glazing.resetDirtCorrectionFactorforSolarandVisibleTransmittance();
  EXPECT_TRUE(glazing.isDirtCorrectionFactorforSolarandVisibleTransmittanceDefaulted());

  EXPECT_TRUE(glazing.setSolarDiffusing(true));
  EXPECT_TRUE(glazing.solarDiffusing());
  EXPECT_FALSE(glazing.isSolarDiffusingDefaulted());
  glazing.setSolarDiffusingNoFail(false);
  EXPECT_FALSE(glazing.solarDiffusing());
  glazing.resetSolarDiffusing();
  EXPECT_TRUE(glazing.isSolarDiffusingDefaulted());
}
