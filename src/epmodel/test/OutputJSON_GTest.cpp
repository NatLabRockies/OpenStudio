/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputJSON.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputJSON_DefaultConstructor) {
  Model model;
  OutputJSON outputJSON(model);

  EXPECT_EQ(OutputJSON::iddObjectType(), outputJSON.iddObject().type());
  EXPECT_EQ("TimeSeriesAndTabular", outputJSON.optionType());
  EXPECT_TRUE(outputJSON.outputJSON());
  EXPECT_FALSE(outputJSON.outputCBOR());
  EXPECT_FALSE(outputJSON.outputMessagePack());
}

TEST_F(EPModelFixture, OutputJSON_ScalarAccessors_RoundTrip) {
  Model model;
  OutputJSON outputJSON(model);

  EXPECT_FALSE(OutputJSON::optionTypeValues().empty());

  EXPECT_TRUE(outputJSON.setOptionType("TimeSeries"));
  EXPECT_EQ("TimeSeries", outputJSON.optionType());

  EXPECT_FALSE(outputJSON.setOptionType("BadEnum"));
  EXPECT_EQ("TimeSeries", outputJSON.optionType());

  EXPECT_TRUE(outputJSON.setOutputJSON(false));
  EXPECT_TRUE(outputJSON.setOutputCBOR(true));
  EXPECT_TRUE(outputJSON.setOutputMessagePack(true));

  EXPECT_FALSE(outputJSON.outputJSON());
  EXPECT_TRUE(outputJSON.outputCBOR());
  EXPECT_TRUE(outputJSON.outputMessagePack());
}
