/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteSolarAndVisibleSpectrum.hpp"

#include <utilities/core/StringHelpers.hpp>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteSolarAndVisibleSpectrum_DefaultConstructor) {
  Model model;
  SiteSolarAndVisibleSpectrum object(model);
  EXPECT_EQ(SiteSolarAndVisibleSpectrum::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, SiteSolarAndVisibleSpectrum_ScalarAccessors_RoundTrip) {
  Model model;
  SiteSolarAndVisibleSpectrum object(model);

  const auto spectrumDataMethodValues = SiteSolarAndVisibleSpectrum::spectrumDataMethodValues();
  ASSERT_FALSE(spectrumDataMethodValues.empty());

  EXPECT_TRUE(object.isSpectrumDataMethodDefaulted());
  EXPECT_EQ("Default", object.spectrumDataMethod());

  const auto nonDefaultIt = std::find_if(spectrumDataMethodValues.begin(), spectrumDataMethodValues.end(),
                                         [](const std::string& v) { return !openstudio::istringEqual(v, "Default"); });
  ASSERT_NE(nonDefaultIt, spectrumDataMethodValues.end());
  EXPECT_TRUE(object.setSpectrumDataMethod(*nonDefaultIt));
  EXPECT_EQ(*nonDefaultIt, object.spectrumDataMethod());
  EXPECT_FALSE(object.isSpectrumDataMethodDefaulted());

  EXPECT_FALSE(object.setSpectrumDataMethod("InvalidChoiceValue"));

  object.resetSpectrumDataMethod();
  EXPECT_TRUE(object.isSpectrumDataMethodDefaulted());
  EXPECT_EQ("Default", object.spectrumDataMethod());
}
