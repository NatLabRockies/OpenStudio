/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREDEEP_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREDEEP_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SiteGroundTemperatureDeep_Impl;
}

class EPMODEL_API SiteGroundTemperatureDeep : public ModelObject
{
 public:
  static constexpr bool is_unique = true;  // This is a Unique ModelObject

  explicit SiteGroundTemperatureDeep(const Model& model);

  virtual ~SiteGroundTemperatureDeep() override = default;
  SiteGroundTemperatureDeep(const SiteGroundTemperatureDeep& other) = default;
  SiteGroundTemperatureDeep(SiteGroundTemperatureDeep&& other) = default;
  SiteGroundTemperatureDeep& operator=(const SiteGroundTemperatureDeep&) = default;
  SiteGroundTemperatureDeep& operator=(SiteGroundTemperatureDeep&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserved from openstudio::model counterpart.
  // - Field Mapping: Month scalar APIs map directly to Site:GroundTemperature:Deep fields.
  double januaryDeepGroundTemperature() const;
  bool isJanuaryDeepGroundTemperatureDefaulted() const;
  bool setJanuaryDeepGroundTemperature(double januaryDeepGroundTemperature);
  void resetJanuaryDeepGroundTemperature();

  double februaryDeepGroundTemperature() const;
  bool isFebruaryDeepGroundTemperatureDefaulted() const;
  bool setFebruaryDeepGroundTemperature(double februaryDeepGroundTemperature);
  void resetFebruaryDeepGroundTemperature();

  double marchDeepGroundTemperature() const;
  bool isMarchDeepGroundTemperatureDefaulted() const;
  bool setMarchDeepGroundTemperature(double marchDeepGroundTemperature);
  void resetMarchDeepGroundTemperature();

  double aprilDeepGroundTemperature() const;
  bool isAprilDeepGroundTemperatureDefaulted() const;
  bool setAprilDeepGroundTemperature(double aprilDeepGroundTemperature);
  void resetAprilDeepGroundTemperature();

  double mayDeepGroundTemperature() const;
  bool isMayDeepGroundTemperatureDefaulted() const;
  bool setMayDeepGroundTemperature(double mayDeepGroundTemperature);
  void resetMayDeepGroundTemperature();

  double juneDeepGroundTemperature() const;
  bool isJuneDeepGroundTemperatureDefaulted() const;
  bool setJuneDeepGroundTemperature(double juneDeepGroundTemperature);
  void resetJuneDeepGroundTemperature();

  double julyDeepGroundTemperature() const;
  bool isJulyDeepGroundTemperatureDefaulted() const;
  bool setJulyDeepGroundTemperature(double julyDeepGroundTemperature);
  void resetJulyDeepGroundTemperature();

  double augustDeepGroundTemperature() const;
  bool isAugustDeepGroundTemperatureDefaulted() const;
  bool setAugustDeepGroundTemperature(double augustDeepGroundTemperature);
  void resetAugustDeepGroundTemperature();

  double septemberDeepGroundTemperature() const;
  bool isSeptemberDeepGroundTemperatureDefaulted() const;
  bool setSeptemberDeepGroundTemperature(double septemberDeepGroundTemperature);
  void resetSeptemberDeepGroundTemperature();

  double octoberDeepGroundTemperature() const;
  bool isOctoberDeepGroundTemperatureDefaulted() const;
  bool setOctoberDeepGroundTemperature(double octoberDeepGroundTemperature);
  void resetOctoberDeepGroundTemperature();

  double novemberDeepGroundTemperature() const;
  bool isNovemberDeepGroundTemperatureDefaulted() const;
  bool setNovemberDeepGroundTemperature(double novemberDeepGroundTemperature);
  void resetNovemberDeepGroundTemperature();

  double decemberDeepGroundTemperature() const;
  bool isDecemberDeepGroundTemperatureDefaulted() const;
  bool setDecemberDeepGroundTemperature(double decemberDeepGroundTemperature);
  void resetDecemberDeepGroundTemperature();

 protected:
  using ImplType = detail::SiteGroundTemperatureDeep_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SiteGroundTemperatureDeep(std::shared_ptr<detail::SiteGroundTemperatureDeep_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
