/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_STEAMEQUIPMENT_HPP
#define EPMODEL_STEAMEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SteamEquipment_Impl;
  }

  class EPMODEL_API SteamEquipment : public ModelObject
  {
   public:
    explicit SteamEquipment(const Model& model);

    virtual ~SteamEquipment() override = default;
    SteamEquipment(const SteamEquipment& other) = default;
    SteamEquipment(SteamEquipment&& other) = default;
    SteamEquipment& operator=(const SteamEquipment&) = default;
    SteamEquipment& operator=(SteamEquipment&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designLevelCalculationMethodValues();

    // Schema Alignment Notes:
    // - IDD type: SteamEquipment (EnergyPlus 24.x)
    // - API: Preserve openstudio::model::SteamEquipment scalar API names/signatures where present.
    // - Field Mapping: designLevel/powerPerFloorArea/powerPerPerson map to E+ fields
    //     Design Level / Power per Floor Area / Power per Person via SteamEquipmentFields.
    // - Field Mapping: fractionLatent/fractionRadiant/fractionLost map to Fraction Latent/Radiant/Lost.
    // - Field Mapping: endUseSubcategory maps to End-Use Subcategory (default "General").
    // - Field Mapping: Zone or ZoneList or Space or SpaceList Name and Schedule Name are
    //     relationship fields (\object-list) and intentionally excluded from scalar accessors.
    // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods;
    //     no dedicated E+ multiplier field exists on SteamEquipment.
    // - ForwardTranslator evidence: ForwardTranslateSteamEquipment.cpp applies model multiplier
    //     directly to translated design-level scalar fields.
    // - TODO(parity): Add relationship APIs and richer definition-backed behavior without changing scalar signatures.
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
    using ImplType = detail::SteamEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SteamEquipment(std::shared_ptr<detail::SteamEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
