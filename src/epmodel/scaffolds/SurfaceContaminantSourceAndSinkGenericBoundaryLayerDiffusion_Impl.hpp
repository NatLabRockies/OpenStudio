/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICBOUNDARYLAYERDIFFUSION_IMPL_HPP
#define EPMODEL_SURFACECONTAMINANTSOURCEANDSINKGENERICBOUNDARYLAYERDIFFUSION_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~SurfaceContaminantSourceAndSinkGenericBoundaryLayerDiffusion_Impl() override = default;

      boost::optional<double> massTransferCoefficient() const;
      bool setMassTransferCoefficient(double massTransferCoefficient);
      void resetMassTransferCoefficient();

      boost::optional<double> henryAdsorptionConstantorPartitionCoefficient() const;
      bool setHenryAdsorptionConstantorPartitionCoefficient(double henryAdsorptionConstantorPartitionCoefficient);
      void resetHenryAdsorptionConstantorPartitionCoefficient();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
