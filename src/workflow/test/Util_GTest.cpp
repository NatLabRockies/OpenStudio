/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Util.hpp"
#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idd/IddObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <map>
#include <string>

using namespace openstudio;

class WorkflowFixture : public testing::Test
{
};

TEST_F(WorkflowFixture, Util_sanitizeKey) {

  const std::map<std::string, std::string> hash_with_sanitized_keys = {
    {"Regular", "Regular"},
    {"key1!@#", "key1"},
    {"key2.{}\\", "key2"},
    {"key3_ ", "key3"},
    {"invalid|key", "invalid_key"},
    {"another key", "another key"},
    {"special@char", "special_char"},
    {"key.with.dots", "key_with_dots"},
    {"key with spaces", "key with spaces"},
    {"slashes\\/included", "slashes_included"},
    {"pipe|character", "pipe_character"},
    {"!exclamation", "_exclamation"},
    {"@at_symbol", "_at_symbol"},
    {"#hash_symbol", "_hash_symbol"},
    {"$dollar_sign", "_dollar_sign"},
    {"%percent_sign", "_percent_sign"},
    {"^caret", "_caret"},
    {"&ampersand", "_ampersand"},
    {"*asterisk", "_asterisk"},
    {"(open_parenthesis)", "_open_parenthesis"},
    {"{open_brace}", "_open_brace"},
    {"}close_brace{", "_close_brace"},
    {"\\backslash\\", "_backslash"},
    {"[open_square]", "_open_square"},
    {"]close_square", "_close_square"},
    {";semicolon;", "_semicolon"},
    {":colon:", "_colon"},
    {"'single_quote'", "_single_quote"},
    {"\"double_quote\"", "_double_quote"},
    {",comma,", "_comma"},
    {"<less_than>", "_less_than"},
    {".period.", "_period"},
    {">greater_than<", "_greater_than"},
    {"/forward_slash/", "_forward_slash"},
    {"?question_mark?", "_question_mark"},
    {"=equal_sign=", "_equal_sign"},
    {"+plus_sign+", "_plus_sign"},
    {"___", ""},  // Consecutive underscores to be squeezed
    {"key_with___underscores", "key_with_underscores"},
    {"key_with__underscores", "key_with_underscores"},
    {"key_with_underscores", "key_with_underscores"},
    {"__underscored__key__", "_underscored_key"},          // Multiple underscores within the key
    {"___double___underscores___", "_double_underscores"}  // Multiple consecutive underscores
  };

  for (const auto& [originalKey, expectedKey] : hash_with_sanitized_keys) {
    const std::string sanitizedKey = openstudio::workflow::util::sanitizeKey(originalKey);
    // Check if the sanitized key matches the expected value
    EXPECT_EQ(sanitizedKey, expectedKey) << "Error: Key '" << originalKey << "' was not sanitized as expected.";
  }
}

TEST_F(WorkflowFixture, Util_mergeOutputTableSummaryReports) {
  IdfObject existingObject(IddObjectType::Output_Table_SummaryReports);
  existingObject.pushExtensibleGroup({"InputVerificationandResultsSummary"});
  existingObject.pushExtensibleGroup({"ClimaticDataSummary"});

  IdfObject newObject(IddObjectType::Output_Table_SummaryReports);
  newObject.pushExtensibleGroup({"ComponentSizingSummary"});
  newObject.pushExtensibleGroup({"ClimaticDataSummary"});
  newObject.pushExtensibleGroup({"EnvelopeSummary"});

  EXPECT_TRUE(openstudio::workflow::util::mergeOutputTableSummaryReports(existingObject, newObject));
  ASSERT_EQ(4, existingObject.numExtensibleGroups());
  auto egs = existingObject.extensibleGroups();
  EXPECT_EQ("InputVerificationandResultsSummary", egs.at(0).getString(0).get());
  EXPECT_EQ("ClimaticDataSummary", egs.at(1).getString(0).get());
  EXPECT_EQ("ComponentSizingSummary", egs.at(2).getString(0).get());
  EXPECT_EQ("EnvelopeSummary", egs.at(3).getString(0).get());
}

TEST_F(WorkflowFixture, Util_addEnergyPlusOutputRequest) {

  Workspace w(StrictnessLevel::Draft, IddFileType::EnergyPlus);
  std::vector<IdfObject> energyPlusOutputRequests;
  {
    // Unique with explicit merge
    WorkspaceObject wo = w.addObject(IdfObject(IddObjectType::Output_Table_SummaryReports)).get();
    wo.pushExtensibleGroup({"InputVerificationandResultsSummary"});
    wo.pushExtensibleGroup({"ClimaticDataSummary"});

    auto& newObject = energyPlusOutputRequests.emplace_back(IddObjectType::Output_Table_SummaryReports);
    newObject.pushExtensibleGroup({"ComponentSizingSummary"});
    newObject.pushExtensibleGroup({"ClimaticDataSummary"});
    newObject.pushExtensibleGroup({"EnvelopeSummary"});

    EXPECT_TRUE(openstudio::workflow::util::addEnergyPlusOutputRequest(w, newObject));
    {
      auto wos = w.getObjectsByType(IddObjectType::Output_Table_SummaryReports);
      ASSERT_EQ(1, wos.size());
      auto egs = wos.front().extensibleGroups();
      EXPECT_EQ("InputVerificationandResultsSummary", egs.at(0).getString(0).get());
      EXPECT_EQ("ClimaticDataSummary", egs.at(1).getString(0).get());
      EXPECT_EQ("ComponentSizingSummary", egs.at(2).getString(0).get());
      EXPECT_EQ("EnvelopeSummary", egs.at(3).getString(0).get());
    }
  }
  {
    // Unique and present already
    WorkspaceObject wo = w.addObject(IdfObject(IddObjectType::Output_SQLite)).get();
    wo.setString(0, "Simple");

    auto& newObject = energyPlusOutputRequests.emplace_back(IddObjectType::Output_SQLite);
    newObject.setString(0, "SimpleAndTabular");
    newObject.setString(1, "JtoKWH");

    EXPECT_TRUE(openstudio::workflow::util::addEnergyPlusOutputRequest(w, newObject));
    {
      auto wos = w.getObjectsByType(IddObjectType::Output_SQLite);
      ASSERT_EQ(1, wos.size());
      const auto& new_wo = wos.front();
      EXPECT_EQ("SimpleAndTabular", new_wo.getString(0).get());
      EXPECT_EQ("JtoKWH", new_wo.getString(1).get());
    }
  }
  {
    // Unique and not present already
    auto& newObject = energyPlusOutputRequests.emplace_back(IddObjectType::Output_Diagnostics);
    newObject.setString(0, "DisplayExtraWarnings");
    newObject.setString(1, "DisplayUnusedSchedules");

    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Output_Diagnostics).size());
    EXPECT_TRUE(openstudio::workflow::util::addEnergyPlusOutputRequest(w, newObject));
    {
      auto wos = w.getObjectsByType(IddObjectType::Output_Diagnostics);
      ASSERT_EQ(1, wos.size());
      const auto& new_wo = wos.front();
      EXPECT_EQ("DisplayExtraWarnings", new_wo.getString(0).get());
      EXPECT_EQ("DisplayUnusedSchedules", new_wo.getString(1).get());
    }
  }
  {
    // Non unique, and present already
    WorkspaceObject wo = w.addObject(IdfObject(IddObjectType::Schedule_Constant)).get();
    wo.setString(0, "AlwaysOn");
    wo.setDouble(2, 1.0);

    auto& newObject = energyPlusOutputRequests.emplace_back(IddObjectType::Schedule_Constant);
    newObject.setString(0, "AlwaysOn");
    newObject.setDouble(2, 1.0);

    EXPECT_TRUE(w.getObjectByTypeAndName(IddObjectType::Schedule_Constant, "AlwaysOn"));
    EXPECT_FALSE(openstudio::workflow::util::addEnergyPlusOutputRequest(w, newObject));
    {
      EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Schedule_Constant).size());
      EXPECT_TRUE(w.getObjectByTypeAndName(IddObjectType::Schedule_Constant, "AlwaysOn"));
    }
  }
  {
    // Non unique, and not present already
    auto& newObject = energyPlusOutputRequests.emplace_back(IddObjectType::Schedule_Constant);
    newObject.setString(0, "A New Schedule");
    newObject.setDouble(2, 18.0);
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Schedule_Constant).size());
    EXPECT_TRUE(w.getObjectByTypeAndName(IddObjectType::Schedule_Constant, "AlwaysOn"));
    EXPECT_TRUE(openstudio::workflow::util::addEnergyPlusOutputRequest(w, newObject));
    {
      auto wos = w.getObjectsByType(IddObjectType::Schedule_Constant);
      ASSERT_EQ(2, wos.size());
      EXPECT_TRUE(w.getObjectByTypeAndName(IddObjectType::Schedule_Constant, "AlwaysOn"));
      auto new_wo_ = w.getObjectByTypeAndName(IddObjectType::Schedule_Constant, "A New Schedule");
      ASSERT_TRUE(new_wo_);
      EXPECT_EQ("A New Schedule", new_wo_->getString(0).get());
      EXPECT_TRUE(new_wo_->isEmpty(1));
      EXPECT_EQ(18.0, new_wo_->getDouble(2).get());
    }
  }
}

TEST_F(WorkflowFixture, Util_isEnergyPlusOutputRequestPotentiallyUnsafe) {

  std::vector<IddObjectType> should_be_allowed{
    IddObjectType::Output_Table_Annual,
    IddObjectType::Meter_Custom,
    IddObjectType::Schedule_Compact,
    IddObjectType::Output_Diagnostics,
    IddObjectType::Output_Variable,
    IddObjectType::EnergyManagementSystem_OutputVariable,
    IddObjectType::PythonPlugin_OutputVariable,
    IddObjectType::LifeCycleCost_Parameters,
    IddObjectType::UtilityCost_Tariff,
    IddObjectType::ComponentCost_Adjustments,
    IddObjectType::Compliance_Building,
    IddObjectType::CurrencyType,
  };
  for (const auto& iddObjectType : should_be_allowed) {
    EXPECT_FALSE(openstudio::workflow::util::isEnergyPlusOutputRequestPotentiallyUnsafe(iddObjectType)) << "Failed for " << iddObjectType;
  }

  EXPECT_TRUE(openstudio::workflow::util::isEnergyPlusOutputRequestPotentiallyUnsafe(IddObjectType::People));
}
