/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/Branch_Impl.hpp"
#include "../StraightComponent/FanConstantVolume.hpp"
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>
#include <utilities/idd/Branch_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, API_Branch_DefaultConstructor) {
  Model model;
  Branch branch(model);
  EXPECT_EQ(Branch::iddObjectType(), branch.iddObject().type());
  EXPECT_FALSE(branch.nameString().empty());
}

TEST_F(EPModelFixture, API_Branch_ComponentAndNodeNameApis) {
  Model model;
  Branch branch(model);
  FanConstantVolume fan(model);
  fan.setName("API Test Fan");

  ASSERT_TRUE(branch.getImpl<detail::Branch_Impl>()->appendComponent(fan.cast<ModelObject>(), "Inlet Node", "Outlet Node"));

  auto workspaceGroup = branch.extensibleGroups().front().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup);
  ASSERT_TRUE(workspaceGroup->getString(openstudio::BranchExtensibleFields::ComponentName));
  EXPECT_EQ(fan.nameString(), workspaceGroup->getString(openstudio::BranchExtensibleFields::ComponentName).get());
  ASSERT_TRUE(workspaceGroup->getTarget(openstudio::BranchExtensibleFields::ComponentName));
  EXPECT_EQ(fan.handle(), workspaceGroup->getTarget(openstudio::BranchExtensibleFields::ComponentName)->handle());

  const auto components = branch.components();
  ASSERT_EQ(1u, components.size());
  EXPECT_EQ(fan.cast<ModelObject>(), components[0]);
  ASSERT_TRUE(branch.componentInletNode(0));
  ASSERT_TRUE(branch.componentOutletNode(0));
  EXPECT_EQ("Inlet Node", branch.componentInletNode(0)->nameString());
  EXPECT_EQ("Outlet Node", branch.componentOutletNode(0)->nameString());

  auto renamedInlet = model.getOrCreateTransientByName<Node>("Renamed Inlet");
  auto renamedOutlet = model.getOrCreateTransientByName<Node>("Renamed Outlet");
  EXPECT_TRUE(branch.getImpl<detail::Branch_Impl>()->setComponentInletNode(0, renamedInlet));
  EXPECT_TRUE(branch.getImpl<detail::Branch_Impl>()->setComponentOutletNode(0, renamedOutlet));
  ASSERT_TRUE(branch.componentInletNode(0));
  ASSERT_TRUE(branch.componentOutletNode(0));
  EXPECT_EQ("Renamed Inlet", branch.componentInletNode(0)->nameString());
  EXPECT_EQ("Renamed Outlet", branch.componentOutletNode(0)->nameString());
}

TEST_F(EPModelFixture, Branch_ScalarAccessors_RoundTrip) {
  Model model;
  Branch branch(model);

  ASSERT_TRUE(branch.setName("Main Supply Branch"));
  EXPECT_EQ("Main Supply Branch", branch.nameString());
}
