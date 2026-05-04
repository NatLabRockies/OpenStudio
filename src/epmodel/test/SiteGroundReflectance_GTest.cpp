/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#include <gtest/gtest.h>

#include <array>

#include "EPModelFixture.hpp"
#include "../ModelObject/SiteGroundReflectance.hpp"
#include "../ModelObject/SiteGroundReflectance_Impl.hpp"

using namespace openstudio::epmodel;

TEST_F(EPModelFixture, SiteGroundReflectance_DefaultConstructor) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundReflectance>();

  EXPECT_EQ(SiteGroundReflectance::iddObjectType(), object.iddObject().type());
  EXPECT_TRUE(object.isJanuaryGroundReflectanceDefaulted());
  EXPECT_DOUBLE_EQ(0.2, object.januaryGroundReflectance());
}

struct MonthAccessor
{
  const char* name;
  double (SiteGroundReflectance::*getter)() const;
  bool (SiteGroundReflectance::*isDefaulted)() const;
  bool (SiteGroundReflectance::*setter)(double);
  void (SiteGroundReflectance::*reset)();
};

TEST_F(EPModelFixture, SiteGroundReflectance_ScalarAccessors_RoundTrip) {
  Model model;
  auto object = model.getUniqueModelObject<SiteGroundReflectance>();

  constexpr double defaultValue = 0.2;
  constexpr double updatedValue = 0.13;

  constexpr std::array<MonthAccessor, 12> months{
    MonthAccessor{.name = "January",
                  .getter = &SiteGroundReflectance::januaryGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isJanuaryGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setJanuaryGroundReflectance,
                  .reset = &SiteGroundReflectance::resetJanuaryGroundReflectance},
    MonthAccessor{.name = "February",
                  .getter = &SiteGroundReflectance::februaryGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isFebruaryGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setFebruaryGroundReflectance,
                  .reset = &SiteGroundReflectance::resetFebruaryGroundReflectance},
    MonthAccessor{.name = "March",
                  .getter = &SiteGroundReflectance::marchGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isMarchGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setMarchGroundReflectance,
                  .reset = &SiteGroundReflectance::resetMarchGroundReflectance},
    MonthAccessor{.name = "April",
                  .getter = &SiteGroundReflectance::aprilGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isAprilGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setAprilGroundReflectance,
                  .reset = &SiteGroundReflectance::resetAprilGroundReflectance},
    MonthAccessor{.name = "May",
                  .getter = &SiteGroundReflectance::mayGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isMayGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setMayGroundReflectance,
                  .reset = &SiteGroundReflectance::resetMayGroundReflectance},
    MonthAccessor{.name = "June",
                  .getter = &SiteGroundReflectance::juneGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isJuneGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setJuneGroundReflectance,
                  .reset = &SiteGroundReflectance::resetJuneGroundReflectance},
    MonthAccessor{.name = "July",
                  .getter = &SiteGroundReflectance::julyGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isJulyGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setJulyGroundReflectance,
                  .reset = &SiteGroundReflectance::resetJulyGroundReflectance},
    MonthAccessor{.name = "August",
                  .getter = &SiteGroundReflectance::augustGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isAugustGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setAugustGroundReflectance,
                  .reset = &SiteGroundReflectance::resetAugustGroundReflectance},
    MonthAccessor{.name = "September",
                  .getter = &SiteGroundReflectance::septemberGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isSeptemberGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setSeptemberGroundReflectance,
                  .reset = &SiteGroundReflectance::resetSeptemberGroundReflectance},
    MonthAccessor{.name = "October",
                  .getter = &SiteGroundReflectance::octoberGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isOctoberGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setOctoberGroundReflectance,
                  .reset = &SiteGroundReflectance::resetOctoberGroundReflectance},
    MonthAccessor{.name = "November",
                  .getter = &SiteGroundReflectance::novemberGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isNovemberGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setNovemberGroundReflectance,
                  .reset = &SiteGroundReflectance::resetNovemberGroundReflectance},
    MonthAccessor{.name = "December",
                  .getter = &SiteGroundReflectance::decemberGroundReflectance,
                  .isDefaulted = &SiteGroundReflectance::isDecemberGroundReflectanceDefaulted,
                  .setter = &SiteGroundReflectance::setDecemberGroundReflectance,
                  .reset = &SiteGroundReflectance::resetDecemberGroundReflectance},
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
