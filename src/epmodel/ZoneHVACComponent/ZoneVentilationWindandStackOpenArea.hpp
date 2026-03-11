/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_HPP
#define EPMODEL_ZONEVENTILATIONWINDANDSTACKOPENAREA_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

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

  class EPMODEL_API ZoneVentilationWindandStackOpenArea : public ModelObject
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
    // - API: Scalar getters/setters preserve the openstudio::model naming while mapping directly to the
    //   EnergyPlus OS:ZoneVentilation:WindandStackOpenArea fields via the OS_ZoneVentilation_WindandStackOpenAreaFields
    //   enums (see ForwardTranslateZoneVentilationWindandStackOpenArea.cpp for the translator evidence).
    // - Field Mapping: Schedule-based inputs such as Opening Area Fraction Schedule, Minimum/Maximum Indoor/Outdoor
    //   Temperature Schedules, and the Delta Temperature Schedule are relationship-only and intentionally excluded from
    //   this scalar-only surface until specialized helpers exist.

    /** @name Getters */
    //@{
    double openingArea() const;

    boost::optional<double> openingEffectiveness() const;
    bool isOpeningEffectivenessAutocalculated() const;

    double effectiveAngle() const;

    double heightDifference() const;

    boost::optional<double> dischargeCoefficientforOpening() const;
    bool isDischargeCoefficientforOpeningAutocalculated() const;

    double minimumIndoorTemperature() const;

    double maximumIndoorTemperature() const;

    double deltaTemperature() const;

    double minimumOutdoorTemperature() const;

    double maximumOutdoorTemperature() const;

    double maximumWindSpeed() const;
    //@}

    /** @name Setters */
    //@{
    bool setOpeningArea(double openingArea);

    bool setOpeningEffectiveness(double openingEffectiveness);
    void autocalculateOpeningEffectiveness();

    bool setEffectiveAngle(double effectiveAngle);

    bool setHeightDifference(double heightDifference);

    bool setDischargeCoefficientforOpening(double dischargeCoefficientforOpening);
    void autocalculateDischargeCoefficientforOpening();

    bool setMinimumIndoorTemperature(double minimumIndoorTemperature);

    bool setMaximumIndoorTemperature(double maximumIndoorTemperature);

    bool setDeltaTemperature(double deltaTemperature);

    bool setMinimumOutdoorTemperature(double minimumOutdoorTemperature);

    bool setMaximumOutdoorTemperature(double maximumOutdoorTemperature);

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
