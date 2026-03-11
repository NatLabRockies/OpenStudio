/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATURESHALLOW_HPP
#define EPMODEL_SITEGROUNDTEMPERATURESHALLOW_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SiteGroundTemperatureShallow_Impl;
}

class EPMODEL_API SiteGroundTemperatureShallow : public ModelObject
{
 public:
  explicit SiteGroundTemperatureShallow(const Model& model);

  virtual ~SiteGroundTemperatureShallow() override = default;
  SiteGroundTemperatureShallow(const SiteGroundTemperatureShallow& other) = default;
  SiteGroundTemperatureShallow(SiteGroundTemperatureShallow&& other) = default;
  SiteGroundTemperatureShallow& operator=(const SiteGroundTemperatureShallow&) = default;
  SiteGroundTemperatureShallow& operator=(SiteGroundTemperatureShallow&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserved openstudio::model month accessor names/signatures delegate to epmodel scalar fields.
  // - Field Mapping: <Month>SurfaceGroundTemperature maps to Site:GroundTemperature:Shallow <Month> Surface Ground Temperature.
  // - Translator Evidence: ForwardTranslateSiteGroundTemperatureShallow.cpp writes these same 12 monthly fields.
  // - TODO(parity): Add legacy non-scalar helper APIs in a follow-up parity pass.
  double januarySurfaceGroundTemperature() const;
  bool isJanuarySurfaceGroundTemperatureDefaulted() const;
  bool setJanuarySurfaceGroundTemperature(double januarySurfaceGroundTemperature);
  void resetJanuarySurfaceGroundTemperature();

  double februarySurfaceGroundTemperature() const;
  bool isFebruarySurfaceGroundTemperatureDefaulted() const;
  bool setFebruarySurfaceGroundTemperature(double februarySurfaceGroundTemperature);
  void resetFebruarySurfaceGroundTemperature();

  double marchSurfaceGroundTemperature() const;
  bool isMarchSurfaceGroundTemperatureDefaulted() const;
  bool setMarchSurfaceGroundTemperature(double marchSurfaceGroundTemperature);
  void resetMarchSurfaceGroundTemperature();

  double aprilSurfaceGroundTemperature() const;
  bool isAprilSurfaceGroundTemperatureDefaulted() const;
  bool setAprilSurfaceGroundTemperature(double aprilSurfaceGroundTemperature);
  void resetAprilSurfaceGroundTemperature();

  double maySurfaceGroundTemperature() const;
  bool isMaySurfaceGroundTemperatureDefaulted() const;
  bool setMaySurfaceGroundTemperature(double maySurfaceGroundTemperature);
  void resetMaySurfaceGroundTemperature();

  double juneSurfaceGroundTemperature() const;
  bool isJuneSurfaceGroundTemperatureDefaulted() const;
  bool setJuneSurfaceGroundTemperature(double juneSurfaceGroundTemperature);
  void resetJuneSurfaceGroundTemperature();

  double julySurfaceGroundTemperature() const;
  bool isJulySurfaceGroundTemperatureDefaulted() const;
  bool setJulySurfaceGroundTemperature(double julySurfaceGroundTemperature);
  void resetJulySurfaceGroundTemperature();

  double augustSurfaceGroundTemperature() const;
  bool isAugustSurfaceGroundTemperatureDefaulted() const;
  bool setAugustSurfaceGroundTemperature(double augustSurfaceGroundTemperature);
  void resetAugustSurfaceGroundTemperature();

  double septemberSurfaceGroundTemperature() const;
  bool isSeptemberSurfaceGroundTemperatureDefaulted() const;
  bool setSeptemberSurfaceGroundTemperature(double septemberSurfaceGroundTemperature);
  void resetSeptemberSurfaceGroundTemperature();

  double octoberSurfaceGroundTemperature() const;
  bool isOctoberSurfaceGroundTemperatureDefaulted() const;
  bool setOctoberSurfaceGroundTemperature(double octoberSurfaceGroundTemperature);
  void resetOctoberSurfaceGroundTemperature();

  double novemberSurfaceGroundTemperature() const;
  bool isNovemberSurfaceGroundTemperatureDefaulted() const;
  bool setNovemberSurfaceGroundTemperature(double novemberSurfaceGroundTemperature);
  void resetNovemberSurfaceGroundTemperature();

  double decemberSurfaceGroundTemperature() const;
  bool isDecemberSurfaceGroundTemperatureDefaulted() const;
  bool setDecemberSurfaceGroundTemperature(double decemberSurfaceGroundTemperature);
  void resetDecemberSurfaceGroundTemperature();

 protected:
  using ImplType = detail::SiteGroundTemperatureShallow_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SiteGroundTemperatureShallow(std::shared_ptr<detail::SiteGroundTemperatureShallow_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
