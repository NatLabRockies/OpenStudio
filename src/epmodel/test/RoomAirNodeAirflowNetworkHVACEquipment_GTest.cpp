/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirNodeAirflowNetworkHVACEquipment.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkHVACEquipment_DefaultConstructor) {
  Model model;
  RoomAirNodeAirflowNetworkHVACEquipment object(model);
  EXPECT_EQ(RoomAirNodeAirflowNetworkHVACEquipment::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirNodeAirflowNetworkHVACEquipment_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirNodeAirflowNetworkHVACEquipment object(model);

  EXPECT_FALSE(object.fractionOfOutputOrSupplyAirFromHVACEquipment1());
  EXPECT_TRUE(object.setFractionOfOutputOrSupplyAirFromHVACEquipment1(0.45));
  ASSERT_TRUE(object.fractionOfOutputOrSupplyAirFromHVACEquipment1());
  EXPECT_DOUBLE_EQ(0.45, object.fractionOfOutputOrSupplyAirFromHVACEquipment1().get());
  EXPECT_FALSE(object.setFractionOfOutputOrSupplyAirFromHVACEquipment1(-0.1));
  EXPECT_FALSE(object.setFractionOfOutputOrSupplyAirFromHVACEquipment1(1.1));
  object.resetFractionOfOutputOrSupplyAirFromHVACEquipment1();
  EXPECT_FALSE(object.fractionOfOutputOrSupplyAirFromHVACEquipment1());

  EXPECT_FALSE(object.fractionOfInputOrReturnAirToHVACEquipment1());
  EXPECT_TRUE(object.setFractionOfInputOrReturnAirToHVACEquipment1(0.65));
  ASSERT_TRUE(object.fractionOfInputOrReturnAirToHVACEquipment1());
  EXPECT_DOUBLE_EQ(0.65, object.fractionOfInputOrReturnAirToHVACEquipment1().get());
  EXPECT_FALSE(object.setFractionOfInputOrReturnAirToHVACEquipment1(-0.2));
  EXPECT_FALSE(object.setFractionOfInputOrReturnAirToHVACEquipment1(1.2));
  object.resetFractionOfInputOrReturnAirToHVACEquipment1();
  EXPECT_FALSE(object.fractionOfInputOrReturnAirToHVACEquipment1());
}
