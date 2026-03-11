/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingGasMultiStage.hpp"

#include <utilities/idd/Coil_Heating_Gas_MultiStage_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_DefaultConstructor) {
  Model model;
  CoilHeatingGasMultiStage coil(model);
  EXPECT_EQ(CoilHeatingGasMultiStage::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_EQ(1u, coil.numberOfStages());
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());
  EXPECT_FALSE(coil.parasiticGasLoad());
}

TEST_F(EPModelFixture, CoilHeatingGasMultiStage_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingGasMultiStage coil(model);

  EXPECT_TRUE(coil.setUnsigned(openstudio::Coil_Heating_Gas_MultiStageFields::NumberofStages, 3u));
  EXPECT_EQ(3u, coil.numberOfStages());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(12.5));
  ASSERT_TRUE(coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(12.5, *coil.offCycleParasiticGasLoad());
  ASSERT_TRUE(coil.parasiticGasLoad());
  EXPECT_DOUBLE_EQ(12.5, *coil.parasiticGasLoad());

  EXPECT_TRUE(coil.setParasiticGasLoad(9.75));
  ASSERT_TRUE(coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(9.75, *coil.offCycleParasiticGasLoad());

  coil.resetParasiticGasLoad();
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(3.2));
  coil.resetOffCycleParasiticGasLoad();
  EXPECT_FALSE(coil.offCycleParasiticGasLoad());
}
