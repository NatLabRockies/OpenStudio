/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_SITEGROUNDREFLECTANCE_IMPL_HPP
#define EPMODEL_SITEGROUNDREFLECTANCE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SiteGroundReflectance_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SiteGroundReflectance_Impl() override = default;

      double januaryGroundReflectance() const;
      bool isJanuaryGroundReflectanceDefaulted() const;
      bool setJanuaryGroundReflectance(double januaryGroundReflectance);
      void resetJanuaryGroundReflectance();

      double februaryGroundReflectance() const;
      bool isFebruaryGroundReflectanceDefaulted() const;
      bool setFebruaryGroundReflectance(double februaryGroundReflectance);
      void resetFebruaryGroundReflectance();

      double marchGroundReflectance() const;
      bool isMarchGroundReflectanceDefaulted() const;
      bool setMarchGroundReflectance(double marchGroundReflectance);
      void resetMarchGroundReflectance();

      double aprilGroundReflectance() const;
      bool isAprilGroundReflectanceDefaulted() const;
      bool setAprilGroundReflectance(double aprilGroundReflectance);
      void resetAprilGroundReflectance();

      double mayGroundReflectance() const;
      bool isMayGroundReflectanceDefaulted() const;
      bool setMayGroundReflectance(double mayGroundReflectance);
      void resetMayGroundReflectance();

      double juneGroundReflectance() const;
      bool isJuneGroundReflectanceDefaulted() const;
      bool setJuneGroundReflectance(double juneGroundReflectance);
      void resetJuneGroundReflectance();

      double julyGroundReflectance() const;
      bool isJulyGroundReflectanceDefaulted() const;
      bool setJulyGroundReflectance(double julyGroundReflectance);
      void resetJulyGroundReflectance();

      double augustGroundReflectance() const;
      bool isAugustGroundReflectanceDefaulted() const;
      bool setAugustGroundReflectance(double augustGroundReflectance);
      void resetAugustGroundReflectance();

      double septemberGroundReflectance() const;
      bool isSeptemberGroundReflectanceDefaulted() const;
      bool setSeptemberGroundReflectance(double septemberGroundReflectance);
      void resetSeptemberGroundReflectance();

      double octoberGroundReflectance() const;
      bool isOctoberGroundReflectanceDefaulted() const;
      bool setOctoberGroundReflectance(double octoberGroundReflectance);
      void resetOctoberGroundReflectance();

      double novemberGroundReflectance() const;
      bool isNovemberGroundReflectanceDefaulted() const;
      bool setNovemberGroundReflectance(double novemberGroundReflectance);
      void resetNovemberGroundReflectance();

      double decemberGroundReflectance() const;
      bool isDecemberGroundReflectanceDefaulted() const;
      bool setDecemberGroundReflectance(double decemberGroundReflectance);
      void resetDecemberGroundReflectance();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif  // EPMODEL_SITEGROUNDREFLECTANCE_IMPL_HPP
