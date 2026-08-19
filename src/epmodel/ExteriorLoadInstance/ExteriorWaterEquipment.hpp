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

  /** \brief Represents the EnergyPlus Exterior:WaterEquipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-exterior-energy-use-equipment.html#exteriorwaterequipment,Exterior:WaterEquipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExteriorWaterEquipment</code>. <b>Not yet available:</b> the Model definition, schedule, and facility relationship methods. EPModel exposes end-use subcategory and multiplier. EnergyPlus Fuel Use Type is fixed to <code>Water</code>.
   *
   * \par Known limitations
   * EPModel stores the compatibility multiplier in the EnergyPlus Design Level field; EnergyPlus has no separate multiplier field.
   */
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

    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
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
