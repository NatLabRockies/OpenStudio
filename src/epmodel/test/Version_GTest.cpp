/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/Version.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, Version_DefaultConstructor) {
  Model model;
  Version version(model);
  EXPECT_EQ(Version::iddObjectType(), version.iddObject().type());
}

TEST_F(EPModelFixture, Version_ScalarAccessors_RoundTrip) {
  Model model;
  Version version(model);

  EXPECT_TRUE(version.isVersionIdentifierDefaulted());
  EXPECT_TRUE(version.setVersionIdentifier("42.0"));
  EXPECT_FALSE(version.isVersionIdentifierDefaulted());
  EXPECT_EQ("42.0", version.versionIdentifier());
  version.resetVersionIdentifier();
  EXPECT_TRUE(version.isVersionIdentifierDefaulted());
}
