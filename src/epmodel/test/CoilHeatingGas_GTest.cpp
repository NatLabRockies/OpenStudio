/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveQuadratic.hpp"
#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/CoilHeatingGas.hpp"
#include "../StraightComponent/Node.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilHeatingGas_DefaultConstructor) {
  Model model;
  CoilHeatingGas coil(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Coil_Heating_Fuel), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
}

TEST_F(EPModelFixture, CoilHeatingGas_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);

  EXPECT_FALSE(CoilHeatingGas::validFuelTypeValues().empty());
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setFuelType("Propane"));
  EXPECT_EQ("Propane", coil.fuelType());
  coil.resetFuelType();
  EXPECT_EQ("NaturalGas", coil.fuelType());

  EXPECT_TRUE(coil.setGasBurnerEfficiency(0.81));
  EXPECT_DOUBLE_EQ(0.81, coil.gasBurnerEfficiency());

  EXPECT_TRUE(coil.setOnCycleParasiticElectricLoad(10.5));
  EXPECT_DOUBLE_EQ(10.5, coil.onCycleParasiticElectricLoad());
  EXPECT_DOUBLE_EQ(10.5, coil.parasiticElectricLoad());
  EXPECT_TRUE(coil.setParasiticElectricLoad(11.5));
  EXPECT_DOUBLE_EQ(11.5, coil.onCycleParasiticElectricLoad());

  EXPECT_TRUE(coil.setOffCycleParasiticGasLoad(2.25));
  EXPECT_DOUBLE_EQ(2.25, coil.offCycleParasiticGasLoad());
  EXPECT_DOUBLE_EQ(2.25, coil.parasiticGasLoad());
  EXPECT_TRUE(coil.setParasiticGasLoad(3.25));
  EXPECT_DOUBLE_EQ(3.25, coil.offCycleParasiticGasLoad());

  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.nominalCapacity());
  EXPECT_TRUE(coil.setNominalCapacity(1200.0));
  ASSERT_TRUE(coil.nominalCapacity());
  EXPECT_DOUBLE_EQ(1200.0, coil.nominalCapacity().get());
  EXPECT_FALSE(coil.isNominalCapacityAutosized());
  coil.resetNominalCapacity();
  EXPECT_FALSE(coil.nominalCapacity());
  coil.autosizeNominalCapacity();
  EXPECT_TRUE(coil.isNominalCapacityAutosized());
  EXPECT_FALSE(coil.autosizedNominalCapacity());
}

TEST_F(EPModelFixture, CoilHeatingGas_RelationshipSetters_RoundTrip) {
  Model model;
  CoilHeatingGas coil(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.4));
  CurveQuadratic plf(model);
  ASSERT_TRUE(plf.setCoefficient1Constant(0.8));
  ASSERT_TRUE(plf.setCoefficient2x(0.2));
  ASSERT_TRUE(plf.setCoefficient3xPOW2(0.0));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve()->handle());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(plf.handle(), children[0].handle());

  coil.resetPartLoadFractionCorrelationCurve();
  EXPECT_FALSE(coil.partLoadFractionCorrelationCurve());
  EXPECT_TRUE(coil.children().empty());
}

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeRejectsAirLoopDemandNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingGas coil(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto demandBranchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(demandBranchNode);

  ThermalZone zone(model);
  ASSERT_TRUE(zone.addToNode(*demandBranchNode));
  EXPECT_FALSE(coil.addToNode(*demandBranchNode));
}

TEST_F(EPModelFixture, CoilHeatingGas_AddToNodeSupportsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilHeatingGas coil(model);
  EXPECT_TRUE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(3u, oaSystem.oaComponents().size());
}
