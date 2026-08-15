/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "Curve/CurveBiquadratic.hpp"
#include "Curve/CurveBiquadratic_Impl.hpp"
#include "Curve/CurveCubic.hpp"
#include "Curve/CurveCubic_Impl.hpp"
#include "Curve/CurveQuadratic.hpp"
#include "Curve/CurveQuadratic_Impl.hpp"
#include "Curve/CurveTriquadratic.hpp"
#include "ResourceObject/ScheduleTypeLimits.hpp"
#include "Schedule/ScheduleConstant.hpp"
#include "Schedule/ScheduleConstant_Impl.hpp"
#include "HVACComponent/AirLoopHVACOutdoorAirSystem.hpp"
#include "Loop/AirLoopHVAC.hpp"
#include "StraightComponent/Node.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed.hpp"
#include "../StraightComponent/CoilHeatingDXSingleSpeed_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Heating_DX_SingleSpeed_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

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

}  // namespace

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_DefaultConstructor) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);
  EXPECT_EQ(CoilHeatingDXSingleSpeed::iddObjectType(), coil.iddObject().type());
  EXPECT_FALSE(coil.nameString().empty());

  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());

  EXPECT_DOUBLE_EQ(5.0, coil.ratedCOP());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate());
  EXPECT_DOUBLE_EQ(773.3, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_DOUBLE_EQ(934.4, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_EQ("Resistive", coil.defrostStrategy());
  EXPECT_EQ("Timed", coil.defrostControl());
  EXPECT_NEAR(0.166667, coil.defrostTimePeriodFraction(), 1e-6);
  auto availability = coil.availabilitySchedule().optionalCast<ScheduleConstant>();
  ASSERT_TRUE(availability);
  EXPECT_DOUBLE_EQ(1.0, availability->value());
  ASSERT_TRUE(coil.totalHeatingCapacityFunctionofTemperatureCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.totalHeatingCapacityFunctionofFlowFractionCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionofTemperatureCurve().optionalCast<CurveCubic>());
  ASSERT_TRUE(coil.energyInputRatioFunctionofFlowFractionCurve().optionalCast<CurveQuadratic>());
  ASSERT_TRUE(coil.partLoadFractionCorrelationCurve().optionalCast<CurveQuadratic>());
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(2000.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());

  const auto children = coil.children();
  ASSERT_EQ(5u, children.size());
  EXPECT_EQ(coil.totalHeatingCapacityFunctionofTemperatureCurve().handle(), children[0].handle());
  EXPECT_EQ(coil.totalHeatingCapacityFunctionofFlowFractionCurve().handle(), children[1].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionofTemperatureCurve().handle(), children[2].handle());
  EXPECT_EQ(coil.energyInputRatioFunctionofFlowFractionCurve().handle(), children[3].handle());
  EXPECT_EQ(coil.partLoadFractionCorrelationCurve().handle(), children[4].handle());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);

  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostStrategyValues().empty());
  ASSERT_FALSE(CoilHeatingDXSingleSpeed::validDefrostControlValues().empty());

  coil.autosizeRatedTotalHeatingCapacity();
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_FALSE(coil.ratedTotalHeatingCapacity());
  EXPECT_TRUE(coil.setRatedTotalHeatingCapacity(15000.0));
  ASSERT_TRUE(coil.ratedTotalHeatingCapacity());
  EXPECT_DOUBLE_EQ(15000.0, *coil.ratedTotalHeatingCapacity());
  EXPECT_FALSE(coil.isRatedTotalHeatingCapacityAutosized());

  EXPECT_TRUE(coil.setRatedCOP(4.2));
  EXPECT_DOUBLE_EQ(4.2, coil.ratedCOP());

  coil.autosizeRatedAirFlowRate();
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
  EXPECT_FALSE(coil.ratedAirFlowRate());
  EXPECT_TRUE(coil.setRatedAirFlowRate(1.2));
  ASSERT_TRUE(coil.ratedAirFlowRate());
  EXPECT_DOUBLE_EQ(1.2, *coil.ratedAirFlowRate());
  EXPECT_FALSE(coil.isRatedAirFlowRateAutosized());

  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate(800.0));
  EXPECT_DOUBLE_EQ(800.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2017());
  EXPECT_TRUE(coil.setRatedSupplyFanPowerPerVolumeFlowRate2023(950.0));
  EXPECT_DOUBLE_EQ(950.0, coil.ratedSupplyFanPowerPerVolumeFlowRate2023());

  EXPECT_TRUE(coil.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, coil.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_FALSE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());
  coil.resetMinimumOutdoorDryBulbTemperatureforCompressorOperation();
  EXPECT_TRUE(coil.isMinimumOutdoorDryBulbTemperatureforCompressorOperationDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforDefrostOperation(6.0));
  EXPECT_DOUBLE_EQ(6.0, coil.maximumOutdoorDryBulbTemperatureforDefrostOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforDefrostOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforDefrostOperationDefaulted());

  EXPECT_TRUE(coil.setCrankcaseHeaterCapacity(120.0));
  EXPECT_DOUBLE_EQ(120.0, coil.crankcaseHeaterCapacity());
  EXPECT_FALSE(coil.isCrankcaseHeaterCapacityDefaulted());
  coil.resetCrankcaseHeaterCapacity();
  EXPECT_TRUE(coil.isCrankcaseHeaterCapacityDefaulted());

  EXPECT_TRUE(coil.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.5));
  EXPECT_DOUBLE_EQ(9.5, coil.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_FALSE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());
  coil.resetMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation();
  EXPECT_TRUE(coil.isMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperationDefaulted());

  CurveBiquadratic defrostCurve(model);
  EXPECT_TRUE(coil.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrostCurve));
  ASSERT_TRUE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(defrostCurve.handle(), coil.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  coil.resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());

  CurveCubic crankcaseCurve(model);
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcaseCurve));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(crankcaseCurve.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  coil.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());

  EXPECT_TRUE(coil.setDefrostStrategy("ReverseCycle"));
  EXPECT_EQ("ReverseCycle", coil.defrostStrategy());
  EXPECT_FALSE(coil.isDefrostStrategyDefaulted());
  coil.resetDefrostStrategy();
  EXPECT_TRUE(coil.isDefrostStrategyDefaulted());

  EXPECT_TRUE(coil.setDefrostControl("OnDemand"));
  EXPECT_EQ("OnDemand", coil.defrostControl());
  EXPECT_FALSE(coil.isDefrostControlDefaulted());
  coil.resetDefrostControl();
  EXPECT_TRUE(coil.isDefrostControlDefaulted());

  EXPECT_TRUE(coil.setDefrostTimePeriodFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, coil.defrostTimePeriodFraction());
  EXPECT_FALSE(coil.isDefrostTimePeriodFractionDefaulted());
  coil.resetDefrostTimePeriodFraction();
  EXPECT_TRUE(coil.isDefrostTimePeriodFractionDefaulted());

  EXPECT_TRUE(coil.setResistiveDefrostHeaterCapacity(450.0));
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(450.0, *coil.resistiveDefrostHeaterCapacity());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  EXPECT_FALSE(coil.isResistiveDefrostHeaterCapacityAutosized());

  coil.autosizeResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityAutosized());
  EXPECT_FALSE(coil.resistiveDefrostHeaterCapacity());

  coil.resetResistiveDefrostHeaterCapacity();
  EXPECT_TRUE(coil.isResistiveDefrostHeaterCapacityDefaulted());
  ASSERT_TRUE(coil.resistiveDefrostHeaterCapacity());
  EXPECT_DOUBLE_EQ(0.0, *coil.resistiveDefrostHeaterCapacity());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_RelationshipConstructor) {
  Model model;
  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(0.3));
  CurveCubic totalHeatingTemp(model);
  CurveCubic totalHeatingFlow(model);
  CurveCubic eirTemp(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic plf(model);

  CoilHeatingDXSingleSpeed coil(model, availability, totalHeatingTemp, totalHeatingFlow, eirTemp, eirFlow, plf);

  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());
  EXPECT_EQ(totalHeatingTemp.handle(), coil.totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(totalHeatingFlow.handle(), coil.totalHeatingCapacityFunctionofFlowFractionCurve().handle());
  EXPECT_EQ(eirTemp.handle(), coil.energyInputRatioFunctionofTemperatureCurve().handle());
  EXPECT_EQ(eirFlow.handle(), coil.energyInputRatioFunctionofFlowFractionCurve().handle());
  EXPECT_EQ(plf.handle(), coil.partLoadFractionCorrelationCurve().handle());
  EXPECT_TRUE(coil.isRatedTotalHeatingCapacityAutosized());
  EXPECT_TRUE(coil.isRatedAirFlowRateAutosized());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToSupplyNode) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingDXSingleSpeed coil(model);

  auto supplyNode = airLoop.supplyInletNode();
  EXPECT_TRUE(coil.addToNode(supplyNode));

  auto supplyComponent = airLoop.supplyComponent(coil.handle());
  ASSERT_TRUE(supplyComponent);
  EXPECT_EQ(coil, *supplyComponent);
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToDemandNodeFails) {
  Model model;
  AirLoopHVAC airLoop(model);
  CoilHeatingDXSingleSpeed coil(model);

  auto demandNode = airLoop.demandInletNode();
  EXPECT_FALSE(coil.addToNode(demandNode));
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_AddToOutdoorAirNodeFails) {
  Model model;
  AirLoopHVAC airLoop(model);
  AirLoopHVACOutdoorAirSystem oaSystem(model);
  auto supplyNode = airLoop.supplyInletNode();
  ASSERT_TRUE(oaSystem.addToNode(supplyNode));

  CoilHeatingDXSingleSpeed coil(model);

  auto outdoorAirObject = oaSystem.outdoorAirModelObject();
  ASSERT_TRUE(outdoorAirObject);
  auto outdoorNode = outdoorAirObject->optionalCast<Node>();
  ASSERT_TRUE(outdoorNode);

  EXPECT_FALSE(coil.addToNode(*outdoorNode));
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_RelationshipValidationPreservesManagedAndRawState) {
  Model model;
  CoilHeatingDXSingleSpeed coil(model);

  ScheduleConstant availability(model);
  ASSERT_TRUE(availability.setValue(1.0));
  EXPECT_TRUE(coil.setAvailabilitySchedule(availability));
  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(availability.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().get());

  ScheduleConstant incompatibleAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(incompatibleAvailability.setScheduleTypeLimits(temperatureLimits));
  EXPECT_FALSE(coil.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  Model foreignModel;
  ScheduleConstant foreignAvailability(foreignModel);
  EXPECT_FALSE(coil.setAvailabilitySchedule(foreignAvailability));
  EXPECT_EQ(availability.handle(), coil.availabilitySchedule().handle());

  CurveBiquadratic bivariate(model);
  CurveQuadratic univariate(model);
  CurveTriquadratic trivariate(model);
  EXPECT_TRUE(coil.setTotalHeatingCapacityFunctionofTemperatureCurve(bivariate));
  EXPECT_FALSE(coil.setTotalHeatingCapacityFunctionofTemperatureCurve(trivariate));
  EXPECT_EQ(bivariate.handle(), coil.totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionofTemperatureCurve(bivariate));
  EXPECT_FALSE(coil.setEnergyInputRatioFunctionofTemperatureCurve(trivariate));
  EXPECT_EQ(bivariate.handle(), coil.energyInputRatioFunctionofTemperatureCurve().handle());

  EXPECT_TRUE(coil.setTotalHeatingCapacityFunctionofFlowFractionCurve(univariate));
  EXPECT_FALSE(coil.setTotalHeatingCapacityFunctionofFlowFractionCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.totalHeatingCapacityFunctionofFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setEnergyInputRatioFunctionofFlowFractionCurve(univariate));
  EXPECT_FALSE(coil.setEnergyInputRatioFunctionofFlowFractionCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.energyInputRatioFunctionofFlowFractionCurve().handle());
  EXPECT_TRUE(coil.setPartLoadFractionCorrelationCurve(univariate));
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_EQ(univariate.handle(), coil.partLoadFractionCorrelationCurve().handle());

  EXPECT_TRUE(coil.setDefrostEnergyInputRatioFunctionofTemperatureCurve(bivariate));
  EXPECT_FALSE(coil.setDefrostEnergyInputRatioFunctionofTemperatureCurve(univariate));
  ASSERT_TRUE(coil.defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(bivariate.handle(), coil.defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  EXPECT_TRUE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(univariate));
  EXPECT_FALSE(coil.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(bivariate));
  ASSERT_TRUE(coil.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(univariate.handle(), coil.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  CurveQuadratic foreignCurve(foreignModel);
  EXPECT_FALSE(coil.setPartLoadFractionCorrelationCurve(foreignCurve));
  EXPECT_EQ(univariate.handle(), coil.partLoadFractionCorrelationCurve().handle());

  CoilHeatingDXSingleSpeed unresolved(model);
  auto workspaceImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  const auto setUnresolvedRaw = [&](unsigned field, const std::string& value) {
    ASSERT_TRUE(workspaceImpl->setPointer(field, openstudio::Handle(), false));
    ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(field, value, false));
  };
  const auto rawValue = [&](unsigned field) { return workspaceImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""); };

  constexpr unsigned availabilityField = openstudio::Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName;
  constexpr unsigned capacityTemperatureField = openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofTemperatureCurveName;
  constexpr unsigned capacityFlowField = openstudio::Coil_Heating_DX_SingleSpeedFields::HeatingCapacityFunctionofFlowFractionCurveName;
  constexpr unsigned eirTemperatureField = openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName;
  constexpr unsigned eirFlowField = openstudio::Coil_Heating_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName;
  constexpr unsigned partLoadField = openstudio::Coil_Heating_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName;
  constexpr unsigned defrostField = openstudio::Coil_Heating_DX_SingleSpeedFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName;
  constexpr unsigned crankcaseField = openstudio::Coil_Heating_DX_SingleSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
  setUnresolvedRaw(availabilityField, "Unresolved Heating Availability");
  setUnresolvedRaw(capacityTemperatureField, "Unresolved Heating Capacity Temperature");
  setUnresolvedRaw(capacityFlowField, "Unresolved Heating Capacity Flow");
  setUnresolvedRaw(eirTemperatureField, "Unresolved Heating EIR Temperature");
  setUnresolvedRaw(eirFlowField, "Unresolved Heating EIR Flow");
  setUnresolvedRaw(partLoadField, "Unresolved Heating Part Load");
  setUnresolvedRaw(defrostField, "Unresolved Heating Defrost");
  setUnresolvedRaw(crankcaseField, "Unresolved Heating Crankcase");

  EXPECT_FALSE(unresolved.setAvailabilitySchedule(incompatibleAvailability));
  EXPECT_FALSE(unresolved.setTotalHeatingCapacityFunctionofTemperatureCurve(trivariate));
  EXPECT_FALSE(unresolved.setTotalHeatingCapacityFunctionofFlowFractionCurve(bivariate));
  EXPECT_FALSE(unresolved.setEnergyInputRatioFunctionofTemperatureCurve(trivariate));
  EXPECT_FALSE(unresolved.setEnergyInputRatioFunctionofFlowFractionCurve(bivariate));
  EXPECT_FALSE(unresolved.setPartLoadFractionCorrelationCurve(bivariate));
  EXPECT_FALSE(unresolved.setDefrostEnergyInputRatioFunctionofTemperatureCurve(univariate));
  EXPECT_FALSE(unresolved.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(bivariate));
  EXPECT_EQ("Unresolved Heating Availability", rawValue(availabilityField));
  EXPECT_EQ("Unresolved Heating Capacity Temperature", rawValue(capacityTemperatureField));
  EXPECT_EQ("Unresolved Heating Capacity Flow", rawValue(capacityFlowField));
  EXPECT_EQ("Unresolved Heating EIR Temperature", rawValue(eirTemperatureField));
  EXPECT_EQ("Unresolved Heating EIR Flow", rawValue(eirFlowField));
  EXPECT_EQ("Unresolved Heating Part Load", rawValue(partLoadField));
  EXPECT_EQ("Unresolved Heating Defrost", rawValue(defrostField));
  EXPECT_EQ("Unresolved Heating Crankcase", rawValue(crankcaseField));
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_CanonicalizationRepairsOnlyBlankAvailability) {
  const auto idfPath = uniqueIdfPath("epmodel-heating-dx-single-speed-availability-repair");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  CoilHeatingDXSingleSpeed blank(model);
  CoilHeatingDXSingleSpeed unresolved(model);
  ASSERT_TRUE(blank.setName("Blank Heating Availability"));
  ASSERT_TRUE(unresolved.setName("Unresolved Heating Availability Coil"));

  constexpr unsigned field = openstudio::Coil_Heating_DX_SingleSpeedFields::AvailabilityScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing Heating Availability", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.availabilitySchedule().handle());
  EXPECT_EQ("Missing Heating Availability", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  Model reloadSource;
  CoilHeatingDXSingleSpeed blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank Heating Availability On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("Blank Heating Availability On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->availabilitySchedule().handle());
}

TEST_F(EPModelFixture, CoilHeatingDXSingleSpeed_RelationshipsSurviveReloadMutationResetAndRemoval) {
  const auto firstIdfPath = uniqueIdfPath("epmodel-heating-dx-single-speed-relationships-first");
  const auto secondIdfPath = uniqueIdfPath("epmodel-heating-dx-single-speed-relationships-second");
  const ScopedFileRemoval removeFirstIdf(firstIdfPath);
  const ScopedFileRemoval removeSecondIdf(secondIdfPath);

  Model model;
  ScheduleConstant availability(model);
  CurveBiquadratic capacityTemperature(model);
  CurveQuadratic capacityFlow(model);
  CurveBiquadratic eirTemperature(model);
  CurveQuadratic eirFlow(model);
  CurveQuadratic partLoad(model);
  CurveBiquadratic defrost(model);
  CurveQuadratic crankcase(model);
  ASSERT_TRUE(availability.setName("Shared Heating Availability"));
  ASSERT_TRUE(capacityTemperature.setName("Shared Heating Capacity Temperature"));
  ASSERT_TRUE(capacityFlow.setName("Shared Heating Capacity Flow"));
  ASSERT_TRUE(eirTemperature.setName("Shared Heating EIR Temperature"));
  ASSERT_TRUE(eirFlow.setName("Shared Heating EIR Flow"));
  ASSERT_TRUE(partLoad.setName("Shared Heating Part Load"));
  ASSERT_TRUE(defrost.setName("Shared Heating Defrost"));
  ASSERT_TRUE(crankcase.setName("Shared Heating Crankcase"));
  ASSERT_TRUE(availability.setValue(1.0));

  CoilHeatingDXSingleSpeed first(model, availability, capacityTemperature, capacityFlow, eirTemperature, eirFlow, partLoad);
  CoilHeatingDXSingleSpeed second(model, availability, capacityTemperature, capacityFlow, eirTemperature, eirFlow, partLoad);
  ASSERT_TRUE(first.setName("First Relationship Heating Coil"));
  ASSERT_TRUE(second.setName("Second Relationship Heating Coil"));
  ASSERT_TRUE(first.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrost));
  ASSERT_TRUE(second.setDefrostEnergyInputRatioFunctionofTemperatureCurve(defrost));
  ASSERT_TRUE(first.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcase));
  ASSERT_TRUE(second.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(crankcase));
  ASSERT_TRUE(model.save(firstIdfPath, true));

  auto loadedModel = Model::load(firstIdfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedFirst = loadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("First Relationship Heating Coil");
  auto loadedSecond = loadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("Second Relationship Heating Coil");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Heating Availability");
  auto loadedCapacityTemperature = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Heating Capacity Temperature");
  auto loadedDefrost = loadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Heating Defrost");
  auto loadedCrankcase = loadedModel->getConcreteModelObjectByName<CurveQuadratic>("Shared Heating Crankcase");
  ASSERT_TRUE(loadedFirst);
  ASSERT_TRUE(loadedSecond);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedCapacityTemperature);
  ASSERT_TRUE(loadedDefrost);
  ASSERT_TRUE(loadedCrankcase);
  EXPECT_EQ(loadedAvailability->handle(), loadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(loadedAvailability->handle(), loadedSecond->availabilitySchedule().handle());
  EXPECT_EQ(loadedCapacityTemperature->handle(), loadedFirst->totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(loadedCapacityTemperature->handle(), loadedSecond->totalHeatingCapacityFunctionofTemperatureCurve().handle());
  ASSERT_TRUE(loadedFirst->defrostEnergyInputRatioFunctionofTemperatureCurve());
  ASSERT_TRUE(loadedSecond->defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_EQ(loadedDefrost->handle(), loadedFirst->defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(loadedDefrost->handle(), loadedSecond->defrostEnergyInputRatioFunctionofTemperatureCurve()->handle());

  ScheduleConstant replacementAvailability(*loadedModel);
  CurveBiquadratic replacementCapacityTemperature(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Heating Availability"));
  ASSERT_TRUE(replacementAvailability.setValue(1.0));
  ASSERT_TRUE(replacementCapacityTemperature.setName("Replacement Heating Capacity Temperature"));
  ASSERT_TRUE(loadedFirst->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedFirst->setTotalHeatingCapacityFunctionofTemperatureCurve(replacementCapacityTemperature));
  loadedFirst->resetDefrostEnergyInputRatioFunctionofTemperatureCurve();
  loadedFirst->resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  ASSERT_TRUE(loadedModel->save(secondIdfPath, true));

  auto reloadedModel = Model::load(secondIdfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedFirst = reloadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("First Relationship Heating Coil");
  auto reloadedSecond = reloadedModel->getConcreteModelObjectByName<CoilHeatingDXSingleSpeed>("Second Relationship Heating Coil");
  auto reloadedOriginalAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Shared Heating Availability");
  auto reloadedReplacementAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Heating Availability");
  auto reloadedOriginalCapacityTemperature = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Heating Capacity Temperature");
  auto reloadedReplacementCapacityTemperature =
    reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Replacement Heating Capacity Temperature");
  auto reloadedDefrost = reloadedModel->getConcreteModelObjectByName<CurveBiquadratic>("Shared Heating Defrost");
  auto reloadedCrankcase = reloadedModel->getConcreteModelObjectByName<CurveQuadratic>("Shared Heating Crankcase");
  ASSERT_TRUE(reloadedFirst);
  ASSERT_TRUE(reloadedSecond);
  ASSERT_TRUE(reloadedOriginalAvailability);
  ASSERT_TRUE(reloadedReplacementAvailability);
  ASSERT_TRUE(reloadedOriginalCapacityTemperature);
  ASSERT_TRUE(reloadedReplacementCapacityTemperature);
  ASSERT_TRUE(reloadedDefrost);
  ASSERT_TRUE(reloadedCrankcase);
  EXPECT_EQ(reloadedReplacementAvailability->handle(), reloadedFirst->availabilitySchedule().handle());
  EXPECT_EQ(reloadedOriginalAvailability->handle(), reloadedSecond->availabilitySchedule().handle());
  EXPECT_EQ(reloadedReplacementCapacityTemperature->handle(), reloadedFirst->totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_EQ(reloadedOriginalCapacityTemperature->handle(), reloadedSecond->totalHeatingCapacityFunctionofTemperatureCurve().handle());
  EXPECT_FALSE(reloadedFirst->defrostEnergyInputRatioFunctionofTemperatureCurve());
  EXPECT_FALSE(reloadedFirst->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  ASSERT_TRUE(reloadedSecond->defrostEnergyInputRatioFunctionofTemperatureCurve());
  ASSERT_TRUE(reloadedSecond->crankcaseHeaterCapacityFunctionofTemperatureCurve());

  const std::array<openstudio::Handle, 6> retainedResources = {reloadedOriginalAvailability->handle(),
                                                               reloadedReplacementAvailability->handle(),
                                                               reloadedOriginalCapacityTemperature->handle(),
                                                               reloadedReplacementCapacityTemperature->handle(),
                                                               reloadedDefrost->handle(),
                                                               reloadedCrankcase->handle()};
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
