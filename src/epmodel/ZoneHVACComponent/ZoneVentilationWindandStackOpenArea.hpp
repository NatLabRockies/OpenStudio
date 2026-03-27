/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_HPP
#define EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_HPP

#include "EPModelAPI.hpp"
#include "ZoneHVACComponent/ZoneHVACComponent.hpp"

#include <memory>

namespace boost {
template <typename T>
class optional;
}

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneVentilationWindandStackOpenArea_Impl;
  }

  class EPMODEL_API ZoneVentilationWindandStackOpenArea : public ZoneHVACComponent
  {
   public:
    explicit ZoneVentilationWindandStackOpenArea(const Model& model);

    virtual ~ZoneVentilationWindandStackOpenArea() override = default;
    ZoneVentilationWindandStackOpenArea(const ZoneVentilationWindandStackOpenArea& other) = default;
    ZoneVentilationWindandStackOpenArea(ZoneVentilationWindandStackOpenArea&& other) = default;
    ZoneVentilationWindandStackOpenArea& operator=(const ZoneVentilationWindandStackOpenArea&) = default;
    ZoneVentilationWindandStackOpenArea& operator=(ZoneVentilationWindandStackOpenArea&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Status: Partial Parity. The opening and environmental scalar fields are aligned, but the schedule-driven control surface remains relationship-driven.
    // - Canonical Counterpart: openstudio::model::ZoneVentilationWindandStackOpenArea.
    // - Implemented Parity: `openingArea`, `openingEffectiveness`, `effectiveAngle`, `heightDifference`, `dischargeCoefficientforOpening`, and the indoor/outdoor temperature and wind limits map directly to the EnergyPlus object.
    // - Documented Delta: Schedule-based inputs such as opening-area fraction, min/max indoor/outdoor temperature schedules, and delta-temperature schedules remain relationship-only.
    // - Field/Storage Mapping: Scalar values are stored directly on the EnergyPlus object while schedule inputs are managed through separate relationship state.
    // - Evidence: `src/model/ZoneVentilationWindandStackOpenArea.hpp`, `src/model/ZoneVentilationWindandStackOpenArea.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneVentilationWindandStackOpenArea.cpp`, `src/energyplus/ReverseTranslator/ReverseTranslateZoneVentilationWindandStackOpenArea.cpp`, and `src/epmodel/test/ZoneVentilationWindandStackOpenArea_GTest.cpp`.
    // - Remaining Parity Work: Add schedule helpers only if the canonical model surface continues to expose them directly.

    /** @name Field Accessors */
    //@{

    double openingArea() const;
    bool setOpeningArea(double openingArea);

    boost::optional<double> openingEffectiveness() const;
    bool isOpeningEffectivenessAutocalculated() const;
    bool setOpeningEffectiveness(double openingEffectiveness);
    void autocalculateOpeningEffectiveness();

    double effectiveAngle() const;
    bool setEffectiveAngle(double effectiveAngle);

    double heightDifference() const;
    bool setHeightDifference(double heightDifference);

    boost::optional<double> dischargeCoefficientforOpening() const;
    bool isDischargeCoefficientforOpeningAutocalculated() const;
    bool setDischargeCoefficientforOpening(double dischargeCoefficientforOpening);
    void autocalculateDischargeCoefficientforOpening();

    double minimumIndoorTemperature() const;
    bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

    double maximumIndoorTemperature() const;
    bool setMaximumIndoorTemperature(double maximumIndoorTemperature);

    double deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);

    double minimumOutdoorTemperature() const;
    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

    double maximumOutdoorTemperature() const;
    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

    double maximumWindSpeed() const;
    bool setMaximumWindSpeed(double maximumWindSpeed);

    //@}

   protected:
    using ImplType = detail::ZoneVentilationWindandStackOpenArea_Impl;

    explicit ZoneVentilationWindandStackOpenArea(std::shared_ptr<detail::ZoneVentilationWindandStackOpenArea_Impl> impl);

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
