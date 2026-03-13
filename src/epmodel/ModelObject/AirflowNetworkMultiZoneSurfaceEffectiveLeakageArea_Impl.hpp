/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKMULTIZONESURFACEEFFECTIVELEAKAGEAREA_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkMultiZoneSurfaceEffectiveLeakageArea_Impl() override = default;

      double effectiveLeakageArea() const;
      bool setEffectiveLeakageArea(double effectiveLeakageArea);

      double dischargeCoefficient() const;
      bool setDischargeCoefficient(double dischargeCoefficient);
      bool isDischargeCoefficientDefaulted() const;
      void resetDischargeCoefficient();

      double referencePressureDifference() const;
      bool setReferencePressureDifference(double referencePressureDifference);
      bool isReferencePressureDifferenceDefaulted() const;
      void resetReferencePressureDifference();

      double airMassFlowExponent() const;
      bool setAirMassFlowExponent(double airMassFlowExponent);
      bool isAirMassFlowExponentDefaulted() const;
      void resetAirMassFlowExponent();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
