/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/OutputTableAnnual.hpp"
#include "../../model/OutputTableAnnual_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/ScheduleConstant.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Output_Table_Annual_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputTableAnnual) {

  ForwardTranslator ft;

  Model m;
  OutputTableAnnual outputTableAnnual(m);

  outputTableAnnual.setName("Zone Electric Annual Summary");
  EXPECT_TRUE(outputTableAnnual.setFilter("Zone 1"));
  ScheduleConstant schedule(m);
  schedule.setName("SCH");
  EXPECT_TRUE(outputTableAnnual.setSchedule(schedule));
  {
    // Zero Extensible Groups = not translated
    const Workspace w = ft.translateModel(m);
    const auto wos = w.getObjectsByType(IddObjectType::Output_Table_Annual);
    EXPECT_TRUE(wos.empty());
  }

  {
    std::vector<AnnualVariableGroup> groups{
      AnnualVariableGroup("Zone Lights Electricity Energy", "SumOrAverage", 4),
      AnnualVariableGroup("Zone Lights Electricity Energy", "Maximum", 1),
    };
    EXPECT_TRUE(outputTableAnnual.addAnnualVariableGroups(groups));
    EXPECT_EQ(2, outputTableAnnual.numberofAnnualVariableGroups());

    const Workspace w = ft.translateModel(m);
    const auto wos = w.getObjectsByType(IddObjectType::Output_Table_Annual);
    ASSERT_EQ(1u, wos.size());
    const auto& wo = wos.front();
    EXPECT_EQ("Zone Electric Annual Summary", wo.nameString());
    ASSERT_TRUE(wo.getTarget(Output_Table_AnnualFields::ScheduleName));
    EXPECT_EQ("SCH", wo.getTarget(Output_Table_AnnualFields::ScheduleName)->nameString());
    ASSERT_TRUE(wo.getString(Output_Table_AnnualFields::Filter));
    EXPECT_EQ("Zone 1", wo.getString(Output_Table_AnnualFields::Filter).get());

    ASSERT_EQ(2, wo.numExtensibleGroups());
    for (const auto& idf_eg : wo.extensibleGroups()) {
      auto& group = groups[idf_eg.groupIndex()];
      EXPECT_EQ(group.variableorMeterorEMSVariableorField(),
                idf_eg.getString(Output_Table_AnnualExtensibleFields::VariableorMeterorEMSVariableorFieldName).get());
      EXPECT_EQ(group.aggregationType(), idf_eg.getString(Output_Table_AnnualExtensibleFields::AggregationTypeforVariableorMeter).get());
      EXPECT_EQ(group.digitsAfterDecimal(), idf_eg.getInt(Output_Table_AnnualExtensibleFields::DigitsAfterDecimal).get());
    }
  }
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputTableAnnual) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woOTA = w.addObject(IdfObject(IddObjectType::Output_Table_Annual)).get();

  woOTA.setName("My OutputTableAnnual");
  EXPECT_TRUE(woOTA.setString(Output_Table_AnnualFields::Filter, "Zone 1"));
  auto woschedule = w.addObject(IdfObject(IddObjectType::Schedule_Constant)).get();
  woschedule.setName("My schedule");
  EXPECT_TRUE(woOTA.setPointer(Output_Table_AnnualFields::ScheduleName, woschedule.handle()));

  woOTA.pushExtensibleGroup({"Zone Lights Electricity Energy", "SumOrAverage", ""});
  woOTA.pushExtensibleGroup({"Zone Electric Equipment Electricity Energy", "Maximum", "1"});

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputTableAnnual>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  ASSERT_TRUE(modelObject.filter());
  EXPECT_EQ("Zone 1", modelObject.filter().get());
  ASSERT_TRUE(modelObject.schedule());
  EXPECT_EQ("My schedule", modelObject.schedule()->nameString());

  EXPECT_EQ(2, modelObject.numberofAnnualVariableGroups());
  {
    auto group = modelObject.getAnnualVariableGroup(0).get();
    EXPECT_EQ("Zone Lights Electricity Energy", group.variableorMeterorEMSVariableorField());
    EXPECT_EQ("SumOrAverage", group.aggregationType());
    EXPECT_EQ(2, group.digitsAfterDecimal());
  }
  {
    auto group = modelObject.getAnnualVariableGroup(1).get();
    EXPECT_EQ("Zone Electric Equipment Electricity Energy", group.variableorMeterorEMSVariableorField());
    EXPECT_EQ("Maximum", group.aggregationType());
    EXPECT_EQ(1, group.digitsAfterDecimal());
  }
}
