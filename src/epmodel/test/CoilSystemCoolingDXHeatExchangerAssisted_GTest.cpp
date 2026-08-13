/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>

#include "EPModelFixture.hpp"
#include "../AirToAirComponent/HeatExchangerAirToAirSensibleAndLatent.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow.hpp"
#include "../AirToAirComponent/HeatExchangerDesiccantBalancedFlow_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1.hpp"
#include "../ResourceObject/HeatExchangerDesiccantBalancedFlowPerformanceDataType1_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted.hpp"
#include "../StraightComponent/CoilSystemCoolingDXHeatExchangerAssisted_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXVariableSpeed.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/AirLoopHVACUnitarySystem.hpp"

#include <utilities/idd/CoilSystem_Cooling_DX_HeatExchangerAssisted_FieldEnums.hxx>

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

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_RenamedSystemsKeepDistinctContainedAirPaths) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted firstSystem(model);
  auto firstHeatExchanger = firstSystem.heatExchanger();
  ASSERT_TRUE(firstHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(firstHeatExchanger.secondaryAirInletModelObject());
  const auto firstSupplyConnectorHandle = firstHeatExchanger.primaryAirOutletModelObject()->handle();
  const auto firstExhaustConnectorHandle = firstHeatExchanger.secondaryAirInletModelObject()->handle();
  ASSERT_TRUE(firstSystem.setName("Renamed Assisted DX Coil System"));

  CoilSystemCoolingDXHeatExchangerAssisted secondSystem(model);
  auto secondHeatExchanger = secondSystem.heatExchanger();
  ASSERT_TRUE(secondHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(secondHeatExchanger.secondaryAirInletModelObject());

  EXPECT_NE(firstSupplyConnectorHandle, secondHeatExchanger.primaryAirOutletModelObject()->handle());
  EXPECT_NE(firstExhaustConnectorHandle, secondHeatExchanger.secondaryAirInletModelObject()->handle());
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_ScalarAccessors_RoundTrip) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model);

  const auto heatExchangerObjectTypes = CoilSystemCoolingDXHeatExchangerAssisted::heatExchangerObjectTypeValues();
  EXPECT_FALSE(heatExchangerObjectTypes.empty());
  EXPECT_TRUE(std::find(heatExchangerObjectTypes.begin(), heatExchangerObjectTypes.end(), "HeatExchanger:AirToAir:SensibleAndLatent")
              != heatExchangerObjectTypes.end());

  const auto coolingCoilObjectTypes = CoilSystemCoolingDXHeatExchangerAssisted::coolingCoilObjectTypeValues();
  EXPECT_FALSE(coolingCoilObjectTypes.empty());
  EXPECT_TRUE(std::find(coolingCoilObjectTypes.begin(), coolingCoilObjectTypes.end(), "Coil:Cooling:DX:SingleSpeed") != coolingCoilObjectTypes.end());

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

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_RelationshipChangesPreserveContainedAirPath) {
  Model model;
  HeatExchangerDesiccantBalancedFlow originalHeatExchanger(model);
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model, originalHeatExchanger);
  auto originalCoolingCoil = coilSystem.coolingCoil();
  AirLoopHVACUnitarySystem unitary(model);

  ASSERT_TRUE(coilSystem.setName("Assisted DX Coil System"));
  ASSERT_TRUE(unitary.setCoolingCoil(coilSystem));
  ASSERT_TRUE(unitary.inletNode());
  ASSERT_TRUE(unitary.outletNode());
  ASSERT_TRUE(coilSystem.inletModelObject());
  ASSERT_TRUE(coilSystem.outletModelObject());
  EXPECT_EQ(unitary.inletNode()->handle(), coilSystem.inletModelObject()->handle());
  EXPECT_EQ(unitary.outletNode()->handle(), coilSystem.outletModelObject()->handle());
  ASSERT_TRUE(originalHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(originalHeatExchanger.secondaryAirInletModelObject());
  ASSERT_TRUE(originalCoolingCoil.inletModelObject());
  ASSERT_TRUE(originalCoolingCoil.outletModelObject());
  EXPECT_EQ(originalHeatExchanger.primaryAirOutletModelObject()->handle(), originalCoolingCoil.inletModelObject()->handle());
  EXPECT_EQ(originalCoolingCoil.outletModelObject()->handle(), originalHeatExchanger.secondaryAirInletModelObject()->handle());

  auto supplyConnector = originalHeatExchanger.primaryAirOutletModelObject()->optionalCast<Node>();
  auto exhaustConnector = originalHeatExchanger.secondaryAirInletModelObject()->optionalCast<Node>();
  ASSERT_TRUE(supplyConnector);
  ASSERT_TRUE(exhaustConnector);
  ASSERT_TRUE(supplyConnector->setName("Custom Assisted DX Supply Connector"));
  ASSERT_TRUE(exhaustConnector->setName("Custom Assisted DX Exhaust Connector"));
  const auto supplyConnectorHandle = supplyConnector->handle();
  const auto exhaustConnectorHandle = exhaustConnector->handle();
  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  ASSERT_TRUE(originalHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(originalHeatExchanger.secondaryAirInletModelObject());
  EXPECT_EQ(supplyConnectorHandle, originalHeatExchanger.primaryAirOutletModelObject()->handle());
  EXPECT_EQ(exhaustConnectorHandle, originalHeatExchanger.secondaryAirInletModelObject()->handle());
  EXPECT_EQ("Custom Assisted DX Supply Connector", originalHeatExchanger.primaryAirOutletModelObject()->nameString());
  EXPECT_EQ("Custom Assisted DX Exhaust Connector", originalHeatExchanger.secondaryAirInletModelObject()->nameString());

  HeatExchangerAirToAirSensibleAndLatent replacementHeatExchanger(model);
  ASSERT_TRUE(coilSystem.setHeatExchanger(replacementHeatExchanger));
  EXPECT_FALSE(originalHeatExchanger.primaryAirInletModelObject());
  EXPECT_FALSE(originalHeatExchanger.primaryAirOutletModelObject());
  EXPECT_FALSE(originalHeatExchanger.secondaryAirInletModelObject());
  EXPECT_FALSE(originalHeatExchanger.secondaryAirOutletModelObject());
  ASSERT_TRUE(replacementHeatExchanger.primaryAirInletModelObject());
  ASSERT_TRUE(replacementHeatExchanger.primaryAirOutletModelObject());
  ASSERT_TRUE(replacementHeatExchanger.secondaryAirInletModelObject());
  ASSERT_TRUE(replacementHeatExchanger.secondaryAirOutletModelObject());
  EXPECT_EQ(unitary.inletNode()->handle(), replacementHeatExchanger.primaryAirInletModelObject()->handle());
  EXPECT_EQ(unitary.outletNode()->handle(), replacementHeatExchanger.secondaryAirOutletModelObject()->handle());

  CoilCoolingDXVariableSpeed replacementCoolingCoil(model);
  ASSERT_TRUE(coilSystem.setCoolingCoil(replacementCoolingCoil));
  EXPECT_FALSE(originalCoolingCoil.inletModelObject());
  EXPECT_FALSE(originalCoolingCoil.outletModelObject());
  ASSERT_TRUE(replacementCoolingCoil.inletModelObject());
  ASSERT_TRUE(replacementCoolingCoil.outletModelObject());
  EXPECT_EQ(replacementHeatExchanger.primaryAirOutletModelObject()->handle(), replacementCoolingCoil.inletModelObject()->handle());
  EXPECT_EQ(replacementCoolingCoil.outletModelObject()->handle(), replacementHeatExchanger.secondaryAirInletModelObject()->handle());

  Model foreignModel;
  HeatExchangerDesiccantBalancedFlow foreignHeatExchanger(foreignModel);
  CoilCoolingDXVariableSpeed foreignCoolingCoil(foreignModel);
  const auto heatExchangerType = coilSystem.heatExchangerObjectType();
  const auto coolingCoilType = coilSystem.coolingCoilObjectType();
  EXPECT_FALSE(coilSystem.setHeatExchanger(foreignHeatExchanger));
  EXPECT_FALSE(coilSystem.setCoolingCoil(foreignCoolingCoil));
  EXPECT_EQ(replacementHeatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_EQ(replacementCoolingCoil.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(heatExchangerType, coilSystem.heatExchangerObjectType());
  EXPECT_EQ(coolingCoilType, coilSystem.coolingCoilObjectType());
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_ForeignConstructorLeavesNoResidue) {
  Model model;
  Model foreignModel;
  HeatExchangerDesiccantBalancedFlow foreignHeatExchanger(foreignModel);

  const auto coilSystemCount = model.getConcreteModelObjects<CoilSystemCoolingDXHeatExchangerAssisted>().size();
  const auto coolingCoilCount = model.getConcreteModelObjects<CoilCoolingDXSingleSpeed>().size();
  EXPECT_THROW(CoilSystemCoolingDXHeatExchangerAssisted(model, foreignHeatExchanger), std::invalid_argument);
  EXPECT_EQ(coilSystemCount, model.getConcreteModelObjects<CoilSystemCoolingDXHeatExchangerAssisted>().size());
  EXPECT_EQ(coolingCoilCount, model.getConcreteModelObjects<CoilCoolingDXSingleSpeed>().size());
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_CanonicalizeRepairsRequiredChildren) {
  Model model;
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model);
  const auto originalHeatExchanger = coilSystem.heatExchanger();
  const auto originalCoolingCoil = coilSystem.coolingCoil();

  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerName, openstudio::Handle()));
  ASSERT_TRUE(coilSystem.setPointer(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilName, openstudio::Handle()));
  ASSERT_TRUE(coilSystem.setString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::HeatExchangerObjectType,
                                   "HeatExchanger:Desiccant:BalancedFlow"));
  ASSERT_TRUE(
    coilSystem.setString(openstudio::CoilSystem_Cooling_DX_HeatExchangerAssistedFields::CoolingCoilObjectType, "Coil:Cooling:DX:VariableSpeed"));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_NE(originalHeatExchanger.handle(), coilSystem.heatExchanger().handle());
  EXPECT_NE(originalCoolingCoil.handle(), coilSystem.coolingCoil().handle());
  EXPECT_EQ(coilSystem.heatExchanger().iddObject().name(), coilSystem.heatExchangerObjectType());
  EXPECT_EQ(coilSystem.coolingCoil().iddObject().name(), coilSystem.coolingCoilObjectType());
  ASSERT_TRUE(coilSystem.heatExchanger().primaryAirOutletModelObject());
  ASSERT_TRUE(coilSystem.heatExchanger().secondaryAirInletModelObject());
  ASSERT_TRUE(coilSystem.coolingCoil().inletModelObject());
  ASSERT_TRUE(coilSystem.coolingCoil().outletModelObject());
  EXPECT_EQ(coilSystem.heatExchanger().primaryAirOutletModelObject()->handle(), coilSystem.coolingCoil().inletModelObject()->handle());
  EXPECT_EQ(coilSystem.coolingCoil().outletModelObject()->handle(), coilSystem.heatExchanger().secondaryAirInletModelObject()->handle());

  const auto heatExchangerCount = model.getModelObjects<AirToAirComponent>().size();
  const auto coolingCoilCount = model.getConcreteModelObjects<CoilCoolingDXSingleSpeed>().size();
  const auto secondReport = model.canonicalize();
  EXPECT_EQ(0u, secondReport.errorCount);
  EXPECT_EQ(heatExchangerCount, model.getModelObjects<AirToAirComponent>().size());
  EXPECT_EQ(coolingCoilCount, model.getConcreteModelObjects<CoilCoolingDXSingleSpeed>().size());
}

TEST_F(EPModelFixture, CoilSystemCoolingDXHeatExchangerAssisted_RemoveDeletesOwnedChildren) {
  Model model;
  HeatExchangerDesiccantBalancedFlow heatExchanger(model);
  const auto performance = heatExchanger.heatExchangerPerformance();
  CoilSystemCoolingDXHeatExchangerAssisted coilSystem(model, heatExchanger);
  const auto coolingCoil = coilSystem.coolingCoil().cast<CoilCoolingDXSingleSpeed>();

  EXPECT_FALSE(coilSystem.remove().empty());
  EXPECT_FALSE(model.getModelObject<CoilSystemCoolingDXHeatExchangerAssisted>(coilSystem.handle()));
  EXPECT_FALSE(model.getModelObject<HeatExchangerDesiccantBalancedFlow>(heatExchanger.handle()));
  EXPECT_FALSE(model.getModelObject<HeatExchangerDesiccantBalancedFlowPerformanceDataType1>(performance.handle()));
  EXPECT_FALSE(model.getModelObject<CoilCoolingDXSingleSpeed>(coolingCoil.handle()));
}
