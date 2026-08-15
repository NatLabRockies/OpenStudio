/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveBiquadratic_Impl.hpp"
#include "../Curve/CurveQuadratic.hpp"
#include "../Curve/CurveQuadratic_Impl.hpp"
#include "../Curve/CurveTriquadratic.hpp"
#include "EPModelFixture.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../ModelObject/ModelObject.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilCoolingDXSingleSpeed_Impl.hpp"
#include "../StraightComponent/CoilCoolingDXTwoSpeed.hpp"
#include "../StraightComponent/Node.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/StringHelpers.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Cooling_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_NodeList_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/idf/WorkspaceExtensibleGroup.hpp>

#include <algorithm>
#include <array>
#include <utility>

using namespace openstudio::epmodel;

namespace {

class ScopedFileRemoval
{
 public:
  explicit ScopedFileRemoval(openstudio::path path) : m_path(std::move(path)) {}

  ~ScopedFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueIdfPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}

unsigned outdoorAirNodeListEntryCount(const Model& model, const std::string& nodeName) {
  unsigned result = 0;
  for (const auto& object : model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList)) {
    for (const auto& group : object.extensibleGroups()) {
      auto workspaceGroup = group.optionalCast<openstudio::WorkspaceExtensibleGroup>();
      if (!workspaceGroup) {
        continue;
      }
      const auto value = workspaceGroup->getString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName);
      if (value && openstudio::istringEqual(*value, nodeName)) {
        ++result;
      }
    }
  }
  return result;
}

bool hasOutdoorAirNode(const Model& model, const std::string& nodeName) {
  const auto objects = model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_Node);
  return std::ranges::any_of(objects, [&](const auto& object) { return openstudio::istringEqual(object.nameString(), nodeName); });
}

}  // namespace

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_EQ(CoilCoolingDXSingleSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  EXPECT_TRUE(coil.totalCoolingCapacityFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(coil.energyInputRatioFunctionOfTemperatureCurve().optionalCast<CurveBiquadratic>());
  EXPECT_TRUE(coil.energyInputRatioFunctionOfFlowFractionCurve().optionalCast<CurveQuadratic>());
  EXPECT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());

  const auto children = coil.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionOfFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
  EXPECT_FALSE(coil.condenserAirInletNodeName());
  EXPECT_TRUE(coil.setCondenserAirInletNodeName(std::string{}));
  EXPECT_TRUE(model.getObjectsByType(openstudio::IddObjectType::OutdoorAir_NodeList).empty());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_CondenserAirInletNodeSetReplaceClearAndSharedDeclaration) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  CoilCoolingDXTwoSpeed sibling(model);
  const auto sharedNode = model.getOrCreateTransientByName<Node>("Shared Condenser Inlet");
  const auto sharedNodeHandle = sharedNode.handle();

  ASSERT_TRUE(coil.setCondenserAirInletNodeName(std::string{"Single Condenser Inlet"}));
  ASSERT_TRUE(coil.condenserAirInletNodeName());
  EXPECT_EQ("Single Condenser Inlet", *coil.condenserAirInletNodeName());
  const auto firstNode = model.getConcreteModelObjectByName<Node>("Single Condenser Inlet");
  ASSERT_TRUE(firstNode);
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Single Condenser Inlet"));

  ASSERT_TRUE(coil.setCondenserAirInletNodeName(std::string{"Shared Condenser Inlet"}));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Single Condenser Inlet"));
  EXPECT_TRUE(model.getObject(firstNode->handle()));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Shared Condenser Inlet"));
  ASSERT_TRUE(sibling.setCondenserAirInletNodeName("Shared Condenser Inlet"));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Shared Condenser Inlet"));
  const auto sharedNodes = model.getConcreteModelObjectsByName<Node>("Shared Condenser Inlet", true);
  ASSERT_EQ(1u, sharedNodes.size());
  EXPECT_EQ(sharedNodeHandle, sharedNodes.front().handle());

  ASSERT_TRUE(coil.setCondenserAirInletNodeName(boost::none));
  EXPECT_FALSE(coil.condenserAirInletNodeName());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Shared Condenser Inlet"));
  EXPECT_TRUE(model.getObject(sharedNodeHandle));

  ASSERT_TRUE(coil.setCondenserAirInletNodeName(std::string{"Shared Condenser Inlet"}));
  EXPECT_FALSE(coil.remove().empty());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Shared Condenser Inlet"));
  EXPECT_TRUE(model.getObject(sharedNodeHandle));
  ASSERT_TRUE(sibling.setCondenserAirInletNodeName(""));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Shared Condenser Inlet"));
  EXPECT_TRUE(model.getObject(sharedNodeHandle));
  EXPECT_EQ(1u, model.getConcreteModelObjectsByName<Node>("Shared Condenser Inlet", true).size());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_CondenserAirInletCanonicalizationRepairsDeclarations) {
  Model model;
  CoilCoolingDXSingleSpeed missingDeclaration(model);
  CoilCoolingDXSingleSpeed richerDeclaration(model);
  ASSERT_TRUE(missingDeclaration.setName("Missing Declaration Coil"));
  ASSERT_TRUE(richerDeclaration.setName("Richer Declaration Coil"));

  constexpr auto field = openstudio::Coil_Cooling_DX_SingleSpeedFields::CondenserAirInletNodeName;
  auto missingImpl = missingDeclaration.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto richerImpl = richerDeclaration.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(missingImpl);
  ASSERT_TRUE(richerImpl);
  // Seed persisted NodeType text without a managed Node or outdoor-air declaration.
  ASSERT_TRUE(missingImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(missingImpl->openstudio::detail::IdfObject_Impl::setString(field, "Imported Missing OA Node", false));
  ASSERT_TRUE(richerImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(richerImpl->openstudio::detail::IdfObject_Impl::setString(field, "Imported Rich OA Node", false));

  auto outdoorAirNode = ModelObject::create(openstudio::IddObjectType::OutdoorAir_Node, model);
  ASSERT_TRUE(outdoorAirNode.setName("Imported Rich OA Node"));
  auto conflictingList = ModelObject::create(openstudio::IddObjectType::OutdoorAir_NodeList, model);
  auto group = conflictingList.pushExtensibleGroup().optionalCast<openstudio::WorkspaceExtensibleGroup>();
  ASSERT_TRUE(group);
  ASSERT_TRUE(group->setString(openstudio::OutdoorAir_NodeListExtensibleFields::NodeorNodeListName, "Imported Rich OA Node"));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_TRUE(model.getConcreteModelObjectByName<Node>("Imported Missing OA Node"));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Missing OA Node"));
  EXPECT_TRUE(model.getConcreteModelObjectByName<Node>("Imported Rich OA Node"));
  EXPECT_TRUE(hasOutdoorAirNode(model, "Imported Rich OA Node"));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Imported Rich OA Node"));

  EXPECT_EQ(0u, model.canonicalize().errorCount);
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(model, "Imported Missing OA Node"));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(model, "Imported Rich OA Node"));
  ASSERT_TRUE(richerDeclaration.setCondenserAirInletNodeName(boost::none));
  EXPECT_TRUE(hasOutdoorAirNode(model, "Imported Rich OA Node"));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_CondenserAirInletReloadMutationResetAndResourceSurvival) {
  const auto firstPath = uniqueIdfPath("epmodel-single-speed-condenser-first");
  const auto secondPath = uniqueIdfPath("epmodel-single-speed-condenser-second");
  const ScopedFileRemoval removeFirst(firstPath);
  const ScopedFileRemoval removeSecond(secondPath);

  Model model;
  CoilCoolingDXSingleSpeed coil(model);
  ASSERT_TRUE(coil.setName("Reload Single Condenser Coil"));
  ASSERT_TRUE(coil.setCondenserAirInletNodeName(std::string{"Reload Single Condenser Inlet"}));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedCoil = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Reload Single Condenser Coil");
  ASSERT_TRUE(loadedCoil);
  ASSERT_TRUE(loadedCoil->condenserAirInletNodeName());
  EXPECT_EQ("Reload Single Condenser Inlet", *loadedCoil->condenserAirInletNodeName());
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(*loadedModel, "Reload Single Condenser Inlet"));
  ASSERT_TRUE(loadedCoil->setCondenserAirInletNodeName(std::string{"Replacement Single Condenser Inlet"}));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*loadedModel, "Reload Single Condenser Inlet"));
  EXPECT_EQ(1u, outdoorAirNodeListEntryCount(*loadedModel, "Replacement Single Condenser Inlet"));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedCoil = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Reload Single Condenser Coil");
  ASSERT_TRUE(reloadedCoil);
  ASSERT_TRUE(reloadedCoil->condenserAirInletNodeName());
  EXPECT_EQ("Replacement Single Condenser Inlet", *reloadedCoil->condenserAirInletNodeName());
  const auto reloadedAvailabilityHandle = reloadedCoil->availabilitySchedule().handle();
  ASSERT_TRUE(reloadedCoil->setCondenserAirInletNodeName(boost::none));
  EXPECT_EQ(0u, outdoorAirNodeListEntryCount(*reloadedModel, "Replacement Single Condenser Inlet"));
  EXPECT_FALSE(reloadedCoil->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedAvailabilityHandle));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsOutboardOANode) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyInletNode));
  auto outboardOANode = oaSystem.outboardOANode();
  ASSERT_TRUE(outboardOANode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*outboardOANode));
  EXPECT_EQ(1u, oaSystem.oaComponents().size());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeRejectsDemandBranchNode) {
  Model model;
  AirLoopHVAC airLoop(model);

  auto branchObject = airLoop.zoneSplitter().lastOutletModelObject();
  ASSERT_TRUE(branchObject);
  auto branchNode = branchObject->optionalCast<Node>();
  ASSERT_TRUE(branchNode);

  CoilCoolingDXSingleSpeed coil(model);
  EXPECT_FALSE(coil.addToNode(*branchNode));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  EXPECT_TRUE(coil.setCondenserType("AirCooled"));
  EXPECT_EQ("AirCooled", coil.condenserType());

  EXPECT_TRUE(coil.setRatedCOP(3.2));
  EXPECT_DOUBLE_EQ(3.2, coil.ratedCOP());

  coil.autosizeRatedTotalCoolingCapacity();
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalCoolingCapacity());
  EXPECT_TRUE(coil.setRatedTotalCoolingCapacity(12000.0));
  ASSERT_TRUE(coil.ratedTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(12000.0, *coil.ratedTotalCoolingCapacity());
  EXPECT_FALSE(coil.isRatedTotalCoolingCapacityAutosized());

  coil.autosizeRatedSensibleHeatRatio();
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_FALSE(coil.ratedSensibleHeatRatio());
  EXPECT_TRUE(coil.setRatedSensibleHeatRatio(0.73));
  ASSERT_TRUE(coil.ratedSensibleHeatRatio());
  EXPECT_DOUBLE_EQ(0.73, *coil.ratedSensibleHeatRatio());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.25));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.25, *coil.ratedAirFlowRate());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-20.0));
  EXPECT_DOUBLE_EQ(-20.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipSetters_RoundTrip) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.25));
  CurveBiquadratic coolingTemp(model);
  CurveQuadratic coolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);
  CurveQuadratic crankcaseCurve(model);
  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(0.5));

  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(coolingTemp));
  EXPECT_EQ(coolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(coolingFlow));
  EXPECT_EQ(coolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(eirTemp));
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(eirFlow));
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(plf));
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  const auto children = coil.children();
  ASSERT_EQ(6u, children.size());
  EXPECT_EQ(crankcaseCurve.handle(), children.back().handle());

  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  coil.resetBasinHeaterOperatingSchedule();
  EXPECT_FALSE(coil.basinHeaterOperatingSchedule());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.75));
  CurveBiquadratic coolingTemp(model);
  CurveQuadratic coolingFlow(model);
  CurveBiquadratic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);

  CoilCoolingDXSingleSpeed coil(model, availability, coolingTemp, coolingFlow, eirTemp, eirFlow, plf);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(coolingTemp.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(coolingFlow.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.isRatedTotalCoolingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedSensibleHeatRatioAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_DOUBLE_EQ(3.0, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedEvaporatorFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedEvaporatorFanPowerPerVolumeFlowRate2023());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_AddToNodeSupplyPath) {
  Model model;
  AirLoopHVAC airLoop(model);

  CoilCoolingDXSingleSpeed coil(model);
  auto supplyInletNode = airLoop.supplyInletNode();
  EXPECT_TRUE(coil.addToNode(supplyInletNode));
  ASSERT_TRUE(coil.inletModelObject());
  EXPECT_EQ(supplyInletNode, coil.inletModelObject()->cast<Node>());
  EXPECT_TRUE(coil.outletModelObject());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipValidationPreservesManagedAndRawState) {
  Model model;
  CoilCoolingDXSingleSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(availability.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().get());

  ScheduleConstant basinSchedule(model);
  ASSERT_TRUE(basinSchedule.setValue(1.0));
  EXPECT_TRUE(coil.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(basinSchedule.scheduleTypeLimits());
  EXPECT_EQ("Availability", basinSchedule.scheduleTypeLimits()->unitType());

  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(coil.setBasinHeaterOperatingSchedule(incompatibleAvailability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(coil.setBasinHeaterOperatingSchedule(foreignSchedule));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  ASSERT_TRUE(coil.basinHeaterOperatingSchedule());
  EXPECT_EQ(basinSchedule.handle(), coil.basinHeaterOperatingSchedule()->handle());

  CurveBiquadratic bivariate(model);
  CurveQuadratic univariate(model);
  CurveTriquadratic trivariate(model);
  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(bivariate));
  EXPECT_FALSE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(univariate));
  EXPECT_FALSE(coil.setTotalCoolingCapacityFunctionOfTemperatureCurve(trivariate));
  EXPECT_EQ(bivariate.handle(), coil.totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(bivariate));
  EXPECT_FALSE(coil.setEnergyInputRatioFunctionOfTemperatureCurve(univariate));
  EXPECT_EQ(bivariate.handle(), coil.energyInputRatioFunctionOfTemperatureCurve().handle());

  EXPECT_TRUE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(univariate));
  EXPECT_FALSE(coil.setTotalCoolingCapacityFunctionOfFlowFractionCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.totalCoolingCapacityFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(univariate));
  EXPECT_FALSE(coil.setEnergyInputRatioFunctionOfFlowFractionCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.energyInputRatioFunctionOfFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(univariate));
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(univariate));
  EXPECT_FALSE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(bivariate));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(univariate.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  CurveQuadratic foreignCurve(foreignModel);
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(foreignCurve));
  EXPECT_EQ(univariate.handle(), coil.partLoadFractionCorrelationCurve().handle());

  CoilCoolingDXSingleSpeed unresolved(model);
  auto workspaceImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) { return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""); };

  constexpr unsigned availabilityField = openstudio::Coil_Cooling_DX_SingleSpeedFields::AvailabilityScheduleName;
  constexpr unsigned capacityTemperatureField = openstudio::Coil_Cooling_DX_SingleSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName;
  constexpr unsigned capacityFlowField = openstudio::Coil_Cooling_DX_SingleSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName;
  constexpr unsigned eirTemperatureField = openstudio::Coil_Cooling_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName;
  constexpr unsigned eirFlowField = openstudio::Coil_Cooling_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName;
  constexpr unsigned partLoadField = openstudio::Coil_Cooling_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName;
  constexpr unsigned crankcaseField = openstudio::Coil_Cooling_DX_SingleSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
  constexpr unsigned basinField = openstudio::Coil_Cooling_DX_SingleSpeedFields::BasinHeaterOperatingScheduleName;
  setUnresolvedRaw(availabilityField, "Unresolved Cooling Availability");
  setUnresolvedRaw(capacityTemperatureField, "Unresolved Cooling Capacity Temperature");
  setUnresolvedRaw(capacityFlowField, "Unresolved Cooling Capacity Flow");
  setUnresolvedRaw(eirTemperatureField, "Unresolved Cooling EIR Temperature");
  setUnresolvedRaw(eirFlowField, "Unresolved Cooling EIR Flow");
  setUnresolvedRaw(partLoadField, "Unresolved Cooling Part Load");
  setUnresolvedRaw(crankcaseField, "Unresolved Cooling Crankcase");
  setUnresolvedRaw(basinField, "Unresolved Cooling Basin Schedule");

  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(unresolved.setTotalCoolingCapacityFunctionOfTemperatureCurve(univariate));
  EXPECT_FALSE(unresolved.setTotalCoolingCapacityFunctionOfFlowFractionCurve(bivariate));
  EXPECT_FALSE(unresolved.setEnergyInputRatioFunctionOfTemperatureCurve(univariate));
  EXPECT_FALSE(unresolved.setEnergyInputRatioFunctionOfFlowFractionCurve(bivariate));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_FALSE(unresolved.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(bivariate));
  EXPECT_FALSE(unresolved.setBasinHeaterOperatingSchedule(incompatibleAvailability));
  EXPECT_EQ("Unresolved Cooling Availability", rawValue(availabilityField));
  EXPECT_EQ("Unresolved Cooling Capacity Temperature", rawValue(capacityTemperatureField));
  EXPECT_EQ("Unresolved Cooling Capacity Flow", rawValue(capacityFlowField));
  EXPECT_EQ("Unresolved Cooling EIR Temperature", rawValue(eirTemperatureField));
  EXPECT_EQ("Unresolved Cooling EIR Flow", rawValue(eirFlowField));
  EXPECT_EQ("Unresolved Cooling Part Load", rawValue(partLoadField));
  EXPECT_EQ("Unresolved Cooling Crankcase", rawValue(crankcaseField));
  EXPECT_EQ("Unresolved Cooling Basin Schedule", rawValue(basinField));
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_CanonicalizationRepairsOnlyBlankAvailability) {
  const auto idfPath = uniqueIdfPath("epmodel-cooling-dx-single-speed-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  CoilCoolingDXSingleSpeed blank(model);
  CoilCoolingDXSingleSpeed unresolved(model);
  ASSERT_TRUE(blank.setName("Blank Cooling Availability"));
  ASSERT_TRUE(unresolved.setName("Unresolved Cooling Availability Coil"));

  constexpr unsigned field = openstudio::Coil_Cooling_DX_SingleSpeedFields::AvailabilityScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing Cooling Availability", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ("Missing Cooling Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  Model reloadSource;
  CoilCoolingDXSingleSpeed blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank Cooling Availability On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Blank Cooling Availability On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilCoolingDXSingleSpeed_RelationshipsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-cooling-dx-single-speed-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-cooling-dx-single-speed-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleConstant availability(model);
  ScheduleConstant basinSchedule(model);
  CurveBiquadratic capacityTemperature(model);
  CurveQuadratic capacityFlow(model);
  CurveBiquadratic eirTemperature(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic partLoad(model);
  CurveQuadratic crankcase(model);
  ASSERT_TRUE(availability.setName("Shared Cooling Availability"));
  ASSERT_TRUE(basinSchedule.setName("Shared Cooling Basin Schedule"));
  ASSERT_TRUE(capacityTemperature.setName("Shared Cooling Capacity Temperature"));
  ASSERT_TRUE(capacityFlow.setName("Shared Cooling Capacity Flow"));
  ASSERT_TRUE(eirTemperature.setName("Shared Cooling EIR Temperature"));
  ASSERT_TRUE(eirFlow.setName("Shared Cooling EIR Flow"));
  ASSERT_TRUE(partLoad.setName("Shared Cooling Part Load"));
  ASSERT_TRUE(crankcase.setName("Shared Cooling Crankcase"));
  ASSERT_TRUE(availability.setValue(1.0));
  ASSERT_TRUE(basinSchedule.setValue(1.0));

  CoilCoolingDXSingleSpeed first(model, availability, capacityTemperature, capacityFlow, eirTemperature, eirFlow, partLoad);
  CoilCoolingDXSingleSpeed second(model, availability, capacityTemperature, capacityFlow, eirTemperature, eirFlow, partLoad);
  ASSERT_TRUE(first.setName("First Relationship Cooling Coil"));
  ASSERT_TRUE(second.setName("Second Relationship Cooling Coil"));
  ASSERT_TRUE(first.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcase));
  ASSERT_TRUE(second.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcase));
  ASSERT_TRUE(first.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(second.setBasinHeaterOperatingSchedule(basinSchedule));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirst = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("First Relationship Cooling Coil");
  auto loadedSecond = loadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Second Relationship Cooling Coil");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Cooling Availability");
  auto loadedBasinSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Cooling Basin Schedule");
  auto loadedCapacityTemperature = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Cooling Capacity Temperature");
  auto loadedCrankcase = loadedModel->getConcreteModelObjectByName<CurveQuadratic>("Shared Cooling Crankcase");
  ASSERT_TRUE(loadedFirst);
  ASSERT_TRUE(loadedSecond);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedBasinSchedule);
  ASSERT_TRUE(loadedCapacityTemperature);
  ASSERT_TRUE(loadedCrankcase);
  EXPECT_EQ(loadedAvailability->handle(), loadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(loadedAvailability->handle(), loadedSecond->availabilitySchedule().handle());
  EXPECT_EQ(loadedCapacityTemperature->handle(), loadedFirst->totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(loadedCapacityTemperature->handle(), loadedSecond->totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  ASSERT_TRUE(loadedFirst->basinHeaterOperatingSchedule());
  ASSERT_TRUE(loadedSecond->basinHeaterOperatingSchedule());
  EXPECT_EQ(loadedBasinSchedule->handle(), loadedFirst->basinHeaterOperatingSchedule()->handle());
  EXPECT_EQ(loadedBasinSchedule->handle(), loadedSecond->basinHeaterOperatingSchedule()->handle());

  ScheduleConstant replacementAvailability(*loadedModel);
  CurveBiquadratic replacementCapacityTemperature(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Cooling Availability"));
  ASSERT_TRUE(replacementAvailability.setValue(1.0));
  ASSERT_TRUE(replacementCapacityTemperature.setName("Replacement Cooling Capacity Temperature"));
  ASSERT_TRUE(loadedFirst->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedFirst->setTotalCoolingCapacityFunctionOfTemperatureCurve(replacementCapacityTemperature));
  loadedFirst->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  loadedFirst->resetBasinHeaterOperatingSchedule();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFirst = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("First Relationship Cooling Coil");
  auto reloadedSecond = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXSingleSpeed>("Second Relationship Cooling Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Cooling Availability");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Cooling Availability");
  auto reloadedBasinSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Cooling Basin Schedule");
  auto reloadedOriginalCapacityTemperature = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Cooling Capacity Temperature");
  auto reloadedReplacementCapacityTemperature =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement Cooling Capacity Temperature");
  auto reloadedCrankcase = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Shared Cooling Crankcase");
  ASSERT_TRUE(reloadedFirst);
  ASSERT_TRUE(reloadedSecond);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedBasinSchedule);
  ASSERT_TRUE(reloadedOriginalCapacityTemperature);
  ASSERT_TRUE(reloadedReplacementCapacityTemperature);
  ASSERT_TRUE(reloadedCrankcase);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(reloadedOriginalAvailability->handle(), reloadedSecond->availabilitySchedule().handle());
  EXPECT_EQ(reloadedReplacementCapacityTemperature->handle(), reloadedFirst->totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_EQ(reloadedOriginalCapacityTemperature->handle(), reloadedSecond->totalCoolingCapacityFunctionOfTemperatureCurve().handle());
  EXPECT_FALSE(reloadedFirst->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(reloadedFirst->basinHeaterOperatingSchedule());
  ASSERT_TRUE(reloadedSecond->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  ASSERT_TRUE(reloadedSecond->basinHeaterOperatingSchedule());
  EXPECT_EQ(reloadedBasinSchedule->handle(), reloadedSecond->basinHeaterOperatingSchedule()->handle());

  const std::array<openstudio::Handle, 6> retainedResources = {
    reloadedOriginalAvailability->handle(),        reloadedReplacementAvailability->handle(),        reloadedBasinSchedule->handle(),
    reloadedOriginalCapacityTemperature->handle(), reloadedReplacementCapacityTemperature->handle(), reloadedCrankcase->handle()};
  EXPECT_FALSE(reloadedFirst->remove().empty());
  EXPECT_EQ(reloadedOriginalAvailability->handle(), reloadedSecond->availabilitySchedule().handle());
  for (const auto& handle : retainedResources) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
  EXPECT_FALSE(reloadedSecond->remove().empty());
  for (const auto& handle : retainedResources) {
    EXPECT_TRUE(reloadedModel->getObject(handle));
  }
}
