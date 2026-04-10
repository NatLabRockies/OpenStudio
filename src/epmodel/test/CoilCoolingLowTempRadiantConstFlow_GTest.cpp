/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantConstFlow.hpp"
#include "../StraightComponent/CoilCoolingLowTempRadiantConstFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingLowTempRadiantConstFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto coolingCoil = radiant.coolingCoil();
  auto coolingImpl = coolingCoil.getImpl<openstudio::epmodel::detail::CoilCoolingLowTempRadiantConstFlow_Impl>();

  ASSERT_TRUE(coolingImpl);
  EXPECT_TRUE(coolingImpl->isTransient());
  ASSERT_TRUE(coolingCoil.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), coolingCoil.containingZoneHVACComponent()->handle());
}
