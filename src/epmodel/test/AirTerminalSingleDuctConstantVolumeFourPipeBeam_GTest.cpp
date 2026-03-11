/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeFourPipeBeam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam airTerminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeFourPipeBeam::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_FALSE(airTerminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeFourPipeBeam_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeFourPipeBeam airTerminal(model);

  EXPECT_TRUE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());
  EXPECT_TRUE(airTerminal.isZoneTotalBeamLengthAutosized());

  EXPECT_TRUE(airTerminal.setDesignPrimaryAirVolumeFlowRate(0.61));
  ASSERT_TRUE(airTerminal.designPrimaryAirVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.61, airTerminal.designPrimaryAirVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());
  airTerminal.autosizeDesignPrimaryAirVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignPrimaryAirVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setDesignChilledWaterVolumeFlowRate(0.11));
  ASSERT_TRUE(airTerminal.designChilledWaterVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.11, airTerminal.designChilledWaterVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());
  airTerminal.autosizeDesignChilledWaterVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignChilledWaterVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setDesignHotWaterVolumeFlowRate(0.09));
  ASSERT_TRUE(airTerminal.designHotWaterVolumeFlowRate());
  EXPECT_DOUBLE_EQ(0.09, airTerminal.designHotWaterVolumeFlowRate().get());
  EXPECT_FALSE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());
  airTerminal.autosizeDesignHotWaterVolumeFlowRate();
  EXPECT_TRUE(airTerminal.isDesignHotWaterVolumeFlowRateAutosized());

  EXPECT_TRUE(airTerminal.setZoneTotalBeamLength(4.3));
  ASSERT_TRUE(airTerminal.zoneTotalBeamLength());
  EXPECT_DOUBLE_EQ(4.3, airTerminal.zoneTotalBeamLength().get());
  EXPECT_FALSE(airTerminal.isZoneTotalBeamLengthAutosized());
  airTerminal.autosizeZoneTotalBeamLength();
  EXPECT_TRUE(airTerminal.isZoneTotalBeamLengthAutosized());

  EXPECT_TRUE(airTerminal.setRatedPrimaryAirFlowRateperBeamLength(0.047));
  EXPECT_DOUBLE_EQ(0.047, airTerminal.ratedPrimaryAirFlowRateperBeamLength());
  EXPECT_FALSE(airTerminal.isRatedPrimaryAirFlowRateperBeamLengthDefaulted());
  airTerminal.resetRatedPrimaryAirFlowRateperBeamLength();
  EXPECT_TRUE(airTerminal.isRatedPrimaryAirFlowRateperBeamLengthDefaulted());
}
