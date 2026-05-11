/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACE_IMPL_HPP
#define EPMODEL_SURFACE_IMPL_HPP

#include "PlanarSurface_Impl.hpp"

#include <utilities/geometry/Point3d.hpp>

namespace openstudio {
namespace epmodel {

  class Space;
  class SubSurface;
  class Surface;
  class SurfaceIntersection;

  namespace detail {

    class EPMODEL_API Surface_Impl : public PlanarSurface_Impl
    {
     public:
      using PlanarSurface_Impl::PlanarSurface_Impl;
      virtual ~Surface_Impl() override = default;

      virtual bool setVertices(const std::vector<Point3d>& vertices) override;

      std::string surfaceType() const;
      bool setSurfaceType(const std::string& surfaceType);

      std::string outsideBoundaryCondition() const;
      bool setOutsideBoundaryCondition(const std::string& outsideBoundaryCondition);

      std::string sunExposure() const;
      bool isSunExposureDefaulted() const;
      bool setSunExposure(const std::string& sunExposure);
      void resetSunExposure();

      std::string windExposure() const;
      bool isWindExposureDefaulted() const;
      bool setWindExposure(const std::string& windExposure);
      void resetWindExposure();

      boost::optional<double> viewFactortoGround() const;
      bool isViewFactortoGroundDefaulted() const;
      bool isViewFactortoGroundAutocalculated() const;
      bool setViewFactortoGround(double viewFactortoGround);
      void resetViewFactortoGround();
      void autocalculateViewFactortoGround();

      unsigned int numberofVertices() const;
      bool isNumberofVerticesDefaulted() const;
      bool isNumberofVerticesAutocalculated() const;
      bool setNumberofVertices(unsigned int numberofVertices);
      void resetNumberofVertices();
      void autocalculateNumberofVertices();

      // Helpers
      std::vector<SubSurface> subSurfaces() const;

      virtual boost::optional<Space> space() const override;
      virtual bool subtractFromGrossArea() const override;
      bool setSpace(const Space& space);

      boost::optional<Surface> adjacentSurface() const;
      bool setAdjacentSurface(Surface& surface);
      void resetAdjacentSurface();

      bool intersect(Surface& otherSurface);
      boost::optional<SurfaceIntersection> computeIntersection(Surface& otherSurface);

      boost::optional<Surface> createAdjacentSurface(const Space& otherSpace);

      bool isGroundSurface() const;
      bool isPartOfEnvelope() const;

      void assignDefaultSurfaceType(bool emitChangeSignals = true);
      void assignDefaultBoundaryCondition(bool emitChangeSignals = true);
      void assignDefaultSunExposure(bool emitChangeSignals = true);
      void assignDefaultWindExposure(bool emitChangeSignals = true);

     private:
      REGISTER_LOGGER("openstudio.epmodel.Surface");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
