/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTCOMBLDG_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTCOMBLDG_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementComBldg_Impl;
}

class EPMODEL_API GroundHeatTransferBasementComBldg : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementComBldg(const Model& model);

  virtual ~GroundHeatTransferBasementComBldg() override = default;
  GroundHeatTransferBasementComBldg(const GroundHeatTransferBasementComBldg& other) = default;
  GroundHeatTransferBasementComBldg(GroundHeatTransferBasementComBldg&& other) = default;
  GroundHeatTransferBasementComBldg& operator=(const GroundHeatTransferBasementComBldg&) = default;
  GroundHeatTransferBasementComBldg& operator=(GroundHeatTransferBasementComBldg&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:ComBldg numeric fields.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

 protected:
  using ImplType = detail::GroundHeatTransferBasementComBldg_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementComBldg(std::shared_ptr<detail::GroundHeatTransferBasementComBldg_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
