/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_HOTWATEREQUIPMENT_HPP
#define EPMODEL_HOTWATEREQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class HotWaterEquipment_Impl;
  }

  class EPMODEL_API HotWaterEquipment : public ModelObject
  {
   public:
    explicit HotWaterEquipment(const Model& model);

    virtual ~HotWaterEquipment() override = default;
    HotWaterEquipment(const HotWaterEquipment& other) = default;
    HotWaterEquipment(HotWaterEquipment&& other) = default;
    HotWaterEquipment& operator=(const HotWaterEquipment&) = default;
    HotWaterEquipment& operator=(HotWaterEquipment&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designLevelCalculationMethodValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::HotWaterEquipment scalar API names/signatures where present.
    // - Field Mapping: designLevel/powerPerFloorArea/powerPerPerson map to E+ fields Design Level/Power per Floor Area/Power per Person.
    // - Field Mapping: schedule and zone/space target references are relationship fields and intentionally excluded.
    // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; no dedicated E+ multiplier field exists.
    // - ForwardTranslator evidence: ForwardTranslateHotWaterEquipment.cpp applies model multiplier directly to translated
    //   design-level scalar fields in HotWaterEquipment.
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
    using ImplType = detail::HotWaterEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit HotWaterEquipment(std::shared_ptr<detail::HotWaterEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
