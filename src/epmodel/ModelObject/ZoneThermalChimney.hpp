/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONETHERMALCHIMNEY_HPP
#define EPMODEL_ZONETHERMALCHIMNEY_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
class Model;

namespace epmodel {

  namespace detail {
    class ZoneThermalChimney_Impl;
  }

  class EPMODEL_API ZoneThermalChimney : public ModelObject
  {
   public:
    explicit ZoneThermalChimney(const Model& model);
    virtual ~ZoneThermalChimney() override = default;
    ZoneThermalChimney(const ZoneThermalChimney& other) = default;
    ZoneThermalChimney(ZoneThermalChimney&& other) = default;
    ZoneThermalChimney& operator=(const ZoneThermalChimney&) = default;
    ZoneThermalChimney& operator=(ZoneThermalChimney&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: zoneThermalChimney() exposes the scalar EnergyPlus fields Width of the Absorber Wall,
    //   Cross Sectional Area of Air Channel Outlet, and Discharge Coefficient while preserving the
    //   IDD-derived naming for the new no-counterpart type.
    // - Field Mapping: Zone Name, Availability Schedule Name, the Zone/Space name group, and the
    //   extensible inlet distance/ratio/area groups remain relationship-like object-list fields and are
    //   intentionally excluded from this scalar-only API surface.
    double widthOfTheAbsorberWall() const;
    bool setWidthOfTheAbsorberWall(double widthOfTheAbsorberWall);

    double crossSectionalAreaOfAirChannelOutlet() const;
    bool setCrossSectionalAreaOfAirChannelOutlet(double crossSectionalAreaOfAirChannelOutlet);

    double dischargeCoefficient() const;
    bool isDischargeCoefficientDefaulted() const;
    bool setDischargeCoefficient(double dischargeCoefficient);
    void resetDischargeCoefficient();

   protected:
    using ImplType = detail::ZoneThermalChimney_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneThermalChimney(std::shared_ptr<detail::ZoneThermalChimney_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
