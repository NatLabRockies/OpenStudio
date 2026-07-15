/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETRETURNAIR_IMPL_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETRETURNAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelTemperatureSensorOffsetReturnAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelTemperatureSensorOffsetReturnAir_Impl() override = default;

      double temperatureSensorOffset() const;
      bool isTemperatureSensorOffsetDefaulted() const;
      bool setTemperatureSensorOffset(double temperatureSensorOffset);
      void resetTemperatureSensorOffset();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
