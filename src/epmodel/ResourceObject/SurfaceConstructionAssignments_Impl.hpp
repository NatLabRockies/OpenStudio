/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONSTRUCTIONASSIGNMENTS_IMPL_HPP
#define EPMODEL_SURFACECONSTRUCTIONASSIGNMENTS_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ConstructionBase;
  class SurfaceConstructionAssignments;

  namespace detail {

    class EPMODEL_API SurfaceConstructionAssignments_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~SurfaceConstructionAssignments_Impl() override = default;

      boost::optional<ConstructionBase> floorConstruction() const;
      bool setFloorConstruction(const ConstructionBase& construction);
      void resetFloorConstruction();

      boost::optional<ConstructionBase> wallConstruction() const;
      bool setWallConstruction(const ConstructionBase& construction);
      void resetWallConstruction();

      boost::optional<ConstructionBase> roofCeilingConstruction() const;
      bool setRoofCeilingConstruction(const ConstructionBase& construction);
      void resetRoofCeilingConstruction();

      void merge(const SurfaceConstructionAssignments& other);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
