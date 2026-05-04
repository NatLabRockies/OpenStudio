/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirTerminalSingleDuctConstantVolumeReheat.hpp"
#include "../../model/CoilHeatingElectric.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Space.hpp"
#include "../../model/ThermalZone.hpp"

#include <utilities/idd/AirTerminal_SingleDuct_ConstantVolume_Reheat_FieldEnums.hxx>
#include <utilities/idd/IddObject.hpp>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/ZoneHVAC_AirDistributionUnit_FieldEnums.hxx>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_AirTerminalSingleDuctConstantVolumeReheat) {
  Model m;

  ThermalZone zone(m);
  Space space(m);
  ASSERT_TRUE(space.setThermalZone(zone));

  Schedule schedule = m.alwaysOnDiscreteSchedule();
  CoilHeatingElectric coil(m, schedule);
  ASSERT_TRUE(coil.setName("Electric Reheat Coil"));

  AirTerminalSingleDuctConstantVolumeReheat terminal(m, schedule, coil);
  ASSERT_TRUE(terminal.setName("ATU SingleDuct ConstantVolume Reheat"));
  ASSERT_TRUE(terminal.setMaximumAirFlowRate(0.42));
  ASSERT_TRUE(terminal.setMaximumHotWaterorSteamFlowRate(0.004));
  ASSERT_TRUE(terminal.setMinimumHotWaterorSteamFlowRate(0.001));
  ASSERT_TRUE(terminal.setConvergenceTolerance(0.0005));
  ASSERT_TRUE(terminal.setMaximumReheatAirTemperature(39.5));

  AirLoopHVAC airLoop(m);
  ASSERT_TRUE(airLoop.addBranchForZone(zone, terminal));

  const auto inletModelObject = terminal.inletModelObject();
  ASSERT_TRUE(inletModelObject);
  const auto outletModelObject = terminal.outletModelObject();
  ASSERT_TRUE(outletModelObject);

  ForwardTranslator ft;
  Workspace w = ft.translateModel(m);

  WorkspaceObjectVector idfTerminals = w.getObjectsByType(IddObjectType::AirTerminal_SingleDuct_ConstantVolume_Reheat);
  ASSERT_EQ(1u, idfTerminals.size());
  WorkspaceObject idfTerminal(idfTerminals[0]);

  EXPECT_EQ("ATU SingleDuct ConstantVolume Reheat", idfTerminal.nameString());

  const auto idfAvailabilitySchedule = idfTerminal.getTarget(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AvailabilityScheduleName);
  ASSERT_TRUE(idfAvailabilitySchedule);
  EXPECT_EQ(schedule.nameString(), idfAvailabilitySchedule->nameString());

  EXPECT_EQ(outletModelObject->nameString(), idfTerminal.getString(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName).get());
  EXPECT_EQ(inletModelObject->nameString(), idfTerminal.getString(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirInletNodeName).get());
  EXPECT_DOUBLE_EQ(0.42, idfTerminal.getDouble(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumAirFlowRate).get());

  EXPECT_EQ("Coil:Heating:Electric", idfTerminal.getString(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilObjectType).get());
  const auto idfReheatCoil = idfTerminal.getTarget(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ReheatCoilName);
  ASSERT_TRUE(idfReheatCoil);
  EXPECT_EQ(idfReheatCoil->iddObject().type(), IddObjectType::Coil_Heating_Electric);
  EXPECT_EQ("Electric Reheat Coil", idfReheatCoil->nameString());
  EXPECT_EQ(inletModelObject->nameString(), idfReheatCoil->getString(Coil_Heating_ElectricFields::AirInletNodeName).get());
  EXPECT_EQ(outletModelObject->nameString(), idfReheatCoil->getString(Coil_Heating_ElectricFields::AirOutletNodeName).get());

  EXPECT_DOUBLE_EQ(0.004, idfTerminal.getDouble(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumHotWaterorSteamFlowRate).get());
  EXPECT_DOUBLE_EQ(0.001, idfTerminal.getDouble(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MinimumHotWaterorSteamFlowRate).get());
  EXPECT_DOUBLE_EQ(0.0005, idfTerminal.getDouble(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::ConvergenceTolerance).get());
  EXPECT_DOUBLE_EQ(39.5, idfTerminal.getDouble(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::MaximumReheatAirTemperature).get());

  WorkspaceObjectVector idfAirDistributionUnits = w.getObjectsByType(IddObjectType::ZoneHVAC_AirDistributionUnit);
  ASSERT_EQ(1u, idfAirDistributionUnits.size());
  WorkspaceObject idfAirDistributionUnit(idfAirDistributionUnits[0]);

  EXPECT_EQ(idfTerminal.getString(AirTerminal_SingleDuct_ConstantVolume_ReheatFields::AirOutletNodeName).get(),
            idfAirDistributionUnit.getString(ZoneHVAC_AirDistributionUnitFields::AirDistributionUnitOutletNodeName).get());
  EXPECT_EQ("AirTerminal:SingleDuct:ConstantVolume:Reheat",
            idfAirDistributionUnit.getString(ZoneHVAC_AirDistributionUnitFields::AirTerminalObjectType).get());
  EXPECT_EQ(idfTerminal.nameString(), idfAirDistributionUnit.getString(ZoneHVAC_AirDistributionUnitFields::AirTerminalName).get());
}
