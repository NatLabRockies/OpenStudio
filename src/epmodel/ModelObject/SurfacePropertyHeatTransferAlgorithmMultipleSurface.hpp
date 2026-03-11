/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMMULTIPLESURFACE_HPP
#define EPMODEL_SURFACEPROPERTYHEATTRANSFERALGORITHMMULTIPLESURFACE_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <memory>
#include <string>
#include <vector>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl;
  }

  class EPMODEL_API SurfacePropertyHeatTransferAlgorithmMultipleSurface : public ModelObject
  {
   public:
    explicit SurfacePropertyHeatTransferAlgorithmMultipleSurface(const Model& model);

    virtual ~SurfacePropertyHeatTransferAlgorithmMultipleSurface() override = default;
    SurfacePropertyHeatTransferAlgorithmMultipleSurface(const SurfacePropertyHeatTransferAlgorithmMultipleSurface& other) = default;
    SurfacePropertyHeatTransferAlgorithmMultipleSurface(SurfacePropertyHeatTransferAlgorithmMultipleSurface&& other) = default;
    SurfacePropertyHeatTransferAlgorithmMultipleSurface& operator=(const SurfacePropertyHeatTransferAlgorithmMultipleSurface&) = default;
    SurfacePropertyHeatTransferAlgorithmMultipleSurface& operator=(SurfacePropertyHeatTransferAlgorithmMultipleSurface&&) = default;

    static IddObjectType iddObjectType();

    static std::vector<std::string> surfaceTypeValues();
    static std::vector<std::string> algorithmValues();

    // Schema Alignment Notes:
    // - API: No openstudio::model counterpart exists, so this IDD-derived class name is preserved.
    // - Field Mapping: surfaceType() / setSurfaceType() map directly to the SurfaceProperty:HeatTransferAlgorithm:MultipleSurface
    //   Surface Type field (enumerated groups of surfaces).
    // - Field Mapping: algorithm() / isAlgorithmDefaulted() / resetAlgorithm() map to Algorithm (default
    //   ConductionTransferFunction) and follow Ruby-style default/reset semantics.
    // - TODO(parity): Introduce relationship helpers for each surface group once scalar coverage is complete.
    std::string surfaceType() const;
    bool setSurfaceType(const std::string& surfaceType);

    std::string algorithm() const;
    bool setAlgorithm(const std::string& algorithm);
    bool isAlgorithmDefaulted() const;
    void resetAlgorithm();

   protected:
    using ImplType = detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyHeatTransferAlgorithmMultipleSurface(
      std::shared_ptr<detail::SurfacePropertyHeatTransferAlgorithmMultipleSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
