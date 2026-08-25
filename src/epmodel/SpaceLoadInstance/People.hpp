/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_PEOPLE_HPP
#define EPMODEL_PEOPLE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class People_Impl;
  }

  /** \brief Represents the EnergyPlus People object.
   *
   * \par EnergyPlus object
   * \epobject{group-internal-gains-people-lights-other.html#people,People}
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::People</code>. <b>Not yet available:</b> the Model schedule, space, and space-type relationship methods. EPModel exposes the scalar comfort/activity fields and compatibility multiplier methods.
   *
   * \par Known limitations
   * The compatibility multiplier scales the stored people-count or density fields because EnergyPlus has no dedicated multiplier field.
   */
  class EPMODEL_API People : public ModelObject
  {
   public:
    explicit People(const Model& model);

    virtual ~People() override = default;
    People(const People& other) = default;
    People(People&& other) = default;
    People& operator=(const People&) = default;
    People& operator=(People&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> clothingInsulationCalculationMethodValues();


    // Clothing insulation calculation method
    std::string clothingInsulationCalculationMethod() const;
    bool setClothingInsulationCalculationMethod(const std::string& clothingInsulationCalculationMethod);

    // Cold stress temperature threshold
    double coldStressTemperatureThreshold() const;
    bool isColdStressTemperatureThresholdDefaulted() const;
    bool setColdStressTemperatureThreshold(double coldStressTemperatureThreshold);
    void resetColdStressTemperatureThreshold();

    // Heat stress temperature threshold
    double heatStressTemperatureThreshold() const;
    bool isHeatStressTemperatureThresholdDefaulted() const;
    bool setHeatStressTemperatureThreshold(double heatStressTemperatureThreshold);
    void resetHeatStressTemperatureThreshold();

    // Multipliers (model compatibility methods)
    bool setMultiplier(double multiplier);
    void resetMultiplier();

   protected:
    using ImplType = detail::People_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit People(std::shared_ptr<detail::People_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
