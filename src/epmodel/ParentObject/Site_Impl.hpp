/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITE_IMPL_HPP
#define EPMODEL_SITE_IMPL_HPP

#include "ParentObject/ParentObject_Impl.hpp"

#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API Site_Impl : public ParentObject_Impl
    {
     public:
      using ParentObject_Impl::ParentObject_Impl;
      virtual ~Site_Impl() override = default;

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

      std::vector<std::string> validTerrainValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
