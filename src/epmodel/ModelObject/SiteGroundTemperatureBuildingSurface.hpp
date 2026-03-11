/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREBUILDINGSURFACE_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREBUILDINGSURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SiteGroundTemperatureBuildingSurface_Impl;
  }

  class EPMODEL_API SiteGroundTemperatureBuildingSurface : public ModelObject
  {
   public:
    explicit SiteGroundTemperatureBuildingSurface(const Model& model);

    virtual ~SiteGroundTemperatureBuildingSurface() override = default;
    SiteGroundTemperatureBuildingSurface(const SiteGroundTemperatureBuildingSurface& other) = default;
    SiteGroundTemperatureBuildingSurface(SiteGroundTemperatureBuildingSurface&& other) = default;
    SiteGroundTemperatureBuildingSurface& operator=(const SiteGroundTemperatureBuildingSurface&) = default;
    SiteGroundTemperatureBuildingSurface& operator=(SiteGroundTemperatureBuildingSurface&& other) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Mirrors the openstudio::model SiteGroundTemperatureBuildingSurface scalar accessor names/signatures for each month.
    // - Field Mapping: Monthly ground temperatures delegate directly to Site:GroundTemperature:BuildingSurface month fields (see ForwardTranslateSiteGroundTemperatureBuildingSurface).
    // - Field Mapping: Resets clear the field string so the IDD default (18°C) repopulates on the next read.
    double januaryGroundTemperature() const;
    bool isJanuaryGroundTemperatureDefaulted() const;
    bool setJanuaryGroundTemperature(double januaryGroundTemperature);
    void resetJanuaryGroundTemperature();

    double februaryGroundTemperature() const;
    bool isFebruaryGroundTemperatureDefaulted() const;
    bool setFebruaryGroundTemperature(double februaryGroundTemperature);
    void resetFebruaryGroundTemperature();

    double marchGroundTemperature() const;
    bool isMarchGroundTemperatureDefaulted() const;
    bool setMarchGroundTemperature(double marchGroundTemperature);
    void resetMarchGroundTemperature();

    double aprilGroundTemperature() const;
    bool isAprilGroundTemperatureDefaulted() const;
    bool setAprilGroundTemperature(double aprilGroundTemperature);
    void resetAprilGroundTemperature();

    double mayGroundTemperature() const;
    bool isMayGroundTemperatureDefaulted() const;
    bool setMayGroundTemperature(double mayGroundTemperature);
    void resetMayGroundTemperature();

    double juneGroundTemperature() const;
    bool isJuneGroundTemperatureDefaulted() const;
    bool setJuneGroundTemperature(double juneGroundTemperature);
    void resetJuneGroundTemperature();

    double julyGroundTemperature() const;
    bool isJulyGroundTemperatureDefaulted() const;
    bool setJulyGroundTemperature(double julyGroundTemperature);
    void resetJulyGroundTemperature();

    double augustGroundTemperature() const;
    bool isAugustGroundTemperatureDefaulted() const;
    bool setAugustGroundTemperature(double augustGroundTemperature);
    void resetAugustGroundTemperature();

    double septemberGroundTemperature() const;
    bool isSeptemberGroundTemperatureDefaulted() const;
    bool setSeptemberGroundTemperature(double septemberGroundTemperature);
    void resetSeptemberGroundTemperature();

    double octoberGroundTemperature() const;
    bool isOctoberGroundTemperatureDefaulted() const;
    bool setOctoberGroundTemperature(double octoberGroundTemperature);
    void resetOctoberGroundTemperature();

    double novemberGroundTemperature() const;
    bool isNovemberGroundTemperatureDefaulted() const;
    bool setNovemberGroundTemperature(double novemberGroundTemperature);
    void resetNovemberGroundTemperature();

    double decemberGroundTemperature() const;
    bool isDecemberGroundTemperatureDefaulted() const;
    bool setDecemberGroundTemperature(double decemberGroundTemperature);
    void resetDecemberGroundTemperature();

   protected:
    using ImplType = detail::SiteGroundTemperatureBuildingSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundTemperatureBuildingSurface(std::shared_ptr<detail::SiteGroundTemperatureBuildingSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
