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

  /** \brief Represents the EnergyPlus ElectricEquipment:ITE:AirCooled object.
   *
   * \par EnergyPlus object
   * \epobject{group-internal-gains-people-lights-other.html#electricequipmentiteaircooled,ElectricEquipment:ITE:AirCooled}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ElectricEquipmentITEAirCooled</code>. <b>Not yet available:</b> the Model definition, schedule, and object relationship methods. EPModel exposes the EnergyPlus ITE scalar fields and compatibility multiplier.
   *
   * \par Known limitations
   * The compatibility multiplier scales the stored design-power fields because EnergyPlus has no dedicated multiplier field.
   */
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
