/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_IMPL_HPP
#define EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API HVACTemplateZoneBaseboardHeat_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~HVACTemplateZoneBaseboardHeat_Impl() override = default;

  boost::optional<double> zoneHeatingSizingFactor() const;
  std::string baseboardHeatingType() const;
  boost::optional<double> baseboardHeatingCapacity() const;
  std::string outdoorAirMethod() const;
  double outdoorAirFlowRateperPerson() const;
  double outdoorAirFlowRateperZoneFloorArea() const;
  double outdoorAirFlowRateperZone() const;

  bool isBaseboardHeatingTypeDefaulted() const;
  bool isBaseboardHeatingCapacityDefaulted() const;
  bool isBaseboardHeatingCapacityAutosized() const;
  bool isOutdoorAirMethodDefaulted() const;
  bool isOutdoorAirFlowRateperPersonDefaulted() const;
  bool isOutdoorAirFlowRateperZoneFloorAreaDefaulted() const;
  bool isOutdoorAirFlowRateperZoneDefaulted() const;

  bool setZoneHeatingSizingFactor(double zoneHeatingSizingFactor);
  bool setBaseboardHeatingType(const std::string& baseboardHeatingType);
  bool setBaseboardHeatingCapacity(double baseboardHeatingCapacity);
  bool setOutdoorAirMethod(const std::string& outdoorAirMethod);
  bool setOutdoorAirFlowRateperPerson(double outdoorAirFlowRateperPerson);
  bool setOutdoorAirFlowRateperZoneFloorArea(double outdoorAirFlowRateperZoneFloorArea);
  bool setOutdoorAirFlowRateperZone(double outdoorAirFlowRateperZone);

  void resetZoneHeatingSizingFactor();
  void resetBaseboardHeatingType();
  void resetBaseboardHeatingCapacity();
  void autosizeBaseboardHeatingCapacity();
  void resetOutdoorAirMethod();
  void resetOutdoorAirFlowRateperPerson();
  void resetOutdoorAirFlowRateperZoneFloorArea();
  void resetOutdoorAirFlowRateperZone();

  std::vector<std::string> baseboardHeatingTypeValues() const;
  std::vector<std::string> outdoorAirMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
