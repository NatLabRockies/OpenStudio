/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_HPP
#define EPMODEL_HVACTEMPLATEZONEBASEBOARDHEAT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class HVACTemplateZoneBaseboardHeat_Impl;
}

class EPMODEL_API HVACTemplateZoneBaseboardHeat : public ModelObject
{
 public:
  explicit HVACTemplateZoneBaseboardHeat(const Model& model);

  virtual ~HVACTemplateZoneBaseboardHeat() override = default;
  HVACTemplateZoneBaseboardHeat(const HVACTemplateZoneBaseboardHeat& other) = default;
  HVACTemplateZoneBaseboardHeat(HVACTemplateZoneBaseboardHeat&& other) = default;
  HVACTemplateZoneBaseboardHeat& operator=(const HVACTemplateZoneBaseboardHeat&) = default;
  HVACTemplateZoneBaseboardHeat& operator=(HVACTemplateZoneBaseboardHeat&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> baseboardHeatingTypeValues();
  static std::vector<std::string> outdoorAirMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to HVACTemplate:Zone:BaseboardHeat non-name scalar fields.
  // - Field Mapping: Zone/Thermostat/Schedule/DOAS/DesignSpecification name fields are object-list
  //   relationship fields and are intentionally excluded from scalar-only scaffold.
  // - TODO(parity): Revisit only if a future parity pass introduces relationship/object-link APIs.
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

 protected:
  using ImplType = detail::HVACTemplateZoneBaseboardHeat_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit HVACTemplateZoneBaseboardHeat(std::shared_ptr<detail::HVACTemplateZoneBaseboardHeat_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
