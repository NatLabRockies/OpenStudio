/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneHVAC_EnergyRecoveryVentilator_Controller_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include "EPModelFixture.hpp"

#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../Curve/TableLookup.hpp"
#include "../Model.hpp"
#include "../ParentObject/ZoneHVACEnergyRecoveryVentilatorController.hpp"
#include "../ParentObject/ZoneHVACEnergyRecoveryVentilatorController_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator.hpp"
#include "../ZoneHVACComponent/ZoneHVACEnergyRecoveryVentilator_Impl.hpp"

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedERVControllerFileRemoval
{
 public:
  explicit ScopedERVControllerFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedERVControllerFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueERVControllerPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, API_ZoneHVACEnergyRecoveryVentilatorController_DefaultConstructor) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);
  EXPECT_FALSE(controller.electronicEnthalpyLimitCurve());
  EXPECT_FALSE(controller.timeofDayEconomizerFlowControlSchedule());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilatorController_RelationshipRoundTripValidationAndReset) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);

  CurveLinear linear(model);
  TableLookup table(model);
  CurveBiquadratic bivariate(model);
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(linear));
  ASSERT_TRUE(controller.electronicEnthalpyLimitCurve());
  EXPECT_EQ(linear.handle(), controller.electronicEnthalpyLimitCurve()->handle());
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(table));
  ASSERT_TRUE(controller.electronicEnthalpyLimitCurve());
  EXPECT_EQ(table.handle(), controller.electronicEnthalpyLimitCurve()->handle());

  Model foreignModel;
  CurveLinear foreignCurve(foreignModel);
  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(bivariate));
  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(foreignCurve));
  ASSERT_TRUE(controller.electronicEnthalpyLimitCurve());
  EXPECT_EQ(table.handle(), controller.electronicEnthalpyLimitCurve()->handle());

  ScheduleConstant validSchedule(model);
  ASSERT_TRUE(validSchedule.setValue(0.5));
  ASSERT_TRUE(controller.setTimeofDayEconomizerFlowControlSchedule(validSchedule));
  ASSERT_TRUE(controller.timeofDayEconomizerFlowControlSchedule());
  EXPECT_EQ(validSchedule.handle(), controller.timeofDayEconomizerFlowControlSchedule()->handle());
  ASSERT_TRUE(validSchedule.scheduleTypeLimits());
  EXPECT_EQ("Continuous", validSchedule.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(validSchedule.scheduleTypeLimits()->isUnitTypeDefaulted());
  EXPECT_DOUBLE_EQ(0.0, validSchedule.scheduleTypeLimits()->lowerLimitValue().value_or(-1.0));
  EXPECT_DOUBLE_EQ(1.0, validSchedule.scheduleTypeLimits()->upperLimitValue().value_or(-1.0));

  ScheduleConstant discreteSchedule(model);
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setUnitType("Availability"));
  ASSERT_TRUE(discreteSchedule.setScheduleTypeLimits(discreteLimits));

  ScheduleConstant temperatureSchedule(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(temperatureLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(temperatureSchedule.setScheduleTypeLimits(temperatureLimits));

  ScheduleConstant outOfRangeSchedule(model);
  ScheduleTypeLimits outOfRangeLimits(model);
  ASSERT_TRUE(outOfRangeLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(outOfRangeLimits.setUpperLimitValue(2.0));
  ASSERT_TRUE(outOfRangeLimits.setNumericType("Continuous"));
  outOfRangeLimits.resetUnitType();
  ASSERT_TRUE(outOfRangeSchedule.setScheduleTypeLimits(outOfRangeLimits));

  ScheduleConstant foreignSchedule(foreignModel);
  EXPECT_FALSE(controller.setTimeofDayEconomizerFlowControlSchedule(discreteSchedule));
  EXPECT_FALSE(controller.setTimeofDayEconomizerFlowControlSchedule(temperatureSchedule));
  EXPECT_FALSE(controller.setTimeofDayEconomizerFlowControlSchedule(outOfRangeSchedule));
  EXPECT_FALSE(controller.setTimeofDayEconomizerFlowControlSchedule(foreignSchedule));
  ASSERT_TRUE(controller.timeofDayEconomizerFlowControlSchedule());
  EXPECT_EQ(validSchedule.handle(), controller.timeofDayEconomizerFlowControlSchedule()->handle());

  controller.resetElectronicEnthalpyLimitCurve();
  controller.resetTimeofDayEconomizerFlowControlSchedule();
  EXPECT_FALSE(controller.electronicEnthalpyLimitCurve());
  EXPECT_FALSE(controller.timeofDayEconomizerFlowControlSchedule());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilatorController_UnresolvedRawPreservationAndReset) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);
  auto workspaceImpl = controller.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);

  constexpr auto curveField = openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::ElectronicEnthalpyLimitCurveName;
  constexpr auto scheduleField = openstudio::ZoneHVAC_EnergyRecoveryVentilator_ControllerFields::TimeofDayEconomizerFlowControlScheduleName;
  ASSERT_TRUE(workspaceImpl->setPointer(curveField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->setPointer(scheduleField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(curveField, "Unresolved ERV Enthalpy Curve", false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(scheduleField, "Unresolved ERV Economizer Schedule", false));

  CurveBiquadratic invalidCurve(model);
  ScheduleConstant invalidSchedule(model);
  ScheduleTypeLimits invalidLimits(model);
  ASSERT_TRUE(invalidLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(invalidLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(invalidLimits.setNumericType("Continuous"));
  ASSERT_TRUE(invalidLimits.setUnitType("Temperature"));
  ASSERT_TRUE(invalidSchedule.setScheduleTypeLimits(invalidLimits));

  EXPECT_FALSE(controller.setElectronicEnthalpyLimitCurve(invalidCurve));
  EXPECT_FALSE(controller.setTimeofDayEconomizerFlowControlSchedule(invalidSchedule));
  EXPECT_EQ("Unresolved ERV Enthalpy Curve", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or(""));
  EXPECT_EQ("Unresolved ERV Economizer Schedule",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or(""));

  controller.resetElectronicEnthalpyLimitCurve();
  controller.resetTimeofDayEconomizerFlowControlSchedule();
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(curveField, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(scheduleField, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, ZoneHVACEnergyRecoveryVentilatorController_ReloadPostLoadMutationAndResourceLifetime) {
  const auto firstPath = uniqueERVControllerPath("epmodel-erv-controller-relationships-first");
  const auto secondPath = uniqueERVControllerPath("epmodel-erv-controller-relationships-second");
  const ScopedERVControllerFileRemoval removeFirst(firstPath);
  const ScopedERVControllerFileRemoval removeSecond(secondPath);

  Model model;
  ZoneHVACEnergyRecoveryVentilator ventilator(model);
  ZoneHVACEnergyRecoveryVentilatorController controller(model);
  CurveLinear originalCurve(model);
  ScheduleConstant originalSchedule(model);
  ASSERT_TRUE(ventilator.setName("Relationship ERV"));
  ASSERT_TRUE(controller.setName("Relationship ERV Controller"));
  ASSERT_TRUE(originalCurve.setName("Original ERV Enthalpy Curve"));
  ASSERT_TRUE(originalSchedule.setName("Original ERV Economizer Schedule"));
  ASSERT_TRUE(originalSchedule.setValue(0.25));
  ASSERT_TRUE(controller.setElectronicEnthalpyLimitCurve(originalCurve));
  ASSERT_TRUE(controller.setTimeofDayEconomizerFlowControlSchedule(originalSchedule));
  ASSERT_TRUE(ventilator.setController(controller));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedVentilator = loadedModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilator>("Relationship ERV");
  auto loadedController = loadedModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilatorController>("Relationship ERV Controller");
  auto loadedOriginalCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Original ERV Enthalpy Curve");
  auto loadedOriginalSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Original ERV Economizer Schedule");
  ASSERT_TRUE(loadedVentilator);
  ASSERT_TRUE(loadedController);
  ASSERT_TRUE(loadedOriginalCurve);
  ASSERT_TRUE(loadedOriginalSchedule);
  ASSERT_TRUE(loadedVentilator->controller());
  EXPECT_EQ(loadedController->handle(), loadedVentilator->controller()->handle());
  ASSERT_TRUE(loadedController->electronicEnthalpyLimitCurve());
  EXPECT_EQ(loadedOriginalCurve->handle(), loadedController->electronicEnthalpyLimitCurve()->handle());
  ASSERT_TRUE(loadedController->timeofDayEconomizerFlowControlSchedule());
  EXPECT_EQ(loadedOriginalSchedule->handle(), loadedController->timeofDayEconomizerFlowControlSchedule()->handle());

  CurveLinear replacementCurve(*loadedModel);
  ScheduleConstant replacementSchedule(*loadedModel);
  ASSERT_TRUE(replacementCurve.setName("Replacement ERV Enthalpy Curve"));
  ASSERT_TRUE(replacementSchedule.setName("Replacement ERV Economizer Schedule"));
  ASSERT_TRUE(replacementSchedule.setValue(0.75));
  ASSERT_TRUE(loadedController->setElectronicEnthalpyLimitCurve(replacementCurve));
  ASSERT_TRUE(loadedController->setTimeofDayEconomizerFlowControlSchedule(replacementSchedule));
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedVentilator = reloadedModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilator>("Relationship ERV");
  auto reloadedController = reloadedModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilatorController>("Relationship ERV Controller");
  auto reloadedReplacementCurve = reloadedModel->getConcreteModelObjectByName<CurveLinear>("Replacement ERV Enthalpy Curve");
  auto reloadedReplacementSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement ERV Economizer Schedule");
  ASSERT_TRUE(reloadedVentilator);
  ASSERT_TRUE(reloadedController);
  ASSERT_TRUE(reloadedReplacementCurve);
  ASSERT_TRUE(reloadedReplacementSchedule);
  ASSERT_TRUE(reloadedVentilator->controller());
  EXPECT_EQ(reloadedController->handle(), reloadedVentilator->controller()->handle());
  ASSERT_TRUE(reloadedController->electronicEnthalpyLimitCurve());
  EXPECT_EQ(reloadedReplacementCurve->handle(), reloadedController->electronicEnthalpyLimitCurve()->handle());
  ASSERT_TRUE(reloadedController->timeofDayEconomizerFlowControlSchedule());
  EXPECT_EQ(reloadedReplacementSchedule->handle(), reloadedController->timeofDayEconomizerFlowControlSchedule()->handle());

  reloadedController->resetElectronicEnthalpyLimitCurve();
  reloadedController->resetTimeofDayEconomizerFlowControlSchedule();
  ASSERT_TRUE(reloadedModel->save(secondPath, true));

  auto resetModel = Model::load(secondPath);
  ASSERT_TRUE(resetModel);
  auto resetVentilator = resetModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilator>("Relationship ERV");
  auto resetController = resetModel->getConcreteModelObjectByName<ZoneHVACEnergyRecoveryVentilatorController>("Relationship ERV Controller");
  auto resetOriginalCurve = resetModel->getConcreteModelObjectByName<CurveLinear>("Original ERV Enthalpy Curve");
  auto resetReplacementCurve = resetModel->getConcreteModelObjectByName<CurveLinear>("Replacement ERV Enthalpy Curve");
  auto resetOriginalSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Original ERV Economizer Schedule");
  auto resetReplacementSchedule = resetModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement ERV Economizer Schedule");
  ASSERT_TRUE(resetVentilator);
  ASSERT_TRUE(resetController);
  ASSERT_TRUE(resetOriginalCurve);
  ASSERT_TRUE(resetReplacementCurve);
  ASSERT_TRUE(resetOriginalSchedule);
  ASSERT_TRUE(resetReplacementSchedule);
  EXPECT_FALSE(resetController->electronicEnthalpyLimitCurve());
  EXPECT_FALSE(resetController->timeofDayEconomizerFlowControlSchedule());
  ASSERT_TRUE(resetVentilator->controller());
  EXPECT_EQ(resetController->handle(), resetVentilator->controller()->handle());

  ASSERT_TRUE(resetController->setElectronicEnthalpyLimitCurve(*resetReplacementCurve));
  ASSERT_TRUE(resetController->setTimeofDayEconomizerFlowControlSchedule(*resetReplacementSchedule));
  EXPECT_FALSE(resetVentilator->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetController->handle()));
  ASSERT_TRUE(resetController->electronicEnthalpyLimitCurve());
  EXPECT_EQ(resetReplacementCurve->handle(), resetController->electronicEnthalpyLimitCurve()->handle());
  ASSERT_TRUE(resetController->timeofDayEconomizerFlowControlSchedule());
  EXPECT_EQ(resetReplacementSchedule->handle(), resetController->timeofDayEconomizerFlowControlSchedule()->handle());
  EXPECT_TRUE(resetModel->getObject(resetOriginalCurve->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementCurve->handle()));
  EXPECT_TRUE(resetModel->getObject(resetOriginalSchedule->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementSchedule->handle()));
  EXPECT_FALSE(resetController->remove().empty());
  EXPECT_TRUE(resetModel->getObject(resetOriginalCurve->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementCurve->handle()));
  EXPECT_TRUE(resetModel->getObject(resetOriginalSchedule->handle()));
  EXPECT_TRUE(resetModel->getObject(resetReplacementSchedule->handle()));
}

TEST_F(EPModelFixture, API_ZoneHVACEnergyRecoveryVentilatorController_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACEnergyRecoveryVentilatorController controller(model);

  ASSERT_TRUE(controller.setTemperatureHighLimit(35.75));
  ASSERT_TRUE(controller.temperatureHighLimit());
  EXPECT_NEAR(35.75, *controller.temperatureHighLimit(), 1e-9);
  controller.resetTemperatureHighLimit();
  EXPECT_FALSE(controller.temperatureHighLimit());

  ASSERT_TRUE(controller.setTemperatureLowLimit(5.0));
  ASSERT_TRUE(controller.temperatureLowLimit());
  EXPECT_NEAR(5.0, *controller.temperatureLowLimit(), 1e-9);
  controller.resetTemperatureLowLimit();
  EXPECT_FALSE(controller.temperatureLowLimit());

  ASSERT_TRUE(controller.setEnthalpyHighLimit(42000.0));
  ASSERT_TRUE(controller.enthalpyHighLimit());
  EXPECT_NEAR(42000.0, *controller.enthalpyHighLimit(), 1e-9);
  controller.resetEnthalpyHighLimit();
  EXPECT_FALSE(controller.enthalpyHighLimit());

  ASSERT_TRUE(controller.setDewpointTemperatureLimit(15.5));
  ASSERT_TRUE(controller.dewpointTemperatureLimit());
  EXPECT_NEAR(15.5, *controller.dewpointTemperatureLimit(), 1e-9);
  controller.resetDewpointTemperatureLimit();
  EXPECT_FALSE(controller.dewpointTemperatureLimit());

  const auto temperatureLimitValues = ZoneHVACEnergyRecoveryVentilatorController::exhaustAirTemperatureLimitValues();
  ASSERT_FALSE(temperatureLimitValues.empty());
  EXPECT_TRUE(controller.setExhaustAirTemperatureLimit(temperatureLimitValues.front()));
  EXPECT_EQ(temperatureLimitValues.front(), controller.exhaustAirTemperatureLimit());

  const auto enthalpyLimitValues = ZoneHVACEnergyRecoveryVentilatorController::exhaustAirEnthalpyLimitValues();
  ASSERT_FALSE(enthalpyLimitValues.empty());
  EXPECT_TRUE(controller.setExhaustAirEnthalpyLimit(enthalpyLimitValues.front()));
  EXPECT_EQ(enthalpyLimitValues.front(), controller.exhaustAirEnthalpyLimit());

  EXPECT_TRUE(controller.setHighHumidityControlFlag(true));
  EXPECT_TRUE(controller.highHumidityControlFlag());
  EXPECT_TRUE(controller.setHighHumidityControlFlag(false));
  EXPECT_FALSE(controller.highHumidityControlFlag());

  ASSERT_TRUE(controller.setHighHumidityOutdoorAirFlowRatio(1.41));
  EXPECT_NEAR(1.41, controller.highHumidityOutdoorAirFlowRatio(), 1e-9);

  EXPECT_TRUE(controller.setControlHighIndoorHumidityBasedOnOutdoorHumidityRatio(false));
  EXPECT_FALSE(controller.controlHighIndoorHumidityBasedOnOutdoorHumidityRatio());
}
