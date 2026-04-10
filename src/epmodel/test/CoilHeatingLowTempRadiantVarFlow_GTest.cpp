/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantVarFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantVarFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);
  ASSERT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  auto heatingCoil = radiant.heatingCoil();
  ASSERT_TRUE(heatingCoil);
  auto typed = heatingCoil->cast<CoilHeatingLowTempRadiantVarFlow>();
  auto heatingImpl = typed.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantVarFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(typed.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), typed.containingZoneHVACComponent()->handle());
}
