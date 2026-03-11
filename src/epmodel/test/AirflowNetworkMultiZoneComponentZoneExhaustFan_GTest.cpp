/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/AirflowNetworkMultiZoneComponentZoneExhaustFan.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentZoneExhaustFan_DefaultConstructor) {
  Model model;
  AirflowNetworkMultiZoneComponentZoneExhaustFan zoneExhaustFan(model);
  EXPECT_EQ(AirflowNetworkMultiZoneComponentZoneExhaustFan::iddObjectType(), zoneExhaustFan.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkMultiZoneComponentZoneExhaustFan_ScalarAccessors_RoundTrip) {
  Model model;
  AirflowNetworkMultiZoneComponentZoneExhaustFan zoneExhaustFan(model);

  EXPECT_TRUE(zoneExhaustFan.setAirMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions(0.0014));
  EXPECT_DOUBLE_EQ(0.0014, zoneExhaustFan.airMassFlowCoefficientWhentheZoneExhaustFanisOffatReferenceConditions());

  EXPECT_TRUE(zoneExhaustFan.isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted());
  EXPECT_DOUBLE_EQ(0.65, zoneExhaustFan.airMassFlowExponentWhentheZoneExhaustFanisOff());

  EXPECT_TRUE(zoneExhaustFan.setAirMassFlowExponentWhentheZoneExhaustFanisOff(0.71));
  EXPECT_DOUBLE_EQ(0.71, zoneExhaustFan.airMassFlowExponentWhentheZoneExhaustFanisOff());
  EXPECT_FALSE(zoneExhaustFan.isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted());

  zoneExhaustFan.resetAirMassFlowExponentWhentheZoneExhaustFanisOff();
  EXPECT_TRUE(zoneExhaustFan.isAirMassFlowExponentWhentheZoneExhaustFanisOffDefaulted());
  EXPECT_DOUBLE_EQ(0.65, zoneExhaustFan.airMassFlowExponentWhentheZoneExhaustFanisOff());
}
