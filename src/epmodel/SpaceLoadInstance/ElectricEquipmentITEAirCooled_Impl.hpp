/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICEQUIPMENTITEAIRCOOLED_IMPL_HPP
#define EPMODEL_ELECTRICEQUIPMENTITEAIRCOOLED_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricEquipmentITEAirCooled_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricEquipmentITEAirCooled_Impl() override = default;

  std::string cPUEndUseSubcategory() const;
  bool isCPUEndUseSubcategoryDefaulted() const;
  bool setCPUEndUseSubcategory(const std::string& cPUEndUseSubcategory);
  void resetCPUEndUseSubcategory();

  std::string fanEndUseSubcategory() const;
  bool isFanEndUseSubcategoryDefaulted() const;
  bool setFanEndUseSubcategory(const std::string& fanEndUseSubcategory);
  void resetFanEndUseSubcategory();

  std::string electricPowerSupplyEndUseSubcategory() const;
  bool isElectricPowerSupplyEndUseSubcategoryDefaulted() const;
  bool setElectricPowerSupplyEndUseSubcategory(const std::string& electricPowerSupplyEndUseSubcategory);
  void resetElectricPowerSupplyEndUseSubcategory();

  bool setMultiplier(double multiplier);
  void resetMultiplier();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
