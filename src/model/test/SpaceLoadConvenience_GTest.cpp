/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <gtest/gtest.h>
#include "ModelFixture.hpp"

#include "../Model.hpp"
#include "../Building.hpp"
#include "../SpaceType.hpp"
#include "../ThermalZone.hpp"
#include "../Space.hpp"

#include "../SpaceLoadInstance.hpp"
#include "../SpaceLoadDefinition.hpp"

#include "../People.hpp"
#include "../PeopleDefinition.hpp"

#include "../ElectricEquipment.hpp"
#include "../ElectricEquipmentDefinition.hpp"
#include "../Lights.hpp"
#include "../LightsDefinition.hpp"
#include "../HotWaterEquipment.hpp"
#include "../HotWaterEquipmentDefinition.hpp"
#include "../GasEquipment.hpp"
#include "../GasEquipmentDefinition.hpp"

#include "../../utilities/geometry/Point3d.hpp"

#include <concepts>
#include <ranges>
#include <string>
#include <vector>

using namespace openstudio;
using namespace openstudio::model;

std::pair<Model, std::vector<Space>> prepareModelWith4Spaces() {
  Model m;

  constexpr double width = 10.0;
  constexpr double height = 3.6;  // It's convenient for ACH, since 3600 s/hr
  constexpr double spaceFloorArea = width * width;

  //            y (=North)
  //   ▲
  //   │                  building height = 3m
  // 10├────────┼────────┼────────┼────────┤
  //   │        │        │        │        │
  //   │        │        │        │        │
  //   │ Space 1│ Space 2│ Space 3│ Space 4│
  //   │        │        │        │        │
  //   └────────┴────────┴────────┴────────┴──► x
  //  0        10       20        30       40

  // Counterclockwise points
  std::vector<Point3d> floorPointsSpace1{{0.0, 0.0, 0.0}, {0.0, width, 0.0}, {width, width, 0.0}, {width, 0.0, 0.0}};

  SpaceType spaceType(m);
  spaceType.setName("SpaceType");

  PeopleDefinition pd(m);
  pd.setName("People Definition");
  pd.setPeopleperSpaceFloorArea(5.0 / spaceFloorArea);  // 5 people per space
  People people(pd);
  people.setName("Space Type People");
  people.setSpaceType(spaceType);

  ThermalZone z(m);
  z.setName("Thermal Zone");
  std::vector<Space> spaces;
  for (int i = 0; i < 4; ++i) {
    auto space = Space::fromFloorPrint(floorPointsSpace1, height, m).get();
    space.setName("Space " + std::to_string(i + 1));
    space.setXOrigin(width * i);
    space.setSpaceType(spaceType);
    space.setThermalZone(z);
    spaces.emplace_back(std::move(space));
  }

  return {m, spaces};
}

// Concepts to constrain template types
template <typename T>
concept IsSpaceLoadInstance = std::derived_from<T, SpaceLoadInstance>;

template <typename T>
concept IsSpaceLoadDefinition = std::derived_from<T, SpaceLoadDefinition>;

// const double getters member function pointer types
using SpaceDoubleGetter = double (Space::*)() const;
using ThermalZoneDoubleGetter = double (ThermalZone::*)() const;
using BuildingDoubleGetter = double (Building::*)() const;

template <IsSpaceLoadInstance Equipment, IsSpaceLoadDefinition EquipmentDefinition, SpaceDoubleGetter spacePowerGetter,
          SpaceDoubleGetter spacePowerPerFloorAreaGetter, SpaceDoubleGetter spacePowerPerPersonGetter, ThermalZoneDoubleGetter zonePowerGetter,
          ThermalZoneDoubleGetter zonePowerPerFloorAreaGetter, ThermalZoneDoubleGetter zonePowerPerPersonGetter,
          BuildingDoubleGetter buildingPowerGetter, BuildingDoubleGetter buildingPowerPerFloorAreaGetter,
          BuildingDoubleGetter buildingPowerPerPersonGetter>
void prepareModel() {
  auto [m, spaces] = prepareModelWith4Spaces();
  auto& space1 = spaces.front();
  auto zone = space1.thermalZone().get();
  auto spaceType = space1.spaceType().get();
  Building building = m.getUniqueModelObject<Building>();
  EXPECT_DOUBLE_EQ(400.0, building.floorArea());
  EXPECT_DOUBLE_EQ(20.0, building.numberOfPeople());

  // Add a SpaceType equipment with 10W/m2, which is 1000W per space
  EquipmentDefinition sp_def(m);
  static_assert(
    requires(EquipmentDefinition d) {
      { d.setWattsperSpaceFloorArea(0.0) } -> std::same_as<bool>;
    }, "EquipmentDefinition must have setWattsperSpaceFloorArea(double)");
  sp_def.setWattsperSpaceFloorArea(10.0);  // 10W/m2
  Equipment sp_e(sp_def);
  sp_e.setName("Space Type Equipment 10W/m2");
  sp_e.setSpaceType(spaceType);

  // In Space 1, add an equipment with 1000W, which is also 10W/m2

  EquipmentDefinition space_def(m);
  if constexpr (std::is_same_v<Equipment, Lights>) {
    // Compile only when Equipment is Lights
    space_def.setLightingLevel(1000.0);
  } else {
    static_assert(
      requires(EquipmentDefinition d) {
        { d.setDesignLevel(0.0) } -> std::same_as<bool>;
      }, "EquipmentDefinition must have setDesignLevel(double)");

    space_def.setDesignLevel(1000.0);
  }
  Equipment space_e(space_def);
  space_e.setName("Space 1 Equipment 1000W");
  space_e.setSpace(space1);

  // Check Absolute values
  EXPECT_DOUBLE_EQ(2000.0, (space1.*spacePowerGetter)());
  for (auto& space : spaces | std::views::drop(1)) {
    EXPECT_DOUBLE_EQ(1000.0, (space.*spacePowerGetter)());
  }
  EXPECT_DOUBLE_EQ(5000.0, (zone.*zonePowerGetter)());
  EXPECT_DOUBLE_EQ(5000.0, (building.*buildingPowerGetter)());

  // Check per floor area values
  EXPECT_DOUBLE_EQ(20.0, (space1.*spacePowerPerFloorAreaGetter)());
  for (auto& space : spaces | std::views::drop(1)) {
    EXPECT_DOUBLE_EQ(10.0, (space.*spacePowerPerFloorAreaGetter)());
  }
  EXPECT_DOUBLE_EQ(12.5, (zone.*zonePowerPerFloorAreaGetter)());
  EXPECT_DOUBLE_EQ(12.5, (building.*buildingPowerPerFloorAreaGetter)());

  // Check per person values
  EXPECT_DOUBLE_EQ(400.0, (space1.*spacePowerPerPersonGetter)());
  for (auto& space : spaces | std::views::drop(1)) {
    EXPECT_DOUBLE_EQ(200.0, (space.*spacePowerPerPersonGetter)());
  }
  EXPECT_DOUBLE_EQ(250.0, (zone.*zonePowerPerPersonGetter)());
  EXPECT_DOUBLE_EQ(250.0, (building.*buildingPowerPerPersonGetter)());
}

template <typename Eq, typename Def, SpaceDoubleGetter sg, SpaceDoubleGetter sgFA, SpaceDoubleGetter sgPP, ThermalZoneDoubleGetter zg,
          ThermalZoneDoubleGetter zgFA, ThermalZoneDoubleGetter zgPP, BuildingDoubleGetter bg, BuildingDoubleGetter bgFA, BuildingDoubleGetter bgPP>
struct EquipmentTraits
{
  using Equipment = Eq;
  using Definition = Def;
  static constexpr auto spaceGetter = sg;
  static constexpr auto spaceGetterFA = sgFA;
  static constexpr auto spaceGetterPP = sgPP;
  static constexpr auto zoneGetter = zg;
  static constexpr auto zoneGetterFA = zgFA;
  static constexpr auto zoneGetterPP = zgPP;
  static constexpr auto buildingGetter = bg;
  static constexpr auto buildingGetterFA = bgFA;
  static constexpr auto buildingGetterPP = bgPP;
};

using LightsTraits =
  EquipmentTraits<Lights, LightsDefinition, &Space::lightingPower, &Space::lightingPowerPerFloorArea, &Space::lightingPowerPerPerson,
                  &ThermalZone::lightingPower, &ThermalZone::lightingPowerPerFloorArea, &ThermalZone::lightingPowerPerPerson,
                  &Building::lightingPower, &Building::lightingPowerPerFloorArea, &Building::lightingPowerPerPerson>;

using HotWaterEquipmentTraits =
  EquipmentTraits<HotWaterEquipment, HotWaterEquipmentDefinition, &Space::hotWaterEquipmentPower, &Space::hotWaterEquipmentPowerPerFloorArea,
                  &Space::hotWaterEquipmentPowerPerPerson, &ThermalZone::hotWaterEquipmentPower, &ThermalZone::hotWaterEquipmentPowerPerFloorArea,
                  &ThermalZone::hotWaterEquipmentPowerPerPerson, &Building::hotWaterEquipmentPower, &Building::hotWaterEquipmentPowerPerFloorArea,
                  &Building::hotWaterEquipmentPowerPerPerson>;

using GasEquipmentTraits =
  EquipmentTraits<GasEquipment, GasEquipmentDefinition, &Space::gasEquipmentPower, &Space::gasEquipmentPowerPerFloorArea,
                  &Space::gasEquipmentPowerPerPerson, &ThermalZone::gasEquipmentPower, &ThermalZone::gasEquipmentPowerPerFloorArea,
                  &ThermalZone::gasEquipmentPowerPerPerson, &Building::gasEquipmentPower, &Building::gasEquipmentPowerPerFloorArea,
                  &Building::gasEquipmentPowerPerPerson>;

using ElectricEquipmentTraits =
  EquipmentTraits<ElectricEquipment, ElectricEquipmentDefinition, &Space::electricEquipmentPower, &Space::electricEquipmentPowerPerFloorArea,
                  &Space::electricEquipmentPowerPerPerson, &ThermalZone::electricEquipmentPower, &ThermalZone::electricEquipmentPowerPerFloorArea,
                  &ThermalZone::electricEquipmentPowerPerPerson, &Building::electricEquipmentPower, &Building::electricEquipmentPowerPerFloorArea,
                  &Building::electricEquipmentPowerPerPerson>;

template <class Traits>
class ConvenienceTest : public ModelFixture
{
};

TYPED_TEST_SUITE_P(ConvenienceTest);

TYPED_TEST_P(ConvenienceTest, Test) {
  using Traits = TypeParam;
  prepareModel<typename Traits::Equipment, typename Traits::Definition, Traits::spaceGetter, Traits::spaceGetterFA, Traits::spaceGetterPP,
               Traits::zoneGetter, Traits::zoneGetterFA, Traits::zoneGetterPP, Traits::buildingGetter, Traits::buildingGetterFA,
               Traits::buildingGetterPP>();
}

REGISTER_TYPED_TEST_SUITE_P(ConvenienceTest, Test);

using AllEquipmentTraitsTypes = ::testing::Types<LightsTraits, HotWaterEquipmentTraits, GasEquipmentTraits, ElectricEquipmentTraits>;

class EquipmentNameGenerator
{
 public:
  template <typename T>
  static std::string GetName(int /*unused*/) {
    if constexpr (std::is_same_v<typename T::Equipment, Lights>) {
      return "Lights";
    } else if constexpr (std::is_same_v<typename T::Equipment, HotWaterEquipment>) {
      return "HotWaterEquipment";
    } else if constexpr (std::is_same_v<typename T::Equipment, ElectricEquipment>) {
      return "ElectricEquipment";
    } else if constexpr (std::is_same_v<typename T::Equipment, GasEquipment>) {
      return "GasEquipment";
    } else {
      return "Unknown";
    }
  }
};

INSTANTIATE_TYPED_TEST_SUITE_P(SpaceLoad, ConvenienceTest, AllEquipmentTraitsTypes, EquipmentNameGenerator);
