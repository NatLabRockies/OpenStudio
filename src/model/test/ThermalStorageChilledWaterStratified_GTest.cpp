/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "ModelFixture.hpp"

#include "../ThermalStorageChilledWaterStratified.hpp"
#include "../ThermalStorageChilledWaterStratified_Impl.hpp"

#include "../Model.hpp"

#include "../AirLoopHVAC.hpp"
#include "../ChillerElectricEIR.hpp"
#include "../Node.hpp"
#include "../PlantLoop.hpp"
#include "../Schedule.hpp"
#include "../ScheduleConstant.hpp"
#include "../ThermalZone.hpp"
#include "../WaterHeaterSizing.hpp"

#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace openstudio;
using namespace openstudio::model;

std::string getObjectNames(const auto& rmed) {
  std::vector<std::string> rm_names;
  rm_names.reserve(rmed.size());
  std::transform(rmed.cbegin(), rmed.cend(), std::back_inserter(rm_names), [](const auto& idfObjet) { return idfObjet.nameString(); });
  return fmt::format("{}", rm_names);
};

TEST_F(ModelFixture, ThermalStorageChilledWaterStratified_GettersSetters) {
  Model m;
  ThermalStorageChilledWaterStratified chw_storage(m);

  chw_storage.setName("My ThermalStorageChilledWaterStratified");

  // Tank Volume: Required Double
  EXPECT_TRUE(chw_storage.setTankVolume(0.3));
  EXPECT_EQ(0.3, chw_storage.tankVolume());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTankVolume(-10.0));
  EXPECT_EQ(0.3, chw_storage.tankVolume());

  // Tank Height: Required Double
  EXPECT_TRUE(chw_storage.setTankHeight(0.4));
  EXPECT_EQ(0.4, chw_storage.tankHeight());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTankHeight(-10.0));
  EXPECT_EQ(0.4, chw_storage.tankHeight());

  // Tank Shape: Required String
  EXPECT_TRUE(chw_storage.setTankShape("VerticalCylinder"));
  EXPECT_EQ("VerticalCylinder", chw_storage.tankShape());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTankShape("BADENUM"));
  EXPECT_EQ("VerticalCylinder", chw_storage.tankShape());

  // Tank Perimeter: Optional Double
  EXPECT_TRUE(chw_storage.setTankPerimeter(0.6));
  ASSERT_TRUE(chw_storage.tankPerimeter());
  EXPECT_EQ(0.6, chw_storage.tankPerimeter().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTankPerimeter(-10.0));
  ASSERT_TRUE(chw_storage.tankPerimeter());
  EXPECT_EQ(0.6, chw_storage.tankPerimeter().get());

  // Setpoint Temperature Schedule Name: Optional Object
  ScheduleConstant setpointTemperatureSchedule(m);
  EXPECT_TRUE(chw_storage.setSetpointTemperatureSchedule(setpointTemperatureSchedule));
  ASSERT_TRUE(chw_storage.setpointTemperatureSchedule());
  EXPECT_EQ(setpointTemperatureSchedule, chw_storage.setpointTemperatureSchedule().get());

  // Deadband Temperature Difference: Required Double
  EXPECT_TRUE(chw_storage.setDeadbandTemperatureDifference(0.8));
  EXPECT_EQ(0.8, chw_storage.deadbandTemperatureDifference());
  // Bad Value
  EXPECT_FALSE(chw_storage.setDeadbandTemperatureDifference(-10.0));
  EXPECT_EQ(0.8, chw_storage.deadbandTemperatureDifference());

  // Temperature Sensor Height: Optional Double
  EXPECT_TRUE(chw_storage.setTemperatureSensorHeight(0.9));
  ASSERT_TRUE(chw_storage.temperatureSensorHeight());
  EXPECT_EQ(0.9, chw_storage.temperatureSensorHeight().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTemperatureSensorHeight(-10.0));
  ASSERT_TRUE(chw_storage.temperatureSensorHeight());
  EXPECT_EQ(0.9, chw_storage.temperatureSensorHeight().get());

  // Minimum Temperature Limit: Optional Double
  EXPECT_TRUE(chw_storage.setMinimumTemperatureLimit(1.0));
  ASSERT_TRUE(chw_storage.minimumTemperatureLimit());
  EXPECT_EQ(1.0, chw_storage.minimumTemperatureLimit().get());

  // Nominal Cooling Capacity: Optional Double
  EXPECT_TRUE(chw_storage.setNominalCoolingCapacity(1.1));
  ASSERT_TRUE(chw_storage.nominalCoolingCapacity());
  EXPECT_EQ(1.1, chw_storage.nominalCoolingCapacity().get());

  // Ambient Temperature Indicator: Required String
  EXPECT_TRUE(chw_storage.setAmbientTemperatureIndicator("Schedule"));
  EXPECT_EQ("Schedule", chw_storage.ambientTemperatureIndicator());
  // Bad Value
  EXPECT_FALSE(chw_storage.setAmbientTemperatureIndicator("BADENUM"));
  EXPECT_EQ("Schedule", chw_storage.ambientTemperatureIndicator());

  // Ambient Temperature Schedule Name: Optional Object
  ScheduleConstant ambientTemperatureSchedule(m);
  EXPECT_TRUE(chw_storage.setAmbientTemperatureSchedule(ambientTemperatureSchedule));
  ASSERT_TRUE(chw_storage.ambientTemperatureSchedule());
  EXPECT_EQ(ambientTemperatureSchedule, chw_storage.ambientTemperatureSchedule().get());

  // Ambient Temperature Thermal Zone Name: Optional Object
  ThermalZone ambientTemperatureThermalZone(m);
  EXPECT_TRUE(chw_storage.setAmbientTemperatureThermalZone(ambientTemperatureThermalZone));
  ASSERT_TRUE(chw_storage.ambientTemperatureThermalZone());
  EXPECT_EQ(ambientTemperatureThermalZone, chw_storage.ambientTemperatureThermalZone().get());

  // Ambient Temperature Outdoor Air Node Name: Optional String
  const std::string ambientTemperatureNodeName = "MyAmbientTempNode";
  EXPECT_TRUE(chw_storage.setAmbientTemperatureOutdoorAirNodeName(ambientTemperatureNodeName));
  ASSERT_TRUE(chw_storage.ambientTemperatureOutdoorAirNodeName());
  EXPECT_EQ(ambientTemperatureNodeName, chw_storage.ambientTemperatureOutdoorAirNodeName().get());

  // Uniform Skin Loss Coefficient per Unit Area to Ambient Temperature: Optional Double
  EXPECT_TRUE(chw_storage.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(1.6));
  ASSERT_TRUE(chw_storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature());
  EXPECT_EQ(1.6, chw_storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setUniformSkinLossCoefficientperUnitAreatoAmbientTemperature(-10.0));
  ASSERT_TRUE(chw_storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature());
  EXPECT_EQ(1.6, chw_storage.uniformSkinLossCoefficientperUnitAreatoAmbientTemperature().get());

  // Use Side Heat Transfer Effectiveness: Required Double
  EXPECT_TRUE(chw_storage.setUseSideHeatTransferEffectiveness(0.95));
  EXPECT_EQ(0.95, chw_storage.useSideHeatTransferEffectiveness());
  // Bad Value
  EXPECT_FALSE(chw_storage.setUseSideHeatTransferEffectiveness(-10.0));
  EXPECT_EQ(0.95, chw_storage.useSideHeatTransferEffectiveness());

  // Use Side Availability Schedule Name: Optional Object
  ScheduleConstant useSideAvailabilitySchedule(m);
  EXPECT_TRUE(chw_storage.setUseSideAvailabilitySchedule(useSideAvailabilitySchedule));
  ASSERT_TRUE(chw_storage.useSideAvailabilitySchedule());
  EXPECT_EQ(useSideAvailabilitySchedule, chw_storage.useSideAvailabilitySchedule().get());

  // Use Side Inlet Height: Required Double
  // Autocalculate
  chw_storage.autocalculateUseSideInletHeight();
  EXPECT_TRUE(chw_storage.isUseSideInletHeightAutocalculated());
  // Set
  EXPECT_TRUE(chw_storage.setUseSideInletHeight(2.1));
  ASSERT_TRUE(chw_storage.useSideInletHeight());
  EXPECT_EQ(2.1, chw_storage.useSideInletHeight().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setUseSideInletHeight(-10.0));
  ASSERT_TRUE(chw_storage.useSideInletHeight());
  EXPECT_EQ(2.1, chw_storage.useSideInletHeight().get());
  EXPECT_FALSE(chw_storage.isUseSideInletHeightAutocalculated());

  // Use Side Outlet Height: Required Double
  EXPECT_TRUE(chw_storage.setUseSideOutletHeight(2.2));
  EXPECT_EQ(2.2, chw_storage.useSideOutletHeight());
  // Bad Value
  EXPECT_FALSE(chw_storage.setUseSideOutletHeight(-10.0));
  EXPECT_EQ(2.2, chw_storage.useSideOutletHeight());

  // Use Side Design Flow Rate: Required Double
  // Autosize
  chw_storage.autosizeUseSideDesignFlowRate();
  EXPECT_TRUE(chw_storage.isUseSideDesignFlowRateAutosized());
  // Set
  EXPECT_TRUE(chw_storage.setUseSideDesignFlowRate(2.3));
  ASSERT_TRUE(chw_storage.useSideDesignFlowRate());
  EXPECT_EQ(2.3, chw_storage.useSideDesignFlowRate().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setUseSideDesignFlowRate(-10.0));
  ASSERT_TRUE(chw_storage.useSideDesignFlowRate());
  EXPECT_EQ(2.3, chw_storage.useSideDesignFlowRate().get());
  EXPECT_FALSE(chw_storage.isUseSideDesignFlowRateAutosized());

  // Source Side Heat Transfer Effectiveness: Required Double
  EXPECT_TRUE(chw_storage.setSourceSideHeatTransferEffectiveness(0.963));
  EXPECT_EQ(0.963, chw_storage.sourceSideHeatTransferEffectiveness());
  // Bad Value
  EXPECT_FALSE(chw_storage.setSourceSideHeatTransferEffectiveness(-10.0));
  EXPECT_EQ(0.963, chw_storage.sourceSideHeatTransferEffectiveness());

  // Source Side Availability Schedule Name: Optional Object
  ScheduleConstant sourceSideAvailabilitySchedule(m);
  EXPECT_TRUE(chw_storage.setSourceSideAvailabilitySchedule(sourceSideAvailabilitySchedule));
  ASSERT_TRUE(chw_storage.sourceSideAvailabilitySchedule());
  EXPECT_EQ(sourceSideAvailabilitySchedule, chw_storage.sourceSideAvailabilitySchedule().get());

  // Source Side Inlet Height: Required Double
  EXPECT_TRUE(chw_storage.setSourceSideInletHeight(2.8));
  EXPECT_EQ(2.8, chw_storage.sourceSideInletHeight());
  // Bad Value
  EXPECT_FALSE(chw_storage.setSourceSideInletHeight(-10.0));
  EXPECT_EQ(2.8, chw_storage.sourceSideInletHeight());

  // Source Side Outlet Height: Required Double
  // Autocalculate
  chw_storage.autocalculateSourceSideOutletHeight();
  EXPECT_TRUE(chw_storage.isSourceSideOutletHeightAutocalculated());
  // Set
  EXPECT_TRUE(chw_storage.setSourceSideOutletHeight(2.9));
  ASSERT_TRUE(chw_storage.sourceSideOutletHeight());
  EXPECT_EQ(2.9, chw_storage.sourceSideOutletHeight().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setSourceSideOutletHeight(-10.0));
  ASSERT_TRUE(chw_storage.sourceSideOutletHeight());
  EXPECT_EQ(2.9, chw_storage.sourceSideOutletHeight().get());
  EXPECT_FALSE(chw_storage.isSourceSideOutletHeightAutocalculated());

  // Source Side Design Flow Rate: Required Double
  // Autosize
  chw_storage.autosizeSourceSideDesignFlowRate();
  EXPECT_TRUE(chw_storage.isSourceSideDesignFlowRateAutosized());
  // Set
  EXPECT_TRUE(chw_storage.setSourceSideDesignFlowRate(3.0));
  ASSERT_TRUE(chw_storage.sourceSideDesignFlowRate());
  EXPECT_EQ(3.0, chw_storage.sourceSideDesignFlowRate().get());
  // Bad Value
  EXPECT_FALSE(chw_storage.setSourceSideDesignFlowRate(-10.0));
  ASSERT_TRUE(chw_storage.sourceSideDesignFlowRate());
  EXPECT_EQ(3.0, chw_storage.sourceSideDesignFlowRate().get());
  EXPECT_FALSE(chw_storage.isSourceSideDesignFlowRateAutosized());

  // Tank Recovery Time: Required Double
  EXPECT_TRUE(chw_storage.setTankRecoveryTime(3.1));
  EXPECT_EQ(3.1, chw_storage.tankRecoveryTime());
  // Bad Value
  EXPECT_FALSE(chw_storage.setTankRecoveryTime(-10.0));
  EXPECT_EQ(3.1, chw_storage.tankRecoveryTime());

  // Inlet Mode: Required String
  EXPECT_TRUE(chw_storage.setInletMode("Fixed"));
  EXPECT_EQ("Fixed", chw_storage.inletMode());
  // Bad Value
  EXPECT_FALSE(chw_storage.setInletMode("BADENUM"));
  EXPECT_EQ("Fixed", chw_storage.inletMode());

  // Number of Nodes: Required Integer
  EXPECT_TRUE(chw_storage.setNumberofNodes(9));
  EXPECT_EQ(9, chw_storage.numberofNodes());
  // Bad Value
  EXPECT_FALSE(chw_storage.setNumberofNodes(-9));
  EXPECT_EQ(9, chw_storage.numberofNodes());

  // Additional Destratification Conductivity: Required Double
  EXPECT_TRUE(chw_storage.setAdditionalDestratificationConductivity(3.4));
  EXPECT_EQ(3.4, chw_storage.additionalDestratificationConductivity());
  // Bad Value
  EXPECT_FALSE(chw_storage.setAdditionalDestratificationConductivity(-10.0));
  EXPECT_EQ(3.4, chw_storage.additionalDestratificationConductivity());

  // Node 1 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode1AdditionalLossCoefficient(3.5));
  EXPECT_EQ(3.5, chw_storage.node1AdditionalLossCoefficient());

  // Node 2 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode2AdditionalLossCoefficient(3.6));
  EXPECT_EQ(3.6, chw_storage.node2AdditionalLossCoefficient());

  // Node 3 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode3AdditionalLossCoefficient(3.7));
  EXPECT_EQ(3.7, chw_storage.node3AdditionalLossCoefficient());

  // Node 4 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode4AdditionalLossCoefficient(3.8));
  EXPECT_EQ(3.8, chw_storage.node4AdditionalLossCoefficient());

  // Node 5 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode5AdditionalLossCoefficient(3.9));
  EXPECT_EQ(3.9, chw_storage.node5AdditionalLossCoefficient());

  // Node 6 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode6AdditionalLossCoefficient(4.0));
  EXPECT_EQ(4.0, chw_storage.node6AdditionalLossCoefficient());

  // Node 7 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode7AdditionalLossCoefficient(4.1));
  EXPECT_EQ(4.1, chw_storage.node7AdditionalLossCoefficient());

  // Node 8 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode8AdditionalLossCoefficient(4.2));
  EXPECT_EQ(4.2, chw_storage.node8AdditionalLossCoefficient());

  // Node 9 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode9AdditionalLossCoefficient(4.3));
  EXPECT_EQ(4.3, chw_storage.node9AdditionalLossCoefficient());

  // Node 10 Additional Loss Coefficient: Required Double
  EXPECT_TRUE(chw_storage.setNode10AdditionalLossCoefficient(4.4));
  EXPECT_EQ(4.4, chw_storage.node10AdditionalLossCoefficient());
}

TEST_F(ModelFixture, ThermalStorageChilledWaterStratified_addToNode) {

  Model m;
  ThermalStorageChilledWaterStratified chw_storage(m);

  auto createLoop = [&m](const std::string& prefix) {
    PlantLoop p(m);
    static constexpr std::array<std::string_view, 10> compNames = {
      "Supply Inlet", "Supply Splitter", "Supply Connection Node", "Supply Mixer", "Supply Outlet",
      "Demand Inlet", "Demand Splitter", "Demand Connection Node", "Demand Mixer", "Demand Outlet",
    };
    p.setName(prefix);
    for (size_t i = 0; auto& comp : p.components()) {
      comp.setName(prefix + " " + std::string{compNames[i++]});
    }
    return p;
  };

  auto useLoop = createLoop("Use Side Loop");
  auto sourceLoop = createLoop("Source Side Loop");

  EXPECT_EQ(5, useLoop.supplyComponents().size()) << getObjectNames(useLoop.supplyComponents());        // o --- Splitter --- o --- Mixer --- o
  EXPECT_EQ(5, useLoop.demandComponents().size()) << getObjectNames(useLoop.demandComponents());        // o --- Splitter --- o --- Mixer --- o
  EXPECT_EQ(5, sourceLoop.supplyComponents().size()) << getObjectNames(sourceLoop.supplyComponents());  // o --- Splitter --- o --- Mixer --- o
  EXPECT_EQ(5, sourceLoop.demandComponents().size()) << getObjectNames(sourceLoop.demandComponents());  // o --- Splitter --- o --- Mixer --- o

  {
    EXPECT_TRUE(useLoop.addSupplyBranchForComponent(chw_storage));
    ASSERT_TRUE(chw_storage.plantLoop());
    EXPECT_FALSE(chw_storage.secondaryPlantLoop());
    ASSERT_EQ(useLoop, chw_storage.plantLoop().get());
    EXPECT_TRUE(chw_storage.supplyInletModelObject());
    EXPECT_TRUE(chw_storage.supplyInletModelObject());
    EXPECT_FALSE(chw_storage.demandInletModelObject());
    EXPECT_FALSE(chw_storage.demandInletModelObject());

    // o --- Splitter --- o --- Storage --- o --- Mixer --- o
    EXPECT_EQ(7, useLoop.supplyComponents().size()) << getObjectNames(useLoop.supplyComponents());
    EXPECT_EQ(5, useLoop.demandComponents().size()) << getObjectNames(useLoop.demandComponents());        // o --- Splitter --- o --- Mixer --- o
    EXPECT_EQ(5, sourceLoop.supplyComponents().size()) << getObjectNames(sourceLoop.supplyComponents());  // o --- Splitter --- o --- Mixer --- o
    EXPECT_EQ(5, sourceLoop.demandComponents().size()) << getObjectNames(sourceLoop.demandComponents());  // o --- Splitter --- o --- Mixer --- o
  }

  {
    EXPECT_TRUE(sourceLoop.addDemandBranchForComponent(chw_storage));
    ASSERT_TRUE(chw_storage.plantLoop());
    ASSERT_TRUE(chw_storage.secondaryPlantLoop());
    EXPECT_NE(chw_storage.plantLoop()->handle(), chw_storage.secondaryPlantLoop()->handle());
    EXPECT_EQ(useLoop, chw_storage.plantLoop().get());
    EXPECT_EQ(sourceLoop, chw_storage.secondaryPlantLoop().get());
    EXPECT_TRUE(chw_storage.supplyInletModelObject());
    EXPECT_TRUE(chw_storage.supplyInletModelObject());
    EXPECT_TRUE(chw_storage.demandInletModelObject());
    EXPECT_TRUE(chw_storage.demandInletModelObject());

    // o --- Splitter --- o --- Storage --- o --- Mixer --- o
    EXPECT_EQ(7, useLoop.supplyComponents().size()) << getObjectNames(useLoop.supplyComponents());
    EXPECT_EQ(5, useLoop.demandComponents().size()) << getObjectNames(useLoop.demandComponents());  // o --- Splitter --- o --- Mixer --- o

    EXPECT_EQ(5, sourceLoop.supplyComponents().size()) << getObjectNames(sourceLoop.supplyComponents());  // o --- Splitter --- o --- Mixer --- o

    // o --- Splitter --- o --- Storage --- o --- Mixer --- o
    EXPECT_EQ(7, sourceLoop.demandComponents().size()) << getObjectNames(sourceLoop.supplyComponents());
  }

  AirLoopHVAC airLoop(m);

  Node supplyOutletNode = airLoop.supplyOutletNode();

  EXPECT_FALSE(chw_storage.addToNode(supplyOutletNode));
  EXPECT_EQ(2, airLoop.supplyComponents().size());
}

TEST_F(ModelFixture, ThermalStorageChilledWaterStratified_HeatCoolFuelTypes) {
  Model m;
  ThermalStorageChilledWaterStratified chw_storage(m);

  EXPECT_EQ(ComponentType(ComponentType::Cooling), chw_storage.componentType());
  testFuelTypeEquality({}, chw_storage.coolingFuelTypes());
  testFuelTypeEquality({}, chw_storage.heatingFuelTypes());
  testAppGFuelTypeEquality({}, chw_storage.appGHeatingFuelTypes());

  PlantLoop plantLoop(m);
  ChillerElectricEIR chiller(m);
  EXPECT_TRUE(plantLoop.addSupplyBranchForComponent(chiller));
  EXPECT_TRUE(plantLoop.addDemandBranchForComponent(chw_storage));

  EXPECT_EQ(ComponentType(ComponentType::Cooling), chw_storage.componentType());
  testFuelTypeEquality({FuelType::Electricity}, chw_storage.coolingFuelTypes());
  testFuelTypeEquality({}, chw_storage.heatingFuelTypes());
  testAppGFuelTypeEquality({}, chw_storage.appGHeatingFuelTypes());
}
