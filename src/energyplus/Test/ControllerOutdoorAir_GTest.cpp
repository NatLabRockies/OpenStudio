/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "EnergyPlusFixture.hpp"

#include "../ForwardTranslator.hpp"

#include "../../model/ControllerOutdoorAir.hpp"

#include "../../model/Model.hpp"
#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVACOutdoorAirSystem.hpp"
#include "../../model/AirTerminalSingleDuctConstantVolumeNoReheat.hpp"
#include "../../model/ControllerMechanicalVentilation.hpp"
#include "../../model/DesignSpecificationOutdoorAir.hpp"
#include "../../model/Node.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Space.hpp"
#include "../../model/SpaceType.hpp"
#include "../../model/ThermalZone.hpp"

#include "../../utilities/core/Logger.hpp"
#include "../../utilities/geometry/Point3d.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceExtensibleGroup.hpp"
#include "../../utilities/idf/WorkspaceObject.hpp"
#include "../../utilities/idf/WorkspaceObject_Impl.hpp"

#include <utilities/idd/Controller_OutdoorAir_FieldEnums.hxx>
#include <utilities/idd/Controller_MechanicalVentilation_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddObject.hpp>

using namespace openstudio::energyplus;
using namespace openstudio::model;
using namespace openstudio;

TEST_F(EnergyPlusFixture, ForwardTranslator_ControllerOutdoorAir) {
  // Test for #3984
  Model m;
  ForwardTranslator ft;

  ControllerOutdoorAir controller_oa(m);
  ControllerMechanicalVentilation controller_mv = controller_oa.controllerMechanicalVentilation();

  // Not used: not translated
  {
    ASSERT_NO_THROW(ft.translateModel(m));
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(0, idf_controller_oas.size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());
  }

  AirLoopHVAC a(m);
  AirLoopHVACOutdoorAirSystem oa_sys(m, controller_oa);

  constexpr double width = 10.0;
  constexpr double height = 3.6;  // It's convenient for ACH, since 3600 s/hr

  // Counterclockwise points
  std::vector<Point3d> floorPointsSpace1{{0.0, 0.0, 0.0}, {0.0, width, 0.0}, {width, width, 0.0}, {width, 0.0, 0.0}};

  auto space = Space::fromFloorPrint(floorPointsSpace1, height, m, "Space 1").get();
  ThermalZone z(m);
  space.setThermalZone(z);

  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeNoReheat atu(m, alwaysOn);
  EXPECT_TRUE(a.addBranchForZone(z, atu));

  // Not used since the OutdoorAirSystem isn't used itself: not translated
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(0, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());
  }

  Node supplyOutlet = a.supplyOutletNode();
  EXPECT_TRUE(oa_sys.addToNode(supplyOutlet));

  EXPECT_FALSE(controller_mv.hasZonesWithDesignSpecificationOutdoorAir());

  // used: should be translated, but it has no DSOA
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(1, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());

    // Zero zones with a DSOA: no Controller:MechanicalVentilation should have been written
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation).size());
  }

  DesignSpecificationOutdoorAir dsoa(m);
  dsoa.setName("DSOA");
  EXPECT_TRUE(space.setDesignSpecificationOutdoorAir(dsoa));

  EXPECT_TRUE(controller_mv.hasZonesWithDesignSpecificationOutdoorAir());

  // used and has DSOA
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(1, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());

    // Zones with a DSOA: no Controller:MechanicalVentilation should have been written
    ASSERT_EQ(1, w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation).size());
    auto idf_controller_mv = w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation)[0];
    ASSERT_EQ(1, idf_controller_mv.numExtensibleGroups());
    {
      auto w_eg = idf_controller_mv.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      EXPECT_EQ(z.nameString(), w_eg.getString(Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName).get());
      auto dsoaOrList_ = w_eg.getTarget(Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
      ASSERT_TRUE(dsoaOrList_);
      EXPECT_EQ(dsoaOrList_->iddObject().type(), IddObjectType::DesignSpecification_OutdoorAir);
      EXPECT_EQ(dsoa.nameString(), dsoaOrList_->nameString());
    }
  }
}

TEST_F(EnergyPlusFixture, ForwardTranslator_ControllerOutdoorAir_MechanicalVentilation) {
  // Test for #3984
  Model m;
  ForwardTranslator ft;

  ControllerOutdoorAir controller_oa(m);
  ControllerMechanicalVentilation controller_mv = controller_oa.controllerMechanicalVentilation();

  AirLoopHVAC a(m);
  AirLoopHVACOutdoorAirSystem oa_sys(m, controller_oa);
  Node supplyOutlet = a.supplyOutletNode();
  EXPECT_TRUE(oa_sys.addToNode(supplyOutlet));

  //            y (=North)
  //   ▲
  //   │               building height = 3m
  // 10├────────┼────────┼────────┤
  //   │        │        │        │
  //   │        │        │        │
  //   │ Space 1│ Space 2│ Space 3│
  //   │        │        │        │
  //   └────────┴────────┴────────┴────► x
  //  0        10       20        30

  constexpr double width = 10.0;
  constexpr double height = 3.6;  // It's convenient for ACH, since 3600 s/hr

  // Counterclockwise points
  std::vector<Point3d> floorPointsSpace1{{0.0, 0.0, 0.0}, {0.0, width, 0.0}, {width, width, 0.0}, {width, 0.0, 0.0}};

  // 3 spaces in a two zones
  auto space1 = Space::fromFloorPrint(floorPointsSpace1, height, m, "Space 1").get();
  auto space2 = Space::fromFloorPrint(floorPointsSpace1, height, m, "Space 2").get();
  space2.setXOrigin(width);
  auto space3 = Space::fromFloorPrint(floorPointsSpace1, height, m, "Space 3").get();
  space3.setXOrigin(width * 2);

  ThermalZone z12(m);
  EXPECT_TRUE(space1.setThermalZone(z12));
  EXPECT_TRUE(space2.setThermalZone(z12));

  ThermalZone z3(m);
  EXPECT_TRUE(space3.setThermalZone(z3));

  auto alwaysOn = m.alwaysOnDiscreteSchedule();
  AirTerminalSingleDuctConstantVolumeNoReheat atu12(m, alwaysOn);
  EXPECT_TRUE(a.addBranchForZone(z12, atu12));

  AirTerminalSingleDuctConstantVolumeNoReheat atu3(m, alwaysOn);
  EXPECT_TRUE(a.addBranchForZone(z3, atu3));

  EXPECT_FALSE(controller_mv.hasZonesWithDesignSpecificationOutdoorAir());
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(1, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());

    // Zero zones with a DSOA: no Controller:MechanicalVentilation should have been written
    auto& idf_controller_oa = idf_controller_oas.front();
    EXPECT_FALSE(idf_controller_oa.getTarget(Controller_OutdoorAirFields::MechanicalVentilationControllerName));
    EXPECT_EQ(0, w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation).size());
  }

  // Create an Office Space Type. Assign to Space 1 & 2 only (not 3), it also has a DSOA
  SpaceType officeSpaceType(m);
  officeSpaceType.setName("officeSpaceType");
  DesignSpecificationOutdoorAir dsoaOffice(m);
  dsoaOffice.setName("dsoaOffice");
  EXPECT_TRUE(officeSpaceType.setDesignSpecificationOutdoorAir(dsoaOffice));
  EXPECT_TRUE(space1.setSpaceType(officeSpaceType));
  EXPECT_TRUE(space2.setSpaceType(officeSpaceType));

  // Space 3 has a space-level DSOA
  DesignSpecificationOutdoorAir dsoaSpace3(m);
  dsoaSpace3.setName("dsoaSpace3");
  EXPECT_TRUE(space3.setDesignSpecificationOutdoorAir(dsoaSpace3));

  EXPECT_TRUE(controller_mv.hasZonesWithDesignSpecificationOutdoorAir());
  EXPECT_EQ(2, z12.spacesWithDesignSpecificationOutdoorAir().size());
  EXPECT_EQ(1, z3.spacesWithDesignSpecificationOutdoorAir().size());
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(1, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());

    // Zones with a DSOA: the Controller:MechanicalVentilation should have been written
    auto& idf_controller_oa = idf_controller_oas.front();
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation).size());
    ASSERT_TRUE(idf_controller_oa.getTarget(Controller_OutdoorAirFields::MechanicalVentilationControllerName));
    auto idf_controller_mv = idf_controller_oa.getTarget(Controller_OutdoorAirFields::MechanicalVentilationControllerName).get();
    ASSERT_EQ(2, idf_controller_mv.numExtensibleGroups());

    {
      auto w_eg = idf_controller_mv.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      EXPECT_EQ(z12.nameString(), w_eg.getString(Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName).get());
      auto dsoaOrList_ = w_eg.getTarget(Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
      ASSERT_TRUE(dsoaOrList_);
      EXPECT_EQ(dsoaOrList_->iddObject().type(), IddObjectType::DesignSpecification_OutdoorAir_SpaceList);
      EXPECT_EQ(z12.nameString() + " DSOA Space List", dsoaOrList_->nameString());
    }
    {
      auto w_eg = idf_controller_mv.extensibleGroups()[1].cast<WorkspaceExtensibleGroup>();
      EXPECT_EQ(z3.nameString(), w_eg.getString(Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName).get());
      auto dsoaOrList_ = w_eg.getTarget(Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
      ASSERT_TRUE(dsoaOrList_);
      EXPECT_EQ(dsoaOrList_->iddObject().type(), IddObjectType::DesignSpecification_OutdoorAir);
      EXPECT_EQ(dsoaSpace3.nameString(), dsoaOrList_->nameString());
    }
  }

  // We should NOT end up with zones that have no DSOAs on it
  space3.resetDesignSpecificationOutdoorAir();
  EXPECT_TRUE(controller_mv.hasZonesWithDesignSpecificationOutdoorAir());
  EXPECT_EQ(2, z12.spacesWithDesignSpecificationOutdoorAir().size());
  EXPECT_EQ(0, z3.spacesWithDesignSpecificationOutdoorAir().size());
  {
    Workspace w = ft.translateModel(m);

    WorkspaceObjectVector idf_controller_oas(w.getObjectsByType(IddObjectType::Controller_OutdoorAir));
    EXPECT_EQ(1, idf_controller_oas.size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC).size());
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::AirLoopHVAC_OutdoorAirSystem).size());

    // Zones with a DSOA: the Controller:MechanicalVentilation should have been written
    auto& idf_controller_oa = idf_controller_oas.front();
    EXPECT_EQ(1, w.getObjectsByType(IddObjectType::Controller_MechanicalVentilation).size());
    ASSERT_TRUE(idf_controller_oa.getTarget(Controller_OutdoorAirFields::MechanicalVentilationControllerName));
    auto idf_controller_mv = idf_controller_oa.getTarget(Controller_OutdoorAirFields::MechanicalVentilationControllerName).get();
    ASSERT_EQ(1, idf_controller_mv.numExtensibleGroups());

    {
      auto w_eg = idf_controller_mv.extensibleGroups()[0].cast<WorkspaceExtensibleGroup>();
      EXPECT_EQ(z12.nameString(), w_eg.getString(Controller_MechanicalVentilationExtensibleFields::ZoneorZoneListName).get());
      auto dsoaOrList_ = w_eg.getTarget(Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObjectName);
      ASSERT_TRUE(dsoaOrList_);
      EXPECT_EQ(dsoaOrList_->iddObject().type(), IddObjectType::DesignSpecification_OutdoorAir_SpaceList);
      EXPECT_EQ(z12.nameString() + " DSOA Space List", dsoaOrList_->nameString());
    }
  }
}
