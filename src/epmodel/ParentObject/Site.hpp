/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITE_HPP
#define EPMODEL_SITE_HPP

#include "EPModelAPI.hpp"
#include "ParentObject/ParentObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class Site_Impl;
  }

  class EPMODEL_API Site : public ParentObject
  {
   public:
    virtual ~Site() override = default;
    Site(const Site& other) = default;
    Site(Site&& other) = default;
    Site& operator=(const Site&) = default;
    Site& operator=(Site&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validTerrainValues();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::Site scalar accessor names/signatures for this model-counterpart class.
    // - Field Mapping: latitude/longitude/timeZone/elevation/keepSiteLocationInformation map directly to EnergyPlus
    //   Site:Location scalar fields.
    // - Field Mapping: terrain API maps to EnergyPlus Building/Terrain (cross-object drift), per ForwardTranslator behavior.
    // - Field Mapping: weather-file, climate-zones, and shading-group accessors are relationship APIs and are intentionally
    //   excluded from this scalar-only scaffold.
    // - ForwardTranslator evidence: ForwardTranslateSite.cpp writes Site:Location scalar fields while
    //   ForwardTranslateBuilding.cpp maps model::Site::terrain() to Building/Terrain.
    // - TODO(parity): Add non-scalar Site relationship APIs in a dedicated parity pass.
    double latitude() const;
    bool isLatitudeDefaulted() const;
    bool setLatitude(double latitude);
    void resetLatitude();

    double longitude() const;
    bool isLongitudeDefaulted() const;
    bool setLongitude(double longitude);
    void resetLongitude();

    double timeZone() const;
    bool isTimeZoneDefaulted() const;
    bool setTimeZone(double timeZone);
    void resetTimeZone();

    double elevation() const;
    bool isElevationDefaulted() const;
    bool setElevation(double elevation);
    void resetElevation();

    std::string terrain() const;
    bool isTerrainDefaulted() const;
    bool setTerrain(const std::string& terrain);
    void resetTerrain();

    bool keepSiteLocationInformation() const;
    bool isKeepSiteLocationInformationDefaulted() const;
    bool setKeepSiteLocationInformation(bool keepSiteLocationInformation);
    void resetKeepSiteLocationInformation();

   protected:
    explicit Site(const Model& model);

    using ImplType = detail::Site_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit Site(std::shared_ptr<detail::Site_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
