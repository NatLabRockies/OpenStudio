/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/SimulationControl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SimulationControl_DefaultConstructor) {
  Model model;
  SimulationControl simulationControl(model);
  EXPECT_EQ(SimulationControl::iddObjectType(), simulationControl.iddObject().type());
}

TEST_F(EPModelFixture, SimulationControl_ScalarAccessors_RoundTrip) {
  Model model;
  SimulationControl simulationControl(model);

  const bool defaultDoZoneSizingCalculation = simulationControl.doZoneSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoZoneSizingCalculationDefaulted());
  EXPECT_TRUE(simulationControl.setDoZoneSizingCalculation(!defaultDoZoneSizingCalculation));
  EXPECT_FALSE(simulationControl.isDoZoneSizingCalculationDefaulted());
  EXPECT_EQ(!defaultDoZoneSizingCalculation, simulationControl.doZoneSizingCalculation());
  simulationControl.setDoZoneSizingCalculationNoFail(defaultDoZoneSizingCalculation);
  EXPECT_EQ(defaultDoZoneSizingCalculation, simulationControl.doZoneSizingCalculation());
  simulationControl.resetDoZoneSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoZoneSizingCalculationDefaulted());
  EXPECT_EQ(defaultDoZoneSizingCalculation, simulationControl.doZoneSizingCalculation());

  const bool defaultDoSystemSizingCalculation = simulationControl.doSystemSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoSystemSizingCalculationDefaulted());
  EXPECT_TRUE(simulationControl.setDoSystemSizingCalculation(!defaultDoSystemSizingCalculation));
  EXPECT_FALSE(simulationControl.isDoSystemSizingCalculationDefaulted());
  EXPECT_EQ(!defaultDoSystemSizingCalculation, simulationControl.doSystemSizingCalculation());
  simulationControl.setDoSystemSizingCalculationNoFail(defaultDoSystemSizingCalculation);
  EXPECT_EQ(defaultDoSystemSizingCalculation, simulationControl.doSystemSizingCalculation());
  simulationControl.resetDoSystemSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoSystemSizingCalculationDefaulted());
  EXPECT_EQ(defaultDoSystemSizingCalculation, simulationControl.doSystemSizingCalculation());

  const bool defaultDoPlantSizingCalculation = simulationControl.doPlantSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoPlantSizingCalculationDefaulted());
  EXPECT_TRUE(simulationControl.setDoPlantSizingCalculation(!defaultDoPlantSizingCalculation));
  EXPECT_FALSE(simulationControl.isDoPlantSizingCalculationDefaulted());
  EXPECT_EQ(!defaultDoPlantSizingCalculation, simulationControl.doPlantSizingCalculation());
  simulationControl.setDoPlantSizingCalculationNoFail(defaultDoPlantSizingCalculation);
  EXPECT_EQ(defaultDoPlantSizingCalculation, simulationControl.doPlantSizingCalculation());
  simulationControl.resetDoPlantSizingCalculation();
  EXPECT_TRUE(simulationControl.isDoPlantSizingCalculationDefaulted());
  EXPECT_EQ(defaultDoPlantSizingCalculation, simulationControl.doPlantSizingCalculation());

  const bool defaultRunSimulationforSizingPeriods = simulationControl.runSimulationforSizingPeriods();
  EXPECT_TRUE(simulationControl.isRunSimulationforSizingPeriodsDefaulted());
  EXPECT_TRUE(simulationControl.setRunSimulationforSizingPeriods(!defaultRunSimulationforSizingPeriods));
  EXPECT_FALSE(simulationControl.isRunSimulationforSizingPeriodsDefaulted());
  EXPECT_EQ(!defaultRunSimulationforSizingPeriods, simulationControl.runSimulationforSizingPeriods());
  simulationControl.setRunSimulationforSizingPeriodsNoFail(defaultRunSimulationforSizingPeriods);
  EXPECT_EQ(defaultRunSimulationforSizingPeriods, simulationControl.runSimulationforSizingPeriods());
  simulationControl.resetRunSimulationforSizingPeriods();
  EXPECT_TRUE(simulationControl.isRunSimulationforSizingPeriodsDefaulted());
  EXPECT_EQ(defaultRunSimulationforSizingPeriods, simulationControl.runSimulationforSizingPeriods());

  const bool defaultRunSimulationforWeatherFileRunPeriods = simulationControl.runSimulationforWeatherFileRunPeriods();
  EXPECT_TRUE(simulationControl.isRunSimulationforWeatherFileRunPeriodsDefaulted());
  EXPECT_TRUE(simulationControl.setRunSimulationforWeatherFileRunPeriods(!defaultRunSimulationforWeatherFileRunPeriods));
  EXPECT_FALSE(simulationControl.isRunSimulationforWeatherFileRunPeriodsDefaulted());
  EXPECT_EQ(!defaultRunSimulationforWeatherFileRunPeriods, simulationControl.runSimulationforWeatherFileRunPeriods());
  simulationControl.setRunSimulationforWeatherFileRunPeriodsNoFail(defaultRunSimulationforWeatherFileRunPeriods);
  EXPECT_EQ(defaultRunSimulationforWeatherFileRunPeriods, simulationControl.runSimulationforWeatherFileRunPeriods());
  simulationControl.resetRunSimulationforWeatherFileRunPeriods();
  EXPECT_TRUE(simulationControl.isRunSimulationforWeatherFileRunPeriodsDefaulted());
  EXPECT_EQ(defaultRunSimulationforWeatherFileRunPeriods, simulationControl.runSimulationforWeatherFileRunPeriods());

  const bool defaultDoHVACSizingSimulationforSizingPeriods = simulationControl.doHVACSizingSimulationforSizingPeriods();
  EXPECT_TRUE(simulationControl.isDoHVACSizingSimulationforSizingPeriodsDefaulted());
  EXPECT_TRUE(simulationControl.setDoHVACSizingSimulationforSizingPeriods(!defaultDoHVACSizingSimulationforSizingPeriods));
  EXPECT_FALSE(simulationControl.isDoHVACSizingSimulationforSizingPeriodsDefaulted());
  EXPECT_EQ(!defaultDoHVACSizingSimulationforSizingPeriods, simulationControl.doHVACSizingSimulationforSizingPeriods());
  simulationControl.setDoHVACSizingSimulationforSizingPeriodsNoFail(defaultDoHVACSizingSimulationforSizingPeriods);
  EXPECT_EQ(defaultDoHVACSizingSimulationforSizingPeriods, simulationControl.doHVACSizingSimulationforSizingPeriods());
  simulationControl.resetDoHVACSizingSimulationforSizingPeriods();
  EXPECT_TRUE(simulationControl.isDoHVACSizingSimulationforSizingPeriodsDefaulted());
  EXPECT_EQ(defaultDoHVACSizingSimulationforSizingPeriods, simulationControl.doHVACSizingSimulationforSizingPeriods());

  const int defaultMaximumNumberofHVACSizingSimulationPasses = simulationControl.maximumNumberofHVACSizingSimulationPasses();
  EXPECT_TRUE(simulationControl.isMaximumNumberofHVACSizingSimulationPassesDefaulted());
  EXPECT_TRUE(simulationControl.setMaximumNumberofHVACSizingSimulationPasses(defaultMaximumNumberofHVACSizingSimulationPasses + 1));
  EXPECT_FALSE(simulationControl.isMaximumNumberofHVACSizingSimulationPassesDefaulted());
  EXPECT_EQ(defaultMaximumNumberofHVACSizingSimulationPasses + 1, simulationControl.maximumNumberofHVACSizingSimulationPasses());
  EXPECT_FALSE(simulationControl.setMaximumNumberofHVACSizingSimulationPasses(0));
  EXPECT_EQ(defaultMaximumNumberofHVACSizingSimulationPasses + 1, simulationControl.maximumNumberofHVACSizingSimulationPasses());
  simulationControl.resetMaximumNumberofHVACSizingSimulationPasses();
  EXPECT_TRUE(simulationControl.isMaximumNumberofHVACSizingSimulationPassesDefaulted());
  EXPECT_EQ(defaultMaximumNumberofHVACSizingSimulationPasses, simulationControl.maximumNumberofHVACSizingSimulationPasses());
}
