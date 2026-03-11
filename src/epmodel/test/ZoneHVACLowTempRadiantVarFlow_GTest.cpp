/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../ZoneHVACComponent/ZoneHVACLowTempRadiantVarFlow.hpp"

using namespace openstudio;
using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_DefaultConstructor) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_FALSE(radiant.hydronicTubingLength());
  EXPECT_FALSE(radiant.heatingDesignCapacity());
  EXPECT_FALSE(radiant.maximumHotWaterFlow());
  EXPECT_FALSE(radiant.coolingDesignCapacity());
  EXPECT_FALSE(radiant.maximumColdWaterFlow());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_TRUE(radiant.setHydronicTubingLength(200.5));
  ASSERT_TRUE(radiant.hydronicTubingLength());
  EXPECT_DOUBLE_EQ(200.5, radiant.hydronicTubingLength().get());
  radiant.autosizeHydronicTubingLength();
  EXPECT_TRUE(radiant.isHydronicTubingLengthAutosized());

  EXPECT_TRUE(radiant.setHeatingDesignCapacity(1024.0));
  ASSERT_TRUE(radiant.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1024.0, radiant.heatingDesignCapacity().get());
  radiant.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(radiant.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(radiant.setMaximumHotWaterFlow(0.004));
  ASSERT_TRUE(radiant.maximumHotWaterFlow());
  EXPECT_DOUBLE_EQ(0.004, radiant.maximumHotWaterFlow().get());
  radiant.autosizeMaximumHotWaterFlow();
  EXPECT_TRUE(radiant.isMaximumHotWaterFlowAutosized());

  EXPECT_TRUE(radiant.setCoolingDesignCapacity(512.0));
  ASSERT_TRUE(radiant.coolingDesignCapacity());
  EXPECT_DOUBLE_EQ(512.0, radiant.coolingDesignCapacity().get());
  radiant.autosizeCoolingDesignCapacity();
  EXPECT_TRUE(radiant.isCoolingDesignCapacityAutosized());

  EXPECT_TRUE(radiant.setMaximumColdWaterFlow(0.003));
  ASSERT_TRUE(radiant.maximumColdWaterFlow());
  EXPECT_DOUBLE_EQ(0.003, radiant.maximumColdWaterFlow().get());
  radiant.autosizeMaximumColdWaterFlow();
  EXPECT_TRUE(radiant.isMaximumColdWaterFlowAutosized());

  EXPECT_TRUE(radiant.setNumberofCircuits("CalculateFromCircuitLength"));
  EXPECT_EQ("CalculateFromCircuitLength", radiant.numberofCircuits());
  radiant.resetNumberofCircuits();
  EXPECT_TRUE(radiant.isNumberofCircuitsDefaulted());

  EXPECT_TRUE(radiant.setCircuitLength(150.0));
  EXPECT_DOUBLE_EQ(150.0, radiant.circuitLength());
  radiant.resetCircuitLength();
  EXPECT_TRUE(radiant.isCircuitLengthDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACLowTempRadiantVarFlow_DesignScalars_RoundTrip) {
  Model model;
  ZoneHVACLowTempRadiantVarFlow radiant(model);

  EXPECT_TRUE(radiant.setFluidtoRadiantSurfaceHeatTransferModel("ISOStandard"));
  EXPECT_EQ("ISOStandard", radiant.fluidtoRadiantSurfaceHeatTransferModel());
  radiant.resetFluidtoRadiantSurfaceHeatTransferModel();
  EXPECT_TRUE(radiant.isFluidtoRadiantSurfaceHeatTransferModelDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingInsideDiameter(0.02));
  EXPECT_DOUBLE_EQ(0.02, radiant.hydronicTubingInsideDiameter());
  radiant.resetHydronicTubingInsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingInsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingOutsideDiameter(0.03));
  EXPECT_DOUBLE_EQ(0.03, radiant.hydronicTubingOutsideDiameter());
  radiant.resetHydronicTubingOutsideDiameter();
  EXPECT_TRUE(radiant.isHydronicTubingOutsideDiameterDefaulted());

  EXPECT_TRUE(radiant.setHydronicTubingConductivity(0.4));
  EXPECT_DOUBLE_EQ(0.4, radiant.hydronicTubingConductivity());
  radiant.resetHydronicTubingConductivity();
  EXPECT_TRUE(radiant.isHydronicTubingConductivityDefaulted());

  EXPECT_TRUE(radiant.setTemperatureControlType("SurfaceFaceTemperature"));
  EXPECT_EQ("SurfaceFaceTemperature", radiant.temperatureControlType());
  radiant.resetTemperatureControlType();
  EXPECT_TRUE(radiant.isTemperatureControlTypeDefaulted());

  EXPECT_TRUE(radiant.setSetpointControlType("ZeroFlowPower"));
  EXPECT_EQ("ZeroFlowPower", radiant.setpointControlType());
  radiant.resetSetpointControlType();
  EXPECT_TRUE(radiant.isSetpointControlTypeDefaulted());

  EXPECT_TRUE(radiant.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", radiant.heatingDesignCapacityMethod());
  radiant.resetHeatingDesignCapacityMethod();
  EXPECT_TRUE(radiant.isHeatingDesignCapacityMethodDefaulted());

  EXPECT_FALSE(radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_TRUE(radiant.setHeatingDesignCapacityPerFloorArea(42.5));
  ASSERT_TRUE(radiant.heatingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(42.5, radiant.heatingDesignCapacityPerFloorArea().get());
  radiant.resetHeatingDesignCapacityPerFloorArea();
  EXPECT_FALSE(radiant.heatingDesignCapacityPerFloorArea());

  EXPECT_DOUBLE_EQ(1.0, radiant.fractionofAutosizedHeatingDesignCapacity());
  EXPECT_TRUE(radiant.setFractionofAutosizedHeatingDesignCapacity(1.2));
  EXPECT_DOUBLE_EQ(1.2, radiant.fractionofAutosizedHeatingDesignCapacity());
  radiant.resetFractionofAutosizedHeatingDesignCapacity();
  EXPECT_DOUBLE_EQ(1.0, radiant.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_DOUBLE_EQ(0.5, radiant.heatingControlThrottlingRange());
  EXPECT_TRUE(radiant.setHeatingControlThrottlingRange(0.8));
  EXPECT_DOUBLE_EQ(0.8, radiant.heatingControlThrottlingRange());
  radiant.resetHeatingControlThrottlingRange();
  EXPECT_DOUBLE_EQ(0.5, radiant.heatingControlThrottlingRange());

  EXPECT_TRUE(radiant.setCoolingDesignCapacityMethod("FractionOfAutosizedCoolingCapacity"));
  EXPECT_EQ("FractionOfAutosizedCoolingCapacity", radiant.coolingDesignCapacityMethod());
  radiant.resetCoolingDesignCapacityMethod();
  EXPECT_TRUE(radiant.isCoolingDesignCapacityMethodDefaulted());

  EXPECT_FALSE(radiant.coolingDesignCapacityPerFloorArea());
  EXPECT_TRUE(radiant.setCoolingDesignCapacityPerFloorArea(27.0));
  ASSERT_TRUE(radiant.coolingDesignCapacityPerFloorArea());
  EXPECT_DOUBLE_EQ(27.0, radiant.coolingDesignCapacityPerFloorArea().get());
  radiant.resetCoolingDesignCapacityPerFloorArea();
  EXPECT_FALSE(radiant.coolingDesignCapacityPerFloorArea());

  EXPECT_FALSE(radiant.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_TRUE(radiant.setFractionofAutosizedCoolingDesignCapacity(0.8));
  ASSERT_TRUE(radiant.fractionofAutosizedCoolingDesignCapacity());
  EXPECT_DOUBLE_EQ(0.8, radiant.fractionofAutosizedCoolingDesignCapacity().get());
  radiant.resetFractionofAutosizedCoolingDesignCapacity();
  EXPECT_FALSE(radiant.fractionofAutosizedCoolingDesignCapacity());

  EXPECT_DOUBLE_EQ(0.5, radiant.coolingControlThrottlingRange());
  EXPECT_TRUE(radiant.setCoolingControlThrottlingRange(0.9));
  EXPECT_DOUBLE_EQ(0.9, radiant.coolingControlThrottlingRange());
  radiant.resetCoolingControlThrottlingRange();
  EXPECT_DOUBLE_EQ(0.5, radiant.coolingControlThrottlingRange());

  EXPECT_TRUE(radiant.setCondensationControlType("VariableOff"));
  EXPECT_EQ("VariableOff", radiant.condensationControlType());
  radiant.resetCondensationControlType();
  EXPECT_TRUE(radiant.isCondensationControlTypeDefaulted());

  EXPECT_DOUBLE_EQ(1.0, radiant.condensationControlDewpointOffset());
  EXPECT_TRUE(radiant.setCondensationControlDewpointOffset(2.5));
  EXPECT_DOUBLE_EQ(2.5, radiant.condensationControlDewpointOffset());
  radiant.resetCondensationControlDewpointOffset();
  EXPECT_DOUBLE_EQ(1.0, radiant.condensationControlDewpointOffset());
}
