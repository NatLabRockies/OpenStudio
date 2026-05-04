/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ParentObject/AirflowNetworkSimulationControl.hpp"
#include "../ParentObject/AirflowNetworkSimulationControl_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, AirflowNetworkSimulationControl_DefaultConstructor) {
  Model model;
  auto simulationControl = model.getUniqueModelObject<AirflowNetworkSimulationControl>();
  EXPECT_EQ(AirflowNetworkSimulationControl::iddObjectType(), simulationControl.iddObject().type());
}

TEST_F(EPModelFixture, AirflowNetworkSimulationControl_ScalarAccessors_RoundTrip) {
  Model model;
  auto simulationControl = model.getUniqueModelObject<AirflowNetworkSimulationControl>();

  EXPECT_FALSE(AirflowNetworkSimulationControl::airflowNetworkControlValues().empty());
  EXPECT_EQ("NoMultizoneOrDistribution", simulationControl.airflowNetworkControl());
  EXPECT_TRUE(simulationControl.isAirflowNetworkControlDefaulted());
  EXPECT_TRUE(simulationControl.setAirflowNetworkControl("MultizoneWithoutDistribution"));
  EXPECT_EQ("MultizoneWithoutDistribution", simulationControl.airflowNetworkControl());
  EXPECT_FALSE(simulationControl.isAirflowNetworkControlDefaulted());
  simulationControl.resetAirflowNetworkControl();
  EXPECT_TRUE(simulationControl.isAirflowNetworkControlDefaulted());
  EXPECT_EQ("NoMultizoneOrDistribution", simulationControl.airflowNetworkControl());

  EXPECT_FALSE(AirflowNetworkSimulationControl::windPressureCoefficientTypeValues().empty());
  EXPECT_EQ("SurfaceAverageCalculation", simulationControl.windPressureCoefficientType());
  EXPECT_TRUE(simulationControl.setWindPressureCoefficientType("Input"));
  EXPECT_EQ("Input", simulationControl.windPressureCoefficientType());
  simulationControl.resetWindPressureCoefficientType();
  EXPECT_EQ("SurfaceAverageCalculation", simulationControl.windPressureCoefficientType());

  EXPECT_FALSE(AirflowNetworkSimulationControl::heightSelectionforLocalWindPressureCalculationValues().empty());
  EXPECT_EQ("OpeningHeight", simulationControl.heightSelectionforLocalWindPressureCalculation());
  EXPECT_TRUE(simulationControl.setHeightSelectionforLocalWindPressureCalculation("ExternalNode"));
  EXPECT_EQ("ExternalNode", simulationControl.heightSelectionforLocalWindPressureCalculation());
  simulationControl.resetHeightSelectionforLocalWindPressureCalculation();
  EXPECT_EQ("OpeningHeight", simulationControl.heightSelectionforLocalWindPressureCalculation());

  EXPECT_FALSE(AirflowNetworkSimulationControl::buildingTypeValues().empty());
  EXPECT_EQ("LowRise", simulationControl.buildingType());
  EXPECT_TRUE(simulationControl.setBuildingType("HighRise"));
  EXPECT_EQ("HighRise", simulationControl.buildingType());
  simulationControl.resetBuildingType();
  EXPECT_EQ("LowRise", simulationControl.buildingType());

  EXPECT_EQ(500, simulationControl.maximumNumberofIterations());
  EXPECT_TRUE(simulationControl.setMaximumNumberofIterations(700));
  EXPECT_EQ(700, simulationControl.maximumNumberofIterations());
  EXPECT_FALSE(simulationControl.setMaximumNumberofIterations(10));
  EXPECT_EQ(700, simulationControl.maximumNumberofIterations());
  simulationControl.resetMaximumNumberofIterations();
  EXPECT_EQ(500, simulationControl.maximumNumberofIterations());

  EXPECT_FALSE(AirflowNetworkSimulationControl::initializationTypeValues().empty());
  EXPECT_EQ("ZeroNodePressures", simulationControl.initializationType());
  EXPECT_TRUE(simulationControl.setInitializationType("LinearInitializationMethod"));
  EXPECT_EQ("LinearInitializationMethod", simulationControl.initializationType());
  simulationControl.resetInitializationType();
  EXPECT_EQ("ZeroNodePressures", simulationControl.initializationType());

  EXPECT_DOUBLE_EQ(1.0e-4, simulationControl.relativeAirflowConvergenceTolerance());
  EXPECT_TRUE(simulationControl.setRelativeAirflowConvergenceTolerance(2.0e-4));
  EXPECT_DOUBLE_EQ(2.0e-4, simulationControl.relativeAirflowConvergenceTolerance());
  EXPECT_FALSE(simulationControl.setRelativeAirflowConvergenceTolerance(0.0));
  simulationControl.resetRelativeAirflowConvergenceTolerance();
  EXPECT_DOUBLE_EQ(1.0e-4, simulationControl.relativeAirflowConvergenceTolerance());

  EXPECT_DOUBLE_EQ(1.0e-6, simulationControl.absoluteAirflowConvergenceTolerance());
  EXPECT_TRUE(simulationControl.setAbsoluteAirflowConvergenceTolerance(2.0e-6));
  EXPECT_DOUBLE_EQ(2.0e-6, simulationControl.absoluteAirflowConvergenceTolerance());
  EXPECT_FALSE(simulationControl.setAbsoluteAirflowConvergenceTolerance(0.0));
  simulationControl.resetAbsoluteAirflowConvergenceTolerance();
  EXPECT_DOUBLE_EQ(1.0e-6, simulationControl.absoluteAirflowConvergenceTolerance());

  EXPECT_DOUBLE_EQ(-0.5, simulationControl.convergenceAccelerationLimit());
  EXPECT_TRUE(simulationControl.setConvergenceAccelerationLimit(0.5));
  EXPECT_DOUBLE_EQ(0.5, simulationControl.convergenceAccelerationLimit());
  EXPECT_FALSE(simulationControl.setConvergenceAccelerationLimit(1.5));
  simulationControl.resetConvergenceAccelerationLimit();
  EXPECT_DOUBLE_EQ(-0.5, simulationControl.convergenceAccelerationLimit());

  EXPECT_DOUBLE_EQ(0.0, simulationControl.azimuthAngleofLongAxisofBuilding());
  EXPECT_TRUE(simulationControl.setAzimuthAngleofLongAxisofBuilding(45.0));
  EXPECT_DOUBLE_EQ(45.0, simulationControl.azimuthAngleofLongAxisofBuilding());
  EXPECT_FALSE(simulationControl.setAzimuthAngleofLongAxisofBuilding(-1.0));
  simulationControl.resetAzimuthAngleofLongAxisofBuilding();
  EXPECT_DOUBLE_EQ(0.0, simulationControl.azimuthAngleofLongAxisofBuilding());

  EXPECT_DOUBLE_EQ(1.0, simulationControl.ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis());
  EXPECT_TRUE(simulationControl.setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(0.5));
  EXPECT_DOUBLE_EQ(0.5, simulationControl.ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis());
  EXPECT_FALSE(simulationControl.setRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis(1.5));
  simulationControl.resetRatioofBuildingWidthAlongShortAxistoWidthAlongLongAxis();
  EXPECT_DOUBLE_EQ(1.0, simulationControl.ratioofBuildingWidthAlongShortAxistoWidthAlongLongAxis());

  EXPECT_FALSE(simulationControl.heightDependenceofExternalNodeTemperature());
  simulationControl.setHeightDependenceofExternalNodeTemperature(true);
  EXPECT_TRUE(simulationControl.heightDependenceofExternalNodeTemperature());
  simulationControl.setHeightDependenceofExternalNodeTemperature(false);
  EXPECT_FALSE(simulationControl.heightDependenceofExternalNodeTemperature());
  simulationControl.resetHeightDependenceofExternalNodeTemperature();
  EXPECT_FALSE(simulationControl.heightDependenceofExternalNodeTemperature());

  EXPECT_FALSE(AirflowNetworkSimulationControl::solverValues().empty());
  EXPECT_EQ("SkylineLU", simulationControl.solver());
  EXPECT_TRUE(simulationControl.setSolver("ConjugateGradient"));
  EXPECT_EQ("ConjugateGradient", simulationControl.solver());
  simulationControl.resetSolver();
  EXPECT_EQ("SkylineLU", simulationControl.solver());

  EXPECT_FALSE(simulationControl.allowUnsupportedZoneEquipment());
  simulationControl.setAllowUnsupportedZoneEquipment(true);
  EXPECT_TRUE(simulationControl.allowUnsupportedZoneEquipment());
  simulationControl.setAllowUnsupportedZoneEquipment(false);
  EXPECT_FALSE(simulationControl.allowUnsupportedZoneEquipment());
  simulationControl.resetAllowUnsupportedZoneEquipment();
  EXPECT_FALSE(simulationControl.allowUnsupportedZoneEquipment());
}
