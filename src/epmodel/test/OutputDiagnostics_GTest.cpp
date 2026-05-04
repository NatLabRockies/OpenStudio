/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include "../ModelObject/OutputDiagnostics.hpp"
#include "../ModelObject/OutputDiagnostics_Impl.hpp"

#include <utilities/idd/Output_Diagnostics_FieldEnums.hxx>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, OutputDiagnostics_DefaultConstructor) {
  Model model;
  auto outputDiagnostics = model.getUniqueModelObject<OutputDiagnostics>();

  EXPECT_EQ(OutputDiagnostics::iddObjectType(), outputDiagnostics.iddObject().type());
}

TEST_F(EPModelFixture, OutputDiagnostics_ScalarAccessors_RoundTrip) {
  Model model;
  auto outputDiagnostics = model.getUniqueModelObject<OutputDiagnostics>();

  // Output:Diagnostics has no fixed scalar fields; validate scalar roundtrip on extensible Key entries.
  auto group = outputDiagnostics.pushExtensibleGroup();
  auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(workspaceGroup);

  EXPECT_TRUE(workspaceGroup->setString(openstudio::Output_DiagnosticsExtensibleFields::Key, "DisplayExtraWarnings"));

  const auto key = workspaceGroup->getString(openstudio::Output_DiagnosticsExtensibleFields::Key);
  ASSERT_TRUE(key);
  EXPECT_EQ("DisplayExtraWarnings", *key);
}
