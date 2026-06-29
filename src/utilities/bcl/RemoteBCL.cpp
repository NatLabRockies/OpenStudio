/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include "LocalBCL.hpp"
#include "RemoteBCL.hpp"
#include "../core/Assert.hpp"
#include "../core/PathHelpers.hpp"
#include "../core/StringHelpers.hpp"
#include "../core/System.hpp"
#include "../core/UnzipFile.hpp"
#include "../core/DeprecatedHelpers.hpp"

#include <httplib.h>

#include <regex>

#define REMOTE_PRODUCTION_SERVER "https://bcl.nlr.gov"
#define REMOTE_DEVELOPMENT_SERVER "https://bcl-test.nlr.gov"

namespace {

std::unique_ptr<httplib::Client> makeClient(const std::string& baseUrl, unsigned timeOutSeconds) {
  auto cli = std::make_unique<httplib::Client>(baseUrl);
  cli->enable_server_certificate_verification(false);
  cli->set_follow_location(true);
  cli->set_connection_timeout(static_cast<int>(timeOutSeconds), 0);
  cli->set_read_timeout(static_cast<int>(timeOutSeconds), 0);
  cli->set_write_timeout(static_cast<int>(timeOutSeconds), 0);
  return cli;
}

}  // namespace

namespace openstudio {

namespace {
  // Map legacy API v2.0 bundle names to new API names
  std::string normalizeFilterType(const std::string& filterType) {
    if (filterType == "nrel_component") {
      return "component";
    }
    if (filterType == "nrel_measure") {
      return "measure";
    }
    return filterType;
  }

  // Look up the taxonomy name for a given TID, searching the component or measure taxonomy
  // based on the normalized filter type. Returns empty string if not found.
  std::string tidToTagName(unsigned tid, const std::string& normalizedFilterType) {
    const auto& taxonomy = (normalizedFilterType == "component") ? RemoteBCL::componentTaxonomy() : RemoteBCL::measureTaxonomy();
    for (const auto& item : taxonomy) {
      if (static_cast<unsigned>(item.tid) == tid) {
        return item.full_name;
      }
    }
    return "";
  }
}  // namespace

const std::vector<TaxonomyItem>& RemoteBCL::measureTaxonomy() {

  static const std::vector<TaxonomyItem> result = {

    {.full_name = "Economics", .tid = 1120, .name = "Economics", .children = {1}},
    {.full_name = "Economics.Life Cycle Cost Analysis", .tid = 1121, .name = "Life Cycle Cost Analysis", .parent = 0},

    {.full_name = "Electric Lighting", .tid = 954, .name = "Electric Lighting", .children = {3, 4}},
    {.full_name = "Electric Lighting.Electric Lighting Controls", .tid = 965, .name = "Electric Lighting Controls", .parent = 2},
    {.full_name = "Electric Lighting.Lighting Equipment", .tid = 966, .name = "Lighting Equipment", .parent = 2},

    {.full_name = "Envelope", .tid = 953, .name = "Envelope", .children = {6, 7, 8, 9, 10, 11}},
    {.full_name = "Envelope.Construction Sets", .tid = 1139, .name = "Construction Sets", .parent = 5},
    {.full_name = "Envelope.Daylighting", .tid = 961, .name = "Daylighting", .parent = 5},
    {.full_name = "Envelope.Fenestration", .tid = 960, .name = "Fenestration", .parent = 5},
    {.full_name = "Envelope.Form", .tid = 962, .name = "Form", .parent = 5},
    {.full_name = "Envelope.Infiltration", .tid = 963, .name = "Infiltration", .parent = 5},
    {.full_name = "Envelope.Opaque", .tid = 964, .name = "Opaque", .parent = 5},

    {.full_name = "Equipment", .tid = 955, .name = "Equipment", .children = {13, 14, 15}},
    {.full_name = "Equipment.Electric Equipment", .tid = 968, .name = "Electric Equipment", .parent = 12},
    {.full_name = "Equipment.Equipment Controls", .tid = 967, .name = "Equipment Controls", .parent = 12},
    {.full_name = "Equipment.Gas Equipment", .tid = 1140, .name = "Gas Equipment", .parent = 12},

    {.full_name = "HVAC", .tid = 956, .name = "HVAC", .children = {17, 18, 19, 20, 21, 22, 23, 24}},
    {.full_name = "HVAC.Cooling", .tid = 971, .name = "Cooling", .parent = 16},
    {.full_name = "HVAC.Distribution", .tid = 974, .name = "Distribution", .parent = 16},
    {.full_name = "HVAC.Energy Recovery", .tid = 973, .name = "Energy Recovery", .parent = 16},
    {.full_name = "HVAC.Heating", .tid = 970, .name = "Heating", .parent = 16},
    {.full_name = "HVAC.Heat Rejection", .tid = 972, .name = "Heat Rejection", .parent = 16},
    {.full_name = "HVAC.HVAC Controls", .tid = 969, .name = "HVAC Controls", .parent = 16},
    {.full_name = "HVAC.Ventilation", .tid = 975, .name = "Ventilation", .parent = 16},
    {.full_name = "HVAC.Whole System", .tid = 976, .name = "Whole System", .parent = 16},

    {.full_name = "Onsite Power Generation", .tid = 1064, .name = "Onsite Power Generation", .children = {26}},
    {.full_name = "Onsite Power Generation.Photovoltaic", .tid = 1065, .name = "Photovoltaic", .parent = 25},

    {.full_name = "People", .tid = 1132, .name = "People", .children = {28, 29}},
    {.full_name = "People.Characteristics", .tid = 1134, .name = "Characteristics", .parent = 27},
    {.full_name = "People.People Schedules", .tid = 1135, .name = "People Schedules", .parent = 27},

    {.full_name = "Refrigeration", .tid = 957, .name = "Refrigeration", .children = {31, 32, 33, 34, 35}},
    {.full_name = "Refrigeration.Cases and Walkins", .tid = 1343, .name = "Cases and Walkins", .parent = 30},
    {.full_name = "Refrigeration.Compressors", .tid = 1344, .name = "Compressors", .parent = 30},
    {.full_name = "Refrigeration.Condensers", .tid = 1345, .name = "Condensers", .parent = 30},
    {.full_name = "Refrigeration.Heat Reclaim", .tid = 1346, .name = "Heat Reclaim", .parent = 30},
    {.full_name = "Refrigeration.Refrigeration Controls", .tid = 1342, .name = "Refrigeration Controls", .parent = 30},

    {.full_name = "Reporting", .tid = 959, .name = "Reporting", .children = {37, 38}},
    {.full_name = "Reporting.QAQC", .tid = 980, .name = "QAQC", .parent = 36},
    {.full_name = "Reporting.Troubleshooting", .tid = 981, .name = "Troubleshooting", .parent = 36},

    {.full_name = "Service Water Heating", .tid = 958, .name = "Service Water Heating", .children = {40, 41, 42}},
    {.full_name = "Service Water Heating.Distribution", .tid = 979, .name = "Distribution", .parent = 39},
    {.full_name = "Service Water Heating.Water Heating", .tid = 978, .name = "Water Heating", .parent = 39},
    {.full_name = "Service Water Heating.Water Use", .tid = 977, .name = "Water Use", .parent = 39},

    {.full_name = "Whole Building", .tid = 1136, .name = "Whole Building", .children = {44, 45}},
    {.full_name = "Whole Building.Space Types", .tid = 1138, .name = "Space Types", .parent = 43},
    {.full_name = "Whole Building.Whole Building Schedules", .tid = 1137, .name = "Whole Building Schedules", .parent = 43},

  };

  return result;
}

const std::vector<TaxonomyItem>& RemoteBCL::componentTaxonomy() {
  static const std::vector<TaxonomyItem> result = {
    {.full_name = "Construction Assembly", .tid = 127, .name = "Construction Assembly", .children = {1, 5, 13, 20}},
    {.full_name = "Construction Assembly.Fenestration", .tid = 1315, .name = "Fenestration", .parent = 0, .children = {2, 3, 4}},
    {.full_name = "Construction Assembly.Fenestration.Door", .tid = 1317, .name = "Door", .parent = 1},
    {.full_name = "Construction Assembly.Fenestration.Skylight", .tid = 1318, .name = "Skylight", .parent = 1},
    {.full_name = "Construction Assembly.Fenestration.Window", .tid = 1316, .name = "Window", .parent = 1},
    {.full_name = "Construction Assembly.Floor", .tid = 152, .name = "Floor", .parent = 0, .children = {6, 7, 8, 9, 10, 11, 12}},
    {.full_name = "Construction Assembly.Floor.Attic Floor", .tid = 928, .name = "Attic Floor", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Exposed Floor", .tid = 153, .name = "Exposed Floor", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Exterior Slab", .tid = 154, .name = "Exterior Slab", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Floor Above Crawlspace", .tid = 899, .name = "Floor Above Crawlspace", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Floor Above Uncond Bsmt", .tid = 900, .name = "Floor Above Uncond Bsmt", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Floor Above Uncond Garage", .tid = 901, .name = "Floor Above Uncond Garage", .parent = 5},
    {.full_name = "Construction Assembly.Floor.Interior Floor", .tid = 927, .name = "Interior Floor", .parent = 5},
    {.full_name = "Construction Assembly.Roof Ceiling", .tid = 134, .name = "Roof Ceiling", .parent = 0, .children = {14, 15, 16, 17, 18, 19}},
    {.full_name = "Construction Assembly.Roof Ceiling.Attic Roof", .tid = 887, .name = "Attic Roof", .parent = 13},
    {.full_name = "Construction Assembly.Roof Ceiling.Crawlspace Ceiling", .tid = 931, .name = "Crawlspace Ceiling", .parent = 13},
    {.full_name = "Construction Assembly.Roof Ceiling.Exterior Roof", .tid = 929, .name = "Exterior Roof", .parent = 13},
    {.full_name = "Construction Assembly.Roof Ceiling.Interior Ceiling", .tid = 930, .name = "Interior Ceiling", .parent = 13},
    {.full_name = "Construction Assembly.Roof Ceiling.Uncond Bsmt Ceiling", .tid = 932, .name = "Uncond Bsmt Ceiling", .parent = 13},
    {.full_name = "Construction Assembly.Roof Ceiling.Uncond Garage Ceiling", .tid = 933, .name = "Uncond Garage Ceiling", .parent = 13},
    {.full_name = "Construction Assembly.Wall", .tid = 129, .name = "Wall", .parent = 0, .children = {21, 22, 23}},
    {.full_name = "Construction Assembly.Wall.Below Grade Wall", .tid = 131, .name = "Below Grade Wall", .parent = 20},
    {.full_name = "Construction Assembly.Wall.Exterior Wall", .tid = 130, .name = "Exterior Wall", .parent = 20},
    {.full_name = "Construction Assembly.Wall.Interior Wall", .tid = 132, .name = "Interior Wall", .parent = 20},

    {.full_name = "Electric Lighting", .tid = 946, .name = "Electric Lighting", .children = {25, 27}},
    {.full_name = "Electric Lighting.Lamp Ballasts", .tid = 949, .name = "Lamp Ballasts", .parent = 24, .children = {26}},
    {.full_name = "Electric Lighting.Lamp Ballasts.Lamp Ballasts", .tid = 1110, .name = "Lamp Ballasts", .parent = 25},
    {.full_name = "Electric Lighting.Lamps", .tid = 947, .name = "Lamps", .parent = 24, .children = {28, 29}},
    {.full_name = "Electric Lighting.Lamps.Non-SSL Lamps", .tid = 1070, .name = "Non-SSL Lamps", .parent = 27},
    {.full_name = "Electric Lighting.Lamps.SSL Replacement Lamps", .tid = 1406, .name = "SSL Replacement Lamps", .parent = 27},

    {.full_name = "EmissionFactors", .tid = 265, .name = "EmissionFactors", .children = {31, 32}},
    {.full_name = "EmissionFactors.Electricity Emission Factors (by State)",
     .tid = 266,
     .name = "Electricity Emission Factors (by State)",
     .parent = 30},
    {.full_name = "EmissionFactors.FossilFuel Emission Factors (by Type)", .tid = 267, .name = "FossilFuel Emission Factors (by Type)", .parent = 30},

    {.full_name = "HVAC", .tid = 210, .name = "HVAC", .children = {34, 36, 38, 41, 42, 49, 51, 53, 55, 57}},
    {.full_name = "HVAC.Boilers", .tid = 1340, .name = "Boilers", .parent = 33, .children = {35}},
    {.full_name = "HVAC.Boilers.Hot-Water Boilers", .tid = 1341, .name = "Hot-Water Boilers", .parent = 34},
    {.full_name = "HVAC.Compressors", .tid = 1281, .name = "Compressors", .parent = 33, .children = {37}},
    {.full_name = "HVAC.Compressors.Positive Displacement Refrigeration Compressors",
     .tid = 1280,
     .name = "Positive Displacement Refrigeration Compressors",
     .parent = 36},
    {.full_name = "HVAC.Ductless Heat Pump", .tid = 1337, .name = "Ductless Heat Pump", .parent = 33, .children = {39, 40}},
    {.full_name = "HVAC.Ductless Heat Pump.Indoor Unit", .tid = 1338, .name = "Indoor Unit", .parent = 38},
    {.full_name = "HVAC.Ductless Heat Pump.Outdoor Unit", .tid = 1339, .name = "Outdoor Unit", .parent = 38},
    {.full_name = "HVAC.Energy Recovery", .tid = 1333, .name = "Energy Recovery", .parent = 33},
    {.full_name = "HVAC.Fan", .tid = 1282, .name = "Fan", .parent = 33, .children = {43, 44, 45, 46, 47, 48}},
    {.full_name = "HVAC.Fan.Axial Fan", .tid = 1284, .name = "Axial Fan", .parent = 42},
    {.full_name = "HVAC.Fan.Centrifugal Fan", .tid = 1283, .name = "Centrifugal Fan", .parent = 42},
    {.full_name = "HVAC.Fan.Cross Flow Fan", .tid = 1286, .name = "Cross Flow Fan", .parent = 42},
    {.full_name = "HVAC.Fan.Mixed Flow Fan", .tid = 1285, .name = "Mixed Flow Fan", .parent = 42},
    {.full_name = "HVAC.Fan.Powered Roof Ventilator", .tid = 1288, .name = "Powered Roof Ventilator", .parent = 42},
    {.full_name = "HVAC.Fan.Tubular Centrifugal Fan", .tid = 1287, .name = "Tubular Centrifugal Fan", .parent = 42},
    {.full_name = "HVAC.Hydronic Cooling Equipment", .tid = 1130, .name = "Hydronic Cooling Equipment", .parent = 33, .children = {50}},
    {.full_name = "HVAC.Hydronic Cooling Equipment.Electrically-Driven Mechanical-Compression Chillers",
     .tid = 1261,
     .name = "Electrically-Driven Mechanical-Compression Chillers",
     .parent = 49},
    {.full_name = "HVAC.Hydronic Heating Equipment", .tid = 1259, .name = "Hydronic Heating Equipment", .parent = 33, .children = {52}},
    {.full_name = "HVAC.Hydronic Heating Equipment.Boilers", .tid = 1260, .name = "Boilers", .parent = 51},
    {.full_name = "HVAC.Motor", .tid = 1265, .name = "Motor", .parent = 33, .children = {54}},
    {.full_name = "HVAC.Motor.Electric Motor", .tid = 1266, .name = "Electric Motor", .parent = 53},
    {.full_name = "HVAC.Packaged Unitary Equipment", .tid = 1278, .name = "Packaged Unitary Equipment", .parent = 33, .children = {56}},
    {.full_name = "HVAC.Packaged Unitary Equipment.Rooftop Units", .tid = 1279, .name = "Rooftop Units", .parent = 55},
    {.full_name = "HVAC.Pumps", .tid = 231, .name = "Pumps", .parent = 33, .children = {58}},
    {.full_name = "HVAC.Pumps.Rotodynamic Pumps", .tid = 1125, .name = "Rotodynamic Pumps", .parent = 57},

    {.full_name = "Location-Dependent Component", .tid = 168, .name = "Location-Dependent Component", .children = {60, 61, 62, 63, 64, 65, 66}},
    {.full_name = "Location-Dependent Component.Cooling Degree Days", .tid = 171, .name = "Cooling Degree Days", .parent = 59},
    {.full_name = "Location-Dependent Component.Design Day", .tid = 121, .name = "Design Day", .parent = 59},
    {.full_name = "Location-Dependent Component.Ground Temperature", .tid = 172, .name = "Ground Temperature", .parent = 59},
    {.full_name = "Location-Dependent Component.Heating Degree Days", .tid = 170, .name = "Heating Degree Days", .parent = 59},
    {.full_name = "Location-Dependent Component.Site", .tid = 924, .name = "Site", .parent = 59},
    {.full_name = "Location-Dependent Component.Water Mains Temperature", .tid = 407, .name = "Water Mains Temperature", .parent = 59},
    {.full_name = "Location-Dependent Component.Weather File", .tid = 169, .name = "Weather File", .parent = 59},

    {.full_name = "Material", .tid = 157, .name = "Material", .children = {68, 69}},
    {.full_name = "Material.Material Heat and Moisture Transfer", .tid = 158, .name = "Material Heat and Moisture Transfer", .parent = 67},
    {.full_name = "Material.Opaque", .tid = 936, .name = "Opaque", .parent = 67, .children = {70, 71, 72, 73, 74, 75, 76, 77, 78}},
    {.full_name = "Material.Opaque.Building Board and Siding", .tid = 937, .name = "Building Board and Siding", .parent = 69},
    {.full_name = "Material.Opaque.Building Membrane", .tid = 938, .name = "Building Membrane", .parent = 69},
    {.full_name = "Material.Opaque.Finish Flooring", .tid = 939, .name = "Finish Flooring", .parent = 69},
    {.full_name = "Material.Opaque.Framing with Cavity", .tid = 945, .name = "Framing with Cavity", .parent = 69},
    {.full_name = "Material.Opaque.Insulation", .tid = 940, .name = "Insulation", .parent = 69},
    {.full_name = "Material.Opaque.Masonry", .tid = 943, .name = "Masonry", .parent = 69},
    {.full_name = "Material.Opaque.Plaster", .tid = 942, .name = "Plaster", .parent = 69},
    {.full_name = "Material.Opaque.Roofing", .tid = 941, .name = "Roofing", .parent = 69},
    {.full_name = "Material.Opaque.Solid Wood", .tid = 944, .name = "Solid Wood", .parent = 69},

    {.full_name = "MEL", .tid = 238, .name = "MEL", .children = {80, 97, 98, 102, 110, 113, 116, 130}},
    {.full_name = "MEL.Appliance",
     .tid = 421,
     .name = "Appliance",
     .parent = 79,
     .children = {81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96}},
    {.full_name = "MEL.Appliance.Beverage Fountain", .tid = 1270, .name = "Beverage Fountain", .parent = 80},
    {.full_name = "MEL.Appliance.Cash Exchange", .tid = 1275, .name = "Cash Exchange", .parent = 80},
    {.full_name = "MEL.Appliance.Coffee Maker", .tid = 1090, .name = "Coffee Maker", .parent = 80},
    {.full_name = "MEL.Appliance.Desktop Fan", .tid = 1095, .name = "Desktop Fan", .parent = 80},
    {.full_name = "MEL.Appliance.Drinking Fountain", .tid = 1269, .name = "Drinking Fountain", .parent = 80},
    {.full_name = "MEL.Appliance.Food Warmer", .tid = 1274, .name = "Food Warmer", .parent = 80},
    {.full_name = "MEL.Appliance.Freezer", .tid = 596, .name = "Freezer", .parent = 80},
    {.full_name = "MEL.Appliance.Ice Machine", .tid = 1096, .name = "Ice Machine", .parent = 80},
    {.full_name = "MEL.Appliance.Microwave", .tid = 1273, .name = "Microwave", .parent = 80},
    {.full_name = "MEL.Appliance.Mini-fridge", .tid = 1098, .name = "Mini-fridge", .parent = 80},
    {.full_name = "MEL.Appliance.Personal Heater", .tid = 1100, .name = "Personal Heater", .parent = 80},
    {.full_name = "MEL.Appliance.Refrigerated Vending Machine", .tid = 1272, .name = "Refrigerated Vending Machine", .parent = 80},
    {.full_name = "MEL.Appliance.Refrigerator", .tid = 1104, .name = "Refrigerator", .parent = 80},
    {.full_name = "MEL.Appliance.Vending Machine", .tid = 1105, .name = "Vending Machine", .parent = 80},
    {.full_name = "MEL.Appliance.Water Cooler", .tid = 916, .name = "Water Cooler", .parent = 80},
    {.full_name = "MEL.Appliance.Water Purifier", .tid = 1271, .name = "Water Purifier", .parent = 80},
    {.full_name = "MEL.Audio", .tid = 411, .name = "Audio", .parent = 79},
    {.full_name = "MEL.Computer", .tid = 239, .name = "Computer", .parent = 79, .children = {99, 100, 101}},
    {.full_name = "MEL.Computer.Desktop", .tid = 475, .name = "Desktop", .parent = 98},
    {.full_name = "MEL.Computer.Integrated Display Computer", .tid = 1097, .name = "Integrated Display Computer", .parent = 98},
    {.full_name = "MEL.Computer.Notebook", .tid = 478, .name = "Notebook", .parent = 98},
    {.full_name = "MEL.Display", .tid = 413, .name = "Display", .parent = 79, .children = {103, 104, 105, 106, 107, 108, 109}},
    {.full_name = "MEL.Display.CRT Monitor", .tid = 484, .name = "CRT Monitor", .parent = 102},
    {.full_name = "MEL.Display.CRT Television", .tid = 1094, .name = "CRT Television", .parent = 102},
    {.full_name = "MEL.Display.Digital Photo Frame", .tid = 1268, .name = "Digital Photo Frame", .parent = 102},
    {.full_name = "MEL.Display.LCD Monitor", .tid = 485, .name = "LCD Monitor", .parent = 102},
    {.full_name = "MEL.Display.LCD Television", .tid = 1267, .name = "LCD Television", .parent = 102},
    {.full_name = "MEL.Display.Plasma Television", .tid = 1102, .name = "Plasma Television", .parent = 102},
    {.full_name = "MEL.Display.Projector", .tid = 1103, .name = "Projector", .parent = 102},
    {.full_name = "MEL.Imaging and Printing", .tid = 414, .name = "Imaging and Printing", .parent = 79, .children = {111, 112}},
    {.full_name = "MEL.Imaging and Printing.Network Printer / Fax / Scanner", .tid = 1099, .name = "Network Printer / Fax / Scanner", .parent = 110},
    {.full_name = "MEL.Imaging and Printing.Personal Printer / Fax / Scanner",
     .tid = 1101,
     .name = "Personal Printer / Fax / Scanner",
     .parent = 110},
    {.full_name = "MEL.Lighting", .tid = 430, .name = "Lighting", .parent = 79, .children = {114, 115}},
    {.full_name = "MEL.Lighting.Egress Light", .tid = 1277, .name = "Egress Light", .parent = 113},
    {.full_name = "MEL.Lighting.Task Light", .tid = 1276, .name = "Task Light", .parent = 113},
    {.full_name = "MEL.Medical",
     .tid = 431,
     .name = "Medical",
     .parent = 79,
     .children = {117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129}},
    {.full_name = "MEL.Medical.Blood Pressure Cuff", .tid = 1352, .name = "Blood Pressure Cuff", .parent = 116},
    {.full_name = "MEL.Medical.Computed Tomography", .tid = 1350, .name = "Computed Tomography", .parent = 116},
    {.full_name = "MEL.Medical.Electrosurgical Unit", .tid = 1353, .name = "Electrosurgical Unit", .parent = 116},
    {.full_name = "MEL.Medical.Exam Bed", .tid = 1354, .name = "Exam Bed", .parent = 116},
    {.full_name = "MEL.Medical.Exam Chair", .tid = 1355, .name = "Exam Chair", .parent = 116},
    {.full_name = "MEL.Medical.Exam Light", .tid = 1356, .name = "Exam Light", .parent = 116},
    {.full_name = "MEL.Medical.Infusion Pump", .tid = 1357, .name = "Infusion Pump", .parent = 116},
    {.full_name = "MEL.Medical.Magnetic Resonance Imaging", .tid = 1351, .name = "Magnetic Resonance Imaging", .parent = 116},
    {.full_name = "MEL.Medical.Phototherapy Equipment", .tid = 1358, .name = "Phototherapy Equipment", .parent = 116},
    {.full_name = "MEL.Medical.Smoke Evaporator", .tid = 1359, .name = "Smoke Evaporator", .parent = 116},
    {.full_name = "MEL.Medical.Surgical Clipper", .tid = 1360, .name = "Surgical Clipper", .parent = 116},
    {.full_name = "MEL.Medical.Surgical Light", .tid = 1361, .name = "Surgical Light", .parent = 116},
    {.full_name = "MEL.Medical.Vital Signs Monitor", .tid = 1362, .name = "Vital Signs Monitor", .parent = 116},
    {.full_name = "MEL.Personal Care", .tid = 435, .name = "Personal Care", .parent = 79},

    {.full_name = "Occupant", .tid = 935, .name = "Occupant"},

    {.full_name = "On-Site Power Generation", .tid = 249, .name = "On-Site Power Generation", .children = {133}},
    {.full_name = "On-Site Power Generation.Photovoltaic System",
     .tid = 250,
     .name = "Photovoltaic System",
     .parent = 132,
     .children = {134, 135, 136, 137}},
    {.full_name = "On-Site Power Generation.Photovoltaic System.Combiner Box", .tid = 952, .name = "Combiner Box", .parent = 133},
    {.full_name = "On-Site Power Generation.Photovoltaic System.Inverter", .tid = 950, .name = "Inverter", .parent = 133},
    {.full_name = "On-Site Power Generation.Photovoltaic System.Photovoltaic Module", .tid = 934, .name = "Photovoltaic Module", .parent = 133},
    {.full_name = "On-Site Power Generation.Photovoltaic System.Racking System", .tid = 951, .name = "Racking System", .parent = 133},

    {.full_name = "Plumbing", .tid = 1248, .name = "Plumbing", .children = {139}},
    {.full_name = "Plumbing.Water Fixture", .tid = 1249, .name = "Water Fixture", .parent = 138, .children = {140, 141, 142, 143}},
    {.full_name = "Plumbing.Water Fixture.Faucet", .tid = 1250, .name = "Faucet", .parent = 139},
    {.full_name = "Plumbing.Water Fixture.Shower Head", .tid = 1251, .name = "Shower Head", .parent = 139},
    {.full_name = "Plumbing.Water Fixture.Toilet", .tid = 1252, .name = "Toilet", .parent = 139},
    {.full_name = "Plumbing.Water Fixture.Urinal", .tid = 1253, .name = "Urinal", .parent = 139},

    {.full_name = "Service Water Heating", .tid = 1334, .name = "Service Water Heating", .children = {145}},
    {.full_name = "Service Water Heating.Tank Water Heater", .tid = 1335, .name = "Tank Water Heater", .parent = 144, .children = {146}},
    {.full_name = "Service Water Heating.Tank Water Heater.Heat Pump Water Heater", .tid = 1336, .name = "Heat Pump Water Heater", .parent = 145},

    {.full_name = "Special Days", .tid = 1124, .name = "Special Days"},

    {.full_name = "Whole Building", .tid = 1347, .name = "Whole Building"},
  };

  return result;
}

std::ostream& operator<<(std::ostream& os, const pugi::xml_document& element) {
  element.save(os, "  ");
  return os;
}

RemoteQueryResponse::RemoteQueryResponse(std::shared_ptr<pugi::xml_document>& domDocument) : m_domDocument(domDocument) {}

pugi::xml_node RemoteQueryResponse::root() const {
  return m_domDocument->document_element();
}

unsigned RemoteBCL::timeOutSeconds() const {
  return m_timeOutSeconds;
}
bool RemoteBCL::setTimeOutSeconds(unsigned timeOutSeconds) {
  if (timeOutSeconds < 10) {
    LOG(Error, "Setting a timeout of " << timeOutSeconds << " is too low.");
    return false;
  } else if (timeOutSeconds < 60) {
    LOG(Warn, "Setting a timeout of " << timeOutSeconds << " appears low and you risk failures to download components and measures");
  }
  m_timeOutSeconds = timeOutSeconds;
  return true;
}

bool RemoteBCL::DownloadFile::open() {
  OS_ASSERT(!m_fileName.empty());
  m_ofs.open(toString(m_fileName).c_str(), std::ios_base::trunc | std::ios_base::out | std::ios_base::binary);
  return m_ofs.good();
}

RemoteBCL::DownloadFile::DownloadFile(openstudio::path t_path) : m_fileName(std::move(t_path)) {}

void RemoteBCL::DownloadFile::flush() {
  if (m_ofs.good()) {
    m_ofs.flush();
  }
}

const openstudio::path& RemoteBCL::DownloadFile::fileName() const noexcept {
  return m_fileName;
}

void RemoteBCL::DownloadFile::close() {
  m_ofs.close();
}

void RemoteBCL::DownloadFile::write(const std::string& data) {
  m_ofs.write(data.data(), static_cast<std::streamsize>(data.size()));
}

RemoteBCL::RemoteBCL()
  : m_prodAuthKey(LocalBCL::instance().prodAuthKey()),
    m_devAuthKey(LocalBCL::instance().devAuthKey()),
    m_numResultsPerQuery(10),
    m_lastTotalResults(0),
    validProdAuthKey(false),
    validDevAuthKey(false),
    m_timeOutSeconds(120) {
  useRemoteProductionUrl();
}

///////////////////////////////////////////////////////////////////////////
/// Inherited members
///////////////////////////////////////////////////////////////////////////

boost::optional<BCLComponent> RemoteBCL::getComponent(const std::string& uid, const std::string& /*versionId*/) const {
  bool downloadStarted = const_cast<RemoteBCL*>(this)->downloadComponent(uid);
  if (downloadStarted) {
    return waitForComponentDownload();
  }
  return boost::none;
}

boost::optional<BCLMeasure> RemoteBCL::getMeasure(const std::string& uid, const std::string& /*versionId*/) const {
  bool downloadStarted = const_cast<RemoteBCL*>(this)->downloadMeasure(uid);
  if (downloadStarted) {
    return waitForMeasureDownload();
  }
  return boost::none;
}

boost::optional<BCLMetaSearchResult> RemoteBCL::metaSearchComponentLibrary(const std::string& searchTerm, const std::string& componentType,
                                                                           const std::string& filterType) const {
  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibraryMetaSearch(searchTerm, componentType, filterType);
  if (searchStarted) {
    return waitForMetaSearch();
  }
  return boost::none;
}

boost::optional<BCLMetaSearchResult> RemoteBCL::metaSearchComponentLibrary(const std::string& searchTerm, const unsigned componentTypeTID,
                                                                           const std::string& filterType) const {
  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibraryMetaSearch(searchTerm, componentTypeTID, filterType);
  if (searchStarted) {
    return waitForMetaSearch();
  }
  return boost::none;
}

std::vector<BCLSearchResult> RemoteBCL::searchComponentLibrary(const std::string& searchTerm, const std::string& componentType,
                                                               const unsigned page) const {
  // Perform metaSearch first
  metaSearchComponentLibrary(searchTerm, componentType, "component");
  if (lastTotalResults() == 0) {
    return {};
  }

  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibrarySearch(searchTerm, componentType, "component", page);
  if (searchStarted) {
    return waitForSearch();
  }
  return {};
}

std::vector<BCLSearchResult> RemoteBCL::searchComponentLibrary(const std::string& searchTerm, const unsigned componentTypeTID,
                                                               const unsigned page) const {
  // Perform metaSearch first
  metaSearchComponentLibrary(searchTerm, componentTypeTID, "component");
  if (lastTotalResults() == 0) {
    return {};
  }

  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibrarySearch(searchTerm, componentTypeTID, "component", page);
  if (searchStarted) {
    return waitForSearch();
  }
  return {};
}

std::vector<BCLSearchResult> RemoteBCL::searchMeasureLibrary(const std::string& searchTerm, const std::string& componentType,
                                                             const unsigned page) const {
  // Perform metaSearch first
  metaSearchComponentLibrary(searchTerm, componentType, "measure");
  if (lastTotalResults() == 0) {
    return {};
  }

  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibrarySearch(searchTerm, componentType, "measure", page);
  if (searchStarted) {
    return waitForSearch();
  }
  return {};
}

std::vector<BCLSearchResult> RemoteBCL::searchMeasureLibrary(const std::string& searchTerm, const unsigned componentTypeTID,
                                                             const unsigned page) const {
  // Perform metaSearch first
  metaSearchComponentLibrary(searchTerm, componentTypeTID, "measure");
  if (lastTotalResults() == 0) {
    return {};
  }

  bool searchStarted = const_cast<RemoteBCL*>(this)->startComponentLibrarySearch(searchTerm, componentTypeTID, "measure", page);
  if (searchStarted) {
    return waitForSearch();
  }
  return {};
}

int RemoteBCL::checkForComponentUpdates() {
  m_componentsWithUpdates.clear();

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  for (const BCLComponent& component : LocalBCL::instance().components()) {
    m_lastSearch.clear();
    m_lastRequestSuccess = false;

    auto res = cli->Get("/api/search/*.xml", httplib::Params{{"fq", "uuid:" + component.uid()}}, httplib::Headers{});
    if (res && res->status == 200) {
      auto remoteQueryResponse = processReply(res->body);
      if (remoteQueryResponse) {
        m_lastSearch = processSearchResponse(*remoteQueryResponse);
      }
      m_lastRequestSuccess = true;
    } else {
      LOG(Error, "checkForComponentUpdates request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
    }

    if (!m_lastSearch.empty() && m_lastSearch[0].versionId() != component.versionId()) {
      m_componentsWithUpdates.push_back(m_lastSearch[0]);
    }
  }

  return static_cast<int>(m_componentsWithUpdates.size());
}

int RemoteBCL::checkForMeasureUpdates() {
  m_measuresWithUpdates.clear();

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  for (const BCLMeasure& measure : LocalBCL::instance().measures()) {
    m_lastSearch.clear();
    m_lastRequestSuccess = false;

    auto res = cli->Get("/api/search/*.xml", httplib::Params{{"fq", "uuid:" + measure.uid()}}, httplib::Headers{});
    if (res && res->status == 200) {
      auto remoteQueryResponse = processReply(res->body);
      if (remoteQueryResponse) {
        m_lastSearch = processSearchResponse(*remoteQueryResponse);
      }
      m_lastRequestSuccess = true;
    } else {
      LOG(Error, "checkForMeasureUpdates request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
    }

    if (!m_lastSearch.empty() && m_lastSearch[0].versionId() != measure.versionId()) {
      m_measuresWithUpdates.push_back(m_lastSearch[0]);
    }
  }

  return static_cast<int>(m_measuresWithUpdates.size());
}

std::vector<BCLSearchResult> RemoteBCL::componentsWithUpdates() const {
  return m_componentsWithUpdates;
}

std::vector<BCLSearchResult> RemoteBCL::measuresWithUpdates() const {
  return m_measuresWithUpdates;
}

void RemoteBCL::updateComponents() {
  if (m_componentsWithUpdates.empty()) {
    checkForComponentUpdates();
  }

  for (const BCLSearchResult& component : m_componentsWithUpdates) {
    downloadComponent(component.uid());
    boost::optional<BCLComponent> newComponent = waitForComponentDownload();

    if (newComponent) {
      LocalBCL::instance().removeOutdatedLocalComponents(newComponent->uid(), newComponent->versionId());
    }
  }
}

void RemoteBCL::updateMeasures() {
  if (m_measuresWithUpdates.empty()) {
    checkForMeasureUpdates();
  }

  for (const BCLSearchResult& measure : m_measuresWithUpdates) {
    downloadMeasure(measure.uid());
    boost::optional<BCLMeasure> newMeasure = waitForMeasureDownload();

    if (newMeasure) {
      LocalBCL::instance().removeOutdatedLocalMeasures(newMeasure->uid(), newMeasure->versionId());
    }
  }
}

///////////////////////////////////////////////////////////////////////////
/// Blocking class members
///////////////////////////////////////////////////////////////////////////

bool RemoteBCL::isOnline() {
  try {
    auto cli = makeClient("https://checkip.amazonaws.com", 10);

    auto res = cli->Get("/");
    if (!res || res->status != 200) {
      return false;
    }
    std::string ip = res->body;
    ip.erase(ip.find_last_not_of("\n\r") + 1);
    std::regex ipRegex("^\\d{1,3}(?:\\.\\d{1,3}){3}$");
    return std::regex_search(ip, ipRegex);
  } catch (const std::exception&) {
    // not online
  }
  return false;
}

boost::optional<BCLComponent> RemoteBCL::lastComponentDownload() const {
  return m_lastComponentDownload;
}

boost::optional<BCLMeasure> RemoteBCL::lastMeasureDownload() const {
  return m_lastMeasureDownload;
}

boost::optional<BCLMetaSearchResult> RemoteBCL::lastMetaSearch() const {
  return m_lastMetaSearch;
}

std::vector<BCLSearchResult> RemoteBCL::lastSearch() const {
  return m_lastSearch;
}

std::string RemoteBCL::remoteUrl() const {
  return m_remoteUrl;
}

std::string RemoteBCL::remoteProductionUrl() {
  return {REMOTE_PRODUCTION_SERVER};
}

std::string RemoteBCL::remoteDevelopmentUrl() {
  return {REMOTE_DEVELOPMENT_SERVER};
}

void RemoteBCL::useRemoteDevelopmentUrl() {
  m_useRemoteDevelopmentUrl = true;
  m_remoteUrl = remoteDevelopmentUrl();
  m_authKey = m_devAuthKey;
}

void RemoteBCL::useRemoteProductionUrl() {
  m_useRemoteDevelopmentUrl = false;
  m_remoteUrl = remoteProductionUrl();
  m_authKey = m_prodAuthKey;
}

std::string RemoteBCL::authKey() const {
  return m_authKey;
}

std::string RemoteBCL::prodAuthKey() const {
  return m_prodAuthKey;
}

bool RemoteBCL::setProdAuthKey(const std::string& prodAuthKey) {
  bool previousValidity = validProdAuthKey;
  if (validateAuthKey(prodAuthKey, remoteProductionUrl())) {
    m_prodAuthKey = prodAuthKey;
    if (!m_useRemoteDevelopmentUrl) {
      m_authKey = prodAuthKey;
    }
    return true;
  }
  validProdAuthKey = previousValidity;
  return false;
}

std::string RemoteBCL::devAuthKey() const {
  return m_devAuthKey;
}

bool RemoteBCL::setDevAuthKey(const std::string& devAuthKey) {
  bool previousValidity = validDevAuthKey;
  if (validateAuthKey(devAuthKey, remoteDevelopmentUrl())) {
    m_devAuthKey = devAuthKey;
    if (m_useRemoteDevelopmentUrl) {
      m_authKey = devAuthKey;
    }
    return true;
  }
  validDevAuthKey = previousValidity;
  return false;
}

int RemoteBCL::resultsPerQuery() const {
  return m_numResultsPerQuery;
}

int RemoteBCL::lastTotalResults() const {
  return m_lastTotalResults;
}

int RemoteBCL::numResultPages() const {
  double numerator(lastTotalResults());
  double denominator(resultsPerQuery());
  return int(std::ceil(numerator / denominator));
}

bool RemoteBCL::validateAuthKey(const std::string& authKey, const std::string& remoteUrl) {
  if (authKey.length() == 32) {
    std::string previousUrl = this->remoteUrl();

    // Check if validation has already run for the given key
    if (remoteUrl == remoteProductionUrl() && authKey == prodAuthKey() && validProdAuthKey) {
      return true;
    } else if (remoteUrl == remoteDevelopmentUrl() && authKey == devAuthKey() && validDevAuthKey) {
      return true;
    }

    // Temporarily set url
    if (remoteUrl == remoteDevelopmentUrl()) {
      useRemoteDevelopmentUrl();
    } else {
      useRemoteProductionUrl();
    }

    m_lastSearch.clear();
    m_lastRequestSuccess = false;

    auto cli = makeClient(remoteUrl, m_timeOutSeconds);
    auto res = cli->Get("/api/search/*.xml", httplib::Params{{"show_rows", "0"}}, httplib::Headers{});
    if (res && res->status == 200) {
      auto remoteQueryResponse = processReply(res->body);
      if (remoteQueryResponse) {
        m_lastSearch = processSearchResponse(*remoteQueryResponse);
      }
      m_lastRequestSuccess = true;
    } else {
      LOG(Error, "validateAuthKey request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
    }

    // Restore url
    if (previousUrl == remoteDevelopmentUrl()) {
      useRemoteDevelopmentUrl();
    } else {
      useRemoteProductionUrl();
    }

    if (remoteUrl == remoteDevelopmentUrl()) {
      return validDevAuthKey;
    } else {
      return validProdAuthKey;
    }
  }
  return false;
}

boost::optional<BCLComponent> RemoteBCL::waitForComponentDownload() const {
  if (waitForLock()) {
    return m_lastComponentDownload;
  }
  return boost::none;
}

boost::optional<BCLComponent> RemoteBCL::waitForComponentDownload(int) const {
  DEPRECATED_AT_MSG(3, 2, 1, "The int parameter is unused. Use waitForComponentDownload() instead");
  return waitForComponentDownload();
}

boost::optional<BCLMeasure> RemoteBCL::waitForMeasureDownload() const {
  if (waitForLock()) {
    return m_lastMeasureDownload;
  }
  return boost::none;
}

boost::optional<BCLMeasure> RemoteBCL::waitForMeasureDownload(int) const {
  DEPRECATED_AT_MSG(3, 2, 1, "The int parameter is unused. Use waitForMeasureDownload() instead");
  return waitForMeasureDownload();
}

boost::optional<BCLMetaSearchResult> RemoteBCL::waitForMetaSearch() const {
  if (waitForLock()) {
    return m_lastMetaSearch;
  }
  return boost::none;
}

boost::optional<BCLMetaSearchResult> RemoteBCL::waitForMetaSearch(int) const {
  DEPRECATED_AT_MSG(3, 2, 1, "The int parameter is unused. Use waitForMetaSearch() instead");
  return waitForMetaSearch();
}

std::vector<BCLSearchResult> RemoteBCL::waitForSearch() const {
  if (waitForLock()) {
    return m_lastSearch;
  }
  return {};
}

std::vector<BCLSearchResult> RemoteBCL::waitForSearch(int) const {
  DEPRECATED_AT_MSG(3, 2, 1, "The int parameter is unused. Use waitForSearch() instead");
  return waitForSearch();
}

///////////////////////////////////////////////////////////////////////////
/// Non-blocking class members
///////////////////////////////////////////////////////////////////////////

bool RemoteBCL::downloadComponent(const std::string& uid) {
  if (uid.empty()) {
    LOG(Error, "Error: No uid provided");
    return false;
  }

  m_downloadFile = std::make_unique<DownloadFile>(openstudio::filesystem::temp_directory_path() / toPath(uid + ".bcl"));
  if (!m_downloadFile->open()) {
    return false;
  }

  m_downloadUid = uid;
  m_lastRequestSuccess = false;

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  auto res = cli->Get("/api/download", httplib::Params{{"uids", uid}}, httplib::Headers{});
  if (res && res->status == 200) {
    m_downloadFile->write(res->body);
    m_downloadFile->flush();
    m_downloadFile->close();
    m_lastRequestSuccess = true;
    onDownloadComplete();
  } else {
    LOG(Error, "downloadComponent request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
    m_downloadFile->close();
  }

  return m_lastRequestSuccess;
}

bool RemoteBCL::downloadMeasure(const std::string& uid) {
  return downloadComponent(uid);
}

bool RemoteBCL::startComponentLibraryMetaSearch(const std::string& searchTerm, const std::string& componentType, const std::string& filterType) {
  m_lastMetaSearch.reset();
  m_lastRequestSuccess = false;

  const std::string normalizedFilterType = normalizeFilterType(filterType);

  std::string query = searchTerm.empty() ? "*" : searchTerm;
  std::string path = "/api/metasearch/" + query + ".xml";

  httplib::Params params{{"fq", "bundle:" + normalizedFilterType}};
  if (!componentType.empty() && componentType != "*") {
    std::string tag = (normalizedFilterType == "component") ? "component_tags" : "measure_tags";
    params.emplace("fq", tag + ":\"" + componentType + "\"");
  }

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  auto res = cli->Get(path, params, httplib::Headers{});
  if (res && res->status == 200) {
    auto remoteQueryResponse = processReply(res->body);
    if (remoteQueryResponse) {
      m_lastMetaSearch = processMetaSearchResponse(*remoteQueryResponse);
    }
    setLastTotalResults(m_lastMetaSearch ? m_lastMetaSearch->numResults() : 0);
    m_lastRequestSuccess = true;
  } else {
    setLastTotalResults(0);
    LOG(Error, "startComponentLibraryMetaSearch request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
  }

  return m_lastRequestSuccess;
}

bool RemoteBCL::startComponentLibraryMetaSearch(const std::string& searchTerm, const unsigned componentTypeTID, const std::string& filterType) {
  m_lastMetaSearch.reset();
  m_lastRequestSuccess = false;

  const std::string normalizedFilterType = normalizeFilterType(filterType);

  std::string query = searchTerm.empty() ? "*" : searchTerm;
  std::string path = "/api/metasearch/" + query + ".xml";

  httplib::Params params{{"fq", "bundle:" + normalizedFilterType}};
  if (componentTypeTID != 0) {
    const std::string tagName = tidToTagName(componentTypeTID, normalizedFilterType);
    if (!tagName.empty()) {
      const std::string tagField = (normalizedFilterType == "component") ? "component_tags" : "measure_tags";
      params.emplace("fq", tagField + ":\"" + tagName + "\"");
    } else {
      LOG(Warn, "Unknown TID " << componentTypeTID << " for bundle '" << normalizedFilterType << "', ignoring tag filter");
    }
  }

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  auto res = cli->Get(path, params, httplib::Headers{});
  if (res && res->status == 200) {
    auto remoteQueryResponse = processReply(res->body);
    if (remoteQueryResponse) {
      m_lastMetaSearch = processMetaSearchResponse(*remoteQueryResponse);
    }
    setLastTotalResults(m_lastMetaSearch ? m_lastMetaSearch->numResults() : 0);
    m_lastRequestSuccess = true;
  } else {
    setLastTotalResults(0);
    LOG(Error, "startComponentLibraryMetaSearch request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
  }

  return m_lastRequestSuccess;
}

bool RemoteBCL::startComponentLibrarySearch(const std::string& searchTerm, const std::string& componentType, const std::string& filterType,
                                            const unsigned page) {
  m_lastSearch.clear();
  m_lastRequestSuccess = false;

  const std::string normalizedFilterType = normalizeFilterType(filterType);

  std::string query = searchTerm.empty() ? "*" : searchTerm;
  std::string path = "/api/search/" + query + ".xml";

  httplib::Params params{{"fq", "bundle:" + normalizedFilterType},
                         {"show_rows", openstudio::string_conversions::number(m_numResultsPerQuery)},
                         {"page", openstudio::string_conversions::number(page)}};
  if (!componentType.empty() && componentType != "*") {
    std::string tag = (normalizedFilterType == "component") ? "component_tags" : "measure_tags";
    params.emplace("fq", tag + ":\"" + componentType + "\"");
  }

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  auto res = cli->Get(path, params, httplib::Headers{});
  if (res && res->status == 200) {
    auto remoteQueryResponse = processReply(res->body);
    if (remoteQueryResponse) {
      m_lastSearch = processSearchResponse(*remoteQueryResponse);
    }
    m_lastRequestSuccess = true;
  } else {
    LOG(Error, "startComponentLibrarySearch request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
  }

  return m_lastRequestSuccess;
}

bool RemoteBCL::startComponentLibrarySearch(const std::string& searchTerm, const unsigned componentTypeTID, const std::string& filterType,
                                            const unsigned page) {
  m_lastSearch.clear();
  m_lastRequestSuccess = false;

  const std::string normalizedFilterType = normalizeFilterType(filterType);

  std::string query = searchTerm.empty() ? "*" : searchTerm;
  std::string path = "/api/search/" + query + ".xml";

  httplib::Params params{{"fq", "bundle:" + normalizedFilterType},
                         {"show_rows", openstudio::string_conversions::number(m_numResultsPerQuery)},
                         {"page", openstudio::string_conversions::number(page)}};
  if (componentTypeTID != 0) {
    const std::string tagName = tidToTagName(componentTypeTID, normalizedFilterType);
    if (!tagName.empty()) {
      const std::string tagField = (normalizedFilterType == "component") ? "component_tags" : "measure_tags";
      params.emplace("fq", tagField + ":\"" + tagName + "\"");
    } else {
      LOG(Warn, "Unknown TID " << componentTypeTID << " for bundle '" << normalizedFilterType << "', ignoring tag filter");
    }
  }

  auto cli = makeClient(remoteUrl(), m_timeOutSeconds);
  auto res = cli->Get(path, params, httplib::Headers{});
  if (res && res->status == 200) {
    auto remoteQueryResponse = processReply(res->body);
    if (remoteQueryResponse) {
      m_lastSearch = processSearchResponse(*remoteQueryResponse);
    }
    m_lastRequestSuccess = true;
  } else {
    LOG(Error, "startComponentLibrarySearch request failed" << (res ? ": HTTP " + std::to_string(res->status) : ""));
  }

  return m_lastRequestSuccess;
}

bool RemoteBCL::waitForLock() const {
  return m_lastRequestSuccess;
}

boost::optional<RemoteQueryResponse> RemoteBCL::processReply(const std::string& reply) {
  std::shared_ptr<pugi::xml_document> document = std::make_shared<pugi::xml_document>();
  auto result = document->load_string(reply.c_str());
  if (!result) {
    LOG(Error, "Bad XML Response: " << result.description());
  } else {
    if (!m_useRemoteDevelopmentUrl) {
      validProdAuthKey = true;
    } else {
      validDevAuthKey = true;
    }
    return RemoteQueryResponse(document);
  }

  return boost::none;
}

boost::optional<BCLMetaSearchResult> RemoteBCL::processMetaSearchResponse(const RemoteQueryResponse& remoteQueryResponse) {
  auto root = remoteQueryResponse.root();

  if (root) {
    if (std::string(root.name()).compare(0, 6, "result") == 0) {  // C++20: std::string(root.name()).starts_with("result")
      auto numResultsElement = root.child("result_count");
      if (numResultsElement) {
        return BCLMetaSearchResult(root);
      }
    }
  }

  return boost::none;
}

std::vector<BCLSearchResult> RemoteBCL::processSearchResponse(const RemoteQueryResponse& remoteQueryResponse) {
  std::vector<BCLSearchResult> searchResults;

  auto root = remoteQueryResponse.root();
  auto result = root.child("result");
  if (result) {
    auto componentElement = result.first_child();

    //Basic check to see if it's non-empty
    while (componentElement.child("name") != nullptr) {
      //Skip components without a uid or version_id
      if ((componentElement.child("uuid") != nullptr) && (componentElement.child("vuuid") != nullptr)) {
        BCLSearchResult searchResult(componentElement);
        searchResults.push_back(searchResult);
      }
      result = result.next_sibling("result");
      componentElement = result.first_child();
    }
  }

  return searchResults;
}

void RemoteBCL::onDownloadComplete() {
  const auto src = m_downloadFile->fileName();
  std::string componentType;

  // Extract the files to a temp location
  openstudio::path tempDest = openstudio::filesystem::temp_directory_path() / toPath(m_downloadUid + '/');

  if (openstudio::filesystem::is_directory(tempDest)) {
    removeDirectory(tempDest);
  }
  openstudio::filesystem::create_directories(tempDest);

  std::vector<openstudio::path> createdFiles;
  try {
    openstudio::UnzipFile uf(src);
    createdFiles = uf.extractAllFiles(tempDest);
  } catch (const std::exception& e) {
    LOG(Error, "Cannot unzip file: " << e.what());
  }
  openstudio::filesystem::remove(src);

  // search for component.xml or measure.xml file
  boost::optional<openstudio::path> xmlPath;

  for (const auto& path : createdFiles) {
    if (path.filename() == toPath("component.xml")) {
      componentType = "component";
      m_lastComponentDownload.reset();
      xmlPath = path;
      break;
    } else if (path.filename() == toPath("measure.xml")) {
      componentType = "measure";
      m_lastMeasureDownload.reset();
      xmlPath = path;
      break;
    }
  }

  if (xmlPath) {
    // cppcheck-suppress shadowVariable
    path src = xmlPath->parent_path();
    path dest = src.parent_path();
    openstudio::filesystem::remove(dest / toPath("DISCLAIMER.txt"));
    openstudio::filesystem::remove(dest / toPath("README.txt"));
    openstudio::filesystem::remove(dest / toPath("output.xml"));
    copyDirectory(src, dest);
    removeDirectory(src);

    if (componentType == "component") {
      path componentXmlPath = dest / toPath("component.xml");
      // open the component to figure out uid and vid
      BCLComponent component(toString(componentXmlPath.parent_path()));
      std::string uid = component.uid();
      std::string versionId = component.versionId();

      // check if component has proper uid and vid
      if (!uid.empty() && !versionId.empty()) {
        dest = LocalBCL::instance().libraryPath() / uid / versionId;

        removeDirectory(dest);
        if (copyDirectory(componentXmlPath.parent_path(), dest)) {
          // Add to LocalBCL
          m_lastComponentDownload = BCLComponent(toString(dest));
          LocalBCL::instance().addComponent(*m_lastComponentDownload);
        }
      }
    } else if (componentType == "measure") {
      path measureXmlPath = dest / toPath("measure.xml");
      // open the measure to figure out uid and vid
      boost::optional<BCLMeasure> measure;
      try {
        measure = BCLMeasure(measureXmlPath.parent_path());

        std::string uid = measure->uid();
        std::string versionId = measure->versionId();

        // check if component has proper uid and vid
        if (!uid.empty() && !versionId.empty()) {
          dest = LocalBCL::instance().libraryPath() / uid / versionId;
          removeDirectory(dest);
          if (copyDirectory(measureXmlPath.parent_path(), dest)) {
            // Add to LocalBCL
            m_lastMeasureDownload = BCLMeasure(dest);
            LocalBCL::instance().addMeasure(*m_lastMeasureDownload);
          }
        }
      } catch (const std::exception&) {
        LOG(Error, "Unable to create measure from download: " + toString(measureXmlPath.parent_path()));
      }
    }
  } else {
    LOG(Error, "No component.xml or measure.xml file found in downloaded contents");
  }

  // delete the temp unzip directory
  removeDirectory(tempDest);

  if (componentType == "measure") {
    this->measureDownloaded.nano_emit(m_downloadUid, m_lastMeasureDownload);
  } else {
    this->componentDownloaded.nano_emit(m_downloadUid, m_lastComponentDownload);
  }
}

int RemoteBCL::setResultsPerQuery(const int numResults) {
  m_numResultsPerQuery = numResults <= 0 ? 10 : numResults > 100 ? 100 : numResults;
  return m_numResultsPerQuery;
}

void RemoteBCL::setLastTotalResults(const int lastTotalResults) {
  m_lastTotalResults = lastTotalResults;
}

}  // namespace openstudio
