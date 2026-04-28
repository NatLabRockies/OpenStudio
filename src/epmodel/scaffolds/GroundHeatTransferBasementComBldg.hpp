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
    bool isJanuaryaveragetemperatureDefaulted() const;
    bool setJanuaryaveragetemperature(double januaryaveragetemperature);
    void resetJanuaryaveragetemperature();

    double februaryaveragetemperature() const;
    bool isFebruaryaveragetemperatureDefaulted() const;
    bool setFebruaryaveragetemperature(double februaryaveragetemperature);
    void resetFebruaryaveragetemperature();

    double marchaveragetemperature() const;
    bool isMarchaveragetemperatureDefaulted() const;
    bool setMarchaveragetemperature(double marchaveragetemperature);
    void resetMarchaveragetemperature();

    double aprilaveragetemperature() const;
    bool isAprilaveragetemperatureDefaulted() const;
    bool setAprilaveragetemperature(double aprilaveragetemperature);
    void resetAprilaveragetemperature();

    double mayaveragetemperature() const;
    bool isMayaveragetemperatureDefaulted() const;
    bool setMayaveragetemperature(double mayaveragetemperature);
    void resetMayaveragetemperature();

    double juneaveragetemperature() const;
    bool isJuneaveragetemperatureDefaulted() const;
    bool setJuneaveragetemperature(double juneaveragetemperature);
    void resetJuneaveragetemperature();

    double julyaveragetemperature() const;
    bool isJulyaveragetemperatureDefaulted() const;
    bool setJulyaveragetemperature(double julyaveragetemperature);
    void resetJulyaveragetemperature();

    double augustaveragetemperature() const;
    bool isAugustaveragetemperatureDefaulted() const;
    bool setAugustaveragetemperature(double augustaveragetemperature);
    void resetAugustaveragetemperature();

    double septemberaveragetemperature() const;
    bool isSeptemberaveragetemperatureDefaulted() const;
    bool setSeptemberaveragetemperature(double septemberaveragetemperature);
    void resetSeptemberaveragetemperature();

    double octoberaveragetemperature() const;
    bool isOctoberaveragetemperatureDefaulted() const;
    bool setOctoberaveragetemperature(double octoberaveragetemperature);
    void resetOctoberaveragetemperature();

    double novemberaveragetemperature() const;
    bool isNovemberaveragetemperatureDefaulted() const;
    bool setNovemberaveragetemperature(double novemberaveragetemperature);
    void resetNovemberaveragetemperature();

    double decemberaveragetemperature() const;
    bool isDecemberaveragetemperatureDefaulted() const;
    bool setDecemberaveragetemperature(double decemberaveragetemperature);
    void resetDecemberaveragetemperature();

    double dailyvariationsinewaveamplitude() const;
    bool isDailyvariationsinewaveamplitudeDefaulted() const;
    bool setDailyvariationsinewaveamplitude(double dailyvariationsinewaveamplitude);
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
