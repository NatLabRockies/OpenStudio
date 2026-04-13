/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingWaterBaseboard.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACBaseboardConvectiveWater.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_DefaultConstructor) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil().cast<CoilHeatingWaterBaseboard>();

  auto alwaysOn = baseboard.availabilitySchedule().cast<ScheduleConstant>();
  EXPECT_DOUBLE_EQ(1.0, alwaysOn.value());
  EXPECT_EQ("HeatingDesignCapacity", heatingCoil.heatingDesignCapacityMethod());
  EXPECT_TRUE(heatingCoil.isHeatingDesignCapacityAutosized());
  EXPECT_TRUE(heatingCoil.isConvergenceToleranceDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("HeatingDesignCapacity"));
  EXPECT_EQ("HeatingDesignCapacity", baseboard.heatingDesignCapacityMethod());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacity(1500.0));
  ASSERT_TRUE(baseboard.heatingDesignCapacity());
  EXPECT_DOUBLE_EQ(1500.0, baseboard.heatingDesignCapacity().get());
  baseboard.autosizeHeatingDesignCapacity();
  EXPECT_TRUE(baseboard.isHeatingDesignCapacityAutosized());

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityPerFloorArea(0.6));
  EXPECT_DOUBLE_EQ(0.6, baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(baseboard.setFractionofAutosizedHeatingDesignCapacity(0.4));
  EXPECT_DOUBLE_EQ(0.4, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(baseboard.setUFactorTimesAreaValue(2.1));
  ASSERT_TRUE(baseboard.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2.1, baseboard.uFactorTimesAreaValue().get());
  baseboard.resetUFactorTimesAreaValue();
  EXPECT_TRUE(baseboard.isUFactorTimesAreaValueDefaulted());
  EXPECT_FALSE(baseboard.uFactorTimesAreaValue());

  EXPECT_TRUE(baseboard.setMaximumWaterFlowRate(0.012));
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, baseboard.maximumWaterFlowRate().get());
  baseboard.resetMaximumWaterFlowRate();
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateDefaulted());
  EXPECT_FALSE(baseboard.maximumWaterFlowRate());
  baseboard.autosizeMaximumWaterFlowRate();
  EXPECT_TRUE(baseboard.isMaximumWaterFlowRateAutosized());

  EXPECT_TRUE(baseboard.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, baseboard.convergenceTolerance());
  baseboard.resetConvergenceTolerance();
  EXPECT_TRUE(baseboard.isConvergenceToleranceDefaulted());
  EXPECT_DOUBLE_EQ(0.001, baseboard.convergenceTolerance());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_CanonicalParentSurface_RoundTrip) {
  Model model;
  ScheduleConstant availability(model);
  ZoneHVACBaseboardConvectiveWater source(model);
  auto heatingCoil = source.heatingCoil().cast<CoilHeatingWaterBaseboard>();
  ASSERT_TRUE(heatingCoil.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));

  ZoneHVACBaseboardConvectiveWater baseboard(model, availability, heatingCoil);

  EXPECT_EQ(availability.handle(), baseboard.availabilitySchedule().handle());
  ASSERT_EQ(1u, baseboard.children().size());
  EXPECT_EQ(baseboard.heatingCoil().handle(), baseboard.children().at(0).handle());

  ScheduleConstant replacementAvailability(model);
  EXPECT_TRUE(baseboard.setAvailabilitySchedule(replacementAvailability));
  EXPECT_EQ(replacementAvailability.handle(), baseboard.availabilitySchedule().handle());

  EXPECT_EQ("CapacityPerFloorArea", baseboard.heatingDesignCapacityMethod());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_ParentAndTransientChildStayAligned) {
  Model model;
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil().cast<CoilHeatingWaterBaseboard>();

  EXPECT_TRUE(baseboard.setHeatingDesignCapacityMethod("CapacityPerFloorArea"));
  EXPECT_EQ("CapacityPerFloorArea", heatingCoil.heatingDesignCapacityMethod());

  EXPECT_TRUE(heatingCoil.setHeatingDesignCapacityPerFloorArea(0.6));
  EXPECT_DOUBLE_EQ(0.6, baseboard.heatingDesignCapacityPerFloorArea());

  EXPECT_TRUE(heatingCoil.setFractionofAutosizedHeatingDesignCapacity(0.75));
  EXPECT_DOUBLE_EQ(0.75, baseboard.fractionofAutosizedHeatingDesignCapacity());

  EXPECT_TRUE(baseboard.setUFactorTimesAreaValue(2.1));
  ASSERT_TRUE(heatingCoil.uFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(2.1, *heatingCoil.uFactorTimesAreaValue());

  EXPECT_TRUE(heatingCoil.setMaximumWaterFlowRate(0.012));
  ASSERT_TRUE(baseboard.maximumWaterFlowRate());
  EXPECT_DOUBLE_EQ(0.012, *baseboard.maximumWaterFlowRate());

  EXPECT_TRUE(heatingCoil.setConvergenceTolerance(0.002));
  EXPECT_DOUBLE_EQ(0.002, baseboard.convergenceTolerance());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACBaseboardConvectiveWater baseboard(model);

  EXPECT_FALSE(baseboard.thermalZone());
  EXPECT_TRUE(baseboard.addToThermalZone(zone));
  ASSERT_TRUE(baseboard.thermalZone());
  EXPECT_EQ(zone, *baseboard.thermalZone());

  baseboard.removeFromThermalZone();
  EXPECT_FALSE(baseboard.thermalZone());
}

TEST_F(EPModelFixture, ZoneHVACBaseboardConvectiveWater_TransientHeatingCoilProjectsThroughPlantLoop) {
  Model model;
  PlantLoop plantLoop(model);
  ZoneHVACBaseboardConvectiveWater baseboard(model);
  auto heatingCoil = baseboard.heatingCoil().cast<CoilHeatingWaterBaseboard>();

  ASSERT_TRUE(plantLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(heatingCoil.inletModelObject());
  ASSERT_TRUE(heatingCoil.outletModelObject());

  const auto demandComponents = plantLoop.demandComponents();
  EXPECT_TRUE(std::any_of(demandComponents.begin(), demandComponents.end(),
                          [&](const auto& object) { return object.handle() == heatingCoil.handle(); }));
  EXPECT_FALSE(std::any_of(demandComponents.begin(), demandComponents.end(),
                           [&](const auto& object) { return object.handle() == baseboard.handle(); }));
}
