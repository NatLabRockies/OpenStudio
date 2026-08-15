/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <algorithm>
#include <utility>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/TableLookup.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitOperatingMode.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitOperatingMode_Impl.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance.hpp"
#include "../ResourceObject/CoilCoolingDXCurveFitPerformance_Impl.hpp"
#include "../Schedule/Schedule.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Coil_Cooling_DX_CurveFit_Performance_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

using namespace openstudio::epmodel;

namespace {
class ScopedCurveFitPerformanceFileRemoval
{
 public:
  explicit ScopedCurveFitPerformanceFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedCurveFitPerformanceFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueCurveFitPerformancePath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_DefaultConstructor) {
  Model model;
  CoilCoolingDXCurveFitPerformance performance(model);
  EXPECT_EQ(CoilCoolingDXCurveFitPerformance::iddObjectType(), performance.iddObject().type());
  EXPECT_FALSE(performance.nameString().empty());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), performance.evaporativeCondenserBasinHeaterOperatingSchedule().handle());
  EXPECT_FALSE(performance.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_FALSE(performance.alternativeOperatingMode1());
  EXPECT_FALSE(performance.alternativeOperatingMode2());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_ScalarAccessors_RoundTrip) {
  Model model;
  CoilCoolingDXCurveFitPerformance performance(model);

  EXPECT_TRUE(performance.setCrankcaseHeaterCapacity(500.0));
  EXPECT_DOUBLE_EQ(500.0, performance.crankcaseHeaterCapacity());

  EXPECT_TRUE(performance.setMinimumOutdoorDryBulbTemperatureforCompressorOperation(-12.0));
  EXPECT_DOUBLE_EQ(-12.0, performance.minimumOutdoorDryBulbTemperatureforCompressorOperation());

  EXPECT_TRUE(performance.setMaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation(9.0));
  EXPECT_DOUBLE_EQ(9.0, performance.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());

  EXPECT_TRUE(performance.setUnitInternalStaticAirPressure(780.0));
  EXPECT_DOUBLE_EQ(780.0, performance.unitInternalStaticAirPressure());

  EXPECT_TRUE(performance.setCapacityControlMethod("Continuous"));
  EXPECT_EQ("Continuous", performance.capacityControlMethod());

  EXPECT_TRUE(performance.setEvaporativeCondenserBasinHeaterCapacity(42.0));
  EXPECT_DOUBLE_EQ(42.0, performance.evaporativeCondenserBasinHeaterCapacity());

  EXPECT_TRUE(performance.setEvaporativeCondenserBasinHeaterSetpointTemperature(3.0));
  EXPECT_DOUBLE_EQ(3.0, performance.evaporativeCondenserBasinHeaterSetpointTemperature());

  EXPECT_TRUE(performance.setCompressorFuelType("Electricity"));
  EXPECT_EQ("Electricity", performance.compressorFuelType());

  const auto capacityControlMethodValues = CoilCoolingDXCurveFitPerformance::capacityControlMethodValues();
  EXPECT_NE(std::find(capacityControlMethodValues.begin(), capacityControlMethodValues.end(), "Discrete"), capacityControlMethodValues.end());

  const auto compressorFuelTypeValues = CoilCoolingDXCurveFitPerformance::compressorFuelTypeValues();
  EXPECT_NE(std::find(compressorFuelTypeValues.begin(), compressorFuelTypeValues.end(), "Electricity"), compressorFuelTypeValues.end());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_BaseOperatingModeRelationship) {
  Model model;
  CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
  CoilCoolingDXCurveFitPerformance performance(model, baseOperatingMode);

  EXPECT_EQ(baseOperatingMode.handle(), performance.baseOperatingMode().handle());
  EXPECT_DOUBLE_EQ(0.0, performance.crankcaseHeaterCapacity());
  EXPECT_DOUBLE_EQ(-25.0, performance.minimumOutdoorDryBulbTemperatureforCompressorOperation());
  EXPECT_DOUBLE_EQ(10.0, performance.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation());
  EXPECT_DOUBLE_EQ(773.3, performance.unitInternalStaticAirPressure());
  EXPECT_EQ("Discrete", performance.capacityControlMethod());
  EXPECT_DOUBLE_EQ(0.0, performance.evaporativeCondenserBasinHeaterCapacity());
  EXPECT_DOUBLE_EQ(2.0, performance.evaporativeCondenserBasinHeaterSetpointTemperature());
  EXPECT_EQ("Electricity", performance.compressorFuelType());
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), performance.evaporativeCondenserBasinHeaterOperatingSchedule().handle());

  CoilCoolingDXCurveFitOperatingMode replacementOperatingMode(model);
  ASSERT_TRUE(performance.setBaseOperatingMode(replacementOperatingMode));
  EXPECT_EQ(replacementOperatingMode.handle(), performance.baseOperatingMode().handle());

  Model otherModel;
  CoilCoolingDXCurveFitOperatingMode foreignOperatingMode(otherModel);
  EXPECT_FALSE(performance.setBaseOperatingMode(foreignOperatingMode));
  EXPECT_EQ(replacementOperatingMode.handle(), performance.baseOperatingMode().handle());

  const auto objectCount = otherModel.getConcreteModelObjects<CoilCoolingDXCurveFitPerformance>().size();
  EXPECT_THROW((CoilCoolingDXCurveFitPerformance{otherModel, replacementOperatingMode}), std::invalid_argument);
  EXPECT_EQ(objectCount, otherModel.getConcreteModelObjects<CoilCoolingDXCurveFitPerformance>().size());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_AlternativeOperatingModeValidationAndRawReset) {
  Model model;
  CoilCoolingDXCurveFitOperatingMode base(model);
  CoilCoolingDXCurveFitOperatingMode alternative1(model);
  CoilCoolingDXCurveFitOperatingMode alternative2(model);
  CoilCoolingDXCurveFitPerformance performance(model, base);

  ASSERT_TRUE(performance.setAlternativeOperatingMode1(alternative1));
  ASSERT_TRUE(performance.setAlternativeOperatingMode2(alternative2));
  ASSERT_TRUE(performance.alternativeOperatingMode1());
  ASSERT_TRUE(performance.alternativeOperatingMode2());
  EXPECT_EQ(alternative1.handle(), performance.alternativeOperatingMode1()->handle());
  EXPECT_EQ(alternative2.handle(), performance.alternativeOperatingMode2()->handle());

  Model foreignModel;
  CoilCoolingDXCurveFitOperatingMode foreignMode(foreignModel);
  EXPECT_FALSE(performance.setAlternativeOperatingMode1(foreignMode));
  EXPECT_FALSE(performance.setAlternativeOperatingMode2(foreignMode));
  EXPECT_EQ(alternative1.handle(), performance.alternativeOperatingMode1()->handle());
  EXPECT_EQ(alternative2.handle(), performance.alternativeOperatingMode2()->handle());

  // Deliberately seed impossible imported relationship text to prove failed public writes preserve it and explicit resets clear it.
  auto workspaceImpl = performance.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto alternative1Field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode1;
  constexpr auto alternative2Field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::AlternativeOperatingMode2;
  ASSERT_TRUE(workspaceImpl->setPointer(alternative1Field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(alternative1Field, "Unresolved Alternative Mode 1", false));
  ASSERT_TRUE(workspaceImpl->setPointer(alternative2Field, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(alternative2Field, "Unresolved Alternative Mode 2", false));

  EXPECT_FALSE(performance.setAlternativeOperatingMode1(foreignMode));
  EXPECT_FALSE(performance.setAlternativeOperatingMode2(foreignMode));
  EXPECT_EQ("Unresolved Alternative Mode 1",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(alternative1Field, false, true).value_or(""));
  EXPECT_EQ("Unresolved Alternative Mode 2",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(alternative2Field, false, true).value_or(""));

  performance.resetAlternativeOperatingMode1();
  performance.resetAlternativeOperatingMode2();
  EXPECT_FALSE(performance.alternativeOperatingMode1());
  EXPECT_FALSE(performance.alternativeOperatingMode2());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(alternative1Field, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(alternative2Field, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_DirectRelationshipValidationAndReset) {
  Model model;
  CoilCoolingDXCurveFitPerformance performance(model);

  CurveLinear initialCurve(model);
  TableLookup alternateCurve(model);
  CurveBiquadratic invalidCurve(model);
  ASSERT_TRUE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(initialCurve));
  ASSERT_TRUE(performance.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(initialCurve.handle(), performance.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  ASSERT_TRUE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(alternateCurve));
  ASSERT_TRUE(performance.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(alternateCurve.handle(), performance.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  Model foreignModel;
  CurveLinear foreignCurve(foreignModel);
  EXPECT_FALSE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(invalidCurve));
  EXPECT_FALSE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(foreignCurve));
  ASSERT_TRUE(performance.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(alternateCurve.handle(), performance.crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());

  ScheduleConstant validSchedule(model);
  ASSERT_TRUE(validSchedule.setValue(1.0));
  ASSERT_TRUE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(validSchedule));
  EXPECT_EQ(validSchedule.handle(), performance.evaporativeCondenserBasinHeaterOperatingSchedule().handle());
  ASSERT_TRUE(validSchedule.scheduleTypeLimits());
  EXPECT_EQ("Discrete", validSchedule.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", validSchedule.scheduleTypeLimits()->unitType());
  EXPECT_DOUBLE_EQ(0.0, validSchedule.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, validSchedule.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant continuousSchedule(model);
  ScheduleTypeLimits continuousLimits(model);
  ASSERT_TRUE(continuousLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(continuousLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(continuousLimits.setNumericType("Continuous"));
  ASSERT_TRUE(continuousLimits.setUnitType("Availability"));
  ASSERT_TRUE(continuousSchedule.setScheduleTypeLimits(continuousLimits));

  ScheduleConstant temperatureSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Discrete"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureSchedule.setScheduleTypeLimits(temperatureLimits));

  ScheduleConstant outOfRangeSchedule(model);
  ScheduleTypeLimits outOfRangeLimits(model);
  ASSERT_TRUE(outOfRangeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(outOfRangeLimits.setUpperLimitValue(2.0));
  ASSERT_TRUE(outOfRangeLimits.setNumericType("Discrete"));
  ASSERT_TRUE(outOfRangeLimits.setUnitType("Availability"));
  ASSERT_TRUE(outOfRangeSchedule.setScheduleTypeLimits(outOfRangeLimits));

  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(continuousSchedule));
  EXPECT_FALSE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(temperatureSchedule));
  EXPECT_FALSE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(outOfRangeSchedule));
  EXPECT_FALSE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(foreignSchedule));
  EXPECT_EQ(validSchedule.handle(), performance.evaporativeCondenserBasinHeaterOperatingSchedule().handle());

  auto workspaceImpl = performance.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);
  constexpr auto curveField = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName;
  ASSERT_TRUE(workspaceImpl->setPointer(curveField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(curveField, "Unresolved Crankcase Curve", false));
  EXPECT_FALSE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(invalidCurve));
  EXPECT_EQ("Unresolved Crankcase Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  performance.resetCrankcaseHeaterCapacityFunctionofTemperatureCurve();
  EXPECT_FALSE(performance.crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or("").empty());

  constexpr auto scheduleField = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(scheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(scheduleField, "Unresolved Basin Schedule", false));
  EXPECT_FALSE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(temperatureSchedule));
  EXPECT_EQ("Unresolved Basin Schedule", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));
  ASSERT_TRUE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(validSchedule));
  EXPECT_EQ(validSchedule.handle(), performance.evaporativeCondenserBasinHeaterOperatingSchedule().handle());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_CanonicalizationRepairsOnlyBlankBasinSchedule) {
  const auto idfPath = uniqueCurveFitPerformancePath("epmodel-curve-fit-performance-basin-repair");
  const ScopedCurveFitPerformanceFileRemoval removeIdf(idfPath);

  Model model;
  CoilCoolingDXCurveFitPerformance blank(model);
  CoilCoolingDXCurveFitPerformance unresolved(model);
  ASSERT_TRUE(blank.setName("Blank Curve Fit Basin Schedule"));
  ASSERT_TRUE(unresolved.setName("Unresolved Curve Fit Basin Schedule"));

  constexpr auto field = openstudio::Coil_Cooling_DX_CurveFit_PerformanceFields::EvaporativeCondenserBasinHeaterOperatingScheduleName;
  auto blankImpl = blank.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  auto unresolvedImpl = unresolved.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankImpl);
  ASSERT_TRUE(unresolvedImpl);
  ASSERT_TRUE(blankImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(unresolvedImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(unresolvedImpl->openstudio::detail::IdfObject_Impl::setString(field, "Missing Curve Fit Basin Schedule", false));

  const auto report = model.canonicalize();
  EXPECT_EQ(0u, report.errorCount);
  EXPECT_GE(report.infoCount, 1u);
  EXPECT_EQ(model.alwaysOnDiscreteSchedule().handle(), blank.evaporativeCondenserBasinHeaterOperatingSchedule().handle());
  EXPECT_EQ("Missing Curve Fit Basin Schedule", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));
  const auto repairedHandle = blank.evaporativeCondenserBasinHeaterOperatingSchedule().handle();
  model.canonicalize();
  EXPECT_EQ(repairedHandle, blank.evaporativeCondenserBasinHeaterOperatingSchedule().handle());
  EXPECT_EQ("Missing Curve Fit Basin Schedule", unresolvedImpl->openstudio::detail::IdfObject_Impl::getString(field, false, true).value_or(""));

  Model reloadSource;
  CoilCoolingDXCurveFitPerformance blankOnLoad(reloadSource);
  ASSERT_TRUE(blankOnLoad.setName("Blank Curve Fit Basin Schedule On Load"));
  auto blankOnLoadImpl = blankOnLoad.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(blankOnLoadImpl);
  ASSERT_TRUE(blankOnLoadImpl->setPointer(field, openstudio::Handle(), false));
  ASSERT_TRUE(blankOnLoadImpl->openstudio::detail::IdfObject_Impl::setString(field, "", false));
  ASSERT_TRUE(reloadSource.save(idfPath, true));
  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedBlank = loadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitPerformance>("Blank Curve Fit Basin Schedule On Load");
  ASSERT_TRUE(loadedBlank);
  EXPECT_EQ(loadedModel->alwaysOnDiscreteSchedule().handle(), loadedBlank->evaporativeCondenserBasinHeaterOperatingSchedule().handle());
}

TEST_F(EPModelFixture, CoilCoolingDXCurveFitPerformance_RelationshipsSurviveReloadMutationAndRemoval) {
  const auto firstPath = uniqueCurveFitPerformancePath("epmodel-curve-fit-performance-relationships-first");
  const auto secondPath = uniqueCurveFitPerformancePath("epmodel-curve-fit-performance-relationships-second");
  const ScopedCurveFitPerformanceFileRemoval removeFirst(firstPath);
  const ScopedCurveFitPerformanceFileRemoval removeSecond(secondPath);

  Model model;
  CoilCoolingDXCurveFitOperatingMode baseOperatingMode(model);
  CoilCoolingDXCurveFitOperatingMode originalAlternative1(model);
  CoilCoolingDXCurveFitOperatingMode originalAlternative2(model);
  CoilCoolingDXCurveFitPerformance performance(model, baseOperatingMode);
  CurveLinear originalCurve(model);
  ScheduleConstant originalSchedule(model);
  ASSERT_TRUE(performance.setName("Reloadable Curve Fit Performance"));
  ASSERT_TRUE(baseOperatingMode.setName("Reloadable Curve Fit Base Mode"));
  ASSERT_TRUE(originalAlternative1.setName("Original Curve Fit Alternative Mode 1"));
  ASSERT_TRUE(originalAlternative2.setName("Original Curve Fit Alternative Mode 2"));
  ASSERT_TRUE(originalCurve.setName("Original Curve Fit Crankcase Curve"));
  ASSERT_TRUE(originalSchedule.setName("Original Curve Fit Basin Schedule"));
  ASSERT_TRUE(originalSchedule.setValue(1.0));
  ASSERT_TRUE(performance.setCrankcaseHeaterCapacityFunctionofTemperatureCurve(originalCurve));
  ASSERT_TRUE(performance.setEvaporativeCondenserBasinHeaterOperatingSchedule(originalSchedule));
  ASSERT_TRUE(performance.setAlternativeOperatingMode1(originalAlternative1));
  ASSERT_TRUE(performance.setAlternativeOperatingMode2(originalAlternative2));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPerformance = loadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitPerformance>("Reloadable Curve Fit Performance");
  auto loadedBase = loadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Reloadable Curve Fit Base Mode");
  auto loadedAlternative1 = loadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Original Curve Fit Alternative Mode 1");
  auto loadedAlternative2 = loadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Original Curve Fit Alternative Mode 2");
  auto loadedCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Original Curve Fit Crankcase Curve");
  auto loadedSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original Curve Fit Basin Schedule");
  ASSERT_TRUE(loadedPerformance);
  ASSERT_TRUE(loadedBase);
  ASSERT_TRUE(loadedAlternative1);
  ASSERT_TRUE(loadedAlternative2);
  ASSERT_TRUE(loadedCurve);
  ASSERT_TRUE(loadedSchedule);
  EXPECT_EQ(loadedBase->handle(), loadedPerformance->baseOperatingMode().handle());
  ASSERT_TRUE(loadedPerformance->alternativeOperatingMode1());
  ASSERT_TRUE(loadedPerformance->alternativeOperatingMode2());
  EXPECT_EQ(loadedAlternative1->handle(), loadedPerformance->alternativeOperatingMode1()->handle());
  EXPECT_EQ(loadedAlternative2->handle(), loadedPerformance->alternativeOperatingMode2()->handle());
  ASSERT_TRUE(loadedPerformance->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(loadedCurve->handle(), loadedPerformance->crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(loadedSchedule->handle(), loadedPerformance->evaporativeCondenserBasinHeaterOperatingSchedule().handle());

  CurveLinear replacementCurve(*loadedModel);
  ScheduleConstant replacementSchedule(*loadedModel);
  CoilCoolingDXCurveFitOperatingMode replacementAlternative1(*loadedModel);
  CoilCoolingDXCurveFitOperatingMode replacementAlternative2(*loadedModel);
  ASSERT_TRUE(replacementCurve.setName("Replacement Curve Fit Crankcase Curve"));
  ASSERT_TRUE(replacementSchedule.setName("Replacement Curve Fit Basin Schedule"));
  ASSERT_TRUE(replacementSchedule.setValue(1.0));
  ASSERT_TRUE(replacementAlternative1.setName("Replacement Curve Fit Alternative Mode 1"));
  ASSERT_TRUE(replacementAlternative2.setName("Replacement Curve Fit Alternative Mode 2"));
  ASSERT_TRUE(loadedPerformance->setCrankcaseHeaterCapacityFunctionofTemperatureCurve(replacementCurve));
  ASSERT_TRUE(loadedPerformance->setEvaporativeCondenserBasinHeaterOperatingSchedule(replacementSchedule));
  ASSERT_TRUE(loadedPerformance->setAlternativeOperatingMode1(replacementAlternative1));
  ASSERT_TRUE(loadedPerformance->setAlternativeOperatingMode2(replacementAlternative2));
  loadedPerformance->resetAlternativeOperatingMode2();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPerformance = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitPerformance>("Reloadable Curve Fit Performance");
  auto reloadedCurve = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Replacement Curve Fit Crankcase Curve");
  auto reloadedSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Curve Fit Basin Schedule");
  auto reloadedBase = reloadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Reloadable Curve Fit Base Mode");
  auto reloadedAlternative1 =
    reloadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Replacement Curve Fit Alternative Mode 1");
  auto reloadedAlternative2 =
    reloadedModel->getConcreteModelObjectByName<CoilCoolingDXCurveFitOperatingMode>("Replacement Curve Fit Alternative Mode 2");
  ASSERT_TRUE(reloadedPerformance);
  ASSERT_TRUE(reloadedCurve);
  ASSERT_TRUE(reloadedSchedule);
  ASSERT_TRUE(reloadedBase);
  ASSERT_TRUE(reloadedAlternative1);
  ASSERT_TRUE(reloadedAlternative2);
  ASSERT_TRUE(reloadedPerformance->crankcaseHeaterCapacityFunctionofTemperatureCurve());
  EXPECT_EQ(reloadedCurve->handle(), reloadedPerformance->crankcaseHeaterCapacityFunctionofTemperatureCurve()->handle());
  EXPECT_EQ(reloadedSchedule->handle(), reloadedPerformance->evaporativeCondenserBasinHeaterOperatingSchedule().handle());
  EXPECT_EQ(reloadedBase->handle(), reloadedPerformance->baseOperatingMode().handle());
  ASSERT_TRUE(reloadedPerformance->alternativeOperatingMode1());
  EXPECT_EQ(reloadedAlternative1->handle(), reloadedPerformance->alternativeOperatingMode1()->handle());
  EXPECT_FALSE(reloadedPerformance->alternativeOperatingMode2());

  const auto curveHandle = reloadedCurve->handle();
  const auto scheduleHandle = reloadedSchedule->handle();
  const auto baseHandle = reloadedBase->handle();
  const auto alternative1Handle = reloadedAlternative1->handle();
  const auto alternative2Handle = reloadedAlternative2->handle();
  EXPECT_FALSE(reloadedPerformance->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(curveHandle));
  EXPECT_TRUE(reloadedModel->getObject(scheduleHandle));
  EXPECT_TRUE(reloadedModel->getObject(baseHandle));
  EXPECT_TRUE(reloadedModel->getObject(alternative1Handle));
  EXPECT_TRUE(reloadedModel->getObject(alternative2Handle));
}
