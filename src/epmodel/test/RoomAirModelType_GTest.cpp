/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/RoomAirModelType.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RoomAirModelType_DefaultConstructor) {
  Model model;
  RoomAirModelType roomAirModelType(model);
  EXPECT_EQ(RoomAirModelType::iddObjectType(), roomAirModelType.iddObject().type());
}

TEST_F(EPModelFixture, RoomAirModelType_ScalarAccessors_RoundTrip) {
  Model model;
  RoomAirModelType roomAirModelType(model);

  const auto roomAirModelingTypes = RoomAirModelType::roomAirModelingTypeValues();
  EXPECT_FALSE(roomAirModelingTypes.empty());
  EXPECT_TRUE(roomAirModelType.isRoomAirModelingTypeDefaulted());
  EXPECT_EQ("Mixing", roomAirModelType.roomAirModelingType());

  EXPECT_TRUE(roomAirModelType.setRoomAirModelingType("CrossVentilation"));
  EXPECT_EQ("CrossVentilation", roomAirModelType.roomAirModelingType());
  EXPECT_FALSE(roomAirModelType.isRoomAirModelingTypeDefaulted());
  roomAirModelType.resetRoomAirModelingType();
  EXPECT_TRUE(roomAirModelType.isRoomAirModelingTypeDefaulted());
  EXPECT_EQ("Mixing", roomAirModelType.roomAirModelingType());

  const auto airTemperatureCouplingStrategies = RoomAirModelType::airTemperatureCouplingStrategyValues();
  EXPECT_FALSE(airTemperatureCouplingStrategies.empty());
  EXPECT_TRUE(roomAirModelType.isAirTemperatureCouplingStrategyDefaulted());
  EXPECT_EQ("Direct", roomAirModelType.airTemperatureCouplingStrategy());

  EXPECT_TRUE(roomAirModelType.setAirTemperatureCouplingStrategy("Indirect"));
  EXPECT_EQ("Indirect", roomAirModelType.airTemperatureCouplingStrategy());
  EXPECT_FALSE(roomAirModelType.isAirTemperatureCouplingStrategyDefaulted());
  roomAirModelType.resetAirTemperatureCouplingStrategy();
  EXPECT_TRUE(roomAirModelType.isAirTemperatureCouplingStrategyDefaulted());
  EXPECT_EQ("Direct", roomAirModelType.airTemperatureCouplingStrategy());
}
