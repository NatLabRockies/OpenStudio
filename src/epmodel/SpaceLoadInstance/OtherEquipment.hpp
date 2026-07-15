/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_OTHEREQUIPMENT_HPP
#define EPMODEL_OTHEREQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {

class FuelType;

namespace epmodel {

  class Model;

  namespace detail {
    class OtherEquipment_Impl;
  }

  class EPMODEL_API OtherEquipment : public ModelObject
  {
   public:
    explicit OtherEquipment(const Model& model);

    virtual ~OtherEquipment() override = default;
    OtherEquipment(const OtherEquipment& other) = default;
    OtherEquipment(OtherEquipment&& other) = default;
    OtherEquipment& operator=(const OtherEquipment&) = default;
    OtherEquipment& operator=(OtherEquipment&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> designLevelCalculationMethodValues();
    static std::vector<std::string> fuelTypeValues();
    static std::vector<std::string> validFuelTypeValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::OtherEquipment scalar API names/signatures where present.
    // - Field Mapping: design-level scalars map to E+ OtherEquipment fields Design Level/Power per Floor Area/Power per Person.
    // - Field Mapping: schedule and zone/space target references are relationship fields and intentionally excluded.
    // - Field Mapping: setMultiplier/resetMultiplier are preserved compatibility methods; no dedicated E+ multiplier field exists.
    // - Field Mapping: fuelType/setFuelType map to E+ Fuel Type; string overload preserves model special-case acceptance of "None".
    // - ForwardTranslator evidence: ForwardTranslateOtherEquipment.cpp writes definition design-level scalars times multiplier and
    //   writes fuel type/end use subcategory directly to OtherEquipment.
    // - TODO(parity): Add relationship and definition-backed APIs without changing preserved scalar signatures.
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

    std::string fuelType() const;
    bool isFuelTypeDefaulted() const;
    bool setFuelType(const FuelType& fuelType);
    bool setFuelType(const std::string& fuelType);
    void resetFuelType();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    bool setMultiplier(double multiplier);
    void resetMultiplier();

   protected:
    using ImplType = detail::OtherEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit OtherEquipment(std::shared_ptr<detail::OtherEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
