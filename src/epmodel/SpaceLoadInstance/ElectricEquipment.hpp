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

  /** \brief Represents the EnergyPlus ElectricEquipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-internal-gains-people-lights-other.html#electricequipment,ElectricEquipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ElectricEquipment</code>. <b>Not yet available:</b> the Model definition, schedule, and zone/space relationship methods. EPModel exposes direct EnergyPlus design-level and fraction fields plus compatibility multiplier methods.
   *
   * \par Known limitations
   * The compatibility multiplier scales the stored design-level fields because EnergyPlus has no dedicated multiplier field.
   */
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
