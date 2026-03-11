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
  double aLBEDOSurfacealbedoforsnowconditions() const;
  double ePSLNSurfaceemissivityNoSnow() const;
  double ePSLNSurfaceemissivitywithSnow() const;
  double vEGHTSurfaceroughnessNosnowconditions() const;
  double vEGHTSurfaceroughnessSnowconditions() const;
  bool pETFlagPotentialevapotranspirationon() const;

  bool isALBEDOSurfacealbedoforNosnowconditionsDefaulted() const;
  bool isALBEDOSurfacealbedoforsnowconditionsDefaulted() const;
  bool isEPSLNSurfaceemissivityNoSnowDefaulted() const;
  bool isEPSLNSurfaceemissivitywithSnowDefaulted() const;
  bool isVEGHTSurfaceroughnessNosnowconditionsDefaulted() const;
  bool isVEGHTSurfaceroughnessSnowconditionsDefaulted() const;
  bool isPETFlagPotentialevapotranspirationonDefaulted() const;

  bool setALBEDOSurfacealbedoforNosnowconditions(double aLBEDOSurfacealbedoforNosnowconditions);
  bool setALBEDOSurfacealbedoforsnowconditions(double aLBEDOSurfacealbedoforsnowconditions);
  bool setEPSLNSurfaceemissivityNoSnow(double ePSLNSurfaceemissivityNoSnow);
  bool setEPSLNSurfaceemissivitywithSnow(double ePSLNSurfaceemissivitywithSnow);
  bool setVEGHTSurfaceroughnessNosnowconditions(double vEGHTSurfaceroughnessNosnowconditions);
  bool setVEGHTSurfaceroughnessSnowconditions(double vEGHTSurfaceroughnessSnowconditions);
  bool setPETFlagPotentialevapotranspirationon(bool pETFlagPotentialevapotranspirationon);

  void resetALBEDOSurfacealbedoforNosnowconditions();
  void resetALBEDOSurfacealbedoforsnowconditions();
  void resetEPSLNSurfaceemissivityNoSnow();
  void resetEPSLNSurfaceemissivitywithSnow();
  void resetVEGHTSurfaceroughnessNosnowconditions();
  void resetVEGHTSurfaceroughnessSnowconditions();
  void resetPETFlagPotentialevapotranspirationon();
};

}  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
