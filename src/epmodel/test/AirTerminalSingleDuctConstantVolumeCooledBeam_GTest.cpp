/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/AirTerminalSingleDuctConstantVolumeCooledBeam.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_DefaultConstructor) {
  Model model;
  AirTerminalSingleDuctConstantVolumeCooledBeam airTerminal(model);
  EXPECT_EQ(AirTerminalSingleDuctConstantVolumeCooledBeam::iddObjectType(), airTerminal.iddObject().type());
  EXPECT_FALSE(airTerminal.nameString().empty());
}

TEST_F(EPModelFixture, AirTerminalSingleDuctConstantVolumeCooledBeam_ScalarAccessors_RoundTrip) {
  Model model;
  AirTerminalSingleDuctConstantVolumeCooledBeam airTerminal(model);

  EXPECT_TRUE(airTerminal.setCooledBeamType("Active"));
  EXPECT_EQ("Active", airTerminal.cooledBeamType());

  EXPECT_TRUE(airTerminal.setSupplyAirVolumetricFlowRate(0.65));
  ASSERT_TRUE(airTerminal.supplyAirVolumetricFlowRate());
  EXPECT_DOUBLE_EQ(0.65, airTerminal.supplyAirVolumetricFlowRate().get());
  EXPECT_FALSE(airTerminal.isSupplyAirVolumetricFlowRateDefaulted());
  EXPECT_FALSE(airTerminal.isSupplyAirVolumetricFlowRateAutosized());
  airTerminal.autosizeSupplyAirVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isSupplyAirVolumetricFlowRateAutosized());
  airTerminal.resetSupplyAirVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isSupplyAirVolumetricFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setMaximumTotalChilledWaterVolumetricFlowRate(0.20));
  ASSERT_TRUE(airTerminal.maximumTotalChilledWaterVolumetricFlowRate());
  EXPECT_DOUBLE_EQ(0.20, airTerminal.maximumTotalChilledWaterVolumetricFlowRate().get());
  EXPECT_FALSE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateDefaulted());
  EXPECT_FALSE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateAutosized());
  airTerminal.autosizeMaximumTotalChilledWaterVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateAutosized());
  airTerminal.resetMaximumTotalChilledWaterVolumetricFlowRate();
  EXPECT_TRUE(airTerminal.isMaximumTotalChilledWaterVolumetricFlowRateDefaulted());

  EXPECT_TRUE(airTerminal.setNumberofBeams(6));
  ASSERT_TRUE(airTerminal.numberofBeams());
  EXPECT_EQ(6, airTerminal.numberofBeams().get());
  EXPECT_FALSE(airTerminal.isNumberofBeamsDefaulted());
  EXPECT_FALSE(airTerminal.isNumberofBeamsAutosized());
  airTerminal.autosizeNumberofBeams();
  EXPECT_TRUE(airTerminal.isNumberofBeamsAutosized());
  airTerminal.resetNumberofBeams();
  EXPECT_TRUE(airTerminal.isNumberofBeamsDefaulted());

  EXPECT_TRUE(airTerminal.setBeamLength(3.8));
  ASSERT_TRUE(airTerminal.beamLength());
  EXPECT_DOUBLE_EQ(3.8, airTerminal.beamLength().get());
  EXPECT_FALSE(airTerminal.isBeamLengthDefaulted());
  EXPECT_FALSE(airTerminal.isBeamLengthAutosized());
  airTerminal.autosizeBeamLength();
  EXPECT_TRUE(airTerminal.isBeamLengthAutosized());
  airTerminal.resetBeamLength();
  EXPECT_TRUE(airTerminal.isBeamLengthDefaulted());

  EXPECT_TRUE(airTerminal.setDesignInletWaterTemperature(14.2));
  EXPECT_DOUBLE_EQ(14.2, airTerminal.designInletWaterTemperature());
  EXPECT_FALSE(airTerminal.isDesignInletWaterTemperatureDefaulted());
  airTerminal.resetDesignInletWaterTemperature();
  EXPECT_TRUE(airTerminal.isDesignInletWaterTemperatureDefaulted());

  EXPECT_TRUE(airTerminal.setDesignOutletWaterTemperature(16.4));
  EXPECT_DOUBLE_EQ(16.4, airTerminal.designOutletWaterTemperature());
  EXPECT_FALSE(airTerminal.isDesignOutletWaterTemperatureDefaulted());
  airTerminal.resetDesignOutletWaterTemperature();
  EXPECT_TRUE(airTerminal.isDesignOutletWaterTemperatureDefaulted());

  EXPECT_TRUE(airTerminal.setCoefficientofInductionKin(0.35));
  ASSERT_TRUE(airTerminal.coefficientofInductionKin());
  EXPECT_DOUBLE_EQ(0.35, airTerminal.coefficientofInductionKin().get());
  EXPECT_FALSE(airTerminal.isCoefficientofInductionKinDefaulted());
  EXPECT_FALSE(airTerminal.isCoefficientofInductionKinAutocalculated());
  airTerminal.autocalculateCoefficientofInductionKin();
  EXPECT_TRUE(airTerminal.isCoefficientofInductionKinAutocalculated());
  airTerminal.resetCoefficientofInductionKin();
  EXPECT_TRUE(airTerminal.isCoefficientofInductionKinDefaulted());
}
