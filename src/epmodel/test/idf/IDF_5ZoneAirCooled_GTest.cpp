/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../EPModelFixture.hpp"

#include "../../Loop/PlantLoop_Impl.hpp"
#include "../../Loop/PlantLoop.hpp"
#include "../../Mixer/Mixer.hpp"
#include "../../StraightComponent/BoilerHotWater.hpp"
#include "../../StraightComponent/BoilerHotWater_Impl.hpp"
#include "../../StraightComponent/Node.hpp"
#include "../../StraightComponent/PipeAdiabatic.hpp"
#include "../../StraightComponent/PipeAdiabatic_Impl.hpp"
#include "../../StraightComponent/PumpVariableSpeed.hpp"
#include "../../StraightComponent/PumpVariableSpeed_Impl.hpp"
#include "../../Splitter/Splitter.hpp"
#include "../../WaterToAirComponent/CoilCoolingWater.hpp"
#include "../../WaterToAirComponent/CoilCoolingWater_Impl.hpp"
#include "../../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../../WaterToAirComponent/CoilHeatingWater_Impl.hpp"
#include "../../WaterToWaterComponent/ChillerElectric.hpp"
#include "../../WaterToWaterComponent/ChillerElectric_Impl.hpp"

#include <algorithm>
#include <resources.hxx>

using namespace openstudio::epmodel;

class FiveZoneAirCooledIDFFixture : public EPModelFixture
{
 protected:
  static openstudio::path fiveZoneAirCooledIdfPath() {
    return resourcesPath() / openstudio::toPath("energyplus/5ZoneAirCooled/in.idf");
  }

  static boost::optional<Model> loadFiveZoneAirCooledModel() {
    return Model::load(fiveZoneAirCooledIdfPath());
  }
};

TEST_F(FiveZoneAirCooledIDFFixture, PlantLoop_IDF_LoopsLoadAndExposeTopologyApis) {
  auto model = loadFiveZoneAirCooledModel();
  ASSERT_TRUE(model);

  auto plantLoops = model->getConcreteModelObjects<PlantLoop>();
  ASSERT_EQ(2u, plantLoops.size());

  auto hotWaterLoopIt = std::find_if(plantLoops.begin(), plantLoops.end(),
                                     [](const PlantLoop& plantLoop) { return plantLoop.nameString() == "Hot Water Loop"; });
  auto chilledWaterLoopIt = std::find_if(plantLoops.begin(), plantLoops.end(),
                                         [](const PlantLoop& plantLoop) { return plantLoop.nameString() == "Chilled Water Loop"; });
  ASSERT_NE(plantLoops.end(), hotWaterLoopIt);
  ASSERT_NE(plantLoops.end(), chilledWaterLoopIt);

  for (auto& plantLoop : plantLoops) {
    auto supplyInletNode = plantLoop.supplyInletNode();
    auto supplyOutletNode = plantLoop.supplyOutletNode();
    auto demandInletNode = plantLoop.demandInletNode();
    auto demandOutletNode = plantLoop.demandOutletNode();

    EXPECT_FALSE(supplyInletNode.nameString().empty());
    EXPECT_FALSE(supplyOutletNode.nameString().empty());
    EXPECT_FALSE(demandInletNode.nameString().empty());
    EXPECT_FALSE(demandOutletNode.nameString().empty());

    auto supplySplitter = plantLoop.supplySplitter();
    auto supplyMixer = plantLoop.supplyMixer();
    auto demandSplitter = plantLoop.demandSplitter();
    auto demandMixer = plantLoop.demandMixer();

    auto splitterInlet = supplySplitter.inletModelObject();
    ASSERT_TRUE(splitterInlet);
    const bool splitterInletIsNode = static_cast<bool>(splitterInlet->optionalCast<Node>());
    EXPECT_TRUE(splitterInletIsNode);

    const auto splitterOutlets = supplySplitter.outletModelObjects();
    ASSERT_FALSE(splitterOutlets.empty());
    EXPECT_TRUE(std::ranges::all_of(splitterOutlets, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); }));

    auto mixerOutlet = supplyMixer.outletModelObject();
    ASSERT_TRUE(mixerOutlet);
    const bool mixerOutletIsNode = static_cast<bool>(mixerOutlet->optionalCast<Node>());
    EXPECT_TRUE(mixerOutletIsNode);

    const auto mixerInlets = supplyMixer.inletModelObjects();
    ASSERT_FALSE(mixerInlets.empty());
    EXPECT_EQ(splitterOutlets.size(), mixerInlets.size());
    EXPECT_TRUE(std::ranges::all_of(mixerInlets, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); }));

    auto demandSplitterInlet = demandSplitter.inletModelObject();
    ASSERT_TRUE(demandSplitterInlet);
    const bool demandSplitterInletIsNode = static_cast<bool>(demandSplitterInlet->optionalCast<Node>());
    EXPECT_TRUE(demandSplitterInletIsNode);

    const auto demandSplitterOutlets = demandSplitter.outletModelObjects();
    ASSERT_FALSE(demandSplitterOutlets.empty());
    EXPECT_TRUE(std::ranges::all_of(demandSplitterOutlets, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); }));

    auto demandMixerOutlet = demandMixer.outletModelObject();
    ASSERT_TRUE(demandMixerOutlet);
    const bool demandMixerOutletIsNode = static_cast<bool>(demandMixerOutlet->optionalCast<Node>());
    EXPECT_TRUE(demandMixerOutletIsNode);

    const auto demandMixerInlets = demandMixer.inletModelObjects();
    ASSERT_FALSE(demandMixerInlets.empty());
    EXPECT_EQ(demandSplitterOutlets.size(), demandMixerInlets.size());
    EXPECT_TRUE(std::ranges::all_of(demandMixerInlets, [](const ModelObject& object) { return object.optionalCast<Node>().has_value(); }));

    const auto supplyComponents = plantLoop.supplyComponents();
    const auto demandComponents = plantLoop.demandComponents();
    ASSERT_FALSE(supplyComponents.empty());
    ASSERT_FALSE(demandComponents.empty());

    EXPECT_EQ(plantLoop.supplyInletNode(), supplyComponents.front().cast<Node>());
    EXPECT_EQ(plantLoop.supplyOutletNode(), supplyComponents.back().cast<Node>());
    EXPECT_EQ(plantLoop.demandInletNode(), demandComponents.front().cast<Node>());
    EXPECT_EQ(plantLoop.demandOutletNode(), demandComponents.back().cast<Node>());
  }
}

TEST_F(FiveZoneAirCooledIDFFixture, PlantLoop_IDF_SupplyAndDemandComponentsExposeExpectedConcreteTypes) {
  auto model = loadFiveZoneAirCooledModel();
  ASSERT_TRUE(model);

  const auto plantLoops = model->getConcreteModelObjects<PlantLoop>();
  ASSERT_EQ(2u, plantLoops.size());

  for (const auto& plantLoop : plantLoops) {
    const auto supplyComponents = plantLoop.supplyComponents();
    const auto demandComponents = plantLoop.demandComponents();
    ASSERT_FALSE(supplyComponents.empty());
    ASSERT_FALSE(demandComponents.empty());

    if (plantLoop.nameString() == "Hot Water Loop") {
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<PumpVariableSpeed>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<BoilerHotWater>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<PipeAdiabatic>().has_value(); }));

      EXPECT_EQ(7u, std::count_if(demandComponents.begin(), demandComponents.end(),
                                  [](const ModelObject& object) { return object.optionalCast<CoilHeatingWater>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(demandComponents, [](const ModelObject& object) { return object.optionalCast<PipeAdiabatic>().has_value(); }));
    } else if (plantLoop.nameString() == "Chilled Water Loop") {
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<PumpVariableSpeed>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<ChillerElectric>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(supplyComponents, [](const ModelObject& object) { return object.optionalCast<PipeAdiabatic>().has_value(); }));

      EXPECT_EQ(2u, std::count_if(demandComponents.begin(), demandComponents.end(),
                                  [](const ModelObject& object) { return object.optionalCast<CoilCoolingWater>().has_value(); }));
      EXPECT_TRUE(std::ranges::any_of(demandComponents, [](const ModelObject& object) { return object.optionalCast<PipeAdiabatic>().has_value(); }));
    } else {
      ADD_FAILURE() << "Unexpected plant loop name: " << plantLoop.nameString();
    }
  }
}

TEST_F(FiveZoneAirCooledIDFFixture, PlantLoop_IDF_ConcretePlantComponentsResolveOwningLoops) {
  auto model = loadFiveZoneAirCooledModel();
  ASSERT_TRUE(model);

  const auto boilers = model->getConcreteModelObjects<BoilerHotWater>();
  const auto chillers = model->getConcreteModelObjects<ChillerElectric>();
  const auto pumps = model->getConcreteModelObjects<PumpVariableSpeed>();
  const auto heatingCoils = model->getConcreteModelObjects<CoilHeatingWater>();
  const auto coolingCoils = model->getConcreteModelObjects<CoilCoolingWater>();
  const auto pipes = model->getConcreteModelObjects<PipeAdiabatic>();

  ASSERT_EQ(1u, boilers.size());
  ASSERT_EQ(1u, chillers.size());
  ASSERT_EQ(2u, pumps.size());
  ASSERT_EQ(7u, heatingCoils.size());
  ASSERT_EQ(2u, coolingCoils.size());
  ASSERT_FALSE(pipes.empty());

  auto boilerLoop = boilers.front().plantLoop();
  ASSERT_TRUE(boilerLoop);
  EXPECT_EQ("Hot Water Loop", boilerLoop->nameString());

  auto chillerLoop = chillers.front().plantLoop();
  ASSERT_TRUE(chillerLoop);
  EXPECT_EQ("Chilled Water Loop", chillerLoop->nameString());
  EXPECT_EQ("AirCooled", chillers.front().condenserType());
  EXPECT_FALSE(chillers.front().condenserWaterLoop());
  EXPECT_FALSE(chillers.front().heatRecoveryLoop());

  unsigned hotWaterPumpCount = 0;
  unsigned chilledWaterPumpCount = 0;
  for (const auto& pump : pumps) {
    auto loop = pump.plantLoop();
    ASSERT_TRUE(loop);
    if (loop->nameString() == "Hot Water Loop") {
      ++hotWaterPumpCount;
    } else if (loop->nameString() == "Chilled Water Loop") {
      ++chilledWaterPumpCount;
    }
  }
  EXPECT_EQ(1u, hotWaterPumpCount);
  EXPECT_EQ(1u, chilledWaterPumpCount);

  EXPECT_TRUE(std::ranges::all_of(heatingCoils, [](const CoilHeatingWater& coil) {
    auto loop = coil.plantLoop();
    return loop && loop->nameString() == "Hot Water Loop";
  }));
  EXPECT_TRUE(std::ranges::all_of(coolingCoils, [](const CoilCoolingWater& coil) {
    auto loop = coil.plantLoop();
    return loop && loop->nameString() == "Chilled Water Loop";
  }));

  bool sawHotWaterPipe = false;
  bool sawChilledWaterPipe = false;
  for (const auto& pipe : pipes) {
    auto loop = pipe.plantLoop();
    ASSERT_TRUE(loop);
    if (loop->nameString() == "Hot Water Loop") {
      sawHotWaterPipe = true;
    } else if (loop->nameString() == "Chilled Water Loop") {
      sawChilledWaterPipe = true;
    }
  }
  EXPECT_TRUE(sawHotWaterPipe);
  EXPECT_TRUE(sawChilledWaterPipe);
}
