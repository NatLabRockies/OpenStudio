/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICEQUIPMENT_IMPL_HPP
#define EPMODEL_ELECTRICEQUIPMENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API ElectricEquipment_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~ElectricEquipment_Impl() override = default;

  std::string designLevelCalculationMethod() const;
  bool isDesignLevelCalculationMethodDefaulted() const;
  bool setDesignLevelCalculationMethod(const std::string& designLevelCalculationMethod);
  void resetDesignLevelCalculationMethod();

  boost::optional<double> designLevel() const;
  bool setDesignLevel(double designLevel);
  void resetDesignLevel();

  boost::optional<double> powerPerFloorArea() const;
  bool setPowerPerFloorArea(double powerPerFloorArea);
  void resetPowerPerFloorArea();

  boost::optional<double> powerPerPerson() const;
  bool setPowerPerPerson(double powerPerPerson);
  void resetPowerPerPerson();

  double fractionLatent() const;
  bool isFractionLatentDefaulted() const;
  bool setFractionLatent(double fractionLatent);
  void resetFractionLatent();

  double fractionRadiant() const;
  bool isFractionRadiantDefaulted() const;
  bool setFractionRadiant(double fractionRadiant);
  void resetFractionRadiant();

  double fractionLost() const;
  bool isFractionLostDefaulted() const;
  bool setFractionLost(double fractionLost);
  void resetFractionLost();

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;
  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  std::vector<std::string> designLevelCalculationMethodValues() const;
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
