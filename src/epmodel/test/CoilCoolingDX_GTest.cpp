/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDX.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/StraightComponent.hpp"
#include "../HVACComponent/ThermalZone.hpp"

#include <utilities/idd/Coil_Cooling_DX_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDX_DefaultConstructor) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_EQ(CoilCoolingDX::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_EQ(CoilCoolingDXCurveFitPerformance::iddObjectType(), coil.performanceObject().iddObject().type());

  const auto children = coil.children();
  ASSERT_EQ(1u, children.size());
  EXPECT_EQ(coil.performanceObject().handle(), children.front().handle());
  EXPECT_FALSE(coil.condenserZone());
}

TEST_F(EPModelFixture, CoilCoolingDX_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_TRUE(coil.setCondenserInletNodeName("DX Condenser Inlet"));
  EXPECT_TRUE(coil.setCondenserOutletNodeName("DX Condenser Outlet"));
  EXPECT_EQ("DX Condenser Inlet", coil.condenserInletNodeName());
  EXPECT_EQ("DX Condenser Outlet", coil.condenserOutletNodeName());
}

TEST_F(EPModelFixture, CoilCoolingDX_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDX coil(model);

  ScheduleConstant schedule(model);
  EXPECT_TRUE(schedule.setValue(0.25));
  EXPECT_TRUE(coil.setAvailabilitySchedule(schedule));
  EXPECT_EQ(schedule.handle(), coil.availabilitySchedule().handle());

  CoilCoolingDXCurveFitPerformance performance(model);
  EXPECT_TRUE(coil.setPerformanceObject(performance));
  EXPECT_EQ(performance.handle(), coil.performanceObject().handle());

  const auto performanceChildren = coil.children();
  ASSERT_EQ(1u, performanceChildren.size());
  EXPECT_EQ(performance.handle(), performanceChildren.front().handle());

  ThermalZone zone(model);
  EXPECT_FALSE(coil.condenserZone());
  EXPECT_TRUE(coil.setCondenserZone(zone));
  ASSERT_TRUE(coil.condenserZone());
  EXPECT_EQ(zone.handle(), coil.condenserZone()->handle());
  coil.resetCondenserZone();
  EXPECT_FALSE(coil.condenserZone());
}

TEST_F(EPModelFixture, CoilCoolingDX_StraightComponentPortsWithoutLoopPlacement) {
  Model model;
  CoilCoolingDX coil(model);

  EXPECT_TRUE(coil.optionalCast<StraightComponent>());
  EXPECT_EQ(openstudio::Coil_Cooling_DXFields::EvaporatorInletNodeName, coil.inletPort());
  EXPECT_EQ(openstudio::Coil_Cooling_DXFields::EvaporatorOutletNodeName, coil.outletPort());
}

TEST_F(EPModelFixture, CoilCoolingDX_AddToNodeSupplyOnly) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDX supplyCoil(model);
  CoilCoolingDX demandCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());
}
