/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SPACEHVACZONEEQUIPMENTSPLITTER_IMPL_HPP
#define EPMODEL_SPACEHVACZONEEQUIPMENTSPLITTER_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API SpaceHVACZoneEquipmentSplitter_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~SpaceHVACZoneEquipmentSplitter_Impl() override = default;

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

  std::vector<std::string> zoneEquipmentObjectTypeValues() const;
  std::vector<std::string> thermostatControlMethodValues() const;
  std::vector<std::string> spaceFractionMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
