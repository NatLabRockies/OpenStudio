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

  /** \brief Represents the EnergyPlus Exterior:FuelEquipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-exterior-energy-use-equipment.html#exteriorfuelequipment,Exterior:FuelEquipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ExteriorFuelEquipment</code>. <b>Not yet available:</b> the Model definition, schedule, and facility relationship methods. EPModel exposes the scalar fuel, end-use, and multiplier surface.
   *
   * \par Known limitations
   * EPModel stores the compatibility multiplier in the EnergyPlus Design Level field; EnergyPlus has no separate multiplier field.
   */
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


    std::string fuelType() const;
    bool setFuelType(const FuelType& fuelType);
    bool setFuelType(const std::string& fuelType);

    double multiplier() const;
    bool isMultiplierDefaulted() const;
    bool setMultiplier(double multiplier);
    void resetMultiplier();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
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
