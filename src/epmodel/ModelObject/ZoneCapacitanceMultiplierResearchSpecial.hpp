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

  class EPMODEL_API ZoneCapacitanceMultiplierResearchSpecial : public ModelObject
  {
   public:
    virtual ~ZoneCapacitanceMultiplierResearchSpecial() override = default;
    ZoneCapacitanceMultiplierResearchSpecial(const ZoneCapacitanceMultiplierResearchSpecial& other) = default;
    ZoneCapacitanceMultiplierResearchSpecial(ZoneCapacitanceMultiplierResearchSpecial&& other) = default;
    ZoneCapacitanceMultiplierResearchSpecial& operator=(const ZoneCapacitanceMultiplierResearchSpecial&) = default;
    ZoneCapacitanceMultiplierResearchSpecial& operator=(ZoneCapacitanceMultiplierResearchSpecial&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve the openstudio::model ZoneCapacitanceMultiplierResearchSpecial scalar accessor names/signatures for parity.
    // - Field Mapping: temperatureCapacityMultiplier(), humidityCapacityMultiplier(), and carbonDioxideCapacityMultiplier()
    //   wrap the EnergyPlus ZoneCapacitanceMultiplier:ResearchSpecial fields via ZoneCapacitanceMultiplier_ResearchSpecialFields.
    // - Field Mapping: ForwardTranslator::translateZoneCapacitanceMultiplierResearchSpecial still drives how these scalars land in the
    //   IDF and should remain aligned with this API.
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
