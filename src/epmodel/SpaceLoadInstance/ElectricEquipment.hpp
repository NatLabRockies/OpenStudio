/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICEQUIPMENT_HPP
#define EPMODEL_ELECTRICEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ElectricEquipment_Impl;
}

class EPMODEL_API ElectricEquipment : public ModelObject
{
 public:
  explicit ElectricEquipment(const Model& model);

  virtual ~ElectricEquipment() override = default;
  ElectricEquipment(const ElectricEquipment& other) = default;
  ElectricEquipment(ElectricEquipment&& other) = default;
  ElectricEquipment& operator=(const ElectricEquipment&) = default;
  ElectricEquipment& operator=(ElectricEquipment&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> designLevelCalculationMethodValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ElectricEquipment scalar API names/signatures where present.
  // - Field Mapping: powerPerFloorArea/powerPerPerson map to E+ fields Watts per Floor Area/Watts per Person.
  // - Field Mapping: schedule and zone/space target references are relationship fields and intentionally excluded.
  // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; no dedicated E+ multiplier field exists.
  // - ForwardTranslator evidence: ForwardTranslateElectricEquipment.cpp applies model multiplier directly to translated
  //   design-level scalar fields in ElectricEquipment.
  // - TODO(parity): Add relationship APIs and richer design-level compatibility behavior without changing scalar signatures.
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

 protected:
  using ImplType = detail::ElectricEquipment_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ElectricEquipment(std::shared_ptr<detail::ElectricEquipment_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
