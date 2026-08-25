/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_BUILDINGSTORY_IMPL_HPP
#define EPMODEL_BUILDINGSTORY_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include "../utilities/core/UUID.hpp"

namespace openstudio {
namespace epmodel {

  class Space;
  class SpaceList;

  namespace detail {

    class EPMODEL_API BuildingStory_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~BuildingStory_Impl() override = default;

      boost::optional<double> nominalZCoordinate() const;
      bool setNominalZCoordinate(double nominalZCoordinate);
      void resetNominalZCoordinate();

      boost::optional<double> nominalFloortoFloorHeight() const;
      bool setNominalFloortoFloorHeight(double nominalFloortoFloorHeight);
      void resetNominalFloortoFloorHeight();

      boost::optional<double> nominalFloortoCeilingHeight() const;
      bool setNominalFloortoCeilingHeight(double nominalFloortoCeilingHeight);
      void resetNominalFloortoCeilingHeight();

      void setSpaceListHandle(const Handle& handle);

      SpaceList spaceList() const;
      bool addSpace(const Space& space);
      std::vector<Space> spaces() const;

     private:
      void updateSpaceListComment();

      Handle m_spaceListHandle;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
