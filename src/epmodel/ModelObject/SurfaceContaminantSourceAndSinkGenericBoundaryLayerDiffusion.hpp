/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICBOUNDARYLAYERDIFFUSION_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICBOUNDARYLAYERDIFFUSION_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl;
  }

  class EPMODEL_API SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion : public ModelObject
  {
   public:
    explicit SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(const Model& model);

    virtual ~SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion() override = default;
    SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(const SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion& other) = default;
    SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion&& other) = default;
    SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion&
      operator=(const SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion&) = default;
    SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion& operator=(SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type uses IDD-derived class/accessor naming.
    // - Field Mapping: Scalar APIs map directly to SurfaceContaminantSourceAndSink:Generic:BoundaryLayerDiffusion numeric fields.
    // - Field Mapping: Surface Name and Schedule Name linkage fields remain excluded as relationship fields.
    // - TODO(parity): Add relationship APIs after scalar saturation without changing scalar signatures.

    // Mass transfer coefficient field
    boost::optional<double> massTransferCoefficient() const;
    bool setMassTransferCoefficient(double massTransferCoefficient);
    void resetMassTransferCoefficient();

    // Henry adsorption constant or partition coefficient field
    boost::optional<double> henryAdsorptionConstantorPartitionCoefficient() const;
    bool setHenryAdsorptionConstantorPartitionCoefficient(double henryAdsorptionConstantorPartitionCoefficient);
    void resetHenryAdsorptionConstantorPartitionCoefficient();

   protected:
    using ImplType = detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion(
      std::shared_ptr<detail::SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
