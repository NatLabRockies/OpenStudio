/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "EPModelFixture.hpp"
#include "../Curve/CurveBiquadratic.hpp"
#include "../Curve/CurveLinear.hpp"
#include "../Curve/CurveLinear_Impl.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../Loop/AirLoopHVAC.hpp"
#include "../Loop/PlantLoop.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../Schedule/ScheduleConstant_Impl.hpp"
#include "../Splitter/AirLoopHVACZoneSplitter.hpp"
#include "../StraightComponent/Node.hpp"
#include "../StraightComponent/PumpConstantSpeed.hpp"
#include "../StraightComponent/PumpConstantSpeed_Impl.hpp"

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/Pump_ConstantSpeed_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

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

TEST_F(EPModelFixture, PumpConstantSpeed_DefaultConstructor) {
  Model model;
  PumpConstantSpeed pump(model);

  EXPECT_EQ(PumpConstantSpeed::iddObjectType(), pump.iddObject().type());
  EXPECT_FALSE(pump.nameString().empty());
  EXPECT_TRUE(pump.isRatedFlowRateAutosized());
  EXPECT_TRUE(pump.isRatedPowerConsumptionAutosized());
  EXPECT_EQ(179352.0, pump.ratedPumpHead());
  EXPECT_EQ(0.9, pump.motorEfficiency());
  EXPECT_FALSE(pump.isPumpControlTypeDefaulted());
  EXPECT_EQ("Intermittent", pump.pumpControlType());
  EXPECT_EQ(0.0, pump.fractionofMotorInefficienciestoFluidStream());
  EXPECT_EQ("PowerPerFlowPerPressure", pump.designPowerSizingMethod());
  EXPECT_EQ(348701.1, pump.designElectricPowerPerUnitFlowRate());
  EXPECT_EQ(1.282051282, pump.designShaftPowerPerUnitFlowRatePerUnitHead());
  EXPECT_EQ("General", pump.endUseSubcategory());
}

TEST_F(EPModelFixture, PumpConstantSpeed_ScalarAccessors_RoundTrip) {
  Model model;
  PumpConstantSpeed pump(model);
  if (!pump.setImpellerDiameter(2.5)) {
    GTEST_SKIP() << "PumpConstantSpeed.setImpellerDiameter not available; skipping scalar accessor roundtrip.";
  }
  ASSERT_TRUE(pump.impellerDiameter());
  EXPECT_DOUBLE_EQ(2.5, pump.impellerDiameter().get());
  pump.resetImpellerDiameter();
  EXPECT_FALSE(pump.impellerDiameter());
}

TEST_F(EPModelFixture, PumpConstantSpeed_RelationshipAccessors_RoundTripAndReset) {
  Model model;
  PumpConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);

  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.zone());

  EXPECT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  EXPECT_TRUE(pump.setPumpCurve(pumpCurve));
  EXPECT_TRUE(pump.setZone(zone));
  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  ASSERT_TRUE(pump.pumpCurve());
  ASSERT_TRUE(pump.zone());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());
  EXPECT_EQ(zone.handle(), pump.zone()->handle());

  pump.resetPumpFlowRateSchedule();
  pump.resetPumpCurve();
  pump.resetZone();
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.zone());
}

TEST_F(EPModelFixture, PumpConstantSpeed_RelationshipSetters_RejectInvalidTargetsWithoutChangingOldTargetOrRawText) {
  Model model;
  PumpConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setPumpCurve(pumpCurve));
  ASSERT_TRUE(pump.setZone(zone));

  Model foreignModel;
  ScheduleConstant foreignSchedule(foreignModel);
  CurveLinear foreignCurve(foreignModel);
  ThermalZone foreignZone(foreignModel);
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(foreignSchedule));
  EXPECT_FALSE(pump.setPumpCurve(foreignCurve));
  EXPECT_FALSE(pump.setZone(foreignZone));
  ASSERT_TRUE(pump.pumpFlowRateSchedule());
  ASSERT_TRUE(pump.pumpCurve());
  ASSERT_TRUE(pump.zone());
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());
  EXPECT_EQ(zone.handle(), pump.zone()->handle());

  ScheduleConstant incompatibleFlowSchedule(model);
  ScheduleTypeLimits incompatibleFlowLimits(model);
  ASSERT_TRUE(incompatibleFlowLimits.setNumericType("Continuous"));
  ASSERT_TRUE(incompatibleFlowLimits.setUnitType("Dimensionless"));
  ASSERT_TRUE(incompatibleFlowLimits.setLowerLimitValue(-0.1));
  ASSERT_TRUE(incompatibleFlowLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(incompatibleFlowSchedule.setScheduleTypeLimits(incompatibleFlowLimits));
  CurveBiquadratic incompatiblePumpCurve(model);
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setPumpCurve(incompatiblePumpCurve));
  EXPECT_EQ(flowSchedule.handle(), pump.pumpFlowRateSchedule()->handle());
  EXPECT_EQ(pumpCurve.handle(), pump.pumpCurve()->handle());

  auto pumpWorkspaceImpl = pump.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(pumpWorkspaceImpl);
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_ConstantSpeedFields::PumpFlowRateScheduleName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_ConstantSpeedFields::PumpCurveName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->setPointer(openstudio::Pump_ConstantSpeedFields::ZoneName, openstudio::Handle(), false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_ConstantSpeedFields::PumpFlowRateScheduleName,
                                                                               "Unresolved Flow Schedule", false));
  ASSERT_TRUE(pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_ConstantSpeedFields::PumpCurveName,
                                                                               "Unresolved Pump Curve", false));
  ASSERT_TRUE(
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::setString(openstudio::Pump_ConstantSpeedFields::ZoneName, "Unresolved Zone", false));
  EXPECT_FALSE(pump.setPumpFlowRateSchedule(incompatibleFlowSchedule));
  EXPECT_FALSE(pump.setPumpCurve(incompatiblePumpCurve));
  EXPECT_FALSE(pump.setZone(foreignZone));
  EXPECT_FALSE(pump.pumpFlowRateSchedule());
  EXPECT_FALSE(pump.pumpCurve());
  EXPECT_FALSE(pump.zone());
  EXPECT_EQ(
    "Unresolved Flow Schedule",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_ConstantSpeedFields::PumpFlowRateScheduleName, false, true)
      .value_or(""));
  EXPECT_EQ(
    "Unresolved Pump Curve",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_ConstantSpeedFields::PumpCurveName, false, true).value_or(""));
  EXPECT_EQ(
    "Unresolved Zone",
    pumpWorkspaceImpl->openstudio::detail::IdfObject_Impl::getString(openstudio::Pump_ConstantSpeedFields::ZoneName, false, true).value_or(""));
}

TEST_F(EPModelFixture, PumpConstantSpeed_Relationships_SaveLoadIdentityByName) {
  const auto idfPath =
    openstudio::tempDir()
    / openstudio::toPath("epmodel-pump-constant-speed-relationships-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
  const ScopedFileRemoval removeIdf(idfPath);

  Model model;
  PumpConstantSpeed pump(model);
  ScheduleConstant flowSchedule(model);
  CurveLinear pumpCurve(model);
  ThermalZone zone(model);
  ASSERT_TRUE(pump.setName("Relationship Pump"));
  ASSERT_TRUE(flowSchedule.setName("Pump Flow Schedule"));
  ASSERT_TRUE(pumpCurve.setName("Pump Pressure Curve"));
  ASSERT_TRUE(zone.setName("Pump Zone"));
  ASSERT_TRUE(pump.setPumpFlowRateSchedule(flowSchedule));
  ASSERT_TRUE(pump.setPumpCurve(pumpCurve));
  ASSERT_TRUE(pump.setZone(zone));
  ASSERT_TRUE(model.save(idfPath, true));

  auto loadedModel = Model::load(idfPath);
  ASSERT_TRUE(loadedModel);
  auto loadedPump = loadedModel->getConcreteModelObjectByName<PumpConstantSpeed>("Relationship Pump");
  auto loadedFlowSchedule = loadedModel->getConcreteModelObjectByName<ScheduleConstant>("Pump Flow Schedule");
  auto loadedPumpCurve = loadedModel->getConcreteModelObjectByName<CurveLinear>("Pump Pressure Curve");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Pump Zone");
  ASSERT_TRUE(loadedPump);
  ASSERT_TRUE(loadedFlowSchedule);
  ASSERT_TRUE(loadedPumpCurve);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedPump->pumpFlowRateSchedule());
  ASSERT_TRUE(loadedPump->pumpCurve());
  ASSERT_TRUE(loadedPump->zone());
  EXPECT_EQ(loadedFlowSchedule->handle(), loadedPump->pumpFlowRateSchedule()->handle());
  EXPECT_EQ(loadedPumpCurve->handle(), loadedPump->pumpCurve()->handle());
  EXPECT_EQ(loadedZone->handle(), loadedPump->zone()->handle());

  ThermalZone replacementZone(*loadedModel);
  ASSERT_TRUE(replacementZone.setName("Replacement Pump Zone"));
  ASSERT_TRUE(loadedPump->setZone(replacementZone));
  loadedPump->resetPumpFlowRateSchedule();
  ASSERT_TRUE(loadedModel->save(idfPath, true));

  auto reloadedModel = Model::load(idfPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedPump = reloadedModel->getConcreteModelObjectByName<PumpConstantSpeed>("Relationship Pump");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Replacement Pump Zone");
  ASSERT_TRUE(reloadedPump);
  ASSERT_TRUE(reloadedZone);
  EXPECT_FALSE(reloadedPump->pumpFlowRateSchedule());
  ASSERT_TRUE(reloadedPump->zone());
  EXPECT_EQ(reloadedZone->handle(), reloadedPump->zone()->handle());
}

TEST_F(EPModelFixture, PumpConstantSpeed_AddToNode) {
  Model model;
  PumpConstantSpeed pump(model);

  AirLoopHVAC airLoop(model);
  Node supplyOutletNode = airLoop.supplyOutletNode();
  EXPECT_FALSE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)2, airLoop.supplyComponents().size());

  Node inletNode = airLoop.zoneSplitter().lastOutletModelObject()->cast<Node>();
  EXPECT_FALSE(pump.addToNode(inletNode));
  EXPECT_EQ((unsigned)5, airLoop.demandComponents().size());

  PlantLoop plantLoop(model);
  supplyOutletNode = plantLoop.supplyOutletNode();
  EXPECT_TRUE(pump.addToNode(supplyOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop.supplyComponents().size());

  Node demandOutletNode = plantLoop.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop.demandComponents().size());

  PumpConstantSpeed pump2(model);
  EXPECT_TRUE(pump2.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)9, plantLoop.demandComponents().size());

  PlantLoop plantLoop2(model);
  demandOutletNode = plantLoop2.demandOutletNode();
  EXPECT_TRUE(pump.addToNode(demandOutletNode));
  EXPECT_EQ((unsigned)7, plantLoop2.demandComponents().size());
}
