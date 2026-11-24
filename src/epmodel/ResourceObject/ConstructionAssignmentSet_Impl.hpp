/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_CONSTRUCTIONASSIGNMENTSET_IMPL_HPP
#define EPMODEL_CONSTRUCTIONASSIGNMENTSET_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ConstructionAssignmentSet;
  class ConstructionBase;
  class SubSurfaceConstructionAssignments;
  class SurfaceConstructionAssignments;

  namespace detail {

    class EPMODEL_API ConstructionAssignmentSet_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~ConstructionAssignmentSet_Impl() override = default;

      boost::optional<SurfaceConstructionAssignments> exteriorSurfaceConstructionAssignments() const;
      bool setExteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
      void resetExteriorSurfaceConstructionAssignments();

      boost::optional<SurfaceConstructionAssignments> interiorSurfaceConstructionAssignments() const;
      bool setInteriorSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
      void resetInteriorSurfaceConstructionAssignments();

      boost::optional<SurfaceConstructionAssignments> groundContactSurfaceConstructionAssignments() const;
      bool setGroundContactSurfaceConstructionAssignments(const SurfaceConstructionAssignments& surfaceConstructionAssignments);
      void resetGroundContactSurfaceConstructionAssignments();

      boost::optional<SubSurfaceConstructionAssignments> exteriorSubSurfaceConstructionAssignments() const;
      bool setExteriorSubSurfaceConstructionAssignments(const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments);
      void resetExteriorSubSurfaceConstructionAssignments();

      boost::optional<SubSurfaceConstructionAssignments> interiorSubSurfaceConstructionAssignments() const;
      bool setInteriorSubSurfaceConstructionAssignments(const SubSurfaceConstructionAssignments& subSurfaceConstructionAssignments);
      void resetInteriorSubSurfaceConstructionAssignments();

      boost::optional<ConstructionBase> interiorPartitionConstruction() const;
      bool setInteriorPartitionConstruction(const ConstructionBase& construction);
      void resetInteriorPartitionConstruction();

      boost::optional<ConstructionBase> adiabaticSurfaceConstruction() const;
      bool setAdiabaticSurfaceConstruction(const ConstructionBase& construction);
      void resetAdiabaticSurfaceConstruction();

      void merge(const ConstructionAssignmentSet& other);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
