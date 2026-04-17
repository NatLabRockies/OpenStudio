/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveQuadraticLinear.hpp"
#include "../Curve/CurveQuadraticLinear_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/ThermalStorageIceDetailed.hpp"
#include "../StraightComponent/Node.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ThermalStorageIceDetailed_DefaultConstructor) {
  Model model;
  ThermalStorageIceDetailed storage(model);
  EXPECT_FALSE(ThermalStorageIceDetailed::iddObjectType().valueName().empty());
  EXPECT_FALSE(storage.availabilitySchedule());

  ASSERT_FALSE(storage.children().empty());
  ASSERT_EQ(2u, storage.children().size());
  ASSERT_TRUE(storage.children()[0].optionalCast<CurveQuadraticLinear>());
  ASSERT_TRUE(storage.children()[1].optionalCast<CurveQuadraticLinear>());
  EXPECT_DOUBLE_EQ(0.5, storage.capacity());
  EXPECT_EQ("FractionDischargedLMTD", storage.dischargingCurveVariableSpecifications());
  EXPECT_EQ("FractionChargedLMTD", storage.chargingCurveVariableSpecifications());
  EXPECT_DOUBLE_EQ(1.0, storage.timestepoftheCurveData().get());
  EXPECT_DOUBLE_EQ(0.0001, storage.parasiticElectricLoadDuringDischarging().get());
  EXPECT_DOUBLE_EQ(0.0002, storage.parasiticElectricLoadDuringCharging().get());
  EXPECT_DOUBLE_EQ(0.0003, storage.tankLossCoefficient().get());
  EXPECT_DOUBLE_EQ(0.0, storage.freezingTemperatureofStorageMedium());
  EXPECT_FALSE(storage.isFreezingTemperatureofStorageMediumDefaulted());
  EXPECT_EQ("OutsideMelt", storage.thawProcessIndicator());
  EXPECT_FALSE(storage.isThawProcessIndicatorDefaulted());
}

TEST_F(EPModelFixture, ThermalStorageIceDetailed_ScalarAccessors_RoundTrip) {
  Model model;
  ThermalStorageIceDetailed storage(model);
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  CurveQuadraticLinear dischargingCurve(model);
  CurveQuadraticLinear chargingCurve(model);

  EXPECT_TRUE(storage.setAvailabilitySchedule(availability));
  ASSERT_TRUE(storage.availabilitySchedule());
  EXPECT_EQ(availability.handle(), storage.availabilitySchedule()->handle());

  EXPECT_TRUE(storage.setDischargingCurve(dischargingCurve));
  EXPECT_EQ(dischargingCurve.handle(), storage.dischargingCurve().handle());

  EXPECT_TRUE(storage.setChargingCurve(chargingCurve));
  EXPECT_EQ(chargingCurve.handle(), storage.chargingCurve().handle());

  EXPECT_TRUE(storage.setCapacity(2.2));
  EXPECT_DOUBLE_EQ(2.2, storage.capacity());
  EXPECT_FALSE(storage.isCapacityAutosized());
  storage.autosizeCapacity();
  EXPECT_TRUE(storage.isCapacityAutosized());

  auto dischargingValues = ThermalStorageIceDetailed::dischargingCurveVariableSpecificationsValues();
  ASSERT_FALSE(dischargingValues.empty());
  const auto& dischargingValue = dischargingValues.front();
  EXPECT_TRUE(storage.setDischargingCurveVariableSpecifications(dischargingValue));
  EXPECT_EQ(dischargingValue, storage.dischargingCurveVariableSpecifications());

  auto chargingValues = ThermalStorageIceDetailed::chargingCurveVariableSpecificationsValues();
  ASSERT_FALSE(chargingValues.empty());
  const auto& chargingValue = chargingValues.front();
  EXPECT_TRUE(storage.setChargingCurveVariableSpecifications(chargingValue));
  EXPECT_EQ(chargingValue, storage.chargingCurveVariableSpecifications());

  EXPECT_TRUE(storage.setTimestepoftheCurveData(1.25));
  ASSERT_TRUE(storage.timestepoftheCurveData());
  EXPECT_DOUBLE_EQ(1.25, storage.timestepoftheCurveData().get());
  storage.resetTimestepoftheCurveData();
  EXPECT_FALSE(storage.timestepoftheCurveData());

  EXPECT_TRUE(storage.setParasiticElectricLoadDuringDischarging(0.12));
  ASSERT_TRUE(storage.parasiticElectricLoadDuringDischarging());
  EXPECT_DOUBLE_EQ(0.12, storage.parasiticElectricLoadDuringDischarging().get());
  storage.resetParasiticElectricLoadDuringDischarging();
  EXPECT_FALSE(storage.parasiticElectricLoadDuringDischarging());

  EXPECT_TRUE(storage.setParasiticElectricLoadDuringCharging(0.05));
  ASSERT_TRUE(storage.parasiticElectricLoadDuringCharging());
  EXPECT_DOUBLE_EQ(0.05, storage.parasiticElectricLoadDuringCharging().get());
  storage.resetParasiticElectricLoadDuringCharging();
  EXPECT_FALSE(storage.parasiticElectricLoadDuringCharging());

  EXPECT_TRUE(storage.setTankLossCoefficient(0.02));
  ASSERT_TRUE(storage.tankLossCoefficient());
  EXPECT_DOUBLE_EQ(0.02, storage.tankLossCoefficient().get());
  storage.resetTankLossCoefficient();
  EXPECT_FALSE(storage.tankLossCoefficient());

  EXPECT_TRUE(storage.setFreezingTemperatureofStorageMedium(-3.0));
  EXPECT_DOUBLE_EQ(-3.0, storage.freezingTemperatureofStorageMedium());
  storage.resetFreezingTemperatureofStorageMedium();
  EXPECT_TRUE(storage.isFreezingTemperatureofStorageMediumDefaulted());

  auto thawValues = ThermalStorageIceDetailed::thawProcessIndicatorValues();
  ASSERT_FALSE(thawValues.empty());
  const auto& thawValue = thawValues.front();
  EXPECT_TRUE(storage.setThawProcessIndicator(thawValue));
  EXPECT_EQ(thawValue, storage.thawProcessIndicator());
  storage.resetThawProcessIndicator();
  EXPECT_TRUE(storage.isThawProcessIndicatorDefaulted());

  storage.resetAvailabilitySchedule();
  EXPECT_FALSE(storage.availabilitySchedule());
  const auto children = storage.children();
  ASSERT_EQ(2u, children.size());
  EXPECT_EQ(dischargingCurve.handle(), children[0].handle());
  EXPECT_EQ(chargingCurve.handle(), children[1].handle());
}

TEST_F(EPModelFixture, ThermalStorageIceDetailed_AddToNodePlantDemandOnly) {
  Model model;
  PlantLoop plantLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  ThermalStorageIceDetailed demandStorage(model);
  ThermalStorageIceDetailed supplyStorage(model);
  ThermalStorageIceDetailed oaStorage(model);
  ThermalStorageIceDetailed orphanStorage(model);

  auto demandInletNode = plantLoop.demandInletNode();
  EXPECT_TRUE(demandStorage.addToNode(demandInletNode));
  ASSERT_TRUE(demandStorage.plantLoop());
  EXPECT_EQ(plantLoop.handle(), demandStorage.plantLoop()->handle());
  ASSERT_TRUE(demandStorage.inletModelObject());
  EXPECT_EQ(demandInletNode, demandStorage.inletModelObject()->cast<Node>());
  EXPECT_TRUE(demandStorage.outletModelObject());

  auto supplyInletNode = plantLoop.supplyInletNode();
  EXPECT_FALSE(supplyStorage.addToNode(supplyInletNode));
  EXPECT_FALSE(supplyStorage.inletModelObject());
  EXPECT_FALSE(supplyStorage.outletModelObject());
  EXPECT_FALSE(supplyStorage.plantLoop());

  ASSERT_TRUE(oaSystem.outboardOANode());
  auto oaNode = oaSystem.outboardOANode();
  EXPECT_FALSE(oaStorage.addToNode(*oaNode));
  EXPECT_FALSE(oaStorage.inletModelObject());
  EXPECT_FALSE(oaStorage.outletModelObject());
  EXPECT_FALSE(oaStorage.plantLoop());

  Node orphanNode(model);
  EXPECT_FALSE(orphanStorage.addToNode(orphanNode));
  EXPECT_FALSE(orphanStorage.inletModelObject());
  EXPECT_FALSE(orphanStorage.outletModelObject());
  EXPECT_FALSE(orphanStorage.plantLoop());
}
