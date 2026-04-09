/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControl_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_DefaultConstructor) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  EXPECT_EQ(CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);

  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalHeatingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());
  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setIndoorUnitReferenceSubcooling(7.5));
  EXPECT_DOUBLE_EQ(7.5, coil.indoorUnitReferenceSubcooling());
}

TEST_F(EPModelFixture, CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilHeatingDXVariableRefrigerantFlowFluidTemperatureControl coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Heating_DX_VariableRefrigerantFlow_FluidTemperatureControlFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
