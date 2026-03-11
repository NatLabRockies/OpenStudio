/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTCOMBLDG_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTCOMBLDG_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

namespace detail {

class EPMODEL_API GroundHeatTransferBasementComBldg_Impl : public ModelObject_Impl
{
 public:
  using ModelObject_Impl::ModelObject_Impl;
  virtual ~GroundHeatTransferBasementComBldg_Impl() override = default;

  double januaryaveragetemperature() const;
  double februaryaveragetemperature() const;
  double marchaveragetemperature() const;
  double aprilaveragetemperature() const;
  double mayaveragetemperature() const;
  double juneaveragetemperature() const;
  double julyaveragetemperature() const;
  double augustaveragetemperature() const;
  double septemberaveragetemperature() const;
  double octoberaveragetemperature() const;
  double novemberaveragetemperature() const;
  double decemberaveragetemperature() const;
  double dailyvariationsinewaveamplitude() const;

  bool isJanuaryaveragetemperatureDefaulted() const;
  bool isFebruaryaveragetemperatureDefaulted() const;
  bool isMarchaveragetemperatureDefaulted() const;
  bool isAprilaveragetemperatureDefaulted() const;
  bool isMayaveragetemperatureDefaulted() const;
  bool isJuneaveragetemperatureDefaulted() const;
  bool isJulyaveragetemperatureDefaulted() const;
  bool isAugustaveragetemperatureDefaulted() const;
  bool isSeptemberaveragetemperatureDefaulted() const;
  bool isOctoberaveragetemperatureDefaulted() const;
  bool isNovemberaveragetemperatureDefaulted() const;
  bool isDecemberaveragetemperatureDefaulted() const;
  bool isDailyvariationsinewaveamplitudeDefaulted() const;

  bool setJanuaryaveragetemperature(double januaryaveragetemperature);
  bool setFebruaryaveragetemperature(double februaryaveragetemperature);
  bool setMarchaveragetemperature(double marchaveragetemperature);
  bool setAprilaveragetemperature(double aprilaveragetemperature);
  bool setMayaveragetemperature(double mayaveragetemperature);
  bool setJuneaveragetemperature(double juneaveragetemperature);
  bool setJulyaveragetemperature(double julyaveragetemperature);
  bool setAugustaveragetemperature(double augustaveragetemperature);
  bool setSeptemberaveragetemperature(double septemberaveragetemperature);
  bool setOctoberaveragetemperature(double octoberaveragetemperature);
  bool setNovemberaveragetemperature(double novemberaveragetemperature);
  bool setDecemberaveragetemperature(double decemberaveragetemperature);
  bool setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude);

  void resetJanuaryaveragetemperature();
  void resetFebruaryaveragetemperature();
  void resetMarchaveragetemperature();
  void resetAprilaveragetemperature();
  void resetMayaveragetemperature();
  void resetJuneaveragetemperature();
  void resetJulyaveragetemperature();
  void resetAugustaveragetemperature();
  void resetSeptemberaveragetemperature();
  void resetOctoberaveragetemperature();
  void resetNovemberaveragetemperature();
  void resetDecemberaveragetemperature();
  void resetDailyvariationsinewaveamplitude();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
