/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/ExternalInterfaceFunctionalMockupUnitImport.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImport_DefaultConstructor) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImport object(model, "test.fmu");

  EXPECT_EQ(ExternalInterfaceFunctionalMockupUnitImport::iddObjectType(), object.iddObject().type());
  EXPECT_EQ("test.fmu", object.fMUFileName());
  EXPECT_TRUE(object.isFMUTimeoutDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fMUTimeout());
  EXPECT_TRUE(object.isFMULoggingOnDefaulted());
  EXPECT_EQ(0, object.fMULoggingOn());
}

TEST_F(EPModelFixture, ExternalInterfaceFunctionalMockupUnitImport_ScalarAccessors_RoundTrip) {
  Model model;
  ExternalInterfaceFunctionalMockupUnitImport object(model, "test.fmu");

  EXPECT_TRUE(object.setFMUTimeout(100.0));
  EXPECT_DOUBLE_EQ(100.0, object.fMUTimeout());
  EXPECT_FALSE(object.isFMUTimeoutDefaulted());

  object.resetFMUTimeout();
  EXPECT_TRUE(object.isFMUTimeoutDefaulted());
  EXPECT_DOUBLE_EQ(0.0, object.fMUTimeout());

  EXPECT_TRUE(object.setFMULoggingOn(2));
  EXPECT_EQ(2, object.fMULoggingOn());
  EXPECT_FALSE(object.isFMULoggingOnDefaulted());

  object.resetFMULoggingOn();
  EXPECT_TRUE(object.isFMULoggingOnDefaulted());
  EXPECT_EQ(0, object.fMULoggingOn());

  EXPECT_TRUE(object.setFMUFileName("updated.fmu"));
  EXPECT_EQ("updated.fmu", object.fMUFileName());
}
