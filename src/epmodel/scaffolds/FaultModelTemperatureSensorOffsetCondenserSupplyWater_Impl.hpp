/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCONDENSERSUPPLYWATER_IMPL_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCONDENSERSUPPLYWATER_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelTemperatureSensorOffsetCondenserSupplyWater_Impl() override = default;

      double referenceSensorOffset() const;
      bool isReferenceSensorOffsetDefaulted() const;
      bool setReferenceSensorOffset(double referenceSensorOffset);
      void resetReferenceSensorOffset();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
