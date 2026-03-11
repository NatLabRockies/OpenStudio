/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundDomainBasement.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundDomainBasement_DefaultConstructor) {
  Model model;
  SiteGroundDomainBasement object(model);
  EXPECT_EQ(SiteGroundDomainBasement::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteGroundDomainBasement_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundDomainBasement object(model);

  EXPECT_FALSE(SiteGroundDomainBasement::undisturbedGroundTemperatureModelTypeValues().empty());
  EXPECT_FALSE(SiteGroundDomainBasement::horizontalInsulationExtentsValues().empty());
  EXPECT_FALSE(SiteGroundDomainBasement::simulationTimestepValues().empty());

  EXPECT_TRUE(object.isGroundDomainDepthDefaulted());
  EXPECT_DOUBLE_EQ(10.0, object.groundDomainDepth());
  EXPECT_TRUE(object.isAspectRatioDefaulted());
  EXPECT_DOUBLE_EQ(1.0, object.aspectRatio());

  EXPECT_TRUE(object.setUndisturbedGroundTemperatureModelType("Site:GroundTemperature:Undisturbed:KusudaAchenbach"));
  EXPECT_EQ("Site:GroundTemperature:Undisturbed:KusudaAchenbach", object.undisturbedGroundTemperatureModelType());

  EXPECT_TRUE(object.isHorizontalInsulationDefaulted());
  EXPECT_FALSE(object.horizontalInsulation());
  EXPECT_TRUE(object.setHorizontalInsulation(true));
  EXPECT_TRUE(object.horizontalInsulation());
  EXPECT_FALSE(object.isHorizontalInsulationDefaulted());
  object.resetHorizontalInsulation();
  EXPECT_TRUE(object.isHorizontalInsulationDefaulted());
  EXPECT_FALSE(object.horizontalInsulation());

  EXPECT_TRUE(object.isHorizontalInsulationExtentsDefaulted());
  EXPECT_EQ("Full", object.horizontalInsulationExtents());
  EXPECT_TRUE(object.setHorizontalInsulationExtents("Perimeter"));
  EXPECT_EQ("Perimeter", object.horizontalInsulationExtents());
  EXPECT_FALSE(object.isHorizontalInsulationExtentsDefaulted());
  object.resetHorizontalInsulationExtents();
  EXPECT_TRUE(object.isHorizontalInsulationExtentsDefaulted());
  EXPECT_EQ("Full", object.horizontalInsulationExtents());

  EXPECT_FALSE(object.perimeterHorizontalInsulationWidth());
  EXPECT_TRUE(object.setPerimeterHorizontalInsulationWidth(1.2));
  ASSERT_TRUE(object.perimeterHorizontalInsulationWidth());
  EXPECT_DOUBLE_EQ(1.2, *object.perimeterHorizontalInsulationWidth());
  object.resetPerimeterHorizontalInsulationWidth();
  EXPECT_FALSE(object.perimeterHorizontalInsulationWidth());

  EXPECT_FALSE(object.basementWallDepth());
  EXPECT_TRUE(object.setBasementWallDepth(2.4));
  ASSERT_TRUE(object.basementWallDepth());
  EXPECT_DOUBLE_EQ(2.4, *object.basementWallDepth());
  object.resetBasementWallDepth();
  EXPECT_FALSE(object.basementWallDepth());

  EXPECT_TRUE(object.isVerticalInsulationDefaulted());
  EXPECT_FALSE(object.verticalInsulation());
  EXPECT_TRUE(object.setVerticalInsulation(true));
  EXPECT_TRUE(object.verticalInsulation());
  EXPECT_FALSE(object.isVerticalInsulationDefaulted());
  object.resetVerticalInsulation();
  EXPECT_TRUE(object.isVerticalInsulationDefaulted());
  EXPECT_FALSE(object.verticalInsulation());

  EXPECT_FALSE(object.verticalInsulationDepth());
  EXPECT_TRUE(object.setVerticalInsulationDepth(1.7));
  ASSERT_TRUE(object.verticalInsulationDepth());
  EXPECT_DOUBLE_EQ(1.7, *object.verticalInsulationDepth());
  object.resetVerticalInsulationDepth();
  EXPECT_FALSE(object.verticalInsulationDepth());

  EXPECT_TRUE(object.isSimulationTimestepDefaulted());
  EXPECT_EQ("Hourly", object.simulationTimestep());
  EXPECT_TRUE(object.setSimulationTimestep("Timestep"));
  EXPECT_EQ("Timestep", object.simulationTimestep());
  EXPECT_FALSE(object.isSimulationTimestepDefaulted());
  object.resetSimulationTimestep();
  EXPECT_TRUE(object.isSimulationTimestepDefaulted());
  EXPECT_EQ("Hourly", object.simulationTimestep());

  EXPECT_TRUE(object.isMeshDensityParameterDefaulted());
  EXPECT_EQ(4, object.meshDensityParameter());
  EXPECT_TRUE(object.setMeshDensityParameter(6));
  EXPECT_EQ(6, object.meshDensityParameter());
  EXPECT_FALSE(object.isMeshDensityParameterDefaulted());
  object.resetMeshDensityParameter();
  EXPECT_TRUE(object.isMeshDensityParameterDefaulted());
  EXPECT_EQ(4, object.meshDensityParameter());

  EXPECT_FALSE(object.setSoilMoistureContentVolumeFraction(120.0));
  EXPECT_FALSE(object.setEvapotranspirationGroundCoverParameter(2.0));
  EXPECT_FALSE(object.setMeshDensityParameter(1));
}
