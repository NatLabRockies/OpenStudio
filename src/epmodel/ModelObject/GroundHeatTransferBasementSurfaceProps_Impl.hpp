/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTSURFACEPROPS_IMPL_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTSURFACEPROPS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GroundHeatTransferBasementSurfaceProps_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GroundHeatTransferBasementSurfaceProps_Impl() override = default;

      double aLBEDOSurfacealbedoforNosnowconditions() const;
      bool isALBEDOSurfacealbedoforNosnowconditionsDefaulted() const;
      bool setALBEDOSurfacealbedoforNosnowconditions(double aLBEDOSurfacealbedoforNosnowconditions);
      void resetALBEDOSurfacealbedoforNosnowconditions();

      double aLBEDOSurfacealbedoforsnowconditions() const;
      bool isALBEDOSurfacealbedoforsnowconditionsDefaulted() const;
      bool setALBEDOSurfacealbedoforsnowconditions(double aLBEDOSurfacealbedoforsnowconditions);
      void resetALBEDOSurfacealbedoforsnowconditions();

      double ePSLNSurfaceemissivityNoSnow() const;
      bool isEPSLNSurfaceemissivityNoSnowDefaulted() const;
      bool setEPSLNSurfaceemissivityNoSnow(double ePSLNSurfaceemissivityNoSnow);
      void resetEPSLNSurfaceemissivityNoSnow();

      double ePSLNSurfaceemissivitywithSnow() const;
      bool isEPSLNSurfaceemissivitywithSnowDefaulted() const;
      bool setEPSLNSurfaceemissivitywithSnow(double ePSLNSurfaceemissivitywithSnow);
      void resetEPSLNSurfaceemissivitywithSnow();

      double vEGHTSurfaceroughnessNosnowconditions() const;
      bool isVEGHTSurfaceroughnessNosnowconditionsDefaulted() const;
      bool setVEGHTSurfaceroughnessNosnowconditions(double vEGHTSurfaceroughnessNosnowconditions);
      void resetVEGHTSurfaceroughnessNosnowconditions();

      double vEGHTSurfaceroughnessSnowconditions() const;
      bool isVEGHTSurfaceroughnessSnowconditionsDefaulted() const;
      bool setVEGHTSurfaceroughnessSnowconditions(double vEGHTSurfaceroughnessSnowconditions);
      void resetVEGHTSurfaceroughnessSnowconditions();

      bool pETFlagPotentialevapotranspirationon() const;
      bool isPETFlagPotentialevapotranspirationonDefaulted() const;
      bool setPETFlagPotentialevapotranspirationon(bool pETFlagPotentialevapotranspirationon);
      void resetPETFlagPotentialevapotranspirationon();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
