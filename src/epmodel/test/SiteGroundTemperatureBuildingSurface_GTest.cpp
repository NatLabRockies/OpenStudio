/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <array>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundTemperatureBuildingSurface.hpp"
#include "../ModelObject/SiteGroundTemperatureBuildingSurface_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundTemperatureBuildingSurface_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundTemperatureBuildingSurface>();

  EXPECT_EQ(SiteGroundTemperatureBuildingSurface::iddObjectType(), object.iddObject().type());
  EXPECT_TRUE(object.isJanuaryGroundTemperatureDefaulted());
  EXPECT_DOUBLE_EQ(18.0, object.januaryGroundTemperature());
}

struct MonthAccessor
{
  const char* name;
  double (SiteGroundTemperatureBuildingSurface::*getter)() const;
  bool (SiteGroundTemperatureBuildingSurface::*isDefaulted)() const;
  bool (SiteGroundTemperatureBuildingSurface::*setter)(double);
  void (SiteGroundTemperatureBuildingSurface::*reset)();
};

TEST_F(EPModelFixture, SiteGroundTemperatureBuildingSurface_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundTemperatureBuildingSurface>();

  constexpr double defaultValue = 18.0;
  constexpr double updatedValue = 23.0;

  constexpr std::array<MonthAccessor, 12> months{
    MonthAccessor{.name = "January",
                  .getter = &SiteGroundTemperatureBuildingSurface::januaryGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isJanuaryGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setJanuaryGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetJanuaryGroundTemperature},
    MonthAccessor{.name = "February",
                  .getter = &SiteGroundTemperatureBuildingSurface::februaryGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isFebruaryGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setFebruaryGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetFebruaryGroundTemperature},
    MonthAccessor{.name = "March",
                  .getter = &SiteGroundTemperatureBuildingSurface::marchGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isMarchGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setMarchGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetMarchGroundTemperature},
    MonthAccessor{.name = "April",
                  .getter = &SiteGroundTemperatureBuildingSurface::aprilGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isAprilGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setAprilGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetAprilGroundTemperature},
    MonthAccessor{.name = "May",
                  .getter = &SiteGroundTemperatureBuildingSurface::mayGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isMayGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setMayGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetMayGroundTemperature},
    MonthAccessor{.name = "June",
                  .getter = &SiteGroundTemperatureBuildingSurface::juneGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isJuneGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setJuneGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetJuneGroundTemperature},
    MonthAccessor{.name = "July",
                  .getter = &SiteGroundTemperatureBuildingSurface::julyGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isJulyGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setJulyGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetJulyGroundTemperature},
    MonthAccessor{.name = "August",
                  .getter = &SiteGroundTemperatureBuildingSurface::augustGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isAugustGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setAugustGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetAugustGroundTemperature},
    MonthAccessor{.name = "September",
                  .getter = &SiteGroundTemperatureBuildingSurface::septemberGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isSeptemberGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setSeptemberGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetSeptemberGroundTemperature},
    MonthAccessor{.name = "October",
                  .getter = &SiteGroundTemperatureBuildingSurface::octoberGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isOctoberGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setOctoberGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetOctoberGroundTemperature},
    MonthAccessor{.name = "November",
                  .getter = &SiteGroundTemperatureBuildingSurface::novemberGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isNovemberGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setNovemberGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetNovemberGroundTemperature},
    MonthAccessor{.name = "December",
                  .getter = &SiteGroundTemperatureBuildingSurface::decemberGroundTemperature,
                  .isDefaulted = &SiteGroundTemperatureBuildingSurface::isDecemberGroundTemperatureDefaulted,
                  .setter = &SiteGroundTemperatureBuildingSurface::setDecemberGroundTemperature,
                  .reset = &SiteGroundTemperatureBuildingSurface::resetDecemberGroundTemperature},
  };

  for (const auto& month : months) {
    SCOPED_TRACE(month.name);
    EXPECT_TRUE((object.*month.isDefaulted)());
    EXPECT_DOUBLE_EQ(defaultValue, (object.*month.getter)());
    EXPECT_TRUE((object.*month.setter)(updatedValue));
    EXPECT_FALSE((object.*month.isDefaulted)());
    EXPECT_DOUBLE_EQ(updatedValue, (object.*month.getter)());
    (object.*month.reset)();
    EXPECT_TRUE((object.*month.isDefaulted)());
    EXPECT_DOUBLE_EQ(defaultValue, (object.*month.getter)());
  }
}
