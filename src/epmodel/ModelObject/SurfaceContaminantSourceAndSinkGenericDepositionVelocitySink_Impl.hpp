/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONVELOCITYSINK_IMPL_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICDEPOSITIONVELOCITYSINK_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceContaminantSourceAndSinkGenericDepositionVelocitySink_Impl() override = default;

      boost::optional<double> depositionVelocity() const;
      bool setDepositionVelocity(double depositionVelocity);
      void resetDepositionVelocity();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
