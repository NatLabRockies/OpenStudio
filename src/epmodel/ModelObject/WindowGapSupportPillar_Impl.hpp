/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWGAPSUPPORTPILLAR_IMPL_HPP
#define EPMODEL_WINDOWGAPSUPPORTPILLAR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowGapSupportPillar_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowGapSupportPillar_Impl() override = default;

      double spacing() const;
      bool isSpacingDefaulted() const;
      bool setSpacing(double spacing);
      void resetSpacing();

      double radius() const;
      bool isRadiusDefaulted() const;
      bool setRadius(double radius);
      void resetRadius();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
