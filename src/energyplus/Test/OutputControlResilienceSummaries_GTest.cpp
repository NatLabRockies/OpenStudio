/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"
#include "../ReverseTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/OutputControlResilienceSummaries.hpp"
#include "../../model/OutputControlResilienceSummaries_Impl.hpp"

#include "../../utilities/idf/IdfFile.hpp"
#include "../../utilities/idf/Workspace.hpp"
#include "../../utilities/idf/IdfObject.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"

#include <utilities/idd/OutputControl_ResilienceSummaries_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_OutputControlResilienceSummaries) {

  ForwardTranslator ft;

  // Create a model
  Model m;

  // Not there: IDF doesn't have it either
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfObjs = w.getObjectsByType(IddObjectType::OutputControl_ResilienceSummaries);
    EXPECT_EQ(0, idfObjs.size());
  }

  // Get the unique object
  OutputControlResilienceSummaries outputControlResilienceSummaries = m.getUniqueModelObject<OutputControlResilienceSummaries>();
  EXPECT_EQ("Simplified", outputControlResilienceSummaries.heatIndexAlgorithm());
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfObjs = w.getObjectsByType(IddObjectType::OutputControl_ResilienceSummaries);
    ASSERT_EQ(1, idfObjs.size());
    auto const& idf_rs = idfObjs.front();

    EXPECT_EQ("Simplified", idf_rs.getString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm).get());
  }
  {
    EXPECT_TRUE(outputControlResilienceSummaries.setHeatIndexAlgorithm("Extended"));
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idfObjs = w.getObjectsByType(IddObjectType::OutputControl_ResilienceSummaries);
    ASSERT_EQ(1, idfObjs.size());
    auto const& idf_rs = idfObjs.front();

    EXPECT_EQ("Extended", idf_rs.getString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm).get());
  }
}

TEST_F(EnergyPlusFixture, ReverseTranslator_OutputControlResilienceSummaries) {

  ReverseTranslator rt;

  Workspace w(StrictnessLevel::Minimal, IddFileType::EnergyPlus);

  // Not there, Model shouldn't have it either
  {
    Model m = rt.translateWorkspace(w);
    EXPECT_FALSE(m.getOptionalUniqueModelObject<OutputControlResilienceSummaries>());
  }

  OptionalWorkspaceObject _i_outputControlResilienceSummaries = w.addObject(IdfObject(IddObjectType::OutputControl_ResilienceSummaries));
  ASSERT_TRUE(_i_outputControlResilienceSummaries);

  // There but no keys, Model shouldn't have it either
  {
    Model m = rt.translateWorkspace(w);
    EXPECT_FALSE(m.getOptionalUniqueModelObject<OutputControlResilienceSummaries>());
  }

  _i_outputControlResilienceSummaries->setString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, "Simplified");

  {
    Model m = rt.translateWorkspace(w);
    ASSERT_TRUE(m.getOptionalUniqueModelObject<OutputControlResilienceSummaries>());
    auto outputControlResilienceSummaries = m.getUniqueModelObject<OutputControlResilienceSummaries>();
    EXPECT_EQ("Simplified", outputControlResilienceSummaries.heatIndexAlgorithm());
  }

  _i_outputControlResilienceSummaries->setString(OutputControl_ResilienceSummariesFields::HeatIndexAlgorithm, "Extended");
  {
    Model m = rt.translateWorkspace(w);
    ASSERT_TRUE(m.getOptionalUniqueModelObject<OutputControlResilienceSummaries>());
    auto outputControlResilienceSummaries = m.getUniqueModelObject<OutputControlResilienceSummaries>();
    EXPECT_EQ("Extended", outputControlResilienceSummaries.heatIndexAlgorithm());
  }
}
