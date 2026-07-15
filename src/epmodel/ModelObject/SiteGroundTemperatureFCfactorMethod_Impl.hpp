/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATUREFCFACTORMETHOD_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATUREFCFACTORMETHOD_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundTemperatureFCfactorMethod_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundTemperatureFCfactorMethod_Impl() override = default;

      // Scalar-only parity for Site:GroundTemperature:FCfactorMethod:
      // - Getters enforce required-getter strictness via asserted presence in .cpp.
      // - Setters use bool-return-with-assert semantics.
      // - Reset methods clear the field to restore default behavior.
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
