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
      bool setNodesAboveEarthTube(int nodesAboveEarthTube);
      bool isNodesAboveEarthTubeDefaulted() const;
      void resetNodesAboveEarthTube();

      int nodesBelowEarthTube() const;
      bool setNodesBelowEarthTube(int nodesBelowEarthTube);
      bool isNodesBelowEarthTubeDefaulted() const;
      void resetNodesBelowEarthTube();

      double earthTubeDimensionlessBoundaryAbove() const;
      bool setEarthTubeDimensionlessBoundaryAbove(double earthTubeDimensionlessBoundaryAbove);
      bool isEarthTubeDimensionlessBoundaryAboveDefaulted() const;
      void resetEarthTubeDimensionlessBoundaryAbove();

      double earthTubeDimensionlessBoundaryBelow() const;
      bool setEarthTubeDimensionlessBoundaryBelow(double earthTubeDimensionlessBoundaryBelow);
      bool isEarthTubeDimensionlessBoundaryBelowDefaulted() const;
      void resetEarthTubeDimensionlessBoundaryBelow();

      double earthTubeSolutionSpaceWidth() const;
      bool setEarthTubeSolutionSpaceWidth(double earthTubeSolutionSpaceWidth);
      bool isEarthTubeSolutionSpaceWidthDefaulted() const;
      void resetEarthTubeSolutionSpaceWidth();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
