/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include <utilities/data/DataEnums.hpp>
#include <utilities/idd/HeatExchanger_FluidToFluid_FieldEnums.hxx>
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../WaterToWaterComponent/HeatExchangerFluidToFluid.hpp"

#include <limits>

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, HeatExchangerFluidToFluid_DefaultConstructor) {
  Model model;
  HeatExchangerFluidToFluid hx(model);
  EXPECT_EQ(HeatExchangerFluidToFluid::iddObjectType(), hx.iddObject().type());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hx.supplyInletPort());
  EXPECT_NE(std::numeric_limits<unsigned>::max(), hx.demandInletPort());
  EXPECT_FALSE(hx.availabilitySchedule());
  EXPECT_FALSE(hx.componentOverrideLoopSupplySideInletNode());
  EXPECT_FALSE(hx.componentOverrideLoopDemandSideInletNode());

  EXPECT_TRUE(hx.isLoopDemandSideDesignFlowRateAutosized());
  EXPECT_TRUE(hx.isLoopSupplySideDesignFlowRateAutosized());
  EXPECT_EQ("Ideal", hx.heatExchangeModelType());
  EXPECT_TRUE(hx.isHeatExchangerUFactorTimesAreaValueAutosized());
  EXPECT_EQ("UncontrolledOn", hx.controlType());
  EXPECT_DOUBLE_EQ(0.01, hx.minimumTemperatureDifferencetoActivateHeatExchanger());
  EXPECT_EQ("LoopToLoop", hx.heatTransferMeteringEndUseType());
  EXPECT_EQ("Loop", hx.componentOverrideCoolingControlTemperatureMode());
  EXPECT_DOUBLE_EQ(1.0, hx.sizingFactor());
  ASSERT_TRUE(hx.operationMinimumTemperatureLimit());
  EXPECT_DOUBLE_EQ(0.0, *hx.operationMinimumTemperatureLimit());
  ASSERT_TRUE(hx.operationMaximumTemperatureLimit());
  EXPECT_DOUBLE_EQ(100.0, *hx.operationMaximumTemperatureLimit());
}

TEST_F(EPModelFixture, HeatExchangerFluidToFluid_RelationshipAccessors_RoundTrip) {
  Model model;
  HeatExchangerFluidToFluid hx(model);
  ScheduleConstant availability(model);
  Node supplyOverride(model);
  Node demandOverride(model);

  EXPECT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(hx.setAvailabilitySchedule(availability));
  ASSERT_TRUE(hx.availabilitySchedule());
  EXPECT_EQ(availability.handle(), hx.availabilitySchedule()->handle());
  hx.resetAvailabilitySchedule();
  EXPECT_FALSE(hx.availabilitySchedule());

  EXPECT_TRUE(hx.setComponentOverrideLoopSupplySideInletNode(supplyOverride));
  ASSERT_TRUE(hx.componentOverrideLoopSupplySideInletNode());
  EXPECT_EQ(supplyOverride.handle(), hx.componentOverrideLoopSupplySideInletNode()->handle());
  hx.resetComponentOverrideLoopSupplySideInletNode();
  EXPECT_FALSE(hx.componentOverrideLoopSupplySideInletNode());

  EXPECT_TRUE(hx.setComponentOverrideLoopDemandSideInletNode(demandOverride));
  ASSERT_TRUE(hx.componentOverrideLoopDemandSideInletNode());
  EXPECT_EQ(demandOverride.handle(), hx.componentOverrideLoopDemandSideInletNode()->handle());
  hx.resetComponentOverrideLoopDemandSideInletNode();
  EXPECT_FALSE(hx.componentOverrideLoopDemandSideInletNode());
}

TEST_F(EPModelFixture, HeatExchangerFluidToFluid_ScalarAccessors_RoundTrip) {
  Model model;
  HeatExchangerFluidToFluid hx(model);

  EXPECT_TRUE(hx.setLoopDemandSideDesignFlowRate(0.11));
  ASSERT_TRUE(hx.loopDemandSideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.11, *hx.loopDemandSideDesignFlowRate());
  hx.autosizeLoopDemandSideDesignFlowRate();
  EXPECT_TRUE(hx.isLoopDemandSideDesignFlowRateAutosized());

  EXPECT_TRUE(hx.setLoopSupplySideDesignFlowRate(0.22));
  ASSERT_TRUE(hx.loopSupplySideDesignFlowRate());
  EXPECT_DOUBLE_EQ(0.22, *hx.loopSupplySideDesignFlowRate());
  hx.autosizeLoopSupplySideDesignFlowRate();
  EXPECT_TRUE(hx.isLoopSupplySideDesignFlowRateAutosized());

  const auto modelTypeValues = HeatExchangerFluidToFluid::heatExchangeModelTypeValues();
  ASSERT_FALSE(modelTypeValues.empty());
  EXPECT_TRUE(hx.setHeatExchangeModelType(modelTypeValues.front()));
  EXPECT_EQ(modelTypeValues.front(), hx.heatExchangeModelType());
  hx.resetHeatExchangeModelType();
  EXPECT_TRUE(hx.isHeatExchangeModelTypeDefaulted());

  EXPECT_TRUE(hx.setHeatExchangerUFactorTimesAreaValue(460.0));
  ASSERT_TRUE(hx.heatExchangerUFactorTimesAreaValue());
  EXPECT_DOUBLE_EQ(460.0, *hx.heatExchangerUFactorTimesAreaValue());
  hx.autosizeHeatExchangerUFactorTimesAreaValue();
  EXPECT_TRUE(hx.isHeatExchangerUFactorTimesAreaValueAutosized());

  const auto controlTypeValues = HeatExchangerFluidToFluid::controlTypeValues();
  ASSERT_FALSE(controlTypeValues.empty());
  EXPECT_TRUE(hx.setControlType(controlTypeValues.front()));
  EXPECT_EQ(controlTypeValues.front(), hx.controlType());
  hx.resetControlType();
  EXPECT_TRUE(hx.isControlTypeDefaulted());

  EXPECT_TRUE(hx.setMinimumTemperatureDifferencetoActivateHeatExchanger(0.25));
  EXPECT_DOUBLE_EQ(0.25, hx.minimumTemperatureDifferencetoActivateHeatExchanger());
  hx.resetMinimumTemperatureDifferencetoActivateHeatExchanger();
  EXPECT_TRUE(hx.isMinimumTemperatureDifferencetoActivateHeatExchangerDefaulted());

  const auto endUseValues = HeatExchangerFluidToFluid::heatTransferMeteringEndUseTypeValues();
  ASSERT_FALSE(endUseValues.empty());
  EXPECT_TRUE(hx.setHeatTransferMeteringEndUseType(endUseValues.front()));
  EXPECT_EQ(endUseValues.front(), hx.heatTransferMeteringEndUseType());
  hx.resetHeatTransferMeteringEndUseType();
  EXPECT_TRUE(hx.isHeatTransferMeteringEndUseTypeDefaulted());

  const auto overrideModeValues = HeatExchangerFluidToFluid::componentOverrideCoolingControlTemperatureModeValues();
  ASSERT_FALSE(overrideModeValues.empty());
  EXPECT_TRUE(hx.setComponentOverrideCoolingControlTemperatureMode(overrideModeValues.front()));
  EXPECT_EQ(overrideModeValues.front(), hx.componentOverrideCoolingControlTemperatureMode());
  hx.resetComponentOverrideCoolingControlTemperatureMode();
  EXPECT_TRUE(hx.isComponentOverrideCoolingControlTemperatureModeDefaulted());

  EXPECT_TRUE(hx.setSizingFactor(1.15));
  EXPECT_DOUBLE_EQ(1.15, hx.sizingFactor());
  hx.resetSizingFactor();
  EXPECT_TRUE(hx.isSizingFactorDefaulted());

  EXPECT_TRUE(hx.setOperationMinimumTemperatureLimit(1.5));
  ASSERT_TRUE(hx.operationMinimumTemperatureLimit());
  EXPECT_DOUBLE_EQ(1.5, *hx.operationMinimumTemperatureLimit());
  hx.resetOperationMinimumTemperatureLimit();
  EXPECT_FALSE(hx.operationMinimumTemperatureLimit());

  EXPECT_TRUE(hx.setOperationMaximumTemperatureLimit(95.0));
  ASSERT_TRUE(hx.operationMaximumTemperatureLimit());
  EXPECT_DOUBLE_EQ(95.0, *hx.operationMaximumTemperatureLimit());
  hx.resetOperationMaximumTemperatureLimit();
  EXPECT_FALSE(hx.operationMaximumTemperatureLimit());
}

TEST_F(EPModelFixture, HeatExchangerFluidToFluid_PlantLoopAttachmentParity) {
  Model model;
  AirLoopHVAC airLoop(model);
  PlantLoop loadLoop(model);
  PlantLoop sourceLoop(model);
  PlantLoop sourceLoop2(model);
  HeatExchangerFluidToFluid hx(model);

  EXPECT_EQ(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideInletNodeName, hx.supplyInletPort());
  EXPECT_EQ(openstudio::HeatExchanger_FluidToFluidFields::LoopSupplySideOutletNodeName, hx.supplyOutletPort());
  EXPECT_EQ(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideInletNodeName, hx.demandInletPort());
  EXPECT_EQ(openstudio::HeatExchanger_FluidToFluidFields::LoopDemandSideOutletNodeName, hx.demandOutletPort());

  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  auto loadSupplyOutletNode = loadLoop.supplyOutletNode();

  EXPECT_FALSE(hx.addToNode(airSupplyOutletNode));
  EXPECT_TRUE(hx.addToNode(loadSupplyOutletNode));
  ASSERT_TRUE(hx.plantLoop());
  EXPECT_EQ(loadLoop, hx.plantLoop().get());
  EXPECT_FALSE(hx.secondaryPlantLoop());
  ASSERT_TRUE(hx.supplyInletModelObject());
  EXPECT_EQ(loadLoop.supplyOutletNode(), hx.supplyInletModelObject()->cast<Node>());
  ASSERT_TRUE(hx.supplyOutletModelObject());
  EXPECT_EQ(loadLoop, hx.supplyOutletModelObject()->cast<Node>().plantLoop().get());
  EXPECT_FALSE(hx.demandInletModelObject());
  EXPECT_FALSE(hx.demandOutletModelObject());

  EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(hx));
  ASSERT_TRUE(hx.secondaryPlantLoop());
  EXPECT_EQ(sourceLoop, hx.secondaryPlantLoop().get());
  ASSERT_TRUE(hx.demandInletModelObject());
  EXPECT_EQ(sourceLoop, hx.demandInletModelObject()->cast<Node>().plantLoop().get());
  ASSERT_TRUE(hx.demandOutletModelObject());
  EXPECT_EQ(sourceLoop, hx.demandOutletModelObject()->cast<Node>().plantLoop().get());

  EXPECT_TRUE(sourceLoop2.addDemandBranchForComponent(hx));
  ASSERT_TRUE(hx.plantLoop());
  EXPECT_EQ(loadLoop, hx.plantLoop().get());
  ASSERT_TRUE(hx.secondaryPlantLoop());
  EXPECT_EQ(sourceLoop2, hx.secondaryPlantLoop().get());
  ASSERT_TRUE(hx.demandInletModelObject());
  EXPECT_EQ(sourceLoop2, hx.demandInletModelObject()->cast<Node>().plantLoop().get());
  ASSERT_TRUE(hx.demandOutletModelObject());
  EXPECT_EQ(sourceLoop2, hx.demandOutletModelObject()->cast<Node>().plantLoop().get());

  EXPECT_TRUE(hx.removeFromSecondaryPlantLoop());
  EXPECT_FALSE(hx.secondaryPlantLoop());
  EXPECT_FALSE(hx.demandInletModelObject());
  EXPECT_FALSE(hx.demandOutletModelObject());

  EXPECT_TRUE(hx.removeFromPlantLoop());
  EXPECT_FALSE(hx.plantLoop());
  EXPECT_FALSE(hx.supplyInletModelObject());
  EXPECT_FALSE(hx.supplyOutletModelObject());
}

TEST_F(EPModelFixture, HeatExchangerFluidToFluid_ComponentClassificationParity) {
  Model model;
  HeatExchangerFluidToFluid hx(model);

  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::None), hx.componentType());
  EXPECT_TRUE(hx.coolingFuelTypes().empty());
  EXPECT_TRUE(hx.heatingFuelTypes().empty());
  EXPECT_TRUE(hx.appGHeatingFuelTypes().empty());

  EXPECT_TRUE(hx.setControlType("HeatingSetpointModulated"));
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Heating), hx.componentType());
  EXPECT_TRUE(hx.coolingFuelTypes().empty());

  EXPECT_TRUE(hx.setControlType("CoolingSetpointModulated"));
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Cooling), hx.componentType());
  EXPECT_TRUE(hx.heatingFuelTypes().empty());
  EXPECT_TRUE(hx.appGHeatingFuelTypes().empty());

  EXPECT_TRUE(hx.setControlType("DualDeadbandSetpointOnOff"));
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Both), hx.componentType());

  EXPECT_TRUE(hx.setControlType("OperationSchemeModulated"));
  EXPECT_EQ(openstudio::ComponentType(openstudio::ComponentType::Both), hx.componentType());
}
