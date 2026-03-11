/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../BranchList.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_BranchList_DefaultConstructor) {
  Model model;
  BranchList branchList(model);
  EXPECT_EQ(BranchList::iddObjectType(), branchList.iddObject().type());
  EXPECT_FALSE(branchList.nameString().empty());
}

TEST_F(EPModelFixture, API_BranchList_DefaultBranchesEmpty) {
  Model model;
  BranchList branchList(model);
  EXPECT_EQ(1u, branchList.branches().size());
}
