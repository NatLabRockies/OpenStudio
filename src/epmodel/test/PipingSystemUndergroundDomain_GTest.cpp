/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/PipingSystemUndergroundDomain.hpp"

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, PipingSystemUndergroundDomain_DefaultConstructor) {
  Model model;
  PipingSystemUndergroundDomain domain(model);
  EXPECT_EQ(PipingSystemUndergroundDomain::iddObjectType(), domain.iddObject().type());
  EXPECT_FALSE(domain.nameString().empty());

  EXPECT_TRUE(domain.isXDirectionMeshDensityParameterDefaulted());
  EXPECT_TRUE(domain.isYDirectionMeshDensityParameterDefaulted());
  EXPECT_TRUE(domain.isZDirectionMeshDensityParameterDefaulted());
  EXPECT_TRUE(domain.isSoilMoistureContentVolumeFractionDefaulted());
  EXPECT_TRUE(domain.isSoilMoistureContentVolumeFractionatSaturationDefaulted());
  EXPECT_TRUE(domain.isThisDomainIncludesBasementSurfaceInteractionDefaulted());
  EXPECT_TRUE(domain.isConvergenceCriterionfortheOuterCartesianDomainIterationLoopDefaulted());
  EXPECT_TRUE(domain.isMaximumIterationsintheOuterCartesianDomainIterationLoopDefaulted());
  EXPECT_TRUE(domain.isEvapotranspirationGroundCoverParameterDefaulted());
}

TEST_F(EPModelFixture, PipingSystemUndergroundDomain_ScalarAccessors_RoundTrip) {
  Model model;
  PipingSystemUndergroundDomain domain(model);

  const auto xMeshTypeValues = PipingSystemUndergroundDomain::xDirectionMeshTypeValues();
  EXPECT_TRUE(std::find(xMeshTypeValues.begin(), xMeshTypeValues.end(), "Uniform") != xMeshTypeValues.end());
  EXPECT_TRUE(std::find(xMeshTypeValues.begin(), xMeshTypeValues.end(), "SymmetricGeometric") != xMeshTypeValues.end());

  const auto groundTempValues = PipingSystemUndergroundDomain::undisturbedGroundTemperatureModelTypeValues();
  EXPECT_TRUE(std::find(groundTempValues.begin(), groundTempValues.end(), "Site:GroundTemperature:Undisturbed:FiniteDifference") !=
              groundTempValues.end());

  EXPECT_TRUE(domain.setXmax(10.0));
  EXPECT_TRUE(domain.setYmax(11.0));
  EXPECT_TRUE(domain.setZmax(6.0));
  EXPECT_TRUE(domain.setXDirectionMeshType("Uniform"));
  EXPECT_TRUE(domain.setYDirectionMeshType("SymmetricGeometric"));
  EXPECT_TRUE(domain.setZDirectionMeshType("Uniform"));
  EXPECT_TRUE(domain.setSoilThermalConductivity(1.4));
  EXPECT_TRUE(domain.setSoilDensity(1800.0));
  EXPECT_TRUE(domain.setSoilSpecificHeat(900.0));
  EXPECT_TRUE(domain.setUndisturbedGroundTemperatureModelType("Site:GroundTemperature:Undisturbed:KusudaAchenbach"));
  EXPECT_TRUE(domain.setNumberofPipeCircuitsEnteredforthisDomain(1));

  EXPECT_DOUBLE_EQ(10.0, domain.xmax());
  EXPECT_DOUBLE_EQ(11.0, domain.ymax());
  EXPECT_DOUBLE_EQ(6.0, domain.zmax());
  EXPECT_EQ("Uniform", domain.xDirectionMeshType());
  EXPECT_EQ("SymmetricGeometric", domain.yDirectionMeshType());
  EXPECT_EQ("Uniform", domain.zDirectionMeshType());
  EXPECT_DOUBLE_EQ(1.4, domain.soilThermalConductivity());
  EXPECT_DOUBLE_EQ(1800.0, domain.soilDensity());
  EXPECT_DOUBLE_EQ(900.0, domain.soilSpecificHeat());
  EXPECT_EQ("Site:GroundTemperature:Undisturbed:KusudaAchenbach", domain.undisturbedGroundTemperatureModelType());
  EXPECT_EQ(1, domain.numberofPipeCircuitsEnteredforthisDomain());

  EXPECT_TRUE(domain.setXDirectionMeshDensityParameter(8));
  EXPECT_EQ(8, domain.xDirectionMeshDensityParameter());
  EXPECT_FALSE(domain.isXDirectionMeshDensityParameterDefaulted());
  domain.resetXDirectionMeshDensityParameter();
  EXPECT_TRUE(domain.isXDirectionMeshDensityParameterDefaulted());

  EXPECT_TRUE(domain.setThisDomainIncludesBasementSurfaceInteraction(true));
  EXPECT_TRUE(domain.thisDomainIncludesBasementSurfaceInteraction());
  EXPECT_FALSE(domain.isThisDomainIncludesBasementSurfaceInteractionDefaulted());
  domain.resetThisDomainIncludesBasementSurfaceInteraction();
  EXPECT_TRUE(domain.isThisDomainIncludesBasementSurfaceInteractionDefaulted());

  EXPECT_TRUE(domain.setWidthofBasementFloorinGroundDomain(4.0));
  ASSERT_TRUE(domain.widthofBasementFloorinGroundDomain());
  EXPECT_DOUBLE_EQ(4.0, *domain.widthofBasementFloorinGroundDomain());
  domain.resetWidthofBasementFloorinGroundDomain();
  EXPECT_FALSE(domain.widthofBasementFloorinGroundDomain());

  EXPECT_TRUE(domain.setShiftPipeXCoordinatesByBasementWidth(true));
  ASSERT_TRUE(domain.shiftPipeXCoordinatesByBasementWidth());
  EXPECT_TRUE(*domain.shiftPipeXCoordinatesByBasementWidth());
  EXPECT_TRUE(domain.setShiftPipeXCoordinatesByBasementWidth(boost::none));
  ASSERT_TRUE(domain.shiftPipeXCoordinatesByBasementWidth());
  EXPECT_FALSE(*domain.shiftPipeXCoordinatesByBasementWidth());

  EXPECT_FALSE(domain.setXDirectionMeshType("Invalid"));
  EXPECT_FALSE(domain.setUndisturbedGroundTemperatureModelType("InvalidType"));
}
