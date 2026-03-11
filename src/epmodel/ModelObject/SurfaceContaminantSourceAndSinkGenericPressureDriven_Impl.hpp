/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICPRESSUREDRIVEN_IMPL_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICPRESSUREDRIVEN_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceContaminantSourceAndSinkGenericPressureDriven_Impl() override = default;

      boost::optional<double> designGenerationRateCoefficient() const;
      bool setDesignGenerationRateCoefficient(double designGenerationRateCoefficient);
      void resetDesignGenerationRateCoefficient();

      boost::optional<double> generationExponent() const;
      bool setGenerationExponent(double generationExponent);
      void resetGenerationExponent();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
