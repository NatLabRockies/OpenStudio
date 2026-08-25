/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_HPP
#define EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
class Model;

namespace epmodel {

  namespace detail {
    class ZoneCapacitanceMultiplierResearchSpecial_Impl;
  }

  /** \brief ZoneCapacitanceMultiplierResearchSpecial.
   *
   * \par EnergyPlus object
   * \epobject{group-simulation-parameters.html#zonecapacitancemultiplierresearchspecial,ZoneCapacitanceMultiplier:ResearchSpecial}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::ZoneCapacitanceMultiplierResearchSpecial</code>. The temperature, humidity, and carbon-dioxide capacity multipliers map directly to EnergyPlus.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API ZoneCapacitanceMultiplierResearchSpecial : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~ZoneCapacitanceMultiplierResearchSpecial() override = default;
    ZoneCapacitanceMultiplierResearchSpecial(const ZoneCapacitanceMultiplierResearchSpecial& other) = default;
    ZoneCapacitanceMultiplierResearchSpecial(ZoneCapacitanceMultiplierResearchSpecial&& other) = default;
    ZoneCapacitanceMultiplierResearchSpecial& operator=(const ZoneCapacitanceMultiplierResearchSpecial&) = default;
    ZoneCapacitanceMultiplierResearchSpecial& operator=(ZoneCapacitanceMultiplierResearchSpecial&&) = default;

    static IddObjectType iddObjectType();
    double temperatureCapacityMultiplier() const;
    bool isTemperatureCapacityMultiplierDefaulted() const;
    bool setTemperatureCapacityMultiplier(double temperatureCapacityMultiplier);
    void resetTemperatureCapacityMultiplier();

    double humidityCapacityMultiplier() const;
    bool isHumidityCapacityMultiplierDefaulted() const;
    bool setHumidityCapacityMultiplier(double humidityCapacityMultiplier);
    void resetHumidityCapacityMultiplier();

    double carbonDioxideCapacityMultiplier() const;
    bool isCarbonDioxideCapacityMultiplierDefaulted() const;
    bool setCarbonDioxideCapacityMultiplier(double carbonDioxideCapacityMultiplier);
    void resetCarbonDioxideCapacityMultiplier();

   protected:
    explicit ZoneCapacitanceMultiplierResearchSpecial(const Model& model);

    using ImplType = detail::ZoneCapacitanceMultiplierResearchSpecial_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneCapacitanceMultiplierResearchSpecial(std::shared_ptr<detail::ZoneCapacitanceMultiplierResearchSpecial_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_ZONECAPACITANCEMULTIPLIERRESEARCHSPECIAL_HPP
