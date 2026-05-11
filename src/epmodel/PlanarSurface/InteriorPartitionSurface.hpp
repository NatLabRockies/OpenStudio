/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_INTERIORPARTITIONSURFACE_HPP
#define EPMODEL_INTERIORPARTITIONSURFACE_HPP

#include "EPModelAPI.hpp"
#include "PlanarSurface.hpp"

#include <utilities/geometry/Point3d.hpp>
#include <utilities/idd/IddEnums.hxx>

#include <memory>

namespace openstudio {
namespace epmodel {

  class Model;

  namespace detail {
    class InteriorPartitionSurface_Impl;
  }

  class EPMODEL_API InteriorPartitionSurface : public PlanarSurface
  {
   public:
    explicit InteriorPartitionSurface(const std::vector<Point3d>& vertices, const Model& model);

    virtual ~InteriorPartitionSurface() override = default;
    InteriorPartitionSurface(const InteriorPartitionSurface& other) = default;
    InteriorPartitionSurface(InteriorPartitionSurface&& other) = default;
    InteriorPartitionSurface& operator=(const InteriorPartitionSurface&) = default;
    InteriorPartitionSurface& operator=(InteriorPartitionSurface&&) = default;

    static IddObjectType iddObjectType();

    // Schema Alignment Notes:
    // - API: Preserve openstudio::model::InteriorPartitionSurface scalar accessor names/signatures.
    // - Field Mapping: surfaceArea -> InternalMass, Surface Area.
    // - Field Mapping: Construction Name, Zone or ZoneList Name, and Space or SpaceList Name are relationship fields and are excluded.
    // - API: converttoInternalMass and numberofVertices are retained compatibility shims; InternalMass has no direct scalar fields for these.
    // - ForwardTranslator evidence: ForwardTranslateInteriorPartitionSurface.cpp writes only InternalMass scalar SurfaceArea (and relationship targets).
    // - TODO(parity): Revisit drifted compatibility shims if epmodel introduces OS-schema-level geometry conversion state.
    bool converttoInternalMass() const;
    bool isConverttoInternalMassDefaulted() const;
    bool setConverttoInternalMass(bool converttoInternalMass);
    void resetConverttoInternalMass();

    boost::optional<double> surfaceArea() const;
    bool setSurfaceArea(boost::optional<double> surfaceArea);
    bool setSurfaceArea(double surfaceArea);
    void resetSurfaceArea();

    boost::optional<double> numberofVertices() const;
    bool isNumberofVerticesDefaulted() const;
    bool isNumberofVerticesAutocalculated() const;
    bool setNumberofVertices(boost::optional<double> numberofVertices);
    bool setNumberofVertices(double numberofVertices);
    void resetNumberofVertices();
    void autocalculateNumberofVertices();

   protected:
    using ImplType = detail::InteriorPartitionSurface_Impl;

    friend class Model;
    friend class openstudio::IdfObject;
    friend class openstudio::detail::IdfObject_Impl;

    explicit InteriorPartitionSurface(std::shared_ptr<detail::InteriorPartitionSurface_Impl> impl);
  };

}  // namespace epmodel
}  // namespace openstudio

#endif
