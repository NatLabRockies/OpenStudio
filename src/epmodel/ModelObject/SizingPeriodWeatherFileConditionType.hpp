/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SIZINGPERIODWEATHERFILECONDITIONTYPE_HPP
#define EPMODEL_SIZINGPERIODWEATHERFILECONDITIONTYPE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SizingPeriodWeatherFileConditionType_Impl;
}

class EPMODEL_API SizingPeriodWeatherFileConditionType : public ModelObject
{
 public:
  explicit SizingPeriodWeatherFileConditionType(const Model& model);

  virtual ~SizingPeriodWeatherFileConditionType() override = default;
  SizingPeriodWeatherFileConditionType(const SizingPeriodWeatherFileConditionType& other) = default;
  SizingPeriodWeatherFileConditionType(SizingPeriodWeatherFileConditionType&& other) = default;
  SizingPeriodWeatherFileConditionType& operator=(const SizingPeriodWeatherFileConditionType&) = default;
  SizingPeriodWeatherFileConditionType& operator=(SizingPeriodWeatherFileConditionType&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> periodSelectionValues();
  static std::vector<std::string> dayofWeekforStartDayValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to E+ SizingPeriod:WeatherFileConditionType scalar fields.
  // - Field Mapping: Name remains available through base ModelObject scalar API.
  // - TODO(parity): Add any non-scalar/relationship API in a dedicated follow-up pass.
  std::string periodSelection() const;
  bool setPeriodSelection(const std::string& periodSelection);

  std::string dayofWeekforStartDay() const;
  bool setDayofWeekforStartDay(const std::string& dayofWeekforStartDay);
  bool isDayofWeekforStartDayDefaulted() const;
  void resetDayofWeekforStartDay();

  bool useWeatherFileDaylightSavingPeriod() const;
  bool setUseWeatherFileDaylightSavingPeriod(bool useWeatherFileDaylightSavingPeriod);
  bool isUseWeatherFileDaylightSavingPeriodDefaulted() const;
  void resetUseWeatherFileDaylightSavingPeriod();

  bool useWeatherFileRainandSnowIndicators() const;
  bool setUseWeatherFileRainandSnowIndicators(bool useWeatherFileRainandSnowIndicators);
  bool isUseWeatherFileRainandSnowIndicatorsDefaulted() const;
  void resetUseWeatherFileRainandSnowIndicators();

 protected:
  using ImplType = detail::SizingPeriodWeatherFileConditionType_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SizingPeriodWeatherFileConditionType(std::shared_ptr<detail::SizingPeriodWeatherFileConditionType_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
