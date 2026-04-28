/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_ZONEBASEBOARDOUTDOORTEMPERATURECONTROLLED_HPP
#define EPMODEL_ZONEBASEBOARDOUTDOORTEMPERATURECONTROLLED_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class ZoneBaseboardOutdoorTemperatureControlled_Impl;
  }

  class EPMODEL_API ZoneBaseboardOutdoorTemperatureControlled : public ModelObject
  {
   public:
    explicit ZoneBaseboardOutdoorTemperatureControlled(const Model& model);

    virtual ~ZoneBaseboardOutdoorTemperatureControlled() override = default;
    ZoneBaseboardOutdoorTemperatureControlled(const ZoneBaseboardOutdoorTemperatureControlled& other) = default;
    ZoneBaseboardOutdoorTemperatureControlled(ZoneBaseboardOutdoorTemperatureControlled&& other) = default;
    ZoneBaseboardOutdoorTemperatureControlled& operator=(const ZoneBaseboardOutdoorTemperatureControlled&) = default;
    ZoneBaseboardOutdoorTemperatureControlled& operator=(ZoneBaseboardOutdoorTemperatureControlled&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - Field Mapping: IDD-derived scalars (capacityAtLowTemperature, lowTemperature, capacityAtHighTemperature, highTemperature, fractionRadiant, endUseSubcategory) map directly to
    //   the EnergyPlus ZoneBaseboard:OutdoorTemperatureControlled fields with the same descriptive names.
    // - Field Mapping: Name, Zone/Space selection, and Schedule Name are object-list relationship fields handled by base ModelObject APIs and intentionally excluded from this scalar API.
    // - TODO(parity): Add richer relationship helpers once non-scalar topology support is in place.
    double capacityAtLowTemperature() const;
    bool setCapacityAtLowTemperature(double capacityAtLowTemperature);

    double lowTemperature() const;
    bool setLowTemperature(double lowTemperature);

    double capacityAtHighTemperature() const;
    bool setCapacityAtHighTemperature(double capacityAtHighTemperature);

    double highTemperature() const;
    bool setHighTemperature(double highTemperature);

    double fractionRadiant() const;
    bool setFractionRadiant(double fractionRadiant);
    bool isFractionRadiantDefaulted() const;
    void resetFractionRadiant();

    std::string endUseSubcategory() const;
    bool setEndUseSubcategory(const std::string& endUseSubcategory);
    bool isEndUseSubcategoryDefaulted() const;
    void resetEndUseSubcategory();

   protected:
    using ImplType = detail::ZoneBaseboardOutdoorTemperatureControlled_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit ZoneBaseboardOutdoorTemperatureControlled(std::shared_ptr<detail::ZoneBaseboardOutdoorTemperatureControlled_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
