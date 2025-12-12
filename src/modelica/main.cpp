#include <fmt/core.h>
#include <iostream>
#include <antlr4-runtime.h>
#include "utilities/core/ApplicationPathHelpers.hpp"
#include "ModelicaFile.hpp"

int main() {
  const auto moPath = openstudio::getApplicationSourceDirectory() / "resources/Examples/compact_osw/modelica/OpenStudioExample/SeedBuilding.mo";

  openstudio::modelica::ModelicaFile moFile(moPath);

  auto classDefinitions = moFile.getClassDefinitions();

  for (const auto& classDef : classDefinitions) {
    std::cout << "Found class name: " << classDef.longClassSpecifier() << std::endl;  // NOLINT
  }

  const auto& class1 = classDefinitions.front();
  class1.addComponentClause("Buildings.ThermalZones.EnergyPlus_24_2_0.ThermalZone zon2(redeclare package Medium = Medium, zoneName = \"MyZone2\");");

  std::cout << moFile.getText() << std::endl;  // NOLINT

  return 0;
}
