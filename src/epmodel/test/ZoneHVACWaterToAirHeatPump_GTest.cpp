/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../Loop/PlantLoop_Impl.hpp"
#include "../ModelObject/OutdoorAirMixer.hpp"
#include "../ModelObject/OutdoorAirMixer_Impl.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilHeatingElectric.hpp"
#include "../StraightComponent/FanOnOff.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"
#include "../WaterToAirComponent/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "../WaterToAirComponent/CoilHeatingWater.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"
#include "../WaterToAirComponent/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACWaterToAirHeatPump.hpp"
#include "../ZoneHVACComponent/ZoneHVACWaterToAirHeatPump_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_WaterToAirHeatPump_FieldEnums.hxx>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_DefaultConstructor) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_FALSE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringCoolingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateDuringHeatingOperation());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_FALSE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());
  EXPECT_FALSE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringCoolingOperation(0.52));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringCoolingOperation());
  EXPECT_DOUBLE_EQ(0.52, wahp.supplyAirFlowRateDuringCoolingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateDuringHeatingOperation(0.48));
  ASSERT_TRUE(wahp.supplyAirFlowRateDuringHeatingOperation());
  EXPECT_DOUBLE_EQ(0.48, wahp.supplyAirFlowRateDuringHeatingOperation().get());
  wahp.autosizeSupplyAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(0.16));
  ASSERT_TRUE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  EXPECT_DOUBLE_EQ(0.16, wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded().get());
  wahp.resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setNoLoadSupplyAirFlowRateControlSetToLowSpeed(true));
  EXPECT_TRUE(wahp.noLoadSupplyAirFlowRateControlSetToLowSpeed());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.25));
  wahp.autosizeOutdoorAirFlowRateDuringCoolingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringCoolingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.22));
  wahp.autosizeOutdoorAirFlowRateDuringHeatingOperation();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateDuringHeatingOperationAutosized());

  EXPECT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.08));
  wahp.resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_FALSE(wahp.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded());
  wahp.autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();
  EXPECT_TRUE(wahp.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized());

  EXPECT_TRUE(wahp.setMaximumSupplyAirTemperaturefromSupplementalHeater(55.0));
  ASSERT_TRUE(wahp.maximumSupplyAirTemperaturefromSupplementalHeater());
  EXPECT_DOUBLE_EQ(55.0, wahp.maximumSupplyAirTemperaturefromSupplementalHeater().get());
  wahp.autosizeMaximumSupplyAirTemperaturefromSupplementalHeater();
  EXPECT_TRUE(wahp.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized());

  EXPECT_TRUE(wahp.setMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation(18.5));
  EXPECT_DOUBLE_EQ(18.5, wahp.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation());
  wahp.resetMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation();
  EXPECT_TRUE(wahp.isMaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperationDefaulted());

  EXPECT_TRUE(wahp.setFanPlacement("BlowThrough"));
  EXPECT_EQ("BlowThrough", wahp.fanPlacement());
  wahp.resetFanPlacement();
  EXPECT_TRUE(wahp.isFanPlacementDefaulted());

  EXPECT_TRUE(wahp.setHeatPumpCoilWaterFlowMode("Cycling"));
  EXPECT_EQ("Cycling", wahp.heatPumpCoilWaterFlowMode());
  wahp.resetHeatPumpCoilWaterFlowMode();
  EXPECT_TRUE(wahp.isHeatPumpCoilWaterFlowModeDefaulted());

  EXPECT_TRUE(wahp.setDXHeatingCoilSizingRatio(1.1));
  EXPECT_DOUBLE_EQ(1.1, wahp.dXHeatingCoilSizingRatio());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_TopologyAndChildren) {
  Model model;
  ThermalZone zone(model);
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(wahp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  EXPECT_EQ(openstudio::ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName, wahp.inletPort());
  EXPECT_EQ(openstudio::ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName, wahp.outletPort());

  ASSERT_TRUE(wahp.inletNode());
  ASSERT_TRUE(wahp.outletNode());
  ASSERT_TRUE(wahp.fanOutletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  ASSERT_TRUE(wahp.outdoorAirMixer());
  ASSERT_TRUE(wahp.mixedAirNode());
  ASSERT_TRUE(wahp.outdoorAirNode());
  ASSERT_TRUE(wahp.reliefAirNode());

  const auto children = wahp.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(fan, children[0]);
  EXPECT_EQ(heatingCoil, children[1]);
  EXPECT_EQ(coolingCoil, children[2]);
  EXPECT_EQ(supplementalHeatingCoil, children[3]);
  EXPECT_EQ(wahp.outdoorAirMixer()->handle(), children[4].handle());

  ASSERT_TRUE(fan.containingHVACComponent());
  ASSERT_TRUE(heatingCoil.containingHVACComponent());
  ASSERT_TRUE(coolingCoil.containingHVACComponent());
  ASSERT_TRUE(supplementalHeatingCoil.containingHVACComponent());
  EXPECT_EQ(wahp, fan.containingHVACComponent().get());
  EXPECT_EQ(wahp, heatingCoil.containingHVACComponent().get());
  EXPECT_EQ(wahp, coolingCoil.containingHVACComponent().get());
  EXPECT_EQ(wahp, supplementalHeatingCoil.containingHVACComponent().get());

  ASSERT_TRUE(wahp.addToThermalZone(zone));
  ASSERT_TRUE(wahp.thermalZone());
  EXPECT_EQ(zone, wahp.thermalZone().get());

  auto coolingInlet = coolingCoil.airInletModelObject()->optionalCast<Node>();
  auto coolingOutlet = coolingCoil.airOutletModelObject()->optionalCast<Node>();
  auto heatingInlet = heatingCoil.airInletModelObject()->optionalCast<Node>();
  auto heatingOutlet = heatingCoil.airOutletModelObject()->optionalCast<Node>();
  auto fanInlet = fan.inletModelObject()->optionalCast<Node>();
  auto fanOutlet = fan.outletModelObject()->optionalCast<Node>();
  auto supplementalInlet = supplementalHeatingCoil.airInletModelObject()->optionalCast<Node>();
  auto supplementalOutlet = supplementalHeatingCoil.airOutletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(coolingInlet);
  ASSERT_TRUE(coolingOutlet);
  ASSERT_TRUE(heatingInlet);
  ASSERT_TRUE(heatingOutlet);
  ASSERT_TRUE(fanInlet);
  ASSERT_TRUE(fanOutlet);
  ASSERT_TRUE(supplementalInlet);
  ASSERT_TRUE(supplementalOutlet);

  EXPECT_EQ(*wahp.inletNode(), *wahp.outdoorAirMixer()->returnAirNode());
  EXPECT_EQ(*wahp.mixedAirNode(), *coolingInlet);
  EXPECT_EQ(*wahp.mixedAirNode(), *wahp.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*wahp.outdoorAirNode(), *wahp.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*wahp.reliefAirNode(), *wahp.outdoorAirMixer()->reliefAirNode());
  EXPECT_EQ(*wahp.coolingCoilOutletNode(), *coolingOutlet);
  EXPECT_EQ(*wahp.coolingCoilOutletNode(), *heatingInlet);
  EXPECT_EQ(*wahp.heatingCoilOutletNode(), *heatingOutlet);
  EXPECT_EQ(*wahp.heatingCoilOutletNode(), *fanInlet);
  EXPECT_EQ(*wahp.fanOutletNode(), *fanOutlet);
  EXPECT_EQ(*wahp.fanOutletNode(), *supplementalInlet);
  EXPECT_EQ(*wahp.outletNode(), *supplementalOutlet);

  wahp.removeFromThermalZone();
  EXPECT_FALSE(wahp.thermalZone());
  EXPECT_TRUE(wahp.inletNode());
  EXPECT_TRUE(wahp.outletNode());
  EXPECT_TRUE(wahp.fanOutletNode());
  EXPECT_TRUE(wahp.coolingCoilOutletNode());
  EXPECT_TRUE(wahp.heatingCoilOutletNode());
  EXPECT_TRUE(wahp.outdoorAirMixer());
  EXPECT_TRUE(wahp.mixedAirNode());
  EXPECT_TRUE(wahp.outdoorAirNode());
  EXPECT_TRUE(wahp.reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_OutdoorAirMixerIsExposedWhenUsed) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.2));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.15));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.05));
  ASSERT_TRUE(wahp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(wahp.outdoorAirMixer());
  ASSERT_TRUE(wahp.mixedAirNode());
  ASSERT_TRUE(wahp.outdoorAirNode());
  ASSERT_TRUE(wahp.reliefAirNode());
  ASSERT_TRUE(wahp.outdoorAirMixer()->mixedAirNode());
  ASSERT_TRUE(wahp.outdoorAirMixer()->outdoorAirNode());
  ASSERT_TRUE(wahp.outdoorAirMixer()->reliefAirNode());
  const auto children = wahp.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(wahp.outdoorAirMixer()->handle(), children.back().handle());
  EXPECT_EQ(OutdoorAirMixer::iddObjectType(), wahp.outdoorAirMixer()->iddObjectType());
  EXPECT_EQ(*wahp.mixedAirNode(), *wahp.outdoorAirMixer()->mixedAirNode());
  EXPECT_EQ(*wahp.outdoorAirNode(), *wahp.outdoorAirMixer()->outdoorAirNode());
  EXPECT_EQ(*wahp.reliefAirNode(), *wahp.outdoorAirMixer()->reliefAirNode());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_SourceWaterBranchesSurviveReloadAndCanMove) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-water-to-air-heat-pump-source-water.idf");

  Model model;
  ThermalZone zone(model);
  PlantLoop sourceLoop(model);
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(sourceLoop.setName("Original WTAHP Source Loop"));
  ASSERT_TRUE(heatingCoil.setName("WTAHP Source Heating Coil"));
  ASSERT_TRUE(coolingCoil.setName("WTAHP Source Cooling Coil"));
  ASSERT_TRUE(wahp.setName("Source Water WTAHP"));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.05));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.05));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.02));
  ASSERT_TRUE(wahp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));
  ASSERT_TRUE(wahp.addToThermalZone(zone));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(heatingCoil));
  ASSERT_TRUE(sourceLoop.addDemandBranchForComponent(coolingCoil));
  EXPECT_EQ(2u, sourceLoop.demandComponents(CoilHeatingWaterToAirHeatPumpEquationFit::iddObjectType()).size()
                  + sourceLoop.demandComponents(CoilCoolingWaterToAirHeatPumpEquationFit::iddObjectType()).size());
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSourceLoop = loadedModel->getConcreteModelObjectByName<PlantLoop>("Original WTAHP Source Loop");
  auto loadedHeatingCoil = loadedModel->getConcreteModelObjectByName<CoilHeatingWaterToAirHeatPumpEquationFit>("WTAHP Source Heating Coil");
  auto loadedCoolingCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingWaterToAirHeatPumpEquationFit>("WTAHP Source Cooling Coil");
  auto loadedWahp = loadedModel->getConcreteModelObjectByName<ZoneHVACWaterToAirHeatPump>("Source Water WTAHP");
  ASSERT_TRUE(loadedSourceLoop);
  ASSERT_TRUE(loadedHeatingCoil);
  ASSERT_TRUE(loadedCoolingCoil);
  ASSERT_TRUE(loadedWahp);
  ASSERT_TRUE(loadedHeatingCoil->plantLoop());
  ASSERT_TRUE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedHeatingCoil->plantLoop());
  EXPECT_EQ(*loadedSourceLoop, *loadedCoolingCoil->plantLoop());
  ASSERT_TRUE(loadedHeatingCoil->containingHVACComponent());
  ASSERT_TRUE(loadedCoolingCoil->containingHVACComponent());
  EXPECT_EQ(*loadedWahp, *loadedHeatingCoil->containingHVACComponent());
  EXPECT_EQ(*loadedWahp, *loadedCoolingCoil->containingHVACComponent());
  ASSERT_TRUE(loadedWahp->outdoorAirMixer());
  EXPECT_EQ(1u, loadedModel->getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());

  EXPECT_TRUE(loadedSourceLoop->removeDemandBranchWithComponent(*loadedHeatingCoil));
  EXPECT_TRUE(loadedSourceLoop->removeDemandBranchWithComponent(*loadedCoolingCoil));
  EXPECT_FALSE(loadedHeatingCoil->plantLoop());
  EXPECT_FALSE(loadedCoolingCoil->plantLoop());
  EXPECT_FALSE(loadedHeatingCoil->waterInletModelObject());
  EXPECT_FALSE(loadedHeatingCoil->waterOutletModelObject());
  EXPECT_FALSE(loadedCoolingCoil->waterInletModelObject());
  EXPECT_FALSE(loadedCoolingCoil->waterOutletModelObject());
  ASSERT_TRUE(loadedHeatingCoil->containingHVACComponent());
  ASSERT_TRUE(loadedCoolingCoil->containingHVACComponent());
  EXPECT_EQ(*loadedWahp, *loadedHeatingCoil->containingHVACComponent());
  EXPECT_EQ(*loadedWahp, *loadedCoolingCoil->containingHVACComponent());
  EXPECT_FALSE(loadedSourceLoop->remove().empty());

  PlantLoop replacementSourceLoop(*loadedModel);
  ASSERT_TRUE(replacementSourceLoop.setName("Replacement WTAHP Source Loop"));
  EXPECT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedHeatingCoil));
  EXPECT_TRUE(replacementSourceLoop.addDemandBranchForComponent(*loadedCoolingCoil));
  ASSERT_TRUE(loadedHeatingCoil->plantLoop());
  ASSERT_TRUE(loadedCoolingCoil->plantLoop());
  EXPECT_EQ(replacementSourceLoop, *loadedHeatingCoil->plantLoop());
  EXPECT_EQ(replacementSourceLoop, *loadedCoolingCoil->plantLoop());
  EXPECT_TRUE(loadedWahp->inletNode());
  EXPECT_TRUE(loadedWahp->outletNode());
  EXPECT_TRUE(loadedWahp->outdoorAirMixer());

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_RemovalCleansOwnedOutdoorAirPath) {
  Model model;
  ThermalZone zone(model);
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingElectric supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));
  ASSERT_TRUE(wahp.addToThermalZone(zone));
  ASSERT_TRUE(wahp.outdoorAirMixer());
  const auto mixerHandle = wahp.outdoorAirMixer()->handle();
  EXPECT_EQ(1u, model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).size());

  EXPECT_FALSE(wahp.remove().empty());
  EXPECT_FALSE(model.getObject(mixerHandle));
  EXPECT_TRUE(model.getConcreteModelObjects<OutdoorAirMixer>().empty());
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_ScheduleRelationships_RoundTrip) {
  Model model;
  ZoneHVACWaterToAirHeatPump wahp(model);

  auto defaultAvailability = wahp.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultAvailability);
  EXPECT_DOUBLE_EQ(1.0, defaultAvailability->value());
  auto defaultFanMode = wahp.supplyAirFanOperatingModeSchedule()->optionalCast<ScheduleConstant>();
  ASSERT_TRUE(defaultFanMode);
  EXPECT_DOUBLE_EQ(1.0, defaultFanMode->value());

  ScheduleCompact availability(model);
  ScheduleCompact fanMode(model);
  ASSERT_TRUE(availability.setToConstantValue(0.6));
  ASSERT_TRUE(fanMode.setToConstantValue(1.0));

  EXPECT_TRUE(wahp.setAvailabilitySchedule(availability));
  EXPECT_TRUE(wahp.setSupplyAirFanOperatingModeSchedule(fanMode));
  EXPECT_EQ(availability.handle(), wahp.availabilitySchedule().handle());
  ASSERT_TRUE(wahp.supplyAirFanOperatingModeSchedule());
  EXPECT_EQ(fanMode.handle(), wahp.supplyAirFanOperatingModeSchedule()->handle());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_NodeRolesFollowBlowThroughOrder) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(wahp.setFanPlacement("BlowThrough"));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(wahp.fanOutletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  ASSERT_TRUE(wahp.outletNode());

  EXPECT_EQ(*wahp.fanOutletNode(), *coolingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.heatingCoilOutletNode(), *supplementalHeatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.outletNode(), *supplementalHeatingCoil.airOutletModelObject()->optionalCast<Node>());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_InternalNodeRenamesSurviveCanonicalize) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(wahp.fanOutletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  ASSERT_TRUE(wahp.fanOutletNode()->setName("Custom WTAHP Fan Outlet"));
  ASSERT_TRUE(wahp.coolingCoilOutletNode()->setName("Custom WTAHP Cooling Outlet"));
  ASSERT_TRUE(wahp.heatingCoilOutletNode()->setName("Custom WTAHP Heating Outlet"));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(wahp.fanOutletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  EXPECT_EQ("Custom WTAHP Fan Outlet", wahp.fanOutletNode()->nameString());
  EXPECT_EQ("Custom WTAHP Cooling Outlet", wahp.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Custom WTAHP Heating Outlet", wahp.heatingCoilOutletNode()->nameString());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_ContainedChildTopologyMutationsAreRejected) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop plantLoop(model);
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  auto originalFanOutlet = wahp.fanOutletNode();
  auto originalCoolingOutlet = wahp.coolingCoilOutletNode();
  auto originalHeatingOutlet = wahp.heatingCoilOutletNode();
  ASSERT_TRUE(originalFanOutlet);
  ASSERT_TRUE(originalCoolingOutlet);
  ASSERT_TRUE(originalHeatingOutlet);

  auto supplyOutletNode = airLoop.supplyOutletNode();

  fan.disconnect();
  EXPECT_FALSE(fan.addToNode(supplyOutletNode));
  EXPECT_FALSE(fan.isRemovable());
  EXPECT_TRUE(fan.remove().empty());

  heatingCoil.disconnectAirSide();
  EXPECT_FALSE(heatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(heatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(heatingCoil.isRemovable());
  EXPECT_TRUE(heatingCoil.remove().empty());

  coolingCoil.disconnectAirSide();
  EXPECT_FALSE(coolingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(coolingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(coolingCoil.isRemovable());
  EXPECT_TRUE(coolingCoil.remove().empty());

  supplementalHeatingCoil.disconnectAirSide();
  EXPECT_FALSE(supplementalHeatingCoil.addToNode(supplyOutletNode));
  EXPECT_FALSE(supplementalHeatingCoil.removeFromAirLoopHVAC());
  EXPECT_FALSE(supplementalHeatingCoil.isRemovable());
  EXPECT_TRUE(supplementalHeatingCoil.remove().empty());
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(supplementalHeatingCoil));
  ASSERT_TRUE(supplementalHeatingCoil.plantLoop());
  supplementalHeatingCoil.disconnect();
  ASSERT_TRUE(supplementalHeatingCoil.plantLoop());
  EXPECT_EQ(plantLoop, supplementalHeatingCoil.plantLoop().get());

  ASSERT_TRUE(wahp.fanOutletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  EXPECT_EQ(*originalFanOutlet, *wahp.fanOutletNode());
  EXPECT_EQ(*originalCoolingOutlet, *wahp.coolingCoilOutletNode());
  EXPECT_EQ(*originalHeatingOutlet, *wahp.heatingCoilOutletNode());
}

TEST_F(EPModelFixture, ZoneHVACWaterToAirHeatPump_CanonicalizeRepairsContainedNodePath) {
  Model model;
  FanOnOff fan(model);
  CoilHeatingWaterToAirHeatPumpEquationFit heatingCoil(model);
  CoilCoolingWaterToAirHeatPumpEquationFit coolingCoil(model);
  CoilHeatingWater supplementalHeatingCoil(model);
  ZoneHVACWaterToAirHeatPump wahp(model);

  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringCoolingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateDuringHeatingOperation(0.0));
  ASSERT_TRUE(wahp.setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(0.0));
  ASSERT_TRUE(wahp.setFanPlacement("DrawThrough"));
  ASSERT_TRUE(wahp.setSupplyAirFan(fan));
  ASSERT_TRUE(wahp.setHeatingCoil(heatingCoil));
  ASSERT_TRUE(wahp.setCoolingCoil(coolingCoil));
  ASSERT_TRUE(wahp.setSupplementalHeatingCoil(supplementalHeatingCoil));

  ASSERT_TRUE(wahp.inletNode());
  ASSERT_TRUE(wahp.outletNode());
  auto expectedInlet = wahp.inletNode();
  auto expectedOutlet = wahp.outletNode();
  ASSERT_TRUE(expectedInlet);
  ASSERT_TRUE(expectedOutlet);

  Node rogueCoolingOutlet(model);
  ASSERT_TRUE(rogueCoolingOutlet.setName("Rogue WTAHP Cooling Outlet"));
  Node rogueHeatingOutlet(model);
  ASSERT_TRUE(rogueHeatingOutlet.setName("Rogue WTAHP Heating Outlet"));
  Node rogueFanOutlet(model);
  ASSERT_TRUE(rogueFanOutlet.setName("Rogue WTAHP Fan Outlet"));

  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airInletPort(), wahp.inletNode()->handle()));
  ASSERT_TRUE(coolingCoil.setPointer(coolingCoil.airOutletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airInletPort(), rogueCoolingOutlet.handle()));
  ASSERT_TRUE(heatingCoil.setPointer(heatingCoil.airOutletPort(), rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.inletPort(), rogueHeatingOutlet.handle()));
  ASSERT_TRUE(fan.setPointer(fan.outletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.airInletPort(), rogueFanOutlet.handle()));
  ASSERT_TRUE(supplementalHeatingCoil.setPointer(supplementalHeatingCoil.airOutletPort(), wahp.outletNode()->handle()));

  auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);

  ASSERT_TRUE(wahp.inletNode());
  ASSERT_TRUE(wahp.outletNode());
  ASSERT_TRUE(wahp.coolingCoilOutletNode());
  ASSERT_TRUE(wahp.heatingCoilOutletNode());
  ASSERT_TRUE(wahp.fanOutletNode());
  EXPECT_EQ(*expectedInlet, *wahp.inletNode());
  EXPECT_EQ(*expectedOutlet, *wahp.outletNode());
  EXPECT_EQ("Rogue WTAHP Cooling Outlet", wahp.coolingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue WTAHP Heating Outlet", wahp.heatingCoilOutletNode()->nameString());
  EXPECT_EQ("Rogue WTAHP Fan Outlet", wahp.fanOutletNode()->nameString());
  EXPECT_EQ(*wahp.coolingCoilOutletNode(), *heatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.heatingCoilOutletNode(), *fan.inletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.fanOutletNode(), *supplementalHeatingCoil.airInletModelObject()->optionalCast<Node>());
  EXPECT_EQ(*wahp.outletNode(), *supplementalHeatingCoil.airOutletModelObject()->optionalCast<Node>());
}
