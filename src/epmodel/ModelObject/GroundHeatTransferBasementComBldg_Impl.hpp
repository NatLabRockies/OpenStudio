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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
