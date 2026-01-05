/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "ModelFixture.hpp"
#include "../OutputControlResilienceSummaries.hpp"
#include "../OutputControlResilienceSummaries_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, OutputControlResilienceSummaries_GettersSetters) {
  Model m;
  OutputControlResilienceSummaries mo = m.getUniqueModelObject<OutputControlResilienceSummaries>();

  EXPECT_EQ("Simplified", mo.heatIndexAlgorithm());

  EXPECT_TRUE(mo.setHeatIndexAlgorithm("Extended"));
  EXPECT_EQ("Extended", mo.heatIndexAlgorithm());

  EXPECT_FALSE(mo.setHeatIndexAlgorithm("BADENUM"));
  EXPECT_EQ("Extended", mo.heatIndexAlgorithm());
}  // End of Getter_Setters test
