/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/AirLoopHVAC_Impl.hpp"
#include "../ModelObject/AirLoopHVACDedicatedOutdoorAirSystem.hpp"
#include "../ModelObject/Branch.hpp"
#include "../ModelObject/BranchList.hpp"
#include "../ModelObject/CoilSystemCoolingDX.hpp"
#include "../ModelObject/CoilSystemCoolingDX_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXTwoSpeed_Impl.hpp"
#include "../StraightComponent/Duct.hpp"
#include "../StraightComponent/FanSystemModel.hpp"
#include "../StraightComponent/FanSystemModel_Impl.hpp"
#include "../StraightComponent/Node.hpp"

#include <utilities/idd/CoilSystem_Cooling_DX_FieldEnums.hxx>

#include <algorithm>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  EXPECT_EQ(CoilCoolingDXTwoSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());

  ASSERT_TRUE(coil.totalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  ASSERT_TRUE(coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());

  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());

  const auto children = coil.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
  EXPECT_EQ(coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[5].handle());
  EXPECT_EQ(coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle(), children[6].handle());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  ASSERT_FALSE(CoilCoolingDXTwoSpeed::condenserTypeValues().empty());

  EXPECT_TRUE(coil.setRatedHighSpeedTotalCoolingCapacity(10000.0));
  ASSERT_TRUE(coil.ratedHighSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(10000.0, coil.ratedHighSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedHighSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedSensibleHeatRatio(0.72));
  ASSERT_TRUE(coil.ratedHighSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.72, coil.ratedHighSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedHighSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedCOP(3.6));
  EXPECT_DOUBLE_EQ(3.6, coil.ratedHighSpeedCOP());

  EXPECT_TRUE(coil.setRatedHighSpeedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedHighSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, coil.ratedHighSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedHighSpeedAirFlowRateAutosized());
  coil.autosizeRatedHighSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017(700.0));
  EXPECT_DOUBLE_EQ(700.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023(900.0));
  EXPECT_DOUBLE_EQ(900.0, coil.ratedHighSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setRatedLowSpeedTotalCoolingCapacity(4200.0));
  ASSERT_TRUE(coil.ratedLowSpeedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(4200.0, coil.ratedLowSpeedTotalCoolingCapacity().get());
  EXPECT_FALSE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  coil.autosizeRatedLowSpeedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedSensibleHeatRatio(0.66));
  ASSERT_TRUE(coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.66, coil.ratedLowSpeedSensibleHeatRatio().get());
  EXPECT_FALSE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());
  coil.autosizeRatedLowSpeedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedLowSpeedSensibleHeatRatioAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedCOP(2.9));
  EXPECT_DOUBLE_EQ(2.9, coil.ratedLowSpeedCOP());

  EXPECT_TRUE(coil.setRatedLowSpeedAirFlowRate(0.85));
  ASSERT_TRUE(coil.ratedLowSpeedAirFlowRate());
  EXPECT_DOUBLE_EQ(0.85, coil.ratedLowSpeedAirFlowRate().get());
  EXPECT_FALSE(coil.isRatedLowSpeedAirFlowRateAutosized());
  coil.autosizeRatedLowSpeedAirFlowRate();
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017(650.0));
  EXPECT_DOUBLE_EQ(650.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023(850.0));
  EXPECT_DOUBLE_EQ(850.0, coil.ratedLowSpeedEvaporatorFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setCondenserType("EvaporativelyCooled"));
  EXPECT_EQ("EvaporativelyCooled", coil.condenserType());

  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserEffectiveness(0.82));
  EXPECT_DOUBLE_EQ(0.82, coil.highSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserAirFlowRate(0.40));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.40, coil.highSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setHighSpeedEvaporativeCondenserPumpRatedPowerConsumption(125.0));
  ASSERT_TRUE(coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(125.0, coil.highSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeHighSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isHighSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserEffectiveness(0.79));
  EXPECT_DOUBLE_EQ(0.79, coil.lowSpeedEvaporativeCondenserEffectiveness());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserAirFlowRate(0.30));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserAirFlowRate());
  EXPECT_DOUBLE_EQ(0.30, coil.lowSpeedEvaporativeCondenserAirFlowRate().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserAirFlowRate();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserAirFlowRateAutosized());
  EXPECT_TRUE(coil.setLowSpeedEvaporativeCondenserPumpRatedPowerConsumption(95.0));
  ASSERT_TRUE(coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption());
  EXPECT_DOUBLE_EQ(95.0, coil.lowSpeedEvaporativeCondenserPumpRatedPowerConsumption().get());
  EXPECT_FALSE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());
  coil.autosizeLowSpeedEvaporativeCondenserPumpRatedPowerConsumption();
  EXPECT_TRUE(coil.isLowSpeedEvaporativeCondenserPumpRatedPowerConsumptionAutosized());

  EXPECT_TRUE(coil.setBasinHeaterCapacity(25.0));
  EXPECT_DOUBLE_EQ(25.0, coil.basinHeaterCapacity());
  EXPECT_TRUE(coil.setBasinHeaterSetpointTemperature(3.5));
  EXPECT_DOUBLE_EQ(3.5, coil.basinHeaterSetpointTemperature());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-10.0));
  EXPECT_DOUBLE_EQ(-10.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(coil.setUnitInternalStaticAirPressure(710.0));
  EXPECT_DOUBLE_EQ(710.0, coil.unitInternalStaticAirPressure());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXTwoSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.75));

  CurveBiquadratic totalCoolingTemp(model);
  CurveQuadratic totalCoolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveBiquadratic lowSpeedTemp(model);
  CurveBiquadratic lowSpeedEirTemp(model);

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(totalCoolingTemp));
  EXPECT_EQ(totalCoolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(totalCoolingFlow));
  EXPECT_EQ(totalCoolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(eirTemp));
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(eirFlow));
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.setLowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve(lowSpeedTemp));
  EXPECT_EQ(lowSpeedTemp.handle(), coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setLowSpeedEnergyInputRatioFunctionOfTemperatureCurve(lowSpeedEirTemp));
  EXPECT_EQ(lowSpeedEirTemp.handle(), coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle());

  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(7u, children.size());
  EXPECT_EQ(totalCoolingTemp.handle(), children[0].handle());
  EXPECT_EQ(totalCoolingFlow.handle(), children[1].handle());
  EXPECT_EQ(eirTemp.handle(), children[2].handle());
  EXPECT_EQ(eirFlow.handle(), children[3].handle());
  EXPECT_EQ(plf.handle(), children[4].handle());
  EXPECT_EQ(lowSpeedTemp.handle(), children[5].handle());
  EXPECT_EQ(lowSpeedEirTemp.handle(), children[6].handle());

  coil.resetBasinHeaterOperatingSchedule();
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.6));

  CurveBiquadratic totalCoolingTemp(model);
  CurveQuadratic totalCoolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveBiquadratic lowSpeedTemp(model);
  CurveBiquadratic lowSpeedEirTemp(model);

  CoilCoolingDXTwoSpeed coil(model, availability, totalCoolingTemp, totalCoolingFlow, eirTemp, eirFlow, plf, lowSpeedTemp, lowSpeedEirTemp);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(totalCoolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(totalCoolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_EQ(lowSpeedTemp.handle(), coil.lowSpeedTotalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(lowSpeedEirTemp.handle(), coil.lowSpeedEnergyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.isRatedHighSpeedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedHighSpeedSensibleHeatRatioAutosized());
  EXPECT_TRUE(coil.isRatedHighSpeedAirFlowRateAutosized());
  EXPECT_TRUE(coil.isRatedLowSpeedTotalCoolingCapacityAutosized());
  ASSERT_TRUE(coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.69, *coil.ratedLowSpeedSensibleHeatRatio());
  EXPECT_TRUE(coil.isRatedLowSpeedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_AddToNodeDirectSupplyAndRejectsOrdinaryOutdoorAir) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  CoilCoolingDXTwoSpeed supplyCoil(model);
  CoilCoolingDXTwoSpeed demandCoil(model);
  CoilCoolingDXTwoSpeed oaCoil(model);

  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(supplyCoil.addToNode(supplyInletNode));
  ASSERT_TRUE(supplyCoil.inletModelObject());
  EXPECT_EQ(supplyInletNode, supplyCoil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(supplyCoil.outletModelObject());
  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  ASSERT_TRUE(systems.front().coolingCoil());
  EXPECT_EQ(supplyCoil.handle(), systems.front().coolingCoil()->handle());
  ASSERT_TRUE(systems.front().inletModelObject());
  ASSERT_TRUE(systems.front().outletModelObject());
  ASSERT_TRUE(systems.front().sensorNode());
  EXPECT_EQ(supplyCoil.inletModelObject()->handle(), systems.front().inletModelObject()->handle());
  EXPECT_EQ(supplyCoil.outletModelObject()->handle(), systems.front().outletModelObject()->handle());
  EXPECT_EQ(systems.front().outletModelObject()->handle(), systems.front().sensorNode()->handle());
  EXPECT_TRUE(airLoop.supplyComponent(supplyCoil.handle()));
  EXPECT_FALSE(airLoop.supplyComponent(systems.front().handle()));

  auto demandInletNode = airLoop.demandInletNode();
  EXPECT_FALSE(demandCoil.addToNode(demandInletNode));
  EXPECT_FALSE(demandCoil.airLoopHVAC());

  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);
  EXPECT_FALSE(oaCoil.addToNode(*outboardOANode));
  EXPECT_FALSE(oaCoil.airLoopHVAC());
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_DedicatedOutdoorAirAdapterLifecycle) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-two-speed-dx-doas-adapter.idf");

  Model model;
  AirLoopHVACOutdoorAirSystem dedicatedOA(model);
  ASSERT_TRUE(dedicatedOA.setName("Two Speed DX Dedicated OA"));
  AirLoopHVACDedicatedOutdoorAirSystem doas(dedicatedOA);

  CoilCoolingDXTwoSpeed coil(model);
  ASSERT_TRUE(coil.setName("Dedicated Two Speed DX Coil"));
  auto outboardNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outboardNode);
  ASSERT_TRUE(coil.addToNode(*outboardNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  ASSERT_TRUE(system.coolingCoil());
  EXPECT_EQ(coil.handle(), system.coolingCoil()->handle());
  ASSERT_TRUE(system.sensorNode());
  ASSERT_TRUE(coil.outletModelObject());
  EXPECT_EQ(coil.outletModelObject()->handle(), system.sensorNode()->handle());
  ASSERT_TRUE(coil.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA.handle(), coil.airLoopHVACOutdoorAirSystem()->handle());
  ASSERT_TRUE(system.airLoopHVACOutdoorAirSystem());
  EXPECT_EQ(dedicatedOA.handle(), system.airLoopHVACOutdoorAirSystem()->handle());
  EXPECT_TRUE(dedicatedOA.oaComponent(coil.handle()));
  EXPECT_FALSE(dedicatedOA.oaComponent(system.handle()));
  EXPECT_EQ(1u, dedicatedOA.oaComponents(openstudio::IddObjectType::Coil_Cooling_DX_TwoSpeed).size());
  EXPECT_TRUE(dedicatedOA.oaComponents(openstudio::IddObjectType::CoilSystem_Cooling_DX).empty());

  FanSystemModel fan(model);
  ASSERT_TRUE(fan.setName("Dedicated OA Fan"));
  outboardNode = dedicatedOA.outboardOANode();
  ASSERT_TRUE(outboardNode);
  ASSERT_TRUE(fan.addToNode(*outboardNode));
  ASSERT_TRUE(fan.outletModelObject());
  ASSERT_TRUE(coil.inletModelObject());
  ASSERT_TRUE(system.inletModelObject());
  EXPECT_EQ(fan.outletModelObject()->handle(), coil.inletModelObject()->handle());
  EXPECT_EQ(coil.inletModelObject()->handle(), system.inletModelObject()->handle());
  ASSERT_TRUE(coil.outletModelObject());
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.sensorNode());
  EXPECT_EQ(coil.outletModelObject()->handle(), system.outletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), system.sensorNode()->handle());

  auto publicPath = dedicatedOA.oaComponents();
  const auto fanIt = std::ranges::find(publicPath, fan.cast<ModelObject>());
  const auto coilIt = std::ranges::find(publicPath, coil.cast<ModelObject>());
  ASSERT_NE(publicPath.end(), fanIt);
  ASSERT_NE(publicPath.end(), coilIt);
  EXPECT_LT(std::distance(publicPath.begin(), fanIt), std::distance(publicPath.begin(), coilIt));
  EXPECT_EQ(publicPath.end(), std::ranges::find(publicPath, system.cast<ModelObject>()));

  ASSERT_TRUE(model.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedOA = loadedModel->getConcreteModelObjectByName<AirLoopHVACOutdoorAirSystem>("Two Speed DX Dedicated OA");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXTwoSpeed>("Dedicated Two Speed DX Coil");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingDX>("Dedicated Two Speed DX Coil CoilSystem");
  auto loadedFan = loadedModel->getConcreteModelObjectByName<FanSystemModel>("Dedicated OA Fan");
  ASSERT_TRUE(loadedOA);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedFan);
  EXPECT_TRUE(loadedOA->oaComponent(loadedCoil->handle()));
  EXPECT_FALSE(loadedOA->oaComponent(loadedSystem->handle()));
  EXPECT_EQ(1u, loadedOA->oaComponents(openstudio::IddObjectType::Coil_Cooling_DX_TwoSpeed).size());
  ASSERT_TRUE(loadedSystem->sensorNode());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  EXPECT_EQ(loadedCoil->outletModelObject()->handle(), loadedSystem->sensorNode()->handle());

  ASSERT_TRUE(loadedFan->removeFromLoop());
  ASSERT_TRUE(loadedCoil->inletModelObject());
  ASSERT_TRUE(loadedSystem->inletModelObject());
  EXPECT_EQ(loadedCoil->inletModelObject()->handle(), loadedSystem->inletModelObject()->handle());
  EXPECT_TRUE(loadedOA->oaComponents(openstudio::IddObjectType::Fan_SystemModel).empty());
  ASSERT_TRUE(loadedCoil->removeFromLoop());
  EXPECT_TRUE(loadedOA->oaComponents(openstudio::IddObjectType::Coil_Cooling_DX_TwoSpeed).empty());
  EXPECT_FALSE(loadedCoil->inletModelObject());
  EXPECT_FALSE(loadedSystem->inletModelObject());
  EXPECT_FALSE(loadedSystem->sensorNode());

  auto loadedOutboardNode = loadedOA->outboardOANode();
  ASSERT_TRUE(loadedOutboardNode);
  ASSERT_TRUE(loadedCoil->addToNode(*loadedOutboardNode));
  EXPECT_EQ(1u, loadedModel->getConcreteModelObjects<CoilSystemCoolingDX>().size());
  EXPECT_TRUE(loadedOA->oaComponent(loadedCoil->handle()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_DualDuctAdapterLifecycleAcrossReloadAndAirLoopRemoval) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-two-speed-dx-adapter.idf");

  Model model;
  AirLoopHVAC airLoop(model, true);
  ASSERT_TRUE(airLoop.setName("DX Adapter Dual Duct Loop"));
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());

  Duct hotDeckDuct(model);
  ASSERT_TRUE(hotDeckDuct.setName("DX Adapter Hot Deck Duct"));
  ASSERT_TRUE(hotDeckDuct.addToNode(deckOutlets[0]));

  CoilCoolingDXTwoSpeed coil(model);
  ASSERT_TRUE(coil.setName("DX Adapter Two Speed Coil"));
  ASSERT_TRUE(coil.addToNode(deckOutlets[1]));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  ASSERT_TRUE(system.coolingCoil());
  EXPECT_EQ(coil.handle(), system.coolingCoil()->handle());
  ASSERT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(airLoop.handle(), coil.airLoopHVAC()->handle());
  EXPECT_TRUE(system.airLoopHVAC());

  ScheduleConstant alternateAvailability(model);
  ASSERT_TRUE(alternateAvailability.setValue(0.8));
  ASSERT_TRUE(coil.setAvailabilitySchedule(alternateAvailability));
  auto systemAvailability = system.getTarget(openstudio::CoilSystem_Cooling_DXFields::AvailabilityScheduleName);
  ASSERT_TRUE(systemAvailability);
  EXPECT_EQ(alternateAvailability.handle(), systemAvailability->handle());

  Duct coldDeckDuct(model);
  ASSERT_TRUE(coldDeckDuct.setName("DX Adapter Cold Deck Duct"));
  ASSERT_TRUE(coldDeckDuct.addToNode(deckOutlets[1]));
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_TRUE(system.sensorNode());
  ASSERT_TRUE(coil.outletModelObject());
  ASSERT_TRUE(coldDeckDuct.inletModelObject());
  EXPECT_EQ(system.outletModelObject()->handle(), coil.outletModelObject()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), system.sensorNode()->handle());
  EXPECT_EQ(system.outletModelObject()->handle(), coldDeckDuct.inletModelObject()->handle());

  auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  ASSERT_EQ(1u, branches[1].components().size());
  EXPECT_EQ(hotDeckDuct.handle(), branches[1].components().front().handle());
  ASSERT_EQ(2u, branches[2].components().size());
  EXPECT_EQ(system.handle(), branches[2].components().front().handle());
  EXPECT_EQ(coldDeckDuct.handle(), branches[2].components().back().handle());

  auto coldPath = airLoop.supplyComponents(airLoop.supplyInletNode(), deckOutlets[1]);
  EXPECT_NE(coldPath.end(), std::ranges::find(coldPath, coil.cast<ModelObject>()));
  EXPECT_EQ(coldPath.end(), std::ranges::find(coldPath, system.cast<ModelObject>()));

  EXPECT_TRUE(coil.removeFromLoop());
  EXPECT_TRUE(hotDeckDuct.airLoopHVAC());
  EXPECT_TRUE(coldDeckDuct.airLoopHVAC());
  EXPECT_FALSE(coil.airLoopHVAC());
  EXPECT_FALSE(system.airLoopHVAC());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
  EXPECT_FALSE(system.inletModelObject());
  EXPECT_FALSE(system.outletModelObject());
  EXPECT_FALSE(system.sensorNode());
  ASSERT_EQ(1u, branches[2].components().size());
  EXPECT_EQ(coldDeckDuct.handle(), branches[2].components().front().handle());

  ASSERT_TRUE(coil.addToNode(deckOutlets[1]));
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilSystemCoolingDX>().size());
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("DX Adapter Dual Duct Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXTwoSpeed>("DX Adapter Two Speed Coil");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingDX>("DX Adapter Two Speed Coil CoilSystem");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedSystem->coolingCoil());
  EXPECT_EQ(loadedCoil->handle(), loadedSystem->coolingCoil()->handle());
  EXPECT_TRUE(loadedLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_FALSE(loadedLoop->supplyComponent(loadedSystem->handle()));
  ASSERT_TRUE(loadedSystem->sensorNode());
  ASSERT_TRUE(loadedCoil->outletModelObject());
  EXPECT_EQ(loadedCoil->outletModelObject()->handle(), loadedSystem->sensorNode()->handle());

  const auto loadedCoilHandle = loadedCoil->handle();
  const auto loadedSystemHandle = loadedSystem->handle();
  EXPECT_FALSE(loadedLoop->remove().empty());
  EXPECT_FALSE(loadedModel->getObject(loadedCoilHandle));
  EXPECT_FALSE(loadedModel->getObject(loadedSystemHandle));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RejectsAmbiguousAdaptersWithoutBranchMutation) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());
  CoilCoolingDXTwoSpeed coil(model);
  CoilSystemCoolingDX firstSystem(model);
  CoilSystemCoolingDX secondSystem(model);

  for (auto* system : {&firstSystem, &secondSystem}) {
    ASSERT_TRUE(system->setCoolingCoilObjectType(coil.iddObject().name()));
    ASSERT_TRUE(system->setPointer(openstudio::CoilSystem_Cooling_DXFields::CoolingCoilName, coil.handle()));
  }

  const auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  EXPECT_TRUE(branches[2].components().empty());
  EXPECT_FALSE(coil.addToNode(deckOutlets[1]));
  EXPECT_TRUE(branches[2].components().empty());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
  EXPECT_TRUE(model.getObject(firstSystem.handle()));
  EXPECT_TRUE(model.getObject(secondSystem.handle()));
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_MalformedPersistedAdapterIsNotProjected) {
  const auto idfPath = openstudio::tempDir() / openstudio::toPath("epmodel-two-speed-dx-malformed-adapter.idf");

  Model model;
  AirLoopHVAC airLoop(model);
  ASSERT_TRUE(airLoop.setName("Malformed DX Adapter Loop"));
  CoilCoolingDXTwoSpeed coil(model);
  ASSERT_TRUE(coil.setName("Malformed DX Adapter Coil"));
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  ASSERT_TRUE(system.inletModelObject());
  ASSERT_TRUE(system.outletModelObject());
  ASSERT_NE(system.inletModelObject()->handle(), system.outletModelObject()->handle());
  ASSERT_TRUE(system.setPointer(openstudio::CoilSystem_Cooling_DXFields::DXCoolingCoilSystemSensorNodeName, system.inletModelObject()->handle()));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedLoop = loadedModel->getConcreteModelObjectByName<AirLoopHVAC>("Malformed DX Adapter Loop");
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXTwoSpeed>("Malformed DX Adapter Coil");
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<CoilSystemCoolingDX>("Malformed DX Adapter Coil CoilSystem");
  ASSERT_TRUE(loadedLoop);
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedSystem);
  EXPECT_TRUE(loadedLoop->supplyComponent(loadedSystem->handle()));
  EXPECT_FALSE(loadedLoop->supplyComponent(loadedCoil->handle()));
  EXPECT_TRUE(loadedSystem->airLoopHVAC());
  EXPECT_FALSE(loadedCoil->airLoopHVAC());
  EXPECT_FALSE(loadedCoil->removeFromLoop());
  EXPECT_FALSE(loadedSystem->removeFromLoop());
  EXPECT_TRUE(loadedSystem->remove().empty());
  EXPECT_TRUE(loadedModel->getObject(loadedSystem->handle()));

  openstudio::filesystem::remove(idfPath);
}

TEST_F(EPModelFixture, CoilCoolingDXTwoSpeed_RemoveDeletesAdapterAndPreservesAdjacentDeckComponents) {
  Model model;
  AirLoopHVAC airLoop(model, true);
  auto deckOutlets = airLoop.supplyOutletNodes();
  ASSERT_EQ(2u, deckOutlets.size());

  Duct hotDeckDuct(model);
  ASSERT_TRUE(hotDeckDuct.addToNode(deckOutlets[0]));
  CoilCoolingDXTwoSpeed coil(model);
  ASSERT_TRUE(coil.addToNode(deckOutlets[1]));
  Duct coldDeckDuct(model);
  ASSERT_TRUE(coldDeckDuct.addToNode(deckOutlets[1]));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  const auto coilHandle = coil.handle();
  const auto systemHandle = systems.front().handle();
  EXPECT_FALSE(coil.remove().empty());
  EXPECT_FALSE(model.getObject(coilHandle));
  EXPECT_FALSE(model.getObject(systemHandle));
  EXPECT_TRUE(hotDeckDuct.airLoopHVAC());
  EXPECT_TRUE(coldDeckDuct.airLoopHVAC());

  const auto branches = airLoop.getImpl<detail::AirLoopHVAC_Impl>()->branchList().branches();
  ASSERT_EQ(3u, branches.size());
  ASSERT_EQ(1u, branches[2].components().size());
  EXPECT_EQ(coldDeckDuct.handle(), branches[2].components().front().handle());
}

TEST_F(EPModelFixture, CoilSystemCoolingDX_DirectRemovalDetachesChildAndHealsBranch) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilCoolingDXTwoSpeed coil(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(coil.addToNode(supplyInletNode));
  Duct downstreamDuct(model);
  ASSERT_TRUE(downstreamDuct.addToNode(supplyInletNode));

  auto systems = model.getConcreteModelObjects<CoilSystemCoolingDX>();
  ASSERT_EQ(1u, systems.size());
  auto system = systems.front();
  const auto systemHandle = system.handle();
  EXPECT_FALSE(system.remove().empty());
  EXPECT_FALSE(model.getObject(systemHandle));
  EXPECT_TRUE(model.getObject(coil.handle()));
  EXPECT_FALSE(coil.airLoopHVAC());
  EXPECT_FALSE(coil.inletModelObject());
  EXPECT_FALSE(coil.outletModelObject());
  EXPECT_TRUE(downstreamDuct.airLoopHVAC());

  EXPECT_TRUE(coil.addToNode(supplyInletNode));
  EXPECT_TRUE(coil.airLoopHVAC());
  EXPECT_EQ(1u, model.getConcreteModelObjects<CoilSystemCoolingDX>().size());
}
