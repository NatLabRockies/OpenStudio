/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACE_IMPL_HPP
#define EPMODEL_SUBSURFACE_IMPL_HPP

#include "PlanarSurface_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class ConstructionBase;
  class Space;
  class Surface;
  class SubSurface;
  class WindowPropertyFrameAndDivider;

  namespace detail {

    class EPMODEL_API SubSurface_Impl : public PlanarSurface_Impl
    {
     public:
      using PlanarSurface_Impl::PlanarSurface_Impl;
      virtual ~SubSurface_Impl() override = default;

      virtual bool setVertices(const std::vector<Point3d>& vertices) override;

      boost::optional<ConstructionBase> construction() const override;
      bool setConstruction(const ConstructionBase& construction) override;
      void resetConstruction() override;

      std::string subSurfaceType() const;
      bool isSubSurfaceTypeDefaulted() const;
      bool setSubSurfaceType(const std::string& subSurfaceType);
      void resetSubSurfaceType();

      boost::optional<double> viewFactortoGround() const;
      bool isViewFactortoGroundDefaulted() const;
      bool isViewFactortoGroundAutocalculated() const;
      bool setViewFactortoGround(double viewFactortoGround);
      void resetViewFactortoGround();
      void autocalculateViewFactortoGround();

      double multiplier() const;
      bool isMultiplierDefaulted() const;
      bool setMultiplier(double multiplier);
      void resetMultiplier();

      unsigned int numberofVertices() const;
      bool isNumberofVerticesDefaulted() const;
      bool isNumberofVerticesAutocalculated() const;
      bool setNumberofVertices(unsigned int numberofVertices);
      void resetNumberofVertices();
      void autocalculateNumberofVertices();

      bool allowWindowPropertyFrameAndDivider() const;
      boost::optional<WindowPropertyFrameAndDivider> windowPropertyFrameAndDivider() const;
      bool setWindowPropertyFrameAndDivider(const WindowPropertyFrameAndDivider& windowPropertyFrameAndDivider);
      void resetWindowPropertyFrameAndDivider();

      virtual boost::optional<Space> space() const override;
      virtual bool subtractFromGrossArea() const override;

      bool isSkylight() const;

      boost::optional<Surface> surface() const;
      bool setSurface(const Surface& surface);

      /// get the adjacent subsurface
      boost::optional<SubSurface> adjacentSubSurface() const;
      bool setAdjacentSubSurface(SubSurface& subSurface);
      void resetAdjacentSubSurface();

      /** Default sub surface type based on vertices. */
      std::string defaultSubSurfaceType() const;
      /** Assign default sub surface type based on vertices. */
      void assignDefaultSubSurfaceType();

      std::string outsideBoundaryCondition() const;

      double roughOpeningArea() const;

      std::vector<Point3d> roughOpeningVertices() const;

      double frameArea() const;

      double dividerArea() const;

     private:
      REGISTER_LOGGER("openstudio.epmodel.SubSurface");
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
