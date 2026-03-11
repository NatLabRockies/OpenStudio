/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/GroundHeatTransferBasementInterior.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, GroundHeatTransferBasementInterior_DefaultConstructor) {
  Model model;
  GroundHeatTransferBasementInterior object(model);
  EXPECT_EQ(GroundHeatTransferBasementInterior::iddObjectType(), object.iddObject().type());
}

TEST_F(EPModelFixture, GroundHeatTransferBasementInterior_ScalarAccessorsRoundTrip) {
  Model model;
  GroundHeatTransferBasementInterior object(model);

  EXPECT_TRUE(object.isCONDFlagIsthebasementconditionedDefaulted());
  EXPECT_TRUE(object.isHINDownwardconvectiononlyheattransfercoefficientDefaulted());
  EXPECT_TRUE(object.isHINUpwardconvectiononlyheattransfercoefficientDefaulted());
  EXPECT_TRUE(object.isHINHorizontalconvectiononlyheattransfercoefficientDefaulted());
  EXPECT_TRUE(object.isHINDownwardcombinedconvectionandradiationheattransfercoefficientDefaulted());
  EXPECT_TRUE(object.isHINUpwardcombinedconvectionandradiationheattransfercoefficientDefaulted());
  EXPECT_TRUE(object.isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted());

  EXPECT_TRUE(object.setCONDFlagIsthebasementconditioned(false));
  EXPECT_FALSE(object.cONDFlagIsthebasementconditioned());
  EXPECT_FALSE(object.isCONDFlagIsthebasementconditionedDefaulted());
  object.resetCONDFlagIsthebasementconditioned();
  EXPECT_TRUE(object.isCONDFlagIsthebasementconditionedDefaulted());

  EXPECT_TRUE(object.setHINDownwardconvectiononlyheattransfercoefficient(0.93));
  EXPECT_TRUE(object.setHINUpwardconvectiononlyheattransfercoefficient(4.05));
  EXPECT_TRUE(object.setHINHorizontalconvectiononlyheattransfercoefficient(3.09));
  EXPECT_TRUE(object.setHINDownwardcombinedconvectionandradiationheattransfercoefficient(6.14));
  EXPECT_TRUE(object.setHINUpwardcombinedconvectionandradiationheattransfercoefficient(9.27));
  EXPECT_TRUE(object.setHINHorizontalcombinedconvectionandradiationheattransfercoefficient(8.30));

  EXPECT_DOUBLE_EQ(0.93, object.hINDownwardconvectiononlyheattransfercoefficient());
  EXPECT_DOUBLE_EQ(4.05, object.hINUpwardconvectiononlyheattransfercoefficient());
  EXPECT_DOUBLE_EQ(3.09, object.hINHorizontalconvectiononlyheattransfercoefficient());
  EXPECT_DOUBLE_EQ(6.14, object.hINDownwardcombinedconvectionandradiationheattransfercoefficient());
  EXPECT_DOUBLE_EQ(9.27, object.hINUpwardcombinedconvectionandradiationheattransfercoefficient());
  EXPECT_DOUBLE_EQ(8.30, object.hINHorizontalcombinedconvectionandradiationheattransfercoefficient());

  EXPECT_FALSE(object.isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted());
  object.resetHINHorizontalcombinedconvectionandradiationheattransfercoefficient();
  EXPECT_TRUE(object.isHINHorizontalcombinedconvectionandradiationheattransfercoefficientDefaulted());
}
