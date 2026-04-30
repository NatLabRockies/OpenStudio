/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"

#include <utilities/idd/Refrigeration_CompressorRack_FieldEnums.hxx>

#include "../Curve/Curve.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/Schedule_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/RefrigerationCompressorRack.hpp"
#include "../StraightComponent/RefrigerationCompressorRack_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, RefrigerationCompressorRack_DefaultConstructor) {
  Model model;
  RefrigerationCompressorRack rack(model);

  EXPECT_EQ(RefrigerationCompressorRack::iddObjectType(), rack.iddObjectType());
  EXPECT_EQ("Outdoors", rack.heatRejectionLocation());
  EXPECT_DOUBLE_EQ(2.0, rack.designCompressorRackCOP());
  ASSERT_TRUE(rack.compressorRackCOPFunctionofTemperatureCurve().optionalCast<CurveQuadratic>());
  EXPECT_DOUBLE_EQ(250.0, rack.designCondenserFanPower());
  EXPECT_FALSE(rack.condenserFanPowerFunctionofTemperatureCurve());
  EXPECT_EQ("AirCooled", rack.condenserType());
  EXPECT_EQ("VariableFlow", rack.waterCooledLoopFlowType());
  EXPECT_FALSE(rack.waterCooledCondenserOutletTemperatureSchedule());
  EXPECT_FALSE(rack.waterCooledCondenserDesignFlowRate());
  EXPECT_FALSE(rack.waterCooledCondenserMaximumFlowRate());
  EXPECT_DOUBLE_EQ(55.0, rack.waterCooledCondenserMaximumWaterOutletTemperature());
  EXPECT_DOUBLE_EQ(10.0, rack.waterCooledCondenserMinimumWaterInletTemperature());
  EXPECT_FALSE(rack.evaporativeCondenserAvailabilitySchedule());
  EXPECT_DOUBLE_EQ(0.9, rack.evaporativeCondenserEffectiveness());
  EXPECT_FALSE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_DOUBLE_EQ(200.0, rack.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, rack.basinHeaterSetpointTemperature());
  ASSERT_TRUE(rack.designEvaporativeCondenserWaterPumpPower());
  EXPECT_DOUBLE_EQ(1000.0, rack.designEvaporativeCondenserWaterPumpPower().value());
  EXPECT_FALSE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_EQ("General", rack.endUseSubcategory());
  EXPECT_TRUE(rack.isEndUseSubcategoryDefaulted());
  EXPECT_FALSE(rack.heatRejectionZone());
}

TEST_F(EPModelFixture, RefrigerationCompressorRack_RelationshipAndScalarAccessors_RoundTrip) {
  Model model;
  RefrigerationCompressorRack rack(model);

  CurveQuadratic compressorCurve(model);
  ASSERT_TRUE(compressorCurve.setCoefficient1Constant(2.0));
  ASSERT_TRUE(compressorCurve.setCoefficient2x(-0.01));
  ASSERT_TRUE(compressorCurve.setCoefficient3xPOW2(0.0001));
  ASSERT_TRUE(compressorCurve.setMinimumValueofx(5.0));
  ASSERT_TRUE(compressorCurve.setMaximumValueofx(40.0));
  EXPECT_TRUE(rack.setCompressorRackCOPFunctionofTemperatureCurve(compressorCurve));
  EXPECT_EQ(compressorCurve.handle(), rack.compressorRackCOPFunctionofTemperatureCurve().handle());

  CurveQuadratic fanCurve(model);
  ASSERT_TRUE(fanCurve.setCoefficient1Constant(1.0));
  ASSERT_TRUE(fanCurve.setCoefficient2x(0.1));
  ASSERT_TRUE(fanCurve.setCoefficient3xPOW2(0.01));
  ASSERT_TRUE(fanCurve.setMinimumValueofx(0.0));
  ASSERT_TRUE(fanCurve.setMaximumValueofx(10.0));
  EXPECT_TRUE(rack.setCondenserFanPowerFunctionofTemperatureCurve(fanCurve));
  ASSERT_TRUE(rack.condenserFanPowerFunctionofTemperatureCurve());
  EXPECT_EQ(fanCurve.handle(), rack.condenserFanPowerFunctionofTemperatureCurve()->handle());

  ScheduleConstant outletSchedule(model);
  ASSERT_TRUE(outletSchedule.setValue(28.0));
  EXPECT_TRUE(rack.setWaterCooledCondenserOutletTemperatureSchedule(outletSchedule));
  ASSERT_TRUE(rack.waterCooledCondenserOutletTemperatureSchedule());
  EXPECT_EQ(outletSchedule.handle(), rack.waterCooledCondenserOutletTemperatureSchedule()->handle());
  ASSERT_TRUE(outletSchedule.scheduleTypeLimits());
  EXPECT_EQ("Temperature", outletSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongSchedule(model);
  ASSERT_TRUE(wrongSchedule.setValue(1.0));
  ScheduleTypeLimits availabilityLimits(model);
  ASSERT_TRUE(availabilityLimits.setUnitType("Availability"));
  ASSERT_TRUE(wrongSchedule.setScheduleTypeLimits(availabilityLimits));
  EXPECT_FALSE(rack.setWaterCooledCondenserOutletTemperatureSchedule(wrongSchedule));
  ASSERT_TRUE(rack.waterCooledCondenserOutletTemperatureSchedule());
  EXPECT_EQ(outletSchedule.handle(), rack.waterCooledCondenserOutletTemperatureSchedule()->handle());

  ScheduleConstant evaporativeSchedule(model);
  ASSERT_TRUE(evaporativeSchedule.setValue(1.0));
  EXPECT_TRUE(rack.setEvaporativeCondenserAvailabilitySchedule(evaporativeSchedule));
  ASSERT_TRUE(rack.evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(evaporativeSchedule.handle(), rack.evaporativeCondenserAvailabilitySchedule()->handle());
  ASSERT_TRUE(evaporativeSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", evaporativeSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant wrongEvapSchedule(model);
  ASSERT_TRUE(wrongEvapSchedule.setValue(15.0));
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(wrongEvapSchedule.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(rack.setEvaporativeCondenserAvailabilitySchedule(wrongEvapSchedule));
  ASSERT_TRUE(rack.evaporativeCondenserAvailabilitySchedule());
  EXPECT_EQ(evaporativeSchedule.handle(), rack.evaporativeCondenserAvailabilitySchedule()->handle());

  ThermalZone zone(model);
  EXPECT_TRUE(rack.setHeatRejectionZone(zone));
  ASSERT_TRUE(rack.heatRejectionZone());
  EXPECT_EQ(zone.handle(), rack.heatRejectionZone()->handle());

  EXPECT_TRUE(rack.setHeatRejectionLocation("Zone"));
  EXPECT_TRUE(rack.setDesignCompressorRackCOP(2.5));
  EXPECT_TRUE(rack.setDesignCondenserFanPower(300.0));
  EXPECT_TRUE(rack.setCondenserType("EvaporativelyCooled"));
  EXPECT_TRUE(rack.setWaterCooledLoopFlowType("ConstantFlow"));
  EXPECT_TRUE(rack.setWaterCooledCondenserDesignFlowRate(0.002));
  EXPECT_TRUE(rack.setWaterCooledCondenserMaximumFlowRate(0.003));
  EXPECT_TRUE(rack.setWaterCooledCondenserMaximumWaterOutletTemperature(50.0));
  EXPECT_TRUE(rack.setWaterCooledCondenserMinimumWaterInletTemperature(12.0));
  EXPECT_TRUE(rack.setEvaporativeCondenserEffectiveness(0.8));
  EXPECT_TRUE(rack.setEvaporativeCondenserAirFlowRate(0.004));
  EXPECT_TRUE(rack.setBasinHeaterCapacity(220.0));
  EXPECT_TRUE(rack.setBasinHeaterSetpointTemperature(3.0));
  EXPECT_TRUE(rack.setDesignEvaporativeCondenserWaterPumpPower(1200.0));
  EXPECT_TRUE(rack.setEndUseSubcategory("Cooling"));

  EXPECT_EQ("Zone", rack.heatRejectionLocation());
  EXPECT_DOUBLE_EQ(2.5, rack.designCompressorRackCOP());
  EXPECT_DOUBLE_EQ(300.0, rack.designCondenserFanPower());
  EXPECT_EQ("EvaporativelyCooled", rack.condenserType());
  EXPECT_EQ("ConstantFlow", rack.waterCooledLoopFlowType());
  ASSERT_TRUE(rack.waterCooledCondenserDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.002, rack.waterCooledCondenserDesignFlowRate().value());
  ASSERT_TRUE(rack.waterCooledCondenserMaximumFlowRate());
  EXPECT_DOUBLE_EQ(0.003, rack.waterCooledCondenserMaximumFlowRate().value());
  EXPECT_DOUBLE_EQ(50.0, rack.waterCooledCondenserMaximumWaterOutletTemperature());
  EXPECT_DOUBLE_EQ(12.0, rack.waterCooledCondenserMinimumWaterInletTemperature());
  EXPECT_DOUBLE_EQ(0.8, rack.evaporativeCondenserEffectiveness());
  ASSERT_TRUE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.004, rack.evaporativeCondenserAirFlowRate().value());
  EXPECT_FALSE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_DOUBLE_EQ(220.0, rack.basinHeaterCapacity());
  EXPECT_DOUBLE_EQ(3.0, rack.basinHeaterSetpointTemperature());
  ASSERT_TRUE(rack.designEvaporativeCondenserWaterPumpPower());
  EXPECT_DOUBLE_EQ(1200.0, rack.designEvaporativeCondenserWaterPumpPower().value());
  EXPECT_FALSE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_EQ("Cooling", rack.endUseSubcategory());
  EXPECT_FALSE(rack.isEndUseSubcategoryDefaulted());

  rack.resetCondenserFanPowerFunctionofTemperatureCurve();
  EXPECT_FALSE(rack.condenserFanPowerFunctionofTemperatureCurve());
  rack.resetWaterCooledCondenserOutletTemperatureSchedule();
  EXPECT_FALSE(rack.waterCooledCondenserOutletTemperatureSchedule());
  rack.resetWaterCooledCondenserDesignFlowRate();
  EXPECT_FALSE(rack.waterCooledCondenserDesignFlowRate());
  rack.resetWaterCooledCondenserMaximumFlowRate();
  EXPECT_FALSE(rack.waterCooledCondenserMaximumFlowRate());
  rack.resetEvaporativeCondenserAvailabilitySchedule();
  EXPECT_FALSE(rack.evaporativeCondenserAvailabilitySchedule());
  EXPECT_TRUE(rack.autocalculateEvaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.isEvaporativeCondenserAirFlowRateAutocalculated());
  EXPECT_FALSE(rack.evaporativeCondenserAirFlowRate());
  EXPECT_TRUE(rack.autocalculateDesignEvaporativeCondenserWaterPumpPower());
  EXPECT_TRUE(rack.isDesignEvaporativeCondenserWaterPumpPowerAutocalculated());
  EXPECT_FALSE(rack.designEvaporativeCondenserWaterPumpPower());
  rack.resetEndUseSubcategory();
  EXPECT_TRUE(rack.isEndUseSubcategoryDefaulted());
  rack.resetHeatRejectionZone();
  EXPECT_FALSE(rack.heatRejectionZone());
}

TEST_F(EPModelFixture, RefrigerationCompressorRack_AddToNode_PlantDemandOnlyAndReattach) {
  Model model;
  RefrigerationCompressorRack rejectedRack(model);

  AirLoopHVAC airLoop(model);
  Node airSupplyOutletNode = airLoop.supplyOutletNode();
  const auto initialAirSupplyCount = airLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedRack.addToNode(airSupplyOutletNode));
  EXPECT_EQ(initialAirSupplyCount, airLoop.supplyComponents().size());

  Node airDemandNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  const auto initialAirDemandCount = airLoop.demandComponents().size();
  EXPECT_FALSE(rejectedRack.addToNode(airDemandNode));
  EXPECT_EQ(initialAirDemandCount, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  Node plantSupplyOutletNode = plantLoop.supplyOutletNode();
  const auto initialPlantSupplyCount = plantLoop.supplyComponents().size();
  EXPECT_FALSE(rejectedRack.addToNode(plantSupplyOutletNode));
  EXPECT_EQ(initialPlantSupplyCount, plantLoop.supplyComponents().size());

  Node unconnectedNode = model.getOrCreateTransientByName<Node>("Unconnected RefrigerationCompressorRack Node");
  EXPECT_FALSE(rejectedRack.addToNode(unconnectedNode));
  EXPECT_FALSE(rejectedRack.loop());
  EXPECT_FALSE(rejectedRack.inletModelObject());
  EXPECT_FALSE(rejectedRack.outletModelObject());

  RefrigerationCompressorRack rack(model);
  Node plantDemandOutletNode = plantLoop.demandOutletNode();
  const auto initialPlantDemandCount = plantLoop.demandComponents().size();
  EXPECT_TRUE(rack.addToNode(plantDemandOutletNode));
  EXPECT_GT(plantLoop.demandComponents().size(), initialPlantDemandCount);
  ASSERT_TRUE(rack.plantLoop());
  EXPECT_EQ(plantLoop.handle(), rack.plantLoop()->handle());
  EXPECT_TRUE(plantLoop.demandComponent(rack.handle()));
  EXPECT_FALSE(plantLoop.supplyComponent(rack.handle()));

  auto inletNode = rack.getModelObjectTarget<Node>(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName);
  auto outletNode = rack.getModelObjectTarget<Node>(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  ASSERT_TRUE(rack.inletModelObject());
  ASSERT_TRUE(rack.outletModelObject());
  EXPECT_EQ(rack.inletModelObject()->handle(), inletNode->handle());
  EXPECT_EQ(rack.outletModelObject()->handle(), outletNode->handle());

  Node plantDemandInletNode = plantLoop.demandInletNode();
  const auto demandCountBeforeSameLoopMove = plantLoop.demandComponents().size();
  const auto firstInletHandle = inletNode->handle();
  const auto firstOutletHandle = outletNode->handle();
  EXPECT_TRUE(rack.addToNode(plantDemandInletNode));
  ASSERT_TRUE(rack.plantLoop());
  EXPECT_EQ(plantLoop.handle(), rack.plantLoop()->handle());
  EXPECT_EQ(demandCountBeforeSameLoopMove, plantLoop.demandComponents().size());
  EXPECT_TRUE(plantLoop.demandComponent(rack.handle()));
  inletNode = rack.getModelObjectTarget<Node>(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserInletNodeName);
  outletNode = rack.getModelObjectTarget<Node>(openstudio::Refrigeration_CompressorRackFields::WaterCooledCondenserOutletNodeName);
  ASSERT_TRUE(inletNode);
  ASSERT_TRUE(outletNode);
  EXPECT_NE(firstInletHandle, inletNode->handle());
  EXPECT_NE(firstOutletHandle, outletNode->handle());

  rack.disconnect();
  EXPECT_FALSE(rack.plantLoop());
  EXPECT_FALSE(rack.inletModelObject());
  EXPECT_FALSE(rack.outletModelObject());

  plantDemandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(rack.addToNode(plantDemandOutletNode));

  PlantLoop secondPlantLoop(model);
  plantDemandInletNode = secondPlantLoop.demandInletNode();
  rack.disconnect();
  EXPECT_TRUE(rack.addToNode(plantDemandInletNode));
  ASSERT_TRUE(rack.plantLoop());
  EXPECT_EQ(secondPlantLoop.handle(), rack.plantLoop()->handle());
  EXPECT_TRUE(secondPlantLoop.demandComponent(rack.handle()));
  EXPECT_FALSE(secondPlantLoop.supplyComponent(rack.handle()));

  RefrigerationCompressorRack branchManagedRack(model);
  EXPECT_TRUE(secondPlantLoop.addDemandBranchForComponent(branchManagedRack));
  ASSERT_TRUE(branchManagedRack.plantLoop());
  EXPECT_TRUE(secondPlantLoop.removeDemandBranchWithComponent(branchManagedRack));
  EXPECT_FALSE(branchManagedRack.plantLoop());
  EXPECT_FALSE(branchManagedRack.inletModelObject());
  EXPECT_FALSE(branchManagedRack.outletModelObject());

  auto cloneObject = model.addObject(branchManagedRack.idfObject());
  ASSERT_TRUE(cloneObject);
  auto clone = cloneObject->cast<RefrigerationCompressorRack>();
  EXPECT_TRUE(secondPlantLoop.addDemandBranchForComponent(clone));
  EXPECT_EQ(2u, secondPlantLoop.demandComponents(RefrigerationCompressorRack::iddObjectType()).size());
}

TEST_F(EPModelFixture, RefrigerationCompressorRack_Remove_RemovesOwnedCurves) {
  Model model;
  RefrigerationCompressorRack rack(model);

  const auto initialRacks = model.getModelObjects<RefrigerationCompressorRack>().size();
  const auto initialCurves = model.getModelObjects<CurveQuadratic>().size();
  auto defaultCurve = rack.compressorRackCOPFunctionofTemperatureCurve();
  ASSERT_TRUE(defaultCurve.optionalCast<CurveQuadratic>());

  CurveQuadratic fanCurve(model);
  ASSERT_TRUE(fanCurve.setCoefficient1Constant(1.0));
  ASSERT_TRUE(fanCurve.setCoefficient2x(0.1));
  ASSERT_TRUE(fanCurve.setCoefficient3xPOW2(0.01));
  ASSERT_TRUE(fanCurve.setMinimumValueofx(0.0));
  ASSERT_TRUE(fanCurve.setMaximumValueofx(10.0));
  ASSERT_TRUE(rack.setCondenserFanPowerFunctionofTemperatureCurve(fanCurve));

  EXPECT_FALSE(rack.remove().empty());
  EXPECT_FALSE(model.getModelObject<CurveQuadratic>(defaultCurve.handle()));
  EXPECT_FALSE(model.getModelObject<CurveQuadratic>(fanCurve.handle()));
  EXPECT_EQ(initialRacks - 1u, model.getModelObjects<RefrigerationCompressorRack>().size());
  EXPECT_EQ(initialCurves - 1u, model.getModelObjects<CurveQuadratic>().size());
}

TEST_F(EPModelFixture, RefrigerationCompressorRack_Remove_PreservesReferencedSchedules) {
  Model model;
  RefrigerationCompressorRack rack(model);
  ScheduleConstant outletSchedule(model);
  ScheduleConstant evaporativeSchedule(model);

  ASSERT_TRUE(outletSchedule.setValue(31.0));
  ASSERT_TRUE(evaporativeSchedule.setValue(1.0));
  ASSERT_TRUE(rack.setWaterCooledCondenserOutletTemperatureSchedule(outletSchedule));
  ASSERT_TRUE(rack.setEvaporativeCondenserAvailabilitySchedule(evaporativeSchedule));
  EXPECT_EQ(1u, model.getModelObjects<RefrigerationCompressorRack>().size());
  EXPECT_EQ(2u, model.getModelObjects<Schedule>().size());

  rack.remove();

  EXPECT_TRUE(model.getModelObjects<RefrigerationCompressorRack>().empty());
  EXPECT_EQ(2u, model.getModelObjects<Schedule>().size());
}
