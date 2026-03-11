/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEHVACZONEEQUIPMENTSPLITTER_HPP
#define EPMODEL_SPACEHVACZONEEQUIPMENTSPLITTER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SpaceHVACZoneEquipmentSplitter_Impl;
}

class EPMODEL_API SpaceHVACZoneEquipmentSplitter : public ModelObject
{
 public:
  explicit SpaceHVACZoneEquipmentSplitter(const Model& model);

  virtual ~SpaceHVACZoneEquipmentSplitter() override = default;
  SpaceHVACZoneEquipmentSplitter(const SpaceHVACZoneEquipmentSplitter& other) = default;
  SpaceHVACZoneEquipmentSplitter(SpaceHVACZoneEquipmentSplitter&& other) = default;
  SpaceHVACZoneEquipmentSplitter& operator=(const SpaceHVACZoneEquipmentSplitter&) = default;
  SpaceHVACZoneEquipmentSplitter& operator=(SpaceHVACZoneEquipmentSplitter&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> zoneEquipmentObjectTypeValues();
  static std::vector<std::string> thermostatControlMethodValues();
  static std::vector<std::string> spaceFractionMethodValues();

  // Schema Alignment Notes:
  // - API: This no-counterpart type keeps IDD-derived class/API naming.
  // - Field Mapping: zoneEquipmentObjectType, thermostatControlMethod, and spaceFractionMethod map directly to
  //   non-extensible EnergyPlus SpaceHVAC:ZoneEquipmentSplitter scalar fields.
  // - Field Mapping: Zone Name, Zone Equipment Name, Zone Equipment Outlet Node Name, Control Space Name, and
  //   extensible Space Name / Space Fraction / Space Supply Node Name groups are relationship-like links and excluded
  //   from scalar accessor generation in this pass.
  // - TODO(parity): Add relationship/non-scalar extensible helper APIs incrementally after scalar saturation.
  std::string zoneEquipmentObjectType() const;
  bool setZoneEquipmentObjectType(const std::string& zoneEquipmentObjectType);

  std::string thermostatControlMethod() const;
  bool isThermostatControlMethodDefaulted() const;
  bool setThermostatControlMethod(const std::string& thermostatControlMethod);
  void resetThermostatControlMethod();

  std::string spaceFractionMethod() const;
  bool isSpaceFractionMethodDefaulted() const;
  bool setSpaceFractionMethod(const std::string& spaceFractionMethod);
  void resetSpaceFractionMethod();

 protected:
  using ImplType = detail::SpaceHVACZoneEquipmentSplitter_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SpaceHVACZoneEquipmentSplitter(std::shared_ptr<detail::SpaceHVACZoneEquipmentSplitter_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
