/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ModelObject/WindowsCalculationEngine.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, WindowsCalculationEngine_DefaultConstructor) {
  Model model;
  WindowsCalculationEngine engine(model);
  EXPECT_EQ(WindowsCalculationEngine::iddObjectType(), engine.iddObject().type());
}

TEST_F(EPModelFixture, WindowsCalculationEngine_ScalarAccessors_RoundTrip) {
  Model model;
  WindowsCalculationEngine engine(model);

  const auto allValues = WindowsCalculationEngine::windowsEngineValues();
  ASSERT_LE(1u, allValues.size());

  const auto defaultValue = engine.windowsEngine();
  auto alternateValue = defaultValue;
  for (const auto& value : allValues) {
    if (value != defaultValue) {
      alternateValue = value;
      break;
    }
  }
  ASSERT_NE(alternateValue, defaultValue);

  EXPECT_TRUE(engine.setWindowsEngine(alternateValue));
  EXPECT_EQ(alternateValue, engine.windowsEngine());
  EXPECT_FALSE(engine.isWindowsEngineDefaulted());

  engine.resetWindowsEngine();
  EXPECT_EQ(defaultValue, engine.windowsEngine());
  EXPECT_TRUE(engine.isWindowsEngineDefaulted());
}
