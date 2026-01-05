/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../OutputTableAnnual.hpp"
#include "../OutputTableAnnual_Impl.hpp"

#include "../Schedule.hpp"
#include "../ScheduleConstant.hpp"
#include "../ScheduleTypeLimits.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, OutputTableAnnual_GettersSetters) {
  Model m;
  OutputTableAnnual outputTableAnnual(m);

  outputTableAnnual.setName("My OutputTableAnnual");

  // Filter: Optional String
  EXPECT_FALSE(outputTableAnnual.filter());
  EXPECT_TRUE(outputTableAnnual.setFilter("KeyValue"));
  ASSERT_TRUE(outputTableAnnual.filter());
  EXPECT_EQ("KeyValue", outputTableAnnual.filter().get());
  outputTableAnnual.resetFilter();
  EXPECT_FALSE(outputTableAnnual.filter());

  // Schedule Name: Optional Object
  EXPECT_FALSE(outputTableAnnual.schedule());
  ScheduleConstant sch(m);
  EXPECT_FALSE(sch.scheduleTypeLimits());
  EXPECT_TRUE(outputTableAnnual.setSchedule(sch));
  ASSERT_TRUE(outputTableAnnual.schedule());
  EXPECT_EQ(sch, outputTableAnnual.schedule().get());

  // The Schedule Type Registry should have done it's thing and assigned a scheduleTypeLimits
  ASSERT_TRUE(sch.scheduleTypeLimits());
  auto sch_type_lim = sch.scheduleTypeLimits().get();
  EXPECT_EQ("OnOff", sch_type_lim.nameString());
  ASSERT_TRUE(sch_type_lim.lowerLimitValue());
  EXPECT_EQ(0.0, sch_type_lim.lowerLimitValue().get());
  ASSERT_TRUE(sch_type_lim.upperLimitValue());
  EXPECT_EQ(1.0, sch_type_lim.upperLimitValue().get());
  ASSERT_TRUE(sch_type_lim.numericType());
  EXPECT_EQ("Discrete", sch_type_lim.numericType().get());
  EXPECT_EQ("Availability", sch_type_lim.unitType());

  outputTableAnnual.resetSchedule();
  EXPECT_FALSE(outputTableAnnual.schedule());
}

TEST_F(ModelFixture, OutputTableAnnual_AnnualVariableGroups) {

  Model m;

  // Wrong Aggregation Type (not in choices)
  EXPECT_FALSE(OutputTableAnnual::isAggregationTypeValid("BADAGGREGATION"));
  EXPECT_THROW(AnnualVariableGroup("Zone Air System Sensible Cooling Energy", "BADAGGREGATION"), openstudio::Exception);

  // Name can't be empty
  EXPECT_THROW(AnnualVariableGroup("", "SumOrAverage"), openstudio::Exception);

  EXPECT_NO_THROW(AnnualVariableGroup("Zone Air System Sensible Cooling Energy", "SumOrAverage", 2));
  EXPECT_NO_THROW(AnnualVariableGroup("Zone Air System Sensible Cooling Energy", "SumOrAverage"));
  EXPECT_NO_THROW(AnnualVariableGroup("Zone Air System Sensible Cooling Energy"));

  OutputTableAnnual table(m);

  EXPECT_EQ(0, table.numberofAnnualVariableGroups());
  EXPECT_TRUE(table.addAnnualVariableGroup("Zone Air System Sensible Cooling Energy"));
  EXPECT_EQ(1, table.numberofAnnualVariableGroups());
  EXPECT_EQ("SumOrAverage", table.getAnnualVariableGroup(0)->aggregationType());
  EXPECT_EQ(2, table.getAnnualVariableGroup(0)->digitsAfterDecimal());

  auto group2 = AnnualVariableGroup("Zone Air System Sensible Cooling Energy", "Maximum", 3);
  EXPECT_TRUE(table.addAnnualVariableGroup(group2));
  EXPECT_EQ(2, table.numberofAnnualVariableGroups());

  auto group3 = AnnualVariableGroup("Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum", 4);
  EXPECT_TRUE(table.addAnnualVariableGroup(group3));
  EXPECT_EQ(3, table.numberofAnnualVariableGroups());

  boost::optional<AnnualVariableGroup> group_ = table.getAnnualVariableGroup(1U);
  ASSERT_TRUE(group_);
  EXPECT_EQ("Zone Air System Sensible Cooling Energy", group_->variableorMeterorEMSVariableorField());
  EXPECT_EQ("Maximum", group_->aggregationType());
  EXPECT_EQ(3, group_->digitsAfterDecimal());

  // Test that you cannot add the same group twice, it'll replace it
  auto group2bis = AnnualVariableGroup("Zone Air System Sensible Cooling Energy", "Maximum", 6);
  // Test that we can locate an existing group correctly
  boost::optional<unsigned> _existingIndex = table.annualVariableGroupIndex(group2bis);
  ASSERT_TRUE(_existingIndex);
  EXPECT_EQ(1U, _existingIndex.get());

  // Now call add, which should return true
  EXPECT_TRUE(table.addAnnualVariableGroup(group2bis));
  // Should still have the same number
  EXPECT_EQ(3, table.numberofAnnualVariableGroups());
  group_ = table.getAnnualVariableGroup(1U);
  ASSERT_TRUE(group_);
  EXPECT_EQ("Zone Air System Sensible Cooling Energy", group_->variableorMeterorEMSVariableorField());
  EXPECT_EQ("Maximum", group_->aggregationType());
  EXPECT_EQ(6, group_->digitsAfterDecimal());

  // Via the overloaded method, also check that it doesn't care about case-sensitivity
  EXPECT_TRUE(table.addAnnualVariableGroup("Zone Air System SENSIBLE Cooling Energy", "MAXIMUM", 8));
  EXPECT_EQ(3, table.numberofAnnualVariableGroups());
  group_ = table.getAnnualVariableGroup(1U);
  ASSERT_TRUE(group_);
  EXPECT_EQ("Zone Air System SENSIBLE Cooling Energy", group_->variableorMeterorEMSVariableorField());
  EXPECT_EQ("MAXIMUM", group_->aggregationType());
  EXPECT_EQ(8, group_->digitsAfterDecimal());

  // Test that you cannot get a group by an index that's too high
  EXPECT_FALSE(table.getAnnualVariableGroup(table.numberofAnnualVariableGroups()));

  // Test that you cannot find a group if it doesn't exist
  auto groupother = AnnualVariableGroup("Another var", "Maximum");
  EXPECT_FALSE(table.annualVariableGroupIndex(groupother));

  // Remove
  EXPECT_FALSE(table.removeAnnualVariableGroup(1000));
  EXPECT_EQ(3, table.numberofAnnualVariableGroups());

  EXPECT_TRUE(table.removeAnnualVariableGroup(1));
  EXPECT_EQ(2, table.numberofAnnualVariableGroups());

  // check that remaining blocks moved correctly
  std::vector<AnnualVariableGroup> groups = table.annualVariableGroups();
  EXPECT_EQ(2U, groups.size());
  EXPECT_EQ("Zone Air System Sensible Cooling Energy", groups[0].variableorMeterorEMSVariableorField());
  EXPECT_EQ("SumOrAverage", groups[0].aggregationType());
  EXPECT_EQ(2, groups[0].digitsAfterDecimal());

  EXPECT_EQ("Site Outdoor Air Drybulb Temperature", groups[1].variableorMeterorEMSVariableorField());
  EXPECT_EQ("ValueWhenMaximumOrMinimum", groups[1].aggregationType());
  EXPECT_EQ(4, groups[1].digitsAfterDecimal());

  // more remove checking
  table.removeAllAnnualVariableGroups();
  EXPECT_EQ(0, table.numberofAnnualVariableGroups());
  EXPECT_FALSE(table.removeAnnualVariableGroup(0));
  EXPECT_EQ(0, table.numberofAnnualVariableGroups());

  // Via a vector
  EXPECT_TRUE(table.addAnnualVariableGroups({group2bis, groupother, group3}));
  groups = table.annualVariableGroups();
  EXPECT_EQ(3U, groups.size());
  EXPECT_EQ(group2bis.variableorMeterorEMSVariableorField(), groups[0].variableorMeterorEMSVariableorField());
  EXPECT_EQ(group2bis.aggregationType(), groups[0].aggregationType());
  EXPECT_EQ(group2bis.digitsAfterDecimal(), groups[0].digitsAfterDecimal());
  EXPECT_EQ(group2bis, groups[0]);

  EXPECT_EQ(groupother.variableorMeterorEMSVariableorField(), groups[1].variableorMeterorEMSVariableorField());
  EXPECT_EQ(groupother.aggregationType(), groups[1].aggregationType());
  EXPECT_EQ(groupother.digitsAfterDecimal(), groups[1].digitsAfterDecimal());
  EXPECT_EQ(groupother, groups[1]);

  EXPECT_EQ(group3.variableorMeterorEMSVariableorField(), groups[2].variableorMeterorEMSVariableorField());
  EXPECT_EQ(group3.aggregationType(), groups[2].aggregationType());
  EXPECT_EQ(group3.digitsAfterDecimal(), groups[2].digitsAfterDecimal());
  EXPECT_EQ(group3, groups[2]);
}

TEST_F(ModelFixture, OutputTableAnnual_AdvancedAggregationTypes) {

  Model m;
  EXPECT_FALSE(OutputTableAnnual::isAggregationTypeAdvanced("SumOrAverage"));
  EXPECT_TRUE(OutputTableAnnual::isAggregationTypeAdvanced("ValueWhenMaximumOrMinimum"));

  std::vector<AnnualVariableGroup> groups{
    {"Zone Air System Sensible Cooling Energy", "SumOrAverage"},
    {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
    {"Zone Total Internal Latent Gain Energy", "SumOrAverage"},
    {"Site Outdoor Air Drybulb Temperature", "ValueWhenMaximumOrMinimum"},
  };

  OutputTableAnnual table(m);

  for (const auto& group : groups) {
    EXPECT_TRUE(table.addAnnualVariableGroup(group));
  }
  EXPECT_EQ(4, table.numberofAnnualVariableGroups());
}
