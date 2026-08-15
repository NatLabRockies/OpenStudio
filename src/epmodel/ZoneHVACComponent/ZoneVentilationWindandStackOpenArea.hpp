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
  class Schedule;

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
    // - Status: Scalar and Schedule Parity. The opening and environmental scalar fields and canonical schedule relationships are aligned.
    // - Canonical Counterpart: openstudio::model::ZoneVentilationWindandStackOpenArea.
    // - Implemented Parity: `openingAreaFractionSchedule`, the optional indoor/outdoor and delta-temperature schedules, and the opening and
    //   environmental scalar fields map directly to the EnergyPlus object.
    // - Documented Delta: The wrapper relies on the established ZoneHVACComponent thermal-zone attachment surface and adds no type-local topology behavior.
    // - Field/Storage Mapping: Scalar values and schedule pointers are stored directly on the EnergyPlus object, with no child objects to synchronize.
    // - Evidence: `src/model/ZoneVentilationWindandStackOpenArea.hpp`, `src/model/ZoneVentilationWindandStackOpenArea.cpp`, `src/energyplus/ForwardTranslator/ForwardTranslateZoneVentilationWindandStackOpenArea.cpp`, `src/energyplus/ReverseTranslator/ReverseTranslateZoneVentilationWindandStackOpenArea.cpp`, and `src/epmodel/test/ZoneVentilationWindandStackOpenArea_GTest.cpp`.
    // - Remaining Parity Work: None within the current canonical public surface.

    /** @name Field Accessors */
    //@{

    double openingArea() const;
    bool setOpeningArea(double openingArea);

    Schedule openingAreaFractionSchedule() const;
    bool setOpeningAreaFractionSchedule(Schedule& schedule);

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
    boost::optional<Schedule> minimumIndoorTemperatureSchedule() const;
    bool setMinimumIndoorTemperatureSchedule(Schedule& schedule);
    void resetMinimumIndoorTemperatureSchedule();

    double maximumIndoorTemperature() const;
    bool setMaximumIndoorTemperature(double maximumIndoorTemperature);
    boost::optional<Schedule> maximumIndoorTemperatureSchedule() const;
    bool setMaximumIndoorTemperatureSchedule(Schedule& schedule);
    void resetMaximumIndoorTemperatureSchedule();

    double deltaTemperature() const;
    bool setDeltaTemperature(double deltaTemperature);
    boost::optional<Schedule> deltaTemperatureSchedule() const;
    bool setDeltaTemperatureSchedule(Schedule& schedule);
    void resetDeltaTemperatureSchedule();

    double minimumOutdoorTemperature() const;
    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);
    boost::optional<Schedule> minimumOutdoorTemperatureSchedule() const;
    bool setMinimumOutdoorTemperatureSchedule(Schedule& schedule);
    void resetMinimumOutdoorTemperatureSchedule();

    double maximumOutdoorTemperature() const;
    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);
    boost::optional<Schedule> maximumOutdoorTemperatureSchedule() const;
    bool setMaximumOutdoorTemperatureSchedule(Schedule& schedule);
    void resetMaximumOutdoorTemperatureSchedule();

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
