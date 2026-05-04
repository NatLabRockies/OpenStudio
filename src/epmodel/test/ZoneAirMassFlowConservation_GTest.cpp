/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ZoneAirMassFlowConservation.hpp"
#include "../ModelObject/ZoneAirMassFlowConservation_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneAirMassFlowConservation_DefaultConstructor) {
  Model model;
  auto zamfc = model.getUniqueModelObject<ZoneAirMassFlowConservation>();

  EXPECT_EQ(ZoneAirMassFlowConservation::iddObjectType(), zamfc.iddObject().type());
  EXPECT_FALSE(zamfc.handle().isNull());
}

TEST_F(EPModelFixture, ZoneAirMassFlowConservation_ScalarAccessors_RoundTrip) {
  Model model;
  auto zamfc = model.getUniqueModelObject<ZoneAirMassFlowConservation>();

  EXPECT_TRUE(zamfc.setAdjustZoneMixingandReturnForAirMassFlowBalance("AdjustReturnThenMixing"));
  EXPECT_FALSE(zamfc.isAdjustZoneMixingandReturnForAirMassFlowBalanceDefaulted());
  EXPECT_EQ("AdjustReturnThenMixing", zamfc.adjustZoneMixingandReturnForAirMassFlowBalance());

  EXPECT_TRUE(zamfc.setInfiltrationBalancingMethod("AdjustInfiltrationFlow"));
  EXPECT_FALSE(zamfc.isInfiltrationBalancingMethodDefaulted());
  EXPECT_EQ("AdjustInfiltrationFlow", zamfc.infiltrationBalancingMethod());

  EXPECT_TRUE(zamfc.setInfiltrationBalancingZones("AllZones"));
  EXPECT_FALSE(zamfc.isInfiltrationBalancingZonesDefaulted());
  EXPECT_EQ("AllZones", zamfc.infiltrationBalancingZones());
}
