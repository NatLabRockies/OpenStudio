/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCOILSUPPLYAIR_IMPL_HPP
#define EPMODEL_FAULTMODELTEMPERATURESENSOROFFSETCOILSUPPLYAIR_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {
  namespace detail {

    class EPMODEL_API FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~FaultModelTemperatureSensorOffsetCoilSupplyAir_Impl() override = default;

      /** @name Reference Sensor Offset */
      //@{
      double referenceSensorOffset() const;
      bool isReferenceSensorOffsetDefaulted() const;
      bool setReferenceSensorOffset(double referenceSensorOffset);
      void resetReferenceSensorOffset();
      //@}
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
