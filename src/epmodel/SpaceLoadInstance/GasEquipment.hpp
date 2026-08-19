/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GASEQUIPMENT_HPP
#define EPMODEL_GASEQUIPMENT_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GasEquipment_Impl;
  }

  /** \brief Represents the EnergyPlus GasEquipment object.
   *
   * \par EnergyPlus object
   * \epobject{group-internal-gains-people-lights-other.html#gasequipment,GasEquipment}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::GasEquipment</code>. <b>Not yet available:</b> the Model definition, schedule, and zone/space relationship methods. EPModel exposes direct design-level and fraction fields plus compatibility multiplier methods.
   *
   * \par Known limitations
   * The compatibility multiplier scales the stored design-level fields because EnergyPlus has no dedicated multiplier field.
   */
  class EPMODEL_API GasEquipment : public ModelObject
  {
   public:
    explicit GasEquipment(const Model& model);

    virtual ~GasEquipment() override = default;
    GasEquipment(const GasEquipment& other) = default;
    GasEquipment(GasEquipment&& other) = default;
    GasEquipment& operator=(const GasEquipment&) = default;
    GasEquipment& operator=(GasEquipment&&) = default;

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

    double carbonDioxideGenerationRate() const;
    bool isCarbonDioxideGenerationRateDefaulted() const;
    bool setCarbonDioxideGenerationRate(double carbonDioxideGenerationRate);
    void resetCarbonDioxideGenerationRate();

    std::string endUseSubcategory() const;
    bool isEndUseSubcategoryDefaulted() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    void resetEndUseSubcategory();

    bool setMultiplier(double multiplier);
    void resetMultiplier();

   protected:
    using ImplType = detail::GasEquipment_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GasEquipment(std::shared_ptr<detail::GasEquipment_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
