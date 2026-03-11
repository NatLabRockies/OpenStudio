/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FuelFactors.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FuelFactors_DefaultConstructor) {
  Model model;
  FuelFactors fuelFactors(model);

  EXPECT_EQ(FuelFactors::iddObjectType(), fuelFactors.iddObject().type());
  EXPECT_EQ("Electricity", fuelFactors.existingFuelResourceName());
  EXPECT_DOUBLE_EQ(2.253, fuelFactors.sourceEnergyFactor());
  EXPECT_DOUBLE_EQ(168.33317, fuelFactors.cO2EmissionFactor());
  EXPECT_DOUBLE_EQ(4.20616E-02, fuelFactors.cOEmissionFactor());
  EXPECT_DOUBLE_EQ(1.39858E-03, fuelFactors.cH4EmissionFactor());
  EXPECT_DOUBLE_EQ(4.10753E-01, fuelFactors.nOxEmissionFactor());
  EXPECT_DOUBLE_EQ(2.41916E-03, fuelFactors.n2OEmissionFactor());
  EXPECT_DOUBLE_EQ(8.65731E-01, fuelFactors.sO2EmissionFactor());
  EXPECT_DOUBLE_EQ(2.95827E-02, fuelFactors.pMEmissionFactor());
  EXPECT_DOUBLE_EQ(1.80450E-02, fuelFactors.pM10EmissionFactor());
  EXPECT_DOUBLE_EQ(1.15377E-02, fuelFactors.pM25EmissionFactor());
  EXPECT_DOUBLE_EQ(1.10837E-03, fuelFactors.nH3EmissionFactor());
  EXPECT_DOUBLE_EQ(3.72332E-03, fuelFactors.nMVOCEmissionFactor());
  EXPECT_DOUBLE_EQ(3.36414E-06, fuelFactors.hgEmissionFactor());
  EXPECT_DOUBLE_EQ(0.0, fuelFactors.pbEmissionFactor());
  EXPECT_DOUBLE_EQ(2.10074, fuelFactors.waterEmissionFactor());
  EXPECT_DOUBLE_EQ(0.0, fuelFactors.nuclearHighLevelEmissionFactor());
  EXPECT_DOUBLE_EQ(0.0, fuelFactors.nuclearLowLevelEmissionFactor());
}

TEST_F(EPModelFixture, FuelFactors_ScalarAccessors_RoundTrip) {
  Model model;
  FuelFactors fuelFactors(model);

  const auto existingFuelResourceNameValues = FuelFactors::existingFuelResourceNameValues();
  EXPECT_FALSE(existingFuelResourceNameValues.empty());
  EXPECT_TRUE(fuelFactors.setExistingFuelResourceName("NaturalGas"));
  EXPECT_EQ("NaturalGas", fuelFactors.existingFuelResourceName());
  EXPECT_FALSE(fuelFactors.setExistingFuelResourceName("BADENUM"));
  EXPECT_EQ("NaturalGas", fuelFactors.existingFuelResourceName());

  EXPECT_TRUE(fuelFactors.setSourceEnergyFactor(0.1));
  EXPECT_DOUBLE_EQ(0.1, fuelFactors.sourceEnergyFactor());

  EXPECT_TRUE(fuelFactors.setCO2EmissionFactor(0.2));
  EXPECT_DOUBLE_EQ(0.2, fuelFactors.cO2EmissionFactor());

  EXPECT_TRUE(fuelFactors.setCOEmissionFactor(0.3));
  EXPECT_DOUBLE_EQ(0.3, fuelFactors.cOEmissionFactor());

  EXPECT_TRUE(fuelFactors.setCH4EmissionFactor(0.4));
  EXPECT_DOUBLE_EQ(0.4, fuelFactors.cH4EmissionFactor());

  EXPECT_TRUE(fuelFactors.setNOxEmissionFactor(0.5));
  EXPECT_DOUBLE_EQ(0.5, fuelFactors.nOxEmissionFactor());

  EXPECT_TRUE(fuelFactors.setN2OEmissionFactor(0.6));
  EXPECT_DOUBLE_EQ(0.6, fuelFactors.n2OEmissionFactor());

  EXPECT_TRUE(fuelFactors.setSO2EmissionFactor(0.7));
  EXPECT_DOUBLE_EQ(0.7, fuelFactors.sO2EmissionFactor());

  EXPECT_TRUE(fuelFactors.setPMEmissionFactor(0.8));
  EXPECT_DOUBLE_EQ(0.8, fuelFactors.pMEmissionFactor());

  EXPECT_TRUE(fuelFactors.setPM10EmissionFactor(0.9));
  EXPECT_DOUBLE_EQ(0.9, fuelFactors.pM10EmissionFactor());

  EXPECT_TRUE(fuelFactors.setPM25EmissionFactor(1.0));
  EXPECT_DOUBLE_EQ(1.0, fuelFactors.pM25EmissionFactor());

  EXPECT_TRUE(fuelFactors.setNH3EmissionFactor(1.1));
  EXPECT_DOUBLE_EQ(1.1, fuelFactors.nH3EmissionFactor());

  EXPECT_TRUE(fuelFactors.setNMVOCEmissionFactor(1.2));
  EXPECT_DOUBLE_EQ(1.2, fuelFactors.nMVOCEmissionFactor());

  EXPECT_TRUE(fuelFactors.setHgEmissionFactor(1.3));
  EXPECT_DOUBLE_EQ(1.3, fuelFactors.hgEmissionFactor());

  EXPECT_TRUE(fuelFactors.setPbEmissionFactor(1.4));
  EXPECT_DOUBLE_EQ(1.4, fuelFactors.pbEmissionFactor());

  EXPECT_TRUE(fuelFactors.setWaterEmissionFactor(1.5));
  EXPECT_DOUBLE_EQ(1.5, fuelFactors.waterEmissionFactor());

  EXPECT_TRUE(fuelFactors.setNuclearHighLevelEmissionFactor(1.6));
  EXPECT_DOUBLE_EQ(1.6, fuelFactors.nuclearHighLevelEmissionFactor());

  EXPECT_TRUE(fuelFactors.setNuclearLowLevelEmissionFactor(1.7));
  EXPECT_DOUBLE_EQ(1.7, fuelFactors.nuclearLowLevelEmissionFactor());
}
