/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted.hpp"
#include "../StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_DefaultConstructor) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model);
  EXPECT_EQ(CoilSystemCoolingDXHeatExchangerAssisted::iddObjectType(), coilSystem.iddObject().type());
  EXPECT_FALSE(coilSystem.nameString().empty());

  auto heatExchanger = coilSystem.heatExchanger();
  auto coolingCoil = coilSystem.coolingCoil();

  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent", heatExchanger.iddObject().name());
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", coolingCoil.iddObject().name());
  EXPECT_EQ(heatExchanger.iddObject().name(), coilSystem.heatExchangerObjectType());
  EXPECT_EQ(coolingCoil.iddObject().name(), coilSystem.coolingCoilObjectType());

  const auto children = coilSystem.children();
  EXPECT_EQ(2u, children.size());
  EXPECT_TRUE(std::any_of(children.begin(), children.end(), [&](const auto& object) { return object.handle() == coolingCoil.handle(); }));
  EXPECT_TRUE(std::any_of(children.begin(), children.end(), [&](const auto& object) { return object.handle() == heatExchanger.handle(); }));
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model);

  const auto heatExchangerObjectTypes = CoilSystemCoolingDXHeatExchangerAssisted::heatExchangerObjectTypeValues();
  EXPECT_FALSE(heatExchangerObjectTypes.empty());
  EXPECT_TRUE(std::find(heatExchangerObjectTypes.begin(), heatExchangerObjectTypes.end(), "HeatExchanger:AirToAir:SensibleAndLatent") !=
              heatExchangerObjectTypes.end());

  const auto coolingCoilObjectTypes = CoilSystemCoolingDXHeatExchangerAssisted::coolingCoilObjectTypeValues();
  EXPECT_FALSE(coolingCoilObjectTypes.empty());
  EXPECT_TRUE(std::find(coolingCoilObjectTypes.begin(), coolingCoilObjectTypes.end(), "Coil:Cooling:DX:SingleSpeed") !=
              coolingCoilObjectTypes.end());

  EXPECT_TRUE(coilSystem.setHeatExchangerObjectType("HeatExchanger:AirToAir:SensibleAndLatent"));
  EXPECT_EQ("HeatExchanger:AirToAir:SensibleAndLatent", coilSystem.heatExchangerObjectType());

  EXPECT_TRUE(coilSystem.setCoolingCoilObjectType("Coil:Cooling:DX:SingleSpeed"));
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", coilSystem.coolingCoilObjectType());

  EXPECT_FALSE(coilSystem.setCoolingCoilObjectType("Invalid Coil Type"));
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_RelationshipAccessors_RoundTrip) {
  Model model;
  HeatExchangerDesiccantBalancedFlow heatExchanger(model);
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model, heatExchanger);
  CoilCoolingDXVariableSpeed coolingCoil(model);

  EXPECT_EQ(heatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_EQ(heatExchanger.iddObject().name(), coilSystem.heatExchangerObjectType());
  EXPECT_EQ("Coil:Cooling:DX:SingleSpeed", coilSystem.coolingCoil().iddObject().name());

  EXPECT_TRUE(coilSystem.setCoolingCoil(coolingCoil));
  EXPECT_EQ(coolingCoil.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(coolingCoil.iddObject().name(), coilSystem.coolingCoilObjectType());

  HeatExchangerAirToAirSensibleAndLatent replacementHeatExchanger(model);
  EXPECT_TRUE(coilSystem.setHeatExchanger(replacementHeatExchanger));
  EXPECT_EQ(replacementHeatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_EQ(replacementHeatExchanger.iddObject().name(), coilSystem.heatExchangerObjectType());
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_AddToNodeRejected) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model);
  AirLoopHVAC airLoop(model);
  auto supplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(coilSystem.addToNode(supplyOutletNode));
  EXPECT_FALSE(coilSystem.airLoopHVAC());
  EXPECT_FALSE(coilSystem.inletModelObject());
  EXPECT_FALSE(coilSystem.outletModelObject());
}
