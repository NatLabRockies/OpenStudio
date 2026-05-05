/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ELECTRICEQUIPMENTITEAIRCOOLED_HPP
#define EPMODEL_ELECTRICEQUIPMENTITEAIRCOOLED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ElectricEquipmentITEAirCooled_Impl;
  }

  class EPMODEL_API ElectricEquipmentITEAirCooled : public ModelObject
  {
   public:
    explicit ElectricEquipmentITEAirCooled(const Model& model);

    virtual ~ElectricEquipmentITEAirCooled() override = default;
    ElectricEquipmentITEAirCooled(const ElectricEquipmentITEAirCooled& other) = default;
    ElectricEquipmentITEAirCooled(ElectricEquipmentITEAirCooled&& other) = default;
    ElectricEquipmentITEAirCooled& operator=(const ElectricEquipmentITEAirCooled&) = default;
    ElectricEquipmentITEAirCooled& operator=(ElectricEquipmentITEAirCooled&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::ElectricEquipmentITEAirCooled scalar accessor names/signatures.
    // - Field Mapping: cPUEndUseSubcategory/fanEndUseSubcategory/electricPowerSupplyEndUseSubcategory
    //   map directly to E+ ElectricEquipment:ITE:AirCooled A17/A18/A19 fields.
    // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; E+ has no dedicated
    //   multiplier field, so multiplier is applied to existing design-power scalar fields (Watts per Unit,
    //   Watts per Floor Area), matching ForwardTranslateElectricEquipmentITEAirCooled multiplier behavior.
    // - Field Mapping: schedule and object-reference fields are relationship fields and intentionally excluded.
    // - TODO(parity): Add relationship and definition-backed behavior without changing preserved scalar signatures.
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

   protected:
    using ImplType = detail::ElectricEquipmentITEAirCooled_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ElectricEquipmentITEAirCooled(std::shared_ptr<detail::ElectricEquipmentITEAirCooled_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
