/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WaterHeaterSizing.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WaterHeaterSizing_DefaultConstructor) {
  Model model;
  WaterHeaterSizing sizing(model);

  EXPECT_EQ(WaterHeaterSizing::iddObjectType(), sizing.iddObject().type());
  ASSERT_TRUE(sizing.designMode());
  EXPECT_EQ("PeakDraw", *sizing.designMode());

  ASSERT_TRUE(sizing.timeStorageCanMeetPeakDraw());
  EXPECT_DOUBLE_EQ(0.538503, *sizing.timeStorageCanMeetPeakDraw());

  ASSERT_TRUE(sizing.timeforTankRecovery());
  EXPECT_DOUBLE_EQ(0.0, *sizing.timeforTankRecovery());

  ASSERT_TRUE(sizing.nominalTankVolumeforAutosizingPlantConnections());
  EXPECT_DOUBLE_EQ(1.0, *sizing.nominalTankVolumeforAutosizingPlantConnections());
}

TEST_F(EPModelFixture, WaterHeaterSizing_ScalarAccessors_RoundTrip) {
  Model model;
  WaterHeaterSizing sizing(model);

  EXPECT_TRUE(sizing.setDesignMode("PerPerson"));
  EXPECT_TRUE(sizing.setTimeStorageCanMeetPeakDraw(1.1));
  EXPECT_TRUE(sizing.setTimeforTankRecovery(0.9));
  EXPECT_TRUE(sizing.setNominalTankVolumeforAutosizingPlantConnections(2.2));
  EXPECT_TRUE(sizing.setNumberofBedrooms(3));
  EXPECT_TRUE(sizing.setNumberofBathrooms(2));
  EXPECT_TRUE(sizing.setStorageCapacityperPerson(0.33));
  EXPECT_TRUE(sizing.setRecoveryCapacityperPerson(0.44));
  EXPECT_TRUE(sizing.setStorageCapacityperFloorArea(0.55));
  EXPECT_TRUE(sizing.setRecoveryCapacityperFloorArea(0.66));
  EXPECT_TRUE(sizing.setNumberofUnits(5.5));
  EXPECT_TRUE(sizing.setStorageCapacityperUnit(1.1));
  EXPECT_TRUE(sizing.setRecoveryCapacityPerUnit(1.2));
  EXPECT_TRUE(sizing.setStorageCapacityperCollectorArea(2.3));
  EXPECT_TRUE(sizing.setHeightAspectRatio(3.3));

  ASSERT_TRUE(sizing.designMode());
  EXPECT_EQ("PerPerson", *sizing.designMode());

  ASSERT_TRUE(sizing.timeStorageCanMeetPeakDraw());
  EXPECT_DOUBLE_EQ(1.1, *sizing.timeStorageCanMeetPeakDraw());

  ASSERT_TRUE(sizing.timeforTankRecovery());
  EXPECT_DOUBLE_EQ(0.9, *sizing.timeforTankRecovery());

  ASSERT_TRUE(sizing.nominalTankVolumeforAutosizingPlantConnections());
  EXPECT_DOUBLE_EQ(2.2, *sizing.nominalTankVolumeforAutosizingPlantConnections());

  ASSERT_TRUE(sizing.numberofBedrooms());
  EXPECT_EQ(3, *sizing.numberofBedrooms());

  ASSERT_TRUE(sizing.numberofBathrooms());
  EXPECT_EQ(2, *sizing.numberofBathrooms());

  ASSERT_TRUE(sizing.storageCapacityperPerson());
  EXPECT_DOUBLE_EQ(0.33, *sizing.storageCapacityperPerson());

  ASSERT_TRUE(sizing.recoveryCapacityperPerson());
  EXPECT_DOUBLE_EQ(0.44, *sizing.recoveryCapacityperPerson());

  ASSERT_TRUE(sizing.storageCapacityperFloorArea());
  EXPECT_DOUBLE_EQ(0.55, *sizing.storageCapacityperFloorArea());

  ASSERT_TRUE(sizing.recoveryCapacityperFloorArea());
  EXPECT_DOUBLE_EQ(0.66, *sizing.recoveryCapacityperFloorArea());

  ASSERT_TRUE(sizing.numberofUnits());
  EXPECT_DOUBLE_EQ(5.5, *sizing.numberofUnits());

  ASSERT_TRUE(sizing.storageCapacityperUnit());
  EXPECT_DOUBLE_EQ(1.1, *sizing.storageCapacityperUnit());

  ASSERT_TRUE(sizing.recoveryCapacityPerUnit());
  EXPECT_DOUBLE_EQ(1.2, *sizing.recoveryCapacityPerUnit());

  ASSERT_TRUE(sizing.storageCapacityperCollectorArea());
  EXPECT_DOUBLE_EQ(2.3, *sizing.storageCapacityperCollectorArea());

  ASSERT_TRUE(sizing.heightAspectRatio());
  EXPECT_DOUBLE_EQ(3.3, *sizing.heightAspectRatio());
}
