/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <utilities/core/Filesystem.hpp>
#include <utilities/core/UUID.hpp>
#include <utilities/idd/ZoneHVAC_IdealLoadsAirSystem_FieldEnums.hxx>
#include <utilities/idf/WorkspaceObject_Impl.hpp>

#include "EPModelFixture.hpp"
#include "../HVACComponent/ThermalZone.hpp"
#include "../HVACComponent/ThermalZone_Impl.hpp"
#include "../ResourceObject/ScheduleTypeLimits.hpp"
#include "../Schedule/ScheduleCompact.hpp"
#include "../Schedule/ScheduleCompact_Impl.hpp"
#include "../Schedule/ScheduleConstant.hpp"
#include "../StraightComponent/Node.hpp"
#include "../ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem.hpp"
#include "../ZoneHVACComponent/ZoneHVACIdealLoadsAirSystem_Impl.hpp"

#include <utility>

using namespace openstudio::epmodel;

namespace {
class ScopedIdealLoadsFileRemoval
{
 public:
  explicit ScopedIdealLoadsFileRemoval(openstudio::path path) : m_path(std::move(path)) {}
  ~ScopedIdealLoadsFileRemoval() {
    boost::system::error_code error;
    boost::filesystem::remove(m_path, error);
  }

 private:
  openstudio::path m_path;
};

openstudio::path uniqueIdealLoadsPath(const std::string& stem) {
  return openstudio::tempDir() / openstudio::toPath(stem + "-" + openstudio::removeBraces(openstudio::createUUID()) + ".idf");
}
}  // namespace

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_DefaultConstructor) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_EQ("DistrictHeatingWater", system.heatingFuelType());
  EXPECT_EQ("DistrictCooling", system.coolingFuelType());
  EXPECT_DOUBLE_EQ(50.0, system.maximumHeatingSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(13.0, system.minimumCoolingSupplyAirTemperature());
  EXPECT_DOUBLE_EQ(0.0156, system.maximumHeatingSupplyAirHumidityRatio());
  EXPECT_DOUBLE_EQ(0.0077, system.minimumCoolingSupplyAirHumidityRatio());
  EXPECT_EQ("NoLimit", system.heatingLimit());
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());
  EXPECT_FALSE(system.maximumSensibleHeatingCapacity());
  EXPECT_EQ("NoLimit", system.coolingLimit());
  EXPECT_FALSE(system.maximumCoolingAirFlowRate());
  EXPECT_FALSE(system.maximumTotalCoolingCapacity());
  EXPECT_EQ("ConstantSensibleHeatRatio", system.dehumidificationControlType());
  EXPECT_DOUBLE_EQ(0.7, system.coolingSensibleHeatRatio());
  EXPECT_EQ("None", system.humidificationControlType());
  EXPECT_EQ("None", system.demandControlledVentilationType());
  EXPECT_EQ("NoEconomizer", system.outdoorAirEconomizerType());
  EXPECT_EQ("None", system.heatRecoveryType());
  EXPECT_DOUBLE_EQ(0.7, system.sensibleHeatRecoveryEffectiveness());
  EXPECT_DOUBLE_EQ(0.65, system.latentHeatRecoveryEffectiveness());
  EXPECT_FALSE(system.availabilitySchedule());
  EXPECT_FALSE(system.heatingAvailabilitySchedule());
  EXPECT_FALSE(system.coolingAvailabilitySchedule());
  EXPECT_FALSE(system.heatingFuelEfficiencySchedule());
  EXPECT_FALSE(system.coolingFuelEfficiencySchedule());
  EXPECT_EQ("DistrictHeatingWater", system.heatingFuelType());
  EXPECT_EQ("DistrictCooling", system.coolingFuelType());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ScheduleRelationshipsRoundTripValidationAndReset) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);

  ScheduleCompact availability(model);
  ScheduleCompact heatingAvailability(model);
  ScheduleCompact coolingAvailability(model);
  ScheduleCompact heatingFuelEfficiency(model);
  ScheduleCompact coolingFuelEfficiency(model);
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  ASSERT_TRUE(heatingAvailability.setToConstantValue(1.0));
  ASSERT_TRUE(coolingAvailability.setToConstantValue(0.0));
  ASSERT_TRUE(heatingFuelEfficiency.setToConstantValue(0.92));
  ASSERT_TRUE(coolingFuelEfficiency.setToConstantValue(3.1));

  ASSERT_TRUE(system.setAvailabilitySchedule(availability));
  ASSERT_TRUE(system.setHeatingAvailabilitySchedule(heatingAvailability));
  ASSERT_TRUE(system.setCoolingAvailabilitySchedule(coolingAvailability));
  ASSERT_TRUE(system.setHeatingFuelEfficiencySchedule(heatingFuelEfficiency));
  ASSERT_TRUE(system.setCoolingFuelEfficiencySchedule(coolingFuelEfficiency));

  ASSERT_TRUE(system.availabilitySchedule());
  ASSERT_TRUE(system.heatingAvailabilitySchedule());
  ASSERT_TRUE(system.coolingAvailabilitySchedule());
  ASSERT_TRUE(system.heatingFuelEfficiencySchedule());
  ASSERT_TRUE(system.coolingFuelEfficiencySchedule());
  EXPECT_EQ(availability.handle(), system.availabilitySchedule()->handle());
  EXPECT_EQ(heatingAvailability.handle(), system.heatingAvailabilitySchedule()->handle());
  EXPECT_EQ(coolingAvailability.handle(), system.coolingAvailabilitySchedule()->handle());
  EXPECT_EQ(heatingFuelEfficiency.handle(), system.heatingFuelEfficiencySchedule()->handle());
  EXPECT_EQ(coolingFuelEfficiency.handle(), system.coolingFuelEfficiencySchedule()->handle());

  ASSERT_TRUE(availability.scheduleTypeLimits());
  EXPECT_EQ("Discrete", availability.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_EQ("Availability", availability.scheduleTypeLimits()->unitType());
  ASSERT_TRUE(heatingFuelEfficiency.scheduleTypeLimits());
  EXPECT_EQ("Continuous", heatingFuelEfficiency.scheduleTypeLimits()->numericType().value_or(""));
  EXPECT_TRUE(heatingFuelEfficiency.scheduleTypeLimits()->isUnitTypeDefaulted());

  EXPECT_FALSE(system.setAvailabilitySchedule(heatingFuelEfficiency));
  EXPECT_FALSE(system.setHeatingAvailabilitySchedule(heatingFuelEfficiency));
  EXPECT_FALSE(system.setCoolingAvailabilitySchedule(heatingFuelEfficiency));
  EXPECT_FALSE(system.setHeatingFuelEfficiencySchedule(availability));
  EXPECT_FALSE(system.setCoolingFuelEfficiencySchedule(availability));

  Model foreignModel;
  ScheduleCompact foreignSchedule(foreignModel);
  ASSERT_TRUE(foreignSchedule.setToConstantValue(1.0));
  EXPECT_FALSE(system.setAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(system.setHeatingAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(system.setCoolingAvailabilitySchedule(foreignSchedule));
  EXPECT_FALSE(system.setHeatingFuelEfficiencySchedule(foreignSchedule));
  EXPECT_FALSE(system.setCoolingFuelEfficiencySchedule(foreignSchedule));

  EXPECT_EQ(availability.handle(), system.availabilitySchedule()->handle());
  EXPECT_EQ(heatingAvailability.handle(), system.heatingAvailabilitySchedule()->handle());
  EXPECT_EQ(coolingAvailability.handle(), system.coolingAvailabilitySchedule()->handle());
  EXPECT_EQ(heatingFuelEfficiency.handle(), system.heatingFuelEfficiencySchedule()->handle());
  EXPECT_EQ(coolingFuelEfficiency.handle(), system.coolingFuelEfficiencySchedule()->handle());

  system.resetAvailabilitySchedule();
  system.resetHeatingAvailabilitySchedule();
  system.resetCoolingAvailabilitySchedule();
  system.resetHeatingFuelEfficiencySchedule();
  system.resetCoolingFuelEfficiencySchedule();
  EXPECT_FALSE(system.availabilitySchedule());
  EXPECT_FALSE(system.heatingAvailabilitySchedule());
  EXPECT_FALSE(system.coolingAvailabilitySchedule());
  EXPECT_FALSE(system.heatingFuelEfficiencySchedule());
  EXPECT_FALSE(system.coolingFuelEfficiencySchedule());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ScheduleResetClearsMalformedRawRelationships) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);
  auto workspaceImpl = system.getImpl<openstudio::detail::WorkspaceObject_Impl>();
  ASSERT_TRUE(workspaceImpl);

  constexpr auto availabilityField = openstudio::ZoneHVAC_IdealLoadsAirSystemFields::AvailabilityScheduleName;
  constexpr auto heatingAvailabilityField = openstudio::ZoneHVAC_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName;
  constexpr auto coolingAvailabilityField = openstudio::ZoneHVAC_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName;
  constexpr auto heatingFuelField = openstudio::ZoneHVAC_IdealLoadsAirSystemFields::HeatingFuelEfficiencyScheduleName;
  constexpr auto coolingFuelField = openstudio::ZoneHVAC_IdealLoadsAirSystemFields::CoolingFuelEfficiencyScheduleName;

  ASSERT_TRUE(workspaceImpl->setPointer(availabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->setPointer(heatingAvailabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->setPointer(coolingAvailabilityField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->setPointer(heatingFuelField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->setPointer(coolingFuelField, openstudio::Handle(), false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(availabilityField, "Unresolved General Schedule", false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatingAvailabilityField, "Unresolved Heating Availability", false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(coolingAvailabilityField, "Unresolved Cooling Availability", false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(heatingFuelField, "Unresolved Heating Efficiency", false));
  ASSERT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::setString(coolingFuelField, "Unresolved Cooling Efficiency", false));

  ScheduleConstant invalidAvailability(model);
  ScheduleTypeLimits temperatureLimits(model);
  ASSERT_TRUE(temperatureLimits.setNumericType("Continuous"));
  ASSERT_TRUE(temperatureLimits.setUnitType("Temperature"));
  ASSERT_TRUE(invalidAvailability.setScheduleTypeLimits(temperatureLimits));
  ScheduleConstant invalidFuelEfficiency(model);
  ScheduleTypeLimits discreteLimits(model);
  ASSERT_TRUE(discreteLimits.setNumericType("Discrete"));
  ASSERT_TRUE(discreteLimits.setUnitType("Availability"));
  ASSERT_TRUE(discreteLimits.setLowerLimitValue(0.0));
  ASSERT_TRUE(discreteLimits.setUpperLimitValue(1.0));
  ASSERT_TRUE(invalidFuelEfficiency.setScheduleTypeLimits(discreteLimits));

  EXPECT_FALSE(system.setAvailabilitySchedule(invalidAvailability));
  EXPECT_FALSE(system.setHeatingAvailabilitySchedule(invalidAvailability));
  EXPECT_FALSE(system.setCoolingAvailabilitySchedule(invalidAvailability));
  EXPECT_FALSE(system.setHeatingFuelEfficiencySchedule(invalidFuelEfficiency));
  EXPECT_FALSE(system.setCoolingFuelEfficiencySchedule(invalidFuelEfficiency));
  EXPECT_EQ("Unresolved General Schedule", workspaceImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Heating Availability",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(heatingAvailabilityField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Cooling Availability",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(coolingAvailabilityField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Heating Efficiency",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(heatingFuelField, false, true).value_or(""));
  EXPECT_EQ("Unresolved Cooling Efficiency",
            workspaceImpl->openstudio::detail::IdfObject_Impl::getString(coolingFuelField, false, true).value_or(""));

  system.resetAvailabilitySchedule();
  system.resetHeatingAvailabilitySchedule();
  system.resetCoolingAvailabilitySchedule();
  system.resetHeatingFuelEfficiencySchedule();
  system.resetCoolingFuelEfficiencySchedule();
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(availabilityField, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(heatingAvailabilityField, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(coolingAvailabilityField, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(heatingFuelField, false, true).value_or("").empty());
  EXPECT_TRUE(workspaceImpl->openstudio::detail::IdfObject_Impl::getString(coolingFuelField, false, true).value_or("").empty());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_SchedulesSurviveReloadPostLoadMutationAndRemoval) {
  const auto firstPath = uniqueIdealLoadsPath("epmodel-ideal-loads-schedules-first");
  const auto secondPath = uniqueIdealLoadsPath("epmodel-ideal-loads-schedules-second");
  const ScopedIdealLoadsFileRemoval removeFirst(firstPath);
  const ScopedIdealLoadsFileRemoval removeSecond(secondPath);

  Model model;
  ThermalZone zone(model);
  ZoneHVACIdealLoadsAirSystem system(model);
  ASSERT_TRUE(zone.setName("Ideal Loads Schedule Zone"));
  ASSERT_TRUE(system.setName("Reloadable Ideal Loads System"));
  ASSERT_TRUE(system.addToThermalZone(zone));

  ScheduleCompact availability(model);
  ScheduleCompact heatingAvailability(model);
  ScheduleCompact coolingAvailability(model);
  ScheduleCompact heatingFuelEfficiency(model);
  ScheduleCompact coolingFuelEfficiency(model);
  ASSERT_TRUE(availability.setName("Ideal Loads General Availability"));
  ASSERT_TRUE(heatingAvailability.setName("Ideal Loads Heating Availability"));
  ASSERT_TRUE(coolingAvailability.setName("Ideal Loads Cooling Availability"));
  ASSERT_TRUE(heatingFuelEfficiency.setName("Ideal Loads Heating Fuel Efficiency"));
  ASSERT_TRUE(coolingFuelEfficiency.setName("Ideal Loads Cooling Fuel Efficiency"));
  ASSERT_TRUE(availability.setToConstantValue(1.0));
  ASSERT_TRUE(heatingAvailability.setToConstantValue(1.0));
  ASSERT_TRUE(coolingAvailability.setToConstantValue(1.0));
  ASSERT_TRUE(heatingFuelEfficiency.setToConstantValue(0.9));
  ASSERT_TRUE(coolingFuelEfficiency.setToConstantValue(3.0));
  ASSERT_TRUE(system.setAvailabilitySchedule(availability));
  ASSERT_TRUE(system.setHeatingAvailabilitySchedule(heatingAvailability));
  ASSERT_TRUE(system.setCoolingAvailabilitySchedule(coolingAvailability));
  ASSERT_TRUE(system.setHeatingFuelEfficiencySchedule(heatingFuelEfficiency));
  ASSERT_TRUE(system.setCoolingFuelEfficiencySchedule(coolingFuelEfficiency));
  ASSERT_TRUE(model.save(firstPath, true));

  auto loadedModel = Model::load(firstPath);
  ASSERT_TRUE(loadedModel);
  auto loadedSystem = loadedModel->getConcreteModelObjectByName<ZoneHVACIdealLoadsAirSystem>("Reloadable Ideal Loads System");
  auto loadedZone = loadedModel->getConcreteModelObjectByName<ThermalZone>("Ideal Loads Schedule Zone");
  auto loadedAvailability = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Ideal Loads General Availability");
  auto loadedHeatingAvailability = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Ideal Loads Heating Availability");
  auto loadedCoolingAvailability = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Ideal Loads Cooling Availability");
  auto loadedHeatingFuelEfficiency = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Ideal Loads Heating Fuel Efficiency");
  auto loadedCoolingFuelEfficiency = loadedModel->getConcreteModelObjectByName<ScheduleCompact>("Ideal Loads Cooling Fuel Efficiency");
  ASSERT_TRUE(loadedSystem);
  ASSERT_TRUE(loadedZone);
  ASSERT_TRUE(loadedAvailability);
  ASSERT_TRUE(loadedHeatingAvailability);
  ASSERT_TRUE(loadedCoolingAvailability);
  ASSERT_TRUE(loadedHeatingFuelEfficiency);
  ASSERT_TRUE(loadedCoolingFuelEfficiency);
  ASSERT_TRUE(loadedSystem->thermalZone());
  EXPECT_EQ(loadedZone->handle(), loadedSystem->thermalZone()->handle());
  EXPECT_TRUE(loadedSystem->inletNode());
  EXPECT_TRUE(loadedSystem->outletNode());
  ASSERT_TRUE(loadedSystem->availabilitySchedule());
  ASSERT_TRUE(loadedSystem->heatingAvailabilitySchedule());
  ASSERT_TRUE(loadedSystem->coolingAvailabilitySchedule());
  ASSERT_TRUE(loadedSystem->heatingFuelEfficiencySchedule());
  ASSERT_TRUE(loadedSystem->coolingFuelEfficiencySchedule());
  EXPECT_EQ(loadedAvailability->handle(), loadedSystem->availabilitySchedule()->handle());
  EXPECT_EQ(loadedHeatingAvailability->handle(), loadedSystem->heatingAvailabilitySchedule()->handle());
  EXPECT_EQ(loadedCoolingAvailability->handle(), loadedSystem->coolingAvailabilitySchedule()->handle());
  EXPECT_EQ(loadedHeatingFuelEfficiency->handle(), loadedSystem->heatingFuelEfficiencySchedule()->handle());
  EXPECT_EQ(loadedCoolingFuelEfficiency->handle(), loadedSystem->coolingFuelEfficiencySchedule()->handle());

  ScheduleCompact replacementAvailability(*loadedModel);
  ScheduleCompact replacementFuelEfficiency(*loadedModel);
  ASSERT_TRUE(replacementAvailability.setName("Replacement Ideal Loads Availability"));
  ASSERT_TRUE(replacementFuelEfficiency.setName("Replacement Ideal Loads Fuel Efficiency"));
  ASSERT_TRUE(replacementAvailability.setToConstantValue(1.0));
  ASSERT_TRUE(replacementFuelEfficiency.setToConstantValue(1.25));
  ASSERT_TRUE(loadedSystem->setAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedSystem->setHeatingAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedSystem->setCoolingAvailabilitySchedule(replacementAvailability));
  ASSERT_TRUE(loadedSystem->setHeatingFuelEfficiencySchedule(replacementFuelEfficiency));
  ASSERT_TRUE(loadedSystem->setCoolingFuelEfficiencySchedule(replacementFuelEfficiency));
  loadedSystem->resetHeatingAvailabilitySchedule();
  loadedSystem->resetCoolingFuelEfficiencySchedule();
  ASSERT_TRUE(loadedModel->save(secondPath, true));

  auto reloadedModel = Model::load(secondPath);
  ASSERT_TRUE(reloadedModel);
  auto reloadedSystem = reloadedModel->getConcreteModelObjectByName<ZoneHVACIdealLoadsAirSystem>("Reloadable Ideal Loads System");
  auto reloadedZone = reloadedModel->getConcreteModelObjectByName<ThermalZone>("Ideal Loads Schedule Zone");
  auto reloadedAvailability = reloadedModel->getConcreteModelObjectByName<ScheduleCompact>("Replacement Ideal Loads Availability");
  auto reloadedFuelEfficiency = reloadedModel->getConcreteModelObjectByName<ScheduleCompact>("Replacement Ideal Loads Fuel Efficiency");
  ASSERT_TRUE(reloadedSystem);
  ASSERT_TRUE(reloadedZone);
  ASSERT_TRUE(reloadedAvailability);
  ASSERT_TRUE(reloadedFuelEfficiency);
  ASSERT_TRUE(reloadedSystem->availabilitySchedule());
  EXPECT_EQ(reloadedAvailability->handle(), reloadedSystem->availabilitySchedule()->handle());
  EXPECT_FALSE(reloadedSystem->heatingAvailabilitySchedule());
  ASSERT_TRUE(reloadedSystem->coolingAvailabilitySchedule());
  EXPECT_EQ(reloadedAvailability->handle(), reloadedSystem->coolingAvailabilitySchedule()->handle());
  ASSERT_TRUE(reloadedSystem->heatingFuelEfficiencySchedule());
  EXPECT_EQ(reloadedFuelEfficiency->handle(), reloadedSystem->heatingFuelEfficiencySchedule()->handle());
  EXPECT_FALSE(reloadedSystem->coolingFuelEfficiencySchedule());
  ASSERT_TRUE(reloadedSystem->thermalZone());
  EXPECT_EQ(reloadedZone->handle(), reloadedSystem->thermalZone()->handle());
  EXPECT_TRUE(reloadedSystem->inletNode());
  EXPECT_TRUE(reloadedSystem->outletNode());

  const auto originalScheduleNames =
    std::vector<std::string>{"Ideal Loads General Availability", "Ideal Loads Heating Availability", "Ideal Loads Cooling Availability",
                             "Ideal Loads Heating Fuel Efficiency", "Ideal Loads Cooling Fuel Efficiency"};
  EXPECT_FALSE(reloadedSystem->remove().empty());
  EXPECT_TRUE(reloadedModel->getObject(reloadedZone->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedAvailability->handle()));
  EXPECT_TRUE(reloadedModel->getObject(reloadedFuelEfficiency->handle()));
  for (const auto& name : originalScheduleNames) {
    EXPECT_TRUE(reloadedModel->getConcreteModelObjectByName<ScheduleCompact>(name));
  }
  EXPECT_TRUE(reloadedModel->getConcreteModelObjects<ZoneHVACIdealLoadsAirSystem>().empty());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ScalarAccessors_RoundTrip) {
  Model model;
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_TRUE(system.setMaximumHeatingSupplyAirTemperature(60.0));
  EXPECT_DOUBLE_EQ(60.0, system.maximumHeatingSupplyAirTemperature());
  system.resetMaximumHeatingSupplyAirTemperature();
  EXPECT_DOUBLE_EQ(50.0, system.maximumHeatingSupplyAirTemperature());

  EXPECT_TRUE(system.setMinimumCoolingSupplyAirTemperature(11.0));
  EXPECT_DOUBLE_EQ(11.0, system.minimumCoolingSupplyAirTemperature());
  system.resetMinimumCoolingSupplyAirTemperature();
  EXPECT_DOUBLE_EQ(13.0, system.minimumCoolingSupplyAirTemperature());

  EXPECT_TRUE(system.setMaximumHeatingSupplyAirHumidityRatio(0.02));
  EXPECT_DOUBLE_EQ(0.02, system.maximumHeatingSupplyAirHumidityRatio());
  system.resetMaximumHeatingSupplyAirHumidityRatio();
  EXPECT_DOUBLE_EQ(0.0156, system.maximumHeatingSupplyAirHumidityRatio());

  EXPECT_TRUE(system.setMinimumCoolingSupplyAirHumidityRatio(0.006));
  EXPECT_DOUBLE_EQ(0.006, system.minimumCoolingSupplyAirHumidityRatio());
  system.resetMinimumCoolingSupplyAirHumidityRatio();
  EXPECT_DOUBLE_EQ(0.0077, system.minimumCoolingSupplyAirHumidityRatio());

  EXPECT_TRUE(system.setHeatingLimit("LimitCapacity"));
  EXPECT_EQ("LimitCapacity", system.heatingLimit());
  system.resetHeatingLimit();
  EXPECT_EQ("NoLimit", system.heatingLimit());

  EXPECT_TRUE(system.setMaximumHeatingAirFlowRate(0.75));
  ASSERT_TRUE(system.maximumHeatingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.75, system.maximumHeatingAirFlowRate().get());
  EXPECT_FALSE(system.isMaximumHeatingAirFlowRateAutosized());
  system.autosizeMaximumHeatingAirFlowRate();
  EXPECT_TRUE(system.isMaximumHeatingAirFlowRateAutosized());
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());
  system.resetMaximumHeatingAirFlowRate();
  EXPECT_FALSE(system.maximumHeatingAirFlowRate());

  EXPECT_TRUE(system.setMaximumSensibleHeatingCapacity(8800.0));
  ASSERT_TRUE(system.maximumSensibleHeatingCapacity());
  EXPECT_DOUBLE_EQ(8800.0, system.maximumSensibleHeatingCapacity().get());
  system.autosizeMaximumSensibleHeatingCapacity();
  EXPECT_TRUE(system.isMaximumSensibleHeatingCapacityAutosized());
  system.resetMaximumSensibleHeatingCapacity();
  EXPECT_FALSE(system.maximumSensibleHeatingCapacity());

  EXPECT_TRUE(system.setCoolingLimit("LimitFlowRate"));
  EXPECT_EQ("LimitFlowRate", system.coolingLimit());
  system.resetCoolingLimit();
  EXPECT_EQ("NoLimit", system.coolingLimit());

  EXPECT_TRUE(system.setMaximumCoolingAirFlowRate(0.35));
  ASSERT_TRUE(system.maximumCoolingAirFlowRate());
  EXPECT_DOUBLE_EQ(0.35, system.maximumCoolingAirFlowRate().get());
  system.autosizeMaximumCoolingAirFlowRate();
  EXPECT_TRUE(system.isMaximumCoolingAirFlowRateAutosized());
  system.resetMaximumCoolingAirFlowRate();
  EXPECT_FALSE(system.maximumCoolingAirFlowRate());

  EXPECT_TRUE(system.setMaximumTotalCoolingCapacity(4200.0));
  ASSERT_TRUE(system.maximumTotalCoolingCapacity());
  EXPECT_DOUBLE_EQ(4200.0, system.maximumTotalCoolingCapacity().get());
  system.autosizeMaximumTotalCoolingCapacity();
  EXPECT_TRUE(system.isMaximumTotalCoolingCapacityAutosized());
  system.resetMaximumTotalCoolingCapacity();
  EXPECT_FALSE(system.maximumTotalCoolingCapacity());

  EXPECT_TRUE(system.setDehumidificationControlType("Humidistat"));
  EXPECT_EQ("Humidistat", system.dehumidificationControlType());
  system.resetDehumidificationControlType();
  EXPECT_EQ("ConstantSensibleHeatRatio", system.dehumidificationControlType());

  EXPECT_TRUE(system.setCoolingSensibleHeatRatio(0.75));
  EXPECT_DOUBLE_EQ(0.75, system.coolingSensibleHeatRatio());
  system.resetCoolingSensibleHeatRatio();
  EXPECT_DOUBLE_EQ(0.7, system.coolingSensibleHeatRatio());

  EXPECT_TRUE(system.setHumidificationControlType("Humidistat"));
  EXPECT_EQ("Humidistat", system.humidificationControlType());
  system.resetHumidificationControlType();
  EXPECT_EQ("None", system.humidificationControlType());

  EXPECT_TRUE(system.setDemandControlledVentilationType("CO2Setpoint"));
  EXPECT_EQ("CO2Setpoint", system.demandControlledVentilationType());
  system.resetDemandControlledVentilationType();
  EXPECT_EQ("None", system.demandControlledVentilationType());

  EXPECT_TRUE(system.setOutdoorAirEconomizerType("DifferentialDryBulb"));
  EXPECT_EQ("DifferentialDryBulb", system.outdoorAirEconomizerType());
  system.resetOutdoorAirEconomizerType();
  EXPECT_EQ("NoEconomizer", system.outdoorAirEconomizerType());

  EXPECT_TRUE(system.setHeatRecoveryType("Sensible"));
  EXPECT_EQ("Sensible", system.heatRecoveryType());
  system.resetHeatRecoveryType();
  EXPECT_EQ("None", system.heatRecoveryType());

  EXPECT_TRUE(system.setSensibleHeatRecoveryEffectiveness(0.85));
  EXPECT_DOUBLE_EQ(0.85, system.sensibleHeatRecoveryEffectiveness());
  system.resetSensibleHeatRecoveryEffectiveness();
  EXPECT_DOUBLE_EQ(0.7, system.sensibleHeatRecoveryEffectiveness());

  EXPECT_TRUE(system.setLatentHeatRecoveryEffectiveness(0.72));
  EXPECT_DOUBLE_EQ(0.72, system.latentHeatRecoveryEffectiveness());
  system.resetLatentHeatRecoveryEffectiveness();
  EXPECT_DOUBLE_EQ(0.65, system.latentHeatRecoveryEffectiveness());

  EXPECT_TRUE(system.setHeatingFuelType("Electricity"));
  EXPECT_EQ("Electricity", system.heatingFuelType());

  EXPECT_TRUE(system.setCoolingFuelType("NaturalGas"));
  EXPECT_EQ("NaturalGas", system.coolingFuelType());
}

TEST_F(EPModelFixture, ZoneHVACIdealLoadsAirSystem_ZoneAttachmentRoundTrip) {
  Model model;
  ThermalZone zone(model);
  ZoneHVACIdealLoadsAirSystem system(model);

  EXPECT_NE(0u, system.inletPort());
  EXPECT_NE(0u, system.outletPort());
  EXPECT_FALSE(system.thermalZone());
  EXPECT_TRUE(system.addToThermalZone(zone));
  ASSERT_TRUE(system.thermalZone());
  EXPECT_EQ(zone, *system.thermalZone());
  EXPECT_TRUE(system.inletNode());
  EXPECT_TRUE(system.outletNode());

  system.removeFromThermalZone();
  EXPECT_FALSE(system.thermalZone());
  EXPECT_FALSE(system.inletNode());
  EXPECT_FALSE(system.outletNode());
}
