/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../scaffolds/SiteSpectrumData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteSpectrumData_DefaultConstructor) {
  Model model;
  SiteSpectrumData object(model);
  EXPECT_EQ(SiteSpectrumData::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteSpectrumData_ScalarAccessors_RoundTrip) {
  Model model;
  SiteSpectrumData object(model);

  const auto spectrumDataTypeValues = SiteSpectrumData::spectrumDataTypeValues();
  ASSERT_FALSE(spectrumDataTypeValues.empty());
  EXPECT_TRUE(object.setSpectrumDataType(spectrumDataTypeValues.front()));
  EXPECT_EQ(spectrumDataTypeValues.front(), object.spectrumDataType());

  EXPECT_FALSE(object.setSpectrumDataType("InvalidChoiceValue"));
}
