/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveExponent.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PumpVariableSpeed.hpp"
#include "../StraightComponent/PumpVariableSpeed_Impl.hpp"

#include <utilities/idd/Pump_VariableSpeed_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>
#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>

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

}  // namespace

TEST_F(EPModelFixture, PumpVariableSpeed_DefaultConstructor) {
  Model model;
  PumpVariableSpeed pump(model);
  EXPECT_EQ(openstudio::IddObjectType(openstudio::IddObjectType::Pump_VariableSpeed), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  EXPECT_EQ("Intermittent", pump.pumpControlType());
  EXPECT_DOUBLE_EQ(0.5, pump.skinLossRadiativeFraction());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_DOUBLE_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_DOUBLE_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_DOUBLE_EQ(0.0, pump.designMinimumFlowRateFraction());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpVariableSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  PumpVariableSpeed pump(model);

  EXPECT_TRUE(pump.isRatedFlowRateDefaulted());
  EXPECT_TRUE(pump.setRatedFlowRate(0.31));
  ASSERT_TRUE(pump.ratedFlowRate());
  EXPECT_DOUBLE_EQ(0.31, pump.ratedFlowRate().get());
  EXPECT_FALSE(pump.isRatedFlowRateDefaulted());

  pump.autosizeRatedFlowRate();
  EXPECT_TRUE(pump.isRatedFlowRateAutosized());

  pump.resetRatedFlowRate();
  EXPECT_FALSE(pump.ratedFlowRate());
  EXPECT_FALSE(pump.isRatedFlowRateAutosized());

  EXPECT_TRUE(pump.setRatedPumpHead(420.0));
  EXPECT_DOUBLE_EQ(420.0, pump.ratedPumpHead());
  pump.resetRatedPumpHead();
  EXPECT_TRUE(pump.isRatedPumpHeadDefaulted());

  EXPECT_TRUE(pump.setRatedPowerConsumption(820.0));
  ASSERT_TRUE(pump.ratedPowerConsumption());
  EXPECT_DOUBLE_EQ(820.0, pump.ratedPowerConsumption().get());
  EXPECT_FALSE(pump.isRatedPowerConsumptionDefaulted());

  pump.autosizeRatedPowerConsumption();
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());

  pump.resetRatedPowerConsumption();
  EXPECT_FALSE(pump.ratedPowerConsumption());
  EXPECT_FALSE(pump.isRatedPowerConsumptionAutosized());

  EXPECT_TRUE(pump.isMotorEfficiencyDefaulted());
  EXPECT_TRUE(pump.setMotorEfficiency(0.91));
  EXPECT_DOUBLE_EQ(0.91, pump.motorEfficiency());
  pump.resetMotorEfficiency();
  EXPECT_TRUE(pump.isMotorEfficiencyDefaulted());

  EXPECT_TRUE(pump.isFractionofMotorInefficienciestoFluidStreamDefaulted());
  EXPECT_TRUE(pump.setFractionofMotorInefficienciestoFluidStream(0.4));
  EXPECT_DOUBLE_EQ(0.4, pump.fractionofMotorInefficienciestoFluidStream());
  pump.resetFractionofMotorInefficienciestoFluidStream();
  EXPECT_TRUE(pump.isFractionofMotorInefficienciestoFluidStreamDefaulted());

  EXPECT_TRUE(pump.setCoefficient1ofthePartLoadPerformanceCurve(0.0012));
  EXPECT_DOUBLE_EQ(0.0012, pump.coefficient1ofthePartLoadPerformanceCurve());
  pump.resetCoefficient1ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient2ofthePartLoadPerformanceCurve(0.0034));
  EXPECT_DOUBLE_EQ(0.0034, pump.coefficient2ofthePartLoadPerformanceCurve());
  pump.resetCoefficient2ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient3ofthePartLoadPerformanceCurve(1.23));
  EXPECT_DOUBLE_EQ(1.23, pump.coefficient3ofthePartLoadPerformanceCurve());
  pump.resetCoefficient3ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.setCoefficient4ofthePartLoadPerformanceCurve(-0.12));
  EXPECT_DOUBLE_EQ(-0.12, pump.coefficient4ofthePartLoadPerformanceCurve());
  pump.resetCoefficient4ofthePartLoadPerformanceCurve();

  EXPECT_TRUE(pump.isMinimumFlowRateDefaulted());
  EXPECT_TRUE(pump.setMinimumFlowRate(0.05));
  EXPECT_DOUBLE_EQ(0.05, pump.minimumFlowRate());
  pump.resetMinimumFlowRate();
  EXPECT_TRUE(pump.isMinimumFlowRateDefaulted());

  const auto controlTypes = PumpVariableSpeed::pumpControlTypeValues();
  ASSERT_FALSE(controlTypes.empty());
  EXPECT_TRUE(pump.setPumpControlType(controlTypes.front()));
  EXPECT_EQ(controlTypes.front(), pump.pumpControlType());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  pump.resetPumpControlType();
  EXPECT_TRUE(pump.isPumpControlTypeDefaulted());

  EXPECT_FALSE(pump.impellerDiameter());
  EXPECT_TRUE(pump.setImpellerDiameter(0.12));
  ASSERT_TRUE(pump.impellerDiameter());
  EXPECT_DOUBLE_EQ(0.12, pump.impellerDiameter().get());
  pump.resetImpellerDiameter();
  EXPECT_FALSE(pump.impellerDiameter());

  const auto vfdValues = PumpVariableSpeed::vfdControlTypeValues();
  ASSERT_FALSE(vfdValues.empty());
  EXPECT_TRUE(pump.setVFDControlType(vfdValues.front()));
  ASSERT_TRUE(pump.vFDControlType());
  EXPECT_EQ(vfdValues.front(), pump.vFDControlType().get());
  pump.resetVFDControlType();

  EXPECT_TRUE(pump.setSkinLossRadiativeFraction(0.54));
  EXPECT_DOUBLE_EQ(0.54, pump.skinLossRadiativeFraction());

  const auto designMethods = PumpVariableSpeed::designPowerSizingMethodValues();
  ASSERT_FALSE(designMethods.empty());
  EXPECT_TRUE(pump.setDesignPowerSizingMethod(designMethods.front()));
  EXPECT_EQ(designMethods.front(), pump.designPowerSizingMethod());

  EXPECT_TRUE(pump.setDesignElectricPowerPerUnitFlowRate(348701.0));
  EXPECT_DOUBLE_EQ(348701.0, pump.designElectricPowerPerUnitFlowRate());

  EXPECT_TRUE(pump.setDesignShaftPowerPerUnitFlowRatePerUnitHead(1.1));
  EXPECT_DOUBLE_EQ(1.1, pump.designShaftPowerPerUnitFlowRatePerUnitHead());

  EXPECT_TRUE(pump.setDesignMinimumFlowRateFraction(0.1));
  EXPECT_DOUBLE_EQ(0.1, pump.designMinimumFlowRateFraction());

  EXPECT_TRUE(pump.setEndUseSubcategory("General"));
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpVariableSpeed_RelationshipAccessors_RoundTripAndReset) {
  Model model;
  PumpVariableSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ScheduleConstant rpmSchedule(model);
  ScheduleConstant minimumRPMSchedule(model);
  ScheduleConstant maximumRPMSchedule(model);
  ScheduleConstant minimumPressureSchedule(model);
  ScheduleConstant maximumPressureSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);

  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.pumpRPMSchedule());
  EXPECT_FALSE(pump.minimumRPMSchedule());
  EXPECT_FALSE(pump.maximumRPMSchedule());
  EXPECT_FALSE(pump.minimumPressureSchedule());
  EXPECT_FALSE(pump.maximumPressureSchedule());
  EXPECT_FALSE(pump.zone());

  EXPECT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  EXPECT_TRUE(pump.setPumpCurve(pumpCurve));
  EXPECT_TRUE(pump.setPumpRPMSchedule(rpmSchedule));
  EXPECT_TRUE(pump.setMinimumRPMSchedule(minimumRPMSchedule));
  EXPECT_TRUE(pump.setMaximumRPMSchedule(maximumRPMSchedule));
  EXPECT_TRUE(pump.setMinimumPressureSchedule(minimumPressureSchedule));
  EXPECT_TRUE(pump.setMaximumPressureSchedule(maximumPressureSchedule));
  EXPECT_TRUE(pump.setZone(zone));

  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  ASSERT_TRUE(pump.pumpCurve());
  ASSERT_TRUE(pump.pumpRPMSchedule());
  ASSERT_TRUE(pump.minimumRPMSchedule());
  ASSERT_TRUE(pump.maximumRPMSchedule());
  ASSERT_TRUE(pump.minimumPressureSchedule());
  ASSERT_TRUE(pump.maximumPressureSchedule());
  ASSERT_TRUE(pump.zone());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());
  EXPECT_EQ(rpmSchedule.handle(), pump.pumpRPMSchedule()->handle());
  EXPECT_EQ(minimumRPMSchedule.handle(), pump.minimumRPMSchedule()->handle());
  EXPECT_EQ(maximumRPMSchedule.handle(), pump.maximumRPMSchedule()->handle());
  EXPECT_EQ(minimumPressureSchedule.handle(), pump.minimumPressureSchedule()->handle());
  EXPECT_EQ(maximumPressureSchedule.handle(), pump.maximumPressureSchedule()->handle());
  EXPECT_EQ(zone.handle(), pump.zone()->handle());
  ASSERT_TRUE(minimumRPMSchedule.scheduleTypeLimits());
  ASSERT_TRUE(maximumRPMSchedule.scheduleTypeLimits());
  ASSERT_TRUE(minimumRPMSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", minimumRPMSchedule.scheduleTypeLimits()->numericType().get());
  EXPECT_EQ("RotationsPerMinute", minimumRPMSchedule.scheduleTypeLimits()->unitType());
  EXPECT_FALSE(minimumRPMSchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(minimumRPMSchedule.scheduleTypeLimits()->upperLimitValue());
  ASSERT_TRUE(maximumRPMSchedule.scheduleTypeLimits()->numericType());
  EXPECT_EQ("Continuous", maximumRPMSchedule.scheduleTypeLimits()->numericType().get());
  EXPECT_EQ("RotationsPerMinute", maximumRPMSchedule.scheduleTypeLimits()->unitType());
  EXPECT_FALSE(maximumRPMSchedule.scheduleTypeLimits()->lowerLimitValue());
  EXPECT_FALSE(maximumRPMSchedule.scheduleTypeLimits()->upperLimitValue());

  pump.resetPumpFlowRateSchedule();
  pump.resetPumpCurve();
  pump.resetPumpRPMSchedule();
  pump.resetMinimumRPMSchedule();
  pump.resetMaximumRPMSchedule();
  pump.resetMinimumPressureSchedule();
  pump.resetMaximumPressureSchedule();
  pump.resetZone();
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.pumpRPMSchedule());
  EXPECT_FALSE(pump.minimumRPMSchedule());
  EXPECT_FALSE(pump.maximumRPMSchedule());
  EXPECT_FALSE(pump.minimumPressureSchedule());
  EXPECT_FALSE(pump.maximumPressureSchedule());
  EXPECT_FALSE(pump.zone());
}

TEST_F(EPModelFixture, PumpVariableSpeed_RelationshipSetters_RejectInvalidTargetsWithoutChangingOldTargetOrRawText) {
  Model model;
  PumpVariableSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ScheduleConstant rpmSchedule(model);
  ScheduleConstant minimumRPMSchedule(model);
  ScheduleConstant maximumRPMSchedule(model);
  ScheduleConstant minimumPressureSchedule(model);
  ScheduleConstant maximumPressureSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setPumpCurve(pumpCurve));
  ASSERT_TRUE(pump.setPumpRPMSchedule(rpmSchedule));
  ASSERT_TRUE(pump.setMinimumRPMSchedule(minimumRPMSchedule));
  ASSERT_TRUE(pump.setMaximumRPMSchedule(maximumRPMSchedule));
  ASSERT_TRUE(pump.setMinimumPressureSchedule(minimumPressureSchedule));
  ASSERT_TRUE(pump.setMaximumPressureSchedule(maximumPressureSchedule));
  ASSERT_TRUE(pump.setZone(zone));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveLinear foreignCurve(foreignModel);
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setPumpCurve(foreignCurve));
  EXPECT_FALSE(pump.setPumpRPMSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMinimumRPMSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMaximumRPMSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMinimumPressureSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMaximumPressureSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setZone(foreignZone));
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());
  EXPECT_EQ(rpmSchedule.handle(), pump.pumpRPMSchedule()->handle());
  EXPECT_EQ(minimumRPMSchedule.handle(), pump.minimumRPMSchedule()->handle());
  EXPECT_EQ(maximumRPMSchedule.handle(), pump.maximumRPMSchedule()->handle());
  EXPECT_EQ(minimumPressureSchedule.handle(), pump.minimumPressureSchedule()->handle());
  EXPECT_EQ(maximumPressureSchedule.handle(), pump.maximumPressureSchedule()->handle());
  EXPECT_EQ(zone.handle(), pump.zone()->handle());

  CurveExponent unsupportedCurve(model);
  EXPECT_FALSE(pump.setPumpCurve(unsupportedCurve));
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());

  ScheduleConstant incompatibleFlowSchedule(model);
  ScheduleTypeLimits incompatibleFlowLimits(model);
  ASSERT_TRUE(incompatibleFlowLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleFlowLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleFlowLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleFlowLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleFlowSchedule.setScheduleTypeLimits(incompatibleFlowLimits));
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_FALSE(pump.setMinimumRPMSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setMaximumRPMSchedule(incompatibleFlowSchedule));
  EXPECT_EQ(minimumRPMSchedule.handle(), pump.minimumRPMSchedule()->handle());
  EXPECT_EQ(maximumRPMSchedule.handle(), pump.maximumRPMSchedule()->handle());

  auto pumpWorkspaceImpl = pump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(pumpWorkspaceImpl);
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::PumpFlowRateScheduleName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::PumpCurveName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::PumpRPMScheduleName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::MinimumRPMSchedule, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::MaximumRPMSchedule, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::MinimumPressureSchedule, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::MaximumPressureSchedule, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_VariableSpeedFields::ZoneName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::PumpFlowRateScheduleName,
                                                                               "Unresolved Flow Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::PumpCurveName,
                                                                               "Unresolved Pump Curve", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::PumpRPMScheduleName,
                                                                               "Unresolved RPM Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::MinimumRPMSchedule,
                                                                               "Unresolved Minimum RPM Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::MaximumRPMSchedule,
                                                                               "Unresolved Maximum RPM Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::MinimumPressureSchedule,
                                                                               "Unresolved Minimum Pressure Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::MaximumPressureSchedule,
                                                                               "Unresolved Maximum Pressure Schedule", false));
  ASSERT_TRUE(
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_VariableSpeedFields::ZoneName, "Unresolved Zone", false));
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setPumpCurve(unsupportedCurve));
  EXPECT_FALSE(pump.setPumpRPMSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMinimumRPMSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setMaximumRPMSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setMinimumPressureSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setMaximumPressureSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setZone(foreignZone));
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.pumpRPMSchedule());
  EXPECT_FALSE(pump.minimumRPMSchedule());
  EXPECT_FALSE(pump.maximumRPMSchedule());
  EXPECT_FALSE(pump.minimumPressureSchedule());
  EXPECT_FALSE(pump.maximumPressureSchedule());
  EXPECT_FALSE(pump.zone());
  EXPECT_EQ(
    "Unresolved Flow Schedule",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::PumpFlowRateScheduleName, false, true)
      .value_or(""));
  EXPECT_EQ(
    "Unresolved Pump Curve",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::PumpCurveName, false, true).value_or(""));
  EXPECT_EQ("Unresolved RPM Schedule",
            pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::PumpRPMScheduleName, false, true)
              .value_or(""));
  EXPECT_EQ("Unresolved Minimum RPM Schedule",
            pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::MinimumRPMSchedule, false, true)
              .value_or(""));
  EXPECT_EQ("Unresolved Maximum RPM Schedule",
            pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::MaximumRPMSchedule, false, true)
              .value_or(""));
  EXPECT_EQ(
    "Unresolved Minimum Pressure Schedule",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::MinimumPressureSchedule, false, true)
      .value_or(""));
  EXPECT_EQ(
    "Unresolved Maximum Pressure Schedule",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::MaximumPressureSchedule, false, true)
      .value_or(""));
  EXPECT_EQ(
    "Unresolved Zone",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_VariableSpeedFields::ZoneName, false, true).value_or(""));
}

TEST_F(EPModelFixture, PumpVariableSpeed_Relationships_SaveLoadIdentityByName) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-pump-variable-speed-relationships-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  PumpVariableSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  ScheduleConstant rpmSchedule(model);
  ScheduleConstant minimumRPMSchedule(model);
  ScheduleConstant maximumRPMSchedule(model);
  ScheduleConstant minimumPressureSchedule(model);
  ScheduleConstant maximumPressureSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);
  ASSERT_TRUE(pump.setName("Relationship Pump"));
  ASSERT_TRUE(flowSchedule.setName("Pump Flow Schedule"));
  ASSERT_TRUE(rpmSchedule.setName("Pump RPM Schedule"));
  ASSERT_TRUE(minimumRPMSchedule.setName("Pump Minimum RPM Schedule"));
  ASSERT_TRUE(maximumRPMSchedule.setName("Pump Maximum RPM Schedule"));
  ASSERT_TRUE(minimumPressureSchedule.setName("Pump Minimum Pressure Schedule"));
  ASSERT_TRUE(maximumPressureSchedule.setName("Pump Maximum Pressure Schedule"));
  ASSERT_TRUE(pumpCurve.setName("Pump Pressure Curve"));
  ASSERT_TRUE(zone.setName("Pump Zone"));
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setPumpCurve(pumpCurve));
  ASSERT_TRUE(pump.setPumpRPMSchedule(rpmSchedule));
  ASSERT_TRUE(pump.setMinimumRPMSchedule(minimumRPMSchedule));
  ASSERT_TRUE(pump.setMaximumRPMSchedule(maximumRPMSchedule));
  ASSERT_TRUE(pump.setMinimumPressureSchedule(minimumPressureSchedule));
  ASSERT_TRUE(pump.setMaximumPressureSchedule(maximumPressureSchedule));
  ASSERT_TRUE(pump.setZone(zone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPump = loadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Relationship Pump");
  auto loadedFlowSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Flow Schedule");
  auto loadedRPMSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump RPM Schedule");
  auto loadedMinimumRPMSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Minimum RPM Schedule");
  auto loadedMaximumRPMSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Maximum RPM Schedule");
  auto loadedMinimumPressureSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Minimum Pressure Schedule");
  auto loadedMaximumPressureSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Maximum Pressure Schedule");
  auto loadedPumpCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Pump Pressure Curve");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Pump Zone");
  ASSERT_TRUE(loadedPump);
  ASSERT_TRUE(loadedFlowSchedule);
  ASSERT_TRUE(loadedRPMSchedule);
  ASSERT_TRUE(loadedMinimumRPMSchedule);
  ASSERT_TRUE(loadedMaximumRPMSchedule);
  ASSERT_TRUE(loadedMinimumPressureSchedule);
  ASSERT_TRUE(loadedMaximumPressureSchedule);
  ASSERT_TRUE(loadedPumpCurve);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedPump->pumpFlowRateSchedule());
  ASSERT_TRUE(loadedPump->pumpCurve());
  ASSERT_TRUE(loadedPump->pumpRPMSchedule());
  ASSERT_TRUE(loadedPump->minimumRPMSchedule());
  ASSERT_TRUE(loadedPump->maximumRPMSchedule());
  ASSERT_TRUE(loadedPump->minimumPressureSchedule());
  ASSERT_TRUE(loadedPump->maximumPressureSchedule());
  ASSERT_TRUE(loadedPump->zone());
  EXPECT_EQ(loadedFlowSchedule->handle(), loadedPump->pumpFlowRateSchedule()->handle());
  EXPECT_EQ(loadedPumpCurve->handle(), loadedPump->pumpCurve()->handle());
  EXPECT_EQ(loadedRPMSchedule->handle(), loadedPump->pumpRPMSchedule()->handle());
  EXPECT_EQ(loadedMinimumRPMSchedule->handle(), loadedPump->minimumRPMSchedule()->handle());
  EXPECT_EQ(loadedMaximumRPMSchedule->handle(), loadedPump->maximumRPMSchedule()->handle());
  EXPECT_EQ(loadedMinimumPressureSchedule->handle(), loadedPump->minimumPressureSchedule()->handle());
  EXPECT_EQ(loadedMaximumPressureSchedule->handle(), loadedPump->maximumPressureSchedule()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedPump->zone()->handle());

  ScheduleConstant replacementMinimumRPMSchedule(*loadedModel);
  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementMinimumRPMSchedule.setName("Replacement Minimum RPM Schedule"));
  ASSERT_TRUE(replacementZone.setName("Replacement Pump Zone"));
  ASSERT_TRUE(loadedPump->setMinimumRPMSchedule(replacementMinimumRPMSchedule));
  loadedPump->resetMaximumRPMSchedule();
  ASSERT_TRUE(loadedPump->setZone(replacementZone));
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPump = reloadedModel->getConcreteModelObjectByName<PumpVariableSpeed>("Relationship Pump");
  auto reloadedMinimumRPMSchedule = reloadedModel->getConcreteModelObjectByName<ScheduleConstant>("Replacement Minimum RPM Schedule");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement Pump Zone");
  ASSERT_TRUE(reloadedPump);
  ASSERT_TRUE(reloadedMinimumRPMSchedule);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedPump->minimumRPMSchedule());
  EXPECT_EQ(reloadedMinimumRPMSchedule->handle(), reloadedPump->minimumRPMSchedule()->handle());
  EXPECT_FALSE(reloadedPump->maximumRPMSchedule());
  ASSERT_TRUE(reloadedPump->zone());
  EXPECT_EQ(reloadedZone->handle(), reloadedPump->zone()->handle());
}

TEST_F(EPModelFixture, PumpVariableSpeed_AddToNode_PlantOnly) {
  Model model;
  PumpVariableSpeed pump(model);

  AirLoopHVAC airLoop(model);
  auto airSupplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(airSupplyOutletNode));
  EXPECT_EQ(2u, airLoop.supplyComponents().size());

  PlantLoop plantLoop(model);
  auto supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ(7u, plantLoop.supplyComponents().size());

  auto demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ(7u, plantLoop.demandComponents().size());

  PumpVariableSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(demandOutletNode));
  EXPECT_EQ(9u, plantLoop.demandComponents().size());
}
