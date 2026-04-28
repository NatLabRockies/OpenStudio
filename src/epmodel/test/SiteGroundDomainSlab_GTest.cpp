/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SiteGroundDomainSlab.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundDomainSlab_DefaultConstructor) {
  Model model;
  SiteGroundDomainSlab object(model);
  EXPECT_EQ(SiteGroundDomainSlab::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteGroundDomainSlab_ScalarAccessors_RoundTrip) {
  Model model;
  SiteGroundDomainSlab object(model);

  EXPECT_FALSE(SiteGroundDomainSlab::undisturbedGroundTemperatureModelTypeValues().empty());
  EXPECT_FALSE(SiteGroundDomainSlab::slabLocationValues().empty());
  EXPECT_FALSE(SiteGroundDomainSlab::horizontalInsulationExtentsValues().empty());
  EXPECT_FALSE(SiteGroundDomainSlab::simulationTimestepValues().empty());

  EXPECT_TRUE(object.isGroundDomainDepthDefaulted());
  EXPECT_DOUBLE_EQ(10.0, object.groundDomainDepth());
  EXPECT_TRUE(object.setGroundDomainDepth(12.0));
  EXPECT_DOUBLE_EQ(12.0, object.groundDomainDepth());
  object.resetGroundDomainDepth();
  EXPECT_DOUBLE_EQ(10.0, object.groundDomainDepth());

  EXPECT_TRUE(object.isHorizontalInsulationDefaulted());
  EXPECT_FALSE(object.horizontalInsulation());
  EXPECT_TRUE(object.setHorizontalInsulation(true));
  EXPECT_TRUE(object.horizontalInsulation());
  object.resetHorizontalInsulation();
  EXPECT_FALSE(object.horizontalInsulation());

  EXPECT_TRUE(object.isHorizontalInsulationExtentsDefaulted());
  EXPECT_EQ("Full", object.horizontalInsulationExtents());
  EXPECT_TRUE(object.setHorizontalInsulationExtents("Perimeter"));
  EXPECT_EQ("Perimeter", object.horizontalInsulationExtents());
  object.resetHorizontalInsulationExtents();
  EXPECT_EQ("Full", object.horizontalInsulationExtents());

  EXPECT_FALSE(object.perimeterInsulationWidth());
  EXPECT_TRUE(object.setPerimeterInsulationWidth(1.8));
  ASSERT_TRUE(object.perimeterInsulationWidth());
  EXPECT_DOUBLE_EQ(1.8, *object.perimeterInsulationWidth());
  object.resetPerimeterInsulationWidth();
  EXPECT_FALSE(object.perimeterInsulationWidth());

  EXPECT_TRUE(object.isGeometricMeshCoefficientDefaulted());
  EXPECT_DOUBLE_EQ(1.6, object.geometricMeshCoefficient());
  EXPECT_TRUE(object.setGeometricMeshCoefficient(1.9));
  EXPECT_DOUBLE_EQ(1.9, object.geometricMeshCoefficient());
  object.resetGeometricMeshCoefficient();
  EXPECT_DOUBLE_EQ(1.6, object.geometricMeshCoefficient());
  EXPECT_FALSE(object.setGeometricMeshCoefficient(0.5));

  EXPECT_TRUE(object.isVerticalInsulationDefaulted());
  EXPECT_FALSE(object.verticalInsulation());
  EXPECT_TRUE(object.setVerticalInsulation(true));
  EXPECT_TRUE(object.verticalInsulation());
  object.resetVerticalInsulation();
  EXPECT_FALSE(object.verticalInsulation());

  EXPECT_FALSE(object.verticalInsulationDepth());
  EXPECT_TRUE(object.setVerticalInsulationDepth(0.75));
  ASSERT_TRUE(object.verticalInsulationDepth());
  EXPECT_DOUBLE_EQ(0.75, *object.verticalInsulationDepth());
  object.resetVerticalInsulationDepth();
  EXPECT_FALSE(object.verticalInsulationDepth());

  EXPECT_TRUE(object.isSimulationTimestepDefaulted());
  EXPECT_EQ("Hourly", object.simulationTimestep());
  EXPECT_TRUE(object.setSimulationTimestep("Timestep"));
  EXPECT_EQ("Timestep", object.simulationTimestep());
  object.resetSimulationTimestep();
  EXPECT_EQ("Hourly", object.simulationTimestep());

  EXPECT_TRUE(object.setSlabLocation("OnGrade"));
  EXPECT_EQ("OnGrade", object.slabLocation());
  EXPECT_TRUE(object.isEvapotranspirationGroundCoverParameterDefaulted());
  EXPECT_FALSE(object.setEvapotranspirationGroundCoverParameter(2.0));
  EXPECT_TRUE(object.setEvapotranspirationGroundCoverParameter(0.6));
  EXPECT_FALSE(object.isEvapotranspirationGroundCoverParameterDefaulted());
  object.resetEvapotranspirationGroundCoverParameter();
  EXPECT_TRUE(object.isEvapotranspirationGroundCoverParameterDefaulted());

  EXPECT_TRUE(object.isMeshDensityParameterDefaulted());
  EXPECT_TRUE(object.setMeshDensityParameter(7));
  EXPECT_FALSE(object.isMeshDensityParameterDefaulted());
  object.resetMeshDensityParameter();
  EXPECT_TRUE(object.isMeshDensityParameterDefaulted());
  EXPECT_FALSE(object.setMeshDensityParameter(1));
}
