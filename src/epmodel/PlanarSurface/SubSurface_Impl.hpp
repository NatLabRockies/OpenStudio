/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACE_IMPL_HPP
#define EPMODEL_SUBSURFACE_IMPL_HPP

#include "PlanarSurface_Impl.hpp"

namespace openstudio {
namespace epmodel {

  class Space;
  class Surface;

  namespace detail {

    class EPMODEL_API SubSurface_Impl : public PlanarSurface_Impl
    {
     public:
      using PlanarSurface_Impl::PlanarSurface_Impl;
      virtual ~SubSurface_Impl() override = default;

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

      boost::optional<double> numberofVertices() const;
      bool isNumberofVerticesDefaulted() const;
      bool isNumberofVerticesAutocalculated() const;
      bool setNumberofVertices(unsigned int numberofVertices);
      void resetNumberofVertices();
      void autocalculateNumberofVertices();

      virtual boost::optional<Space> space() const override;
      virtual bool subtractFromGrossArea() const override;

      boost::optional<Surface> surface() const;
      bool setSurface(const Surface& surface);

      /** Default sub surface type based on vertices. */
      std::string defaultSubSurfaceType() const;

      /** Assign default sub surface type based on vertices. */
      void assignDefaultSubSurfaceType();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
