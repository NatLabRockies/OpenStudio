/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/FaultModelFoulingAirFilter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, FaultModelFoulingAirFilter_DefaultConstructor) {
  Model model;
  FaultModelFoulingAirFilter fault(model);
  EXPECT_EQ(FaultModelFoulingAirFilter::iddObjectType(), fault.iddObject().type());
}

TEST_F(EPModelFixture, FaultModelFoulingAirFilter_ScalarAccessors_RoundTrip) {
  Model model;
  FaultModelFoulingAirFilter fault(model);

  const auto values = FaultModelFoulingAirFilter::fanObjectTypeValues();
  EXPECT_FALSE(values.empty());

  EXPECT_TRUE(fault.setFanObjectType("Fan:OnOff"));
  EXPECT_EQ("Fan:OnOff", fault.fanObjectType());

  EXPECT_TRUE(fault.setFanObjectType("Fan:VariableVolume"));
  EXPECT_EQ("Fan:VariableVolume", fault.fanObjectType());

  EXPECT_FALSE(fault.setFanObjectType("InvalidFanObjectType"));
  EXPECT_EQ("Fan:VariableVolume", fault.fanObjectType());
}
