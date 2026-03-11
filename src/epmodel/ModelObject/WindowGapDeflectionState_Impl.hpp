/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_WINDOWGAPDEFLECTIONSTATE_IMPL_HPP
#define EPMODEL_WINDOWGAPDEFLECTIONSTATE_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API WindowGapDeflectionState_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~WindowGapDeflectionState_Impl() override = default;

      double deflectedThickness() const;
      bool setDeflectedThickness(double deflectedThickness);

      double initialTemperature() const;
      bool setInitialTemperature(double initialTemperature);

      double initialPressure() const;
      bool setInitialPressure(double initialPressure);
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
