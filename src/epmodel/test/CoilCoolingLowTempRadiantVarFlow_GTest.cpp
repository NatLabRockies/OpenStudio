/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  auto coolingCoil = radiant.coolingCoil();
  ASSERT_TRUE(coolingCoil);
  auto typed = coolingCoil->cast<CoilCoolingLowTempRadiantVarFlow>();
  auto coolingImpl = typed.getImpl<openstudio::epmodel::detail::CoilCoolingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(coolingImpl);
  EXPECT_TRUE(coolingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}
