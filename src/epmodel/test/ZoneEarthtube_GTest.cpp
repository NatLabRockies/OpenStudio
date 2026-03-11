/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneEarthtube.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneEarthtube_DefaultConstructor) {
  Model model;
  ZoneEarthtube earthtube(model);
  EXPECT_EQ(ZoneEarthtube::iddObjectType(), earthtube.iddObject().type());
}

TEST_F(EPModelFixture, ZoneEarthtube_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneEarthtube earthtube(model);

  EXPECT_TRUE(earthtube.setDesignFlowRate(0.5));
  EXPECT_TRUE(earthtube.setMinimumZoneTemperaturewhenCooling(18.0));
  EXPECT_TRUE(earthtube.setMaximumZoneTemperaturewhenHeating(26.0));
  EXPECT_TRUE(earthtube.setDeltaTemperature(1.0));
  EXPECT_TRUE(earthtube.setEarthtubeType("Intake"));
  EXPECT_TRUE(earthtube.setFanPressureRise(12.0));
  EXPECT_FALSE(earthtube.isFanPressureRiseDefaulted());
  earthtube.resetFanPressureRise();
  EXPECT_TRUE(earthtube.isFanPressureRiseDefaulted());
  EXPECT_TRUE(earthtube.setFanTotalEfficiency(0.85));
  EXPECT_TRUE(earthtube.setPipeRadius(0.6));
  EXPECT_TRUE(earthtube.setPipeThickness(0.25));
  EXPECT_TRUE(earthtube.setPipeLength(20.0));
  EXPECT_TRUE(earthtube.setPipeThermalConductivity(210.0));
  EXPECT_TRUE(earthtube.setPipeDepthUnderGroundSurface(4.0));
  EXPECT_TRUE(earthtube.setSoilCondition("LightAndDry"));
  EXPECT_TRUE(earthtube.setAverageSoilSurfaceTemperature(16.5));
  EXPECT_TRUE(earthtube.setAmplitudeofSoilSurfaceTemperature(6.0));
  EXPECT_TRUE(earthtube.setPhaseConstantofSoilSurfaceTemperature(1.5));
  EXPECT_TRUE(earthtube.isConstantTermFlowCoefficientDefaulted());
  EXPECT_TRUE(earthtube.setConstantTermFlowCoefficient(2.0));
  EXPECT_FALSE(earthtube.isConstantTermFlowCoefficientDefaulted());
  earthtube.resetConstantTermFlowCoefficient();
  EXPECT_TRUE(earthtube.isConstantTermFlowCoefficientDefaulted());
  EXPECT_TRUE(earthtube.setTemperatureTermFlowCoefficient(0.25));
  EXPECT_TRUE(earthtube.setVelocityTermFlowCoefficient(0.4));
  EXPECT_TRUE(earthtube.setVelocitySquaredTermFlowCoefficient(0.02));
  EXPECT_TRUE(earthtube.setEarthTubeModelType("Vertical"));

  EXPECT_DOUBLE_EQ(0.5, earthtube.designFlowRate());
  EXPECT_DOUBLE_EQ(18.0, earthtube.minimumZoneTemperaturewhenCooling());
  EXPECT_DOUBLE_EQ(26.0, earthtube.maximumZoneTemperaturewhenHeating());
  EXPECT_DOUBLE_EQ(1.0, earthtube.deltaTemperature());
  EXPECT_EQ("Intake", earthtube.earthtubeType());
  EXPECT_DOUBLE_EQ(0.85, earthtube.fanTotalEfficiency());
  EXPECT_DOUBLE_EQ(0.6, earthtube.pipeRadius());
  EXPECT_DOUBLE_EQ(0.25, earthtube.pipeThickness());
  EXPECT_DOUBLE_EQ(20.0, earthtube.pipeLength());
  EXPECT_DOUBLE_EQ(210.0, earthtube.pipeThermalConductivity());
  EXPECT_DOUBLE_EQ(4.0, earthtube.pipeDepthUnderGroundSurface());
  EXPECT_EQ("LightAndDry", earthtube.soilCondition());
  EXPECT_DOUBLE_EQ(16.5, earthtube.averageSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(6.0, earthtube.amplitudeofSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(1.5, earthtube.phaseConstantofSoilSurfaceTemperature());
  EXPECT_DOUBLE_EQ(0.25, earthtube.temperatureTermFlowCoefficient());
  EXPECT_DOUBLE_EQ(0.4, earthtube.velocityTermFlowCoefficient());
  EXPECT_DOUBLE_EQ(0.02, earthtube.velocitySquaredTermFlowCoefficient());
  EXPECT_EQ("Vertical", earthtube.earthTubeModelType());
}
