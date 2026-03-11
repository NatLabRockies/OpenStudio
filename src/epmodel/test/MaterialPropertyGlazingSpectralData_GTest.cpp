/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ResourceObject/MaterialPropertyGlazingSpectralData.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, MaterialPropertyGlazingSpectralData_DefaultConstructor) {
  Model model;
  MaterialPropertyGlazingSpectralData glazingSpectralData(model);
  EXPECT_EQ(MaterialPropertyGlazingSpectralData::iddObjectType(), glazingSpectralData.iddObject().type());
}

TEST_F(EPModelFixture, MaterialPropertyGlazingSpectralData_ScalarAccessors_RoundTrip) {
  Model model;
  MaterialPropertyGlazingSpectralData glazingSpectralData(model);

  EXPECT_TRUE(glazingSpectralData.setName("Clear Triple Pane Spectral Data"));
  EXPECT_EQ("Clear Triple Pane Spectral Data", glazingSpectralData.nameString());
}
