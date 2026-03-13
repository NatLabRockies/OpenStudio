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
