/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_GEOMETRYTRANSFORM_IMPL_HPP
#define EPMODEL_GEOMETRYTRANSFORM_IMPL_HPP

#include "ModelObject_Impl.hpp"

#include <vector>

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API GeometryTransform_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~GeometryTransform_Impl() override = default;

      std::string planeofTransform() const;
      bool setPlaneofTransform(const std::string& planeofTransform);
      bool isPlaneofTransformDefaulted() const;
      void resetPlaneofTransform();

      double currentAspectRatio() const;
      bool setCurrentAspectRatio(double currentAspectRatio);

      double newAspectRatio() const;
      bool setNewAspectRatio(double newAspectRatio);

      std::vector<std::string> planeofTransformValues() const;
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
