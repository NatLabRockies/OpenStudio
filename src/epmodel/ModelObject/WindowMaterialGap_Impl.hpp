/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
 *  See also https://openstudio.net/license
 ***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWMATERIALGAP_IMPL_HPP
#define EPMODEL_WINDOWMATERIALGAP_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowMaterialGap_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowMaterialGap_Impl() override = default;

      double thickness() const;
      bool setThickness(double thickness);

      double pressure() const;
      bool setPressure(double pressure);
      bool isPressureDefaulted() const;
      void resetPressure();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
