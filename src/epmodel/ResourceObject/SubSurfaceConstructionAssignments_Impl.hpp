/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACECONSTRUCTIONASSIGNMENTS_IMPL_HPP
#define EPMODEL_SUBSURFACECONSTRUCTIONASSIGNMENTS_IMPL_HPP

#include "ResourceObject/ResourceObject_Impl.hpp"

#include <boost/optional.hpp>

namespace openstudio {
namespace epmodel {

  class ConstructionBase;
  class SubSurfaceConstructionAssignments;

  namespace detail {

    class EPMODEL_API SubSurfaceConstructionAssignments_Impl : public ResourceObject_Impl
    {
     public:
      using ResourceObject_Impl::ResourceObject_Impl;
      virtual ~SubSurfaceConstructionAssignments_Impl() override = default;

      boost::optional<ConstructionBase> fixedWindowConstruction() const;
      bool setFixedWindowConstruction(const ConstructionBase& construction);
      void resetFixedWindowConstruction();

      boost::optional<ConstructionBase> operableWindowConstruction() const;
      bool setOperableWindowConstruction(const ConstructionBase& construction);
      void resetOperableWindowConstruction();

      boost::optional<ConstructionBase> doorConstruction() const;
      bool setDoorConstruction(const ConstructionBase& construction);
      void resetDoorConstruction();

      boost::optional<ConstructionBase> glassDoorConstruction() const;
      bool setGlassDoorConstruction(const ConstructionBase& construction);
      void resetGlassDoorConstruction();

      boost::optional<ConstructionBase> overheadDoorConstruction() const;
      bool setOverheadDoorConstruction(const ConstructionBase& construction);
      void resetOverheadDoorConstruction();

      boost::optional<ConstructionBase> skylightConstruction() const;
      bool setSkylightConstruction(const ConstructionBase& construction);
      void resetSkylightConstruction();

      boost::optional<ConstructionBase> tubularDaylightDomeConstruction() const;
      bool setTubularDaylightDomeConstruction(const ConstructionBase& construction);
      void resetTubularDaylightDomeConstruction();

      boost::optional<ConstructionBase> tubularDaylightDiffuserConstruction() const;
      bool setTubularDaylightDiffuserConstruction(const ConstructionBase& construction);
      void resetTubularDaylightDiffuserConstruction();

      void merge(const SubSurfaceConstructionAssignments& other);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
