/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../CoilSystemCoolingWaterHeatExchangerAssisted.hpp"
#include "../CoilSystemCoolingWaterHeatExchangerAssisted_Impl.hpp"
#include "../CoilCoolingWater.hpp"
#include "../CoilCoolingWater_Impl.hpp"
#include "../HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../HeatExchangerAirToAirSensibleAndLatent_Impl.hpp"
#include "../HeatExchangerDesiccantBalancedFlow.hpp"
#include "../HeatExchangerDesiccantBalancedFlow_Impl.hpp"
#include "../AirLoopHVAC.hpp"
#include "../PlantLoop.hpp"
#include "../Node.hpp"
#include "../AirLoopHVACUnitarySystem.hpp"
#include "../ZoneHVACUnitVentilator.hpp"
#include "../ZoneHVACFourPipeFanCoil.hpp"
#include "../FanConstantVolume.hpp"
#include "../CoilHeatingWater.hpp"
#include "../Schedule.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
    {
      Model m;
      CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);

      exit(0);
    },
    ::testing::ExitedWithCode(0), "");
}

// This test ensures that only the parent CoilSystem can call addToNode, the individual CoilCoolingWater and HX cannot
TEST_F(ModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_addToNode) {

  Model m;
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);

  AirLoopHVAC a(m);
  Node n = a.supplyOutletNode();

  auto cc = coilSystem.coolingCoil().cast<CoilCoolingWater>();
  auto hx = coilSystem.heatExchanger().cast<HeatExchangerAirToAirSensibleAndLatent>();

  EXPECT_EQ(2u, a.supplyComponents().size());

  EXPECT_FALSE(cc.addToNode(n));
  EXPECT_EQ(2u, a.supplyComponents().size());

  EXPECT_FALSE(hx.addToNode(n));
  EXPECT_EQ(2u, a.supplyComponents().size());

  EXPECT_TRUE(coilSystem.addToNode(n));
  EXPECT_EQ(3u, a.supplyComponents().size());

  {
    auto containingHVACComponent = cc.containingHVACComponent();
    ASSERT_TRUE(containingHVACComponent);
    EXPECT_EQ(containingHVACComponent->handle(), coilSystem.handle());
  }

  {
    auto containingHVACComponent = hx.containingHVACComponent();
    ASSERT_TRUE(containingHVACComponent);
    EXPECT_EQ(containingHVACComponent->handle(), coilSystem.handle());
  }

  // BUT, we need to be able to connect the water side of the Coil...
  PlantLoop p(m);
  EXPECT_TRUE(p.addDemandBranchForComponent(cc));
}

TEST_F(ModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_correctHXs) {

  Model m;
  HeatExchangerAirToAirSensibleAndLatent hxAirToAir(m);
  EXPECT_NO_THROW(CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m, hxAirToAir));
  HeatExchangerDesiccantBalancedFlow hxDesiccant(m);
  EXPECT_ANY_THROW(CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m, hxDesiccant));
}

TEST_F(ModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_clone) {

  Model m;

  // Create a CoilSystem, connected to an AirLoopHVAC, and with its coolingCoil connected to a PlantLoop
  CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);
  auto cc = coilSystem.coolingCoil().cast<CoilCoolingWater>();
  auto hx = coilSystem.heatExchanger().cast<HeatExchangerAirToAirSensibleAndLatent>();

  AirLoopHVAC a(m);
  EXPECT_EQ(2, a.supplyComponents().size());  // o --- o
  Node n = a.supplyOutletNode();
  EXPECT_TRUE(coilSystem.addToNode(n));
  EXPECT_EQ(3, a.supplyComponents().size());  // o --- oa_sys --- o

  PlantLoop p(m);
  EXPECT_EQ(5, p.demandComponents().size());  // o --- Splitter --- o --- Mixer --- o

  EXPECT_TRUE(p.addDemandBranchForComponent(cc));
  EXPECT_EQ(7, p.demandComponents().size());  // o --- Splitter --- o --- coolingCoil --- Mixer --- o

  EXPECT_EQ(1u, m.getConcreteModelObjects<CoilSystemCoolingWaterHeatExchangerAssisted>().size());
  EXPECT_EQ(1u, m.getConcreteModelObjects<CoilCoolingWater>().size());
  EXPECT_EQ(1u, m.getConcreteModelObjects<HeatExchangerAirToAirSensibleAndLatent>().size());

  ASSERT_TRUE(coilSystem.airLoopHVAC());
  EXPECT_EQ(coilSystem.airLoopHVAC()->handle(), a.handle());

  EXPECT_TRUE(cc.plantLoop());

  // TODO: should these work?
  //ASSERT_TRUE(coilSystem.plantLoop());
  //EXPECT_EQ(coilSystem.plantLoop()->handle(), p.handle());
  //EXPECT_TRUE(hx.airLoopHVAC());

  auto coilSystemClone = coilSystem.clone(m).cast<CoilSystemCoolingWaterHeatExchangerAssisted>();

  EXPECT_EQ(2u, m.getConcreteModelObjects<CoilSystemCoolingWaterHeatExchangerAssisted>().size());
  EXPECT_EQ(2u, m.getConcreteModelObjects<CoilCoolingWater>().size());
  EXPECT_EQ(2u, m.getConcreteModelObjects<HeatExchangerAirToAirSensibleAndLatent>().size());

  EXPECT_TRUE(coilSystem.airLoopHVAC());
  EXPECT_TRUE(coilSystem.inletModelObject());
  EXPECT_TRUE(coilSystem.outletModelObject());

  EXPECT_FALSE(coilSystemClone.airLoopHVAC());
  EXPECT_FALSE(coilSystemClone.inletModelObject());
  EXPECT_FALSE(coilSystemClone.outletModelObject());

  EXPECT_NE(coilSystemClone.coolingCoil().handle(), cc.handle());
  EXPECT_NE(coilSystemClone.heatExchanger().handle(), hx.handle());

  coilSystemClone.remove();
  EXPECT_EQ(1, m.getConcreteModelObjects<CoilSystemCoolingWaterHeatExchangerAssisted>().size());
  EXPECT_EQ(1, m.getConcreteModelObjects<CoilCoolingWater>().size());

  coilSystem.remove();
  EXPECT_EQ(0, m.getConcreteModelObjects<CoilSystemCoolingWaterHeatExchangerAssisted>().size());
  EXPECT_EQ(0, m.getConcreteModelObjects<CoilCoolingWater>().size());

  EXPECT_EQ(2, a.supplyComponents().size());  // o --- o
  EXPECT_EQ(5, p.demandComponents().size());  // o --- Splitter --- o --- Mixer --- o
}

TEST_F(ModelFixture, CoilSystemCoolingWaterHeatExchangerAssisted_containingComponent) {

  Model m;

  {
    AirLoopHVACUnitarySystem unitary(m);
    CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);

    EXPECT_TRUE(unitary.setCoolingCoil(coilSystem));
    boost::optional<HVACComponent> _c = coilSystem.containingHVACComponent();
    ASSERT_TRUE(_c);
    EXPECT_EQ(_c->handle(), unitary.handle());
  }

  {
    ZoneHVACUnitVentilator uv(m);

    CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);
    EXPECT_TRUE(uv.setCoolingCoil(coilSystem));
    boost::optional<ZoneHVACComponent> _c = coilSystem.containingZoneHVACComponent();
    ASSERT_TRUE(_c);
    EXPECT_EQ(_c->handle(), uv.handle());
  }

  {
    Schedule s = m.alwaysOnDiscreteSchedule();
    FanConstantVolume supplyFan(m);
    CoilCoolingWater coolingCoil(m);
    CoilHeatingWater heatingCoil(m);

    ZoneHVACFourPipeFanCoil fc(m, s, supplyFan, coolingCoil, heatingCoil);

    CoilSystemCoolingWaterHeatExchangerAssisted coilSystem(m);
    EXPECT_TRUE(fc.setCoolingCoil(coilSystem));
    boost::optional<ZoneHVACComponent> _c = coilSystem.containingZoneHVACComponent();
    ASSERT_TRUE(_c);
    EXPECT_EQ(_c->handle(), fc.handle());
  }
}
