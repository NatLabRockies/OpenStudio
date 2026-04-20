/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ROOMAIRSETTINGSTHREENODEDISPLACEMENTVENTILATION_IMPL_HPP
#define EPMODEL_ROOMAIRSETTINGSTHREENODEDISPLACEMENTVENTILATION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
namespace detail {

class EPMODEL_API RoomAirSettingsThreeNodeDisplacementVentilation_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~RoomAirSettingsThreeNodeDisplacementVentilation_Impl() override = default;

  double numberofPlumesperOccupant() const;
  bool isNumberofPlumesperOccupantDefaulted() const;
  bool setNumberofPlumesperOccupant(double numberofPlumesperOccupant);
  void resetNumberofPlumesperOccupant();

  double thermostatHeight() const;
  bool isThermostatHeightDefaulted() const;
  bool setThermostatHeight(double thermostatHeight);
  void resetThermostatHeight();

  double comfortHeight() const;
  bool isComfortHeightDefaulted() const;
  bool setComfortHeight(double comfortHeight);
  void resetComfortHeight();

  double temperatureDifferenceThresholdforReporting() const;
  bool isTemperatureDifferenceThresholdforReportingDefaulted() const;
  bool setTemperatureDifferenceThresholdforReporting(double temperatureDifferenceThresholdforReporting);
  void resetTemperatureDifferenceThresholdforReporting();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
