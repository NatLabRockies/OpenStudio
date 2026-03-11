/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_ZONEEARTHTUBEPARAMETERS_IMPL_HPP
#define EPMODEL_ZONEEARTHTUBEPARAMETERS_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API ZoneEarthtubeParameters_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~ZoneEarthtubeParameters_Impl() override = default;

      int nodesAboveEarthTube() const;
      bool isNodesAboveEarthTubeDefaulted() const;
      bool setNodesAboveEarthTube(int nodesAboveEarthTube);
      void resetNodesAboveEarthTube();

      int nodesBelowEarthTube() const;
      bool isNodesBelowEarthTubeDefaulted() const;
      bool setNodesBelowEarthTube(int nodesBelowEarthTube);
      void resetNodesBelowEarthTube();

      double earthTubeDimensionlessBoundaryAbove() const;
      bool isEarthTubeDimensionlessBoundaryAboveDefaulted() const;
      bool setEarthTubeDimensionlessBoundaryAbove(double earthTubeDimensionlessBoundaryAbove);
      void resetEarthTubeDimensionlessBoundaryAbove();

      double earthTubeDimensionlessBoundaryBelow() const;
      bool isEarthTubeDimensionlessBoundaryBelowDefaulted() const;
      bool setEarthTubeDimensionlessBoundaryBelow(double earthTubeDimensionlessBoundaryBelow);
      void resetEarthTubeDimensionlessBoundaryBelow();

      double earthTubeSolutionSpaceWidth() const;
      bool isEarthTubeSolutionSpaceWidthDefaulted() const;
      bool setEarthTubeSolutionSpaceWidth(double earthTubeSolutionSpaceWidth);
      void resetEarthTubeSolutionSpaceWidth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
