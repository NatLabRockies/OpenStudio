/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACEPROPERTYUNDERWATER_HPP
#define EPMODEL_SURFACEPROPERTYUNDERWATER_HPP

#include "EPModelAPI.hpp"
#include "ModelObject.hpp"

#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class SurfacePropertyUnderwater_Impl;
  }

  class EPMODEL_API SurfacePropertyUnderwater : public ModelObject
  {
   public:
    explicit SurfacePropertyUnderwater(const Model& model);

    virtual ~SurfacePropertyUnderwater() override = default;
    SurfacePropertyUnderwater(const SurfacePropertyUnderwater& other) = default;
    SurfacePropertyUnderwater(SurfacePropertyUnderwater&& other) = default;
    SurfacePropertyUnderwater& operator=(const SurfacePropertyUnderwater&) = default;
    SurfacePropertyUnderwater& operator=(SurfacePropertyUnderwater&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: This no-counterpart type keeps the IDD-derived class/API naming.
    // - Field Mapping: Distance from Surface Centroid to Leading Edge of Boundary Layer routes to the scalar accessor below.
    // - Field Mapping: Free Stream Water Temperature Schedule and Free Stream Water Velocity Schedule are object-list relationships and excluded from scalar APIs.
    // - TODO(parity): Add non-scalar schedule target helpers once relationship APIs are needed.
    double distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer() const;
    bool setDistanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer(double distanceFromSurfaceCentroidToLeadingEdgeOfBoundaryLayer);

   protected:
    using ImplType = detail::SurfacePropertyUnderwater_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit SurfacePropertyUnderwater(std::shared_ptr<detail::SurfacePropertyUnderwater_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
