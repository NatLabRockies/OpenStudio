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

  /** \brief SiteGroundTemperatureBuildingSurface.
   *
   * \par EnergyPlus object
   * \epobject{group-location-climate-weather-file-access.html#sitegroundtemperaturebuildingsurface,Site:GroundTemperature:BuildingSurface}.
   *
   * \par OpenStudio Model API
   * The corresponding OpenStudio Model class is <code>openstudio::model::SiteGroundTemperatureBuildingSurface</code>. The twelve monthly temperatures map directly to EnergyPlus; resetting a value restores the IDD default. EPModel uses named month methods rather than Model's month-indexed and all-month helper family.
   *
   * \par Known limitations
   * No known EPModel-specific limitations.
   */
  class EPMODEL_API SiteGroundTemperatureBuildingSurface : public ModelObject
  {
   public:
    static constexpr bool is_unique = true;  // This is a Unique ModelObject

    virtual ~SiteGroundTemperatureBuildingSurface() override = default;
    SiteGroundTemperatureBuildingSurface(const SiteGroundTemperatureBuildingSurface& other) = default;
    SiteGroundTemperatureBuildingSurface(SiteGroundTemperatureBuildingSurface&& other) = default;
    SiteGroundTemperatureBuildingSurface& operator=(const SiteGroundTemperatureBuildingSurface&) = default;
    SiteGroundTemperatureBuildingSurface& operator=(SiteGroundTemperatureBuildingSurface&& other) = default;

    static IddObjectType iddObjectType();
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
    explicit SiteGroundTemperatureBuildingSurface(const Model& model);

    using ImplType = detail::SiteGroundTemperatureBuildingSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SiteGroundTemperatureBuildingSurface(std::shared_ptr<detail::SiteGroundTemperatureBuildingSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
