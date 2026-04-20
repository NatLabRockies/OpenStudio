/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_HPP
#define EPMODEL_GROUNDHEATTRANSFERSLABMATERIALS_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class GroundHeatTransferSlabMaterials_Impl;
  }

  class EPMODEL_API GroundHeatTransferSlabMaterials : public ModelObject
  {
   public:
    explicit GroundHeatTransferSlabMaterials(const Model& model);

    virtual ~GroundHeatTransferSlabMaterials() override = default;
    GroundHeatTransferSlabMaterials(const GroundHeatTransferSlabMaterials& other) = default;
    GroundHeatTransferSlabMaterials(GroundHeatTransferSlabMaterials&& other) = default;
    GroundHeatTransferSlabMaterials& operator=(const GroundHeatTransferSlabMaterials&) = default;
    GroundHeatTransferSlabMaterials& operator=(GroundHeatTransferSlabMaterials&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to GroundHeatTransfer:Slab:Materials N1-N9 fields.
    // - TODO(parity): Add relationship APIs incrementally if future schema revisions introduce link fields.
    double nMATNumberofmaterials() const;
    bool setNMATNumberofmaterials(double nMATNumberofmaterials);

    double aLBEDOSurfaceAlbedoNoSnow() const;
    bool isALBEDOSurfaceAlbedoNoSnowDefaulted() const;
    bool setALBEDOSurfaceAlbedoNoSnow(double aLBEDOSurfaceAlbedoNoSnow);
    void resetALBEDOSurfaceAlbedoNoSnow();

    double aLBEDOSurfaceAlbedoSnow() const;
    bool isALBEDOSurfaceAlbedoSnowDefaulted() const;
    bool setALBEDOSurfaceAlbedoSnow(double aLBEDOSurfaceAlbedoSnow);
    void resetALBEDOSurfaceAlbedoSnow();

    double ePSLWSurfaceEmissivityNoSnow() const;
    bool isEPSLWSurfaceEmissivityNoSnowDefaulted() const;
    bool setEPSLWSurfaceEmissivityNoSnow(double ePSLWSurfaceEmissivityNoSnow);
    void resetEPSLWSurfaceEmissivityNoSnow();

    double ePSLWSurfaceEmissivitySnow() const;
    bool isEPSLWSurfaceEmissivitySnowDefaulted() const;
    bool setEPSLWSurfaceEmissivitySnow(double ePSLWSurfaceEmissivitySnow);
    void resetEPSLWSurfaceEmissivitySnow();

    double z0SurfaceRoughnessNoSnow() const;
    bool isZ0SurfaceRoughnessNoSnowDefaulted() const;
    bool setZ0SurfaceRoughnessNoSnow(double z0SurfaceRoughnessNoSnow);
    void resetZ0SurfaceRoughnessNoSnow();

    double z0SurfaceRoughnessSnow() const;
    bool isZ0SurfaceRoughnessSnowDefaulted() const;
    bool setZ0SurfaceRoughnessSnow(double z0SurfaceRoughnessSnow);
    void resetZ0SurfaceRoughnessSnow();

    double hINIndoorHConvDownwardFlow() const;
    bool isHINIndoorHConvDownwardFlowDefaulted() const;
    bool setHINIndoorHConvDownwardFlow(double hINIndoorHConvDownwardFlow);
    void resetHINIndoorHConvDownwardFlow();

    double hINIndoorHConvUpward() const;
    bool isHINIndoorHConvUpwardDefaulted() const;
    bool setHINIndoorHConvUpward(double hINIndoorHConvUpward);
    void resetHINIndoorHConvUpward();

   protected:
    using ImplType = detail::GroundHeatTransferSlabMaterials_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit GroundHeatTransferSlabMaterials(std::shared_ptr<detail::GroundHeatTransferSlabMaterials_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
