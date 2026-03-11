/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORFUELEQUIPMENT_IMPL_HPP
#define EPMODEL_EXTERIORFUELEQUIPMENT_IMPL_HPP

#include "ModelObject/ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ExteriorFuelEquipment_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ExteriorFuelEquipment_Impl() override = default;

  std::string fuelType() const;

  double multiplier() const;
  bool isMultiplierDefaulted() const;

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;

  bool setFuelType(const std::string& fuelType);

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  std::vector<std::string> fuelTypeValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
