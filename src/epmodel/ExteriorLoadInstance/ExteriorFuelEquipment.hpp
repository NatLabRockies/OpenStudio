/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORFUELEQUIPMENT_HPP
#define EPMODEL_EXTERIORFUELEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {

class FuelType;

namespace epmodel {

class Model;

namespace detail {
class ExteriorFuelEquipment_Impl;
}

class EPMODEL_API ExteriorFuelEquipment : public ModelObject
{
 public:
  explicit ExteriorFuelEquipment(const Model& model);

  virtual ~ExteriorFuelEquipment() override = default;
  ExteriorFuelEquipment(const ExteriorFuelEquipment& other) = default;
  ExteriorFuelEquipment(ExteriorFuelEquipment&& other) = default;
  ExteriorFuelEquipment& operator=(const ExteriorFuelEquipment&) = default;
  ExteriorFuelEquipment& operator=(ExteriorFuelEquipment&&) = default;

  static IddObjectType iddObjectType();

  static std::vector<std::string> fuelTypeValues();
  static std::vector<std::string> validFuelTypeValues();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExteriorFuelEquipment scalar accessor names/signatures.
  // - Field Mapping: multiplier API maps to E+ Exterior:FuelEquipment Design Level.
  // - Field Mapping: fuelType/endUseSubcategory map to E+ Fuel Use Type/End-Use Subcategory.
  // - Field Mapping: relationship fields (Schedule Name and related definition/facility graph) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateExteriorFuelEquipment.cpp writes DesignLevel from
  //   definition.designLevel() * modelObject.multiplier(), and writes FuelUseType/EndUseSubcategory directly.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  std::string fuelType() const;

  double multiplier() const;
  bool isMultiplierDefaulted() const;

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;

  bool setFuelType(const FuelType& fuelType);
  bool setFuelType(const std::string& fuelType);

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

 protected:
  using ImplType = detail::ExteriorFuelEquipment_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExteriorFuelEquipment(std::shared_ptr<detail::ExteriorFuelEquipment_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
