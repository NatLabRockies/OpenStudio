/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SUBSURFACE_IMPL_HPP
#define EPMODEL_SUBSURFACE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SubSurface_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SubSurface_Impl() override = default;

      std::string subSurfaceType() const;
      bool isSubSurfaceTypeDefaulted() const;
      bool setSubSurfaceType(const std::string& subSurfaceType);
      void resetSubSurfaceType();

      boost::optional<double> viewFactortoGround() const;
      bool isViewFactortoGroundDefaulted() const;
      bool isViewFactortoGroundAutocalculated() const;
      bool setViewFactortoGround(boost::optional<double> viewFactortoGround);
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
      bool setNumberofVertices(boost::optional<double> numberofVertices);
      bool setNumberofVertices(double numberofVertices);
      void resetNumberofVertices();
      void autocalculateNumberofVertices();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
