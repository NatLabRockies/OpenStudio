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

  /** \brief Represents the EnergyPlus SteamEquipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-internal-gains-people-lights-other.html#steamequipment,SteamEquipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SteamEquipment</code>. <b>Not yet available:</b> the Model definition, schedule, and zone/space relationship methods. EPModel exposes direct design-level and fraction fields plus compatibility multiplier methods.
   *
   * \par Known limitations
   * The compatibility multiplier scales the stored design-level fields because EnergyPlus has no dedicated multiplier field.
   */
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
