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
