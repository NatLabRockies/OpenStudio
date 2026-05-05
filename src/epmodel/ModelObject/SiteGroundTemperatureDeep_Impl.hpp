/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREDEEP_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREDEEP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundTemperatureDeep_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundTemperatureDeep_Impl() override = default;

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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
