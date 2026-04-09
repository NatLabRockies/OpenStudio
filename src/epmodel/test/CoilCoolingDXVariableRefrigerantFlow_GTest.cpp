/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../StraightComponent/CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"

#include <utilities/idd/Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_DefaultConstructor) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);
  EXPECT_EQ(CoilCoolingDXVariableRefrigerantFlow::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);

  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12345.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12345.0, coil.ratedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());
  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.71));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.71, coil.ratedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedSensibleHeatRatioAutosized());
  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedAirFlowRate(1.35));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.35, coil.ratedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());
  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilCoolingDXVariableRefrigerantFlow_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilCoolingDXVariableRefrigerantFlow coil(model);
  Node node(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirInletNode, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_DX_VariableRefrigerantFlowFields::CoilAirOutletNode, coil.outletPort());
  EXPECT_FALSE(coil.addToNode(node));
}
