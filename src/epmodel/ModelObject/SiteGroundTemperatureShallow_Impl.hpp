/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDTEMPERATURESHALLOW_IMPL_HPP
#define EPMODEL_SITEGROUNDTEMPERATURESHALLOW_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundTemperatureShallow_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundTemperatureShallow_Impl() override = default;

      // Scalar-only parity for Site:GroundTemperature:Shallow:
      // - Required double getters enforce required getter strictness via asserted presence.
      // - Setters return bool and assert success for non-failable scalar fields.
      // - Reset methods clear fields to allow IDD defaults to apply.
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
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
