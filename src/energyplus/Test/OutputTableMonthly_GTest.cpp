/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/OutputTableMonthly.hpp"
#include "../../model/OutputTableMonthly_Impl.hpp"

#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"

// E+ FieldEnums
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/Output_Table_Monthly_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputTableMonthly) {

  ForwardTranslator ft;

  Model m;
  OutputTableMonthly outputTableMonthly(m);
  outputTableMonthly.setName("Zone Temperature Oscillation Report");
  EXPECT_TRUE(outputTableMonthly.setDigitsAfterDecimal(6));

  {
    // Zero Extensible Groups = not translated
    const Workspace w = ft.translateModel(m);
    const auto idfObjs = w.getObjectsByType(IddObjectType::Output_Table_Monthly);
    EXPECT_TRUE(idfObjs.empty());
  }

  {
    std::vector<MonthlyVariableGroup> groups{
      MonthlyVariableGroup("Zone Oscillating Temperatures Time", "HoursNonZero"),
      MonthlyVariableGroup("Zone People Occupant Count", "SumOrAverageDuringHoursShown"),
    };
    EXPECT_TRUE(outputTableMonthly.addMonthlyVariableGroups(groups));
    EXPECT_EQ(2, outputTableMonthly.numberofMonthlyVariableGroups());

    const Workspace w = ft.translateModel(m);
    const auto wos = w.getObjectsByType(IddObjectType::Output_Table_Monthly);
    ASSERT_EQ(1u, wos.size());
    const auto& wo = wos.front();
    EXPECT_EQ("Zone Temperature Oscillation Report", wo.nameString());
    EXPECT_EQ(6, wo.getInt(Output_Table_MonthlyFields::DigitsAfterDecimal).get());
    ASSERT_EQ(2, wo.numExtensibleGroups());
    for (const auto& idf_eg : wo.extensibleGroups()) {
      auto& group = groups[idf_eg.groupIndex()];

      EXPECT_EQ(group.variableOrMeterName(), idf_eg.getString(Output_Table_MonthlyExtensibleFields::VariableorMeterName).get());
      EXPECT_EQ(group.aggregationType(), idf_eg.getString(Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter).get());
    }
  }
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputTableMonthly) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  auto woOTM = w.addObject(IdfObject(IddObjectType::Output_Table_Monthly)).get();

  woOTM.setName("My OutputTableMonthly");
  EXPECT_TRUE(woOTM.setInt(Output_Table_MonthlyFields::DigitsAfterDecimal, 6));
  woOTM.pushExtensibleGroup({"Boiler Heating Energy", "Maximum"});
  woOTM.pushExtensibleGroup({"Boiler NaturalGas Energy", "SumOrAverage"});

  const Model m = rt.translateWorkspace(w);
  const auto modelObjects = m.getConcreteModelObjects<OutputTableMonthly>();
  ASSERT_EQ(1u, modelObjects.size());

  const auto& modelObject = modelObjects.front();
  EXPECT_EQ(6, modelObject.digitsAfterDecimal());
  EXPECT_EQ(2, modelObject.numberofMonthlyVariableGroups());
  {
    auto group = modelObject.getMonthlyVariableGroup(0).get();
    EXPECT_EQ("Boiler Heating Energy", group.variableOrMeterName());
    EXPECT_EQ("Maximum", group.aggregationType());
  }
  {
    auto group = modelObject.getMonthlyVariableGroup(1).get();
    EXPECT_EQ("Boiler NaturalGas Energy", group.variableOrMeterName());
    EXPECT_EQ("SumOrAverage", group.aggregationType());
  }
}
