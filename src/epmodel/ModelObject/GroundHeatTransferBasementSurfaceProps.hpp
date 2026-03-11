/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERBASEMENTSURFACEPROPS_HPP
#define EPMODEL_GROUNDHEATTRANSFERBASEMENTSURFACEPROPS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

class Model;

namespace detail {
class GroundHeatTransferBasementSurfaceProps_Impl;
}

class EPMODEL_API GroundHeatTransferBasementSurfaceProps : public ModelObject
{
 public:
  explicit GroundHeatTransferBasementSurfaceProps(const Model& model);

  virtual ~GroundHeatTransferBasementSurfaceProps() override = default;
  GroundHeatTransferBasementSurfaceProps(const GroundHeatTransferBasementSurfaceProps& other) = default;
  GroundHeatTransferBasementSurfaceProps(GroundHeatTransferBasementSurfaceProps&& other) = default;
  GroundHeatTransferBasementSurfaceProps& operator=(const GroundHeatTransferBasementSurfaceProps&) = default;
  GroundHeatTransferBasementSurfaceProps& operator=(GroundHeatTransferBasementSurfaceProps&&) = default;

  static IddObjectType iddObjectType();

  // Schema Alignment Notes:
  // - API: This no-counterpart type uses IDD-derived class/accessor naming.
  // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Basement:SurfaceProps fields N1-N6 and A1.
  // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
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

 protected:
  using ImplType = detail::GroundHeatTransferBasementSurfaceProps_Impl;

  friend class Model;
  friend class openstudio::IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  explicit GroundHeatTransferBasementSurfaceProps(std::shared_ptr<detail::GroundHeatTransferBasementSurfaceProps_Impl> impl);
};

}  // namespace epmodel
}  // namespace openstudio

#endif
