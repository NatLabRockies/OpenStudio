/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_EXTERIORWATEREQUIPMENT_HPP
#define EPMODEL_EXTERIORWATEREQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject/ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class ExteriorWaterEquipment_Impl;
}

class EPMODEL_API ExteriorWaterEquipment : public ModelObject
{
 public:
  explicit ExteriorWaterEquipment(const Model& model);

  virtual ~ExteriorWaterEquipment() override = default;
  ExteriorWaterEquipment(const ExteriorWaterEquipment& other) = default;
  ExteriorWaterEquipment(ExteriorWaterEquipment&& other) = default;
  ExteriorWaterEquipment& operator=(const ExteriorWaterEquipment&) = default;
  ExteriorWaterEquipment& operator=(ExteriorWaterEquipment&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserve openstudio::model::ExteriorWaterEquipment scalar accessor names/signatures.
  // - Field Mapping: multiplier API maps to E+ Exterior:WaterEquipment Design Level.
  // - Field Mapping: endUseSubcategory maps directly to E+ End-Use Subcategory.
  // - Field Mapping: Fuel Use Type is translator-fixed to "Water"; no corresponding scalar model API.
  // - Field Mapping: relationship fields (Schedule Name and related definition/facility graph) are excluded.
  // - ForwardTranslator evidence: ForwardTranslateExteriorWaterEquipment.cpp writes DesignLevel from
  //   definition.designLevel() * modelObject.multiplier(), writes FuelUseType="Water", and writes EndUseSubcategory directly.
  // - TODO(parity): Add excluded relationship APIs without changing preserved scalar signatures.
  double multiplier() const;
  bool isMultiplierDefaulted() const;

  std::string endUseSubcategory() const;
  bool isEndUseSubcategoryDefaulted() const;

  bool setMultiplier(double multiplier);
  void resetMultiplier();

  bool setEndUseSubcategory(const std::string& endUseSubcategory);
  void resetEndUseSubcategory();

 protected:
  using ImplType = detail::ExteriorWaterEquipment_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit ExteriorWaterEquipment(std::shared_ptr<detail::ExteriorWaterEquipment_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
