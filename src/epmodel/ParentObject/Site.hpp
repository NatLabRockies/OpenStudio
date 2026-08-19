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

/** \brief Defines the geographic site location and site-level simulation settings.
 *
 * \par EnergyPlus object
 * \epobject{group-location-climate-weather-file-access.html#sitelocation,Site:Location}
 *
 * \par Important behavior
 * Latitude, longitude, time zone, elevation, and site-location controls are stored on Site:Location. The terrain methods are a projected view of the EnergyPlus Building Terrain field, because Site:Location has no terrain field.
 *
 * \par OpenStudio Model API
 * The corresponding OpenStudio Model class is <code>openstudio::model::Site</code>.
 * <b>Not yet available:</b> Model's weather-file, climate-zone, ground-temperature, water-mains, and ground-reflectance relationships are not exposed.
 *
 * \par Known limitations
 * Terrain is persisted on the related Building object; callers should keep the Building wrapper in the same model when using the projected terrain API.
 */
  class EPMODEL_API Site : public ParentObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~Site() override = default;
    Site(const Site& other) = default;
    Site(Site&& other) = default;
    Site& operator=(const Site&) = default;
    Site& operator=(Site&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> validTerrainValues();

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
