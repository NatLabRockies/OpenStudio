/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../OutputTableMonthly.hpp"
#include "../OutputTableMonthly_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, OutputTableMonthly_GettersSetters) {
  Model m;
  OutputTableMonthly outputTableMonthly(m);

  outputTableMonthly.setName("My OutputTableMonthly");

  // default moved to ctor
  EXPECT_EQ(2, outputTableMonthly.digitsAfterDecimal());

  // Digits After Decimal: Required Integer
  EXPECT_TRUE(outputTableMonthly.setDigitsAfterDecimal(7));
  EXPECT_EQ(7, outputTableMonthly.digitsAfterDecimal());
  // Bad Value
  EXPECT_FALSE(outputTableMonthly.setDigitsAfterDecimal(-10));
  EXPECT_EQ(7, outputTableMonthly.digitsAfterDecimal());
}

TEST_F(ModelFixture, OutputTableMonthly_MonthlyVariableGroups) {

  Model m;

  // Wrong Aggregation Type (not in choices)
  EXPECT_FALSE(OutputTableMonthly::isAggregationTypeValid("BADAGGREGATION"));
  EXPECT_THROW(MonthlyVariableGroup("Zone Air System Sensible Cooling Energy", "BADAGGREGATION"), openstudio::Exception);

  // Name can't be empty
  EXPECT_THROW(MonthlyVariableGroup("", "SumOrAverage"), openstudio::Exception);

  EXPECT_NO_THROW(MonthlyVariableGroup("Zone Air System Sensible Cooling Energy", "SumOrAverage"));
  EXPECT_NO_THROW(MonthlyVariableGroup("Zone Air System Sensible Cooling Energy"));

  OutputTableMonthly table(m);

  EXPECT_EQ(0, table.numberofMonthlyVariableGroups());
  EXPECT_TRUE(table.addMonthlyVariableGroup("Zone Air System Sensible Cooling Energy"));
  EXPECT_EQ(1, table.numberofMonthlyVariableGroups());
  EXPECT_EQ("SumOrAverage", table.getMonthlyVariableGroup(0)->aggregationType());

  auto group2 = MonthlyVariableGroup("Zone Air System Sensible Cooling Energy", "Maximum");
  EXPECT_TRUE(table.addMonthlyVariableGroup(group2));
  EXPECT_EQ(2, table.numberofMonthlyVariableGroups());

  auto group3 = MonthlyVariableGroup("Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum");
  EXPECT_TRUE(table.addMonthlyVariableGroup(group3));
  EXPECT_EQ(3, table.numberofMonthlyVariableGroups());

  boost::optional<MonthlyVariableGroup> group_ = table.getMonthlyVariableGroup(1U);
  ASSERT_TRUE(group_);
  EXPECT_EQ("Zone Air System Sensible Cooling Energy", group_->variableOrMeterName());
  EXPECT_EQ("Maximum", group_->aggregationType());

  // Test that you cannot add the same group twice
  auto group2bis = MonthlyVariableGroup("Zone Air System Sensible Cooling Energy", "Maximum");
  // Test that we can locate an existing group correctly
  boost::optional<unsigned> _existingIndex = table.monthlyVariableGroupIndex(group2bis);
  ASSERT_TRUE(_existingIndex);
  EXPECT_EQ(1U, _existingIndex.get());

  // Now call add, which should return false
  EXPECT_FALSE(table.addMonthlyVariableGroup(group2bis));
  // Should still have the same number
  EXPECT_EQ(3, table.numberofMonthlyVariableGroups());

  // Via the overloaded method, also check that it doesn't care about case-sensitivity
  EXPECT_FALSE(table.addMonthlyVariableGroup("Zone Air System SENSIBLE Cooling Energy", "MAXIMUM"));
  EXPECT_EQ(3, table.numberofMonthlyVariableGroups());

  // Test that you cannot get a group by an index that's too high
  EXPECT_FALSE(table.getMonthlyVariableGroup(table.numberofMonthlyVariableGroups()));

  // Test that you cannot find a group if it doesn't exist
  auto groupother = MonthlyVariableGroup("Another surface", "Maximum");
  EXPECT_FALSE(table.monthlyVariableGroupIndex(groupother));

  // Remove
  EXPECT_FALSE(table.removeMonthlyVariableGroup(1000));
  EXPECT_EQ(3, table.numberofMonthlyVariableGroups());

  EXPECT_TRUE(table.removeMonthlyVariableGroup(1));
  EXPECT_EQ(2, table.numberofMonthlyVariableGroups());

  // check that remaining blocks moved correctly
  std::vector<MonthlyVariableGroup> groups = table.monthlyVariableGroups();
  EXPECT_EQ(2U, groups.size());
  EXPECT_EQ("Zone Air System Sensible Cooling Energy", groups[0].variableOrMeterName());
  EXPECT_EQ("SumOrAverage", groups[0].aggregationType());

  EXPECT_EQ("Site Outdoor Air Drybulb Temperature", groups[1].variableOrMeterName());
  EXPECT_EQ("ValueWhenMaximumOrMinimum", groups[1].aggregationType());

  // more remove checking
  table.removeAllMonthlyVariableGroups();
  EXPECT_EQ(0, table.numberofMonthlyVariableGroups());
  EXPECT_FALSE(table.removeMonthlyVariableGroup(0));
  EXPECT_EQ(0, table.numberofMonthlyVariableGroups());

  // Via a vector
  EXPECT_TRUE(table.addMonthlyVariableGroups({group2bis, groupother, group3}));
  groups = table.monthlyVariableGroups();
  EXPECT_EQ(3U, groups.size());
  EXPECT_EQ(group2bis.variableOrMeterName(), groups[0].variableOrMeterName());
  EXPECT_EQ(group2bis.aggregationType(), groups[0].aggregationType());
  EXPECT_EQ(group2bis, groups[0]);

  EXPECT_EQ(groupother.variableOrMeterName(), groups[1].variableOrMeterName());
  EXPECT_EQ(groupother.aggregationType(), groups[1].aggregationType());
  EXPECT_EQ(groupother, groups[1]);

  EXPECT_EQ(group3.variableOrMeterName(), groups[2].variableOrMeterName());
  EXPECT_EQ(group3.aggregationType(), groups[2].aggregationType());
  EXPECT_EQ(group3, groups[2]);
}

TEST_F(ModelFixture, OutputTableMonthly_AdvancedAggregationTypes) {

  Model m;
  EXPECT_FALSE(OutputTableMonthly::isAggregationTypeAdvanced("SumOrAverage"));
  EXPECT_TRUE(OutputTableMonthly::isAggregationTypeAdvanced("ValueWhenMaximumOrMinimum"));

  std::vector<MonthlyVariableGroup> groups{
    {"Zone Air System Sensible Cooling Energy", "SumOrAverage"},
    {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
    {"Zone Total Internal Latent Gain Energy", "SumOrAverage"},
    {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
  };

  OutputTableMonthly table(m);

  for (const auto& group : groups) {
    EXPECT_TRUE(table.addMonthlyVariableGroup(group));
  }
  EXPECT_EQ(4, table.numberofMonthlyVariableGroups());
}

TEST_F(ModelFixture, OutputTableMonthly_FactoryMethod) {
  Model m;

  std::vector<std::string> standardReportNames = OutputTableMonthly::validStandardReportNames();
  EXPECT_GT(standardReportNames.size(), 50);

  for (const auto& standardReportName : standardReportNames) {
    EXPECT_NO_THROW(OutputTableMonthly::fromStandardReports(m, standardReportName));
  }
  EXPECT_EQ(standardReportNames.size(), m.getConcreteModelObjects<OutputTableMonthly>().size());
}
