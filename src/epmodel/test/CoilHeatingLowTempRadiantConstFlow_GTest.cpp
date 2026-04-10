/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow.hpp"
#include "../StraightComponent/CoilHeatingLowTempRadiantConstFlow_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantConstFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingLowTempRadiantConstFlow_IsTransientCompanionView) {
  Model model;
  ZoneHVACLowTempRadiantConstFlow radiant(model);
  auto heatingCoil = radiant.heatingCoil();
  auto heatingImpl = heatingCoil.getImpl<openstudio::epmodel::detail::CoilHeatingLowTempRadiantConstFlow_Impl>();

  ASSERT_TRUE(heatingImpl);
  EXPECT_TRUE(heatingImpl->isTransient());
  ASSERT_TRUE(heatingCoil.containingZoneHVACComponent());
  EXPECT_EQ(radiant.handle(), heatingCoil.containingZoneHVACComponent()->handle());
}
