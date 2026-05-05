/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAKAGERATIO_IMPL_HPP
#define EPMODEL_AIRFLOWNETWORKDISTRIBUTIONCOMPONENTLEAKAGERATIO_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace epmodel {

  namespace detail {

    class EPMODEL_API AirflowNetworkDistributionComponentLeakageRatio_Impl : public ModelObject_Impl
    {
     public:
      using ModelObject_Impl::ModelObject_Impl;
      virtual ~AirflowNetworkDistributionComponentLeakageRatio_Impl() override = default;

      boost::optional<double> effectiveLeakageRatio() const;
      bool setEffectiveLeakageRatio(double effectiveLeakageRatio);
      void resetEffectiveLeakageRatio();

      double maximumFlowRate() const;
      bool setMaximumFlowRate(double maximumFlowRate);

      double referencePressureDifference() const;
      bool setReferencePressureDifference(double referencePressureDifference);

      double airMassFlowExponent() const;
      bool isAirMassFlowExponentDefaulted() const;
      bool setAirMassFlowExponent(double airMassFlowExponent);
      void resetAirMassFlowExponent();
    };

  }  // namespace detail
}  // namespace epmodel
}  // namespace openstudio

#endif
