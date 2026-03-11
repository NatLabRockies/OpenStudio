/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREFCFACTORMETHOD_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREFCFACTORMETHOD_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class SiteGroundTemperatureFCfactorMethod_Impl;
}

class EPMODEL_API SiteGroundTemperatureFCfactorMethod : public ModelObject
{
 public:
  explicit SiteGroundTemperatureFCfactorMethod(const Model& model);

  virtual ~SiteGroundTemperatureFCfactorMethod() override = default;
  SiteGroundTemperatureFCfactorMethod(const SiteGroundTemperatureFCfactorMethod& other) = default;
  SiteGroundTemperatureFCfactorMethod(SiteGroundTemperatureFCfactorMethod&& other) = default;
  SiteGroundTemperatureFCfactorMethod& operator=(const SiteGroundTemperatureFCfactorMethod&) = default;
  SiteGroundTemperatureFCfactorMethod& operator=(SiteGroundTemperatureFCfactorMethod&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: Preserved from openstudio::model counterpart accessor naming/signatures.
  // - Field Mapping: Month scalar APIs map directly to EnergyPlus Site:GroundTemperature:FCfactorMethod fields.
  // - Translator Evidence: ForwardTranslateSiteGroundTemperatureFCfactorMethod.cpp writes the same 12 monthly fields.
  // - TODO(parity): Add legacy non-scalar helper APIs in a follow-up parity pass.
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
  using ImplType = detail::SiteGroundTemperatureFCfactorMethod_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit SiteGroundTemperatureFCfactorMethod(std::shared_ptr<detail::SiteGroundTemperatureFCfactorMethod_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
