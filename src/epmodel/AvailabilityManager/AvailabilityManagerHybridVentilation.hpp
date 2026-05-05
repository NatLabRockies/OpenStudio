/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_HPP
#define EPMODEL_AVAILABILITYMANAGERHYBRIDVENTILATION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class AvailabilityManagerHybridVentilation_Impl;
  }

  class EPMODEL_API AvailabilityManagerHybridVentilation : public ModelObject
  {
   public:
    explicit AvailabilityManagerHybridVentilation(const Model& model);

    virtual ~AvailabilityManagerHybridVentilation() override = default;
    AvailabilityManagerHybridVentilation(const AvailabilityManagerHybridVentilation& other) = default;
    AvailabilityManagerHybridVentilation(AvailabilityManagerHybridVentilation&& other) = default;
    AvailabilityManagerHybridVentilation& operator=(const AvailabilityManagerHybridVentilation&) = default;
    AvailabilityManagerHybridVentilation& operator=(AvailabilityManagerHybridVentilation&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserves openstudio::model scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: scalar APIs map directly to E+ AvailabilityManager:HybridVentilation fields
    //   (Use Weather File Rain Indicators, wind/temp/enthalpy/dewpoint limits, and minimum operation times).
    // - TODO(parity): Keep relationship fields (HVAC Air Loop Name, Control Zone Name, schedule/curve links,
    //   ZoneVentilation Object Name) out of this scalar-only scaffold pass.
    bool useWeatherFileRainIndicators() const;
    bool setUseWeatherFileRainIndicators(bool useWeatherFileRainIndicators);

    double maximumWindSpeed() const;
    bool setMaximumWindSpeed(double maximumWindSpeed);

    double minimumOutdoorTemperature() const;
    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

    double maximumOutdoorTemperature() const;
    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

    double minimumOutdoorEnthalpy() const;
    bool setMinimumOutdoorEnthalpy(double minimumOutdoorEnthalpy);

    double maximumOutdoorEnthalpy() const;
    bool setMaximumOutdoorEnthalpy(double maximumOutdoorEnthalpy);

    double minimumOutdoorDewpoint() const;
    bool setMinimumOutdoorDewpoint(double minimumOutdoorDewpoint);

    double maximumOutdoorDewpoint() const;
    bool setMaximumOutdoorDewpoint(double maximumOutdoorDewpoint);

    double minimumHVACOperationTime() const;
    bool setMinimumHVACOperationTime(double minimumHVACOperationTime);

    double minimumVentilationTime() const;
    bool setMinimumVentilationTime(double minimumVentilationTime);

   protected:
    using ImplType = detail::AvailabilityManagerHybridVentilation_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit AvailabilityManagerHybridVentilation(std::shared_ptr<detail::AvailabilityManagerHybridVentilation_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
